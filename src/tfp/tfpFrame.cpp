/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpFrame.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpFrame class source.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25 September 2010
 * Copyright:   Copyright (c) 2010 ~ 2018, Nick Matthews.
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

#include <wx/filename.h>

#include <wx/webview.h>
#include <wx/webviewfshandler.h>
#include <wx/numdlg.h>

#include <rec/recIndividual.h>
#include <rec/recVersion.h>
#include <rec/recUser.h>
#include <rg/rgDialogs.h>

#include "tfpApp.h"
#include "tfpExport.h"
#include "tfpFrame.h"
#include "tfpMemory.h"
#include "tfpRd.h"
#include "tfpVersion.h"
#include "tfpWr.h"

#include "img/forward.xpm"
#include "img/back.xpm"
#include "img/find.xpm"
#include "img/home.xpm"
#include "img/ref.xpm"
#include "img/event.xpm"
#include "img/gallery.xpm"

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "img/tfp.xpm"
#endif

BEGIN_EVENT_TABLE(TfpFrame, wxFrame)
    EVT_MENU( tfpID_NEW_WINDOW, TfpFrame::OnNewWindow )
    EVT_MENU( tfpID_NEW_FILE, TfpFrame::OnNewFile )
    EVT_MENU( tfpID_OPEN_FILE, TfpFrame::OnOpenFile )
    EVT_MENU( tfpID_CLOSE_FILE, TfpFrame::OnCloseFile )
    EVT_MENU( tfpID_IMPORT_GEDCOM, TfpFrame::OnImportGedcom )
    EVT_MENU( tfpID_EXPORT_GEDCOM, TfpFrame::OnExportGedcom )
    EVT_MENU( tfpID_EXPORT_HTML, TfpFrame::OnExportHtml )
    EVT_MENU( tfpID_PRINT, TfpFrame::OnPrint )
    EVT_MENU( tfpID_PREVIEW, TfpFrame::OnPreview )
    EVT_MENU( tfpID_PAGE_SETUP, TfpFrame::OnPageSetup )
    EVT_MENU( wxID_EXIT, TfpFrame::OnQuit )
    EVT_MENU_RANGE( tfpID_EDIT_CONTEXT_BEG, tfpID_EDIT_CONTEXT_END, TfpFrame::OnEditContext )
    EVT_MENU( tfpID_EDIT_INDIVIDUAL, TfpFrame::OnEditIndividual )
    EVT_MENU( tfpID_EDIT_IND_NEW_MALE, TfpFrame::OnAddNewIndMale )
    EVT_MENU( tfpID_EDIT_IND_NEW_FEMALE, TfpFrame::OnAddNewIndFemale )
