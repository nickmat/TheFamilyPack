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
#include "calJDay.h"
#include "calLatin.h"
#include "calJulian.h"
#include "calGregorian.h"

const wxString CalendarSchemeName[] = {
    wxT("Unstated"),
    wxT("Unknown"),
    wxT("Unlisted"),
    wxT("Julian Day Number"),
    wxT("Julian Day"),
    wxT("Modified Julian Day"),
    wxT("Rata Die"),
    wxT("Julian"),
    wxT("Gregorian"),
    wxT("Catholic"),
    wxT("English"),
    wxT("Scottish"),
    wxT("Swedish"),
    wxT("French Revolutionary")
};

const wxString CalendarSchemeAbrev[] = {
    wxT("Us"),
    wxT("Uk"),
    wxT("Ul"),
    wxT("JDN"),
    wxT("JD"),
    wxT("MJD"),
    wxT("RD"),
    wxT("J"),
    wxT("G"),
    wxT("Cath"),
    wxT("Eng"),
    wxT("Scot"),
    wxT("Swed"),
    wxT("FR")
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


bool calIsLeapYear( int year, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_Julian:
        return calJulianIsLeapYear( year );
    case CALENDAR_SCH_Gregorian:
        return calGregorianIsLeapYear( year );
    }
    return false;
}

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

bool calYearFromJdn( int& year, long jdn, CalendarScheme scheme )
{
    int day, month;

    switch( scheme )
    {
    case CALENDAR_SCH_Gregorian:
        calGregorianFromJdn( jdn, day, month, year );
        return true;
    case CALENDAR_SCH_Julian:
        calJulianFromJdn( jdn, day, month, year );
        return true;
    }
    return false;
}

wxString calStrFromJdn( long jdn, CalendarScheme scheme )
{
    wxString str;

    switch( scheme )
    {
    case CALENDAR_SCH_Gregorian:
    case CALENDAR_SCH_Julian:
        return calLatinStrFromJdn( jdn, scheme );
    case CALENDAR_SCH_JulianDayNumber:
    case CALENDAR_SCH_JulianDay:
    case CALENDAR_SCH_ModJulianDay:
    case CALENDAR_SCH_RataDie:
        return calJDayStrFromJdn( jdn, scheme );
    case CALENDAR_SCH_Unstated:
        return wxT("Unstated");
    case CALENDAR_SCH_Unknown:
        return wxT("Unknown");
    case CALENDAR_SCH_Unlisted:
        return wxT("Unlisted");
    }
    return wxT("Not yet done");
}

wxString calStrFromJdnRange( long jdn1, long jdn2, CalendarScheme scheme )
{
    // Format: dd mmm... yyyy
    // Format: nnnnnnn
    if( jdn1 == jdn2 )
    {
        return calStrFromJdn( jdn1, scheme );
    }

    wxString str;

    switch( scheme )
    {
    case CALENDAR_SCH_Gregorian:
    case CALENDAR_SCH_Julian:
        return calLatinStrFromJdnRange( jdn1, jdn2, scheme );
    case CALENDAR_SCH_JulianDayNumber:
    case CALENDAR_SCH_JulianDay:
    case CALENDAR_SCH_ModJulianDay:
    case CALENDAR_SCH_RataDie:
        return calJDayStrFromJdnRange( jdn1, jdn2, scheme );
    }
    // Use the defaults from the single jdn version
    return calStrFromJdn( jdn1, scheme );
}

bool calStrToJdn( long& jdn, const wxString& str, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_Julian:
    case CALENDAR_SCH_Gregorian:
        return calLatinStrToJdn( jdn, str, scheme );
    case CALENDAR_SCH_JulianDayNumber:
    case CALENDAR_SCH_JulianDay:
    case CALENDAR_SCH_ModJulianDay:
    case CALENDAR_SCH_RataDie:
        return calJDayStrToJdn( jdn, str, scheme );
    }
    return false;
}

bool calStrToJdnRange(
    long& jdn1, long& jdn2, const wxString& str, CalendarScheme scheme )
{
    bool ret;

    switch( scheme )
    {
    case CALENDAR_SCH_Julian:
    case CALENDAR_SCH_Gregorian:
        ret = calLatinStrToJdnRange( jdn1, jdn2, str, scheme );
        break;
    case CALENDAR_SCH_JulianDayNumber:
    case CALENDAR_SCH_JulianDay:
    case CALENDAR_SCH_ModJulianDay:
    case CALENDAR_SCH_RataDie:
        ret = calJDayStrToJdnRange( jdn1, jdn2, str, scheme );
        break;
    default:
        jdn1 = jdn2 = 0;
        ret = false;
    }

    return ret;
}

// End of Calendar.cpp
