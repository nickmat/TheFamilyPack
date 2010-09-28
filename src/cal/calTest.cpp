/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Project: TFP  The Family Pack for wxWidgets *  Written by: Nick Matthews  *
 *  Module: Test Calendar functions            *  Date Started: 26 Jul 2008  *
 *    File: CalTest.cpp         Type: C Source *  Date Revised: 22 Nov 2008  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    Copyright (c) 2008, Nick Matthews

*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "calendar.h"
#include "calLatin.h"

// if this is defined, create a command line date calculator
#define CAL_CALC

#ifndef CAL_CALC
// Set this define to limit testing to a single module or to all modules
#define TEST_ALL
#define TEST_STRINGS  /* May be slow */
//#define TEST_JULIAN
//#define TEST_GREGORIAN


#ifdef TEST_ALL
#define TEST_JULIAN
#define TEST_GREGORIAN
#endif // TEST_ALL
#endif // CAL_CALC

#define TEST_ASSERT( condition )   AssertTrue( condition, __LINE__, #condition )

int g_test_success_count = 0;

void AssertTrue( bool condition, int line, const char* msg )
{
    if( !(condition) )
    {
        wxPrintf( wxT("FAILURE!\n") );
        wxPrintf( wxT("Line: '%d', %s\n"), line, wxString( msg, *wxConvCurrent) );
        exit(1);
    }
    ++g_test_success_count;
}

#ifdef TEST_JULIAN

void TestCalJulian() 
{
    int LengthOfMonth[2][12] = {
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };

    wxPrintf( wxT("Testing Julian module\n") );
#ifdef TEST_STRINGS
    wxPrintf( wxT("Including String convertions\n") );
#endif // TEST_STRINGS
    long prev_jd;
	TEST_ASSERT( calJulianToJdn( prev_jd, 31, 12, -1001 ) );
    TEST_ASSERT( prev_jd == 1355807L );
    for( int year = -1000 ; year < 2150 ; ++year )
    {
        size_t leap_year = ( year % 4 == 0 ) ? 1 : 0;
        size_t tleap_year = ( calJulianIsLeapYear( year ) == true ) ? 1 : 0;
        if( tleap_year != leap_year )
        {
            wxPrintf( wxT("year=%d leap_year=%d\n"), year, leap_year );
        }
        TEST_ASSERT( tleap_year == leap_year );
        for( int month = 1 ; month <= 12 ; ++month )
        {
            int month_length = LengthOfMonth[leap_year][month-1];
            int tmonth_length = calJulianLastDayInMonth( month, year );
            if( tmonth_length != month_length )
            {
                wxPrintf( wxT("month_length=%d, month=%d, year=%d\n"), tmonth_length, month, year );
            }
            TEST_ASSERT( tmonth_length == month_length );
            for( int day = 1 ; day <= month_length ; ++day )
            {
                long jd;
				TEST_ASSERT( calJulianToJdn( jd, day, month, year ) );
                if( jd != prev_jd+1 )
                {
                    wxPrintf( wxT("day=%d, month=%d, year=%d\n"), day, month, year );
                    wxPrintf( wxT("prev_jd=%ld, jd=%ld, leap_year=%d\n"), prev_jd, jd, leap_year );
                }
                TEST_ASSERT( jd == prev_jd+1 );
                ++prev_jd;

                int tday, tmonth, tyear;
                calJulianFromJdn( jd, tday, tmonth, tyear );
                if( tday != day || tmonth != month || tyear != year )
                {
                    wxPrintf( wxT("jd=%ld, leap_year=%d\n"), jd, leap_year );
                    wxPrintf( wxT(" day=%d,  month=%d,  year=%d\n"), day, month, year );
                    wxPrintf( wxT("tday=%d, tmonth=%d, tyear=%d\n"), tday, tmonth, tyear );
                }
                TEST_ASSERT( tday == day );
                TEST_ASSERT( tmonth == month );
                TEST_ASSERT( tyear == year );
#ifdef TEST_STRINGS
				wxString tstr = calStrFromJdn( jd, CALENDAR_SCH_Julian );
				if( tstr == wxEmptyString )
				{
                    wxPrintf( wxT("jd=%ld CalendarScheme=\n"), jd, CALENDAR_SCH_Julian );
				}
				TEST_ASSERT( tstr != wxEmptyString );
				long tjd;
				TEST_ASSERT( calStrToJdn( tjd, tstr, CALENDAR_SCH_Julian ) );
				if( tjd != jd )
				{
                    wxPrintf( wxT("tjd=%ld, jd=%ld\n"), tjd, jd );
                    wxPrintf( wxT("tstr=%s CalendarScheme=\n"), tstr.c_str(), CALENDAR_SCH_Julian );
				}
                TEST_ASSERT( tjd == jd );
#endif // TEST_STRINGS
			}
        }
    }
}
#endif // TEST_JULIAN

#ifdef TEST_GREGORIAN

