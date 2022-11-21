/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recContact.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Contact record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25 February 2011
 * Copyright:   Copyright (c) 2011..2022, Nick Matthews.
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

class recContactList : public recDbT<recContactList>
{
public:
    static constexpr const char* s_tablename = "ContactList";
    static constexpr recTable s_table = recTable::ContactList;

    recContactList() : f_ind_id(0) {}
    recContactList( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname); }
    recContactList( const recContactList& at );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recContactList& r2 ) const {
        return f_ind_id == r2.f_ind_id;
    }

    idt FGetIndID() const { return f_ind_id; }

    void FSetIndID( idt indID ) { f_ind_id = indID; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "CL" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recContactVec GetContacts( idt listID, const wxString& dbname = "Main" );
    recContactVec GetContacts( const wxString& dbname = "Main" ) const {
        return GetContacts( f_id, dbname ); }

    static recIdVec GetContactIDs( idt listID, const wxString& dbname = "Main" );
    recIdVec GetContactIDs( const wxString& dbname = "Main" ) const {
        return GetContactIDs( f_id, dbname );
    }

    static idt FindIndID( idt indID, const wxString& dbname = "Main" );

    // Merge in Contacts from target ContactList and then delete it.
    void Assimilate( idt targetID, const wxString& dbname = "Main" ) const;

    static idt Transfer(
        idt from_clID, const wxString& fromdb, idt to_clID, const wxString& todb );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt clID, const wxString& dbname );

private:
    idt  f_ind_id;
};

//============================================================================
//                 recContactType
//============================================================================

class recContactType : public recDbT<recContactType>, public recUidT<recContactType>
{
public:
    static constexpr const char* s_tablename = "ContactType";
    static constexpr recTable s_table = recTable::ContactType;

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
    recContactType( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recContactType( const recContactType& at );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recContactType& r2 ) const;

    wxString FGetName() const { return f_name; }

    void FSetName( const wxString name ) { f_name = name; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "CT" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetTypeStr( idt typeID, const wxString& dbname = "Main" );

    static recContactTypeVec GetList( const wxString& dbname = "Main" );

    static idt Transfer( idt from_ctID, const wxString& fromdb, const wxString& todb );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool DeleteIfOrphaned( idt ctID, const wxString& dbname = "Main" );

private:
    wxString f_name;
};


//============================================================================
//                 recContact
//============================================================================

class recContact : public recDbT<recContact>
{
public:
    static constexpr const char* s_tablename = "Contact";
    static constexpr recTable s_table = recTable::Contact;

    recContact() : f_type_id(0), f_list_id(0), f_list_seq(0) {}
    recContact( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recContact( const recContact& source );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recContact& r2 ) const;

    idt FGetTypeID() const { return f_type_id; }
    idt FGetListID() const { return f_list_id; }
    int FGetListSeq() const { return f_list_seq; }
    wxString FGetValue() const { return f_val; }

    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetListID( idt listID ) { f_list_id = listID; }
    void FSetListSeq( idt seq ) { f_list_seq = seq; }
    void FSetValue( const wxString& value ) { f_val = value; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "C" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetTypeStr( const wxString& dbname = "Main" ) const {
        return recContactType::GetTypeStr( f_type_id, dbname ); }
    wxString GetHtmlValue( const wxString prefixHref = wxEmptyString ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt conID, const wxString& dbname );
    bool RemoveFromDatabase( const wxString& dbname );

private:
    idt      f_type_id;
    idt      f_list_id;
    int      f_list_seq;
    wxString f_val;
};


#endif // RECCONTACT_H
