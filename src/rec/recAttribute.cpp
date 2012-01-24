/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recAttribute.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Attribute and AttributeType records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     19 October 2011
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


#include <rec/recAttribute.h>

recAttribute::recAttribute( const recAttribute& attr )
{
    f_id       = attr.f_id;
    f_per_id   = attr.f_per_id;
    f_type_id  = attr.f_type_id;
    f_val      = attr.f_val;
    f_sequence = attr.f_sequence;
}

void recAttribute::Clear()
{
    f_id       = 0;
    f_per_id   = 0;
    f_type_id  = 0;
    f_val      = wxEmptyString;
    f_sequence = 0;
}

void recAttribute::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Attribute (per_id, type_id, val, sequence)"
            "VALUES ("ID", "ID", '%q', %u);",
            f_per_id, f_type_id, UTF8_(f_val), f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Attribute (id, per_id, type_id, val, sequence)"
                "VALUES ("ID", "ID", "ID", '%q', %u);",
                f_id, f_per_id, f_type_id, UTF8_(f_val), f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Attribute SET per_id="ID", type_id="ID", val='%q', sequence=%u WHERE id="ID";",
                f_per_id, f_type_id, UTF8_(f_val), f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recAttribute::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT per_id, type_id, val, sequence FROM Attribute WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_per_id   = GET_ID( result.GetInt64( 0 ) );
    f_type_id  = GET_ID( result.GetInt64( 1 ) );
    f_val      = result.GetAsString( 2 );
    f_sequence = (unsigned) result.GetInt( 3 );
    return true;
}

wxString recAttribute::GetValue( idt id )
{
    if( id == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT val FROM Attribute WHERE id="ID";", id );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 )
    {
        return wxEmptyString;
    }
    return result.GetAsString( 0 );
}


//----------------------------------------------------------

recAttributeType::recAttributeType( const recAttributeType& at )
{
    f_id   = at.f_id;
    f_grp  = at.f_grp;
    f_name = at.f_name;
}

void recAttributeType::Clear()
{
    f_id   = 0;
    f_grp  = AGRP_Unstated;
    f_name = wxEmptyString;
}

void recAttributeType::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO AttributeType (grp, name) VALUES (%u, '%q');",
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
                "INSERT INTO AttributeType (id, grp, name) "
                "VALUES ("ID", %u, '%q');",
                f_id, f_grp, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE AttributeType SET grp=%u, name='%q' WHERE id="ID";",
                f_grp, UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recAttributeType::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT grp, name FROM AttributeType WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_grp  = (AGrp) result.GetInt( 0 );
    f_name = result.GetAsString( 1 );
    return true;
}

wxString recAttributeType::GetTypeStr( idt id )
{
    recAttributeType at( id );
    return at.f_name;
}

recAttributeTypeVec recAttributeType::GetTypeList()
{
    recAttributeType at;
    recAttributeTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, grp, name FROM AttributeType "
        "WHERE id<0 ORDER BY id DESC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        at.f_id = GET_ID( result.GetInt64( 0 ) );
        at.f_grp = (AGrp) result.GetInt( 1 );
        at.f_name = result.GetAsString( 2 );
        list.push_back( at );
    }

    // Put user entries in list.
    sql.Format(
        "SELECT id, grp, name FROM AttributeType "
        "WHERE id>0 ORDER BY id ASC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        at.f_id = GET_ID( result.GetInt64( 0 ) );
        at.f_grp = (AGrp) result.GetInt( 1 );
        at.f_name = result.GetAsString( 2 );
        list.push_back( at );
    }

    return list;
}

// End of recAttribute.cpp file