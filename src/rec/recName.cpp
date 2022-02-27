/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Name, NamePart, NamePartType and NameStyle records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22 November 2010
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

#include <rec/recName.h>

#include <rec/recPersona.h>

#include <wx/tokenzr.h>


//============================================================================
//-------------------------[ recName ]----------------------------------------
//============================================================================

recName::recName( const recName& n )
{
    f_id       = n.f_id;
    f_ind_id   = n.f_ind_id;
    f_per_id   = n.f_per_id;
    f_style_id = n.f_style_id;
    f_sequence = n.f_sequence;
}

void recName::Clear()
{
    f_id       = 0;
    f_ind_id   = 0;
    f_per_id   = 0;
    f_style_id = 0;
    f_sequence = 0;
}

void recName::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Name (ind_id, per_id, style_id, sequence)"
            "VALUES (" ID ", " ID ", " ID ", %d);",
            UTF8_( dbname ), f_ind_id, f_per_id, f_style_id, f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Name (id, ind_id, per_id, style_id, sequence)"
                "VALUES (" ID ", " ID ", " ID ", " ID ", %d);",
                UTF8_( dbname ), f_id, f_ind_id, f_per_id, f_style_id, f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Name SET ind_id=" ID ", per_id=" ID ", style_id=" ID ", sequence=%d WHERE id=" ID ";",
                UTF8_( dbname ), f_ind_id, f_per_id, f_style_id, f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recName::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ind_id, per_id, style_id, sequence "
        "FROM \"%s\".Name WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ind_id   = GET_ID( result.GetInt64( 0 ) );
    f_per_id   = GET_ID( result.GetInt64( 1 ) );
    f_style_id = GET_ID( result.GetInt64( 2 ) );
    f_sequence = result.GetInt( 3 );
    return true;
}

bool recName::Equivalent( const recName& r2 ) const
{
    return
        f_ind_id == r2.f_ind_id &&
        f_per_id == r2.f_per_id &&
        f_style_id == r2.f_style_id &&
        f_sequence == r2.f_sequence
    ;
}

idt recName::GetIndID( idt nameID, const wxString& dbname )
{
    return ExecuteID( "SELECT ind_id FROM \"%s\".Name WHERE id=" ID ";",
        UTF8_( dbname ), nameID );
}

idt recName::GetPerID( idt nameID, const wxString& dbname )
{
    return ExecuteID( "SELECT per_id FROM \"%s\".Name WHERE id=" ID ";",
        UTF8_( dbname ), nameID );
}

idt recName::CreateName( const wxString& nameStr, idt style )
{
    recName name(0);
    name.f_style_id = style;
    name.Save();
    name.AddNameParts( nameStr );
    return name.f_id;
}

idt recName::Create( const wxString& nameStr, idt indID, idt perID, idt style, int* pseq )
{
    assert( pseq != NULL ); // TODO: Allow for NULL
    recName name(0);
    name.f_ind_id = indID;
    name.f_per_id = perID;
    name.f_style_id = style;
    name.f_sequence = ++(*pseq);
    name.Save();
    name.AddNameParts( nameStr );
    return name.f_id;
}

int recName::AddNameParts( const wxString& nameStr, recStdNameType type, int seq ) const
{
    recNamePart part(0);
    part.f_name_id = f_id;
    part.f_sequence = seq;

    wxStringTokenizer tk( nameStr );
    if( type == NAME_TYPE_Unstated ) {
        // TODO: Action should depend on naming conventions
        while( tk.HasMoreTokens() ) {
            part.f_id = 0;
            part.f_val = tk.GetNextToken();
            part.f_type_id = tk.HasMoreTokens() ? NAME_TYPE_Given_name : NAME_TYPE_Surname;
            ++part.f_sequence;
            part.Save();
        }
    } else {
        part.f_type_id = type;
        while( tk.HasMoreTokens() ) {
            part.f_id = 0;
            part.f_val = tk.GetNextToken();
            ++part.f_sequence;
            part.Save();
        }
    }
    return part.f_sequence;
}

