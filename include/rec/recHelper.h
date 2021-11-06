/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recHelper.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     General helper classes and functions
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     30th April 2013
 * Copyright:   Copyright (c) 2013 .. 2021, Nick Matthews.
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

// Some helpful defines
typedef wxLongLong_t    idt;
#define ID              "%lld"
#define GET_ID( id )    ((id).GetValue())
#define UTF8_(s) ((const char*)(s).utf8_str())
#define BOOL_(i) ( (i) ? 1 : 0 )
#define ID_OR_NULL(id) (UTF8_((id) ? recGetStr( id ) : "NULL"))
#define STR_OR_NULL(s) ( (s).IsEmpty() ? UTF8_("NULL") : \
    wxSQLite3StatementBuffer.FormatV( "'%q'", UTF8_(s) ) ) 

// Useful defines placed here for convenience.
typedef std::vector< wxString >  StringVec;
typedef std::vector< int >  IntVec;
typedef std::vector< wxLongLong_t > IntegerVec;
typedef std::vector< double > DoubleVec;
typedef std::vector< bool > BoolVec;

typedef std::vector< idt >  recIdVec;

typedef std::map< idt, wxString > recAssMap;

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
// Convert the given idStr into an idt if it has a matching prefix.
extern idt recIdFromStr( const wxString& prefix, const wxString idStr );

// Convert the given commer delimited string into two idt's
// return true if both are non-zero.
extern bool recGetIDs( const wxString& str, idt* id1, idt* id2, idt* id3 = NULL );
inline wxString recGetStr( idt id ) { return wxString::Format( ID, id ); }
inline wxString recGetIDStr( idt id ) { return id ? recGetStr( id ) : ""; }

enum class recSplitStrRet { none, number, associate, text };
extern recSplitStrRet recSplitStr( const wxString& str, idt* id1, idt* id2, wxString* dbname );

enum Sex { SEX_Unstated, SEX_Male, SEX_Female, SEX_Unknown };
extern wxString recGetSexStr( Sex sex );

// Surname grouping.
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

enum recET_GRP {
    recET_GRP_Unstated,    // 0
    recET_GRP_Birth,       // 1
    recET_GRP_NrBirth,     // 2
    recET_GRP_FamUnion,    // 3
    recET_GRP_FamOther,    // 4
    recET_GRP_Death,       // 5
    recET_GRP_NrDeath,     // 6
    recET_GRP_Other,       // 7
    recET_GRP_Personal,    // 8
    recET_GRP_Relation,    // 9
    recET_GRP_FamRelation, // 10
    recET_GRP_MAX          // 11
};

inline recET_GRP_FILTER recEventTypeGrpToFilter( recET_GRP grp ) { return  recET_GRP_FILTER(1 << grp); }

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

extern wxString recHTMLifyStr( const wxString& str );

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

#endif // REC_RECHELPER_H
