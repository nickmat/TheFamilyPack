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
//                 recArchive
//============================================================================

class recArchive : public recDb
{
    wxString  f_name;
    wxString  f_note;
    idt       f_con_list_id;

public:
    recArchive() {}
    recArchive( idt id ) : recDb(id) { Read(); }
    recArchive( const recArchive& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Archive" );
    bool Equivalent( const recArchive& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetNote() const { return f_note; }
    idt FGetConListId() const { return f_con_list_id; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetConListId( idt con_list_id ) { f_con_list_id = con_list_id; }

    static wxString GetIdStr( idt arcID ) { return wxString::Format( "Ar" ID, arcID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }
};

inline bool operator==( const recArchive& r1, const recArchive& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recArchive& r1, const recArchive& r2 )
{
    return !(r1 == r2);
}


//============================================================================
//                 recArchiveReference
//============================================================================

class recArchiveReference : public recDb
{
    idt      f_archive_id;
    idt      f_ref_id;
    wxString f_call_num;
    wxString f_note;

public:
    recArchiveReference() {}
    recArchiveReference( idt id ) : recDb(id) { Read(); }
    recArchiveReference( const recArchiveReference& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "ArchiveReference" );
    bool Equivalent( const recArchiveReference& r2 ) const;

    idt FGetArchiveId() const { return f_archive_id; }
    idt FGetRefId() const { return f_ref_id; }
    wxString FGetCallNum() const { return f_call_num; }
    wxString FGetNote() const { return f_note; }

    void FSetArchiveId( idt archive_id ) { f_archive_id = archive_id; }
    void FSetRefId( idt ref_id ) { f_ref_id = ref_id; }
    void FSetCallNum( const wxString& call_num ) { f_call_num = call_num; }
    void FSetNote( const wxString& note ) { f_note = note; }
};

inline bool operator==( const recArchiveReference& r1, const recArchiveReference& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recArchiveReference& r1, const recArchiveReference& r2 )
{
    return !(r1 == r2);
}


#endif // RECARCHIVE_H
