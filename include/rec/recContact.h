/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recContact.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Contact record header.
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

#ifndef RECCONTACT_H
#define RECCONTACT_H

#include <rec/recDatabase.h>

class recContactList;
class recContact;
class recContactType;
typedef std::vector< recContactList >  recContactListVec;
typedef std::vector< recContact >  recContactVec;
typedef std::vector< recContactType >  recContactTypeVec;

//============================================================================
//                 recContactList
//============================================================================

class recContactList : public recDb
{
public:
    recContactList() : f_ind_id(0) {}
    recContactList( idt id ) : recDb(id) { Read(); }
    recContactList( const recContactList& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "ContactList" );
    bool Equivalent( const recContactList& r2 ) const { return f_ind_id == r2.f_ind_id; };

    idt FGetIndID() const { return f_ind_id; }

    void FSetIndID( idt indID ) { f_ind_id = indID; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "CL" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recContactVec GetContacts( idt listID );
    recContactVec GetContacts() const { return GetContacts( f_id ); }

    static idt FindIndID( idt indID );

    // Merge in Contacts from target ContactList and then delete it.
    void Assimilate( idt targetID ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    idt  f_ind_id;
};

inline bool operator==( const recContactList& r1, const recContactList& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recContactList& r1, const recContactList& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recContactType
//============================================================================

class recContactType : public recDb
{
public:
    enum Type {
        CT_Unstated = 0,
        CT_Address = -1,
        CT_Telephone = -2,
        CT_Mobile = -3,
        CT_Email = -4,
        CT_Website = -5,
        CT_Fax = -6,
        CT_MAX = 7
    };

    recContactType() {}
    recContactType( idt id ) : recDb(id) { Read(); }
    recContactType( const recContactType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "ContactType" );
    bool Equivalent( const recContactType& r2 ) const { return f_name == r2.f_name; };

    wxString FGetName() const { return f_name; }

    void FSetName( const wxString name ) { f_name = name; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "CT" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetTypeStr( idt typeID );

    static recContactTypeVec GetList();

private:
    wxString  f_name;
};

inline bool operator==( const recContactType& r1, const recContactType& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recContactType& r1, const recContactType& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recContact
//============================================================================

class recContact : public recDb
{
public:

    recContact() {}
    recContact( idt id ) : recDb(id) { Read(); }
    recContact( const recContact& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Contact" )
    bool Equivalent( const recContact& r2 ) const;

    idt FGetTypeID() const { return f_type_id; }
    idt FGetListID() const { return f_list_id; }
    wxString FGetValue() const { return f_val; }

    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetListID( idt listID ) { f_list_id = listID; }
    void FSetValue( const wxString& value ) { f_val = value; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "C" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetTypeStr() const { return recContactType::GetTypeStr( f_type_id ); }
    wxString GetHtmlValue( const wxString prefixHref = wxEmptyString ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    idt      f_type_id;
    idt      f_list_id;
    wxString f_val;
};

inline bool operator==( const recContact& r1, const recContact& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recContact& r1, const recContact& r2 )
{
    return !(r1 == r2);
}


#endif // RECCONTACT_H
