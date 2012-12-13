/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include "dlgEdReference.h"
#include "dlgEdEvent.h"
#include "dlgEdPersona.h"
#include "dlgEdRelationship.h"
#include "dlgSelect.h"


int tfpGetEntityIndex( TfpEntities* array, int ind )
{
    for( size_t i = 0 ; i < array->size() ; i++ ) {
        if( (*array)[i].index == ind ) return i;
    }
    return -1;
}

BEGIN_EVENT_TABLE( dlgEditReference, wxDialog )
    EVT_MENU( ID_EDREF_NEW_SOURCE,   dlgEditReference::OnNewSource )
    EVT_MENU( ID_EDREF_NEW_EVENT,    dlgEditReference::OnNewEvent )
    EVT_MENU( ID_EDREF_NEW_PLACE,    dlgEditReference::OnNewPlace )
    EVT_MENU( ID_EDREF_NEW_DATE,     dlgEditReference::OnNewDate )
    EVT_MENU( ID_EDREF_NEW_DATE_AGE, dlgEditReference::OnNewDateAge )
    EVT_MENU( ID_EDREF_NEW_NAME,     dlgEditReference::OnNewName )
    EVT_MENU( ID_EDREF_NEW_REL,      dlgEditReference::OnNewRelationship )
    EVT_MENU( ID_EDREF_NEW_PER_EVENT,dlgEditReference::OnNewPersonalEvent )
END_EVENT_TABLE()

dlgEditReference::dlgEditReference( wxWindow* parent )
    : fbDlgEditReference( parent )
{
    m_listEntities->InsertColumn( ENT_COL_Number, _("ID") );
    m_listEntities->InsertColumn( ENT_COL_Type, _("Type") );
    m_listEntities->InsertColumn( ENT_COL_Value, _("Value") );
    m_listPersona->InsertColumn( PER_COL_Number, _("Number") );
    m_listPersona->InsertColumn( PER_COL_Name, _("Name") );
    m_listPersona->InsertColumn( PER_COL_Individuals, _("Individuals") );
}

bool dlgEditReference::TransferDataToWindow()
{
    if( m_reference.f_id == 0 ) {
        m_reference.Save();
    } else {
        m_reference.Read();
    }

    wxString str;
    str << wxT("R") << m_reference.f_id;
    m_staticRefID->SetLabel( str  );

    m_textCtrlTitle->SetValue( m_reference.f_title );
    m_textCtrlStatement->SetValue(  m_reference.f_statement );
    UpdateHtml();

    recRefEntVec  evid_ents;
    evid_ents = m_reference.ReadReferenceEntitys();
    for( size_t i = 0 ; i < evid_ents.size() ; i++ )
    {
        TfpEntity entity;
        entity.rec = evid_ents[i];
        idt entID = entity.rec.f_entity_id;
        entity.owner = 0;
        m_entities.push_back( entity );
        m_listEntities->InsertItem( i, entity.rec.GetTypeStr() );
        switch( entity.rec.f_entity_type )
        {
        case recReferenceEntity::TYPE_Date:
            m_listEntities->SetItem( i, ENT_COL_Number, recDate::GetIdStr( entID ) );
            m_listEntities->SetItem( i, ENT_COL_Value, recDate::GetStr( entID ) );
            break;
        case recReferenceEntity::TYPE_Name:
            m_listEntities->SetItem( i, ENT_COL_Number, recName::GetIdStr( entID ) );
            m_listEntities->SetItem( i, ENT_COL_Value, recName::GetNameStr( entID ) );
            break;
        case recReferenceEntity::TYPE_Place:
            m_listEntities->SetItem( i, ENT_COL_Number, recPlace::GetIdStr( entID ) );
            m_listEntities->SetItem( i, ENT_COL_Value, recPlace::GetAddressStr( entID ) );
            break;
        case recReferenceEntity::TYPE_Relationship:
            m_listEntities->SetItem( i, ENT_COL_Number, recRelationship::GetIdStr( entID ) );
            m_listEntities->SetItem( i, ENT_COL_Value, recRelationship::GetValue1Str( entID ) );
            break;
        case recReferenceEntity::TYPE_Event:
            m_listEntities->SetItem( i, ENT_COL_Number, recEvent::GetIdStr( entID ) );
            m_listEntities->SetItem( i, ENT_COL_Value, recEvent::GetTitle( entID ) );
            break;
        default:
            m_listEntities->SetItem( i, ENT_COL_Value, _("Unknown Reference Entity") );
        }
    }
    m_listEntities->SetColumnWidth( ENT_COL_Value, -1 );

    m_personaIDs = m_reference.GetPersonaList();
    for( size_t i = 0 ; i < m_personaIDs.size() ; i++ ) {
        m_listPersona->InsertItem( i, recPersona::GetIdStr( m_personaIDs[i] ) );
        m_listPersona->SetItem( i, PER_COL_Name, recPersona::GetNameStr( m_personaIDs[i] ) );
        m_listPersona->SetItem( i, PER_COL_Individuals, recPersona::GetIndividualIdStr( m_personaIDs[i] ) );
    }
    m_listPersona->SetColumnWidth( PER_COL_Name, -1 );
    return true;
}

