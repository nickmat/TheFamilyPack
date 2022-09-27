/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recHelper.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     General helper classes and functions
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     30th April 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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

#ifndef REC_RECHELPER_H
#define REC_RECHELPER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include <wx/wxsqlite3.h>

using idt = long long;

// Some helpful defines
#define ID              "%lld"
#define GET_ID( id )    ((long long)(id).GetValue())
#define UTF8_(s)        ((const char*)(s).utf8_str())
#define BOOL_(i)        ( (i) ? 1 : 0 )

// Useful defines placed here for convenience.
using  StringVec = std::vector< wxString >;
using  StringMap = std::map< wxString, wxString >;
using  IntVec = std::vector< int >;
using  DoubleVec = std::vector< double >;
using  BoolVec = std::vector< bool >;

using  recIdStringMap = std::map< idt, wxString >;
using  recIdVec = std::vector< idt >;

struct recExternalDb
{
    wxString       dbfilename; // Absolute filename
    StringVec      assdbs;     // List of dbname's associated to this external db.
    recIdStringMap assIdMap;   // Map the associate ID to the dbname.
};

using recExternalDbMap = std::map<wxString,recExternalDb>;

// This class is used when we want to compare two lists that have been
// obtained by separate routes. The normal pattern is that either
// first and second are the same or one of them is zero.
class recCheckID {

    idt m_firstID, m_secondID;

public:
    recCheckID() {}
    recCheckID( idt id1, idt id2 ) : m_firstID(id1), m_secondID(id2) {}

    idt GetFirstID() const { return m_firstID; }
    idt GetSecondID() const { return m_secondID; }

    void SetFirstID( idt id ) { m_firstID = id; }
    void SetSecondID( idt id ) { m_secondID = id; }
    void SetIDs( idt id1, idt id2 ) { m_firstID = id1; m_secondID = id2; }
};
typedef std::vector< recCheckID >  recCheckIdVec;

extern bool recCheckIDsAreEqual( const recCheckIdVec& ids );
extern bool recCheckIDsHaveAdditionalFirst( const recCheckIdVec& ids );
extern bool recCheckIDsHaveAdditionalSecond( const recCheckIdVec& ids );

// Convert the given string into an idt
extern idt recGetID( const wxString& str );
extern idt recGetID( const std::string& str );
extern idt recGetID( const char* str );

// Convert the given commer delimited string into two idt's
// return false if id1 or id2 are nullptr.
extern bool recGetIDs( const wxString& str, idt* id1, idt* id2, idt* id3 = nullptr );

// Convert the given idStr into an idt if it has a matching prefix.
extern idt recIdFromStr( const wxString& prefix, const wxString idStr );

inline wxString recGetStr( idt id ) { return wxString::Format( ID, id ); }

enum class recSplitStrRet { none, number, associate, text };
extern recSplitStrRet recSplitStr( const wxString& str, idt* id1, idt* id2, wxString* dbname );

// Make sure the string ends with a '/'.
inline wxString recMakeDirectoryStr( const wxString& dir ) {
    if( !dir.empty() && *dir.rbegin() != '/' ) {
        return dir + "/";
    }
    return dir;
}

enum class Sex { unstated, male, female, unknown };
extern wxString recGetSexStr( Sex sex );

enum class recTextStyle : int { normal, bold, italic, bolditalic };
constexpr int recTextStyleSize = 4;
extern wxString recGetTextStyleName( recTextStyle style );
extern std::string recStyleHTMLifyStr( const wxString& str, recTextStyle style );

extern std::string recHTMLifyStr( const wxString& str );

inline bool recIsCharDigit( const wxString& str, size_t pos ) {
    return str.size() > pos && wxIsdigit( str.GetChar( pos ) );
}

inline bool recIsCharNumber( const wxString& str, size_t pos ) {
    return str.size() > pos && (wxIsdigit( str.GetChar( pos ) ) || str.GetChar( pos ) == '-');
}

// Surname grouping
enum recSurnameGroup {
    recSG_DefaultInd, recSG_Individual, recSG_Persona, recSG_All, recSG_MAX
};

// Event/Eventa groups
enum recET_GRP_FILTER {
    recET_GRP_FILTER_Unstated    = 0x0001,
    recET_GRP_FILTER_Birth       = 0x0002,
    recET_GRP_FILTER_NrBirth     = 0x0004,
    recET_GRP_FILTER_FamUnion    = 0x0008,
    recET_GRP_FILTER_FamOther    = 0x0010,
    recET_GRP_FILTER_Death       = 0x0020,
    recET_GRP_FILTER_NrDeath     = 0x0040,
    recET_GRP_FILTER_Other       = 0x0080,
    recET_GRP_FILTER_Personal    = 0x0100,
    recET_GRP_FILTER_Relation    = 0x0200,
    recET_GRP_FILTER_FamRelation = 0x0400,

