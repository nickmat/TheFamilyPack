/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event and other tables.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd October 2010
 * Copyright:   Copyright (c) 2010-2013, Nick Matthews.
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
#include <rec/recEventum.h>
#include <rec/recPlace.h>
#include <rec/recIndividual.h>

//============================================================================
//-------------------------[ recEvent ]---------------------------------------
//============================================================================

recEvent::recEvent( const recEvent& e )
{
    f_id        = e.f_id;
    f_title     = e.f_title;
    f_higher_id = e.f_higher_id;
    f_type_id   = e.f_type_id;
    f_date1_id  = e.f_date1_id;
    f_date2_id  = e.f_date2_id;
    f_place_id  = e.f_place_id;
    f_note      = e.f_note;
    f_date_pt   = e.f_date_pt;
}

void recEvent::Clear()
{
    f_id        = 0;
    f_title     = wxEmptyString;
    f_higher_id = 0;
    f_type_id   = 0;
    f_date1_id  = 0;
    f_date2_id  = 0;
    f_place_id  = 0;
    f_note      = wxEmptyString;
    f_date_pt   = 0;
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
            "(title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt) "
            "VALUES ('%q', "ID", "ID", "ID", "ID", "ID", '%q', %ld);",
            UTF8_(f_title), f_higher_id, f_type_id, f_date1_id, f_date2_id, f_place_id,
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
                "(id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt) "
                "VALUES ("ID", '%q', "ID", "ID", "ID", "ID", "ID", '%q', %ld);",
                f_id, UTF8_(f_title), f_higher_id, f_type_id, f_date1_id, f_date2_id, f_place_id,
                UTF8_(f_note), f_date_pt
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Event SET "
                "title='%q', higher_id="ID", type_id="ID", date1_id="ID", date2_id="ID", place_id="ID", "
                "note='%q', date_pt=%ld "
                "WHERE id="ID";",
                UTF8_(f_title), f_higher_id, f_type_id, f_date1_id, f_date2_id, f_place_id,
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
        "SELECT title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt "
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
    f_title     = result.GetAsString( 0 );
    f_higher_id = GET_ID( result.GetInt64( 1 ) );
    f_type_id   = GET_ID( result.GetInt64( 2 ) );
    f_date1_id  = GET_ID( result.GetInt64( 3 ) );
    f_date2_id  = GET_ID( result.GetInt64( 4 ) );
    f_place_id  = GET_ID( result.GetInt64( 5 ) );
    f_note      = result.GetAsString( 6 );
    f_date_pt   = (long) result.GetInt( 7 );
    return true;
}

idt recEvent::CreateFromEventum( idt erID )
{
    recEvent e(0);
    recEventum er(erID);

    e.f_title    = er.f_title;
    e.f_type_id  = er.f_type_id;
    e.f_date1_id = recDate::Create( er.f_date1_id );
    e.f_date2_id = recDate::Create( er.f_date2_id );
    e.f_place_id = recPlace::Create( er.f_place_id );
    e.f_note     = er.f_note;
    e.f_date_pt  = er.f_date_pt;

    e.Save();
    return e.FGetID();
}

