/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventTypeRole.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventTypeRole records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015, Nick Matthews.
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
}

void recEventTypeRole::Clear()
{
    f_id       = 0;
    f_type_id  = 0;
    f_prime    = false;
    f_official = false;
    f_name     = wxEmptyString;
}

void recEventTypeRole::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventTypeRole (type_id, prime, official, name) "
            "VALUES ("ID", %d, %d, '%q');",
            f_type_id, f_prime, BOOL_(f_official), UTF8_(f_name)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventTypeRole (id, type_id, prime, official, name) "
                "VALUES ("ID", "ID", %d, %d, '%q');",
                f_id, f_type_id, f_prime, BOOL_(f_official), UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventTypeRole "
                "SET type_id="ID", prime=%d, official=%d, name='%q' "
                "WHERE id="ID";",
                f_type_id, f_prime, BOOL_(f_official), UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventTypeRole::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT type_id, prime, official, name "
        "FROM EventTypeRole WHERE id="ID";",
        f_id
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
    return true;
}

wxString recEventTypeRole::GetName( idt roleID )
{
    recEventTypeRole role( roleID );
    return role.f_name;
}

wxString recEventTypeRole::GetPrimeStr() const
{
    wxString str;
    recET_GRP group = recEventType::GetGroup( f_type_id );

    switch( group )
    {
    case recET_GRP_Birth:
    case recET_GRP_NrBirth:
    case recET_GRP_Death:
    case recET_GRP_NrDeath:
    case recET_GRP_Other:
    case recET_GRP_Personal:
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
    case recET_GRP_FamUnion:
    case recET_GRP_FamOther:
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
        "WHERE type_id="ID"%s%s AND name LIKE '%q';",
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
        "WHERE type_id="ID" AND prime=%d AND official=%d AND name LIKE '%q';",
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
        role.Save();
        return role.f_id;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );
}

// End of recEventTypeRole.cpp file
