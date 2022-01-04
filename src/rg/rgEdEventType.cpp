/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventType.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventType record dialog, GUI only.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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
    m_roles = recEventType::GetRoles( m_et.FGetID() );

    m_listRole->InsertColumn( RC_Number,   _("Number") );
    m_listRole->InsertColumn( RC_Name,     _("Name") );
    m_listRole->InsertColumn( RC_Prime,    _("Prime") );
    m_listRole->InsertColumn( RC_Official, _("Official") );
}

bool rgDlgEditEventType::TransferDataToWindow()
{
    wxArrayString groupList = recEventType::GetGroupStrings();
    m_choiceGroup->Set( groupList );
    m_choiceGroup->SetSelection( int( recEventTypeGrp::other ) );

    for( size_t i = 0 ; i < m_roles.size() ; i++ ) {
        m_listRole->InsertItem( i, m_roles[i].GetIdStr() );
        m_listRole->SetItem( i, RC_Name, m_roles[i].FGetName() );
        m_listRole->SetItem( i, RC_Prime, m_roles[i].GetPrimeStr() );
        m_listRole->SetItem( i, RC_Official, m_roles[i].FGetOfficial() ? "Yes" : "" );
    }

    m_textCtrlValue->SetValue( m_et.FGetName() );

    m_staticTypeID->SetLabel( m_et.GetIdStr() );
    return true;
}

bool rgDlgEditEventType::TransferDataFromWindow()
{
    m_et.FSetGrp( recEventTypeGrp( m_choiceGroup->GetSelection() ) );
    m_et.FSetName( m_textCtrlValue->GetValue() );
    m_et.Save();
    return true;
}

void rgDlgEditEventType::OnButtonRoleAdd( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), _("OnButtonRoleAdd") );
}

void rgDlgEditEventType::OnButtonRoleEdit( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), _("OnButtonRoleEdit") );
}

void rgDlgEditEventType::OnButtonRoleDelete( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), _("OnButtonRoleDelete") );
}

// End of src/rg/rgEdEventType.cpp file
