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


//============================================================================
//                 dlgCreateIndividual dialog
//============================================================================

dlgCreateIndividual::dlgCreateIndividual( wxWindow* parent, idt famID )
    : fbDlgCreateIndividual( parent )
{
    m_sex = SEX_Unstated;
    m_individual.Clear();
    m_individual.f_fam_id = famID;
    m_persona.Clear();
    m_name.Clear();
}

bool dlgCreateIndividual::TransferDataToWindow()
{
    wxASSERT( m_individual.f_id  == 0 );
    m_individual.Save(); // Create id

    m_staticIndID->SetLabel( m_individual.GetIdStr() );
    m_choiceSex->SetSelection( m_sex );
    m_textSurname->SetValue( m_surname );
    m_textGiven->SetFocus();
    return true;
}

bool dlgCreateIndividual::TransferDataFromWindow()
{
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.f_note = m_textNote->GetValue();
    m_persona.Save();

    m_name.f_per_id = m_persona.f_id;
    m_name.Save();
    int seq = m_name.AddNameParts( m_textGiven->GetValue(), NAME_TYPE_Given_name, 0 );
    m_name.AddNamePart( m_textSurname->GetValue(), NAME_TYPE_Surname, seq );

    m_individual.f_per_id = m_persona.f_id;
    m_individual.Update();
    m_individual.Save();

    return true;
}


//============================================================================
//                 dlgEditIndPersona dialog
//============================================================================

BEGIN_EVENT_TABLE( dlgEditIndPersona, wxDialog )
    EVT_MENU( ID_EDIND_NEW_EVENT,   dlgEditIndPersona::OnNewEvent )
    EVT_MENU( ID_EDIND_EXIST_EVENT, dlgEditIndPersona::OnExistingEvent )
END_EVENT_TABLE()

dlgEditIndPersona::dlgEditIndPersona( wxWindow* parent, idt indID )
    : fbDlgEditIndPersona( parent ), m_individual(indID)
{
    m_persona.ReadID( m_individual.GetPersona() );

    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listAttr->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Value") );
    m_listAttr->InsertColumn( 1, itemCol );

    m_listName->InsertColumn( NC_Number, _("Number") );
    m_listName->InsertColumn( NC_Type, _("Type") );
    m_listName->InsertColumn( NC_Name, _("Name") );

    m_listEvent->InsertColumn( EC_Number, _("Number") );
    m_listEvent->InsertColumn( EC_Role, _("Role") );
    m_listEvent->InsertColumn( EC_Title, _("Title") );
    m_listEvent->InsertColumn( EC_Date, _("Date") );
    m_listEvent->InsertColumn( EC_Place, _("Place") );
 
    m_listRel->InsertColumn( RC_Family, _("Family") );         // Number
    m_listRel->InsertColumn( RC_Ind, _("Individual") );        // Number
    m_listRel->InsertColumn( RC_Relation, _("Relationship") ); // Text
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
        m_listName->InsertItem( i, m_names[i].GetIdStr() );
        m_listName->SetItem( i, NC_Type, recNameStyle::GetStyleStr( m_names[i].f_style_id ) );
        m_listName->SetItem( i, NC_Name, m_names[i].GetNameStr() );
    }
    m_listName->SetColumnWidth( NC_Number, 60 );
    if( m_names.size() ) {
        m_listName->SetColumnWidth( NC_Name, wxLIST_AUTOSIZE );
    }
#if 0
    m_attributes = m_persona.ReadAttributes();
    for( size_t i = 0 ; i < m_attributes.size() ; i++ ) {
        m_listAttr->InsertItem( i, recAttributeType::GetTypeStr( m_attributes[i].f_type_id ) );
        m_listAttr->SetItem( i, COL_Value, m_attributes[i].f_val );
    }
#endif
    m_eps = m_persona.ReadEventPersonas();
    for( size_t i = 0 ; i < m_eps.size() ; i++ ) {
        m_listEvent->InsertItem( i, recEvent::GetIdStr( m_eps[i].f_event_id ) );
        m_listEvent->SetItem( i, EC_Role, recEventTypeRole::GetName( m_eps[i].f_role_id ) );
        m_listEvent->SetItem( i, EC_Title, recEvent::GetTitle( m_eps[i].f_event_id ) );
        m_listEvent->SetItem( i, EC_Date, recEvent::GetDateStr( m_eps[i].f_event_id ) );
        m_listEvent->SetItem( i, EC_Place, recEvent::GetAddressStr( m_eps[i].f_event_id ) );
    }

    

    m_relationships = m_individual.GetIndRelationships();
    for( size_t i = 0 ; i < m_relationships.size() ; i++ ) {
        m_listRel->InsertItem( i, recFamily::GetIdStr( m_relationships[i].GetFamily() ) );
        m_listRel->SetItem( i, RC_Ind, recIndividual::GetFullName( m_relationships[i].GetIndividual2() ) );
        m_listRel->SetItem( i, RC_Relation, m_relationships[i].GetTypeStr() );
    }

    m_notebook->SetSelection( 0 );
    m_textCtrlNote->SetFocus();
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
#if 0
    for( size_t i = 0 ; i < m_attributes.size() ; i++ ) {
        if( m_attributes[i].f_sequence != i+1 ) {
            m_attributes[i].f_sequence = i+1;
            m_attributes[i].Save();
        }
    }
