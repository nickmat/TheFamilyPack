/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSetupDatabase.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create a new database, setup dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     15th December 2021
 * Copyright:   Copyright (c) 2021 Nick Matthews.
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

#ifndef SRC_RG_RGSETUPDATABASE_H
#define SRC_RG_RGSETUPDATABASE_H

#include "fb/fbRgSetupDatabase.h"

#include <rec/recUser.h>


//-------------------------------------------------------------------------------
//-------------------[ rgDlgSetupDatabase ]--------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSetupDatabase : public fbRgSetupDatabase
{
public:
    rgDlgSetupDatabase( wxWindow* parent, const wxString& dbname );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnContactsButton( wxCommandEvent& event ) override;

    wxString       m_database_name;
    recUserSetting m_user_setting;
};

#endif // SRC_RG_RGSETUPDATABASE_H
