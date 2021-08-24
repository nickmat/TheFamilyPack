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
}

void rgDlgSetupReference::OnMediaDeselect( wxListEvent& event )
{
}

void rgDlgSetupReference::OnMediaSelect( wxListEvent& event )
{
}

void rgDlgSetupReference::OnMediaAddButton( wxCommandEvent& event )
{
    wxSize s = m_buttonMediaAdd->GetSize();
    m_buttonMediaAdd->PopupMenu( m_popupAddMedia, 0, s.y );
}


void rgDlgSetupReference::OnAddNewMedia( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnAddNewMedia" );
}

void rgDlgSetupReference::OnAddExistingMedia( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnAddExistingMedia" );
}

void rgDlgSetupReference::OnMediaEditButton( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnMediaDeleteButton( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnMediaView( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnTemplateBrowse( wxCommandEvent& event )
{
    // For now templates are files, but we want them to become
    // common data.
    bool ret = false;
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
