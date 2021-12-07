/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdSystem.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database System Settings dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10 April 2012
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
#include "rgEdSystem.h"

bool rgEditSystemSettings( wxWindow* parent )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;
    rgDlgEditSystem* dialog = new rgDlgEditSystem( parent );

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
//                 dlgEditSystem
//============================================================================

rgDlgEditSystem::rgDlgEditSystem( wxWindow* parent )
    : fbRgEditSystem( parent )
{
    m_userID = recGetCurrentUser();
    m_users = recUser::GetUsers();
}

bool rgDlgEditSystem::TransferDataToWindow()
{
    for( auto& user : m_users ) {
        m_choiceUser->Append( user.GetNameStr() );
        if( user.FGetID() == m_userID ) {
            size_t cnt = m_choiceUser->GetCount() - 1;
            m_choiceUser->SetSelection( cnt );
        }
    }
    return true;
}

bool rgDlgEditSystem::TransferDataFromWindow()
{
    int i = m_choiceUser->GetSelection();
    recSetCurrentUser( m_users[i].FGetID() );
    return true;
}

// End of src/rg/rgEdSystem.cpp file
