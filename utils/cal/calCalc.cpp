/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calCalc.cpp
 * Project:     CalCalc: Program to test calendar (cal) library.
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

#define VERSION   "0.4.1"
#define PROGNAME  "CalCalc"
#define COPYRIGHT  "2008-2011 Nick Matthews"

const char* g_version = VERSION;
const char* g_progName = PROGNAME;
const char* g_copyright = COPYRIGHT;

#ifdef _DEBUG
const char* g_title = PROGNAME " - Version " VERSION " Debug\n"
                         "Copyright (c) " COPYRIGHT "\n\n";
#else
const char* g_title = PROGNAME " - Version " VERSION "\n"
                         "Copyright (c) " COPYRIGHT "\n\n";
#endif

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
        "\n"
        "Enter one of the following commands:-\n"
        "x date         Enter the date to convert.\n"
        "a age date     Enter age in years & date to convert to birth date range.\n"
        "am age date    Enter age in months & date to convert to birth date range.\n"
        "range          Set to enter and display a date range.\n"
        "single         Set to enter and display a single date.\n"
        "from sch       Set the entered scheme type (see below).\n"
        "to sch         Set the scheme type to convert to.\n"
        "help           Display this screen.\n"
        "exit           Exit the program.\n"
        "\n"
        "sch can be one of the following:-\n"
        "us          Unstated\n"
        "uk          Unknown\n"
        "ul          Unlisted\n"
        "jdn         Julian Day Number\n"
        "jd          Julian Day\n"
        "mjd         Modified Julian Day\n"
        "rd          Rata Die (Fixed Date)\n"
        "j           Julian\n"
        "g           Gregorian\n"
        "cath        Catholic\n"
        "eng         English\n"
        "scot        Scottish\n"
        "swed        Swedish\n"
        "fr          French Revolutionary\n"
        "\n"
    );
}

/*! Convert the given date string
 */
void ccConvertDate( const wxString& datestr )
{
    long jdn1 = -1, jdn2 = -1;
    wxString xdate = "Error reading date";
    bool ret;

    wxString date = datestr;
    date.Trim();
    if( g_range == true )
    {
        ret = calStrToJdnRange( &jdn1, &jdn2, date, g_from );
        if( ret == true )
        {
            xdate = calStrFromJdnRange( jdn1, jdn2, g_to );
        }
        wxPrintf(
            "%s (%s) -> %ld ~ %ld -> %s (%s)\n",
            date.c_str(), CalendarSchemeAbrev[g_from],
            jdn1, jdn2,
            xdate.c_str(), CalendarSchemeAbrev[g_to]
        );
    } else {
        // g_range == false
        ret = calStrToJdn( &jdn1, date, g_from );
        if( ret == true )
        {
            xdate = calStrFromJdn( jdn1, g_to );
        }
        wxPrintf(
            "%s (%s) -> %ld -> %s (%s)\n",
            date.c_str(), CalendarSchemeAbrev[g_from],
            jdn1,
            xdate.c_str(), CalendarSchemeAbrev[g_to]
        );
    }
}

/*! Calculate a date range given an age in years and a single date.
 */
void ccAgeDateToRange( const wxString& line )
{
    wxStringTokenizer tkz;
    wxString token;
    long jdn1, jdn2, year;
    wxString adate;
    bool ret;

    tkz.SetString( line );
    token = tkz.GetNextToken();
    token.ToLong( &year );
    token = tkz.GetString();
    token.Trim();  // Get rid of newline

    if( g_range == true ) {
        ret = calStrToJdnRange( &jdn1, &jdn2, token, g_from );
        if( ret == false ) return;
    } else {
        ret = calStrToJdn( &jdn1, token, g_from );
        if( ret == false ) return;
        jdn2 = jdn1;
    }

    ret = calAddToJdn( &jdn1, -(year+1), CALENDAR_UNIT_Year, g_from );
    jdn1++;
    ret = calAddToJdn( &jdn2, -year, CALENDAR_UNIT_Year, g_from );

    adate = calStrFromJdnRange( jdn1, jdn2, g_to );
    wxPrintf(
        "%ld yrs on %s (%s) -> %ld ~ %ld -> %s (%s)\n",
        year, token.c_str(), CalendarSchemeAbrev[g_from],
        jdn1, jdn2,
        adate.c_str(), CalendarSchemeAbrev[g_to]
    );
}

/*! Calculate a date range given an age in months and a single date.
 */
