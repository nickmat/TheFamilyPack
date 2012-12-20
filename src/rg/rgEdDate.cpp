/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Date dialogs.
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
    0    // CALENDAR_SCH_FrenchRevolution
};

CalendarUnit rgDate::unit[] = {
    CALENDAR_UNIT_Year,
    CALENDAR_UNIT_Month,
    CALENDAR_UNIT_Week,
    CALENDAR_UNIT_Day
};

int rgDate::unit_list[CALENDAR_UNIT_Max] = {
    0,  // CALENDAR_UNIT_Unstated
    0,  // CALENDAR_UNIT_Year
    1,  // CALENDAR_UNIT_Month
    2,  // CALENDAR_UNIT_Week
    3   // CALENDAR_UNIT_Day
};

recRelativeDate::Type rgDate::calc[] = {
    recRelativeDate::TYPE_AgeRoundDown,
    recRelativeDate::TYPE_Duration
};

int rgDate::calc_list[recRelativeDate::TYPE_Max] = {
    0,  // TYPE_Unstated
    0,  // TYPE_AgeRoundDown
    1   // TYPE_Duration
};

using namespace rgDate;

//============================================================================
//-------------------------[ rgDlgEditDate ]----------------------------------
//============================================================================

rgDlgEditDate::rgDlgEditDate( wxWindow* parent, idt dateID )
    : m_date(dateID), fbRgEditDate( parent )
{
}

bool rgDlgEditDate::TransferDataToWindow()
{
    wxASSERT( CALENDAR_SCH_Max == 14 ); // Don't forget to update when adding schemes
    wxASSERT( m_date.FGetID() != 0  );
    wxASSERT( m_date.f_rel_id == 0 );

    m_staticDateID->SetLabel( m_date.GetIdStr() );
    if( m_date.FGetType() < 1 || m_date.FGetType() >= recDate::PREF_Max ) {
        m_date.FSetType( recDate::PREF_On );
    }
    m_choiceType->SetSelection( m_date.f_type - 1 );
    m_choiceInput->SetSelection( sch_list[m_date.f_record_sch] );
    m_choiceDisplay->SetSelection( sch_list[m_date.f_display_sch] );

    m_textCtrlDate->SetValue( m_date.GetJdnStr() );
    m_output = m_date.GetStr();
    m_staticOutput->SetLabel( m_output );
    return true;
}

bool rgDlgEditDate::TransferDataFromWindow()
{
    m_date.f_type = m_choiceType->GetSelection() + 1;
    m_date.f_record_sch = scheme[ m_choiceInput->GetSelection() ];
    m_date.f_display_sch = scheme[ m_choiceDisplay->GetSelection() ];
    m_date.SetJdnDate( m_textCtrlDate->GetValue() );

    m_date.Save();
    return true;
}

void rgDlgEditDate::OnIdle( wxIdleEvent& event )
{
    recDate date(0);
    date.f_type = m_choiceType->GetSelection() + 1;
    date.f_record_sch = scheme[ m_choiceInput->GetSelection() ];
    date.f_display_sch = scheme[ m_choiceDisplay->GetSelection() ];
    date.SetJdnDate( m_textCtrlDate->GetValue() );

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

//============================================================================
//-------------------------[ rgDlgEditDateFromAge ]---------------------------
//============================================================================


rgDlgEditRelativeDate::rgDlgEditRelativeDate( wxWindow* parent, idt dateID )
    : m_date(dateID),  fbRgEditRelativeDate( parent )
{
    m_relative.ReadID( m_date.FGetRelID() );
    m_base.ReadID( m_relative.FGetBaseID() );
}

bool rgDlgEditRelativeDate::TransferDataToWindow()
{
    wxASSERT( m_date.FGetID() != 0 );
    wxASSERT( m_relative.FGetID() != 0 );
    wxASSERT( m_base.FGetID() != 0 );

    m_staticOutput->SetLabel( m_date.GetStr() );
    m_choiceDisplay->SetSelection( sch_list[m_date.FGetDisplaySch()] );
    m_choiceType->SetSelection( m_date.FGetType() );
    m_textCtrlBase->SetValue( m_base.GetStr() );
    wxString age = wxString::Format( "%ld", m_relative.FGetValue() );
    m_textCtrlAge->SetValue( age );
    m_choiceInput->SetSelection( sch_list[m_relative.FGetScheme()] );
    m_unitday = m_unitdmy = unit_list[m_relative.FGetUnit()];
    if( m_unitday <= 1 ) {
        m_unitday = 2;
    }
    SetUnitRadio();
    m_radioUnits->SetSelection( unit_list[m_relative.FGetUnit()] );
    m_staticDateID->SetLabel( m_date.GetIdStr() );
    return true;
}

void rgDlgEditRelativeDate::SetUnitRadio()
{
    if( CalendarStructs[m_relative.FGetScheme()] == CALENDAR_STRUCT_Day ) {
        m_radioUnits->Enable( 0, false );
        m_radioUnits->Enable( 1, false );
        m_radioUnits->SetSelection( m_unitday );
    } else if( CalendarStructs[m_relative.FGetScheme()] == CALENDAR_STRUCT_Triple ) {
        m_radioUnits->Enable( 0, true );
        m_radioUnits->Enable( 1, true );
        m_radioUnits->SetSelection( m_unitdmy );
    } else {
        wxASSERT( false );
    }
}

bool rgDlgEditRelativeDate::TransferDataFromWindow()
{
    CalcDate();
    m_date.Save();
    m_relative.Save();
    return true;
}

void rgDlgEditRelativeDate::OnIdle( wxIdleEvent& event )
{
    CalcDate();
    wxString str = m_date.GetStr();
    if( str != m_output ) {
        m_staticOutput->SetLabel( str );
        m_output = str;
    }
    CalendarScheme sch = m_relative.FGetScheme();
    if( sch != m_scheme ) {
        SetUnitRadio();
        m_scheme = sch;
    } else {
        if( CalendarStructs[sch] == CALENDAR_STRUCT_Day ) {
            m_unitday = m_radioUnits->GetSelection();
        } else {
            m_unitdmy = m_radioUnits->GetSelection();
        }
    }
}

void rgDlgEditRelativeDate::OnBaseButton( wxCommandEvent& event )
{
    if( rgEditDate( m_base.FGetID() ) ) {
        m_base.Read();
        m_textCtrlBase->SetValue( m_base.GetStr() );
    }
}

void rgDlgEditRelativeDate::CalcDate()
{
    m_date.FSetDisplaySch( scheme[m_choiceDisplay->GetSelection()] );
    m_relative.FSetType( calc[m_choiceType->GetSelection()] );
    wxString agestr = m_textCtrlAge->GetValue();
    agestr.ToLong( &m_relative.f_val );
    m_relative.FSetScheme( scheme[m_choiceInput->GetSelection()] );
    m_date.FSetRecordSch( m_relative.FGetScheme() );
    m_relative.FSetUnit( unit[m_radioUnits->GetSelection()] );

    m_relative.CalculateDate( m_date );
}

// End of src/rg/rgEdDate.cpp file
