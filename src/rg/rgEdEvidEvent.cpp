/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEvidEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Event entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25th February 2013
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

#include "rg/rgDialogs.h"
#include "rgEdEvidEvent.h"
#include "rgEdReference.h"

#if 0
bool rgEditEvidEvent( dlgEditReference* parent, idt eveID )
{
    wxASSERT( eveID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEvidEvent* dialog = new rgDlgEditEvidEvent( parent, eveID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
    return 0;
}
#endif

bool rgEditEvidEvent( rgDlgEditReference* parent, idt eveID )
{
    wxASSERT( eveID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEvidEvent* dialog = new rgDlgEditEvidEvent( parent, eveID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateEvidEvent( rgDlgEditReference* parent )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt typeID = rgSelectEventType( parent );
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
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
    unsigned style = rgSELSTYLE_Create | rgSELSTYLE_Unknown;
    if( parent->SelectDate( &dateID1, _("Select Start Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    idt dateID2 = 0;
    if( enddate ) {
        if( parent->SelectDate( &dateID2, _("Select End Date"), style ) == false ) {
            recDb::Rollback( savepoint );
            return 0;
        }
    }
    idt placeID;
    if( parent->SelectPlace( &placeID, _("Select Place"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    idt perID1 = parent->SelectCreatePersona();
    if( perID1 == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    wxString title;
    idt perID2 = 0;
    if( person2 ) {
        perID2 = parent->SelectCreatePersona();
        if( perID2 == 0 ) {
            recDb::Rollback( savepoint );
            return 0;
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

    recEvent e(0);
    e.FSetTitle( title );
    e.FSetTypeID( typeID );
    e.FSetDate1ID( dateID1 );
    e.FSetDate2ID( dateID2 );
    e.FSetPlaceID( placeID );
    e.Save();
    idt eveID = e.FGetID();

    recEventPersona ep1(0);
    ep1.FSetEventID( eveID );
    ep1.FSetPerID( perID1 );
    ep1.FSetRoleID( role1 );
    ep1.FSetPerSeq( 1 );
    ep1.Save();
    if( person2 ) {
        recEventPersona ep2(0);
        ep2.FSetEventID( eveID );
        ep2.FSetPerID( perID2 );
        ep2.FSetRoleID( role2 );
        ep2.FSetPerSeq( 2 );
        ep2.Save();
    }
    if( rgEditEvidEvent( parent, eveID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        eveID = 0;
    }
    return eveID;
}

idt rgCreateEvidPerEvent( rgDlgEditReference* wind, const wxString& role )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = wind->SelectCreatePersona();
    if( perID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    idt eveTypeID = rgSelectEventType( wind, rgSELSTYLE_Create, NULL, recET_FILTER_GrpPersonal );
    if( eveTypeID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    wxString title = wxString::Format(
        _("%s of %s"),
        recEventType::GetTypeStr( eveTypeID ), recPersona::GetNameStr( perID ) 
    );

    idt date1ID, date2ID;
    unsigned style = rgSELSTYLE_Create | rgSELSTYLE_Unknown;
    if( wind->SelectDate( &date1ID, _("Select Start Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    if( wind->SelectDate( &date2ID, _("Select End Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    if( date1ID == date2ID ) {
        date2ID = 0;
    }
    idt placeID;
    if( wind->SelectPlace( &placeID, _("Select Place"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    idt roleID = 0;
    wxString note;
    if( role.size() ) {
        roleID = recEventTypeRole::Find( role, eveTypeID, recEventTypeRole::PRIME_First );
        if( roleID == 0 ) {
            note << "Stated as: " << role;
        }
    }

    recEvent eve(0);
    eve.FSetTitle( title );
    eve.FSetTypeID( eveTypeID );
    eve.FSetDate1ID( date1ID );
    eve.FSetDate2ID( date2ID );
    eve.FSetPlaceID( placeID );
    eve.FSetDatePt( recDate::DATE_POINT_Mid );
    eve.Save();
    idt eveID = eve.FGetID();

    recEventPersona ep(0);
    ep.FSetEventID( eveID );
    ep.FSetPerID( perID );
    ep.FSetRoleID( roleID );
    ep.FSetNote( note );
    ep.FSetPerSeq( 1 );
    ep.Save();

    if( rgEditPerEventRole( wind, ep.FGetID() ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        eveID = 0;
    }
    return eveID;
}

//============================================================================
//-------------------------[ rgDlgEditEvidEvent ]-----------------------------
//============================================================================

void rgDlgEditEvidEvent::ListLinkedPersona()
{
    m_eps = m_event.GetEventPersonas();
    m_personas.clear();
    recPersona per;
    m_listPersona->DeleteAllItems();
    for( size_t i = 0 ; i < m_eps.size() ; i++ ) {
        per.ReadID( m_eps[i].FGetPerID() );
        m_personas.push_back( per );
        m_listPersona->InsertItem( i, per.GetIdStr() );
        m_listPersona->SetItem( i, COL_Name, per.GetNameStr() );
        m_listPersona->SetItem( i, COL_Role, recEventTypeRole::GetName( m_eps[i].FGetRoleID() ) );
        m_listPersona->SetItem( i, COL_Note, m_eps[i].FGetNote() );
    }
}

void rgDlgEditEvidEvent::OnAddButton( wxCommandEvent& event )
{
    idt perID = m_refDialog->SelectCreatePersona();
    if( perID == 0 ) {
        return;
    }
    if( rgCreatePerEventRole( this, perID, m_event.FGetID(), 0 ) ) {
        ListLinkedPersona();
    }
}

void rgDlgEditEvidEvent::EditRow( long row )
{
    idt epID = m_eps[row].FGetID();
    if( rgEditPerEventRole( this, epID ) ) {
        ListLinkedPersona();
    }
}

void rgDlgEditEvidEvent::DeleteRow( long row )
{
    idt epID = m_eps[row].FGetID();
    int ans = wxMessageBox( 
        _("Remove the link between the Persona and this Event from database?"),
        _("Delete Link"),
        wxYES_NO | wxCANCEL, this
    );
    if( ans != wxYES ) {
        return;
    }
    recEventPersona::Delete( epID );
    ListLinkedPersona();
}

#if 0
#define ID_DATE_MENU_START  20000
#define ID_AGE_MENU_START  20500
#define ID_PLACE_MENU_START 21000
#define ID_ROLE_MENU_START  22000


IMPLEMENT_CLASS( dlgEditEvent, wxDialog )

BEGIN_EVENT_TABLE( dlgEditEvent, wxDialog )
    EVT_MENU_RANGE( ID_DATE_MENU_START, ID_DATE_MENU_START+100, dlgEditEvent::OnDateSelect )
    EVT_MENU_RANGE( ID_AGE_MENU_START, ID_AGE_MENU_START+100, dlgEditEvent::OnAgeSelect )
    EVT_MENU_RANGE( ID_PLACE_MENU_START, ID_PLACE_MENU_START+100, dlgEditEvent::OnPlaceSelect )
END_EVENT_TABLE()


dlgEditEvent::dlgEditEvent( wxWindow* parent ) 
    : mp_entities(NULL), m_refID(0), m_dateButton(EV_DATE_Beg), fbDlgEditEvent( parent )
{
    m_event.Clear();
    m_etype.Clear();

    m_listPersona->InsertColumn( 0, wxT("Persona") );
    m_listPersona->InsertColumn( 1, wxT("Role") );
    m_listPersona->InsertColumn( 2, wxT("Note") );
}

void dlgEditEvent::SetData( idt typeID, idt eventID )
{
    m_event.f_id = eventID;
    m_etype.f_id = typeID;
}

bool dlgEditEvent::TransferDataToWindow()
{
    if( m_event.f_id == 0 ) {
        m_etype.Read();
        m_event.f_type_id = m_etype.f_id;
        m_event.Save();
    } else {
        m_event.Read();
        m_etype.f_id = m_event.f_type_id;
        m_etype.Read();
    }

    m_staticType->SetLabel( m_etype.f_name );
    m_textCtrlTitle->SetValue( m_event.f_title );
    m_textCtrlDateBeg->SetValue( recDate::GetStr( m_event.f_date1_id ) );
    m_textCtrlDateEnd->SetValue( recDate::GetStr( m_event.f_date2_id ) );
    m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_event.f_place_id ) );

    m_pes = m_event.GetEventPersonas();
    for( size_t i = 0 ; i < m_pes.size() ; i++ ) {
        m_listPersona->InsertItem( i, recPersona::GetNameStr( m_pes[i].f_per_id ) );
        m_listPersona->SetItem( i, COL_Role, recEventTypeRole::GetName( m_pes[i].f_role_id ) );
        m_listPersona->SetItem( i, COL_Note, m_pes[i].f_note );
    }

    return true;
}

bool dlgEditEvent::TransferDataFromWindow()
{
    m_event.f_title = m_textCtrlTitle->GetValue();
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
    wxMenu* amenu = new wxMenu;
    size_t m = 0;
    dmenu->Append( ID_DATE_MENU_START, wxT("Create new") );
    dmenu->Append( ID_DATE_MENU_START + 1, wxT("From age at"), amenu );
//    size_t maxEntries = wxMin( 98, mp_entities->size() );
    for( size_t i = 0 ; i < m_dateStrings.size() ; i++ ) {
        dmenu->Append( ID_DATE_MENU_START + 2, m_dateStrings[i].m_str );
        amenu->Append( ID_AGE_MENU_START, m_dateStrings[i].m_str );

#if 0
        if( (*mp_entities)[i].rec.f_entity_type == recReferenceEntity::TYPE_Date ) {
            wxString dstr = recDate::GetStr( (*mp_entities)[i].rec.f_entity_id );
            dmenu->Append( ID_DATE_MENU_START + 2, dstr );
            amenu->Append( ID_AGE_MENU_START, dstr );
            (*mp_entities)[i].index = m;
            m++;
        } else {
            (*mp_entities)[i].index = -1;
        }
#endif
    }
    PopupMenu( dmenu );
    delete amenu;
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
        textCtrlDate->SetValue( m_dateStrings[i-2].m_str );
        idt dateID = m_dateStrings[i-2].m_index;
        if( m_dateButton == EV_DATE_Beg ) {
            m_event.f_date1_id = dateID;
        } else {
            m_event.f_date2_id = dateID;
        }
    }
}

void dlgEditEvent::OnAgeSelect( wxCommandEvent& event )
{
    wxMessageBox( "Rewrite needed", "OnAgeSelect" );
#if 0
    const wxString savepoint = "EvtDateAge";
    size_t i = event.GetId() - ID_AGE_MENU_START;
    wxTextCtrl* textCtrlDate =
        ( m_dateButton == EV_DATE_Beg ) ? m_textCtrlDateBeg : m_textCtrlDateEnd;

    dlgEditDateFromAge* dialog =
        new dlgEditDateFromAge( NULL, m_dateStrings[i].m_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        TfpEntityString es;
        es.m_str = dialog->GetDate()->GetStr();
        es.m_id = dialog->GetDate()->f_id;
        es.m_index = -1;
        m_dateStrings.push_back( es );
        textCtrlDate->SetValue( es.m_str );
        if( m_dateButton == EV_DATE_Beg ) {
            m_event.f_date1_id = es.m_id;
        } else {
            m_event.f_date2_id = es.m_id;
        }
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditEvent::OnPlaceButton( wxCommandEvent& event )
{
    if( mp_entities ) {
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
    } else {
        // TODO:
        wxMessageBox( wxT("Not yet implimented"), wxT("OnPlaceButton") );
    }
}

void dlgEditEvent::OnPlaceSelect( wxCommandEvent& event )
{
    size_t i = event.GetId() - ID_PLACE_MENU_START;

    if( i == 0 ) {
        m_textCtrlPlace->SetValue( wxT("TODO: Get New Place") );
    } else {
        wxASSERT( mp_entities != NULL );
        int entry = tfpGetEntityIndex( mp_entities, i );
        idt placeID = (*mp_entities)[entry].rec.f_entity_id;
        m_textCtrlPlace->SetValue( recPlace::GetAddressStr( placeID ) );
        m_event.f_place_id = placeID;
    }
}

void dlgEditEvent::OnAddButton( wxCommandEvent& event )
{
    const wxString savepoint = "EvtRole";
    dlgEditRole* dialog = new dlgEditRole( NULL, m_event.f_id );
    dialog->SetRefID( m_refID );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        recEventPersona* pe = dialog->GetEventPersona();
        int row = m_pes.size();
        m_listPersona->InsertItem( row, recPersona::GetNameStr( pe->f_per_id ) );
        m_listPersona->SetItem( row, COL_Role, recEventTypeRole::GetName( pe->f_role_id ) );
        m_listPersona->SetItem( row, COL_Note, pe->f_note );
        m_pes.push_back( *pe );
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditEvent::OnEditButton( wxCommandEvent& event )
{
#if 0
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnEditButton")
    );
    // TODO: Implement OnEditButton
#endif
    const wxString savepoint = "EvtEdRole";
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Personas") );
        return;
    }
    idt id = m_pes[row].f_id;
    dlgEditRole* dialog = new dlgEditRole( NULL, m_event.f_id, id );
    dialog->SetRefID( m_refID );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recEventPersona* pe = dialog->GetEventPersona();
        m_listPersona->SetItem( row, COL_Role, recEventTypeRole::GetName( pe->f_role_id ) );
        m_listPersona->SetItem( row, COL_Note, pe->f_note );
        m_pes[row] = *pe;
    } else {
        // Dialog Cancelled
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
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
#endif

// End of dlgEdEvent.cpp file
