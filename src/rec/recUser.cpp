/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recUser.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 User records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25 February 2011
 * Copyright:   Copyright (c) 2011 ~ 2017, Nick Matthews.
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

#include <rec/recUser.h>
#include <rec/recContact.h>
#include <rec/recResearcher.h>

//============================================================================
//                 recUser
//============================================================================

recUser::recUser( const recUser& s )
{
    f_id     = s.f_id;
    f_res_id = s.f_res_id;
}

void recUser::Clear()
{
    f_id     = 0;
    f_res_id = 0;
}

void recUser::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        // Add new record
        sql.Format(
            "INSERT INTO User (res_id) VALUES (" ID ");",
            f_res_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() ) {
            // Add new record
            sql.Format(
                "INSERT INTO User (id, res_id) VALUES (" ID ", " ID ");",
                f_id, f_res_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE User SET res_id=" ID " WHERE id=" ID ";",
                f_res_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recUser::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT res_id FROM User WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_res_id = GET_ID( result.GetInt64( 0 ) );
    return true;
}

bool recUser::Equivalent( const recUser& r2 ) const
{ 
    return f_res_id == r2.f_res_id;
}

recUserVec recUser::GetUsers()
{
    recUserVec vec;

    wxSQLite3ResultSet result = 
        s_db->ExecuteQuery( "SELECT id, res_id FROM User;" );

    recUser user;
    while( result.NextRow() ) {
        user.f_id = GET_ID( result.GetInt64( 0 ) );
        user.f_res_id = GET_ID( result.GetInt64( 1 ) );
        vec.push_back( user );
    }
    return vec;
}

wxString recUser::GetNameStr() const
{
    return recResearcher::GetNameStr( f_res_id );
}

wxString recUser::GetSetting( idt userID, recUserSetting::Property prop )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT val FROM UserSetting WHERE user_id=" ID " AND property=%d;",
        userID, prop
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        // Get Default Value
        sql.Format(
            "SELECT val FROM UserSetting WHERE user_id=0 AND property=%d;",
            prop
        );
        result = s_db->GetTable( sql );

        if( result.GetRowCount() != 1 ) {
            // Still can't find it.
            return wxEmptyString;
        }
    }
    return result.GetAsString( 0 );
}

//============================================================================
//                 recUserSetting
//============================================================================

recUserSetting::recUserSetting( const recUserSetting& r2 )
{
    f_id       = r2.f_id;
    f_user_id  = r2.f_user_id;
    f_property = r2.f_property;
    f_val      = r2.f_val;
}

void recUserSetting::Clear()
{
    f_id       = 0;
    f_user_id  = 0;
    f_property = UP_Unstated;
    f_val      = wxEmptyString;
}

void recUserSetting::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        // Add new record
        sql.Format(
            "INSERT INTO UserSetting (user_id, property, val) VALUES (" ID ", %d, '%q');",
            f_user_id, f_property, UTF8_(f_val)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() ) {
            // Add new record
            sql.Format(
                "INSERT INTO UserSetting (id, user_id, property, val)"
                " VALUES (" ID ", " ID ", %d, '%q');",
                f_id, f_user_id, f_property, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE UserSetting SET user_id=" ID ", property=%d, val='%q' WHERE id=" ID ";",
                f_user_id, f_property, UTF8_(f_val), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recUserSetting::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT user_id, property, val FROM UserSetting WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_user_id  = GET_ID( result.GetInt64( 0 ) );
    f_property = (Property) result.GetInt( 1 );
    f_val      = result.GetAsString( 2 );
    return true;
}

bool recUserSetting::Equivalent( const recUserSetting& r2 ) const
{ 
    return 
        f_user_id  == r2.f_user_id  &&
        f_property == r2.f_property &&
        f_val      == r2.f_val;
}

void recUserSetting::Find( idt userID, recUserSetting::Property prop )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, val FROM UserSetting WHERE user_id=" ID " AND property=%d;",
        userID, prop
    );
    wxSQLite3Table result = s_db->GetTable( sql );

    Clear();
    f_user_id = userID;
    f_property = prop;
    if( result.GetRowCount() != 1 ) {
        return;
    }
    f_id = GET_ID( result.GetInt64( 0 ) );
    f_val = result.GetAsString( 1 );
}

// End of recUser.cpp file
