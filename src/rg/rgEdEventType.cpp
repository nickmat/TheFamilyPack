/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventType.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventType record dialog, GUI only.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
 * Copyright:   Copyright (c) 2012..2023, Nick Matthews.
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

#include "rg/rgDialogs.h"
#include "rgEdEventType.h"

bool rgEditEventType( wxWindow* wind, idt etID )
{
    wxASSERT( etID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEventType* dialog = new rgDlgEditEventType( wind, etID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateEventType( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEventType et(0);
    et.CreateUidChanged();
    et.Save();
    idt etID = et.FGetID();
    if( rgEditEventType( wind, etID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        etID = 0;
    }
    return etID;
}

//============================================================================
//-------------------------[ rgDlgEditEventType ]-----------------------------
//============================================================================

rgDlgEditEventType::rgDlgEditEventType( wxWindow* parent, idt etID ) 
    : m_et(etID), fbRgEditEventType(parent) 
{
    wxASSERT( m_et.FGetID() != 0 );

    m_listRole->InsertColumn( RC_Number,   _("Number") );
    m_listRole->InsertColumn( RC_Name,     _("Name") );
    m_listRole->InsertColumn( RC_Prime,    _("Prime") );
    m_listRole->InsertColumn( RC_Official, _("Official") );
}

bool rgDlgEditEventType::TransferDataToWindow()
{
    wxArrayString groupList = recEventType::GetGroupStrings();
    m_choiceGroup->Set( groupList );
    m_choiceGroup->SetSelection( int( m_et.FGetGrp() ) );
    m_spinCtrlSig->SetValue( m_et.FGetSig() );
    m_textCtrlValue->SetValue( m_et.FGetName() );
    m_textCtrlUid->SetValue( m_et.FGetUid() );
    wxString changed = calStrFromJdn( m_et.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );
    m_staticTypeID->SetLabel( m_et.GetIdStr() );
    UpdateRoleList( 0 );
    return true;
}

bool rgDlgEditEventType::TransferDataFromWindow()
{
    m_et.FSetGrp( recEventTypeGrp( m_choiceGroup->GetSelection() ) );
    m_et.FSetSig( m_spinCtrlSig->GetValue() );
    m_et.FSetName( m_textCtrlValue->GetValue() );
    m_et.Save();
    return true;
}

void rgDlgEditEventType::UpdateRoleList( idt roleID )
{
    m_roles = recEventType::GetRoles( m_et.FGetID() );
    m_listRole->DeleteAllItems();
    int row = -1;
    for( size_t i = 0; i < m_roles.size(); i++ ) {
        m_listRole->InsertItem( i, m_roles[i].GetIdStr() );
        m_listRole->SetItem( i, RC_Name, m_roles[i].FGetName() );
        m_listRole->SetItem( i, RC_Prime, m_roles[i].GetPrimeStr() );
        m_listRole->SetItem( i, RC_Official, m_roles[i].FGetOfficial() ? "Yes" : "" );
        if( roleID == m_roles[i].FGetID() ) {
            m_listRole->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    if( !m_roles.empty() ) {
        m_listRole->SetColumnWidth( RC_Name, -1 );
    }
    if( row > 0 ) {
        m_listRole->EnsureVisible( row );
    }
    RoleButtonsEnable( row );
}

void rgDlgEditEventType::RoleButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonRoleEdit->Disable();
        m_buttonRoleDelete->Disable();
        return;
    }
    m_buttonRoleEdit->Enable();
    m_buttonRoleDelete->Enable();
}

void rgDlgEditEventType::OnRoleSelect( wxListEvent& event )
{
    long row = m_listRole->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    RoleButtonsEnable( row );
}

void rgDlgEditEventType::OnRoleDeselect( wxListEvent& event )
{
    RoleButtonsEnable( -1 );
}

void rgDlgEditEventType::OnButtonRoleAdd( wxCommandEvent& event )
{
    idt roleID = rgCreateRole( this, m_et.FGetID() );
    if( roleID ) {
        UpdateRoleList( roleID );
    }
}

void rgDlgEditEventType::OnButtonRoleEdit( wxCommandEvent& event )
{
    long row = m_listRole->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    wxASSERT( row != wxNOT_FOUND ); // Should not have been enabled then!
    idt roleID = m_roles[row].FGetID();
    if( rgEditRole( this, roleID ) ) {
        UpdateRoleList( roleID );
    }
}

void rgDlgEditEventType::OnButtonRoleDelete( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), _("OnButtonRoleDelete") );
    long row = m_listRole->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    wxASSERT( row != wxNOT_FOUND ); // Should not have been enabled then!
    idt roleID = m_roles[row].FGetID();
    if( roleID < 0 ) {
        wxMessageBox( "Connot delete common data.", "Delete Role Error" );
        return;
    }
    int ret = wxMessageBox(
        "Remove " + m_roles[row].GetIdStr() + " from database?",
        "Delete Role",
        wxOK | wxCANCEL
    );
    if( ret == wxOK ) {
        bool ret2 = recEventTypeRole::DeleteIfOrphaned( roleID );
        if( ret2 == false ) {
            wxMessageBox(
                "Unable to delete " + m_roles[row].GetIdStr() + ". Role in use.",
                "Delete Role"
            );
            return;
        }
        UpdateRoleList( 0 );
    }
}

// End of src/rg/rgEdEventType.cpp file
