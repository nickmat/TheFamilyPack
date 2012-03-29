/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdRole.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Event Role entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22 October 2010
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

#include <rec/recPersona.h>

#include "dlgEdRole.h"
#include "dlgEd.h"

//============================================================================
//-------------------------[ dlgEditRole ]------------------------------------
//============================================================================

#define ID_PERSONA_MENU_START 30000
#define ID_ROLE_MENU_START    31000

IMPLEMENT_CLASS( dlgEditRole, wxDialog )

BEGIN_EVENT_TABLE( dlgEditRole, wxDialog )
    EVT_MENU_RANGE( ID_ROLE_MENU_START, ID_ROLE_MENU_START+100, dlgEditRole::OnRoleSelect )
END_EVENT_TABLE()


dlgEditRole::dlgEditRole( wxWindow* parent, idt eventID, idt epID )
    : fbDlgEditRole( parent )
{
    m_event.f_id = eventID;
    m_pe.f_id = epID;
}

bool dlgEditRole::TransferDataToWindow()
{
    if( m_event.f_id == 0 ) {
        wxMessageBox(
            _("No Event ID given"),
            _("Edit Role Dialog")
        );
        return false;
    }
    m_event.Read();
    m_roles = recEventType::GetRoles( m_event.f_type_id );
    if( m_pe.f_id == 0 ) {
        m_pe.Clear();
        m_pe.Save();
        m_pe.f_event_id = m_event.f_id;
    } else {
        m_pe.Read();
        wxASSERT( m_event.f_id == m_pe.f_event_id );
    }

    m_staticTextEvent->SetLabel( m_event.f_title );
    if( m_pe.f_per_id != 0 ) {
        m_textCtrlPersona->SetValue( recPersona::GetNameStr( m_pe.f_per_id ) );
    }
    if( m_pe.f_role_id != 0 ) {
        m_textCtrlRole->SetValue( recEventTypeRole::GetName( m_pe.f_role_id ) );
    }
    m_textCtrlNote->SetValue( m_pe.f_note );
    return true;
}

bool dlgEditRole::TransferDataFromWindow()
{
    m_pe.f_note = m_textCtrlNote->GetValue();

    m_pe.Save();
    return true;
}

void dlgEditRole::OnPersonaButton( wxCommandEvent& event )
{
    idt perID;
    unsigned style = TFP_SELECT_STYLE_CREATE;
    if( tfpSelectPersona( &perID, style, m_refID ) ) {
        m_textCtrlPersona->SetValue( recPersona::GetNameStr( perID ) );
        m_pe.f_per_id = perID;
    }
}

void dlgEditRole::OnRoleButton( wxCommandEvent& event )
{
    wxMenu* rmenu = new wxMenu;

    rmenu->Append( ID_ROLE_MENU_START, _("Create new role") );
    for( size_t i = 0 ; i < m_roles.size() ; i++ ) {
        rmenu->Append( ID_ROLE_MENU_START+1+i, m_roles[i].f_name );
    }
    PopupMenu( rmenu );
    delete rmenu;
}

void dlgEditRole::OnRoleSelect( wxCommandEvent& event )
{
    size_t i = event.GetId() - ID_ROLE_MENU_START;

    if( i == 0 )
    {
        m_textCtrlRole->SetValue( _("TODO: Get New Role") );
    } else {
        m_textCtrlRole->SetValue( m_roles[i-1].f_name );
        m_pe.f_role_id = m_roles[i-1].f_id;
    }
}

//============================================================================
//-------------------------[ dlgEditIndRole ]---------------------------------
//============================================================================

dlgEditIndRole::dlgEditIndRole( wxWindow* parent, idt epID ) 
    : fbDlgEditIndRole(parent)
{
    m_ep.ReadID( epID );
    m_event.ReadID( m_ep.FGetID() );
    m_et.ReadID( m_event.FGetTypeID() );
    m_roles = m_et.GetRoles();
}

bool dlgEditIndRole::TransferDataToWindow()
{
    wxASSERT( m_ep.FGetID() != 0 );
    wxASSERT( m_ep.FGetEventID() != 0 );
    wxASSERT( m_ep.FGetPerID() != 0 );

    m_staticName->SetLabel( recPersona::GetNameStr( m_ep.FGetPerID() ) );
    m_staticNameID->SetLabel( recPersona::GetIndividualIdStr( m_ep.FGetPerID() ) );
    m_staticEvent->SetLabel( m_et.GetTypeStr() );
    m_staticEP_ID->SetLabel( m_ep.GetIdStr() );

    wxArrayString roleStrs;
    int sel = 0;
    for( size_t i = 0 ; i < m_roles.size() ; i++ ) {
        roleStrs.push_back( m_roles[i].FGetName() );
        if( m_roles[i].FGetID() == m_ep.FGetRoleID() ) {
            sel = i;
        }
    }
    m_choiceRole->Set( roleStrs );
    m_choiceRole->SetSelection( sel );

    m_textCtrlNote->SetValue( m_ep.FGetNote() );
    return true;
}

bool dlgEditIndRole::TransferDataFromWindow()
{
    int sel = m_choiceRole->GetSelection();
    if( sel >= 0 && sel < (int) m_roles.size() ) {
        m_ep.FSetRoleID( m_roles[sel].FGetID() );
    } else {
        return false;
    }
    m_ep.FSetNote( m_textCtrlNote->GetValue() );

    m_ep.Save();
    return true;
}

void dlgEditIndRole::OnButtonAddClick( wxCommandEvent& event )
{
    // TODO: Create new roles for event type
    wxMessageBox(
        wxT("Not yet implimented\nAdd Role"),
        wxT("OnButtonAddClick")
    );
}


// End of dlgEdRole.cpp file
