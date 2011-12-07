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
    m_event.Clear();
    m_date1.Clear();
    m_place.Clear();
}

bool dlgEditIndEvent::TransferDataToWindow()
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
