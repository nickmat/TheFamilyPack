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

#include <rec/recLink.h>

#include "dlgEdIndEvent.h"


//-----------------------------------------------------
//      dlgEditIndEvent
//-----------------------------------------------------

dlgEditIndEvent::dlgEditIndEvent( wxWindow* parent )
    : fbDlgEditIndEvent2( parent )
{
    m_event.Clear();
    m_date1.Clear();
    m_place.Clear();

    m_listPersona->InsertColumn( COL_IndID, _("Individual") );
    m_listPersona->InsertColumn( COL_Name, _("Name") );
    m_listPersona->InsertColumn( COL_Role, _("Role") );
    m_listPersona->InsertColumn( COL_Note, _("Note") );
}

bool dlgEditIndEvent::TransferDataToWindow()
{
    if( m_event.f_id ) {
        m_event.Read();
    } else {
        m_event.Save();
    }
    m_staticType->SetLabel( m_event.GetTypeStr() );
    m_staticEventID->SetLabel( m_event.GetIdStr() );
    m_textCtrlTitle->SetValue( m_event.f_title );
    if( m_event.f_date1_id == 0 ) {
        m_date1.SetDefaults();
        m_date1.Save();
    } else {
        m_date1.f_id = m_event.f_date1_id;
        m_date1.Read();
    }
    m_textCtrlDate1->SetValue( m_date1.GetStr() );
    m_buttonDate2->Enable( false );
    if( m_event.f_place_id == 0 ) {
        m_place.Clear();
        m_place.Save();
    } else {
        m_place.f_id = m_event.f_place_id;
        m_place.Read();
    }
    m_textCtrlAddr->SetValue( m_place.GetAddressStr() );
    m_textCtrlNote->SetValue( m_event.f_note );

    m_evpers = m_event.GetEventPersonas();
    m_individuals.clear();
    recIndividual ind;
    for( size_t i = 0 ; i < m_evpers.size() ; i++ ) {
        ind.ReadPersona( m_evpers[i].f_per_id );
        m_individuals.push_back( ind );
        m_listPersona->InsertItem( i, ind.GetIdStr() );
        m_listPersona->SetItem( i, COL_Name, ind.GetFullName() );
        m_listPersona->SetItem( i, COL_Role, recEventTypeRole::GetName( m_evpers[i].f_role_id ) );
        m_listPersona->SetItem( i, COL_Note, m_evpers[i].f_note );
    }

    m_refEventIDs = recLinkEvent::FindEquivRefEvents( m_event.f_id );
    m_htmlWin2->SetPage( WrReferenceEvents() );
    return true;
}

wxString dlgEditIndEvent::WrReferenceEvents()
{

//    size_t i, j, cnt;
//    recIndividual ind( indID );
//    recPersona per( ind.f_per_id );
//    recIndividual spouse;
    wxString htm;

    htm << "<html><head><title>"
        << m_event.f_title << "</title></head>"
           "<body><center><table width=100%>";


    for( size_t i = 0 ; i < m_refEventIDs.size() ; i++ ) {
        recEvent e(m_refEventIDs[i]);
        htm << "<tr><td>"
            << e.f_title
            << "</td></tr>";
    }


#if 0
    wxSQLite3Table eTable = ind.GetRefEventsTable();
    for( size_t j = 0 ; j < (size_t) eTable.GetRowCount() ; j++ ) {
        eTable.SetRow( j );
        idt eventID = GET_ID( eTable.GetInt64( 0 ) );
        idt roleID = GET_ID( eTable.GetInt64( 1 ) );
        idt refID = recEvent::FindReferenceID( eventID );

        htm << "<tr><td align=right>"
            << recEventTypeRole::GetName( roleID )
            << ":</td><td><b>"
            << recEvent::GetTitle( eventID );
        if( refID != 0 ) {
            htm << " <a href=R" << refID
                << "><img src=memory:ref.bmp></a>";
        }
        htm << "<br>"
            << recEvent::GetDetailStr( eventID )
            << "</b></td></tr>";
    }
#endif
    htm << "</table></center></body></html>";

    return htm;
}

bool dlgEditIndEvent::TransferDataFromWindow()
{
    wxASSERT( m_event.f_type_id != 0 );

    m_event.f_title = m_textCtrlTitle->GetValue();

    wxString str = m_textCtrlDate1->GetValue();
    if( str.IsEmpty() ) {
        m_date1.Delete();
        m_event.f_date1_id = 0;
    } else {
        m_date1.SetDate( str );
        m_date1.Save();
        m_event.f_date1_id = m_date1.f_id;
    }

    m_event.f_date2_id = 0;

    str = m_textCtrlAddr->GetValue();
    if( str.IsEmpty() ) {
        m_place.Delete();
        m_event.f_place_id = 0;
    } else {
        m_place.SetAddress( str );
        m_place.Save();
        m_event.f_place_id = m_place.f_id;
    }

    m_event.f_note = m_textCtrlNote->GetValue();

    m_event.Save();
    return true;
}