bool dlgEditReference::TransferDataFromWindow()
{
    m_reference.f_title = m_textCtrlTitle->GetValue();
    m_reference.f_statement = m_textCtrlStatement->GetValue();
    m_reference.Save();
    for( size_t i = 0 ; i < m_entities.size() ; i++ ) {
        recReferenceEntity* re = &m_entities[i].rec;
        if( re->f_sequence != i+1 ) {
            re->f_sequence = i+1;
            re->Save();
        }
    }
    return true;
}

void dlgEditReference::OnTool( wxCommandEvent& event )
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

void dlgEditReference::DoCut()
{
    m_textCtrlStatement->Cut();
}

void dlgEditReference::DoCopy()
{
    m_textCtrlStatement->Copy();
}

void dlgEditReference::DoPaste()
{
    m_textCtrlStatement->Paste();
}

void dlgEditReference::DoUndo()
{
    m_textCtrlStatement->Undo();
}

void dlgEditReference::DoRedo()
{
    m_textCtrlStatement->Redo();
}

void dlgEditReference::OnStatementViewChanging( wxNotebookEvent& event )
{
    if( event.GetSelection() == 0 ) {
        m_reference.f_statement = m_textCtrlStatement->GetValue();
        UpdateHtml();
    }
}


void dlgEditReference::OnPersonaAddButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnPersonaAddButton")
    );
}

void dlgEditReference::OnPersonaEditButton( wxCommandEvent& event )
{
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
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnPersonaDeleteButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnPersonaDeleteButton")
    );
}

void dlgEditReference::OnAddButton( wxCommandEvent& event )
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

void dlgEditReference::OnNewSource( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnNewSource" );
}

void dlgEditReference::OnNewDate( wxCommandEvent& event )
{
    idt dateID = rgCreateDate( m_textCtrlStatement->GetStringSelection() );
    if( dateID == 0 ) {
        return;
    }

    int row = m_entities.size();
    TfpEntity entity;
    entity.rec.Clear();
    entity.owner = 0;
    entity.rec.f_ref_id = m_reference.f_id;
    entity.rec.f_entity_type = recReferenceEntity::TYPE_Date;
    entity.rec.f_entity_id = dateID;
    entity.rec.Save();
    m_entities.push_back( entity );

    m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
    m_listEntities->SetItem( row, ENT_COL_Number, recDate::GetIdStr( dateID ) );
    m_listEntities->SetItem( row, ENT_COL_Value, recDate::GetStr( dateID ) );
}

