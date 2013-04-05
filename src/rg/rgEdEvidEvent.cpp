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

bool rgEditEventRecord( wxWindow* wind, idt erID )
{
    idt refID = recEventRecord::FindReferenceID( erID );
    wxASSERT( refID != 0 );
    if( refID ) {
        return rgEditReference( wind, refID );
    }
    return false;
}

bool rgEditEvidEvent( rgDlgEditReference* parent, idt eveID )
{
    wxMessageBox( "To be rewritten", "rgEditEvidEvent" );
    return false;


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
    wxMessageBox( "To be rewritten", "rgCreateEvidEvent" );
    return false;


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

    recEventRecord e(0);
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
    wxMessageBox( "To be rewritten", "rgCreateEvidPerEvent" );
    return false;


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

    recEventRecord eve(0);
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

BEGIN_EVENT_TABLE( rgDlgEditEvidEvent, wxDialog )
    EVT_MENU( ID_EDEE_OPTN_EDIT,       rgDlgEditEvidEvent::OnOptnEdit )
    EVT_MENU( ID_EDEE_OPTN_UNLINK,     rgDlgEditEvidEvent::OnOptnUnlink )
    EVT_MENU( ID_EDEE_OPTN_CREATE,     rgDlgEditEvidEvent::OnOptnCreate )
    EVT_MENU( ID_EDEE_OPTN_CREATE_REL, rgDlgEditEvidEvent::OnOptnCreateRel )
END_EVENT_TABLE()

rgDlgEditEvidEvent::rgDlgEditEvidEvent( rgDlgEditReference* parent, idt erID )
    : m_event(erID), fbRgEditEvent( parent )
{
    wxASSERT( false ); // Not currently working

    m_date1ID = m_event.FGetDate1ID();
    m_date2ID = m_event.FGetDate2ID();
    m_placeID = m_event.FGetPlaceID();

    m_listPersona->InsertColumn( COL_PerID, _("Persona"), wxLIST_FORMAT_LEFT, 70 );
    m_listPersona->InsertColumn( COL_Name, _("Name") );
    m_listPersona->InsertColumn( COL_Role, _("Role") );
    m_listPersona->InsertColumn( COL_Note, _("Note") );
}

bool rgDlgEditEvidEvent::TransferDataToWindow()
{
    wxASSERT( m_event.GetID() != 0 );
    m_staticType->SetLabel( m_event.GetTypeStr() );
    m_textCtrlTitle->SetValue( m_event.FGetTitle() );
    m_textCtrlDate1->SetValue( recDate::GetStr( m_date1ID ) );
    if( recEventType::HasDateSpan( m_event.FGetTypeID() ) ) {
        m_textCtrlDate2->SetValue( recDate::GetStr( m_date2ID ) );
    } else {
        m_buttonDate2->Enable( false );
        m_textCtrlDate2->Enable( false );
    }
    m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_placeID ) );
    m_textCtrlNote->SetValue( m_event.f_note );
    ListLinkedPersona();
    m_staticEventID->SetLabel( m_event.GetIdStr() );
    return true;
}

bool rgDlgEditEvidEvent::TransferDataFromWindow()
{
    wxASSERT( m_event.FGetTypeID() != 0 );

    m_event.FSetTitle( m_textCtrlTitle->GetValue() );
    wxString str = m_textCtrlDate1->GetValue();
    idt dateID = m_event.FGetDate1ID();
    if( str.IsEmpty() ) {
        if( dateID != 0 ) {
            m_event.FSetDate1ID( 0 );
            m_event.Save();
            recDate::DeleteIfOrphaned( dateID );
        }
        recDate::DeleteIfOrphaned( m_date1ID );
    } else {
        if( m_date1ID ) {
            recDate::SetDate( m_date1ID, str );
        } else {
            m_date1ID = recDate::Create( str );
        }
        if( dateID != m_date1ID ) {
            m_event.FSetDate1ID( m_date1ID );
        }
    }

    str = m_textCtrlDate2->GetValue();
    dateID = m_event.FGetDate2ID();
    if( str.IsEmpty() ) {
        if( dateID != 0 ) {
            m_event.FSetDate2ID( 0 );
            m_event.Save();
            recDate::DeleteIfOrphaned( dateID );
        }
        recDate::DeleteIfOrphaned( m_date2ID );
    } else {
        if( m_date2ID ) {
            recDate::SetDate( m_date2ID, str );
        } else {
            m_date2ID = recDate::Create( str );
        }
        if( dateID != m_date2ID ) {
            m_event.FSetDate2ID( m_date2ID );
        }
    }

    str = m_textCtrlPlace->GetValue();
    idt placeID = m_event.FGetPlaceID();
    if( str.IsEmpty() ) {
        if( placeID != 0 ) {
            m_event.FSetPlaceID( 0 );
            m_event.Save();
            recPlace::DeleteIfOrphaned( placeID );
        }
        recPlace::DeleteIfOrphaned( m_placeID );
    } else {
        if( m_placeID ) {
            recPlace::SetAddress( m_placeID, str );
        } else {
            m_placeID = recPlace::Create( str );
        }
        if( placeID != m_placeID ) {
            m_event.FSetPlaceID( m_placeID );
        }
    }
    m_event.FSetNote( m_textCtrlNote->GetValue() );

    m_event.UpdateDatePoint(); 
    m_event.Save();

    for( size_t i = 0 ; i < m_eps.size() ; i++ ) {
        m_eps[i].FSetPerSeq( i + 1 );
        m_eps[i].Save();
    }

    return true;
}

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

