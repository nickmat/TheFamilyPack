/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventRecord.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventRecord table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <rec/recEventRecord.h>
#include <rec/recEventType.h>
#include <rec/recEvent.h>
#include <rec/recPlace.h>


//============================================================================
//-------------------------[ recEventRecord ]---------------------------------
//============================================================================

recEventRecord::recEventRecord( const recEventRecord& e )
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

void recEventRecord::Clear()
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

void recEventRecord::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventRecord "
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
                "INSERT INTO EventRecord "
                "(id, title, type_id, date1_id, date2_id, place_id, note, date_pt) "
                "VALUES ("ID", '%q', "ID", "ID", "ID", "ID", '%q', %ld);",
                f_id, UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id,
                UTF8_(f_note), f_date_pt
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventRecord SET "
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

bool recEventRecord::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, type_id, date1_id, date2_id, place_id, note, date_pt "
        "FROM EventRecord WHERE id="ID";",
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

wxString recEventRecord::SetAutoTitle( const wxString& name1, const wxString& name2 )
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

wxString recEventRecord::GetDetailStr() const
{
    wxString str;
    str << recDate::GetStr( f_date1_id );
    if( !str.empty() && f_place_id != 0 ) {
        str << ", ";
    }
    str << recPlace::GetAddressStr( f_place_id );
    return str;
}

wxString recEventRecord::GetTypeStr() const
{
    return recEventType::GetTypeStr( f_type_id );
}

wxString recEventRecord::GetDateStr() const
{
    wxString str;
    str << recDate::GetStr( f_date1_id );
    if( f_date2_id != 0 ) {
        str << _(" To ") << recDate::GetStr( f_date2_id );
    }
    return str;
}

wxString recEventRecord::GetAddressStr() const
{
    return recPlace::GetAddressStr( f_place_id );
}

recEventType::ETYPE_Grp recEventRecord::GetTypeGroup() const
{
    return recEventType::GetGroup( f_type_id );
}
    

wxString recEventRecord::GetDetailStr( idt id )
{
    recEventRecord e( id );
    return e.GetDetailStr();
}

wxString recEventRecord::GetTypeStr( idt id )
{
    idt typeID = ExecuteID(
        "SELECT type_id FROM EventRecord WHERE id="ID";", id
    );
    return recEventType::GetTypeStr( typeID );
}

wxString recEventRecord::GetTitle( idt evID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT title FROM EventRecord WHERE id="ID";", evID );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

idt recEventRecord::GetDate1ID( idt evID )
{
    if( evID == 0 ) return 0;
    return ExecuteID( "SELECT date1_id FROM EventRecord WHERE id="ID";", evID );
}

wxString recEventRecord::GetDateStr( idt evID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;
    wxString str;

    sql.Format( "SELECT date1_id, date2_id FROM EventRecord WHERE id="ID";", evID );
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

wxString recEventRecord::GetAddressStr( idt evID )
{
    idt placeID = ExecuteID(
        "SELECT place_id FROM EventRecord WHERE id="ID";", evID
    );
    return recPlace::GetAddressStr( placeID );
}

wxString recEventRecord::GetNote( idt id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT note FROM EventRecord WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

recIdVec recEventRecord::FindRealEventIDs( idt erID )
{
    recIdVec eveIDs;
    // TODO: Get a list of Event's 
    // by matching Persona and Individuls for the prime roles
    return eveIDs;
}

recEveEveRecordVec recEventRecord::GetEveEveRecords( idt erID )
{
    recEveEveRecordVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, event_id, conf, note FROM "
        "  EventEventRecord WHERE event_rec_id="ID";",
        erID
    );
    result = s_db->ExecuteQuery( sql );

    recEventEventRecord eer(0);
    eer.FSetEventRecID( erID );
    while( result.NextRow() ) {
        eer.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        eer.FSetEventID( GET_ID( result.GetInt64( 1 ) ) );
        eer.FSetConf( result.GetDouble( 2 ) );
        eer.FSetNote( result.GetAsString( 3 ) );
        vec.push_back( eer );
    }
    return vec;
}

bool recEventRecord::IsFamilyEvent( idt eveID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT ET.grp FROM EventRecord E, EventType ET"
        " WHERE E.type_id=ET.id AND E.id="ID";",
        eveID
    );
    result = s_db->ExecuteQuery( sql );
    recEventType::ETYPE_Grp grp = (recEventType::ETYPE_Grp) result.GetInt( 0 );
    if( grp == recEventType::ETYPE_Grp_Union || recEventType::ETYPE_Grp_Family ) {
        return true;
    }
    return false;
}

recEventPersonaVec recEventRecord::GetEventPersonas()
{
    recEventPersonaVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, per_id, role_id, note "
        "FROM EventPersona WHERE event_rec_id="ID";",
        f_id
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    recEventPersona record;
    record.FSetEventRecID( f_id );
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

void recEventRecord::UpdateDatePoint( idt evID )
{
    recEventRecord ev(evID);
    ev.UpdateDatePoint();
}

void recEventRecord::UpdateDatePoint()
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

void recEventRecord::RemoveFromDatabase()
{
    if( f_id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    wxSQLite3StatementBuffer sql;

    // TODO: Ensure Event is removed from reference statement.
    sql.Format(
        "DELETE FROM EventPersona WHERE event_rec_id="ID";"
        "DELETE FROM ReferenceEntity WHERE entity_type=2 AND entity_id="ID";",
        f_id, f_id
    );
    s_db->ExecuteUpdate( sql );

    Delete();
    Clear();
}

void recEventRecord::RemoveFromDatabase( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEventRecord eve(id);
    eve.RemoveFromDatabase();
}

void recEventRecord::RemoveIncOrphansFromDatabase( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEventRecord eve(id);
    RemoveFromDatabase( eve.f_id );
    recDate::DeleteIfOrphaned( eve.f_date1_id );
    recDate::DeleteIfOrphaned( eve.f_date2_id );
    recPlace::DeleteIfOrphaned( eve.f_place_id );
    // TODO: Delete orphaned EventType and/or EventTypeRole 
}

void recEventRecord::RemoveDates( idt dateID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE EventRecord SET date1_id=0, date_pt=0 WHERE date1_id="ID";"
        "UPDATE EventRecord SET date2_id=0 WHERE date2_id="ID";",
        dateID, dateID
    );
    s_db->ExecuteUpdate( sql );
}

void recEventRecord::RemovePlace( idt placeID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE EventRecord SET place_id=0 WHERE place_id="ID";",
        placeID
    );
    s_db->ExecuteUpdate( sql );
}

void recEventRecord::DeleteIfOrphaned( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal dates.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM EventPersona WHERE event_rec_id="ID";", id );
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

wxSQLite3Table recEventRecord::GetTitleList()
{
    return s_db->GetTable( "SELECT id, title FROM EventRecord ORDER BY id;" );
}

wxSQLite3Table recEventRecord::GetTitleList( idt offset, int limit )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM EventRecord ORDER BY id LIMIT "ID", %d;",
        offset, limit
    );
    return s_db->GetTable( sql );
}

int recEventRecord::GetLastPerSeqNumber( idt eventID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(per_seq) FROM EventPersona WHERE event_rec_id="ID";",
        eventID
    );
    return s_db->ExecuteScalar( sql );
}

recIdVec recEventRecord::FindMatchingEvents() const
{
    recIdVec eveIDs;
    return eveIDs;
}

// End of src/rec/recEventRecord.cpp file
