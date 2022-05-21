/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdNameStyle.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit Name Style dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21st May 2022
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

#include <rg/rgDialogs.h>
#include "rgEdNameStyle.h"

#include <cal/calendar.h>


bool rgEditNameStyle( wxWindow* wind, idt nsID )
{
    return rgEdit<rgDlgEditNameStyle>( wind, nsID, _( "Edit Name Style" ) );
}

idt rgCreateNameStyle( wxWindow* wind )
{
    return rgCreate<recNameStyle, rgDlgEditNameStyle>(
        wind, _( "Create Name Style" )
    );
}


//============================================================================
//--------------------------[ rgDlgEditNameStyle ]----------------------------
//============================================================================

rgDlgEditNameStyle::rgDlgEditNameStyle( wxWindow* parent, idt nsID )
    : m_style( nsID ), fbRgEditNameStyle( parent )
{
}

bool rgDlgEditNameStyle::TransferDataToWindow()
{
    m_staticNameStyleID->SetLabel( m_style.GetIdStr() );
    m_textCtrlStyle->SetValue( m_style.FGetName() );
    m_textCtrlUid->SetValue( m_style.FGetUid() );
    wxString changed = calStrFromJdn( m_style.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );
    return true;
}

bool rgDlgEditNameStyle::TransferDataFromWindow()
{
    m_style.FSetName( m_textCtrlStyle->GetValue() );
    m_style.FSetChanged( calGetTodayJdn() );
    m_style.Save();
    return true;
}


// End of src/rg/rgEdNameStyle.cpp file
