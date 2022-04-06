/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recCitation.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Citation records header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
 * Copyright:   Copyright (c) 2021..2022, Nick Matthews.
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
    wxString f_uid;
    long f_changed;

public:
    static constexpr const char* s_tablename = "Citation";

    recCitation() : f_higher_id(0), f_ref_id(0), f_ref_seq(0), f_rep_id(0), f_changed(0) {}
    recCitation( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recCitation( const recCitation& source );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recCitation& r2 ) const;

    idt FGetHigherID() const { return f_higher_id; }
    idt FGetRefID() const { return f_ref_id; }
    idt FGetRefSeq() const { return f_ref_seq; }
    idt FGetRepID() const { return f_rep_id; }
    wxString FGetComment() const { return f_comment; }
    wxString FGetUid() const { return f_uid; }
    long FGetChanged() const { return f_changed; }

    void FSetHigherID( idt highID ) { f_higher_id = highID; }
    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetRefSeq( idt ref_seq ) { f_ref_seq = ref_seq; }
    void FSetRepID( idt repID ) { f_rep_id = repID; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }
    void FSetUid( const wxString& uid ) { f_uid = uid; }
    void FSetChanged( long jdn ) { f_changed = jdn; }

    static wxString GetIdStr( idt citID ) { return wxString::Format( "Ci" ID, citID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    int GetNextRefSequence( idt refID ) const;

    static recCitationPartVec GetPartList( idt citID, const wxString& dbname = "Main" );
    recCitationPartVec GetPartList( const wxString& dbname = "Main" ) const {
        return GetPartList( f_id, dbname ); }

    static wxString GetCitationStr( idt citID, const wxString& dbname = "Main" );
    wxString GetCitationStr( const wxString& dbname = "Main" ) const;

    static void Renumber( idt id, idt to_id );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt citID, const wxString& dbname );
};


//============================================================================
//                 recRepository
//============================================================================

class recRepository : public recDbT< recRepository>
{
    wxString f_name;
    wxString f_note;
    idt      f_con_list_id;
    wxString f_uid;
    long     f_changed;

public:
    static constexpr const char* s_tablename = "Repository";

    recRepository() : f_con_list_id(0), f_changed(0) {}
    recRepository( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recRepository( const recRepository& source );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recRepository& r2 ) const;

    wxString FGetName() const { return f_name; }
    wxString FGetNote() const { return f_note; }
    idt FGetConListID() const { return f_con_list_id; }
    wxString FGetUid() const { return f_uid; }
    long FGetChanged() const { return f_changed; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetConListID( idt clID ) { f_con_list_id = clID; }
    void FSetUid( const wxString& uid ) { f_uid = uid; }
    void FSetChanged( long jdn ) { f_changed = jdn; }

    static wxString GetIdStr( idt repID ) { return wxString::Format( "Ar" ID, repID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recRepositoryVec GetFullList( const wxString& dbname = "Main" );

    wxString GetChangedDate() const;
    static wxString GetChangedDate( idt refID, const wxString& dbname );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void DeleteIfOrphaned( idt cptID, const wxString& dbname );
};


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
    recCitationPart( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recCitationPart( const recCitationPart& source );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
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

    static void RemoveFromDatabase( idt conID, const wxString& dbname );
    void RemoveFromDatabase( const wxString& dbname );
};


//============================================================================
//                 recCitationPartType
//============================================================================

class recCitationPartType : public recDbT< recCitationPartType>
{
    wxString f_name;
    int      f_style;
    wxString f_comment;
    wxString f_uid;
    long     f_changed;

public:
    static constexpr const char* s_tablename = "CitationPartType";

    recCitationPartType() : f_style(0) {}
    recCitationPartType( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recCitationPartType( const recCitationPartType& at );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recCitationPartType& r2 ) const;

    wxString FGetName() const { return f_name; }
    int FGetStyle() const { return f_style; }
    wxString FGetComment() const { return f_comment; }
    wxString FGetUid() const { return f_uid; }
    long FGetChanged() const { return f_changed; }

    void FSetName( const wxString& name ) { f_name = name; }
    void FSetStyle( int style ) { f_style = style; }
    void FSetComment( const wxString& comment ) { f_comment = comment; }
    void FSetUid( const wxString& uid ) { f_uid = uid; }
    void FSetChanged( long jdn ) { f_changed = jdn; }

    static wxString GetIdStr( idt ciptID ) { return wxString::Format( "CiPT" ID, ciptID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetStr( idt id, const wxString& dbname = "Main" );

    static recCitationPartTypeVec GetList( const wxString& dbname = "Main" );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void DeleteIfOrphaned( idt cptID, const wxString& dbname );
};

#endif // RECCITATION_H
