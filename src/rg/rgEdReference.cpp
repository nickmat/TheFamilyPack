/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     26th February 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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

#include <wx/numdlg.h>

#include "rgEdReference.h"

#include <rg/rgDialogs.h>

#include "rgSelect.h"

#include <rec/recAssociate.h>
#include <rec/recCitation.h>
#include <rec/recDate.h>
#include <rec/recEventa.h>
#include <rec/recMedia.h>
#include <rec/recPersona.h>
#include <rec/recPlace.h>
#include <rec/recResearcher.h>
#include <rec/recUser.h>

bool rgEditReference( wxWindow* parent, idt refID )
{
    wxASSERT( refID != 0 );
    if( ! recReference::Exists( refID ) ) {
        wxString mess = wxString::Format(
            "Reference %s not found.",
            recReference::GetIdStr( refID)
        );
        wxMessageBox( mess, "Edit Reference Error" );
        return false;
    }
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;
    rgDlgEditReference* dialog = new rgDlgEditReference( parent, refID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateReference( wxWindow* parent )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recReference ref(0);
    ref.FSetResID( recGetCurrentResearcher() );
    ref.FSetUid( recCreateUid() );
    ref.FSetChanged( calGetTodayJdn() );
    ref.Save();
    idt refID = ref.FGetID();

    if( rgEditReference( parent, refID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return refID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

idt rgCreateReferenceFromTemplate( wxWindow* parent )
{
    // Ensure media database is attached before we begin.
    unsigned style = rgSELSTYLE_Create | rgSELSTYLE_Unknown;
    unsigned button = rgSELSTYLE_None;
    idt assID = rgSelectAssociate( parent, "Main", style, &button, "Check Media Database is Connected");
    if( assID != 0 || button == rgSELSTYLE_Unknown ) {
        wxString asspath = recAssociate::GetAttachedName( assID, "Main");
        if( asspath.empty() ) {
            return 0;
        }
    }

    idt refID = 0;
    recDb::Begin();
    try {
        refID = rgGetRefSetupData( parent, assID );
        if( refID ) {
            recDb::Commit();
        }
        else {
            refID = 0;
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        refID = 0;
        recDb::ErrorMessage( e );
    }
    return refID;
}

extern bool rgSelectDateFromReference(
    wxWindow* wind, idt* dateID, idt refID, const wxString& title, unsigned style )
{
    wxASSERT( dateID );  // Can't handle NULL pointer
    if( dateID == nullptr ) {
        return false;
    }

    unsigned retButton;
    *dateID = rgSelectDate( wind, style, &retButton, recD_FILTER_Reference, refID );
    if( retButton == rgSELSTYLE_Create ) {
        recReferenceEntity::Create( refID, recReferenceEntity::TYPE_Date, *dateID );
    }
    if( *dateID == 0 ) {
        if( retButton == rgSELSTYLE_Unknown ) {
            return true;
        }
        return false;
    }
    return true;
}

extern bool rgSelectPlaceFromReference(
    wxWindow* wind, idt* placeID, idt refID, const wxString& title, unsigned style )
{
    wxASSERT( placeID );  // Can't handle NULL pointer
    if( placeID == nullptr ) {
        return false;
    }

    unsigned retButton;
    *placeID = rgSelectPlace( wind, style, &retButton, recD_FILTER_Reference, refID );
    if( retButton == rgSELSTYLE_Create ) {
        recReferenceEntity::Create( refID, recReferenceEntity::TYPE_Place, *placeID );
    }
    if( *placeID == 0 ) {
        if( retButton == rgSELSTYLE_Unknown ) {
            return true;
        }
        return false;
    }
    return true;
}

//============================================================================
//-------------------------[ rgDlgEditReference ]-----------------------------
//============================================================================


rgDlgEditReference::rgDlgEditReference( wxWindow* parent, idt refID )
    : m_reference(refID), m_resID(0), fbRgEditReference( parent )
{
    m_listCitation->InsertColumn( CIT_COL_Number, _( "Number" ) );
    m_listCitation->InsertColumn( CIT_COL_Citation, _( "Citation" ) );

    m_listMedia->InsertColumn( MED_COL_Number, _( "Number" ) );
    m_listMedia->InsertColumn( MED_COL_Title, _( "Title" ) );

    m_listPersona->InsertColumn( PER_COL_Number, _( "Number" ) );
    m_listPersona->InsertColumn( PER_COL_Name, _( "Name" ) );
    m_listPersona->InsertColumn( PER_COL_Individuals, _( "Individuals" ) );

    m_listEventa->InsertColumn( EA_COL_Number, _( "Number" ) );
    m_listEventa->InsertColumn( EA_COL_Title, _( "Title" ) );
    m_listEventa->InsertColumn( EA_COL_Event, _( "Events" ) );

    m_listEntities->InsertColumn( ENT_COL_Number, _("ID") );
    m_listEntities->InsertColumn( ENT_COL_Type, _("Type") );
    m_listEntities->InsertColumn( ENT_COL_Value, _("Value") );

}

bool rgDlgEditReference::TransferDataToWindow()
{
    wxASSERT( m_reference.FGetID() != 0 );
    m_staticRefID->SetLabel( m_reference.GetIdStr()  );
    m_textCtrlTitle->SetValue( m_reference.FGetTitle() );
    UpdateHigherRef();
    m_resID = m_reference.FGetResID();
    UpdateResearcher();
    m_textCtrlUserRef->SetValue( m_reference.FGetUserRef() );
    m_textCtrlStatement->SetValue(  m_reference.FGetStatement() );
    m_textCtrlUid->SetValue( m_reference.FGetUid() );
    wxString changed = calStrFromJdn( m_reference.FGetChanged(), CALENDAR_SCH_Gregorian );
    m_textCtrlChanged->SetValue( changed );

    UpdateHtml();
    UpdateEntities();
    return true;
}

bool rgDlgEditReference::TransferDataFromWindow()
{
    m_reference.FSetTitle( m_textCtrlTitle->GetValue() );
    m_reference.FSetUserRef( m_textCtrlUserRef->GetValue() );
    m_reference.FSetStatement( m_textCtrlStatement->GetValue() );
    m_reference.FSetResID( m_resID );
    m_reference.FSetChanged( calGetTodayJdn() );

    m_reference.Save();
    return true;
}

void rgDlgEditReference::UpdateHigherRef()
{
    idt hrefID = m_reference.FGetHigherID();
    wxString title = recReference::GetTitle( hrefID );
    if( !title.empty() ) {
        title = recReference::GetIdStr( hrefID ) + ": " + title;
    }
    m_textCtrlHigherRef->SetValue( title );
}

void rgDlgEditReference::UpdateResearcher()
{
    recResearcher res( m_resID );
    m_textCtrlResearcher->SetValue( res.GetIdStr() + ": " + res.FGetName() );
}

void rgDlgEditReference::UpdateHtml()
{
    wxString htm;

    htm <<
        "<!DOCTYPE html>\n"
        "<html>\n<head>\n"
        "<title>" << m_reference.GetIdStr() << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tab.css'>\n"
        "</head>\n<body>\n"
    ;

    if( m_reference.f_statement.compare( 0, 9, "<!-- HTML" ) == 0 ) {
        htm << m_reference.FGetStatement();
    } else { // treat as text
        htm << "<pre>\n"
            << m_reference.FGetStatement()
            << "</pre>";
    }
    htm << "\n</body></html>";

    m_webview->SetPage( htm, "" );
}

void rgDlgEditReference::UpdateCitations( idt citID )
{
    m_citationIDs = m_reference.GetCitationList();
    m_listCitation->DeleteAllItems();
    int row = -1;
    for( size_t i = 0; i < m_citationIDs.size(); i++ ) {
        m_listCitation->InsertItem( i, recCitation::GetIdStr( m_citationIDs[i] ) );
        m_listCitation->SetItem( i, CIT_COL_Citation, recCitation::GetCitationStr( m_citationIDs[i] ) );
        if( citID == m_citationIDs[i] ) {
            m_listCitation->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    m_listCitation->SetColumnWidth( CIT_COL_Citation, -1 );
    if( row >= 0 ) {
        m_listCitation->EnsureVisible( row );
    }
    CitationButtonsEnable( row );
}

void rgDlgEditReference::UpdateMedias( idt medID )
{
    m_mediaIDs = m_reference.GetMediaList();
    m_listMedia->DeleteAllItems();
    int row = -1;
    for ( size_t i = 0; i < m_mediaIDs.size(); i++ ) {
        m_listMedia->InsertItem( i, recMedia::GetIdStr( m_mediaIDs[i] ) );
        m_listMedia->SetItem( i, MED_COL_Title, recMedia::GetTitle( m_mediaIDs[i] ) );
        if ( medID == m_mediaIDs[i] ) {
            m_listMedia->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    m_listMedia->SetColumnWidth( MED_COL_Title, -1 );
    if ( row >= 0 ) {
        m_listMedia->EnsureVisible( row );
    }
    MediaButtonsEnable( row );
}

void rgDlgEditReference::UpdatePersonas( idt perID )
{
    m_personaIDs = m_reference.GetPersonaList();
    m_listPersona->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_personaIDs.size() ; i++ ) {
        m_listPersona->InsertItem( i, recPersona::GetIdStr( m_personaIDs[i] ) );
        m_listPersona->SetItem( i, PER_COL_Name, recPersona::GetNameStr( m_personaIDs[i] ) );
        m_listPersona->SetItem( i, PER_COL_Individuals, recPersona::GetIndividualIdStr( m_personaIDs[i] ) );
        if( perID == m_personaIDs[i] ) {
            m_listPersona->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    m_listPersona->SetColumnWidth( PER_COL_Name, -1 );
    if( row >= 0 ) {
        m_listPersona->EnsureVisible( row );
    }
    PersonaButtonsEnable( row );
}

void rgDlgEditReference::UpdateEventas( idt eaID )
{
    m_eventaIDs = m_reference.GetEventaList();
    m_listEventa->DeleteAllItems();
    int row = -1;
    for ( size_t i = 0; i < m_eventaIDs.size(); i++ ) {
        m_listEventa->InsertItem( i, recEventa::GetIdStr( m_eventaIDs[i] ) );
        m_listEventa->SetItem( i, EA_COL_Title, recEventa::GetTitle( m_eventaIDs[i] ) );
        m_listEventa->SetItem( i, EA_COL_Event, recEventa::GetLinkedEventIDsStr( m_eventaIDs[i] ) );
        if ( eaID == m_eventaIDs[i] ) {
            m_listEventa->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    m_listEventa->SetColumnWidth( EA_COL_Title, -1 );
    if ( row >= 0 ) {
        m_listEventa->EnsureVisible( row );
    }
    EventaButtonsEnable( row );
}

void rgDlgEditReference::UpdateEntities( idt reID )
{
    m_entities = m_reference.ReadReferenceEntitys();
    m_listEntities->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_entities.size() ; i++ )
    {
        InsertEntityListItem( i );
        if( reID == m_entities[i].FGetID() ) {
            m_listEntities->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_entities[i].FGetSequence() != i+1 ) {
            m_entities[i].FSetSequence( i+1 );
            m_entities[i].Save();
        }
    }
    m_listEntities->SetColumnWidth( ENT_COL_Value, -1 );
    if( row >= 0 ) {
        m_listEntities->EnsureVisible( row );
    }
    EntityButtonsEnable( row );
}

wxString rgDlgEditReference::GetSelectedText() const
{
    switch( TPage( m_notebookTop->GetSelection() ) )
    {
    case TPage::source:
        return m_textCtrlStatement->GetStringSelection();
    case TPage::view:
        return m_webview->GetSelectedText();
    default:
        wxASSERT( false );
    }
    return wxString();
}

void rgDlgEditReference::OnButtonHigherRef( wxCommandEvent& event )
{
    long num = wxGetNumberFromUser(
        _( "Enter Higher Reference ID number" ),
        _( "Reference ID:" ),
        _( "Select Reference" ),
        0L, LONG_MIN, LONG_MAX, this
    );
    idt id = static_cast<idt>(num);
    if( id == 0 || !recReference::Exists( id ) ) {
        wxString mess;
        mess << "Reference R" << num << " Not available.";
        wxMessageBox( mess, "Reference ID Error" );
        return;
    }
    m_reference.FSetHigherID( id );
    UpdateHigherRef();
}

void rgDlgEditReference::OnButtonResearcher( wxCommandEvent& event )
{
    idt resID = rgSelectResearcher( this );
    if( resID == 0 ) {
        return;
    }
    m_resID = resID;
    UpdateResearcher();
}

void rgDlgEditReference::OnStatementViewChanged( wxBookCtrlEvent& event )
{
    if( m_notebookTop->GetSelection() == 1 ) {
        m_reference.f_statement = m_textCtrlStatement->GetValue();
        UpdateHtml();
    }
    m_panelTop->PostSizeEvent();
}

void rgDlgEditReference::OnToolCut( wxCommandEvent& event )
{
    m_textCtrlStatement->Cut();
}

void rgDlgEditReference::OnToolCopy( wxCommandEvent& event )
{
    m_textCtrlStatement->Copy();
}

void rgDlgEditReference::OnToolPaste( wxCommandEvent& event )
{
    m_textCtrlStatement->Paste();
}

void rgDlgEditReference::OnToolUndo( wxCommandEvent& event )
{
    m_textCtrlStatement->Undo();
}

void rgDlgEditReference::OnToolRedo( wxCommandEvent& event )
{
    m_textCtrlStatement->Redo();
}

void rgDlgEditReference::OnEntityViewChanged( wxBookCtrlEvent& event )
{
    switch( BPage( m_notebookBottom->GetSelection() ) )
    {
    case BPage::citation:
        UpdateCitations();
        break;
    case BPage::media:
        UpdateMedias();
        break;
    case BPage::persona:
        UpdatePersonas();
        break;
    case BPage::eventa:
        UpdateEventas();
        break;
    case BPage::entity:
        UpdateEntities();
        break;
    default:
        wxASSERT( false );
    }
    m_panelBottom->PostSizeEvent();
}

void rgDlgEditReference::CitationButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonCitationEdit->Disable();
        m_buttonCitationDel->Disable();
        m_buttonCitationUp->Disable();
        m_buttonCitationDn->Disable();
        return;
    }
    m_buttonCitationEdit->Enable();
    m_buttonCitationDel->Enable();
    if( row == 0 ) {
        m_buttonCitationUp->Disable();
    }
    else {
        m_buttonCitationUp->Enable();
    }
    if( row == m_listCitation->GetItemCount() - 1 ) {
        m_buttonCitationDn->Disable();
    }
    else {
        m_buttonCitationDn->Enable();
    }
}

void rgDlgEditReference::OnCitationDeselect( wxListEvent& event )
{
    CitationButtonsEnable( -1 );
}

void rgDlgEditReference::OnCitationSelect( wxListEvent& event )
{
    long row = m_listCitation->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    CitationButtonsEnable( row );
}


void rgDlgEditReference::OnCitationAddButton( wxCommandEvent& event )
{
    idt citID = rgCreateCitation( this, m_reference.FGetID() );
    if( citID ) {
        UpdateCitations( citID );
    }
}

void rgDlgEditReference::OnCitationEditButton( wxCommandEvent& event )
{
    long row = m_listCitation->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    wxASSERT( row != wxNOT_FOUND ); // Should not have been enabled then!
    idt citID = m_citationIDs[row];
    if( rgEditCitation( this, citID ) ) {
        UpdateCitations( citID );
    }
}

void rgDlgEditReference::OnCitationDeleteButton( wxCommandEvent& event )
{
    long row = m_listCitation->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    wxASSERT( row != wxNOT_FOUND ); // Should not have been enabled then!
    idt citID = m_citationIDs[row];
    wxMessageDialog dlg(
        this,
        recCitation::GetCitationStr(citID) +
        "\n Remove Citation from database?",
        "Confirm Delete", wxOK | wxCANCEL | wxCENTRE
    );
    if( dlg.ShowModal() != wxID_OK ) {
        return;
    }
    recCitation::RemoveFromDatabase( citID, "Main" );
    UpdateCitations( citID );
}

void rgDlgEditReference::OnCitationUpButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnCitationUpButton" );
}

void rgDlgEditReference::OnCitationDownButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnCitationDownButton" );
}

void rgDlgEditReference::MediaButtonsEnable( long row )
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
    m_buttonMediaView->Enable();
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
}

void rgDlgEditReference::OnMediaDeselect( wxListEvent& event )
{
    MediaButtonsEnable( -1 );
}

void rgDlgEditReference::OnMediaSelect( wxListEvent& event )
{
    long row = m_listMedia->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    MediaButtonsEnable( row );
}

void rgDlgEditReference::OnMediaAddButton( wxCommandEvent & event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaAddButton" );
}

void rgDlgEditReference::OnMediaEditButton( wxCommandEvent & event )
{
    long row = m_listMedia->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Edit Media" ) );
        return;
    }
    idt medID = m_mediaIDs[row];
    if ( rgEditMedia( this, medID ) ) {
        UpdateMedias( medID );
    }
}

void rgDlgEditReference::OnMediaDeleteButton( wxCommandEvent & event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaDeleteButton" );
}

void rgDlgEditReference::OnMediaUpButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaUpButton" );
}

void rgDlgEditReference::OnMediaDownButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaDownButton" );
}

void rgDlgEditReference::OnMediaViewButton( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnMediaViewButton" );
}

void rgDlgEditReference::PersonaButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonPersonaEdit->Disable();
        m_buttonPersonaDel->Disable();
        return;
    }
    m_buttonPersonaEdit->Enable();
    m_buttonPersonaDel->Enable();
}

void rgDlgEditReference::OnPersonaDeselect( wxListEvent& event )
{
    PersonaButtonsEnable( -1 );
}

void rgDlgEditReference::OnPersonaSelect( wxListEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    PersonaButtonsEnable( row );
}

void rgDlgEditReference::OnPersonaAddButton( wxCommandEvent& event )
{
    wxSize s = m_buttonPersonaAdd->GetSize();
    m_buttonPersonaAdd->PopupMenu( m_menuAddPersona, 0, s.y );
}

void rgDlgEditReference::OnAddMalePersona( wxCommandEvent & event )
{
    AddPersona( Sex::male );
}

void rgDlgEditReference::OnAddFemalePersona( wxCommandEvent & event )
{
    AddPersona( Sex::female );
}

void rgDlgEditReference::OnAddUnknownPersona( wxCommandEvent & event )
{
    AddPersona( Sex::unknown );
}

void rgDlgEditReference::AddPersona( Sex sex )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recPersona per(0);
    per.FSetRefID( m_reference.FGetID() );
    per.FSetSex( sex );
    per.Save();
    idt perID = per.FGetID();

    wxString nameStr = GetSelectedText();
    idt nameID = rgCreatePersonaName( this, perID, rgCRNAME_EditExtend, nameStr );
    if( nameID ) {
        recDb::ReleaseSavepoint( savepoint );
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Name, nameID );
        UpdateEntities( reID );
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditReference::OnPersonaEditButton( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Persona") );
        return;
    }
    idt perID = m_personaIDs[row];
    if( rgEditPersona( this, perID ) ) {
        UpdatePersonas( perID );
    }
}

