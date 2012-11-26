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

//============================================================================
//-------------------------[ recEvent ]---------------------------------------
//============================================================================

recEvent::recEvent( const recEvent& e )
{
    f_id       = e.f_id;
    f_title    = e.f_title;
    f_type_id  = e.f_type_id;
    f_date1_id = e.f_date1_id;
    f_date2_id = e.f_date2_id;
    f_place_id = e.f_place_id;
    f_note     = e.f_note;
    f_date_pt  = e.f_date_pt;
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
    f_date_pt  = 0;
}

void recEvent::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Event "
            "(title, type_id, date1_id, date2_id, place_id, note, date_pt) "
            "VALUES ('%q', "ID", "ID", "ID", "ID", '%q', %ld);",
            UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id, 
            UTF8_(f_note), f_date_pt
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Event "
                "(id, title, type_id, date1_id, date2_id, place_id, note, date_pt) "
                "VALUES ("ID", '%q', "ID", "ID", "ID", "ID", '%q', %ld);",
                f_id, UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id,
                UTF8_(f_note), f_date_pt
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Event SET "
                "title='%q', type_id="ID", date1_id="ID", date2_id="ID", place_id="ID", "
                "note='%q', date_pt=%ld "
                "WHERE id="ID";",
                UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id, 
                UTF8_(f_note), f_date_pt, f_id
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
        "SELECT title, type_id, date1_id, date2_id, place_id, note, date_pt "
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
    f_date_pt  = (long) result.GetInt( 6 );
    return true;
}

wxString recEvent::SetAutoTitle( const wxString& name1, const wxString& name2 )
{
    f_title = wxEmptyString;
    wxString n1, n2;
    if( n1.size() ) {
        n1 = name1;
        n2 = name2;
    } else {
        n1 = name2;
        n2 = name1;
    }
    wxString type = recEventType::GetTypeStr( f_type_id );
    if( type.size() ) {
        f_title << type << " of ";
    } else {
        f_title << "Unknown event for ";
    }
    if( n1.size() ) {
        f_title << n1;
    } else {
        f_title << "Unknown person";
    }
    if( n2.size() ) {
        f_title << " and " << n2;
    }
    return f_title;
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

recEventType::ETYPE_Grp recEvent::GetTypeGroup() const
{
    return recEventType::GetGroup( f_type_id );
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

recIndEventVec recEvent::GetIndividualEvents()
{
    recIndEventVec vec;
    recIndividualEvent record;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, ind_id, role_id, note, ind_seq "
        "FROM IndividualEvent WHERE event_id="ID";",
        f_id
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_event_id = f_id;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_ind_id = GET_ID( table.GetInt64( 1 ) );
        record.f_role_id = GET_ID( table.GetInt64( 2 ) );
        record.f_note = table.GetAsString( 3 );
        record.f_ind_seq = table.GetInt( 4 );
        vec.push_back( record );
    }
    return vec;
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

void recEvent::UpdateDatePoint( idt evID )
{
    recEvent ev(evID);
    ev.UpdateDatePoint();
}

void recEvent::UpdateDatePoint()
{
    recEventType::ETYPE_Grp grp = recEventType::GetGroup( f_type_id );
    switch( grp )
    {
    case recEventType::ETYPE_Grp_Birth:
    case recEventType::ETYPE_Grp_Nr_Birth:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DATE_POINT_Beg );
    case recEventType::ETYPE_Grp_Death:
    case recEventType::ETYPE_Grp_Nr_Death:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DATE_POINT_End );
    }
    f_date_pt = recDate::GetDatePoint( f_date1_id );
}

recEventVec recEvent::FindEquivRefEvents( idt indEventID )
{
    recEventVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, title, type_id, date1_id, date2_id, place_id, note FROM "
        "  Event "
        "JOIN "
        "  (SELECT DISTINCT event_id FROM "
        "   (SELECT EP.event_id, LP.ind_per_id FROM "
        "   LinkPersona LP, EventPersona EP, Event E, EventTypeRole R "
        "   WHERE LP.ref_per_id=EP.per_id AND EP.role_id=R.id AND E.id="ID" "
        "    AND R.type_id=E.type_id AND NOT R.prime=0) "
        "  JOIN "
        "   (SELECT per_id FROM EventPersona WHERE event_id="ID") "
        "  ON ind_per_id=per_id) "
        "ON id=event_id;",
        indEventID, indEventID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        recEvent e(0);
        e.f_id       = GET_ID( result.GetInt64( 0 ) );
        e.f_title    = result.GetAsString( 1 );
        e.f_type_id  = GET_ID( result.GetInt64( 2 ) );
        e.f_date1_id = GET_ID( result.GetInt64( 3 ) );
        e.f_date2_id = GET_ID( result.GetInt64( 4 ) );
        e.f_place_id = GET_ID( result.GetInt64( 5 ) );
        e.f_note     = result.GetAsString( 6 );
        vec.push_back( e );
    }
    return vec;
}