void dlgEditReference::OnNewDateAge( wxCommandEvent& event )
{
    wxString valStr = m_textCtrlStatement->GetStringSelection();
    long val;
    if( !valStr.ToLong( &val ) ) {
        val = 0;
    }

    idt baseID;
    unsigned style = dlgSelect::SELSTYLE_CreateButton;
    if( SelectDate( &baseID, _("Select Base Date"), style ) == false ) {
        return;
    }

    idt dateID = rgCreateRelativeDate( baseID, val );
    if( dateID == 0 ) {
        return;
    }

    int row = m_entities.size();
    TfpEntity entity;
    entity.rec.Clear();
    entity.owner = 0;
    entity.rec.f_ref_id = m_reference.f_id;
    entity.rec.f_entity_type = recReferenceEntity::TYPE_Date;
    entity.rec.f_entity_id = dateID;
    entity.rec.Save();
    m_entities.push_back( entity );

    m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
    m_listEntities->SetItem( row, ENT_COL_Number, recDate::GetIdStr( dateID ) );
    m_listEntities->SetItem( row, ENT_COL_Value, recDate::GetStr( dateID ) );
}

void dlgEditReference::OnNewPlace( wxCommandEvent& event )
{
    idt placeID = rgCreatePlace( m_textCtrlStatement->GetStringSelection() );
    if( placeID == 0 ) {
        return;
    }

    int row = m_entities.size();
    TfpEntity entity;
    entity.rec.Clear();
    entity.owner = 0;
    entity.rec.f_ref_id = m_reference.f_id;
    entity.rec.f_entity_type = recReferenceEntity::TYPE_Place;
    entity.rec.f_entity_id = placeID;
    entity.rec.Save();
    m_entities.push_back( entity );

    m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
    m_listEntities->SetItem( row, ENT_COL_Number, recPlace::GetIdStr( placeID ) );
    m_listEntities->SetItem( row, ENT_COL_Value, recPlace::GetAddressStr( placeID ) );
}

