/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Eventa table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013-2016, Nick Matthews.
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

#include <rec/recEventa.h>

#include <rec/recEvent.h>
#include <rec/recIndividual.h>
#include <rec/recIndEvent.h>
#include <rec/recPersona.h>
#include <rec/recPlace.h>


//============================================================================
//--------------------------[ recEventa ]-------------------------------------
//============================================================================

recEventa::recEventa( const recEventa& e )
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

void recEventa::Clear()
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

void recEventa::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Eventa "
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
                "INSERT INTO Eventa "
                "(id, title, type_id, date1_id, date2_id, place_id, note, date_pt) "
                "VALUES ("ID", '%q', "ID", "ID", "ID", "ID", '%q', %ld);",
                f_id, UTF8_(f_title), f_type_id, f_date1_id, f_date2_id, f_place_id,
                UTF8_(f_note), f_date_pt
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Eventa SET "
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

bool recEventa::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, type_id, date1_id, date2_id, place_id, note, date_pt "
        "FROM Eventa WHERE id="ID";",
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

idt recEventa::CreateFromEvent( const recEvent& eve )
{
    Clear();
    f_title    = eve.FGetTitle();
    f_type_id  = eve.FGetTypeID();
    f_date1_id = recDate::Create( eve.FGetDate1ID() );
    f_date2_id = recDate::Create( eve.FGetDate2ID() );
    f_place_id = recPlace::Create( eve.FGetPlaceID() );
    f_note     = eve.FGetNote();
    f_date_pt  = eve.FGetDatePt();
    Save();
    return f_id;
}

idt recEventa::CreateFromEvent( idt eveID )
{
    recEvent eve(eveID);
    recEventa ea;
    return ea.CreateFromEvent( eve );
}

wxString recEventa::SetAutoTitle( const wxString& name1, const wxString& name2 )
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

wxString recEventa::GetDetailStr() const
{
    wxString str;
    str << recDate::GetStr( f_date1_id );
    if( !str.empty() && f_place_id != 0 ) {
        str << ", ";
    }
    str << recPlace::GetAddressStr( f_place_id );
    return str;
}

wxString recEventa::GetTypeStr() const
{
    return recEventType::GetTypeStr( f_type_id );
}

wxString recEventa::GetDateStr() const
{
    wxString str;
    str << recDate::GetStr( f_date1_id );
    if( f_date2_id != 0 ) {
        str << _(" To ") << recDate::GetStr( f_date2_id );
    }
    return str;
}

wxString recEventa::GetAddressStr() const
{
    return recPlace::GetAddressStr( f_place_id );
}

recET_GRP recEventa::GetTypeGroup() const
{
    return recEventType::GetGroup( f_type_id );
}


wxString recEventa::GetDetailStr( idt id )
{
    recEventa e( id );
    return e.GetDetailStr();
}

wxString recEventa::GetTypeStr( idt id )
{
    idt typeID = ExecuteID(
        "SELECT type_id FROM Eventa WHERE id="ID";", id
    );
    return recEventType::GetTypeStr( typeID );
}