    recET_GRP_FILTER_None        = 0x0000,
    recET_GRP_FILTER_All         = 0x07ff,
    recET_GRP_FILTER_AllValid    = 0x07fe,
    recET_GRP_FILTER_Family = (
        recET_GRP_FILTER_FamUnion |
        recET_GRP_FILTER_FamOther |
        recET_GRP_FILTER_FamRelation
    )
};

enum class recEventTypeGrp {
    unstated,     // 0
    birth,        // 1
    nr_birth,     // 2
    fam_union,    // 3
    fam_other,    // 4
    death,        // 5
    nr_death,     // 6
    other,        // 7
    personal,     // 8
    relation,     // 9
    fam_relation, // 10
    max           // 11
};

inline recET_GRP_FILTER recEventTypeGrpToFilter( recEventTypeGrp grp ) { return  recET_GRP_FILTER(1 << unsigned(grp)); }

enum recEntity {
    recENT_NULL,
    recENT_Individual,
    recENT_Family,
    recENT_Event,
    recENT_Role,
    recENT_Date,
    recENT_Place,
    recENT_Name,
    recENT_Reference,
    recENT_Persona,
    recENT_Eventa,
    recENT_Media,
    recENT_Gallery,
    recENT_MAX
};

// Used for searching for records with binary fields
enum TriLogic { TRILOGIC_false, TRILOGIC_true, TRILOGIC_both };

// Create a string list of ID strings for a given record type
// ie "Pa12, Pa34, Pa56" from a recIdVec
template <class rec>
wxString recIdVecToStr( const recIdVec& ids ) {
    wxString str;
    for( size_t i = 0 ; i < ids.size() ; i++ ) {
        if( i > 0 ) str << ", ";
        str << rec::GetIdStr( ids[i] );
    }
    return str;
}

extern recIdVec recIdVecFromStr( const wxString& prefix, const wxString list );

extern void recIdVecAddIfUnique( recIdVec& vec, idt id );

extern wxString GetBlobFormatStr( const wxMemoryBuffer& buf );

extern std::string recTextFileRead( const std::string& filename );

// Read/Write CSV files

std::istream& recCsvRead( std::istream& in, std::string& str );
std::istream& recCsvRead( std::istream& in, wxString& str );
std::istream& recCsvRead( std::istream& in, idt& id );
std::istream& recCsvRead( std::istream& in, int& num );
std::istream& recCsvRead( std::istream& in, unsigned& num );
std::istream& recCsvRead( std::istream& in, long& num );

std::ostream& recCsvWrite( std::ostream& out, const std::string& str, char term = ',' );
std::ostream& recCsvWrite( std::ostream& out, const wxString& str, char term = ',' );
std::ostream& recCsvWrite( std::ostream& out, idt id, char term = ',' );
std::ostream& recCsvWrite( std::ostream& out, int num, char term = ',' );
std::ostream& recCsvWrite( std::ostream& out, unsigned num, char term = ',' );

// GEDCOM style UID's
extern wxString recCreateUid();
extern bool recCheckUid( const wxString& uid );

enum class recCorrectUid { restore, create, cancel };

enum class recMatchUID { unequal, younger, older, equal };


enum class recTable {
    null_table, Associate, Citation, CitationPart, CitationPartType,
    Contact, ContactList, ContactType, Date, Event, Eventa,
    EventaPersona, EventEventa, EventType, EventTypeRole, Family,
    FamilyEvent, FamilyEventa, FamilyIndEventa, FamilyIndividual,
    Gallery, GalleryMedia, Individual, IndividualEvent, IndividualPersona,
    Media, MediaData, Name, NamePart, NamePartType, NameStyle, Persona,
    Place, PlacePart, PlacePartType, Reference, ReferenceEntity,
    RelativeDate, Repository, Researcher, System, User, UserSetting,
    Version, max_table
};

constexpr const char* recTablePrefixes[] = {
    "", "A", "Ci", "CiP", "CiPT", "C", "CL", "CT", "D", "E", "Ea",
    "EP", "EEa", "ET", "Ro", "F", "FE", "FEa", "FIEa", "FIn",
    "G", "GM", "I", "IE", "IP", "M", "MD", "N", "NP", "NPT", "NS", "Pa",
    "P", "PP", "PPT", "R", "REn", "RD", "Rp", "Re", "Sy", "U", "US",
    "V", ""
};

constexpr size_t recTablesSize = sizeof( recTablePrefixes ) / sizeof( char* );

struct recRecordId {
    recRecordId() : table( recTable::null_table ), id( 0 ) {}

    recTable table;
    idt id;
};

using recRecordIdVec = std::vector<recRecordId>;

// Convert a Record string to a recRecordID struct.
extern recRecordId recGetRecordId( const std::string& str );
inline recRecordId recGetRecordId( const wxString& str ) {
    return recGetRecordId( std::string( str ) );
}
// Convert a space separated list of Records to vector of recRecordID structs.
extern recRecordIdVec recGetRecordIDs( const wxString& str );


#endif // REC_RECHELPER_H