//    EVT_MENU( tfpID_EDIT_EVENT_CURRENT, TfpFrame::OnEditEventCurrent )
//    EVT_MENU( tfpID_EDIT_EVENT_NEW, TfpFrame::OnEditEventNew )
    EVT_MENU( tfpID_EDIT_NEW_REFERENCE, TfpFrame::OnEditNewReference )
    EVT_MENU( tfpID_EDIT_REFERENCE, TfpFrame::OnEditReference )
    EVT_MENU( tfpID_EDIT_RESEARCHER, TfpFrame::OnEditResearcher )
    EVT_MENU( tfpID_FIND_FAMILY_ID, TfpFrame::OnFindFamilyID )
    EVT_MENU( tfpID_FIND_INDIVIDUAL_ID, TfpFrame::OnFindIndividualID )
    EVT_MENU( tfpID_FIND_EVENT_ID, TfpFrame::OnFindEventID )
    EVT_MENU( tfpID_LIST_SURNAME_INDEX, TfpFrame::OnListIndex )
    EVT_MENU( tfpID_LIST_PERSONAS, TfpFrame::OnListPersonas )
    EVT_MENU( tfpID_LIST_INDIVIDUALS, TfpFrame::OnListIndividuals )
    EVT_MENU( tfpID_LIST_GALLERIES, TfpFrame::OnListGalleries )
    EVT_MENU( tfpID_LIST_ALL_REFERENCES, TfpFrame::OnListReferences )
    EVT_MENU( tfpID_LIST_PAGED_REFERENCES, TfpFrame::OnListPagedReferences )
    EVT_MENU( tfpID_LIST_ALL_EVENTS, TfpFrame::OnListAllEvents )
    EVT_MENU( tfpID_LIST_PAGED_EVENTS, TfpFrame::OnListPagedEvents )
    EVT_MENU( tfpID_LIST_SELECTED_EVENTS, TfpFrame::OnListSelectedEvents )
    EVT_MENU( tfpID_LIST_ALL_EVENTUMS, TfpFrame::OnListAllEventas )
    EVT_MENU( tfpID_LIST_PAGED_EVENTUMS, TfpFrame::OnListPagedEventas )
    EVT_MENU( tfpID_LIST_SELECTED_EVENTUMS, TfpFrame::OnListSelectedEventas )
    EVT_MENU( tfpID_LIST_RESEARCHERS, TfpFrame::OnListResearchers )
    EVT_MENU( tfpID_PED_CHART, TfpFrame::OnPedChart )
    EVT_MENU( tfpID_DESC_CHART, TfpFrame::OnDescChart )
    EVT_MENU( tfpID_SYSTEM_SETTING, TfpFrame::OnSystemOptions )
    EVT_MENU( tfpID_USER_SETTING, TfpFrame::OnUserOptions )
    EVT_MENU( tfpID_TOOL_SYSTEM_CHECK, TfpFrame::OnSystemCheck )
    EVT_MENU( tfpID_HELP_WEB_HOME, TfpFrame::OnHelpWebHome )
    EVT_MENU( tfpID_HELP_ABOUT_DB, TfpFrame::OnAboutDatabase )
    EVT_MENU( wxID_ABOUT, TfpFrame::OnAbout )
    EVT_MENU( tfpID_FIND_BACK, TfpFrame::OnFindBack )
    EVT_MENU( tfpID_FIND_FORWARD, TfpFrame::OnFindForward )
    EVT_MENU( tfpID_GOTO_HOME, TfpFrame::OnHome )
    EVT_TEXT_ENTER( tfpID_SHOW_PAGE, TfpFrame::OnShowPage )
    EVT_MENU( tfpID_PAGE_ITEM_EDIT, TfpFrame::OnPageItemEdit )
    EVT_WEBVIEW_NAVIGATING( tfpID_BROWSER, TfpFrame::OnNavigationRequest )
    EVT_MENU_RANGE( tfpID_HCTXMENU_BEG, tfpID_HCTXMENU_END, TfpFrame::OnHtmCtxMenu )
    EVT_MENU_RANGE( tfpID_INDMENU_BEG, tfpID_INDMENU_END, TfpFrame::OnHtmIndMenu )
    EVT_IDLE( TfpFrame::OnIdle )
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
    m_changeState = recDb::GetChange();
    // Set frames Icon
    SetIcon( wxICON( tfp ) );

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
    menuFile->Append( tfpID_EXPORT_GEDCOM, _("Export &GEDCOM file") );
    menuFile->Append( tfpID_EXPORT_HTML, _("&Export HTML files") );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_PRINT, _("&Print...\tCtrl-P") );
    menuFile->Append( tfpID_PREVIEW, _("Pre&view\tCtrl-Shift-P") );
    menuFile->Append( tfpID_PAGE_SETUP, _("Page Set&up...") );
    menuFile->AppendSeparator();
    menuFile->Append( wxID_EXIT, _("E&xit") );

    wxMenu* menuEdIndL = new wxMenu;
    menuEdIndL->Append( tfpID_EDIT_INDIVIDUAL_LEFT, _("&Edit Individual") );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_NEW_MOTHER_LEFT, _("Add new &Mother") );
    menuEdIndL->Append( tfpID_EDIT_NEW_FATHER_LEFT, _("Add new &Father") );
    menuEdIndL->Append( tfpID_EDIT_NEW_SPOUSE_LEFT, _("Add new &Spouse") );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_EXIST_MOTHER_LEFT, _("Add existing M&other") );
    menuEdIndL->Append( tfpID_EDIT_EXIST_FATHER_LEFT, _("Add existing F&ather") );
    menuEdIndL->Append( tfpID_EDIT_EXIST_SPOUSE_LEFT, _("Add existing S&pouse") );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_DELETE_IND_LEFT, _("&Delete Individual") );

    wxMenu* menuEdIndR = new wxMenu;
    menuEdIndR->Append( tfpID_EDIT_INDIVIDUAL_RIGHT, _("&Edit Individual") );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_NEW_MOTHER_RIGHT, _("Add new &Mother") );
    menuEdIndR->Append( tfpID_EDIT_NEW_FATHER_RIGHT, _("Add new &Father") );
    menuEdIndR->Append( tfpID_EDIT_NEW_SPOUSE_RIGHT, _("Add new &Spouse") );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_EXIST_MOTHER_RIGHT, _("Add existing M&other") );
    menuEdIndR->Append( tfpID_EDIT_EXIST_FATHER_RIGHT, _("Add existing F&ather") );
    menuEdIndR->Append( tfpID_EDIT_EXIST_SPOUSE_RIGHT, _("Add existing S&pouse") );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_DELETE_IND_RIGHT, _("&Delete Individual") );

    wxMenu* menuEdFam = new wxMenu;
    menuEdFam->Append( tfpID_EDIT_FAMILY, _("&Edit Family") );
    menuEdFam->AppendSeparator();
    menuEdFam->Append( tfpID_EDIT_NEW_SON, _("Add new &Son") );
    menuEdFam->Append( tfpID_EDIT_NEW_DAUR, _("Add new &Daughter") );
    menuEdFam->AppendSeparator();
    menuEdFam->Append( tfpID_EDIT_EXIST_SON, _("Add existing S&on") );
    menuEdFam->Append( tfpID_EDIT_EXIST_DAUR, _("Add existing D&aughter") );

    m_menuEditInd = new wxMenu;
    m_menuEditInd->Append( tfpID_EDIT_IND_LEFT, "? ?..", menuEdIndL );
    m_menuEditInd->Append( tfpID_EDIT_IND_RIGHT, "? ?..", menuEdIndR );
    m_menuEditInd->Append( tfpID_EDIT_FAMILY_MENU, _("F&amily"), menuEdFam );
    m_menuEditInd->AppendSeparator();
    m_menuEditInd->Append( tfpID_EDIT_INDIVIDUAL, _("Existing &Individual..") );
    m_menuEditInd->AppendSeparator();
    m_menuEditInd->Append( tfpID_EDIT_IND_NEW_MALE, _("Add New &Male...") );
    m_menuEditInd->Append( tfpID_EDIT_IND_NEW_FEMALE, _("Add New &Female...") );

    m_menuEditEvent = new wxMenu;
    m_menuEditEvent->Append( tfpID_EDIT_EVENT_CURRENT, _("None") );
    m_menuEditEvent->Append( tfpID_EDIT_EVENT_SELECT, _("&Select Event") );
    m_menuEditEvent->Append( tfpID_EDIT_EVENT_NEW_CON, _("&New Conclusion Event") );

    m_menuEditReference = new wxMenu;
    m_menuEditReference->Append( tfpID_EDIT_REFERENCE, _("&Reference...") );
    m_menuEditReference->Append( tfpID_EDIT_NEW_REFERENCE, _("&New Reference") );

    wxMenu* menuEdCore = new wxMenu;
    menuEdCore->Append( tfpID_EDIT_EVENT_TYPE, _("&Event Types...") );

    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append( tfpID_EDIT_IND_MENU, _("&Individual"), m_menuEditInd );
    menuEdit->Append( tfpID_EDIT_EVENT_MENU, _("&Event"), m_menuEditEvent );
    menuEdit->Append( tfpID_EDIT_REFERENCE_MENU, _("&Reference"), m_menuEditReference );
    menuEdit->Append( tfpID_EDIT_RESEARCHER, _("R&esearcher...") );
    menuEdit->Append( tfpID_EDIT_CORE_MENU, _("&Core Data"), menuEdCore );

    wxMenu* menuFind = new wxMenu;
    menuFind->Append( tfpID_FIND_FAMILY_ID, _("&Family ID...") );
    menuFind->Append( tfpID_FIND_INDIVIDUAL_ID, _("&Individual ID...") );
    menuFind->Append( tfpID_FIND_EVENT_ID, _("&Event ID...") );

    wxMenu* menuListRef = new wxMenu;
    menuListRef->Append( tfpID_LIST_ALL_REFERENCES, _("&All References\tAlt-R") );
    menuListRef->Append( tfpID_LIST_PAGED_REFERENCES, _("&Paged References") );

    wxMenu* menuListEvent = new wxMenu;
    menuListEvent->Append( tfpID_LIST_ALL_EVENTS, _("&All Events\tAlt-E") );
    menuListEvent->Append( tfpID_LIST_PAGED_EVENTS, _("&Paged Events") );
    menuListEvent->Append( tfpID_LIST_SELECTED_EVENTS, _("&Selected Events...") );
    menuListEvent->AppendSeparator();
    menuListEvent->Append( tfpID_LIST_ALL_EVENTUMS, _("All Even&tas") );
    menuListEvent->Append( tfpID_LIST_PAGED_EVENTUMS, _("Pa&ged Eventas") );
    menuListEvent->Append( tfpID_LIST_SELECTED_EVENTUMS, _("Se&lected Eventas...") );

    wxMenu* menuList = new wxMenu;
    menuList->Append( tfpID_LIST_SURNAME_INDEX, _("&Surname Index\tAlt-S") );
    menuList->Append( tfpID_LIST_PERSONAS, _("Person&a Index\tAlt-A") );
    menuList->Append( tfpID_LIST_INDIVIDUALS, _( "&Individuals\tAlt-I" ) );
    menuList->Append( tfpID_LIST_GALLERIES, _( "&Galleries\tAlt-G" ) );
    menuList->Append( tfpID_LIST_REFERENCE_MENU, _("&References"), menuListRef );
    menuList->Append( tfpID_LIST_EVENT_MENU, _("&Events"), menuListEvent );
    menuList->Append( tfpID_LIST_RESEARCHERS, _("Resear&chers\tAlt-C") );

    wxMenu* menuChart = new wxMenu;
    menuChart->Append( tfpID_PED_CHART, _("&Pedigree...") );
    menuChart->Append( tfpID_DESC_CHART, _("&Descendant...") );

    wxMenu* menuTools = new wxMenu;
    menuTools->Append( tfpID_SYSTEM_SETTING, _("&System Options...") );
    menuTools->Append( tfpID_USER_SETTING, _("&User Options...") );
    menuTools->Append( tfpID_TOOL_SYSTEM_CHECK, _("Systems &Check") );

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
    m_toolbar = CreateToolBar();
    m_showpage = new wxTextCtrl( m_toolbar, tfpID_SHOW_PAGE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
    wxBitmap bmpForward( forward_xpm );
    wxBitmap bmpBack( back_xpm );
    wxBitmap bmpFind( find_xpm );
    wxBitmap bmpEvents( event_xpm );
    wxBitmap bmpRefs( ref_xpm );
    wxBitmap bmpGalleries( gallery_xpm );
    wxBitmap bmpHome( home_xpm );
    m_toolbar->AddTool( tfpID_FIND_BACK, _("Back"), bmpBack );
    m_toolbar->AddTool( tfpID_FIND_FORWARD, _("Forward"), bmpForward );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_LIST_SURNAME_INDEX, _("Index"), bmpFind );
    m_toolbar->AddTool( tfpID_LIST_PAGED_EVENTS, _("Events"), bmpEvents );
    m_toolbar->AddTool( tfpID_LIST_PAGED_REFERENCES, _( "References" ), bmpRefs );
    m_toolbar->AddTool( tfpID_LIST_GALLERIES, _( "Galleries" ), bmpGalleries );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_GOTO_HOME, _("Home"), bmpHome );
    m_toolbar->AddSeparator();
    m_toolbar->AddControl( m_showpage );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_PAGE_ITEM_EDIT, _("Edit"), *imgEditBitmap );
    m_toolbar->Realize();
    SetToolBar( m_toolbar );

    m_statusbar = CreateStatusBar();

    m_webPageAllow = false;
    m_browser = wxWebView::New( this, tfpID_BROWSER );
    m_browser->RegisterHandler( GetWebViewMemoryHandler() );
    m_browser->EnableHistory( false ); // We handle our own history.

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
    TfpFrame* frame = new TfpFrame(
        "The Family Pack", wxDefaultPosition, wxSize( 900, 700 )
    );
    frame->Show(true);
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
    m_changeState = recDb::GetChange();
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

