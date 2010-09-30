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
        CPPUNIT_TEST( CalJDN );
    CPPUNIT_TEST_SUITE_END();

    void CalJDN();

    DECLARE_NO_COPY_CLASS(CalTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( CalTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CalTestCase, "CalTestCase" );


void CalTestCase::CalJDN()
{
    CPPUNIT_ASSERT( true );
}

// End of testCalendar.cpp
