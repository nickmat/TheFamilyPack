/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdGallery.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Image Gallery dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2018
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
    m_gallery.Save();
    return true;
}

void rgDlgEditGallery::UpdateMediaList( idt medID )
{
    m_gmms = m_gallery.GetGalleryMediaMediaVec();
    m_listImage->DeleteAllItems();
    long row = 0, sel = -1;
    for ( auto gmm : m_gmms ) {
        m_listImage->InsertItem( row, gmm.GetMedIdStr() );
        m_listImage->SetItem( row, IC_title, gmm.GetTitle() );
        if ( medID == gmm.GetMedID() ) {
            m_listImage->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            sel = row;
        }
        row++;
    }
    if ( !m_gmms.empty() ) {
        m_listImage->SetColumnWidth( IC_title, wxLIST_AUTOSIZE );
    }
    if ( sel >= 0 ) {
        m_listImage->EnsureVisible( sel );
    }
}

void rgDlgEditGallery::OnMediaAddButton( wxCommandEvent& event )
{
    wxSize s = m_buttonImageAdd->GetSize();
    m_buttonImageAdd->PopupMenu( m_popupAddMedia, 0, s.y );
}

void rgDlgEditGallery::OnAddNewMedia( wxCommandEvent & event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnAddNewMedia" );
}

void rgDlgEditGallery::OnAddExistingMedia( wxCommandEvent & event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnAddExistingMedia" );
}

void rgDlgEditGallery::OnMediaEditButton( wxCommandEvent& event )
{
    long row = m_listImage->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "Row not selected" ), _( "Media Up" ) );
        return;
    }
    idt medID = m_gmms[row].GetMedID();
    if ( rgEditMedia( this, medID ) ) {
        UpdateMediaList( medID );
    }
}

void rgDlgEditGallery::OnMediaRemoveButton( wxCommandEvent& event )
{
    long row = m_listImage->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "Row not selected" ), _( "Remove from Gallery" ) );
        return;
    }
    recGalleryMedia& gm = m_gmms[row].GetGalleryMedia();
    recMedia& med = m_gmms[row].GetMedia();
    wxString mess = wxString::Format(
        _( "Remove Media %s: %s\nfrom Gallery %s" ),
        med.GetIdStr(), m_gmms[row].GetTitle(), m_gallery.GetIdStr()
    );
    int ans = wxMessageBox( mess, _( "Remove Media" ), wxYES_NO | wxCANCEL, this );
    if ( ans != wxYES ) {
        return;
    }
    gm.Delete();
    UpdateMediaList();
}

void rgDlgEditGallery::OnMediaUpButton( wxCommandEvent& event )
{
    long row = m_listImage->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "Row not selected" ), _( "Media Up" ) );
        return;
    }
    if ( row == 0 ) {
        return; // Already at top.
    }
    recGalleryMedia& gm = m_gmms[row].GetGalleryMedia();
    recGalleryMedia& gm_prev = m_gmms[row - 1].GetGalleryMedia();
    int seq = gm.FGetMedSeq();
    gm.FSetMedSeq( gm_prev.FGetMedSeq() );
    gm.Save();
    gm_prev.FSetMedSeq( seq );
    gm_prev.Save();
    UpdateMediaList( gm.FGetMedID() );
}

void rgDlgEditGallery::OnMediaDownButton( wxCommandEvent& event )
{
    long row = m_listImage->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "Row not selected" ), _( "Media Down" ) );
        return;
    }
    if ( row == m_listImage->GetItemCount() - 1 ) {
        return; // Already at bottom.
    }
    recGalleryMedia& gm = m_gmms[row].GetGalleryMedia();
    recGalleryMedia& gm_next = m_gmms[row + 1].GetGalleryMedia();
    int seq = gm.FGetMedSeq();
    gm.FSetMedSeq( gm_next.FGetMedSeq() );
    gm.Save();
    gm_next.FSetMedSeq( seq );
    gm_next.Save();
    UpdateMediaList( gm.FGetMedID() );
}

void rgDlgEditGallery::OnViewImage( wxCommandEvent& event )
{
    long row = m_listImage->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "Row not selected" ), _( "View Media" ) );
        return;
    }
    rgViewMedia( this, "Main", m_gmms[row].GetMedID());
}

// End of src/rg/rgEdGallery.cpp
