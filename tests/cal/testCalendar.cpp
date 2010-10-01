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
    long mjd;
};

/*! Size of SampleList array.
 */
const int MaxSample = 33;

/*! Taken from the Sample Table given in Appendix C
 *  of the book "Calendrical Calculations" by Nachum Dershowitz
 *  and Edward M. Reingold.
 */
SampleDate SampleList[MaxSample] = {
    //  JDN       RD
    { 1507232, -214193, -892769 },
    { 1660038, -61387, -739963 },
    { 1746894, 25469, -653107 },
    { 1770642, 49217, -629359 },
    { 1892732, 171307, -507269 },
    { 1931580, 210155, -468421 },
    { 1974852, 253427, -425149 },
    { 2091165, 369740, -308836 },
    { 2121510, 400085, -278491 },
    { 2155780, 434355, -244221 },
    { 2174030, 452605, -225971 },
    { 2191585, 470160, -208416 },
    { 2195262, 473837, -204739 },
    { 2229275, 507850, -170726 },
    { 2245581, 524156, -154420 },
    { 2266101, 544676, -133900 },
    { 2288543, 567118, -111458 },
    { 2290902, 569477, -109099 },
    { 2323141, 601716, -76860 },
    { 2334849, 613424, -65152 },
    { 2348021, 626596, -51980 },
    { 2366979, 645554, -33022 },
    { 2385649, 664224, -14352 },
    { 2392826, 671401, -7175 },
    { 2416224, 694799, 16223 },
    { 2425849, 704424, 25848 },
    { 2430267, 708842, 30266 },
    { 2430834, 709409, 30833 },
    { 2431005, 709580, 31004 },
    { 2448699, 727274, 48698 },
    { 2450139, 728714, 50138 },
    { 2465738, 744313, 65737 },
    { 2486077, 764652, 86076 }
};

void CalTestCase::TestTable()
{
    long jdn, num;

    for( int i = 0 ; i < MaxSample ; i++ ) {
        CalConvertFromJdn( num, SampleList[i].jdn, CALENDAR_SCH_RataDie );
        CPPUNIT_ASSERT( num == SampleList[i].rd );
        CalConvertToJdn( jdn, SampleList[i].rd, CALENDAR_SCH_RataDie );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );

        CalConvertFromJdn( num, SampleList[i].jdn, CALENDAR_SCH_ModJulianDay );
        CPPUNIT_ASSERT( num == SampleList[i].mjd );
        CalConvertToJdn( jdn, SampleList[i].mjd, CALENDAR_SCH_ModJulianDay );
        CPPUNIT_ASSERT( jdn == SampleList[i].jdn );
    }
}

// End of testCalendar.cpp