int recName::AddNamePart( const wxString& nameStr, recStdNameType type, int seq ) const
{
    recNamePart part(0);
    part.f_name_id = f_id;
    part.f_type_id = type;
    part.f_val = nameStr;
    part.f_sequence = ++seq;
    part.Save();
    return part.f_sequence;
}

idt recName::GetDefaultNameID( idt indID, idt perID, const wxString& dbname )
{
    wxString str;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id FROM \"%s\".Name WHERE ind_id=" ID " AND per_id=" ID " ORDER BY sequence;",
        UTF8_( dbname ), indID, perID
    );
    wxSQLite3Table result = s_db->GetTable( sql );
    if( result.GetRowCount() > 0 ) {
        return GET_ID( result.GetInt64( 0 ) );
    }
    return 0;
}

wxString recName::GetDefaultNameStr( idt indID, idt perID, const wxString& dbname )
{
    idt nameID = GetDefaultNameID( indID, perID, dbname );
    return GetNameStr( nameID, dbname );
}

recNameVec recName::GetNames( idt indID, idt perID, const wxString& dbname )
{
    recNameVec list;
    recName name(0);
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, style_id, sequence FROM \"%s\".Name"
        " WHERE ind_id=" ID " AND per_id=" ID " ORDER BY sequence;",
        UTF8_( dbname ), indID, perID
    );
    result = s_db->GetTable( sql );

    name.FSetIndID( indID );
    name.FSetPerID( perID );
    list.reserve( result.GetRowCount() );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        name.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        name.FSetTypeID( GET_ID( result.GetInt64( 1 ) ) );
        name.FSetSequence( result.GetInt( 2 ) );
        list.push_back( name );
    }
    return list;
}

void recName::RemoveFromDatabase( idt id, const wxString& dbname )
{
    if( id == 0 ) return;

    // TODO: Consider making 2 functions, one for reference, one for individual.
    wxSQLite3StatementBuffer sql;

    // TODO: Ensure Event is removed from reference statement.
    sql.Format(
        "DELETE FROM \"%s\".NamePart WHERE name_id=" ID ";"
        "DELETE FROM \"%s\".ReferenceEntity "
             "WHERE entity_type=7 AND entity_id=" ID ";"
        "DELETE FROM \"%s\".Name WHERE id=" ID ";",
        UTF8_( dbname ), id, UTF8_( dbname ), id, UTF8_( dbname ), id
    );
    s_db->ExecuteUpdate( sql );
}

