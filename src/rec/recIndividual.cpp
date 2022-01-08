/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Individual record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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

#include <rec/recIndividual.h>


//============================================================================
//-------------------------[ recIndividual ]----------------------------------
//============================================================================

recIndividual::recIndividual( const recIndividual& i )
{
    f_id      = i.f_id;
    f_sex     = i.f_sex;
    f_fam_id  = i.f_fam_id;
    f_note    = i.f_note;
    f_privacy = i.f_privacy;
    f_name    = i.f_name;
    f_surname = i.f_surname;
    f_epitaph = i.f_epitaph;
}

void recIndividual::Clear()
{
    f_id      = 0;
    f_sex     = SEX_Unstated;
    f_fam_id  = 0;
    f_note    = wxEmptyString;
    f_privacy = 0;
    f_name    = wxEmptyString;
    f_surname = wxEmptyString;
    f_epitaph = wxEmptyString;
}

void recIndividual::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    UpdateEpitaph(); // Ensure date epitaph is up todate

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Individual"
            " (sex, fam_id, note, privacy, name, surname, epitaph)"
            " VALUES (%u, " ID ", '%q', %d, '%q', '%q', '%q');",
            f_sex, f_fam_id, UTF8_(f_note), f_privacy,
            UTF8_(f_name), UTF8_(f_surname), UTF8_(f_epitaph)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Individual"
                " (id, sex, fam_id, note, privacy, name, surname, epitaph)"
                " VALUES (" ID ", %u, " ID ", '%q', %d, '%q', '%q', '%q');",
                f_id, f_sex, f_fam_id, UTF8_(f_note), f_privacy,
                UTF8_(f_name), UTF8_(f_surname), UTF8_(f_epitaph)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Individual"
                " SET sex=%u, fam_id=" ID ", note='%q', privacy=%d,"
                " name='%q', surname='%q', epitaph='%q'"
                " WHERE id=" ID ";",
                f_sex, f_fam_id, UTF8_(f_note), f_privacy,
                UTF8_(f_name), UTF8_(f_surname), UTF8_(f_epitaph), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recIndividual::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT sex, fam_id, note, privacy, name, surname, epitaph"
        " FROM Individual WHERE id=" ID ";", f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_sex     = (Sex) result.GetInt( 0 );
    f_fam_id  = GET_ID( result.GetInt64( 1 ) );
    f_note    = result.GetAsString( 2 );
    f_privacy = result.GetInt( 3 );
    f_name    = result.GetAsString( 4 );
    f_surname = result.GetAsString( 5 );
    f_epitaph = result.GetAsString( 6 );
    return true;
}

recIndividualVec recIndividual::ReadVec( unsigned sexfilter )
{
    wxString query =
        "SELECT id, sex, fam_id, note, privacy, name, surname, epitaph FROM ";
    wxString queryMid = "Individual WHERE ";
    if( sexfilter == recInd_FILTER_SexAll ) {
        query << "Individual ";
    } else if( sexfilter == recInd_FILTER_SexMalePlus ) {
        query << queryMid << "NOT sex=2 ";
    } else if( sexfilter == recInd_FILTER_SexFemalePlus ) {
        query << queryMid << "NOT sex=1 ";
    } else {
        bool started = false;
        query << queryMid;
        if( sexfilter & recInd_FILTER_SexUnstated ) {
            if( started ) query << "OR "; else started = true;
            query << "sex=0 ";
        }
        if( sexfilter & recInd_FILTER_SexMale ) {
            if( started ) query << "OR "; else started = true;
            query << "sex=1 ";
        }
        if( sexfilter & recInd_FILTER_SexFemale ) {
            if( started ) query << "OR "; else started = true;
            query << "sex=2 ";
        }
        if( sexfilter & recInd_FILTER_SexUnknown ) {
            if( started ) query << "OR "; else started = true;
            query << "sex=3 ";
        }
    }
    query << "ORDER BY surname, name, epitaph, id;";

    wxSQLite3ResultSet result = s_db->ExecuteQuery( query );

    recIndividual ind;
    recIndividualVec inds;
    while( result.NextRow() ) {
        ind.f_id      = GET_ID( result.GetInt64( 0 ) );
        ind.f_sex     = (Sex) result.GetInt( 1 );
        ind.f_fam_id  = GET_ID( result.GetInt64( 2 ) );
        ind.f_note    = result.GetAsString( 3 );
        ind.f_privacy = result.GetInt( 4 );
        ind.f_name    = result.GetAsString( 5 );
        ind.f_surname = result.GetAsString( 6 );
        ind.f_epitaph = result.GetAsString( 7 );
        inds.push_back( ind );
    }
    return inds;
}

