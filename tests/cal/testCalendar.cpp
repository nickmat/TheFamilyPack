/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        testCalendar.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     CppUnit test program for the calendar library
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     30th September 2010
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

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif // WX_PRECOMP

#include "wx/sstream.h"

#include "cal/calendar.h"

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class CalTestCase : public CppUnit::TestCase
{
public:
    CalTestCase() {}

private:
    CPPUNIT_TEST_SUITE( CalTestCase );
        CPPUNIT_TEST( TestTable );
        CPPUNIT_TEST( TestJulian );
        CPPUNIT_TEST( TestGregorian );
        CPPUNIT_TEST( TestAdd );
    CPPUNIT_TEST_SUITE_END();

    void TestTable();
    void TestJulian();
    void TestGregorian();

    void TestAdd();

    DECLARE_NO_COPY_CLASS(CalTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( CalTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CalTestCase, "CalTestCase" );

// Define one, and only one, of the following
//#define CALTEST_LONG
//#define CALTEST_SHORT
#define CALTEST_BRIEF

struct DMYt {
    long day;
    long month;
    long year;
};

inline bool operator==(const DMYt& d1, const DMYt& d2)
{
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}


struct SampleDate {
    long jdn;
    long rd;
    double jd;
    long mjd;
    DMYt g;
    DMYt j;
};

/*! Size of SampleList array.
 */
const int MaxSample = 33;

/*! Taken from the Sample Table given in Appendix C
 *  of the book "Calendrical Calculations" by Nachum Dershowitz
 *  and Edward M. Reingold.
 */
SampleDate SampleList[MaxSample] = {
    //                                         Gregorian          Julian
    //  JDN       RD      JD         MJD      d   m     y       d   m     y
    { 1507232,-214193, 1507231.5, -892769, { 24,  7, -586 }, { 30,  7, -586 } },
    { 1660038, -61387, 1660037.5, -739963, {  5, 12, -168 }, {  8, 12, -168 } },
    { 1746894,  25469, 1746893.5, -653107, { 24,  9,   70 }, { 26,  9,   70 } },
    { 1770642,  49217, 1770641.5, -629359, {  2, 10,  135 }, {  3, 10,  135 } },
    { 1892732, 171307, 1892731.5, -507269, {  8,  1,  470 }, {  7,  1,  470 } },
    { 1931580, 210155, 1931579.5, -468421, { 20,  5,  576 }, { 18,  5,  576 } },
    { 1974852, 253427, 1974851.5, -425149, { 10, 11,  694 }, {  7, 11,  694 } },
    { 2091165, 369740, 2091164.5, -308836, { 25,  4, 1013 }, { 19,  4, 1013 } },
    { 2121510, 400085, 2121509.5, -278491, { 24,  5, 1096 }, { 18,  5, 1096 } },
    { 2155780, 434355, 2155779.5, -244221, { 23,  3, 1190 }, { 16,  3, 1190 } },
    { 2174030, 452605, 2174029.5, -225971, { 10,  3, 1240 }, {  3,  3, 1240 } },
    { 2191585, 470160, 2191584.5, -208416, {  2,  4, 1288 }, { 26,  3, 1288 } },
    { 2195262, 473837, 2195261.5, -204739, { 27,  4, 1298 }, { 20,  4, 1298 } },
    { 2229275, 507850, 2229274.5, -170726, { 12,  6, 1391 }, {  4,  6, 1391 } },
    { 2245581, 524156, 2245580.5, -154420, {  3,  2, 1436 }, { 25,  1, 1436 } },
    { 2266101, 544676, 2266100.5, -133900, {  9,  4, 1492 }, { 31,  3, 1492 } },
    { 2288543, 567118, 2288542.5, -111458, { 19,  9, 1553 }, {  9,  9, 1553 } },
    { 2290902, 569477, 2290901.5, -109099, {  5,  3, 1560 }, { 24,  2, 1560 } },
    { 2323141, 601716, 2323140.5,  -76860, { 10,  6, 1648 }, { 31,  5, 1648 } },
    { 2334849, 613424, 2334848.5,  -65152, { 30,  6, 1680 }, { 20,  6, 1680 } },
    { 2348021, 626596, 2348020.5,  -51980, { 24,  7, 1716 }, { 13,  7, 1716 } },
    { 2366979, 645554, 2366978.5,  -33022, { 19,  6, 1768 }, {  8,  6, 1768 } },
    { 2385649, 664224, 2385648.5,  -14352, {  2,  8, 1819 }, { 21,  7, 1819 } },
    { 2392826, 671401, 2392825.5,   -7175, { 27,  3, 1839 }, { 15,  3, 1839 } },
    { 2416224, 694799, 2416223.5,   16223, { 19,  4, 1903 }, {  6,  4, 1903 } },
    { 2425849, 704424, 2425848.5,   25848, { 25,  8, 1929 }, { 12,  8, 1929 } },
    { 2430267, 708842, 2430266.5,   30266, { 29,  9, 1941 }, { 16,  9, 1941 } },
    { 2430834, 709409, 2430833.5,   30833, { 19,  4, 1943 }, {  6,  4, 1943 } },
    { 2431005, 709580, 2431004.5,   31004, {  7, 10, 1943 }, { 24,  9, 1943 } },
    { 2448699, 727274, 2448698.5,   48698, { 17,  3, 1992 }, {  4,  3, 1992 } },
    { 2450139, 728714, 2450138.5,   50138, { 25,  2, 1996 }, { 12,  2, 1996 } },
    { 2465738, 744313, 2465737.5,   65737, { 10, 11, 2038 }, { 28, 10, 2038 } },
    { 2486077, 764652, 2486076.5,   86076, { 18,  7, 2094 }, {  5,  7, 2094 } }
};

void CalTestCase::TestTable()
{
    long jdn;//, num;
//    double dbl;
    DMYt dmy;

    for( int i = 0 ; i < MaxSample ; i++ ) {
#if 0   
        // Support for RataDie  currently dropped
        calConvertFromJdn( SampleList[i].jdn, &num, CALENDAR_SCH_RataDie );
        CPPUNIT_ASSERT( num == SampleList[i].rd );
        calConvertToJdn( &jdn, SampleList[i].rd, CALENDAR_SCH_RataDie );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        // Support for Julian Day  currently dropped
        calConvertFromJdn( SampleList[i].jdn, &dbl, CALENDAR_SCH_JulianDay );
        // We shouldn't really equate doubles here - but it should work ok.
        CPPUNIT_ASSERT( dbl == SampleList[i].jd );
        calConvertToJdn( &jdn, SampleList[i].jd, CALENDAR_SCH_JulianDay );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        // Support for Modified Julian Day  currently dropped
        calConvertFromJdn( SampleList[i].jdn, &num, CALENDAR_SCH_ModJulianDay );
        CPPUNIT_ASSERT( num == SampleList[i].mjd );
        calConvertToJdn( &jdn, SampleList[i].mjd, CALENDAR_SCH_ModJulianDay );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );
#endif

//        calConvertFromJdn( SampleList[i].jdn, &dmy, CALENDAR_SCH_Gregorian );
        calConvertFromJdn( SampleList[i].jdn, CALENDAR_SCH_Gregorian,
            &dmy.year, &dmy.month, &dmy.day );
        CPPUNIT_ASSERT( dmy.day == SampleList[i].g.day );
        CPPUNIT_ASSERT( dmy.month == SampleList[i].g.month );
        CPPUNIT_ASSERT( dmy.year == SampleList[i].g.year );
//        calConvertToJdn( &jdn, SampleList[i].g, CALENDAR_SCH_Gregorian );
        calConvertToJdn( &jdn, CALENDAR_SCH_Gregorian, 
            SampleList[i].g.year, SampleList[i].g.month, SampleList[i].g.day );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

//        calConvertFromJdn( SampleList[i].jdn, &dmy, CALENDAR_SCH_Julian );
        calConvertFromJdn( SampleList[i].jdn, CALENDAR_SCH_Julian,
            &dmy.year, &dmy.month, &dmy.day );
        CPPUNIT_ASSERT( dmy.day == SampleList[i].j.day );
        CPPUNIT_ASSERT( dmy.month == SampleList[i].j.month );
        CPPUNIT_ASSERT( dmy.year == SampleList[i].j.year );
//        calConvertToJdn( &jdn, SampleList[i].j, CALENDAR_SCH_Julian );
        calConvertToJdn( &jdn, CALENDAR_SCH_Julian, 
            SampleList[i].j.year, SampleList[i].j.month, SampleList[i].j.day );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );
    }
}

