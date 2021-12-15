/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSetupDatabase.cpp
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "rgSetupDatabase.h"
#include "rg/rgDialogs.h"


bool rgSetupDatabase( wxWindow * wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgSetupDatabase dialog( wind );

    if ( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    }
    else {
        recDb::Rollback( savepoint );
    }
    return ret;
}


//-------------------------------------------------------------------------------
//-------------------[ rgDlgSetupDatabase ]--------------------------------------
//-------------------------------------------------------------------------------

rgDlgSetupDatabase::rgDlgSetupDatabase( wxWindow* parent )
    : fbRgSetupDatabase( parent )
{
}

bool rgDlgSetupDatabase::TransferDataToWindow()
{
    return true;
}

bool rgDlgSetupDatabase::TransferDataFromWindow()
{
    return true;
}

// End of src/rg/rgSetupDatabase.cpp file
