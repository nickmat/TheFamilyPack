/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Persona, Attribute and AttributeType records.
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


#include <rec/recPersona.h>

#include <rec/recIndividual.h>

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
    f_sex     = Sex::unstated;
    f_ref_id  = 0;
    f_note    = wxEmptyString;
}

void recPersona::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Persona (sex, ref_id, note) VALUES (%u, " ID ", '%q');",
            UTF8_( dbname ), f_sex, f_ref_id, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Persona (id, sex, ref_id, note) "
                "VALUES (" ID ", %u, " ID ", '%q');",
                UTF8_( dbname ), f_id, f_sex, f_ref_id, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Persona SET sex=%u, ref_id=" ID ", note='%q' WHERE id=" ID ";",
                UTF8_( dbname ), f_sex, f_ref_id, UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recPersona::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT sex, ref_id, note FROM \"%s\".Persona WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
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

bool recPersona::Equivalent( const recPersona& r2 ) const
{
    return
        f_sex == r2.f_sex &&
        f_ref_id == r2.f_ref_id &&
        f_note == r2.f_note
    ;
}

idt recPersona::Create( idt refID, Sex sex )
{
    recPersona per(0);
    per.f_ref_id = refID;
    per.f_sex = sex;
    per.Save();
    return per.f_id;
}

Sex recPersona::GetSex( idt id, const wxString& dbname )
{
    recPersona per( id, dbname );
    return per.f_sex;
}

idt recPersona::GetRefID( idt id, const wxString& dbname )
{
    return recDb::ExecuteID(
        "SELECT ref_id FROM \"%s\".Persona WHERE id=" ID ";",
        UTF8_( dbname ), id
    );
}

recNameVec recPersona::ReadNames( idt perID, const wxString& dbname )
{
    recNameVec list;
    recName name;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, ind_id, style_id, sequence FROM \"%s\".Name WHERE per_id=" ID " "
        "ORDER BY sequence;",
        UTF8_( dbname ), perID
    );
    result = s_db->GetTable( sql );

    name.FSetPerID( perID );
    list.reserve( result.GetRowCount() );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        name.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        name.FSetIndID( GET_ID( result.GetInt64( 1 ) ) );
        name.FSetTypeID( GET_ID( result.GetInt64( 2 ) ) );
        name.FSetSequence( result.GetInt( 3 ) );
        list.push_back( name );
    }
    return list;
}

recIdVec recPersona::GetNameListID( idt perID, const wxString& dbname )
{
    return ExecuteIdVec(
        "SELECT id FROM \"%s\".Name WHERE per_id=" ID ";",
        UTF8_( dbname ), perID
    );
}

recEventaPersonaVec recPersona::ReadEventaPersonas(
    idt perID, recEventOrder order, const wxString& dbname )
{
    recEventaPersonaVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }
    wxString orderStr;
    switch( order )
    {
    case recEO_DatePt:
        orderStr = "date_pt, EP.per_seq";
        break;
    case recEO_PerSeq:
        orderStr = "EP.per_seq, date_pt";
        break;
    default:
        wxASSERT( false ); // Shouldn't be here
    }

    sql.Format(
        "SELECT EP.id, eventa_id, role_id, EP.note, per_seq FROM \"%s\".EventaPersona EP"
        " INNER JOIN \"%s\".Eventa E ON E.id=eventa_id"
        " WHERE per_id=" ID " ORDER BY %s;",
        UTF8_( dbname ), UTF8_( dbname ), perID, UTF8_(orderStr)
    );
    result = s_db->GetTable( sql );

    list.reserve( result.GetRowCount() );
    recEventaPersona record;
    record.f_per_id = perID;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        record.f_id         = GET_ID( result.GetInt64( 0 ) );
        record.f_eventa_id  = GET_ID( result.GetInt64( 1 ) );
        record.f_role_id    = GET_ID( result.GetInt64( 2 ) );
        record.f_note       = result.GetAsString( 3 );
        record.f_per_seq    = result.GetInt( 4 );
        list.push_back( record );
    }
    return list;
}

