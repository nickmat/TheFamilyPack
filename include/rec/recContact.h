/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recContact.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Contact record header.
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

#ifndef RECCONTACT_H
#define RECCONTACT_H

#include <rec/recDatabase.h>

class recContact;
class recContactType;
typedef std::vector< recContact >  recContactVec;
typedef std::vector< recContactType >  recContactTypeVec;

//============================================================================
//                 recContact
//============================================================================

class recContact : public recDb
{
public:
    idt     f_type_id;
    idt     f_repos_id;
    idt     f_res_id;
    idt     f_ind_id;
    wxString f_val;

    recContact() {}
    recContact( idt id ) : recDb(id) { Read(); }
    recContact( const recContact& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Contact" );

};

inline bool recEquivalent( const recContact& r1, const recContact& r2 )
{
    return
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_repos_id == r2.f_repos_id &&
        r1.f_res_id   == r2.f_res_id   &&
        r1.f_ind_id   == r2.f_ind_id   &&
        r1.f_val      == r2.f_val;
}

inline bool operator==( const recContact& r1, const recContact& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recContact& r1, const recContact& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recContactType
//============================================================================

class recContactType : public recDb
{
public:
    wxString  f_name;

    recContactType() {}
    recContactType( idt id ) : recDb(id) { Read(); }
    recContactType( const recContactType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "ContactType" );

    static wxString GetStr( idt id );

    static recContactTypeVec GetList();
};

inline bool recEquivalent( const recContactType& r1, const recContactType& r2 )
{
    return
        r1.f_name == r2.f_name;
}

inline bool operator==( const recContactType& r1, const recContactType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recContactType& r1, const recContactType& r2 )
{
    return !(r1 == r2);
}


//============================================================================
//                 recResearcher
//============================================================================

class recResearcher : public recDb
{
public:

    recResearcher() {}
    recResearcher( idt id ) : recDb(id) { Read(); }
    recResearcher( const recResearcher& res );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Researcher" )
    bool Equivalent( const recResearcher& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetComment() const { return f_comments; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetComments( const wxString& com ) { f_comments = com; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "Re"ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

private:
    wxString  f_name;
    wxString  f_comments;
};


inline bool operator==( const recResearcher& r1, const recResearcher& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recResearcher& r1, const recResearcher& r2 )
{
    return !(r1 == r2);
}

#endif // RECCONTACT_H
