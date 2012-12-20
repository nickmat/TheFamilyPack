/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calJulian.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Julian Calendar functions.
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
#include "calCommon.h"
#include "calJulian.h"


// Days in the year at the start of each month (Jan = 1) (not leap year)
int calLatinDiy[14] = {
    // Note: we add an extra 0 to the beginning of the array to save
    //       subtracting 1 from the month number
    0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

int calLatinLengthOfMonth[3][12] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, // Nomal year
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, // Leap year
    { 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }  // For the Swedish calendar scheme
};


// Julian Calendar

#define BASEDATE_Julian    1721058L

/*! Returns true if the year is a leap year in the Julian Calendar.
 */
bool calJulianIsLeapYear( int year )
{
    return ( year % 4 ) == 0;
}

/*! Returns the last day of the month for the give month and year
 *  in the Julian Calendar.
 */
int calJulianLastDayInMonth( int month, int year )
{
    if( calJulianIsLeapYear( year ) )
    {
        return calLatinLengthOfMonth[1][month-1];
    }
    return calLatinLengthOfMonth[0][month-1];
}

/*! Sets jdn to the Julian Day Number for the given day, month and year
 *  in the Julian Calendar. Always returns true.
 */
bool calJulianToJdn( long* jdn, const DMYDate& dmy )
{
    *jdn =
        FDiv(dmy.year,4)*1461 + PMod(dmy.year,4)*365
        + calLatinDiy[dmy.month] + dmy.day + BASEDATE_Julian;

    // Adjust if in the 1st 2 months of 4 year cycle
    if( dmy.month < 3 && (dmy.year%4) == 0 ) --(*jdn);

    return true;
}

/*! Splits the given Julian Day Number date into the day, month and year
 *  for the Julian Calendar.
 */
bool calJulianFromJdn( long date, DMYDate* dmy )
{
    date -= BASEDATE_Julian;

    dmy->year = (int) FDiv( date, 1461 ) * 4;
    date = PMod( date, 1461 );

    if( date < 60 )
    {
        if( date < 31 )
        {
            dmy->month = 1;
            dmy->day = (int) date + 1;
            return true;
        }
        dmy->month = 2;
        dmy->day = (int) date - 30;
        return true;
    }
    --date; // remove the leap day
    dmy->year += (int) date / 365;
    date %= 365;
    dmy->month = 1;
    while( date >= (long) calLatinDiy[dmy->month+1] ) dmy->month++;
    dmy->day = (int) date - calLatinDiy[dmy->month] + 1;
    return true;
}

// End of calJulian.cpp
