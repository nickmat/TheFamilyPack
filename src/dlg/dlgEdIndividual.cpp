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

#include "dlgEdPersona.h"
#include "dlgEdName.h"
#include "dlgEdAttribute.h"
#include "dlgEd.h"



dlgEditIndPersona::dlgEditIndPersona( wxWindow* parent, idt indID ) 
    : fbDlgEditIndPersona( parent )
{
    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listName->InsertColumn( 0, itemCol );
    m_listAttr->InsertColumn( 0, itemCol );
    m_listRel->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Value") );
    m_listName->InsertColumn( 1, itemCol );
    m_listAttr->InsertColumn( 1, itemCol );
    m_listRel->InsertColumn( 1, itemCol );

    m_listEvent->InsertColumn( EV_COL_Number, _("Number") );
    m_listEvent->InsertColumn( EV_COL_Role, _("Role") );
    m_listEvent->InsertColumn( EV_COL_Title, _("Title") );
    m_listEvent->InsertColumn( EV_COL_Date, _("Date") );
    m_listEvent->InsertColumn( EV_COL_Place, _("Place") );

    m_persona.Clear();
    m_individual.Clear();
    m_individual.f_id = indID;
}

bool dlgEditIndPersona::TransferDataToWindow()
{
    if( m_individual.f_id == 0 ) {
        m_individual.Save();
        m_persona.Save();
        m_individual.f_per_id = m_persona.f_id;
    } else {
        m_individual.Read();
        m_persona.f_id = m_individual.f_per_id;
        m_persona.Read();
    }

    m_nameStr = m_persona.GetNameStr();
    m_staticPerName->SetLabel( m_nameStr );
    m_staticIndID->SetLabel( m_individual.GetIdStr() );
    m_staticPerID->SetLabel( m_persona.GetIdStr() );

    m_staticTextEpitaph->SetLabel( m_individual.f_epitaph );
    m_choiceSex->SetSelection( (int) m_persona.f_sex );
    m_textCtrlNote->SetValue(  m_persona.f_note );

    m_names = m_persona.ReadNames();
    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        m_listName->InsertItem( i, recNameStyle::GetStyleStr( m_names[i].f_style_id ) );
        m_listName->SetItem( i, COL_Value, m_names[i].GetNameStr() );
    }

    m_attributes = m_persona.ReadAttributes();
    for( size_t i = 0 ; i < m_attributes.size() ; i++ ) {
        m_listAttr->InsertItem( i, recAttributeType::GetTypeStr( m_attributes[i].f_type_id ) );
        m_listAttr->SetItem( i, COL_Value, m_attributes[i].f_val );
    }

    m_evpers = m_persona.ReadEventPersonas();
    for( size_t i = 0 ; i < m_evpers.size() ; i++ ) {
        m_listEvent->InsertItem( i, recEvent::GetIdStr( m_evpers[i].f_event_id ) );
        m_listEvent->SetItem( i, EV_COL_Role, recEventTypeRole::GetName( m_evpers[i].f_role_id ) );
        m_listEvent->SetItem( i, EV_COL_Title, recEvent::GetTitle( m_evpers[i].f_event_id ) );
        m_listEvent->SetItem( i, EV_COL_Date, recEvent::GetDateStr( m_evpers[i].f_event_id ) );
        m_listEvent->SetItem( i, EV_COL_Place, recEvent::GetAddressStr( m_evpers[i].f_event_id ) );
    }

    m_relationships = m_persona.ReadRelationships();
    for( size_t i = 0 ; i < m_relationships.size() ; i++ ) {
        m_listRel->InsertItem( i, m_relationships[i].GetIdStr() );
        m_listRel->SetItem( i, COL_Value, m_relationships[i].GetRelOfPersonaStr( m_persona.f_id ) );
    }

    return true;
}

bool dlgEditIndPersona::TransferDataFromWindow()
{
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.f_note = m_textCtrlNote->GetValue();
    m_persona.Save();

    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        if( m_names[i].f_sequence != i+1 ) {
            m_names[i].f_sequence = i+1;
            m_names[i].Save();
        }
    }

    for( size_t i = 0 ; i < m_attributes.size() ; i++ ) {
        if( m_attributes[i].f_sequence != i+1 ) {
            m_attributes[i].f_sequence = i+1;
            m_attributes[i].Save();
        }
    }

    m_individual.Update();
    m_individual.Save();
    return true;
}

void dlgEditIndPersona::OnNameAddButton( wxCommandEvent& event )
{
    const wxString savepoint = "PerAddName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetPersonaID( m_persona.f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recName* name = dialog->GetName();
        int row = m_names.size();
        m_listName->InsertItem( row, recNameStyle::GetStyleStr( name->f_style_id ) );
        m_listName->SetItem( row, COL_Value, name->GetNameStr() );
        m_names.push_back( *name );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndPersona::OnNameEditButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }

    const wxString savepoint = "PerEdName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetData( m_names[row].f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recName* name = dialog->GetName();
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( name->f_style_id ) );
        m_listName->SetItem( row, COL_Value, name->GetNameStr() );
        m_names[row] = *name;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndPersona::OnNameDeleteButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listName->DeleteItem( row );
        m_names[row].DeleteAll();
        m_names.erase( m_names.begin() + row );
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Name") );
    }
}

void dlgEditIndPersona::OnNameUpButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row > 0 ) {
        recName attr = m_names[row];
        m_names[row] = m_names[row-1];
        m_names[row-1] = attr;

        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );
        --row;
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditIndPersona::OnNameDownButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row < (long) m_listName->GetItemCount() - 1 ) {
        recName name = m_names[row];
        m_names[row] = m_names[row+1];
        m_names[row+1] = name;

        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );
        row++;
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditIndPersona::OnAttrAddButton( wxCommandEvent& event )
{
    const wxString savepoint = "PerAddAttr";
    dlgEditAttribute* dialog = new dlgEditAttribute( NULL );
    dialog->SetPersonaID( m_persona.f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recAttribute* attr = dialog->GetAttribute();
        int row = m_attributes.size();
        m_listAttr->InsertItem( row, recAttributeType::GetTypeStr( attr->f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, attr->f_val );
        m_attributes.push_back( *attr );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndPersona::OnAttrEditButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Attribute") );
        return;
    }

    const wxString savepoint = "PerEdAttr";
    dlgEditAttribute* dialog = new dlgEditAttribute( NULL );
    dialog->SetAttributeID( m_attributes[row].f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recAttribute* attr = dialog->GetAttribute();
        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( attr->f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, attr->f_val );
        m_attributes[row] = *attr;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndPersona::OnAttrDeleteButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listAttr->DeleteItem( row );
        m_attributes[row].Delete();
        m_attributes.erase( m_attributes.begin() + row );
    } else {
        wxMessageBox( _("No row selected"), _("Delete Attribute") );
    }
}

void dlgEditIndPersona::OnAttrUpButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Attribute Up") );
        return;
    }
    if( row > 0 ) {
        recAttribute attr = m_attributes[row];
        m_attributes[row] = m_attributes[row-1];
        m_attributes[row-1] = attr;

        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );
        --row;
        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );

        m_listAttr->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditIndPersona::OnAttrDownButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Attribute Down") );
        return;
    }
    if( row < (long) m_listAttr->GetItemCount() - 1 ) {
        recAttribute attr = m_attributes[row];
        m_attributes[row] = m_attributes[row+1];
        m_attributes[row+1] = attr;

        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );
        row++;
        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );

        m_listAttr->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}


//============================================================================
//                 Original dlgEditIndividual dialog
//============================================================================


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
