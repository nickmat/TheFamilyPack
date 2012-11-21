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
#include <rec/recLink.h>

#include "dlgEd.h"
#include "dlgEdFamily.h"
#include "dlgEdIndividual.h"
#include "dlgEdPersona.h"
#include "dlgSelIndividual.h"
#include "dlgEdReference.h"
#include "dlgEdResearcher.h"
#include "dlgEdSystem.h"
#include "dlgSelect.h"
#include "dlgEdIndEvent.h"
#include "dlgEdRole.h"
#include "dlg/dlgNote.h"


idt tfpAddNewIndividual( idt famID, Sex sex, const wxString& surname )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recIndividual ind(0);
    ind.Save();
    idt indID = ind.FGetID();

    recFamily family(famID);
    idt* pIndID = ( sex == SEX_Female ) ? &family.f_wife_id : &family.f_husb_id;
    wxASSERT( *pIndID == 0 );
    *pIndID = indID;
    family.Save();

    dlgCreateIndividual* dialog = new dlgCreateIndividual( NULL, indID );
    dialog->SetSex( sex );
    dialog->SetSurname( surname );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        indID = 0;
    }
    dialog->Destroy();
    return indID;
}

idt tfpAddNewChild( idt famID, Sex sex )
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

    idt indID = tfpAddNewIndividual( 0, sex, surname );
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

