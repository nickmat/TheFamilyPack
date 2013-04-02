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

#include <vector>


enum {
    calR_MAX = 5,
    calR_INVALID = -1
};

enum CalendarScheme {

    /*! Unstated: Us
     *
     *  No attempt at classifing the calendar system has been made.
     */
    CALENDAR_SCH_Unstated = 0,

    /*! Unknown: Uk
     *
     *  The precise calendar system used is undetermined.
     */
    CALENDAR_SCH_Unknown,

    /*! Unlisted: Ul
     *
     *  The calendar system is known but not currently supported.
     */
    CALENDAR_SCH_Unlisted,

    /*! Julian Day Number: JDN. The calendar system used internally by TFP.
     *
     *  The Julian Day starting at midday. JDN 0 represents the day starting at
     *  midday Monday 24 Nov -4713 (Gregorian). Although the calendar library can correctly
     *  handle JDN 0 and negative JD Numbers, TFP has a special meaning for jdn 0.
     *  So for all practical purposes, JD 1 is the earliest date available.
     */
    CALENDAR_SCH_JulianDayNumber,

    /*! Julian Day: JD  [TEMPORARILY WITHDRAWN]
     *
     *  JD = JDN - 0.5
     *  The system used by astronomers to mark time since midday Monday 1st January 4713 B.C.E. (Julian Calendar).
     *
     *  The fractional part of the day is used to denote the time of day, so the day
     *  comencing Midnight on Tuesday 2nd January 4713 B.C.E. would given as JD 0.5
     *  and Sunday 19th September 1948 (Gregorian Calendar) is JD 2432313.5.
     *  Included for completeness.
     */
    CALENDAR_SCH_JulianDay,

    /*! Modified Julian Day: MJD.  [TEMPORARILY WITHDRAWN]
     *
     *  MJD = JDN - 2400001
     *
     *  A shortened version of the Julian Day. Included for completeness.
     */
    CALENDAR_SCH_ModJulianDay,

    /*! Rata Die: RD.  [TEMPORARILY WITHDRAWN]
     *
     *  RD = JDN - 1721425
     *
     *  RD 1 = 1st January year 1 Gregorian.  This is the base date used by
     *  Nachum Dershowitz and Edward M. Reingold in their book "Calendrical
     *  Calculations". A volume recommended to anyone interested in extending
     *  this library. Included for completeness.
     */
    CALENDAR_SCH_RataDie,

    /*! Julian Calendar: J.
     *
     *  1 Jan 1 (J) = 1721424 JDN
     *
     *  The main dating system used in the western world from the Roman times until
     *  it was replaced by the Gregorian Calendar from 1582.
     */
    CALENDAR_SCH_Julian,

    /*! Gregorian Calendar: G.
     *
     *  1 Jan 1 (G) = 1721426 JDN
     *
     *  The main dating system in use in the world today, it came into use from 1582
     *  onwards. Around the change over period, Julian dates where often labeled
     *  "Old Style" whilst Gregorian dates where labeled "New Style".
     */
    CALENDAR_SCH_Gregorian,

    /*! Catholic Calendar: Cath. [NOT YET AVAILABLE]
     *
     *  4 Oct 1582 (Julian) followed by 15 Oct 1582 (Gregorian).
     *
     *   4 Oct 1582 (Old Style) = 2299171 JDN
     *  15 Oct 1582 (New Style) = 2299172 JDN
     *
     *  The Catholic Calendar uses the Julian Calendar up to 4 Oct 1582 (Julian),
     *  and the Gregorian Calendar there after. Meaning that Thur 4 Oct 1582
     *  (Catholic) is followed by Fri 15 Oct 1582 (Catholic) and October for that
     *  year held only 21 days.
     *
     *  The Catholic Calendar is used by many catholic countries.
     */
    CALENDAR_SCH_Catholic,

    /*! English Calendar: Eng. [NOT YET AVAILABLE]
     *
     *  2 Sep 1752 (Julian) followed by 15 Sep 1752 (Gregorian).
     *
     *  Between 1 Jan 1200 (Julian) and 2 Sep 1752 (Julian) the new year
     *  falls on March 25th. 1 Jan 1200 is an arbitrary date as the change happened
     *  over a period of time. This scheme is best avoided for dates before 1400.
     *
     *  Scheme used in England and Wales and British Overseas Territories, but
     *  not Scotland.
     */
    CALENDAR_SCH_English,

    /*! Scottish Calendar: Scot. [NOT YET AVAILABLE]
     *
     *  As English Calendar except new year always falls on 1st Jan.
     */
    CALENDAR_SCH_Scottish,

    /*! Swedish Calendar: Swed.  [NOT YET AVAILABLE]
     *
     *  Sweden attempted a slow change over from Julian to Gregorian calendar.
     */
    CALENDAR_SCH_Swedish,