recIdVec recIndividual::GetIdVec()
{
    return ExecuteIdVec( "SELECT id FROM Individual ORDER BY id;", 0 );
}

wxString recIndividual::GetDescriptionStr( idt indID )
{
    recIndividual ind(indID);
    if( ind.FGetID() == 0 ) {
        return wxEmptyString;
    }
    wxString name = ind.FGetName();
    if( name.size() == 0 ) {
        name = "? ?";
    }
    if( ind.FGetEpitaph().size() ) {
        return name + " " + ind.FGetEpitaph();
    }
    return name;
}

void recIndividual::UpdateEpitaph( idt indID )
{
    recIndividual ind(indID);
    ind.UpdateEpitaph();
    ind.Save();
}

void recIndividual::UpdateEpitaph()
{
    idt bDateID, dDateID;

    bDateID = recEvent::GetDate1ID( GetBirthEvent() );
    if( bDateID == 0 ) {
        bDateID = recEvent::GetDate1ID( GetNrBirthEvent() );
    }
    dDateID = recEvent::GetDate1ID( GetDeathEvent() );
    if( dDateID == 0 ) {
        dDateID = recEvent::GetDate1ID( GetNrDeathEvent() );
    }
    if( bDateID == 0 && dDateID == 0 ) {
        f_epitaph = wxEmptyString;
        return;
    }

    f_epitaph = "(";
    if( bDateID ) {
        f_epitaph << recDate::GetYear( bDateID );
    } else {
        f_epitaph << " ";
    }
    f_epitaph << " - ";
    if( dDateID ) {
        f_epitaph << recDate::GetYear( dDateID );
    } else {
        f_epitaph << " ";
    }
    f_epitaph << ")";
}

void recIndividual::UpdateNames()
{
    idt nameID = GetNameID();
    f_surname = recName::GetSurname( nameID );
    if( f_surname.length() == 0 ) f_surname = "?";
    f_name = recName::GetNameStr( nameID );
    if( f_name.length() == 0 ) f_name = "? ?";
}

void recIndividual::UpdateDefaultFamily()
{
    recFamilyVec families = GetFamilyList();
    if( families.size() == 0 ) {
        // Create a new family.
        recFamily fam( 0 );
        if ( f_sex == SEX_Female ) {
            fam.FSetWifeID( f_id );
        } else {
            fam.FSetHusbID( f_id );
        }
        fam.Save();
        f_fam_id = fam.FGetID();
        return;
    }
    for( size_t i = 0 ; i < families.size() ; i++ ) {
        if( families[i].FGetID() == f_fam_id ) {
            return;
        }
    }
    f_fam_id = families[0].FGetID();
}

void recIndividual::Update()
{
    UpdateDefaultFamily();
    UpdateNames();
    UpdateEpitaph();
}

void recIndividual::Update( idt indID )
{
    if( indID ) {
        recIndividual ind(indID);
        ind.Update();
        ind.Save();
    }
}

Sex recIndividual::GetSex( idt indID )
{
    if( indID == 0 ) {
        return SEX_Unstated;
    }
    int i = ExecuteInt( "SELECT sex FROM Individual WHERE id=" ID ";", indID );
    wxASSERT( i >= 0 && i <= SEX_Unknown );
    return Sex( i );
}

idt recIndividual::GetFamilyID( idt indID )
{
    if( indID == 0 ) {
        return 0;
    }
    return ExecuteID( "SELECT fam_id FROM Individual WHERE id=" ID ";", indID );
}

int recIndividual::GetPrivacy( idt indID )
{
    if( indID == 0 ) {
        return 0;
    }
    return ExecuteInt( "SELECT privacy FROM Individual WHERE id=" ID ";", indID );
}

wxString recIndividual::GetName( idt indID )
{
    if( indID == 0 ) {
        return wxEmptyString;
    }
    return ExecuteStr( "SELECT name FROM Individual WHERE id=" ID ";", indID );
}

wxString recIndividual::GetSurname( idt indID )
{
    if( indID == 0 ) {
        return wxEmptyString;
    }
    return ExecuteStr( "SELECT surname FROM Individual WHERE id=" ID ";", indID );
}

wxString recIndividual::GetEpitaph( idt indID )
{
    if( indID == 0 ) {
        return wxEmptyString;
    }
    return ExecuteStr( "SELECT epitaph FROM Individual WHERE id=" ID ";", indID );
}

idt recIndividual::FindEvent( idt indID, idt roleID )
{
    if( indID == 0 || roleID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT event_id FROM IndividualEvent WHERE ind_id=" ID " AND role_id=" ID ";",
        indID, roleID
    );
    return ExecuteID( sql );
}

