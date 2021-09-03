/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recMediaData.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 MediaData records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018 ~ 2019, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recMediaData.h>

#include <rec/recAssociate.h>
#include <rec/recMedia.h>

#include <wx/file.h>

recMediaData::recMediaData( const recMediaData& n )
{
    f_id = n.f_id;
    f_title = n.f_title;
    f_data = n.f_data;
    f_type = n.f_type;
    f_privacy = n.f_privacy;
    f_copyright = n.f_copyright;
    f_file = f_file;
}

void recMediaData::Clear()
{
    f_id = 0;
    f_title.clear();
    f_data.Clear();
    f_type = Mime::null_mime;
    f_privacy = 0;
    f_copyright.clear();
    f_file.clear();
}

void recMediaData::Save( const wxString & dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO %q.MediaData (title, data, type, privacy, copyright, file)"
            " VALUES ('%q', x'%q', %d, %d, '%q', '%q');",
            UTF8_( dbname ), UTF8_( f_title ), UTF8_( GetBlobFormatStr( f_data ) ),
            f_type, f_privacy, UTF8_( f_copyright ), UTF8_( f_file )
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists( dbname ) )
        {
            // Add new record
            sql.Format(
                "INSERT INTO %q.MediaData (id, title, data, type, privacy, copyright, file)"
                " VALUES (" ID ", '%q', x'%q', %d, %d, '%q', '%q');",
                UTF8_( dbname ), f_id, UTF8_( f_title ), UTF8_( GetBlobFormatStr( f_data ) ),
                f_type, f_privacy, UTF8_( f_copyright ), UTF8_( f_file )
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE %q.MediaData SET title='%q', data=x'%q', type=%d,"
                " privacy=%d, copyright='%q', file='%q'"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_( f_title ), UTF8_( GetBlobFormatStr( f_data ) ),
                f_type, f_privacy, UTF8_( f_copyright ), UTF8_( f_file ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recMediaData::Read( const wxString & dbname )
{
    wxSQLite3StatementBuffer sql;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, data, type, privacy, copyright, file"
        " FROM %q.MediaData WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    if ( result.Eof() )
    {
        Clear();
        return false;
    }
    f_data.Clear();
    f_title = result.GetAsString( 0 );
    result.GetBlob( 1, f_data );
    f_type = Mime( result.GetInt( 2 ) );
    f_privacy = result.GetInt( 3 );
    f_copyright = result.GetAsString( 4 );
    f_file = result.GetAsString( 5 );
    return true;
}

bool recMediaData::ReadID( idt id, idt assID )
{
    wxString dbname = recAssociate::GetPath( assID );
    if ( dbname.empty() ) {
        Clear();
        return false;
    }
    f_id = id;
    return Read( dbname );
}

bool recMediaData::Equivalent( const recMediaData& r2 ) const
{
    return
        f_title == r2.f_title &&
        f_data == r2.f_data   &&
        f_type == r2.f_type &&
        f_privacy == r2.f_privacy   &&
        f_copyright == r2.f_copyright   &&
        f_file == r2.f_file;
}

wxString recMediaData::GetFileName( const wxString& assDb, idt mdID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT file FROM %q.MediaData WHERE id=" ID ";", UTF8_( assDb ), mdID );
    return ExecuteStr( sql );
}

idt recMediaData::FindMedia( idt mdID, idt assID )
{
    if ( !recMedia::TableExists() ) {
        return 0;
    }
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id FROM Media WHERE data_id=" ID " AND ass_id=" ID ";", mdID, assID
    );
    return ExecuteID( sql );
}

bool recMediaData::ImportData( wxString& filename )
{
    wxFile infile( filename );
    wxFileOffset fLen = infile.Length();
    void* tmp = f_data.GetAppendBuf( fLen );
    size_t iRead = infile.Read( tmp, fLen );
    f_data.UngetAppendBuf( iRead );
    return !f_data.IsEmpty();
}

wxSQLite3Table recMediaData::GetMediaDataList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, privacy, copyright, file FROM %q.MediaData ORDER BY file;", UTF8_( dbname )
    );
    return s_db->GetTable( sql );
}

// End of recMediaData.cpp file
