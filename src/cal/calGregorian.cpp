/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calGregorian.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Gregorian Calendar functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     28 September 2010
 * Copyright:   Copyright (c) 2010, 2023 Nick Matthews.
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

#include "cal/calendar.h"
#include "calCommon.h"
#include "calGregorian.h"

#define BASEDATE_Gregorian 1721060L

/*! Returns true if the year is a leap year in the Gregorian Calendar.
 */
bool calGregorianIsLeapYear( int year )
{
    return ( year%4 == 0 && year%100 != 0 ) || year%400 == 0;
}

/*! Returns the last day of the month for the give month and year
 *  in the Gregorian Calendar.
 */
int calGregorianLastDayInMonth( int month, int year )
{
    if( calGregorianIsLeapYear( year ) )
    {
        return calLatinLengthOfMonth[1][month-1];
    }
    return calLatinLengthOfMonth[0][month-1];
}

/*! Sets jdn to the Julian Day Number for the given day, month and year
 *  in the Gregorian Calendar. Always returns true.
 */
bool calGregorianToJdn( long* jdn, const DMYDate& dmy )
{
    *jdn =
        FDiv( dmy.year, 400 )*146097L          //     days in 400 year cycles
        + (PMod( dmy.year, 400 )/100)*36524L   // - 1 days in 100 year cycles
        + (PMod( dmy.year, 100 )/4)*1461       // + 1 days in 4 year cycles
        + PMod( dmy.year, 4 )*365              // + 1 days in year
        + calLatinDiy[dmy.month] + dmy.day     // - 1 days numbered from 1 not 0
        + BASEDATE_Gregorian;

    // Adjust if in the 1st 2 months of 4 year cycle
    if( dmy.month < 3 && dmy.year%4 == 0 ) --(*jdn);

    // Adjust if in the 1st 2 months of 100 year cycle
    if( dmy.year%100 == 0 && dmy.month < 3 ) ++(*jdn);

    // Adjust if in the 1st 2 months of 400 year cycle
    if( dmy.year%400 == 0 && dmy.month < 3 ) --(*jdn);

    return true;
}

long calGregorianToJdn( long year, long month, long day )
{
    long jdn =
        FDiv( year, 400 )*146097L          //     days in 400 year cycles
        + (PMod( year, 400 )/100)*36524L   // - 1 days in 100 year cycles
        + (PMod( year, 100 )/4)*1461       // + 1 days in 4 year cycles
        + PMod( year, 4 )*365              // + 1 days in year
        + calLatinDiy[month] + day     // - 1 days numbered from 1 not 0
        + BASEDATE_Gregorian;

    // Adjust if in the 1st 2 months of 4 year cycle
    if( month < 3 && year%4 == 0 ) --jdn;

    // Adjust if in the 1st 2 months of 100 year cycle
    if( year%100 == 0 && month < 3 ) ++jdn;

    // Adjust if in the 1st 2 months of 400 year cycle
    if( year%400 == 0 && month < 3 ) --jdn;

    return jdn;
}

/*! Splits the given Julian Day Number date into the day, month and year
 *  for the Gregorian Calendar.
 */
bool calGregorianFromJdn( long date, DMYDate* dmy )
{
    date -= BASEDATE_Gregorian;
    dmy->year = (int) FDiv( date, 146097L ) * 400;
    date = PMod( date, 146097L );

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
    dmy->year += (int) ((date/36524L) * 100);
    date %= 36524L;

    if( date < 59 ) // Note, this is not a leap year
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
    ++date; // add the missing the leap day
    dmy->year += (int) (date/1461) * 4;
    date %= 1461;

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
    while( (int) date >= calLatinDiy[dmy->month+1] ) dmy->month++;
    dmy->day = (int) date - calLatinDiy[dmy->month] + 1;
    return true;
}

void calGregorianFromJdn( long jdn, long* year, long* month, long* day )
{
    long date = jdn - BASEDATE_Gregorian;
    *year = FDiv( date, 146097L ) * 400;
    date = PMod( date, 146097L );

    if( date < 60 )
    {
        if( date < 31 )
        {
            *month = 1;
            *day = date + 1;
            return;
        }
        *month = 2;
        *day = date - 30;
        return;
    }
    --date; // remove the leap day
    *year += ((date/36524L) * 100);
    date %= 36524L;

    if( date < 59 ) // Note, this is not a leap year
    {
        if( date < 31 )
        {
            *month = 1;
            *day = date + 1;
            return;
        }
        *month = 2;
        *day = date - 30;
        return;
    }
    ++date; // add the missing the leap day
    *year += (date/1461) * 4;
    date %= 1461;

    if( date < 60 )
    {
        if( date < 31 )
        {
            *month = 1;
            *day = date + 1;
            return;
        }
        *month = 2;
        *day = date - 30;
        return;
    }
    --date; // remove the leap day
    *year += date / 365;
    date %= 365;
    *month = 1;
    while( date >= calLatinDiy[(*month)+1] ) {
        (*month)++;
    }
    *day = date - calLatinDiy[*month] + 1;
}

long calGregorianYearFromJdn( long jdn )
{
    long year, month, day;
    calGregorianFromJdn( jdn, &year, &month, &day );
    return year;
}


// End of calGregorian.cpp
