/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual entity dialog.
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

#include <rec/recLink.h>

#include "dlgEdIndividual.h"
#include "dlgEdIndEvent.h"

IMPLEMENT_CLASS( dlgEditIndividual, wxDialog )

BEGIN_EVENT_TABLE( dlgEditIndividual, wxDialog )
    EVT_LIST_ITEM_ACTIVATED( tfpID_EDIND_EVENTS, dlgEditIndividual::OnEventActivated )
END_EVENT_TABLE()

dlgEditIndividual::dlgEditIndividual( wxWindow* parent )
    : fbDlgEditIndividual( parent )
{
    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listCtrl->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Date") );
    m_listCtrl->InsertColumn( 1, itemCol );
    itemCol.SetText( wxT("Place") );
    m_listCtrl->InsertColumn( 2, itemCol );
    itemCol.SetText( wxT("Note") );
    m_listCtrl->InsertColumn( 3, itemCol );

    m_fam_id = 0;
    m_sex = SEX_Unstated;
    m_individual.Clear();
}

bool dlgEditIndividual::TransferDataToWindow()
{
    if( m_individual.f_id  == 0 )
    {
        m_individual.Clear();
        m_individual.Save();
    } else {
        m_individual.Read();
    }
    if( m_fam_id == 0 ) {
        m_fam_id = m_individual.f_fam_id;
    }
    if( m_individual.f_per_id == 0 ) {
        m_persona.Clear();
        m_persona.f_sex = m_individual.f_sex;
        m_persona.Save();
        m_individual.f_per_id = m_persona.f_id;
        m_name.Clear();
        m_name.f_per_id = m_persona.f_id;
        m_name.Save();
    } else {
        m_persona.f_id = m_individual.f_per_id;
        m_persona.Read();
        m_name.FindPersona( m_persona.f_id );
    }
    wxString name = m_name.GetSurname();
    if( name != wxEmptyString ) {
        m_surname = name;
    }
    m_given = m_name.GetNamePartStr( NAME_TYPE_Given_name );
    if( m_individual.f_sex == SEX_Unstated ) {
        m_individual.f_sex = m_sex;
    }
//    m_occAttr.f_id = m_individual.f_occ_id;
//    m_occAttr.Read();
//    m_birthEvent.f_id = m_individual.f_birth_id;
//    m_birthEvent.Read();
//    m_nrbirthEvent.f_id = m_individual.f_nr_birth_id;
//    m_nrbirthEvent.Read();
//    m_deathEvent.f_id = m_individual.f_death_id;
//    m_deathEvent.Read();
//    m_nrdeathEvent.f_id = m_individual.f_nr_death_id;
//    m_nrdeathEvent.Read();

    wxString str;
    str << "I " << m_individual.f_id;
    m_staticIndID->SetLabel( str  );
    m_textGiven->SetValue( m_given );
    m_textSurname->SetValue( m_surname );
    m_choiceSex->SetSelection( m_individual.f_sex );
//    m_occAttr.f_id = m_individual.f_occ_id;
//    m_occAttr.Read();
//    m_textOccAttr->SetValue( m_occAttr.f_val );

//    m_listCtrl->InsertItem( 0, _("Birth") );
//    m_listCtrl->SetItem( 0, 1, m_birthEvent.GetDateStr() );
//    m_listCtrl->SetItem( 0, 2, m_birthEvent.GetAddressStr() );

//    str = m_nrbirthEvent.GetTypeStr();
//    if( str.IsEmpty() ) str = _("Baptism");
//    m_listCtrl->InsertItem( 1, str );
//    m_listCtrl->SetItem( 1, 1, m_nrbirthEvent.GetDateStr() );
//    m_listCtrl->SetItem( 1, 2, m_nrbirthEvent.GetAddressStr() );

//    m_listCtrl->InsertItem( 2, _("Death") );
//    m_listCtrl->SetItem( 2, 1, m_deathEvent.GetDateStr() );
//    m_listCtrl->SetItem( 2, 2, m_deathEvent.GetAddressStr() );

//    str = m_nrdeathEvent.GetTypeStr();
//    if( str.IsEmpty() ) str = _("Burial");
//    m_listCtrl->InsertItem( 3, str );
//    m_listCtrl->SetItem( 3, 1, m_nrdeathEvent.GetDateStr() );
//    m_listCtrl->SetItem( 3, 2, m_nrdeathEvent.GetAddressStr() );

    return true;
}

