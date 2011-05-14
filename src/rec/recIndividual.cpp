/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family, FamilyIndividual, Individual and
 *              IndividualPersona records.
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

#include <rec/recIndividual.h>
#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recEvent.h>


recIndividual::recIndividual( const recIndividual& i )
{
    f_id          = i.f_id;
    f_surname     = i.f_surname;
    f_given       = i.f_given;
    f_birth_jdn   = i.f_birth_jdn;
    f_epitaph     = i.f_epitaph;
    f_sex         = i.f_sex;
    f_fam_id      = i.f_fam_id;
    f_per_id      = i.f_per_id;
    f_birth_id    = i.f_birth_id;
    f_nr_birth_id = i.f_nr_birth_id;
    f_death_id    = i.f_death_id;
    f_nr_death_id = i.f_nr_death_id;
    f_occ_id      = i.f_occ_id;
}

void recIndividual::Clear()
{
    f_id          = 0;
    f_surname     = wxEmptyString;
    f_given       = wxEmptyString;
    f_birth_jdn   = 0;
    f_epitaph     = wxEmptyString;
    f_sex         = SEX_Unstated;
    f_fam_id      = 0;
    f_per_id      = 0;
    f_birth_id    = 0;
    f_nr_birth_id = 0;
    f_death_id    = 0;
    f_nr_death_id = 0;
    f_occ_id      = 0;
}

void recIndividual::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    UpdateDateEpitaph(); // Ensure date epitaph is up todate

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Individual (surname, given, birth_jdn, epitaph, sex, "
            "fam_id, per_id, birth_id, nr_birth_id, "
            "death_id, nr_death_id, occ_id) VALUES "
            "('%q', '%q', %ld, '%q', %u, "ID", "ID", "ID", "ID", "ID", "ID", "ID");",
            UTF8_(f_surname), UTF8_(f_given), f_birth_jdn, UTF8_(f_epitaph),
            f_sex, f_fam_id, f_per_id, f_birth_id, f_nr_birth_id,
            f_death_id, f_nr_death_id, f_occ_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Individual (id, surname, given, birth_jdn, epitaph, "
                "sex, fam_id, per_id, birth_id, "
                "nr_birth_id, death_id, nr_death_id, occ_id) "
                "VALUES ("ID", '%q', '%q', %ld, '%q', %u, "ID", "ID", "ID", "ID", "ID", "ID", "ID");",
                f_id, UTF8_(f_surname), UTF8_(f_given), f_birth_jdn, UTF8_(f_epitaph),
                f_sex, f_fam_id, f_per_id, f_birth_id, f_nr_birth_id,
                f_death_id, f_nr_death_id, f_occ_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Individual SET surname='%q', given='%q', birth_jdn=%ld, "
                "epitaph='%q', sex=%u, fam_id="ID", per_id="ID", birth_id="ID", "
                "nr_birth_id="ID", death_id="ID", nr_death_id="ID", occ_id="ID" WHERE id="ID";",
                UTF8_(f_surname), UTF8_(f_given), f_birth_jdn, UTF8_(f_epitaph),
                f_sex, f_fam_id, f_per_id, f_birth_id, f_nr_birth_id,
                f_death_id, f_nr_death_id, f_occ_id, f_id
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
        "SELECT surname, given, birth_jdn, epitaph, sex, fam_id, per_id, "
        "birth_id, nr_birth_id, death_id, nr_death_id, occ_id "
        "FROM Individual WHERE id="ID";", f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_surname     = result.GetAsString( 0 );
    f_given       = result.GetAsString( 1 );
    f_birth_jdn   = result.GetInt( 2 );
    f_epitaph     = result.GetAsString( 3 );
    f_sex         = (Sex) result.GetInt( 4 );
    f_fam_id      = GET_ID( result.GetInt64( 5 ) );
    f_per_id      = GET_ID( result.GetInt64( 6 ) );
    f_birth_id    = GET_ID( result.GetInt64( 7 ) );
    f_nr_birth_id = GET_ID( result.GetInt64( 8 ) );
    f_death_id    = GET_ID( result.GetInt64( 9 ) );
    f_nr_death_id = GET_ID( result.GetInt64( 10 ) );
    f_occ_id      = GET_ID( result.GetInt64( 11 ) );
    return true;
}

void recIndividual::UpdateDateEpitaph()
{
    idt date_id;
    recEvent event;
    recDate date;
    wxString epi;

    epi << wxT("(");

    event.f_id = f_birth_id;
    event.Read();
    date_id = event.f_date1_id;
    if( date_id == 0 ) {
        event.f_id = f_nr_birth_id;
        event.Read();
        date_id = event.f_date1_id;
    }

    date.f_id = date_id;
    if( date.Read() == true && date.f_jdn != 0 )
    {
        epi << date.GetYear();
    } else {
        epi << wxT(" ");
    }
    f_birth_jdn = date.f_jdn;

    epi << wxT(" - ");

    event.f_id = f_death_id;
    event.Read();
    date_id = event.f_date1_id;
    if( date_id == 0 ) {
        event.f_id = f_nr_death_id;
        event.Read();
        date_id = event.f_date1_id;
    }

    date.f_id = date_id;
    if( date.Read() == true && date.f_jdn != 0 )
    {
        epi << date.GetYear();
    } else {
        epi << wxT(" ");
    }

    epi << wxT(")");
    f_epitaph = epi;
}


wxString recIndividual::GetFullName( idt id )
{
    wxString str;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT surname, given FROM Individual WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    str << result.GetAsString( 1 ) << " " << result.GetAsString( 0 );
    return str;
}

wxString recIndividual::GetSurname( idt id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT surname FROM Individual WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

wxString recIndividual::GetDateEpitaph( idt id )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT epitaph FROM Individual WHERE id="ID";", id );
    result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}


recFamilyList recIndividual::GetFamilyList( idt ind )
{
    recFamilyList families;
    recFamily family;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( ind == 0 ) return families;

    sql.Format(
        "SELECT id, husb_id, wife_id, event_id FROM Family "
        "WHERE husb_id="ID" OR wife_id="ID";",
        ind, ind
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        family.f_id = GET_ID( result.GetInt64( 0 ) );
        family.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        family.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        family.f_event_id = GET_ID( result.GetInt64( 3 ) );
        families.push_back( family );
    }
    return families;
}

recFamilyList recIndividual::GetParentList( idt indID )
{
    recFamily parent;
    recFamilyList parents;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 ) return parents;

    sql.Format(
        "SELECT F.id, F.husb_id, F.wife_id, F.event_id "
        "FROM Family F, FamilyIndividual FI "
        "WHERE F.id=FI.fam_id AND FI.ind_id="ID";",
        indID
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        parent.f_id = GET_ID( result.GetInt64( 0 ) );
        parent.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        parent.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        parent.f_event_id = GET_ID( result.GetInt64( 3 ) );
        parents.push_back( parent );
    }
    return parents;
}

