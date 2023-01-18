/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Individual record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010..2023, Nick Matthews.
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
#include <rec/recFamily.h>

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
    f_sex     = Sex::unstated;
    f_fam_id  = 0;
    f_note    = wxEmptyString;
    f_privacy = 0;
    f_name    = wxEmptyString;
    f_surname = wxEmptyString;
    f_epitaph = wxEmptyString;
}

void recIndividual::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    UpdateEpitaph(); // Ensure date epitaph is up todate

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Individual"
            " (sex, fam_id, note, privacy, name, surname, epitaph)"
            " VALUES (%u, " ID ", '%q', %d, '%q', '%q', '%q');",
            UTF8_( dbname ), f_sex, f_fam_id, UTF8_(f_note), f_privacy,
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
                "INSERT INTO \"%s\".Individual"
                " (id, sex, fam_id, note, privacy, name, surname, epitaph)"
                " VALUES (" ID ", %u, " ID ", '%q', %d, '%q', '%q', '%q');",
                UTF8_( dbname ), f_id, f_sex, f_fam_id, UTF8_(f_note), f_privacy,
                UTF8_(f_name), UTF8_(f_surname), UTF8_(f_epitaph)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Individual"
                " SET sex=%u, fam_id=" ID ", note='%q', privacy=%d,"
                " name='%q', surname='%q', epitaph='%q'"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_sex, f_fam_id, UTF8_(f_note), f_privacy,
                UTF8_(f_name), UTF8_(f_surname), UTF8_(f_epitaph), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recIndividual::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT sex, fam_id, note, privacy, name, surname, epitaph"
        " FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), f_id
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

bool recIndividual::Equivalent( const recIndividual& r2 ) const
{
    return
        f_sex == r2.f_sex &&
        f_fam_id == r2.f_fam_id &&
        f_note == r2.f_note &&
        f_privacy == r2.f_privacy &&
        f_name == r2.f_name &&
        f_surname == r2.f_surname &&
        f_epitaph == r2.f_epitaph
    ;
}

