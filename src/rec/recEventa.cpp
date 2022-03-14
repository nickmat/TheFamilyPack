/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Eventa table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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
#include <rec/recFamily.h>
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
    f_ref_id   = e.f_ref_id;
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
    f_ref_id   = 0;
    f_type_id  = 0;
    f_date1_id = 0;
    f_date2_id = 0;
    f_place_id = 0;
    f_note     = wxEmptyString;
    f_date_pt  = 0;
}

void recEventa::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Eventa "
            "(title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt) "
            "VALUES ('%q', " ID ", " ID ", " ID ", " ID ", " ID ", '%q', %ld);",
            UTF8_( dbname ), UTF8_(f_title), f_ref_id, f_type_id,
            f_date1_id, f_date2_id, f_place_id, UTF8_(f_note), f_date_pt
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Eventa "
                "(id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt) "
                "VALUES (" ID ", '%q', " ID ", " ID ", " ID ", " ID ", " ID ", '%q', %ld);",
                UTF8_( dbname ), f_id, UTF8_(f_title), f_ref_id, f_type_id,
                f_date1_id, f_date2_id, f_place_id, UTF8_(f_note), f_date_pt
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Eventa SET "
                "title='%q', ref_id=" ID ", type_id=" ID ", date1_id=" ID ", date2_id=" ID ", place_id=" ID ", "
                "note='%q', date_pt=%ld "
                "WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_title), f_ref_id, f_type_id,
                f_date1_id, f_date2_id, f_place_id, UTF8_(f_note), f_date_pt, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventa::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt"
        " FROM \"%s\".Eventa WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_title    = result.GetAsString( 0 );
    f_ref_id = GET_ID( result.GetInt64( 1 ) );
    f_type_id = GET_ID( result.GetInt64( 2 ) );
    f_date1_id = GET_ID( result.GetInt64( 3 ) );
    f_date2_id = GET_ID( result.GetInt64( 4 ) );
    f_place_id = GET_ID( result.GetInt64( 5 ) );
    f_note     = result.GetAsString( 6 );
    f_date_pt  = (long) result.GetInt( 7 );
    return true;
}

wxString recEventa::SetAutoTitle(
    const wxString& name1, const wxString& name2, const wxString& dbname )
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

wxString recEventa::GetDetailStr( const wxString& dbname ) const
{
    wxString str;
    str << recDate::GetStr( f_date1_id, dbname );
    if( !str.empty() && f_place_id != 0 ) {
        str << ", ";
    }
    str << recPlace::GetAddressStr( f_place_id, dbname );
    return str;
}

wxString recEventa::GetTypeStr( const wxString& dbname ) const
{
    return recEventType::GetTypeStr( f_type_id, dbname );
}

wxString recEventa::GetDateStr( const wxString& dbname ) const
{
    wxString str;
    str << recDate::GetStr( f_date1_id, dbname );
    if( f_date2_id != 0 ) {
        str << _(" To ") << recDate::GetStr( f_date2_id, dbname );
    }
    return str;
}

wxString recEventa::GetAddressStr( const wxString& dbname ) const
{
    return recPlace::GetAddressStr( f_place_id, dbname );
}

recEventTypeGrp recEventa::GetTypeGroup( const wxString& dbname ) const
{
    return recEventType::GetGroup( f_type_id, dbname );
}


wxString recEventa::GetDetailStr( idt id, const wxString& dbname )
{
    recEventa e( id, dbname );
    return e.GetDetailStr( dbname );
}

wxString recEventa::GetTypeStr( idt id, const wxString& dbname )
{
    idt typeID = ExecuteID(
        "SELECT type_id FROM \"%s\".Eventa WHERE id=" ID ";",
        UTF8_( dbname ), id
    );
    return recEventType::GetTypeStr( typeID );
}

wxString recEventa::GetTitle( idt evID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT title FROM \"%s\".Eventa WHERE id=" ID ";", UTF8_( dbname ), evID );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

