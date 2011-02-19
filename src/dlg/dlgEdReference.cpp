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

#include "dlgEdReference.h"
#include "dlgEdEvent.h"
#include "dlgEdPersona.h"
#include "dlgEdPlace.h"
#include "dlgEdDate.h"
#include "dlgEdName.h"
#include "dlgEdAttribute.h"
#include "dlgSelect.h"


int tfpGetEntityIndex( TfpEntities* array, int ind )
{
    for( size_t i = 0 ; i < array->size() ; i++ ) {
        if( (*array)[i].index == ind ) return i;
    }
    return -1;
}

BEGIN_EVENT_TABLE( dlgEditReference, wxDialog )
    EVT_MENU( ID_EDREF_NEW_SOURCE, dlgEditReference::OnNewSource )
    EVT_MENU( ID_EDREF_NEW_EVENT,  dlgEditReference::OnNewEvent )
    EVT_MENU( ID_EDREF_NEW_PLACE,  dlgEditReference::OnNewPlace )
    EVT_MENU( ID_EDREF_NEW_DATE,   dlgEditReference::OnNewDate )
    EVT_MENU( ID_EDREF_NEW_NAME,   dlgEditReference::OnNewName )
    EVT_MENU( ID_EDREF_NEW_PER,    dlgEditReference::OnNewPersona )
    EVT_MENU( ID_EDREF_NEW_ATTR,   dlgEditReference::OnNewAttribute )
END_EVENT_TABLE()

dlgEditReference::dlgEditReference( wxWindow* parent )
    : fbDlgEditReference( parent )
{
    m_listEntities->InsertColumn( COL_Type, _("Type") );
    m_listEntities->InsertColumn( COL_Value, _("Value") );
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

    recRefEntVec  evid_ents;
    evid_ents = m_reference.ReadReferenceEntitys();
    for( size_t i = 0 ; i < evid_ents.size() ; i++ )
    {
        TfpEntity entity;
        entity.rec = evid_ents[i];
        id_t entID = entity.rec.f_entity_id;
        entity.owner = 0;
        m_entities.push_back( entity );
        m_listEntities->InsertItem( i, entity.rec.GetTypeStr() );
        switch( entity.rec.f_entity_type )
        {
        case recReferenceEntity::TYPE_Date:
            m_listEntities->SetItem( i, COL_Value, recDate::GetStr( entID ) );
            break;
        case recReferenceEntity::TYPE_Name:
            m_listEntities->SetItem( i, COL_Value, recName::GetFullName( entID ) );
            break;
        case recReferenceEntity::TYPE_Place:
            m_listEntities->SetItem( i, COL_Value, recPlace::GetAddressStr( entID ) );
            break;
        case recReferenceEntity::TYPE_Persona:
            m_listEntities->SetItem( i, COL_Value, recPersona::GetFullName( entID ) );
            break;
        case recReferenceEntity::TYPE_Attribute:
            {
                recAttribute attribute( entID );
                m_listEntities->SetItem( i, COL_Value, attribute.f_val );
                m_entities[i].owner = attribute.f_per_id;
            }
            break;
        case recReferenceEntity::TYPE_Event:
            m_listEntities->SetItem( i, COL_Value, recEvent::GetTitle( entID ) );
            break;
        default:
            m_listEntities->SetItem( i, COL_Value, _("Unknown Reference Entity") );
        }
    }
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

void dlgEditReference::OnAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_EDREF_NEW_SOURCE, _("&Source") );
    menu->Append( ID_EDREF_NEW_DATE, _("&Date") );
    menu->Append( ID_EDREF_NEW_PLACE, _("P&lace") );
    menu->Append( ID_EDREF_NEW_PER, _("&Persona") );
    menu->Append( ID_EDREF_NEW_EVENT, _("&Event") );
    menu->Append( ID_EDREF_NEW_ATTR, _("&Attribute") );
    menu->Append( ID_EDREF_NEW_NAME, _("&Name") );
    PopupMenu( menu );
    delete menu;
}

void dlgEditReference::OnNewSource( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnNewSource")
    );
}

void dlgEditReference::OnNewDate( wxCommandEvent& event )
{
    const wxString savepoint = "RefDate";
    dlgEditDate* dialog = new dlgEditDate( NULL );

    dialog->SetText( m_textCtrlStatement->GetStringSelection() );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Date;
        entity.rec.f_entity_id = dialog->GetDate()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, COL_Value, dialog->GetDate()->GetStr() );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewPlace( wxCommandEvent& event )
{
    const wxString savepoint = "RefPlace";
    dlgEditPlace* dialog = new dlgEditPlace( NULL );

    dialog->SetText( m_textCtrlStatement->GetStringSelection() );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Place;
        entity.rec.f_entity_id = dialog->GetPlace()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, COL_Value, dialog->GetPlace()->GetAddressStr() );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewPersona( wxCommandEvent& event )
{
    wxString nameStr = m_textCtrlStatement->GetStringSelection();
    const wxString savepoint = "RefPer";
    recDb::Savepoint( savepoint );
    recPersona persona(0);
    persona.Save();
    recName name(0);
    name.f_per_id = persona.f_id;
    name.Save();
    name.AddNameParts( nameStr );
    persona.f_name_id = name.f_id;
    persona.Save();

    dlgEditPersona* dialog = new dlgEditPersona( NULL );
    dialog->SetPersonaID( persona.f_id );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Persona;
        entity.rec.f_entity_id = dialog->GetPersona()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, COL_Value, dialog->GetPersona()->GetFullName() );
