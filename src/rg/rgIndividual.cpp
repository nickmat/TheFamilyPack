/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to create and edit Individuals and Families.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3rd March 2013
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

#include <rec/recIndividual.h>
//#include <rec/recLink.h>

#include <rg/rgDialogs.h>
#include "rgCrIndividual.h"
//#include "rgEdIndividual.h"


idt rgAddNewIndividual( wxWindow* wind, Sex sex, const wxString& surname, idt famID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recFamily fam(famID);
    if( famID == 0 ) {
        fam.Save();
        famID = fam.FGetID();
    }
    idt* pIndID = ( sex == SEX_Female ) ? &fam.f_wife_id : &fam.f_husb_id;
    wxASSERT( *pIndID == 0 );

    idt indID = rgCreateIndividual( wind, famID, sex, rgCRNAME_Sur_Given, surname );
    if( indID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    *pIndID = indID;
    fam.Save();
    recDb::ReleaseSavepoint( savepoint );
    return indID;
}

// End of src/rg/rgIndividual.cpp file
