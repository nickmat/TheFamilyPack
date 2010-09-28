/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calendar.h
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

#ifndef CALENDAR_H
#define CALENDAR_H

enum CalendarScheme {
    CALENDAR_SCH_Unstated = 0,
    CALENDAR_SCH_Unknown,
    CALENDAR_SCH_Unlisted,
    CALENDAR_SCH_JulianDayNumber,
    CALENDAR_SCH_JulianDay,
    CALENDAR_SCH_ModJulianDay,
    CALENDAR_SCH_RataDie,
    CALENDAR_SCH_Julian,
    CALENDAR_SCH_Gregorian,
    CALENDAR_SCH_Catholic,
    CALENDAR_SCH_English,
    CALENDAR_SCH_Scottish,
    CALENDAR_SCH_Swedish,
    CALENDAR_SCH_FrenchRevolution,
    CALENDAR_SCH_Max                 // End marker
};
// Array of scheme names
extern const wxString CalendarSchemeName[];
// Array of scheme abreviations
extern const wxString CalendarSchemeAbrev[];

// Returns true if year is a leap year and false if not,
// or the calendar scheme does not support leap years.
extern bool calIsLeapYear( int year, CalendarScheme scheme );

// Returns the number of days in the given month for the given year
// or 0 if the calendar scheme does not support months
extern int calLastDayInMonth( int month, int year, CalendarScheme scheme );

// Get the year number, based on the given calendar scheme
// Returns false if unable to determine year
extern bool calYearFromJdn( int& year, long jdn, CalendarScheme scheme );

// Returns a string representation of the julian day number for the given
// calendar scheme. Returns a wxEmptyString on error.
extern wxString calStrFromJdn( long jdn, CalendarScheme scheme );

// Returns a string giving a date range of two julian day numbers in a given
// calendar scheme. Returns a wxEmptyString on error.
extern wxString calStrFromJdnRange( long jdn1, long jdn2, CalendarScheme scheme );

// Converts a string into a julian day number based on the given
// calendar scheme. Returns zero if unable to parse string.
extern bool calStrToJdn( long& jdn, const wxString& str, CalendarScheme scheme );

// Converts a string of a date range in a given calendar scheme into two julian
// day numbers. Note: jdn1 <= jdn2. Returns false if unable to parse string.
extern bool calStrToJdnRange( long& jdn1, long& jdn2, const wxString& str,
                             CalendarScheme scheme );

#endif // CALENDAR_H