#ifdef CALTEST_LONG
#define CALTEST_J_START_YEAR     -1000
#define CALTEST_J_START_PREV_JDN 1355807L
#define CALTEST_J_END_YEAR       2150
#endif

#ifdef CALTEST_SHORT
#define CALTEST_J_START_YEAR     1200
#define CALTEST_J_START_PREV_JDN 2159357L
#define CALTEST_J_END_YEAR       2050
#endif

#ifdef CALTEST_BRIEF
#define CALTEST_J_START_YEAR     1890
#define CALTEST_J_START_PREV_JDN 2411380L
#define CALTEST_J_END_YEAR       2010
#endif

static bool IsLeapYearJulian( long year )
{
    return ( year % 4 ) == 0;
}

void CalTestCase::TestJulian()
{
    int LengthOfMonth[2][12] = {
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };
    DMYt dmy;
    long prev_jd;

    dmy.day = 31; dmy.month = 12; dmy.year = CALTEST_J_START_YEAR-1;
//    CPPUNIT_ASSERT( calConvertToJdn( &prev_jd, dmy, CALENDAR_SCH_Julian ) );
    CPPUNIT_ASSERT( calConvertToJdn( &prev_jd, CALENDAR_SCH_Julian, dmy.year, dmy.month, dmy.day ) );
    CPPUNIT_ASSERT( prev_jd == CALTEST_J_START_PREV_JDN );

    for( dmy.year = CALTEST_J_START_YEAR ; 
        dmy.year < CALTEST_J_END_YEAR ; ++dmy.year )
    {
        size_t leap_year = ( dmy.year % 4 == 0 ) ? 1 : 0;
//        size_t tleap_year = ( calIsLeapYear( dmy.year, CALENDAR_SCH_Julian ) == true ) ? 1 : 0;
        size_t tleap_year = ( IsLeapYearJulian( dmy.year ) == true ) ? 1 : 0;
        CPPUNIT_ASSERT( tleap_year == leap_year );
        for( dmy.month = 1 ; dmy.month <= 12 ; ++dmy.month )
        {
            int month_length = LengthOfMonth[leap_year][dmy.month-1];
            int tmonth_length = calLastDayInMonth( dmy.month, dmy.year, CALENDAR_SCH_Julian );
            CPPUNIT_ASSERT( tmonth_length == month_length );
            for( dmy.day = 1 ; dmy.day <= month_length ; ++dmy.day )
            {
                long jd;
//				CPPUNIT_ASSERT( calConvertToJdn( &jd, dmy, CALENDAR_SCH_Julian ) );
                CPPUNIT_ASSERT( calConvertToJdn( &jd, CALENDAR_SCH_Julian, dmy.year, dmy.month, dmy.day ) );
                CPPUNIT_ASSERT( jd == prev_jd+1 );
                ++prev_jd;

                DMYt tdmy;
//                calConvertFromJdn( jd, &tdmy, CALENDAR_SCH_Julian );
                calConvertFromJdn( jd, CALENDAR_SCH_Julian,
                    &tdmy.year, &tdmy.month, &tdmy.day );
                CPPUNIT_ASSERT( tdmy == dmy );
			}
        }
    }
}

