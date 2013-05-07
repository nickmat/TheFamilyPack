/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recHelper.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     General helper classes and functions
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     30th April 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <vector>

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
// Convert the given commer delimited string into two idt's
// return true if both are non-zero.
extern bool recGetIDs( const wxString& str, idt* id1, idt* id2 );
inline wxString recGetStr( idt id ) { return wxString::Format( ID, id ); }
inline wxString recGetIDStr( idt id ) { return id ? recGetStr( id ) : ""; }

enum Sex { SEX_Unstated, SEX_Male, SEX_Female, SEX_Unknown };
extern wxString recGetSexStr( Sex sex );

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

#endif // REC_RECHELPER_H