recEventPersonaVec recIndividual::GetEventPersonaVec( idt id )
{
    recEventPersona pe;
    recEventPersonaVec peList;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( id == 0 ) return peList;

    sql.Format(
        "SELECT PE.id, PE.per_id, PE.event_id, PE.role_id, PE.note "
        "FROM IndividualPersona IP, EventPersona PE "
        "WHERE IP.per_id=PE.per_id AND IP.ind_id="ID";",
        id
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        pe.f_id = GET_ID( result.GetInt64( 0 ) );
        pe.f_per_id = GET_ID( result.GetInt64( 1 ) );
        pe.f_event_id = GET_ID( result.GetInt64( 2 ) );
        pe.f_role_id = GET_ID( result.GetInt64( 3 ) );
        pe.f_note = result.GetAsString( 4 );
        peList.push_back( pe );
    }

    return peList;
}

wxSQLite3Table recIndividual::GetEventsTable( idt id )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT DISTINCT event_id, role_id FROM EventPersona "
        "INNER JOIN "
        "(SELECT per_id FROM IndividualPersona WHERE ind_id="ID") "
        "USING(per_id);",
        id
    );
    return s_db->GetTable( sql );
}

wxSQLite3Table recIndividual::GetAttributesTable( idt id )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT DISTINCT id, type_id, val FROM Attribute "
        "INNER JOIN "
        "(SELECT per_id FROM IndividualPersona WHERE ind_id="ID") "
        "USING(per_id);",
        id
    );
    return s_db->GetTable( sql );
}

wxArrayString recIndividual::GetEventIdStrList( idt indID, idt etrID )
{
    wxArrayString list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 ) return list;

    sql.Format(
        "SELECT id, title, date1_id, place_id FROM Event "
        "WHERE id=("
        "SELECT event_id FROM EventPersona INNER JOIN "
        "(SELECT per_id AS ipp FROM IndividualPersona WHERE ind_id="ID") Mip "
        "ON per_id=Mip.ipp WHERE role_id=%d"
        ");",
        indID, etrID
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        list.Add( result.GetAsString( 0 ) );
        list.Add( result.GetAsString( 1 ) );
        list.Add( recDate::GetStr( GET_ID( result.GetInt64( 2 ) ) ) );
        list.Add( recPlace::GetAddressStr( GET_ID( result.GetInt64( 3 ) ) ) );
    }
    return list;
}

