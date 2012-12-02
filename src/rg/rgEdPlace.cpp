/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPlace.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Place dialog.
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

#include "rgEdPlace.h"

// NOTE We are using a simplified place model where the only PlaceTypePart is
// "Address" and there is one, and only one, PlacePart per Place.

rgDlgEditPlace::rgDlgEditPlace( wxWindow* parent, idt placeID )
    : m_place(placeID), fbRgEditPlace( parent )
{
    recPlacePartVec parts = m_place.GetPlaceParts();
    wxASSERT( parts.size() == 1 ); // Using simple address model
    m_pp = parts[0];
}


bool rgDlgEditPlace::TransferDataToWindow()
{
    wxASSERT( m_place.FGetID() != 0  );

    m_staticPlaceID->SetLabel( m_place.GetIdStr() );
    m_textCtrlAddr->SetValue( m_pp.FGetValue() );
    return true;
}

bool rgDlgEditPlace::TransferDataFromWindow()
{
    m_pp.FSetValue( m_textCtrlAddr->GetValue() );
    m_pp.Save();

    return true;
}


// End of src/rg/rgEdPlace.cpp file
