/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recAssociate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Associate records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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

#include <rec/recAssociate.h>

recAssociate::recAssociate( const recAssociate& at )
{
    f_id = at.f_id;
    f_path = at.f_path;
}

void recAssociate::Clear()
{
    f_id = 0;
    f_path = "";
}

void recAssociate::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Associate (path) VALUES ('%q');",
            UTF8_( f_path )
            );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Associate (id, path) "
                "VALUES (" ID ", '%q');",
                f_id, UTF8_( f_path )
                );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Associate SET path='%q' WHERE id=" ID ";",
                UTF8_( f_path ), f_id
                );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recAssociate::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT path FROM Associate WHERE id=" ID ";", f_id );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_path = result.GetAsString( 0 );
    return true;
}

wxString recAssociate::GetPath( idt assID )
{
    if ( s_assmap.count( assID ) == 1 ) {
        return s_assmap[assID];
    }
    recAssociate ass( assID );
    wxString path = ass.FGetPath();
    if ( path.empty() ) {
        return path;
    }
    // Check if it's already attached.
    if ( s_db->GetDatabaseFilename( path ).empty() ) {
        if ( AttachDb( path, path ) ) {
            s_assmap[assID] = path;
        } else {
            return wxString();
        }
    }
    return s_assmap[assID];
}

// End of recAssociate.cpp file
