/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdNamePartType.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit NamePartType dialog.
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
#include "rgEdNamePartType.h"

#include <cal/calendar.h>


bool rgEditNamePartType( wxWindow* wind, idt nptID )
{
    return rgEdit<rgDlgEditNamePartType>( wind, nptID );
}

idt rgCreateNamePartType( wxWindow* wind )
{
    recNamePartType npt( 0 );
    npt.FSetUid( recCreateUid() );
    npt.FSetChanged( calGetTodayJdn() );
    return rgCreate<recNamePartType, rgDlgEditNamePartType>(
        wind, npt, _( "Create Name Style" )
    );
}


//============================================================================
//------------------------[ rgDlgEditNamePartType ]---------------------------
//============================================================================

rgDlgEditNamePartType::rgDlgEditNamePartType( wxWindow* parent, idt nptID )
    : m_type( nptID ), fbRgEditNamePartType( parent )
{
}

bool rgDlgEditNamePartType::TransferDataToWindow()
{
    wxASSERT( m_type.FGetID() != 0 );

    m_staticNPTypeID->SetLabel( m_type.GetIdStr() );
    m_textCtrlType->SetValue( m_type.FGetName() );
    size_t grp = static_cast<size_t>(m_type.FGetGroup());
    StringVec grps = recNamePartType::GetGroupList();
    m_choiceGroup->Append( "<Select Group>" );
    m_choiceGroup->SetSelection( 0 );
    for( size_t i = 1; i < grps.size(); i++ ) {
        m_choiceGroup->Append( grps[i] );
        if( i == grp ) {
            m_choiceGroup->SetSelection( i );
        }
    }
    m_textCtrlUid->SetValue( m_type.FGetUid() );
    wxString changed = calStrFromJdn( m_type.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );

    return true;
}

bool rgDlgEditNamePartType::TransferDataFromWindow()
{
    m_type.FSetName( m_textCtrlType->GetValue() );
    int grp = m_choiceGroup->GetSelection();
    if( grp == 0 ) {
        grp = 1; // default to 1 "Name"
    }
    m_type.FSetGroup( static_cast<recNamePartType::NPTypeGrp>(grp) );
    m_type.FSetChanged( calGetTodayJdn() );
    m_type.Save();
    return true;
}


// End of src/rg/rgEdNamePartType.cpp file
