/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd October 2010
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

#include <rec/recEvent.h>
#include <rec/recEventa.h>
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
    f_user_ref  = e.f_user_ref;
}

void recEvent::Clear()
{
    f_id        = 0;
    f_title     = "";
    f_higher_id = 0;
    f_type_id   = 0;
    f_date1_id  = 0;
    f_date2_id  = 0;
    f_place_id  = 0;
    f_note      = "";
    f_date_pt   = 0;
    f_user_ref  = "";
}

void recEvent::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Event"
            " (title, higher_id, type_id, date1_id, date2_id, place_id,"
            " note, date_pt, user_ref)"
            " VALUES ('%q', " ID ", " ID ", " ID ", " ID ", " ID ", '%q', %ld, '%q');",
            UTF8_( dbname ), UTF8_(f_title), f_higher_id, f_type_id, f_date1_id, f_date2_id, f_place_id,
            UTF8_(f_note), f_date_pt, UTF8_(f_user_ref)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Event"
                " (id, title, higher_id, type_id, date1_id, date2_id, place_id,"
                " note, date_pt, user_ref)"
                " VALUES (" ID ", '%q', " ID ", " ID ", " ID ", " ID ", " ID ", '%q', %ld, '%q');",
                UTF8_( dbname ), f_id, UTF8_(f_title), f_higher_id, f_type_id, f_date1_id, f_date2_id, f_place_id,
                UTF8_(f_note), f_date_pt, UTF8_(f_user_ref)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Event SET"
                " title='%q', higher_id=" ID ", type_id=" ID ", date1_id=" ID ", date2_id=" ID ","
                " place_id=" ID ", note='%q', date_pt=%ld, user_ref='%q'"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_title), f_higher_id, f_type_id, f_date1_id, f_date2_id, f_place_id,
                UTF8_(f_note), f_date_pt, UTF8_(f_user_ref), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEvent::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, higher_id, type_id, date1_id, date2_id, place_id,"
        " note, date_pt, user_ref"
        " FROM \"%s\".Event WHERE id=" ID ";",
        UTF8_( dbname ), f_id
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
    f_user_ref  = result.GetAsString( 8 );
    return true;
}

bool recEvent::Equivalent( const recEvent& r2 ) const
{
    return
        f_title == r2.f_title &&
        f_higher_id == r2.f_higher_id &&
        f_type_id == r2.f_type_id &&
        f_date1_id == r2.f_date1_id &&
        f_date2_id == r2.f_date2_id &&
        f_place_id == r2.f_place_id &&
        f_note == r2.f_note &&
        f_date_pt == r2.f_date_pt &&
        f_user_ref == r2.f_user_ref
    ;
}

idt recEvent::CreateFromEventa( const recEventa& ea, const wxString& dbname )
{
    Clear();
    f_title    = ea.FGetTitle();
    f_type_id  = ea.FGetTypeID();
    f_date1_id = recDate::Create( ea.FGetDate1ID() );
    f_date2_id = recDate::Create( ea.FGetDate2ID() );
    f_place_id = recPlace::Create( ea.FGetPlaceID() );
    f_note     = ea.FGetNote();
    f_date_pt  = ea.FGetDatePt();
    Save( dbname );
    return f_id;
}

idt recEvent::CreateFromEventa( idt eaID, const wxString& dbname )
{
    recEventa ea( eaID, dbname );
    recEvent e;
    return e.CreateFromEventa( ea, dbname );
}

void recEvent::CreateRolesFromEventa( idt eID, idt eaID, const wxString& dbname )
{
    recEventaPersonaVec epas = recEventa::GetEventaPersonas( eaID, dbname );
    for( size_t i = 0 ; i < epas.size() ; i++ ) {
        recIdVec indIDs = recPersona::GetIndividualIDs( epas[i].FGetPerID(), dbname );
        for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
            recIndividualEvent ie;
            if( ie.Find( indIDs[j], eID, epas[i].FGetRoleID(), dbname ) ) {
                continue;
            }
            ie.FSetIndID( indIDs[j] );
            ie.FSetEventID( eID );
            ie.FSetRoleID( epas[i].FGetRoleID() );
            ie.FSetNote( epas[i].FGetNote() );
            ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indIDs[j], dbname ) + 1 );
            ie.Save( dbname );
            recIndividual::UpdateEpitaph( indIDs[j], dbname );
        }
    }
}