#ifdef CALTEST_LONG
#define CALTEST_G_START_YEAR     -1000
#define CALTEST_G_START_PREV_JDN 1355817L
#define CALTEST_G_END_YEAR       2150
#endif

#ifdef CALTEST_SHORT
#define CALTEST_G_START_YEAR     1200
#define CALTEST_G_START_PREV_JDN 2159350L
#define CALTEST_G_END_YEAR       2050
#endif

#ifdef CALTEST_BRIEF
#define CALTEST_G_START_YEAR     1890
#define CALTEST_G_START_PREV_JDN 2411368L
#define CALTEST_G_END_YEAR       2010
#endif

bool IsLeapYearGregorian( long year )
{
    return ( year%4 == 0 && year%100 != 0 ) || year%400 == 0;
}

void CalTestCase::TestGregorian()
{
    int LengthOfMonth[2][12] = {
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };
    DMYt dmy;
    long prev_jd;

    dmy.day = 31; dmy.month = 12; dmy.year = CALTEST_G_START_YEAR-1;
//    CPPUNIT_ASSERT( calConvertToJdn( &prev_jd, dmy, CALENDAR_SCH_Gregorian ) );
    CPPUNIT_ASSERT( calConvertToJdn( &prev_jd, CALENDAR_SCH_Gregorian, dmy.year, dmy.month, dmy.day ) );
    CPPUNIT_ASSERT( prev_jd == CALTEST_G_START_PREV_JDN );

    for( dmy.year = CALTEST_G_START_YEAR ; 
        dmy.year < CALTEST_G_END_YEAR ; ++dmy.year )
    {
        size_t leap_year;
        leap_year = ( dmy.year % 4 == 0 ) ? 1 : 0;
        leap_year = ( dmy.year % 100 == 0 ) ? 0 : leap_year;
        leap_year = ( dmy.year % 400 == 0 ) ? 1 : leap_year;
//        size_t tleap_year = ( calIsLeapYear( dmy.year, CALENDAR_SCH_Gregorian ) == true ) ? 1 : 0;
        size_t tleap_year = ( IsLeapYearGregorian( dmy.year ) == true ) ? 1 : 0;
        CPPUNIT_ASSERT( tleap_year == leap_year );
        for( dmy.month = 1 ; dmy.month <= 12 ; ++dmy.month )
        {
            int month_length = LengthOfMonth[leap_year][dmy.month-1];
            int tmonth_length = calLastDayInMonth( dmy.month, dmy.year, CALENDAR_SCH_Gregorian );
            CPPUNIT_ASSERT( tmonth_length == month_length );
            for( dmy.day = 1 ; dmy.day <= month_length ; ++dmy.day )
            {
                long jd;
//				CPPUNIT_ASSERT( calConvertToJdn( &jd, dmy, CALENDAR_SCH_Gregorian ) );
                CPPUNIT_ASSERT( calConvertToJdn( &jd, CALENDAR_SCH_Gregorian, dmy.year, dmy.month, dmy.day ) );
                CPPUNIT_ASSERT( jd == prev_jd+1 );
                ++prev_jd;

                DMYt tdmy;
//                calConvertFromJdn( jd, &tdmy, CALENDAR_SCH_Gregorian );
                calConvertFromJdn( jd, CALENDAR_SCH_Gregorian,
                    &tdmy.year, &tdmy.month, &tdmy.day );
                CPPUNIT_ASSERT( tdmy == dmy );
			}
        }
    }
}