idt recIndividual::FindGroupEvent( idt indID, recEventTypeGrp grp )
{
    if( indID == 0 || grp == recEventTypeGrp::unstated ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id FROM IndividualEvent IE "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM EventTypeRole R "
        "  INNER JOIN "
        "  EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND R.prime=1) "
        "ON rid=IE.role_id WHERE IE.ind_id=" ID " "
        "ORDER BY IE.ind_seq;",
        grp, indID
    );
    return ExecuteID( sql );
}

recIdVec recIndividual::FindEvents( idt indID, idt roleID )
{
    if ( indID == 0 || roleID == 0 ) return recIdVec();

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT event_id FROM IndividualEvent WHERE ind_id=" ID " AND role_id=" ID ";",
        indID, roleID
    );
    return ExecuteIdVec( sql );
}

recIdVec recIndividual::FindGroupEvents( idt indID, recEventTypeGrp grp )
{
    recIdVec eIDs;
    if( indID == 0 || grp == recEventTypeGrp::unstated ) {
        return eIDs;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id FROM IndividualEvent IE "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM EventTypeRole R "
        "  INNER JOIN "
        "  EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND R.prime=1) "
        "ON rid=IE.role_id WHERE IE.ind_id=" ID " "
        "ORDER BY IE.ind_seq;",
        grp, indID
    );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    while( result.NextRow() ) {
        eIDs.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return eIDs;
}

idt recIndividual::GetPersonalSummaryIE( idt indID, idt etID )
{
    if( indID == 0 || etID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.id FROM IndividualEvent IE, EventTypeRole ET"
        " WHERE IE.role_id=ET.id AND IE.ind_id=" ID
        " AND ET.type_id=" ID " AND IE.higher_id=0;",
        indID, etID
    );
    return ExecuteID( sql );
}

idt recIndividual::GetPersonalSummaryEvent( idt indID, idt etID )
{
    if( indID == 0 || etID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id FROM IndividualEvent IE, EventTypeRole ET"
        " WHERE IE.role_id=ET.id AND IE.ind_id=" ID
        " AND ET.type_id=" ID " AND IE.higher_id=0;",
        indID, etID
    );
    return ExecuteID( sql );
}

idt recIndividual::CreateBirthDate( idt indID )
{
    recDate::TypePrefix prefix = recDate::PREF_Unstated;
    recEvent e( GetBirthEvent( indID ) );
    if( e.FGetID() == 0 ) {
        e.ReadID( GetNrBirthEvent( indID ) );
        prefix = recDate::PREF_OrBefore;
    }
    if( e.FGetDate1ID() == 0 ) {
        return 0; // No event or date found
    }
    recDate date( e.FGetDate1ID() );
    date.FSetID( 0 );
    date.FSetType( date.FGetType() | prefix );
    date.Save();
    return date.FGetID();
}

idt recIndividual::CreateDeathDate( idt indID )
{
    recDate::TypePrefix prefix = recDate::PREF_Unstated;
    recEvent e( GetDeathEvent( indID ) );
    if( e.FGetID() == 0 ) {
        e.ReadID( GetNrDeathEvent( indID ) );
        prefix = recDate::PREF_OrBefore;
    }
    if( e.FGetDate1ID() == 0 ) {
        return 0; // No event or date found
    }
    recDate date( e.FGetDate1ID() );
    date.FSetID( 0 );
    date.FSetType( date.FGetType() | prefix );
    date.Save();
    return date.FGetID();
}

recFamilyVec recIndividual::GetFamilyList( idt ind )
{
    recFamilyVec families;
    recFamily family;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( ind == 0 ) return families;

    sql.Format(
        "SELECT id, husb_id, wife_id FROM Family "
        "WHERE husb_id=" ID " OR wife_id=" ID ";",
        ind, ind
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        family.f_id = GET_ID( result.GetInt64( 0 ) );
        family.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        family.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        families.push_back( family );
    }
    return families;
}

recFamilyVec recIndividual::GetParentList( idt indID )
{
    recFamily parent;
    recFamilyVec parents;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 ) return parents;

    sql.Format(
        "SELECT F.id, F.husb_id, F.wife_id "
        "FROM Family F, FamilyIndividual FI "
        "WHERE F.id=FI.fam_id AND FI.ind_id=" ID ";",
        indID
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        parent.f_id = GET_ID( result.GetInt64( 0 ) );
        parent.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        parent.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        parents.push_back( parent );
    }
    return parents;
}

