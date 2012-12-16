/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calLatin.cpp
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/tokenzr.h"

#include "calendar.h"
#include "calLatin.h"
#include "calJulian.h"
#include "calGregorian.h"

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


wxString calMonthName[3][12] = {
    {
        wxT("Jan"), wxT("Feb"), wxT("Mar"), wxT("Apr"), wxT("May"), wxT("Jun"),
        wxT("Jul"), wxT("Aug"), wxT("Sep"), wxT("Oct"), wxT("Nov"), wxT("Dec")
    }, {
        wxT("JAN"), wxT("FEB"), wxT("MAR"), wxT("APR"), wxT("MAY"), wxT("JUN"),
        wxT("JUL"), wxT("AUG"), wxT("SEP"), wxT("OCT"), wxT("NOV"), wxT("DEC")
    }, {
        wxT("January"), wxT("Febuary"), wxT("March"),
        wxT("April"), wxT("May"), wxT("June"),
        wxT("July"), wxT("August"), wxT("September"),
        wxT("October"), wxT("November"), wxT("December")
    }
};

/*! Convert a latin style month name to month number.
 *  Return the month number 1-12 for correct match, or zero if no match
 */
int calLatinLookUpMonth( const wxString& str )
{
    int i;
    wxString name = str.Left( 3 ).Upper();

    for( i = 0 ; i < 12 ; i++ )
    {
        if( name.IsSameAs( calMonthName[1][i] ) ) return i+1;
    }
    return 0;
}

/*! Parse a latin style date string in the format:  dd mmm... yyyy
 *
 *  Sets day, month and year if successful and returns true. If it doesn't
 *  succeed, returns false and day, month and year are indeterminate.
 */
bool calLatinFromStr( const wxString& str, DMYDate& dmy )
{
    wxString token;
    bool b;
    int i;
    long lg;
    wxStringTokenizer tkz( str );

    token = tkz.GetNextToken();
    b = token.ToLong( &lg );
    if( b == false ) return false;
    dmy.day = (int) lg;

    token = tkz.GetNextToken().Left( 3 ).Upper();
    for( i = 0 ; i < 12 ; i++ )
    {
        if( token.IsSameAs( calMonthName[1][i] ) ) break;
    }
    if( i == 13 ) return false;
    dmy.month = i+1;

    token = tkz.GetNextToken();
    b = token.ToLong( &lg );
    if( b == false ) return false;
    dmy.year = (int) lg;
    return true;
}

/*! Sets jdn to the JDN corresponding to the day, month and year according
 *  to the given latin calendar scheme.
 */
bool calLatinToJdn( long* jdn, const DMYDate& dmy, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_Julian:
        return calJulianToJdn( jdn, dmy );
    case CALENDAR_SCH_Gregorian:
        return calGregorianToJdn( jdn, dmy );
    }
    return false;
}

/*! Sets day month and year in the given calendar scheme from the JDN jdn.
 */
bool calLatinFromJdn( long jdn, DMYDate* dmy, CalendarScheme scheme )
{
    switch( scheme )
    {
    case CALENDAR_SCH_Julian:
        return calJulianFromJdn( jdn, dmy );
    case CALENDAR_SCH_Gregorian:
        return calGregorianFromJdn( jdn, dmy );
    }
    return false;
}

bool calLatinToJdn( long* jdn, int d, int m, int y, CalendarScheme scheme ) 
{
    DMYDate dmy; 
    
    dmy.day = d; 
    dmy.month = m; 
    dmy.year = y;
    return calLatinToJdn( jdn, dmy, scheme );
}

/*! Convert a JDN jdn into a latin style string in the given calendar
 *  scheme and return the string.
 */
wxString calLatinStrFromJdn( long jdn, CalendarScheme scheme )
{
    DMYDate dmy;
    wxString str;

    calLatinFromJdn( jdn, &dmy, scheme );

    str << dmy.day << wxT(" ")
        << calMonthName[0][dmy.month-1]
        << wxT(" ") << dmy.year;

    return str;
}

/*! Convert a JDN range jdn1 to jdn2 into a latin style string in the
 *  given calendar scheme and return the string.
 */
wxString calLatinStrFromJdnRange( long jdn1, long jdn2, CalendarScheme scheme )
{
    if( jdn1 == jdn2 )
    {
        // Format: dd Mmm yyyy
        return calLatinStrFromJdn( jdn1, scheme );
    }

    DMYDate dmy1, dmy2;
    wxString str;

    calLatinFromJdn( jdn1, &dmy1, scheme );
    calLatinFromJdn( jdn2, &dmy2, scheme );

    if( dmy1.day == 1 )
    {
        if( dmy1.year == dmy2.year )
        {
            if( dmy1.month == 1 && dmy2.month == 12 && dmy2.day == 31 )
            {
                // Format: yyyy
                str << dmy1.year;
                return str;
            }
            if( dmy1.month == dmy2.month &&
                dmy2.day == calLastDayInMonth( dmy2.month, dmy2.year, scheme ) )
            {
                // Format: Mmm yyyy
                str << calMonthName[0][dmy1.month-1] << wxT(" ") << dmy1.year;
                return str;
            }
        }
        if( dmy1.month == 1 && dmy2.month == 12 && dmy2.day == 31 )
        {
            // Format: yyyy - yyyy
            str << dmy1.year << wxT(" - ") << dmy2.year;
            return str;
        }
        if( dmy2.day == calLastDayInMonth( dmy2.month, dmy2.year, scheme ) )
        {
            // Format: Mmm yyyy - Mmm yyyy
            str << calMonthName[0][dmy1.month-1] << wxT(" ") << dmy1.year
                << wxT(" - ")
                << calMonthName[0][dmy2.month-1] << wxT(" ") << dmy2.year;
            return str;
        }
    }
    // Format: dd Mmm yyyy - dd Mmm yyyy
    str << dmy1.day << wxT(" ") << calMonthName[0][dmy1.month-1] << wxT(" ") << dmy1.year
        << wxT(" - ")
        << dmy2.day << wxT(" ") << calMonthName[0][dmy2.month-1] << wxT(" ") << dmy2.year;
    return str;
}

