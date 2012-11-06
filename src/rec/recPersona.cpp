/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Persona, Attribute and AttributeType records.
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


#include <rec/recPersona.h>
#include <rec/recIndividual.h>
#include <rec/recDate.h>

recPersona::recPersona( const recPersona& p )
{
    f_id      = p.f_id;
    f_sex     = p.f_sex;
    f_ref_id  = p.f_ref_id;
    f_note    = p.f_note;
}

void recPersona::Clear()
{
    f_id      = 0;
    f_sex     = SEX_Unstated;
    f_ref_id  = 0;
    f_note    = wxEmptyString;
}

void recPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Persona (sex, ref_id, note) VALUES (%u, "ID", '%q');",
            f_sex, f_ref_id, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Persona (id, sex, ref_id, note) "
                "VALUES ("ID", %u, "ID", '%q');",
                f_id, f_sex, f_ref_id, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Persona SET sex=%u, ref_id="ID", note='%q' WHERE id="ID";",
                f_sex, f_ref_id, UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recPersona::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT sex, ref_id, note FROM Persona WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_sex  = (Sex) result.GetInt( 0 );
    f_ref_id = GET_ID( result.GetInt64( 1 ) );
    f_note = result.GetAsString( 2 );
    return true;
}

Sex recPersona::GetSex( idt id )
{
    recPersona per(id);
    return per.f_sex;
}

idt recPersona::GetDefaultNameID( idt id )
{
    wxString str;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id FROM Name WHERE per_id="ID" ORDER BY sequence;",
        id
    );
    wxSQLite3Table result = s_db->GetTable( sql );
    if( result.GetRowCount() > 0 ) {
        return GET_ID( result.GetInt64( 0 ) );
    }
    return 0;
}

recNameVec recPersona::ReadNames( idt perID )
{
    recNameVec list;
    recName name;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, style_id, sequence FROM Name WHERE per_id="ID" "
        "ORDER BY sequence;",
        perID
    );
    result = s_db->GetTable( sql );

    name.f_per_id = perID;
    list.reserve( result.GetRowCount() );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        name.f_id         = GET_ID( result.GetInt64( 0 ) );
        name.f_style_id   = GET_ID( result.GetInt64( 1 ) );
        name.f_sequence = (unsigned) result.GetInt( 2 );
        list.push_back( name );
    }
    return list;
}

recEventPersonaVec recPersona::ReadEventPersonas( idt perID )
{
    recEventPersonaVec list;
    recEventPersona record;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT EP.id, event_id, role_id, EP.note, per_seq FROM EventPersona EP"
        " INNER JOIN Event E ON E.id=event_id"
        " WHERE per_id="ID" ORDER BY date_pt;", 
        perID
    );
    result = s_db->GetTable( sql );

    list.reserve( result.GetRowCount() );
    record.f_per_id = perID;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        record.f_id       = GET_ID( result.GetInt64( 0 ) );
        record.f_event_id = GET_ID( result.GetInt64( 1 ) );
        record.f_role_id  = GET_ID( result.GetInt64( 2 ) );
        record.f_note     = result.GetAsString( 3 );
        record.f_per_seq  = result.GetInt( 4 );
        list.push_back( record );
    }
    return list;
}

recRelationshipVec recPersona::ReadRelationships( idt perID )
{
    recRelationshipVec list;
    recRelationship rel;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, per1_id, per2_id, descrip FROM "
        "Relationship WHERE per1_id="ID" OR per2_id="ID";",
        perID, perID
    );
    result = s_db->GetTable( sql );

    list.reserve( result.GetRowCount() );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        rel.f_id      = GET_ID( result.GetInt64( 0 ) );
        rel.f_per1_id = GET_ID( result.GetInt64( 1 ) );
        rel.f_per2_id = GET_ID( result.GetInt64( 2 ) );
        rel.f_descrip = result.GetAsString( 3 );
        list.push_back( rel );
    }
    return list;
}

recIdVec recPersona::GetIndividualIDs( idt perID )
{
    recIdVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return vec;
    }

    sql.Format(
        "SELECT id FROM Individual WHERE per_id="ID";",
        perID
    );
    idt indID = ExecuteID( sql );
    if( indID ) {
        // if persona is attached directly to an Individual
        // it wont be linked to any other.
        vec.push_back( indID );
        return vec;
    }

    sql.Format(
        "SELECT I.id FROM Individual I, LinkPersona LP "
        "WHERE LP.ref_per_id="ID" AND I.per_id=LP.ind_per_id "
        "ORDER BY I.id;",
        perID
    );
    result = s_db->GetTable( sql );
    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        vec.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return vec;
}

