/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Event entity dialog.
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

#include "dlgEdEvent.h"

#define ID_DATE_MENU_START  20000
#define ID_PLACE_MENU_START 21000
#define ID_ROLE_MENU_START  22000


IMPLEMENT_CLASS( dlgEditEvent, wxDialog )

BEGIN_EVENT_TABLE( dlgEditEvent, wxDialog )
    EVT_MENU_RANGE( ID_DATE_MENU_START, ID_DATE_MENU_START+100, dlgEditEvent::OnDateSelect )
    EVT_MENU_RANGE( ID_PLACE_MENU_START, ID_PLACE_MENU_START+100, dlgEditEvent::OnPlaceSelect )
END_EVENT_TABLE()


dlgEditEvent::dlgEditEvent( wxWindow* parent ) : fbDlgEditEvent( parent )
{
	m_listPersona->InsertColumn( 0, wxT("Persona") );
	m_listPersona->InsertColumn( 1, wxT("Role") );
	m_listPersona->InsertColumn( 2, wxT("Note") );
}

void dlgEditEvent::SetData( id_t typeID, id_t eventID )
{
    m_event.f_id = eventID;
    m_etype.f_id = typeID;
}

bool dlgEditEvent::TransferDataToWindow()
{
    if( m_event.f_id == 0 ) {
        m_event.Save();
        m_etype.Read();
        m_event.f_type_id = m_etype.f_id;
    } else {
        m_event.Read();
        m_etype.f_id = m_event.f_type_id;
        m_etype.Read();
    }

    m_staticType->SetLabel( m_etype.f_name );
    m_textCtrlTitle->SetValue( m_event.f_val );
    m_textCtrlDateBeg->SetValue( recDate::GetStr( m_event.f_date1_id ) );
    m_textCtrlDateEnd->SetValue( recDate::GetStr( m_event.f_date2_id ) );
    m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_event.f_place_id ) );

    m_pes = m_event.GetPersonaEvents();
    for( size_t i = 0 ; i < m_pes.size() ; i++ ) {
		m_listPersona->InsertItem( i, recPersona::GetFullName( m_pes[i].f_per_id ) );
		m_listPersona->SetItem( i, COL_Role, recEventTypeRole::GetName( m_pes[i].f_role_id ) );
		m_listPersona->SetItem( i, COL_Note, m_pes[i].f_note );
    }

    return true;
}

bool dlgEditEvent::TransferDataFromWindow()
{
    m_event.f_val = m_textCtrlTitle->GetValue();
    m_event.Save();

    return true;
}


void dlgEditEvent::OnDateBegButton( wxCommandEvent& event )
{
    DateSelectButton( EV_DATE_Beg );
}

void dlgEditEvent::OnDateEndButton( wxCommandEvent& event )
{
    DateSelectButton( EV_DATE_End );
}

void dlgEditEvent::DateSelectButton( EvDate button )
{
    m_dateButton = button;
    wxMenu* dmenu = new wxMenu;
    size_t m = 0;
    dmenu->Append( ID_DATE_MENU_START + m++, wxT("Create new") );
    for( size_t i = 0 ; i < mp_entities->size() ; i++ ) {
        if( (*mp_entities)[i].rec.f_entity_type == recReferenceEntity::TYPE_Date ) {
            dmenu->Append(
                ID_DATE_MENU_START + m,
                recDate::GetStr( (*mp_entities)[i].rec.f_entity_id )
            );
            (*mp_entities)[i].index = m;
            m++;
        } else {
            (*mp_entities)[i].index = -1;
        }
    }
    PopupMenu( dmenu );
    delete dmenu;
}

void dlgEditEvent::OnDateSelect( wxCommandEvent& event )
{
    size_t i = event.GetId() - ID_DATE_MENU_START;
    wxTextCtrl* textCtrlDate = 
		( m_dateButton == EV_DATE_Beg ) ? m_textCtrlDateBeg : m_textCtrlDateEnd;

	if( i == 0 ) {
        textCtrlDate->SetValue( wxT("TODO: Get New Date") );
    } else {
        int entry = tfpGetEntityIndex( mp_entities, i );
        id_t dateID = (*mp_entities)[entry].rec.f_entity_id;
        textCtrlDate->SetValue( recDate::GetStr( dateID ) );

        if( m_dateButton == EV_DATE_Beg ) {
            m_event.f_date1_id = dateID;
        } else {
            m_event.f_date2_id = dateID;
        }
    }
}

void dlgEditEvent::OnPlaceButton( wxCommandEvent& event )
{
    wxMenu* pmenu = new wxMenu;
    size_t m = 0;
    pmenu->Append( ID_PLACE_MENU_START + m++, wxT("Create new") );
    for( size_t i = 0 ; i < mp_entities->size() ; i++ ) {
        if( (*mp_entities)[i].rec.f_entity_type == recReferenceEntity::TYPE_Place ) {
            pmenu->Append(
                ID_PLACE_MENU_START + m,
                recPlace::GetAddressStr( (*mp_entities)[i].rec.f_entity_id )
            );
            (*mp_entities)[i].index = m;
            m++;
        } else {
            (*mp_entities)[i].index = -1;
        }
    }
    PopupMenu( pmenu );
    delete pmenu;
}

void dlgEditEvent::OnPlaceSelect( wxCommandEvent& event )
{
    size_t i = event.GetId() - ID_PLACE_MENU_START;

    if( i == 0 )
    {
        m_textCtrlPlace->SetValue( wxT("TODO: Get New Place") );
    } else {
        int entry = tfpGetEntityIndex( mp_entities, i );
        id_t placeID = (*mp_entities)[entry].rec.f_entity_id;
        m_textCtrlPlace->SetValue( recPlace::GetAddressStr( placeID ) );
        m_event.f_place_id = placeID;
    }
}

void dlgEditEvent::OnAddButton( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented\nDate"), 
		wxT("OnEditButton")
	);
#if 0
    recEventTypeRole role;
    role.Clear();

    RoleEntryDlg* dialog = new RoleEntryDlg( NULL );
    dialog->SetData( m_event.id );
    dialog->SetEventType( &m_etype );
    dialog->SetEntities( mp_entities );

    if( dialog->ShowModal() == wxID_OK )
    {
        recPersonaEvent* pe = dialog->GetPersonaEvent();
        pe->Save();
        int row = m_pes.size();
		m_listPersona->InsertItem( row, RecPersona::GetName( pe->per_id ) );
		m_listPersona->SetItem( row, COL_Role, recEventTypeRole::GetName( pe->role_id ) );
		m_listPersona->SetItem( row, COL_Note, pe->note );
        m_pes.push_back( *pe );
    }
    dialog->Destroy();
#endif
}

void dlgEditEvent::OnEditButton( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented\nDate"), 
		wxT("OnEditButton")
	);
	// TODO: Implement OnEditButton
}

void dlgEditEvent::OnDeleteButton( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented\nDate"), 
		wxT("OnDeleteButton")
	);
	// TODO: Implement OnDeleteButton
}

void dlgEditEvent::OnUpButton( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented\nDate"), 
		wxT("OnUpButton")
	);
	// TODO: Implement OnUpButton
}

void dlgEditEvent::OnDownButton( wxCommandEvent& event )
{
	wxMessageBox( 
		wxT("Not yet implimented\nDate"), 
		wxT("OnDownButton")
	);
	// TODO: Implement OnDownButton
}

// End of dlgEdEvent.cpp file