wxString recEvent::SetAutoTitle( const wxString& name1, const wxString& name2 )
{
    f_title = wxEmptyString;
    wxString n1, n2;
    if( name1.size() ) {
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

void recEvent::SetDatePeriodToInclude( idt eID, idt dateID )
{
    recEvent e(eID);
    recDate date(dateID);
    recDate date1(e.FGetDate1ID());
    recDate date2(e.FGetDate2ID());

    if( date.FGetJdn() < date1.FGetJdn() ) {
        e.FSetDate1ID( date.FGetID() );
        if( date2.FGetID() == 0 ) {
            e.FSetDate2ID( date1.FGetID() );
            e.Save();
        } else {
            e.Save();
            recDate::DeleteIfOrphaned( date1.FGetID() );
        }
    } else if(
        ( e.FGetDate2ID() == 0 && date.FGetJdn() > date1.FGetJdn() ) ||
        ( e.FGetDate2ID() != 0 && date.FGetJdn() > date2.FGetJdn() )
    ) {
        e.FSetDate2ID( date.FGetID() );
        e.Save();
        recDate::DeleteIfOrphaned( date2.FGetID() );
    }
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

recET_GRP recEvent::GetTypeGroup() const
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

bool recEvent::IsFamilyEvent( idt eveID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT ET.grp FROM Event E, EventType ET"
        " WHERE E.type_id=ET.id AND E.id="ID";",
        eveID
    );
    result = s_db->ExecuteQuery( sql );
    recET_GRP grp = (recET_GRP) result.GetInt( 0 );
    if( grp == recET_GRP_FamUnion || recET_GRP_FamOther ) {
        return true;
    }
    return false;
}

recIndEventVec recEvent::GetIndividualEvents( idt eID )
{
    recIndEventVec vec;
    recIndividualEvent record;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, ind_id, role_id, note, ind_seq"
        " FROM IndividualEvent WHERE event_id="ID
        " ORDER BY id;",
        eID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_event_id = eID;
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

void recEvent::UpdateDatePoint( idt evID )
{
    recEvent ev(evID);
    ev.UpdateDatePoint();
}

void recEvent::UpdateDatePoint()
{
    recET_GRP grp = recEventType::GetGroup( f_type_id );
    switch( grp )
    {
    case recET_GRP_Birth:
    case recET_GRP_NrBirth:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DATE_POINT_Beg );
    case recET_GRP_Death:
    case recET_GRP_NrDeath:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DATE_POINT_End );
    }
    f_date_pt = recDate::GetDatePoint( f_date1_id );
}

recEventumVec recEvent::FindEquivRefEvents( idt indEventID )
{
    recEventumVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, title, type_id, date1_id, date2_id, place_id, note FROM "
        "  Eventum "
        "JOIN "
        "   (SELECT EP.eventum_id FROM "
        "   IndividualEvent IE, IndividualPersona IP, EventumPersona EP "
        "   WHERE IE.event_id="ID
        "     AND IP.ind_id=IE.ind_id "
        "     AND EP.per_id=IP.per_id "
        "     AND IE.role_id=EP.role_id "
        "    GROUP BY eventum_id) "
        "ON id=eventum_id;",
        indEventID, indEventID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        recEventum e(0);
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

recEventEventumVec recEvent::GetEventEventums( idt eveID )
{
    recEventEventumVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, eventum_id, conf, note FROM "
        "  EventEventum WHERE event_id="ID";",
        eveID
    );
    result = s_db->ExecuteQuery( sql );

    recEventEventum eer(0);
    eer.FSetEventID( eveID );
    while( result.NextRow() ) {
        eer.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        eer.FSetEventumID( GET_ID( result.GetInt64( 1 ) ) );
        eer.FSetConf( result.GetDouble( 2 ) );
        eer.FSetNote( result.GetAsString( 3 ) );
        vec.push_back( eer );
    }
    return vec;
}

void recEvent::RemoveFromDatabase()
{
    if( f_id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "DELETE FROM IndividualEvent WHERE event_id="ID";"
        "DELETE FROM FamilyEvent WHERE event_id="ID";",
        f_id, f_id
    );
    s_db->ExecuteUpdate( sql );

    Delete();
    Clear();
}

void recEvent::RemoveFromDatabase( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEvent eve(id);
    eve.RemoveFromDatabase();
}

void recEvent::RemoveIncOrphansFromDatabase( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEvent eve(id);
    RemoveFromDatabase( eve.f_id );
    recDate::DeleteIfOrphaned( eve.f_date1_id );
    recDate::DeleteIfOrphaned( eve.f_date2_id );
    recPlace::DeleteIfOrphaned( eve.f_place_id );
    // TODO: Delete orphaned EventType and/or EventTypeRole
}

void recEvent::RemoveDates( idt dateID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Event SET date1_id=0, date_pt=0 WHERE date1_id="ID";"
        "UPDATE Event SET date2_id=0 WHERE date2_id="ID";",
        dateID, dateID
    );
    s_db->ExecuteUpdate( sql );
}

