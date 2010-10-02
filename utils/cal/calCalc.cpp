/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calCalc.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Commandline Calendar Calculator for testing library.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     2 October 2010
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

#include <stdio.h>
#include <wx/app.h>
#include <wx/tokenzr.h>

#include "cal/calendar.h"

/*! True if in range mode, false if in single day mode.
 */
bool g_range = false;

/*! The calendar scheme assumed for input date.
 */
CalendarScheme g_from = CALENDAR_SCH_Gregorian;

/*! The calendar scheme assumed for the output date.
 */
CalendarScheme g_to = CALENDAR_SCH_Gregorian;

/*! Display useage screen
 */
void ccUse()
{
	wxPrintf(
		wxT("\n")
		wxT("Enter one of the following commands:-\n")
		wxT("x date      Enter the date to convert.\n")
		wxT("a age date  Enter age & date to convert to birth date range.\n")
		wxT("range       Set to enter and display a date range.\n")
		wxT("single      Set to enter and display a single date.\n")
		wxT("from sch    Set the entered scheme type (see below).\n")
		wxT("to sch      Set the scheme type to convert to.\n")
		wxT("help        Display this screen.\n")
		wxT("exit        Exit the program.\n")
		wxT("\n")
		wxT("sch can be one of the following:-\n")
		wxT("us          Unstated\n")
		wxT("uk          Unknown\n")
		wxT("ul          Unlisted\n")
		wxT("jdn         Julian Day Number\n")
		wxT("jd          Julian Day\n")
		wxT("mjd         Modified Julian Day\n")
		wxT("rd          Rata Die (Fixed Date)\n")
		wxT("j           Julian\n")
		wxT("g           Gregorian\n")
		wxT("cath        Catholic\n")
		wxT("eng         English\n")
		wxT("scot        Scottish\n")
		wxT("swed        Swedish\n")
		wxT("fr          French Revolutionary\n")
		wxT("\n")
	);
}

/*! Convert the given date string
 */
void ccConvertDate( wxString& date )
{
	long jdn1 = -1, jdn2 = -1;
	wxString xdate = wxT("Error reading date");
	bool ret;

	date.Trim();
	if( g_range == true )
	{
        ret = calStrToJdnRange( jdn1, jdn2, date, g_from );
		if( ret == true )
		{
			xdate = calStrFromJdnRange( jdn1, jdn2, g_to );
		}
		wxPrintf( 
			wxT("%s (%s) -> %ld - %ld -> %s (%s)\n"),
			date.c_str(), CalendarSchemeAbrev[g_from].c_str(),
			jdn1, jdn2,
			xdate.c_str(), CalendarSchemeAbrev[g_to].c_str()
		);
	} else { 
		// g_range == false
        ret = calStrToJdn( jdn1, date, g_from );
		if( ret == true )
		{
			xdate = calStrFromJdn( jdn1, g_to );
		}
		wxPrintf( 
			wxT("%s (%s) -> %ld -> %s (%s)\n"),
			date.c_str(), CalendarSchemeAbrev[g_from].c_str(),
			jdn1,
			xdate.c_str(), CalendarSchemeAbrev[g_to].c_str()
		);
	}
}

/*! Calculate a date range given an age and a single date.
 */
void ccAgeDateToRange( wxString& line )
{
  	wxStringTokenizer tkz;
    wxString token;
	long age, jdn, jdn1, jdn2;
    DMYDate dmy;
	wxString adate;
	bool ret;

    tkz.SetString( line );
    token = tkz.GetNextToken();
	token.ToLong( &age );
	token = tkz.GetString();
	token.Trim();  // Get rid of newline

    ret = calStrToJdn( jdn, token, g_from );
	if( ret == false ) return;
    ret = calConvertFromJdn( jdn, dmy, g_from );
	if( ret == false ) return;
	dmy.year -= age;
	ret = calConvertToJdn( jdn2, dmy, g_from );
	if( ret == false ) return;
	--dmy.year;
	ret = calConvertToJdn( jdn1, dmy, g_from );
	if( ret == false ) return;
	++jdn1;
	adate = calStrFromJdnRange( jdn1, jdn2, g_to );
	wxPrintf( 
		wxT("%ld yrs on %s (%s) -> %ld - %ld -> %s (%s)\n"),
		age, token.c_str(), CalendarSchemeAbrev[g_from].c_str(),
		jdn1, jdn2,
		adate.c_str(), CalendarSchemeAbrev[g_to].c_str()
	);
}

