/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSelEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select Event dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th December 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#include "rgTableCtrl.h"
#include "rgSelEvent.h"
#include "rg/rgDialogs.h"


bool rgSelectEventList( wxWindow* wind, recSelSetEvent& evefilter )
{
    idt ret = rgSelectEvent( wind, evefilter, rgSELSTYLE_SelList );
    if( ret == 0 ) {
        return false;
    }
    return true;
}

idt rgSelectEvent(
    wxWindow* wind,
    recSelSetEvent& evefilter,
    unsigned selstyle,
    unsigned* button )
{
    idt eveID = 0;
    bool cont = true;
    if( button ) *button = rgSELSTYLE_None;

    rgDlgSelectEvent dialog( wind, selstyle, evefilter );
    if( dialog.ShowModal() == wxID_OK ) {
        if( dialog.GetCreatePressed() ) {
            if( button ) *button = rgSELSTYLE_Create;
        }
        else if( dialog.GetUnknownPressed() ) {
            if( button ) *button = rgSELSTYLE_Unknown;
        }
        else {
            eveID = dialog.GetID();
        }
    }
    return eveID;
}

idt rgSelectEvent(
    wxWindow* wind,
    const wxString& dbname,
    unsigned selstyle,
    unsigned* button )
{
    idt eveID = 0;
    bool cont = true;
    recSelSetEvent evefilter(dbname);

    return rgSelectEvent( wind, evefilter, selstyle, button );
}


//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectEvent ]----------------------------------------
//-------------------------------------------------------------------------------

rgDlgSelectEvent::rgDlgSelectEvent( 
    wxWindow* parent, unsigned selstyle, recSelSetEvent& sse )
    : m_create(false), m_selList(false),
    m_sse(sse), m_fe(sse),
    m_begDatePt(0), m_endDatePt(0), fbRgSelectEvent( parent )
{
    wxSize sz = m_listEvent->GetClientSize();
    //                               ID   Date  scrollbar
    int titlewidth = sz.GetWidth() - 50 - 100 - 20;
    if( titlewidth < 200 ) titlewidth = 200;

    m_listEvent->InsertColumn( COL_ID, _("ID"), wxLIST_FORMAT_LEFT, 50 );
    m_listEvent->InsertColumn( COL_Title, _("Title"), wxLIST_FORMAT_LEFT, titlewidth );
    m_listEvent->InsertColumn( COL_DatePt, _("Date Point"), wxLIST_FORMAT_LEFT, 100 );

    if( selstyle & rgSELSTYLE_Create ){
        m_buttonCreate->Show();
    } else {
        m_buttonCreate->Hide();
    }
    if( selstyle & rgSELSTYLE_SelList ) {
        m_selList = true;
        m_buttonSelect->SetLabel( "OK" );
        m_buttonSelect->Enable( true );
    }
    
}

idt rgDlgSelectEvent::GetID()
{
    if( m_fe.GetTableSize() > 0 ) {
        if( m_selList ) {
            return m_fe.GetIdForRow( 0 );
        } else if( m_listEvent->GetSelectedItemCount() > 0 ) {
            long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
            return m_fe.GetIdForRow( row );
        }
    }
    return 0;
}

bool rgDlgSelectEvent::TransferDataToWindow()
{
    wxArrayString grpStrings;
    BoolVec grpsChkd;

    for( unsigned i = 0 ; i < unsigned(recEventTypeGrp::max) ; i++ ) {
        unsigned flag = 1 << i;
        if( m_fe.GetGroupsEnabled() & flag ) {
            grpStrings.push_back( recEventType::GetGroupValueStr( recEventTypeGrp( i ) ) );
            m_grps.push_back( i );
            grpsChkd.push_back( (m_fe.GetGroupsChecked() & flag) != 0 );  
        }
    }
    m_checkListGrp->InsertItems( grpStrings, 0 );
    for( size_t i = 0 ; i < m_grps.size() ; i++ ) {
        m_checkListGrp->Check( i, grpsChkd[i] );
    }

    UpdateTypeCtrl();
    UpdateTypeList();
    m_textCtrlBegDatePt->SetValue( m_sse.GetBegDateStr() );
    m_textCtrlEndDatePt->SetValue( m_sse.GetEndDateStr() );
    m_indIDs = m_fe.GetIndIDs();
    if( m_indIDs.size() ) {
        m_textCtrlIndID->SetValue( recIdVecToStr<recIndividual>( m_indIDs ) );
    }
    Refresh();
    return true;
}

