/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recVersion.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Version record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
 * Copyright:   Copyright (c) 2010 ~ 2019, Nick Matthews.
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


// Defined in recUpgrade.cpp file
extern const int recVerMajor;
extern const int recVerMinor;
extern const int recVerRev;
extern const int recVerTest;
extern const wxStringCharType* recVerStr;

extern const int recMediaVerMajor;
extern const int recMediaVerMinor;
extern const int recMediaVerRev;
extern const int recMediaVerTest;
extern const wxStringCharType* recMediaVerStr;

extern bool recDoFullUpgrade();
extern bool recDoMediaUpgrade();


class recVersion : public recDb
{
public:
    recVersion() {}
    recVersion( idt id ) : recDb( id ) { Read(); }
    recVersion( const recVersion& ver );
    bool Read() override;

    int FGetMajor() const { return f_major; }
    int FGetMinor() const { return f_minor; }
    int FGetRevision() const { return f_revision; }
    int FGetTest() const { return f_test; }

    /*! Return the database full version string.
    */
    static wxString GetVersionStr( recDb::DatabaseType type = recDb::DT_Full );

    /*! Check whether the database version is compatable with the program
     *  version. If not, handle updating the database and return true. 
     *  Or, if it is not possible to update, return false.
     */
    static DatabaseType Manage();

    bool IsEqual( 
        int major, int minor = -1, int revision = -1, int test = -1 ) const;
    bool IsMoreThan( 
        int major, int minor = -1, int revision = -1, int test = -1 ) const;
    bool IsLessThan( 
        int major, int minor = -1, int revision = -1, int test = -1 ) const;

private:
    void Clear() override;
    void Save() override { wxASSERT( false ); }
    TABLE_NAME_MEMBERS( "Version" );

    int  f_major;
    int  f_minor;
    int  f_revision;
    int  f_test;
};

#endif // RECVERSION_H
