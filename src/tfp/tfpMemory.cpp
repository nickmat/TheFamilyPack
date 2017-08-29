/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpMemory.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Load image and text files into memory filesystem.
 * Author:      Nick Matthews
 * Created:     26 September 2010
 * Copyright:   Copyright (c) 2010 ~ 2017, Nick Matthews.
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
#include "tfpText.h"

#include "img/cht/dss.xpm"
#include "img/cht/ds.xpm"
#include "img/cht/dc.xpm"
#include "img/cht/dt.xpm"
#include "img/cht/de.xpm"
#include "img/cht/sss.xpm"
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
#include "img/blank.xpm"
#include "img/menu.xpm"
#include "img/ind.xpm"
#include "img/fam.xpm"
#include "img/par.xpm"
#include "img/sib.xpm"
#include "img/mar.xpm"
#include "img/kid.xpm"
#include "img/ref.xpm"
#include "img/event.xpm"


// Common bitmaps
wxBitmap* imgEditBitmap = NULL;

/*! \brief Create the memory file system and read in the memory files.
 */
void tfpLoadMemoryFiles()
{
    // This function should only be run once
    static bool hasrun = false;
    wxASSERT( hasrun == false );
    hasrun = true;

    // Create common bitmaps
    imgEditBitmap = new wxBitmap( edit_xpm );

    wxFileSystem::AddHandler( new wxMemoryFSHandler );
    wxBitmap logo6Bitmap( logo6_xpm );
    wxMemoryFSHandler::AddFile( "logo6.png", logo6Bitmap, wxBITMAP_TYPE_PNG );
#ifdef _DEBUG
    wxString v;
    v << tfpHtmVersion << "<br><br><a href='tfpc:Test'>Test html page</a>";
    wxString startupText( wxString::Format( s_startup_htm, v ) );
#else
    wxString startupText( wxString::Format( s_startup_htm, tfpHtmVersion ) );
#endif

    wxMemoryFSHandler::AddFile( "startup.htm", startupText );
    wxMemoryFSHandler::AddFile( "tfp.css", s_tfp_css );
    wxMemoryFSHandler::AddFile( "tab.css", s_tab_css );

    wxBitmap dssBitmap( dss_xpm );
    wxMemoryFSHandler::AddFile( "dss.png", dssBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap dsBitmap( ds_xpm );
    wxMemoryFSHandler::AddFile( "ds.png", dsBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap dcBitmap( dc_xpm );
    wxMemoryFSHandler::AddFile( "dc.png", dcBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap dtBitmap( dt_xpm );
    wxMemoryFSHandler::AddFile( "dt.png", dtBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap deBitmap( de_xpm );
    wxMemoryFSHandler::AddFile( "de.png", deBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap sssBitmap( sss_xpm );
    wxMemoryFSHandler::AddFile( "sss.png", sssBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap ssBitmap( ss_xpm );
    wxMemoryFSHandler::AddFile( "ss.png", ssBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap scBitmap( sc_xpm );
    wxMemoryFSHandler::AddFile( "sc.png", scBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap stBitmap( st_xpm );
    wxMemoryFSHandler::AddFile( "st.png", stBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap seBitmap( se_xpm );
    wxMemoryFSHandler::AddFile( "se.png", seBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap puBitmap( pu_xpm );
    wxMemoryFSHandler::AddFile( "pu.png", puBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap pdBitmap( pd_xpm );
    wxMemoryFSHandler::AddFile( "pd.png", pdBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap ptBitmap( pt_xpm );
    wxMemoryFSHandler::AddFile( "pt.png", ptBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap peBitmap( pe_xpm );
    wxMemoryFSHandler::AddFile( "pe.png", peBitmap, wxBITMAP_TYPE_PNG );
    wxMemoryFSHandler::AddFile( "edit.png", *imgEditBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap blankBitmap( blank_xpm );
    wxMemoryFSHandler::AddFile( "blank.png", blankBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap menuBitmap( menu_xpm );
    wxMemoryFSHandler::AddFile( "menu.png", menuBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap dchtBitmap( dcht_xpm );
    wxMemoryFSHandler::AddFile( "dcht.png", dchtBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap pchtBitmap( pcht_xpm );
    wxMemoryFSHandler::AddFile( "pcht.png", pchtBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap indBitmap( ind_xpm );
    wxMemoryFSHandler::AddFile( "ind.png", indBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap famBitmap( fam_xpm );
    wxMemoryFSHandler::AddFile( "fam.png", famBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap parBitmap( par_xpm );
    wxMemoryFSHandler::AddFile( "par.png", parBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap sibBitmap( sib_xpm );
    wxMemoryFSHandler::AddFile( "sib.png", sibBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap marBitmap( mar_xpm );
    wxMemoryFSHandler::AddFile( "mar.png", marBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap kidBitmap( kid_xpm );
    wxMemoryFSHandler::AddFile( "kid.png", kidBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap refBitmap( ref_xpm );
    wxMemoryFSHandler::AddFile( "ref.png", refBitmap, wxBITMAP_TYPE_PNG );
    wxBitmap eveBitmap( event_xpm );
    wxMemoryFSHandler::AddFile( "eve.png", eveBitmap, wxBITMAP_TYPE_PNG );
}

void tfpDeleteBitmaps()
{
    wxDELETE( imgEditBitmap );
}

// End of tfpMemory.cpp file

