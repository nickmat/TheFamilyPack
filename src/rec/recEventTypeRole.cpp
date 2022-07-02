/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventTypeRole.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventTypeRole records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015..2022, Nick Matthews.
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

#include <rec/recEventTypeRole.h>

#include <rec/recEvent.h>


//============================================================================
//-------------------------[ recEventTypeRole ]-------------------------------
//============================================================================

recEventTypeRole::recEventTypeRole( const recEventTypeRole& etr )
{
    f_id       = etr.f_id;
    f_type_id  = etr.f_type_id;
    f_prime    = etr.f_prime;
    f_official = etr.f_official;
    f_name     = etr.f_name;
    f_uid = etr.f_uid;
    f_changed = etr.f_changed;
}

void recEventTypeRole::Clear()
{
    f_id       = 0;
    f_type_id  = 0;
    f_prime    = PRIME_None;
    f_official = false;
    f_name.clear();
    f_uid.clear();
    f_changed = 0;
}

void recEventTypeRole::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".EventTypeRole (type_id, prime, official, name, uid, changed) "
            "VALUES (" ID ", %d, %d, '%q', '%q', %ld);",
            UTF8_( dbname ), f_type_id, f_prime, BOOL_(f_official),
            UTF8_(f_name), UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".EventTypeRole (id, type_id, prime, official, name, uid, changed) "
                "VALUES (" ID ", " ID ", %d, %d, '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, f_type_id, f_prime, BOOL_(f_official),
                UTF8_(f_name), UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".EventTypeRole "
                "SET type_id=" ID ", prime=%d, official=%d, name='%q', uid = '%q', changed = %ld "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_type_id, f_prime, BOOL_(f_official),
                UTF8_(f_name), UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventTypeRole::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT type_id, prime, official, name, uid, changed "
        "FROM \"%s\".EventTypeRole WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_type_id = GET_ID( result.GetInt64( 0 ) );
    f_prime = result.GetInt( 1 );
    f_official = result.GetBool( 2 );
    f_name = result.GetAsString( 3 );
    f_uid = result.GetAsString( 4 );
    f_changed = result.GetInt( 5 );
    return true;
}

bool recEventTypeRole::Equivalent( const recEventTypeRole& r2 ) const
{
    return
        f_type_id == r2.f_type_id &&
        f_prime == r2.f_prime &&
        f_official == r2.f_official &&
        f_name == r2.f_name &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

wxString recEventTypeRole::GetName( idt roleID, const wxString& dbname )
{
    recEventTypeRole role( roleID, dbname );
    return role.f_name;
}

wxString recEventTypeRole::GetPrimeStr() const
{
    wxString str;
    recEventTypeGrp group = recEventType::GetGroup( f_type_id );

    switch( group )
    {
    case recEventTypeGrp::birth:
    case recEventTypeGrp::nr_birth:
    case recEventTypeGrp::death:
    case recEventTypeGrp::nr_death:
    case recEventTypeGrp::other:
    case recEventTypeGrp::personal:
        switch( f_prime )
        {
        case PRIME_None:
            str = _("No");
            break;
        case PRIME_First:
            str = _("Yes");
            break;
        default:
            str = _("?");
        }
        break;
    case recEventTypeGrp::fam_union:
    case recEventTypeGrp::fam_other:
        switch( f_prime )
        {
        case PRIME_None:
            str = _("No");
            break;
        case PRIME_First:
            str = _("Male");
            break;
        case PRIME_Second:
            str = _("Female");
            break;
        case PRIME_Any:
            str = _("Neutral");
            break;
        default:
            str = _("?");
        }
        break;
    }
    return str;
}

wxString recEventTypeRole::GetTypeAndRoleStr( idt roleID )
{
    recEventTypeRole role( roleID );
    return recEventType::GetTypeStr( role.f_type_id ) + " - " + role.f_name;
}

idt recEventTypeRole::Select( idt typeID, SelectFilter sf )
{
    recEventTypeRoleVec vec;
    switch(sf )
    {
    case SF_All:
        vec = recEventType::GetRoles( typeID );
        break;
    case SF_Prime:
        vec = recEventType::GetPrimeRoles( typeID );
        break;
    case SF_Prime1:
        vec = recEventType::GetPrimeRoles( typeID, -1 );
        break;
    case SF_Prime2:
        vec = recEventType::GetPrimeRoles( typeID, -2 );
        break;
    default:
        return 0;
    }
    if( vec.size() == 0 ) return 0;
    if( vec.size() == 1 ) return vec[0].f_id;

    wxArrayString list;
    for( size_t i = 0 ; i < vec.size() ; i++ )
    {
        list.Add( vec[i].f_name );
    }

    int index = recGetSingleChoiceIndex( _("Select Event Role"), list );
    if( index < 0 ) return 0;
    return vec[index].f_id;
}

idt recEventTypeRole::Find( const wxString& name, idt type, Prime prime, TriLogic official )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    wxString primeCondition;
    if( prime != PRIME_Ignore ) {
        primeCondition << " AND prime=" << prime;
    }
    wxString officialCondition;
    if( official != TRILOGIC_both ) {
        officialCondition << " AND official=" << official;
    }
    sql.Format(
        "SELECT id FROM EventTypeRole "
        "WHERE type_id=" ID "%s%s AND name LIKE '%q';",
        type, UTF8_(primeCondition), UTF8_(officialCondition), UTF8_(name)
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 ) {
        return 0;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );
}

