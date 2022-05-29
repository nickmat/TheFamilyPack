/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Researcher record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     4th December 2021
 * Copyright:   Copyright (c) 2021 .. 2022, Nick Matthews.
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

class recResearcher : public recDbT<recResearcher>, public recUidT<recResearcher>
{
public:
    static constexpr const char* s_tablename = "Researcher";

    recResearcher() : f_con_list_id(0) {}
    recResearcher( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recResearcher( const recResearcher& res );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recResearcher& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetComment() const { return f_comment; }
    idt FGetConListID() const { return f_con_list_id; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetComment( const wxString& com ) { f_comment = com; }
    void FSetConListID( idt clID ) { f_con_list_id = clID; }

    static wxString GetIdStr( idt resID ) { return wxString::Format( "Re" ID, resID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetNameStr( idt resID, const wxString& dbname = "Main" );

    idt GetUserID( const wxString& dbname = "Main" ) const;
    wxString GetUserIdStr( const wxString& dbname = "Main" ) const;
    recContactVec GetContacts( const wxString& dbname = "Main" ) const {
        return recContactList::GetContacts( f_con_list_id, dbname ); }

    static recResearcherVec GetResearchers( Coverage filter, const wxString& dbname = "Main" );

    static idt recResearcher::Transfer(
        idt from_resID, const wxString& fromdb, const wxString& todb );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static bool DeleteIfOrphaned( idt resID, const wxString& dbname );

private:
    wxString  f_name;
    wxString  f_comment;
    idt       f_con_list_id;
};


#endif // RECRESEARCHER_H
