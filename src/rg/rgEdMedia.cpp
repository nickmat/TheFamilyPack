/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Name:        src/rg/rgEdMedia.cpp
* Project:     The Family Pack: Genealogy data storage and display program.
* Purpose:     Edit database Media dialog.
* Author:      Nick Matthews
* Website:     http://thefamilypack.org
* Created:     2nd October 2018
* Copyright:   Copyright (c) 2018, Nick Matthews.
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
#include "rgEdMedia.h"


bool rgEditMedia( wxWindow* wind, idt medID )
{
    wxASSERT( medID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditMedia* dialog = new rgDlgEditMedia( wind, medID );

    if ( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

rgDlgEditMedia::rgDlgEditMedia( wxWindow* parent, idt medID )
    : m_media( medID ), fbRgEditMedia( parent )
{
    m_md.ReadID( m_media.FGetDataID() );
}

bool rgDlgEditMedia::TransferDataToWindow()
{
    wxASSERT( m_md.FGetID() != 0 );

    m_staticMediaID->SetLabel( m_media.GetIdStr() );
    m_textCtrlTitle->SetValue( m_media.FGetTitle() );
    m_imagePanel->SetScrollMode( true );
    m_imagePanel->SetImage( m_md.FGetData() );
    return true;
}

bool rgDlgEditMedia::TransferDataFromWindow()
{
    m_media.FSetTitle( m_textCtrlTitle->GetValue() );
    m_media.Save();
    return true;
}

// End of src/rg/rgEdMedia.cpp file