wxString recPersona::GetIndividualIdStr( idt perID )
{
    recIdVec inds = GetIndividualIDs( perID );
    wxString str;
    for( size_t i = 0 ; i < inds.size() ; i++ ) {
        if( i ) {
            str << ", ";
        }
        str << recIndividual::GetIdStr( inds[i] );
    }
    return str;
}

idt recPersona::FindEvent( idt perID, idt roleID )
{
    if( perID == 0 || roleID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT event_id FROM EventPersona WHERE per_id="ID" AND role_id ="ID";",
        perID, roleID
    );
    return ExecuteID( sql );
}

idt recPersona::FindEvent( idt perID, recEventType::ETYPE_Grp grp )
{
    if( perID == 0 || grp == recEventType::ETYPE_Grp_Unstated ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT EP.event_id FROM EventPersona EP "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM EventTypeRole R "
        "  INNER JOIN "
        "  EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND R.prime=1) "
        "ON rid=EP.role_id WHERE EP.per_id="ID" "
        "ORDER BY EP.per_seq;",
        grp, perID
    );
    return ExecuteID( sql );
}

idt recPersona::FindCommonEvent( idt perID, recEventType::ETYPE_Grp grp, idt secID )
{
    if( grp == recEventType::ETYPE_Grp_Unstated ) {
        return 0;
    }
    idt perID1, perID2;
    if( perID == 0 ) {
        perID1 = secID;
        perID2 = 0;
    } else {
        perID1 = perID;
        perID2 = secID;
    }
    if( perID1 == 0 ) {
        return 0;
    }

    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result1, result2;
    sql.Format(
        "SELECT EP.event_id FROM EventPersona EP "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM EventTypeRole R "
        "  INNER JOIN "
        "  EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND NOT R.prime=0) "
        "ON rid=EP.role_id WHERE EP.per_id="ID" "
        "ORDER BY EP.per_seq;",
        grp, perID1
    );
    result1 = s_db->GetTable( sql );
    if( perID2 == 0 ) {
        if( result1.GetRowCount() ) {
            return GET_ID( result1.GetInt64( 0 ) );
        }
        return 0;
    }
    sql.Format(
        "SELECT EP.event_id FROM EventPersona EP "
        "INNER JOIN "
        "(SELECT R.id AS rid FROM EventTypeRole R "
        "  INNER JOIN "
        "  EventType T ON R.type_id=T.id "
        "  WHERE T.grp=%d AND NOT R.prime=0) "
        "ON rid=EP.role_id WHERE EP.per_id="ID" "
        "ORDER BY EP.per_seq;",
        grp, perID2
    );
    result2 = s_db->GetTable( sql );

    for( int i = 0 ; i < result1.GetRowCount() ; i++ ) {
        result1.SetRow( i );
        for( int j = 0 ; j < result2.GetRowCount() ; j++ ) {
            result2.SetRow( j );
            if( result1.GetInt64( 0 ) == result2.GetInt64( 0 ) ) {
                return GET_ID( result1.GetInt64( 0 ) );
            }
        }
    }
    return 0;
}

idt recPersona::FindAttribute( idt perID, idt atypeID )
{
    if( perID == 0 || atypeID == 0 ) return 0;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id FROM Attribute WHERE per_id="ID" AND type_id ="ID" "
        "ORDER BY sequence;",
        perID, atypeID
    );
    // TODO: Return a list to convert into a comma separated string.
    return ExecuteID( sql );
}

wxString recPersona::GetDateEpitaph( idt perID )
{
    idt bDateID, dDateID;

    bDateID = recEvent::GetDate1ID( GetBirthEvent( perID ) );
    if( bDateID == 0 ) {
        bDateID = recEvent::GetDate1ID( GetNrBirthEvent( perID ) );
    }
    dDateID = recEvent::GetDate1ID( GetDeathEvent( perID ) );
    if( dDateID == 0 ) {
        dDateID = recEvent::GetDate1ID( GetNrDeathEvent( perID ) );
    }
    if( bDateID == 0 && dDateID == 0 ) return wxEmptyString;

    wxString str;
    str << "(";
    if( bDateID ) {
        str << recDate::GetYear( bDateID );
    } else {
        str << " ";
    }
    str << " - ";
    if( dDateID ) {
        str << recDate::GetYear( dDateID );
    } else {
        str << " ";
    }
    str << ")";
    return str;
}

int recPersona::CountNames( idt perID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM Name WHERE per_id="ID";", perID );
    return s_db->ExecuteScalar( sql );
}


// End of recPersona.cpp file
