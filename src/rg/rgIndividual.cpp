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

    idt indID = rgCreateIndividual( wind, famID, sex, rgCRNAME_Sur_Given, surname );
    if( indID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    if( sex == SEX_Female && fam.FGetWifeID() == 0 ) {
        fam.FSetWifeID( indID );
    } else {
        wxASSERT( fam.FGetHusbID() == 0 );
        fam.FSetHusbID( indID );
    }
    fam.Save();
    recDb::ReleaseSavepoint( savepoint );
    return indID;
}

bool rgAddNewParent( wxWindow* wind, idt indID, Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    idt famID = 0;
    recFamilyVec parents = recIndividual::GetParentList( indID );

    if( parents.size() ) {
        if( parents.size() == 1 ) {
            if( parents[0].f_husb_id == 0 && sex != SEX_Female ) {
                famID = parents[0].f_id;
            } else if( parents[0].f_wife_id == 0 && sex == SEX_Female ) {
                famID = parents[0].f_id;
            }
        }
        if( famID == 0 ) {
            recIdVec indIDs;
            IntVec rows;
            idt parID;
            for( size_t i = 0 ; i < parents.size() ; i++ ) {
                if( sex == SEX_Female && parents[i].f_wife_id == 0 ) {
                    parID = parents[i].f_husb_id;
                } else if( sex == SEX_Male && parents[i].f_husb_id == 0 ) {
                    parID = parents[i].f_wife_id;
                } else {
                    parID = 0;
                }
                if( parID ) {
                    indIDs.push_back( parID );
                    rows.push_back( i );
                }
            }
            if( indIDs.size() ) {
                idt indID = rgSelectIndividual( indIDs );
                if( indID == 0 ) {
                    recDb::Rollback( savepoint );
                    return false;
                }
                for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
                    if( indID == indIDs[i] ) {
                        famID = parents[rows[i]].FGetID();
                        break;
                    }
                }
            }
        }
    }

    wxString surname;
    if( sex == SEX_Male ) {
        surname = recIndividual::GetSurname( indID );
    }

    idt parentID = rgAddNewIndividual( wind, sex, surname, famID );
    if( parentID ) {
        recFamilyIndividual fi(0);
        fi.fSetFamID( recIndividual::GetDefaultFamily( parentID ) );
        fi.fSetIndID( indID );
        fi.Find();
        if( fi.FGetID() == 0 ) {
            fi.fSetSeqChild( 1 );
            fi.fSetSeqParent( recFamily::GetParentNextSequence( parentID ) );
            fi.Save();
        }

        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

bool rgAddExistParent( wxWindow* wind, idt indID, Sex sex )
{
    wxASSERT( indID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    idt parentID = rgSelectIndividual( sex );
    if( parentID == 0 ) {
        recDb::ReleaseSavepoint( savepoint );
        return false;
    }
    recFamilyVec families = recIndividual::GetFamilyList( parentID );
    wxASSERT( families.size() > 0 );
    size_t i = 0;
    if( families.size() > 1 ) {
        // TODO: Allow for selecting from multiple families.
        wxMessageBox( "Select which of multiple families\nNot yet implimented", "tfpAddExistParent" );
        recDb::ReleaseSavepoint( savepoint );
        return false;
    }
    recFamilyIndividual fi(0);
    fi.f_fam_id = families[i].FGetID();
    fi.f_ind_id = indID;
    fi.f_seq_child = recFamily::GetChildNextSequence( families[i].FGetID() );
    fi.f_seq_parent = recFamily::GetParentNextSequence( indID );
    fi.Save();
    recDb::ReleaseSavepoint( savepoint );
    return true;
}

bool rgAddNewSpouse( wxWindow* wind, idt indID, Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    idt famID = recIndividual::GetDefaultFamily( indID );
    recFamily fam(famID);
    if( sex == SEX_Female ) {
        if( fam.f_wife_id != 0 ) {
            fam.Clear();
            fam.f_husb_id = indID;
            fam.Save();
        }
    } else {
        if( fam.f_husb_id != 0 ) {
            fam.Clear();
            fam.f_wife_id = indID;
            fam.Save();
        }
    }
    famID = fam.FGetID();

    if( rgAddNewIndividual( wind, sex, "", famID ) != 0 ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

bool rgAddExistSpouse( wxWindow* wind, idt indID, Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    recDb::Savepoint( savepoint );

    recIndividual ind, spouse;
    ind.f_id = indID;
    ind.Read();
    recFamily fam;
    fam.f_id = ind.f_fam_id;
    fam.Read();
    if( sex == SEX_Male ) {
        spouse.f_id = rgSelectIndividual( SEX_Male );
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
        spouse.f_id = rgSelectIndividual( SEX_Female );
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

idt rgAddNewChild( wxWindow* wind, idt famID, Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    // TODO: Allow for other naming systems
    wxString surname;
    recFamily family(famID);
    idt parentID = family.f_husb_id;
    if( parentID == 0 ) {
        parentID = family.f_wife_id;
    }
    if( parentID ) {
        surname = recIndividual::GetSurname( parentID );
    }

    idt indID = rgAddNewIndividual( wind, sex, surname );
    if( indID ) {
        recFamilyIndividual fi(0);
        fi.f_fam_id = famID;
        fi.f_ind_id = indID;
        fi.f_seq_child = recFamily::GetChildNextSequence( famID );
        fi.Save();
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }
    return indID;
}

idt rgAddExistChild( wxWindow* wind, idt famID, Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt indID = rgSelectIndividual( sex );
    if( indID != 0 ) {
        recFamilyIndividual fi;
        fi.Clear();
        fi.f_fam_id = famID;
        fi.f_ind_id = indID;
        fi.f_seq_child = recFamily::GetChildNextSequence( famID );
        fi.Save();
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }

    return indID;
}

bool rgDeleteIndividual( wxWindow* wind, idt indID )
{
    bool ret = false;
    wxString mess = wxString::Format(
        _("This action will completely remove Individual %s\n%s\nfrom the database\n\nDo you want to continue?"),
        recIndividual::GetIdStr( indID ),
        recIndividual::GetFullName( indID )
    );
    int ans = wxMessageBox( mess, _("Delete Individual"), wxYES_NO | wxCANCEL, wind );
    if( ans == wxYES ) {
        recIndividual::RemoveFromDatabase( indID );
        ret = true;
    }
    return ret;
}

// End of src/rg/rgIndividual.cpp file