idt recEventa::GetRefID( idt eaID, const wxString& dbname )
{
    if ( eaID == 0 ) return 0;
    return ExecuteID(
        "SELECT ref_id FROM \"%s\".Eventa WHERE id=" ID ";",
        UTF8_( dbname ), eaID
    );
}

idt recEventa::GetDate1ID( idt evID, const wxString& dbname )
{
    if ( evID == 0 ) return 0;
    return ExecuteID(
        "SELECT date1_id FROM \"%s\".Eventa WHERE id=" ID ";",
        UTF8_( dbname ), evID
    );
}

wxString recEventa::GetDateStr( idt evID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;
    wxString str;

    sql.Format(
        "SELECT date1_id, date2_id FROM \"%s\".Eventa WHERE id=" ID ";",
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

wxString recEventa::GetAddressStr( idt evID, const wxString& dbname )
{
    idt placeID = ExecuteID(
        "SELECT place_id FROM \"%s\".Eventa WHERE id=" ID ";",
        UTF8_( dbname ), evID
    );
    return recPlace::GetAddressStr( placeID );
}

wxString recEventa::GetNote( idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT note FROM \"%s\".Eventa WHERE id=" ID ";",
        UTF8_( dbname ), id
    );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

recEventEventaVec recEventa::GetEventEventas( idt erID, const wxString& dbname )
{
    recEventEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, event_id, conf, note FROM "
        "  \"%s\".EventEventa WHERE eventa_id=" ID ";",
        UTF8_( dbname ), erID
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

bool recEventa::IsFamilyEvent( idt eveID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT ET.grp FROM \"%s\".Eventa E, \"%s\".EventType ET"
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

recEventaPersonaVec recEventa::GetEventaPersonas( idt eaID, const wxString& dbname )
{
    recEventaPersonaVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, per_id, role_id, note, per_seq"
        " FROM \"%s\".EventaPersona WHERE eventa_id=" ID
        " ORDER BY per_seq;",
        UTF8_( dbname ), UTF8_( dbname ), eaID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    recEventaPersona record;
    record.FSetEventaID( eaID );
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_per_id = GET_ID( table.GetInt64( 1 ) );
        record.f_role_id = GET_ID( table.GetInt64( 2 ) );
        record.f_note = table.GetAsString( 3 );
        record.f_per_seq = table.GetInt( 4 );
        vec.push_back( record );
    }
    return vec;
}

void recEventa::UpdateDatePoint( idt evID, const wxString& dbname )
{
    recEventa ev( evID, dbname );
    ev.UpdateDatePoint( dbname );
}

void recEventa::UpdateDatePoint( const wxString& dbname )
{
    recEventTypeGrp grp = recEventType::GetGroup( f_type_id, dbname );
    switch( grp )
    {
    case recEventTypeGrp::birth:
    case recEventTypeGrp::nr_birth:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DatePoint::beg );
        return;
    case recEventTypeGrp::death:
    case recEventTypeGrp::nr_death:
        f_date_pt = recDate::GetDatePoint( f_date1_id, recDate::DatePoint::end );
        return;
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
        "DELETE FROM EventaPersona WHERE eventa_id=" ID ";"
        "DELETE FROM ReferenceEntity WHERE entity_type=2 AND entity_id=" ID ";",
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
        "UPDATE Eventa SET date1_id=0, date_pt=0 WHERE date1_id=" ID ";"
        "UPDATE Eventa SET date2_id=0 WHERE date2_id=" ID ";",
        dateID, dateID
    );
    s_db->ExecuteUpdate( sql );
}

void recEventa::RemovePlace( idt placeID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Eventa SET place_id=0 WHERE place_id=" ID ";",
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

    sql.Format( "SELECT COUNT(*) FROM EventaPersona WHERE eventa_id=" ID ";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format( "SELECT COUNT(*) FROM EventEventa WHERE eventa_id=" ID ";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format( "SELECT COUNT(*) FROM FamilyIndEventa WHERE event_id=" ID ";", id );
    if ( s_db->ExecuteScalar( sql ) > 0 ) return;
    sql.Format( "SELECT COUNT(*) FROM FamilyEventa WHERE event_id=" ID ";", id );
    if ( s_db->ExecuteScalar( sql ) > 0 ) return;

    RemoveFromDatabase( id );
}

wxSQLite3Table recEventa::GetTitleList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM \"%s\".Eventa"
        " WHERE NOT id=0 ORDER BY id;", UTF8_( dbname )
    );
    return s_db->GetTable( sql );
}

wxSQLite3Table recEventa::GetTitleList( idt offset, int limit, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM \"%s\".Eventa"
        " WHERE NOT id=0 ORDER BY id LIMIT " ID ", %d;",
        UTF8_( dbname ), offset, limit
    );
    return s_db->GetTable( sql );
}

