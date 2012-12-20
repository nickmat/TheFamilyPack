/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calendar.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Program interface functions.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     28 September 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include "calendar.h"
#include "calCommon.h"
#include "calParse.h"
#include "calRecord.h"
#include "calJulian.h"
#include "calGregorian.h"

const wxString CalendarSchemeName[] = {
    _("Unstated"),
    _("Unknown"),
    _("Unlisted"),
    _("Julian Day Number"),
    _("Julian Day"),
    _("Modified Julian Day"),
    _("Rata Die"),
    _("Julian"),
    _("Gregorian"),
    _("Catholic"),
    _("English"),
    _("Scottish"),
    _("Swedish"),
    _("French Revolutionary")
};

const wxString CalendarSchemeAbrev[] = {
    "null", // Unstated
    "NK",   // Unknown
    "NL",   // Unlisted
    "JDN",
    "JD",
    "MJD",
    "RD",
    "J",
    "G",
    "Cath",
    "Eng",
    "Scot",
    "Swed",
    "FR"
};

const wxString CalendarUnitName[] = {
    _("Unstated"),
    _("Year"),
    _("Month"),
    _("Week"),
    _("Day")
};

const CalendarStructure CalendarStructs[CALENDAR_SCH_Max] = {
    CALENDAR_STRUCT_Unstated,  // CALENDAR_SCH_Unstated
    CALENDAR_STRUCT_Unstated,  // CALENDAR_SCH_Unknown
    CALENDAR_STRUCT_Unstated,  // CALENDAR_SCH_Unlisted
    CALENDAR_STRUCT_Day,       // CALENDAR_SCH_JulianDayNumber
    CALENDAR_STRUCT_Time,      // CALENDAR_SCH_JulianDay
    CALENDAR_STRUCT_Day,       // CALENDAR_SCH_ModJulianDay
    CALENDAR_STRUCT_Day,       // CALENDAR_SCH_RataDie
    CALENDAR_STRUCT_Triple,    // CALENDAR_SCH_Julian
    CALENDAR_STRUCT_Triple,    // CALENDAR_SCH_Gregorian
    CALENDAR_STRUCT_Triple,    // CALENDAR_SCH_Catholic
    CALENDAR_STRUCT_Triple,    // CALENDAR_SCH_English
    CALENDAR_STRUCT_Triple,    // CALENDAR_SCH_Scottish
    CALENDAR_STRUCT_Triple,    // CALENDAR_SCH_Swedish
    CALENDAR_STRUCT_Triple     // CALENDAR_SCH_FrenchRevolution
};

// Helper function.
// Integer function to return floor( a / b )
long FDiv( long a, long b )
{
    long q = a / b;
    if( a % b < 0 ) --q;
    return q;
}

// Helper function.
// Integer function to return positive value of ( a % b )
long PMod( long a, long b )
{
    long r = a % b;
    if( r < 0 ) r += b;
    return r;
}

bool calConvertToJdn( long* jdn, CalendarScheme sch, 
    long r0, long r1, long r2, long r3, long r4 )
{
    calRecord rec( sch, r0, r1, r2, r3, r4 );
    return rec.ConvertToJdn( jdn );
}

bool calConvertToJdnRange( long* jdn1, long*jdn2, CalendarScheme sch, 
    long r0, long r1, long r2, long r3, long r4 )
{
    calRecord rec( sch, r0, r1, r2, r3, r4 );
    return rec.ConvertToRange( jdn1, jdn2 );
}

bool calConvertFromJdn( long jdn, CalendarScheme sch, 
     long* r0, long* r1, long* r2, long* r3, long* r4 )
{
    calRecord rec( sch );
    bool ok = rec.ConvertFromJdn( jdn );
    if( ok ) {
        rec.GetR( r0, r1, r2, r3, r4 );
    }
    return ok;
}

bool calStrToJdn( long* jdn, const wxString& str, CalendarScheme sch )
{
    calTokenVec tokens = calParseStr( str );
    calRecord rec( sch, tokens.size(), &tokens[0] );
    return rec.ConvertToJdn( jdn );
}

