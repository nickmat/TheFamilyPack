/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Name:        src/rg/rgEdMedia.cpp
* Project:     The Family Pack: Genealogy data storage and display program.
* Purpose:     Edit database Media dialog.
* Author:      Nick Matthews
* Website:     http://thefamilypack.org
* Created:     2nd October 2018
* Copyright:   Copyright (c) 2018..2022, Nick Matthews.
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

#include <rec/recAssociate.h>

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

bool rgEditMediaData( wxWindow* wind, idt mdID, const wxString& dbname )
{
    wxASSERT( mdID != 0 && !dbname.empty() );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditMediaData* dialog = new rgDlgEditMediaData( wind, mdID, dbname );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    }
    else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

//============================================================================
//                 rgDlgEditMedia dialog
//============================================================================

rgDlgEditMedia::rgDlgEditMedia( wxWindow* parent, idt medID )
    : m_media( medID ), m_md( m_media.FGetDataID(), m_media.FGetAssID() ),
    fbRgEditMedia( parent )
{
}

bool rgDlgEditMedia::TransferDataToWindow()
{
    wxASSERT( m_md.FGetID() != 0 );

    idt refID = m_media.FGetRefID();
    m_staticMediaID->SetLabel( m_media.GetIdStr() );
    m_textCtrlTitle->SetValue( m_media.FGetTitle() );
    m_textCtrlNote->SetValue( m_media.FGetNote() );
    m_imagePanel->SetScrollMode( false );
    m_imagePanel->SetImage( m_md.FGetData() );
    m_staticText_mdID->SetLabel(
        recAssociate::GetIdStr( m_media.FGetAssID() ) + ":" +
        recMediaData::GetIdStr( m_media.FGetDataID() ) );
    m_spinCtrlPrivacy->SetValue( m_media.FGetPrivacy() );
    m_staticTextRefID->SetLabel( recReference::GetIdStr( refID ) );
    m_staticTextRefTitle->SetLabel( recReference::GetTitle( refID ) );
    return true;
}

bool rgDlgEditMedia::TransferDataFromWindow()
{
    m_media.FSetTitle( m_textCtrlTitle->GetValue() );
    m_media.FSetNote( m_textCtrlNote->GetValue() );
    m_media.FSetPrivacy( m_spinCtrlPrivacy->GetValue() );
    m_media.Save();
    return true;
}

void rgDlgEditMedia::OnImageLeftDClick( wxMouseEvent& event )
{
    rgViewMedia( this, m_media.FGetDataID(), m_media.FGetAssID() );
}

void rgDlgEditMedia::OnButtonMediaData( wxCommandEvent& event )
{
    wxString db = recAssociate::GetAttachedName( m_media.FGetAssID(), "Main" );
    rgEditMediaData( this, m_media.FGetID(), db );
}

//============================================================================
//                 rgDlgEditMediaData dialog
//============================================================================

rgDlgEditMediaData::rgDlgEditMediaData( wxWindow* parent, idt mdID, const wxString& dbname )
    : m_md( mdID, dbname ), m_dbname( dbname ),
    fbRgEditMediaData( parent )
{
    m_choiceFileType->Append( m_md.GetMimeList() );
}

bool rgDlgEditMediaData::TransferDataToWindow()
{
    wxASSERT( m_md.FGetID() != 0 );

    m_textCtrlTitle->SetValue( m_md.FGetTitle() );
    m_textCtrlFile->SetValue( m_md.FGetFile() );
    m_choiceFileType->SetSelection( int( m_md.FGetType() ) - 1 );
    m_textCtrlCopyright->SetValue( m_md.FGetCopyright() );
    m_spinPrivacy->SetValue( m_md.FGetPrivacy() );
    m_imagePanel->SetScrollMode( false );
    m_imagePanel->SetImage( m_md.FGetData() );
    m_staticMediaDataID->SetLabel( m_md.GetIdStr() + "," + m_dbname );
    m_textCtrlUid->SetValue( m_md.FGetUid() );
    wxString changed = calStrFromJdn( m_md.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );
    return true;
}

bool rgDlgEditMediaData::TransferDataFromWindow()
{
    m_md.FSetTitle( m_textCtrlTitle->GetValue() );
    m_md.FSetFile( m_textCtrlFile->GetValue() );
    m_md.FSetType( recMediaData::Mime( m_choiceFileType->GetSelection() + 1 ) );
    m_md.FSetCopyright( m_textCtrlCopyright->GetValue() );
    m_md.FSetPrivacy( m_spinPrivacy->GetValue() );
    m_md.Save( m_dbname );
    return true;
}

void rgDlgEditMediaData::OnImageLeftDClick( wxMouseEvent& event )
{
    rgViewMedia( this, m_md.FGetID(), m_dbname );
}


// End of src/rg/rgEdMedia.cpp file
