/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recSource.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Source record.
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

#include <rec/recSource.h>

//============================================================================
//                 recSource
//============================================================================

recSource::recSource( const recSource& s )
{
    f_higher_id    = s.f_higher_id;
    f_sub_date1_id = s.f_sub_date1_id;
    f_sub_date2_id = s.f_sub_date2_id;
    f_sub_place_id = s.f_sub_place_id;
    f_loc_place_id = s.f_loc_place_id;
    f_res_id       = s.f_res_id;
    f_comments     = s.f_comments;
}

void recSource::Clear()
{
    f_higher_id    = 0;
    f_sub_date1_id = 0;
    f_sub_date2_id = 0;
    f_sub_place_id = 0;
    f_loc_place_id = 0;
    f_res_id       = 0;
    f_comments     = wxEmptyString;
}

void recSource::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Source (higher_id, sub_date1_id, sub_date2_id, "
            "sub_place_id, loc_place_id, res_id, comments) "
            "VALUES ("ID", "ID", "ID", "ID", "ID", "ID", '%q');",
            f_higher_id, f_sub_date1_id, f_sub_date2_id, f_sub_place_id,
            f_loc_place_id, f_res_id, UTF8_(f_comments)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Source (id, higher_id, sub_date1_id, sub_date2_id, "
                "sub_place_id, loc_place_id, res_id, comments) "
                "VALUES ("ID", "ID", "ID", "ID", "ID", "ID", "ID", '%q');",
                f_id, f_higher_id, f_sub_date1_id, f_sub_date2_id, f_sub_place_id,
                f_loc_place_id, f_res_id, UTF8_(f_comments)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Source SET higher_id="ID", sub_date1_id="ID", sub_date2_id="ID", "
                "sub_place_id="ID", loc_place_id="ID", res_id="ID", comments='%q' "
                "WHERE id="ID";",
                f_higher_id, f_sub_date1_id, f_sub_date2_id, f_sub_place_id,
                f_loc_place_id, f_res_id, UTF8_(f_comments), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recSource::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT higher_id, sub_date1_id, sub_date2_id, "
        "sub_place_id, loc_place_id, res_id, comments "
        "FROM Source WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_higher_id    = GET_ID( result.GetInt64( 0 ) );
    f_sub_date1_id = GET_ID( result.GetInt64( 1 ) );
    f_sub_date2_id = GET_ID( result.GetInt64( 2 ) );
    f_sub_place_id = GET_ID( result.GetInt64( 3 ) );
    f_loc_place_id = GET_ID( result.GetInt64( 4 ) );
    f_res_id       = GET_ID( result.GetInt64( 5 ) );
    f_comments     = result.GetAsString( 6 );
    return true;
}

//============================================================================
//                 recCitationPart
//============================================================================

recCitationPart::recCitationPart( const recCitationPart& cp )
{
    f_type_id   = cp.f_type_id;
    f_source_id = cp.f_source_id;
    f_val       = cp.f_val;
}

void recCitationPart::Clear()
{
    f_type_id   = 0;
    f_source_id = 0;
    f_val       = wxEmptyString;
}

void recCitationPart::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO CitationPart (type_id, source_id, val) "
            "VALUES ("ID", "ID", '%q');",
            f_type_id, f_source_id, UTF8_(f_val)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO CitationPart (id, type_id, source_id, val) "
                "VALUES ("ID", "ID", "ID", '%q');",
                f_id, f_type_id, f_source_id, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE CitationPart SET type_id="ID", source_id="ID", val='%q' "
                "WHERE id="ID";",
                f_type_id, f_source_id, UTF8_(f_val), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitationPart::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT type_id, source_id, val "
        "FROM CitationPart WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_type_id   = GET_ID( result.GetInt64( 0 ) );
    f_source_id = GET_ID( result.GetInt64( 1 ) );
    f_val       = result.GetAsString( 2 );
    return true;
}

//============================================================================
//                 recCitationPartType
//============================================================================

recCitationPartType::recCitationPartType( const recCitationPartType& at )
{
    f_id   = at.f_id;
    f_name = at.f_name;
}

void recCitationPartType::Clear()
{
    f_id   = 0;
    f_name = wxEmptyString;
}

void recCitationPartType::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO CitationPartType (name) VALUES ('%q');",
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
                "INSERT INTO CitationPartType (id, name) "
                "VALUES ("ID", '%q');",
                f_id, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE CitationPartType SET name='%q' WHERE id="ID";",
                UTF8_(f_name), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitationPartType::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT name FROM CitationPartType WHERE id="ID";", f_id );
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

wxString recCitationPartType::GetStr( idt id )
{
    recCitationPartType at( id );
    return at.f_name;
}

recCitationPartTypeVec recCitationPartType::GetList()
{
    recCitationPartType at;
    recCitationPartTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, name FROM CitationPartType "
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
        "SELECT id, name FROM CitationPartType "
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
//                 recRepository
//============================================================================

recRepository::recRepository( const recRepository& at )
{
    f_id       = at.f_id;
    f_name     = at.f_name;
    f_access   = at.f_access;
    f_comments = at.f_comments;
}

void recRepository::Clear()
{
    f_id       = 0;
    f_name     = wxEmptyString;
    f_access   = wxEmptyString;
    f_comments = wxEmptyString;
}

void recRepository::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Repository (name, access, comments) "
            "VALUES ('%q', '%q', '%q');",
            UTF8_(f_name), UTF8_(f_access), UTF8_(f_comments)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Repository (id, name, access, comments) "
                "VALUES ("ID", '%q', '%q', '%q');",
                f_id, UTF8_(f_name), UTF8_(f_access), UTF8_(f_comments)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Repository SET name='%q', access='%q', comments='%q' "
                "WHERE id="ID";",
                UTF8_(f_name), UTF8_(f_access), UTF8_(f_comments), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRepository::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, access, comments FROM Repository WHERE id="ID";",
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
    f_access   = result.GetAsString( 1 );
    f_comments = result.GetAsString( 2 );
    return true;
}

//============================================================================
//                 recRepositorySource
//============================================================================

recRepositorySource::recRepositorySource( const recRepositorySource& at )
{
    f_id        = at.f_id;
    f_repos_id  = at.f_repos_id;
    f_source_id = at.f_source_id;
    f_call_num  = at.f_call_num;
    f_desc      = at.f_desc;
}

void recRepositorySource::Clear()
{
    f_id        = 0;
    f_repos_id  = 0;
    f_source_id = 0;
    f_call_num  = wxEmptyString;
    f_desc      = wxEmptyString;
}

void recRepositorySource::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO RepositorySource (repos_id, source_id, call_num, desc) "
            "VALUES ("ID", "ID", '%q', '%q');",
            f_repos_id, f_source_id, UTF8_(f_call_num), UTF8_(f_desc)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO RepositorySource (id, repos_id, source_id, call_num, desc) "
                "VALUES ("ID", "ID", "ID", '%q', '%q');",
                f_id, f_repos_id, f_source_id, UTF8_(f_call_num), UTF8_(f_desc)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE RepositorySource SET repos_id="ID", source_id="ID", "
                "call_num='%q', desc='%q' WHERE id="ID";",
                f_repos_id, f_source_id, UTF8_(f_call_num), UTF8_(f_desc), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRepositorySource::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT repos_id, source_id, call_num, desc FROM RepositorySource WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_repos_id  = GET_ID( result.GetInt64( 0 ) );
    f_source_id = GET_ID( result.GetInt64( 1 ) );
    f_call_num  = result.GetAsString( 2 );
    f_desc      = result.GetAsString( 3 );
    return true;
}

// End of recSource.cpp file
