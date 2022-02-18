/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Media records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018 ~ 2021, Nick Matthews.
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

#include <rec/recMedia.h>
#include <rec/recMediaData.h>

recMedia::recMedia( const recMedia& n )
{
    f_id = n.f_id;
    f_data_id = n.f_data_id;
    f_ass_id = n.f_ass_id;
    f_ref_id = n.f_ref_id;
    f_ref_seq = n.f_ref_seq;
    f_privacy = n.f_privacy;
    f_title = n.f_title;
    f_note = n.f_note;
}

void recMedia::Clear()
{
    f_id = 0;
    f_data_id = 0;
    f_ass_id = 0;
    f_ref_id = 0;
    f_ref_seq = 0;
    f_privacy = 0;
    f_title.clear();
    f_note.clear();
}

void recMedia::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Media (data_id, ass_id, ref_id, ref_seq, privacy, title, note)"
            " VALUES (" ID ", " ID ", " ID ", %d, %d, '%q', '%q');",
            UTF8_( dbname ), f_data_id, f_ass_id, f_ref_id, f_ref_seq, f_privacy, UTF8_( f_title ), UTF8_( f_note )
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Media (id, data_id, ass_id, ref_id, ref_seq, privacy, title, note)"
                " VALUES (" ID ", " ID ", " ID ", " ID ", %d, %d, '%q', '%q');",
                UTF8_( dbname ), f_id, f_data_id, f_ass_id, f_ref_id, f_ref_seq, f_privacy, UTF8_( f_title ), UTF8_( f_note )
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Media"
                " SET data_id=" ID ", ass_id=" ID ", ref_id=" ID ", ref_seq=%d, privacy=%d,"
                " title='%q', note='%q' WHERE id=" ID ";",
                UTF8_( dbname ), f_data_id, f_ass_id, f_ref_id, f_ref_seq, f_privacy, UTF8_( f_title ), UTF8_( f_note ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recMedia::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT data_id, ass_id, ref_id, ref_seq, privacy, title, note"
        " FROM \"%s\".Media WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_data_id = GET_ID( result.GetInt64( 0 ) );
    f_ass_id = GET_ID( result.GetInt64( 1 ) );
    f_ref_id = GET_ID( result.GetInt64( 2 ) );
    f_ref_seq = result.GetInt( 3 );
    f_privacy = result.GetInt( 4 );
    f_title = result.GetAsString( 5 );
    f_note = result.GetAsString( 6 );
    return true;
}

bool recMedia::Equivalent( const recMedia& r2 ) const
{
    return
        f_data_id == r2.f_data_id &&
        f_ass_id == r2.f_ass_id   &&
        f_ref_id == r2.f_ref_id   &&
        f_ref_seq == r2.f_ref_seq &&
        f_privacy == r2.f_privacy &&
        f_title == r2.f_title     &&
        f_note == r2.f_note
    ;
}

idt recMedia::Create( idt mdID, idt assID, idt refID )
{
    recMedia med( 0 );
    recMediaData md( mdID, assID );

    med.f_data_id = mdID;
    med.f_ass_id = assID;
    med.f_ref_id = refID;
    med.f_ref_seq = recMedia::GetNextRefSeq( refID );
    med.f_privacy = md.FGetPrivacy();
    med.f_title = md.FGetTitle();
    med.Save();
    return med.f_id;
}

int recMedia::GetNextRefSeq( idt refID )
{
    return ExecuteInt( "SELECT MAX(ref_seq) FROM Media WHERE ref_id=" ID ";", refID ) + 1;
}

wxString recMedia::GetTitle( idt medID, const wxString& dbname )
{
    return ExecuteStr( "SELECT title FROM \"%s\".Media WHERE id=" ID ";", UTF8_( dbname ), medID );
}

wxSQLite3Table recMedia::GetMediaList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, ass_id, ref_id, title FROM \"%s\".Media ORDER BY id;",
        UTF8_( dbname )
    );
    return s_db->GetTable( sql );
}

wxSQLite3Table recMedia::GetMediaList( idt offset, int limit, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, ass_id, ref_id, title FROM \"%s\".Media ORDER BY id LIMIT " ID ", %d;",
        UTF8_( dbname ), offset, limit
    );
    return s_db->GetTable( sql );
}

// End of recMedia.cpp file
