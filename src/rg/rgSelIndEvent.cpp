/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSelIndEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select Event dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     5th December 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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
#include "rgSelIndEvent.h"
#include "rg/rgDialogs.h"

bool rgSelectIndEventList( wxWindow* wind, recFilterEvent* evefilter )
{
    wxASSERT( evefilter != NULL );
    idt ret = rgSelectIndEvent( wind, rgSELSTYLE_SelList, evefilter );
    if( ret == 0 ) {
        return false;
    }
    return true;
}

idt rgSelectIndEvent( wxWindow* wind, unsigned selstyle, recFilterEvent* exfilter, bool* ok, idt indID )
{
    idt eveID = 0;
    bool cont = true;
    recFilterEvent* fe = exfilter;
    if( fe == NULL ) {
        fe = new recFilterEvent;
    }
    if( ok ) *ok = false;

    rgDlgSelectIndEvent* dialog = new rgDlgSelectIndEvent( wind, selstyle, fe );
    if( dialog->ShowModal() == wxID_OK ) {
        if( ok ) *ok = true;
        if( dialog->GetCreatePressed() ) {
            eveID = rgCreateIndEvent( wind, indID );
            if( eveID == 0 && ok ) *ok = false;
        } else if( dialog->GetUnknownPressed() ) {
            eveID = 0;
        } else {
            eveID = dialog->GetID();
        }
    }
    dialog->Destroy();
    if( exfilter == NULL ) {
        delete fe;
    }
    return eveID;
}

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectIndEvent ]-------------------------------------
//-------------------------------------------------------------------------------

rgDlgSelectIndEvent::rgDlgSelectIndEvent( wxWindow* parent, unsigned selstyle, recFilterEvent* fe )
    : m_create(false), m_selList(false), m_fe(fe),
    m_begDatePt(0), m_endDatePt(0), fbRgSelectIndEvent( parent )
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

bool rgDlgSelectIndEvent::TransferDataToWindow()
{
    m_fe->SetFEClass( recFilterEvent::FE_Ind ); // TODO: allow for FE_Ref as well.
    wxArrayString grpStrings = recEventType::GetGroupStrings( 1 );
    m_checkListGrp->InsertItems( grpStrings, 0 );
    for( size_t i = 1 ; i < recEventType::ETYPE_Grp_MAX ; i++ ) {
        bool flag = m_fe->GetGroupFlag( i );
        m_checkListGrp->Check( i-1, flag );
    }
    CreateTypeList();
    m_textCtrlBegDatePt->SetValue( m_fe->GetBegDatePtStr() );
    m_textCtrlEndDatePt->SetValue( m_fe->GetEndDatePtStr() );
    return true;
}

bool rgDlgSelectIndEvent::TransferDataFromWindow()
{
    m_fe->SetBegDatePtStr( m_textCtrlBegDatePt->GetValue() );
    m_fe->SetEndDatePtStr( m_textCtrlEndDatePt->GetValue() );
    return true;
}

void rgDlgSelectIndEvent::OnIdle( wxIdleEvent& event )
{
    if( m_begDatePt != m_fe->GetBegDatePt() || m_endDatePt != m_fe->GetEndDatePt() ) {
        m_fe->SetBegDatePt( m_begDatePt );
        m_fe->SetEndDatePt( m_endDatePt );
        Refresh();
    }
}

void rgDlgSelectIndEvent::OnGroupCheckToggled( wxCommandEvent& event )
{
    int i = event.GetInt();
    bool flag = m_checkListGrp->wxCheckListBox::IsChecked( i );
    m_fe->SetGroupFlag( i+1, flag );
    CreateTypeList();
}

void rgDlgSelectIndEvent::OnGroupCheckSelect( wxCommandEvent& event )
{
    int i = event.GetInt();
    if( m_checkListGrp->IsSelected( i ) ) {
        bool flag = m_checkListGrp->wxCheckListBox::IsChecked( i );
        m_checkListGrp->Check( i, !flag );
        m_checkListGrp->SetSelection( wxNOT_FOUND );
        m_fe->SetGroupFlag( i+1, !flag );
        CreateTypeList();
    }
}

void rgDlgSelectIndEvent::SetGroupAll( bool check )
{
    for( size_t i = 1 ; i < recEventType::ETYPE_Grp_MAX ; i++ ) {
        m_checkListGrp->Check( i-1, check );
        m_fe->SetGroupFlag( i, check );
    }
    CreateTypeList();
}