/*! Converts the string str into a JDN and sets jdn. Returns true
 *  if successful, else false.
 */
bool calLatinStrToJdn( long* jdn, const wxString& str, CalendarScheme scheme )
{
    DMYDate dmy;

    if( calLatinFromStr( str, dmy ) == false )
    {
        *jdn = 0;
        return false;
    }
    return calLatinToJdn( jdn, dmy, scheme );
}

/*! Converts the string str into a JDN range and sets jdn1 and jdn2.
 *  Returns true if successful, else false.
 */
bool calLatinStrToJdnRange(
    long* jdn1, long* jdn2, const wxString& str, CalendarScheme scheme )
{
    bool ret1 = false, ret2 = false;
    long day, year;
    int month;

    wxArrayString tokens = wxStringTokenize( str );
    *jdn1 = *jdn2 = 0; // error returns should have these set to zero
    size_t count =  tokens.GetCount();
    if( count == 0 ) return false;

    // Format: year1 - year2
    if( count == 3 && tokens[1] == wxT("-") )
    {
        if( tokens[0].ToLong( &year ) == false ) return false;
        ret1 = calLatinToJdn( jdn1, 1, 1, year, scheme );
        if( tokens[2].ToLong( &year ) == false ) return false;
        ret2 = calLatinToJdn( jdn2, 31, 12, year, scheme );
    }
    // Format: Mon1 year1 - Mon2 year2
    else if( count == 5 && tokens[2] == wxT("-") )
    {
        month = calLatinLookUpMonth( tokens[0] );
        if( month == 0 ) return false;
        if( tokens[1].ToLong( &year ) == false ) return false;
        ret1 = calLatinToJdn( jdn1, 1, month, year, scheme );
        month = calLatinLookUpMonth( tokens[3] );
        if( month == 0 ) return false;
        if( tokens[4].ToLong( &year ) == false ) return false;
        day = calLastDayInMonth( month, year, scheme );
        ret2 = calLatinToJdn( jdn2, day, month, year, scheme );
    }
    // Format: day1 Mon1 year1 - day2 Mon2 year2
    else if( count == 7 && tokens[3] == wxT("-") )
    {
        if( tokens[0].ToLong( &day ) == false ) return false;
        month = calLatinLookUpMonth( tokens[1] );
        if( month == 0 ) return false;
        if( tokens[2].ToLong( &year ) == false ) return false;
        ret1 = calLatinToJdn( jdn1, day, month, year, scheme );
        if( tokens[4].ToLong( &day ) == false ) return false;
        month = calLatinLookUpMonth( tokens[5] );
        if( month == 0 ) return false;
        if( tokens[6].ToLong( &year ) == false ) return false;
        ret2 = calLatinToJdn( jdn2, day, month, year, scheme );
    }
    // Format: year
    else if( count == 1 )
    {
        if( tokens[0].ToLong( &year ) == false ) return false;
        ret1 = calLatinToJdn( jdn1, 1, 1, year, scheme );
        ret2 = calLatinToJdn( jdn2, 31, 12, year, scheme );
    }
    // Format: Mon year
    else if( count == 2 )
    {
        month = calLatinLookUpMonth( tokens[0] );
        if( month == 0 ) return false;
        if( tokens[1].ToLong( &year ) == false ) return false;
        ret1 = calLatinToJdn( jdn1, 1, month, year, scheme );
        day = calLastDayInMonth( month, year, scheme );
        ret2 = calLatinToJdn( jdn2, day, month, year, scheme );
    }
    // Format: day Mon year
    else if( count == 3 )
    {
        if( tokens[0].ToLong( &day ) == false ) return false;
        month = calLatinLookUpMonth( tokens[1] );
        if( month == 0 ) return false;
        if( tokens[2].ToLong( &year ) == false ) return false;
        ret1 = calLatinToJdn( jdn1, day, month, year, scheme );
        *jdn2 = *jdn1;
        ret2 = ret1;
    }

    if( ret1 == false || ret2 == false )
    {
        *jdn1 = *jdn2 = 0;
        return false;
    }
    if( *jdn1 > *jdn2 )
    {
        long temp = *jdn1;
        *jdn1 = *jdn2;
        *jdn2 = temp;
    }
    return true;
}

/*! Add to jdn the given value based on the values unit and the given scheme. 
 *  Returns true if successful, else false.
 */
bool calLatinAddToJdn(
    long* jdn, long value, CalendarUnit unit, CalendarScheme scheme )
{
    DMYDate dmy;
    if( !calConvertFromJdn( *jdn, &dmy, scheme ) ) return false;
    switch( unit )
    {
    case CALENDAR_UNIT_Year:
        dmy.year += value;
        break;
    case CALENDAR_UNIT_Month:
        dmy.year += value / 12;
        dmy.month += value % 12;
        if( dmy.month > 12 ) {
            dmy.year++;
            dmy.month -= 12;
        }
        if( dmy.month < 1 ) {
            --dmy.year;
            dmy.month += 12;
        }
        break;
    default:
        return false;
    }
    return calConvertToJdn( jdn, dmy, scheme );
}

// End of calJulian.cpp
