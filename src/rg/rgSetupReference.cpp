/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSetupReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Setup Creation of database Reference entity.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     23rd August 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#include "rgSetupReference.h"

#include <rg/rgDialogs.h>

#include <rec/recMedia.h>

bool rgGetRefSetupData( wxWindow* parent, idt refID, rgRefData& data )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;
    rgDlgSetupReference dialog( parent, refID );

    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    }
    else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

//============================================================================
//-------------------------[ rgDlgSetupReference ]-----------------------------
//============================================================================


rgDlgSetupReference::rgDlgSetupReference( wxWindow* parent, idt refID )
    : m_reference( refID ), fbRgSetupReferenceDialog( parent )
{
    m_listMedia->InsertColumn( MED_COL_Number, _( "Number" ) );
    m_listMedia->InsertColumn( MED_COL_Title, _( "Title" ) );
}

bool rgDlgSetupReference::TransferDataToWindow()
{
    wxASSERT( m_reference.FGetID() != 0 );
    m_staticRefID->SetLabel( m_reference.GetIdStr() );
    m_textCtrlRefTitle->SetValue( m_reference.FGetTitle() );
    UpdateMedias( 0 );
    return false;
}

bool rgDlgSetupReference::TransferDataFromWindow()
{
    return false;
}

void rgDlgSetupReference::UpdateMedias( idt medID )
{
    m_mediaIDs = recReference::GetMediaList( m_reference.FGetID() );
    long row = 0, sel = -1;
    for( idt mediaID : m_mediaIDs ) {
        m_listMedia->InsertItem( row, mediaID );
        m_listMedia->SetItem( row, MED_COL_Title, recMedia::GetTitle( mediaID ) );
        if( mediaID == medID ) {
            m_listMedia->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            sel = row;
        }
        row++;
    }
    if( !m_mediaIDs.empty() ) {
        m_listMedia->SetColumnWidth( MED_COL_Title, wxLIST_AUTOSIZE );
    }
    if( sel >= 0 ) {
        m_listMedia->EnsureVisible( sel );
    }
    MediaButtonsEnable( sel );
}

void rgDlgSetupReference::MediaButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonMediaEdit->Disable();
        m_buttonMediaDel->Disable();
//        m_buttonUp->Disable();
//        m_buttonDn->Disable();
        m_buttonMediaView->Disable();
        return;
    }
    m_buttonMediaEdit->Enable();
    m_buttonMediaDel->Enable();
    // TODO: Add a ref order field to the Media table.
#if 0
    if( row == 0 ) {
        m_buttonUp->Disable();
    }
    else {
        m_buttonUp->Enable();
    }
    if( row == m_listChildren->GetItemCount() - 1 ) {
        m_buttonDn->Disable();
    }
    else {
        m_buttonDn->Enable();
    }
#endif
    m_buttonMediaView->Enable();
}

void rgDlgSetupReference::OnMediaDeselect( wxListEvent& event )
{
    MediaButtonsEnable( -1 );
}

void rgDlgSetupReference::OnMediaSelect( wxListEvent& event )
{
    long row = m_listMedia->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    MediaButtonsEnable( row );
}

void rgDlgSetupReference::OnMediaAddButton( wxCommandEvent& event )
{
    wxSize s = m_buttonMediaAdd->GetSize();
    m_buttonMediaAdd->PopupMenu( m_popupAddMedia, 0, s.y );
}

void rgDlgSetupReference::OnAddNewMedia( wxCommandEvent& event )
{
    wxString caption = _( "Select Media file" );
    wxString wildcard = "Image (*.jpg)|*.jpg";
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        unsigned style = rgSELSTYLE_Create | rgSELSTYLE_Unknown;
        unsigned button = rgSELSTYLE_None;
        idt assID = rgSelectAssociate( this, style, &button );
        if( assID != 0 || button == rgSELSTYLE_Unknown ) {

        }
//        wxMessageBox( _( "Path: " + path ), "OnAddNewMedia" );
    }
}

void rgDlgSetupReference::OnAddExistingMedia( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnAddExistingMedia" );
}

void rgDlgSetupReference::OnMediaEditButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaEditButton" );
}

void rgDlgSetupReference::OnMediaDeleteButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaDeleteButton" );
}

void rgDlgSetupReference::OnMediaView( wxCommandEvent& event )
{
    long row = m_listMedia->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _( "Row not selected" ), _( "View Media" ) );
        return;
    }
    rgViewMedia( this, m_mediaIDs[row] );
}

void rgDlgSetupReference::OnTemplateBrowse( wxCommandEvent& event )
{
    // For now templates are files, but we want them to become
    // common data.
    wxString caption = _( "Select template file" );
    wxString wildcard = "xhtml (*.htm)|*.htm";
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        m_textCtrlTemplate->SetValue( path );
    }
}

// End of src/rg/rgSetupReference.cpp file
