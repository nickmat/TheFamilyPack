/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recArchive.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Archive database records header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
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

#ifndef RECARCHIVE_H
#define RECARCHIVE_H

#include <rec/recDatabase.h>


//============================================================================
//                 recRepository
//============================================================================

class recRepository : public recDb
{
public:
    wxString  f_name;
    wxString  f_access;
    wxString  f_comments;

    recRepository() {}
    recRepository( idt id ) : recDb(id) { Read(); }
    recRepository( const recRepository& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Repository" );
};

inline bool recEquivalent( const recRepository& r1, const recRepository& r2 )
{
    return
        r1.f_name     == r2.f_name    &&
        r1.f_access   == r2.f_access  &&
        r1.f_comments == r2.f_comments;
}

inline bool operator==( const recRepository& r1, const recRepository& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recRepository& r1, const recRepository& r2 )
{
    return !(r1 == r2);
}


//============================================================================
//                 recRepositorySource
//============================================================================

class recRepositorySource : public recDb
{
public:
    idt      f_repos_id;
    idt      f_source_id;
    wxString  f_call_num;
    wxString  f_descrip;

    recRepositorySource() {}
    recRepositorySource( idt id ) : recDb(id) { Read(); }
    recRepositorySource( const recRepositorySource& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "RepositorySource" );
};

inline bool recEquivalent( const recRepositorySource& r1, const recRepositorySource& r2 )
{
    return
        r1.f_repos_id  == r2.f_repos_id  &&
        r1.f_source_id == r2.f_source_id &&
        r1.f_call_num  == r2.f_call_num  &&
        r1.f_descrip   == r2.f_descrip;
}

inline bool operator==( const recRepositorySource& r1, const recRepositorySource& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recRepositorySource& r1, const recRepositorySource& r2 )
{
    return !(r1 == r2);
}



#endif // RECARCHIVE_H
