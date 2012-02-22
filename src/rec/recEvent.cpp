/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event, EventTypes, EventTypeRole and
 *              RecEventPersona records.
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

//-----------------------------------------------------
//      recEvent
//-----------------------------------------------------

recEvent::recEvent( const recEvent& e )
{
    f_id       = e.f_id;
    f_title    = e.f_title;
    f_type_id  = e.f_type_id;
    f_date1_id = e.f_date1_id;
    f_date2_id = e.f_date2_id;
    f_place_id = e.f_place_id;
    f_note     = e.f_note;
}

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

    sql.Format(
        "SELECT title, type_id, date1_id, date2_id, place_id, note "
        "FROM Event WHERE id="ID";",
        f_id
    );
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
    if( !str.empty() && f_place_id != 0 ) {
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

wxString recEvent::GetDetailStr( idt id )
{
    recEvent e( id );
    return e.GetDetailStr();
}

wxString recEvent::GetTypeStr( idt id )
{
    idt typeID = ExecuteID(
        "SELECT type_id FROM Event WHERE id="ID";", id
    );
    return recEventType::GetTypeStr( typeID );
}

wxString recEvent::GetTitle( idt evID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT title FROM Event WHERE id="ID";", evID );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

idt recEvent::GetDate1ID( idt evID )
{
    if( evID == 0 ) return 0;
    return ExecuteID( "SELECT date1_id FROM Event WHERE id="ID";", evID );
}

wxString recEvent::GetDateStr( idt evID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;
    wxString str;

    sql.Format( "SELECT date1_id, date2_id FROM Event WHERE id="ID";", evID );
    result = s_db->ExecuteQuery( sql );
    if( result.Eof() ) return str;

    idt date1ID = GET_ID( result.GetInt64( 0 ) );
    idt date2ID = GET_ID( result.GetInt64( 1 ) );
    str << recDate::GetStr( date1ID );
    if( date2ID != 0 ) {
        str << _(" To ") << recDate::GetStr( date2ID );
    }
    return str;
}

wxString recEvent::GetAddressStr( idt evID )
{
    idt placeID = ExecuteID(
        "SELECT place_id FROM Event WHERE id="ID";", evID
    );
    return recPlace::GetAddressStr( placeID );
}

wxString recEvent::GetNote( idt id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT note FROM Event WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

recEventPersonaVec recEvent::GetEventPersonas()
{
    recEventPersonaVec vec;
    recEventPersona record;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, per_id, role_id, note "
        "FROM EventPersona WHERE event_id="ID";",
        f_id
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_event_id = f_id;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_per_id = GET_ID( table.GetInt64( 1 ) );
        record.f_role_id = GET_ID( table.GetInt64( 2 ) );
        record.f_note = table.GetAsString( 3 );
        vec.push_back( record );
    }
    return vec;
}

long recEvent::GetDatePoint( idt evID )
{
    recEvent ev(evID);
    recEventType::ETYPE_Grp grp = recEventType::GetGroup( ev.f_type_id );
    switch( grp )
    {
    case recEventType::ETYPE_Grp_Birth:
    case recEventType::ETYPE_Grp_Nr_Birth:
        return recDate::GetDatePoint( ev.f_date1_id, recDate::DATE_POINT_Beg );
    case recEventType::ETYPE_Grp_Death:
    case recEventType::ETYPE_Grp_Nr_Death:
        return recDate::GetDatePoint( ev.f_date1_id, recDate::DATE_POINT_End );
    }
    return recDate::GetDatePoint( ev.f_date1_id );
}


bool recEvent::DeleteFromDb( idt id )
{
    wxSQLite3StatementBuffer sql;

    // TODO: Ensure Event is removed from reference statement.
    sql.Format(
//        "UPDATE Family SET event_id=0 WHERE event_id="ID";"
        "UPDATE Individual SET birth_id=0 WHERE birth_id="ID";"
        "UPDATE Individual SET nr_birth_id=0 WHERE nr_birth_id="ID";"
        "UPDATE Individual SET death_id=0 WHERE death_id="ID";"
        "UPDATE Individual SET nr_death_id=0 WHERE nr_death_id="ID";"
        "DELETE FROM EventPersona WHERE event_id="ID";"
        "DELETE FROM ReferenceEntity "
             "WHERE entity_type=2 AND entity_id="ID";"
        "DELETE FROM Event WHERE id="ID";",
        id, id, id, id, id, id, id, id
    );
    s_db->ExecuteUpdate( sql );
    return true;
}

wxSQLite3ResultSet recEvent::GetTitleList()
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM Event ORDER BY id;"
    );
    return s_db->ExecuteQuery( sql );
}