void ccAgeMonthsDateToRange( const wxString& line )
{
    wxStringTokenizer tkz;
    wxString token;
    long jdn1, jdn2, month;
    wxString adate;
    bool ret;

    tkz.SetString( line );
    token = tkz.GetNextToken();
    token.ToLong( &month );
    token = tkz.GetString();
    token.Trim();  // Get rid of newline

    if( g_range == true ) {
        ret = calStrToJdnRange( &jdn1, &jdn2, token, g_from );
        if( ret == false ) return;
    } else {
        ret = calStrToJdn( &jdn1, token, g_from );
        if( ret == false ) return;
        jdn2 = jdn1;
    }

    ret = calAddToJdn( &jdn1, -(month+1), CALENDAR_UNIT_Month, g_from );
    jdn1++;
    ret = calAddToJdn( &jdn2, -month, CALENDAR_UNIT_Month, g_from );

    adate = calStrFromJdnRange( jdn1, jdn2, g_to );
    wxPrintf(
        "%ld mths on %s (%s) -> %ld ~ %ld -> %s (%s)\n",
        month, token.c_str(), CalendarSchemeAbrev[g_from],
        jdn1, jdn2,
        adate.c_str(), CalendarSchemeAbrev[g_to]
    );
}

/*! Convert the string to a calender scheme.
 */
CalendarScheme ccGetScheme( const wxString& token )
{
    if( token == "us"   ) return CALENDAR_SCH_Unstated;
    if( token == "uk"   ) return CALENDAR_SCH_Unknown;
    if( token == "ul"   ) return CALENDAR_SCH_Unlisted;
    if( token == "jdn"  ) return CALENDAR_SCH_JulianDayNumber;
    if( token == "jd"   ) return CALENDAR_SCH_JulianDay;
    if( token == "mjd"  ) return CALENDAR_SCH_ModJulianDay;
    if( token == "rd"   ) return CALENDAR_SCH_RataDie;
    if( token == "j"    ) return CALENDAR_SCH_Julian;
    if( token == "g"    ) return CALENDAR_SCH_Gregorian;
    if( token == "cath" ) return CALENDAR_SCH_Catholic;
    if( token == "eng"  ) return CALENDAR_SCH_English;
    if( token == "scot" ) return CALENDAR_SCH_Scottish;
    if( token == "swed" ) return CALENDAR_SCH_Swedish;
    if( token == "fr"   ) return CALENDAR_SCH_FrenchRevolution;
    if( token == "i"    ) return CALENDAR_SCH_IslamicTabular;
    if( token == "h"    ) return CALENDAR_SCH_Hebrew;
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
        wxPrintf( "cc: " );
        wxFgets( wxStringBuffer( line, 256 ), 256, stdin );
        if( line == wxT("\n") ) break;
        tkz.SetString( line );
        token = tkz.GetNextToken();
        if( token == wxEmptyString ) continue;

        if( token == "?" || token == "help" ) {
            ccUse();
            continue;
        }
        if( token == "x" )  {
            ccConvertDate( tkz.GetString() );
            continue;
        }
        if( token == "a" ) {
            ccAgeDateToRange( tkz.GetString() );
            continue;
        }
        if( token == "am" ) {
            ccAgeMonthsDateToRange( tkz.GetString() );
            continue;
        }
        if( token == "range" )  {
            g_range = true;
            continue;
        }
        if( token == "single" ) {
            g_range = false;
            continue;
        }
        if( token == "from" )   {
            token = tkz.GetNextToken();
            g_from = ccGetScheme( token );
            wxPrintf(
                "Convert from %s (%s)\n",
                CalendarSchemeName[g_from],
                CalendarSchemeAbrev[g_from]
            );
            continue;
        }
        if( token == "to" ) {
            token = tkz.GetNextToken();
            g_to = ccGetScheme( token );
            wxPrintf( wxT("Convert to %s (%s)\n"),
                CalendarSchemeName[g_to],
                CalendarSchemeAbrev[g_to]
            );
            continue;
        }
        if( token == "exit" ) {
            return 0;
        }
        wxPrintf( " Unrecognized command!\n" );
    }
    return errnum;
}

int main()
{
    int ret = 0;
    if( wxInitialize() == false ) return 1;
    calInit();
    wxPrintf( g_title );
    ret = ccEval();
    calUninit();
    wxUninitialize();
    return ret;
}

// End of calCalc.cpp
