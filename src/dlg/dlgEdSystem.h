/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdSystem.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database System Settings dialog header.
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

#ifndef DLGEDSYSTEM_H
#define DLGEDSYSTEM_H

#include <rec/recSystem.h>
#include <rec/recUser.h>

#include "fbDlg.h"

//============================================================================
//                 dlgEditSystem
//============================================================================

class dlgEditSystem : public fbDlgEditSystem
{
public:
    dlgEditSystem( wxWindow* parent );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    idt        m_userID;
    recUserVec m_users;
};

//============================================================================
//                 dlgEditUserSettings
//============================================================================

class dlgEditUserSettings : public fbDlgEditUserSettings
{
public:
    dlgEditUserSettings( wxWindow* parent );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recUser   m_user;
    wxString  m_homeStr;
};

#endif // DLGEDSYSTEM_H