int recEventa::GetLastPerSeqNumber( idt eventID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(per_seq) FROM \"%s\".EventaPersona WHERE eventa_id=" ID ";",
        eventID
    );
    return s_db->ExecuteScalar( sql );
}

recFamilyEventaVec recEventa::GetFamilyEventas( idt eaID, const wxString& dbname )
{
    recFamilyEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, fam_id, conf, note FROM "
        "  \"%s\".FamilyEventa WHERE eventa_id=" ID ";",
        UTF8_( dbname ), eaID
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

recFamilyIndEventaVec recEventa::GetFamilyIndEventas( idt eaID, const wxString& dbname )
{
    recFamilyIndEventaVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, fam_ind_id, conf, note FROM "
        "  \"%s\".FamilyIndEventa WHERE eventa_id=" ID ";",
        UTF8_( dbname ), eaID
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

recIdVec recEventa::GetLinkedEventIDs( idt eaID, const wxString& dbname )
{
    return ExecuteIdVec(
        "SELECT event_id FROM \"%s\".EventEventa"
        " WHERE eventa_id=" ID
        " ORDER BY event_id;",
        UTF8_( dbname ), eaID
    );
}

wxString recEventa::GetLinkedEventIDsStr( idt eaID, const wxString& dbname )
{
    recIdVec eveIDs = GetLinkedEventIDs( eaID, dbname );
    wxString str;
    for ( size_t i = 0; i < eveIDs.size(); i++ ) {
        if ( i ) {
            str << ", ";
        }
        str << recEvent::GetIdStr( eveIDs[i] );
    }
    return str;
}

recIdVec recEventa::FindLinkedEventsViaInd( const wxString& dbname ) const
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id"
        " FROM \"%s\".EventaPersona EP, \"%s\".IndividualPersona IP,"
        " \"%s\".IndividualEvent IE, \"%s\".EventTypeRole ETR"
        " WHERE EP.eventa_id=" ID
        " AND EP.per_id=IP.per_id AND IP.ind_id=IE.ind_id"
        " AND EP.role_id=IE.role_id"
        " AND EP.role_id=ETR.id AND ETR.prime>0"
        " GROUP BY IE.event_id"
        " ORDER BY IE.event_id;",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), f_id
    );
    return ExecuteIdVec( sql );
}

recCheckIdVec recEventa::FindCheckedLinkedEvents( const wxString& dbname ) const
{
    recCheckIdVec list;
    recIdVec e1 = GetLinkedEventIDs( dbname );
    recIdVec e2 = FindLinkedEventsViaInd( dbname );

    // This assumes e1 and e2 are both in ascending order
    for ( size_t i = 0, j = 0; i < e1.size() || j < e2.size(); ) {
        recCheckID chk;
        if ( i == e1.size() ) {
            chk.SetIDs( 0, e2[j++] );
        } else if ( j == e2.size() ) {
            chk.SetIDs( e1[i++], 0 );
        } else if ( e1[i] == e2[j] ) {
            chk.SetIDs( e1[i++], e2[j++] );
        } else if ( e1[i] > e2[j] ) {
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
