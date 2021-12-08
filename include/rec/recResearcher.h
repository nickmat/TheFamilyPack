/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Researcher record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     4th December 2021
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

#ifndef RECRESEARCHER_H
#define RECRESEARCHER_H

#include <rec/recDatabase.h>
#include <rec/recContact.h>

class recResearcher;
typedef std::vector< recResearcher >  recResearcherVec;


//============================================================================
//                 recResearcher
//============================================================================

class recResearcher : public recDb
{
public:
    recResearcher() : f_con_list_id(0) {}
    recResearcher( idt id ) : recDb(id) { Read(); }
    recResearcher( const recResearcher& res );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Researcher" )
    bool Equivalent( const recResearcher& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetComments() const { return f_comments; }
    idt FGetConListID() const { return f_con_list_id; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetComments( const wxString& com ) { f_comments = com; }
    void FSetConListID( idt clID ) { f_con_list_id = clID; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "Re" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetNameStr( idt resID );

    idt GetUserID() const;
    wxString GetUserIdStr() const;
    recContactVec GetContacts() const { return recContactList::GetContacts( f_con_list_id ); }

    static recResearcherVec GetResearchers( Coverage filter = Coverage::all );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    wxString  f_name;
    wxString  f_comments;
    idt       f_con_list_id;
};


inline bool operator==( const recResearcher& r1, const recResearcher& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recResearcher& r1, const recResearcher& r2 )
{
    return !(r1 == r2);
}

#endif // RECRESEARCHER_H