wxString calStrFromJdn( long jdn, CalendarScheme sch )
{
    calRecord rec( sch );
    rec.ConvertFromJdn( jdn );
    return rec.GetStr();
}

bool calStrToJdnRange(
    long* jdn1, long* jdn2, const wxString& str, CalendarScheme sch )
{ 
    bool ok = true;
    calTokenVec tokens = calParseStr( str );
    for( size_t i = 0 ; i < tokens.size() ; i++ ) {
        if( tokens[i].GetToken() == calTOKEN_RangeSep ) {
            if( i == 0 ) {
                return false;
            }
            calRecord rec1( sch, i, &tokens[0] );
            ok = rec1.ConvertRangeStartToJdn( jdn1 );
            size_t len = tokens.size() - i - 1;
            if( len == 0 ) {
                return false;
            }
            if( ok ) {
                calRecord rec2( sch, len, &tokens[i+1] );
                ok = rec2.ConvertRangeEndToJdn( jdn2 );
            }
            return ok;
        }
    }
    calRecord rec3( sch, tokens.size(), &tokens[0] );
    ok = rec3.ConvertToRange( jdn1, jdn2 );

    return ok;
}

wxString calStrFromJdnRange( long jdn1, long jdn2, CalendarScheme sch )
{
    wxString str;
    calRecord rec1( sch );
    rec1.ConvertFromJdn( jdn1 );
    if( jdn1 == jdn2 ) {
        return rec1.GetStr();
    }
    rec1.RemoveFieldsIfFirst();

    calRecord rec2( sch );
    rec2.ConvertFromJdn( jdn2 );
    rec2.RemoveFieldsIfLast();

    if( rec1 == rec2 ) {
        return rec1.GetStr();
    }
    str << rec1.GetStr() << " - " << rec2.GetStr();

    return str;
}

bool calYearFromJdn( int* year, long jdn, CalendarScheme sch )
{
    calRecord rec( sch );
    bool ok = rec.ConvertFromJdn( jdn );
    if( ok ) {
        *year = rec.GetR( 0 );
    }
    return ok;
}



//-------------------------------------------------------------------------------

int calLastDayInMonth( int month, int year, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_Gregorian:
        return calGregorianLastDayInMonth( month, year );
    case CALENDAR_SCH_Julian:
        return calJulianLastDayInMonth( month, year );
    }
    return 0;
}

//------------------------------------------------------------------------
/*! Add to jdn the given value based on the values unit and the given scheme. 
 *  Returns true if successful, else false.
 */
bool calLatinAddToJdn(
    long* jdn, long value, CalendarUnit unit, CalendarScheme scheme )
{
    //DMYDate dmy;
    long year, month, day;
//    if( !calConvertFromJdn( *jdn, &dmy, scheme ) ) return false;
    if( !calConvertFromJdn( *jdn, scheme, &year, &month, &day ) ) return false;
    switch( unit )
    {
    case CALENDAR_UNIT_Year:
        year += value;
        break;
    case CALENDAR_UNIT_Month:
        year += value / 12;
        month += value % 12;
        if( month > 12 ) {
            year++;
            month -= 12;
        }
        if( month < 1 ) {
            --year;
            month += 12;
        }
        break;
    default:
        return false;
    }
//    return calConvertToJdn( jdn, dmy, scheme );
    return calConvertToJdn( jdn, scheme, year, month, day );
}


bool calAddToJdn( 
    long* jdn, long value, CalendarUnit unit, CalendarScheme scheme )
{
    switch( unit )
    {
    case CALENDAR_UNIT_Day:
        *jdn += value;
        return true;
    case CALENDAR_UNIT_Week:
        *jdn += value * 7;
        return true;
    case CALENDAR_UNIT_Month:
    case CALENDAR_UNIT_Year:
        switch( scheme )
        {
        case CALENDAR_SCH_Julian:
        case CALENDAR_SCH_Gregorian:
            return calLatinAddToJdn( jdn, value, unit, scheme );
        }
        break;
    }
    return false;
}

// End of calendar.cpp
