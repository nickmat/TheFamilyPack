/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual Event dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010-2015, Nick Matthews.
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

#include <wx/fs_mem.h>

#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recEventa.h>
#include <rg/rgDialogs.h>

#include "rgEdEvent.h"


bool rgEditEvent( wxWindow* wind, idt eveID )
{
    wxASSERT( eveID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEvent* dialog = new rgDlgEditEvent( wind, eveID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}


idt rgCreateIndEvent(
    wxWindow* wind, idt ind1ID, idt ind2ID, idt famID, unsigned grpfilter )
{
    wxASSERT( ind1ID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    if( ind2ID && grpfilter == recET_GRP_FILTER_All ) {
        grpfilter = recET_GRP_FILTER_Family;
    }
    idt typeID = rgSelectEventType( wind, rgSELSTYLE_Create, NULL, grpfilter );
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    recEvent eve(0);
    eve.FSetTypeID( typeID );
    eve.SetAutoTitle(
        recIndividual::GetName( ind1ID ),
        recIndividual::GetName( ind2ID )
    );
    eve.Save();
    idt eveID = eve.GetID();

    recIndividualEvent ie(0);
    ie.FSetEventID( eveID );
    ie.FSetIndID( ind1ID );
    ie.Save();
    rgSHOWROLE sr = rgSHOWROLE_PrimeAll;
    if( ind2ID ) {
        Sex sex = recIndividual::GetSex( ind1ID );
        if( sex == SEX_Male ) sr = rgSHOWROLE_PrimeMale;
        if( sex == SEX_Female ) sr = rgSHOWROLE_PrimeFemale;
    }
    if( ! rgEditIndEventRole( wind, ie.FGetID(), sr )  ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    if( ind2ID ) {
        ie.Clear();
        ie.FSetEventID( eveID );
        ie.FSetIndID( ind2ID );
        ie.Save();
        sr = rgSHOWROLE_PrimeAll;
        Sex sex = recIndividual::GetSex( ind2ID );
        if( sex == SEX_Male ) sr = rgSHOWROLE_PrimeMale;
        if( sex == SEX_Female ) sr = rgSHOWROLE_PrimeFemale;
        if( ! rgEditIndEventRole( wind, ie.FGetID(), sr )  ) {
            recDb::Rollback( savepoint );
            return 0;
        }
    }
    if( famID ) {
        recFamilyEvent fe(0);
        fe.FSetFamID( famID );
        fe.FSetEventID( eveID );
        fe.FSetFamSeq( recFamily::GetMaxEventSeqNumber( famID ) + 1 );
        fe.Save();
    }

    if( ! rgEditEvent( wind, eveID ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return eveID;
}

idt rgCreateDefaultIndEvent( wxWindow* wind, idt ind1ID, idt ind2ID, recET_GRP grp )
{
    wxASSERT( ind1ID != 0 );
    // TODO: Determine what the default Event (for the given group)
    // by examining the individual (for some culture identity).
    recEventType::EType typeID;
    recEventTypeRole::Role roleID, role2ID = recEventTypeRole::ROLE_Marriage_Bride;
    switch( grp )
    {
    case recET_GRP_FamUnion:
        typeID = recEventType::ET_Marriage;
        roleID = recEventTypeRole::ROLE_Marriage_Groom;
        break;
    case recET_GRP_Birth:
        typeID = recEventType::ET_Birth;
        roleID = recEventTypeRole::ROLE_Birth_Born;
        break;
    case recET_GRP_NrBirth:
        typeID = recEventType::ET_Baptism;
        roleID = recEventTypeRole::ROLE_Baptism_Baptised;
        break;
    case recET_GRP_Death:
        typeID = recEventType::ET_Death;
        roleID = recEventTypeRole::ROLE_Death_Died;
        break;
    case recET_GRP_NrDeath:
        typeID = recEventType::ET_Burial;
        roleID = recEventTypeRole::ROLE_Burial_Deceased;
        break;
    default:
        return 0;
    }
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEvent eve(0);
    eve.FSetTypeID( typeID );
    eve.SetAutoTitle(
        recIndividual::GetName( ind1ID ),
        recIndividual::GetName( ind2ID )
    );
    eve.Save();
    idt eveID = eve.GetID();

    recIndividualEvent ie(0);
    ie.FSetEventID( eveID );
    ie.FSetIndID( ind1ID );
    ie.FSetRoleID( roleID );
    ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( ind1ID ) + 1 );
    ie.Save();
    if( ind2ID ) {
        ie.Clear();
        ie.FSetEventID( eveID );
        ie.FSetIndID( ind2ID );
        ie.FSetRoleID( role2ID );
        ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( ind2ID ) + 1 );
        ie.Save();
        idt famID = recFamily::Find( ind1ID, ind2ID );
        wxASSERT( famID != 0 );
        recFamilyEvent fe(0);
        fe.FSetFamID( famID );
        fe.FSetEventID( eveID );
        fe.FSetFamSeq( recFamily::GetMaxEventSeqNumber( famID ) + 1 );
        fe.Save();
    }
    if( ! rgEditEvent( wind, eveID ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return eveID;
}

idt rgCreatePersonalEvent( wxWindow* wind, idt indID, recEventType::EType etype )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEvent eve(0);
    eve.FSetTypeID( etype );
    eve.SetAutoTitle( recIndividual::GetName( indID ) );
    eve.Save();
    if( !rgCreateIndEventRole( wind, indID, eve.FGetID(), 0 ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return eve.FGetID();
}

idt rgCreateEventFromRecord( wxWindow* wind, idt erID )
{
    wxASSERT( erID != 0 );
    recEventa er(erID);

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEvent e(0);
    e.FSetTitle( er.FGetTitle() );
    e.FSetTypeID( er.FGetTypeID() );
    e.FSetDate1ID( er.FGetDate1ID() );
    e.FSetDate2ID( er.FGetDate2ID() );
    e.FSetPlaceID( er.FGetPlaceID() );
    e.FSetNote( er.FGetNote() );
    e.FSetDatePt( er.FGetDatePt() );
    e.Save();
    idt eID = e.FGetID();

    recEventEventa eer(0);
    eer.FSetEventID( eID );
    eer.FSetEventaID( erID );
    eer.FSetConf( 0.999 );
    eer.Save();

    recEventaPersonaVec pers = er.GetEventaPersonas();
    for( size_t i = 0 ; i < pers.size() ; i++ ) {
        recIdVec indIDs = recPersona::GetIndividualIDs( pers[i].FGetPerID() );
        for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
            recIndividualEvent ie(0);
            ie.FSetIndID( indIDs[j] );
            ie.FSetEventID( eID );
            ie.FSetRoleID( pers[i].FGetRoleID() );
            ie.FSetNote( pers[i].FGetNote() );
            ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indIDs[j] ) + 1 );
            ie.Save();
        }
    }

    if( ! rgEditEvent( wind, eID ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return eID;
}

//============================================================================
//-------------------------[ rgDlgEditEvent ]---------------------------------
//============================================================================

rgDlgEditEvent::rgDlgEditEvent( wxWindow* parent, idt eventID )
    : m_event(eventID), fbRgEditEvent( parent )
{
    m_date1ID = m_event.FGetDate1ID();
    m_date2ID = m_event.FGetDate2ID();
    m_placeID = m_event.FGetPlaceID();

    m_listIndividual->InsertColumn( COL_IndID, _("Individual"), wxLIST_FORMAT_LEFT, 70 );
    m_listIndividual->InsertColumn( COL_Name, _("Name") );
    m_listIndividual->InsertColumn( COL_Role, _("Role") );
    m_listIndividual->InsertColumn( COL_Note, _("Note") );

    m_listRecord->InsertColumn( COL_RecID, _("Record"), wxLIST_FORMAT_LEFT, 70 );
    m_listRecord->InsertColumn( COL_RefID, _("Reference") );
    m_listRecord->InsertColumn( COL_RefTitle, _("Reference Title") );
}

bool rgDlgEditEvent::TransferDataToWindow()
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
    m_textCtrlUserRef->SetValue( m_event.FGetUserRef() );
    m_textCtrlNote->SetValue( m_event.FGetNote() );
    ListLinkedIndividuals();
    ListEventas();
    m_staticEventID->SetLabel( m_event.GetIdStr() );
    return true;
}

void rgDlgEditEvent::ListLinkedIndividuals()
{
    m_ies = m_event.GetIndividualEvents();
    m_listIndividual->DeleteAllItems();
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        idt indID = m_ies[i].FGetIndID();
        m_listIndividual->InsertItem( i, recIndividual::GetIdStr( indID ) );
        m_listIndividual->SetItem( i, COL_Name, recIndividual::GetName( indID ) );
        m_listIndividual->SetItem( i, COL_Role, recEventTypeRole::GetName( m_ies[i].f_role_id ) );
        m_listIndividual->SetItem( i, COL_Note, m_ies[i].f_note );
    }
    m_listIndividual->SetColumnWidth( COL_Name, wxLIST_AUTOSIZE );
    m_listIndividual->SetColumnWidth( COL_Role, wxLIST_AUTOSIZE );
}

void rgDlgEditEvent::ListEventas()
{
    m_eers = m_event.GetEventEventas();
    m_listRecord->DeleteAllItems();
    for( size_t i = 0 ; i < m_eers.size() ; i++ ) {
        idt erID = m_eers[i].FGetEventaID();
        idt refID = recEventa::FindReferenceID( erID );
        m_listRecord->InsertItem( i, recEventa::GetIdStr( erID ) );
        m_listRecord->SetItem( i, COL_RefID, recReference::GetIdStr( refID ) );
        m_listRecord->SetItem( i, COL_RefTitle, recReference::GetTitle( refID ) );
    }
    m_listRecord->SetColumnWidth( COL_RefTitle, wxLIST_AUTOSIZE );
}

bool rgDlgEditEvent::TransferDataFromWindow()
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
    m_event.FSetUserRef( m_textCtrlUserRef->GetValue() );
    m_event.FSetNote( m_textCtrlNote->GetValue() );

    m_event.UpdateDatePoint();
    m_event.Save();

    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        m_ies[i].FSetIndSeq( i + 1 );
        m_ies[i].Save();
    }

    return true;
}

void rgDlgEditEvent::OnDate1Button( wxCommandEvent& event )
{
    if( m_date1ID == 0 ) {
        m_date1ID = rgCreateDate( this );
        if( m_date1ID == 0 ) {
            return;
        }
    } else {
        if( !rgEditDate( this, m_date1ID ) ) {
            return;
        }
    }
    m_textCtrlDate1->SetValue( recDate::GetStr( m_date1ID ) );
}

void rgDlgEditEvent::OnDate2Button( wxCommandEvent& event )
{
    if( m_date2ID == 0 ) {
        m_date2ID = rgCreateDate( this );
        if( m_date2ID == 0 ) {
            return;
        }
    } else {
        if( !rgEditDate( this, m_date2ID ) ) {
            return;
        }
    }
    m_textCtrlDate1->SetValue( recDate::GetStr( m_date2ID ) );
}

void rgDlgEditEvent::OnPlaceButton( wxCommandEvent& event )
{
    if( m_placeID == 0 ) {
        m_placeID = rgCreatePlace( this );
        if( m_placeID == 0 ) {
            return;
        }
    } else {
        if( !rgEditPlace( this, m_placeID ) ) {
            return;
        }
    }
    m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_placeID ) );
}