void rgDlgEditReference::OnPersonaDeleteButton( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Persona") );
        return;
    }
    idt perID = m_personaIDs[row];
    wxString mess = wxString::Format(
        "Remove Persona %s: %s\nfrom Database?",
        recPersona::GetIdStr( perID ), recPersona::GetNameStr( perID )
    );
    int ans = wxMessageBox( mess, _("Delete Persona"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    recPersona::RemoveFromDatabase( perID );
    UpdatePersonas();
}

void rgDlgEditReference::EventaButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonEventaEdit->Disable();
        m_buttonEventaDel->Disable();
        return;
    }
    m_buttonEventaEdit->Enable();
    m_buttonEventaDel->Enable();
}

void rgDlgEditReference::OnEventaDeselect( wxListEvent& event )
{
    EventaButtonsEnable( -1 );
}

void rgDlgEditReference::OnEventaSelect( wxListEvent& event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    EventaButtonsEnable( row );
}

void rgDlgEditReference::OnEventaAddButton( wxCommandEvent & event )
{
    wxSize s = m_buttonEventaAdd->GetSize();
    m_buttonPersonaAdd->PopupMenu( m_menuAddEventa, 0, s.y );
}

void rgDlgEditReference::OnNewEventa( wxCommandEvent& cmnd_event )
{
    idt eaID = rgCreateEventa( this, m_reference.FGetID() );
    if ( eaID ) {
        UpdateEventas( eaID );
    }
}

