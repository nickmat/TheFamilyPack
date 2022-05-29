/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        test/ru/ruMain.cpp
 * Project:     recUnit: Unit test program for the rec library.
 * Purpose:     Program main function source.
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

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#include "ruMain.h"

#include <rec/recDatabase.h>
#include <rec/recAssociate.h>

const char* g_TestFileName = "test.tfpd";
const char* g_AssociateFileName = "test-ass.tfpd";
const char* g_OriginalExternalFileName1 = "test1-orig.tfpd";
const char* g_ExternalFileName1 = "test1.tfpd";
const char* g_OriginalAssociateFileName1 = "test1-ass1-orig.tfpd";
const char* g_AssociateFileName1 = "test1-ass1.tfpd";

const char* g_maindb = "Main";
const char* g_extdb1 = "Test1";

int main( int argc, char* argv[] ) {

    wxInitializer initializer;
    recInitialize();
    // Program should be run from tfp/test directory

    wxString fname = g_TestFileName;
    if( wxFileExists( fname ) ) {
        wxRemoveFile( fname );
    }
    recDb::CreateDb( fname, 0 );

    wxString afname = g_AssociateFileName;
    if( wxFileExists( afname ) ) {
        wxRemoveFile( afname );
    }
    recDb::CreateDbFile( afname, recDb::DbType::media_data_only );
    recAssociate ass( 0 );
    ass.FSetPath( "test-ass" );
    ass.FSetComment( "Test file" );
    ass.Save();

    wxCopyFile( g_OriginalExternalFileName1, g_ExternalFileName1 );
    wxCopyFile( g_OriginalAssociateFileName1, g_AssociateFileName1 );
    recDb::OpenExternalDb( g_ExternalFileName1, g_extdb1 );

    int result = Catch::Session().run( argc, argv );

    recDb::CloseDb();
    recUninitialize();

    return result;
}

/* End of test/ru/ruMain.cpp file */
