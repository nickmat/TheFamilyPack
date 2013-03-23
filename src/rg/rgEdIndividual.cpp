/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdIndividual.cpp
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
#include <rg/rgDialogs.h>

#include "rgEdIndividual.h"

bool rgEditIndividual( wxWindow* parent, idt indID  )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;
    rgDlgEditIndividual* dialog = new rgDlgEditIndividual( parent, indID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

//============================================================================
//                 rgDlgEditIndividual dialog
//============================================================================

BEGIN_EVENT_TABLE( rgDlgEditIndividual, wxDialog )
    EVT_MENU( ID_EDIND_NEW_EVENT,   rgDlgEditIndividual::OnNewEvent )
    EVT_MENU( ID_EDIND_EXIST_EVENT, rgDlgEditIndividual::OnExistingEvent )
    EVT_MENU( ID_EDIND_UNLINK_EVENT, rgDlgEditIndividual::OnUnlinkEvent )
    EVT_MENU( ID_EDIND_DELETE_EVENT, rgDlgEditIndividual::OnDeleteEvent )
END_EVENT_TABLE()

rgDlgEditIndividual::rgDlgEditIndividual( wxWindow* parent, idt indID )
    : m_individual(indID), m_order(recEO_DatePt),
    fbRgEditIndividual( parent )
{
    m_persona.ReadID( m_individual.GetPersona() );

    m_listName->InsertColumn( NC_Number, _("Number") );
    m_listName->InsertColumn( NC_Type, _("Type") );
    m_listName->InsertColumn( NC_Name, _("Name") );

    m_listEvent->InsertColumn( EC_Number, _("Number") );
    m_listEvent->InsertColumn( EC_Role, _("Role") );
    m_listEvent->InsertColumn( EC_Title, _("Title") );
    m_listEvent->InsertColumn( EC_Date, _("Date") );
    m_listEvent->InsertColumn( EC_Place, _("Place") );
}

bool rgDlgEditIndividual::TransferDataToWindow()
{
    wxASSERT( m_individual.FGetID() != 0 );

    m_staticTextEpitaph->SetLabel( m_individual.f_epitaph );
    m_choiceSex->SetSelection( (int) m_persona.f_sex );
    m_textCtrlNote->SetValue(  m_persona.f_note );
    m_staticIndID->SetLabel( m_individual.GetIdStr() );

    UpdateNameList();
    UpdateEventList();

    m_notebook->SetSelection( 0 );
    m_textCtrlNote->SetFocus();
    return true;
}

bool rgDlgEditIndividual::TransferDataFromWindow()
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
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        if( m_ies[i].FGetIndSeq() != i+1 ) {
            m_ies[i].FSetIndSeq( i+1 );
            m_ies[i].Save();
        }
    }
    m_individual.Update();
    m_individual.Save();
    return true;
}

void rgDlgEditIndividual::UpdateNameList( idt nameID )
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
    // Check for name change.
    wxString name = m_persona.GetNameStr();
    if( name != m_nameStr ) {
        m_staticPerName->SetLabel( name );
        m_nameStr = name;
    }
}

void rgDlgEditIndividual::UpdateEventList( idt eveID )
{
    m_ies = m_individual.GetEvents( m_order );
    m_listEvent->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        m_listEvent->InsertItem( i, recEvent::GetIdStr( m_ies[i].FGetEventID() ) );
        m_listEvent->SetItem( i, EC_Role, recEventTypeRole::GetName( m_ies[i].FGetRoleID() ) );
        m_listEvent->SetItem( i, EC_Title, recEvent::GetTitle( m_ies[i].FGetEventID() ) );
        m_listEvent->SetItem( i, EC_Date, recEvent::GetDateStr( m_ies[i].FGetEventID() ) );
        m_listEvent->SetItem( i, EC_Place, recEvent::GetAddressStr( m_ies[i].FGetEventID() ) );
        if( eveID == m_ies[i].FGetEventID() ) {
            m_listEvent->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_order == recEO_PerSeq && m_ies[i].FGetIndSeq() != i+1 ) {
            m_ies[i].FSetIndSeq( i+1 );
            m_ies[i].Save();
        }
    }
    if( row >= 0 ) {
        m_listEvent->EnsureVisible( row );
    }
}

void rgDlgEditIndividual::OnPageChanged( wxBookCtrlEvent& event )
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
    default:
        wxASSERT( false );
    }
    PostSizeEvent();
}

void rgDlgEditIndividual::OnNameAddButton( wxCommandEvent& event )
{
    idt nameID = rgCreateName( this, m_persona.FGetID() );
    if( nameID ) {
        UpdateNameList( nameID );
    }
}