void rgDlgEditReference::OnNewPersonalEventa( wxCommandEvent& event )
{
    idt eaID = rgCreatePersonalEventa(
        this, m_reference.FGetID(), GetSelectedText()
        );
    if ( eaID ) {
        UpdateEventas( eaID );
    }
}

void rgDlgEditReference::OnEventaEditButton( wxCommandEvent & event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Edit Eventa" ) );
        return;
    }
    idt eaID = m_eventaIDs[row];
    if ( rgEditEventa( this, eaID ) ) {
        UpdateEventas( eaID );
    }
}

void rgDlgEditReference::OnEventaDeleteButton( wxCommandEvent & event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if ( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Delete Eventa" ) );
        return;
    }
    idt eaID = m_eventaIDs[row];
    wxString mess = wxString::Format(
        "Remove Eventa %s: %s\nfrom Database?",
        recEventa::GetIdStr( eaID ), recEventa::GetTitle( eaID )
        );
    int ans = wxMessageBox( mess, _( "Delete Eventa" ), wxYES_NO | wxCANCEL, this );
    if ( ans != wxYES ) {
        return;
    }
    recEventa::RemoveFromDatabase( eaID );
    UpdateEventas();
}

void rgDlgEditReference::EntityButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonEdit->Disable();
        m_buttonDel->Disable();
        m_buttonUp->Disable();
        m_buttonDn->Disable();
        return;
    }
    m_buttonEdit->Enable();
    m_buttonDel->Enable();
    if( row == 0 ) {
        m_buttonUp->Disable();
    }
    else {
        m_buttonUp->Enable();
    }
    if( row == m_listEntities->GetItemCount() - 1 ) {
        m_buttonDn->Disable();
    }
    else {
        m_buttonDn->Enable();
    }
}

