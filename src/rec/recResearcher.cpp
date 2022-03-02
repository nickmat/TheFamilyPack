/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recResearcher.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Researcher record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     4th December 2021
 * Copyright:   Copyright (c) 2021 .. 2022, Nick Matthews.
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

#include <rec/recResearcher.h>
#include <rec/recUser.h>

//============================================================================
//                 recResearcher
//============================================================================

recResearcher::recResearcher( const recResearcher& res )
{
    f_id          = res.f_id;
    f_name        = res.f_name;
    f_comment    = res.f_comment;
    f_con_list_id = res.f_con_list_id;
}

void recResearcher::Clear()
{
    f_id          = 0;
    f_name        = wxEmptyString;
    f_comment     = wxEmptyString;
    f_con_list_id = 0;
}

void recResearcher::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Researcher (name, comments, con_list_id)"
            " VALUES ('%q', NULLIF('%q', ''), NULLIF(" ID ", 0));",
            UTF8_( dbname ), UTF8_(f_name), UTF8_(f_comment), f_con_list_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Researcher (id, name, comments, con_list_id)"
                " VALUES (" ID ", '%q', NULLIF('%q', ''), NULLIF(" ID ", 0));",
                UTF8_( dbname ), f_id, UTF8_(f_name), UTF8_(f_comment), f_con_list_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Researcher SET name='%q', comments=NULLIF('%q', ''),"
                " con_list_id=NULLIF(" ID ", 0)"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_name), UTF8_(f_comment), f_con_list_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recResearcher::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, comments, con_list_id FROM \"%s\".Researcher WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name        = result.GetAsString( 0 );
    f_comment    = result.GetAsString( 1 );
    f_con_list_id = GET_ID( result.GetInt64( 2 ) );
    return true;
}

bool recResearcher::Equivalent( const recResearcher& r2 ) const
{
    return
        f_name        == r2.f_name     &&
        f_comment     == r2.f_comment  &&
        f_con_list_id == r2.f_con_list_id;
}

wxString recResearcher::GetNameStr( idt resID, const wxString& dbname )
{
    return ExecuteStr(
        "SELECT name FROM \"%s\".Researcher WHERE id=" ID ";",
        UTF8_( dbname ), resID
    );
}

idt recResearcher::GetUserID( const wxString& dbname ) const
{
    return ExecuteID(
        "SELECT id FROM \"%s\".User WHERE res_id=" ID ";",
        UTF8_( dbname ), f_id
    );
}

wxString recResearcher::GetUserIdStr( const wxString& dbname ) const
{
    idt uID = GetUserID( dbname );
    if( uID == 0 ) return wxEmptyString;
    return recUser::GetIdStr( uID );
}

recResearcherVec recResearcher::GetResearchers( Coverage filter, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    recResearcherVec list;
    recResearcher res;

    if( filter == Coverage::all || filter == Coverage::user ) {
        sql.Format(
            "SELECT id, name, comments, con_list_id FROM \"%s\".Researcher"
            " WHERE id>0 ORDER BY id;",
            UTF8_( dbname )
        );
        wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

        while( result.NextRow() ) {
            res.FSetID( GET_ID( result.GetInt64( 0 ) ) );
            res.FSetName( result.GetAsString( 1 ) );
            res.FSetComment( result.GetAsString( 2 ) );
            res.FSetConListID( GET_ID( result.GetInt64( 3 ) ) );
            list.push_back( res );
        }
    }
    if( filter == Coverage::all || filter == Coverage::common ) {
        sql.Format(
            "SELECT id, name, comments, con_list_id FROM \"%s\".Researcher"
            " WHERE id<0 ORDER BY id;",
            UTF8_( dbname )
        );
        wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

        while( result.NextRow() ) {
            res.FSetID( GET_ID( result.GetInt64( 0 ) ) );
            res.FSetName( result.GetAsString( 1 ) );
            res.FSetComment( result.GetAsString( 2 ) );
            res.FSetConListID( GET_ID( result.GetInt64( 3 ) ) );
            list.push_back( res );
        }
    }
    return list;
}

void recResearcher::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE User SET res_id=" ID " WHERE res_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Reference SET res_id=" ID " WHERE res_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Researcher SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recResearcher::CsvTitles()
{
    return std::string("ID, Name, Comments, Contact List ID\n");
}

void recResearcher::CsvWrite( std::ostream& out, idt id )
{
    recResearcher res( id );
    recCsvWrite( out, res.FGetID() );
    recCsvWrite( out, res.FGetName() );
    recCsvWrite( out, res.FGetComment() );
    recCsvWrite( out, res.FGetConListID(), '\n' );
}

bool recResearcher::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    recCsvRead( in, f_comment );
    recCsvRead( in, f_con_list_id );
    return bool( in );
}

// End of recContact.cpp file