void CalTestCase::TestAdd()
{
    long jdn1, jdn2;
    long year, month, day;
    CalendarScheme sch = CALENDAR_SCH_Gregorian;

    jdn1 = jdn2 = 2455611; // 18 Feb 2011 (G)
    year = 62;
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -(year+1), CALENDAR_UNIT_Year, sch ) );
    jdn1++;
    CPPUNIT_ASSERT( jdn1 == 2432601 );  // 19 Feb 1948 (G)
    CPPUNIT_ASSERT( calAddToJdn( &jdn2, -year, CALENDAR_UNIT_Year, sch ) );
    CPPUNIT_ASSERT( jdn2 == 2432966 );  // 18 Feb 1949 (G)

    jdn1 = jdn2 = 2455459; // 19 Sep 2010 (G)
    year = 62;
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -(year+1), CALENDAR_UNIT_Year, sch ) );
    jdn1++;
    CPPUNIT_ASSERT( jdn1 == 2432449 );  // 20 Sep 1947 (G)
    CPPUNIT_ASSERT( calAddToJdn( &jdn2, -year, CALENDAR_UNIT_Year, sch ) );
    CPPUNIT_ASSERT( jdn2 == 2432814 );  // 19 Sep 1948 (G)

    jdn1 = jdn2 = 2455458; // 18 Sep 2010 (G)
    year = 61;
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -(year+1), CALENDAR_UNIT_Year, sch ) );
    jdn1++;
    CPPUNIT_ASSERT( jdn1 == 2432814 );  // 19 Sep 1948 (G)
    CPPUNIT_ASSERT( calAddToJdn( &jdn2, -year, CALENDAR_UNIT_Year, sch ) );
    CPPUNIT_ASSERT( jdn2 == 2433178 );  // 18 Sep 1949 (G)

    jdn1 = jdn2 = 2432814; // 19 Sep 1948 (G)
    month = 10;
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -(month+1), CALENDAR_UNIT_Month, sch ) );
    jdn1++;
    CPPUNIT_ASSERT( jdn1 == 2432479 );  // 20 Oct 1947 (G)
    CPPUNIT_ASSERT( calAddToJdn( &jdn2, -month, CALENDAR_UNIT_Month, sch ) );
    CPPUNIT_ASSERT( jdn2 == 2432509 );  // 19 Nov 1947 (G)

    jdn1 = 2432613; // 2 Mar 1948 (G)
    jdn2 = 2432978; // 2 Mar 1949 (G)
    day = 4;
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -(day+1), CALENDAR_UNIT_Day, sch ) );
    jdn1++;
    CPPUNIT_ASSERT( jdn1 == 2432609 );  // 27 Feb 1948 (G)
    CPPUNIT_ASSERT( calAddToJdn( &jdn2, -day, CALENDAR_UNIT_Day, sch ) );
    CPPUNIT_ASSERT( jdn2 == 2432974 );  // 26 Feb 1949 (G)

    jdn1 = 2455612; // 19 Feb 2011 (G)
    day = 4;
    month = 11;
    year = 10;
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -year, CALENDAR_UNIT_Year, sch ) );
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -month, CALENDAR_UNIT_Month, sch ) );
    CPPUNIT_ASSERT( calAddToJdn( &jdn1, -day, CALENDAR_UNIT_Day, sch ) );
    CPPUNIT_ASSERT( jdn1 == 2451619 );  // 15 Mar 2000 (G)
}

// End of testCalendar.cpp
