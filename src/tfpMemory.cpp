/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpMemory.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Load image and text files into memory filesystem.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     26 September 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
 * Website:     http://thefamilypack.org
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

#include <wx/filesys.h>
#include <wx/fs_mem.h>

#include "tfpVersion.h"

#include "logo6.xpm"
#include "generated/tfpText.ci"

void tfpLoadMemoryFiles()
{
    wxFileSystem::AddHandler( new wxMemoryFSHandler );
    wxBitmap logo6Bitmap( logo6_xpm );
    wxMemoryFSHandler::AddFile( wxT("logo6.bmp"), logo6Bitmap, wxBITMAP_TYPE_XPM );
    wxString startupText( wxString::Format( s_startup_htm, tfpVersion ) );
    wxMemoryFSHandler::AddFile( wxT("startup.htm"), startupText );
}

// End of tfpMemory.cpp file

