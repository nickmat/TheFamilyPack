/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Date entity dialog.
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

#include "dlgEdDate.h"

CalendarScheme dlgEditDate::scheme[] = {
    CALENDAR_SCH_Unstated,
    CALENDAR_SCH_JulianDayNumber,
    CALENDAR_SCH_Julian,
    CALENDAR_SCH_Gregorian
};

int dlgEditDate::sch_list[CALENDAR_SCH_Max] = {
    0,   // CALENDAR_SCH_Unstated
    0,   // CALENDAR_SCH_Unknown
    0,   // CALENDAR_SCH_Unlisted
    1,   // CALENDAR_SCH_JulianDayNumber
    0,   // CALENDAR_SCH_JulianDay
    0,   // CALENDAR_SCH_ModJulianDay
    0,   // CALENDAR_SCH_RataDie
    2,   // CALENDAR_SCH_Julian
    3,   // CALENDAR_SCH_Gregorian
    0,   // CALENDAR_SCH_Catholic
    0,   // CALENDAR_SCH_English
    0,   // CALENDAR_SCH_Scottish
    0,   // CALENDAR_SCH_Swedish
    0,   // CALENDAR_SCH_FrenchRevolution
};

dlgEditDate::dlgEditDate( wxWindow* parent, id_t id )
    : fbDlgEditDate( parent )
{
    m_date.f_id = id;
    m_date.Read();
}

bool dlgEditDate::TransferDataToWindow()
{
    if( m_date.f_id == 0 )
    {
        m_date.Clear();
        m_date.Save();
        // TODO: This needs to be set up using a particular convention
        m_date.f_type = recDate::PREF_On;
        m_date.f_record_sch = CALENDAR_SCH_Gregorian;
        m_date.f_display_sch = CALENDAR_SCH_Gregorian;
    } else {
        m_date.Read();
        m_text = m_date.GetJdnStr();
    }
    m_textCtrlDate->SetValue( m_text );

    wxString idStr = wxString::Format( "D "ID":", m_date.f_id );
    m_staticTextId->SetLabel( idStr );
    m_choiceType->SetSelection( m_date.f_type );
    m_choiceOriginal->SetSelection( sch_list[m_date.f_record_sch] );
    m_choiceDisplay->SetSelection( sch_list[m_date.f_display_sch] );

    return true;
}

bool dlgEditDate::TransferDataFromWindow()
{
    m_date.f_type = m_choiceType->GetSelection();
    m_date.f_record_sch = scheme[ m_choiceOriginal->GetSelection() ];
    m_date.f_display_sch = scheme[ m_choiceDisplay->GetSelection() ];
    m_date.SetDate( m_textCtrlDate->GetValue() );

    m_date.Save();
    return true;
}

void dlgEditDate::SetStaticDate( wxIdleEvent& event )
{
    recDate date(0);
    date.f_type = m_choiceType->GetSelection();
    date.f_record_sch = scheme[ m_choiceOriginal->GetSelection() ];
    date.f_display_sch = scheme[ m_choiceDisplay->GetSelection() ];
    date.SetDate( m_textCtrlDate->GetValue() );

    wxString str;
    if( date.f_desc.IsEmpty() ) {
        str = date.GetStr();
    } else {
        str = "*";
    }
    if( str != m_output ) {
        m_staticTextOutput->SetLabel( str );
        m_output = str;
    }
}



// End of dlgEdDate.cpp file