void rgDlgEditIndividual::OnNameEditButton( wxCommandEvent& event )
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

void rgDlgEditIndividual::OnNameDeleteButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    wxString mess = wxString::Format( 
        "Remove Name %s: %s\nfrom Individual %s?", 
        recName::GetIdStr( nameID ), recName::GetNameStr( nameID ),
        m_individual.GetIdStr()
    );
    int ans = wxMessageBox( mess, _("Delete Name"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    recName::RemoveFromDatabase( nameID );
    UpdateNameList();
}

void rgDlgEditIndividual::OnNameUpButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_names[row].FGetPerSeq();
    m_names[row].FSetPerSeq( m_names[row-1].FGetPerSeq() );
    m_names[row].Save();
    m_names[row-1].FSetPerSeq( seq );
    m_names[row-1].Save();
    UpdateNameList( m_names[row].FGetID() );
}

void rgDlgEditIndividual::OnNameDownButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row == m_listName->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_names[row].FGetPerSeq();
    m_names[row].FSetPerSeq( m_names[row+1].FGetPerSeq() );
    m_names[row].Save();
    m_names[row+1].FSetPerSeq( seq );
    m_names[row+1].Save();
    UpdateNameList( m_names[row].FGetID() );
}

void rgDlgEditIndividual::OnEventAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_EDIND_NEW_EVENT, _("&New Event") );
    menu->Append( ID_EDIND_EXIST_EVENT, _("&Existing Event") );
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditIndividual::OnNewEvent( wxCommandEvent& event )
{
    idt eveID = rgCreateIndEvent( this, m_individual.FGetID() );
    if( eveID ) {
        UpdateEventList( eveID );
    }
}

void rgDlgEditIndividual::OnExistingEvent( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt eveID = rgSelectIndEvent( this );
    if( eveID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

    recIndividualEvent ie(0);
    ie.FSetEventID( eveID );
    ie.FSetIndID( m_individual.FGetID() );
    ie.Save();

    if( ! rgEditIndEventRole( this, ie.FGetID(), rgSHOWROLE_All )  ) {
        recDb::Rollback( savepoint );
        return;
    }

    if( rgEditEvent( this, eveID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        UpdateEventList( eveID );
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditIndividual::OnEventEditButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event") );
        return;
    }
    idt eveID = m_ies[row].FGetEventID();
    if( rgEditEvent( this, eveID ) ) {
        UpdateEventList( eveID );
    }
}

void rgDlgEditIndividual::OnEventDeleteButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_currentRow = row;
        wxMenu* menu = new wxMenu;
        menu->Append( ID_EDIND_UNLINK_EVENT, _("&Unlink Event") );
        menu->Append( ID_EDIND_DELETE_EVENT, _("&Delete Event") );
        PopupMenu( menu );
        delete menu;
    } else {
        wxMessageBox( _("No row selected"), _("Delete Event") );
    }
}

void rgDlgEditIndividual::OnUnlinkEvent( wxCommandEvent& event )
{
    recIndividualEvent::Delete( m_ies[m_currentRow].FGetID() );
    UpdateEventList();
}

void rgDlgEditIndividual::OnDeleteEvent( wxCommandEvent& event )
{
    int ans = wxMessageBox( 
        _("Remove Event completely from database?"), _("Delete Event"),
        wxYES_NO | wxCANCEL, this
    );
    if( ans != wxYES ) {
        return;
    }
    recEvent::RemoveIncOrphansFromDatabase( m_ies[m_currentRow].FGetEventID() );
    UpdateEventList();
}

void rgDlgEditIndividual::OnEventUpButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Event Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_ies[row].FGetIndSeq();
    m_ies[row].FSetIndSeq( m_ies[row-1].FGetIndSeq() );
    m_ies[row].Save();
    m_ies[row-1].FSetIndSeq( seq );
    m_ies[row-1].Save();
    UpdateEventList( m_ies[row].FGetEventID() );
}

void rgDlgEditIndividual::OnEventDownButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Event Down") );
        return;
    }
    if( row == m_listEvent->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_ies[row].FGetIndSeq();
    m_ies[row].FSetIndSeq( m_ies[row+1].FGetIndSeq() );
    m_ies[row].Save();
    m_ies[row+1].FSetIndSeq( seq );
    m_ies[row+1].Save();
    UpdateEventList( m_ies[row].FGetEventID() );
}

void rgDlgEditIndividual::OnEventOrderBy( wxCommandEvent& event )
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
    idt eveID = ( row >= 0 ) ? m_ies[row].FGetEventID() : 0;
    UpdateEventList( eveID );
}

// End of src/rg/rgEdIndividual.cpp