void rgDlgSelectIndEvent::CreateTypeList()
{
    unsigned grpfilter = 0;
    for( size_t i = 1 ; i < recEventType::ETYPE_Grp_MAX ; i++ ) {
        bool flag = m_fe->GetGroupFlag( i );
        switch( (recEventType::ETYPE_Grp) i )
        {
        case recEventType::ETYPE_Grp_Birth:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpBirth;
            }
            break;
        case recEventType::ETYPE_Grp_Nr_Birth:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpNrBirth;
            }
            break;
        case recEventType::ETYPE_Grp_Union:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpFamUnion;
            }
            break;
        case recEventType::ETYPE_Grp_Family:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpFamOther;
            }
            break;
        case recEventType::ETYPE_Grp_Death:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpDeath;
            }
            break;
        case recEventType::ETYPE_Grp_Nr_Death:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpNrDeath;
            }
            break;
        case recEventType::ETYPE_Grp_Other:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpOther;
            }
            break;
        case recEventType::ETYPE_Grp_Personal:
            if( flag ) {
                grpfilter |= recET_FILTER_GrpPersonal;
            }
            break;
        default:
            wxASSERT( false ); // Shouldn't be here!
        }
    }

    wxArrayString typeStrings;
    m_fe->ClearTypeIDs();
    recEventTypeVec ets = recEventType::ReadVec( grpfilter );
    for( size_t i = 0 ; i < ets.size() ; i++ ) {
        typeStrings.push_back( ets[i].FGetName() );
        m_fe->AddTypeIDs( ets[i].FGetID() );
    }
    if( ets.size() ) {
        m_checkListType->Enable( true );
        m_checkListType->Set( typeStrings );
    } else {
        m_checkListType->Enable( false );
        m_checkListType->Set( typeStrings );
    }
    SetTypeAll( true );
}

void rgDlgSelectIndEvent::OnTypeCheckToggled( wxCommandEvent& event )
{
    int i = event.GetInt();
    bool flag = m_checkListType->wxCheckListBox::IsChecked( i );
    m_fe->SetTypeFlag( i, flag );
    Refresh();
}

void rgDlgSelectIndEvent::OnTypeCheckSelect( wxCommandEvent& event )
{
    int i = event.GetInt();
    if( m_checkListType->IsSelected( i ) ) {
        bool flag = m_checkListType->wxCheckListBox::IsChecked( i );
        m_checkListType->Check( i, !flag );
        m_checkListType->SetSelection( wxNOT_FOUND );
        m_fe->SetTypeFlag( i, !flag );
        Refresh();
    }
}

void rgDlgSelectIndEvent::OnBegDateText( wxCommandEvent& event )
{
    wxString str = m_textCtrlBegDatePt->GetValue();
    if( str.size() ) {
        long jdn1, jdn2;
        if( calStrToJdnRange( &jdn1, &jdn2, str, CALENDAR_SCH_Gregorian ) ) {
            m_begDatePt = jdn1;
        }
    }
}

void rgDlgSelectIndEvent::OnListEventItemDeselected( wxListEvent& event )
{
    if( !m_selList ) {
        m_buttonSelect->Enable( false );
    }
}

void rgDlgSelectIndEvent::OnListEventItemSelected( wxListEvent& event )
{
    if( !m_selList ) {
        m_buttonSelect->Enable( true );
    }
}

void rgDlgSelectIndEvent::OnCreateButton( wxCommandEvent& event )
{
    m_create = true;
    EndDialog( wxID_OK );
}

void rgDlgSelectIndEvent::OnEndDateText( wxCommandEvent& event )
{
    wxString str = m_textCtrlEndDatePt->GetValue();
    if( str.size() ) {
        long jdn1, jdn2;
        if( calStrToJdnRange( &jdn1, &jdn2, str, CALENDAR_SCH_Gregorian ) ) {
            m_endDatePt = jdn2;
        }
    }
}

void rgDlgSelectIndEvent::SetTypeAll( bool check )
{
    size_t size = m_fe->GetTypesSize();
    for( size_t i = 0 ; i < size ; i++ ) {
        m_fe->SetTypeFlag( i, check );
        m_checkListType->Check( i, check );
    }
    Refresh();
}

void rgDlgSelectIndEvent::Refresh()
{
    // Remove any selection first
    if( m_fe->GetTableSize() > 0 && m_listEvent->GetSelectedItemCount() > 0 ) {
        long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
        m_listEvent->SetItemState( row, 0, wxLIST_STATE_SELECTED );
    }
    m_fe->CreateEventTable();
    m_listEvent->SetTable( m_fe->GetTable() );
    m_listEvent->Refresh();
    m_staticEventCount->SetLabel( wxString::Format( "%d Events", m_fe->GetTableSize() ) );
    if( !m_selList ) {
        m_buttonSelect->Enable( false );
    }
}

idt rgDlgSelectIndEvent::GetID() const
{
    if( m_fe->GetTableSize() > 0 ) {
        if( m_selList ) {
            return m_fe->GetIdForRow( 0 );
        } else if( m_listEvent->GetSelectedItemCount() > 0 ) {
            long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
            return m_fe->GetIdForRow( row );
        }
    }
    return 0;
}

// End of src/rg/rgSelIndEvent.cpp file
