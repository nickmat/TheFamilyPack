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
#include "dlg/dlgEdFamily.h"
#include "dlg/dlgEdIndividual.h"
#include "dlg/dlgSelIndividual.h"


static id_t tfpPickIndividual( Sex sex )
{
	id_t indID = 0;
    dlgSelectIndividual* dialog = new dlgSelectIndividual( NULL );

	if( dialog->CreateTable( sex ) == true ) {
		if( dialog->ShowModal() == wxID_OK ) {
			indID = dialog->GetSelectedID();
		}
	}
    dialog->Destroy();
	return indID;
}


bool tfpEditFamily( id_t famID )
{
//    wxMessageBox( wxT("Not yet implimented"), wxT("tfpEditFamily") );
//    return false;
	const wxString savepoint = "EdFam";
	bool ret = false;

	dlgEditFamily* dialog = new dlgEditFamily( NULL );
	dialog->SetFamilyID( famID );

	recDb::Savepoint( savepoint );
	if( dialog->ShowModal() == wxID_OK ) {
		recDb::ReleaseSavepoint( savepoint );
		ret = true;
	} else {
		recDb::Rollback( savepoint );
	}
	dialog->Destroy();
	return ret;
}

bool tfpEditIndividual( id_t indID  )
{
	const wxString savepoint = "EdInd";
	bool ret = false;
	dlgEditIndividual* dialog = new dlgEditIndividual( NULL );
	recDb::Savepoint( savepoint );

	dialog->SetIndividualID( indID );

	if( dialog->ShowModal() == wxID_OK ) {
		recDb::ReleaseSavepoint( savepoint );
		ret = true;
	} else {
		recDb::Rollback( savepoint );
	}
	dialog->Destroy();
	return ret;
}

id_t tfpAddIndividual( id_t famID, Sex sex, const wxString& surname )
{
	const wxString savepoint = "AddInd";
	id_t ret = 0;
	dlgEditIndividual* dialog = new dlgEditIndividual( NULL );
	recDb::Savepoint( savepoint );

	recIndividual ind;
	ind.Clear();
	ind.Save();

	if( famID != 0 ) {
    	recFamily fam;
		fam.f_id = famID;
		fam.Read();
		if( sex == SEX_Female ) {
            fam.f_wife_id = ind.f_id;
		} else {
			fam.f_husb_id = ind.f_id;
		}
		fam.Save();
	} // else let dialog create new Family record

	dialog->SetIndividualID( ind.f_id );
	dialog->SetFamilyID( famID );
	dialog->SetSex( sex );
	dialog->SetSurname( surname );

	if( dialog->ShowModal() == wxID_OK ) {
		recDb::ReleaseSavepoint( savepoint );
		ret = ind.f_id;
	} else {
		recDb::Rollback( savepoint );
	}
	dialog->Destroy();
	return ret;
}