wxSQLite3ResultSet recIndividual::GetNameList( wxString surname )
{
    wxSQLite3StatementBuffer sql;

    if( surname.length() == 0 ) {
        // Full list
        sql.Format(
            "SELECT surname, given, epitaph, fam_id FROM Individual "
            "ORDER BY surname, given, birth_jdn;"
        );
    } else if( surname.length() == 1 ) {
        // Name beginning with letter
        wxString name = surname + wxT("%");
        sql.Format(
            "SELECT surname, given, epitaph, fam_id FROM Individual "
            "WHERE surname LIKE '%q' ORDER BY surname, given, birth_jdn;",
            UTF8_(name)
        );
    } else {
        // All matching the given surname
        sql.Format(
            "SELECT surname, given, epitaph, fam_id FROM Individual "
            "WHERE surname='%q' ORDER BY surname, given;",
            UTF8_(surname)
        );
    }
    return s_db->ExecuteQuery( sql );
}

wxSQLite3Table recIndividual::GetNameTable( Sex sex )
{
    wxSQLite3StatementBuffer sql;

    if( sex == SEX_Unstated ) {
        sql.Format(
            "SELECT id, surname, given, epitaph, sex, fam_id FROM Individual "
            "ORDER BY surname, given;"
        );
    } else {
        sql.Format(
            "SELECT id, surname, given, epitaph, sex, fam_id FROM Individual "
            "WHERE sex=%d ORDER BY surname, given;", sex
        );
    }
    return s_db->GetTable( sql );
}

//----------------------------------------------------------

recIndividualPersona::recIndividualPersona( const recIndividualPersona& ip )
{
    f_id     = ip.f_id;
    f_per_id = ip.f_per_id;
    f_ind_id = ip.f_ind_id;
    f_note   = ip.f_note;
}

void recIndividualPersona::Clear()
{
    f_id     = 0;
    f_per_id = 0;
    f_ind_id = 0;
    f_note   = wxEmptyString;
}

void recIndividualPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO IndividualPersona (per_id, ind_id, note) "
            "VALUES ("ID", "ID", '%q');",
            f_per_id, f_ind_id, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO IndividualPersona (id, per_id, ind_id, note) "
                "VALUES ("ID", "ID", "ID", '%q');",
                f_id, f_per_id, f_ind_id, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE IndividualPersona SET per_id="ID", ind_id="ID", note='%q' "
                "WHERE id="ID";",
                f_per_id, f_ind_id, UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recIndividualPersona::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT per_id, ind_id, note FROM IndividualPersona "
        "WHERE id="ID";", f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_per_id = GET_ID( result.GetInt64( 0 ) );
    f_ind_id = GET_ID( result.GetInt64( 1 ) );
    f_note   = result.GetAsString( 2 );
    return true;
}

/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recIndividualPersona::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_per_id == 0 || f_ind_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, note FROM IndividualPersona "
        "WHERE per_id="ID" AND ind_id="ID";",
        f_per_id, f_ind_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_note = result.GetAsString( 1 );
    return true;
}


//----------------------------------------------------------

recFamily::recFamily( const recFamily& f )
{
    f_id       = f.f_id;
    f_husb_id  = f.f_husb_id;
    f_wife_id  = f.f_wife_id;
    f_event_id = f.f_event_id;
}

void recFamily::Clear()
{
    f_id       = 0;
    f_husb_id  = 0;
    f_wife_id  = 0;
    f_event_id = 0;
}

void recFamily::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Family (husb_id, wife_id, event_id) "
            "VALUES ("ID", "ID", "ID");",
            f_husb_id, f_wife_id, f_event_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Family (id, husb_id, wife_id, event_id) "
                "VALUES ("ID", "ID", "ID", "ID");",
                f_id, f_husb_id, f_wife_id, f_event_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Family SET husb_id="ID", wife_id="ID", event_id="ID" "
                "WHERE id="ID";",
                f_husb_id, f_wife_id, f_event_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamily::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT husb_id, wife_id, event_id FROM Family WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_husb_id  = GET_ID( result.GetInt64( 0 ) );
    f_wife_id  = GET_ID( result.GetInt64( 1 ) );
    f_event_id = GET_ID( result.GetInt64( 2 ) );
    return true;
}

bool recFamily::ReadParents( idt ind )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT fam_id FROM FamilyIndividual WHERE ind_id="ID";", ind
    );
    result = s_db->ExecuteQuery( sql );
    f_id =  GET_ID( result.GetInt64( 0 ) );
    return Read();
}

recIndividualList recFamily::GetChildren( idt fam )
{
    recIndividualList children;
    recIndividual ind;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( fam == 0 ) return children;

    sql.Format(
        "SELECT ind_id FROM FamilyIndividual WHERE fam_id="ID" "
        "ORDER BY sequence ASC;", fam
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        ind.f_id = GET_ID( result.GetInt64( 0 ) );
        ind.Read();
        children.push_back( ind );
    }
    return children;
}

