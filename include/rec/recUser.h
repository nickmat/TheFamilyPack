/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recUser.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 User record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25 February 2011
 * Copyright:   Copyright (c) 2011 .. 2021, Nick Matthews.
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

#ifndef RECUSER_H
#define RECUSER_H

#include <rec/recDatabase.h>
#include <rec/recSystem.h>

class recUser;
typedef std::vector< recUser >  recUserVec;
class recUserSetting;
typedef std::vector< recUserSetting >  recUserSettingVec;

//============================================================================
//                 recUserSetting
//============================================================================

class recUserSetting : public recDbT< recUserSetting>
{
public:
    static constexpr const char* s_tablename = "UserSetting";
    static constexpr recTable s_table = recTable::UserSetting;

    enum class Property {
        unstated = 0,
        home_screen,
        max_property
    };

    recUserSetting() : f_user_id( 0 ), f_property( Property::unstated ) {}
    recUserSetting( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recUserSetting( const recUserSetting& user );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recUserSetting& r2 ) const;

    idt FGetUserID() const { return f_user_id; }
    Property FGetProperty() const { return f_property; }
    wxString FGetValue() const { return f_val; }

    void FSetUserID( idt userID ) { f_user_id = userID; }
    void FSetProperty( Property up ) { f_property = up; }
    void FSetValue( const wxString& val ) { f_val = val; }

    void Find( idt userID, recUserSetting::Property prop, const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    idt      f_user_id;
    Property f_property;
    wxString f_val;
};


//============================================================================
//                 recUser
//============================================================================

class recUser : public recDbT< recUser>
{
public:
    static constexpr const char* s_tablename = "User";
    static constexpr recTable s_table = recTable::User;

    recUser() : f_res_id(0) {}
    recUser( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recUser( const recUser& user );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recUser& r2 ) const;

    idt FGetResID() const { return f_res_id; }

    void FSetResID( idt resID ) { f_res_id = resID; }

    static wxString GetIdStr( idt userID ) { return wxString::Format( "U" ID, userID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    idt FindFirst( const wxString& dbname, idt resID )
    {
        return ExecuteID(
            "SELECT id FROM \"%s\".User WHERE res_id=" ID " ORDER BY id;",
            dbname, resID );
    }

    static recUserVec GetUsers( const wxString& dbname = "Main");

    wxString GetNameStr() const;
    static wxString GetSetting( const wxString& dbname, idt userID, recUserSetting::Property prop );
    wxString GetSetting( const wxString& dbname, recUserSetting::Property prop ) const {
        return GetSetting( dbname, f_id, prop ); }

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    idt  f_res_id;
};

inline idt recGetCurrentResearcher() {
    recUser user( recGetCurrentUser() );
    return user.FGetResID();
}

#endif // RECUSER_H
