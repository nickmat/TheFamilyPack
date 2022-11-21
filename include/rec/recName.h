/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recName.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Name, NamePart, NamePartType and NameStyle records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22 November 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

#ifndef RECNAME_H
#define RECNAME_H

#include <vector>
#include <rec/recDatabase.h>

class recName;
class recNameStyle;
class recNamePart;
class recNamePartType;
typedef std::vector< recName >          recNameVec;
typedef std::vector< recNameStyle >     recNameStyleVec;
typedef std::vector< recNamePart >      recNamePartVec;
typedef std::vector< recNamePartType >  recNamePartTypeVec;


enum recStdNameType  // These match the create.sql file
{
    NAME_TYPE_Unstated   = 0,
    NAME_TYPE_Given_name = -1,
    NAME_TYPE_Surname    = -2,
    NAME_TYPE_Post_name  = -3,
    NAME_TYPE_Max        = 4
};

//============================================================================
//-------------------------[ recName ]----------------------------------------
//============================================================================

class recName : public recDbT<recName>
{
public:
    static constexpr const char* s_tablename = "Name";
    static constexpr recTable s_table = recTable::Name;

    idt  f_ind_id;
    idt  f_per_id;
    idt  f_style_id;
    int  f_sequence;

    recName() : f_ind_id(0), f_per_id(0), f_style_id(0), f_sequence(0) {}
    recName( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recName( const recName& name );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recName& r2 ) const;

    idt FGetIndID() const { return f_ind_id; }
    idt FGetPerID() const { return f_per_id; }
    idt FGetTypeID() const { return f_style_id; } // Depreciated
    idt FGetStyleID() const { return f_style_id; }
    int FGetSequence() const { return f_sequence; }

    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetTypeID( idt typeID ) { f_style_id = typeID; }  // Depreciated
    void FSetStyleID( idt typeID ) { f_style_id = typeID; }
    void FSetSequence( int seq ) { f_sequence = seq; }

    static wxString GetIdStr( idt nameID ) { return wxString::Format( "N" ID, nameID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt GetIndID( idt nameID, const wxString& dbname = "Main" );
    static idt GetPerID( idt nameID, const wxString& dbname = "Main" );

    static idt CreateName( const wxString& nameStr, idt style = 0 );
    static idt Create( const wxString& nameStr, idt indID, idt perID, idt style, int* pseq );

    int AddNameParts( const wxString& nameStr, recStdNameType type = NAME_TYPE_Unstated, int seq = 0 ) const;
    int AddNamePart( const wxString& nameStr, recStdNameType type, int seq ) const;

    static idt GetDefaultNameID( idt indID, idt perID, const wxString& dbname = "Main" );
    static wxString GetDefaultNameStr( idt indID, idt perID, const wxString& dbname = "Main" );
    static recNameVec GetNames( idt indID, idt perID, const wxString& dbname = "Main" );

    static wxString GetNameStr( idt id, const wxString& dbname = "Main" );
    wxString GetNameStr( const wxString& dbname = "Main" ) const {
        return GetNameStr( f_id, dbname ); }

    // Depreciated, use GetStyleStr
    static wxString GetTypeStr( idt id, const wxString& dbname = "Main" ) {
        return GetStyleStr( id, dbname );
    }
    // Depreciated, use GetStyleStr
    wxString GetTypeStr( const wxString& dbname = "Main" ) const {
        return GetStyleStr( dbname );
    }
 
    static wxString GetStyleStr( idt id, const wxString& dbname = "Main" );
    wxString GetStyleStr( const wxString& dbname = "Main" ) const;

    static recIdVec GetNamePartListID( idt namID, const wxString& dbname = "Main" );
    recIdVec GetNamePartListID( const wxString& dbname = "Main" ) const {
        return GetNamePartListID( f_id, dbname );
    }

    static wxString GetNamePartStr( idt nameID, idt partID, const wxString& dbname = "Main" );
    wxString GetNamePartStr( idt partID, const wxString& dbname = "Main" ) const
        { return GetNamePartStr( f_id, partID, dbname ); }
    static wxString GetSurname( idt id, const wxString& dbname = "Main" )
        { return GetNamePartStr( id, NAME_TYPE_Surname, dbname ); }
    wxString GetSurname( const wxString& dbname = "Main" ) const {
        return GetNamePartStr( NAME_TYPE_Surname, dbname ); }

    static wxSQLite3ResultSet GetSurnameIndex( recSurnameGroup sng, const wxString& dbname = "Main" );
    static recNameVec GetNameList( const wxString& surname, recSurnameGroup sng, const wxString& dbname = "Main" );

    static int GetNextSequence( idt indID, idt perID );
    void SetNextSequence() { f_sequence = GetNextSequence( f_ind_id, f_per_id ); }

    static idt CreateIndNameFromPersona( idt indID, idt perID );

    static recNamePartVec GetParts( idt nameID, const wxString& dbname = "Main" );
    recNamePartVec GetParts( const wxString& dbname = "Main" ) const {
        return GetParts( f_id, dbname ); }

    static idt Transfer(
        idt from_namID, const wxString& fromdb,
        idt to_indID, idt to_perID, idt to_namID, const wxString& todb );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt conID, const wxString& dbname = "Main" );
    bool RemoveFromDatabase( const wxString& dbname = "Main" );
};


//============================================================================
//-------------------------[ recNamePart ]------------------------------------
//============================================================================

class recNamePart : public recDbT<recNamePart>
{
public:
    static constexpr const char* s_tablename = "NamePart";
    static constexpr recTable s_table = recTable::NamePart;

