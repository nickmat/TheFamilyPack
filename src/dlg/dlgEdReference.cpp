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

//WX_DEFINE_OBJARRAY( TfpEntities );

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
    EVT_MENU( ID_EDREF_NEW_PER,    dlgEditReference::OnNewPersona )
    EVT_MENU( ID_EDREF_NEW_ATTR,   dlgEditReference::OnNewAttribute )
    EVT_MENU( ID_EDREF_NEW_ROLE,   dlgEditReference::OnNewRole )
END_EVENT_TABLE()

dlgEditReference::dlgEditReference( wxWindow* parent )
    : fbDlgEditReference( parent )
{
	m_listEntities->InsertColumn( COL_Type, wxT("Type") );
	m_listEntities->InsertColumn( COL_Value, wxT("Value") );
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
    m_textCtrl12->SetValue(  m_reference.f_statement );

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
            m_listEntities->SetItem( i, COL_Value, recEvent::GetValue( entID ) );
            break;
        default:
	        m_listEntities->SetItem( i, COL_Value, wxT("Unknown Reference Entity") );
        }
    }
    return true;
}

bool dlgEditReference::TransferDataFromWindow()
{
    m_reference.f_title = m_textCtrlTitle->GetValue();
    m_reference.f_statement = m_textCtrl12->GetValue();

    m_reference.Save();
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
//    case tfpID_EDREF_OnBold:      DoBold();      break;
//    case tfpID_EDREF_OnItalic:    DoItalic();    break;
//    case tfpID_EDREF_OnUnderline: DoUnderline(); break;
//    case tfpID_EDREF_OnFont:      DoFont();      break;
    }
}

void dlgEditReference::OnAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_EDREF_NEW_SOURCE, wxT("&Source") );
    menu->Append( ID_EDREF_NEW_EVENT, wxT("&Event") );
    menu->Append( ID_EDREF_NEW_PLACE, wxT("P&lace") );
    menu->Append( ID_EDREF_NEW_DATE, wxT("&Date") );
    menu->Append( ID_EDREF_NEW_PER, wxT("&Persona") );
    menu->Append( ID_EDREF_NEW_ATTR, wxT("&Attribute") );
    menu->Append( ID_EDREF_NEW_ROLE, wxT("&Role") );
    PopupMenu( menu );
    delete menu;
}

void dlgEditReference::OnEditButton( wxCommandEvent& event )
{
	long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( wxT("No row selected"), wxT("Edit Entity") );
        return;
    }
    id_t id = m_entities[row].rec.f_entity_id;
    switch( m_entities[row].rec.f_entity_type )
    {
    case recReferenceEntity::TYPE_Date:      DoEditDate( id, row );      break;
    case recReferenceEntity::TYPE_Place:     DoEditPlace( id, row );     break;
    case recReferenceEntity::TYPE_Persona:   DoEditPersona( id, row );   break;
    case recReferenceEntity::TYPE_Attribute: DoEditAttribute( id, row ); break;
    case recReferenceEntity::TYPE_Event:     DoEditEvent( id, row );     break;
    default:
        wxMessageBox( _("Element cannot be edited"), _("Edit") );
        return;
    }
}

void dlgEditReference::OnDeleteButton( wxCommandEvent& event )
{
	long row = m_listEntities->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( wxT("No row selected"), wxT("Edit Entity") );
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
        wxMessageBox( wxT("Element cannot be deleted"), wxT("Delete") );
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
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("OnUpButton")
	);
	// TODO: Implement OnUpButton
#if 0
    wxArrayInt rows = m_grid->GetSelectedRows();
    if( rows.GetCount() != 1 )
    {
        wxMessageBox( wxT("Single row not selected"), wxT("OnUpButton") );
        return;
    }
    int row = rows[0];
    EntGridTable* table = (EntGridTable*) m_grid->GetTable();
    table->MoveRowUp( row );
    if( row != 0 )
    {
        m_grid->SelectRow( row - 1 );
        m_grid->MakeCellVisible( row - 1, 0 );
    }
#endif
}

void dlgEditReference::OnDownButton( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("OnDownButton")
	);
	// TODO: Implement OnDownButton
#if 0
    wxArrayInt rows = m_grid->GetSelectedRows();
    if( rows.GetCount() != 1 )
    {
        wxMessageBox( wxT("Single row not selected"), wxT("OnUpButton") );
        return;
    }
    int row = rows[0];
    EntGridTable* table = (EntGridTable*) m_grid->GetTable();
    table->MoveRowDown( row );
    if( row != table->GetNumberRows() - 1 )
    {
        m_grid->SelectRow( row + 1 );
        m_grid->MakeCellVisible( row + 1, 0 );
    }
#endif
}


void dlgEditReference::DoCut()
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("DoCut")
	);
	// TODO: Implement DoCut
}

void dlgEditReference::DoCopy()
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("DoCopy")
	);
	// TODO: Implement DoCopy
}

void dlgEditReference::DoPaste()
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("DoPaste")
	);
	// TODO: Implement DoPaste
}

void dlgEditReference::DoUndo()
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("DoUndo")
	);
	// TODO: Implement DoUndo
}

void dlgEditReference::DoRedo()
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("DoRedo")
	);
	// TODO: Implement DoRedo
}

void dlgEditReference::OnNewSource( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("OnNewSource")
	);
}