void dlgEditReference::OnNewRelationship( wxCommandEvent& event )
{
    const wxString savepoint = "RefNewRel";
    recDb::Savepoint( savepoint );

    idt per1ID = SelectCreatePersona();
    if( per1ID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    idt per2ID = SelectCreatePersona();
    if( per2ID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    dlgEditRelationship* dialog = new dlgEditRelationship( NULL );
    dialog->SetPersona1ID( per1ID );
    dialog->SetPersona2ID( per2ID );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Relationship;
        entity.rec.f_entity_id = dialog->GetRelationship()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, ENT_COL_Number, dialog->GetRelationship()->GetIdStr() );
        m_listEntities->SetItem( row, ENT_COL_Value, dialog->GetRelationship()->GetValue1Str() );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewEvent( wxCommandEvent& cmnd_event )
{
    const wxString savepoint = "RefEvent";
    // Future selection dialogs will be able to create new "user created" 
    // items and we will need to be able to roll these back.
    recDb::Savepoint( savepoint );

    idt typeID = rgSelectEventType();
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

    bool enddate = false;
    bool person2 = false;
    recEventTypeRole::Role role1 = recEventTypeRole::ROLE_Unstated;
    recEventTypeRole::Role role2 = recEventTypeRole::ROLE_Unstated;
    recEventType etype( typeID );

    switch( etype.f_grp )
    {
    case recEventType::ETYPE_Grp_Birth:
        role1 = recEventTypeRole::ROLE_Birth_Born;
        break;
    case recEventType::ETYPE_Grp_Nr_Birth:
        break;
    case recEventType::ETYPE_Grp_Death:
        role1 = recEventTypeRole::ROLE_Death_Died;
        break;
    case recEventType::ETYPE_Grp_Nr_Death:
        break;
    case recEventType::ETYPE_Grp_Union:
        person2 = true;
        role1 = recEventTypeRole::ROLE_Marriage_Groom;
        role2 = recEventTypeRole::ROLE_Marriage_Bride;
        break;
    case recEventType::ETYPE_Grp_Family:
        person2 = true;
        break;
    default:
        enddate = true;
    }

    idt dateID1;
    unsigned style = dlgSelect::SELSTYLE_CreateButton | dlgSelect::SELSTYLE_UnknownButton;
    if( SelectDate( &dateID1, _("Select Start Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return;
    }
    idt dateID2 = 0;
    if( enddate ) {
        if( SelectDate( &dateID2, _("Select End Date"), style ) == false ) {
            recDb::Rollback( savepoint );
            return;
        }
    }
    idt placeID;
    if( SelectPlace( &placeID, _("Select Place"), style ) == false ) {
        recDb::Rollback( savepoint );
        return;
    }

    wxString title;
    idt perID1 = SelectCreatePersona();
    if( perID1 == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    idt perID2 = 0;
    if( person2 ) {
        perID2 = SelectCreatePersona();
        if( perID2 == 0 ) {
            recDb::Rollback( savepoint );
            return;
        }
        title = wxString::Format(
            _("%s of %s and %s"),
            etype.GetTypeStr(),
            recPersona::GetNameStr( perID1 ),
            recPersona::GetNameStr( perID2 )
        );
    } else {
        title = wxString::Format(
            _("%s of %s"),
            etype.GetTypeStr(),
            recPersona::GetNameStr( perID1 )
        );
    }

    dlgEditEvent* dialog = new dlgEditEvent( NULL );

    dialog->SetEntities( &m_entities );
    dialog->SetRefID( m_reference.f_id );
    dialog->SetDateStrings( GetDateEntityStringVec() );

    recEvent e(0);
    e.f_title = title;
    e.f_type_id = typeID;
    e.f_date1_id = dateID1;
    e.f_date2_id = dateID2;
    e.f_place_id = placeID;
    e.Save();
    dialog->SetData( typeID, e.f_id );
    recEventPersona ep1(0);
    ep1.f_event_id = e.f_id;
    ep1.f_per_id = perID1;
    ep1.f_role_id = role1;
    ep1.Save();
    if( person2 ) {
        recEventPersona ep2(0);
        ep2.f_event_id = e.f_id;
        ep2.f_per_id = perID2;
        ep2.f_role_id = role2;
        ep2.Save();
    }
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Event;
        entity.rec.f_entity_id = dialog->GetEvent()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, ENT_COL_Number, dialog->GetEvent()->GetIdStr() );
        m_listEntities->SetItem( row, ENT_COL_Value, dialog->GetEvent()->f_title );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewPersonalEvent( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEvent eve(0);
    recEventPersona ep(0);

    eve.FSetTypeID( rgSelectEventType( rgSELSTYLE_Create, NULL, recET_FILTER_GrpPersonal ) );
    if( eve.FGetTypeID() == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    ep.FSetPerID( SelectCreatePersona() );
    if( ep.FGetPerID() == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    idt date1ID, date2ID;
    unsigned style = dlgSelect::SELSTYLE_CreateButton | dlgSelect::SELSTYLE_UnknownButton;
    if( SelectDate( &date1ID, _("Select Start Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return;
    }
    if( SelectDate( &date2ID, _("Select End Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return;
    }
    if( date1ID == date2ID ) {
        date2ID = 0;
    }
    eve.FSetDate1ID( date1ID );
    eve.FSetDate2ID( date2ID );
    idt placeID;
    if( SelectPlace( &placeID, _("Select Place"), style ) == false ) {
        recDb::Rollback( savepoint );
        return;
    }
    eve.FSetPlaceID( placeID );

    eve.FSetTitle( 
        wxString::Format( 
            _("%s of %s"), 
            eve.GetTypeStr(), 
            recPersona::GetNameStr( ep.FGetPerID() )
        )
    );
    eve.FSetDatePt( recDate::DATE_POINT_Mid );

    ep.FSetNote( m_textCtrlStatement->GetStringSelection() );
    ep.FSetPerSeq( 1 );

    eve.Save();
    ep.FSetEventID( eve.FGetID() );
    ep.Save();

    if( rgEditPerEventRole( ep.FGetID() ) ) {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Event;
        entity.rec.f_entity_id = eve.FGetID();
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, ENT_COL_Number, eve.GetIdStr() );
        m_listEntities->SetItem( row, ENT_COL_Value, eve.FGetTitle() );
    } else {
        recDb::Rollback( savepoint );
    }
}

void dlgEditReference::OnNewName( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = SelectCreatePersona();
    if( perID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }
    wxString nameStr = m_textCtrlStatement->GetStringSelection();
    idt nameID = rgCreateName( perID, rgCRNAME_Default, nameStr );
    if( nameID ) {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Name;
        entity.rec.f_entity_id = nameID;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, ENT_COL_Number, recName::GetIdStr( nameID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recName::GetNameStr( nameID ) );
    } else {
        recDb::Rollback( savepoint );
    }
}

void dlgEditReference::OnEditButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    idt id = m_entities[row].rec.f_entity_id;
    switch( m_entities[row].rec.f_entity_type )
    {
    case recReferenceEntity::TYPE_Date:      DoEditDate( id, row );      break;
    case recReferenceEntity::TYPE_Place:     DoEditPlace( id, row );     break;
    case recReferenceEntity::TYPE_Relationship: DoEditRelationship( id, row ); break;
    case recReferenceEntity::TYPE_Event:     DoEditEvent( id, row );     break;
    case recReferenceEntity::TYPE_Name :     DoEditName( id, row );      break;
    default:
        wxMessageBox( _("Element cannot be edited"), _("Edit") );
        return;
    }
}

void dlgEditReference::DoEditDate( idt dateID, long row )
{
    if( rgEditDate( dateID ) ) {
        m_listEntities->SetItem( row, ENT_COL_Number, recDate::GetIdStr( dateID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recDate::GetStr( dateID ) );
    }
}

void dlgEditReference::DoEditPlace( idt placeID, long row )
{
    if( rgEditPlace( placeID ) ) {
        m_listEntities->SetItem( row, ENT_COL_Number, recPlace::GetIdStr( placeID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recPlace::GetAddressStr( placeID ) );
    }
}

void dlgEditReference::DoEditRelationship( idt id, long row )
{
    const wxString savepoint = "RefEdRel";
    dlgEditRelationship* dialog = new dlgEditRelationship( NULL, id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, ENT_COL_Number, dialog->GetRelationship()->GetIdStr() );
        m_listEntities->SetItem( row, ENT_COL_Value, dialog->GetRelationship()->GetValue1Str() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditEvent( idt id, long row )
{
    const wxString savepoint = "RefEdEvent";
    dlgEditEvent* dialog = new dlgEditEvent( NULL );

    dialog->SetData( 0, id );
    dialog->SetEntities( &m_entities );
    dialog->SetRefID( m_reference.f_id );
    dialog->SetDateStrings( GetDateEntityStringVec() );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, ENT_COL_Number, dialog->GetEvent()->GetIdStr() );
        m_listEntities->SetItem( row, ENT_COL_Value, dialog->GetEvent()->f_title );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditName( idt id, long row )
{
    if( rgEditName( id ) ) {
        m_listEntities->SetItem( row, ENT_COL_Number, recName::GetIdStr( id ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recName::GetNameStr( id ) );
    }
}

void dlgEditReference::OnDeleteButton( wxCommandEvent& event )
{
    wxMessageBox( _("Rewrite needed"), _("OnDeleteButton") );
#if 0
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    idt reID = m_entities[row].rec.f_id;
    idt entID = m_entities[row].rec.f_entity_id;
    recReferenceEntity::Type type = m_entities[row].rec.f_entity_type;
    switch( type )
    {
    case recReferenceEntity::TYPE_Date:
        recDate::Delete( entID );
        recReferenceEntity::Delete( reID );
        break;
    case recReferenceEntity::TYPE_Place:
        {
            recPlacePartList arr_pp = recPlace::GetPlaceParts( entID );
            for( size_t i = 0 ; i < arr_pp.size() ; i++ ) {
                arr_pp[i].Delete();
            }
            recPlace::Delete( entID );
            recReferenceEntity::Delete( reID );
        }
        break;
    case recReferenceEntity::TYPE_Relationship:
        wxMessageBox( _("Rewrite needed"), _("OnDeleteButton") );
#if 0
        {
            recAttributeVec arrAttr = recPersona::ReadAttributes( entID );
            for( size_t i = 0 ; i < arrAttr.size() ; i++ ) {
                arrAttr[i].Delete();
            }
            recPersona::Delete( entID );
            recReferenceEntity::Delete( reID );
        }
#endif
        break;
    case recReferenceEntity::TYPE_Attribute:
        recAttribute::Delete( entID );
        recReferenceEntity::Delete( reID );
        break;
    default:
        wxMessageBox( _("Element cannot be deleted"), _("Delete") );
        return;
    }
    m_listEntities->DeleteItem( row );
    m_entities.erase( m_entities.begin() + row );
    // Remove list rows that are owned by entID (Persona only?)
    if( type == recReferenceEntity::TYPE_Persona ) {
        size_t i = 0;
        while( i < m_entities.size() ) {
            if( m_entities[i].rec.f_entity_type == recReferenceEntity::TYPE_Attribute
                && m_entities[i].owner == entID )
            {
                recAttribute::Delete( m_entities[i].rec.f_entity_id );
                recReferenceEntity::Delete( m_entities[i].rec.f_id );
                m_listEntities->DeleteItem( i );
                m_entities.erase( m_entities.begin() + i );
            } else {
                i++;
            }
        }
    }
#endif
}

void dlgEditReference::OnUpButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    if( row != 0 ) {
        TfpEntity temp = m_entities[row];
        m_entities[row] = m_entities[row-1];
        m_entities[row-1] = temp;

        m_listEntities->DeleteItem( row );
        InsertListItem( row-1, m_entities[row-1] );
        long state = wxLIST_STATE_SELECTED;
        m_listEntities->SetItemState( row-1, state, state );
        m_listEntities->EnsureVisible( row-1 );
    }
}

void dlgEditReference::OnDownButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    if( row < m_listEntities->GetItemCount()-1 ) {
        TfpEntity temp = m_entities[row];
        m_entities[row] = m_entities[row+1];
        m_entities[row+1] = temp;

        m_listEntities->DeleteItem( row );
        InsertListItem( row+1, m_entities[row+1] );
        long state = wxLIST_STATE_SELECTED;
        m_listEntities->SetItemState( row+1, state, state );
        m_listEntities->EnsureVisible( row+1 );
    }
}


void dlgEditReference::UpdateHtml()
{
    wxString htm;

    htm << "<html><head><title>" << m_reference.GetIdStr()
        << "</title></head><body>\n";

    if( m_reference.f_statement.compare( 0, 9, "<!-- HTML" ) == 0 ) {
        htm << m_reference.f_statement;
    } else { // treat as text
        htm << "<pre>"
            << m_reference.f_statement
            << "</pre>";
    }
    htm << "\n</body></html>";

    m_htmlView->SetPage( htm );
}

void dlgEditReference::InsertListItem( long row, const TfpEntity& ent )
{
    wxString str, idStr;
    switch( ent.rec.f_entity_type )
    {
    case recReferenceEntity::TYPE_Event:
        idStr = recEvent::GetIdStr( ent.rec.f_entity_id );
        str = recEvent::GetTitle( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Place:
        idStr = recPlace::GetIdStr( ent.rec.f_entity_id );
        str = recPlace::GetAddressStr( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Date:
        idStr = recDate::GetIdStr( ent.rec.f_entity_id );
        str = recDate::GetStr( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Relationship:
        idStr = recRelationship::GetIdStr( ent.rec.f_entity_id );
        str = recRelationship::GetValue1Str( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Name:
        idStr = recName::GetIdStr( ent.rec.f_entity_id );
        str = recName::GetNameStr( ent.rec.f_entity_id );
        break;
    default:
        str = _("Unknown entity type.");
    }
    TfpEntity entity = ent;
    m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
    m_listEntities->SetItem( row, ENT_COL_Number, idStr );
    m_listEntities->SetItem( row, ENT_COL_Value, str );
}

idt dlgEditReference::SelectCreatePersona()
{
    idt perID = 0;
    recIdVec list = m_reference.GetPersonaList();
    wxArrayString table;
    for( size_t i = 0 ; i < list.size() ; i++ ) {
        table.Add( wxString::Format( "Pa"ID, list[i] ) );
        table.Add( recPersona::GetNameStr( list[i] ) );
    }

    dlgSelectCreatePersona* dialog = 
        new dlgSelectCreatePersona( NULL, m_reference.f_id );
    dialog->SetTable( table );
    dialog->SetCreateButton();

    if( dialog->ShowModal() == wxID_OK ) {
        if( dialog->GetCreatePressed() == true ) {
            perID = dialog->GetPersonaID();
        } else {
            long row = dialog->GetSelectedRow();
            perID = list[row];
        }
    }

    dialog->Destroy();
    return perID;
}

bool dlgEditReference::SelectDate( 
    idt* dateID, const wxString& title, unsigned style )
{
    wxASSERT( dateID );  // Can't handle NULL pointer

    unsigned retButton;
    *dateID = rgSelectDate( style, &retButton, recD_FILTER_Reference, m_reference.FGetID() );
    if( retButton == rgSELSTYLE_Create ) {
        int row = m_entities.size();
        TfpEntity entity;
        entity.owner = 0;
        entity.index = -1;
        entity.rec.Clear();
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Date;
        entity.rec.f_entity_id = *dateID;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, ENT_COL_Number, recDate::GetIdStr( *dateID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recDate::GetStr( *dateID ) );
    }
    if( *dateID == 0 ) {
        if( retButton == rgSELSTYLE_Unknown ) {
            return true;
        }
        return false;
    }
    return true;
}

bool dlgEditReference::SelectPlace( 
    idt* placeID, const wxString& title, unsigned style )
{
    wxASSERT( placeID );  // Can't handle NULL pointer

    unsigned retButton;
    *placeID = rgSelectPlace( style, &retButton, recP_FILTER_Reference, m_reference.FGetID() );
    if( retButton == rgSELSTYLE_Create ) {
        int row = m_entities.size();
        TfpEntity entity;
        entity.owner = 0;
        entity.index = -1;
        entity.rec.Clear();
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Place;
        entity.rec.f_entity_id = *placeID;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, ENT_COL_Number, recPlace::GetIdStr( *placeID ) );
        m_listEntities->SetItem( row, ENT_COL_Value, recPlace::GetAddressStr( *placeID ) );
    }
    if( *placeID == 0 ) {
        if( retButton == rgSELSTYLE_Unknown ) {
            return true;
        }
        return false;
    }
    return true;
}

idt dlgEditReference::SelectName()
{
    idt nameID = 0;
    recIdVec names;
    wxArrayString table;
    for( size_t i = 0 ; i < m_entities.size() ; i++ ) {
        if( m_entities[i].rec.f_entity_type == recReferenceEntity::TYPE_Name ) {
            idt id = m_entities[i].rec.f_entity_id;
            names.push_back( id );
            table.Add( wxString::Format( "N"ID, id ) );
            table.Add( recName::GetNameStr( id ) );
        }
    }
    if( names.size() == 0 ) {
        return 0;
    }
    if( names.size() == 1 ) {
        return names[0];
    }

    dlgSelectName* dialog = new dlgSelectName( NULL );
    dialog->SetTable( table );

    if( dialog->ShowModal() == wxID_OK ) {
        long row = dialog->GetSelectedRow();
        nameID = names[row];
    }

    dialog->Destroy();
    return nameID;
}

TfpEntityStringVec dlgEditReference::GetDateEntityStringVec()
{
    TfpEntityString estr;
    TfpEntityStringVec list;
    for( size_t i = 0 ; i < m_entities.size() ; i++ ) {
        if( m_entities[i].rec.f_entity_type == recReferenceEntity::TYPE_Date ) {
            idt id = m_entities[i].rec.f_entity_id;
            estr.m_str = recDate::GetStr( id );
            estr.m_index = i;
            estr.m_id = id;
            list.push_back( estr );
        }
    }
    return list;
}


// End of dlgEdReference.cpp file
