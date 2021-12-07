/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recContact.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Contact records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25 February 2011
 * Copyright:   Copyright (c) 2011 .. 2021, Nick Matthews.
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

#include <rec/recContact.h>
#include <rec/recUser.h>

//============================================================================
//                 recContact
//============================================================================

recContact::recContact( const recContact& s )
{
    f_id       = s.f_id;
    f_type_id  = s.f_type_id;
    f_list_id  = s.f_list_id;
    f_val      = s.f_val;
}

void recContact::Clear()
{
    f_id       = 0;
    f_type_id  = 0;
    f_list_id  = 0;
    f_val      = wxEmptyString;
}

void recContact::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Contact (type_id, list_id, val) "
            "VALUES (" ID ", " ID ", '%q');",
            f_type_id, f_list_id, UTF8_(f_val)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Contact (id, type_id, list_id, val) "
                "VALUES (" ID ", " ID ", " ID ", '%q');",
                f_id, f_type_id, f_list_id, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Contact SET type_id=" ID ", list_id=" ID ", val='%q' "
                "WHERE id=" ID ";",
                f_type_id, f_list_id, UTF8_(f_val), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recContact::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT type_id, list_id, val "
        "FROM Contact WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_type_id  = GET_ID( result.GetInt64( 0 ) );
    f_list_id  = GET_ID( result.GetInt64( 1 ) );
    f_val      = result.GetAsString( 2 );
    return true;
}

bool recContact::Equivalent( const recContact& r2 ) const 
{
    return
        f_type_id  == r2.f_type_id  &&
        f_list_id  == r2.f_list_id  &&
        f_val      == r2.f_val;
}

wxString recContact::GetHtmlValue( const wxString prefixHref ) const
{
    wxString format;

    switch( f_type_id )
    {
    case recContactType::CT_Website:
        format = "<a href='%shttp://%s'>%s</a>";
        break;
    case recContactType::CT_Email:
        format = "<a href='%smailto:%s'>%s</a>";
        break;
    default:
        return recHTMLifyStr( f_val );
    }
    return wxString::Format( format, prefixHref, f_val, f_val );
}

void recContact::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Contact SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recContact::CsvTitles()
{
    return std::string( "ID, Contact Type ID, Contact List ID, Value\n" );
}

void recContact::CsvWrite( std::ostream& out, idt id )
{
    recContact con( id );
    recCsvWrite( out, con.FGetID() );
    recCsvWrite( out, con.FGetTypeID() );
    recCsvWrite( out, con.FGetListID() );
    recCsvWrite( out, con.FGetValue(), '\n' );
}

bool recContact::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_type_id );
    recCsvRead( in, f_list_id );
    recCsvRead( in, f_val );
    return bool( in );
}

//============================================================================
//                 recContactList
//============================================================================

recContactList::recContactList( const recContactList& cl )
{
    f_id     = cl.f_id;
    f_ind_id = cl.f_ind_id;
}

void recContactList::Clear()
{
    f_id     = 0;
    f_ind_id = 0;
}

void recContactList::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        // Add new record
        sql.Format(
            "INSERT INTO ContactList (ind_id) VALUES (NULLIF(" ID ", 0));",
            f_ind_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() ) {
            // Add new record
            sql.Format(
                "INSERT INTO ContactList (id, ind_id) "
                "VALUES (" ID ", NULLIF(" ID ", 0));",
                f_id, f_ind_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE ContactList SET ind_id=NULLIF(" ID ", 0) WHERE id=" ID ";",
                f_ind_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recContactList::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT ind_id FROM ContactList WHERE id=" ID ";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ind_id = GET_ID( result.GetInt64( 0 ) );
    return true;
}

recContactVec recContactList::GetContacts( idt listID )
{
    recContactVec list;

    if( listID == 0 ) return list;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, type_id, val"
        " FROM Contact WHERE list_id=" ID ";",
        listID
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recContact con(0);
    con.FSetListID( listID );
    while( result.NextRow() ) {
        con.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        con.FSetTypeID( GET_ID( result.GetInt64( 1 ) ) );
        con.FSetValue( result.GetAsString( 2 ) );
        list.push_back( con );
    }
    return list;
}

idt recContactList::FindIndID( idt indID )
{
    return ExecuteID( "SELECT id FROM ContactList WHERE ind_id=" ID ";", indID );
}

void recContactList::Assimilate( idt targetID ) const
{
    if( f_id == 0 || targetID == 0 || f_id == targetID ) return;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "UPDATE Contact SET list_id=" ID " WHERE list_id=" ID ";",
        f_id, targetID
    );
    s_db->ExecuteUpdate( sql );
    Delete( targetID );
}

void recContactList::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Contact SET list_id=" ID " WHERE list_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Researcher SET con_list_id=" ID " WHERE con_list_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Repository SET con_list_id=" ID " WHERE con_list_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE ContactList SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recContactList::CsvTitles()
{
    return std::string("ID, Individual ID\n");
}

void recContactList::CsvWrite( std::ostream& out, idt id )
{
    recContactList cl( id );
    recCsvWrite( out, cl.FGetID() );
    recCsvWrite( out, cl.FGetIndID(), '\n' );
}

bool recContactList::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_ind_id );
    return bool( in );
}

//============================================================================
//                 recContactType
//============================================================================

recContactType::recContactType( const recContactType& at )
{
    f_id   = at.f_id;
    f_name = at.f_name;
}

void recContactType::Clear()
{
    f_id   = 0;
    f_name = wxEmptyString;
}

void recContactType::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO ContactType (name) VALUES ('%q');",
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
                "INSERT INTO ContactType (id, name) "
                "VALUES (" ID ", '%q');",
                f_id, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE ContactType SET name='%q' WHERE id=" ID ";",
                UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recContactType::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT name FROM ContactType WHERE id=" ID ";", f_id );
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

wxString recContactType::GetTypeStr( idt typeID )
{
    recContactType ct( typeID );
    return ct.f_name;
}

recContactTypeVec recContactType::GetList()
{
    recContactType at;
    recContactTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, name FROM ContactType "
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
        "SELECT id, name FROM ContactType "
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

void recContactType::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Contact SET type_id=" ID " WHERE type_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE ContactType SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recContactType::CsvTitles()
{
    return std::string( "ID, Name\n" );
}

void recContactType::CsvWrite( std::ostream& out, idt id )
{
    recContactType ct( id );
    recCsvWrite( out, ct.FGetID() );
    recCsvWrite( out, ct.FGetName(), '\n' );
}

bool recContactType::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    return bool( in );
}


// End of recContact.cpp file
