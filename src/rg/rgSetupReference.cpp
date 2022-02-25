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

#include "rgRefTemplate.h"

#include <rg/rgDialogs.h>

#include <rec/recAssociate.h>
#include <rec/recMedia.h>
#include <rec/recMediaData.h>


static bool GetSetupData( wxWindow* wind, rgRefData& data, idt assID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    rgDlgSetupReference dialog( wind, data, assID );

    if( dialog.ShowModal() != wxID_OK ) {
        recDb::Rollback( savepoint );
        return false;
    }

    if( !rgEnterTemplateData( wind, dialog.GetTemplateFile(), data ) ) {
        recDb::Rollback( savepoint );
        return false;
    }

    recDb::ReleaseSavepoint( savepoint );
    return true;
}



idt rgGetRefSetupData( wxWindow* parent, idt assID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recReference ref( 0 );
    ref.Save();
    idt refID = ref.FGetID();
    rgRefData data;
    data.m_ref_id = refID;

    if( GetSetupData( parent, data, assID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    }
    else {
        recDb::Rollback( savepoint );
        return 0;
    }
    return refID;
}

//============================================================================
//-------------------------[ rgDlgSetupReference ]-----------------------------
//============================================================================


rgDlgSetupReference::rgDlgSetupReference( wxWindow* parent, rgRefData& data, idt assID )
    : m_reference(data.m_ref_id ), m_data(data),
    m_dbnames( recDb::GetDatabaseList() ), // m_assID( assID ), 
    fbRgSetupReferenceDialog( parent )
{
    m_listMedia->InsertColumn( MED_COL_Number, _( "Number" ) );
    m_listMedia->InsertColumn( MED_COL_Title, _( "Title" ) );
    m_choiceMediaDb->Append( m_dbnames );
    wxString dbname = recAssociate::GetAttachedName( assID, "Main");
    int index = 0;
    for( size_t i = 0; i < m_dbnames.size(); i++ ) {
        if( dbname.compare( m_dbnames[i] ) == 0 ) {
            index = i;
            break;
        }
    }
    m_choiceMediaDb->SetSelection( index );
}

bool rgDlgSetupReference::TransferDataToWindow()
{
    wxASSERT( m_reference.FGetID() != 0 );
    m_staticRefID->SetLabel( m_reference.GetIdStr() );
    m_textCtrlRefTitle->SetValue( m_reference.FGetTitle() );
    UpdateMedias( 0 );
    return true;
}

bool rgDlgSetupReference::TransferDataFromWindow()
{
    m_reference.FSetTitle( m_textCtrlRefTitle->GetValue() );
    m_reference.Save();
    m_template = m_textCtrlTemplate->GetValue();
    return true;
}

void rgDlgSetupReference::UpdateMedias( idt medID )
{
    m_mediaIDs = recReference::GetMediaList( m_reference.FGetID() );
    long row = 0, sel = -1;
    for( idt mediaID : m_mediaIDs ) {
        m_listMedia->InsertItem( row, recMedia::GetIdStr( mediaID ) );
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
        m_buttonMediaUp->Disable();
        m_buttonMediaDn->Disable();
        m_buttonMediaView->Disable();
        return;
    }
    m_buttonMediaEdit->Enable();
    m_buttonMediaDel->Enable();
    if( row == 0 ) {
        m_buttonMediaUp->Disable();
    }
    else {
        m_buttonMediaUp->Enable();
    }
    if( row == m_listMedia->GetItemCount() - 1 ) {
        m_buttonMediaDn->Disable();
    }
    else {
        m_buttonMediaDn->Enable();
    }
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
    if( dialog.ShowModal() != wxID_OK ) {
        return;
    }
    wxString path = dialog.GetPath();
    int index = m_choiceMediaDb->GetSelection();
    wxString dbname = m_dbnames[index];
    idt assID = recDb::GetAssociateDbAssID( "Main", dbname );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recMediaData md( 0 );
    md.ImportData( path );
    md.Save( dbname );
    if( !rgEditMediaData( this, md.FGetID(), dbname ) ) {
        recDb::Rollback( savepoint );
        return;
    }
    idt medID = recMedia::Create( md.FGetID(), assID, m_reference.FGetID() );
    if( !rgEditMedia( this, medID ) ) {
        recDb::Rollback( savepoint );
        return;
    }
    recDb::ReleaseSavepoint( savepoint );
    UpdateMedias( 0 );
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

void rgDlgSetupReference::OnMediaUpButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaUpButton" );
}

void rgDlgSetupReference::OnMediaDownButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaDeleteButton" );
}

void rgDlgSetupReference::OnMediaViewButton( wxCommandEvent& event )
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

void rgDlgSetupReference::OnNext( wxCommandEvent& event )
{
    EndModal( wxID_OK );
}

// End of src/rg/rgSetupReference.cpp file
