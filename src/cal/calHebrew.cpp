/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calHebrew.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Hebrew Calendar functions.
 * Author:      Nick Matthews
 * Created:     30th March 2013
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/tokenzr.h"

#include "calendar.h"
#include "calCommon.h"
#include "calHebrew.h"

#define BASEDATE_Hebrew    347998L

namespace {

long calHebrewElapsedDays( long year )
{
    long months = FDiv( 235 * year - 234, 19 ); 
    long days = 29 * months + FDiv( 12084L + 13753L * months, 25920 );
    if( ( ( 3 * ( days + 1 ) ) % 7 ) < 3 ) {
        return days + 1;
    }
    return days;
}

long calHebrewNewYear( long year )
{
    long ny0 = calHebrewElapsedDays( year - 1 );
    long ny1 = calHebrewElapsedDays( year );
    long ny2 = calHebrewElapsedDays( year + 1 );
    long correction = 0;
    if( ( ny2 - ny1 ) == 356 ) {
        correction = 2;
    } else if( ( ny1 - ny0 ) == 382 ) {
        correction = 1;
    }
    return BASEDATE_Hebrew + ny1 + correction;
}

long calHebrewDaysInYear( long year )
{
    return calHebrewNewYear( year + 1 ) - calHebrewNewYear( year );
}

bool calHebrewTestForYear( long year, long jdn )
{
    return calHebrewNewYear( year ) > jdn;
}

} // namespace

/*! Returns true if the year is a leap year in the Hebrew Calendar.
 *  Note that a Hebrew leap years are years with an additional 13th
 *  month. Also note, non-leap years are not all the same length.
 */
bool calHebrewIsLeapYear( long year )
{
    return PMod( 1 + 7 * year, 19 ) < 7;
}

/*! Returns the last day of the month for the given month and year
 *  in the Hebrew Calendar.
 */
int calHebrewLastDayInMonth( long month, long year )
{
    wxASSERT( month >= 1 && month <= 13 );
    long diy;
    switch( month )
    {
    case 2: case 4: case 6: case 10: case 13:
        return 29;
    case 8:
        diy = calHebrewDaysInYear( year );
        if( diy != 355 && diy != 385 ) {
            return 29;
        }
        break;
    case 9:
        diy = calHebrewDaysInYear( year );
        if( diy == 353 || diy == 383 ) {
            return 29;
        }
        break;
    case 12:
        if( ! calHebrewIsLeapYear( year ) ) {
            return 29;
        }
        break;
    }
    return 30;
}

/*! Sets jdn to the Julian Day Number for the given day, month and year
 *  in the Hebrew Calendar. Always returns true.
 */
bool calHebrewToJdn( long* jdn, long year, long month, long day )
{
    long diy = calHebrewDaysInYear( year );
    bool leap = calHebrewIsLeapYear( year );

    long mdays = 0;
    switch( month )
    {
    case 6: // fall thru intended
        mdays += 30; // month 5
    case 5:
        mdays += 29; // month 4
    case 4:
        mdays += 30; // month 3
    case 3:
        mdays += 29; // month 2
    case 2:
        mdays += 30; // month 1
    case 1:
        if( leap ) { // month 13
            mdays += 29;
        }
    case 13: 
        if( leap ) { // month 12
            mdays += 30;
        } else {
            mdays += 29;
        }
    case 12:
        mdays += 30; // month 11
    case 11:
        mdays += 29; // month 10
    case 10:
        if( diy == 353 || diy == 383 ) { // month 9
            mdays += 29;
        } else {
            mdays += 30;
        }
    case 9:
        if( diy == 355 || diy == 385 ) { // month 8
            mdays += 30;
        } else {
            mdays += 29;
        }
    case 8:
        mdays += 30;  // month 7
    }
    *jdn = calHebrewNewYear( year ) + mdays + day - 1;
    return true;
}

/*! Splits the given Hebrew Day Number date into the day, month and year
 *  for the Hebrew Calendar.
 */
bool calHebrewFromJdn( long jdn, long* year, long* month, long* day )
{
    long y = FDiv( 4L * ( jdn - BASEDATE_Hebrew ), 1461 );
    for(;;) { 
        if( calHebrewNewYear( y ) > jdn ) {
            --y;
            break;
        }
        y++;
    }

    long temp;
    calHebrewToJdn( &temp, y, 1, 1 );
    long m = ( jdn < temp ) ? 7 : 1;
    for(;;) {
        long ldim = calHebrewLastDayInMonth( m, y );
        calHebrewToJdn( &temp, y, m, ldim );
        if( jdn <= temp ) {
            break;
        }
        m++;
        wxASSERT( m <= 13 );
    }
    calHebrewToJdn( &temp, y, m, 1 );
    *day = jdn - temp + 1;
    *year = y;
    *month = m;
    return true;
}

// End of src/cal/calHebrew.cpp
