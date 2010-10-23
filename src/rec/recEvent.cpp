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
    f_id       = 0;
    f_title    = wxEmptyString;
    f_type_id  = 0;
    f_date1_id = 0;
    f_date2_id = 0;
    f_place_id = 0;
    f_note     = wxEmptyString;
}

void recEvent::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO Event (title, type_id, date1_id, date2_id, place_id, note) "
            "VALUES ('%q', "ID", "ID", "ID", "ID", '%q');",
            UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id, UTF8_(f_note)
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO Event (id, title, type_id, date1_id, date2_id, place_id, note) "
                "VALUES ("ID", '%q', "ID", "ID", "ID", "ID", '%q');",
                f_id, UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id, UTF8_(f_note)
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE Event SET title='%q', type_id="ID", date1_id="ID", date2_id="ID", place_id="ID", note='%q' "
                "WHERE id="ID";", 
                UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id, UTF8_(f_note), f_id
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

	sql.Format( "SELECT title, type_id, date1_id, date2_id, place_id, note FROM Event WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_title    = result.GetAsString( 0 );
    f_type_id  = GET_ID( result.GetInt64( 1 ) );
    f_date1_id = GET_ID( result.GetInt64( 2 ) );
    f_date2_id = GET_ID( result.GetInt64( 3 ) );
    f_place_id = GET_ID( result.GetInt64( 4 ) );
    f_note     = result.GetAsString( 5 );
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
    recEvent e( id );
    return e.GetDetailStr();
}

wxString recEvent::GetTypeStr( id_t id )
{
    id_t typeID = ExecuteID(
        "SELECT type_id FROM Event WHERE id="ID";", id
    );
    return recEventType::GetTypeStr( typeID );
}

wxString recEvent::GetTitle( id_t id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT title FROM Event WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

wxString recEvent::GetNote( id_t id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT note FROM Event WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

id_t recEvent::FindReference( id_t eventID )
{
    return ExecuteID(
        "SELECT ref_id FROM ReferenceEntity "
        "WHERE entity_type=2 AND entity_id="ID";",
        eventID
    );
}

recPersonaEventVec recEvent::GetPersonaEvents()
{
    recPersonaEvent record;
	wxSQLite3StatementBuffer sql;

	sql.Format( "SELECT * FROM PersonaEvent WHERE event_id="ID";", f_id );
    wxSQLite3Table table = s_db->GetTable( sql );

    recPersonaEventVec vec( table.GetRowCount() );
    record.f_event_id = f_id;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_per_id = GET_ID( table.GetInt64( 1 ) );
        record.f_role_id = GET_ID( table.GetInt64( 3 ) );
        record.f_note = table.GetAsString( 4 );
        vec.push_back( record );
    }
	return vec;
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
    recEventType et( id );
    return et.f_name;
}

recEventTypeVec recEventType::ReadAll()
{
    wxSQLite3Table table = s_db->GetTable( 
        "SELECT id, grp, name FROM EventType ORDER BY id DESC;"
    );

    recEventType et;
    recEventTypeVec vec;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        et.f_id = GET_ID( table.GetInt64( 0 ) );
		et.f_grp = (ETYPE_Grp) table.GetInt( 1 );
        et.f_name = table.GetAsString( 2 );
        if( et.f_id != 0 ) {
            vec.push_back( et );
        }
    }
	return vec;
}

id_t recEventType::Select()
{
	recEventTypeVec vec = recEventType::ReadAll();
    wxArrayString list;
    for( size_t i = 0 ; i < vec.size() ; i++ )
    {
        list.Add( vec[i].f_name );
    }

    int index = wxGetSingleChoiceIndex( wxEmptyString, _("Select Event Type"), list );
    if( index < 0 ) return 0;
	return vec[index].f_id;
}

// Return an vector of roles for this type of event
recEventTypeRoleVec recEventType::GetRoles( id_t typeID )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
	wxSQLite3StatementBuffer sql;

	sql.Format(
        "SELECT id, name FROM EventTypeRole WHERE type_id="ID";", 
        typeID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_type_id = typeID;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_name = table.GetAsString( 1 );
        vec.push_back( record );
    }
	return vec;
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