void rgDlgEditReference::OnEntityDeselect( wxListEvent& event )
{
    EntityButtonsEnable( -1 );
}

void rgDlgEditReference::OnEntitySelect( wxListEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    EntityButtonsEnable( row );
}

void rgDlgEditReference::OnAddEntityButton( wxCommandEvent& event )
{
    wxSize s = m_buttonAdd->GetSize();
    m_buttonAdd->PopupMenu( m_menuAddEntity, 0, s.y );
}

void rgDlgEditReference::OnNewDate( wxCommandEvent& event )
{
    idt dateID = rgCreateDate( this, GetSelectedText() );
    if( dateID ) {
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Date, dateID );
        UpdateEntities( reID );
    }
}

void rgDlgEditReference::OnNewDateAge( wxCommandEvent& event )
{
    wxString valStr = GetSelectedText();
    long val;
    if( !valStr.ToLong( &val ) ) {
        val = 0;
    }

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    unsigned retButton;
    idt baseID = rgSelectDate( this, rgSELSTYLE_Create, &retButton, recD_FILTER_Reference, m_reference.FGetID() );
    if( baseID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    if( retButton == rgSELSTYLE_Create ) {
        CreateRefEntity( recReferenceEntity::TYPE_Date, baseID );
    }

    idt dateID = rgCreateRelativeDate( this, baseID, val );
    if( dateID ) {
        recDb::ReleaseSavepoint( savepoint );
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Date, dateID );
        UpdateEntities( reID );
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditReference::OnNewPlace( wxCommandEvent& event )
{
    idt placeID = rgCreatePlace( this, GetSelectedText() );
    if( placeID ) {
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Place, placeID );
        UpdateEntities( reID );
    }
}

void rgDlgEditReference::OnNewName( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = rgSelectPersona(
        this, m_reference.FGetID(), rgSELSTYLE_Create, rgSELPER_CreateUnnamed
        );
    if ( perID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

    wxString nameStr = GetSelectedText();
    idt nameID = rgCreatePersonaName( this, perID, rgCRNAME_EditExtend, nameStr );
    if ( nameID ) {
        recDb::ReleaseSavepoint( savepoint );
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Name, nameID );
        UpdateEntities( reID );
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditReference::OnEditEntityButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    idt id = m_entities[row].FGetEntityID();
    switch( m_entities[row].FGetEntityType() )
    {
    case recReferenceEntity::TYPE_Date:
        if( rgEditDate( this, id ) ) break;
        return;
    case recReferenceEntity::TYPE_Place:
        if( rgEditPlace( this, id ) ) break;
        return;
    case recReferenceEntity::TYPE_Name:
        if( rgEditName( this, id ) ) break;
        return;
    default:
        wxMessageBox( _("Element cannot be edited"), _("Edit") );
        return;
    }
    UpdateEntities( m_entities[row].FGetID() );
}

void rgDlgEditReference::OnDeleteEntityButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    idt reID = m_entities[row].FGetID();
    idt entID = m_entities[row].FGetEntityID();
    switch( m_entities[row].FGetEntityType() )
    {
    case recReferenceEntity::TYPE_Date:
        recDate::RemoveFromDatabase( entID );
        break;
    case recReferenceEntity::TYPE_Place:
        recPlace::RemoveFromDatabase( entID );
        break;
    case recReferenceEntity::TYPE_Name:
        recName::RemoveFromDatabase( entID );
        break;
    default:
        wxMessageBox( _("Element cannot be deleted"), _("Delete") );
        return;
    }
    UpdateEntities();
}

void rgDlgEditReference::OnUpEntityButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_entities[row].FGetSequence();
    m_entities[row].FSetSequence( m_entities[row-1].FGetSequence() );
    m_entities[row].Save();
    m_entities[row-1].FSetSequence( seq );
    m_entities[row-1].Save();
    UpdateEntities( m_entities[row].FGetID() );
}