idt recEventTypeRole::FindOrCreate( const wxString& name, idt type, Prime prime, bool official )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    sql.Format(
        "SELECT id FROM EventTypeRole "
        "WHERE type_id=" ID " AND prime=%d AND official=%d AND name LIKE '%q';",
        type, prime, official, UTF8_(name)
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 )
    {
        // Create
        recEventTypeRole role;
        role.f_id = 0;
        role.f_type_id = type;
        role.f_prime = prime;
        role.f_official = official;
        role.f_name = name;
        role.f_uid = recCreateUid();
        role.f_changed = calGetTodayJdn();
        role.Save();
        return role.f_id;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );
}

idt recEventTypeRole::Transfer( idt from_roleID, const wxString& fromdb, const wxString& todb )
{
    if( from_roleID == 0 ) return 0;

    recEventTypeRole from_role( from_roleID, fromdb );
    idt to_roleID = recEventTypeRole::FindUid( from_role.FGetUid(), todb );

    recEventTypeRole to_role( to_roleID, todb );
    recMatchUID match = from_role.CompareUID( to_role );
    if( match == recMatchUID::unequal || match == recMatchUID::younger ) {
        recEventTypeRole new_role( from_role );
        new_role.FSetID( to_roleID );
        new_role.Save( todb );
        to_roleID = new_role.FGetID();
    }
    return to_roleID;
}

std::string recEventTypeRole::CsvTitles()
{
    return std::string(
        "ID, Event Type ID, Prime, Official, Name, UID, Last Changed\n"
    );
}

void recEventTypeRole::CsvWrite( std::ostream& out, idt id )
{
    recEventTypeRole etr( id );
    recCsvWrite( out, etr.FGetID() );
    recCsvWrite( out, etr.FGetTypeID() );
    recCsvWrite( out, etr.FGetID() );
    recCsvWrite( out, int( etr.FGetOfficial() ) );
    recCsvWrite( out, etr.FGetName());
    recCsvWrite( out, etr.FGetUid() );
    recCsvWrite( out, etr.FGetChanged(), '\n' );
}

bool recEventTypeRole::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_type_id );
    recCsvRead( in, f_prime );
    int official;
    recCsvRead( in, official );
    f_official = official;
    recCsvRead( in, f_name );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

bool recEventTypeRole::DeleteIfOrphaned( idt roleID, const wxString& dbname )
{
    if( roleID <= 0 ) return false;

    int cnt = ExecuteInt( "SELECT COUNT(*) FROM \"%s\".EventaPersona WHERE role_id=" ID ";", dbname, roleID );
    if( cnt > 0 ) return false;
    cnt = ExecuteInt( "SELECT COUNT(*) FROM \"%s\".IndividualEvent WHERE role_id=" ID ";", dbname, roleID );
    if( cnt > 0 ) return false;

    recEventTypeRole role( roleID, dbname );
    bool ret = role.Delete( dbname );
    recEventType::DeleteIfOrphaned( role.FGetTypeID(), dbname );
    return ret;
}

// End of recEventTypeRole.cpp file