wxString recName::GetNameStr( idt id, const wxString& dbname )
{
    if( id == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT val FROM \"%s\".NamePart "
        "WHERE name_id=" ID " "
        "ORDER BY sequence;",
        UTF8_( dbname ), id
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

wxString recName::GetTypeStr( const wxString& dbname ) const
{
    return ExecuteStr(
        "SELECT name FROM \"%s\".NameStyle WHERE id=" ID ";",
        UTF8_( dbname ), f_style_id
    );
}

wxString recName::GetTypeStr( idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( 
        "SELECT NS.name FROM \"%s\".Name N, \"%s\".NameStyle NS"
        " WHERE N.id=" ID " AND N.style_id=NS.id;",
        UTF8_( dbname ), UTF8_( dbname ), id
    );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

wxString recName::GetNamePartStr( idt nameID, idt partID, const wxString& dbname )
{
    if( nameID == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT val FROM \"%s\".NamePart "
        "WHERE name_id=" ID " AND type_id=" ID " "
        "ORDER BY sequence;",
        UTF8_( dbname ), nameID, partID
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

wxSQLite3ResultSet recName::GetSurnameIndex( recSurnameGroup surnamegrp, const wxString& dbname )
{
    const char* grp;
    switch ( surnamegrp ) {
    case recSG_Individual:
        grp = "per_id";
        break;
    case recSG_Persona:
        grp = "ind_id";
        break;
    default:
        return wxSQLite3ResultSet();
    }
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT NP.val FROM \"%s\".NamePart NP, \"%s\".Name N"
        " WHERE N.%s=0 AND N.id=NP.name_id AND NP.type_id=-2"
        " GROUP BY NP.val;", UTF8_( dbname ), UTF8_( dbname ), grp
    );
    return s_db->ExecuteQuery( sql );
}

recNameVec recName::GetNameList( const wxString& surname, recSurnameGroup sng, const wxString& dbname )
{
    recNameVec list;

    const char* not_grp;
    switch ( sng ) {
    case recSG_Individual:
        not_grp = "per_id";
        break;
    case recSG_Persona:
        not_grp = "ind_id";
        break;
    default:
        return list;
    }

    wxSQLite3StatementBuffer sql;
    if ( surname.empty() ) {
        // Select all names for group.
        sql.Format(
            "SELECT N.id, N.ind_id, N.per_id, N.style_id, N.sequence"
            " FROM \"%s\".Name N, \"%s\".NamePart NP"
            " WHERE NP.type_id=-2 AND N.id=NP.name_id AND N.%s=0;",
            UTF8_( dbname ), UTF8_( dbname ), not_grp
        );
    } else {
        sql.Format(
            "SELECT N.id, N.ind_id, N.per_id, N.style_id, N.sequence"
            " FROM \"%s\".Name N, \"%s\".NamePart NP"
            " WHERE NP.type_id=-2 AND N.id=NP.name_id AND N.%s=0 AND NP.val='%q';",
            UTF8_( dbname ), UTF8_( dbname ), not_grp, UTF8_( surname )
        );
    }
    wxSQLite3Table result = s_db->GetTable( sql );

    recName name( 0 );
    list.reserve( result.GetRowCount() );
    for ( int i = 0; i < result.GetRowCount(); i++ )
    {
        result.SetRow( i );
        name.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        name.FSetIndID( GET_ID( result.GetInt64( 1 ) ) );
        name.FSetPerID( GET_ID( result.GetInt64( 2 ) ) );
        name.FSetTypeID( GET_ID( result.GetInt64( 3 ) ) );
        name.FSetSequence( result.GetInt( 4 ) );
        list.push_back( name );
    }
    return list;
}

int recName::GetNextSequence( idt indID, idt perID )
{
    const char* owner;
    if( indID ) {
        owner = "ind_id";
    } else if( perID ) {
        owner = "per_id";
    } else {
        return 1;
    }
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT MAX(sequence) FROM Name WHERE %s=" ID ";", owner, perID );
    return s_db->ExecuteScalar( sql ) + 1;
}

idt recName::CreateIndNameFromPersona( idt indID, idt perID )
{
    if( indID == 0 || perID == 0 ) {
        return 0;
    }
    idt pnID = recPersona::GetNameID( perID );
    if( pnID == 0 ) {
        return 0;
    }
    recName pn(pnID);
    recName name(0);
    name.FSetIndID( indID );
    name.FSetTypeID( pn.FGetTypeID() );
    name.SetNextSequence();
    name.Save();

    recNamePartVec parts = pn.GetParts();
    for( size_t i = 0 ; i < parts.size() ; i++ ) {
        recNamePart p(parts[i]);
        p.FSetID( 0 );
        p.FSetNameID( name.FGetID() );
        p.FSetValue( p.FGetValue().Capitalize() );
        p.Save();
    }
    return name.FGetID();
}

recNamePartVec recName::GetParts( idt nameID, const wxString& dbname )
{
    recNamePartVec list;
    recNamePart part;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( nameID == 0 ) {
        return list;
    }

    sql.Format(
        "SELECT id, type_id, val, sequence FROM \"%s\".NamePart "
        "WHERE name_id=" ID " ORDER BY sequence;",
        UTF8_( dbname ), nameID
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


//============================================================================
//-------------------------[ recNamePart ]------------------------------------
//============================================================================

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

void recNamePart::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".NamePart (name_id, type_id, val, sequence)"
            "VALUES (" ID ", " ID ", '%q', %d);",
            UTF8_( dbname ), f_name_id, f_type_id, UTF8_(f_val), f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".NamePart (id, name_id, type_id, val, sequence)"
                "VALUES (" ID ", " ID ", " ID ", '%q', %d);",
                UTF8_( dbname ), f_id, f_name_id, f_type_id, UTF8_(f_val), f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".NamePart SET name_id=" ID ", type_id=" ID ", val='%q', sequence=%d "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_name_id, f_type_id, UTF8_(f_val), f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recNamePart::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name_id, type_id, val, sequence "
        "FROM \"%s\".NamePart WHERE id=" ID ";",
        UTF8_( dbname ), f_id
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

bool recNamePart::Equivalent( const recNamePart& r2 ) const
{
    return
        f_name_id == r2.f_name_id &&
        f_type_id == r2.f_type_id &&
        f_val == r2.f_val &&
        f_sequence == r2.f_sequence
    ;
}

wxString recNamePart::GetValue( idt id, const wxString& dbname )
{
    if( id == 0 ) return wxEmptyString;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT val FROM \"%s\".NamePart WHERE id=" ID ";",
        UTF8_( dbname ), id
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 )
    {
        return wxEmptyString;
    }
    return result.GetAsString( 0 );
}

wxSQLite3ResultSet recNamePart::GetSurnameList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT val FROM \"%s\".NamePart WHERE type_id=-2 GROUP BY val;",
        UTF8_( dbname )
    );
    return s_db->ExecuteQuery( sql );
}


//============================================================================
//-------------------------[ recNamePartType ]--------------------------------
//============================================================================

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

void recNamePartType::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".NamePartType (grp, name) VALUES (%d, '%q');",
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
                "INSERT INTO \"%s\".NamePartType (id, grp, name) "
                "VALUES (" ID ", %d, '%q');",
                UTF8_( dbname ), f_id, f_grp, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".NamePartType SET grp=%d, name='%q' WHERE id=" ID ";",
                UTF8_( dbname ), f_grp, UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recNamePartType::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( 
        "SELECT grp, name FROM \"%s\".NamePartType WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
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

bool recNamePartType::Equivalent( const recNamePartType& r2 ) const
{
    return
        f_grp == r2.f_grp &&
        f_name == r2.f_name
    ;
}

wxString recNamePartType::GetTypeStr( idt id, const wxString& dbname )
{
    recNamePartType npt( id, dbname );
    return npt.f_name;
}

recNamePartTypeVec recNamePartType::GetTypeList( const wxString& dbname )
{
    recNamePartType at;
    recNamePartTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, grp, name FROM \"%s\".NamePartType "
        "WHERE id<0 ORDER BY id DESC;",
        UTF8_( dbname )
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
        "SELECT id, grp, name FROM \"%s\".NamePartType "
        "WHERE id>0 ORDER BY id ASC;",
        UTF8_( dbname )
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


//============================================================================
//-------------------------[ recNameStyle ]-----------------------------------
//============================================================================

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

void recNameStyle::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".NameStyle (name) VALUES ('%q');",
            UTF8_( dbname ), UTF8_(f_name)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".NameStyle (id, name) "
                "VALUES (" ID ", '%q');",
                UTF8_( dbname ), f_id, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".NameStyle SET name='%q' WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recNameStyle::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( 
        "SELECT name FROM \"%s\".NameStyle WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
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

wxString recNameStyle::GetStyleStr( idt id, const wxString& dbname )
{
    recNameStyle at( id, dbname );
    return at.f_name;
}

recNameStyleVec recNameStyle::GetStyleList( const wxString& dbname )
{
    recNameStyle at;
    recNameStyleVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, name FROM \"%s\".NameStyle "
        "WHERE id<=0 ORDER BY id DESC;",
        UTF8_( dbname )
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
        "SELECT id, name FROM \"%s\".NameStyle "
        "WHERE id>0 ORDER BY id ASC;",
        UTF8_( dbname )
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


// End of src/rec/recName.cpp file