recIndividualVec recIndividual::ReadVec( unsigned sexfilter, const wxString& dbname )
{
    wxString query =
        "SELECT id, sex, fam_id, note, privacy, name, surname, epitaph FROM ";
    wxString queryMid = "\"" + dbname + "\".Individual WHERE ";
    if( sexfilter == recInd_FILTER_SexAll ) {
        query << "\"" << dbname << "\".Individual ";
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

recIdVec recIndividual::GetIdVec( const wxString& dbname )
{
    return ExecuteIdVec( "SELECT id FROM \"%s\".Individual ORDER BY id;", UTF8_( dbname ), 0 );
}

wxString recIndividual::GetDescriptionStr( idt indID, const wxString& dbname )
{
    recIndividual ind( indID, dbname );
    if( ind.FGetID() == 0 ) {
        return wxEmptyString;
    }
    wxString name = ind.FGetName();
    if( name.empty() ) {
        name = "? ?";
    }
    if( !ind.FGetEpitaph().empty() ) {
        return name + " " + ind.FGetEpitaph();
    }
    return name;
}

void recIndividual::UpdateEpitaph( idt indID, const wxString& dbname )
{
    recIndividual ind( indID, dbname );
    ind.UpdateEpitaph( dbname );
    ind.Save( dbname );
}

void recIndividual::UpdateEpitaph( const wxString& dbname )
{
    idt bDateID, dDateID;

    bDateID = recEvent::GetDate1ID( GetBirthEvent( dbname ), dbname );
    if( bDateID == 0 ) {
        bDateID = recEvent::GetDate1ID( GetNrBirthEvent( dbname ), dbname );
    }
    dDateID = recEvent::GetDate1ID( GetDeathEvent( dbname ), dbname );
    if( dDateID == 0 ) {
        dDateID = recEvent::GetDate1ID( GetNrDeathEvent( dbname ), dbname );
    }
    if( bDateID == 0 && dDateID == 0 ) {
        f_epitaph = wxEmptyString;
        return;
    }

    f_epitaph = "(";
    if( bDateID ) {
        f_epitaph << recDate::GetYear( bDateID, dbname );
    } else {
        f_epitaph << " ";
    }
    f_epitaph << " - ";
    if( dDateID ) {
        f_epitaph << recDate::GetYear( dDateID, dbname );
    } else {
        f_epitaph << " ";
    }
    f_epitaph << ")";
}

void recIndividual::UpdateNames( const wxString& dbname )
{
    idt nameID = GetNameID( dbname );
    f_surname = recName::GetSurname( nameID, dbname );
    if( f_surname.length() == 0 ) f_surname = "?";
    f_name = recName::GetNameStr( nameID, dbname );
    if( f_name.length() == 0 ) f_name = "? ?";
}

void recIndividual::UpdateDefaultFamily( const wxString& dbname )
{
    recFamilyVec families = recFamily::GetFamilyList( f_id, dbname );
    if( families.empty() ) {
        // Create a new family.
        recFamily fam( 0 );
        if ( f_sex == Sex::female ) {
            fam.FSetWifeID( f_id );
        } else {
            fam.FSetHusbID( f_id );
        }
        fam.Save( dbname );
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

void recIndividual::Update( const wxString& dbname )
{
    UpdateDefaultFamily( dbname );
    UpdateNames( dbname );
    UpdateEpitaph( dbname );
}

void recIndividual::Update( idt indID, const wxString& dbname )
{
    if( indID ) {
        recIndividual ind( indID, dbname );
        ind.Update( dbname );
        ind.Save( dbname );
    }
}

recIndividualVec recIndividual::GetChildren( idt famID, const wxString& dbname )
{
    recIndividualVec children;

    if( famID == 0 ) return children;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ind_id FROM \"%s\".FamilyIndividual WHERE fam_id=" ID " "
        "ORDER BY seq_child ASC;", UTF8_( dbname ), famID
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    recIndividual ind;
    for( int i = 0; i < result.GetRowCount(); i++ )
    {
        result.SetRow( i );
        ind.f_id = GET_ID( result.GetInt64( 0 ) );
        ind.Read( dbname );
        children.push_back( ind );
    }
    return children;
}

Sex recIndividual::GetSex( idt indID, const wxString& dbname )
{
    if( indID == 0 ) {
        return Sex::unstated;
    }
    int i = ExecuteInt( "SELECT sex FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), indID );
    wxASSERT( i >= 0 && i <= static_cast<int>(Sex::unknown) );
    return Sex( i );
}

idt recIndividual::GetFamilyID( idt indID, const wxString& dbname )
{
    if( indID == 0 ) {
        return 0;
    }
    return ExecuteID( "SELECT fam_id FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), indID );
}

int recIndividual::GetPrivacy( idt indID, const wxString& dbname )
{
    if( indID == 0 ) {
        return 0;
    }
    return ExecuteInt( "SELECT privacy FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), indID );
}

wxString recIndividual::GetName( idt indID, const wxString& dbname )
{
    if( indID == 0 ) {
        return wxEmptyString;
    }
    return ExecuteStr( "SELECT name FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), indID );
}

wxString recIndividual::GetSurname( idt indID, const wxString& dbname )
{
    if( indID == 0 ) {
        return wxEmptyString;
    }
    return ExecuteStr( "SELECT surname FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), indID );
}

wxString recIndividual::GetEpitaph( idt indID, const wxString& dbname )
{
    if( indID == 0 ) {
        return wxEmptyString;
    }
    return ExecuteStr( "SELECT epitaph FROM \"%s\".Individual WHERE id=" ID ";", UTF8_( dbname ), indID );
}

idt recIndividual::FindEvent( idt indID, idt roleID, const wxString& dbname )
{
    if( indID == 0 || roleID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT event_id FROM \"%s\".IndividualEvent WHERE ind_id=" ID " AND role_id=" ID ";",
        UTF8_( dbname ), indID, roleID
    );
    return ExecuteID( sql );
}

idt recIndividual::FindGroupEvent( idt indID, recEventTypeGrp grp, const wxString& dbname )
{
    if( indID == 0 || grp == recEventTypeGrp::unstated ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id FROM \"%s\".IndividualEvent IE "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM \"%s\".EventTypeRole R "
        "  INNER JOIN "
        "  \"%s\".EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND R.prime=1) "
        "ON rid=IE.role_id WHERE IE.ind_id=" ID " AND IE.higher_id=0 "
        "ORDER BY IE.ind_seq;",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), grp, indID
    );
    return ExecuteID( sql );
}

idt recIndividual::GetNrBirthEventID( idt indID, const wxString& dbname )
{
    return ExecuteID(
        "SELECT E.id"
        " FROM \"" + dbname + "\".IndividualEvent IE, \""
        + dbname + "\".Event E, \"" + dbname + "\".EventType ET"
        " WHERE ind_id=" ID " AND IE.event_id=E.id AND E.type_id=ET.id"
        " AND ET.grp=2 AND ET.sig>25 ORDER BY ET.sig DESC, E.date_pt;",
        indID, dbname
    );
}

idt recIndividual::GetNrDeathEventID( idt indID, const wxString& dbname )
{
    return ExecuteID(
        "SELECT E.id"
        " FROM \"" + dbname + "\".IndividualEvent IE, \""
        + dbname + "\".Event E, \"" + dbname + "\".EventType ET"
        " WHERE ind_id=" ID " AND IE.event_id=E.id AND E.type_id=ET.id"
        " AND ET.grp=6 AND ET.sig>25 ORDER BY ET.sig DESC, E.date_pt DESC;",
        indID, dbname
    );
}

recIdVec recIndividual::FindEvents( idt indID, idt roleID, const wxString& dbname )
{
    if ( indID == 0 || roleID == 0 ) return recIdVec();

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT event_id FROM \"%s\".IndividualEvent WHERE ind_id=" ID " AND role_id=" ID ";",
        UTF8_( dbname ), indID, roleID
    );
    return ExecuteIdVec( sql );
}

recIdVec recIndividual::FindGroupEvents( idt indID, recEventTypeGrp grp, const wxString& dbname )
{
    recIdVec eIDs;
    if( indID == 0 || grp == recEventTypeGrp::unstated ) {
        return eIDs;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id FROM \"%s\".IndividualEvent IE "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM \"%s\".EventTypeRole R "
        "  INNER JOIN "
        "  \"%s\".EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND R.prime=1) "
        "ON rid=IE.role_id WHERE IE.ind_id=" ID " "
        "ORDER BY IE.ind_seq;",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), grp, indID
    );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    while( result.NextRow() ) {
        eIDs.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return eIDs;
}

idt recIndividual::GetPersonalSummaryIE( idt indID, idt etID, const wxString& dbname )
{
    if( indID == 0 || etID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.id FROM \"%s\".IndividualEvent IE, \"%s\".EventTypeRole ET"
        " WHERE IE.role_id=ET.id AND IE.ind_id=" ID
        " AND ET.type_id=" ID " AND IE.higher_id=0;",
        UTF8_( dbname ), UTF8_( dbname ), indID, etID
    );
    return ExecuteID( sql );
}

idt recIndividual::GetPersonalSummaryEvent( idt indID, idt etID, const wxString& dbname )
{
    if( indID == 0 || etID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT IE.event_id FROM \"%s\".IndividualEvent IE, \"%s\".EventTypeRole ET"
        " WHERE IE.role_id=ET.id AND IE.ind_id=" ID
        " AND ET.type_id=" ID " AND IE.higher_id=0;",
        UTF8_( dbname ), UTF8_( dbname ), indID, etID
    );
    return ExecuteID( sql );
}

idt recIndividual::CreateBirthDate( idt indID, const wxString& dbname )
{
    recDate::TypePrefix prefix = recDate::PREF_Unstated;
    recEvent e( GetBirthEvent( indID, dbname ), dbname );
    if( e.FGetID() == 0 ) {
        e.ReadID( GetNrBirthEvent( indID, dbname ), dbname );
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

idt recIndividual::CreateDeathDate( idt indID, const wxString& dbname )
{
    recDate::TypePrefix prefix = recDate::PREF_Unstated;
    recEvent e( GetDeathEvent( indID, dbname ), dbname );
    if( e.FGetID() == 0 ) {
        e.ReadID( GetNrDeathEvent( indID, dbname ), dbname );
        prefix = recDate::PREF_OrBefore;
    }
    if( e.FGetDate1ID() == 0 ) {
        return 0; // No event or date found
    }
    recDate date( e.FGetDate1ID(), dbname );
    date.FSetID( 0 );
    date.FSetType( date.FGetType() | prefix );
    date.Save( dbname );
    return date.FGetID();
}

recIndEventVec recIndividual::GetEvents( idt indID, recEventOrder order, const wxString& dbname )
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
        "SELECT IE.id, event_id, role_id, IE.note, ind_seq FROM \"%s\".IndividualEvent IE"
        " INNER JOIN \"%s\".Event E ON E.id=event_id"
        " WHERE IE.higher_id=0 AND ind_id=" ID " ORDER BY %s;",
        UTF8_( dbname ), UTF8_( dbname ), indID, UTF8_(orderStr)
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

wxSQLite3ResultSet recIndividual::GetEventaSet( idt indID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT eventa_id, role_id FROM"
        "   (SELECT DISTINCT eventa_id, role_id FROM \"%s\".EventaPersona EP"
        "  INNER JOIN"
        "   (SELECT per_id AS ip_per_id FROM \"%s\".IndividualPersona WHERE ind_id=" ID ")"
        "  ON EP.per_id=ip_per_id)"
        " INNER JOIN \"%s\".Eventa WHERE id=eventa_id"
        " ORDER BY date_pt;",
        UTF8_( dbname ), UTF8_( dbname ), indID, UTF8_( dbname )
    );
    return s_db->ExecuteQuery( sql );
}

wxSQLite3ResultSet recIndividual::GetReferenceSet( idt indID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT R.id, R.title "
        "FROM \"%s\".IndividualPersona IP, \"%s\".Persona P, \"%s\".Reference R "
        "WHERE IP.ind_id=" ID " AND IP.per_id=P.id AND P.ref_id=R.id;",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), indID
    );
    return s_db->ExecuteQuery( sql );
}

wxSQLite3ResultSet recIndividual::GetNameSet( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT name, epitaph, id FROM \"%s\".Individual WHERE NOT id=0"
        " ORDER BY surname, name, epitaph;", UTF8_( dbname )
    );

    return s_db->ExecuteQuery( sql );
}

int recIndividual::GetMaxEventSeqNumber( idt indID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(ind_seq) FROM \"%s\".IndividualEvent WHERE ind_id=" ID ";",
        UTF8_( dbname ), indID
    );
    return s_db->ExecuteScalar( sql );
}

bool recIndividual::CreateMissingFamilies( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, sex FROM \"%s\".Individual WHERE fam_id=0;", UTF8_( dbname )
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        idt indID = GET_ID( result.GetInt64( 0 ) );
        if( indID <= 0 ) continue;
        Sex sex = (Sex) result.GetInt( 1 );
        recFamily fam(0);
        if( sex == Sex::female ) {
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

std::string recIndividual::CsvTitles()
{
    return std::string(
        "id, sex, fam_id, 'note', privacy, 'name', 'surname', 'epitaph'\n"
    );
}

void recIndividual::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recIndividual ind( id, dbname );
    recCsvWrite( out, ind.FGetID() );
    recCsvWrite( out, static_cast<int>(ind.FGetSex()) );
    recCsvWrite( out, ind.FGetFamID() );
    recCsvWrite( out, ind.FGetNote() );
    recCsvWrite( out, ind.FGetPrivacy() );
    recCsvWrite( out, ind.FGetName() );
    recCsvWrite( out, ind.FGetSurname() );
    recCsvWrite( out, ind.FGetEpitaph(), '\n' );
}

bool recIndividual::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    int sex;
    recCsvRead( in, sex );
    f_sex = static_cast<Sex>(sex);
    recCsvRead( in, f_fam_id );
    recCsvRead( in, f_note );
    recCsvRead( in, f_privacy );
    recCsvRead( in, f_name );
    recCsvRead( in, f_surname );
    recCsvRead( in, f_epitaph );
    return bool( in );
}

void recIndividual::RemoveFromDatabase( idt indID, const wxString& dbname )
{
    // TODO: Delete orphaned EventType and/or EventTypeRole
    // TODO: Remove ContactList if orphaned
    if( indID <= 0 ) {
        return;
    }

    recNameVec names = GetNames( indID, dbname );
    for ( size_t i = 0; i < names.size(); i++ ) {
        names[i].RemoveFromDatabase( dbname );
    }

    recFamilyVec families = recFamily::GetFamilyList( indID, dbname );
    for ( size_t i = 0; i < families.size(); i++ ) {
        if ( families[i].f_husb_id == indID ) {
            families[i].f_husb_id = 0;
        }
        if ( families[i].f_wife_id == indID ) {
            families[i].f_wife_id = 0;
        }
        if ( families[i].f_husb_id == 0 && families[i].f_wife_id == 0 ) {
            families[i].RemoveFromDatabase( dbname );
        } else {
            families[i].Save( dbname );
        }
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "DELETE FROM \"%s\".FamilyIndividual WHERE ind_id=" ID " ;"
        "DELETE FROM \"%s\".IndividualEvent WHERE ind_id=" ID ";"
        "DELETE FROM \"%s\".IndividualPersona WHERE ind_id=" ID ";",
        UTF8_( dbname ), indID, UTF8_( dbname ), indID, UTF8_( dbname ), indID
    );
    s_db->ExecuteUpdate( sql );

    Delete( indID );
}

// End of src/rec/recIndividual.cpp file