wxString recEventa::GetTitle( idt evID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT title FROM Eventa WHERE id="ID";", evID );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

idt recEventa::GetDate1ID( idt evID )
{
    if( evID == 0 ) return 0;
    return ExecuteID( "SELECT date1_id FROM Eventa WHERE id="ID";", evID );
}

wxString recEventa::GetDateStr( idt evID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;
    wxString str;

    sql.Format( "SELECT date1_id, date2_id FROM Eventa WHERE id="ID";", evID );
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

wxString recEventa::GetAddressStr( idt evID )
{
    idt placeID = ExecuteID(
        "SELECT place_id FROM Eventa WHERE id="ID";", evID
    );
    return recPlace::GetAddressStr( placeID );
}

wxString recEventa::GetNote( idt id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT note FROM Eventa WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

recEventEventaVec recEventa::GetEventEventas( idt erID )
{
    recEventEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, event_id, conf, note FROM "
        "  EventEventa WHERE eventa_id="ID";",
        erID
    );
    result = s_db->ExecuteQuery( sql );

    recEventEventa eer(0);
    eer.FSetEventaID( erID );
    while( result.NextRow() ) {
        eer.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        eer.FSetEventID( GET_ID( result.GetInt64( 1 ) ) );
        eer.FSetConf( result.GetDouble( 2 ) );
        eer.FSetNote( result.GetAsString( 3 ) );
        vec.push_back( eer );
    }
    return vec;
}

bool recEventa::IsFamilyEvent( idt eveID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT ET.grp FROM Eventa E, EventType ET"
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

recEventaPersonaVec recEventa::GetEventaPersonas( idt emID )
{
    recEventaPersonaVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, per_id, role_id, note "
        "FROM EventaPersona WHERE eventa_id="ID";",
        emID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    recEventaPersona record;
    record.FSetEventaID( emID );
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

void recEventa::UpdateDatePoint( idt evID )
{
    recEventa ev(evID);
    ev.UpdateDatePoint();
}

void recEventa::UpdateDatePoint()
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

void recEventa::RemoveFromDatabase()
{
    if( f_id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    wxSQLite3StatementBuffer sql;

    // TODO: Ensure Event is removed from reference statement.
    sql.Format(
        "DELETE FROM EventaPersona WHERE eventa_id="ID";"
        "DELETE FROM ReferenceEntity WHERE entity_type=2 AND entity_id="ID";",
        f_id, f_id
    );
    s_db->ExecuteUpdate( sql );

    Delete();
    Clear();
}

void recEventa::RemoveFromDatabase( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEventa eve(id);
    eve.RemoveFromDatabase();
}

void recEventa::RemoveIncOrphansFromDatabase( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal events.
        return;
    }
    recEventa eve(id);
    RemoveFromDatabase( eve.f_id );
    recDate::DeleteIfOrphaned( eve.f_date1_id );
    recDate::DeleteIfOrphaned( eve.f_date2_id );
    recPlace::DeleteIfOrphaned( eve.f_place_id );
    // TODO: Delete orphaned EventType and/or EventTypeRole
}

void recEventa::RemoveDates( idt dateID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Eventa SET date1_id=0, date_pt=0 WHERE date1_id="ID";"
        "UPDATE Eventa SET date2_id=0 WHERE date2_id="ID";",
        dateID, dateID
    );
    s_db->ExecuteUpdate( sql );
}

void recEventa::RemovePlace( idt placeID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Eventa SET place_id=0 WHERE place_id="ID";",
        placeID
    );
    s_db->ExecuteUpdate( sql );
}

void recEventa::DeleteIfOrphaned( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal dates.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM EventaPersona WHERE eventa_id="ID";", id );
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

wxSQLite3Table recEventa::GetTitleList()
{
    return s_db->GetTable( "SELECT id, title FROM Eventa ORDER BY id;" );
}

wxSQLite3Table recEventa::GetTitleList( idt offset, int limit )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM Eventa ORDER BY id LIMIT "ID", %d;",
        offset, limit
    );
    return s_db->GetTable( sql );
}

int recEventa::GetLastPerSeqNumber( idt eventID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(per_seq) FROM EventaPersona WHERE eventa_id="ID";",
        eventID
    );
    return s_db->ExecuteScalar( sql );
}

recFamilyEventaVec recEventa::GetFamilyEventas( idt eaID )
{
    recFamilyEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, fam_id, conf, note FROM "
        "  FamilyEventa WHERE eventa_id="ID";",
        eaID
    );
    result = s_db->ExecuteQuery( sql );

    recFamilyEventa fea(0);
    fea.FSetEventaID( eaID );
    while( result.NextRow() ) {
        fea.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        fea.FSetFamID( GET_ID( result.GetInt64( 1 ) ) );
        fea.FSetConf( result.GetDouble( 2 ) );
        fea.FSetNote( result.GetAsString( 3 ) );
        vec.push_back( fea );
    }
    return vec;
}

recFamilyIndEventaVec recEventa::GetFamilyIndEventas( idt eaID )
{
    recFamilyIndEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, fam_ind_id, conf, note FROM "
        "  FamilyIndEventa WHERE eventa_id="ID";",
        eaID
    );
    result = s_db->ExecuteQuery( sql );

    recFamilyIndEventa fiea(0);
    fiea.FSetEventaID( eaID );
    while( result.NextRow() ) {
        fiea.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        fiea.FSetFamIndID( GET_ID( result.GetInt64( 1 ) ) );
        fiea.FSetConf( result.GetDouble( 2 ) );
        fiea.FSetNote( result.GetAsString( 3 ) );
        vec.push_back( fiea );
    }
    return vec;
}

recIdVec recEventa::FindLinkedEvents( recEVENT_Link link ) const
{
    recIdVec eveIDs;
    wxSQLite3StatementBuffer sql;

    if( link == recEVENT_Link_EvEvRec ) {
        sql.Format(
            // This query finds Event's which match the Eventa,
            // by using the EventEventa table.
            "SELECT event_id FROM EventEventa"
            " WHERE eventa_id="ID
            " ORDER BY event_id;",
            f_id
        );
    } else { // recEVENT_Link_IndPer
        sql.Format(
            // This query finds Event's which match the Eventa,
            // by matching the linked prime Persona with their Indiviuals.
            "SELECT IE.event_id"
            " FROM EventaPersona EP, IndividualPersona IP,"
            " IndividualEvent IE, EventTypeRole ETR"
            " WHERE EP.eventa_id="ID
            " AND EP.per_id=IP.per_id AND IP.ind_id=IE.ind_id AND EP.role_id=IE.role_id"
            " AND EP.role_id=ETR.id AND ETR.prime>0"
            " GROUP BY IE.event_id"
            " ORDER BY IE.event_id;",
            f_id
        );
    }
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        eveIDs.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }

    return eveIDs;
}

