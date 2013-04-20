/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventType.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventType table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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
    f_grp  = ETYPE_Grp_Unstated;
    f_name = wxEmptyString;
}

void recEventType::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventType (grp, name) VALUES (%d, '%q');",
            f_grp, UTF8_(f_name)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventType (id, grp, name) VALUES ("ID", %d, '%q');",
                f_id, f_grp, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventType SET grp=%d, name='%q' WHERE id="ID";",
                f_grp, UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventType::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT grp, name FROM EventType WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_grp = (ETYPE_Grp) result.GetInt( 0 );
    f_name = result.GetAsString( 1 );
    return true;
}

bool recEventType::HasDateSpan() const
{
    switch( f_grp )
    {
    case ETYPE_Grp_Other:
    case ETYPE_Grp_Personal:
        return true;
    default:
        return false;
    }
}

bool recEventType::HasDateSpan( idt etID )
{
    recEventType et(etID);
    return et.HasDateSpan();
}

wxString recEventType::GetGroupStr( ETYPE_Grp grp )
{
    wxASSERT( grp >= 0 && grp < ETYPE_Grp_MAX );
    static wxString grparray[ETYPE_Grp_MAX] = {
        _("Unstated"),
        _("Birth"),
        _("Near Birth"),
        _("Family Union"),
        _("Other Family"),
        _("Death"),
        _("Near Death"),
        _("Other"),
        _("Personal")
    };
    return grparray[grp];
}

wxString recEventType::GetGroupStr( idt etID )
{
    recEventType et(etID);
    return et.GetGroupStr();
}

wxArrayString recEventType::GetGroupStrings( size_t start )
{
    wxArrayString strs;
    for( size_t i = start ; i < ETYPE_Grp_MAX ; i++ ) {
        strs.push_back( GetGroupStr( (ETYPE_Grp) i ) );
    }
    return strs;
}

wxString recEventType::GetTypeStr( idt id )
{
    recEventType et( id );
    return et.f_name;
}

recEventType::ETYPE_Grp recEventType::GetGroup( idt id )
{
    recEventType et( id );
    return et.f_grp;
}

recEventTypeVec recEventType::ReadVec( unsigned filter )
{
    recEventTypeVec vec;
    if( filter == recET_FILTER_GrpNone ) {
        return vec;
    }
    wxString query = "SELECT id, grp, name FROM EventType WHERE ";
    if( filter == recET_FILTER_GrpAll ) {
        query << "NOT grp=0 ";
    } else {
        bool started = false;
        if( filter & recET_FILTER_GrpUnstated ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=0 ";
        }
        if( filter & recET_FILTER_GrpBirth ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=1 ";
        }
        if( filter & recET_FILTER_GrpNrBirth ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=2 ";
        }
        if( filter & recET_FILTER_GrpFamUnion ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=3 ";
        }
        if( filter & recET_FILTER_GrpFamOther ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=4 ";
        }
        if( filter & recET_FILTER_GrpDeath ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=5 ";
        }
        if( filter & recET_FILTER_GrpNrDeath ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=6 ";
        }
        if( filter & recET_FILTER_GrpOther ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=7 ";
        }
        if( filter & recET_FILTER_GrpPersonal ) {
            if( started ) query << "OR "; else started = true;
            query << "grp=8 ";
        }
    }
    query << "ORDER BY id DESC;";
    wxSQLite3ResultSet result = s_db->ExecuteQuery( query );

    recEventType et;
    while( result.NextRow() ) {
        et.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        et.FSetGrp( (ETYPE_Grp) result.GetInt( 1 ) );
        et.FSetName( result.GetAsString( 2 ) );
        vec.push_back( et );
    }
    return vec;
}

// Return an vector of roles for this type of event
recEventTypeRoleVec recEventType::GetRoles( idt typeID )
{
    recEventTypeRole record;
    recEventTypeRoleVec vec;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, prime, official, name FROM EventTypeRole"
        " WHERE type_id="ID" ORDER BY id DESC;",
        typeID
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

recEventTypeRoleVec recEventType::GetPrimeRoles( idt typeID, int prime )
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
        "SELECT id, name FROM EventTypeRole "
        "WHERE type_id="ID" AND (%q) ORDER BY id DESC;",
        typeID, UTF8_(filter)
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

// End of src/rec/recEventType.cpp file
