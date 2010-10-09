/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event, EventTypes, EventTypeRole and 
 *              RecPersonaEvent records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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

#include <rec/recEvent.h>
#include <rec/recDate.h>
#include <rec/recPlace.h>

void recEvent::Clear()
{
    f_id = 0;
    f_type_id  = 0;
    f_val      = wxEmptyString;
    f_date1_id = 0;
    f_date2_id = 0;
    f_place_id = 0;
}

void recEvent::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO Event (type_id, val, date1_id, date2_id, place_id) "
            "VALUES ("ID", '%q', "ID", "ID", "ID");",
            f_type_id, UTF8_(f_val), f_date1_id, f_date2_id, f_place_id
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO Event (id, type_id, val, date1_id, date2_id, place_id) "
                "VALUES ("ID", "ID", '%q', "ID", "ID", "ID");",
                f_id, f_type_id, UTF8_(f_val), f_date1_id, f_date2_id, f_place_id
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE Event SET type_id="ID", val='%q', date1_id="ID", date2_id="ID", place_id="ID" "
                "WHERE id="ID";", 
                f_type_id, UTF8_(f_val), f_date1_id, f_date2_id, f_place_id, f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recEvent::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM Event WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_type_id  = GET_ID( result.GetInt64( 1 ) );;
    f_val      = result.GetAsString( 2 );
    f_date1_id = GET_ID( result.GetInt64( 3 ) );;
    f_date2_id = GET_ID( result.GetInt64( 4 ) );;
    f_place_id = GET_ID( result.GetInt64( 5 ) );;
	return true;
}

wxString recEvent::GetDetailStr() const
{
    wxString str;
    str << recDate::GetStr( f_date1_id );
    if( !str.empty() ) {
        str << ", ";
    }
    str << recPlace::GetAddressStr( f_place_id );
    return str;
}

wxString recEvent::GetTypeStr() const
{
    return recEventType::GetTypeStr( f_type_id );
}

wxString recEvent::GetDateStr() const
{
    wxString str;
    str << recDate::GetStr( f_date1_id );
    if( f_date2_id != 0 ) {
        str << _(" To ") << recDate::GetStr( f_date2_id );
    }
    return str;
}

wxString recEvent::GetAddressStr() const
{
    return recPlace::GetAddressStr( f_place_id );
}

wxString recEvent::GetDetailStr( id_t id )
{
    recEvent e;
    e.f_id = id;
    e.Read();
    return e.GetDetailStr();
}

//----------------------------------------------------------


void recEventType::Clear()
{
    f_id = 0;
	f_grp  = ETYPE_Grp_Unstated;
    f_name = wxEmptyString;
}

void recEventType::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
			"INSERT INTO EventType (grp, name) VALUES (%d, '%q');", 
			f_grp, UTF8_(f_name) 
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO EventType (id, grp, name) VALUES ("ID", %d, '%q');", 
                f_id, f_grp, UTF8_(f_name)
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE EventType SET grp=%d, name='%q' WHERE id="ID";", 
                f_grp, UTF8_(f_name), f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recEventType::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT grp, name FROM EventType WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
	f_grp = (ETYPE_Grp) result.GetInt( 0 );
    f_name = result.GetAsString( 1 );
	return true;
}

wxString recEventType::GetTypeStr( id_t id )
{
    recEventType et;
    et.f_id = id;
    et.Read();
    return et.f_name;
}

//----------------------------------------------------------


void recEventTypeRole::Clear()
{
    f_id = 0;
	f_type_id = 0;
    f_name    = wxEmptyString;
}

void recEventTypeRole::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
            "INSERT INTO EventTypeRole (type_id, name) VALUES ("ID", '%q');",
            f_type_id, UTF8_(f_name) 
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO EventTypeRole (id, type_id, name) VALUES ("ID", "ID", '%q');", 
                f_id, f_type_id, UTF8_(f_name)
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE EventTypeRole SET type_id="ID", name='%q' WHERE id="ID";", 
                f_type_id, UTF8_(f_name), f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recEventTypeRole::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM EventTypeRole WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_type_id = GET_ID( result.GetInt64( 1 ) );
    f_name = result.GetAsString( 2 );
	return true;
}


//----------------------------------------------------------


void recPersonaEvent::Clear()
{
    f_id = 0;
	f_per_id   = 0;
	f_event_id = 0;
	f_role_id  = 0;
	f_note     = wxEmptyString;
}

void recPersonaEvent::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO PersonaEvent (per_id, event_id, role_id, note) "
            "VALUES ("ID", "ID", "ID", '%q');",
            f_per_id, f_event_id, f_role_id, UTF8_(f_note)
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO PersonaEvent (id, per_id, event_id, role_id, note) "
                "VALUES ("ID", "ID", "ID", "ID", '%q');",
                f_id, f_per_id, f_event_id, f_role_id, UTF8_(f_note)
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE PersonaEvent SET per_id="ID", event_id="ID", role_id="ID", note='%q' "
                "WHERE id="ID";", 
                f_per_id, f_event_id, f_role_id, UTF8_(f_note), f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recPersonaEvent::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM PersonaEvent WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_per_id   = GET_ID( result.GetInt64( 1 ) );
    f_event_id = GET_ID( result.GetInt64( 2 ) );
    f_role_id  = GET_ID( result.GetInt64( 3 ) );
    f_note     = result.GetAsString( 4 );
	return true;
}

// End of recEvent.cpp file
