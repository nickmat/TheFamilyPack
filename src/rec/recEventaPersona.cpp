/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventaPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventaPersona records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015, Nick Matthews.
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

#include <rec/recEventaPersona.h>

#include <rec/recEvent.h>
#include <rec/recEventa.h>
#include <rec/recPlace.h>
#include <rec/recIndividual.h>

//============================================================================
//--------------------------[ recEventaPersona ]------------------------------
//============================================================================

recEventaPersona::recEventaPersona( const recEventaPersona& ep )
{
    f_id           = ep.f_id;
    f_eventa_id    = ep.f_eventa_id;
    f_per_id       = ep.f_per_id;
    f_role_id      = ep.f_role_id;
    f_note         = ep.f_note;
    f_per_seq      = ep.f_per_seq;
}

void recEventaPersona::Clear()
{
    f_id           = 0;
    f_eventa_id   = 0;
    f_per_id       = 0;
    f_role_id      = 0;
    f_note         = wxEmptyString;
    f_per_seq      = 0;
}

void recEventaPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventaPersona (eventa_id, per_id, role_id, note, per_seq) "
            "VALUES ("ID", "ID", "ID", '%q', %d);",
            f_eventa_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventaPersona (id, eventa_id, per_id, role_id, note, per_seq) "
                "VALUES ("ID", "ID", "ID", "ID", '%q', %d);",
                f_id, f_eventa_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventaPersona SET eventa_id="ID", per_id="ID", role_id="ID", "
                "note='%q', per_seq=%d "
                "WHERE id="ID";",
                f_eventa_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventaPersona::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT id, eventa_id, per_id, role_id, note, per_seq "
        "FROM EventaPersona WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_eventa_id   = GET_ID( result.GetInt64( 1 ) );
    f_per_id       = GET_ID( result.GetInt64( 2 ) );
    f_role_id      = GET_ID( result.GetInt64( 3 ) );
    f_note         = result.GetAsString( 4 );
    f_per_seq      = result.GetInt( 5 );
    return true;
}

wxString recEventaPersona::GetRoleStr( idt perID, idt typeID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ETR.name FROM EventaPersona EP, EventTypeRole ETR"
        " WHERE EP.role_id=ETR.id AND EP.per_id="ID" AND ETR.type_id="ID
        " ORDER BY EP.per_seq;",
        perID, typeID
    );
    return ExecuteStr( sql );
}

bool recEventaPersona::LinkExists() const
{
    if( f_per_id == 0 || f_eventa_id == 0 || f_role_id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM EventaPersona "
        "WHERE eventa_id="ID" AND per_id="ID" AND role_id="ID";",
        f_eventa_id, f_per_id, f_role_id
    );

    if( s_db->ExecuteScalar( sql ) == 0 ) {
        return false;
    }
    return true;
}


// End of recEventaPersona.cpp file