void recEvent::DeleteFromDb()
{
    if( f_id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    wxSQLite3StatementBuffer sql;

    // TODO: Ensure Event is removed from reference statement.
    sql.Format(
        "DELETE FROM EventPersona WHERE event_id="ID";"
        "DELETE FROM IndividualEvent WHERE event_id="ID";"
        "DELETE FROM FamilyEvent WHERE event_id="ID";"
        "DELETE FROM ReferenceEntity WHERE entity_type=2 AND entity_id="ID";",
        f_id, f_id, f_id, f_id
    );
    s_db->ExecuteUpdate( sql );

    Delete();
    recDate::DeleteIfOrphaned( f_date1_id );
    recDate::DeleteIfOrphaned( f_date2_id );
    recPlace::DeleteIfOrphaned( f_place_id );
    // TODO: Delete orphaned EventType and/or EventTypeRole 
    Clear();
}

void recEvent::DeleteFromDb( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEvent eve(id);
    eve.DeleteFromDb();
}

void recEvent::DeleteIfOrphaned( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal dates.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM EventPersona WHERE event_id="ID";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format(
        "SELECT COUNT(*) FROM ReferenceEntity"
        " WHERE entity_type=2 AND entity_id="ID";",
        id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format( "SELECT COUNT(*) FROM IndividualEvent WHERE event_id="ID";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    DeleteFromDb( id );
}

wxSQLite3ResultSet recEvent::GetTitleList()
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM Event ORDER BY id;"
    );
    return s_db->ExecuteQuery( sql );
}

int recEvent::GetLastPerSeqNumber( idt eventID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(per_seq) FROM EventPersona WHERE event_id="ID";",
        eventID
    );
    return s_db->ExecuteScalar( sql );
}

//============================================================================
//-------------------------[ recEventType ]-----------------------------------
//============================================================================

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

wxString recEventType::GetGroupStr( ETYPE_Grp grp )
{
    wxASSERT( grp >= 0 && grp < ETYPE_Grp_MAX );
    static wxString grparray[ETYPE_Grp_MAX] = {
        _("Unstated"),
        _("Birth"),
        _("Near Birth"),
        _("Family Union"),
        _("Other Family"),
        _("Death"),
        _("Near Death"),
        _("Other"),
        _("Personal")
    };
    return grparray[grp];
}

wxArrayString recEventType::GetGroupStrings()
{
    wxArrayString strs;
    for( size_t i = 0 ; i < ETYPE_Grp_MAX ; i++ ) {
        strs.push_back( GetGroupStr( (ETYPE_Grp) i ) );
    }
    return strs;
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

recEventTypeVec recEventType::ReadVec( unsigned filter )
{
    recEventTypeVec vec;
    if( filter == recET_FILTER_GrpNone ) {
        return vec;
    }
    wxString query = "SELECT id, grp, name FROM EventType WHERE ";
    if( filter == recET_FILTER_GrpAll ) {
        query << "NOT grp=0 ";
    } else {
        bool started = false;
        if( filter & recET_FILTER_GrpBirth ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=1 ";
        }
        if( filter & recET_FILTER_GrpNrBirth ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=2 ";
        }
        if( filter & recET_FILTER_GrpFamUnion ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=3 ";
        }
        if( filter & recET_FILTER_GrpFamOther ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=4 ";
        }
        if( filter & recET_FILTER_GrpDeath ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=5 ";
        }
        if( filter & recET_FILTER_GrpNrDeath ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=6 ";
        }
        if( filter & recET_FILTER_GrpOther ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=7 ";
        }
        if( filter & recET_FILTER_GrpPersonal ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=8 ";
        }
    }
    query << "ORDER BY id DESC;";
    wxSQLite3ResultSet result = s_db->ExecuteQuery( query );

    recEventType et;
    while( result.NextRow() ) {
        et.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        et.FSetGrp( (ETYPE_Grp) result.GetInt( 1 ) );
        et.FSetName( result.GetAsString( 2 ) );
        vec.push_back( et );
    }
    return vec;
}

// Return an vector of roles for this type of event
recEventTypeRoleVec recEventType::GetRoles( idt typeID )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, prime, official, name FROM EventTypeRole"
        " WHERE type_id="ID" ORDER BY id DESC;",
        typeID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_type_id = typeID;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_prime = table.GetInt( 1 );
        record.f_official = table.GetBool( 2 );
        record.f_name = table.GetAsString( 3 );
        vec.push_back( record );
    }
    return vec;
}

