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

#include <wx/html/htmlwin.h>
#include <rec/recDatabase.h>

class TfpHtml;
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
    wxMenu*             m_menuEditInd;
    idt                 m_EditIndLeft;
    idt                 m_EditIndRight;
    idt                 m_EditFamily;
    wxTextCtrl*         m_showpage;
    wxArrayString       m_back;
    wxArrayString       m_forward;
    TfpHtml*            m_html;
    wxHtmlEasyPrinting* m_prn;
    wxString            m_dbFileName;

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

    void OnEditContext( wxCommandEvent& event );
    void OnEditReference( wxCommandEvent& event );

    void OnEditIndividual( wxCommandEvent& event );
    void OnAddNewIndMale( wxCommandEvent& event );
    void OnAddNewIndFemale( wxCommandEvent& event );

    void OnFindFamilyID( wxCommandEvent& event );
    void OnFindIndividualID( wxCommandEvent& event );

    void OnListIndex( wxCommandEvent& event );
    void OnListNames( wxCommandEvent& event );
    void OnListIndividuals( wxCommandEvent& event );
    void OnListReferences( wxCommandEvent& event );
    void OnListEvents( wxCommandEvent& event );

    void OnPedChart( wxCommandEvent& event );
    void OnDescChart( wxCommandEvent& event );

    void OnHelpWebHome( wxCommandEvent& event );
    void OnAboutDatabase( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );

    void OnFindBack( wxCommandEvent& event );
    void OnFindForward( wxCommandEvent& event );
    void OnHome( wxCommandEvent& event );
    void OnShowPage( wxCommandEvent& event );

    void OnCloseWindow( wxCloseEvent& event );

    bool NewFile();
    bool OpenFile();
    bool ImportGedcom();

    void SetDatabaseOpen( wxString& path );
    void SetNoDatabase();

    void PushHtmName( const wxString& name );
    void RefreshEditMenu();
};

#define tfpMAX_MENU_ITEMS 50

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
    tfpID_EDIT_IND_MENU,
    tfpID_EDIT_IND_LEFT,
    tfpID_EDIT_IND_RIGHT,
    tfpID_EDIT_CONTEXT_BEG,
    tfpID_EDIT_INDIVIDUAL_LEFT,
    tfpID_EDIT_NEW_MOTHER_LEFT,
    tfpID_EDIT_NEW_FATHER_LEFT,
    tfpID_EDIT_NEW_SPOUSE_LEFT,
    tfpID_EDIT_EXIST_MOTHER_LEFT,
    tfpID_EDIT_EXIST_FATHER_LEFT,
    tfpID_EDIT_EXIST_SPOUSE_LEFT,
    tfpID_EDIT_INDIVIDUAL_RIGHT,
    tfpID_EDIT_NEW_MOTHER_RIGHT,
    tfpID_EDIT_NEW_FATHER_RIGHT,
    tfpID_EDIT_NEW_SPOUSE_RIGHT,
    tfpID_EDIT_EXIST_MOTHER_RIGHT,
    tfpID_EDIT_EXIST_FATHER_RIGHT,
    tfpID_EDIT_EXIST_SPOUSE_RIGHT,
    tfpID_EDIT_CONTEXT_END,
    tfpID_EDIT_INDIVIDUAL,
    tfpID_EDIT_IND_NEW_MALE,
    tfpID_EDIT_IND_NEW_FEMALE,
    tfpID_EDIT_REFERENCE,
    tfpID_FIND_FAMILY_ID,
    tfpID_FIND_INDIVIDUAL_ID,
    tfpID_LIST_SURNAME_INDEX,
    tfpID_LIST_NAMES,
	tfpID_LIST_INDIVIDUALS,
	tfpID_LIST_REFERENCES,
	tfpID_LIST_EVENTS,
    tfpID_PED_CHART,
    tfpID_DESC_CHART,
    tfpID_HELP_WEB_HOME,
    tfpID_HELP_ABOUT_DB,
    tfpID_FIND_BACK,
    tfpID_FIND_FORWARD,
    tfpID_GOTO_HOME,
    tfpID_SHOW_PAGE,
    tfpID_HCTXMENU_BEG,
    tfpID_HCTXMENU_EDIT_FAMILY,
    tfpID_HCTXMENU_EDIT_NEW_SON,
    tfpID_HCTXMENU_EDIT_NEW_DAUR,
    tfpID_HCTXMENU_EDIT_EXIST_SON,
    tfpID_HCTXMENU_EDIT_EXIST_DAUR,
    tfpID_HCTXMENU_EDIT_INDIVIDUAL,
    tfpID_HCTXMENU_EDIT_NEW_MOTHER,
    tfpID_HCTXMENU_EDIT_NEW_FATHER,
    tfpID_HCTXMENU_EDIT_NEW_SPOUSE,
    tfpID_HCTXMENU_EDIT_EXIST_MOTHER,
    tfpID_HCTXMENU_EDIT_EXIST_FATHER,
    tfpID_HCTXMENU_EDIT_EXIST_SPOUSE,
    tfpID_HCTXMENU_END,
    tfpID_INDMENU_PARENTS,
    tfpID_INDMENU_SIBLINGS,
    tfpID_INDMENU_SPOUSES,
    tfpID_INDMENU_CHILDREN,
    tfpID_INDMENU_BEG,
    tfpID_INDMENU_END = tfpID_INDMENU_BEG + tfpMAX_MENU_ITEMS
};

#endif // TFPFRAME_H

