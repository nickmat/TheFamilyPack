/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recCitation.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Citation records.
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

#include <rec/recCitation.h>


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
            "VALUES (" ID ", " ID ", '%q');",
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
                "VALUES (" ID ", " ID ", " ID ", '%q');",
                f_id, f_type_id, f_source_id, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE CitationPart SET type_id=" ID ", source_id=" ID ", val='%q' "
                "WHERE id=" ID ";",
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
        "FROM CitationPart WHERE id=" ID ";",
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
                "VALUES (" ID ", '%q');",
                f_id, UTF8_(f_name)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE CitationPartType SET name='%q' WHERE id=" ID ";",
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

    sql.Format( "SELECT name FROM CitationPartType WHERE id=" ID ";", f_id );
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

// End of src/rec/recCitation.cpp file