void rgDlgEditEvidEvent::OnDate1Button( wxCommandEvent& event )
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

void rgDlgEditEvidEvent::OnDate2Button( wxCommandEvent& event )
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

void rgDlgEditEvidEvent::OnPlaceButton( wxCommandEvent& event )
{
    m_button = EEEB_Place;
    wxMenu* menu = new wxMenu;
    if( m_placeID ) {
        menu->Append( ID_EDEE_OPTN_EDIT, _("&Edit") );
        menu->Append( ID_EDEE_OPTN_UNLINK, _("&Unlink") );
    } else {
        menu->Append( ID_EDEE_OPTN_CREATE, _("Set &Date") );
        menu->Append( ID_EDEE_OPTN_CREATE_REL, _("Set &Relative Date") );
    }
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditEvidEvent::OnOptnEdit( wxCommandEvent& event )
{
    switch( m_button )
    {
    case EEEB_Date1:
        if( !rgEditDate( this, m_date1ID ) ) {
            return;
        }
        m_textCtrlDate1->SetValue( recDate::GetStr( m_date1ID ) );
        break;
    case EEEB_Date2:
        if( !rgEditDate( this, m_date2ID ) ) {
            return;
        }
        m_textCtrlDate2->SetValue( recDate::GetStr( m_date2ID ) );
        break;
    case EEEB_Place:
        if( !rgEditPlace( this, m_placeID ) ) {
            return;
        }
        m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_placeID ) );
        break;
    }
}

void rgDlgEditEvidEvent::OnOptnUnlink( wxCommandEvent& event )
{
    switch( m_button )
    {
    case EEEB_Date1:
        m_date1ID = 0;
        m_textCtrlDate1->SetValue( "" );
        break;
    case EEEB_Date2:
        m_date2ID = 0;
        m_textCtrlDate2->SetValue( "" );
        break;
    case EEEB_Place:
        m_placeID = 0;
        m_textCtrlPlace->SetValue( "" );
        break;
    }
    m_event.FSetDate1ID( m_date1ID );
    m_event.FSetDate2ID( m_date2ID );
    m_event.FSetPlaceID( m_placeID );
}

void rgDlgEditEvidEvent::OnOptnCreate( wxCommandEvent& event )
{
    switch( m_button )
    {
    case EEEB_Date1:
        if( ! m_refDialog->SelectDate( &m_date1ID, "", rgSELSTYLE_Create ) ) {
            return;
        }
        m_textCtrlDate1->SetValue( recDate::GetStr( m_date1ID ) );
        break;
    case EEEB_Date2:
        if( ! m_refDialog->SelectDate( &m_date2ID, "", rgSELSTYLE_Create ) ) {
            return;
        }
        m_textCtrlDate2->SetValue( recDate::GetStr( m_date2ID ) );
        break;
    case EEEB_Place:
        if( ! m_refDialog->SelectPlace( &m_placeID, "", rgSELSTYLE_Create ) ) {
            return;
        }
        m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_placeID ) );
        break;
    }
    m_event.FSetDate1ID( m_date1ID );
    m_event.FSetDate2ID( m_date2ID );
    m_event.FSetPlaceID( m_placeID );
}

void rgDlgEditEvidEvent::OnOptnCreateRel( wxCommandEvent& event )
{
    idt id;
    switch( m_button )
    {
    case EEEB_Date1:
        if( ! m_refDialog->SelectDate( &id, _("Select Base Date"), rgSELSTYLE_Create ) ) {
            return;
        }
        m_date1ID = rgCreateRelativeDate( this, id );
        if( m_date1ID == 0 ) {
            m_date1ID = m_event.FGetDate1ID();
            return;
        }
        m_refDialog->CreateRefEntity( recReferenceEntity::TYPE_Date, m_date1ID );
        m_textCtrlDate1->SetValue( recDate::GetStr( m_date1ID ) );
        break;
    case EEEB_Date2:
        if( ! m_refDialog->SelectDate( &id, _("Select Base Date"), rgSELSTYLE_Create ) ) {
            return;
        }
        m_date2ID = rgCreateRelativeDate( this, id );
        if( m_date2ID == 0 ) {
            m_date2ID = m_event.FGetDate2ID();
            return;
        }
        m_refDialog->CreateRefEntity( recReferenceEntity::TYPE_Date, m_date2ID );
        m_textCtrlDate2->SetValue( recDate::GetStr( m_date2ID ) );
        break;
    case EEEB_Place:
        if( ! m_refDialog->SelectPlace( &id, "", rgSELSTYLE_Create ) ) {
            return;
        }
        m_placeID = rgCreateRelativeDate( this, id );
        if( m_placeID == 0 ) {
            m_placeID = m_event.FGetPlaceID();
            return;
        }
        m_refDialog->CreateRefEntity( recReferenceEntity::TYPE_Place, m_placeID );
        m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_placeID ) );
        break;
    }
    m_event.FSetDate1ID( m_date1ID );
    m_event.FSetDate2ID( m_date2ID );
    m_event.FSetPlaceID( m_placeID );
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

// End of src/rg/rgEdEvidEvent.cpp file
