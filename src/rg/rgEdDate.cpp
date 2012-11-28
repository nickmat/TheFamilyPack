/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Date entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     28th November 2012
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

#include "rgEdDate.h"

//============================================================================
//-------------------------[ rgDlgEditDate ]----------------------------------
//============================================================================


CalendarScheme rgDate::scheme[] = {
    CALENDAR_SCH_Unstated,
    CALENDAR_SCH_JulianDayNumber,
    CALENDAR_SCH_Julian,
    CALENDAR_SCH_Gregorian
};

int rgDate::sch_list[CALENDAR_SCH_Max] = {
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

using namespace rgDate;

rgDlgEditDate::rgDlgEditDate( wxWindow* parent, idt dateID )
    : m_date(dateID), fbRgEditDate( parent )
{
}

bool rgDlgEditDate::TransferDataToWindow()
{
    wxASSERT( m_date.FGetID() != 0  );
    wxASSERT( m_date.f_rel_id == 0 );

    m_staticDateID->SetLabel( m_date.GetIdStr() );
    m_choiceType->SetSelection( m_date.f_type );
    m_choiceInput->SetSelection( sch_list[m_date.f_record_sch] );
    m_choiceDisplay->SetSelection( sch_list[m_date.f_display_sch] );

    m_output = m_date.GetJdnStr();
    m_textCtrlDate->SetValue( m_output );
    return true;
}

bool rgDlgEditDate::TransferDataFromWindow()
{
    m_date.f_type = m_choiceType->GetSelection();
    m_date.f_record_sch = scheme[ m_choiceInput->GetSelection() ];
    m_date.f_display_sch = scheme[ m_choiceDisplay->GetSelection() ];
    m_date.SetDate( m_textCtrlDate->GetValue() );

    m_date.Save();
    return true;
}

void rgDlgEditDate::OnIdle( wxIdleEvent& event )
{
    recDate date(0);
    date.f_type = m_choiceType->GetSelection();
    date.f_record_sch = scheme[ m_choiceInput->GetSelection() ];
    date.f_display_sch = scheme[ m_choiceDisplay->GetSelection() ];
    date.SetDate( m_textCtrlDate->GetValue() );

    wxString str;
    if( date.f_descrip.IsEmpty() ) {
        str = date.GetStr();
    } else {
        str = "*";
    }
    if( str != m_output ) {
        m_staticOutput->SetLabel( str );
        m_output = str;
    }
}

//===========================================================================
//       dlgEditDateFromAge
//===========================================================================
#if 0
CalendarUnit dlgEditDateFromAge::unit[] = {
    CALENDAR_UNIT_Year,
    CALENDAR_UNIT_Month,
    CALENDAR_UNIT_Week,
    CALENDAR_UNIT_Day
};

dlgEditDateFromAge::dlgEditDateFromAge( wxWindow* parent, idt baseID, idt dateID )
    : fbDlgEditDateFromAge( parent )
{
    m_base.f_id = baseID;
    m_base.Read();
    m_basestr = m_base.GetStr();
    m_date.f_id = dateID;
    m_date.Read();
}

bool dlgEditDateFromAge::TransferDataToWindow()
{
    m_textCtrlBaseDate->SetValue( m_basestr );

    if( m_date.f_id == 0 ) {
        m_relative.Clear();
        m_relative.f_range = 1;
        m_relative.f_base_id = m_base.f_id;
        m_relative.f_type = recRelativeDate::TYPE_AgeRoundDown;
        m_relative.f_scheme = m_base.f_record_sch;
        m_relative.Save();
        m_date.Clear();
        m_date.f_rel_id = m_relative.f_id;
        m_date.Save();
        // TODO: This needs to be set up using a particular convention
        m_date.f_type = recDate::PREF_On;
        m_date.f_record_sch = m_base.f_record_sch;
        m_date.f_display_sch = m_base.f_display_sch;

    } else {
        m_date.Read();
        m_relative.Read();
        m_text = m_date.GetJdnStr();
    }
    m_textCtrlAge->SetValue( m_text );

    m_staticTextId->SetLabel( m_date.GetIdStr() );
    m_choiceType->SetSelection( m_date.f_type );
    m_choiceDisplay->SetSelection( dlgEditDate::sch_list[m_date.f_display_sch] );

    return true;
}

bool dlgEditDateFromAge::TransferDataFromWindow()
{
    CalcDate();
    m_date.Save();
    m_relative.Save();
    return true;
}

void dlgEditDateFromAge::SetStaticDate( wxIdleEvent& event )
{
    CalcDate();
    wxString str = m_date.GetStr();
    if( str != m_output ) {
        m_staticTextOutput->SetLabel( str );
        m_output = str;
    }
}

void dlgEditDateFromAge::CalcDate()
{
    m_date.f_type = m_choiceType->GetSelection();
    m_date.f_record_sch = dlgEditDate::scheme[ m_choiceDisplay->GetSelection() ];
    wxString agestr = m_textCtrlAge->GetValue();
    agestr.ToLong( &m_relative.f_val );
    m_relative.f_unit = unit[ m_radioBoxUnits->GetSelection() ];
    m_relative.CalculateDate( m_date );
}
#endif
// End of dlgEdDate.cpp file
