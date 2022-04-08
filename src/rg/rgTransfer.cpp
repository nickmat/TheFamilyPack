/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgTransfer.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Transfer records from a external database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     6th March 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rg/rgDialogs.h>

#include <rec/recDb.h>


idt rgTransferReference( wxWindow* wind, idt refID, const wxString& extdb, const wxString& todb )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    // TODO: Determine the Associate database for any media.

    idt to_assID = 0;
    if( recReference::GetMediaCount( refID, extdb ) > 0 ) {
        to_assID = rgSelectAssociate( wind, todb, rgSELSTYLE_Create, nullptr, "Select Database To Store Media" );
    }
//    idt newRefID = ReferenceTransfer( refID, extdb, todb, to_assID );
    wxMessageBox( "Not yet implimented", "rgTransferReference" );
    idt newRefID = 0;
    if( newRefID == 0 ) {
        recDb::Rollback( savepoint );
    }
    else {
        recDb::ReleaseSavepoint( savepoint );
    }
    return newRefID;
}

// End of src/rg/rgTransfer.cpp file