    idt       f_name_id;
    idt       f_type_id;
    wxString  f_val;
    int       f_sequence;

    recNamePart() : f_name_id( 0 ), f_type_id( 0 ), f_sequence( 0 ) {}
    recNamePart( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recNamePart( const recNamePart& attr );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recNamePart& r2 ) const;

    idt FGetNameID() const { return f_name_id; }
    idt FGetTypeID() const { return f_type_id; }
    wxString FGetValue() const { return f_val; }
    int FGetNameSeq() const { return f_sequence; }

    void FSetNameID( idt nameID ) { f_name_id = nameID; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetValue( const wxString& val ) { f_val = val; }
    void FSetNameSeq( int nameSeq ) { f_sequence = nameSeq; }

    static wxString GetIdStr( idt npID ) { return wxString::Format( "NP" ID, npID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetValue( idt id, const wxString& dbname = "Main" );
    static wxSQLite3ResultSet GetSurnameList( const wxString& dbname = "Main" );

    int SetNextSequence( const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt conID, const wxString& dbname );
    bool RemoveFromDatabase( const wxString& dbname );
};


//============================================================================
//-------------------------[ recNamePartType ]--------------------------------
//============================================================================

class recNamePartType 
    : public recDbT<recNamePartType>, public recUidT<recNamePartType>
{
public:
    static constexpr const char* s_tablename = "NamePartType";
    static constexpr recTable s_table = recTable::NamePartType;

    static constexpr const char* s_grps[] = { "null", "Name", "Title", "Other" };
    static constexpr size_t s_grps_size = sizeof( s_grps ) / sizeof( char* );

    enum class NPTypeGrp {
        unstated, name, title, other
    };

    NPTypeGrp f_grp;
    wxString  f_name;

    recNamePartType() : f_grp( NPTypeGrp::unstated ) {}
    recNamePartType( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recNamePartType( const recNamePartType& at );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recNamePartType& r2 ) const;

    NPTypeGrp FGetGroup() const { return f_grp; }
    wxString FGetName() const { return f_name; }

    void FSetGroup( NPTypeGrp group ) { f_grp = group; }
    void FSetName( const wxString& name ) { f_name = name; }

    static wxString GetIdStr( idt nptID ) { return wxString::Format( "NPT" ID, nptID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetGroupStr() const;
    static wxString GetGroupStr( idt id, const wxString& dbname = "Main" ) {
        recNamePartType npt( id, dbname );
        return npt.GetGroupStr();
    }

    static StringVec GetGroupList();

    static wxString GetTypeStr( idt id, const wxString& dbname = "Main" );

    static recNamePartTypeVec GetTypeList( const wxString& dbname = "Main" );

    static idt Transfer(
        idt from_nptID, const wxString& fromdb, const wxString& todb );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool DeleteIfOrphaned( idt nptID, const wxString& dbname );
};


//============================================================================
//-------------------------[ recNameStyle ]-----------------------------------
//============================================================================

class recNameStyle : public recDbT<recNameStyle>, public recUidT<recNameStyle>
{
public:
    static constexpr const char* s_tablename = "NameStyle";
    static constexpr recTable s_table = recTable::NameStyle;

    enum Style {
        NS_Default = 0, // Recorded (ie Name as recorded in documents)
        NS_Birth   = -1,
        NS_Married = -2,
        NS_Alias   = -3,
        NS_MAX     = 4
    };

    wxString  f_name;

    recNameStyle() {}
    recNameStyle( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recNameStyle( const recNameStyle& at );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recNameStyle& r2 ) const {
        return f_name == r2.f_name;
    }

    wxString FGetName() const { return f_name; }

    void FSetName( const wxString& name ) { f_name = name; }

    static wxString GetIdStr( idt nsID ) { return wxString::Format( "NS" ID, nsID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetStyleStr( idt id, const wxString& dbname = "Main" );

    static recNameStyleVec GetStyleList( const wxString& dbname = "Main" );

    static idt Transfer(
        idt from_nsID, const wxString& fromdb, const wxString& todb );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static bool DeleteIfOrphaned( idt nsID, const wxString& dbname );
};

#endif // RECNAME_H