bool tfpAddNewParent( id_t indID, Sex sex )
{
	const wxString savepoint = wxT("AddNewParent");
    bool ret = false;
    recDb::Savepoint( savepoint );
    dlgEditIndividual* dialog = new dlgEditIndividual( NULL );

    recIndividual ind, parent;
    ind.f_id = indID;
    ind.Read();
    parent.Clear();
    parent.Save();
    recFamily fam;
    fam.ReadParents( indID );

    if( sex == SEX_Female ) {  // Add Mother
        wxASSERT( fam.f_wife_id == 0 );
        fam.f_wife_id = parent.f_id;
        dialog->SetSex( SEX_Female );
    } else {                   // Add Father
        wxASSERT( fam.f_husb_id == 0 );
        fam.f_husb_id = parent.f_id;
        dialog->SetSex( SEX_Male );
        dialog->SetSurname( ind.f_surname );
    }
    fam.Save();
    recFamilyIndividual fi;
    fi.f_fam_id = fam.f_id;
    fi.f_ind_id = indID;
    fi.Find();
    if( fi.f_id == 0 ) {
        fi.f_sequence = 1;
        fi.Save();
    }

    dialog->SetIndividualID( parent.f_id );
    dialog->SetFamilyID( fam.f_id );

    if( dialog->ShowModal() == wxID_OK ) {
		recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
		recDb::Rollback( savepoint );
    }
    dialog->Destroy();

    return ret;
}

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
    if( sex == SEX_Female ) {    // Add Wife
        if( fam.f_wife_id != 0 ) { // More than one wife
            fam.Clear();
            fam.f_husb_id = ind.f_id;
        }
        spouse.f_sex = SEX_Female;
        fam.f_wife_id = spouse.f_id;
    } else {                     // Add Husb
        if( fam.f_husb_id != 0 ) { // More than one Husb
            fam.Clear();
            fam.f_wife_id = ind.f_id;
        }
        spouse.f_sex = SEX_Male;
        fam.f_husb_id = spouse.f_id;
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

id_t tfpAddNewChild( id_t famID, Sex sex )
{
	const wxString savepoint = "AddNewChild";
	id_t indID = 0;
	dlgEditIndividual* dialog = new dlgEditIndividual( NULL );
	recDb::Savepoint( savepoint );

	wxString surname;
	recFamily fam;
	fam.f_id = famID;
	fam.Read();
	surname = recIndividual::GetSurname( fam.f_husb_id );

	indID = tfpAddIndividual( 0, sex, surname );
	if( indID != 0 ) {
        recFamilyIndividual fi;
		fi.Clear();
        fi.f_fam_id = famID;
		fi.f_ind_id = indID;
		fi.f_sequence = recFamily::GetChildNextSequence( famID );
		fi.Save();
		recDb::ReleaseSavepoint( savepoint );
	} else {
		recDb::Rollback( savepoint );
	}

	return indID;
}

bool tfpAddExistSpouse( id_t indID, Sex sex )
{
	const wxString savepoint = wxT("AddExistSpouse");
    bool ret = false;
	recDb::Savepoint( savepoint );

    recIndividual ind, spouse;
    ind.f_id = indID;
    ind.Read();
    recFamily fam;
    fam.f_id = ind.f_fam_id;
    fam.Read();
    if( sex == SEX_Male ) {
        spouse.f_id = tfpPickIndividual( SEX_Male );
        if( spouse.f_id != 0 ) {
            spouse.Read();
            if( fam.f_husb_id == 0 ) { // No husband yet
                fam.f_husb_id = spouse.f_id;

                recFamily spouseFam;
                spouseFam.f_id = spouse.f_fam_id;
                spouseFam.Read();
                if( spouseFam.f_wife_id == 0 ) {
                    // We have two families but only need one.
                    recFamily::Delete( spouse.f_fam_id );
                    spouse.f_fam_id = ind.f_fam_id;
                }

            } else {
                fam.f_id = spouse.f_fam_id;
                fam.Read();
                if( fam.f_wife_id == 0 ) { // Spouse has no wife yet
                    fam.f_wife_id = ind.f_id;
                } else { // Create a new family
                    fam.Clear();
                    fam.f_wife_id = ind.f_id;
                    fam.f_husb_id = spouse.f_id;
                }
            }
        }
    } else { // SEX_Male
        spouse.f_id = tfpPickIndividual( SEX_Female );
        if( spouse.f_id != 0 ) {
            spouse.Read();
            if( fam.f_wife_id == 0 ) { // No wives yet
                fam.f_wife_id = spouse.f_id;
                recFamily spouseFam;
                spouseFam.f_id = spouse.f_fam_id;
                spouseFam.Read();
                if( spouseFam.f_husb_id == 0 ) {
                    // We have two families but only need one.
                    recFamily::Delete( spouse.f_fam_id );
                    spouse.f_fam_id = ind.f_fam_id;
                }
            } else {
                fam.f_id = spouse.f_fam_id;
                fam.Read();
                if( fam.f_husb_id == 0 ) { // Spouse has no husband yet
                    fam.f_husb_id = ind.f_id;
                } else { // Create a new family
                    fam.Clear();
                    fam.f_husb_id = ind.f_id;
                    fam.f_wife_id = spouse.f_id;
                }
            }
        }
    }
    if( spouse.f_id != 0 ) {
        ret = true;
        fam.Save();
		recDb::ReleaseSavepoint( savepoint );
    } else {
		recDb::Rollback( savepoint );
    }

    return ret;
}

bool tfpAddExistChild( id_t famID, Sex sex )
{
//    wxMessageBox( wxT("Not yet implimented"), wxT("tfpAddExistChild") );
//    return false;
	const wxString savepoint = "AddExistingChild";
    bool ret = false;
	recDb::Savepoint( savepoint );

	id_t indID = tfpPickIndividual( sex );
	if( indID != 0 ) {
        recFamilyIndividual fi;
		fi.Clear();
        fi.f_fam_id = famID;
		fi.f_ind_id = indID;
		fi.f_sequence = recFamily::GetChildNextSequence( famID );
		fi.Save();
        ret = true;
		recDb::ReleaseSavepoint( savepoint );
	} else {
		recDb::Rollback( savepoint );
	}

	return ret;
}

// End of tfpEdit.cpp file
