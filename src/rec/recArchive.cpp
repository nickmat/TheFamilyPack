/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recArchive.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Archive database records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recArchive.h>

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
                "VALUES (" ID ", '%q', '%q', '%q');",
                f_id, UTF8_(f_name), UTF8_(f_access), UTF8_(f_comments)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Repository SET name='%q', access='%q', comments='%q' "
                "WHERE id=" ID ";",
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
        "SELECT name, access, comments FROM Repository WHERE id=" ID ";",
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
    f_descrip   = at.f_descrip;
}

void recRepositorySource::Clear()
{
    f_id        = 0;
    f_repos_id  = 0;
    f_source_id = 0;
    f_call_num  = wxEmptyString;
    f_descrip   = wxEmptyString;
}

void recRepositorySource::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO RepositorySource (repos_id, source_id, call_num, descrip) "
            "VALUES (" ID ", " ID ", '%q', '%q');",
            f_repos_id, f_source_id, UTF8_(f_call_num), UTF8_(f_descrip)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO RepositorySource (id, repos_id, source_id, call_num, descrip) "
                "VALUES (" ID ", " ID ", " ID ", '%q', '%q');",
                f_id, f_repos_id, f_source_id, UTF8_(f_call_num), UTF8_(f_descrip)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE RepositorySource SET repos_id=" ID ", source_id=" ID ", "
                "call_num='%q', descrip='%q' WHERE id=" ID ";",
                f_repos_id, f_source_id, UTF8_(f_call_num), UTF8_(f_descrip), f_id
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
        "SELECT repos_id, source_id, call_num, descrip FROM RepositorySource WHERE id=" ID ";",
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
    f_descrip   = result.GetAsString( 3 );
    return true;
}

// End of recSource.cpp file
