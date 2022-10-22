/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPlace.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Place dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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
#include "rgEdPlace.h"


bool rgEditPlace( wxWindow* wind, idt placeID, const wxString& title )
{
    return rgEdit<rgDlgEditPlace>( wind, placeID, title );
}

idt rgCreatePlace( wxWindow* wind, const wxString& placeStr )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recPlace place( 0 );
    place.CreateUidChanged();
    place.Save();
    idt placeID = place.FGetID();

    recPlacePart pp( 0 );
    pp.FSetPlaceID( placeID );
    pp.FSetTypeID( recPlacePartType::TYPE_Address );
    pp.FSetValue( placeStr );
    pp.FSetSequence( 1 );
    pp.Save();

    if( rgEdit<rgDlgEditPlace>( wind, placeID, _( "Create Place" ) ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return placeID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

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

    m_textCtrlUid->SetValue( m_place.FGetUid() );
    wxString changed = calStrFromJdn( m_place.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );

    return true;
}

bool rgDlgEditPlace::TransferDataFromWindow()
{
    m_pp.FSetValue( m_textCtrlAddr->GetValue() );
    m_pp.Save();

    return true;
}


// End of src/rg/rgEdPlace.cpp file