void recEvent::RemovePlace( idt placeID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Event SET place_id=0 WHERE place_id="ID";",
        placeID
    );
    s_db->ExecuteUpdate( sql );
}

void recEvent::DeleteIfOrphaned( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal dates.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM EventumPersona WHERE event_id="ID";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format(
        "SELECT COUNT(*) FROM ReferenceEntity"
        " WHERE entity_type=2 AND entity_id="ID";",
        id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format( "SELECT COUNT(*) FROM IndividualEvent WHERE event_id="ID";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    RemoveFromDatabase( id );
}

wxSQLite3Table recEvent::GetTitleList()
{
    return s_db->GetTable( "SELECT id, title FROM Event ORDER BY id;" );
}

wxSQLite3Table recEvent::GetTitleList( idt offset, int limit )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM Event ORDER BY id LIMIT "ID", %d;",
        offset, limit
    );
    return s_db->GetTable( sql );
}


//============================================================================
//-------------------------[ recEventEventum ]--------------------------------
//============================================================================

recEventEventum::recEventEventum( const recEventEventum& d )
{
    f_id           = d.f_id;
    f_event_id     = d.f_event_id;
    f_eventum_id   = d.f_eventum_id;
    f_conf         = d.f_conf;
    f_note         = d.f_note;
}

void recEventEventum::Clear()
{
    f_id           = 0;
    f_event_id     = 0;
    f_eventum_id   = 0;
    f_conf         = 0;
    f_note         = wxEmptyString;
}

void recEventEventum::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventEventum "
            "(event_id, eventum_id, conf, note) "
            "VALUES ("ID", "ID", %f, '%q');",
            f_event_id, f_eventum_id, f_conf, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventEventum "
                "(id, event_id, eventum_id, conf, note) "
                "VALUES ("ID", "ID", "ID", %f, '%q');",
                f_id, f_event_id, f_eventum_id, f_conf, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventEventum SET event_id="ID", eventum_id="ID", "
                "conf=%f, note='%q' "
                "WHERE id="ID";",
                f_event_id, f_eventum_id, f_conf,
                UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventEventum::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT event_id, eventum_id, conf, note "
        "FROM EventEventum WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_event_id     = GET_ID( result.GetInt64( 0 ) );
    f_eventum_id   = GET_ID( result.GetInt64( 1 ) );
    f_conf         = result.GetDouble( 2 );
    f_note         = result.GetAsString( 3 );
    return true;
}

idt recEventEventum::Create( idt eID, idt erID, double conf, const wxString& note )
{
    recEventEventum eer(0);

    eer.FSetEventID( eID );
    eer.FSetEventumID( erID );
    eer.FSetConf( conf );
    eer.FSetNote( note );
    eer.Save();

    return eer.FGetID();
}


/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recEventEventum::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_event_id == 0 || f_eventum_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, conf, note FROM EventEventum "
        "WHERE event_id="ID" AND eventum_id="ID";",
        f_event_id, f_eventum_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_conf = result.GetDouble( 1 );
    f_note = result.GetAsString( 2 );
    return true;
}

/*! Given the Event id and Eventum id, find the matching record id.
 */
