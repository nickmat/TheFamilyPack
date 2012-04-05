/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recContact.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Contact records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     25 February 2011
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2011, Nick Matthews.
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

//============================================================================
//                 recContact
//============================================================================

recContact::recContact( const recContact& s )
{
    f_id       = s.f_id;
    f_type_id  = s.f_type_id;
    f_repos_id = s.f_repos_id;
    f_res_id   = s.f_res_id;
    f_ind_id   = s.f_ind_id;
    f_val      = s.f_val;
}

void recContact::Clear()
{
    f_id       = 0;
    f_type_id  = 0;
    f_repos_id = 0;
    f_res_id   = 0;
    f_ind_id   = 0;
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
            "INSERT INTO Contact (type_id, repos_id, res_id, ind_id, val) "
            "VALUES ("ID", "ID", "ID", "ID", '%q');",
            f_type_id, f_repos_id, f_res_id, f_ind_id, UTF8_(f_val)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Contact (id, type_id, repos_id, res_id, ind_id, val) "
                "VALUES ("ID", "ID", "ID", "ID", "ID", '%q');",
                f_id, f_type_id, f_repos_id, f_res_id, f_ind_id, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Contact SET type_id="ID", repos_id="ID", res_id="ID", "
                "ind_id="ID", val='%q' "
                "WHERE id="ID";",
                f_type_id, f_repos_id, f_res_id, f_ind_id, UTF8_(f_val), f_id
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
        "SELECT type_id, repos_id, res_id, ind_id, val "
        "FROM Contact WHERE id="ID";",
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
    f_repos_id = GET_ID( result.GetInt64( 1 ) );
    f_res_id   = GET_ID( result.GetInt64( 2 ) );
    f_ind_id   = GET_ID( result.GetInt64( 3 ) );
    f_val      = result.GetAsString( 4 );
    return true;
}

bool recContact::Equivalent( const recContact& r2 ) const 
{
    return
        f_type_id  == r2.f_type_id  &&
        f_repos_id == r2.f_repos_id &&
        f_res_id   == r2.f_res_id   &&
        f_ind_id   == r2.f_ind_id   &&
        f_val      == r2.f_val;
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
                "VALUES ("ID", '%q');",
                f_id, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE ContactType SET name='%q' WHERE id="ID";",
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

    sql.Format( "SELECT name FROM ContactType WHERE id="ID";", f_id );
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

//============================================================================
//                 recResearcher
//============================================================================

recResearcher::recResearcher( const recResearcher& at )
{
    f_id       = at.f_id;
    f_name     = at.f_name;
    f_comments = at.f_comments;
}

void recResearcher::Clear()
{
    f_id       = 0;
    f_name     = wxEmptyString;
    f_comments = wxEmptyString;
}

void recResearcher::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Researcher (name, comments) "
            "VALUES ('%q', '%q');",
            UTF8_(f_name), UTF8_(f_comments)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Researcher (id, name, comments) "
                "VALUES ("ID", '%q', '%q');",
                f_id, UTF8_(f_name), UTF8_(f_comments)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Researcher SET name='%q', comments='%q' "
                "WHERE id="ID";",
                UTF8_(f_name), UTF8_(f_comments), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recResearcher::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, comments FROM Researcher WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name     = result.GetAsString( 0 );
    f_comments = result.GetAsString( 1 );
    return true;
}

bool recResearcher::Equivalent( const recResearcher& r2 ) const
{
    return
        f_name     == r2.f_name    &&
        f_comments == r2.f_comments;
}

recContactVec recResearcher::GetContacts() const
{
    recContactVec list;

    if( f_id == 0 ) return list;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, type_id, repos_id, ind_id, val"
        " FROM Contact WHERE res_id="ID";",
        f_id
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recContact con(0);
    con.FSetResID( f_id );
    while( result.NextRow() ) {
        con.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        con.FSetTypeID( GET_ID( result.GetInt64( 1 ) ) );
        con.FSetReposID( GET_ID( result.GetInt64( 2 ) ) );
        con.FSetIndID( GET_ID( result.GetInt64( 3 ) ) );
        con.FSetValue( result.GetAsString( 4 ) );
        list.push_back( con );
    }
    return list;
}


// End of recContact.cpp file
