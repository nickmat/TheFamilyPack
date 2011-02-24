/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recSource.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Source record.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22 November 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include <rec/recSource.h>

recSource::recSource( const recSource& s )
{
    f_higher_id    = s.f_higher_id;
    f_sub_date1_id = s.f_sub_date1_id;
    f_sub_date2_id = s.f_sub_date2_id;
    f_sub_place_id = s.f_sub_place_id;
    f_loc_place_id = s.f_loc_place_id;
    f_res_id       = s.f_res_id;
    f_comments     = s.f_comments;
}

void recSource::Clear()
{
    f_higher_id    = 0;
    f_sub_date1_id = 0;
    f_sub_date2_id = 0;
    f_sub_place_id = 0;
    f_loc_place_id = 0;
    f_res_id       = 0;
    f_comments     = wxEmptyString;
}

void recSource::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Source (higher_id, sub_date1_id, sub_date2_id, "
            "sub_place_id, loc_place_id, res_id, comments) "
            "VALUES ("ID", "ID", "ID", "ID", "ID", "ID", '%q');",
            f_higher_id, f_sub_date1_id, f_sub_date2_id, f_sub_place_id,
            f_loc_place_id, f_res_id, UTF8_(f_comments)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Source (id, higher_id, sub_date1_id, sub_date2_id, "
                "sub_place_id, loc_place_id, res_id, comments) "
                "VALUES ("ID", "ID", "ID", "ID", "ID", "ID", "ID", '%q');",
                f_id, f_higher_id, f_sub_date1_id, f_sub_date2_id, f_sub_place_id,
                f_loc_place_id, f_res_id, UTF8_(f_comments)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Source SET higher_id="ID", sub_date1_id="ID", sub_date2_id="ID", "
                "sub_place_id="ID", loc_place_id="ID", res_id="ID", comments='%q' "
                "WHERE id="ID";",
                f_higher_id, f_sub_date1_id, f_sub_date2_id, f_sub_place_id,
                f_loc_place_id, f_res_id, UTF8_(f_comments), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recSource::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT higher_id, sub_date1_id, sub_date2_id, "
        "sub_place_id, loc_place_id, res_id, comments "
        "FROM Source WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_higher_id    = GET_ID( result.GetInt64( 0 ) );
    f_sub_date1_id = GET_ID( result.GetInt64( 1 ) );
    f_sub_date2_id = GET_ID( result.GetInt64( 2 ) );
    f_sub_place_id = GET_ID( result.GetInt64( 3 ) );
    f_loc_place_id = GET_ID( result.GetInt64( 4 ) );
    f_res_id       = GET_ID( result.GetInt64( 5 ) );
    f_comments     = result.GetAsString( 6 );
    return true;
}

// End of recVersion.cpp file