wxString recEvent::SetAutoTitle( const wxString& name1, const wxString& name2, const wxString& dbname )
{
    f_title = wxEmptyString;
    wxString n1, n2;
    if( name1.empty() ) {
        n1 = name2;
        n2 = name1;
    }
    else {
        n1 = name1;
        n2 = name2;
    }
    wxString type = recEventType::GetTypeStr( f_type_id, dbname );
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

void recEvent::SetDatePeriodToInclude( idt eID, idt dateID, const wxString& dbname )
{
    recEvent e( eID, dbname );
    recDate date( dateID, dbname );
    recDate date1( e.FGetDate1ID(), dbname );
    recDate date2( e.FGetDate2ID(), dbname );

    if( date.FGetJdn() < date1.FGetJdn() ) {
        e.FSetDate1ID( date.FGetID() );
        if( date2.FGetID() == 0 ) {
            e.FSetDate2ID( date1.FGetID() );
            e.Save( dbname );
        } else {
            e.Save( dbname );
            recDate::DeleteIfOrphaned( date1.FGetID(), dbname );
        }
    } else if(
        ( e.FGetDate2ID() == 0 && date.FGetJdn() > date1.FGetJdn() ) ||
        ( e.FGetDate2ID() != 0 && date.FGetJdn() > date2.FGetJdn() )
    ) {
        e.FSetDate2ID( date.FGetID() );
        e.Save( dbname );
        recDate::DeleteIfOrphaned( date2.FGetID(), dbname );
    }
}

wxString recEvent::GetDetailStr( const wxString& dbname ) const
{
    wxString str;
    str << recDate::GetStr( f_date1_id, dbname );
    if( !str.empty() && f_place_id != 0 ) {
        str << ", ";
    }
    str << recPlace::GetAddressStr( f_place_id, dbname );
    return str;
}

wxString recEvent::GetTypeStr( const wxString& dbname ) const
{
    return recEventType::GetTypeStr( f_type_id, dbname );
}

wxString recEvent::GetDateStr( const wxString& dbname ) const
{
    wxString str;
    str << recDate::GetStr( f_date1_id, dbname );
    if( f_date2_id != 0 ) {
        str << _(" To ") << recDate::GetStr( f_date2_id, dbname );
    }
    return str;
}

wxString recEvent::GetAddressStr( const wxString& dbname ) const
{
    return recPlace::GetAddressStr( f_place_id, dbname );
}

recEventTypeGrp recEvent::GetTypeGroup( const wxString& dbname ) const
{
    return recEventType::GetGroup( f_type_id, dbname );
}


wxString recEvent::GetDetailStr( idt id, const wxString& dbname )
{
    recEvent e( id, dbname );
    return e.GetDetailStr( dbname );
}

wxString recEvent::GetTypeStr( idt id, const wxString& dbname )
{
    idt typeID = ExecuteID(
        "SELECT type_id FROM \"%s\".Event WHERE id=" ID ";", UTF8_( dbname ), id
    );
    return recEventType::GetTypeStr( typeID );
}

wxString recEvent::GetTitle( idt evID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT title FROM \"%s\".Event WHERE id=" ID ";", UTF8_( dbname ), evID );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

idt recEvent::GetDate1ID( idt evID, const wxString& dbname )
{
    if( evID == 0 ) return 0;
    return ExecuteID( 
        "SELECT date1_id FROM \"%s\".Event WHERE id=" ID ";",
        UTF8_( dbname ), evID
    );
}

wxString recEvent::GetDateStr( idt evID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;
    wxString str;

    sql.Format(
        "SELECT date1_id, date2_id FROM \"%s\".Event WHERE id=" ID ";",
        UTF8_( dbname ), evID
    );
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

wxString recEvent::GetAddressStr( idt evID, const wxString& dbname )
{
    idt placeID = ExecuteID(
        "SELECT place_id FROM \"%s\".Event WHERE id=" ID ";",
        UTF8_( dbname ), evID
    );
    return recPlace::GetAddressStr( placeID );
}

wxString recEvent::GetNote( idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT note FROM \"%s\".Event WHERE id=" ID ";", UTF8_( dbname ), id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

bool recEvent::IsFamilyEvent( idt eveID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT ET.grp FROM \"%s\".Event E, \"%s\".EventType ET"
        " WHERE E.type_id=ET.id AND E.id=" ID ";",
        UTF8_( dbname ), UTF8_( dbname ), eveID
    );
    result = s_db->ExecuteQuery( sql );
    recEventTypeGrp grp = recEventTypeGrp( result.GetInt( 0 ) );
    if( grp == recEventTypeGrp::fam_union || grp == recEventTypeGrp::fam_other ) {
        return true;
    }
    return false;
}

recIndEventVec recEvent::GetIndividualEvents( idt eID, const wxString& dbname )
{
    recIndEventVec vec;
    recIndividualEvent record;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, higher_id, ind_id, role_id, note, ind_seq"
        " FROM \"%s\".IndividualEvent WHERE event_id=" ID
        " ORDER BY id;",
        UTF8_( dbname ), eID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.FSetEventID( eID );
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.FSetID( GET_ID( table.GetInt64( 0 ) ) );
        record.FSetHigherID( GET_ID( table.GetInt64( 1 ) ) );
        record.FSetIndID( GET_ID( table.GetInt64( 2 ) ) );
        record.FSetRoleID( GET_ID( table.GetInt64( 3 ) ) );
        record.FSetNote( table.GetAsString( 4 ) );
        record.FSetIndSeq( table.GetInt( 5 ) );
        vec.push_back( record );
    }
    return vec;
}

void recEvent::UpdateDatePoint( idt evID, const wxString& dbname )
{
    recEvent ev( evID, dbname );
    ev.UpdateDatePoint( dbname );
}

void recEvent::UpdateDatePoint( const wxString& dbname )
{
    recEventTypeGrp grp = recEventType::GetGroup( f_type_id, dbname );
    switch( grp )
    {
    case recEventTypeGrp::birth:
    case recEventTypeGrp::nr_birth:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DatePoint::beg, dbname );
        return;
    case recEventTypeGrp::death:
    case recEventTypeGrp::nr_death:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DatePoint::end, dbname );
        return;
    }
    f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DatePoint::mid, dbname );
}

