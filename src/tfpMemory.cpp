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

#include "tfpMemory.h"
#include "tfpVersion.h"

#include "img/logo6.xpm"
#include "generated/tfpText.ci"

#include "img/cht/ds.xpm"
#include "img/cht/dc.xpm"
#include "img/cht/dt.xpm"
#include "img/cht/de.xpm"
#include "img/cht/ss.xpm"
#include "img/cht/sc.xpm"
#include "img/cht/st.xpm"
#include "img/cht/se.xpm"
#include "img/cht/pu.xpm"
#include "img/cht/pd.xpm"
#include "img/cht/pt.xpm"
#include "img/cht/pe.xpm"

#include "img/dcht.xpm"
#include "img/pcht.xpm"
#include "img/edit.xpm"
#include "img/menu.xpm"
#include "img/ind.xpm"
#include "img/fam.xpm"
#include "img/par.xpm"
#include "img/sib.xpm"
#include "img/mar.xpm"
#include "img/kid.xpm"
#include "img/ref.xpm"
#include "img/event.xpm"

// Common bitmats
wxBitmap imgEditBitmap( edit_xpm );
wxBitmap imgMenuBitmap( menu_xpm );

/*! \brief Create the memory file system and read in the memory files.
 */
void tfpLoadMemoryFiles()
{
    wxFileSystem::AddHandler( new wxMemoryFSHandler );
    wxBitmap logo6Bitmap( logo6_xpm );
    wxMemoryFSHandler::AddFile( "logo6.bmp", logo6Bitmap, wxBITMAP_TYPE_XPM );
    wxString startupText( wxString::Format( s_startup_htm, tfpHtmVersion ) );
    wxMemoryFSHandler::AddFile( "startup.htm", startupText );

    wxBitmap dsBitmap( ds_xpm );
    wxMemoryFSHandler::AddFile( "ds.bmp", dsBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap dcBitmap( dc_xpm );
    wxMemoryFSHandler::AddFile( "dc.bmp", dcBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap dtBitmap( dt_xpm );
    wxMemoryFSHandler::AddFile( "dt.bmp", dtBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap deBitmap( de_xpm );
    wxMemoryFSHandler::AddFile( "de.bmp", deBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap ssBitmap( ss_xpm );
    wxMemoryFSHandler::AddFile( "ss.bmp", ssBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap scBitmap( sc_xpm );
    wxMemoryFSHandler::AddFile( "sc.bmp", scBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap stBitmap( st_xpm );
    wxMemoryFSHandler::AddFile( "st.bmp", stBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap seBitmap( se_xpm );
    wxMemoryFSHandler::AddFile( "se.bmp", seBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap puBitmap( pu_xpm );
    wxMemoryFSHandler::AddFile( "pu.bmp", puBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap pdBitmap( pd_xpm );
    wxMemoryFSHandler::AddFile( "pd.bmp", pdBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap ptBitmap( pt_xpm );
    wxMemoryFSHandler::AddFile( "pt.bmp", ptBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap peBitmap( pe_xpm );
    wxMemoryFSHandler::AddFile( "pe.bmp", peBitmap, wxBITMAP_TYPE_XPM );
    wxMemoryFSHandler::AddFile( "edit.bmp", imgEditBitmap, wxBITMAP_TYPE_XPM );
    wxMemoryFSHandler::AddFile( "menu.bmp", imgMenuBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap dchtBitmap( dcht_xpm );
    wxMemoryFSHandler::AddFile( "dcht.bmp", dchtBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap pchtBitmap( pcht_xpm );
    wxMemoryFSHandler::AddFile( "pcht.bmp", pchtBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap indBitmap( ind_xpm );
    wxMemoryFSHandler::AddFile( "ind.bmp", indBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap famBitmap( fam_xpm );
    wxMemoryFSHandler::AddFile( "fam.bmp", famBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap parBitmap( par_xpm );
    wxMemoryFSHandler::AddFile( "par.bmp", parBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap sibBitmap( sib_xpm );
    wxMemoryFSHandler::AddFile( "sib.bmp", sibBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap marBitmap( mar_xpm );
    wxMemoryFSHandler::AddFile( "mar.bmp", marBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap kidBitmap( kid_xpm );
    wxMemoryFSHandler::AddFile( "kid.bmp", kidBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap refBitmap( ref_xpm );
    wxMemoryFSHandler::AddFile( "ref.bmp", refBitmap, wxBITMAP_TYPE_XPM );
    wxBitmap eveBitmap( event_xpm );
    wxMemoryFSHandler::AddFile( "eve.bmp", eveBitmap, wxBITMAP_TYPE_XPM );
}

// End of tfpMemory.cpp file

