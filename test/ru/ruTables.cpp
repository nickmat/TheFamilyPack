/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        test/ru/ruTables.cpp
 * Project:     recUnit: Unit test program for the rec library.
 * Purpose:     Test the database SQL table classes.
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

// The plan is to run every function and every SQL statement
// For the table ContactType.
TEST_CASE( "Test recContactType table", "[ContactType]" )
{    
    int count = recContactType::Count();
    wxString ct_uid1 = "51A3D97127E0D17639E54F56EEFA3D1D91CC";

    // recContactList()
    recContactType ct1;
    REQUIRE( ct1.FGetID() == 0 );
    REQUIRE( ct1.FGetName() == "" );
    REQUIRE( ct1.FGetUid() == "" );
    REQUIRE( ct1.FGetChanged() == 0 );

    // Save() Add new record and auto increment id (f_id=0 auto increment).
    // GetIdStr()
    ct1.FSetName( "SF" );
    ct1.FSetUid( ct_uid1 );
    ct1.FSetChanged( 2459681 );
    ct1.Save();
    REQUIRE( ct1.GetIdStr() == "CT1" );

    // recContactList( id )
    recContactType ct2( 1 );
    REQUIRE( ct2.FGetID() == 1 ); // Created by auto increment
    REQUIRE( ct2.FGetName() == "SF" );
    REQUIRE( ct2.FGetUid() == ct_uid1 );
    REQUIRE( ct2.FGetChanged() == 2459681 );

    // Save() Update existing record (f_id=1 existing id)
    ct2.FSetName( "SourceForce" );
    ct2.Save();

    // Read()
    ct1.Read();
    REQUIRE( ct1.FGetID() == 1 );
    REQUIRE( ct1.FGetName() == "SourceForce" );
    REQUIRE( ct1.FGetUid() == ct_uid1 );
    REQUIRE( ct1.FGetChanged() == 2459681 );

    // Save() Add new record (f_id=10 new id)
    ct1.FSetID( 10 );
    ct1.Save();
    ct2.ReadID( 10 );
    REQUIRE( ct2.FGetID() == 10 );

    // Confirm 2 records (CT1 and CT10) added to db.
    REQUIRE( recContactType::Count() == count + 2 );

    // GetTypeStr( id )
    REQUIRE( recContactType::GetTypeStr( -4 ) == "Email" );

    // GetList()
    recContactTypeVec cts = recContactType::GetList();
    // Note, the order is neg id's decending followed by pos ascending
    REQUIRE( cts.size() == count - 1 + 2 ); // id 0 not included
    REQUIRE( cts[0].FGetID() == -1 );
    REQUIRE( cts[0].FGetName() == "Address" );
    REQUIRE( cts[0].FGetUid() == "88815CB7641A5C15A6B47B40E69DE654DD52" );
    REQUIRE( cts[0].FGetChanged() == 2459664 );
    size_t last = cts.size() - 1;
    REQUIRE( cts[last].FGetID() == 10 );

    // Note, Renumber( to, from ), and Csv*(...) functions not tested here.

    // Leave database as we found it.
    // Remove all records created
    REQUIRE( ct2.Exists() );
    REQUIRE( ct2.Delete() );
    REQUIRE( !ct2.Exists() );

    // DeleteIfOrphaned( id )
    REQUIRE( recContactType::Exists( 1 ) );
    REQUIRE( recContactType::DeleteIfOrphaned( 1 ) );
    REQUIRE( !recContactType::Exists( 1 ) );

    REQUIRE( recContactType::Count() == count );
}


/* End of test/ru/ruTables.cpp file */