recIdList recFamily::GetChildrenIds( idt fam )
{
    recIdList children;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( fam == 0 ) return children;

    sql.Format(
        "SELECT ind_id FROM FamilyIndividual WHERE fam_id="ID" "
        "ORDER BY sequence ASC;", fam
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        children.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return children;
}

unsigned recFamily::GetChildNextSequence( idt famID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(sequence) FROM FamilyIndividual WHERE fam_id="ID";",
        famID
    );
    return (unsigned) s_db->ExecuteScalar( sql ) + 1;
}

recFamIndVec recFamily::GetChildLinks( idt famID )
{
    recFamIndVec ChildLinks;
    recFamilyIndividual fi;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( famID == 0 ) return ChildLinks;

    sql.Format(
        "SELECT id, ind_id, sequence FROM FamilyIndividual WHERE fam_id="ID" "
        "ORDER BY sequence ASC;", famID
    );
    result = s_db->GetTable( sql );

    fi.f_fam_id = famID;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        fi.f_id = GET_ID( result.GetInt64( 0 ) );
        fi.f_ind_id = GET_ID( result.GetInt64( 1 ) );
        fi.f_sequence = (unsigned) result.GetInt( 2 );
        ChildLinks.push_back( fi );
    }
    return ChildLinks;
}

wxArrayString recFamily::GetMarriageEventTable() const
{
    wxArrayString list;
    if( f_id == 0 ) return list;
    if( f_husb_id == 0 && f_wife_id == 0 ) return list;
    if( f_husb_id == 0 ) {
        return recIndividual::GetEventIdStrList( f_wife_id, recEventTypeRole::ROLE_Marriage_Bride );
    }
    if( f_wife_id == 0 ) {
        return recIndividual::GetEventIdStrList( f_husb_id, recEventTypeRole::ROLE_Marriage_Groom );
    }

    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    sql.Format(
        "SELECT id, title, date1_id, place_id FROM Event "
        "WHERE id=("
        "SELECT event_id FROM EventPersona INNER JOIN "
        "(SELECT per_id AS ipp FROM IndividualPersona WHERE ind_id="ID") Mip "
        "ON per_id=Mip.ipp WHERE role_id=%d "
        "INTERSECT "
        "SELECT event_id FROM EventPersona INNER JOIN "
        "(SELECT per_id AS ipp FROM IndividualPersona WHERE ind_id="ID") Fip "
        "ON per_id=Fip.ipp WHERE role_id=%d"
        ");",
        f_husb_id, recEventTypeRole::ROLE_Marriage_Groom,
        f_wife_id, recEventTypeRole::ROLE_Marriage_Bride
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        list.Add( result.GetAsString( 0 ) );
        list.Add( result.GetAsString( 1 ) );
        list.Add( recDate::GetStr( GET_ID( result.GetInt64( 2 ) ) ) );
        list.Add( recPlace::GetAddressStr( GET_ID( result.GetInt64( 3 ) ) ) );
    }
    return list;
}

//----------------------------------------------------------

recFamilyIndividual::recFamilyIndividual( const recFamilyIndividual& fi )
{
    f_id       = fi.f_id;
    f_ind_id   = fi.f_ind_id;
    f_fam_id   = fi.f_fam_id;
    f_sequence = fi.f_sequence;
}

void recFamilyIndividual::Clear()
{
    f_id       = 0;
    f_ind_id   = 0;
    f_fam_id   = 0;
    f_sequence = 0;
}

void recFamilyIndividual::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO FamilyIndividual (fam_id, ind_id, sequence) "
            "VALUES ("ID", "ID", %u);",
            f_fam_id, f_ind_id, f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO FamilyIndividual (id, fam_id, ind_id, sequence) "
                "VALUES ("ID", "ID", "ID", %u);",
                f_id, f_fam_id, f_ind_id, f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE FamilyIndividual SET fam_id="ID", ind_id="ID", sequence=%u "
                "WHERE id="ID";",
                f_fam_id, f_ind_id, f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamilyIndividual::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ind_id, fam_id, sequence FROM FamilyIndividual "
        "WHERE id="ID";", f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ind_id   = GET_ID( result.GetInt64( 0 ) );
    f_fam_id   = GET_ID( result.GetInt64( 1 ) );
    f_sequence = (unsigned) result.GetInt( 2 );
    return true;
}

bool recFamilyIndividual::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_fam_id == 0 || f_ind_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, sequence FROM FamilyIndividual "
        "WHERE fam_id="ID" AND ind_id="ID";",
        f_fam_id, f_ind_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 ) {
        f_id = 0;
        f_sequence = 0;
        return true;
    }
    result.SetRow( 0 );
    f_id = GET_ID( result.GetInt64( 0 ) );
    f_sequence = (unsigned) result.GetInt( 1 );
    if( result.GetRowCount() != 1 ) return false;
    return true;
}

// End of recIndividual.cpp file