recEventTypeRoleVec recEventType::GetPrimeRoles( idt typeID, int prime )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    wxString filter;
    switch( prime )
    {
    case 0:
        filter = "NOT prime=0";
        break;
    case -1:
        filter = "prime=1 OR prime=3";
        break;
    case -2:
        filter = "prime=2 OR prime=3";
        break;
    default:
        filter = wxString::Format( "prime=%d", prime );
    }
    sql.Format(
        "SELECT id, name FROM EventTypeRole "
        "WHERE type_id="ID" AND (%q) ORDER BY id DESC;",
        typeID, UTF8_(filter)
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


//============================================================================
//-------------------------[ recEventTypeRole ]-------------------------------
//============================================================================

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

wxString recEventTypeRole::GetPrimeStr() const
{
    wxString str;
    recEventType::ETYPE_Grp group = recEventType::GetGroup( f_type_id );

    switch( group )
    {
    case recEventType::ETYPE_Grp_Birth:
    case recEventType::ETYPE_Grp_Nr_Birth:
    case recEventType::ETYPE_Grp_Death:
    case recEventType::ETYPE_Grp_Nr_Death:
    case recEventType::ETYPE_Grp_Other:
    case recEventType::ETYPE_Grp_Personal:
        switch( f_prime )
        {
        case PRIME_None:
            str = _("No");
            break;
        case PRIME_First:
            str = _("Yes");
            break;
        default:
            str = _("?");
        }
        break;
    case recEventType::ETYPE_Grp_Union:
    case recEventType::ETYPE_Grp_Family:
        switch( f_prime )
        {
        case PRIME_None:
            str = _("No");
            break;
        case PRIME_First:
            str = _("Male");
            break;
        case PRIME_Second:
            str = _("Female");
            break;
        case PRIME_Any:
            str = _("Neutral");
            break;
        default:
            str = _("?");
        }
        break;
    }
    return str;
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
        vec = recEventType::GetPrimeRoles( typeID, -1 );
        break;
    case SF_Prime2:
        vec = recEventType::GetPrimeRoles( typeID, -2 );
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

    int index = recGetSingleChoiceIndex( _("Select Event Role"), list );
    if( index < 0 ) return 0;
    return vec[index].f_id;
}

idt recEventTypeRole::FindOrCreate( const wxString& name, idt type, bool prime, bool official )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    sql.Format(
        "SELECT id FROM EventTypeRole "
        "WHERE type_id="ID" AND prime=%d AND official=%d AND name LIKE '%q';",
        type, prime, official, UTF8_(name)
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 )
    {
        // Create
        recEventTypeRole role;
        role.f_id = 0;
        role.f_type_id = type;
        role.f_prime = prime;
        role.f_official = official;
        role.f_name = name;
        role.Save();
        return role.f_id;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );


}

//============================================================================
//-------------------------[ recEventPersona ]--------------------------------
//============================================================================

recEventPersona::recEventPersona( const recEventPersona& ep )
{
    f_id       = ep.f_id;
    f_event_id = ep.f_event_id;
    f_per_id   = ep.f_per_id;
    f_role_id  = ep.f_role_id;
    f_note     = ep.f_note;
    f_per_seq  = ep.f_per_seq;
}

void recEventPersona::Clear()
{
    f_id       = 0;
    f_event_id = 0;
    f_per_id   = 0;
    f_role_id  = 0;
    f_note     = wxEmptyString;
    f_per_seq  = 0;
}

void recEventPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventPersona (event_id, per_id, role_id, note, per_seq) "
            "VALUES ("ID", "ID", "ID", '%q', %d);",
            f_event_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventPersona (id, event_id, per_id, role_id, note, per_seq) "
                "VALUES ("ID", "ID", "ID", "ID", '%q', %d);",
                f_id, f_event_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventPersona SET event_id="ID", per_id="ID", role_id="ID", "
                "note='%q', per_seq=%d "
                "WHERE id="ID";",
                f_event_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq, f_id
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
        "SELECT id, event_id, per_id, role_id, note, per_seq "
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
    f_per_seq  = result.GetInt( 5 );
    return true;
}

