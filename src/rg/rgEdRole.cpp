/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdRole.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventTypeRole record dialog, GUI only.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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
#include "rgEdRole.h"

bool rgEditRole( wxWindow* wind, idt roleID )
{
    wxASSERT( roleID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRole* dialog = new rgDlgEditRole( wind, roleID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateRole( wxWindow* wind, idt etID )
{
    wxASSERT( etID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEventTypeRole role(0);
    role.FSetTypeID( etID );
    role.Save();
    idt roleID = role.FGetID();
    if( rgEditRole( wind, roleID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        roleID = 0;
    }
    return roleID;
}

//============================================================================
//-------------------------[ rgDlgEditRole ]----------------------------------
//============================================================================

rgDlgEditRole::rgDlgEditRole( wxWindow* parent, idt etrID ) 
    : m_role(etrID), fbRgEditRole(parent) 
{
    m_et.ReadID( m_role.FGetTypeID() );
}

bool rgDlgEditRole::TransferDataToWindow()
{
    wxASSERT( m_role.FGetID() != 0 );
    wxASSERT( m_et.FGetID() != 0 );
    m_staticEventType->SetLabel( m_et.FGetName() );
    m_staticEventTypeID->SetLabel( m_et.GetIdStr() );
    m_staticTypeGroup->SetLabel( m_et.GetGroupStr() );
    m_textCtrlValue->SetValue( m_role.FGetName() );

    wxArrayString primeList;
    primeList.push_back( _("No") );
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
    m_staticRoleID->SetLabel( m_role.GetIdStr() );
    return true;
}

bool rgDlgEditRole::TransferDataFromWindow()
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

void rgDlgEditRole::OnChoicePrime( wxCommandEvent& event )
{
    if( m_choicePrime->GetSelection() == 0 ) {
        m_checkOfficial->Enable( true );
    } else {
        m_checkOfficial->Enable( false );
    }
}

// End of src/rg/rgEdRole.cpp file
