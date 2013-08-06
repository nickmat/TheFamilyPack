/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     26th February 2013
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recPersona.h>
#include <rec/recEventum.h>

#include <rg/rgDialogs.h>
#include "rgEdReference.h"
#include "rgSelect.h"

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
    ref.Save();
    idt refID = ref.FGetID();

    if( rgEditReference( parent, refID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return refID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

extern bool rgSelectDateFromReference(
    wxWindow* wind, idt* dateID, idt refID, const wxString& title, unsigned style )
{
    wxASSERT( dateID );  // Can't handle NULL pointer

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

BEGIN_EVENT_TABLE( rgDlgEditReference, wxDialog )
    EVT_MENU( ID_EDREF_NEW_SOURCE,   rgDlgEditReference::OnNewSource )
    EVT_MENU( ID_EDREF_NEW_NAME,     rgDlgEditReference::OnNewName )
    EVT_MENU( ID_EDREF_NEW_DATE,     rgDlgEditReference::OnNewDate )
    EVT_MENU( ID_EDREF_NEW_DATE_AGE, rgDlgEditReference::OnNewDateAge )
    EVT_MENU( ID_EDREF_NEW_PLACE,    rgDlgEditReference::OnNewPlace )
    EVT_MENU( ID_EDREF_NEW_EVENT,    rgDlgEditReference::OnNewEvent )
    EVT_MENU( ID_EDREF_NEW_PER_EVENT,rgDlgEditReference::OnNewPersonalEvent )
    EVT_MENU( ID_EDREF_NEW_REL,      rgDlgEditReference::OnNewRelationship )
    EVT_MENU_RANGE( ID_ADDPER_MALE, ID_ADDPER_UNKNOWN, rgDlgEditReference::OnPersonaAddMenuOp )
END_EVENT_TABLE()

rgDlgEditReference::rgDlgEditReference( wxWindow* parent, idt refID )
    : m_reference(refID), fbRgEditReference( parent )
{
    m_listEntities->InsertColumn( ENT_COL_Number, _("ID") );
    m_listEntities->InsertColumn( ENT_COL_Type, _("Type") );
    m_listEntities->InsertColumn( ENT_COL_Value, _("Value") );

    m_listPersona->InsertColumn( PER_COL_Number, _("Number") );
    m_listPersona->InsertColumn( PER_COL_Name, _("Name") );
    m_listPersona->InsertColumn( PER_COL_Individuals, _("Individuals") );
}

bool rgDlgEditReference::TransferDataToWindow()
{
    wxASSERT( m_reference.FGetID() != 0 );
    m_staticRefID->SetLabel( m_reference.GetIdStr()  );
    m_textCtrlTitle->SetValue( m_reference.FGetTitle() );
    m_textCtrlStatement->SetValue(  m_reference.FGetStatement() );

    UpdateHtml();
    UpdatePersonas();
    UpdateEntities();
    return true;
}

bool rgDlgEditReference::TransferDataFromWindow()
{
    m_reference.FSetTitle( m_textCtrlTitle->GetValue() );
    m_reference.FSetStatement( m_textCtrlStatement->GetValue() );
    m_reference.Save();
    return true;
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
}

wxString rgDlgEditReference::GetSelectedText() const
{
    switch( m_notebookTop->GetSelection() )
    {
    case 0: // Source
        return m_textCtrlStatement->GetStringSelection();
    case 1: // View
        return m_webview->GetSelectedText();
    }
    return wxEmptyString;
}

void rgDlgEditReference::OnTool( wxCommandEvent& event )
{
    switch( event.GetId() )
    {
    case tfpID_EDREF_OnCut:
        m_textCtrlStatement->Cut();
        break;
    case tfpID_EDREF_OnCopy:
        m_textCtrlStatement->Copy();
        break;
    case tfpID_EDREF_OnPaste:
        m_textCtrlStatement->Paste();
        break;
    case tfpID_EDREF_OnUndo:
        m_textCtrlStatement->Undo();
        break;
    case tfpID_EDREF_OnRedo:
        m_textCtrlStatement->Redo();
        break;
    }
}

void rgDlgEditReference::OnStatementViewChanged( wxBookCtrlEvent& event )
{
    if( m_notebookTop->GetSelection() == 1 ) {
        m_reference.f_statement = m_textCtrlStatement->GetValue();
        UpdateHtml();
    }
    m_panelTop->PostSizeEvent();
}

void rgDlgEditReference::OnEntityViewChanged( wxBookCtrlEvent& event )
{
    switch( m_notebookBottom->GetSelection() )
    {
    case 0:
        UpdatePersonas();
        break;
    case 1:
        UpdateEntities();
        break;
    default:
        wxASSERT( false );
    }
    m_panelBottom->PostSizeEvent();
}

void rgDlgEditReference::OnPersonaAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_ADDPER_MALE, _("Add &Male Persona") );
    menu->Append( ID_ADDPER_FEMALE, _("Add &Female Persona") );
    menu->Append( ID_ADDPER_UNKNOWN, _("Add &Unknown Persona") );
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditReference::OnPersonaAddMenuOp( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recPersona per(0);
    per.FSetRefID( m_reference.FGetID() );
    switch( event.GetId() )
    {
    case ID_ADDPER_MALE:
        per.FSetSex( SEX_Male );
        break;
    case ID_ADDPER_FEMALE:
        per.FSetSex( SEX_Female );
        break;
    case ID_ADDPER_UNKNOWN:
        per.FSetSex( SEX_Unknown );
        break;
    }
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
        wxMessageBox( _("No row selected"), _("Edit Entity") );
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

void rgDlgEditReference::OnAddEntityButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_EDREF_NEW_SOURCE, _("&Source") );
    menu->Append( ID_EDREF_NEW_DATE, _("&Date") );
    menu->Append( ID_EDREF_NEW_DATE_AGE, _("Date a&ge") );
    menu->Append( ID_EDREF_NEW_PLACE, _("&Place") );
    menu->Append( ID_EDREF_NEW_NAME, _("&Name") );
    menu->Append( ID_EDREF_NEW_REL, _("&Relationship") );
    menu->Append( ID_EDREF_NEW_EVENT, _("&Event") );
    menu->Append( ID_EDREF_NEW_PER_EVENT, _("Personal E&vent") );
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditReference::OnNewSource( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnNewSource" );
}

void rgDlgEditReference::OnNewName( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = rgSelectPersona(
        this, m_reference.GetID(), rgSELSTYLE_Create, rgSELPER_CreateUnnamed
    );
    if( perID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

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

void rgDlgEditReference::OnNewEvent( wxCommandEvent& cmnd_event )
{
    idt eveID = rgCreateEventum( this, m_reference.FGetID() );
    if( eveID ) {
        UpdateEntities();// reID );
    }
}

void rgDlgEditReference::OnNewPersonalEvent( wxCommandEvent& event )
{
    idt eveID = rgCreatePersonalEventum(
        this, m_reference.FGetID(), GetSelectedText()
    );
    if( eveID ) {
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Event, eveID );
        UpdateEntities( reID );
    }
}

void rgDlgEditReference::OnNewRelationship( wxCommandEvent& event )
{
    idt relID = rgCreatePersonaRelationship(
        this, m_reference.FGetID(), GetSelectedText()
    );
    if( relID ) {
        idt reID = CreateRefEntity( recReferenceEntity::TYPE_Relationship, relID );
        UpdateEntities( reID );
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
    case recReferenceEntity::TYPE_Relationship:
        if( rgEditPersonaRelationship( this, id ) ) break;
        return;
    case recReferenceEntity::TYPE_Event:
        if( rgEditEventum( this, id ) ) break;
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
    case recReferenceEntity::TYPE_Relationship:
        recRelationship::Delete( entID );
        recReferenceEntity::Delete( reID );
        break;
    case recReferenceEntity::TYPE_Name:
        recName::RemoveFromDatabase( entID );
        break;
    case recReferenceEntity::TYPE_Event:
        recEventum::RemoveFromDatabase( entID );
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
#if 0
bool rgDlgEditReference::SelectDate(
    idt* dateID, const wxString& title, unsigned style )
{
    wxASSERT( dateID );  // Can't handle NULL pointer

    unsigned retButton;
    *dateID = rgSelectDate( this, style, &retButton, recD_FILTER_Reference, m_reference.FGetID() );
    if( retButton == rgSELSTYLE_Create ) {
        CreateRefEntity( recReferenceEntity::TYPE_Date, *dateID );
    }
    if( *dateID == 0 ) {
        if( retButton == rgSELSTYLE_Unknown ) {
            return true;
        }
        return false;
    }
    return true;
}

bool rgDlgEditReference::SelectPlace(
    idt* placeID, const wxString& title, unsigned style )
{
    wxASSERT( placeID );  // Can't handle NULL pointer

    unsigned retButton;
    *placeID = rgSelectPlace( this, style, &retButton, recP_FILTER_Reference, m_reference.FGetID() );
    if( retButton == rgSELSTYLE_Create ) {
        CreateRefEntity( recReferenceEntity::TYPE_Place, *placeID );
    }
    if( *placeID == 0 ) {
        if( retButton == rgSELSTYLE_Unknown ) {
            return true;
        }
        return false;
    }
    return true;
}
#endif

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
    case recReferenceEntity::TYPE_Relationship:
        m_listEntities->SetItem( row, ENT_COL_Number, recRelationship::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recRelationship::GetValue1Str( entID ) );
        break;
    case recReferenceEntity::TYPE_Event:
        m_listEntities->SetItem( row, ENT_COL_Number, recEventum::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recEventum::GetTitle( entID ) );
        break;
    default:
        m_listEntities->SetItem( row, ENT_COL_Value, _("Unknown Reference Entity") );
    }
}

// End of src/rg/rgEdReference.cpp file