recCheckIdVec recEventa::FindCheckedLinkedEvents() const
{
    recCheckIdVec list;
    recIdVec e1 = FindLinkedEvents( recEVENT_Link_EvEvRec );
    recIdVec e2 = FindLinkedEvents( recEVENT_Link_IndPer );

    // This assumes e1 and e2 are both in ascending order
    for( size_t i = 0, j = 0 ; i < e1.size() || j < e2.size() ; ) {
        recCheckID chk;
        if( i == e1.size() ) {
            chk.SetIDs( 0, e2[j++] );
        } else if( j == e2.size() ) {
            chk.SetIDs( e1[i++], 0 );
        } else if( e1[i] == e2[j] ) {
            chk.SetIDs( e1[i++], e2[j++] );
        } else if( e1[i] > e2[j] ) {
            chk.SetIDs( e1[i++], 0 );
        } else {
            chk.SetIDs( 0, e2[j++] );
        }
        list.push_back( chk );
    }
    return list;
}

void recEventa::CreateFamilyLink() const
{
    recEventaPersonaVec eapas = GetEventaPersonas();
    recIdVec partners, children;
    for( size_t i = 0 ; i < eapas.size() ; i++ ) {
        recEventTypeRole ro(eapas[i].FGetRoleID());
        if( ro.FGetPrime() > 0 ) {
            partners.push_back( eapas[i].FGetPerID() );
        } else {
            children.push_back( eapas[i].FGetPerID() );
        }
    }
    if( partners.empty() ) {
        return;
    }
    wxASSERT( partners.size() <= 2 );

    recIdVec fams; // List of possible families.
    if( partners.size() == 2 ) {
        recIdVec ind1s = recPersona::GetIndividualIDs( partners[0] );
        recIdVec ind2s = recPersona::GetIndividualIDs( partners[1] );
        // Go through all possibilities
        for( size_t i = 0 ; i < ind1s.size() ; i++ ) {
            for( size_t j = 0 ; j < ind2s.size() ; j++ ) {
                idt famID = recFamily::FindOrCreate( ind1s[i], ind2s[j] );
                if( famID ) {
                    fams.push_back( famID );
                }
            }
        }
    } else if( partners.size() == 1 ) {
        recIdVec inds = recPersona::GetIndividualIDs( partners[0] );
        for( size_t i = 0 ; i < inds.size() ; i++ ) {
            idt famID = recFamily::FindOrCreate( inds[i], 0 );
            if( famID ) {
                fams.push_back( famID );
            }
        }
    }
    for( size_t i = 0 ; i < fams.size() ; i++ ) {
        recFamilyEventa::Create( fams[i], FGetID() );
        for( size_t j = 0 ; j < children.size() ; j++ ) {
            recIdVec inds = recPersona::GetIndividualIDs( children[j] );
            for( size_t k = 0 ; k < inds.size() ; k++ ) {
                recFamilyIndividual fi(0);
                fi.FSetFamID( fams[i] );
                fi.FSetIndID( inds[k] );
                fi.Find();
                if( fi.FGetID() == 0 ) {
                    // Doesn't exist, so create it.
                    fi.FSetSeqChild( recFamily::GetChildNextSequence( fams[i] ) );
                    fi.FSetSeqParent( recFamily::GetParentNextSequence( inds[k] ) );
                    fi.Save();
                }
                recFamilyIndEventa::Create( fi.FGetID(), FGetID() );
            }
        }
    }
}

void recEventa::CreatePersonalEvent() const
{
    recEvent eve(0);
    recEventaPersonaVec eapas = GetEventaPersonas();
    for( size_t i = 0 ; i < eapas.size() ; i++ ) {
        recEventTypeRole ro(eapas[i].FGetRoleID());
        if( ro.FGetPrime() == 0 ) {
            continue;
        }
        // List of Individuls associated with this Persona
        recIdVec indIDs = recPersona::GetIndividualIDs( eapas[i].FGetPerID() );
        for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
            if( eve.FGetID() == 0 ) {
                // About time we created the Event
                eve.CreateFromEventa( *this );
                recEventEventa::Create( eve.FGetID(), f_id );
            }
            // Find summary IndividualEvent
            idt ieSumID = recIndividual::GetPersonalSummaryIE( indIDs[j], ro.FGetTypeID() );
            if( ieSumID == 0 ) {
                // Create the summary personal Event.
                recEvent e(0);
                e.FSetTypeID( FGetTypeID() );
                e.SetAutoTitle( recIndividual::GetName( indIDs[j] ) + _(" - Summary") );
                e.FSetDate1ID( recIndividual::CreateBirthDate( indIDs[j] ) );
                e.FSetDate2ID( recIndividual::CreateDeathDate( indIDs[j] ) );
                e.Save();
                idt sum_etrID = recEventType::GetSummaryRole( FGetTypeID() );
                ieSumID = recIndividualEvent::Create( indIDs[j], e.FGetID(), sum_etrID );
            }
            recIndividualEvent ie(0);
            ie.FSetHigherID( ieSumID );
            ie.FSetIndID( indIDs[j] );
            ie.FSetEventID( eve.FGetID() );
            ie.FSetRoleID( ro.FGetID() );
            ie.FSetNote( eapas[i].FGetNote() );
            ie.Save();
        }
    }
}

// End of src/rec/recEventa.cpp file
