/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdArchive.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Archive dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th November 2021
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

//#include <rec/recSystem.h>
#include <rec/recCitation.h>

#include <rg/rgDialogs.h>
#include "rgEdCitation.h"
#include "rgCommon.h"


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

bool rgEditArchive( wxWindow* wind, idt arcID, const wxString& title )
{
    wxASSERT( arcID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditArchive dialog( wind, arcID );
    if( !title.empty() ) {
        dialog.SetTitle( title );
    }

    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

idt rgCreateArchive( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContactList list(0);
    list.Save();

    recRepository arc(0);
    arc.FSetConListID( list.FGetID() );
    arc.Save();
    idt arcID = arc.FGetID();

    if( rgEditArchive( wind, arcID, _( "Create Archive" ) ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return arcID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

idt rgSelectArchive( wxWindow* wind, unsigned flag, unsigned* retbutton, const wxString& title )
{
    idt arcID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    rgDlgSelectArchive dialog( wind, flag, title );

    bool cont = true;
    while( cont ) {
        recRepositoryVec vec = recRepository::GetFullList();
        wxArrayString table;
        for( auto arc : vec ) {
            table.push_back( arc.GetIdStr() );
            table.push_back( arc.FGetName() );
            table.push_back( arc.FGetNote() );
        }
        dialog.SetTable( table );
        if( vec.size() == 1 ) {
            dialog.SetSelectedRow( 0 );
        }
        if( dialog.ShowModal() == wxID_OK ) {
            if( dialog.GetCreatePressed() ) {
                arcID = rgCreateArchive( wind );
                if( arcID ) {
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
                arcID = 0;
                break;
            }
            size_t item = (size_t)dialog.GetSelectedRow();
            arcID = vec[item].FGetID();
        }
        cont = false;
    }

    return arcID;
}

bool rgEditCitationPart( wxWindow* wind, idt cipID, const wxString& title )
{
    return rgEdit<rgDlgEditCitationPart>( wind, cipID, title );
}

idt rgCreateCitationPart( wxWindow* wind, idt citID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recCitationPart part( 0 );
    part.FSetCitID( citID );
    part.FSetCitSeq( part.GetNextCitationSeq( citID ) );
    part.Save();
    idt partID = part.FGetID();

    if( rgEditCitationPart( wind, partID, _( "Create Citation Part" ) ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return partID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

bool rgEditCitationPartType( wxWindow* wind, idt cipID, const wxString& title )
{
    return rgEdit<rgDlgEditCitationPart>( wind, cipID, title );
}

idt rgCreateCitationPartType( wxWindow* wind )
{
    return rgCreate<recCitationPartType, rgDlgEditCitationPartType>(
        wind, _( "Create Citation Part Type" )
    );
}
//============================================================================
//--------------------------[ rgDlgEditCitation ]-----------------------------
//============================================================================

rgDlgEditCitation::rgDlgEditCitation( wxWindow* parent, idt citID )
    : m_citation( citID ), fbRgEditCitation( parent )
{
    m_archive.ReadID( m_citation.FGetRefID() );
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


void rgDlgEditCitation::OnButtonSelectAchive( wxCommandEvent& event )
{
    idt orig_arcID = m_archive.FGetID();
    idt arcID = rgSelectArchive( this, rgSELSTYLE_Create );
    if( arcID != orig_arcID ) {
        m_archive.ReadID( arcID );
        m_citation.FSetRepID( arcID );
        UpdateArchive();
        UpdateCitation();
    }
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

//============================================================================
//---------------------------[ rgDlgEditArchive ]-----------------------------
//============================================================================

rgDlgEditArchive::rgDlgEditArchive( wxWindow* parent, idt arcID )
    : m_archive(arcID), fbRgEditArchive( parent )
{
    m_list.ReadID( m_archive.FGetConListID() );
    m_contacts = m_list.GetContacts();

    wxListItem itemCol;
    itemCol.SetText( _("ID") );
    m_listContacts->InsertColumn( COL_ConID, itemCol );
    itemCol.SetText( _("Type") );
    m_listContacts->InsertColumn( COL_Type, itemCol );
    itemCol.SetText( _("Value") );
    m_listContacts->InsertColumn( COL_Value, itemCol );
}

bool rgDlgEditArchive::TransferDataToWindow()
{
    wxASSERT( m_archive.FGetID() != 0 );

    m_textCtrlName->SetValue( m_archive.FGetName() );
    m_textCtrlNote->SetValue( m_archive.FGetNote() );

    for( size_t i = 0 ; i < m_contacts.size() ; i++ ) {
        m_listContacts->InsertItem( i, m_contacts[i].GetIdStr() );
        m_listContacts->SetItem( i, COL_Type, m_contacts[i].GetTypeStr() );
        m_listContacts->SetItem( i, COL_Value, m_contacts[i].FGetValue() );
    }

    m_staticArcID->SetLabel( m_archive.GetIdStr() );

    return true;
}

bool rgDlgEditArchive::TransferDataFromWindow()
{
    m_archive.FSetName( m_textCtrlName->GetValue() );
    m_archive.FSetNote( m_textCtrlNote->GetValue() );

    m_archive.Save();
    return true;
}

void rgDlgEditArchive::OnButtonAdd( wxCommandEvent& event )
{
    idt conID = rgCreateContact( this, m_list.FGetID() );
    if( conID ) {
        recContact con(conID);
        int row = m_contacts.size();
        m_listContacts->InsertItem( row, con.GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, con.GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, con.FGetValue() );
        m_contacts.push_back( con );
    }
}

void rgDlgEditArchive::OnButtonEdit( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Contact") );
        return;
    }
    if( rgEditContact( this, m_contacts[row].FGetID() ) ) {
        m_contacts[row].Read();
        m_listContacts->SetItem( row, COL_ConID, m_contacts[row].GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, m_contacts[row].GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, m_contacts[row].FGetValue() );
    }
}

void rgDlgEditArchive::OnButtonDelete( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listContacts->DeleteItem( row );
        m_contacts[row].Delete();
        m_contacts.erase( m_contacts.begin() + row );
    } else {
        wxMessageBox( _("No row selected"), _("Delete Contact") );
    }
}


//============================================================================
//--------------------------[ rgDlgSelectArchive ]----------------------------
//============================================================================

wxString rgDlgSelectArchive::sm_colHeaders[COL_MAX] = {
    _( "ID" ), _( "Name" ), _( "Comment" )
};

//============================================================================
//------------------------[ rgDlgEditCitationPart ]---------------------------
//============================================================================

rgDlgEditCitationPart::rgDlgEditCitationPart( wxWindow* parent, idt cipID )
    : m_part( cipID ), fbRgEditCitationPart( parent )
{
}

bool rgDlgEditCitationPart::TransferDataToWindow()
{
    UpdatePartType( m_part.FGetTypeID() );
    m_textCtrlValue->SetValue( m_part.FGetValue() );
    m_textCtrlComment->SetValue( m_part.FGetComment() );
    m_staticCipID->SetLabel(
        recCitation::GetIdStr( m_part.FGetCitID() ) + ":" + m_part.GetIdStr()
    );
    return true;
}

bool rgDlgEditCitationPart::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type <= 0 ) {
        wxMessageBox( _( "Please select a Citation Part Type" ), _( "Citation Part Type Required" ) );
        return false;
    }
    m_part.FSetTypeID( m_types[type-1].FGetID() );
    m_part.FSetValue( m_textCtrlValue->GetValue() );
    m_part.FSetComment( m_textCtrlComment->GetValue() );
    m_part.Save();
    return true;
}

void rgDlgEditCitationPart::UpdatePartType( idt ciptID )
{
    m_choiceType->Clear();
    m_choiceType->Append( _( "<Select Type>" ) );
    m_choiceType->SetSelection( 0 );
    m_types = recCitationPartType::GetList();
    for( size_t i = 0; i < m_types.size(); i++ ) {
        m_choiceType->Append( m_types[i].FGetName() );
        if( ciptID == m_types[i].FGetID() ) {
            m_choiceType->SetSelection( (int)i + 1 );
        }
    }
}

void rgDlgEditCitationPart::OnButtonTypeAdd( wxCommandEvent& event )
{
    idt ciptID = rgCreateCitationPartType( this );
    if( ciptID ) {
        m_part.FSetTypeID( ciptID );
        UpdatePartType( ciptID );
    }
}


//============================================================================
//----------------------[ rgDlgEditCitationPartType ]-------------------------
//============================================================================

rgDlgEditCitationPartType::rgDlgEditCitationPartType( wxWindow* parent, idt ciptID )
    : m_type(ciptID), fbRgEditCitationPartType(parent)
{
}

bool rgDlgEditCitationPartType::TransferDataToWindow()
{
    m_staticCiPT_ID->SetLabel( m_type.GetIdStr() );
    m_textCtrlName->SetValue( m_type.FGetName() );
    m_textCtrlComment->SetValue( m_type.FGetComment() );
    return true;
}

bool rgDlgEditCitationPartType::TransferDataFromWindow()
{
    m_type.FSetName( m_textCtrlName->GetValue() );
    m_type.FSetComment( m_textCtrlComment->GetValue() );
    m_type.Save();
    return true;
}

// End of src/rg/rgEdCitation.cpp file
