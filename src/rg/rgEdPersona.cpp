/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Persona entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010-2015, Nick Matthews.
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

#include <wx/tokenzr.h>

#include <rec/recIndividual.h>
#include <rec/recIndPersona.h>
#include <rg/rgDialogs.h>

#include "rgEdReference.h"
#include "rgEdPersona.h"

bool rgEditPersona( wxWindow* parent, idt perID )
{
    wxASSERT( perID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditPersona* dialog = new rgDlgEditPersona( parent, perID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateNamedPersona( wxWindow* wind, idt refID )
{
    wxASSERT( refID!= 0 ); // Must be associated with a reference
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = recPersona::Create( refID );
    idt nameID = rgCreatePersonaName( wind, perID );
    if( nameID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recReferenceEntity::Create( refID, recReferenceEntity::TYPE_Name, nameID );

    if( ! rgEditPersona( wind, perID ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return perID;
}

//============================================================================
//-------------------------[ rgDlgEditPersona ]-------------------------------
//============================================================================

rgDlgEditPersona::rgDlgEditPersona( wxWindow* parent, idt perID )
    : m_persona(perID), m_order(recEO_DatePt),
    fbRgEditPersona( parent )
{
    m_refID = m_persona.FGetRefID();
    wxASSERT( m_refID != 0 );

    m_listName->InsertColumn( NC_Number, _("Number") );
    m_listName->InsertColumn( NC_Type, _("Type") );
    m_listName->InsertColumn( NC_Name, _("Name") );

    m_listEvent->InsertColumn( EV_COL_Number, _("Number") );
    m_listEvent->InsertColumn( EV_COL_Role, _("Role") );
    m_listEvent->InsertColumn( EV_COL_Title, _("Title") );
    m_listEvent->InsertColumn( EV_COL_Date, _("Date") );
    m_listEvent->InsertColumn( EV_COL_Place, _("Place") );

    m_listRel->InsertColumn( RC_Number, _("Number") );
    m_listRel->InsertColumn( RC_Value, _("Value") );
}

bool rgDlgEditPersona::TransferDataToWindow()
{
    m_nameStr = m_persona.GetNameStr();
    m_staticPerName->SetLabel( m_nameStr );
    m_staticPerID->SetLabel( m_persona.GetIdStr() );

    m_choiceSex->SetSelection( (int) m_persona.f_sex );
    m_textCtrlNote->SetValue(  m_persona.f_note );

    m_indLinks = m_persona.GetIndividualIDs();
    m_staticIndId->SetLabel( GetIndLinksString() );

    UpdateNameList();
    UpdateEventList();
    UpdateRelList();
    return true;
}

bool rgDlgEditPersona::TransferDataFromWindow()
{
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.f_note = m_textCtrlNote->GetValue();
    m_persona.Save();
    return true;
}

wxString rgDlgEditPersona::GetIndLinksString() const
{
    wxString txt;

    for( size_t i = 0 ; i < m_indLinks.size() ; i++ ) {
        if( i > 0 ) {
            txt << wxT(", ");
        }
        txt << wxT("I ") << m_indLinks[i];
    }
    return txt;
}

void rgDlgEditPersona::UpdateNameList( idt nameID )
{
    m_names = m_persona.ReadNames();
    m_listName->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        m_listName->InsertItem( i, m_names[i].GetIdStr() );
        m_listName->SetItem( i, NC_Type, recNameStyle::GetStyleStr( m_names[i].FGetTypeID() ) );
        m_listName->SetItem( i, NC_Name, m_names[i].GetNameStr() );
        if( nameID == m_names[i].FGetID() ) {
            m_listName->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    if( m_names.size() ) {
        m_listName->SetColumnWidth( NC_Name, -1 );
    }
    if( row >= 0 ) {
        m_listName->EnsureVisible( row );
    }
}

void rgDlgEditPersona::UpdateEventList( idt eveID )
{
    m_evpers = m_persona.ReadEventaPersonas( m_order );
    m_listEvent->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_evpers.size() ; i++ ) {
        m_listEvent->InsertItem( i, recEvent::GetIdStr( m_evpers[i].f_eventa_id ) );
        m_listEvent->SetItem( i, EV_COL_Role, recEventTypeRole::GetName( m_evpers[i].f_role_id ) );
        m_listEvent->SetItem( i, EV_COL_Title, recEvent::GetTitle( m_evpers[i].f_eventa_id ) );
        m_listEvent->SetItem( i, EV_COL_Date, recEvent::GetDateStr( m_evpers[i].f_eventa_id ) );
        m_listEvent->SetItem( i, EV_COL_Place, recEvent::GetAddressStr( m_evpers[i].f_eventa_id ) );
        if( eveID == m_evpers[i].FGetEventaID() ) {
            m_listEvent->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_order == recEO_PerSeq && m_evpers[i].FGetPerSeq() != i+1 ) {
            m_evpers[i].FSetPerSeq( i+1 );
            m_evpers[i].Save();
        }
    }
    if( row >= 0 ) {
        m_listEvent->EnsureVisible( row );
    }
}

void rgDlgEditPersona::UpdateRelList( idt relID )
{
    m_relationships = m_persona.ReadRelationships();
    m_listRel->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_relationships.size() ; i++ ) {
        m_listRel->InsertItem( i, m_relationships[i].GetIdStr() );
        m_listRel->SetItem( i, RC_Value, m_relationships[i].GetRelOfPersonaStr( m_persona.f_id ) );
        if( relID == m_relationships[i].FGetID() ) {
            m_listRel->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    if( m_relationships.size() ) {
        m_listRel->SetColumnWidth( RC_Value, -1 );
    }
    if( row >= 0 ) {
        m_listRel->EnsureVisible( row );
    }
}

void rgDlgEditPersona::OnPageChanged( wxBookCtrlEvent& event )
{
    Page page = (Page) m_notebook->GetSelection();
    switch( page )
    {
    case PAGE_Persona:
        break;
    case PAGE_Name:
        UpdateNameList();
        break;
    case PAGE_Event:
        UpdateEventList();
        break;
    case PAGE_Rel:
        UpdateRelList();
        break;
    default:
        wxASSERT( false );
    }
    PostSizeEvent();
}

void rgDlgEditPersona::OnIndLinkButton( wxCommandEvent& event )
{
    idt indID = rgSelectIndividual( this );
    if( indID == 0 ) return;

    recIndividualPersona lp(0);
    lp.f_ind_id = indID;
    lp.f_per_id = m_persona.f_id;
    lp.f_conf = 0.999;
    lp.Save();

    m_staticIndId->SetLabel( recIndividual::GetIdStr( indID ) );
}

void rgDlgEditPersona::OnNameAddButton( wxCommandEvent& event )
{
    idt nameID = rgCreatePersonaName( this, m_persona.FGetID() );
    if( nameID ) {
        recReferenceEntity::Create( m_refID, recReferenceEntity::TYPE_Name, nameID );
        UpdateNameList( nameID );
    }
}

void rgDlgEditPersona::OnNameEditButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    if( rgEditName( this, nameID ) ) {
        UpdateNameList( nameID );
    }
}

void rgDlgEditPersona::OnNameDeleteButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    wxString mess = wxString::Format(
        "Remove Name %s: %s\nfrom Persona %s?",
        recName::GetIdStr( nameID ), recName::GetNameStr( nameID ),
        m_persona.GetIdStr()
    );
    int ans = wxMessageBox( mess, _("Delete Name"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    recName::RemoveFromDatabase( nameID );
    UpdateNameList();
}

void rgDlgEditPersona::OnNameUpButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_names[row].FGetSequence();
    m_names[row].FSetSequence( m_names[row-1].FGetSequence() );
    m_names[row].Save();
    m_names[row-1].FSetSequence( seq );
    m_names[row-1].Save();
    UpdateNameList( m_names[row].FGetID() );
}

void rgDlgEditPersona::OnNameDownButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row == m_listName->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_names[row].FGetSequence();
    m_names[row].FSetSequence( m_names[row+1].FGetSequence() );
    m_names[row].Save();
    m_names[row+1].FSetSequence( seq );
    m_names[row+1].Save();
    UpdateNameList( m_names[row].FGetID() );
}

void rgDlgEditPersona::OnEventAddButton( wxCommandEvent& event )
{
    idt eveID = rgCreateEventa( this, m_refID );
    if( eveID ) {
        recReferenceEntity::Create( m_refID, recReferenceEntity::TYPE_Event, eveID );
        UpdateEventList( eveID );
    }
}

void rgDlgEditPersona::OnEventEditButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event"), wxOK | wxCENTRE, this );
        return;
    }
    idt eventID = m_evpers[row].FGetEventaID();
    if( rgEditEventa( this, eventID ) ) {
        UpdateEventList( eventID );
    }
}

void rgDlgEditPersona::OnEventDeleteButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete From Event") );
        return;
    }
    idt eveID = m_evpers[row].FGetEventaID();
    wxString mess = wxString::Format(
        "Remove %s %s from Event %s\n%s?",
        m_persona.GetNameStr(), m_persona.GetIdStr(),
        recEvent::GetIdStr( eveID ), recEvent::GetTitle( eveID )
    );
    int ans = wxMessageBox( mess, _("Delete From Event"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    m_evpers[row].Delete();
    UpdateEventList();
}

void rgDlgEditPersona::OnEventUpButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_evpers[row].FGetPerSeq();
    m_evpers[row].FSetPerSeq( m_evpers[row-1].FGetPerSeq() );
    m_evpers[row].Save();
    m_evpers[row-1].FSetPerSeq( seq );
    m_evpers[row-1].Save();
    UpdateEventList( m_evpers[row].FGetEventaID() );
}

void rgDlgEditPersona::OnEventDownButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row == m_listEvent->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_evpers[row].FGetPerSeq();
    m_evpers[row].FSetPerSeq( m_evpers[row+1].FGetPerSeq() );
    m_evpers[row].Save();
    m_evpers[row+1].FSetPerSeq( seq );
    m_evpers[row+1].Save();
    UpdateEventList( m_evpers[row].FGetEventaID() );
}

void rgDlgEditPersona::OnOrderBy( wxCommandEvent& event )
{
    switch( event.GetSelection() )
    {
    case 0:
        m_order = recEO_DatePt;
        m_buttonEventUp->Enable( false );
        m_buttonEventDn->Enable( false );
        break;
    case 1:
        m_order = recEO_PerSeq;
        m_buttonEventUp->Enable( true );
        m_buttonEventDn->Enable( true );
        break;
    default:
        return;
    }
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    idt eveID = ( row >= 0 ) ? m_evpers[row].FGetEventaID() : 0;
    UpdateEventList( eveID );
}

void rgDlgEditPersona::OnRelAddButton( wxCommandEvent& event )
{
    idt relID = rgCreatePersonaRelationship( this, m_refID, "", m_persona.FGetID() );
    if( relID ) {
        recReferenceEntity::Create( m_refID, recReferenceEntity::TYPE_Relationship, relID );
        UpdateRelList( relID );
    }
}

void rgDlgEditPersona::OnRelEditButton( wxCommandEvent& event )
{
    long row = m_listRel->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Relationship") );
        return;
    }
    idt relID = m_relationships[row].FGetID();
    if( rgEditPersonaRelationship( this, relID ) ) {
        UpdateRelList( relID );
    }
}

void rgDlgEditPersona::OnRelDeleteButton( wxCommandEvent& event )
{
    long row = m_listRel->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Relationship") );
        return;
    }
    idt relID = m_relationships[row].FGetID();
    wxString mess = wxString::Format(
        "Remove Relationship %s\n%s\nfrom Persona?",
        m_relationships[row].GetIdStr(), m_relationships[row].FGetDescrip()
    );
    int ans = wxMessageBox( mess, _("Delete Relationship"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    m_relationships[row].Delete();
    UpdateRelList();
}

// End of dlgEdPersona.cpp file
