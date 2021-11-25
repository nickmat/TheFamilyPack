/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recCitation.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Citation records header.
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

#ifndef RECCITATION_H
#define RECCITATION_H

#include <rec/recDatabase.h>

class recRepository;
using recRepositoryVec = std::vector<recRepository>;

class recCitationPart;
typedef std::vector< recCitationPart >  recCitationPartVec;

class recCitationPartType;
typedef std::vector< recCitationPartType >  recCitationPartTypeVec;

//============================================================================
//                 recCitation
//============================================================================

class recCitation : public recDb
{
    idt f_ref_id;
    int f_ref_seq;
    idt f_rep_id;
    wxString f_comment;

public:
    recCitation() {}
    recCitation( idt id ) : recDb( id ) { Read(); }
    recCitation( const recCitation& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Citation" );
    bool Equivalent( const recCitation& r2 ) const;

    idt FGetRefId() const { return f_ref_id; }
    idt FGetRefSeq() const { return f_ref_seq; }
    idt FGetRepId() const { return f_rep_id; }
    wxString FGetComment() const { return f_comment; }

    void FSetRefId( idt refID ) { f_ref_id = refID; }
    void FSetRefSeq( idt ref_seq ) { f_ref_seq = ref_seq; }
    void FSetRepId( idt repID ) { f_rep_id = repID; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }

    static wxString GetIdStr( idt citID ) { return wxString::Format( "Ci" ID, citID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recCitationPartVec GetPartList( idt citID );
    recCitationPartVec GetPartList() const { return GetPartList( f_id ); }

    static wxString GetCitationStr( idt citID );
    wxString GetCitationStr() const;
};

inline bool operator==( const recCitation& r1, const recCitation& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recCitation& r1, const recCitation& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recRepository
//============================================================================

class recRepository : public recDb
{
    wxString f_name;
    wxString f_note;
    idt f_con_list_id;

public:
    recRepository() {}
    recRepository( idt id ) : recDb( id ) { Read(); }
    recRepository( const recRepository& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Repository" );
    bool Equivalent( const recRepository& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetNote() const { return f_note; }
    idt FGetConListId() const { return f_con_list_id; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetConListId( idt clID ) { f_con_list_id = clID; }

    static wxString GetIdStr( idt repID ) { return wxString::Format( "Ar" ID, repID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recRepositoryVec GetFullList();
};

inline bool operator==( const recRepository& r1, const recRepository& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recRepository& r1, const recRepository& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recCitationPart
//============================================================================

class recCitationPart : public recDb
{
    idt f_cit_id;
    idt f_type_id;
    wxString f_val;
    int f_cit_seq;
    wxString f_comment;

public:
    recCitationPart() {}
    recCitationPart( idt id ) : recDb( id ) { Read(); }
    recCitationPart( const recCitationPart& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "CitationPart" );
    bool Equivalent( const recCitationPart& r2 ) const;

    idt FGetCitId() const { return f_cit_id; }
    idt FGetTypeId() const { return f_type_id; }
    wxString FGetVal() const { return f_val; }
    int FGetCitSeq() const { return f_cit_seq; }
    wxString FGetComment() const { return f_comment; }

    void FSetCitId( idt citID ) { f_cit_id = citID; }
    void FSetTypeId( idt type_id ) { f_type_id = type_id; }
    void FSetVal( const wxString& val ) { f_val = val; }
    void FSetCitSeq( int seq ) { f_cit_seq = seq; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }
};

inline bool operator==( const recCitationPart& r1, const recCitationPart& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recCitationPart& r1, const recCitationPart& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recCitationPartType
//============================================================================

class recCitationPartType : public recDb
{
    wxString  f_name;
    int f_style;
    wxString f_comment;

public:
    recCitationPartType() {}
    recCitationPartType( idt id ) : recDb(id) { Read(); }
    recCitationPartType( const recCitationPartType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "CitationPartType" );
    bool Equivalent( const recCitationPartType& r2 ) const;

    wxString FGetName() const { return f_name; }
    int FGetStyle() const { return f_style; }
    wxString FGetComment() const { return f_comment; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetStyle( int style ) { f_style = style; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }

    static wxString GetStr( idt id );

    static recCitationPartTypeVec GetList();
};

inline bool operator==( const recCitationPartType& r1, const recCitationPartType& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recCitationPartType& r1, const recCitationPartType& r2 )
{
    return !(r1 == r2);
}

#endif // RECCITATION_H