recEventVec recEvent::GetLowerEvents( idt eventID, const wxString& dbname )
{
    recEventVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, title, type_id, date1_id, date2_id, place_id,"
        " note, date_pt, user_ref"
        " FROM \"%s\".Event WHERE higher_id=" ID
        " ORDER BY date_pt;",
        UTF8_( dbname ), eventID
    );
    result = s_db->ExecuteQuery( sql );

    recEvent e(0);
    e.f_higher_id = eventID;
    while( result.NextRow() ) {
        e.f_id       = GET_ID( result.GetInt64( 0 ) );
        e.f_title    = result.GetAsString( 1 );
        e.f_type_id  = GET_ID( result.GetInt64( 2 ) );
        e.f_date1_id = GET_ID( result.GetInt64( 3 ) );
        e.f_date2_id = GET_ID( result.GetInt64( 4 ) );
        e.f_place_id = GET_ID( result.GetInt64( 5 ) );
        e.f_note     = result.GetAsString( 6 );
        e.f_date_pt  = (long) result.GetInt( 7 );
        e.f_user_ref = result.GetAsString( 8 );
        vec.push_back( e );
    }
    return vec;
}

recEventaVec recEvent::FindEquivRefEvents( idt indEventID, const wxString& dbname )
{
    recEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt FROM "
        "  \"%s\".Eventa "
        "JOIN "
        "   (SELECT EP.eventa_id FROM "
        "   \"%s\".IndividualEvent IE, \"%s\".IndividualPersona IP, \"%s\".EventaPersona EP "
        "   WHERE IE.event_id=" ID
        "     AND IP.ind_id=IE.ind_id "
        "     AND EP.per_id=IP.per_id "
        "     AND IE.role_id=EP.role_id "
        "    GROUP BY eventa_id) "
        "ON id=eventa_id;",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), indEventID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        recEventa e(0);
        e.f_id       = GET_ID( result.GetInt64( 0 ) );
        e.f_title    = result.GetAsString( 1 );
        e.f_ref_id   = GET_ID( result.GetInt64( 2 ) );
        e.f_type_id  = GET_ID( result.GetInt64( 3 ) );
        e.f_date1_id = GET_ID( result.GetInt64( 4 ) );
        e.f_date2_id = GET_ID( result.GetInt64( 5 ) );
        e.f_place_id = GET_ID( result.GetInt64( 6 ) );
        e.f_note     = result.GetAsString( 7 );
        e.f_date_pt  = (long) result.GetInt( 8 );
        vec.push_back( e );
    }
    return vec;
}

