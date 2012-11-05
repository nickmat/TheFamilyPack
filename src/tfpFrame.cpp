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

#include <wx/webview.h>
#include <wx/html/htmlwin.h>
#include <wx/html/htmprint.h>
#include <wx/numdlg.h>

#include <rec/recIndividual.h>
#include <rec/recVersion.h>
#include <rec/recUser.h>

#include "webviewfshandler.h"
#include "tfpFrame.h"
#include "tfpApp.h"
#include "tfpVersion.h"
#include "tfpMemory.h"
#include "tfpRd.h"
#include "tfpWr.h"
#include "dlg/dlgEd.h"
#include "tfpHtml.h"

#include "img/forward.xpm"
#include "img/back.xpm"
#include "img/find.xpm"
#include "img/home.xpm"
#include "img/findref.xpm"

BEGIN_EVENT_TABLE(TfpFrame, wxFrame)
    EVT_MENU( tfpID_NEW_WINDOW, TfpFrame::OnNewWindow )
    EVT_MENU( tfpID_NEW_FILE, TfpFrame::OnNewFile )
    EVT_MENU( tfpID_OPEN_FILE, TfpFrame::OnOpenFile )
    EVT_MENU( tfpID_CLOSE_FILE, TfpFrame::OnCloseFile )
    EVT_MENU( tfpID_IMPORT_GEDCOM, TfpFrame::OnImportGedcom )
    EVT_MENU( tfpID_EXPORT_HTML, TfpFrame::OnExportHtml )
    EVT_MENU( tfpID_PRINT, TfpFrame::OnPrint )
    EVT_MENU( tfpID_PREVIEW, TfpFrame::OnPreview )
    EVT_MENU( tfpID_PAGE_SETUP, TfpFrame::OnPageSetup )
    EVT_MENU( wxID_EXIT, TfpFrame::OnQuit )
    EVT_MENU_RANGE( tfpID_EDIT_CONTEXT_BEG, tfpID_EDIT_CONTEXT_END, TfpFrame::OnEditContext )
    EVT_MENU( tfpID_EDIT_INDIVIDUAL, TfpFrame::OnEditIndividual )
    EVT_MENU( tfpID_EDIT_IND_NEW_MALE, TfpFrame::OnAddNewIndMale )
    EVT_MENU( tfpID_EDIT_IND_NEW_FEMALE, TfpFrame::OnAddNewIndFemale )
    EVT_MENU( tfpID_EDIT_REFERENCE, TfpFrame::OnEditReference )
    EVT_MENU( tfpID_EDIT_RESEARCHER, TfpFrame::OnEditResearcher )
    EVT_MENU( tfpID_FIND_FAMILY_ID, TfpFrame::OnFindFamilyID )
    EVT_MENU( tfpID_FIND_INDIVIDUAL_ID, TfpFrame::OnFindIndividualID )
    EVT_MENU( tfpID_LIST_SURNAME_INDEX, TfpFrame::OnListIndex )
    EVT_MENU( tfpID_LIST_NAMES, TfpFrame::OnListNames )
    EVT_MENU( tfpID_LIST_INDIVIDUALS, TfpFrame::OnListIndividuals )
    EVT_MENU( tfpID_LIST_REFERENCES, TfpFrame::OnListReferences )
    EVT_MENU( tfpID_LIST_EVENTS, TfpFrame::OnListEvents )
    EVT_MENU( tfpID_LIST_RESEARCHERS, TfpFrame::OnListResearchers )
    EVT_MENU( tfpID_PED_CHART, TfpFrame::OnPedChart )
    EVT_MENU( tfpID_DESC_CHART, TfpFrame::OnDescChart )
    EVT_MENU( tfpID_SYSTEM_SETTING, TfpFrame::OnSystemOptions )
    EVT_MENU( tfpID_USER_SETTING, TfpFrame::OnUserOptions )
    EVT_MENU( tfpID_HELP_WEB_HOME, TfpFrame::OnHelpWebHome )
    EVT_MENU( tfpID_HELP_ABOUT_DB, TfpFrame::OnAboutDatabase )
    EVT_MENU( wxID_ABOUT, TfpFrame::OnAbout )
    EVT_MENU( tfpID_FIND_BACK, TfpFrame::OnFindBack )
    EVT_MENU( tfpID_FIND_FORWARD, TfpFrame::OnFindForward )
    EVT_MENU( tfpID_GOTO_HOME, TfpFrame::OnHome )
    EVT_TEXT_ENTER( tfpID_SHOW_PAGE, TfpFrame::OnShowPage )
    EVT_MENU( tfpID_PAGE_ITEM_EDIT, TfpFrame::OnPageItemEdit )
    EVT_WEB_VIEW_NAVIGATING( tfpID_BROWSER, TfpFrame::OnNavigationRequest )
    EVT_MENU_RANGE( tfpID_HCTXMENU_BEG, tfpID_HCTXMENU_END, TfpFrame::OnHtmCtxMenu )
    EVT_MENU_RANGE( tfpID_INDMENU_BEG, tfpID_INDMENU_END, TfpFrame::OnHtmIndMenu )
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

    // create a menu bar for use with an open database
    wxMenu *menuFile = new wxMenu;
    menuFile->Append( tfpID_NEW_WINDOW, _("New &Window\tCtrl-W") );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_NEW_FILE, _("&New Database\tCtrl-N") );
    menuFile->Append( tfpID_OPEN_FILE, _("&Open Database\tCtrl-O") );
    menuFile->Append( tfpID_CLOSE_FILE, _("&Close Database") );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_IMPORT_GEDCOM, _("&Import GEDCOM file") );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_EXPORT_HTML, _("&Export HTML files") );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_PRINT, _("&Print...\tCtrl-P") );
    menuFile->Append( tfpID_PREVIEW, _("Pre&view\tCtrl-Shift-P") );
    menuFile->Append( tfpID_PAGE_SETUP, _("Page Set&up...") );
    menuFile->AppendSeparator();
    menuFile->Append( wxID_EXIT, _("E&xit") );

    wxMenu* menuEdIndL = new wxMenu;
    menuEdIndL->Append( tfpID_EDIT_INDIVIDUAL_LEFT, _("Edit Individual") );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_NEW_MOTHER_LEFT, _("Add new Mother") );
    menuEdIndL->Append( tfpID_EDIT_NEW_FATHER_LEFT, _("Add new Father") );
    menuEdIndL->Append( tfpID_EDIT_NEW_SPOUSE_LEFT, _("Add new Spouse") );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_EXIST_MOTHER_LEFT, _("Add existing Mother") );
    menuEdIndL->Append( tfpID_EDIT_EXIST_FATHER_LEFT, _("Add existing Father") );
    menuEdIndL->Append( tfpID_EDIT_EXIST_SPOUSE_LEFT, _("Add existing Spouse") );

    wxMenu* menuEdIndR = new wxMenu;
    menuEdIndR->Append( tfpID_EDIT_INDIVIDUAL_RIGHT, _("Edit Individual") );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_NEW_MOTHER_RIGHT, _("Add new Mother") );
    menuEdIndR->Append( tfpID_EDIT_NEW_FATHER_RIGHT, _("Add new Father") );
    menuEdIndR->Append( tfpID_EDIT_NEW_SPOUSE_RIGHT, _("Add new Spouse") );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_EXIST_MOTHER_RIGHT, _("Add existing Mother") );
    menuEdIndR->Append( tfpID_EDIT_EXIST_FATHER_RIGHT, _("Add existing Father") );
    menuEdIndR->Append( tfpID_EDIT_EXIST_SPOUSE_RIGHT, _("Add existing Spouse") );

    m_menuEditInd = new wxMenu;
    m_menuEditInd->Append( tfpID_EDIT_IND_LEFT, "? ?..", menuEdIndL );
    m_menuEditInd->Append( tfpID_EDIT_IND_RIGHT, "? ?..", menuEdIndR );
    m_menuEditInd->AppendSeparator();
    m_menuEditInd->Append( tfpID_EDIT_INDIVIDUAL, _("Existing &Individual..") );
    m_menuEditInd->AppendSeparator();
    m_menuEditInd->Append( tfpID_EDIT_IND_NEW_MALE, _("Add New &Male...") );
    m_menuEditInd->Append( tfpID_EDIT_IND_NEW_FEMALE, _("Add New &Female...") );
    
    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append( tfpID_EDIT_IND_MENU, _("&Individual"), m_menuEditInd );
    menuEdit->Append( tfpID_EDIT_REFERENCE, _("&Reference...") );
    menuEdit->Append( tfpID_EDIT_RESEARCHER, _("&Researcher...") );

    wxMenu* menuFind = new wxMenu;
    menuFind->Append( tfpID_FIND_FAMILY_ID, _("&Family ID...") );
    menuFind->Append( tfpID_FIND_INDIVIDUAL_ID, _("&Individual ID...") );

    wxMenu* menuList = new wxMenu;
    menuList->Append( tfpID_LIST_SURNAME_INDEX, _("&Surname Index\tAlt-S") );
    menuList->Append( tfpID_LIST_NAMES, _("&Names\tAlt-N") );
    menuList->Append( tfpID_LIST_INDIVIDUALS, _("&Individuals\tAlt-I") );
    menuList->Append( tfpID_LIST_REFERENCES, _("&References\tAlt-R") );
    menuList->Append( tfpID_LIST_EVENTS, _("&Events\tAlt-E") );
    menuList->Append( tfpID_LIST_RESEARCHERS, _("Resear&chers\tAlt-C") );

    wxMenu* menuChart = new wxMenu;
    menuChart->Append( tfpID_PED_CHART, _("&Pedigree...") );
    menuChart->Append( tfpID_DESC_CHART, _("&Descendant...") );

    wxMenu* menuTools = new wxMenu;
    menuTools->Append( tfpID_SYSTEM_SETTING, _("&System Options...") );
    menuTools->Append( tfpID_USER_SETTING, _("&User Options...") );

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append( tfpID_HELP_WEB_HOME, _("The Family Pack &Website") );
    menuHelp->Append( tfpID_HELP_ABOUT_DB, _("About &Database") );
    menuHelp->Append( wxID_ABOUT, _("&About \"The Family Pack\"") );

    m_menuOpenDB = new wxMenuBar;
    m_menuOpenDB->Append( menuFile, _("&File") );
    m_menuOpenDB->Append( menuEdit, _("&Edit") );
    m_menuOpenDB->Append( menuFind, _("F&ind") );
    m_menuOpenDB->Append( menuList, _("&List") );
    m_menuOpenDB->Append( menuChart, _("&Chart") );
    m_menuOpenDB->Append( menuTools, _("&Tools") );
    m_menuOpenDB->Append( menuHelp, _("&Help") );

    // Menu bar for use with closed database
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

    m_menuClosedDB = new wxMenuBar;
    m_menuClosedDB->Append( menuInitFile, _("&File") );
    m_menuClosedDB->Append( menuInitHelp, _("&Help") );
    SetMenuBar( m_menuClosedDB );

    // Add toolbar
    m_toolbar = new wxToolBar( this, wxID_ANY );
    m_showpage = new wxTextCtrl( m_toolbar, tfpID_SHOW_PAGE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
    wxBitmap bmpForward( forward_xpm );
    wxBitmap bmpBack( back_xpm );
    wxBitmap bmpFind( find_xpm );
    wxBitmap bmpFindref( findref_xpm );
    wxBitmap bmpHome( home_xpm );
    m_toolbar->AddTool( tfpID_FIND_BACK, _("Back"), bmpBack );
    m_toolbar->AddTool( tfpID_FIND_FORWARD, _("Forward"), bmpForward );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_LIST_SURNAME_INDEX, _("Index"), bmpFind );
    m_toolbar->AddTool( tfpID_LIST_REFERENCES, _("References"), bmpFindref );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_GOTO_HOME, _("Home"), bmpHome );
    m_toolbar->AddSeparator();
    m_toolbar->AddControl( m_showpage );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_PAGE_ITEM_EDIT, _("Edit"), imgEditBitmap );
    m_toolbar->Realize();
    SetToolBar( m_toolbar );

    m_statusbar = CreateStatusBar();

    m_webPageAllow = false;
    m_browser = wxWebView::New( this, tfpID_BROWSER );
    m_browser->RegisterHandler( 
        wxSharedPtr<wxWebViewHandler>( new wxWebViewFSHandler( "memory" ))
    );

    SetNoDatabase();
    if( recDb::IsOpen() ) {
        SetDatabaseOpen( recDb::GetFileName() );
        DisplayHomePage();
    } else {
        m_browser->LoadURL( "memory:startup.htm" );
    }
}

