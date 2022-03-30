/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSetupDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create a new database, setup dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     15th December 2021
 * Copyright:   Copyright (c) 2021..2022 Nick Matthews.
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

#include <rec/recFamily.h>
#include <rec/recResearcher.h>
#include <rec/recSystem.h>

/* Note, when this dialog is called we know no data has been entered
 * yet into the database. So we can setup User U1 directly.
 */

bool rgSetupDatabase( wxWindow * wind, const wxString& dbname )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    rgDlgSetupDatabase dialog( wind, dbname );

    if ( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        return true;
    }
    recDb::Rollback( savepoint );
    return false;
}


//-------------------------------------------------------------------------------
//-------------------[ rgDlgSetupDatabase ]--------------------------------------
//-------------------------------------------------------------------------------

rgDlgSetupDatabase::rgDlgSetupDatabase( wxWindow* parent, const wxString& dbname )
    : m_database_name(dbname),  fbRgSetupDatabase( parent )
{
    m_user_setting.Find( 1, recUserSetting::Property::home_screen );
}

bool rgDlgSetupDatabase::TransferDataToWindow()
{
    m_staticDbName->SetLabel( m_database_name );
    recContactList cl( 0 );
    cl.Save();
    idt clID = cl.FGetID();
    recResearcher res( 0 );
    res.FSetID( 1 );
    res.FSetConListID( clID );
    res.FSetUid( recCreateUid() );
    res.Save();
    recUser user( 1 );
    user.FSetResID( res.FGetID() );
    user.Save();
    recSetCurrentUser( 1 );
    return true;
}

bool rgDlgSetupDatabase::TransferDataFromWindow()
{
    wxString name = m_textCtrlUserName->GetValue();
    if( name.empty() ) {
        name = "Unnamed"; // We don't want a blank name!
    }
    recResearcher res( 1 );
    res.FSetName( name );
    res.Save();
    wxString home = m_comboBoxHomePage->GetValue();
    home.Trim( false );
    if( !home.empty() ) {
        size_t pos = home.find( ' ' );
        if( pos != wxString::npos ) {
            home = home.substr( 0, pos - 1 );
        }
        if( home.compare( "F1" ) == 0 ) {
            recFamily fam( 0 );
            fam.FSetID( 1 );
            fam.Save();
        }
        m_user_setting.FSetValue( home );
        m_user_setting.Save();
    }
    return true;
}

void rgDlgSetupDatabase::OnContactsButton( wxCommandEvent& event )
{
    wxString name = m_textCtrlUserName->GetValue();
    recResearcher res( 1 );
    res.FSetName( name );
    res.Save();
    if( rgEditResearcher( this, 1 ) ) {
        recResearcher res( 1 );
        m_textCtrlUserName->SetValue( res.FGetName() );
    }
}

// End of src/rg/rgSetupDatabase.cpp file
