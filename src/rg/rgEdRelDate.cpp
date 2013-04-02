/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdRelDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Relative Date dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     12th March 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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
#include "rgEdRelDate.h"

bool rgEditRelativeDate( wxWindow* wind, idt dateID )
{
    wxASSERT( dateID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRelativeDate* dialog = new rgDlgEditRelativeDate( wind, dateID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateRelativeDate( wxWindow* wind, idt baseID, long value )
{
    wxASSERT( baseID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recRelativeDate rel(0);
    rel.SetDefaults();
    rel.FSetValue( value );
    rel.FSetBaseID( baseID );
    rel.Save();

    recDate date(0);
    date.SetDefaults();
    date.FSetRelID( rel.FGetID() );
    date.Save();
    idt dateID = date.FGetID();
    if( rgEditRelativeDate( wind, dateID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return dateID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//-------------------------[ rgDlgEditRelativeDate ]--------------------------
//============================================================================

using namespace rgDate;

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
    m_choiceDisplay->Set( GetCalendarList() );
    m_choiceDisplay->SetSelection( sch_list[m_date.FGetDisplaySch()] );
    m_choiceCalc->SetSelection( m_relative.FGetType() );
    m_textCtrlBase->SetValue( m_base.GetStr() );
    m_choicePrecision->SetSelection( m_date.FGetType() - 1 );
    wxString age = wxString::Format( "%ld", m_relative.FGetValue() );
    m_textCtrlAge->SetValue( age );
    m_choiceInput->Set( GetCalendarList() );
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
    if( rgEditDate( this, m_base.FGetID() ) ) {
        m_base.Read();
        m_textCtrlBase->SetValue( m_base.GetStr() );
    }
}

void rgDlgEditRelativeDate::CalcDate()
{
    m_date.FSetDisplaySch( scheme[m_choiceDisplay->GetSelection()] );
    m_relative.FSetType( calc[m_choiceCalc->GetSelection()] );
    m_date.FSetType( m_choicePrecision->GetSelection() + 1 );
    wxString agestr = m_textCtrlAge->GetValue();
    agestr.ToLong( &m_relative.f_val );
    m_relative.FSetScheme( scheme[m_choiceInput->GetSelection()] );
    m_date.FSetRecordSch( m_relative.FGetScheme() );
    m_relative.FSetUnit( unit[m_radioUnits->GetSelection()] );

    m_relative.CalculateDate( m_date );
}

// End of src/rg/rgEdRelDate.cpp file
