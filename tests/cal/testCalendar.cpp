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
    CPPUNIT_TEST_SUITE_END();

    void TestTable();

    DECLARE_NO_COPY_CLASS(CalTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( CalTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CalTestCase, "CalTestCase" );

struct SampleDate {
    long jdn;
    long rd;
    double jd;
    long mjd;
    DMYDate g;
    DMYDate j;
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
    long jdn, num;
    double dbl;
    DMYDate dmy;

    for( int i = 0 ; i < MaxSample ; i++ ) {
        CalConvertFromJdn( SampleList[i].jdn, num, CALENDAR_SCH_RataDie );
        CPPUNIT_ASSERT( num == SampleList[i].rd );
        CalConvertToJdn( jdn, SampleList[i].rd, CALENDAR_SCH_RataDie );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        CalConvertFromJdn( SampleList[i].jdn, dbl, CALENDAR_SCH_JulianDay );
        // We shouldn't really equate doubles here - but it should work ok.
        CPPUNIT_ASSERT( dbl == SampleList[i].jd );
        CalConvertToJdn( jdn, SampleList[i].jd, CALENDAR_SCH_JulianDay );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        CalConvertFromJdn( SampleList[i].jdn, num, CALENDAR_SCH_ModJulianDay );
        CPPUNIT_ASSERT( num == SampleList[i].mjd );
        CalConvertToJdn( jdn, SampleList[i].mjd, CALENDAR_SCH_ModJulianDay );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        CalConvertFromJdn( SampleList[i].jdn, dmy, CALENDAR_SCH_Gregorian );
        CPPUNIT_ASSERT( dmy.day == SampleList[i].g.day );
        CPPUNIT_ASSERT( dmy.month == SampleList[i].g.month );
        CPPUNIT_ASSERT( dmy.year == SampleList[i].g.year );
        CalConvertToJdn( jdn, SampleList[i].g, CALENDAR_SCH_Gregorian );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        CalConvertFromJdn( SampleList[i].jdn, dmy, CALENDAR_SCH_Julian );
        CPPUNIT_ASSERT( dmy.day == SampleList[i].j.day );
        CPPUNIT_ASSERT( dmy.month == SampleList[i].j.month );
        CPPUNIT_ASSERT( dmy.year == SampleList[i].j.year );
        CalConvertToJdn( jdn, SampleList[i].j, CALENDAR_SCH_Julian );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );
    }
}

// End of testCalendar.cpp
