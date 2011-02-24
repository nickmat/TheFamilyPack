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

recPersona::recPersona( const recPersona& p )
{
    f_id      = p.f_id;
    f_name_id = p.f_name_id;
    f_sex     = p.f_sex;
    f_note    = p.f_note;
}

void recPersona::Clear()
{
    f_id      = 0;
    f_name_id = 0;
    f_sex     = SEX_Unstated;
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
            "INSERT INTO Persona (name_id, sex, note) VALUES ("ID", %u, '%q');",
            f_name_id, f_sex, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Persona (id, name_id, sex, note) "
                "VALUES ("ID", "ID", %u, '%q');",
                f_id, f_name_id, f_sex, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Persona SET name_id="ID", sex=%u, note='%q' WHERE id="ID";",
                f_name_id, f_sex, UTF8_(f_note), f_id
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

    sql.Format( "SELECT name_id, sex, note FROM Persona WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name_id = GET_ID( result.GetInt64( 0 ) );
    f_sex  = (Sex) result.GetInt( 1 );
    f_note = result.GetAsString( 2 );
    return true;
}

wxString recPersona::GetSurname( id_t id )
{
    wxString str;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT val FROM NamePart "
        "WHERE name_id=(SELECT name_id FROM Persona WHERE id="ID") AND type_id=-2 "
        "ORDER BY sequence;",
        id
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() > 0 )
    {
        for( int row = 0 ; row < result.GetRowCount() ; row++ )
        {
            if( row > 0 )
            {
                str << " ";
            }
            result.SetRow( row );
            str << result.GetAsString( 0 );
        }
    }
    return str;
}

wxString recPersona::GetGivenName( id_t id )
{
    wxString str;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT val FROM NamePart "
        "WHERE name_id=(SELECT name_id FROM Persona WHERE id="ID") "
        "AND (type_id=-1 OR type_id=-3) "
        "ORDER BY sequence;", id
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() > 0 )
    {
        for( int row = 0 ; row < result.GetRowCount() ; row++ )
        {
            if( row > 0 )
            {
                str << " ";
            }
            result.SetRow( row );
            str << result.GetAsString( 0 );
        }
    }
    return str;
}

recAttributeList recPersona::ReadAttributes( id_t perID )
{
    recAttributeList list;
    recAttribute record;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, type_id, val FROM Attribute "
        "WHERE per_id="ID";", perID
    );
    result = s_db->GetTable( sql );

    list.reserve( result.GetRowCount() );
    record.f_per_id = perID;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        record.f_id = GET_ID( result.GetInt64( 0 ) );
        record.f_type_id = GET_ID( result.GetInt64( 1 ) );
        record.f_val = result.GetAsString( 2 );
        list.push_back( record );
    }
    return list;
}


recNameVec recPersona::ReadNames( id_t perID )
{
    recNameVec list;
    recName name;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, style_id FROM Name WHERE per_id="ID" "
        "ORDER BY style_id;",
        perID
    );
    result = s_db->GetTable( sql );

    name.f_per_id = perID;
    list.reserve( result.GetRowCount() );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        name.f_id = GET_ID( result.GetInt64( 0 ) );
        name.f_style_id = GET_ID( result.GetInt64( 1 ) );
        list.push_back( name );
    }
    return list;
}

recIdVec recPersona::GetIndividualIDs( id_t perID )
{
    recIdVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( perID == 0 ) {
        return vec;
    }

    sql.Format(
        "SELECT ind_id FROM IndividualPersona WHERE per_id="ID" ORDER BY ind_id;",
        perID
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        vec.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return vec;
}


//----------------------------------------------------------

recAttribute::recAttribute( const recAttribute& attr )
{
    f_id       = attr.f_id;
    f_per_id   = attr.f_per_id;
    f_type_id  = attr.f_type_id;
    f_val      = attr.f_val;
}

void recAttribute::Clear()
{
    f_id       = 0;
    f_per_id   = 0;
    f_type_id  = 0;
    f_val      = wxEmptyString;
}

void recAttribute::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Attribute (per_id, type_id, val)"
            "VALUES ("ID", "ID", '%q');",
            f_per_id, f_type_id, UTF8_(f_val)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Attribute (id, per_id, type_id, val)"
                "VALUES ("ID", "ID", "ID", '%q');",
                f_id, f_per_id, f_type_id, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Attribute SET per_id="ID", type_id="ID", val='%q' WHERE id="ID";",
                f_per_id, f_type_id, UTF8_(f_val), f_id
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

    sql.Format( "SELECT * FROM Attribute WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_per_id   = GET_ID( result.GetInt64( 1 ) );
    f_type_id  = GET_ID( result.GetInt64( 2 ) );
    f_val      = result.GetAsString( 3 );
    return true;
}

wxString recAttribute::GetValue( id_t id )
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
    f_grp  = ATYPE_Grp_Unstated;
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
    f_grp  = (ATYPE_Grp) result.GetInt( 0 );
    f_name = result.GetAsString( 1 );
    return true;
}

wxString recAttributeType::GetTypeStr( id_t id )
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
        at.f_grp = (ATYPE_Grp) result.GetInt( 1 );
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
        at.f_grp = (ATYPE_Grp) result.GetInt( 1 );
        at.f_name = result.GetAsString( 2 );
        list.push_back( at );
    }

    return list;
}

// End of recPersona.cpp file
