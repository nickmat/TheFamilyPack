/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdUser.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database User Settings dialog.
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

#include <rg/rgDialogs.h>
#include "rgEdUser.h"

bool rgEditUserSettings( wxWindow* parent )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;
    rgDlgEditUserSettings* dialog = new rgDlgEditUserSettings( parent );

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
//                 dlgEditUserSettings
//============================================================================

rgDlgEditUserSettings::rgDlgEditUserSettings( wxWindow* parent )
    : fbRgEditUserSettings( parent )
{
    m_user.ReadID( recGetCurrentUser() );
    m_homeStr = m_user.GetSetting( recUserSetting::UP_HomeScreen );
}

bool rgDlgEditUserSettings::TransferDataToWindow()
{
    m_staticUserName->SetLabel( m_user.GetNameStr() );
    m_staticUserID->SetLabel( m_user.GetIdStr() );

    m_textCtrlHome->SetValue( m_homeStr );

    return true;
}

bool rgDlgEditUserSettings::TransferDataFromWindow()
{
    recUserSetting us;
    m_homeStr = m_textCtrlHome->GetValue();

    us.Find( m_user.FGetID(), recUserSetting::UP_HomeScreen );
    us.FSetValue( m_homeStr );
    us.Save();

    return true;
}

// End of src/rg/rgEdUser.cpp file
