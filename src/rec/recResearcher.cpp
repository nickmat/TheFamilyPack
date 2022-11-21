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
    f_id = res.f_id;
    f_name = res.f_name;
    f_comment = res.f_comment;
    f_con_list_id = res.f_con_list_id;
    f_uid = res.f_uid;
    f_changed = res.f_changed;
}

void recResearcher::Clear()
{
    f_id = 0;
    f_name.clear();
    f_comment.clear();
    f_con_list_id = 0;
    f_uid.clear();
    f_changed = 0;
}

void recResearcher::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Researcher (name, comment, con_list_id, uid, changed)"
            " VALUES ('%q', NULLIF('%q', ''), NULLIF(" ID ", 0), '%q', %ld);",
            UTF8_( dbname ), UTF8_(f_name), UTF8_(f_comment), f_con_list_id,
            UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Researcher (id, name, comment, con_list_id, uid, changed)"
                " VALUES (" ID ", '%q', NULLIF('%q', ''), NULLIF(" ID ", 0), '%q', %ld);",
                UTF8_( dbname ), f_id, UTF8_(f_name), UTF8_(f_comment), f_con_list_id,
                UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Researcher SET name='%q', comment=NULLIF('%q', ''),"
                " con_list_id=NULLIF(" ID ", 0), uid='%q', changed=%ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_name), UTF8_(f_comment), f_con_list_id,
                UTF8_( f_uid ), f_changed, f_id
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
        "SELECT name, comment, con_list_id, uid, changed FROM \"%s\".Researcher WHERE id=" ID ";",
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
    f_uid = result.GetAsString( 3 );
    f_changed = result.GetInt( 4 );
    return true;
}

bool recResearcher::Equivalent( const recResearcher& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_comment == r2.f_comment &&
        f_con_list_id == r2.f_con_list_id &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
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
    wxASSERT( filter != Coverage::all && filter != Coverage::notzero );
    wxSQLite3StatementBuffer sql;
    recResearcherVec list;
    recResearcher res;

    if( filter == Coverage::userfirst || filter == Coverage::user ) {
        sql.Format(
            "SELECT id, name, comment, con_list_id, uid, changed FROM \"%s\".Researcher"
            " WHERE id>0 ORDER BY id;",
            UTF8_( dbname )
        );
        wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

        while( result.NextRow() ) {
            res.FSetID( GET_ID( result.GetInt64( 0 ) ) );
            res.FSetName( result.GetAsString( 1 ) );
            res.FSetComment( result.GetAsString( 2 ) );
            res.FSetConListID( GET_ID( result.GetInt64( 3 ) ) );
            res.FSetUid( result.GetAsString( 4 ) );
            res.FSetChanged( result.GetInt( 5 ) );
            list.push_back( res );
        }
    }
    if( filter == Coverage::userfirst || filter == Coverage::common ) {
        sql.Format(
            "SELECT id, name, comment, con_list_id, uid, changed FROM \"%s\".Researcher"
            " WHERE id<0 ORDER BY id;",
            UTF8_( dbname )
        );
        wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

        while( result.NextRow() ) {
            res.FSetID( GET_ID( result.GetInt64( 0 ) ) );
            res.FSetName( result.GetAsString( 1 ) );
            res.FSetComment( result.GetAsString( 2 ) );
            res.FSetConListID( GET_ID( result.GetInt64( 3 ) ) );
            res.FSetUid( result.GetAsString( 4 ) );
            res.FSetChanged( result.GetInt( 5 ) );
            list.push_back( res );
        }
    }
    return list;
}

idt recResearcher::Transfer(
    idt from_resID, const wxString& fromdb, const wxString& todb )
{
    if( from_resID == 0 ) return 0;
    recResearcher from_res( from_resID, fromdb );
    idt to_resID = from_resID;
    if( from_resID > 0 ) {
        recResearcher::FindUid( from_res.FGetUid(), todb );
    }
    recResearcher to_res( to_resID, todb );
    if( to_resID == 0 || from_res.FGetChanged() > to_res.FGetChanged() ) {
        idt to_clID = recContactList::Transfer( from_res.FGetConListID(), fromdb, to_res.FGetConListID(), todb );
        recResearcher new_res( from_res );
        new_res.FSetConListID( to_clID );
        new_res.FSetID( to_resID );
        new_res.Save( todb );
        to_resID = new_res.FGetID();
    }

    return to_resID;
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
    return std::string("ID, Name, Comment, Contact List ID, UID, Last Changed\n");
}

void recResearcher::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recResearcher res( id, dbname );
    recCsvWrite( out, res.FGetID() );
    recCsvWrite( out, res.FGetName() );
    recCsvWrite( out, res.FGetComment() );
    recCsvWrite( out, res.FGetConListID() );
    recCsvWrite( out, res.FGetUid() );
    recCsvWrite( out, res.FGetChanged(), '\n' );
}

bool recResearcher::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    recCsvRead( in, f_comment );
    recCsvRead( in, f_con_list_id );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

bool recResearcher::DeleteIfOrphaned( idt resID, const wxString& dbname )
{
    if( resID <= 0 ) return false;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Reference WHERE res_id=" ID ";",
        UTF8_( dbname ), resID
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".User WHERE res_id=" ID ";",
        UTF8_( dbname ), resID
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    recResearcher res( resID, dbname );
    if( !Delete( resID, dbname ) ) return false;

    recContactList::RemoveFromDatabase( res.FGetConListID(), dbname );
    return true;
}

// End of recContact.cpp file