void rgDlgEditEvent::OnAddInd( wxCommandEvent& event )
{
    if( rgCreateIndEventRole( this, 0, m_event.FGetID(), 0 ) ) {
        ListLinkedIndividuals();
    }
}

void rgDlgEditEvent::OnEditInd( wxCommandEvent& event )
{
    long row = m_listIndividual->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Individual") );
        return;
    }
    idt ieID = m_ies[row].FGetID();
    if( rgEditIndEventRole( this, ieID ) ) {
        ListLinkedIndividuals();
    }
}

void rgDlgEditEvent::OnDelInd( wxCommandEvent& event )
{
    long row = m_listIndividual->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Link") );
        return;
    }
    idt ieID = m_ies[row].FGetID();
    int ans = wxMessageBox(
        _("Remove the link between the Individual and this Event from database?"),
        _("Delete Link"),
        wxYES_NO | wxCANCEL, this
    );
    if( ans != wxYES ) {
        return;
    }
    recIndividualEvent::Delete( ieID );
    ListLinkedIndividuals();
}

void rgDlgEditEvent::OnAddRecord( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnAddRecord" );
}

void rgDlgEditEvent::OnEditRecord( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnEditRecord" );
}

void rgDlgEditEvent::OnDeleteRecord( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnDelRecord" );
}

// End of dlgEdIndEvent.cpp file