int recPersona::GetMaxEventaSeqNumber( idt perID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(per_seq) FROM EventaPersona WHERE per_id=" ID ";",
        perID
    );
    return s_db->ExecuteScalar( sql );
}

recIdVec recPersona::GetIndividualIDs( idt perID, const wxString& dbname )
{
    recIdVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return vec;
    }

    sql.Format(
        "SELECT ind_id FROM \"%s\".IndividualPersona WHERE per_id=" ID " ORDER BY id;",
        UTF8_( dbname ), perID
    );
    result = s_db->GetTable( sql );
    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        vec.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return vec;
}

wxString recPersona::GetIndividualIdStr( idt perID, const wxString& dbname )
{
    recIdVec inds = GetIndividualIDs( perID, dbname );
    wxString str;
    for( size_t i = 0 ; i < inds.size() ; i++ ) {
        if( i ) {
            str << ", ";
        }
        str << recIndividual::GetIdStr( inds[i] );
    }
    return str;
}

recIdVec recPersona::FindIndividualReferenceLink(
    idt indID, idt refID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT P.id FROM"
        " \"%s\".Persona P, \"%s\".IndividualPersona IP WHERE"
        " IP.ind_id=" ID " AND IP.per_id=P.id AND P.ref_id=" ID ";",
        UTF8_( dbname ), UTF8_( dbname ), indID, refID
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recIdVec vec;
    while( result.NextRow() ) {
        vec.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return vec;
}

idt recPersona::Transfer( idt from_perID, const wxString& fromdb, idt to_refID, const wxString& todb )
{
    if( from_perID == 0 ) return 0;

    recPersona from_per( from_perID, fromdb );
    recPersona to_per( from_per );
    if( to_per.FGetID() > 0 ) {
        to_per.FSetID( 0 );
    }
    to_per.FSetRefID( to_refID );
    to_per.Save( todb );
    idt to_perID = to_per.FGetID();

    recIdVec namIDs = from_per.GetNameListID( fromdb );
    for( idt namID : namIDs ) {
        recName::Transfer( namID, fromdb, 0, to_perID, todb );
    }
    // TODO: IndividualPersona and EventaPersona records should be included.
    return to_perID;
}

std::string recPersona::CsvTitles()
{
    return std::string( "ID, Sex, Reference ID, Note\n" );
}

void recPersona::CsvWrite( std::ostream& out, idt id )
{
    recPersona pa( id );
    recCsvWrite( out, pa.FGetID() );
    recCsvWrite( out, int( pa.FGetSex() ) );
    recCsvWrite( out, pa.FGetRefID() );
    recCsvWrite( out, pa.FGetNote(), '\n' );
}

bool recPersona::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    int sex;
    recCsvRead( in, sex );
    f_sex = Sex( sex );
    recCsvRead( in, f_ref_id );
    recCsvRead( in, f_note );
    return bool( in );
}

bool recPersona::RemoveFromDatabase( const wxString& dbname )
{
    if( f_id <= 0 ) {
        return false;
    }

    recNameVec names = ReadNames( dbname );
    for( size_t i = 0 ; i < names.size() ; i++ ) {
        names[i].RemoveFromDatabase( dbname );
    }
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "DELETE FROM \"%s\".EventaPersona WHERE per_id=" ID ";",
        UTF8_( dbname ), f_id
    );
    s_db->ExecuteUpdate( sql );

    Delete();
    // TODO: Delete orphaned EventType and/or EventTypeRole
    Clear();
    return true;
}

bool recPersona::RemoveFromDatabase( idt id, const wxString& dbname )
{
    if( id <= 0 ) {
        return false;
    }
    recPersona per(id);
    return per.RemoveFromDatabase();
}

// End of recPersona.cpp file