bool dlgEditIndividual::TransferDataFromWindow()
{
    recNamePartVec exist;
    recNamePartVec names;
    int seq = 1;
    recNamePart np;
    idt ud_surname = 0;

    exist = m_name.GetParts();
    names = recNamePart::ConvertStrToList( m_textGiven->GetValue() );

    size_t ecount = exist.size();
    size_t ncount = names.size();
    size_t n = 0 ;
    for( size_t i = 0 ; i < ecount ; i++ ) {
        if( exist[i].f_type_id == NAME_TYPE_Given_name ) {
            if( n < ncount ) {
                exist[i].f_val = names[n++].f_val;
                exist[i].f_sequence = seq++;
                exist[i].Save();
            } else {
                // Used up all given names
                exist[i].Delete();
            }
        }
        if( exist[i].f_type_id == NAME_TYPE_Surname ) {
            exist[i].f_val = m_textSurname->GetValue();
            exist[i].Save();
            ud_surname = exist[i].f_id;
            // Wait to save until sequence number known
        }
    }
    while( n < ncount ) {
        np.Clear();
        np.f_name_id = m_name.f_id;
        np.f_type_id = NAME_TYPE_Given_name;
        np.f_val = names[n++].f_val;
        np.f_sequence = seq++;
        np.Save();
    }

    np.Clear();
    if( ud_surname == 0 ) {
        np.f_name_id = m_name.f_id;
        np.f_type_id = NAME_TYPE_Surname;
        np.f_val = m_textSurname->GetValue();
        ud_surname = np.f_id;
    } else {
        np.f_id = ud_surname;
        np.Read();
    }
    np.f_sequence = seq++;
    np.Save();
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.Save();

    if( m_fam_id == 0 ) {
        recFamily family;
        family.Clear();
        if( m_persona.f_sex == SEX_Female ) {
            family.f_wife_id = m_individual.f_id;
        } else {
            family.f_husb_id = m_individual.f_id;
        }
        family.Save();
        m_fam_id = family.f_id;
    }

    m_individual.f_given = m_textGiven->GetValue();
    m_individual.f_surname = m_textSurname->GetValue();
    m_individual.f_sex = (Sex) m_choiceSex->GetSelection();
    m_individual.f_fam_id = m_fam_id;

    recLinkPersona lp(0);
    lp.f_ref_per_id = m_persona.f_id;
    lp.f_ind_per_id = m_individual.f_per_id;
    if( lp.Find() == false ) {
        lp.Save();
    }

    wxString str = m_textOccAttr->GetValue();
    if( str == wxEmptyString ) {
//        m_occAttr.Delete();
//        m_individual.f_occ_id = 0;
    } else {
//        m_occAttr.f_per_id = m_persona.f_id;
//        m_occAttr.f_type_id = recAttributeType::ATYPE_Occupation;
//        m_occAttr.f_val = str;
//        m_occAttr.Save();
//        m_individual.f_occ_id = m_occAttr.f_id;
    }
    m_individual.Save();

    return true;
}

void dlgEditIndividual::OnEventActivated( wxListEvent& event )
{
#if 0
    recEvent* pEvent;
    idt roleID, typeID;
    idt* pEventID;
    switch( event.m_itemIndex )
    {
    case 0:
        pEvent = &m_birthEvent;
        typeID = recEventType::ET_Birth;
        roleID = recEventTypeRole::ROLE_Birth_Born;
        pEventID = &m_individual.f_birth_id;
        break;
    case 1:
        wxMessageBox(
            wxT("Not yet implimented\nNr Birth"),
            wxT("OnEventSelected")
        );
        return;
    case 2:
        pEvent = &m_deathEvent;
        typeID = recEventType::ET_Death;
        roleID = recEventTypeRole::ROLE_Death_Died;
        pEventID = &m_individual.f_death_id;
        break;
    case 3:
        wxMessageBox(
            wxT("Not yet implimented\nNr Death"),
            wxT("OnEventSelected")
        );
        return;
    default:
        wxASSERT( false );
        return;
    }

    const wxString savepoint = wxT("EdIndEvent");
    recDb::Savepoint( savepoint );

    if( pEvent->f_id == 0 ) {
        pEvent->f_type_id = typeID;
        pEvent->Save();
        *pEventID = pEvent->f_id;
        recEventPersona pe;
        pe.Clear();
        pe.f_per_id = m_persona.f_id;
        pe.f_event_id = pEvent->f_id;
        pe.f_role_id = roleID;
        pe.Save();
    }

    dlgEditIndEvent* dialog = new dlgEditIndEvent( NULL );
    dialog->SetEvent( pEvent );

    if( dialog->ShowModal() == wxID_OK ) {
        pEvent->Save();
        recDb::ReleaseSavepoint( savepoint );
        UpdateEventDetails();
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditIndividual::UpdateEventDetails()
{
#if 0
    m_listCtrl->SetItem( 0, 0, wxT("Birth") );
    m_listCtrl->SetItem( 0, 1, m_birthEvent.GetDateStr() );
    m_listCtrl->SetItem( 0, 2, m_birthEvent.GetAddressStr() );

    wxString str = m_nrbirthEvent.GetTypeStr();
    if( str.IsEmpty() ) str = wxT("Baptism");
    m_listCtrl->SetItem( 1, 0, str );
    m_listCtrl->SetItem( 1, 1, m_nrbirthEvent.GetDateStr() );
    m_listCtrl->SetItem( 1, 2, m_nrbirthEvent.GetAddressStr() );

    m_listCtrl->SetItem( 2, 0, wxT("Death") );
    m_listCtrl->SetItem( 2, 1, m_deathEvent.GetDateStr() );
    m_listCtrl->SetItem( 2, 2, m_deathEvent.GetAddressStr() );

    str = m_nrdeathEvent.GetTypeStr();
    if( str.IsEmpty() ) str = wxT("Burial");
    m_listCtrl->SetItem( 3, 0, str );
    m_listCtrl->SetItem( 3, 1, m_nrdeathEvent.GetDateStr() );
    m_listCtrl->SetItem( 3, 2, m_nrdeathEvent.GetAddressStr() );
#endif
}


// End of dlgEdIndividual.cpp
