/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        test/ru/ruTransfer.cpp
 * Project:     recUnit: Unit test program for the rec library.
 * Purpose:     Test the tranfer of records from one database to another.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th April 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  recUnit is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  recUnit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with recUnit. If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <catch2/catch.hpp>

#include "ruMain.h"

#include <rec/recDb.h>

TEST_CASE( "Test recContactType::Transfer function", "[ContactType]" )
{
    int cnt_main = recContactType::Count( g_maindb );
    int cnt_extdb = recContactType::Count( g_extdb1 );

    REQUIRE( !recContactType::Exists( 1, g_maindb ) );
    REQUIRE( recContactType::Exists( 2, g_extdb1 ) );
    recContactType from_ct( 2, g_extdb1 );

    idt to_id = recContactType::Transfer( 2, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recContactType to_ct( 1, g_maindb );
    REQUIRE( from_ct.Equivalent( to_ct ) );

    to_id = recContactType::Transfer( -4, g_extdb1, g_maindb );
    REQUIRE( to_id == -4 );

    REQUIRE( recContactType::DeleteIfOrphaned( 1, g_maindb ) );

    REQUIRE( recContactType::Count( g_maindb ) == cnt_main );
    REQUIRE( recContactType::Count( g_extdb1 ) == cnt_extdb );
}

/* End of test/ru/ruTransfer.cpp file */
