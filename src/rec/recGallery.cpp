/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recGallery.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Gallery records.
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

#include <rec/recGallery.h>


recGallery::recGallery( const recGallery& at )
{
    f_id = at.f_id;
    f_title = at.f_title;
    f_note = at.f_note;
}

void recGallery::Clear()
{
    f_id = 0;
    f_title = "";
    f_note = "";
}

void recGallery::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Gallery (title, note) VALUES ('%q', '%q');",
            UTF8_( f_title ), UTF8_( f_note )
            );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Gallery (id, title, note) "
                "VALUES (" ID ", '%q', '%q');",
                f_id, UTF8_( f_title ), UTF8_( f_note )
                );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Gallery SET title='%q', note='%q' WHERE id=" ID ";",
                UTF8_( f_title ), UTF8_( f_note ), f_id
                );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recGallery::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT title, note FROM Gallery WHERE id=" ID ";", f_id );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_title = result.GetAsString( 0 );
    f_note = result.GetAsString( 1 );
    return true;
}

bool recGallery::Equivalent( const recGallery& r2 ) const
{
    return
        f_title == r2.f_title &&
        f_note == r2.f_note
    ;
}

// End of recAssociate.cpp file
