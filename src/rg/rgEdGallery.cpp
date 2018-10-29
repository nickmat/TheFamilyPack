/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdGallery.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Image Gallery dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2018
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

#include "rgEdGallery.h"

#include "rg/rgDialogs.h"

#include <rec/recGallery.h>
#include <rec/recGalleryMedia.h>


bool rgEditGallery( wxWindow* parent, idt galID  )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;
    rgDlgEditGallery dialog( parent, galID );

    if ( dialog.IsGalIdOk( galID ) && dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog.Destroy();
    return ret;
}
//============================================================================
//                 rgDlgEditGallery dialog
//============================================================================

rgDlgEditGallery::rgDlgEditGallery( wxWindow* parent, idt galID )
    : m_gallery(galID), fbRgEditGallery(parent)
{
    m_listImage->InsertColumn( IC_id, _( "Number" ) );
    m_listImage->InsertColumn( IC_title, _( "Title" ) );
}

bool rgDlgEditGallery::IsGalIdOk( idt galID )
{
    if ( galID == 0 ) {
        m_gallery.Save();
        return true;
    }
    return ( galID == m_gallery.FGetID() );
}

bool rgDlgEditGallery::TransferDataToWindow()
{
    wxASSERT( m_gallery.FGetID() != 0 );

    m_textCtrlTitle->SetValue( m_gallery.FGetTitle() );
    m_textCtrlNote->SetValue( m_gallery.FGetNote() );
    m_staticGalID->SetLabel( m_gallery.GetIdStr() );

    UpdateMediaList();

    m_notebook->SetSelection( PAGE_Note );
    m_textCtrlNote->SetFocus();
    return true;
}

bool rgDlgEditGallery::TransferDataFromWindow()
{
    m_gallery.FSetTitle( m_textCtrlTitle->GetValue() );
    m_gallery.FSetNote( m_textCtrlNote->GetValue() );

    for ( size_t i = 0; i < m_gmms.size(); i++ ) {
        recGalleryMedia& gm = m_gmms[i].GetGalleryMedia();
        if ( gm.FGetMedSeq() != i + 1 ) {
            gm.FSetMedSeq( i + 1 );
            gm.Save();
        }
    }
    return true;
}

void rgDlgEditGallery::UpdateMediaList()
{
    m_gmms = m_gallery.GetGalleryMediaMediaVec();
    long row = 0;
    for ( auto gmm : m_gmms ) {
        m_listImage->InsertItem( row, gmm.GetMedIdStr() );
        m_listImage->SetItem( row, IC_title, gmm.GetTitle() );
        m_listImage->EnsureVisible( row );
        row++;
    }
    m_listImage->SetColumnWidth( IC_title, wxLIST_AUTOSIZE );
}

void rgDlgEditGallery::OnNameAddButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnNameAddButton" );
}

void rgDlgEditGallery::OnNameEditButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnNameEditButton" );
}

void rgDlgEditGallery::OnNameDeleteButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnNameDeleteButton" );
}

void rgDlgEditGallery::OnNameUpButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnNameUpButton" );
}

void rgDlgEditGallery::OnNameDownButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnNameDownButton" );
}

void rgDlgEditGallery::OnViewImage( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnViewImage" );
}

// End of src/rg/rgEdGallery.cpp
