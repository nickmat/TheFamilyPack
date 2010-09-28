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
#include "calLatin.h"
#include "calJulian.h"

// Julian Calendar

#define BASEDATE_Julian    1721058L

bool calJulianIsLeapYear( int year )
{
    return ( year % 4 ) == 0;
}

int calJulianLastDayInMonth( int month, int year )
{
    if( calJulianIsLeapYear( year ) )
    {
        return calLatinLengthOfMonth[1][month-1];
    }
    return calLatinLengthOfMonth[0][month-1];
}

bool calJulianToJdn( long& jdn, int day, int month, int year )
{
    jdn = 
		FDiv(year,4)*1461 + PMod(year,4)*365 
		+ calLatinDiy[month] + day + BASEDATE_Julian;

	// Adjust if in the 1st 2 months of 4 year cycle
    if( month < 3 && (year%4) == 0 ) --jdn;

    return true;
}

void calJulianFromJdn( long date, int& day, int& month, int& year )
{
    date -= BASEDATE_Julian;

	year = (int) FDiv( date, 1461 ) * 4;
	date = PMod( date, 1461 );

    if( date < 60 ) 
    {
        if( date < 31 ) 
        {
            month = 1;
            day = (int) date + 1;
            return;
        }
        month = 2;
        day = (int) date - 30;
        return;
    }
    --date; // remove the leap day
    year += (int) date / 365;
    date %= 365;
    month = 1;
    while( date >= (long) calLatinDiy[month+1] ) month++;
    day = (int) date - calLatinDiy[month] + 1;
}
#if 0
wxString calJulianStrFromJdn( long jdn )
{
    wxString str;
    int day, month, year;

    calJulianFromJdn( jdn, day, month, year );
    str << day << wxT(" ") << MonthName[0][month-1] << wxT(" ") << year;
    return str;
}
#endif
// End of calJulian.cpp