bool tfpAddNewParent( idt indID, Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
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
            intVec rows;
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
                int row = tfpSelectIndividual( NULL, indIDs );
                if( row >= 0 ) {
                    famID = parents[rows[row]].f_id;
                } else if( row == -2 ) { // Create button pressed
                    famID = 0;
                } else {
                    return false;
                }
            }
        }
    }

    wxString surname;
    if( sex == SEX_Male ) {
        surname = recIndividual::GetSurname( indID );
    }
    recDb::Savepoint( savepoint );
    if( famID == 0 ) {
        // Create a new family
        recFamily fam(0);
        fam.Save();
        famID = fam.FGetID();
    }

    idt newIndID = tfpAddNewIndividual( famID, sex, surname );
    if( newIndID ) {
        recFamilyIndividual fi(0);
        fi.fSetFamID( recIndividual::GetDefaultFamily( newIndID ) );
        fi.fSetIndID( indID );
        fi.Find();
        if( fi.FGetID() == 0 ) {
            fi.fSetSeqChild( 1 );
            fi.fSetSeqParent( recFamily::GetParentNextSequence( newIndID ) );
            fi.Save();
        }

        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

bool tfpAddExistParent( idt indID, Sex sex )
{
    wxASSERT( indID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;

    idt parentID = tfpPickIndividual( sex );
    if( parentID == 0 ) {
        return false;
    }
    recFamilyVec families = recIndividual::GetFamilyList( parentID );
    wxASSERT( families.size() > 0 );
    size_t i = 0;
    if( families.size() > 1 ) {
        // TODO: Allow for selecting from multiple families.
        wxMessageBox( "Select which of multiple families\nNot yet implimented", "tfpAddExistParent" );
        return false;
    }
    recDb::Savepoint( savepoint );
    recFamilyIndividual fi(0);
    fi.f_fam_id = families[i].FGetID();
    fi.f_ind_id = indID;
    fi.f_seq_child = recFamily::GetChildNextSequence( families[i].FGetID() );
    fi.f_seq_parent = recFamily::GetParentNextSequence( indID );
    fi.Save();
    recDb::ReleaseSavepoint( savepoint );
    return true;
}

bool tfpAddNewParent( const wxString& ref )
{
    const wxString savepoint = "AddIndPar";
    recDb::Savepoint( savepoint );
    idt indID;
    ref.Mid( 1 ).ToLongLong( &indID );
    Sex sex = ( ref.GetChar(0) == 'F' ) ? SEX_Female : SEX_Male;
    if( tfpAddNewParent( indID, sex ) == true ) {
        recDb::ReleaseSavepoint( savepoint );
        return true;
    } else {
        recDb::Rollback( savepoint );
        return false;
    }
}

bool tfpAddNewSpouse( const wxString& ref )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    idt id = recGetID( ref.Mid( 1 ) );
    idt famID;
    Sex sex;
    if( ref.StartsWith( "R" ) || ref.StartsWith( "L" ) ) {
        sex = ref.StartsWith( "R" ) ? SEX_Female : SEX_Male;
        famID = id;
    } else if( ref.StartsWith( "H" ) || ref.StartsWith( "W" ) ) {
        famID = recIndividual::GetDefaultFamily( id );
        recFamily fam(famID);
        if( ref.StartsWith( "H" ) ) {
            sex = SEX_Female;
            if( fam.f_wife_id != 0 ) {
                fam.Clear();
                fam.f_husb_id = id;
                fam.Save();
            }
        } else {
            sex = SEX_Male;
            if( fam.f_husb_id != 0 ) {
                fam.Clear();
                fam.f_wife_id = id;
                fam.Save();
            }
        }
        famID = fam.FGetID();
    } else {
        wxASSERT( false ); // shouldn't be here
    }

    if( tfpAddNewIndividual( famID, sex ) != 0 ) {
        recDb::ReleaseSavepoint( savepoint );
        return true;
    } else {
        recDb::Rollback( savepoint );
        return false;
    }
}

bool tfpEditIndividual( idt indID  )
{
    const wxString savepoint = "EdInd";
    bool ret = false;
    dlgEditIndPersona* dialog = new dlgEditIndPersona( NULL, indID );
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

bool tfpDeleteIndividual( idt indID )
{
    bool ret = false;
    wxString mess = wxString::Format(
        _("This action will completely remove Individual %s\n%s\nfrom the database\n\nDo you want to continue?"),
        recIndividual::GetIdStr( indID ),
        recIndividual::GetFullName( indID )
    );
    int ans = wxMessageBox( mess, "Delete Individual", wxYES_NO | wxCANCEL );
    if( ans == wxYES ) {
        recIndividual::DeleteFromDb( indID );
        ret = true;
    }
    return ret;
}

bool tfpEditFamily( idt famID )
{
    wxASSERT( famID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    dlgEditFamily* dialog = new dlgEditFamily( NULL );
    dialog->SetFamilyID( famID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

bool tfpEditReference( idt refID  )
{
    const wxString savepoint = "EdRef";
    bool ret = false;
    dlgEditReference* dialog = new dlgEditReference( NULL );
    recDb::Savepoint( savepoint );

    dialog->SetID( refID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

bool tfpAddExistSpouse( idt indID, Sex sex )
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

idt tfpAddExistChild( idt famID, Sex sex )
{
    const wxString savepoint = "AddExistingChild";
    recDb::Savepoint( savepoint );

    idt indID = tfpPickIndividual( sex );
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

#if 0
idt tfpGetExistingMarriageEvent_( idt famID )
{
    idt eventID = 0;
    dlgSelectEvent* dialog = new dlgSelectEvent( NULL );
    if( dialog->CreateMarriageTable( famID ) ) {
        if( dialog->ShowModal() == wxID_OK ) {
            eventID = dialog->GetSelectedID();
        }

    }
    dialog->Destroy();
    return eventID;
}
#endif

idt tfpAddMarriageEvent( const recFamily& family )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt typeID = recEventType::Select( recEventType::SF_Family );
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    idt husbRoleID = recEventTypeRole::Select( typeID, recEventTypeRole::SF_Prime1 );
    if( husbRoleID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    idt wifeRoleID = recEventTypeRole::Select( typeID, recEventTypeRole::SF_Prime2 );
    if( wifeRoleID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    recEvent eve(0);
    eve.FSetTypeID( typeID );
    eve.Save();
    idt eventID = eve.FGetID();
    wxString title;

    recEventPersona ep(0);
    ep.f_event_id = eventID;
    if( family.f_husb_id ) {
        ep.f_per_id = recIndividual::GetPersona( family.f_husb_id );
        ep.f_role_id = husbRoleID;
        ep.f_per_seq = 1;
        ep.Save();
    }
    if( family.f_wife_id ) {
        ep.f_id = 0;
        ep.f_per_id = recIndividual::GetPersona( family.f_wife_id );
        ep.f_role_id = wifeRoleID;
        ep.f_per_seq = 2;
        ep.Save();
    }

    dlgEditIndEvent* dialog = new dlgEditIndEvent( NULL, eventID );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        eventID = 0;
    }
    dialog->Destroy();
    return eventID;
}

bool tfpEditEvent( idt eveID  )
{
    const wxString savepoint = "EdEvent";
    bool ret = false;
    dlgEditIndEvent* dialog = new dlgEditIndEvent( NULL, eveID );
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

idt tfpGetRole( idt eventPersonaID, unsigned flags )
{
    const wxString savepoint = "GetEPRole";
    idt roleID = 0;
    dlgEditIndRole* dialog = new dlgEditIndRole( NULL, eventPersonaID );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        roleID = dialog->GetRoleID();
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return roleID;
}

bool tfpEditResearcher( idt resID  )
{
    const wxString savepoint = "EdRes";
    recDb::Savepoint( savepoint );
    bool ret = false;
    dlgEditResearcher* dialog = new dlgEditResearcher( NULL, resID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

bool tfpEditSystem()
{
    const wxString savepoint = "EdSys";
    recDb::Savepoint( savepoint );
    bool ret = false;
    dlgEditSystem* dialog = new dlgEditSystem( NULL );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

bool tfpEditUserSettings()
{
    const wxString savepoint = "EdUserSet";
    recDb::Savepoint( savepoint );
    bool ret = false;
    dlgEditUserSettings* dialog = new dlgEditUserSettings( NULL );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt tfpPickIndividual( Sex sex )
{
    idt indID = 0;
    dlgSelIndividual* dialog = new dlgSelIndividual( NULL );

    if( dialog->CreateTable( sex ) == true ) {
        if( dialog->ShowModal() == wxID_OK ) {
            indID = dialog->GetSelectedID();
        }
    }
    dialog->Destroy();
    return indID;
}

bool tfpSelectPersona( idt* perID, unsigned style, idt refID )
{
    wxASSERT( perID );  // Can't handle NULL pointer
    recIdVec list = recReference::GetPersonaList( refID );
    wxArrayString table;
    for( size_t i = 0 ; i < list.size() ; i++ ) {
        table.Add( recPersona::GetIdStr( list[i] ) );
        table.Add( recPersona::GetNameStr( list[i] ) );
    }

    dlgSelectCreatePersona* dialog = 
        new dlgSelectCreatePersona( NULL, refID );
    dialog->SetTable( table );
    if( style & TFP_SELECT_STYLE_CREATE ) {
        dialog->SetCreateButton();
    }
    if( style & TFP_SELECT_STYLE_UNKNOWN ) {
        dialog->SetUnknownButton();
    }

    bool ret;
    if( dialog->ShowModal() == wxID_OK ) {
        if( dialog->GetCreatePressed() ) {
            *perID = dialog->GetPersonaID();
        } else if( dialog->GetUnknownPressed() ) {
            *perID = 0;
        } else {
            long row = dialog->GetSelectedRow();
            *perID = list[row];
        }
        ret = true;
    } else {
        *perID = 0;
        ret = false;
    }

    dialog->Destroy();
    return ret;
}

long tfpSelectIndividual( idt* indID, recIdVec indIDs )
{
    wxArrayString table;
    for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
        table.Add( recIndividual::GetIdStr( indIDs[i] ) );
        table.Add( recIndividual::GetFullNameEpitaph( indIDs[i] ) );
    }
    dlgSelectIndividual* dialog = new 
        dlgSelectIndividual( NULL, _("Select Family"), dlgSelect::SELSTYLE_CreateButton );
    dialog->SetTable( table );

    long row;
    if( dialog->ShowModal() == wxID_OK ) {
        if( dialog->GetCreatePressed() ) {
            row = -2;
        } else {
            row = dialog->GetSelectedRow();
        }
    } else {
        row = -1;
    }
    if( indID ) {
        if( row >= 0 ) {
            *indID = indIDs[row];
        } else {
            *indID = 0;
        }
    }

    dialog->Destroy();
    return row;
}

// End of dlgEd.cpp file