recIdVec recEvent::GetReferenceIDs( idt eveID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT EA.ref_id"
        " FROM \"%s\".EventEventa EE, \"%s\".Eventa EA"
        " WHERE EE.event_id=" ID " AND EE.eventa_id=EA.id;",
        UTF8_( dbname ), UTF8_( dbname ), eveID
    );
    return ExecuteIdVec( sql );
}

recEventaVec recEvent::GetEventasIncludeLower( idt eveID, const wxString& dbname )
{
    recEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT DISTINCT EA.id, EA.title, EA.ref_id, EA.type_id,"
        " EA.date1_id, EA.date2_id, EA.place_id, EA.note, EA.date_pt"
        " FROM \"%s\".IndividualEvent IE, \"%s\".EventEventa EE, \"%s\".Eventa EA,"
        " (SELECT id FROM \"%s\".IndividualEvent WHERE event_id=" ID ") IE2"
        " WHERE (IE.higher_id=IE2.id OR IE.event_id=" ID ")"
        " AND IE.event_id=EE.event_id AND EE.eventa_id=EA.id"
        " ORDER BY EA.date_pt;",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), eveID, eveID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        recEventa e(0);
        e.f_id       = GET_ID( result.GetInt64( 0 ) );
        e.f_title    = result.GetAsString( 1 );
        e.f_ref_id   = GET_ID( result.GetInt64( 2 ) );
        e.f_type_id  = GET_ID( result.GetInt64( 3 ) );
        e.f_date1_id = GET_ID( result.GetInt64( 4 ) );
        e.f_date2_id = GET_ID( result.GetInt64( 5 ) );
        e.f_place_id = GET_ID( result.GetInt64( 6 ) );
        e.f_note     = result.GetAsString( 7 );
        e.f_date_pt  = (long) result.GetInt( 8 );
        vec.push_back( e );
    }
    return vec;
}

recEventEventaVec recEvent::GetEventEventas( idt eveID, const wxString& dbname )
{
    recEventEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, eventa_id, conf, note FROM "
        "  \"%s\".EventEventa WHERE event_id=" ID ";",
        UTF8_( dbname ), eveID
    );
    result = s_db->ExecuteQuery( sql );

    recEventEventa eer(0);
    eer.FSetEventID( eveID );
    while( result.NextRow() ) {
        eer.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        eer.FSetEventaID( GET_ID( result.GetInt64( 1 ) ) );
        eer.FSetConf( result.GetDouble( 2 ) );
        eer.FSetNote( result.GetAsString( 3 ) );
        vec.push_back( eer );
    }
    return vec;
}

