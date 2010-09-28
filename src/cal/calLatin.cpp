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

// Return the month number 1-12 for correct match, or zero if no match
int calLatinLookUpMonth( const wxString str )
{
	int i;
    wxString name = str.Left( 3 ).Upper();

	for( i = 0 ; i < 12 ; i++ )
	{
		if( name.IsSameAs( calMonthName[1][i] ) ) return i+1;
	}
	return 0;
}

// Parse a Latin style date string in the format:  dd mmm... yyyy 
bool calLatinFromStr( const wxString& str, int& day, int& month, int& year )
{
    wxString token;
	bool b;
	int i;
	long lg;
	wxStringTokenizer tkz( str );

    token = tkz.GetNextToken();
	b = token.ToLong( &lg );
	if( b == false ) return false;
	day = (int) lg;

    token = tkz.GetNextToken().Left( 3 ).Upper();
	for( i = 0 ; i < 12 ; i++ )
	{
		if( token.IsSameAs( calMonthName[1][i] ) ) break;
	}
	if( i == 13 ) return false;
	month = i+1;

	token = tkz.GetNextToken();
	b = token.ToLong( &lg );
	if( b == false ) return false;
	year = (int) lg;
	return true;
}

bool calLatinToJdn( long& jdn, int day, int month, int year, CalendarScheme scheme )
{
	switch( scheme )
	{
    case CALENDAR_SCH_Julian:
        return calJulianToJdn( jdn, day, month, year );
    case CALENDAR_SCH_Gregorian:
        return calGregorianToJdn( jdn, day, month, year );
	}
	return false;
}

void calLatinFromJdn( 
    long jdn, int& day, int& month, int& year, CalendarScheme scheme )
{
	switch( scheme )
	{
    case CALENDAR_SCH_Julian:
        calJulianFromJdn( jdn, day, month, year );
		break;
    case CALENDAR_SCH_Gregorian:
        calGregorianFromJdn( jdn, day, month, year );
		break;
	}
}

wxString calLatinStrFromJdn( long jdn, CalendarScheme scheme )
{
	int day, month, year;
	wxString str;

	calLatinFromJdn( jdn, day, month, year, scheme );

	str << day << wxT(" ") 
		<< calMonthName[0][month-1] 
	    << wxT(" ") << year;

	return str;
}

wxString calLatinStrFromJdnRange( long jdn1, long jdn2, CalendarScheme scheme )
{
	if( jdn1 == jdn2 )
	{
		// Format: dd Mmm yyyy
		return calLatinStrFromJdn( jdn1, scheme );
	}

	int day1, month1, year1;
	int day2, month2, year2;
	wxString str;

    calLatinFromJdn( jdn1, day1, month1, year1, scheme );
    calLatinFromJdn( jdn2, day2, month2, year2, scheme );

	if( day1 == 1 )
	{
		if( year1 == year2 )
		{
			if( month1 == 1 && month2 == 12 && day2 == 31 )
			{
				// Format: yyyy
				str << year1;
				return str;
			}
			if( month1 == month2 && 
				day2 == calLastDayInMonth( month2, year2, scheme ) )
			{
				// Format: Mmm yyyy
				str << calMonthName[0][month1-1] << wxT(" ") << year1;
				return str;
			}
		}
		if( month1 == 1 && month2 == 12 && day2 == 31 )
		{
			// Format: yyyy - yyyy
			str << year1 << wxT(" - ") << year2;
			return str;
		}
		if( day2 == calLastDayInMonth( month2, year2, scheme ) )
		{
			// Format: Mmm yyyy - Mmm yyyy
			str << calMonthName[0][month1-1] << wxT(" ") << year1
				<< wxT(" - ")
				<< calMonthName[0][month2-1] << wxT(" ") << year2;
			return str;
		}
	}
	// Format: dd Mmm yyyy - dd Mmm yyyy
	str << day1 << wxT(" ") << calMonthName[0][month1-1] << wxT(" ") << year1
		<< wxT(" - ")
		<< day2 << wxT(" ") << calMonthName[0][month2-1] << wxT(" ") << year2;
	return str;
}

bool calLatinStrToJdn( long& jdn, const wxString& str, CalendarScheme scheme )
{
    int day, month, year;
    
	if( calLatinFromStr( str, day, month, year ) == false ) 
	{
		jdn = 0;
		return false;
	}
    return calLatinToJdn( jdn, day, month, year, scheme );
}

bool calLatinStrToJdnRange( 
    long& jdn1, long& jdn2, const wxString& str, CalendarScheme scheme )
{
	bool ret1 = false, ret2 = false;
	long day, year;
	int month;

	wxArrayString tokens = wxStringTokenize( str );
	jdn1 = jdn2 = 0; // error returns should have these set to zero
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
		jdn2 = jdn1;
		ret2 = ret1;
	}

	if( ret1 == false || ret2 == false )
	{
		jdn1 = jdn2 = 0;
		return false;
	}
	if( jdn1 > jdn2 )
	{
		long temp = jdn1;
		jdn1 = jdn2;
		jdn2 = temp;
	}
	return true;
}

// End of calJulian.cpp
