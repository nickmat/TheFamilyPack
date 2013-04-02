/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Date dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     28th November 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012-2013, Nick Matthews.
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

#include "rg/rgDialogs.h"
#include "rgEdDate.h"

bool rgEditDate( wxWindow* wind, idt dateID )
{
    wxASSERT( dateID != 0 );
    if( recDate::IsRelative( dateID ) ) {
        return rgEditRelativeDate( wind, dateID );
    }
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditDate* dialog = new rgDlgEditDate( wind, dateID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateDate( wxWindow* wind, const wxString& dateStr )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recDate date(0);
    date.SetDefaults();
    if( dateStr.size() ) {
        date.SetDate( dateStr );
    }
    date.Save();
    idt dateID = date.FGetID();
    if( rgEditDate( wind, dateID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return dateID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

CalendarScheme rgDate::scheme[] = {
    CALENDAR_SCH_Unstated,
    CALENDAR_SCH_JulianDayNumber,
    CALENDAR_SCH_Julian,
    CALENDAR_SCH_Gregorian,
    CALENDAR_SCH_FrenchRevolution,
    CALENDAR_SCH_IslamicTabular,
    CALENDAR_SCH_Hebrew
};
size_t rgDate::SchemeListSize = sizeof( rgDate::scheme ) / sizeof( CalendarScheme );

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
    4,   // CALENDAR_SCH_FrenchRevolution
    5,   // CALENDAR_SCH_IslamicTabular,
    6    // CALENDAR_SCH_Hebrew
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
    recRelativeDate::TYPE_Duration,
    recRelativeDate::TYPE_AddToStart,
    recRelativeDate::TYPE_AddToEnd
};

int rgDate::calc_list[recRelativeDate::TYPE_Max] = {
    0,  // TYPE_Unstated
    0,  // TYPE_AgeRoundDown
    1   // TYPE_Duration
};

wxArrayString rgDate::GetCalendarList()
{
    wxArrayString list;
    for( size_t i = 0 ; i < rgDate::SchemeListSize ; i++ ) {
        list.push_back( CalendarSchemeName[rgDate::scheme[i]] );
    }
    return list;
}

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
    wxASSERT( CALENDAR_SCH_Max == 16 ); // Don't forget to update when adding schemes
    wxASSERT( m_date.FGetID() != 0  );
    wxASSERT( m_date.f_rel_id == 0 );

    m_staticDateID->SetLabel( m_date.GetIdStr() );
    if( m_date.FGetType() < 1 || m_date.FGetType() >= recDate::PREF_Max ) {
        m_date.FSetType( recDate::PREF_On );
    }
    m_choiceType->SetSelection( m_date.f_type - 1 );
    m_choiceInput->Set( GetCalendarList() );
    m_choiceInput->SetSelection( sch_list[m_date.f_record_sch] );
    m_choiceDisplay->Set( GetCalendarList() );
    m_choiceDisplay->SetSelection( sch_list[m_date.f_display_sch] );

    m_textCtrlDate->SetValue( m_date.GetInputJdnStr() );
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

// End of src/rg/rgEdDate.cpp file
