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

#include <map>
#include "calParse.h"

typedef std::map< wxString, unsigned > calLabelMap;
calLabelMap LabelLookup;

extern void calInit();

namespace {

calTOKEN GetTokenType( const wxUniChar& uc )
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

calTOKEN GetPunctType( const wxString& punct )
{
    if( punct == "~" ) {
        return calTOKEN_RangeSep;
    }
    if( punct == "-" ) {
        return calTOKEN_Minus;
    }
    return calTOKEN_Punct;
}

long GetValue( const wxString& label )
{
    wxString value = label.Left(3).Lower();
    if( LabelLookup.count( value ) ) {
        return LabelLookup[value];
    }
    value = label.Left(4).Lower();
    if( LabelLookup.count( value ) ) {
        return LabelLookup[value];
    }
    return 0;
}

} // namespace

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
            type = GetTokenType( *it );
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

    hasrun = true;
}

// End of src/cal/calParse.cpp