/*! \brief Called on a Export GEDCOM menu option event.
 */
void TfpFrame::OnExportGedcom( wxCommandEvent& event )
{
    wxString caption = _("Save GEDCOM As");
    wxString wildcard = "GEDCOM (*.ged)|*.ged";
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        if( tfpExportGedcom( path ) )
        {
            wxMessageBox( _("GEDCOM Saved OK"), _("Export") );
        } else {
            wxMessageBox( _("Error Reading GEDCOM File"), _("Export") );
        }
    }
}

/*! \brief Called on a Export Html menu option event.
 */
void TfpFrame::OnExportHtml( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnExportHtml" );
}

/*! \brief Called on a Print menu option event.
 */
void TfpFrame::OnPrint( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnPrint" );
}

/*! \brief Called on a Print Preview menu option event.
 */
void TfpFrame::OnPreview( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnPreview" );
}

/*! \brief Called on a  Page Setup menu option event.
 */
void TfpFrame::OnPageSetup( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet implimented"), "OnPageSetup" );
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
    wxMessageBox( _("Not yet implimented"), "OnEditIndividual" );
}

/*! \brief Called on a Add New Male Individual menu option event.
 */
void TfpFrame::OnAddNewIndMale( wxCommandEvent& event )
{
    idt id = 0;
    recDb::Begin();
    try {
        id = rgAddNewIndividual( this, SEX_Male );
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
        id = rgAddNewIndividual( this, SEX_Female );
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
    wxString disp = GetDisplay();
    bool ret = false;
    idt id;
    unsigned rettype = 0;

    recDb::Begin();
    try {
        switch( event.GetId() )
        {
        case tfpID_EDIT_INDIVIDUAL_LEFT:
            ret = rgEditIndividual( this, m_EditIndLeft );
            break;
        case tfpID_EDIT_NEW_MOTHER_LEFT:
            ret = rgAddNewParent( this, m_EditIndLeft, SEX_Female );
            break;
        case tfpID_EDIT_NEW_FATHER_LEFT:
            ret = rgAddNewParent( this, m_EditIndLeft, SEX_Male );
            break;
        case tfpID_EDIT_NEW_SPOUSE_LEFT:
            id = rgAddNewIndividual( this, SEX_Female, 0, "", m_EditFamily );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_MOTHER_LEFT:
            ret = rgAddExistParent( this, m_EditIndLeft, SEX_Female );
            break;
        case tfpID_EDIT_EXIST_FATHER_LEFT:
            ret = rgAddExistParent( this, m_EditIndLeft, SEX_Male );
            break;
        case tfpID_EDIT_EXIST_SPOUSE_LEFT:
            ret = rgAddExistSpouse( this, m_EditIndLeft, SEX_Female );
            break;
        case tfpID_EDIT_DELETE_IND_LEFT:
            ret = rgDeleteIndividual( this, m_EditIndLeft );
            break;
        case tfpID_EDIT_INDIVIDUAL_RIGHT:
            ret = rgEditIndividual( this, m_EditIndRight );
            break;
        case tfpID_EDIT_NEW_MOTHER_RIGHT:
            ret = rgAddNewParent( this, m_EditIndRight, SEX_Female );
            break;
        case tfpID_EDIT_NEW_FATHER_RIGHT:
            ret = rgAddNewParent( this, m_EditIndRight, SEX_Male );
            break;
        case tfpID_EDIT_NEW_SPOUSE_RIGHT:
            id = rgAddNewIndividual( this, SEX_Male, 0, "", m_EditFamily );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_MOTHER_RIGHT:
            ret = rgAddExistParent( this, m_EditIndRight, SEX_Female );
            break;
        case tfpID_EDIT_EXIST_FATHER_RIGHT:
            ret = rgAddExistParent( this, m_EditIndRight, SEX_Male );
            break;
        case tfpID_EDIT_EXIST_SPOUSE_RIGHT:
            ret = rgAddExistSpouse( this, m_EditIndRight, SEX_Female );
            break;
        case tfpID_EDIT_DELETE_IND_RIGHT:
            ret = rgDeleteIndividual( this, m_EditIndRight );
            break;
        case tfpID_EDIT_FAMILY:
            ret = rgEditFamily( this, m_EditFamily );
            break;
        case tfpID_EDIT_NEW_SON:
            id = rgAddNewChild( this, m_EditFamily, SEX_Male );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_NEW_DAUR:
            id = rgAddNewChild( this, m_EditFamily, SEX_Female );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_SON:
            id = rgAddExistChild( this, m_EditFamily, SEX_Male );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_DAUR:
            id = rgAddExistChild( this, m_EditFamily, SEX_Female );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EVENT_CURRENT:
            ret = rgEditEvent( this, m_editEventID );
            break;
        case tfpID_EDIT_EVENT_SELECT:
            id = rgSelectEvent( this, rgSELSTYLE_None );
            if( id ) id = rgEditEvent( this, id );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EVENT_NEW_CON:
            id = rgSelectIndividual( this, rgSELSTYLE_None );
            if( id ) id = rgCreateIndEvent( this, id );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EVENT_TYPE:
            id = rgSelectEventType( this, rgSELSTYLE_Create, &rettype );
            if( id ) ret = true;
            if( id && rettype == rgSELSTYLE_None ) ret = rgEditEventType( this, id );
            break;
        default:
            wxMessageBox( "Not yet implimented", "OnEditContext" );
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


/*! \brief Called on a Edit New Reference menu option event.
 */
void TfpFrame::OnEditNewReference( wxCommandEvent& event )
{
    recDb::Begin();
    try {
        if( rgCreateReference( this ) == 0 ) {
            recDb::Rollback();
        } else {
            recDb::Commit();
            RefreshHtmPage();
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
        _("Enter the Reference ID number"),

        _("Reference ID:"),
        _("Edit Reference"),
        (long) 0, (long) 0, (long) INT_MAX, this
    );
    if( num <= 0 ) return;

    recDb::Begin();
    try {
        if( rgEditReference( this, (idt) num ) ) {
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

/*! \brief Called on a Edit Researcher menu option event.
 */
void TfpFrame::OnEditResearcher( wxCommandEvent& event )
{
    long num = wxGetNumberFromUser(
        wxT("Enter the Researcher ID or 0 for new Researcher"),

        wxT("Researcher ID:"),
        wxT("Edit Researcher"),
        (long) 0, (long) 0, (long) INT_MAX
    );
    if( num < 0 ) return;

    recDb::Begin();
    try {
        bool ret = false;
        if( num == 0 ) {
            idt resID = rgCreateResearcher( this );
            if( resID != 0 ) {
                ret = true;
            }
        } else {
            ret = rgEditResearcher( this, (idt) num );
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

/*! \brief Called on a Find Family ID menu option event.
 */
void TfpFrame::OnFindFamilyID( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnFindFamilyID" );
}

/*! \brief Called on a Find Individual ID menu option event.
 */
void TfpFrame::OnFindIndividualID( wxCommandEvent& event )
{
    wxMessageBox( wxT("Not yet implimented"), wxT("OnFindIndividualID") );
}

/*! \brief Called on a Find Individual ID menu option event.
 */
void TfpFrame::OnFindEventID( wxCommandEvent& event )
{
    idt eveID = rgSelectEvent( this );
    if( eveID ) {
        DisplayHtmPage( "E"+recGetStr( eveID ) );
    }
}

/*! \brief Called on a List Index menu option event.
 */
void TfpFrame::OnListIndex( wxCommandEvent& event )
{
    DisplayHtmPage( "NI" );
}

/*! \brief Called on a List Personas menu option event.
 */
void TfpFrame::OnListPersonas( wxCommandEvent& event )
{
    DisplayHtmPage( "NP" );
}

/*! \brief Called on a  List Individuals menu option event.
 */
void TfpFrame::OnListIndividuals( wxCommandEvent& event )
{
    DisplayHtmPage( "ND*" );
}

void TfpFrame::OnListGalleries( wxCommandEvent & event )
{
    DisplayHtmPage( "G" );
}

/*! \brief Called on a List References menu option event.
 */
void TfpFrame::OnListReferences( wxCommandEvent& event )
{
    DisplayHtmPage( "R" );
}

/*! \brief Called on a List/Paged Events menu option event.
 */
void TfpFrame::OnListPagedReferences( wxCommandEvent& event )
{
    DisplayHtmPage( "R,0" );
}

/*! \brief Called on a List/All Events menu option event.
 */
void TfpFrame::OnListAllEvents( wxCommandEvent& event )
{
    DisplayHtmPage( "E" );
}

/*! \brief Called on a List/Paged Events menu option event.
 */
void TfpFrame::OnListPagedEvents( wxCommandEvent& event )
{
    DisplayHtmPage( "E,0" );
}

/*! \brief Called on a List/Selected Events menu option event.
 */
void TfpFrame::OnListSelectedEvents( wxCommandEvent& event )
{
    if( rgSelectEventList( this, &m_selEvent ) ) {
        DisplayHtmPage( "E$" );
    }
}

/*! \brief Called on a List/All Eventas menu option event.
 */
void TfpFrame::OnListAllEventas( wxCommandEvent& event )
{
    DisplayHtmPage( "Ea" );
}

/*! \brief Called on a List/Paged Eventas menu option event.
 */
void TfpFrame::OnListPagedEventas( wxCommandEvent& event )
{
    DisplayHtmPage( "Ea,0" );
}

/*! \brief Called on a List/Selected Eventas menu option event.
 */
void TfpFrame::OnListSelectedEventas( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnListSelectedEventas" );
//    if( rgSelectIndEventaList( this, &m_emFilter ) ) {
//        DisplayHtmPage( "Ea$" );
//    }
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
    wxMessageBox( "Not yet implimented", "OnPedChart" );
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
        bool ret = rgEditSystemSettings( this );
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
        bool ret = rgEditUserSettings( this );
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

void TfpFrame::OnSystemCheck( wxCommandEvent& event )
{
    recDb::Begin();
    try {
        if( recDb::GlobalUpdate() ) {
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
            recDb::GetFileName(), recVersion::GetVersionStr()
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
    DisplayHtmPage( page );
}

/*! \brief Called when the toolbar Edit button is pressed.
 */
void TfpFrame::OnPageItemEdit( wxCommandEvent& event )
{
    wxString display = GetDisplay();
    if( display == "E$" ) {
        DoSelectionUpdate( display );
        return;
    }
    idt id;
    wxUniChar uch = display.GetChar( 0 );
    wxUniChar uch1 = display.size() > 1 ? display.GetChar( 1 ) : (wxUniChar) '\0';
    if( display.StartsWith( "FI" ) ) {
        idt indID = recGetID( display.Mid(2) );
        id = recIndividual::GetFamilyID( indID );
    } else if( display.StartsWith( "E^" ) || display.StartsWith( "Ea" ) ) {
        id = recGetID( display.Mid(2) );
    } else {
        id = recGetID( display.Mid(1) );
    }
    recDb::Begin();
    try {
        bool ret = false;
        switch( uch.GetValue() )
        {
        case 'F':
            ret = rgEditFamily( this, id );
            break;
        case 'R':
            ret = rgEditReference( this, id );
            break;
        case 'E':
            if( uch1.GetValue() == 'a' ) {
                ret = rgEditEventa( this, id );
            } else {
                ret = rgEditEvent( this, id );
            }
            break;
        case 'I':
            ret = rgEditIndividual( this, id );
            break;
        case 'P':
            if( uch1.GetValue() == 'a' ) {
                ret = rgEditPersona( this, recGetID( display.Mid(2) ) );
            }
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
    if( url.StartsWith( "mailto:" ) ) return;
    // We will handle all other navigation ourselves.
    evt.Veto();

    if( url.StartsWith( "null:" ) ) {
        // do nothing
        return;
    }
    if( url.StartsWith( "tfp:" ) ) {
        DisplayHtmPage( url.Mid( 4 ) );
        return;
    }
    if( url.StartsWith( "tfpe:" ) ) {
        DoEdit( url.Mid( 5 ) );
        return;
    }
    if ( url.StartsWith( "tfpi:" ) ) {
        DoPopupNote( url.Mid( 5 ) );
        return;
    }
    if ( url.StartsWith( "tfpv:" ) ) {
        DoPopupViewer( url.Mid( 5 ) );
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
    idt id = recGetID( m_ctxmenuref.substr( 1 ) );
    idt id2 = 0;
    size_t pos = m_ctxmenuref.find( '+' );
    if ( pos != wxString::npos ) {
        id2 = recGetID( m_ctxmenuref.substr( pos + 1 ) );
    }
    Sex sex = ( m_ctxmenuref.substr( 0, 1 ) == "H" ) ? SEX_Female : SEX_Male;

    recDb::Begin();
    try {
        switch( event.GetId() )
        {
        case tfpID_HCTXMENU_EDIT_FAMILY:
            ret = rgEditFamily( this, id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SON:
            if( rgAddNewChild( this, id, SEX_Male ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_NEW_DAUR:
            if( rgAddNewChild( this, id, SEX_Female ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SON:
            id = rgAddExistChild( this, id, SEX_Male );
            if( id ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_DAUR:
            id = rgAddExistChild( this, id, SEX_Female );
            if( id ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_INDIVIDUAL:
            ret = rgEditIndividual( this, id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_MOTHER:
            ret = rgAddNewParent( this, id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_FATHER:
            ret = rgAddNewParent( this, id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SPOUSE:
            ret = rgAddNewSpouse( this, id, sex, id2 );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_MOTHER:
            ret = rgAddExistParent( this, id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_FATHER:
            ret = rgAddExistParent( this, id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SPOUSE:
            ret = rgAddExistSpouse( this, id, sex );
            break;
        case tfpID_HCTXMENU_EDIT_DELETE_IND:
            ret = rgDeleteIndividual( this, id );
            break;
        case tfpID_HCTXMENU_EDIT_REFERENCE:
            ret = rgEditReference( this, id );
            break;
        case tfpID_HCTXMENU_EDIT_EVENT:
            ret = rgEditEvent( this, id );
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

void TfpFrame::OnIdle( wxIdleEvent& event )
{
    if( m_changeState != recDb::GetChange() ) {
        if( recDb::IsOpen() ) {
            RefreshHtmPage();
        } else {
            Close( true );
        }
    }
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
    if( dialog.ShowModal() == wxID_OK ) {
        wxString path = dialog.GetPath();
        if( recDb::OpenDb( path ) == true ) {
            SetDatabaseOpen( path );
            DisplayHomePage();
            ret = true;
        } else {
            // No change if fail.
            m_changeState = recDb::GetChange();
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
    idt id;

    recDb::Begin();
    try {
        if( href.StartsWith( "cEER" ) ) {
            idt eID, erID;
            recGetIDs( href.Mid(4), &eID, &erID );
            id = rgCreateIndEventEventa( this, eID, erID );
            if( id ) ret = true;
        } else if( href.StartsWith( "cE" ) ) {
            id = rgCreateEventFromRecord( this, recGetID( href.Mid(2) ) );
            if( id ) ret = true;
        } else if( href.StartsWith( "Em" ) ) {
            idt indID1, indID2;
            recGetIDs( href.substr(2), &indID1, &indID2 );
            id = rgCreateDefaultIndEvent( this, indID1, indID2, recET_GRP_FamUnion );
            if( id ) ret = true;
        } else if( href.StartsWith( "Eb" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(2) ), 0, recET_GRP_Birth );
            if( id ) ret = true;
        } else if( href.StartsWith( "Enb" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(3) ), 0, recET_GRP_NrBirth );
            if( id ) ret = true;
        } else if( href.StartsWith( "Ed" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(2) ), 0, recET_GRP_Death );
            if( id ) ret = true;
        } else if( href.StartsWith( "End" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(3) ), 0, recET_GRP_NrDeath );
            if( id ) ret = true;
        } else if( href.StartsWith( "Eo" ) ) {
            id = rgCreatePersonalEvent( this, recGetID( href.Mid(2) ), recEventType::ET_Occupation );
            if( id ) ret = true;
        } else if( href.StartsWith( "IL" ) ) {
            id = rgAddNewIndividual( this, SEX_Male, -1, "", recGetID( href.Mid(2) ) );
            if( id ) ret = true;
        } else if( href.StartsWith( "IR" ) ) {
            id = rgAddNewIndividual( this, SEX_Female, -1, "", recGetID( href.Mid(2) ) );
            if( id ) ret = true;
        } else if( href.StartsWith( "IF" ) ) {
            ret = rgAddNewParent( this, recGetID( href.Mid(2) ), SEX_Female );
        } else if( href.StartsWith( "IM" ) ) {
            ret = rgAddNewParent( this, recGetID( href.Mid(2) ), SEX_Male );
        } else if( href.StartsWith( "I" ) ) {
            ret = rgEditIndividual( this, recGetID( href.Mid(1) ) );
        } else if( href.StartsWith( "Re" ) ) {
            ret = rgEditResearcher( this, recGetID( href.Mid(2) ) );
        } else if( href.StartsWith( "R" ) ) {
            ret = rgEditReference( this, recGetID( href.Mid(1) ) );
        } else if( href.StartsWith( "C" ) ) {
            ret = rgEditContact( this, recGetID( href.Mid(1) ) );
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

void TfpFrame::DoSelectionUpdate( const wxString& display )
{
    try {
        bool ret = false;
        if( display == "E$" ) {
            ret = rgSelectEventList( this, &m_selEvent );
        }
        if( ret == true ) {
            RefreshHtmPage();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
    }
}

void TfpFrame::DoPopupNote( const wxString& ref )
{
    dlgNote* note = new dlgNote( this, ref );
    note->Show();
}

void TfpFrame::DoPopupViewer( const wxString & href )
{
    if ( href.StartsWith( "M" ) ) {
        idt medID = recGetID( href.substr( 1 ) );
        if ( medID ) {
            rgViewMedia( this, medID );
            return;
        }
    }
    wxMessageBox(
        wxString::Format( _( "Unable to view [%s]" ), href ),
        _( "Unknown Media" )
        );
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
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_DELETE_IND, _("Delete Individual") );
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
            parmenu->Append( cmd_ID + c, recIndividual::GetName( families[i].f_husb_id ) );
        }
        if( families[i].f_wife_id != 0 ) {
            parmenu->Append( cmd_ID + c, recIndividual::GetName( families[i].f_wife_id ) );
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
            sibmenu->Append( cmd_ID + c, inds[j].FGetName() );
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
            marmenu->Append( cmd_ID + c, recIndividual::GetName( families[i].f_husb_id ) );
            m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
            c++;
        }
        if( families[i].f_wife_id != 0 && families[i].f_wife_id != indID ) {
            marmenu->Append( cmd_ID + c, recIndividual::GetName( families[i].f_wife_id ) );
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
            kidmenu->Append( cmd_ID + c, inds[j].FGetName() );
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
    m_titleFmt = wxString::Format( "TFP: %s, %%s", dbfile.GetName() );
    SetMenuBar( m_menuOpenDB );
    m_toolbar->EnableTool( tfpID_LIST_SURNAME_INDEX, true );
    m_toolbar->EnableTool( tfpID_LIST_PAGED_EVENTS, true );
    m_toolbar->EnableTool( tfpID_LIST_PAGED_REFERENCES, true );
    m_toolbar->EnableTool( tfpID_LIST_GALLERIES, true );
    m_toolbar->EnableTool( tfpID_GOTO_HOME, true );
    m_showpage->Enable( true );
}

void TfpFrame::SetNoDatabase()
{
    SetTitle( "The Family Pack" );
    SetMenuBar( m_menuClosedDB );
    m_toolbar->EnableTool( tfpID_LIST_SURNAME_INDEX, false );
    m_toolbar->EnableTool( tfpID_LIST_PAGED_EVENTS, false );
    m_toolbar->EnableTool( tfpID_LIST_PAGED_REFERENCES, false );
    m_toolbar->EnableTool( tfpID_LIST_GALLERIES, false );
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
    m_menuEditInd->Enable( tfpID_EDIT_FAMILY_MENU, false );
    m_menuEditEvent->SetLabel( tfpID_EDIT_EVENT_CURRENT, noname );
    m_menuEditEvent->Enable( tfpID_EDIT_EVENT_CURRENT, false );
    m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, false );

    switch( uch.GetValue() )
    {
    case 'F': {
            recFamily fam(0);
            fam.Decode( disp );
            if( fam.FGetID() ) {
                m_EditFamily = fam.FGetID();
                if( fam.f_husb_id ) {
                    name = recIndividual::GetName( fam.f_husb_id );
                    m_menuEditInd->SetLabel( tfpID_EDIT_IND_LEFT, name );
                    m_menuEditInd->Enable( tfpID_EDIT_IND_LEFT, true );
                } else {
                    m_menuEditInd->SetLabel( tfpID_EDIT_IND_LEFT, noname );
                    m_menuEditInd->Enable( tfpID_EDIT_IND_LEFT, false );
                }
                m_EditIndLeft = fam.f_husb_id;
                if( fam.f_wife_id ) {
                    name = recIndividual::GetName( fam.f_wife_id );
                    m_menuEditInd->SetLabel( tfpID_EDIT_IND_RIGHT, name );
                    m_menuEditInd->Enable( tfpID_EDIT_IND_RIGHT, true );
                } else {
                    m_menuEditInd->SetLabel( tfpID_EDIT_IND_RIGHT, noname );
                    m_menuEditInd->Enable( tfpID_EDIT_IND_RIGHT, false );
                }
                m_EditIndRight = fam.f_wife_id;
                m_menuEditInd->Enable( tfpID_EDIT_FAMILY_MENU, true );
                m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
            } else {
                m_menuEditInd->Enable( tfpID_EDIT_FAMILY_MENU, false );
                m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, false );
            }
        }
        break;
    case 'I':
        if( disp.size() >= 2 && wxIsdigit( disp.GetChar( 1 ) ) ) {
            idt indID = recGetID( disp.Mid( 1 ) );
            name = recIndividual::GetName( indID );
            if( name.size() > 50 ) {
                name = name.Mid( 0, 48 ) + "...";
            }
            m_menuEditInd->SetLabel( tfpID_EDIT_IND_LEFT, name );
            m_menuEditInd->Enable( tfpID_EDIT_IND_LEFT, true );
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'E':
        if( disp.size() >= 2 && wxIsdigit( disp.GetChar( 1 ) ) ) {
            m_editEventID = recGetID( disp.Mid( 1 ) );
            name = recEvent::GetTitle( m_editEventID );
            m_menuEditEvent->SetLabel( tfpID_EDIT_EVENT_CURRENT, name );
            m_menuEditEvent->Enable( tfpID_EDIT_EVENT_CURRENT, true );
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        } else if( disp.size() >= 3 && (
                ( disp.GetChar( 1 ) == 'a' && wxIsdigit( disp.GetChar( 2 ) ) ) ||
                ( disp.GetChar( 1 ) == '^' && wxIsdigit( disp.GetChar( 2 ) ) )
                ) ) {
            m_editEventID = recGetID( disp.Mid( 2 ) );
            name = recEventa::GetTitle( m_editEventID );
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'R':
        if( disp.size() >= 2 &&
            ( wxIsdigit( disp.GetChar( 1 ) ) || disp.GetChar( 1 ) == '$' )
        ) {
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'P':
        if( disp.size() >= 3 && disp.GetChar( 1 ) == 'a'
            && wxIsdigit( disp.GetChar( 2 ) ) 
        ) {
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    }
}

bool TfpFrame::DisplayHtmPage( const wxString& pagename )
{
    wxBusyCursor wait;
    wxString name( pagename );

    wxString text = GetDisplayText( name );
    if( !text.IsEmpty() ) {
        SetTitle( wxString::Format( m_titleFmt, name ) );
        PushHtmName( name );
        m_browser->SetPage( text, "" );
        RefreshEditMenu();
        m_changeState = recDb::GetChange();
        return true;
    }
    return false;
}

void TfpFrame::RefreshHtmPage()
{
    wxString name = GetCurrentName();
    SetTitle( wxString::Format( m_titleFmt, name ) );
    if( name.size() ) {
        m_browser->SetPage( GetDisplayText( name ), "" );
        RefreshEditMenu();
    }
    m_changeState = recDb::GetChange();
}

bool TfpFrame::DisplayHomePage()
{
    return DisplayHtmPage( recGetHomeDisplay() );
}

wxString TfpFrame::GetDisplayText( wxString& name )
{
    name.MakeUpper();
    // TODO: We need to do this in a try ... catch framework.
    wxASSERT( name.size() > 0 );
    wxLongLong_t num, num1 = 0, num2 = 0;
    bool success, success1 = false, success2 = false;

    success = name.Mid(1).ToLongLong( &num );
    if( name.size() > 1 ) {
        success1 = name.Mid(2).ToLongLong( &num1 );
    }
    if( name.size() > 2 ) {
        success2 = name.Mid(3).ToLongLong( &num2 );
    }

    if( name.compare( 0, 2, "CD" ) == 0 && success1 ) {
        return tfpCreateDescChart( num1 );
    }
    if( name.compare( 0, 2, "CP" ) == 0 && success1 ) {
        return tfpCreatePedChart( num1 );
    }
    if( name.compare( 0, 1, "D" ) == 0 && success ) {
        return tfpWriteDate( num );
    }
    if( name.compare( "E" ) == 0 ) {
        return tfpWriteEventIndex();
    }
    if( name.compare( "E$" ) == 0 ) {
        return tfpWriteEventSelection( m_selEvent );
    }
    if( name.compare( "EA" ) == 0 ) {
        name.MakeCapitalized();
        return tfpWriteEventaIndex();
    }
// We don't have a Eventa filter yet!
//    if( name.compare( "EA$" ) == 0 ) {
//        name.MakeCapitalized();
//        return tfpWriteEventaSelection( m_erFilter );
//    }
    if( name.compare( 0, 2, "EA" ) == 0 && success1 ) {
        name.MakeCapitalized();
        return tfpWriteEventaPage( num1 );
    }
    if( name.compare( 0, 3, "EA," ) == 0 && success2 ) {
        name.MakeCapitalized();
        return tfpWriteEventaPagedIndex( num2 );
    }
    if( name.compare( 0, 1, "E" ) == 0 && success ) {
        return tfpWriteEventPage( num, &m_compEvent );
    }
    if( name.compare( 0, 2, "E," ) == 0 && success1 ) {
        return tfpWriteEventPagedIndex( num1 );
    }
    if( name.compare( 0, 2, "FI" ) == 0 && success1 ) {
        return tfpWriteIndFamilyPage( num1 );
    }
    if( name.compare( 0, 1, "F" ) == 0 ) {
        // Note, Family Page may have alternate parents
        // so name string requires further decoding.
        return tfpWriteFamilyPage( name.Mid(1) );
    }
    if ( name.compare( "G" ) == 0 ) {
        return tfpWriteGalleryList();
    }
    if ( name.compare( 0, 1, "G" ) == 0 && success ) {
        return tfpWriteGalleryPage( num  );
    }
    if( name.compare( 0, 1, "I" ) == 0 && success ) {
        return tfpWriteIndividualPage( num );
    }
    if ( name.compare( "NI" ) == 0 ) {
        return tfpWriteSurnameIndex( recSG_Individual );
    }
    if ( name.compare( "NP" ) == 0 ) {
        return tfpWriteSurnameIndex( recSG_Persona );
    }
    if ( name.compare( "ND*" ) == 0 ) { 
        return tfpWriteIndividualList();
    }
    if ( name.compare( 0, 3, "NI+" ) == 0 && !success2 ) {
        return tfpWriteNameList( name.Mid( 3 ), recSG_Individual );
    }
    if ( name.compare( 0, 3, "NP+" ) == 0 && !success2 ) {
        return tfpWriteNameList( name.Mid( 3 ), recSG_Persona );
    }
    if( name.compare( 0, 1, "N" ) == 0 && success ) {
        return tfpWriteName( num );
    }
    if( name.compare( 0, 2, "PA" ) == 0 ) {
        name.MakeCapitalized();
        return tfpWritePersonaPage( num1 );
    }
    if( name.compare( 0, 1, "P" ) == 0 && success ) {
        return tfpWritePlace( num );
    }
    if( name.compare( "R" ) == 0 ) {
        return tfpWriteReferenceIndex();
    }
    if( name.compare( 0, 2, "R," ) == 0 && success1 ) {
        return tfpWriteReferencePagedIndex( num1 );
    }
    if( name.compare( 0, 1, "R" ) == 0 && success ) {
        return tfpWriteReferencePage( num );
    }
    if( name.compare( "RE" ) == 0 ) {
        name.MakeCapitalized();
        return tfpWriteResearcherList();
    }

    return wxString::Format(
        "<html><head><title>Error</title></head>"
        "<body><h1>Error</h1><p>Page [%s] not understood.</p></body></html>",
        name
    );
}

// End of tfpFrame.cpp file

