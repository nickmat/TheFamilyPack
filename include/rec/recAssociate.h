/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recAssociate.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Associate record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018..2022, Nick Matthews.
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

class recAssociate;
typedef std::vector< recAssociate >  recAssociateVec;

class recAssociate : public recDbT<recAssociate>
{
public:
    static constexpr const char* s_tablename = "Associate";

    recAssociate() {}
    recAssociate( idt id, const wxString& extdb = "Main" ) : recDbT( id ) { Read( extdb ); }
    recAssociate( const recAssociate& source );

    void Clear();
    void Save( const wxString& extdb = "Main" );
    bool Read( const wxString& extdb = "Main" );
    bool Equivalent( const recAssociate& r2 ) const { return f_path == r2.f_path; }

    wxString FGetPath() const { return f_path; }
    wxString FGetComment() const { return f_comment; }

    void FSetPath( const wxString& path ) { f_path = path; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }

    static wxString GetIdStr( idt assID ) { return wxString::Format( "A" ID, assID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( const wxString& path, const wxString& comment = "" );

    /* Returns the attached database schema name.
    *  If the database is not currently attached, will attempt to attach first.
    */
    static wxString GetAttachedName( idt assID, const wxString& extdb );

    static recAssociateVec GetList( const wxString& extdb = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    wxString f_path;
    wxString f_comment;
};

#endif // RECASSOCIATE_H
