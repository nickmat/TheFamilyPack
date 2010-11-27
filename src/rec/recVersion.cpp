/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recVersion.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Version record.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
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

#include <rec/recVersion.h>

const int recVersionMajor    = 0;
const int recVersionMinor    = 0;
const int recVersionRevision = 8;
const int recVersionTest     = 0;
const wxChar* recVersionStr  = wxT("0.0.8.0");


recVersion::recVersion( const recVersion& v )
{
    f_id       = v.f_id;
    f_major    = v.f_major;
    f_minor    = v.f_minor;
    f_revision = v.f_revision;
}

void recVersion::Clear()
{
    f_id       = 0;
    f_major    = 0;
    f_minor    = 0;
    f_revision = 0;
}

void recVersion::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Version (major, minor, revision, test) "
            "VALUES (%d, %d, %d, %d);",
            f_major, f_minor, f_revision, f_test
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Version (id, major, minor, revision, test) "
                "VALUES ("ID", %d, %d, %d, %d);",
                f_id, f_major, f_minor, f_revision, f_test
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Version SET major=%d, minor=%d, revision=%d, test=%d "
                "WHERE id="ID";",
                f_major, f_minor, f_revision, f_test, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recVersion::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT major, minor, revision, test FROM Version WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_major    = result.GetInt( 0 );
    f_minor    = result.GetInt( 1 );
    f_revision = result.GetInt( 2 );
    f_test     = result.GetInt( 3 );
    return true;
}

bool recVersion::IsEqual( int major, int minor, int revision, int test ) const
{
    return
        f_major    == major    &&
        f_minor    == minor    &&
        f_revision == revision &&
        f_test     == test;
}

bool recVersion::IsMoreThan( int major, int minor, int revision, int test ) const
{
    if( f_major > major ) return true;
    if( f_major < major ) return false;
    if( f_minor > minor ) return true;
    if( f_minor < minor ) return false;
    if( f_revision > revision ) return true;
    if( f_revision < revision ) return false;
    if( f_test > test ) return true;
    return false;
}

bool recVersion::IsLessThan( int major, int minor, int revision, int test ) const
{
    if( f_major < major ) return true;
    if( f_major > major ) return false;
    if( f_minor < minor ) return true;
    if( f_minor > minor ) return false;
    if( f_revision < revision ) return true;
    if( f_revision > revision ) return false;
    if( f_test < test ) return true;
    return false;
}

// End of recVersion.cpp file
