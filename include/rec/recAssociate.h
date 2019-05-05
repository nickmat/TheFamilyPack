/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recAssociate.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Associate record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018 ~ 2019, Nick Matthews.
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

#ifndef RECASSOCIATE_H
#define RECASSOCIATE_H

#include <rec/recDatabase.h>

class recAssociate : public recDb
{
public:

    recAssociate() {}
    recAssociate( idt id ) : recDb( id ) { Read(); }
    recAssociate( const recAssociate& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Associate" );
    bool Equivalent( const recAssociate& r2 ) const { return f_path == r2.f_path; }

    wxString FGetPath() const { return f_path; }

    void FSetPath( const wxString& path ) { f_path = path; }

    static wxString GetIdStr( idt assID ) { return wxString::Format( "A" ID, assID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetPath( idt assID );

private:
    wxString f_path;
};

inline bool operator==( const recAssociate& r1, const recAssociate& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recAssociate& r1, const recAssociate& r2 )
{
    return !( r1 == r2 );
}


#endif // RECASSOCIATE_H
