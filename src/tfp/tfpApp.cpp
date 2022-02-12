/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpApp.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Program App class
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 September 2010
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

#include <wx/webviewfshandler.h>

#include <rec/recDatabase.h>
#include "tfpApp.h"
#include "tfpFrame.h"
#include "tfpMemory.h"

wxIMPLEMENT_APP( TfpApp );

/*! This is where all the application initialisation is carried out.
 *  Function ends by creating the programs main frame and making it visible.
 */
bool TfpApp::OnInit()
{
    wxImage::AddHandler( new wxPNGHandler );
    wxImage::AddHandler( new wxJPEGHandler );
    wxImage::AddHandler( new wxGIFHandler );
    wxImage::AddHandler( new wxXPMHandler );
    tfpLoadMemoryFiles();

    m_webviewFSHandler = wxSharedPtr<wxWebViewHandler>( new wxWebViewFSHandler( "memory" ) );

    recInitialize();

    wxString dbfname;
    if( argc > 1 ) {
        // 1st comand line argument is assumed to be a database file
        dbfname = argv[1];
    }

    TfpFrame* frame = new TfpFrame( 
        this, "The Family Pack", 
        wxDefaultPosition, wxSize( 900, 700 ),
        dbfname
    );
    frame->Show(true);

    SetTopWindow( frame );

    return true;
}

/*! Called on application shutdown. Returns 0 to allow continued shutdown.
*/
int TfpApp::OnExit()
{
    recUninitialize();
    tfpDeleteBitmaps();
    return 0;
}

void TfpApp::CloseFrame( TfpFrame* frame )
{
    for( auto i = m_frames.begin(); i != m_frames.end(); i++ ) {
        if( frame == *i ) {
            m_frames.erase( i );
            return;
        }
    }
}

TfpFrame* TfpApp::GetTfpFrame( size_t index ) const
{
    if( index < m_frames.size() ) {
        return m_frames[index];
    }
    return nullptr;
}

wxSharedPtr<wxWebViewHandler> GetWebViewMemoryHandler()
{
    return wxGetApp().GetWebViewFSHandler();
}

// End of tfpApp.cpp file
