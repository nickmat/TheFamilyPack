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
    f_uid = et.f_uid;
    f_changed = et.f_changed;
}

void recEventType::Clear()
{
    f_id   = 0;
    f_grp  = recEventTypeGrp::unstated;
    f_name.clear();
    f_uid.clear();
    f_changed = 0;
}

void recEventType::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".EventType (grp, name, uid, changed)"
            " VALUES (%d, '%q', '%q', %ld);",
            UTF8_( dbname ), f_grp, UTF8_(f_name), UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".EventType (id, grp, name, uid, changed)"
                " VALUES (" ID ", %d, '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, f_grp, UTF8_(f_name), UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".EventType SET grp=%d, name='%q', uid = '%q', changed = %ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_grp, UTF8_(f_name), UTF8_( f_uid ), f_changed, f_id
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
        "SELECT grp, name, uid, changed FROM \"%s\".EventType WHERE id=" ID ";",
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
    f_uid = result.GetAsString( 2 );
    f_changed = result.GetInt( 3 );
    return true;
}

bool recEventType::Equivalent( const recEventType& r2 ) const
{
    return
        f_grp == r2.f_grp &&
        f_name == r2.f_name &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
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
    static const char* grparray[] = {
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
    const size_t size = sizeof( grparray ) / sizeof( const char* );
    wxASSERT( size == static_cast<size_t>(recEventTypeGrp::max) );

    size_t index = static_cast<size_t>(grp);
    if( index >= size ) {
        index = 0;
    }
    return grparray[index];
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
    query << "SELECT id, grp, name, uid, changed FROM " << dbname << ".EventType WHERE ";
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
        et.FSetUid( result.GetAsString( 3 ) );
        et.FSetChanged( result.GetInt( 4 ) );
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
        "SELECT id, prime, official, name, uid, changed"
        " FROM \"%s\".EventTypeRole WHERE type_id=" ID
        " ORDER BY prime DESC, official, name;",
        UTF8_( dbname ), typeID
    );
    wxSQLite3Table table = s_db->GetTable( sql );

    record.f_type_id = typeID;
    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        record.FSetID( GET_ID( table.GetInt64( 0 ) ) );
        record.FSetPrime( table.GetInt( 1 ) );
        record.FSetOfficial( table.GetBool( 2 ) );
        record.FSetName( table.GetAsString( 3 ) );
        record.FSetUid( table.GetAsString( 4 ) );
        record.FSetChanged( table.GetInt( 5 ) );
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
    return std::string( "ID, Group, Name, UID, Last Changed\n" );
}

void recEventType::CsvWrite( std::ostream& out, idt id )
{
    recEventType et( id );
    recCsvWrite( out, et.FGetID() );
    recCsvWrite( out, static_cast<int>( et.FGetGrp() ) );
    recCsvWrite( out, et.FGetName() );
    recCsvWrite( out, et.FGetUid() );
    recCsvWrite( out, et.FGetChanged(), '\n' );
}

bool recEventType::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    int group;
    recCsvRead( in, group );
    f_grp = static_cast<recEventTypeGrp>( group );
    recCsvRead( in, f_name );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

// End of src/rec/recEventType.cpp file