    /*! French Revolution Calendar: FR.
     *
     *  Short lived attempt to rationalise the calendar after the French Revolution.
     */
    CALENDAR_SCH_FrenchRevolution,

    /*! Islamic Tabular Calendar: I.
     *
     *  Arithmetic version of the Islamic lunar or Hijri calendar.
     *  Based on leap years in years 2, 5, 7, 10, 13, 16, 18, 21, 24, 26 and 29 of a
     *  30 year cycle. (Note, there are other variations)
     */
    CALENDAR_SCH_IslamicTabular,

    /*! Hebrew Calendar: H.
     *
     *  The arithmetic Hebrew Calendar.
     */
    CALENDAR_SCH_Hebrew,

    /*! End marker, used to size arrays etc.
     */
    CALENDAR_SCH_Max
};

/*! Initialize the calendar lib
 */
extern void calInit();

/*! Uninitialize the calendar lib
 */
extern void calUninit();

/*! Array of scheme names
 */
extern const char* CalendarSchemeName[];

/*! Array of scheme abreviations
 */
extern const char* CalendarSchemeAbrev[];

/*! Convert a date given in individual records (Largest, ie year, first) for a 
 *  given scheme into a julian day number. This only returns a range of more than a day 
 *  if the records are incomplete ie all but year are set to calR_INVALID.
 *  Returns true if successful, false otherwise.
 */
extern bool calConvertToJdn( 
    long* jdn, CalendarScheme scheme, 
    long r0, long r1 = calR_INVALID, long r2 = calR_INVALID, 
    long r3 = calR_INVALID, long r4 = calR_INVALID );

/*! Convert an incomplete date given in individual records (Largest, ie year, first) 
 *  for a given scheme into a julian day number range, Submit calR_INVALID values for
 *  the missing date parts (days or days and months).
 *  Returns true if successful, false otherwise.
 */
extern bool calConvertToJdnRange( 
    long* jdn1, long*jdn2, CalendarScheme scheme, 
    long r0, long r1 = calR_INVALID, long r2 = calR_INVALID, 
    long r3 = calR_INVALID, long r4 = calR_INVALID );

/*! Convert a julian day number into individual records (Largest, ie year, first) 
 *  for the given scheme.
 *  Returns true if successful, false otherwise.
 */
extern bool calConvertFromJdn( 
    long jdn, CalendarScheme scheme, 
    long* r0, long* r1 = NULL, long* r2 = NULL, long* r3 = NULL, long* r4 = NULL );

/*! Returns the number of days in the given month for the given year
 * or 0 if the calendar scheme does not support months
 */
extern int calLastDayInMonth( int month, int year, CalendarScheme scheme );

/*! Returns the number of months in the given year
 * or 0 if the calendar scheme does not support months
 */
extern long calLastMonthInYear( long year, CalendarScheme scheme );

/*! Get the year number, based on the given calendar scheme
 * Returns false if unable to determine year
 */
extern bool calYearFromJdn( int* year, long jdn, CalendarScheme scheme );

/*! Returns a string representation of the julian day number for the given
 * calendar scheme. Returns a wxEmptyString on error.
 */
extern wxString calStrFromJdn( long jdn, CalendarScheme scheme );

/*! Converts a string into a julian day number based on the given
 * calendar scheme. Returns zero if unable to parse string.
 */
extern bool calStrToJdn( long* jdn, const wxString& str, CalendarScheme scheme );

/*! Converts a string of a date range in a given calendar scheme into two julian
 * day numbers. Note: jdn1 <= jdn2. Returns false if unable to parse string.
 */
extern bool calStrToJdnRange(
    long* jdn1, long* jdn2, const wxString& str, CalendarScheme scheme );

/*! Returns a string giving a date range of two julian day numbers in a given
 * calendar scheme. Returns a wxEmptyString on error.
 */
extern wxString calStrFromJdnRange( long jdn1, long jdn2, CalendarScheme scheme );

enum CalendarUnit {
    CALENDAR_UNIT_Unstated,
    CALENDAR_UNIT_Year,
    CALENDAR_UNIT_Month,
    CALENDAR_UNIT_Week,
    CALENDAR_UNIT_Day,
    CALENDAR_UNIT_Max
};

/*! Array of unit names
 */
extern const char* CalendarUnitName[];

/*! Add to jdn the given value, based on the values unit and the given scheme. 
 *  Returns true if successful, else false.
 */
extern bool calAddToJdn(
    long* jdn, long value, CalendarUnit unit, CalendarScheme scheme );

enum CalendarStructure {
    CALENDAR_STRUCT_Unstated,  // Value held as a string
    CALENDAR_STRUCT_Time,      // Value hels as a double
    CALENDAR_STRUCT_Day,       // Value held as a long
    CALENDAR_STRUCT_Triple,    // Value held as a DMYDate 
    CALENDAR_STRUCT_Max
};

extern const CalendarStructure CalendarStructs[CALENDAR_SCH_Max];

#endif // CALENDAR_H