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
    idt     f_res_id;
    idt     f_fam_id;

    recUser() {}
    recUser( idt id ) : recDb(id) { Read(); }
    recUser( const recUser& user );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "User" );

};

inline bool recEquivalent( const recUser& r1, const recUser& r2 )
{
    return
        r1.f_res_id == r2.f_res_id &&
        r1.f_fam_id == r2.f_fam_id;
}

inline bool operator==( const recUser& r1, const recUser& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recUser& r1, const recUser& r2 )
{
    return !(r1 == r2);
}


#endif // RECUSER_H