void dlgEditIndEvent::OnDate1Button( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDate1Button")
    );
}

void dlgEditIndEvent::OnAddrButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nAddress"),
        wxT("OnAddrButton")
    );
}


//-----------------------------------------------------
//      dlgEditIndEvent
//-----------------------------------------------------

dlgEditIndEvent_::dlgEditIndEvent_( wxWindow* parent )
    : fbDlgEditIndEvent( parent )
{
    m_event.Clear();
    m_date1.Clear();
    m_place.Clear();
}

bool dlgEditIndEvent_::TransferDataToWindow()
{
    m_staticType->SetLabel( m_event.GetTypeStr() );

    m_textCtrlTitle->SetValue( m_event.f_title );

    if( m_event.f_date1_id == 0 ) {
        m_date1.SetDefaults();
        m_date1.Save();
    } else {
        m_date1.f_id = m_event.f_date1_id;
        m_date1.Read();
    }
    m_textCtrlDate1->SetValue( m_date1.GetStr() );

    m_buttonDate2->Enable( false );

    if( m_event.f_place_id == 0 ) {
        m_place.Clear();
        m_place.Save();
    } else {
        m_place.f_id = m_event.f_place_id;
        m_place.Read();
    }
    m_textCtrlAddr->SetValue( m_place.GetAddressStr() );

    m_textCtrlNote->SetValue( m_event.f_note );

    return true;
}

bool dlgEditIndEvent_::TransferDataFromWindow()
{
    wxASSERT( m_event.f_type_id != 0 );

    m_event.f_title = m_textCtrlTitle->GetValue();

    wxString str = m_textCtrlDate1->GetValue();
    if( str.IsEmpty() ) {
        m_date1.Delete();
        m_event.f_date1_id = 0;
    } else {
        m_date1.SetDate( str );
        m_date1.Save();
        m_event.f_date1_id = m_date1.f_id;
    }

    m_event.f_date2_id = 0;

    str = m_textCtrlAddr->GetValue();
    if( str.IsEmpty() ) {
        m_place.Delete();
        m_event.f_place_id = 0;
    } else {
        m_place.SetAddress( str );
        m_place.Save();
        m_event.f_place_id = m_place.f_id;
    }

    m_event.f_note = m_textCtrlNote->GetValue();

    m_event.Save();
    return true;
}

void dlgEditIndEvent_::OnDate1Button( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDate1Button")
    );
}

void dlgEditIndEvent_::OnAddrButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nAddress"),
        wxT("OnAddrButton")
    );
}

//-----------------------------------------------------
//      dlgEditFamEvent
//-----------------------------------------------------

dlgEditFamEvent::dlgEditFamEvent(
    wxWindow* parent, idt eventID, recEventType::ETYPE_Grp grp
    ) : fbDlgEditFamEvent(parent), m_grp(grp)
{
    m_event.f_id = eventID;
}


bool dlgEditFamEvent::TransferDataToWindow()
{
    if( m_event.f_id == 0 ) {
        m_event.Clear();
        m_event.Save();
    } else {
        m_event.Read();
    }
    m_textCtrlTitle->SetValue( m_event.f_title );
    m_textCtrlType->SetValue( recEventType::GetTypeStr( m_event.f_type_id ) );
    m_textCtrlDate->SetValue( recDate::GetStr( m_event.f_date1_id ) );
    m_textCtrlAddr->SetValue( recPlace::GetAddressStr( m_event.f_place_id ) );
    m_textCtrlNote->SetValue( m_event.f_note );

    return true;
}


bool dlgEditFamEvent::TransferDataFromWindow()
{
    m_event.f_title = m_textCtrlTitle->GetValue();
    m_event.f_note = m_textCtrlNote->GetValue();
    m_event.Save();

    return true;
}

void dlgEditFamEvent::OnTypeButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nType"),
        wxT("OnTypeButton")
    );
}

void dlgEditFamEvent::OnDateButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDateButton")
    );
}

void dlgEditFamEvent::OnAddrButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nAddress"),
        wxT("OnAddrButton")
    );
}


// End of dlgEdIndEvent.cpp file
