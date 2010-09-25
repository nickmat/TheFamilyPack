/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpFrame.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpFrame class source.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     25 September 2010
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

#include "wx/html/htmlwin.h"
#include "wx/html/htmprint.h"

#include "tfpFrame.h"
#include "tfpApp.h"
#include "tfpVersion.h"

BEGIN_EVENT_TABLE(TfpFrame, wxFrame)
    EVT_MENU( tfpID_NEW_FILE, TfpFrame::OnNewFile )
    EVT_MENU( tfpID_OPEN_FILE, TfpFrame::OnOpenFile )
    EVT_MENU( tfpID_IMPORT_GEDCOM, TfpFrame::OnImportGedcom )
    EVT_MENU( tfpID_HELP_WEB_HOME, TfpFrame::OnHelpWebHome )
    EVT_MENU( wxID_EXIT, TfpFrame::OnQuit )
    EVT_MENU( wxID_ABOUT, TfpFrame::OnAbout )
    EVT_CLOSE( TfpFrame::OnCloseWindow )
END_EVENT_TABLE()


// frame constructor
TfpFrame::TfpFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
        : wxFrame( (wxFrame*) NULL, wxID_ANY, title, pos, size )
{
    // Set frames Icon
    SetIcon( wxIcon( wxT("tfp") ) );

    wxMenu *menuInitFile = new wxMenu;
    menuInitFile->Append( tfpID_NEW_FILE, wxT("&New File\tCtrl-N") );
    menuInitFile->Append( tfpID_OPEN_FILE, wxT("&Open File\tCtrl-O") );
    menuInitFile->AppendSeparator();
    menuInitFile->Append( tfpID_IMPORT_GEDCOM, wxT("&Import GEDCOM file") );
    menuInitFile->AppendSeparator();
    menuInitFile->Append( wxID_EXIT, wxT("E&xit") );

    wxMenu *menuInitHelp = new wxMenu;
    menuInitHelp->Append( tfpID_HELP_WEB_HOME, wxT("The Family Pack &Website") );
    menuInitHelp->Append( wxID_ABOUT, wxT("&About \"The Family Pack\"") );

    // Menu bar for use with closed database
    m_menuClosedDB = new wxMenuBar;
    m_menuClosedDB->Append( menuInitFile, wxT("&File") );
    m_menuClosedDB->Append( menuInitHelp, wxT("&Help") );
    SetMenuBar( m_menuClosedDB );

    CreateStatusBar();

    m_html = new wxHtmlWindow( this );
    m_html->SetRelatedStatusBar( 0 );

    m_prn = new wxHtmlEasyPrinting( "Easy Printing Demo", this );

    m_html->SetPage( "<html><body>This is a test</body></html>" );
}

// frame destructor
TfpFrame::~TfpFrame()
{
    delete m_prn;
    m_prn = (wxHtmlEasyPrinting*) NULL;
}

void TfpFrame::OnCloseWindow( wxCloseEvent& WXUNUSED(event) )
{
    this->Destroy();
}

void TfpFrame::OnNewFile( wxCommandEvent& WXUNUSED(event) )
{
    NewFile();
}

void TfpFrame::OnOpenFile( wxCommandEvent& WXUNUSED(event) )
{
    OpenFile();
}

void TfpFrame::OnImportGedcom( wxCommandEvent& WXUNUSED(event) )
{
    ImportGedcom();
}


void TfpFrame::OnQuit( wxCommandEvent& WXUNUSED(event) )
{
    // true is to force the frame to close
    Close( true );
}

void TfpFrame::OnHelpWebHome( wxCommandEvent& WXUNUSED(event) )
{
	wxLaunchDefaultBrowser( wxT("http://thefamilypack.org") );
}

void TfpFrame::OnAbout( wxCommandEvent& WXUNUSED(event) )
{
    wxMessageBox(
        wxString::Format(
            wxT("%s")
            wxT("Built with %s\n")
            wxT("by %s\n")
            wxT("running under %s."),

            tfpTitle,
            wxVERSION_STRING,
            tfpGetCompilerVersion(),
            wxGetOsDescription().c_str()
        ),
        wxT("About The Family Pack"),
        wxOK | wxICON_INFORMATION,
        this
    );
}


void TfpFrame::NewFile()
{
    wxMessageBox( wxT("Not yet implimented"), wxT("NewFile") );
}

void TfpFrame::OpenFile()
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OpenFile") );
}

void TfpFrame::ImportGedcom()
{
    wxMessageBox( wxT("Not yet implimented"), wxT("ImportGedcom") );
}

// End of tfpFrame.cpp file

