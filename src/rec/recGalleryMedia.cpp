#include "..\..\include\rec\recGalleryMedia.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recGalleryMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 recGalleryMedia records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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

#include <rec/recGalleryMedia.h>


recGalleryMedia::recGalleryMedia( const recGalleryMedia& n )
{
    f_id = n.f_id;
    f_title = n.f_title;
    f_gal_id = n.f_gal_id;
    f_med_id = n.f_med_id;
    f_med_seq = n.f_med_seq;
}

void recGalleryMedia::Clear()
{
    f_id = 0;
    f_title = "";
    f_gal_id = 0;
    f_med_id = 0;
    f_med_seq = 0;
}

void recGalleryMedia::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO GalleryMedia (title, gal_id, med_id, med_seq)"
            " VALUES ('%q', " ID ", " ID ", %d);",
            UTF8_( f_title ), f_gal_id, f_med_id, f_med_seq
            );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO GalleryMedia (id, title, gal_id, med_id, med_seq)"
                " VALUES (" ID ", '%q', " ID ", " ID ", %d);",
                f_id, UTF8_( f_title ), f_gal_id, f_med_id, f_med_seq
                );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE GalleryMedia SET title='%q', gal_id=" ID ", med_id=" ID ", med_seq=%d WHERE id=" ID ";",
                UTF8_( f_title ), f_gal_id, f_med_id, f_med_seq, f_id
                );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recGalleryMedia::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, gal_id, med_id, med_seq"
        " FROM GalleryMedia WHERE id=" ID ";",
        f_id
        );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_title = result.GetAsString( 0 );
    f_gal_id = GET_ID( result.GetInt64( 1 ) );
    f_med_id = GET_ID( result.GetInt64( 2 ) );
    f_med_seq = result.GetInt( 3 );
    return true;
}

bool recGalleryMedia::Equivalent( const recGalleryMedia& r2 ) const
{
    return
        f_title == r2.f_title &&
        f_gal_id == r2.f_gal_id   &&
        f_med_id == r2.f_med_id   &&
        f_med_seq == r2.f_med_seq;
}

void recGalleryMedia::SetNextMedSequence( idt galID )
{
    f_med_seq = recDb::ExecuteInt(
        "SELECT MAX(med_seq) FROM GalleryMedia WHERE gal_id=" ID ";", galID ) + 1;
}

wxString recGalleryMedia::GetTitle( idt galID, idt medID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT title FROM GalleryMedia WHERE gal_id=" ID " AND med_id=" ID ";",
        galID, medID
    );
    return recDb::ExecuteStr( sql );
}


// End of recGalleryMedia.cpp file