void rgDlgEditReference::OnDownEntityButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    if( row == m_listEntities->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_entities[row].FGetSequence();
    m_entities[row].FSetSequence( m_entities[row+1].FGetSequence() );
    m_entities[row].Save();
    m_entities[row+1].FSetSequence( seq );
    m_entities[row+1].Save();
    UpdateEntities( m_entities[row].FGetID() );
}

idt rgDlgEditReference::CreateRefEntity( recReferenceEntity::Type type, idt entID )
{
    recReferenceEntity re(0);
    re.FSetRefID( m_reference.FGetID() );
    re.FSetEntityType( type );
    re.FSetEntityID( entID );
    re.FSetSequence( m_reference.GetNextEntitySequence() );
    re.Save();
    return re.FGetID();
}

void rgDlgEditReference::InsertEntityListItem( size_t row )
{
    idt entID = m_entities[row].FGetEntityID();
    m_listEntities->InsertItem( row, m_entities[row].GetTypeStr() );
    switch( m_entities[row].FGetEntityType() )
    {
    case recReferenceEntity::TYPE_Date:
        m_listEntities->SetItem( row, ENT_COL_Number, recDate::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recDate::GetStr( entID ) );
        break;
    case recReferenceEntity::TYPE_Name:
        m_listEntities->SetItem( row, ENT_COL_Number, recName::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recName::GetNameStr( entID ) );
        break;
    case recReferenceEntity::TYPE_Place:
        m_listEntities->SetItem( row, ENT_COL_Number, recPlace::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recPlace::GetAddressStr( entID ) );
        break;
    default:
        m_listEntities->SetItem( row, ENT_COL_Value, _("Unknown Reference Entity") );
    }
}

// End of src/rg/rgEdReference.cpp file
