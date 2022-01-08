/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Eventa entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25th February 2013
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

#include <rec/recDate.h>
#include <rec/recFamily.h>
#include <rec/recPlace.h>
#include <rec/recPersona.h>

#include "rg/rgDialogs.h"
#include "rgEdEventa.h"
#include "rgEdReference.h"

bool rgEditEventa( wxWindow* wind, idt erID )
{
    wxASSERT( erID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEventa* dialog = new rgDlgEditEventa( wind, erID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}
// Create a new Eventa from the reference document id
idt rgCreateEventa( wxWindow* wind, idt refID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt typeID = rgSelectEventType( wind );
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
    case recEventTypeGrp::birth:
        role1 = recEventTypeRole::ROLE_Birth_Born;
        break;
    case recEventTypeGrp::nr_birth:
        break;
    case recEventTypeGrp::death:
        role1 = recEventTypeRole::ROLE_Death_Died;
        break;
    case recEventTypeGrp::nr_death:
        break;
    case recEventTypeGrp::fam_union:
        person2 = true;
        role1 = recEventTypeRole::ROLE_Marriage_Groom;
        role2 = recEventTypeRole::ROLE_Marriage_Bride;
        break;
    case recEventTypeGrp::fam_other:
        person2 = true;
        break;
    default:
        enddate = true;
    }

    idt dateID1;
    unsigned style = rgSELSTYLE_Create | rgSELSTYLE_Unknown;
    if( rgSelectDateFromReference( wind, &dateID1, refID, _("Select Start Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    idt dateID2 = 0;
    if( enddate ) {
        if( rgSelectDateFromReference( wind, &dateID2, refID, _("Select End Date"), style ) == false ) {
            recDb::Rollback( savepoint );
            return 0;
        }
    }
    idt placeID;
    if( rgSelectPlaceFromReference( wind, &placeID, refID, _("Select Place"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    idt perID1 = rgSelectPersona( wind, refID );
    if( perID1 == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    wxString title;
    idt perID2 = 0;
    if( person2 ) {
        perID2 = rgSelectPersona( wind, refID );
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

    recEventa er(0);
    er.FSetTitle( title );
    er.FSetRefID( refID );
    er.FSetTypeID( typeID );
    er.FSetDate1ID( dateID1 );
    er.FSetDate2ID( dateID2 );
    er.FSetPlaceID( placeID );
    er.Save();
    idt erID = er.FGetID();

    recEventaPersona ep1(0);
    ep1.FSetEventaID( erID );
    ep1.FSetPerID( perID1 );
    ep1.FSetRoleID( role1 );
    ep1.FSetPerSeq( 1 );
    ep1.Save();
    recIdVec indID1s = recPersona::GetIndividualIDs( perID1 );
    recIdVec indID2s;
    if( person2 ) {
        recEventaPersona ep2(0);
        ep2.FSetEventaID( erID );
        ep2.FSetPerID( perID2 );
        ep2.FSetRoleID( role2 );
        ep2.FSetPerSeq( 2 );
        ep2.Save();
        indID2s = recPersona::GetIndividualIDs( perID2 );
        recIdVec famIDs = recFamily::FindVec( indID1s, indID2s );
        for( size_t i = 0 ; i < famIDs.size() ; i++ ) {
            double conf = 0.999/indID1s.size();
            rgFindOrCreateIndEvent( wind, erID, conf, famIDs[i], role1 );
        }
    } else {
        for( size_t i = 0 ; i < indID1s.size() ; i++ ) {
            double conf = 0.999/indID1s.size();
            rgFindOrCreateIndEvent( wind, erID, conf, indID1s[i], role1 );
        }
    }

    if( rgEditEventa( wind, erID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        erID = 0;
    }
    return erID;
}

idt rgCreatePersonalEventa( wxWindow* wind, idt refID, const wxString& role )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = rgSelectPersona( wind, refID );
    if( perID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    idt eveTypeID = rgSelectEventType( wind, rgSELSTYLE_Create, NULL, recET_GRP_FILTER_Personal );
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
    if( rgSelectDateFromReference( wind, &date1ID, refID, _("Select Start Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    if( rgSelectDateFromReference( wind, &date2ID, refID, _("Select End Date"), style ) == false ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    if( date1ID == date2ID ) {
        date2ID = 0;
    }
    idt placeID;
    if( rgSelectPlaceFromReference( wind, &placeID, refID, _("Select Place"), style ) == false ) {
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

    recEventa eve(0);
    eve.FSetTitle( title );
    eve.FSetRefID( refID );
    eve.FSetTypeID( eveTypeID );
    eve.FSetDate1ID( date1ID );
    eve.FSetDate2ID( date2ID );
    eve.FSetPlaceID( placeID );
    eve.SetDatePt( recDate::DatePoint::mid );
    eve.Save();
    idt eveID = eve.FGetID();

    recEventaPersona ep(0);
    ep.FSetEventaID( eveID );
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
//--------------------------[ rgDlgEditEventa ]-------------------------------
//============================================================================

BEGIN_EVENT_TABLE( rgDlgEditEventa, wxDialog )
    EVT_MENU( ID_EDEE_OPTN_EDIT,       rgDlgEditEventa::OnOptnEdit )
    EVT_MENU( ID_EDEE_OPTN_UNLINK,     rgDlgEditEventa::OnOptnUnlink )
    EVT_MENU( ID_EDEE_OPTN_CREATE,     rgDlgEditEventa::OnOptnCreate )
    EVT_MENU( ID_EDEE_OPTN_CREATE_REL, rgDlgEditEventa::OnOptnCreateRel )
END_EVENT_TABLE()

rgDlgEditEventa::rgDlgEditEventa( wxWindow* parent, idt erID )
    : m_event(erID), fbRgEditEventa( parent )
{
    m_refID = recEventa::GetRefID( erID );
    wxASSERT( m_refID != 0 );

    m_date1ID = m_event.FGetDate1ID();
    m_date2ID = m_event.FGetDate2ID();
    m_placeID = m_event.FGetPlaceID();

    m_listPersona->InsertColumn( COL_PerID, _("Persona"), wxLIST_FORMAT_LEFT, 70 );
    m_listPersona->InsertColumn( COL_Name, _("Name") );
    m_listPersona->InsertColumn( COL_Role, _("Role") );
    m_listPersona->InsertColumn( COL_Note, _("Note") );

    m_listConclusion->InsertColumn( COL_EveID, _("Event"), wxLIST_FORMAT_LEFT, 70 );
    m_listConclusion->InsertColumn( COL_EveTitle, _("Title") );
}

bool rgDlgEditEventa::TransferDataToWindow()
{
    wxASSERT( m_event.FGetID() != 0 );
    m_staticType->SetLabel( m_event.GetTypeStr() );
    m_textCtrlTitle->SetValue( m_event.FGetTitle() );
    m_staticDate1->SetLabel( recDate::GetStr( m_date1ID ) );
    m_staticDate2->SetLabel( recDate::GetStr( m_date2ID ) );
    if( ! recEventType::HasDateSpan( m_event.FGetTypeID() ) ) {
        m_buttonDate2->Enable( false );
    }
    m_staticPlace->SetLabel( recPlace::GetAddressStr( m_placeID ) );
    m_textCtrlNote->SetValue( m_event.f_note );
    ListLinkedPersona();
    ListEvents();
    m_staticEventaID->SetLabel( m_event.GetIdStr() );
    return true;
}

void rgDlgEditEventa::ListLinkedPersona()
{
    m_eps = m_event.GetEventaPersonas();
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

void rgDlgEditEventa::ListEvents()
{
    m_eers = m_event.GetEventEventas();
    m_listConclusion->DeleteAllItems();
    for( size_t i = 0 ; i < m_eers.size() ; i++ ) {
        idt eveID = m_eers[i].FGetEventID();
        m_listConclusion->InsertItem( i, recEvent::GetIdStr( eveID ) );
        m_listConclusion->SetItem( i, COL_EveTitle, recEvent::GetTitle( eveID ) );
    }
    m_listConclusion->SetColumnWidth( COL_EveTitle, wxLIST_AUTOSIZE );
}

bool rgDlgEditEventa::TransferDataFromWindow()
{
    wxASSERT( m_event.FGetTypeID() != 0 );

    m_event.FSetTitle( m_textCtrlTitle->GetValue() );
    m_event.FSetNote( m_textCtrlNote->GetValue() );

    m_event.UpdateDatePoint();
    m_event.Save();

    return true;
}

void rgDlgEditEventa::OnDate1Button( wxCommandEvent& event )
{
    m_button = EEEB_Date1;
    wxMenu* menu = new wxMenu;
    if( m_date1ID ) {
        menu->Append( ID_EDEE_OPTN_EDIT, _("&Edit") );
        menu->Append( ID_EDEE_OPTN_UNLINK, _("&Unlink") );
    } else {
        menu->Append( ID_EDEE_OPTN_CREATE, _("Set &Date") );
        menu->Append( ID_EDEE_OPTN_CREATE_REL, _("Set &Relative Date") );
    }
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditEventa::OnDate2Button( wxCommandEvent& event )
{
    m_button = EEEB_Date2;
    wxMenu* menu = new wxMenu;
    if( m_date2ID ) {
        menu->Append( ID_EDEE_OPTN_EDIT, _("&Edit") );
        menu->Append( ID_EDEE_OPTN_UNLINK, _("&Unlink") );
    } else {
        menu->Append( ID_EDEE_OPTN_CREATE, _("Set &Date") );
        menu->Append( ID_EDEE_OPTN_CREATE_REL, _("Set &Relative Date") );
    }
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditEventa::OnPlaceButton( wxCommandEvent& event )
{
    m_button = EEEB_Place;
    if( m_placeID ) {
        wxMenu* menu = new wxMenu;
        menu->Append( ID_EDEE_OPTN_EDIT, _("&Edit") );
        menu->Append( ID_EDEE_OPTN_UNLINK, _("&Unlink") );
        PopupMenu( menu );
        delete menu;
    } else {
        OnOptnCreate( event );
    }
}

void rgDlgEditEventa::OnOptnEdit( wxCommandEvent& event )
{
    switch( m_button )
    {
    case EEEB_Date1:
        if( !rgEditDate( this, m_date1ID ) ) {
            return;
        }
        m_staticDate1->SetLabel( recDate::GetStr( m_date1ID ) );
        break;
    case EEEB_Date2:
        if( !rgEditDate( this, m_date2ID ) ) {
            return;
        }
        m_staticDate2->SetLabel( recDate::GetStr( m_date2ID ) );
        break;
    case EEEB_Place:
        if( !rgEditPlace( this, m_placeID ) ) {
            return;
        }
        m_staticPlace->SetLabel( recPlace::GetAddressStr( m_placeID ) );
        break;
    }
}

void rgDlgEditEventa::OnOptnUnlink( wxCommandEvent& event )
{
    switch( m_button )
    {
    case EEEB_Date1:
        m_event.FSetDate1ID( 0 );
        m_date1ID = 0;
        m_staticDate1->SetLabel( "" );
        break;
    case EEEB_Date2:
        m_event.FSetDate2ID( 0 );
        m_date2ID = 0;
        m_staticDate2->SetLabel( "" );
        break;
    case EEEB_Place:
        m_event.FSetPlaceID( 0 );
        m_placeID = 0;
        m_staticPlace->SetLabel( "" );
        break;
    }
    m_event.Save();
}

void rgDlgEditEventa::OnOptnCreate( wxCommandEvent& event )
{
    switch( m_button )
    {
    case EEEB_Date1:
        if( ! rgSelectDateFromReference(
            this, &m_date1ID, m_refID, _("Select Event Record Date"), rgSELSTYLE_Create
        ) ) {
            return;
        }
        m_staticDate1->SetLabel( recDate::GetStr( m_date1ID ) );
        m_event.FSetDate1ID( m_date1ID );
        break;
    case EEEB_Date2:
        if( ! rgSelectDateFromReference(
            this, &m_date2ID, m_refID, _("Select Event Record End Date"), rgSELSTYLE_Create
        ) ) {
            return;
        }
        m_staticDate2->SetLabel( recDate::GetStr( m_date2ID ) );
        m_event.FSetDate2ID( m_date2ID );
        break;
    case EEEB_Place:
        if( ! rgSelectPlaceFromReference(
            this, &m_placeID, m_refID, _("Select Event Record Place"), rgSELSTYLE_Create
        ) ) {
            return;
        }
        m_staticPlace->SetLabel( recPlace::GetAddressStr( m_placeID ) );
        m_event.FSetPlaceID( m_placeID );
        break;
    }
    m_event.Save();
}

void rgDlgEditEventa::OnOptnCreateRel( wxCommandEvent& event )
{
    idt id;
    switch( m_button )
    {
    case EEEB_Date1:
        if( ! rgSelectDateFromReference(
            this, &id, m_refID, _("Select Base Date"), rgSELSTYLE_Create
        ) ) {
            return;
        }
        m_date1ID = rgCreateRelativeDate( this, id );
        if( m_date1ID == 0 ) {
            m_date1ID = m_event.FGetDate1ID();
            return;
        }
        m_event.FSetDate1ID( m_date1ID );
        recReferenceEntity::Create( m_refID, recReferenceEntity::TYPE_Date, m_date1ID );
        m_staticDate1->SetLabel( recDate::GetStr( m_date1ID ) );
        break;
    case EEEB_Date2:
        if( ! rgSelectDateFromReference(
            this, &id, m_refID, _("Select Base Date"), rgSELSTYLE_Create
        ) ) {
            return;
        }
        m_date2ID = rgCreateRelativeDate( this, id );
        if( m_date2ID == 0 ) {
            m_date2ID = m_event.FGetDate2ID();
            return;
        }
        m_event.FSetDate2ID( m_date2ID );
        recReferenceEntity::Create( m_refID, recReferenceEntity::TYPE_Date, m_date2ID );
        m_staticDate2->SetLabel( recDate::GetStr( m_date2ID ) );
        break;
    case EEEB_Place:
        wxASSERT( false ); // No such thing as relative place
        return;
    }
    m_event.Save();
}

void rgDlgEditEventa::OnAddPer( wxCommandEvent& event )
{
    idt perID = rgSelectPersona( this, m_refID );
    if( perID == 0 ) {
        return;
    }
    if( rgCreatePerEventRole( this, perID, m_event.FGetID(), 0 ) ) {
        ListLinkedPersona();
    }
}

void rgDlgEditEventa::OnEditPer( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Individual") );
        return;
    }
    idt epID = m_eps[row].FGetID();
    if( rgEditPerEventRole( this, epID ) ) {
        ListLinkedPersona();
    }
}

void rgDlgEditEventa::OnDeletePer( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Link") );
        return;
    }
    idt epID = m_eps[row].FGetID();
    int ans = wxMessageBox(
        _("Remove the link between the Persona and this Event from database?"),
        _("Delete Link"),
        wxYES_NO | wxCANCEL, this
    );
    if( ans != wxYES ) {
        return;
    }
    recEventaPersona::Delete( epID );
    ListLinkedPersona();
}

void rgDlgEditEventa::OnAddCon( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnAddCon" );
}

void rgDlgEditEventa::OnEditCon( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnEditCon" );
}

void rgDlgEditEventa::OnDeleteCon( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnDeleteCon" );
}

// End of src/rg/rgEdEventa.cpp file
