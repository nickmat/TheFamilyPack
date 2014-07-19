/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calParse.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Class to parse a date string into tokens.
 * Author:      Nick Matthews
 * Created:     20th December 2012
 * Copyright:   Copyright (c) 2012-2014, Nick Matthews.
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
calParser* g_calparser = NULL;

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

calTokenVec calParseStr( const wxString& str, CalendarScheme sch )
{
    wxASSERT( g_calparser != NULL );
    calSYNTAX syntax = calSYNTAX_NULL;

    switch( sch ) 
    {
    case CALENDAR_SCH_JulianDayNumber:
        syntax = calSYNTAX_Number;
        break;
    case CALENDAR_SCH_Julian:
    case CALENDAR_SCH_Gregorian:
        syntax = calSYNTAX_Latin;
        break;
     case CALENDAR_SCH_FrenchRevolution:
        syntax = calSYNTAX_French;
        break;
    case CALENDAR_SCH_IslamicTabular:
        syntax = calSYNTAX_Isamic;
        break;
    case CALENDAR_SCH_Hebrew:
        syntax = calSYNTAX_Hebrew;
        break;
   }
    return g_calparser->ParseStr( str, syntax ); 
}


calParser::calParser()
    : m_syntax(calSYNTAX_NULL)
{
    m_lookup[calSYNTAX_Latin]["jan"] = 1;
    m_lookup[calSYNTAX_Latin]["feb"] = 2;
    m_lookup[calSYNTAX_Latin]["mar"] = 3;
    m_lookup[calSYNTAX_Latin]["apr"] = 4;
    m_lookup[calSYNTAX_Latin]["may"] = 5;
    m_lookup[calSYNTAX_Latin]["jun"] = 6;
    m_lookup[calSYNTAX_Latin]["jul"] = 7;
    m_lookup[calSYNTAX_Latin]["aug"] = 8;
    m_lookup[calSYNTAX_Latin]["sep"] = 9;
    m_lookup[calSYNTAX_Latin]["oct"] = 10;
    m_lookup[calSYNTAX_Latin]["nov"] = 11;
    m_lookup[calSYNTAX_Latin]["dec"] = 12;

    // French revolutionary GedCom names
    m_lookup[calSYNTAX_French]["vend"] = 1;
    m_lookup[calSYNTAX_French]["brum"] = 2;
    m_lookup[calSYNTAX_French]["frim"] = 3;
    m_lookup[calSYNTAX_French]["nivo"] = 4;
    m_lookup[calSYNTAX_French]["pluv"] = 5;
    m_lookup[calSYNTAX_French]["vent"] = 6;
    m_lookup[calSYNTAX_French]["germ"] = 7;
    m_lookup[calSYNTAX_French]["flor"] = 8;
    m_lookup[calSYNTAX_French]["prai"] = 9;
    m_lookup[calSYNTAX_French]["mess"] = 10;
    m_lookup[calSYNTAX_French]["ther"] = 11;
    m_lookup[calSYNTAX_French]["fruc"] = 12;
    m_lookup[calSYNTAX_French]["comp"] = 13;

    // French revolutionary full names
    // TODO: Use correct accented utf charaters 
#if 0
    m_lookup[calSYNTAX_French][L"vendémiaire"] = 1;
    m_lookup[calSYNTAX_French]["brumaire"] = 2;
    m_lookup[calSYNTAX_French]["frimaire"] = 3;
    m_lookup[calSYNTAX_French][L"nivôse"] = 4;
    m_lookup[calSYNTAX_French][L"pluviôse"] = 5;
    m_lookup[calSYNTAX_French][L"ventôse"] = 6;
    m_lookup[calSYNTAX_French]["germinal"] = 7;
    m_lookup[calSYNTAX_French][L"floréal"] = 8;
    m_lookup[calSYNTAX_French]["prairial"] = 9;
    m_lookup[calSYNTAX_French]["messidor"] = 10;
    m_lookup[calSYNTAX_French]["thermidor"] = 11;
    m_lookup[calSYNTAX_French]["fructidor"] = 12;
    m_lookup[calSYNTAX_French][L"complémentaires"] = 13;
#endif
    m_lookup[calSYNTAX_French]["vendemiaire"] = 1;
    m_lookup[calSYNTAX_French]["brumaire"] = 2;
    m_lookup[calSYNTAX_French]["frimaire"] = 3;
    m_lookup[calSYNTAX_French]["nivose"] = 4;
    m_lookup[calSYNTAX_French]["pluviose"] = 5;
    m_lookup[calSYNTAX_French]["ventose"] = 6;
    m_lookup[calSYNTAX_French]["germinal"] = 7;
    m_lookup[calSYNTAX_French]["floreal"] = 8;
    m_lookup[calSYNTAX_French]["prairial"] = 9;
    m_lookup[calSYNTAX_French]["messidor"] = 10;
    m_lookup[calSYNTAX_French]["thermidor"] = 11;
    m_lookup[calSYNTAX_French]["fructidor"] = 12;
    m_lookup[calSYNTAX_French]["complementaires"] = 13;

    // Islamic month names
    m_lookup[calSYNTAX_Isamic]["muharram"] = 1;
    m_lookup[calSYNTAX_Isamic]["safar"] = 2;
    m_lookup[calSYNTAX_Isamic]["rabi'i"] = 3;
    m_lookup[calSYNTAX_Isamic]["rabi'ii"] = 4;
    m_lookup[calSYNTAX_Isamic]["jumadai"] = 5;
    m_lookup[calSYNTAX_Isamic]["jumadaii"] = 6;
    m_lookup[calSYNTAX_Isamic]["rajab"] = 7;
    m_lookup[calSYNTAX_Isamic]["sha'ban"] = 8;
    m_lookup[calSYNTAX_Isamic]["ramadan"] = 9;
    m_lookup[calSYNTAX_Isamic]["shawwal"] = 10;
    m_lookup[calSYNTAX_Isamic]["qa'da"] = 11;
    m_lookup[calSYNTAX_Isamic]["hijja"] = 12;
    m_lookup[calSYNTAX_Isamic]["dhu"] = calLabelIgnore;
    m_lookup[calSYNTAX_Isamic]["al"] = calLabelIgnore;

    // Hebrew GedCom names
    m_lookup[calSYNTAX_Hebrew]["nsn"] = 1;
    m_lookup[calSYNTAX_Hebrew]["iyr"] = 2;
    m_lookup[calSYNTAX_Hebrew]["svn"] = 3;
    m_lookup[calSYNTAX_Hebrew]["tmz"] = 4;
    m_lookup[calSYNTAX_Hebrew]["aav"] = 5;
    m_lookup[calSYNTAX_Hebrew]["ell"] = 6;
    m_lookup[calSYNTAX_Hebrew]["tsh"] = 7;
    m_lookup[calSYNTAX_Hebrew]["csh"] = 8;
    m_lookup[calSYNTAX_Hebrew]["ksl"] = 9;
    m_lookup[calSYNTAX_Hebrew]["tvt"] = 10;
    m_lookup[calSYNTAX_Hebrew]["shv"] = 11;
    m_lookup[calSYNTAX_Hebrew]["adr"] = 12;
    m_lookup[calSYNTAX_Hebrew]["ads"] = 13;

    // Hebrew Acadamy names
    m_lookup[calSYNTAX_Hebrew]["nisan"] = 1;
    m_lookup[calSYNTAX_Hebrew]["iyyar"] = 2;
    m_lookup[calSYNTAX_Hebrew]["sivan"] = 3;
    m_lookup[calSYNTAX_Hebrew]["tammuz"] = 4;
    m_lookup[calSYNTAX_Hebrew]["av"] = 5;
    m_lookup[calSYNTAX_Hebrew]["elul"] = 6;
    m_lookup[calSYNTAX_Hebrew]["tishri"] = 7;
    m_lookup[calSYNTAX_Hebrew]["marheshvan"] = 8;
    m_lookup[calSYNTAX_Hebrew]["kislev"] = 9;
    m_lookup[calSYNTAX_Hebrew]["tevet"] = 10;
    m_lookup[calSYNTAX_Hebrew]["shvat"] = 11;
    m_lookup[calSYNTAX_Hebrew]["adar"] = 12;
    m_lookup[calSYNTAX_Hebrew]["adari"] = 12;
    m_lookup[calSYNTAX_Hebrew]["adarii"] = 13;

    m_lookup[calSYNTAX_NULL]["year"]  = 0;
    m_lookup[calSYNTAX_NULL]["month"] = 1;
    m_lookup[calSYNTAX_NULL]["day"]   = 2;

    m_lookup[calSYNTAX_NULL]["(jdn)"] = CALENDAR_SCH_JulianDayNumber;
    m_lookup[calSYNTAX_NULL]["(j)"]   = CALENDAR_SCH_Julian;
    m_lookup[calSYNTAX_NULL]["(g)"]   = CALENDAR_SCH_Gregorian;
    m_lookup[calSYNTAX_NULL]["(fr)"]  = CALENDAR_SCH_FrenchRevolution;
    m_lookup[calSYNTAX_NULL]["(i)"]   = CALENDAR_SCH_IslamicTabular;
    m_lookup[calSYNTAX_NULL]["(h)"]   = CALENDAR_SCH_Hebrew;
}

calTokenVec calParser::ParseStr( const wxString& str, calSYNTAX syn )
{
    calTokenVec vec;
    calToken token;
    wxString outStr;
    calTOKEN type;
    long num;

    m_syntax = syn;
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
        } else if( type == calTOKEN_RangeSep ) {
            num = 0;
        } else {
            num = GetValue( outStr );
            if( num == calLabelNotFound ) {
                calTokenVec empty;
                return empty;
            }
            if( num == calLabelIgnore ) {
                outStr.clear();
                continue;
            }
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
    } else if( wxIsalpha( uc ) || uc == '\'' ) {
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
    wxString value;
    switch( m_syntax )
    {
    case calSYNTAX_Latin:
        value = label.Left(3).Lower();
        break;
    default:
        value = label.Lower();
    }
    if( m_lookup[m_syntax].count( value ) ) {
        return m_lookup[m_syntax][value];
    }
    return calLabelNotFound;
}

// End of src/cal/calParse.cpp
