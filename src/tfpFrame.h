/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpFrame.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpFrame class header.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     24 September 2010
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

#ifndef TFPFRAME_H
#define TFPFRAME_H

#include "wx/html/htmlwin.h"

class wxHtmlEasyPrinting;

// Define a new frame type: this is going to be our main frame
class TfpFrame : public wxFrame
{
private:
    DECLARE_EVENT_TABLE()

    wxMenuBar*          m_menuClosedDB;
    wxHtmlWindow*       m_html;
    wxHtmlEasyPrinting* m_prn;

public:
    // ctor and dtor
    TfpFrame( const wxString& title, const wxPoint& pos, const wxSize& size );
    virtual ~TfpFrame();

    // event handlers (these functions should _not_ be virtual)
    void OnNewFile( wxCommandEvent& event );
    void OnOpenFile( wxCommandEvent& event );
    void OnImportGedcom( wxCommandEvent& event );

    void OnHelpWebHome( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );
    void OnQuit( wxCommandEvent& event );

    void OnHtmlLinkClicked( wxHtmlLinkEvent& event );
    void OnCloseWindow( wxCloseEvent& event );

    void NewFile();
    void OpenFile();
    void ImportGedcom();
};

enum
{
    // menu items
    tfpID_NEW_FILE = wxID_HIGHEST+1,
    tfpID_OPEN_FILE,
    tfpID_IMPORT_GEDCOM,
	tfpID_HELP_WEB_HOME
};

extern TfpFrame* GetMainFrame();

#endif // TFPFRAME_H