idt recEventEventum::Find( idt eID, idt erID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( eID == 0 || erID == 0 ) return 0; // Only find single record

    sql.Format(
        "SELECT id FROM EventEventum "
        "WHERE event_id="ID" AND eventum_id="ID";",
        eID, erID
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        return 0;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );
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
    recET_GRP group = recEventType::GetGroup( f_type_id );

    switch( group )
    {
    case recET_GRP_Birth:
    case recET_GRP_NrBirth:
    case recET_GRP_Death:
    case recET_GRP_NrDeath:
    case recET_GRP_Other:
    case recET_GRP_Personal:
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
    case recET_GRP_FamUnion:
    case recET_GRP_FamOther:
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

idt recEventTypeRole::Find( const wxString& name, idt type, Prime prime, TriLogic official )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    wxString primeCondition;
    if( prime != PRIME_Ignore ) {
        primeCondition << " AND prime=" << prime;
    }
    wxString officialCondition;
    if( official != TRILOGIC_both ) {
        officialCondition << " AND official=" << official;
    }
    sql.Format(
        "SELECT id FROM EventTypeRole "
        "WHERE type_id="ID"%s%s AND name LIKE '%q';",
        type, UTF8_(primeCondition), UTF8_(officialCondition), UTF8_(name)
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 ) {
        return 0;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );
}

idt recEventTypeRole::FindOrCreate( const wxString& name, idt type, Prime prime, bool official )
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
//-------------------------[ recEventumPersona ]------------------------------
//============================================================================

recEventumPersona::recEventumPersona( const recEventumPersona& ep )
{
    f_id           = ep.f_id;
    f_eventum_id   = ep.f_eventum_id;
    f_per_id       = ep.f_per_id;
    f_role_id      = ep.f_role_id;
    f_note         = ep.f_note;
    f_per_seq      = ep.f_per_seq;
}

void recEventumPersona::Clear()
{
    f_id           = 0;
    f_eventum_id   = 0;
    f_per_id       = 0;
    f_role_id      = 0;
    f_note         = wxEmptyString;
    f_per_seq      = 0;
}

void recEventumPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventumPersona (eventum_id, per_id, role_id, note, per_seq) "
            "VALUES ("ID", "ID", "ID", '%q', %d);",
            f_eventum_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventumPersona (id, eventum_id, per_id, role_id, note, per_seq) "
                "VALUES ("ID", "ID", "ID", "ID", '%q', %d);",
                f_id, f_eventum_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventumPersona SET eventum_id="ID", per_id="ID", role_id="ID", "
                "note='%q', per_seq=%d "
                "WHERE id="ID";",
                f_eventum_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventumPersona::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT id, eventum_id, per_id, role_id, note, per_seq "
        "FROM EventumPersona WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_eventum_id   = GET_ID( result.GetInt64( 1 ) );
    f_per_id       = GET_ID( result.GetInt64( 2 ) );
    f_role_id      = GET_ID( result.GetInt64( 3 ) );
    f_note         = result.GetAsString( 4 );
    f_per_seq      = result.GetInt( 5 );
    return true;
}

wxString recEventumPersona::GetRoleStr( idt perID, idt typeID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ETR.name FROM EventumPersona EP, EventTypeRole ETR"
        " WHERE EP.role_id=ETR.id AND EP.per_id="ID" AND ETR.type_id="ID
        " ORDER BY EP.per_seq;",
        perID, typeID
    );
    return ExecuteStr( sql );
}

bool recEventumPersona::LinkExists() const
{
    if( f_per_id == 0 || f_eventum_id == 0 || f_role_id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM EventumPersona "
        "WHERE eventum_id="ID" AND per_id="ID" AND role_id="ID";",
        f_eventum_id, f_per_id, f_role_id
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

idt recIndividualEvent::Create( idt indID, idt eID, idt roleID, const wxString& note )
{
    recIndividualEvent ie(0);
    ie.FSetIndID( indID );
    ie.FSetEventID( eID );
    ie.FSetRoleID( roleID );
    ie.FSetNote( note );
    ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indID ) + 1 );
    ie.Save();
    return ie.FGetID();
}

bool recIndividualEvent::Find( idt indID, idt eveID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 || eveID == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT id, role_id, note, ind_seq "
        "FROM IndividualEvent WHERE ind_id="ID" AND event_id="ID";",
        indID, eveID
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_id       = GET_ID( result.GetInt64( 0 ) );
    f_ind_id   = indID;
    f_event_id = eveID;
    f_role_id  = GET_ID( result.GetInt64( 1 ) );
    f_note     = result.GetAsString( 2 );
    f_ind_seq  = result.GetInt( 3 );
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
