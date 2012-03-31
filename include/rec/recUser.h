/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recUser.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 User record header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     25 February 2011
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2011, Nick Matthews.
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

class recUser;
typedef std::vector< recUser >  recUserVec;

//============================================================================
//                 recUser
//============================================================================

class recUser : public recDb
{
public:
    recUser() {}
    recUser( idt id ) : recDb(id) { Read(); }
    recUser( const recUser& user );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "User" )
    bool Equivalent( const recUser& r2 ) const;

    idt FGetResID() const { return f_res_id; }

    void FSetResID( idt resID ) { f_res_id = resID; }

    static wxString GetIdStr( idt userID ) { return wxString::Format( "U"ID, userID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

private:
    idt  f_res_id;
};

inline bool operator==( const recUser& r1, const recUser& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recUser& r1, const recUser& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recUserSetting
//============================================================================

class recUserSetting : public recDb
{
public:
    enum Property {
        UP_Unstated = 0,
        UP_HomeScreen,
        UP_MAX
    };

    recUserSetting() {}
    recUserSetting( idt id ) : recDb(id) { Read(); }
    recUserSetting( const recUserSetting& user );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "UserSetting" )
    bool Equivalent( const recUserSetting& r2 ) const;

    idt FGetUserID() const { return f_user_id; }
    Property FGetProperty() const { return f_property; }
    wxString FGetValue() const { return f_val; }

    void FSetUserID( idt userID ) { f_user_id = userID; }
    void FSetProperty( Property up ) { f_property = up; }
    void FSetValue( const wxString& val ) { f_val = val; }

private:
    idt      f_user_id;
    Property f_property;
    wxString f_val;
};

inline bool operator==( const recUserSetting& r1, const recUserSetting& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recUserSetting& r1, const recUserSetting& r2 )
{
    return !(r1 == r2);
}


#endif // RECUSER_H
