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

#include "wx/wxsqlite3.h"

#include "tfpFrame.h"
#include "tfpApp.h"
#include "tfpVersion.h"
#include "rec/recDatabase.h"

BEGIN_EVENT_TABLE(TfpFrame, wxFrame)
    EVT_MENU( tfpID_NEW_FILE, TfpFrame::OnNewFile )
    EVT_MENU( tfpID_OPEN_FILE, TfpFrame::OnOpenFile )
    EVT_MENU( tfpID_IMPORT_GEDCOM, TfpFrame::OnImportGedcom )
    EVT_MENU( tfpID_HELP_WEB_HOME, TfpFrame::OnHelpWebHome )
    EVT_MENU( wxID_EXIT, TfpFrame::OnQuit )
    EVT_MENU( wxID_ABOUT, TfpFrame::OnAbout )
    EVT_HTML_LINK_CLICKED( wxID_ANY, TfpFrame::OnHtmlLinkClicked )
    EVT_CLOSE( TfpFrame::OnCloseWindow )
END_EVENT_TABLE()


/*! \brief Frame constructor.
 *
 *  Create the window Icon, Menu bar, Status bar and Html control.
 *  Set the window to display the splash screen.
 */
TfpFrame::TfpFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
    : wxFrame( (wxFrame*) NULL, wxID_ANY, title, pos, size )
{
    // Set frames Icon
    SetIcon( wxIcon( "tfp" ) );

    wxMenu *menuInitFile = new wxMenu;
    menuInitFile->Append( tfpID_NEW_FILE, _("&New File\tCtrl-N") );
    menuInitFile->Append( tfpID_OPEN_FILE, _("&Open File\tCtrl-O") );
    menuInitFile->AppendSeparator();
    menuInitFile->Append( tfpID_IMPORT_GEDCOM, _("&Import GEDCOM file") );
    menuInitFile->AppendSeparator();
    menuInitFile->Append( wxID_EXIT, _("E&xit") );

    wxMenu *menuInitHelp = new wxMenu;
    menuInitHelp->Append( tfpID_HELP_WEB_HOME, _("The Family Pack &Website") );
    menuInitHelp->Append( wxID_ABOUT, _("&About \"The Family Pack\"") );

    // Menu bar for use with closed database
    m_menuClosedDB = new wxMenuBar;
    m_menuClosedDB->Append( menuInitFile, _("&File") );
    m_menuClosedDB->Append( menuInitHelp, _("&Help") );
    SetMenuBar( m_menuClosedDB );

    CreateStatusBar( 1 );

    m_html = new wxHtmlWindow( this );
    m_html->SetRelatedStatusBar( 0 );

    m_prn = new wxHtmlEasyPrinting( _("Easy Printing Demo"), this );

    m_html->LoadPage( "memory:startup.htm" );
}

/*! \brief Frame destructor.
 */
TfpFrame::~TfpFrame()
{
    wxDELETE( m_prn );
}

/*! \brief Called on a Close Window event.
 */
void TfpFrame::OnCloseWindow( wxCloseEvent& event )
{
    this->Destroy();
}

/*! \brief Called on a New File menu option event.
 */
void TfpFrame::OnNewFile( wxCommandEvent& event )
{
    NewFile();
}

/*! \brief Called on an Open File menu option event.
 */
void TfpFrame::OnOpenFile( wxCommandEvent& event )
{
    OpenFile();
}

/*! \brief Called on a Inport GEDCOM File menu option event.
 */
void TfpFrame::OnImportGedcom( wxCommandEvent& event )
{
    ImportGedcom();
}

/*! \brief Called on an Exit Application menu option event.
 */
void TfpFrame::OnQuit( wxCommandEvent& event )
{
    // true is to force the frame to close
    Close( true );
}

/*! \brief Called on a Help, TFP Website menu option event.
 *
 */
void TfpFrame::OnHelpWebHome( wxCommandEvent& event )
{
    wxLaunchDefaultBrowser( "http://thefamilypack.org" );
}

/*! \brief Called on a Help, About menu option event.
 *
 *  Displays a message box with the current TFP version number,
 *  wxWidgets version number, the compiler name and version and
 *  operating system description.
 *
 */
void TfpFrame::OnAbout( wxCommandEvent& event )
{
    wxMessageBox(
        wxString::Format(
            _("%s"
            "Built with %s and SQLite %s\n"
            "by %s\n"
            "running under %s."),

            tfpTitle,
            wxVERSION_STRING,
            wxSQLite3Database::GetVersion(),
            tfpGetCompilerVersion(),
            wxGetOsDescription().c_str()
        ),
        _("About The Family Pack"),
        wxOK | wxICON_INFORMATION,
        this
    );
}

/*! \brief Called on a link in the html control being clicked.
 *
 *  Decodes the href string of the clicked link. If the first
 *  character of the href string is:-
 *
 *  ':' then the remainder of the string is a command.
 *
 *  '!' then the remainder of the string is a web address to be
 *  passed to the default external browser.
 *  
 */
void TfpFrame::OnHtmlLinkClicked( wxHtmlLinkEvent& event )
{
    wxString href = event.GetLinkInfo().GetHref().c_str();

    switch( (wxChar) href.GetChar( 0 ) )
    {
    case ':': // Program Commands
        if( href == ":New" ) {
            NewFile();
        } else if( href == ":Open" ) {
            OpenFile();
        } else if( href == ":Import" ) {
            ImportGedcom();
        } else {
            wxMessageBox( _("Error: Invalid Command"), _("Link Error") );
        }
        break;
    case '!':  // Display in external browser
        wxLaunchDefaultBrowser( href.Mid( 1 ) );
        break;
    }
}


void TfpFrame::NewFile()
{
//    wxMessageBox( wxT("Not yet implimented"), wxT("NewFile") );
    wxString caption = _("Create TFP Database");
    wxString wildcard = _("TFP Database (*.tfpd)|*.tfpd");
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        unsigned flags = recDb::CREATE_DB_STD_EXT | recDb::CREATE_DB_ENUM_FN;
        if( recDb::CreateDb( path, flags ) == true )
        {
//            SetDatabaseOpen( path, true );
//            DisplayHtmPage( wxT("F1") );
        }
    }
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

