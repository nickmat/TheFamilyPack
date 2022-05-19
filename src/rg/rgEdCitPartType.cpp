/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdCitPartType.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit CitationPartType dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     18th May 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recCitation.h>

#include <rg/rgDialogs.h>
#include "rgEdCitPartType.h"

#include <cal/calendar.h>


bool rgEditCitationPartType( wxWindow* wind, idt cipID, const wxString& title )
{
    return rgEdit<rgDlgEditCitationPartType>( wind, cipID, title );
}

idt rgCreateCitationPartType( wxWindow* wind )
{
    return rgCreate<recCitationPartType, rgDlgEditCitationPartType>(
        wind, _( "Create Citation Part Type" )
    );
}


//============================================================================
//----------------------[ rgDlgEditCitationPartType ]-------------------------
//============================================================================

rgDlgEditCitationPartType::rgDlgEditCitationPartType( wxWindow* parent, idt ciptID )
    : m_type(ciptID), fbRgEditCitationPartType(parent)
{
}

bool rgDlgEditCitationPartType::TransferDataToWindow()
{
    m_staticCiPT_ID->SetLabel( m_type.GetIdStr() );
    m_textCtrlName->SetValue( m_type.FGetName() );
    m_textCtrlComment->SetValue( m_type.FGetComment() );

    size_t style = static_cast<size_t>(m_type.FGetStyle());
    m_choiceStyle->SetSelection( static_cast<int>(m_type.FGetStyle()) );
    for( size_t i = 0; i < recTextStyleSize; i++ ) {
        m_choiceStyle->Append( recGetTextStyleName( static_cast<recTextStyle>(i) ) );
        if( style == i ) {
            m_choiceStyle->SetSelection( static_cast<int>(i) );
        }
    }

    m_textCtrlUid->SetValue( m_type.FGetUid() );
    wxString changed = calStrFromJdn( m_type.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );

    return true;
}

bool rgDlgEditCitationPartType::TransferDataFromWindow()
{
    m_type.FSetName( m_textCtrlName->GetValue() );
    m_type.FSetComment( m_textCtrlComment->GetValue() );
    int style = m_choiceStyle->GetSelection();
    wxASSERT( style < recTextStyleSize );
    m_type.FSetStyle( static_cast<recTextStyle>(style) );
    m_type.FSetChanged( calGetTodayJdn() );
    m_type.Save();
    return true;
}

// End of src/rg/rgEdCitPartType.cpp file
