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


bool rgEditGallery( wxWindow* parent, idt galID, const wxString& title )
{
    return rgEdit<rgDlgEditGallery>( parent, galID, title );
}

idt rgCreateGallery( wxWindow* wind )
{
    recGallery gal( 0 );
    gal.FSetUid( recCreateUid() );
    gal.FSetChanged( calGetTodayJdn() );
    return rgCreate<recGallery, rgDlgEditGallery>(
        wind, gal, _( "Create Gallery" )
    );
}

idt rgSelectGallery( wxWindow* wind, unsigned flag, unsigned* retbutton, const wxString& title )
{
    idt galID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    rgDlgSelectGallery dialog( wind, flag, title );

    bool cont = true;
    while( cont ) {
        recGalleryVec vec = recGallery::GetGalleries();
        wxArrayString table;
        for( auto gal : vec ) {
            table.push_back( gal.GetIdStr() );
            table.push_back( gal.FGetTitle() );
        }
        dialog.SetTable( table );
        if( vec.size() == 1 ) {
            dialog.SetSelectedRow( 0 );
        }
        if( dialog.ShowModal() == wxID_OK ) {
            if( dialog.GetCreatePressed() ) {
                galID = rgCreateGallery( wind );
                if( galID ) {
                    if( retbutton ) *retbutton = rgSELSTYLE_Create;
                    break;
                }
                else {
                    dialog.SetCreatePressed( false );
                    continue;
                }
            }
            if( dialog.GetUnknownPressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                galID = 0;
                break;
            }
            size_t item = (size_t) dialog.GetSelectedRow();
            galID = vec[item].FGetID();
        }
        cont = false;
    }

    return galID;
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

bool rgDlgEditGallery::TransferDataToWindow()
{
    wxASSERT( m_gallery.FGetID() != 0 );

    m_textCtrlTitle->SetValue( m_gallery.FGetTitle() );
    m_textCtrlUid->SetValue( m_gallery.FGetUid() );
    wxString changed = calStrFromJdn( m_gallery.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );
    m_textCtrlNote->SetValue( m_gallery.FGetNote() );
    m_staticGalID->SetLabel( m_gallery.GetIdStr() );

    UpdateMediaList();
    return true;
}

bool rgDlgEditGallery::TransferDataFromWindow()
{
    m_gallery.FSetTitle( m_textCtrlTitle->GetValue() );
    m_gallery.FSetNote( m_textCtrlNote->GetValue() );
    m_gallery.FSetChanged( calGetTodayJdn() );

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

//============================================================================
//--------------------------[ rgDlgSelectGallery ]----------------------------
//============================================================================

wxString rgDlgSelectGallery::sm_colHeaders[COL_MAX] = {
    _( "ID" ), _( "Title" )
};


// End of src/rg/rgEdGallery.cpp
