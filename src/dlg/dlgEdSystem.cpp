/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdSystem.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database System Settings dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     10 April 2012
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

#include "dlgEdSystem.h"

//============================================================================
//                 dlgEditSystem
//============================================================================

dlgEditSystem::dlgEditSystem( wxWindow* parent )
    : fbDlgEditSystem( parent )
{
    m_userID = recGetCurrentUser();
    m_users = recUser::GetUsers();
}

bool dlgEditSystem::TransferDataToWindow()
{
    for( size_t i = 0 ; i < m_users.size() ; i++ ) {
        if( i == 0 ) {
            m_choiceUser->Append( _("<Select User>") );
        } else {
            m_choiceUser->Append( m_users[i].GetNameStr() );
        }
        if( m_userID == m_users[i].FGetID() ) {
            m_choiceUser->SetSelection( (int) i );
        }
    }

    return true;
}

bool dlgEditSystem::TransferDataFromWindow()
{
    int user = m_choiceUser->GetSelection();
    if( user <= 0 ) {
        wxMessageBox( _("Please select a User"), _("User Required") );
        return false;
    }
    recSetCurrentUser( (idt) user );
    return true;
}

//============================================================================
//                 dlgEditUserSettings
//============================================================================

dlgEditUserSettings::dlgEditUserSettings( wxWindow* parent )
    : fbDlgEditUserSettings( parent )
{
    m_user.ReadID( recGetCurrentUser() );
    m_homeStr = m_user.GetSetting( recUserSetting::UP_HomeScreen );
}

bool dlgEditUserSettings::TransferDataToWindow()
{
    m_staticUserName->SetLabel( m_user.GetNameStr() );
    m_staticUserID->SetLabel( m_user.GetIdStr() );

    m_textCtrlHome->SetValue( m_homeStr );

    return true;
}

bool dlgEditUserSettings::TransferDataFromWindow()
{
    recUserSetting us;
    m_homeStr = m_textCtrlHome->GetValue();

    us.Find( m_user.FGetID(), recUserSetting::UP_HomeScreen );
    us.FSetValue( m_homeStr );
    us.Save();

    return true;
}

// End of dlgEditNamePart.cpp file
