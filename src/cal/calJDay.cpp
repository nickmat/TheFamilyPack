/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calJDay.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Day number Calendar functions.
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

#include "wx/tokenzr.h"

#include "calendar.h"
#include "calJDay.h"

/*! Modified Julian Day, a shorter version of Julian Days.
 */
#define BASEDATE_ModJulianDay  2400001L

/*! Rata Die (Fixed Date) has 1 Jan 1 (G) as day 1 (31 Dec 0 (G) as day 0)
 *  and is defined in "Calendrical Calculations" by Nachum Dershowitz and
 *  Edward M. Reingold. It is used as the fixed date in their algorithms.
 */
#define BASEDATE_RataDie       1721425L

/*! Convert a julian day number into an integer format date of the given scheme.
 *  Returns true if successful, false otherwise.
 */
bool CalConvertFromJdn( long& num, long jdn, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_JulianDayNumber:
        num = jdn;
        return true;
    case CALENDAR_SCH_ModJulianDay:
        num = jdn - BASEDATE_ModJulianDay;
        return true;
    case CALENDAR_SCH_RataDie:
        num = jdn - BASEDATE_RataDie;
        return true;
    }
    return false;
}

/*! Convert a date in integer format of given scheme into a julian day number.
 *  Returns true if successful, false otherwise.
 */
extern bool CalConvertToJdn( long& jdn, long num, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_JulianDayNumber:
        jdn = num;
        return true;
    case CALENDAR_SCH_ModJulianDay:
        jdn = num + BASEDATE_ModJulianDay;
        return true;
    case CALENDAR_SCH_RataDie:
        jdn = num + BASEDATE_RataDie;
        return true;
    }
    return false;
}

/*! Return the string representing the jdn in the given scheme.
 *  The scheme is one which is represented by a single number.
 */
wxString calJDayStrFromJdn( long jdn, CalendarScheme scheme )
{
    wxString str;

    switch( scheme )
    {
    case CALENDAR_SCH_JulianDayNumber:
        str << jdn;
        return str;
    case CALENDAR_SCH_JulianDay:
        str << ( jdn - 1 ) << wxT(".5");
        return str;
    case CALENDAR_SCH_ModJulianDay:
        str << jdn - BASEDATE_ModJulianDay;
        return str;
    case CALENDAR_SCH_RataDie:
        str << jdn - BASEDATE_RataDie;
        return str;
    }
    return wxEmptyString;
}

/*! Return the string representing the jdn range in the given scheme.
 *  The scheme is one which is represented by a single number.
 */
wxString calJDayStrFromJdnRange( long jdn1, long jdn2, CalendarScheme scheme )
{
    wxString str;

    switch( scheme )
    {
    case CALENDAR_SCH_JulianDayNumber:
        str << jdn1 << wxT(" - ") << jdn2;
        return str;
    case CALENDAR_SCH_JulianDay:
        str << jdn1 - 1 << wxT(".5 - ") << jdn2 - 1 << wxT(".5");
        return str;
    case CALENDAR_SCH_ModJulianDay:
        str << jdn1 - BASEDATE_ModJulianDay
            << wxT(" - ")
            << jdn2 - BASEDATE_ModJulianDay;
        return str;
    case CALENDAR_SCH_RataDie:
        str << jdn1 - BASEDATE_RataDie
            << wxT(" - ")
            << jdn2 - BASEDATE_RataDie;
        return str;
    }
    return wxEmptyString;
}

/*! Parse the string and obtain its jdn for the given scheme.
 *  The scheme is one which is represented by a single number.
 */
bool calJDayStrToJdn( long& jdn, const wxString& str, CalendarScheme scheme )
{
    bool ret;
    jdn = 0; // in case of error

    switch( scheme )
    {
    case CALENDAR_SCH_JulianDayNumber:
        return str.ToLong( &jdn );
    case CALENDAR_SCH_JulianDay:
        double jd;
        ret = str.ToDouble( &jd );
        if( ret == false ) return false;
        jdn = (long) ( jd - 0.5 );
        return true;
    case CALENDAR_SCH_ModJulianDay:
        ret = str.ToLong( &jdn );
        if( ret == false ) return false;
        jdn += BASEDATE_ModJulianDay;
        return true;
    case CALENDAR_SCH_RataDie:
        ret = str.ToLong( &jdn );
        if( ret == false ) return false;
        jdn += BASEDATE_RataDie;
        return true;
    }
    return false;
}

/*! Parse the string and obtain its jdn range for the given scheme.
 *  The scheme is one which is represented by a single number.
 *
 *  Expected format:  nnnnn - nnnnn
 */
bool calJDayStrToJdnRange(
    long& jdn1, long& jdn2, const wxString& str, CalendarScheme scheme )
{
    bool ret1 = false, ret2 = false;
    wxArrayString tokens = wxStringTokenize( str );

    jdn1 = jdn2 = 0; // error returns should have these set to zero
    size_t count =  tokens.GetCount();
    if( count == 1 )
    {
        ret2 = ret1 = calJDayStrToJdn( jdn1, tokens[0], scheme );
        jdn2 = jdn1;
    }
    else if( count == 3 && tokens[1] == wxT("-") )
    {
        ret1 = calJDayStrToJdn( jdn1, tokens[0], scheme );
        ret2 = calJDayStrToJdn( jdn2, tokens[2], scheme );
    }
    if( ret1 == false || ret2 == false )
    {
        jdn1 = jdn2 = 0;
        return false;
    }
    if( jdn1 > jdn2 )
    {
        long temp = jdn1;
        jdn1 = jdn2;
        jdn2 = temp;
    }
    return true;
}

// End of calJDay.cpp file