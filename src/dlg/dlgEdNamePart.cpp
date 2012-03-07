/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdNamePart.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name Part entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 November 2010
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

#include "dlgEdNamePart.h"

dlgEditNamePart::dlgEditNamePart( wxWindow* parent )
    : fbDlgEditNamePart( parent )
{
    m_np.Clear();
}

bool dlgEditNamePart::TransferDataToWindow()
{
    if( m_np.f_id == 0 ) {
        m_np.Save();
    } else {
        m_np.Read();
    }

    m_staticNameID->SetLabel( recName::GetIdStr( m_np.f_name_id ) );
    m_staticNamePartID->SetLabel( m_np.GetIdStr() );

    m_types = recNamePartType::GetTypeList();
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        m_choiceType->Append( m_types[i].f_name );
        if( m_np.f_type_id == m_types[i].f_id ) {
            m_choiceType->SetSelection( (int) i );
        }
    }

    m_textCtrlValue->SetValue( m_np.f_val );

    return true;
}

bool dlgEditNamePart::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type < 0 ) {
        m_np.f_type_id = 0;
    } else {
        m_np.f_type_id = m_types[type].f_id;
    }
    m_np.f_val = m_textCtrlValue->GetValue();
    m_np.Save();
    return true;
}

// End of dlgEditNamePart.cpp file
