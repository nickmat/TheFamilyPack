/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgViewMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     View Media (Image) dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10 October 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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
#include "rgViewMedia.h"

#include <wx/colour.h>

void rgViewMedia( wxWindow* wind, idt medID )
{
    wxASSERT( medID != 0 );
    rgViewMediaForm* frame = new rgViewMediaForm( wind, medID );
    frame->SetBackgroundColour( *wxWHITE );
    frame->Show();
}

//============================================================================
//-------------------------[ rgViewMediaForm ]--------------------------------
//============================================================================

rgViewMediaForm::rgViewMediaForm( wxWindow* parent, idt medID )
    : m_media(medID), fbRgViewMedia( parent )
{
    m_imageViewer->SetImage( m_media );
}

// End of src/rg/rgViewMedia.cpp file