recIndEventVec recIndividual::GetEvents( idt indID, recEventOrder order )
{
    recIndEventVec list;
    recIndividualEvent record;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 ) {
        return list;
    }
    wxString orderStr;
    switch( order )
    {
    case recEO_DatePt:
        orderStr = "date_pt, IE.ind_seq";
        break;
    case recEO_PerSeq:
        orderStr = "IE.ind_seq, date_pt";
        break;
    default:
        wxASSERT( false ); // Shouldn't be here
    }

    sql.Format(
        "SELECT IE.id, event_id, role_id, IE.note, ind_seq FROM IndividualEvent IE"
        " INNER JOIN Event E ON E.id=event_id"
        " WHERE IE.higher_id=0 AND ind_id=" ID " ORDER BY %s;",
        indID, UTF8_(orderStr)
    );
    result = s_db->GetTable( sql );

    list.reserve( result.GetRowCount() );
    record.f_ind_id = indID;
    record.f_higher_id = 0;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        record.f_id       = GET_ID( result.GetInt64( 0 ) );
        record.f_event_id = GET_ID( result.GetInt64( 1 ) );
        record.f_role_id  = GET_ID( result.GetInt64( 2 ) );
        record.f_note     = result.GetAsString( 3 );
        record.f_ind_seq  = result.GetInt( 4 );
        list.push_back( record );
    }
    return list;
}

wxSQLite3ResultSet recIndividual::GetEventaSet( idt indID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT eventa_id, role_id FROM"
        "   (SELECT DISTINCT eventa_id, role_id FROM EventaPersona EP"
        "  INNER JOIN"
        "   (SELECT per_id AS ip_per_id FROM IndividualPersona WHERE ind_id=" ID ")"
        "  ON EP.per_id=ip_per_id)"
        " INNER JOIN Eventa WHERE id=eventa_id"
        " ORDER BY date_pt;",
        indID
    );
    return s_db->ExecuteQuery( sql );
}

wxSQLite3ResultSet recIndividual::GetReferenceSet( idt indID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT R.id, R.title "
        "FROM IndividualPersona IP, Persona P, Reference R "
        "WHERE IP.ind_id=" ID " AND IP.per_id=P.id AND P.ref_id=R.id;",
        indID
    );
    return s_db->ExecuteQuery( sql );
}

wxSQLite3ResultSet recIndividual::GetNameSet()
{
    return s_db->ExecuteQuery(
        "SELECT name, epitaph, id FROM Individual"
        " ORDER BY surname, name, epitaph;"
    );
}

int recIndividual::GetMaxEventSeqNumber( idt indID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(ind_seq) FROM IndividualEvent WHERE ind_id=" ID ";",
        indID
    );
    return s_db->ExecuteScalar( sql );
}

bool recIndividual::CreateMissingFamilies()
{
    wxSQLite3ResultSet result =
        s_db->ExecuteQuery( "SELECT id, sex FROM Individual WHERE fam_id=0;" );

    while( result.NextRow() ) {
        idt indID = GET_ID( result.GetInt64( 0 ) );
        if( indID <= 0 ) continue;
        Sex sex = (Sex) result.GetInt( 1 );
        recFamily fam(0);
        if( sex == SEX_Female ) {
            fam.f_wife_id = indID;
        } else {
            fam.f_husb_id = indID;
        }
        fam.Save();
        recIndividual ind(indID);
        ind.f_fam_id = fam.FGetID();
        ind.Save();
    }
    return true;
}

void recIndividual::RemoveFromDatabase( idt indID )
{
    // TODO: Delete orphaned EventType and/or EventTypeRole
    // TODO: Remove ContactList if orphaned
    if( indID <= 0 ) {
        return;
    }

    recNameVec names = GetNames( indID );
    for ( size_t i = 0; i < names.size(); i++ ) {
        names[i].RemoveFromDatabase();
    }

    recFamilyVec families = GetFamilyList( indID );
    for ( size_t i = 0; i < families.size(); i++ ) {
        if ( families[i].f_husb_id == indID ) {
            families[i].f_husb_id = 0;
        }
        if ( families[i].f_wife_id == indID ) {
            families[i].f_wife_id = 0;
        }
        if ( families[i].f_husb_id == 0 && families[i].f_wife_id == 0 ) {
            families[i].RemoveFromDatabase();
        } else {
            families[i].Save();
        }
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "DELETE FROM FamilyIndividual WHERE ind_id=" ID " ;"
        "DELETE FROM IndividualEvent WHERE ind_id=" ID ";"
        "DELETE FROM IndividualPersona WHERE ind_id=" ID ";",
        indID, indID, indID
    );
    s_db->ExecuteUpdate( sql );

    Delete( indID );
}

// End of src/rec/recIndividual.cpp file