#endif
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
        m_listName->InsertItem( row, name->GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( name->f_style_id ) );
        m_listName->SetItem( row, NC_Name, name->GetNameStr() );
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
        m_listName->SetItem( row, NC_Number, name->GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( name->f_style_id ) );
        m_listName->SetItem( row, NC_Name, name->GetNameStr() );
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

        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );
        --row;
        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );

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

        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );
        row++;
        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditIndPersona::OnAttrAddButton( wxCommandEvent& event )
{
    wxMessageBox( "Not Used", "OnAttrAddButton" );
#if 0
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
#endif
}

void dlgEditIndPersona::OnAttrEditButton( wxCommandEvent& event )
{
    wxMessageBox( "Not Used", "OnAttrEditButton" );
#if 0
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
#endif
}

void dlgEditIndPersona::OnAttrDeleteButton( wxCommandEvent& event )
{
    wxMessageBox( "Not Used", "OnAttrDeleteButton" );
#if 0
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listAttr->DeleteItem( row );
        m_attributes[row].Delete();
        m_attributes.erase( m_attributes.begin() + row );
    } else {
        wxMessageBox( _("No row selected"), _("Delete Attribute") );
    }
#endif
}

void dlgEditIndPersona::OnAttrUpButton( wxCommandEvent& event )
{
    wxMessageBox( "Not Used", "OnAttrUpButton" );
#if 0
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
#endif
}

void dlgEditIndPersona::OnAttrDownButton( wxCommandEvent& event )
{
    wxMessageBox( "Not Used", "OnAttrDownButton" );
#if 0
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
#endif
}

void dlgEditIndPersona::OnEventAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_EDIND_NEW_EVENT, _("&New Event") );
    menu->Append( ID_EDIND_EXIST_EVENT, _("&Existing Event") );
    PopupMenu( menu );
    delete menu;
}

void dlgEditIndPersona::OnNewEvent( wxCommandEvent& event )
{
    const wxString savepoint = "IndAddEvent";
    recDb::Savepoint( savepoint );

    idt typeID = recEventType::Select( recEventType::SF_Individual );
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    idt roleID = recEventTypeRole::Select( typeID, recEventTypeRole::SF_Prime );
    if( roleID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

    recEvent eve(0);
    eve.f_type_id = typeID;
    eve.f_title = wxString::Format(
        _("%s of %s"), recEventType::GetTypeStr( typeID ), m_individual.GetFullName()
    );
    eve.Save();

    recEventPersona ep(0);
    ep.f_event_id = eve.GetID();
    ep.f_per_id = m_persona.f_id;
    ep.f_role_id = roleID;
    ep.Save();

    dlgEditIndEvent* dialog = new dlgEditIndEvent( NULL, eve.GetID() );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_eps.size();
        m_listEvent->InsertItem( row, recEvent::GetIdStr( eve.GetID() ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( roleID ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eve.GetID() ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eve.GetID() ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eve.GetID() ) );
        m_eps.push_back( ep );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndPersona::OnExistingEvent( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnExistingEvent") );
}

void dlgEditIndPersona::OnEventEditButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event") );
        return;
    }

    const wxString savepoint = "IndEdEvent";
    recDb::Savepoint( savepoint );

    dlgEditIndEvent* dialog = new dlgEditIndEvent( NULL, m_eps[row].f_event_id );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndPersona::OnEventDeleteButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listEvent->DeleteItem( row );
        recEvent::DeleteFromDb( m_eps[row].f_event_id );
        m_eps.erase( m_eps.begin() + row );
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Event") );
    }
}

void dlgEditIndPersona::OnEventUpButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventUpButton") );
}

void dlgEditIndPersona::OnEventDownButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventDownButton") );
}

void dlgEditIndPersona::OnRelAddButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelAddButton") );
}

void dlgEditIndPersona::OnRelEditButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelEditButton") );
}

void dlgEditIndPersona::OnRelDeleteButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelDeleteButton") );
}

void dlgEditIndPersona::OnRelUpButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelUpButton") );
}

void dlgEditIndPersona::OnRelDownButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelDownButton") );
}


// End of dlgEdIndividual.cpp