void TestCalGregorian() 
{
    int LengthOfMonth[2][12] = {
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };

    wxPrintf( wxT("Testing Gregorian module\n") );
#ifdef TEST_STRINGS
    wxPrintf( wxT("Including String convertions\n") );
#endif // TEST_STRINGS
    long prev_jd;
	TEST_ASSERT( calGregorianToJdn( prev_jd, 31, 12, -1001 ) );
    if( prev_jd != 1355817L )
    {
        wxPrintf( wxT("31 Dec -1001 Greg to %ld JD\n"), prev_jd );
    }
    TEST_ASSERT( prev_jd == 1355817L );
    for( int year = -1000 ; year < 2150 ; ++year )
    {
        size_t leap_year = ( year % 4 == 0 ) ? 1 : 0;
        if( year % 100 == 0 ) leap_year = 0;
        if( year % 400 == 0 ) leap_year = 1;
        size_t tleap_year = ( calGregorianIsLeapYear( year ) == true ) ? 1 : 0;
        if( tleap_year != leap_year )
        {
            wxPrintf( wxT("year=%d, tleap_year=%d, leap_year=%d\n"), year, tleap_year, leap_year );
        }
        TEST_ASSERT( tleap_year == leap_year );
        for( long month = 1 ; month <= 12 ; ++month )
        {
            int month_length = LengthOfMonth[leap_year][month-1];
            int tmonth_length = calGregorianLastDayInMonth( month, year );
            if( tmonth_length != month_length )
            {
                wxPrintf( wxT("month_length=%d, month=%d, year=%d\n"), tmonth_length, month, year );
            }
            TEST_ASSERT( tmonth_length == month_length );
            for( int day = 1 ; day <= month_length ; ++day )
            {
                long jd;
				TEST_ASSERT( calGregorianToJdn( jd, day, month, year ) );
                if( jd != prev_jd+1 )
                {
                    wxPrintf( wxT("day=%d, month=%d, year=%d\n"), day, month, year );
                    wxPrintf( wxT("prev_jd=%ld, jd=%ld, leap_year=%d\n"), prev_jd, jd, leap_year );
                }
                TEST_ASSERT( jd == prev_jd+1 );
                ++prev_jd;
                int tday, tmonth, tyear;
                calGregorianFromJdn( jd, tday, tmonth, tyear );
                if( tday != day || tmonth != month || tyear != year )
                {
                    wxPrintf( wxT("jd=%d, leap_year=%d\n"), jd, leap_year );
                    wxPrintf( wxT(" day=%d,  month=%d,  year=%d\n"), day, month, year );
                    wxPrintf( wxT("tday=%d, tmonth=%d, tyear=%d\n"), tday, tmonth, tyear );
                }
                TEST_ASSERT( tday == day );
                TEST_ASSERT( tmonth == month );
                TEST_ASSERT( tyear == year );
#ifdef TEST_STRINGS
				wxString tstr = calStrFromJdn( jd, CALENDAR_SCH_Gregorian );
				if( tstr == wxEmptyString )
				{
                    wxPrintf( wxT("jd=%ld CalendarScheme=\n"), jd, CALENDAR_SCH_Gregorian );
				}
				TEST_ASSERT( tstr != wxEmptyString );
				long tjd;
				TEST_ASSERT( calStrToJdn( tjd, tstr, CALENDAR_SCH_Gregorian ) );
				if( tjd != jd )
				{
                    wxPrintf( wxT("tjd=%ld, jd=%ld\n"), tjd, jd );
                    wxPrintf( wxT("tstr=%s CalendarScheme=\n"), tstr.c_str(), CALENDAR_SCH_Gregorian );
				}
                TEST_ASSERT( tjd == jd );
#endif // TEST_STRINGS
           }
        }
    }
}
#endif // TEST_GREGORIAN

#ifdef CAL_CALC
#include <stdio.h>
#include "wx/app.h"
#include "wx/tokenzr.h"

bool g_range = false;
CalendarScheme g_from = CALENDAR_SCH_Gregorian;
CalendarScheme g_to = CALENDAR_SCH_Gregorian;

void ccUse()
{
	wxPrintf(
		wxT("\n")
		wxT("Enter one of the following commands:-\n")
		wxT("x date      Enter the date to convert\n")
		wxT("a age date  Enter age & date to convert to birth date range\n")
		wxT("range       Set to enter and display a date range\n")
		wxT("single      Set to enter and display a single date\n")
		wxT("from sch    Set the entered scheme type (see below)\n")
		wxT("to sch      Set the scheme type to convert to\n")
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

void ccAgeDateToRange( wxString& line )
{
  	wxStringTokenizer tkz;
    wxString token;
	long age, jdn1, jdn2;
	bool ret;
	int day, month, year;
	wxString adate;

    tkz.SetString( line );
    token = tkz.GetNextToken();
	token.ToLong( &age );
	token = tkz.GetString();
	token.Trim();  // Get rid of newline
	ret = calLatinFromStr( token, day, month, year );
	if( ret == false ) return;
	year -= age;
	ret = calLatinToJdn( jdn2, day, month, year, g_from );
	if( ret == false ) return;
	--year;
	ret = calLatinToJdn( jdn1, day, month, year, g_from );
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

int ccEval()
{
	int errnum = 0;
    wxString line;
    wxString token;
  	wxStringTokenizer tkz;

	for(;;)
	{
		wxPrintf( wxT("cc: ") );
        wxFgets( line.GetWriteBuf( 256 ), 256, stdin );
		line.UngetWriteBuf();
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
		wxPrintf( wxT(" Unrecognized command!\n") );
	}
	return errnum;
}

#endif // CAL_CALC

int main()
{
	int ret = 0;
	if( wxInitialize() == false ) return 1;
#ifdef CAL_CALC
	wxPrintf( 
		wxT("CalCalc: the Calendar Calculator v0.2.1\n") 
		wxT("Copyright (c) 2008 Nick Matthews\n") 
		wxT("\n") 
	);
    ret = ccEval();
#else // ! CAL_CALC
#ifdef TEST_JULIAN
    TestCalJulian();
#endif // TEST_JULIAN

#ifdef TEST_GREGORIAN
    TestCalGregorian();
#endif // TEST_GREGORIAN

    wxPrintf( wxT("SUCCESS!\n") );
    wxPrintf( wxT("%d tests completed successfully\n"), g_test_success_count );
#endif // CAL_CALC
	wxUninitialize();
    return ret;
}

// End of CalTest.cpp