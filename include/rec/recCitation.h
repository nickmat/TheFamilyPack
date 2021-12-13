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

class recCitation : public recDbT<recCitation>
{
    idt f_higher_id;
    idt f_ref_id;
    int f_ref_seq;
    idt f_rep_id;
    wxString f_comment;

public:
    static constexpr const char* s_tablename = "Citation";

    recCitation() : f_higher_id(0), f_ref_id(0), f_ref_seq(0), f_rep_id(0) {}
    recCitation( idt id ) : recDbT( id ) { Read(); }
    recCitation( const recCitation& source );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recCitation& r2 ) const;

    idt FGetHigherID() const { return f_higher_id; }
    idt FGetRefID() const { return f_ref_id; }
    idt FGetRefSeq() const { return f_ref_seq; }
    idt FGetRepID() const { return f_rep_id; }
    wxString FGetComment() const { return f_comment; }

    void FSetHigherID( idt highID ) { f_higher_id = highID; }
    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetRefSeq( idt ref_seq ) { f_ref_seq = ref_seq; }
    void FSetRepID( idt repID ) { f_rep_id = repID; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }

    static wxString GetIdStr( idt citID ) { return wxString::Format( "Ci" ID, citID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    int GetNextRefSequence( idt refID ) const;

    static recCitationPartVec GetPartList( idt citID );
    recCitationPartVec GetPartList() const { return GetPartList( f_id ); }

    static wxString GetCitationStr( idt citID );
    wxString GetCitationStr() const;

    static void Renumber( idt id, idt to_id );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt citID, Coverage limit = Coverage::user );
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

class recRepository : public recDbT< recRepository>
{
    wxString f_name;
    wxString f_note;
    idt f_con_list_id;

public:
    static constexpr const char* s_tablename = "Repository";

    recRepository() : f_con_list_id(0) {}
    recRepository( idt id ) : recDbT( id ) { Read(); }
    recRepository( const recRepository& source );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recRepository& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetNote() const { return f_note; }
    idt FGetConListID() const { return f_con_list_id; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetConListID( idt clID ) { f_con_list_id = clID; }

    static wxString GetIdStr( idt repID ) { return wxString::Format( "Ar" ID, repID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recRepositoryVec GetFullList();

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void DeleteIfOrphaned( idt cptID, Coverage limit = Coverage::user );
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

class recCitationPart : public recDbT< recCitationPart>
{
    idt f_cit_id;
    idt f_type_id;
    wxString f_val;
    int f_cit_seq;
    wxString f_comment;

public:
    static constexpr const char* s_tablename = "CitationPart";

    recCitationPart() : f_cit_id(0), f_type_id(0), f_cit_seq(0) {}
    recCitationPart( idt id ) : recDbT( id ) { Read(); }
    recCitationPart( const recCitationPart& source );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recCitationPart& r2 ) const;

    idt FGetCitID() const { return f_cit_id; }
    idt FGetTypeID() const { return f_type_id; }
    wxString FGetValue() const { return f_val; }
    int FGetCitSeq() const { return f_cit_seq; }
    wxString FGetComment() const { return f_comment; }

    void FSetCitID( idt citID ) { f_cit_id = citID; }
    void FSetTypeID( idt type_id ) { f_type_id = type_id; }
    void FSetValue( const wxString& val ) { f_val = val; }
    void FSetCitSeq( int seq ) { f_cit_seq = seq; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }

    static wxString GetIdStr( idt repID ) { return wxString::Format( "CiP" ID, repID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    int GetNextCitationSeq( idt citID ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
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

class recCitationPartType : public recDbT< recCitationPartType>
{
    wxString  f_name;
    int f_style;
    wxString f_comment;

public:
    static constexpr const char* s_tablename = "CitationPartType";

    recCitationPartType() : f_style(0) {}
    recCitationPartType( idt id ) : recDbT(id) { Read(); }
    recCitationPartType( const recCitationPartType& at );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recCitationPartType& r2 ) const;

    wxString FGetName() const { return f_name; }
    int FGetStyle() const { return f_style; }
    wxString FGetComment() const { return f_comment; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetStyle( int style ) { f_style = style; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }

    static wxString GetIdStr( idt ciptID ) { return wxString::Format( "CiPT" ID, ciptID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetStr( idt id );

    static recCitationPartTypeVec GetList();

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void DeleteIfOrphaned( idt cptID, Coverage limit = Coverage::user );
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
