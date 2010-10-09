/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpEdit.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to edit the database.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recIndividual.h>

#include "tfpEdit.h"
#include "dlg/dlgEdIndividual.h"

bool tfpAddNewSpouse( id_t indID, Sex sex )
{
	const wxString savepoint = wxT("AddNewSpouse");
    bool ret = false;
    recDb::Savepoint( savepoint );

    recIndividual ind, spouse;
    ind.f_id = indID;
    ind.Read();
    spouse.Clear();
    spouse.Save();
    recFamily fam;
    fam.f_id = ind.f_fam_id;
    fam.Read();
    if( sex == SEX_Female ) {    // Add Spouse to Wife
        if( fam.f_husb_id != 0 ) { // More than one Husb
            fam.Clear();
            fam.f_wife_id = ind.f_id;
        }
        spouse.f_sex = SEX_Male;
        fam.f_husb_id = spouse.f_id;
    } else {                     // Add Spouse to Husb
        if( fam.f_wife_id != 0 ) { // More than one wife
            fam.Clear();
            fam.f_husb_id = ind.f_id;
        }
        spouse.f_sex = SEX_Female;
        fam.f_wife_id = spouse.f_id;
    }
    fam.Save();
    spouse.f_fam_id = fam.f_id;
    spouse.Save();

    dlgEditIndividual* dialog = new dlgEditIndividual( NULL );

    dialog->SetIndividualID( spouse.f_id );

    if( dialog->ShowModal() == wxID_OK ) {
		recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
		recDb::Rollback( savepoint );
    }
    dialog->Destroy();

    return ret;
}



// End of tfpEdit.cpp file
