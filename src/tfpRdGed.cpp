/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpRdGed.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Read GEDCOM import files.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     19 September 2011
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2011, Nick Matthews.
 * Website:     http://thefamilypack.org
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

#include <wx/wfstream.h>

#include <rec/recGedParse.h>

#include "tfpRd.h"


bool tfpReadGedcom( wxString& path )
{
    unsigned flags = recDb::CREATE_DB_STD_EXT | recDb::CREATE_DB_ENUM_FN;
    if( recDb::CreateDb( path, flags ) == false ) return false;

    try {
        recGedParse ged( path );
        if( !ged.Import() ) {
            if( recDb::IsGUI() ) {
                wxMessageBox( _("Error Reading GEDCOM File"), _("Import") );
            }
            return true; // We did actually create a database
        }
//        ged.CleanUp();

    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }

    return true;
}

// End of tfpRdGed.cpp Source