bool rgDlgSelectEvent::TransferDataFromWindow()
{
    m_sse.SetGroupsChecked( m_fe.GetGroupsChecked() );
    m_sse.ClearTypeChecked();
    for( size_t i = 0 ; i < m_fe.GetTypesSize() ; i++ ) {
        if( m_fe.GetTypeChecked( i ) ) {
            m_sse.AddTypeChecked( m_fe.GetTypeID( i ) );
        }
    }
    m_sse.SetBegDateStr( m_textCtrlBegDatePt->GetValue() );
    m_sse.SetEndDateStr( m_textCtrlEndDatePt->GetValue() );
    m_sse.SetIndIDs( m_indIDs );
    return true;
}

void rgDlgSelectEvent::OnIdle( wxIdleEvent& event )
{
    bool changed = false;
    if( m_begDatePt != m_fe.GetBegDatePt() ||
        m_endDatePt != m_fe.GetEndDatePt()
    ) {
        m_fe.SetBegDatePt( m_begDatePt );
        m_fe.SetEndDatePt( m_endDatePt );
        changed = true;
    }
    if( IndIDsChanged() ) {
        m_fe.SetIndIDs( m_indIDs );
        changed = true;
    }
    if( changed ) {
        Refresh();
    }
}

void rgDlgSelectEvent::OnGroupCheckToggled( wxCommandEvent& event )
{
    int i = event.GetInt();
    bool chk = m_checkListGrp->wxCheckListBox::IsChecked( i );

    m_fe.SetGroupsChecked( m_fe.GetGroupsChecked() ^ ( 1 << m_grps[i] ) );
    CreateTypeList();
}

void rgDlgSelectEvent::OnGroupCheckSelect( wxCommandEvent& event )
{
    int i = event.GetInt();
    if( m_checkListGrp->IsSelected( i ) ) {
        bool flag = m_checkListGrp->wxCheckListBox::IsChecked( i );
        m_checkListGrp->Check( i, !flag );
        m_checkListGrp->SetSelection( wxNOT_FOUND );
        m_fe.SetGroupsChecked( m_fe.GetGroupsChecked() ^ ( 1 << m_grps[i] ) );
        CreateTypeList();
    }
}

void rgDlgSelectEvent::OnTypeCheckToggled( wxCommandEvent& event )
{
    int i = event.GetInt();
    bool flag = m_checkListType->wxCheckListBox::IsChecked( i );
    m_fe.SetTypeFlag( i, flag );
    Refresh();
}

void rgDlgSelectEvent::OnTypeCheckSelect( wxCommandEvent& event )
{
    int i = event.GetInt();
    if( m_checkListType->IsSelected( i ) ) {
        bool flag = m_checkListType->wxCheckListBox::IsChecked( i );
        m_checkListType->Check( i, !flag );
        m_checkListType->SetSelection( wxNOT_FOUND );
        m_fe.SetTypeFlag( i, !flag );
        Refresh();
    }
}

void rgDlgSelectEvent::OnBegDateText( wxCommandEvent& event )
{
    wxString str = m_textCtrlBegDatePt->GetValue();
    if( str.size() ) {
        long jdn1, jdn2;
        if( calStrToJdnRange( &jdn1, &jdn2, str, CALENDAR_SCH_Gregorian ) ) {
            m_begDatePt = jdn1;
        }
    } else {
        m_begDatePt = 0;
    }
}

void rgDlgSelectEvent::OnEndDateText( wxCommandEvent& event )
{
    wxString str = m_textCtrlEndDatePt->GetValue();
    if( str.size() ) {
        long jdn1, jdn2;
        if( calStrToJdnRange( &jdn1, &jdn2, str, CALENDAR_SCH_Gregorian ) ) {
            m_endDatePt = jdn2;
        }
    } else {
        m_endDatePt = 0;
    }
}