void recEvent::RemoveFromDatabase( const wxString& dbname )
{
    if( f_id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "DELETE FROM \"%s\".IndividualEvent WHERE event_id=" ID ";"
        "DELETE FROM \"%s\".FamilyEvent WHERE event_id=" ID ";",
        UTF8_( dbname ), f_id, UTF8_( dbname ), f_id
    );
    s_db->ExecuteUpdate( sql );

    Delete( dbname );
    Clear();
}

void recEvent::RemoveFromDatabase( idt id, const wxString& dbname )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEvent eve( id, dbname );
    eve.RemoveFromDatabase( dbname );
}

void recEvent::RemoveIncOrphansFromDatabase( idt id, const wxString& dbname )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEvent eve( id, dbname );
    RemoveFromDatabase( eve.f_id, dbname );
    recDate::DeleteIfOrphaned( eve.f_date1_id, dbname );
    recDate::DeleteIfOrphaned( eve.f_date2_id, dbname );
    recPlace::DeleteIfOrphaned( eve.f_place_id, dbname );
    // TODO: Delete orphaned EventType and/or EventTypeRole
}

std::string recEvent::CsvTitles()
{
    return std::string(
        "id, 'title', higher_id, type_id, date1_id, date2_id, place_id,"
        " 'note', date_pt, 'user_ref'\n"
    );
}

void recEvent::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recEvent eve( id, dbname );
    recCsvWrite( out, eve.FGetID() );
    recCsvWrite( out, eve.FGetTitle() );
    recCsvWrite( out, eve.FGetHigherID() );
    recCsvWrite( out, eve.FGetTypeID() );
    recCsvWrite( out, eve.FGetDate1ID() );
    recCsvWrite( out, eve.FGetDate2ID() );
    recCsvWrite( out, eve.FGetPlaceID() );
    recCsvWrite( out, eve.FGetNote() );
    recCsvWrite( out, eve.FGetDatePt() );
    recCsvWrite( out, eve.FGetUserRef(), '\n' );
}

bool recEvent::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_title );
    recCsvRead( in, f_higher_id );
    recCsvRead( in, f_type_id );
    recCsvRead( in, f_date1_id );
    recCsvRead( in, f_date2_id );
    recCsvRead( in, f_place_id );
    recCsvRead( in, f_note );
    recCsvRead( in, f_date_pt );
    recCsvRead( in, f_user_ref );
    return bool( in );
}

void recEvent::RemoveDates( idt dateID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE \"%s\".Event SET date1_id=0, date_pt=0 WHERE date1_id=" ID ";"
        "UPDATE \"%s\".Event SET date2_id=0 WHERE date2_id=" ID ";",
        UTF8_( dbname ), dateID, UTF8_( dbname ), dateID
    );
    s_db->ExecuteUpdate( sql );
}

void recEvent::RemovePlace( idt placeID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE \"%s\".Event SET place_id=0 WHERE place_id=" ID ";",
        UTF8_( dbname ), placeID
    );
    s_db->ExecuteUpdate( sql );
}

void recEvent::DeleteIfOrphaned( idt id, const wxString& dbname )
{
    if( id <= 0 ) {
        // Don't delete universal dates.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".EventaPersona WHERE event_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".ReferenceEntity"
        " WHERE entity_type=2 AND entity_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format( 
        "SELECT COUNT(*) FROM \"%s\".IndividualEvent WHERE event_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    RemoveFromDatabase( id, dbname );
}

wxSQLite3Table recEvent::GetTitleList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM \"%s\".Event"
        " WHERE NOT id=0 AND higher_id=0 ORDER BY id;",
        UTF8_( dbname )
    );
    return s_db->GetTable( sql );
}

wxSQLite3Table recEvent::GetTitleList( idt offset, int limit, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM \"%s\".Event"
        " WHERE NOT id=0 AND higher_id=0"
        " ORDER BY id LIMIT " ID ", %d;",
        UTF8_( dbname ), offset, limit
    );
    return s_db->GetTable( sql );
}


// End of recEvent.cpp file