void dlgEditReference::OnNewEvent( wxCommandEvent& cmnd_event )
{
    const wxString savepoint = "RefEvent";
    id_t type = recEventType::Select();
    if( type == 0 ) return;

    dlgEditEvent* dialog = new dlgEditEvent( NULL );

    dialog->SetData( type );
    dialog->GetEvent()->f_val = m_textCtrl12->GetStringSelection();
    dialog->SetEntities( &m_entities );

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
        m_listEntities->SetItem( row, COL_Value, dialog->GetEvent()->f_val );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditReference::OnNewRole( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("OnNewRole")
	);
}

void dlgEditReference::OnNewPlace( wxCommandEvent& event )
{
	wxMessageBox( 
		"Not yet implimented",
		"OnNewDate"
	);
#if 0
    const wxString savepoint = "RefPlace";
    PlaceEntryDlg* dialog = new PlaceEntryDlg( NULL );

    dialog->SetData();
    dialog->SetText( m_textCtrl12->GetStringSelection() );

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
#endif
}

void dlgEditReference::OnNewDate( wxCommandEvent& event )
{
	wxMessageBox( 
		"Not yet implimented",
		"OnNewDate"
	);
#if 0
    const wxString savepoint = "RefDate";
    DateEntryDlg* dialog = new DateEntryDlg( NULL );

    dialog->SetID( 0 );
    dialog->SetText( m_textCtrl12->GetStringSelection() );

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
#endif
}

void dlgEditReference::OnNewPersona( wxCommandEvent& event )
{
	wxMessageBox( 
		"Not yet implimented",
		"OnNewPersona"
	);
#if 0
    const wxString savepoint = "RefPer";
    dlgEditPersona* dialog = new dlgEditPersona( NULL );

    dialog->SetData();
    dialog->SetDefault( m_textCtrl12->GetStringSelection() );

    recDb::Savepoint( savepoint );
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
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditReference::OnNewAttribute( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("OnNewAttribute")
	);
}

void dlgEditReference::DoEditDate( id_t id, long row )
{
	wxMessageBox( 
		"Not yet implimented",
		"DoEditDate"
	);
#if 0
    const wxString savepoint = "RefEdDate";
    DateEntryDlg* dialog = new DateEntryDlg( NULL );

    dialog->SetID( id );
    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetDate()->GetStr() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditReference::DoEditPlace( id_t id, long row )
{
	wxMessageBox( 
		"Not yet implimented",
		"DoEditPlace"
	);
#if 0
    const wxString savepoint = "RefEdPlace";
    PlaceEntryDlg* dialog = new PlaceEntryDlg( NULL );

    dialog->SetData( id );
    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetPlace()->GetAddressStr() );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditReference::DoEditPersona( id_t id, long row )
{
	wxMessageBox( 
		wxT("Not yet implimented"), 
		wxT("DoEditPersona")
	);
#if 0
    const wxString savepoint = wxT("RefEdPer");
    RecAttribute attr;
    size_t i = 0;

    DlgEditPersona* dialog = new DlgEditPersona( NULL );
    dialog->SetData( id );
    g_db->Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        g_db->ReleaseSavepoint( savepoint );
        // remove the attributes
        while( i < m_entities.GetCount() )  {
            if( m_entities[i].rec.entity_type == RecReferenceEntity::TYPE_Attribute
                && m_entities[i].owner == id )
            {
				m_entities[i].rec.Delete();
                m_entities.Detach( i );
                m_grid->DeleteRows( i );
                if( i < row ) --row;
            } else {
                i++;
            }
        }
        // Put the Attributes back
        ArrAttribute attrs = dialog->GetAttributes();
        for( i = 0 ; i < attrs.GetCount() ; i++ ) {
            row++;
            m_grid->InsertRows( row );
            m_grid->SetCellValue( row, COL_Type,
                RecReferenceEntity::sm_typeStr[RecReferenceEntity::TYPE_Attribute] );
            m_grid->SetCellValue( row, COL_Value, attrs[i].val );

            Entity entity;
            entity.rec.Clear();
            entity.owner = id;
            entity.rec.ref_id = m_reference.id;
            entity.rec.entity_type = RecReferenceEntity::TYPE_Attribute;
            entity.rec.entity_id = attrs[i].id;
            entity.rec.Save();
            m_entities.Add( entity );
        }
    } else {
        g_db->Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditReference::DoEditAttribute( id_t id, long row )
{
	wxMessageBox( 
		"Not yet implimented",
		"DoEditAttribute"
	);
#if 0
    const wxString savepoint = "RefEdAttr";
    AttrEntryDlg* dialog = new AttrEntryDlg( NULL );
    recAttribute attr;

    attr.Clear();
    attr.f_id = id;
    attr.Read();
    dialog->SetAttribute( &attr );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        attr.Save();
        m_listEntities->SetItem( row, COL_Value, attr.f_val );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditReference::DoEditEvent( id_t id, long row )
{
    const wxString savepoint = "RefEdEvent";
    dlgEditEvent* dialog = new dlgEditEvent( NULL );

    dialog->SetData( 0, id );
    dialog->SetEntities( &m_entities );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        m_listEntities->SetItem( row, COL_Value, dialog->GetEvent()->f_val );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

// End of dlgEdReference.cpp file
