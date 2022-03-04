/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recIndPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 IndividualPersona table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

#include <rec/recIndPersona.h>


//============================================================================
//                 recIndividualPersona
//============================================================================

recIndividualPersona::recIndividualPersona( const recIndividualPersona& d )
{
    f_id     = d.f_id;
    f_ind_id = d.f_ind_id;
    f_per_id = d.f_per_id;
    f_conf   = d.f_conf;
    f_note   = d.f_note;
}

void recIndividualPersona::Clear()
{
    f_id     = 0;
    f_ind_id = 0;
    f_per_id = 0;
    f_conf   = 0;
    f_note   = wxEmptyString;
}

void recIndividualPersona::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".IndividualPersona "
            "(ind_id, per_id, conf, note) "
            "VALUES (" ID ", " ID ", %f, '%q');",
            UTF8_( dbname ), f_ind_id, f_per_id, f_conf, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".IndividualPersona "
                "(id, ind_id, per_id, conf, note) "
                "VALUES (" ID ", " ID ", " ID ", %f, '%q');",
                UTF8_( dbname ), f_id, f_ind_id, f_per_id, f_conf, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".IndividualPersona SET ind_id=" ID ", per_id=" ID ", "
                "conf=%f, note='%q' "
                "WHERE id=" ID ";",
                f_ind_id, f_per_id, f_conf,
                UTF8_( dbname ), UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recIndividualPersona::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ind_id, per_id, conf, note"
        " FROM \"%s\".IndividualPersona WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ind_id = GET_ID( result.GetInt64( 0 ) );
    f_per_id = GET_ID( result.GetInt64( 1 ) );
    f_conf   = result.GetDouble( 2 );
    f_note   = result.GetAsString( 3 );
    return true;
}

bool recIndividualPersona::Equivalent( const recIndividualPersona& r2 ) const
{
    return
        f_ind_id == r2.f_ind_id &&
        f_per_id == r2.f_per_id &&
        f_conf == r2.f_conf &&
        f_note == r2.f_note
    ;
}

/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recIndividualPersona::Find( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_ind_id == 0 || f_per_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, conf, note FROM \"%s\".IndividualPersona "
        "WHERE ind_id=" ID " AND per_id=" ID ";",
        UTF8_( dbname ), f_ind_id, f_per_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_conf = result.GetDouble( 1 );
    f_note = result.GetAsString( 2 );
    return true;
}

// End of recLink.cpp file
