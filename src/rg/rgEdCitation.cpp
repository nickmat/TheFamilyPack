/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdCitation.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit Citation dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th November 2021
 * Copyright:   Copyright (c) 2021..2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recCitation.h>

#include <rg/rgDialogs.h>
#include "rgEdCitation.h"


bool rgEditCitation( wxWindow* wind, idt citID, const wxString& title )
{
    return rgEdit<rgDlgEditCitation>( wind, citID, title );
}

idt rgCreateCitation( wxWindow* wind, idt refID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recCitation cit( 0 );
    cit.FSetRefID( refID );
    cit.FSetRefSeq( cit.GetNextRefSequence( refID ) );
    cit.Save();
    idt citID = cit.FGetID();

    if( rgEditCitation( wind, citID, _( "Create Citation" ) ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return citID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//--------------------------[ rgDlgEditCitation ]-----------------------------
//============================================================================

rgDlgEditCitation::rgDlgEditCitation( wxWindow* parent, idt citID )
    : m_citation( citID ), fbRgEditCitation( parent )
{
    m_archive.ReadID( m_citation.FGetRepID() );
    m_parts = m_citation.GetPartList();

    m_listParts->InsertColumn( PC_citID, _( "ID" ), wxLIST_FORMAT_LEFT, 60 );
    m_listParts->InsertColumn( PC_value, _( "Value" ) );
    m_listParts->InsertColumn( PC_type, _( "Type" ) );
    m_listParts->InsertColumn( PC_comment, _( "Comment" ) );
}

bool rgDlgEditCitation::TransferDataToWindow()
{
    UpdateCitation();
    m_textCtrlComment->SetValue( m_citation.FGetComment() );
    UpdateArchive();
    UpdatePartList( 0 );
    wxString idStr = recReference::GetIdStr( m_citation.FGetRefID() )
        + ":" + m_citation.GetIdStr();
    m_staticRefCiID->SetLabel( idStr );
    return true;
}

bool rgDlgEditCitation::TransferDataFromWindow()
{
    m_citation.FSetComment( m_textCtrlComment->GetValue() );
    m_citation.Save();
    return true;
}

void rgDlgEditCitation::UpdateCitation()
{
    m_textCtrlCitation->SetValue( m_citation.GetCitationStr() );
}

void rgDlgEditCitation::UpdateArchive()
{
    wxString arcStr = m_archive.GetIdStr( m_citation.FGetRepID() )
        + ": " + m_archive.FGetName();
    m_textCtrlArchive->SetValue( arcStr );
}

void rgDlgEditCitation::UpdatePartList( idt cpID )
{
    m_parts = m_citation.GetPartList();
    m_listParts->DeleteAllItems();
    long row = -1;
    for( size_t i = 0; i < m_parts.size(); i++ ) {
        m_listParts->InsertItem( i, m_parts[i].GetIdStr() );
        m_listParts->SetItem( i, PC_value, m_parts[i].FGetValue() );
        m_listParts->SetItem( i, PC_type, recCitationPartType::GetStr( m_parts[i].FGetTypeID() ) );
        m_listParts->SetItem( i, PC_comment, m_parts[i].FGetComment() );
        if( cpID == m_parts[i].FGetID() ) {
            m_listParts->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_parts[i].FGetCitSeq() != i + 1 ) {
            m_parts[i].FSetCitSeq( i + 1 );
            m_parts[i].Save();
        }
    }
    if( !m_parts.empty() ) {
        m_listParts->SetColumnWidth( PC_value, wxLIST_AUTOSIZE );
    }
    if( row >= 0 ) {
        m_listParts->EnsureVisible( row );
    }
    PartsButtonsEnable( row );
    UpdateCitation();
}


void rgDlgEditCitation::PartsButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonEdit->Disable();
        m_buttonDelete->Disable();
        m_buttonUp->Disable();
        m_buttonDown->Disable();
        return;
    }
    m_buttonEdit->Enable();
    m_buttonDelete->Enable();
    if( row == 0 ) {
        m_buttonUp->Disable();
    }
    else {
        m_buttonUp->Enable();
    }
    if( row == m_listParts->GetItemCount() - 1 ) {
        m_buttonDown->Disable();
    }
    else {
        m_buttonDown->Enable();
    }
}

void rgDlgEditCitation::OnButtonSelectExtends( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonSelectExtends" );
}

void rgDlgEditCitation::OnButtonRepository( wxCommandEvent& event )
{
    idt orig_arcID = m_archive.FGetID();
    if( orig_arcID <= 0 ) {
        OnSelectRepository( event );
        return;
    }
    wxSize s = m_buttontRepository->GetSize();
    m_buttontRepository->PopupMenu( m_menuRepository, 0, s.y );
}

void rgDlgEditCitation::OnSelectRepository( wxCommandEvent& event )
{
    idt orig_arcID = m_archive.FGetID();
    idt arcID = rgSelectRepository( this, rgSELSTYLE_Create );
    if( arcID != orig_arcID ) {
        m_archive.ReadID( arcID );
        m_citation.FSetRepID( arcID );
        UpdateArchive();
        UpdateCitation();
    }
}

void rgDlgEditCitation::OnEditRepository( wxCommandEvent& event )
{
    idt repID = m_archive.FGetID();
    rgEditRepository( this, repID );
    m_archive.ReadID( repID );
    UpdateArchive();
    UpdateCitation();
}

void rgDlgEditCitation::OnPartDeselect( wxListEvent& event )
{
    PartsButtonsEnable( -1 );
}

void rgDlgEditCitation::OnPartSelect( wxListEvent& event )
{
    long row = m_listParts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    PartsButtonsEnable( row );
}

void rgDlgEditCitation::OnButtonAdd( wxCommandEvent& event )
{
    idt cipID = rgCreateCitationPart( this, m_citation.FGetID() );
    if( cipID ) {
        UpdatePartList( cipID );
    }
}

void rgDlgEditCitation::OnButtonEdit( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonEdit" );
}

void rgDlgEditCitation::OnButtonDelete( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonDelete" );
}

void rgDlgEditCitation::OnButtonUp( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonUp" );
}

void rgDlgEditCitation::OnButtonDown( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonDown" );
}

// End of src/rg/rgEdCitation.cpp file