//-----------------------------------------------------
//      recEventType
//-----------------------------------------------------

recEventType::recEventType( const recEventType& et )
{
    f_id   = et.f_id;
    f_grp  = et.f_grp;
    f_name = et.f_name;
}

void recEventType::Clear()
{
    f_id   = 0;
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

wxString recEventType::GetTypeStr( idt id )
{
    recEventType et( id );
    return et.f_name;
}

recEventType::ETYPE_Grp recEventType::GetGroup( idt id )
{
    recEventType et( id );
    return et.f_grp;
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

recEventTypeVec recEventType::ReadAllIndividual()
{
    wxSQLite3Table table = s_db->GetTable(
        "SELECT T.id AS type_id, T.grp AS grp, T.name AS type "
        "FROM EventType T, EventTypeRole R "
        "WHERE T.id=R.type_id AND R.prime=1 "
        "GROUP BY T.id HAVING COUNT(T.id)=1 "
        "ORDER BY T.id DESC;"
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

recEventTypeVec recEventType::ReadAllFamily()
{
    wxSQLite3Table table = s_db->GetTable(
        "SELECT T.id AS type_id, T.grp AS grp, T.name AS type "
        "FROM EventType T, EventTypeRole R "
        "WHERE T.id=R.type_id AND R.prime=2 "
        "GROUP BY T.id HAVING COUNT(T.id)=1 "
        "ORDER BY T.id DESC;"
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

idt recEventType::Select( SelectFilter sf )
{
    recEventTypeVec vec;
    switch( sf )
    {
    case SF_All:
        vec = recEventType::ReadAll();
        break;
    case SF_Individual:
        vec = recEventType::ReadAllIndividual();
        break;
    case SF_Family:
        vec = recEventType::ReadAllFamily();
        break;
    default:
        return 0;
    }

    wxArrayString list;
    for( size_t i = 0 ; i < vec.size() ; i++ )
    {
        list.Add( vec[i].f_name );
    }

    if( vec.size() == 0 ) return 0;
    int index = wxGetSingleChoiceIndex( wxEmptyString, _("Select Event Type"), list );
    if( index < 0 ) return 0;
    return vec[index].f_id;
}

// Return an vector of roles for this type of event
recEventTypeRoleVec recEventType::GetRoles( idt typeID )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, name FROM EventTypeRole WHERE type_id="ID" ORDER BY id DESC;",
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

recEventTypeRoleVec recEventType::GetPrimeRoles( idt typeID, int prime )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    if( prime == 0 ) {
        sql.Format(
            "SELECT id, name FROM EventTypeRole "
            "WHERE type_id="ID" AND (prime=1 OR prime=2) ORDER BY id DESC;",
            typeID
        );
    } else {
        sql.Format(
            "SELECT id, name FROM EventTypeRole "
            "WHERE type_id="ID" AND prime=%d ORDER BY id DESC;",
            typeID, prime
        );
    }
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


//-----------------------------------------------------
//      recEventTypeRole
//-----------------------------------------------------

recEventTypeRole::recEventTypeRole( const recEventTypeRole& etr )
{
    f_id       = etr.f_id;
    f_type_id  = etr.f_type_id;
    f_prime    = etr.f_prime;
    f_official = etr.f_official;
    f_name     = etr.f_name;
}

void recEventTypeRole::Clear()
{
    f_id       = 0;
    f_type_id  = 0;
    f_prime    = false;
    f_official = false;
    f_name     = wxEmptyString;
}

void recEventTypeRole::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventTypeRole (type_id, prime, official, name) "
            "VALUES ("ID", %d, %d, '%q');",
            f_type_id, f_prime, BOOL_(f_official), UTF8_(f_name)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventTypeRole (id, type_id, prime, official, name) "
                "VALUES ("ID", "ID", %d, %d, '%q');",
                f_id, f_type_id, f_prime, BOOL_(f_official), UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventTypeRole "
                "SET type_id="ID", prime=%d, official=%d, name='%q' "
                "WHERE id="ID";",
                f_type_id, f_prime, BOOL_(f_official), UTF8_(f_name), f_id
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

    sql.Format(
        "SELECT type_id, prime, official, name "
        "FROM EventTypeRole WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_type_id = GET_ID( result.GetInt64( 0 ) );
    f_prime = result.GetInt( 1 );
    f_official = result.GetBool( 2 );
    f_name = result.GetAsString( 3 );
    return true;
}

wxString recEventTypeRole::GetName( idt roleID )
{
    recEventTypeRole role( roleID );
    return role.f_name;
}

wxString recEventTypeRole::GetTypeAndRoleStr( idt roleID )
{
    recEventTypeRole role( roleID );
    return recEventType::GetTypeStr( role.f_type_id ) + " - " + role.f_name;
}

idt recEventTypeRole::Select( idt typeID, SelectFilter sf )
{
    recEventTypeRoleVec vec;
    switch(sf )
    {
    case SF_All:
        vec = recEventType::GetRoles( typeID );
        break;
    case SF_Prime:
        vec = recEventType::GetPrimeRoles( typeID );
        break;
    case SF_Prime1:
        vec = recEventType::GetPrimeRoles( typeID, 1 );
        break;
    case SF_Prime2:
        vec = recEventType::GetPrimeRoles( typeID, 2 );
        break;
    default:
        return 0;
    }
    if( vec.size() == 0 ) return 0;
    if( vec.size() == 1 ) return vec[0].f_id;

    wxArrayString list;
    for( size_t i = 0 ; i < vec.size() ; i++ )
    {
        list.Add( vec[i].f_name );
    }

    int index = wxGetSingleChoiceIndex( wxEmptyString, _("Select Event Role"), list );
    if( index < 0 ) return 0;
    return vec[index].f_id;
}


//----------------------------------------------------------


recEventPersona::recEventPersona( const recEventPersona& ep )
{
    f_id       = ep.f_id;
    f_event_id = ep.f_event_id;
    f_per_id   = ep.f_per_id;
    f_role_id  = ep.f_role_id;
    f_note     = ep.f_note;
    f_sequence = ep.f_sequence;
}

void recEventPersona::Clear()
{
    f_id       = 0;
    f_event_id = 0;
    f_per_id   = 0;
    f_role_id  = 0;
    f_note     = wxEmptyString;
    f_sequence = 0;
}

void recEventPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventPersona (event_id, per_id, role_id, note, sequence) "
            "VALUES ("ID", "ID", "ID", '%q', %ld);",
            f_event_id, f_per_id, f_role_id, UTF8_(f_note), f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventPersona (id, event_id, per_id, role_id, note, sequence) "
                "VALUES ("ID", "ID", "ID", "ID", '%q', %ld);",
                f_id, f_event_id, f_per_id, f_role_id, UTF8_(f_note), f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventPersona SET event_id="ID", per_id="ID", role_id="ID", "
                "note='%q', sequence=%ld "
                "WHERE id="ID";",
                f_event_id, f_per_id, f_role_id, UTF8_(f_note), f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventPersona::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT id, event_id, per_id, role_id, note, sequence "
        "FROM EventPersona WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_event_id = GET_ID( result.GetInt64( 1 ) );
    f_per_id   = GET_ID( result.GetInt64( 2 ) );
    f_role_id  = GET_ID( result.GetInt64( 3 ) );
    f_note     = result.GetAsString( 4 );
    f_sequence = result.GetInt( 5 );
    return true;
}

bool recEventPersona::LinkExists() const
{
    if( f_per_id == 0 || f_event_id == 0 || f_role_id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM EventPersona "
        "WHERE event_id="ID" AND per_id="ID" AND role_id="ID";",
        f_event_id, f_per_id, f_role_id
    );

    if( s_db->ExecuteScalar( sql ) == 0 ) {
        return false;
    }
    return true;
}

// End of recEvent.cpp file