wxString recEventPersona::GetRoleStr( idt perID, idt typeID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ETR.name FROM EventPersona EP, EventTypeRole ETR"
        " WHERE EP.role_id=ETR.id AND EP.per_id="ID" AND ETR.type_id="ID
        " ORDER BY EP.per_seq;",
        perID, typeID
    );
    return ExecuteStr( sql );
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

//============================================================================
//-------------------------[ recIndividualEvent ]-----------------------------
//============================================================================

recIndividualEvent::recIndividualEvent( const recIndividualEvent& ep )
{
    f_id       = ep.f_id;
    f_ind_id   = ep.f_ind_id;
    f_event_id = ep.f_event_id;
    f_role_id  = ep.f_role_id;
    f_note     = ep.f_note;
    f_ind_seq  = ep.f_ind_seq;
}

void recIndividualEvent::Clear()
{
    f_id       = 0;
    f_ind_id   = 0;
    f_event_id = 0;
    f_role_id  = 0;
    f_note     = wxEmptyString;
    f_ind_seq  = 0;
}

void recIndividualEvent::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO IndividualEvent (ind_id, event_id, role_id, note, ind_seq) "
            "VALUES ("ID", "ID", "ID", '%q', %d);",
            f_ind_id, f_event_id, f_role_id, UTF8_(f_note), f_ind_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO IndividualEvent (id, ind_id, event_id, role_id, note, ind_seq) "
                "VALUES ("ID", "ID", "ID", "ID", '%q', %d);",
                f_id, f_ind_id, f_event_id, f_role_id, UTF8_(f_note), f_ind_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE IndividualEvent SET ind_id="ID", event_id="ID", role_id="ID", "
                "note='%q', ind_seq=%d "
                "WHERE id="ID";",
                f_ind_id, f_event_id, f_role_id, UTF8_(f_note), f_ind_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recIndividualEvent::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ind_id, event_id, role_id, note, ind_seq "
        "FROM IndividualEvent WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ind_id   = GET_ID( result.GetInt64( 0 ) );
    f_event_id = GET_ID( result.GetInt64( 1 ) );
    f_role_id  = GET_ID( result.GetInt64( 2 ) );
    f_note     = result.GetAsString( 3 );
    f_ind_seq  = result.GetInt( 4 );
    return true;
}

wxString recIndividualEvent::GetRoleStr( idt indID, idt typeID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ETR.name FROM IndividualEvent IE, EventTypeRole ETR"
        " WHERE IE.role_id=ETR.id AND IE.ind_id="ID" AND ETR.type_id="ID
        " ORDER BY IE.ind_seq;",
        indID, typeID
    );
    return ExecuteStr( sql );
}


//============================================================================
//-------------------------[ recFamilyEvent ]---------------------------------
//============================================================================

recFamilyEvent::recFamilyEvent( const recFamilyEvent& ep )
{
    f_id       = ep.f_id;
    f_fam_id   = ep.f_fam_id;
    f_event_id = ep.f_event_id;
    f_note     = ep.f_note;
    f_fam_seq  = ep.f_fam_seq;
}

void recFamilyEvent::Clear()
{
    f_id       = 0;
    f_fam_id   = 0;
    f_event_id = 0;
    f_note     = wxEmptyString;
    f_fam_seq  = 0;
}

void recFamilyEvent::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO FamilyEvent (fam_id, event_id, note, fam_seq) "
            "VALUES ("ID", "ID", '%q', %d);",
            f_fam_id, f_event_id, UTF8_(f_note), f_fam_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO FamilyEvent (id, fam_id, event_id, note, fam_seq) "
                "VALUES ("ID", "ID", "ID", '%q', %d);",
                f_id, f_fam_id, f_event_id, UTF8_(f_note), f_fam_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE FamilyEvent SET fam_id="ID", event_id="ID", note='%q',"
                " fam_seq=%d WHERE id="ID";",
                f_fam_id, f_event_id, UTF8_(f_note), f_fam_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamilyEvent::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT fam_id, event_id, note, fam_seq"
        " FROM FamilyEvent WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_fam_id   = GET_ID( result.GetInt64( 0 ) );
    f_event_id = GET_ID( result.GetInt64( 1 ) );
    f_note     = result.GetAsString( 2 );
    f_fam_seq  = result.GetInt( 3 );
    return true;
}

// End of recEvent.cpp file
