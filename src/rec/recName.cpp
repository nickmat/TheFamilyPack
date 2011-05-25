/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Name, NamePart, NamePartType and NameStyle records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22 November 2010
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

#include <wx/tokenzr.h>

#include <rec/recName.h>

recName::recName( const recName& n )
{
    f_id       = n.f_id;
    f_per_id   = n.f_per_id;
    f_style_id = n.f_style_id;
}

void recName::Clear()
{
    f_id       = 0;
    f_per_id   = 0;
    f_style_id = 0;
}

void recName::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Name (per_id, style_id)"
            "VALUES ("ID", "ID");",
            f_per_id, f_style_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Name (id, per_id, style_id)"
                "VALUES ("ID", "ID", "ID");",
                f_id, f_per_id, f_style_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Name SET per_id="ID", style_id="ID" WHERE id="ID";",
                f_per_id, f_style_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recName::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT per_id, style_id "
        "FROM Name WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_per_id   = GET_ID( result.GetInt64( 0 ) );
    f_style_id = GET_ID( result.GetInt64( 1 ) );
    return true;
}

void recName::AddNameParts( const wxString& nameStr ) const
{
    recNamePart part(0);
    part.f_name_id = f_id;

    wxStringTokenizer tk( nameStr );
    while( tk.HasMoreTokens() ) {
        part.f_id = 0;
        part.f_val = tk.GetNextToken();
        part.f_type_id = tk.HasMoreTokens() ? NAME_TYPE_Given_name : NAME_TYPE_Surname;
        ++part.f_sequence;
        part.Save();
    }
}

bool recName::DeleteAll()
{
    if( f_id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "DELETE FROM NamePart WHERE name_id="ID";", f_id );
    s_db->ExecuteUpdate( sql );

    return Delete();
}

