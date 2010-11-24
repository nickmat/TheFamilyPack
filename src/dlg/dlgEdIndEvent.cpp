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

#include "dlgEdIndEvent.h"

dlgEditIndEvent::dlgEditIndEvent( wxWindow* parent )
    : fbDlgEditIndEvent( parent )
{
    m_pEvent = NULL;
}

bool dlgEditIndEvent::TransferDataToWindow()
{
    wxASSERT( m_pEvent != NULL );
    if( m_pEvent == NULL ) return false;

    m_staticTextType->SetLabel( m_pEvent->GetTypeStr() );
    if( m_pEvent->f_date1_id == 0 ) {
        m_date1.SetDefaults();
        m_date1.Save();
    } else {
        m_date1.f_id = m_pEvent->f_date1_id;
        m_date1.Read();
    }
    m_textCtrlDate->SetValue( m_date1.GetStr() );
    if( m_pEvent->f_place_id == 0 ) {
        m_place.Clear();
        m_place.Save();
    } else {
        m_place.f_id = m_pEvent->f_place_id;
        m_place.Read();
    }
    m_textCtrlAddr->SetValue( m_place.GetAddressStr() );

    return true;
}

bool dlgEditIndEvent::TransferDataFromWindow()
{
    wxASSERT( m_pEvent != NULL );
    if( m_pEvent == NULL ) return false;

    wxString str = m_textCtrlDate->GetValue();
    if( str.IsEmpty() ) {
        m_date1.Delete();
        m_pEvent->f_date1_id = 0;
    } else {
        m_date1.SetDate( str );
        m_date1.Save();
        m_pEvent->f_date1_id = m_date1.f_id;
    }

    str = m_textCtrlAddr->GetValue();
    if( str.IsEmpty() ) {
        m_place.Delete();
        m_pEvent->f_place_id = 0;
    } else {
        m_place.SetAddress( str );
        m_place.Save();
        m_pEvent->f_place_id = m_place.f_id;
    }

    if( m_pEvent->f_date1_id == 0 && m_pEvent->f_place_id == 0 ) {
        m_pEvent->Delete();
        m_pEvent->Clear();
    } else {
        m_pEvent->Save();
    }

    return true;
}

void dlgEditIndEvent::OnDateButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDateButton")
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
//      dlgEditFamEvent
//-----------------------------------------------------

dlgEditFamEvent::dlgEditFamEvent(
    wxWindow* parent, id_t eventID, recEventType::ETYPE_Grp grp
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
