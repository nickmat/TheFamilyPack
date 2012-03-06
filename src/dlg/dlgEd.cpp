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
#include "dlgSelEvent.h"
#include "dlgEdReference.h"
#include "dlgSelect.h"
#include "dlgEdIndEvent.h"
#include "dlg/dlgNote.h"


idt tfpAddNewIndividual( idt famID, Sex sex, const wxString& surname )
{
    const wxString savepoint = wxT("CreateNewInd");
    idt indID = 0;
    recDb::Savepoint( savepoint );

    recFamily family(famID);
    if( family.f_id == 0 ) {
        family.Save();
        famID = family.f_id;
    }
    wxASSERT( family.f_id != 0 );
    idt* pIndID = ( sex == SEX_Female ) ? &family.f_wife_id : &family.f_husb_id;
    if( *pIndID != 0 ) {
        family.f_id = 0;
        *pIndID = 0;
        family.Save();
        famID = family.f_id;
    }

    dlgCreateIndividual* dialog = new dlgCreateIndividual( NULL, famID );
    dialog->SetSex( sex );
    dialog->SetSurname( surname );

    if( dialog->ShowModal() == wxID_OK ) {
        indID = dialog->GetIndividualID();
        *pIndID = indID;
        if( family.GetId() ) {
            family.Save();
        }
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return indID;
}

idt tfpAddNewChild( idt famID, Sex sex )
{
    const wxString savepoint = "AddNewChild";
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
        fi.f_sequence = recFamily::GetChildNextSequence( famID );
        fi.Save();
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }

    return indID;
}

bool tfpAddNewParent( idt indID, Sex sex )
{
    const wxString savepoint = wxT("AddNewParent");
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
    recDb::Savepoint( savepoint );
    if( sex == SEX_Male ) {
        surname = recIndividual::GetSurname( indID );
    }

    idt newIndID = tfpAddNewIndividual( famID, sex, surname );
    if( newIndID ) {
        recFamilyIndividual fi(0);
        fi.f_fam_id = recIndividual::GetDefaultFamily( newIndID );
        fi.f_ind_id = indID;
        fi.Find();
        if( fi.f_id == 0 ) {
            fi.f_sequence = 1;
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
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("tfpAddExistParent") );
    return false;
}

bool tfpAddNewParent( const wxString& ref )
{
    idt indID;
    ref.Mid( 1 ).ToLongLong( &indID );
    Sex sex = ( ref.GetChar(0) == 'F' ) ? SEX_Female : SEX_Male;
    recDb::Begin();
    if( tfpAddNewParent( indID, sex ) == true ) {
        recDb::Commit();
        return true;
    } else {
        recDb::Rollback();
        return false;
    }
}

bool tfpAddNewSpouse( const wxString& ref )
{
    recDb::Begin();
    idt famID = recGetID( ref.Mid( 1 ) );
    Sex sex = ( ref.GetChar(0) == 'R' ) ? SEX_Female : SEX_Male;
    if( tfpAddNewIndividual( famID, sex ) != 0 ) {
        recDb::Commit();
        return true;
    } else {
        recDb::Rollback();
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




bool tfpEditFamily( idt famID )
{
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

bool tfpEditReference( const wxString& ref )
{
    wxLongLong_t refID;
    ref.ToLongLong( &refID );
    recDb::Begin();
    if( tfpEditReference( refID ) == true ) {
        recDb::Commit();
        return true;
    } else {
        recDb::Rollback();
        return false;
    }
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

bool tfpAddExistChild( idt famID, Sex sex )
{
    const wxString savepoint = "AddExistingChild";
    bool ret = false;
    recDb::Savepoint( savepoint );

    idt indID = tfpPickIndividual( sex );
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

idt tfpGetExistingMarriageEvent( idt famID )
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

idt tfpAddMarriageEvent( const recFamily& family )
{
    idt eventID = 0;

    const wxString savepoint = "AddFamEvent";
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

    dlgEditIndEvent* dialog = new dlgEditIndEvent( NULL );
    dialog->SetEventType( typeID );
    dialog->SetEventTitle( wxString::Format( 
        _("%s of %s and %s"), 
        recEventType::GetTypeStr( typeID ), 
        recIndividual::GetFullName( family.f_husb_id ),
        recIndividual::GetFullName( family.f_wife_id )
    ) );

    if( dialog->ShowModal() == wxID_OK )
    {
        eventID = dialog->GetEventID();
        recLinkEvent le(0);
        le.f_ind_event_id = eventID;
        le.Save();
        recEventPersona ep(0);
        ep.f_event_id = eventID;
        ep.f_sequence = recEvent::GetDatePoint( eventID );
        if( family.f_husb_id ) {
            ep.f_per_id = recIndividual::GetPersona( family.f_husb_id );
            ep.f_role_id = husbRoleID;
            ep.Save();
        }
        if( family.f_wife_id ) {
            ep.f_id = 0;
            ep.f_per_id = recIndividual::GetPersona( family.f_wife_id );
            ep.f_role_id = wifeRoleID;
            ep.Save();
        }
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return eventID;
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

void tfpDisplayNote( wxWindow* parent, const wxString& name )
{
    if( !name.IsEmpty() ) {
        dlgNote* dialog = new dlgNote( parent );
        dialog->SetDisplay( name );
        dialog->Show();
    }
}

// End of dlgEd.cpp file
