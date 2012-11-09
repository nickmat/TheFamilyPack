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
#include <rec/recIndividual.h>

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

dlgEditIndRole::dlgEditIndRole( wxWindow* parent, idt ieID ) 
    : fbDlgEditIndRole(parent)
{
    m_ie.ReadID( ieID );
    m_event.ReadID( m_ie.FGetEventID() );
    m_et.ReadID( m_event.FGetTypeID() );
}

bool dlgEditIndRole::TransferDataToWindow()
{
    wxASSERT( m_ie.FGetID() != 0 );
    wxASSERT( m_ie.FGetEventID() != 0 );
    wxASSERT( m_ie.FGetIndID() != 0 );

    m_staticName->SetLabel( recIndividual::GetFullName( m_ie.FGetIndID() ) );
    m_staticNameID->SetLabel( recIndividual::GetIdStr( m_ie.FGetIndID() ) );
    m_staticEvent->SetLabel( m_et.GetTypeStr() );
    m_staticEP_ID->SetLabel( m_ie.GetIdStr() );

    SetRoleList( m_ie.FGetRoleID() );

    m_textCtrlNote->SetValue( m_ie.FGetNote() );
    return true;
}

bool dlgEditIndRole::TransferDataFromWindow()
{
    int sel = m_choiceRole->GetSelection();
    if( sel >= 0 && sel < (int) m_roles.size() ) {
        m_ie.FSetRoleID( m_roles[sel].FGetID() );
    } else {
        return false;
    }
    m_ie.FSetNote( m_textCtrlNote->GetValue() );

    m_ie.Save();
    return true;
}

void dlgEditIndRole::SetRoleList( idt selection )
{
    m_roles = m_et.GetRoles();
    wxArrayString roleStrs;
    int sel = 0;
    for( size_t i = 0 ; i < m_roles.size() ; i++ ) {
        roleStrs.push_back( m_roles[i].FGetName() );
        if( m_roles[i].FGetID() == selection ) {
            sel = i;
        }
    }
    m_choiceRole->Set( roleStrs );
    m_choiceRole->SetSelection( sel );
}

void dlgEditIndRole::OnButtonAddClick( wxCommandEvent& event )
{
    const wxString savepoint = "CreateRole";
    recDb::Savepoint( savepoint );

    dlgCreateRole* dialog = new dlgCreateRole( NULL, m_event.FGetTypeID() );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        SetRoleList( dialog->GetRoleID() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

//============================================================================
//-------------------------[ dlgCreateRole ]---------------------------------
//============================================================================

dlgCreateRole::dlgCreateRole( wxWindow* parent, idt etID ) 
    : m_et(etID), m_role(0), fbDlgCreateRole(parent) 
{
    m_role.FSetTypeID( etID );
    m_role.FSetPrime( recEventTypeRole::PRIME_First );
}

bool dlgCreateRole::TransferDataToWindow()
{
    if( m_role.FGetID() == 0 ) {
        m_role.Save();
    }
    m_staticRoleID->SetLabel( m_role.GetIdStr() );
    m_textEventType->SetValue( m_et.FGetName() );
    m_textCtrlValue->SetValue( m_role.FGetName() );

    wxArrayString primeList;
    primeList.push_back( _("Other Role") );
    switch( m_et.FGetGrp() )
    {
    case recEventType::ETYPE_Grp_Birth:
    case recEventType::ETYPE_Grp_Nr_Birth:
    case recEventType::ETYPE_Grp_Death:
    case recEventType::ETYPE_Grp_Nr_Death:
    case recEventType::ETYPE_Grp_Other:
    case recEventType::ETYPE_Grp_Personal:
        primeList.push_back( _("Prime Role") );
        break;
    case recEventType::ETYPE_Grp_Union:
    case recEventType::ETYPE_Grp_Family:
        primeList.push_back( _("1st Prime Role") );
        primeList.push_back( _("2nd Prime Role") );
        primeList.push_back( _("Either Prime Role") );
        break;
    default:
        return false;
    }
    m_choicePrime->Set( primeList );
    m_choicePrime->SetSelection( m_role.FGetPrime() );
    m_checkOfficial->Enable( !m_role.FGetPrime() );
    return true;
}

bool dlgCreateRole::TransferDataFromWindow()
{
    m_role.FSetPrime( m_choicePrime->GetSelection() );
    if( !m_role.FGetPrime() ) {
        m_role.FSetOfficial( m_checkOfficial->GetValue() );
    } else {
        m_role.FSetOfficial( false );
    }
    m_role.FSetName( m_textCtrlValue->GetValue() );
    m_role.Save();
    return true;
}

void dlgCreateRole::OnSelectPrime( wxCommandEvent& event )
{
    if( m_choicePrime->GetSelection() == 0 ) {
        m_checkOfficial->Enable( true );
    } else {
        m_checkOfficial->Enable( false );
    }
}


// End of dlgEdRole.cpp file