void rgDlgSelectEvent::OnIndIdText( wxCommandEvent& event )
{
    wxString str = m_textCtrlIndID->GetValue();
    m_indIDs = recIndividual::GetIdVecFromStr( str );
}

void rgDlgSelectEvent::OnListEventItemDeselected( wxListEvent& event )
{
    if( !m_selList ) {
        m_buttonSelect->Enable( false );
    }
}

void rgDlgSelectEvent::OnListEventItemSelected( wxListEvent& event )
{
    if( !m_selList ) {
        m_buttonSelect->Enable( true );
    }
}

void rgDlgSelectEvent::OnCreateButton( wxCommandEvent& event )
{
    m_create = true;
    EndDialog( wxID_OK );
}

bool rgDlgSelectEvent::IndIDsChanged() const
{
    const recIdVec& indIDs = m_fe.GetIndIDs();

    if( indIDs.size() != m_indIDs.size() ) {
        return true;
    }
    for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
        if( indIDs[i] != m_indIDs[i] ) {
            return true;
        }
    }
    return false;
}

void rgDlgSelectEvent::SetGroupAll( bool check )
{
    unsigned grps_chkd = m_fe.GetGroupsChecked();
    for( size_t i = 0 ; i < m_grps.size() ; i++ ) {
        m_checkListGrp->Check( i, check );
        unsigned flag = 1 << m_grps[i];
        if( check ) {
            grps_chkd |= flag;
        } else {
            grps_chkd &= flag;
        }
    }
    m_fe.SetGroupsChecked( grps_chkd );
    CreateTypeList();
}

void rgDlgSelectEvent::CreateTypeList()
{
    m_fe.ResetTypeIDs( true );

    wxArrayString typeStrings;
    for( size_t i = 0 ; i < m_fe.GetTypesSize() ; i++ ) {
        idt typeID = m_fe.GetTypeID( i );
        typeStrings.push_back( recEventType::GetName( typeID ) );
    }
    if( m_fe.GetTypesSize() ) {
        m_checkListType->Enable( true );
    } else {
        m_checkListType->Enable( false );
    }
    m_checkListType->Set( typeStrings );
    SetTypeAll( true );
}

void rgDlgSelectEvent::UpdateTypeCtrl()
{
    wxArrayString typeStrings;
    for( size_t i = 0 ; i < m_fe.GetTypesSize() ; i++ ) {
        idt typeID = m_fe.GetTypeID( i );
        typeStrings.push_back( recEventType::GetName( typeID, m_sse.GetDbname() ) );
    }
    if( m_fe.GetTypesSize() ) {
        m_checkListType->Enable( true );
    } else {
        m_checkListType->Enable( false );
    }
    m_checkListType->Set( typeStrings );
}

void rgDlgSelectEvent::UpdateTypeList()
{
    for( size_t i = 0 ; i < m_fe.GetTypesSize() ; i++ ) {
        bool chk = m_fe.GetTypeChecked( i );
        m_checkListType->Check( i, chk );
    }
}

void rgDlgSelectEvent::SetTypeAll( bool check )
{
    size_t size = m_fe.GetTypesSize();
    for( size_t i = 0 ; i < size ; i++ ) {
        m_fe.SetTypeFlag( i, check );
        m_checkListType->Check( i, check );
    }
    Refresh();
}

void rgDlgSelectEvent::Refresh()
{
    // Remove any selection first
    if( m_fe.GetTableSize() > 0 && m_listEvent->GetSelectedItemCount() > 0 ) {
        long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
        m_listEvent->SetItemState( row, 0, wxLIST_STATE_SELECTED );
    }
    m_fe.CreateEventTable( m_sse.GetDbname() );
    m_listEvent->SetTable( m_fe.GetTable() );
    m_listEvent->Refresh();
    m_staticEventCount->SetLabel( wxString::Format( "%d Events", m_fe.GetTableSize() ) );
    if( !m_selList ) {
        m_buttonSelect->Enable( false );
    }
}

// End of src/rg/rgSelEvent.cpp file
