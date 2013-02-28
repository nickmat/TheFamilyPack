/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     26th February 2013
 * RCS-ID:      $Id$
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
#include <rec/recEvent.h>

#include <rg/rgDialogs.h>
#include "rgEdReference.h"

bool rgEditReference( wxWindow* parent, idt refID )
{
    wxASSERT( refID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgEditReference* dialog = new rgDlgEditReference( parent, refID );
    recDb::Savepoint( savepoint );

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
    m_staticRefID->SetLabel( m_reference.GetIdStr()  );
    m_textCtrlTitle->SetValue( m_reference.FGetTitle() );
    m_textCtrlStatement->SetValue(  m_reference.FGetStatement() );

    UpdateHtml();
    ListEntities();
    ListPersonas();
    return true;
}

void rgDlgEditReference::UpdateHtml()
{
    wxString htm;

    htm << "<html><head><title>" << m_reference.GetIdStr()
        << "</title></head><body>\n";

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

void rgDlgEditReference::ListEntities()
{
    m_entities = m_reference.ReadReferenceEntitys();
    m_listEntities->DeleteAllItems();
    for( size_t i = 0 ; i < m_entities.size() ; i++ )
    {
        InsertEntityListItem( i );
    }
    m_listEntities->SetColumnWidth( ENT_COL_Value, -1 );
}

void rgDlgEditReference::ListPersonas()
{
    m_personaIDs = m_reference.GetPersonaList();
    m_listPersona->DeleteAllItems();
    for( size_t i = 0 ; i < m_personaIDs.size() ; i++ ) {
        m_listPersona->InsertItem( i, recPersona::GetIdStr( m_personaIDs[i] ) );
        m_listPersona->SetItem( i, PER_COL_Name, recPersona::GetNameStr( m_personaIDs[i] ) );
        m_listPersona->SetItem( i, PER_COL_Individuals, recPersona::GetIndividualIdStr( m_personaIDs[i] ) );
    }
    m_listPersona->SetColumnWidth( PER_COL_Name, -1 );
}

bool rgDlgEditReference::TransferDataFromWindow()
{
    m_reference.FSetTitle( m_textCtrlTitle->GetValue() );
    m_reference.FSetStatement( m_textCtrlStatement->GetValue() );
    m_reference.Save();
    return true;
}
void rgDlgEditReference::OnTool( wxCommandEvent& event )
{
    switch( event.GetId() )
    {
    case tfpID_EDREF_OnCut:       DoCut();       break;
    case tfpID_EDREF_OnCopy:      DoCopy();      break;
    case tfpID_EDREF_OnPaste:     DoPaste();     break;
    case tfpID_EDREF_OnUndo:      DoUndo();      break;
    case tfpID_EDREF_OnRedo:      DoRedo();      break;
    }
}

void rgDlgEditReference::DoCut()
{
    m_textCtrlStatement->Cut();
}

void rgDlgEditReference::DoCopy()
{
    m_textCtrlStatement->Copy();
}

void rgDlgEditReference::DoPaste()
{
    m_textCtrlStatement->Paste();
}

void rgDlgEditReference::DoUndo()
{
    m_textCtrlStatement->Undo();
}

void rgDlgEditReference::DoRedo()
{
    m_textCtrlStatement->Redo();
}

void rgDlgEditReference::OnStatementViewChanging( wxNotebookEvent& event )
{
    if( event.GetSelection() == 0 ) {
        m_reference.f_statement = m_textCtrlStatement->GetValue();
        UpdateHtml();
    }
}

void rgDlgEditReference::OnPersonaAddButton( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnPersonaAddButton" );
}

void rgDlgEditReference::OnPersonaEditButton( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnPersonaAddButton" );
#if 0
    const wxString savepoint = "RefEdPer";
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }

    dlgEditPersona* dialog = new dlgEditPersona( NULL );
    dialog->SetPersonaID( m_personaIDs[row] );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listPersona->SetItem( row, PER_COL_Number, recPersona::GetIdStr( m_personaIDs[row] ) );
        m_listPersona->SetItem( row, PER_COL_Name, recPersona::GetNameStr( m_personaIDs[row] ) );
        m_listPersona->SetItem( row, PER_COL_Individuals, recPersona::GetIndividualIdStr( m_personaIDs[row] ) );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void rgDlgEditReference::OnPersonaDeleteButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnPersonaDeleteButton")
    );
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

    idt perID = rgSelectCreatePersona( this, m_reference.FGetID() );
    if( perID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

    wxString nameStr = m_textCtrlStatement->GetStringSelection();
    idt nameID = rgCreateName( perID, rgCRNAME_Default, nameStr );
    if( nameID ) {
        recDb::ReleaseSavepoint( savepoint );
        CreateRefEntity( recReferenceEntity::TYPE_Name, nameID );
        UpdateLists();
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditReference::OnNewDate( wxCommandEvent& event )
{
    idt dateID = rgCreateDate( m_textCtrlStatement->GetStringSelection() );
    if( dateID ) {
        CreateRefEntity( recReferenceEntity::TYPE_Date, dateID );
        UpdateLists();
    }
}

void rgDlgEditReference::OnNewDateAge( wxCommandEvent& event )
{
    wxString valStr = m_textCtrlStatement->GetStringSelection();
    long val;
    if( !valStr.ToLong( &val ) ) {
        val = 0;
    }

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    unsigned retButton;
    idt baseID = rgSelectDate( rgSELSTYLE_Create, &retButton, recD_FILTER_Reference, m_reference.FGetID() );
    if( baseID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    if( retButton == rgSELSTYLE_Create ) {
        CreateRefEntity( recReferenceEntity::TYPE_Date, baseID );
    }

    idt dateID = rgCreateRelativeDate( baseID, val );
    if( dateID ) {
        recDb::ReleaseSavepoint( savepoint );
        CreateRefEntity( recReferenceEntity::TYPE_Date, dateID );
        UpdateLists();
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditReference::OnNewPlace( wxCommandEvent& event )
{
    idt placeID = rgCreatePlace( m_textCtrlStatement->GetStringSelection() );
    if( placeID ) {
        CreateRefEntity( recReferenceEntity::TYPE_Place, placeID );
        UpdateLists();
    }
}

void rgDlgEditReference::OnNewEvent( wxCommandEvent& cmnd_event )
{
    idt eveID = rgCreateEvidEvent( this );
    if( eveID ) {
        CreateRefEntity( recReferenceEntity::TYPE_Event, eveID );
        UpdateLists();
    }
}

void rgDlgEditReference::OnNewPersonalEvent( wxCommandEvent& event )
{
    idt eveID = rgCreateEvidPerEvent( this, m_textCtrlStatement->GetStringSelection() );
    if( eveID ) {
        CreateRefEntity( recReferenceEntity::TYPE_Event, eveID );
        UpdateLists();
    }
}

void rgDlgEditReference::OnNewRelationship( wxCommandEvent& event )
{
    idt relID = rgCreatePerRelationship( this, m_textCtrlStatement->GetStringSelection() );
    if( relID ) {
        CreateRefEntity( recReferenceEntity::TYPE_Relationship, relID );
        UpdateLists();
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
        if( rgEditDate( id ) ) break;
        return;
    case recReferenceEntity::TYPE_Place: 
        if( rgEditPlace( id ) ) break;
        return;
    case recReferenceEntity::TYPE_Relationship:
        if( rgEditPerRelationship( this, id ) ) break;
        return;
    case recReferenceEntity::TYPE_Event: 
        if( rgEditEvidEvent( this, id ) ) break;
        return;
    case recReferenceEntity::TYPE_Name:
        if( rgEditName( id ) ) break;
        return;
    default:
        wxMessageBox( _("Element cannot be edited"), _("Edit") );
        return;
    }
    UpdateLists();
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
        recEvent::RemoveFromDatabase( entID );
        break;
    default:
        wxMessageBox( _("Element cannot be deleted"), _("Delete") );
        return;
    }
    UpdateLists();
}

void rgDlgEditReference::OnUpEntityButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    if( row != 0 ) {
        recReferenceEntity ent = m_entities[row];
        m_entities[row] = m_entities[row-1];
        m_entities[row-1] = ent;
        UpdateSequence();

        m_listEntities->DeleteItem( row );
        InsertEntityListItem( row-1 );
        long state = wxLIST_STATE_SELECTED;
        m_listEntities->SetItemState( row-1, state, state );
        m_listEntities->EnsureVisible( row-1 );
    }
}

void rgDlgEditReference::OnDownEntityButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    if( row < m_listEntities->GetItemCount()-1 ) {
        recReferenceEntity ent = m_entities[row];
        m_entities[row] = m_entities[row+1];
        m_entities[row+1] = ent;
        UpdateSequence();

        m_listEntities->DeleteItem( row );
        InsertEntityListItem( row+1 );
        long state = wxLIST_STATE_SELECTED;
        m_listEntities->SetItemState( row+1, state, state );
        m_listEntities->EnsureVisible( row+1 );
    }
}

void rgDlgEditReference::CreateRefEntity( recReferenceEntity::Type type, idt entID )
{
    recReferenceEntity re(0);
    re.FSetRefID( m_reference.FGetID() );
    re.FSetEntityType( type );
    re.FSetEntityID( entID );
    re.FSetSequence( m_reference.GetNextEntitySequence() );
    re.Save();
}

bool rgDlgEditReference::SelectDate( 
    idt* dateID, const wxString& title, unsigned style )
{
    wxASSERT( dateID );  // Can't handle NULL pointer

    unsigned retButton;
    *dateID = rgSelectDate( style, &retButton, recD_FILTER_Reference, m_reference.FGetID() );
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
    *placeID = rgSelectPlace( style, &retButton, recP_FILTER_Reference, m_reference.FGetID() );
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

idt rgDlgEditReference::SelectCreatePersona()
{
    return rgSelectCreatePersona( this, m_reference.FGetID() );
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
    case recReferenceEntity::TYPE_Relationship:
        m_listEntities->SetItem( row, ENT_COL_Number, recRelationship::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recRelationship::GetValue1Str( entID ) );
        break;
    case recReferenceEntity::TYPE_Event:
        m_listEntities->SetItem( row, ENT_COL_Number, recEvent::GetIdStr( entID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recEvent::GetTitle( entID ) );
        break;
    default:
        m_listEntities->SetItem( row, ENT_COL_Value, _("Unknown Reference Entity") );
    }
}

void rgDlgEditReference::UpdateSequence()
{
    for( size_t i = 0 ; i < m_entities.size() ; i++ ) {
        if( m_entities[i].FGetSequence() != i+1 ) {
            m_entities[i].FSetSequence( i+1 );
            m_entities[i].Save();
        }
    }
}

// End of src/rg/rgEdReference.cpp file
