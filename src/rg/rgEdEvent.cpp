/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual Event dialog.
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

#include <wx/fs_mem.h>

#include <rec/recLink.h>
#include <rg/rgDialogs.h>

#include "rgEdEvent.h"


bool rgEditEvent( idt eveID )
{
    wxASSERT( eveID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEvent* dialog = new rgDlgEditEvent( NULL, eveID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}


idt rgCreateIndEvent( idt ind1ID, idt ind2ID )
{
    wxASSERT( ind1ID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    unsigned grpfilter = recET_FILTER_GrpAll;
    if( ind2ID ) {
        grpfilter = recET_FILTER_GrpFamily;
    }
    idt typeID = rgSelectEventType( rgSELSTYLE_Create, NULL, grpfilter );
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    recEvent eve(0);
    eve.FSetTypeID( typeID );
    eve.SetAutoTitle(
        recIndividual::GetFullName( ind1ID ),
        recIndividual::GetFullName( ind2ID )
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
    if( ! rgEditIndEventRole( ie.FGetID(), sr )  ) {
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
        if( ! rgEditIndEventRole( ie.FGetID(), sr )  ) {
            recDb::Rollback( savepoint );
            return 0;
        }
    }

    if( ! rgEditEvent( eveID ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return eveID;
}

//============================================================================
//-------------------------[ rgDlgEditEvidEvent ]-----------------------------
//============================================================================

rgDlgEditEvent::rgDlgEditEvent( wxWindow* parent, idt eventID )
    : fbRgEditEvent( parent ), m_event(eventID)
{
    m_date1ID = m_event.FGetDate1ID();
    m_date2ID = m_event.FGetDate2ID();
    m_placeID = m_event.FGetPlaceID();

    m_listPersona->InsertColumn( COL_IndID, _("Individual") );
    m_listPersona->InsertColumn( COL_Name, _("Name") );
    m_listPersona->InsertColumn( COL_Role, _("Role") );
    m_listPersona->InsertColumn( COL_Note, _("Note") );
}

bool rgDlgEditEvent::TransferDataToWindow()
{
    wxASSERT( m_event.GetID() != 0 );
    m_staticType->SetLabel( m_event.GetTypeStr() );
    m_staticEventID->SetLabel( m_event.GetIdStr() );
    m_textCtrlTitle->SetValue( m_event.f_title );
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
    return true;
}

void rgDlgEditEvent::ListLinkedPersona()
{
    m_ies = m_event.GetIndividualEvents();
    m_individuals.clear();
    recIndividual ind;
    m_listPersona->DeleteAllItems();
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        ind.ReadID( m_ies[i].FGetIndID() );
        m_individuals.push_back( ind );
        m_listPersona->InsertItem( i, ind.GetIdStr() );
        m_listPersona->SetItem( i, COL_Name, ind.GetFullName() );
        m_listPersona->SetItem( i, COL_Role, recEventTypeRole::GetName( m_ies[i].f_role_id ) );
        m_listPersona->SetItem( i, COL_Note, m_ies[i].f_note );
    }
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
        m_date1ID = rgCreateDate();
        if( m_date1ID == 0 ) {
            return;
        }
    } else {
        if( !rgEditDate( m_date1ID ) ) {
            return;
        }
    }
    m_textCtrlDate1->SetValue( recDate::GetStr( m_date1ID ) );
}

void rgDlgEditEvent::OnDate2Button( wxCommandEvent& event )
{
    if( m_date2ID == 0 ) {
        m_date2ID = rgCreateDate();
        if( m_date2ID == 0 ) {
            return;
        }
    } else {
        if( !rgEditDate( m_date2ID ) ) {
            return;
        }
    }
    m_textCtrlDate1->SetValue( recDate::GetStr( m_date2ID ) );
}

void rgDlgEditEvent::OnPlaceButton( wxCommandEvent& event )
{
    if( m_placeID == 0 ) {
        m_placeID = rgCreatePlace();
        if( m_placeID == 0 ) {
            return;
        }
    } else {
        if( !rgEditPlace( m_placeID ) ) {
            return;
        }
    }
    m_textCtrlPlace->SetValue( recPlace::GetAddressStr( m_placeID ) );
}

void rgDlgEditEvent::OnAddButton( wxCommandEvent& event )
{
    if( rgCreateIndEventRole( 0, m_event.FGetID(), 0 ) ) {
        ListLinkedPersona();
    }
}

void rgDlgEditEvent::OnEditButton( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Individual") );
        return;
    }
    EditRow( row );
}

void rgDlgEditEvent::EditRow( long row )
{
    idt ieID = m_ies[row].FGetID();
    if( rgEditIndEventRole( ieID ) ) {
        ListLinkedPersona();
    }
}

void rgDlgEditEvent::OnDeleteButton( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Link") );
        return;
    }
    DeleteRow( row );
}

void rgDlgEditEvent::DeleteRow( long row )
{
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
    ListLinkedPersona();
}

// End of dlgEdIndEvent.cpp file