/*! Convert the string to a calender scheme.
 */
CalendarScheme ccGetScheme( wxString& token )
{
    if( token == wxT("us")   ) return CALENDAR_SCH_Unstated;	
    if( token == wxT("uk")   ) return CALENDAR_SCH_Unknown;	
    if( token == wxT("ul")   ) return CALENDAR_SCH_Unlisted;	
    if( token == wxT("jdn")  ) return CALENDAR_SCH_JulianDayNumber;	
    if( token == wxT("jd")   ) return CALENDAR_SCH_JulianDay;	
    if( token == wxT("mjd")  ) return CALENDAR_SCH_ModJulianDay;	
    if( token == wxT("rd")   ) return CALENDAR_SCH_RataDie;	
    if( token == wxT("j")    ) return CALENDAR_SCH_Julian;	
    if( token == wxT("g")    ) return CALENDAR_SCH_Gregorian;	
    if( token == wxT("cath") ) return CALENDAR_SCH_Catholic;	
    if( token == wxT("eng")  ) return CALENDAR_SCH_English;	
    if( token == wxT("scot") ) return CALENDAR_SCH_Scottish;	
    if( token == wxT("swed") ) return CALENDAR_SCH_Swedish;	
    if( token == wxT("fr")   ) return CALENDAR_SCH_FrenchRevolution;	
    return CALENDAR_SCH_Unstated;	    
}

/*! Run the Calculator.
 */
int ccEval()
{
	int errnum = 0;
    wxString line;
    wxString token;
  	wxStringTokenizer tkz;

	for(;;)
	{
		wxPrintf( wxT("cc: ") );
        wxFgets( wxStringBuffer( line, 256 ), 256, stdin );
		if( line == wxT("\n") ) break;
        tkz.SetString( line );
        token = tkz.GetNextToken();
        if( token == wxEmptyString ) continue;

		if( token == wxT("?") || token == wxT("help") ) {
			ccUse();
            continue;
		}
		if( token == wxT("x") )	{
            ccConvertDate( tkz.GetString() );
			continue;
		}
		if( token == wxT("a") ) {
			ccAgeDateToRange( tkz.GetString() );
			continue;
		}
		if( token == wxT("range") )	{
			g_range = true;
            continue;
		}
		if( token == wxT("single") ) {
			g_range = false;
            continue;
		}
		if( token == wxT("from") )	{
            token = tkz.GetNextToken();
			g_from = ccGetScheme( token );
			wxPrintf( wxT("Convert from %s (%s)\n"), 
				CalendarSchemeName[g_from].c_str(),
				CalendarSchemeAbrev[g_from].c_str()
			);
			continue;
		}
		if( token == wxT("to") )	{
            token = tkz.GetNextToken();
			g_to = ccGetScheme( token );
			wxPrintf( wxT("Convert to %s (%s)\n"), 
				CalendarSchemeName[g_to].c_str(),
				CalendarSchemeAbrev[g_to].c_str()
			);
			continue;
		}
        if( token == wxT("exit") ) {
            return 0;
        }
		wxPrintf( wxT(" Unrecognized command!\n") );
	}
	return errnum;
}

int main()
{
	int ret = 0;
	if( wxInitialize() == false ) return 1;
	wxPrintf( 
		wxT("CalCalc: the Calendar Calculator v0.3.0\n") 
		wxT("Copyright (c) 2008-2010 Nick Matthews\n") 
		wxT("\n") 
	);
    ret = ccEval();
	wxUninitialize();
    return ret;
}

// End of calCalc.cpp
