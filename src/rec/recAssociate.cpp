/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recAssociate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Associate records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018..2022, Nick Matthews.
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
    f_comment = at.f_comment;
}

void recAssociate::Clear()
{
    f_id = 0;
    f_path.clear();
    f_comment.clear();
}

void recAssociate::Save( const wxString& extdb )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Associate (path, comment) VALUES ('%q', '%q');",
            UTF8_( extdb ), UTF8_( f_path ), UTF8_( f_comment )
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Associate (id, path, comment) "
                "VALUES (" ID ", '%q', '%q');",
                UTF8_( extdb ), f_id, UTF8_( f_path ), UTF8_( f_comment )
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Associate SET path='%q', comment='%q' WHERE id=" ID ";",
                UTF8_( extdb ), UTF8_( f_path ), UTF8_( f_comment ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recAssociate::Read( const wxString& extdb )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( 
        "SELECT path, comment FROM \"%s\".Associate WHERE id=" ID ";",
        UTF8_( extdb ), f_id
    );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_path = result.GetAsString( 0 );
    f_comment = result.GetAsString( 1 );
    return true;
}

idt recAssociate::Create( const wxString & path, const wxString& comment )
{
    recAssociate ass( 0 );
    ass.FSetPath( path );
    ass.FSetComment( comment );
    ass.Save();
    return ass.FGetID();
}

wxString recAssociate::GetAttachedName( idt assID, const wxString& extdb )
{
    if ( s_extdbs[extdb].assIdMap.count(assID) == 1 ) {
        return s_extdbs[extdb].assIdMap[assID];
    }
    recAssociate ass( assID, extdb );
    wxString path = ass.FGetPath();
    if ( path.empty() ) {
        return wxString();
    }
    wxString cap( path.Capitalize() );
    StringVec assvec = s_extdbs[extdb].assdbs;
    for( auto& n = assvec.begin(); n != assvec.end(); n++ ) {
        if( *n == cap ) {
            s_extdbs[extdb].assIdMap[assID] = cap;
            return cap;
        }
    }
    cap = recDb::OpenAssociateDb( extdb, path, path );
    if( !cap.empty() ) {
        s_extdbs[extdb].assIdMap[assID] = cap;
    }
    return cap;
}

recAssociateVec recAssociate::GetList( const wxString& extdb )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, path, comment FROM \"%s\".Associate"
        " WHERE id>0 ORDER BY id ASC;",
        UTF8_( extdb )
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recAssociateVec vec;
    recAssociate ass( 0 );
    while ( result.NextRow() ) {
        ass.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        ass.FSetPath( result.GetAsString( 1 ) );
        ass.FSetComment( result.GetAsString( 2 ) );
        vec.push_back( ass );
    }
    return vec;
}

// End of recAssociate.cpp file
