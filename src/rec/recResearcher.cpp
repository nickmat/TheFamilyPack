/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recResearcher.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Researcher record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     4th December 2021
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

#include <rec/recResearcher.h>
#include <rec/recUser.h>

//============================================================================
//                 recResearcher
//============================================================================

recResearcher::recResearcher( const recResearcher& res )
{
    f_id          = res.f_id;
    f_name        = res.f_name;
    f_comments    = res.f_comments;
    f_con_list_id = res.f_con_list_id;
}

void recResearcher::Clear()
{
    f_id          = 0;
    f_name        = wxEmptyString;
    f_comments    = wxEmptyString;
    f_con_list_id = 0;
}

void recResearcher::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Researcher (name, comments, con_list_id)"
            " VALUES ('%q', NULLIF('%q', ''), NULLIF(" ID ", 0));",
            UTF8_(f_name), UTF8_(f_comments), f_con_list_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Researcher (id, name, comments, con_list_id)"
                " VALUES (" ID ", NULLIF('%q', ''), '%q', NULLIF(" ID ", 0));",
                f_id, UTF8_(f_name), UTF8_(f_comments), f_con_list_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Researcher SET name='%q', comments=NULLIF('%q', ''),"
                " con_list_id=NULLIF(" ID ", 0)"
                " WHERE id=" ID ";",
                UTF8_(f_name), UTF8_(f_comments), f_con_list_id, f_id
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
        "SELECT name, comments, con_list_id FROM Researcher WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name        = result.GetAsString( 0 );
    f_comments    = result.GetAsString( 1 );
    f_con_list_id = GET_ID( result.GetInt64( 2 ) );
    return true;
}

bool recResearcher::Equivalent( const recResearcher& r2 ) const
{
    return
        f_name        == r2.f_name     &&
        f_comments    == r2.f_comments &&
        f_con_list_id == r2.f_con_list_id;
}

wxString recResearcher::GetNameStr( idt resID )
{
    return ExecuteStr( "SELECT name FROM Researcher WHERE id=" ID ";", resID );
}

idt recResearcher::GetUserID() const
{
    return ExecuteID( "SELECT id FROM User WHERE res_id=" ID ";", f_id );
}

wxString recResearcher::GetUserIdStr() const
{
    idt uID = GetUserID();
    if( uID == 0 ) return wxEmptyString;
    return recUser::GetIdStr( uID );
}

recResearcherVec recResearcher::GetResearchers( ListFilter filter )
{
    recResearcherVec list;
    recResearcher res;

    if( filter == ListFilter::all || filter == ListFilter::user ) {
        wxSQLite3ResultSet result = s_db->ExecuteQuery(
            "SELECT id, name, comments, con_list_id FROM Researcher"
            " WHERE id>0 ORDER BY id;"
        );

        while( result.NextRow() ) {
            res.FSetID( GET_ID( result.GetInt64( 0 ) ) );
            res.FSetName( result.GetAsString( 1 ) );
            res.FSetComments( result.GetAsString( 2 ) );
            res.FSetConListID( GET_ID( result.GetInt64( 3 ) ) );
            list.push_back( res );
        }
    }
    if( filter == ListFilter::all || filter == ListFilter::common ) {
        wxSQLite3ResultSet result = s_db->ExecuteQuery(
            "SELECT id, name, comments, con_list_id FROM Researcher"
            " WHERE id<0 ORDER BY id;"
        );

        while( result.NextRow() ) {
            res.FSetID( GET_ID( result.GetInt64( 0 ) ) );
            res.FSetName( result.GetAsString( 1 ) );
            res.FSetComments( result.GetAsString( 2 ) );
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
    recCsvWrite( out, res.FGetComments() );
    recCsvWrite( out, res.FGetConListID(), '\n' );
}

bool recResearcher::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    recCsvRead( in, f_comments );
    recCsvRead( in, f_con_list_id );
    return bool( in );
}

// End of recContact.cpp file