bool recName::FindPersona( idt perID, idt styleID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    sql.Format(
        "SELECT id FROM Name WHERE per_id="ID" AND style_id="ID";",
        perID, styleID
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_per_id = perID;
    f_style_id = styleID;
    return true;
}

wxString recName::GetNamePart( idt nptID )
{
    if( f_id == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT val FROM NamePart "
        "WHERE name_id="ID" AND type_id="ID" "
        "ORDER BY sequence;",
        f_id, nptID
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    wxString str;
    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        if( i > 0 ) {
            str << " ";
        }
        str << result.GetAsString( 0 );
    }
    return str;
}

wxString recName::GetSurname( idt id )
{
    wxString str;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT val FROM NamePart WHERE name_id="ID" AND type_id=-2 "
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

wxString recName::GetGivenName( idt id )
{
    wxString str;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT val FROM NamePart WHERE name_id="ID" AND (type_id=-1 OR type_id=-3) "
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

recNamePartVec recName::GetParts( idt nameID )
{
    recNamePartVec list;
    recNamePart part;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( nameID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, type_id, val, sequence FROM NamePart "
        "WHERE name_id="ID" ORDER BY sequence;",
        nameID
    );
    result = s_db->GetTable( sql );

    part.f_name_id = nameID;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        part.f_id = GET_ID( result.GetInt64( 0 ) );
        part.f_type_id = GET_ID( result.GetInt64( 1 ) );
        part.f_val      = result.GetAsString( 2 );
        part.f_sequence = (unsigned) result.GetInt( 3 );
        list.push_back( part );
    }
    return list;
}

#if 0
wxString recName::GetValue( idt id )
{
    if( id == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT val FROM Name WHERE id="ID";", id );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 )
    {
        return wxEmptyString;
    }
    return result.GetAsString( 0 );
}

/*! Takes a space delimited list from str and converts it to a list of
 *  of Attributes in sequencial order of given type.
 */
recNameList recName::ConvertStrToList(
    const wxString& str, idt type )
{
    recNameList list;
    recName name;
    name.Clear();
    name.f_type_id = type;

    wxStringTokenizer tk( str );
    while( tk.HasMoreTokens() ) {
        name.f_val = tk.GetNextToken();
        ++name.f_sequence;
        list.push_back( name );
    }
    return list;
}
#endif


//----------------------------------------------------------

recNamePart::recNamePart( const recNamePart& n )
{
    f_id       = n.f_id;
    f_name_id  = n.f_name_id;
    f_type_id  = n.f_type_id;
    f_val      = n.f_val;
    f_sequence = n.f_sequence;
}

void recNamePart::Clear()
{
    f_id       = 0;
    f_name_id  = 0;
    f_type_id  = 0;
    f_val      = wxEmptyString;
    f_sequence = 0;
}

void recNamePart::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO NamePart (name_id, type_id, val, sequence)"
            "VALUES ("ID", "ID", '%q', %u);",
            f_name_id, f_type_id, UTF8_(f_val), f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO NamePart (id, name_id, type_id, val, sequence)"
                "VALUES ("ID", "ID", "ID", '%q', %u);",
                f_id, f_name_id, f_type_id, UTF8_(f_val), f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE NamePart SET name_id="ID", type_id="ID", val='%q', sequence=%u "
                "WHERE id="ID";",
                f_name_id, f_type_id, UTF8_(f_val), f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recNamePart::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name_id, type_id, val, sequence "
        "FROM NamePart WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name_id  = GET_ID( result.GetInt64( 0 ) );
    f_type_id  = GET_ID( result.GetInt64( 1 ) );
    f_val      = result.GetAsString( 2 );
    f_sequence = (unsigned) result.GetInt( 3 );
    return true;
}

wxString recNamePart::GetValue( idt id )
{
    if( id == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT val FROM NamePart WHERE id="ID";", id );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 )
    {
        return wxEmptyString;
    }
    return result.GetAsString( 0 );
}

/*! Takes a space delimited list from str and converts it to a list of
 *  of Attributes in sequencial order of given type.
 */
recNamePartVec recNamePart::ConvertStrToList(
    const wxString& str, idt type )
{
    recNamePartVec list;
    recNamePart name(0);
    name.f_type_id = type;

    wxStringTokenizer tk( str );
    while( tk.HasMoreTokens() ) {
        name.f_val = tk.GetNextToken();
        ++name.f_sequence;
        list.push_back( name );
    }
    return list;
}

//----------------------------------------------------------

recNamePartType::recNamePartType( const recNamePartType& at )
{
    f_id   = at.f_id;
    f_grp  = at.f_grp;
    f_name = at.f_name;
}

void recNamePartType::Clear()
{
    f_id   = 0;
    f_grp  = NTYPE_Grp_Unstated;
    f_name = wxEmptyString;
}

void recNamePartType::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO NamePartType (grp, name) VALUES (%u, '%q');",
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
                "INSERT INTO NamePartType (id, grp, name) "
                "VALUES ("ID", %u, '%q');",
                f_id, f_grp, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE NamePartType SET grp=%u, name='%q' WHERE id="ID";",
                f_grp, UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recNamePartType::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT grp, name FROM NamePartType WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_grp  = (NTYPE_Grp) result.GetInt( 0 );
    f_name = result.GetAsString( 1 );
    return true;
}

wxString recNamePartType::GetTypeStr( idt id )
{
    recNamePartType at( id );
    return at.f_name;
}

recNamePartTypeVec recNamePartType::GetTypeList()
{
    recNamePartType at;
    recNamePartTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, grp, name FROM NamePartType "
        "WHERE id<0 ORDER BY id DESC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        at.f_id = GET_ID( result.GetInt64( 0 ) );
        at.f_grp = (NTYPE_Grp) result.GetInt( 1 );
        at.f_name = result.GetAsString( 2 );
        list.push_back( at );
    }

    // Put user entries in list.
    sql.Format(
        "SELECT id, grp, name FROM NamePartType "
        "WHERE id>0 ORDER BY id ASC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        at.f_id = GET_ID( result.GetInt64( 0 ) );
        at.f_grp = (NTYPE_Grp) result.GetInt( 1 );
        at.f_name = result.GetAsString( 2 );
        list.push_back( at );
    }

    return list;
}

//----------------------------------------------------------

recNameStyle::recNameStyle( const recNameStyle& at )
{
    f_id   = at.f_id;
    f_name = at.f_name;
}

void recNameStyle::Clear()
{
    f_id   = 0;
    f_name = wxEmptyString;
}

void recNameStyle::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO NameStyle (name) VALUES ('%q');",
            UTF8_(f_name)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO NameStyle (id, name) "
                "VALUES ("ID", '%q');",
                f_id, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE NameStyle SET name='%q' WHERE id="ID";",
                UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recNameStyle::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT name FROM NameStyle WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name = result.GetAsString( 0 );
    return true;
}

wxString recNameStyle::GetStyleStr( idt id )
{
    recNameStyle at( id );
    return at.f_name;
}

recNameStyleVec recNameStyle::GetStyleList()
{
    recNameStyle at;
    recNameStyleVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, name FROM NameStyle "
        "WHERE id<=0 ORDER BY id DESC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        at.f_id = GET_ID( result.GetInt64( 0 ) );
        at.f_name = result.GetAsString( 1 );
        list.push_back( at );
    }

    // Put user entries in list.
    sql.Format(
        "SELECT id, name FROM NameStyle "
        "WHERE id>0 ORDER BY id ASC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        at.f_id = GET_ID( result.GetInt64( 0 ) );
        at.f_name = result.GetAsString( 1 );
        list.push_back( at );
    }

    return list;
}

// End of recPersona.cpp file
