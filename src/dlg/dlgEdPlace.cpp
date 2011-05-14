/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdPlace.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Place entity dialog.
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

#include "dlgEdPlace.h"

dlgEditPlace::dlgEditPlace( wxWindow* parent, idt id )
    : fbDlgEditPlace( parent )
{
    m_place.f_id = id;
    m_place.Read();
}


bool dlgEditPlace::TransferDataToWindow()
{
    if( m_place.f_id == 0 )
    {
        m_place.Clear();
        m_place.Save();
    } else {
        m_place.Read();
        m_text = m_place.GetAddressStr();
    }

    wxTextCtrl* textCtrl = (wxTextCtrl*) FindWindow( tfpID_EDPLACE_ADDR );
    textCtrl->SetValue( m_text );

    return true;
}

bool dlgEditPlace::TransferDataFromWindow()
{
    wxTextCtrl* textCtrl = (wxTextCtrl*) FindWindow( tfpID_EDPLACE_ADDR );
    m_text = textCtrl->GetValue();

    m_place.Save();

    recPlacePartList ppVec = m_place.GetPlaceParts();
    if( ppVec.size() == 0 )
    {
        recPlacePart pp;
        pp.Clear();
        pp.f_type_id = recPlacePartType::TYPE_Address;
        pp.f_place_id = m_place.f_id;
        pp.f_val = m_text;
        pp.Save();
    } else {
        ppVec[0].f_type_id = recPlacePartType::TYPE_Address;
        ppVec[0].f_val = m_text;
        ppVec[0].Save();
        for( size_t i = 1 ; i < ppVec.size() ; i++ ) {
            ppVec[i].Delete();
        }
    }

    return true;
}


// End of dlgEdPlace.cpp file
