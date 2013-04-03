/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recUpgrade.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage upgrading between database versions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd April 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <rec/recVersion.h>

// This is the database version this program is designed to work with.
const int recVerMajor    = 0;
const int recVerMinor    = 0;
const int recVerRev      = 10;
const int recVerTest     = 0;
const wxStringCharType* recVerStr = wxS("TFPD-0.0.10.0");

//============================================================================
//                 Code to upgrade old versions
//============================================================================

namespace {

void UpgradeRev0_0_9to10( int test )
{
    wxASSERT( test == 25 );
    // Version 0.0.9.25 to 0.0.10.0
    // Change to Core Data only, only affects new databases.
    // Removed intitial F1 family record for new databases. 
    char* query =
        "BEGIN;\n"
        "UPDATE Version SET revision=10, test=0 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeRev0_0_10toCurrent( int test )
{
    wxASSERT( test == 0 );
}

} // namespace

bool recDoUpgrade()
{
    recVersion v;
    if( v.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        return true; // Already current vertion
    }
    if( v.IsLessThan( 0, 0, 9, 25 ) ) {
        recMessage(
            wxString::Format(
                _("Cannot read old database version %s file."),
                v.GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( v.IsMoreThan( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        recMessage(
            wxString::Format(
                _("Cannot read future database version %s file."),
                v.GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( recPermissionToUpgrade() == false ) {
        return false;
    }

    try {
        if( v.IsEqual( 0, 0, 9 ) ) {
            UpgradeRev0_0_9to10( v.FGetTest() );
            v.Read();
        }
        if( v.IsEqual( 0, 0, 10 ) ) {
            UpgradeRev0_0_10toCurrent( v.FGetTest() );
            v.Read();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        return false;
    }

    wxASSERT( v.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) );
    return true;
}

// End of recVersion.cpp file
