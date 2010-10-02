/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calLatin.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Latin (Gregorian & Julian) Calendar functions.
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

#ifndef CALLATIN_H
#define CALLATIN_H

extern int calLatinDiy[];
extern int calLatinLengthOfMonth[3][12];
extern wxString calMonthName[3][12];

struct DMYDate;

// Return the month number 1-12 for correct match, or zero if no match
extern int calLatinLookUpMonth( const wxString str );

// Parse a Latin style date string in the format:  dd mmm... yyyy
// and update day, month and year arguments. Returns true on success
extern bool calLatinFromStr( const wxString& str, DMYDate& dmy );

// Given the day month year and scheme, calculate the jdn.
// Returns true on success
extern bool calLatinToJdn( long& jdn, const DMYDate& dmy, CalendarScheme scheme );

extern bool calLatinToJdn( long& jdn, int d, int m, int y, CalendarScheme scheme );

// Return the string representing the jdn in the given scheme
extern wxString calLatinStrFromJdn( long jdn, CalendarScheme scheme );

// Return the string representing the jdn range in the given scheme
extern wxString calLatinStrFromJdnRange(
    long jdn1, long jdn2, CalendarScheme scheme );

// Parse the string and obtain its jdn for the given scheme
extern bool calLatinStrToJdn( long& jdn, const wxString& str, CalendarScheme scheme );

// Parse the string and obtain its jdn range for the given scheme
extern bool calLatinStrToJdnRange(
    long& jdn1, long& jdn2, const wxString& str, CalendarScheme scheme );

#endif // CALLATIN_H