/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventType.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventType table.
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

#include <rec/recEventType.h>
#include <rec/recEvent.h>

//============================================================================
//-------------------------[ recEventType ]-----------------------------------
//============================================================================

recEventType::recEventType( const recEventType& et )
{
    f_id   = et.f_id;
    f_grp  = et.f_grp;
    f_name = et.f_name;
}

void recEventType::Clear()
{
    f_id   = 0;
    f_grp  = recEventTypeGrp::unstated;
    f_name = wxEmptyString;
}

void recEventType::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".EventType (grp, name) VALUES (%d, '%q');",
            UTF8_( dbname ), f_grp, UTF8_(f_name)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".EventType (id, grp, name) VALUES (" ID ", %d, '%q');",
                UTF8_( dbname ), f_id, f_grp, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".EventType SET grp=%d, name='%q' WHERE id=" ID ";",
                UTF8_( dbname ), f_grp, UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventType::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( 
        "SELECT grp, name FROM \"%s\".EventType WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_grp = recEventTypeGrp( result.GetInt( 0 ) );
    f_name = result.GetAsString( 1 );
    return true;
}

bool recEventType::Equivalent( const recEventType& r2 ) const
{
    return
        f_grp == r2.f_grp &&
        f_name == r2.f_name
    ;
}

bool recEventType::HasDateSpan() const
{
    switch( f_grp )
    {
    case recEventTypeGrp::other:
    case recEventTypeGrp::personal:
        return true;
    default:
        return false;
    }
}

wxString recEventType::GetName( idt tID, const wxString& dbname )
{
    return ExecuteStr(
        "SELECT name FROM \"%s\".EventType WHERE id=" ID ";",
        UTF8_( dbname ), tID
    );
}

bool recEventType::HasDateSpan( idt etID, const wxString& dbname )
{
    recEventType et( etID, dbname );
    return et.HasDateSpan();
}

wxString recEventType::GetGroupValueStr( recEventTypeGrp grp )
{
    wxASSERT( unsigned(grp) < unsigned(recEventTypeGrp::max) );
    static wxString grparray[size_t(recEventTypeGrp::max)] = {
        _("Unstated"),
        _("Birth"),
        _("Near Birth"),
        _("Family Union"),
        _("Other Family"),
        _("Death"),
        _("Near Death"),
        _("Other"),
        _("Personal"),
        _("Relationship"),
        _("Family Relationship")
    };
    return grparray[size_t(grp)];
}

wxString recEventType::GetGroupStr( idt etID, const wxString& dbname )
{
    recEventType et( etID, dbname );
    return et.GetGroupValueStr( et.FGetGrp() );
}

wxArrayString recEventType::GetGroupStrings( size_t start )
{
    wxArrayString strs;
    for( size_t i = start ; i < size_t(recEventTypeGrp::max) ; i++ ) {
        strs.push_back( GetGroupValueStr( recEventTypeGrp( i ) ) );
    }
    return strs;
}

wxString recEventType::GetTypeStr( idt id, const wxString& dbname )
{
    recEventType et( id, dbname );
    return et.f_name;
}

recEventTypeGrp recEventType::GetGroup( idt id, const wxString& dbname )
{
    recEventType et( id, dbname );
    return et.f_grp;
}

recEventTypeVec recEventType::ReadVec( unsigned filter, const wxString& dbname )
{
    recEventTypeVec vec;
    if( filter == recET_GRP_FILTER_None ) {
        return vec;
    }
    wxString query;
    query << "SELECT id, grp, name FROM " << dbname << ".EventType WHERE ";
    if( filter == recET_GRP_FILTER_All ) {
        query << "NOT grp=0 ";
    } else {
        bool started = false;
        if( filter & recET_GRP_FILTER_Unstated ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=0 ";
        }
        if( filter & recET_GRP_FILTER_Birth ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=1 ";
        }
        if( filter & recET_GRP_FILTER_NrBirth ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=2 ";
        }
        if( filter & recET_GRP_FILTER_FamUnion ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=3 ";
        }
        if( filter & recET_GRP_FILTER_FamOther ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=4 ";
        }
        if( filter & recET_GRP_FILTER_Death ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=5 ";
        }
        if( filter & recET_GRP_FILTER_NrDeath ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=6 ";
        }
        if( filter & recET_GRP_FILTER_Other ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=7 ";
        }
        if( filter & recET_GRP_FILTER_Personal ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=8 ";
        }
        if( filter & recET_GRP_FILTER_Relation ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=9 ";
        }
        if( filter & recET_GRP_FILTER_FamRelation ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=10 ";
        }
    }
    query << "ORDER BY id DESC;";
    wxSQLite3ResultSet result = s_db->ExecuteQuery( query );

    recEventType et;
    while( result.NextRow() ) {
        et.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        et.FSetGrp( recEventTypeGrp( result.GetInt( 1 ) ) );
        et.FSetName( result.GetAsString( 2 ) );
        vec.push_back( et );
    }
    return vec;
}

// Return an vector of roles for this type of event
recEventTypeRoleVec recEventType::GetRoles( idt typeID, const wxString& dbname )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, prime, official, name FROM \"%s\".EventTypeRole"
        " WHERE type_id=" ID " ORDER BY prime DESC, official, name;",
        UTF8_( dbname ), typeID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_type_id = typeID;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_prime = table.GetInt( 1 );
        record.f_official = table.GetBool( 2 );
        record.f_name = table.GetAsString( 3 );
        vec.push_back( record );
    }
    return vec;
}

recEventTypeRoleVec recEventType::GetPrimeRoles(
    idt typeID, int prime, const wxString& dbname )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    wxString filter;
    switch( prime )
    {
    case 0:
        filter = "NOT prime=0";
        break;
    case -1:
        filter = "prime=1 OR prime=3";
        break;
    case -2:
        filter = "prime=2 OR prime=3";
        break;
    default:
        filter = wxString::Format( "prime=%d", prime );
    }
    sql.Format(
        "SELECT id, name FROM \"%s\".EventTypeRole "
        "WHERE type_id=" ID " AND (%q) ORDER BY id DESC;",
        UTF8_( dbname ), typeID, UTF8_(filter)
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_type_id = typeID;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.f_id = GET_ID( table.GetInt64( 0 ) );
        record.f_name = table.GetAsString( 1 );
        vec.push_back( record );
    }
    return vec;
}

idt recEventType::GetSummaryRole( idt typeID )
{
    // TODO: This should be found by adding a boolian "summary" field 
    // to the recEventTypeRole table.
    switch( typeID )
    {
    case ET_Residence:
        return recEventTypeRole::ROLE_Residence_Summary;
    case ET_Condition:
        return recEventTypeRole::ROLE_Condition_Summary;
    case ET_Occupation:
        return recEventTypeRole::ROLE_Occupation_Summary;
    default:
        return recEventTypeRole::ROLE_Unstated;
    }
}

std::string recEventType::CsvTitles()
{
    return std::string( "ID, Group, Name\n" );
}

void recEventType::CsvWrite( std::ostream& out, idt id )
{
    recEventType et( id );
    recCsvWrite( out, et.FGetID() );
    recCsvWrite( out, int( et.FGetGrp() ) );
    recCsvWrite( out, et.FGetName(), '\n' );
}

bool recEventType::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    int group;
    recCsvRead( in, group );
    f_grp = recEventTypeGrp( group );
    recCsvRead( in, f_name );
    return bool( in );
}

// End of src/rec/recEventType.cpp file