#if 0
//    dialog->SetData();
//    dialog->SetDefault( m_textCtrlStatement->GetStringSelection() );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Persona;
        entity.rec.f_entity_id = dialog->GetPersona()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, COL_Value, dialog->GetPersona()->GetFullName() );

        // Add attributes
        entity.owner = entity.rec.f_entity_id;
        recAttributeList aa = dialog->GetAttributes();
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Attribute;
        row++;
        for( size_t i = 0 ; i < aa.size() ; i++ ) {
            entity.rec.f_id = 0;
            entity.rec.f_entity_id = aa[i].f_id;
            entity.rec.Save();
            m_entities.push_back( entity );

            m_listEntities->InsertItem( row+i, entity.rec.GetTypeStr() );
            m_listEntities->SetItem( row+i, COL_Value, aa[i].f_val );
        }
#endif
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewEvent( wxCommandEvent& cmnd_event )
{
    const wxString savepoint = "RefEvent";
    id_t type = recEventType::Select();
    if( type == 0 ) return;

    dlgEditEvent* dialog = new dlgEditEvent( NULL );

    dialog->SetData( type );
    dialog->GetEvent()->f_title = m_textCtrlStatement->GetStringSelection();
    dialog->SetEntities( &m_entities );
    dialog->SetDateStrings( GetDateEntityStringVec() );

    recDb::Savepoint( savepoint );
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
        m_listEntities->SetItem( row, COL_Value, dialog->GetEvent()->f_title );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewAttribute( wxCommandEvent& event )
{
    id_t perID = SelectPersona();
    if( perID == 0 ) {
        return;
    }
    const wxString savepoint = "RefAttr";
    recDb::Savepoint( savepoint );

    dlgEditAttribute* dialog = new dlgEditAttribute( NULL );
    dialog->SetPersonaID( perID );
    dialog->SetValue( m_textCtrlStatement->GetStringSelection() );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Attribute;
        entity.rec.f_entity_id = dialog->GetAttribute()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, COL_Value, dialog->GetAttribute()->f_val );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewName( wxCommandEvent& event )
{
    id_t perID = SelectPersona();
    if( perID == 0 ) {
        return;
    }

    const wxString savepoint = "RefName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetPersonaID( perID );
    dialog->CreateName( m_textCtrlStatement->GetStringSelection() );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        int row = m_entities.size();
        TfpEntity entity;
        entity.rec.Clear();
        entity.owner = 0;
        entity.rec.f_ref_id = m_reference.f_id;
        entity.rec.f_entity_type = recReferenceEntity::TYPE_Name;
        entity.rec.f_entity_id = dialog->GetName()->f_id;
        entity.rec.Save();
        m_entities.push_back( entity );

        m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
        m_listEntities->SetItem( row, COL_Value, dialog->GetName()->GetFullName() );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnEditButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    id_t id = m_entities[row].rec.f_entity_id;
    switch( m_entities[row].rec.f_entity_type )
    {
    case recReferenceEntity::TYPE_Date:      DoEditDate( id, row );      break;
    case recReferenceEntity::TYPE_Place:     DoEditPlace( id, row );     break;
    case recReferenceEntity::TYPE_Persona:   DoEditPersona( id, row );   break;
    case recReferenceEntity::TYPE_Event:     DoEditEvent( id, row );     break;
    case recReferenceEntity::TYPE_Attribute: DoEditAttribute( id, row ); break;
    case recReferenceEntity::TYPE_Name :     DoEditName( id, row );      break;
    default:
        wxMessageBox( _("Element cannot be edited"), _("Edit") );
        return;
    }
}

void dlgEditReference::DoEditDate( id_t id, long row )
{
    const wxString savepoint = "RefEdDate";
    dlgEditDate* dialog = new dlgEditDate( NULL, id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetDate()->GetStr() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditPlace( id_t id, long row )
{
    const wxString savepoint = "RefEdPlace";
    dlgEditPlace* dialog = new dlgEditPlace( NULL, id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetPlace()->GetAddressStr() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditPersona( id_t id, long row )
{
    const wxString savepoint = "RefEdPer";
    recAttribute attr;
    size_t i = 0;

    dlgEditPersona* dialog = new dlgEditPersona( NULL );
    dialog->SetPersonaID( id );
    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetPersona()->GetFullName() );
#if 0
        // remove the attributes
        while( i < m_entities.size() )  {
            if( m_entities[i].rec.f_entity_type == recReferenceEntity::TYPE_Attribute
                && m_entities[i].owner == id )
            {
                m_entities[i].rec.Delete();
                m_entities.erase( m_entities.begin() + i );
                m_listEntities->DeleteItem( i );
                if( (long) i < row ) --row;
            } else {
                i++;
            }
        }
        // Put the Attributes back
        recAttributeList attrs = dialog->GetAttributes();
        for( i = 0 ; i < attrs.size() ; i++ ) {
            row++;

            TfpEntity entity;
            entity.rec.Clear();
            entity.owner = id;
            entity.rec.f_ref_id = m_reference.f_id;
            entity.rec.f_entity_type = recReferenceEntity::TYPE_Attribute;
            entity.rec.f_entity_id = attrs[i].f_id;
            entity.rec.Save();
            m_entities.insert( m_entities.begin()+row, entity );

            m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
            m_listEntities->SetItem( row, COL_Value, attrs[i].f_val );
        }
#endif
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditEvent( id_t id, long row )
{
    const wxString savepoint = "RefEdEvent";
    dlgEditEvent* dialog = new dlgEditEvent( NULL );

    dialog->SetData( 0, id );
    dialog->SetEntities( &m_entities );
    dialog->SetDateStrings( GetDateEntityStringVec() );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetEvent()->f_title );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditAttribute( id_t id, long row )
{
    const wxString savepoint = "RefEdAttr";
    dlgEditAttribute* dialog = new dlgEditAttribute( NULL );
    dialog->SetAttributeID( id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetAttribute()->f_val );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::DoEditName( id_t id, long row )
{
    const wxString savepoint = "RefEdName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetData( id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetName()->GetFullName() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnDeleteButton( wxCommandEvent& event )
{
    long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Entity") );
        return;
    }
    id_t reID = m_entities[row].rec.f_id;
    id_t entID = m_entities[row].rec.f_entity_id;
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
    case recReferenceEntity::TYPE_Persona:
        {
            recAttributeList arrAttr = recPersona::ReadAttributes( entID );
            for( size_t i = 0 ; i < arrAttr.size() ; i++ ) {
                arrAttr[i].Delete();
            }
            recPersona::Delete( entID );
            recReferenceEntity::Delete( reID );
        }
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

void dlgEditReference::InsertListItem( long row, const TfpEntity& ent )
{
    wxString str;
    switch( ent.rec.f_entity_type )
    {
    case recReferenceEntity::TYPE_Event:
        str = recEvent::GetTitle( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Place:
        str = recPlace::GetAddressStr( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Date:
        str = recDate::GetStr( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Persona:
        str = recPersona::GetFullName( ent.rec.f_entity_id );
        break;
    case recReferenceEntity::TYPE_Attribute:
        str = recAttribute::GetValue( ent.rec.f_entity_id );
        break;
    default:
        str = _("Unknown entity type.");
    }
    TfpEntity entity = ent;
    m_listEntities->InsertItem( row, entity.rec.GetTypeStr() );
    m_listEntities->SetItem( row, COL_Value, str );
}

id_t dlgEditReference::SelectPersona()
{
    id_t perID = 0;
    recIdVec list;
    wxArrayString table;
    for( size_t i = 0 ; i < m_entities.size() ; i++ ) {
        if( m_entities[i].rec.f_entity_type == recReferenceEntity::TYPE_Persona ) {
            id_t id = m_entities[i].rec.f_entity_id;
            list.push_back( id );
            table.Add( wxString::Format( "Pa"ID, id ) );
            table.Add( recPersona::GetFullName( id ) );
        }
    }
    if( list.size() == 0 ) {
        return 0;
    }
    if( list.size() == 1 ) {
        return list[0];
    }

    dlgSelectPersona* dialog = new dlgSelectPersona( NULL );
    dialog->SetTable( table );

    if( dialog->ShowModal() == wxID_OK ) {
        long row = dialog->GetSelectedRow();
        perID = list[row];
    }

    dialog->Destroy();
    return perID;
}

id_t dlgEditReference::SelectName()
{
    id_t nameID = 0;
    recIdVec names;
    wxArrayString table;
    for( size_t i = 0 ; i < m_entities.size() ; i++ ) {
        if( m_entities[i].rec.f_entity_type == recReferenceEntity::TYPE_Name ) {
            id_t id = m_entities[i].rec.f_entity_id;
            names.push_back( id );
            table.Add( wxString::Format( "N"ID, id ) );
            table.Add( recName::GetFullName( id ) );
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
            estr.m_str = recDate::GetStr( m_entities[i].rec.f_entity_id );
            estr.m_index = i;
            list.push_back( estr );
        }
    }
    return list;
}


// End of dlgEdReference.cpp file
