/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recVersion.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Version record header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#ifndef RECVERSION_H
#define RECVERSION_H

#include <rec/recDatabase.h>


extern const int recVersionMajor;
extern const int recVersionMinor;
extern const int recVersionRevision;
extern const int recVersionTest;
extern const wxChar* recVersionStr;


class recVersion : public recDb 
{
public:
	int  f_major;
	int  f_minor;
    int  f_revision;
    int  f_test;

    recVersion() {}
    recVersion( id_t id ) : recDb(id) { Read(); }
    recVersion( const recVersion& ver );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Version" );

    bool IsEqual( int major, int minor, int revision, int test = 0 ) const;
    bool IsMoreThan( int major, int minor, int revision, int test = 0 ) const;
    bool IsLessThan( int major, int minor, int revision, int test = 0 ) const;
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recVersion& r1, const recVersion& r2 )
{
    return
        r1.f_major    == r2.f_major    && 
        r1.f_minor    == r2.f_minor    &&
        r1.f_revision == r2.f_revision &&
        r1.f_test     == r2.f_test;
}

inline bool operator==( const recVersion& r1, const recVersion& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recVersion& r1, const recVersion& r2 )
{
    return !(r1 == r2);
}

#endif // RECVERSION_H