/*! \brief Frame destructor.
 */
TfpFrame::~TfpFrame()
{
    if( GetMenuBar() != m_menuOpenDB ) {
        wxDELETE( m_menuOpenDB );
    }
    if( GetMenuBar() != m_menuClosedDB ) {
        wxDELETE( m_menuClosedDB );
    }
}

/*! \brief Called on a New Window menu option event.
 */
void TfpFrame::OnNewWindow( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnNewWindow") );
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

/*! \brief Called on a Close File menu option event.
 */
void TfpFrame::OnCloseFile( wxCommandEvent& event )
{
    recDb::CloseDb();
    SetNoDatabase();
    m_browser->LoadURL( "memory:startup.htm" );
}

/*! \brief Called on a Inport GEDCOM File menu option event.
 */
void TfpFrame::OnImportGedcom( wxCommandEvent& event )
{
    try {
        ImportGedcom();
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

/*! \brief Called on a Export Html menu option event.
 */
void TfpFrame::OnExportHtml( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnExportHtml") );
}

/*! \brief Called on a Print menu option event.
 */
void TfpFrame::OnPrint( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnPrint") );
}

/*! \brief Called on a Print Preview menu option event.
 */
void TfpFrame::OnPreview( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnPreview") );
}

/*! \brief Called on a  Page Setup menu option event.
 */
void TfpFrame::OnPageSetup( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnPageSetup") );
}

/*! \brief Called on an Exit Application menu option event.
 */
void TfpFrame::OnQuit( wxCommandEvent& event )
{
    // true is to force the frame to close
    Close( true );
}

/*! \brief Called on a Edit Individual menu option event.
 */
void TfpFrame::OnEditIndividual( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEditIndividual") );
}

/*! \brief Called on a Add New Male Individual menu option event.
 */
void TfpFrame::OnAddNewIndMale( wxCommandEvent& event )
{
    idt id = 0;
    recDb::Begin();
    try {
        id = tfpAddNewIndividual( 0, SEX_Male );
        if( id != 0 ) {
            recDb::Commit();
            wxString str;
            str << "FI" << id;
            DisplayHtmPage( str );
        } else {
            recDb::Rollback();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

/*! \brief Called on a Add New Female Individual menu option event.
 */
void TfpFrame::OnAddNewIndFemale( wxCommandEvent& event )
{
    idt id = 0;
    recDb::Begin();
    try {
        id = tfpAddNewIndividual( 0, SEX_Female );
        if( id != 0 ) {
            recDb::Commit();
            wxString str;
            str << "FI" << id;
            DisplayHtmPage( str );
        } else {
            recDb::Rollback();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void TfpFrame::OnEditContext( wxCommandEvent& event )
{
    bool ret = false;
    idt id;

    recDb::Begin();
    try {
        switch( event.GetId() )
        {
        case tfpID_EDIT_INDIVIDUAL_LEFT:
            ret = tfpEditIndividual( m_EditIndLeft );
            break;
        case tfpID_EDIT_NEW_MOTHER_LEFT:
            ret = tfpAddNewParent( m_EditIndLeft, SEX_Female );
            break;
        case tfpID_EDIT_NEW_FATHER_LEFT:
            ret = tfpAddNewParent( m_EditIndLeft, SEX_Male );
            break;
        case tfpID_EDIT_NEW_SPOUSE_LEFT:
            id = tfpAddNewIndividual( m_EditFamily, SEX_Female );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_MOTHER_LEFT:
            ret = tfpAddExistParent( m_EditIndLeft, SEX_Female );
            break;
        case tfpID_EDIT_EXIST_FATHER_LEFT:
            ret = tfpAddExistParent( m_EditIndLeft, SEX_Male );
            break;
        case tfpID_EDIT_EXIST_SPOUSE_LEFT:
            ret = tfpAddExistSpouse( m_EditIndLeft, SEX_Female );
            break;
        case tfpID_EDIT_INDIVIDUAL_RIGHT:
            ret = tfpEditIndividual( m_EditIndRight );
            break;
        case tfpID_EDIT_NEW_MOTHER_RIGHT:
            ret = tfpAddNewParent( m_EditIndRight, SEX_Female );
            break;
        case tfpID_EDIT_NEW_FATHER_RIGHT:
            ret = tfpAddNewParent( m_EditIndRight, SEX_Male );
            break;
        case tfpID_EDIT_NEW_SPOUSE_RIGHT:
            id = tfpAddNewIndividual( m_EditFamily, SEX_Male );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_MOTHER_RIGHT:
            ret = tfpAddExistParent( m_EditIndRight, SEX_Female );
            break;
        case tfpID_EDIT_EXIST_FATHER_RIGHT:
            ret = tfpAddExistParent( m_EditIndRight, SEX_Male );
            break;
        case tfpID_EDIT_EXIST_SPOUSE_RIGHT:
            ret = tfpAddExistSpouse( m_EditIndRight, SEX_Female );
            break;
#if 0
        case tfpID_HCTXMENU_EDIT_FAMILY:
            ret = tfpEditFamily( id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SON:
            if( tfpAddNewChild( id, SEX_Male ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_NEW_DAUR:
            if( tfpAddNewChild( id, SEX_Female ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SON:
            ret = tfpAddExistChild( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_DAUR:
            ret = tfpAddExistChild( id, SEX_Female );
            break;
#endif
        }
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}


/*! \brief Called on a Edit Reference menu option event.
 */
void TfpFrame::OnEditReference( wxCommandEvent& event )
{
    long num = wxGetNumberFromUser(
        wxT("Enter the Reference ID or 0 for new Reference"),

        wxT("Reference ID:"),
        wxT("Edit Reference"),
        (long) 0, (long) 0, (long) INT_MAX
    );
    if( num < 0 ) return;

    recDb::Begin();
    try {
        bool ret = tfpEditReference( (idt) num );
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

/*! \brief Called on a Edit Researcher menu option event.
 */
void TfpFrame::OnEditResearcher( wxCommandEvent& event )
{
    long num = wxGetNumberFromUser(
        wxT("Enter the Researcher ID or 0 for new Reference"),

        wxT("Researcher ID:"),
        wxT("Edit Researcher"),
        (long) 0, (long) 0, (long) INT_MAX
    );
    if( num < 0 ) return;

    recDb::Begin();
    try {
        bool ret = tfpEditResearcher( (idt) num );
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

/*! \brief Called on a Find Family ID menu option event.
 */
void TfpFrame::OnFindFamilyID( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnFindFamilyID") );
}

/*! \brief Called on a Find Individual ID menu option event.
 */
void TfpFrame::OnFindIndividualID( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnFindIndividualID") );
}

/*! \brief Called on a List Index menu option event.
 */
void TfpFrame::OnListIndex( wxCommandEvent& event )
{
    DisplayHtmPage( "N" );
}

/*! \brief Called on a List Names menu option event.
 */
void TfpFrame::OnListNames( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnListNames") );
}

/*! \brief Called on a  List Individuals menu option event.
 */
void TfpFrame::OnListIndividuals( wxCommandEvent& event )
{
    DisplayHtmPage( "N*" );
}

/*! \brief Called on a List References menu option event.
 */
void TfpFrame::OnListReferences( wxCommandEvent& event )
{
    DisplayHtmPage( "R" );
}

/*! \brief Called on a List Events menu option event.
 */
void TfpFrame::OnListEvents( wxCommandEvent& event )
{
    DisplayHtmPage( "E" );
}

/*! \brief Called on a List Researchers menu option event.
 */
void TfpFrame::OnListResearchers( wxCommandEvent& event )
{
    DisplayHtmPage( "Re" );
}

/*! \brief Called on a Pedigree Chart menu option event.
 */
void TfpFrame::OnPedChart( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnPedChart") );
}

/*! \brief Called on a Descendant Chart menu option event.
 */
void TfpFrame::OnDescChart( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnDescChart" );
}

/*! \brief Called on a System Settings menu option event.
 */
void TfpFrame::OnSystemOptions( wxCommandEvent& event )
{
    recDb::Begin();
    try {
        bool ret = tfpEditSystem();
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

/*! \brief Called on a User Settings menu option event.
 */
void TfpFrame::OnUserOptions( wxCommandEvent& event )
{
    recDb::Begin();
    try {
        bool ret = tfpEditUserSettings();
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
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
            "For TFP Database Version %s.\n"
            "Built with %s and SQLite %s\n"
            "by %s\n"
            "running under %s."),

            tfpTitle,
            recVerStr,
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

/*! \brief Called on a Help, About Database menu option event.
 *
 *  Displays a message box with information about the currently.
 *  open database.
 */
void TfpFrame::OnAboutDatabase( wxCommandEvent& event )
{
    wxMessageBox(
        wxString::Format(
            _("Database \"%s\"\nVersion %s"),
            m_dbFileName, recVersion::GetVersionStr()
        ),
        _("About TFP Database"),
        wxOK | wxICON_INFORMATION,
        this
    );
}

/*! \brief Called on a Find Back button option event.
 */
void TfpFrame::OnFindBack( wxCommandEvent& event )
{
    size_t ind = m_back.size();

    if( ind > 1 ) {
        --ind;
        m_forward.push_back( m_back[ind] );
        m_toolbar->EnableTool( tfpID_FIND_FORWARD, true );
        m_back.pop_back();
        if( ind == 1 ) {
            m_toolbar->EnableTool( tfpID_FIND_BACK, false );
        }
        RefreshHtmPage();
        RefreshEditMenu();
    }
}

/*! \brief Called on a Find Forward button option event.
 */
void TfpFrame::OnFindForward( wxCommandEvent& event )
{
    size_t ind = m_forward.size();

    if( ind > 0 )
    {
        --ind;
        wxString name = m_forward[ind];
        m_back.push_back( name );
        if( m_back.size() > 1 ) {
            m_toolbar->EnableTool( tfpID_FIND_BACK, true );
        }
        m_forward.pop_back();
        if( ind == 0 ) {
            m_toolbar->EnableTool( tfpID_FIND_FORWARD, false );
        }
        RefreshHtmPage();
        RefreshEditMenu();
    }
}

/*! \brief Called on a Home button option event.
 */
void TfpFrame::OnHome( wxCommandEvent& event )
{
    DisplayHomePage();
}

/*! \brief Called on a pressing enter in toolbar text box.
 */
void TfpFrame::OnShowPage( wxCommandEvent& event )
{
    wxString page = m_showpage->GetValue();
    m_showpage->SetValue( wxEmptyString );
//    tfpDisplayNote( this, page );
    DisplayHtmPage( page );
}

/*! \brief Called when the toolbar Edit button is pressed.
 */
void TfpFrame::OnPageItemEdit( wxCommandEvent& event )
{
    wxString display = GetDisplay();
    wxUniChar uch = display.GetChar( 0 );
    idt id = recGetID( display.Mid(1) );
    recDb::Begin();
    try {
        bool ret = false;
        switch( uch.GetValue() )
        {
        case 'F': 
            {
                recFamily fam(id);
                if( id == 0 && display.StartsWith( "FI" ) ) {
                    fam.Decode( display );
                }
                ret = tfpEditFamily( fam );
                break;
            }
        case 'R':
            ret = tfpEditReference( id );
            break;
        case 'E':
            ret = tfpEditEvent( id );
            break;
        case 'I':
            ret = tfpEditIndividual( id );
            break;
        }
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void TfpFrame::OnNavigationRequest( wxWebViewEvent& evt )
{
    if( m_webPageAllow ) {
        m_webPageAllow = false;
        return;
    }
    wxString url = evt.GetURL();
    wxString target = evt.GetTarget();

    if( url == wxWebViewDefaultURLStr ) return;
    if( url.StartsWith( "memory:" ) ) return;
    // We will handle all other navigation ourselves.
    evt.Veto();

    if( url.StartsWith( "tfp:" ) ) {
        DisplayHtmPage( url.Mid( 4 ) );
        return;
    }
    if( url.StartsWith( "tfpe:" ) ) {
        DoEdit( url.Mid( 5 ) );
        return;
    }
    if( url.StartsWith( "tfpi:" ) ) {
        DoPopupNote( url.Mid( 5 ) );
        return;
    }
    if( url.StartsWith( "tfpc:" ) ) {
        DoTfpCommand( url.Mid( 5 ) );
        return;
    }
    if( url.StartsWith( "http:" ) || url.StartsWith( "https:" ) ) {
        wxLaunchDefaultBrowser( url );
        return;
    }

    wxMessageBox(
        wxString::Format( 
            _("Unable to proccess link\n[%s]\n[%s]"), url, target
        ),
        _("Unknown Link")
    );
}

void TfpFrame::OnHtmCtxMenu( wxCommandEvent& event )
{
    bool ret = false;
    Sex sex;
    idt id = recGetID( m_ctxmenuref.Mid(1) );
    recFamily fam(id);
    if( id == 0 && m_ctxmenuref.StartsWith( "F0," ) ) {
        fam.Decode( m_ctxmenuref );
    }

    recDb::Begin();
    try {
        switch( event.GetId() )
        {
        case tfpID_HCTXMENU_EDIT_FAMILY:
            ret = tfpEditFamily( fam );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SON:
            if( tfpAddNewChild( id, SEX_Male ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_NEW_DAUR:
            if( tfpAddNewChild( id, SEX_Female ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SON:
            ret = tfpAddExistChild( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_DAUR:
            ret = tfpAddExistChild( id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_INDIVIDUAL:
            ret = tfpEditIndividual( id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_MOTHER:
            ret = tfpAddNewParent( id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_FATHER:
            ret = tfpAddNewParent( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SPOUSE:
            sex = ( m_ctxmenuref.GetChar(0) == 'H' ) ? SEX_Female : SEX_Male;
            id = tfpAddNewIndividual( recIndividual::GetDefaultFamily( id ), sex );
            if( id ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_MOTHER:
            ret = tfpAddExistParent( id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_FATHER:
            ret = tfpAddExistParent( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SPOUSE:
            sex = ( m_ctxmenuref.GetChar(0) == 'H' ) ? SEX_Female : SEX_Male;
            ret = tfpAddExistSpouse( id, sex );
            break;
        case tfpID_HCTXMENU_EDIT_REFERENCE:
            ret = tfpEditReference( id );
            break;
        case tfpID_HCTXMENU_EDIT_EVENT:
            ret = tfpEditEvent( id );
            break;
        }
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void TfpFrame::OnHtmIndMenu( wxCommandEvent& event )
{
    size_t i = event.GetId() - tfpID_INDMENU_BEG;
    DisplayHtmPage( m_ctxmenuPages[i] );
}


/*! \brief Called on a Close Window event.
 */
void TfpFrame::OnCloseWindow( wxCloseEvent& event )
{
    this->Destroy();
}


bool TfpFrame::NewFile()
{
    bool ret = false;
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
            SetDatabaseOpen( path );
            // Start with the 1st (empty) Family.
            DisplayHtmPage( "F1" );
            ret = true;
        }
    }
    return ret;
}

bool TfpFrame::OpenFile()
{
    bool ret = false;
    wxString caption = _("Select TFP Database");
    wxString wildcard = _("TFP Database (*.tfpd)|*.tfpd");
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        if( recDb::OpenDb( path ) == true )
        {
            SetDatabaseOpen( path );
            DisplayHomePage();
            ret = true;
        }
    }
    return ret;
}

bool TfpFrame::ImportGedcom()
{
    bool ret = false;
    wxString caption = _("Select GEDCOM file");
    wxString wildcard = "GEDCOM (*.ged)|*.ged";
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        if( tfpReadGedcom( path ) )
        {
            SetDatabaseOpen( path );
            DisplayHtmPage( "F1" );
            ret = true;
        } else {
            wxMessageBox( _("Error Reading GEDCOM File"), _("Import") );
        }
    }
    return ret;
}

void TfpFrame::OpenTestFile()
{
    wxString caption = _("Select htm file");
    wxString wildcard = _("Htm file (*.htm)|*.htm");
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        m_webPageAllow = true;
        m_browser->LoadURL( "file://" + path );
    }
}

// Handles scheme "tfpc:" 
void TfpFrame::DoTfpCommand( const wxString& href )
{
    if( href == "New" ) {
        NewFile();
    } else if( href == "Open" ) {
        OpenFile();
    } else if( href == "Import" ) {
        ImportGedcom();
#ifdef _DEBUG
    } else if( href == "Test" ) {
        OpenTestFile();
#endif
    } else if( href.StartsWith( "M" ) ) {
        DoHtmCtxMenu( href.Mid( 1 ) );
    } else {
        wxMessageBox( 
            wxString::Format( _("Error: Invalid Command \"tfpc:%s\""), href ),
            _("Link Error") 
        );
    }
}

void TfpFrame::DoEdit( const wxString& href )
{
    bool ret = false;

    recDb::Begin();
    try {
        if( href.StartsWith( "IL" ) || href.StartsWith( "IR" ) ) {
            ret = tfpAddNewSpouse( href.Mid(1) );
        } else if( href.StartsWith( "IF" ) || href.StartsWith( "IM" ) ) {
            ret = tfpAddNewParent( href.Mid(1) );
        } else if( href.StartsWith( "I" ) ) {
            ret = tfpEditIndividual( recGetID( href.Mid(1) ) );
        } else if( href.StartsWith( "Re" ) ) {
            ret = tfpEditResearcher( recGetID( href.Mid(2) ) );
        } else if( href.StartsWith( "R" ) ) {
            ret = tfpEditReference( recGetID( href.Mid(1) ) );
        } else {
            wxMessageBox(
                wxString::Format( _("Unable to edit ref\n[%s]"), href ),
                _("Unknown Edit")
            );
        }
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void TfpFrame::DoPopupNote( const wxString& ref )
{
    dlgNote* note = new dlgNote( this, ref );
    note->Show();
}

void TfpFrame::DoHtmCtxMenu( const wxString& ref )
{
    m_ctxmenuref = ref;
    wxMenu* menu = new wxMenu;

    switch( (wxChar) ref.GetChar( 0 ) )
    {
    case 'F': // Edit family record or children
        menu->Append( tfpID_HCTXMENU_EDIT_FAMILY, _("Edit Family") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_SON, _("Add new Son") );
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_DAUR, _("Add new Daughter") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_SON, _("Add existing Son") );
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_DAUR, _("Add existing Daughter") );
        break;
    case 'H': case 'W': // Edit a Husb or Wife Individual
        menu->Append( tfpID_HCTXMENU_EDIT_INDIVIDUAL, _("Edit Individual") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_MOTHER, _("Add new Mother") );
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_FATHER, _("Add new Father") );
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_SPOUSE, _("Add new Spouse") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_MOTHER, _("Add existing Mother") );
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_FATHER, _("Add existing Father") );
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_SPOUSE, _("Add existing Spouse") );
        break;
    case 'R':
        // Parents, Spouses (Marriage), Siblings, and Children
        // List individuals and jump to the selected individuals family
        AddFamiliesToMenu( ref, menu, tfpID_INDMENU_BEG );
        break;
    default:
        delete menu;
        wxMessageBox( wxT("Error: \"") + ref + wxT("\" Unknown Menu"), wxT("Link Error") );
        return;
    }

    PopupMenu( menu );
    delete menu;
}

int TfpFrame::AddFamiliesToMenu( const wxString& ref, wxMenu* menu, int cmd_ID )
{
    recFamilyVec families;
    size_t c = 0, i, j;
    recIndividualList inds;
    wxLongLong_t indID;
    ref.Mid( 1 ).ToLongLong( &indID );
    m_ctxmenuPages.clear();
    wxString page;


    menu->Append( cmd_ID + c, wxT("Family") );
    m_ctxmenuPages.push_back( "FI"+recGetStr( indID ) );
    c++;

    wxMenu* parmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_PARENTS, "Parents", parmenu );

    families = recIndividual::GetParentList( indID );
    int items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        if( families[i].f_husb_id != 0 ) {
            parmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_husb_id ) );
        }
        if( families[i].f_wife_id != 0 ) {
            parmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_wife_id ) );
        }
        m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
        c++;
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_PARENTS, false );
    }

    wxMenu* sibmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_SIBLINGS, "Siblings", sibmenu );
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        inds = families[i].GetChildren();
        for( j = 0 ; j < inds.size() ; j++ ) {
            if( inds[j].f_id == indID ) continue;
            sibmenu->Append( cmd_ID + c, inds[j].GetFullName() );
            m_ctxmenuPages.push_back( "FI"+recGetStr( inds[j].f_id ) );
            c++;
        }
        inds.empty();
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_SIBLINGS, false );
    }

    wxMenu* marmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_SPOUSES, "Spouses", marmenu );
    families.empty();
    families = recIndividual::GetFamilyList( indID );
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        if( families[i].f_husb_id != 0 && families[i].f_husb_id != indID ) {
            marmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_husb_id ) );
            m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
            c++;
        }
        if( families[i].f_wife_id != 0 && families[i].f_wife_id != indID ) {
            marmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_wife_id ) );
            m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
            c++;
        }
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_SPOUSES, false );
    }

    wxMenu* kidmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_CHILDREN, "Children", kidmenu );
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        inds.empty();
        inds = families[i].GetChildren();
        for( j = 0 ; j < inds.size() ; j++ ) {
            kidmenu->Append( cmd_ID + c, inds[j].GetFullName() );
            m_ctxmenuPages.push_back( "FI"+recGetStr( inds[j].f_id ) );
            c++;
        }
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_CHILDREN, false );
    }
    families.clear();
    inds.clear();
    return c;
}

void TfpFrame::SetDatabaseOpen( const wxString& path )
{
    wxFileName dbfile( path );
    m_dbFileName = dbfile.GetFullPath();
    wxString fmt( wxString::Format( "TFP: %s, %%s", dbfile.GetName() ) );
    SetMenuBar( m_menuOpenDB );
    m_toolbar->EnableTool( tfpID_LIST_SURNAME_INDEX, true );
    m_toolbar->EnableTool( tfpID_LIST_REFERENCES, true );
    m_toolbar->EnableTool( tfpID_GOTO_HOME, true );
    m_showpage->Enable( true );
}

void TfpFrame::SetNoDatabase()
{
    m_dbFileName = wxEmptyString;
    SetMenuBar( m_menuClosedDB );
    m_toolbar->EnableTool( tfpID_LIST_SURNAME_INDEX, false );
    m_toolbar->EnableTool( tfpID_LIST_REFERENCES, false );
    m_toolbar->EnableTool( tfpID_GOTO_HOME, false );
    m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, false );
    m_showpage->Enable( false );
    m_back.clear();
    m_toolbar->EnableTool( tfpID_FIND_BACK, false );
    m_forward.clear();
    m_toolbar->EnableTool( tfpID_FIND_FORWARD, false );
}

void TfpFrame::PushHtmName( const wxString& name )
{
    m_back.push_back( name );
    if( m_back.size() > 1 ) {
        m_toolbar->EnableTool( tfpID_FIND_BACK, true );
    }
    if( m_forward.size() != 0 ) {
        m_forward.clear();
        m_toolbar->EnableTool( tfpID_FIND_FORWARD, false );
    }
    RefreshEditMenu();
}

wxString TfpFrame::GetCurrentName()
{
    size_t ind = m_back.size();
    if( ind >= 1 ) {
        return m_back[ind-1];
    }
    return wxEmptyString;
}

void TfpFrame::RefreshEditMenu()
{
    wxASSERT( m_back.size() > 0 );
    wxString disp = GetDisplay();
    wxUniChar uch = disp.GetChar( 0 );
    wxUniChar uch1;
    wxString name;
    wxString noname = _("none");

    // Clear previous settings
    m_menuEditInd->SetLabel( tfpID_EDIT_IND_LEFT, noname );
    m_menuEditInd->Enable( tfpID_EDIT_IND_LEFT, false );
    m_menuEditInd->SetLabel( tfpID_EDIT_IND_RIGHT, noname );
    m_menuEditInd->Enable( tfpID_EDIT_IND_RIGHT, false );
    m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, false );

    switch( uch.GetValue() ) 
    {
    case 'F': {
            m_EditFamily = 0;
            uch1 = disp.GetChar( 1 );
            if( uch1.GetValue() == 'I' ) {
                idt indID = recGetID( disp.Mid( 2 ) );
                m_EditFamily = recIndividual::GetDefaultFamily( indID );
            } else {
                m_EditFamily = recGetID( disp.Mid( 1 ) );
            }
            recFamily fam(m_EditFamily);
            if( fam.f_husb_id ) {
                name = recIndividual::GetFullName( fam.f_husb_id );
                m_menuEditInd->SetLabel( tfpID_EDIT_IND_LEFT, name );
                m_menuEditInd->Enable( tfpID_EDIT_IND_LEFT, true );
            } else {
                m_menuEditInd->SetLabel( tfpID_EDIT_IND_LEFT, noname );
                m_menuEditInd->Enable( tfpID_EDIT_IND_LEFT, false );
            }
            m_EditIndLeft = fam.f_husb_id;
            if( fam.f_wife_id ) {
                name = recIndividual::GetFullName( fam.f_wife_id );
                m_menuEditInd->SetLabel( tfpID_EDIT_IND_RIGHT, name );
                m_menuEditInd->Enable( tfpID_EDIT_IND_RIGHT, true );
            } else {
                m_menuEditInd->SetLabel( tfpID_EDIT_IND_RIGHT, noname );
                m_menuEditInd->Enable( tfpID_EDIT_IND_RIGHT, false );
            }
            m_EditIndRight = fam.f_wife_id;
            // Update Toolbar
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'R': case 'E': case 'I':
        if( disp.size() >= 2 && wxIsdigit( disp.GetChar( 1 ) ) ) {
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    }
}

bool TfpFrame::DisplayHtmPage( const wxString& name )
{
    wxString text = tfpGetDisplayText( name );
    if( !text.IsEmpty() ) {
        PushHtmName( name );
        m_browser->SetPage( text, "" );
        return true;
    }
    return false;
}

void TfpFrame::RefreshHtmPage()
{
    wxString name = GetCurrentName();
    if( name.size() ) {
        m_browser->SetPage( tfpGetDisplayText( name ), "" );
    }
}

bool TfpFrame::DisplayHomePage()
{
    return DisplayHtmPage( recGetHomeDisplay() ); 
}

/////////////////////////////////////////////////////////////
// This could be moved to a new file

wxString tfpGetDisplayText( const wxString& name )
{
    wxUniChar uch, uch1;
    wxLongLong_t num;
    bool success;
    wxString ErrorPage = "<html><head><title>Error</title></head>"
        "<body><h1>Error writing [%s]</h1><p>%s</p></body></html>";

    wxASSERT( name.size() > 0 );
    uch = name.GetChar( 0 );
    switch( uch.GetValue() )
    {
    case 'C':  // Chart reference
        success = name.Mid(2).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format( 
                ErrorPage, name, _("Invalid Individual ID link") 
            );
        }
        switch( (wxChar) name.GetChar( 1 ) )
        {
        case 'D':
            return tfpCreateDescChart( num );
        case 'P':
            return tfpCreatePedChart( num );
        }
        return wxString::Format( 
            ErrorPage, name, _("Invalid Chart link reference") 
        );
    case 'D':  // Date
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format( 
                ErrorPage, name, _("Invalid Date ID link") 
            );
        }
        return tfpWriteDate( num );
    case 'E':  // Reference Document
        if( name == "E" ) {
            return tfpWriteEventIndex();
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format( 
                ErrorPage, name, _("Invalid Reference Document ID link") 
            );
        }
        return tfpWriteEventPage( num );
    case 'F':  // Family reference
        if( name.GetChar( 1 ) == 'I' ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                return wxString::Format( 
                    ErrorPage, name, _("Invalid Individual ID link") 
                );
            }
            return tfpWriteIndFamilyPage( num );
        }
        return tfpWriteFamilyPage( name.Mid(1) );
    case 'I':  // Individual reference
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format( 
                ErrorPage, name, _("Invalid Individual ID link") 
            );
        }
        return tfpWriteIndividualPage( num );
    case 'N':  // Name index
        if( name == "N" ) {
            return tfpWriteIndividualIndex();
        }
        if( name == "N*" ) {
            return tfpWriteIndividualList( wxEmptyString );
        }
        return tfpWriteIndividualList( name.Mid( 1 ) );
    case 'P':  // Place
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format( 
                ErrorPage, name, _("Invalid Place ID link") 
            );
        }
        return tfpWritePlace( num );
    case 'R':  // Reference Document
        if( name == "R" ) {
            return tfpWriteReferenceIndex();
        }
        if( name == "Re" ) {
            return tfpWriteResearcherList();
        }
        uch1 = name.GetChar( 1 );
        if( !wxIsdigit( uch1 ) ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                return wxString::Format( 
                    ErrorPage, name, _("Invalid ID link") 
                );
            }
            switch( uch1.GetValue() )
            {
            case 's':
                return tfpWriteRelationship( num );
            default:
                return wxString::Format( 
                    ErrorPage, name, _("Invalid ID link") 
                );
            }
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format( 
                ErrorPage, name, _("Invalid Reference Document ID link") 
            );
        }
        return tfpWriteReferencePage( num );
    }
    return wxString::Format( 
        ErrorPage, name, _("Invalid Display Name") 
    );
}


// End of tfpFrame.cpp file

