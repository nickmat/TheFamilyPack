/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calGregorian.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Gregorian Calendar functions.
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
#include "calGregorian.h"

#define BASEDATE_Gregorian 1721060L

bool calGregorianIsLeapYear( int year )
{
    return ( year%4 == 0 && year%100 != 0 ) || year%400 == 0;
}


int calGregorianLastDayInMonth( int month, int year )
{
    if( calGregorianIsLeapYear( year ) )
    {
        return calLatinLengthOfMonth[1][month-1];
    }
    return calLatinLengthOfMonth[0][month-1];
}


bool calGregorianToJdn( long& jdn, int day, int month, int year )
{
    jdn = 
		FDiv( year, 400 )*146097L          //     days in 400 year cycles
        + (PMod( year, 400 )/100)*36524L   // - 1 days in 100 year cycles
        + (PMod( year, 100 )/4)*1461       // + 1 days in 4 year cycles
        + PMod( year, 4 )*365              // + 1 days in year
        + calLatinDiy[month] + day         // - 1 days numbered from 1 not 0
        + BASEDATE_Gregorian;

    // Adjust if in the 1st 2 months of 4 year cycle
    if( month < 3 && year%4 == 0 ) --jdn;

    // Adjust if in the 1st 2 months of 100 year cycle
    if( year%100 == 0 && month < 3 ) ++jdn;

    // Adjust if in the 1st 2 months of 400 year cycle
    if( year%400 == 0 && month < 3 ) --jdn;

    return true;
}


void calGregorianFromJdn( long date, int& day, int& month, int& year )
{
    date -= BASEDATE_Gregorian;
    year = (int) FDiv( date, 146097L ) * 400;
    date = PMod( date, 146097L );

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
    year += (int) ((date/36524L) * 100);
    date %= 36524L;

	if( date < 59 ) // Note, this is not a leap year
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
    ++date; // add the missing the leap day
    year += (int) (date/1461) * 4;
    date %= 1461;

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
    while( (int) date >= calLatinDiy[month+1] ) month++;
    day = (int) date - calLatinDiy[month] + 1;
}
#if 0
wxString calGregorianStrFromJdn( long jdn )
{
    wxString str;
    int day, month, year;

    calGregorianFromJdn( jdn, day, month, year );
    str << day << wxT(" ") << MonthName[0][month-1] << wxT(" ") << year;
    return str;
}
#endif
// End of calGregorian.cpp
