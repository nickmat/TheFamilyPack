/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpFrame.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpFrame class header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 September 2010
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


/*! \brief The main application frame.
 *
 *  This is a wxHtml control, so all our main program
 *  display will be html pages written directly from the database by the
 *  application. The hypertext links will be used as a simple text code to
 *  interpret the users commands.
 */
class TfpFrame : public wxFrame
{
private:
    DECLARE_EVENT_TABLE()

    wxMenuBar*          m_menuOpenDB;
    wxMenuBar*          m_menuClosedDB;
    wxToolBar*          m_toolbar;
    wxArrayString       m_back;
    wxArrayString       m_forward;
    wxHtmlWindow*       m_html;
    wxHtmlEasyPrinting* m_prn;
    wxString            m_dbname;

public:
    // ctor and dtor
    TfpFrame( const wxString& title, const wxPoint& pos, const wxSize& size );
    virtual ~TfpFrame();

    // event handlers
    void OnNewWindow( wxCommandEvent& event );
    void OnNewFile( wxCommandEvent& event );
    void OnOpenFile( wxCommandEvent& event );
    void OnCloseFile( wxCommandEvent& event );
    void OnImportGedcom( wxCommandEvent& event );
    void OnExportHtml( wxCommandEvent& event );
    void OnPrint( wxCommandEvent& event );
    void OnPreview( wxCommandEvent& event );
    void OnPageSetup( wxCommandEvent& event );
    void OnQuit( wxCommandEvent& event );

    void OnEditIndividual( wxCommandEvent& event );
    void OnEditReference( wxCommandEvent& event );

    void OnFindFamilyID( wxCommandEvent& event );
    void OnFindIndividualID( wxCommandEvent& event );

    void OnListIndex( wxCommandEvent& event );
    void OnListNames( wxCommandEvent& event );
    void OnListIndividuals( wxCommandEvent& event );

    void OnPedChart( wxCommandEvent& event );
    void OnDescChart( wxCommandEvent& event );

    void OnHelpWebHome( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );

    void OnFindBack( wxCommandEvent& event );
    void OnFindForward( wxCommandEvent& event );
    void OnHome( wxCommandEvent& event );

    void OnHtmlLinkClicked( wxHtmlLinkEvent& event );
    void OnCloseWindow( wxCloseEvent& event );

private:
    void NewFile();
    void OpenFile();
    void ImportGedcom();

    void SetDatabaseOpen( wxString& path, bool open );
    bool DisplayHtmPage( const wxString& name );
    wxString GetDisplayText( const wxString& name );
};

enum
{
    // menu items
    tfpID_NEW_WINDOW = wxID_HIGHEST+1,
    tfpID_NEW_FILE,
    tfpID_OPEN_FILE,
    tfpID_CLOSE_FILE,
    tfpID_IMPORT_GEDCOM,
    tfpID_EXPORT_HTML,
    tfpID_PRINT,
    tfpID_PREVIEW,
    tfpID_PAGE_SETUP,
    tfpID_EDIT_INDIVIDUAL,
    tfpID_EDIT_REFERENCE,
    tfpID_FIND_FAMILY_ID,
    tfpID_FIND_INDIVIDUAL_ID,
    tfpID_LIST_SURNAME_INDEX,
    tfpID_LIST_NAMES,
	tfpID_LIST_INDIVIDUALS,
    tfpID_PED_CHART,
    tfpID_DESC_CHART,
    tfpID_HELP_WEB_HOME,
    tfpID_FIND_BACK,
    tfpID_FIND_FORWARD,
    tfpID_GOTO_HOME
};

#endif // TFPFRAME_H

