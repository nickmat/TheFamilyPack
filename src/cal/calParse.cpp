/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calParse.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Class to parse a date string into tokens.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     20th December 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "calParse.h"

//typedef std::map< wxString, unsigned > calLabelMap;
//calLabelMap LabelLookup;
extern calParser* g_calparser = NULL;

void calInitParser()
{
    wxASSERT( g_calparser == NULL );
    g_calparser = new calParser;
}

void calUninitParser()
{
    wxASSERT( g_calparser != NULL );
    delete g_calparser;
    g_calparser = NULL;
}

calTokenVec calParseStr( const wxString& str )
{
    wxASSERT( g_calparser != NULL );
    return g_calparser->ParseStr( str ); 
}


calParser::calParser()
{
    m_lookup["jan"] = 1;
    m_lookup["feb"] = 2;
    m_lookup["mar"] = 3;
    m_lookup["apr"] = 4;
    m_lookup["may"] = 5;
    m_lookup["jun"] = 6;
    m_lookup["jul"] = 7;
    m_lookup["aug"] = 8;
    m_lookup["sep"] = 9;
    m_lookup["oct"] = 10;
    m_lookup["nov"] = 11;
    m_lookup["dec"] = 12;

    m_lookup["vend"] = 1;
    m_lookup["brum"] = 2;
    m_lookup["frim"] = 3;
    m_lookup["nivo"] = 4;
    m_lookup["pluv"] = 5;
    m_lookup["vent"] = 6;
    m_lookup["germ"] = 7;
    m_lookup["flor"] = 8;
    m_lookup["prai"] = 9;
    m_lookup["mess"] = 10;
    m_lookup["ther"] = 11;
    m_lookup["fruc"] = 12;
    m_lookup["comp"] = 13;

    m_lookup["year"]  = 0;
    m_lookup["month"] = 1;
    m_lookup["day"]   = 2;

    m_lookup["(jdn)"] = CALENDAR_SCH_JulianDayNumber;
    m_lookup["(j)"]   = CALENDAR_SCH_Julian;
    m_lookup["(g)"]   = CALENDAR_SCH_Gregorian;
    m_lookup["(fr)"]  = CALENDAR_SCH_FrenchRevolution;
}

calTokenVec calParser::ParseStr( const wxString& str )
{
    calTokenVec vec;
    calToken token;
    wxString outStr;
    calTOKEN type;
    long num;

    for( wxString::const_iterator it = str.begin() ; it != str.end() ; ) {
        if( wxIsspace( *it ) ) {
            it++;
            continue;
        }
        if( *it == '(' ) {
            do {
                outStr << *it++;
            } while( it != str.end() && *it != ')' );
            token.SetToken( calTOKEN_Scheme );
        } else {
            if( *it == '-' ) {
                type = calTOKEN_Number;
            } else {
                type = GetTokenType( *it );
            }
            do {
                outStr << *it++;
            } while( it != str.end() && type == GetTokenType( *it ) );
            if( type == calTOKEN_Punct ) {
                type = GetPunctType( outStr );
            }
            token.SetToken( type );
        }
        if( type == calTOKEN_Number ) {
            outStr.ToCLong( &num );
        } else {
            num = GetValue( outStr );
        }
        token.SetNumber( num );
        token.SetLabel( outStr );
        vec.push_back( token );
        outStr.clear();
    }
    return vec;
}


calTOKEN calParser::GetTokenType( const wxUniChar& uc )
{
    if( wxIsdigit( uc ) ) {
        return calTOKEN_Number;
    } else if( wxIsalpha( uc ) ) {
        return calTOKEN_Label;
    } else if( wxIspunct( uc ) ) {
        return calTOKEN_Punct;
    }
    return calTOKEN_NULL;
}

calTOKEN calParser::GetPunctType( const wxString& punct )
{
    if( punct == "~" ) {
        return calTOKEN_RangeSep;
    }
    if( punct == "-" ) {
        return calTOKEN_Minus;
    }
    return calTOKEN_Punct;
}

long calParser::GetValue( const wxString& label )
{
    wxString value = label.Left(3).Lower();
    if( m_lookup.count( value ) ) {
        return m_lookup[value];
    }
    value = label.Left(4).Lower();
    if( m_lookup.count( value ) ) {
        return m_lookup[value];
    }
    return 0;
}

//-------------------------------------------------------

#if 0
calTokenVec calParseStr( const wxString& str )
{
    calTokenVec vec;
    calToken token;
    wxString outStr;
    calTOKEN type;
    long num;

    calInit();
    for( wxString::const_iterator it = str.begin() ; it != str.end() ; ) {
        if( wxIsspace( *it ) ) {
            it++;
            continue;
        }
        if( *it == '(' ) {
            do {
                outStr << *it++;
            } while( it != str.end() && *it != ')' );
            token.SetToken( calTOKEN_Scheme );
        } else {
            if( *it == '-' ) {
                type = calTOKEN_Number;
            } else {
                type = GetTokenType( *it );
            }
            do {
                outStr << *it++;
            } while( it != str.end() && type == GetTokenType( *it ) );
            if( type == calTOKEN_Punct ) {
                type = GetPunctType( outStr );
            }
            token.SetToken( type );
        }
        if( type == calTOKEN_Number ) {
            outStr.ToCLong( &num );
        } else {
            num = GetValue( outStr );
        }
        token.SetNumber( num );
        token.SetLabel( outStr );
        vec.push_back( token );
        outStr.clear();
    }
    return vec;
}

void calInit()
{
    static bool hasrun = false;
    if( hasrun ) {
        return;
    }

    LabelLookup["jan"] = 1;
    LabelLookup["feb"] = 2;
    LabelLookup["mar"] = 3;
    LabelLookup["apr"] = 4;
    LabelLookup["may"] = 5;
    LabelLookup["jun"] = 6;
    LabelLookup["jul"] = 7;
    LabelLookup["aug"] = 8;
    LabelLookup["sep"] = 9;
    LabelLookup["oct"] = 10;
    LabelLookup["nov"] = 11;
    LabelLookup["dec"] = 12;

    LabelLookup["vend"] = 1;
    LabelLookup["brum"] = 2;
    LabelLookup["frim"] = 3;
    LabelLookup["nivo"] = 4;
    LabelLookup["pluv"] = 5;
    LabelLookup["vent"] = 6;
    LabelLookup["germ"] = 7;
    LabelLookup["flor"] = 8;
    LabelLookup["prai"] = 9;
    LabelLookup["mess"] = 10;
    LabelLookup["ther"] = 11;
    LabelLookup["fruc"] = 12;
    LabelLookup["comp"] = 13;

    LabelLookup["year"]  = 0;
    LabelLookup["month"] = 1;
    LabelLookup["day"]   = 2;


    LabelLookup["(jdn)"] = CALENDAR_SCH_JulianDayNumber;
    LabelLookup["(j)"]   = CALENDAR_SCH_Julian;
    LabelLookup["(g)"]   = CALENDAR_SCH_Gregorian;
    LabelLookup["(fr)"]  = CALENDAR_SCH_FrenchRevolution;

    hasrun = true;
}
#endif

// End of src/cal/calParse.cpp
