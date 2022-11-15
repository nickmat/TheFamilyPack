/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpFrame.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpFrame class source.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25 September 2010
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

#include <rec/recCitation.h>
#include <rec/recCsv.h>
#include <rec/recFamily.h>
#include <rec/recIndividual.h>
#include <rec/recVersion.h>

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
#include "img/transfer.xpm"

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "img/tfp.xpm"
#endif

BEGIN_EVENT_TABLE(TfpFrame, wxFrame)
    EVT_MENU_OPEN( TfpFrame::OnMenuOpen )
    EVT_MENU( tfpID_NEW_FILE, TfpFrame::OnNewFile )
    EVT_MENU( tfpID_OPEN_FILE, TfpFrame::OnOpenFile )
    EVT_MENU( tfpID_CLOSE_FILE, TfpFrame::OnCloseFile )
    EVT_MENU( tfpID_FILE_ATTACH_NEW_FULL, TfpFrame::OnAttachNewFile )
    EVT_MENU( tfpID_FILE_ATTACH_NEW_MEDIA, TfpFrame::OnAttachNewFile )
    EVT_MENU( tfpID_FILE_ATTACH_OPEN, TfpFrame::OnAttachOpenFile )
    EVT_MENU_RANGE( tfpID_FILE_ATTACH_CLOSE_0, tfpID_FILE_ATTACH_CLOSE_LAST, TfpFrame::OnAttachCloseFile )
    EVT_MENU( tfpID_FILE_EXTERNAL_OPEN, TfpFrame::OnExternalOpenFile )
    EVT_MENU_RANGE( tfpID_FILE_EXTERNAL_CLOSE_0, tfpID_FILE_EXTERNAL_CLOSE_LAST, TfpFrame::OnExternalCloseFile )
    EVT_MENU( tfpID_IMPORT_GEDCOM, TfpFrame::OnImportGedcom )
    EVT_MENU( tfpID_IMPORT_CSV_BACKUP, TfpFrame::OnImportCsv )
    EVT_MENU( tfpID_EXPORT_GEDCOM, TfpFrame::OnExportGedcom )
    EVT_MENU( tfpID_EXPORT_HTML, TfpFrame::OnExportHtml )
    EVT_MENU( tfpID_EXPORT_CSV_BACKUP, TfpFrame::OnExportCsv )
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
    EVT_MENU( tfpID_EDIT_REF_TEMPLATE, TfpFrame::OnEditRefTemplate )
    EVT_MENU( tfpID_EDIT_REFERENCE, TfpFrame::OnEditReference )
    EVT_MENU( tfpID_EDIT_GALLERY, TfpFrame::OnEditGallery )
    EVT_MENU( tfpID_EDIT_RESEARCHER, TfpFrame::OnEditResearcher )
    EVT_MENU( tfpID_EDIT_REPOSITORY, TfpFrame::OnEditRepository )
    EVT_MENU( tfpID_EDIT_ASSOCIATE, TfpFrame::OnEditAssociate )
    EVT_MENU( tfpID_FIND_FAMILY_ID, TfpFrame::OnFindFamilyID )
    EVT_MENU( tfpID_FIND_INDIVIDUAL_ID, TfpFrame::OnFindIndividualID )
    EVT_MENU( tfpID_FIND_EVENT_ID, TfpFrame::OnFindEventID )
    EVT_MENU( tfpID_LIST_SURNAME_INDEX, TfpFrame::OnListIndex )
    EVT_MENU( tfpID_LIST_PERSONAS, TfpFrame::OnListPersonas )
    EVT_MENU( tfpID_LIST_INDIVIDUALS, TfpFrame::OnListIndividuals )
    EVT_MENU( tfpID_LIST_GALLERIES, TfpFrame::OnListGalleries )
    EVT_MENU( tfpID_LIST_MEDIA_LIST, TfpFrame::OnListMediaList )
    EVT_MENU( tfpID_LIST_MEDIA_PAGED_LIST, TfpFrame::OnListMediaPagedList )
    EVT_MENU( tfpID_LIST_MEDIADATA_LIST, TfpFrame::OnListMediaDataList )
    EVT_MENU( tfpID_LIST_ALL_REFERENCES, TfpFrame::OnListReferences )
    EVT_MENU( tfpID_LIST_PAGED_REFERENCES, TfpFrame::OnListPagedReferences )
    EVT_MENU( tfpID_LIST_ALL_EVENTS, TfpFrame::OnListAllEvents )
    EVT_MENU( tfpID_LIST_PAGED_EVENTS, TfpFrame::OnListPagedEvents )
    EVT_MENU( tfpID_LIST_SELECTED_EVENTS, TfpFrame::OnListSelectedEvents )
    EVT_MENU( tfpID_LIST_ALL_EVENTUMS, TfpFrame::OnListAllEventas )
    EVT_MENU( tfpID_LIST_PAGED_EVENTUMS, TfpFrame::OnListPagedEventas )
    EVT_MENU( tfpID_LIST_SELECTED_EVENTUMS, TfpFrame::OnListSelectedEventas )
    EVT_MENU( tfpID_LIST_RESEARCHERS, TfpFrame::OnListResearchers )
    EVT_MENU( tfpID_LIST_REPOSITORIES, TfpFrame::OnListRepositories )
    EVT_MENU( tfpID_PED_CHART, TfpFrame::OnPedChart )
    EVT_MENU( tfpID_DESC_CHART, TfpFrame::OnDescChart )
    EVT_MENU( tfpID_SYSTEM_SETTING, TfpFrame::OnSystemOptions )
    EVT_MENU( tfpID_USER_SETTING, TfpFrame::OnUserOptions )
    EVT_MENU( tfpID_TOOLS_COMPACT, TfpFrame::OnToolsCompact )
    EVT_MENU( tfpID_TOOL_SYSTEM_CHECK, TfpFrame::OnSystemCheck )
    EVT_MENU( tfpID_WINDOW_NEW, TfpFrame::OnWindowNew )
    EVT_MENU( tfpID_WINDOW_CLOSE, TfpFrame::OnWindowClose )
    EVT_MENU_RANGE( tfpID_WINDOW_01, tfpID_WINDOW_10, TfpFrame::OnSelectWindow )
    EVT_MENU( tfpID_WINDOW_WINDOWS, TfpFrame::OnWindowWindows )
    EVT_MENU( tfpID_HELP_WEB_HOME, TfpFrame::OnHelpWebHome )
    EVT_MENU( tfpID_HELP_ABOUT_DB, TfpFrame::OnAboutDatabase )
    EVT_MENU( wxID_ABOUT, TfpFrame::OnAbout )
    EVT_MENU( tfpID_FIND_BACK, TfpFrame::OnFindBack )
    EVT_MENU( tfpID_FIND_FORWARD, TfpFrame::OnFindForward )
    EVT_MENU( tfpID_GOTO_HOME, TfpFrame::OnHome )
    EVT_TEXT_ENTER( tfpID_SHOW_PAGE, TfpFrame::OnShowPage )
    EVT_MENU( tfpID_PAGE_ITEM_EDIT, TfpFrame::OnPageItemEdit )
    EVT_MENU( tfpID_PAGE_ITEM_TRANSFER, TfpFrame::OnPageItemTransfer )
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
TfpFrame::TfpFrame(
    TfpApp* app,
    const wxPoint& pos,
    const wxSize& size,
    const wxString& dbfilename,
    const wxString& dbname )
    : m_tfpApp(app), m_selEvent(dbname),
    wxFrame( (wxFrame*) nullptr, wxID_ANY, "TFP", pos, size )
{
    app->AddFrame( this );
    m_dbname = dbname;
    m_changeState = recDb::GetChange();
    // Set frames Icon
    SetIcon( wxICON( tfp ) );

    CreateFullMenuRW();
    CreateMediaMenu();
    CreateClosedMenu();
    CreateFullToolbar();
    m_statusbar = CreateStatusBar();

    m_webPageAllow = false;
    m_browser = wxWebView::New( this, tfpID_BROWSER );
    m_browser->RegisterHandler( GetWebViewMemoryHandler() );
    m_browser->EnableHistory( false ); // We handle our own history.

    SetNoDatabase();
    if( !dbfilename.empty() ) {
        OpenFilename( dbfilename );
    }
    else if( recDb::IsOpen() ) {
        wxString fname = recDb::GetFileName();
        recDb::DbType type = recDb::GetDatabaseType( dbname );
        SetDatabaseMenu( fname, type );
    }
}

/*! \brief Frame destructor.
 */
TfpFrame::~TfpFrame()
{
    for( size_t i = m_menuWindowItemSize; i < 10; i++ ) {
        wxDELETE( m_menuWindowItem[i] );
    }
    if( GetMenuBar() != m_menuOpenDB ) {
        wxDELETE( m_menuOpenDB );
    }
    if( GetMenuBar() != m_menuMediaDB ) {
        wxDELETE( m_menuMediaDB );
    }
    if( GetMenuBar() != m_menuClosedDB ) {
        wxDELETE( m_menuClosedDB );
    }
    m_tfpApp->CloseFrame( this );
}

void TfpFrame::OnMenuOpen( wxMenuEvent& event )
{
    wxMenu* menu = event.GetMenu();
    if( menu == m_menuWindow ) {
        UpdateWindowMenu();
    }
    else if( menu == m_menuFileAssociate ) {
        UpdateFileAssociateMenu();
    }
    else if( menu == m_menuFileExternal ) {
        UpdateFileExternalMenu();
    }
    event.Skip();
}

void TfpFrame::UpdateWindowMenu()
{
    for( size_t i = 0; i < m_menuWindowItemSize; i++ ) {
        m_menuWindow->Remove( m_menuWindowItem[i] );
    }
    wxMenuItem* windows = m_menuWindow->Remove( tfpID_WINDOW_WINDOWS );
    
    m_menuWindowItemSize = m_tfpApp->GetFramesSize();
    if( m_menuWindowItemSize > 10 ) {
        m_menuWindowItemSize = 10;
    }
    wxString title;
    for( size_t i = 0; i < m_menuWindowItemSize; i++ ) {
        title.clear();
        if( i < 9 ) {
            title << "&" << (i + 1) << " ";
        }
        else {
            title << "1&0 ";
        }
        TfpFrame* frame = m_tfpApp->GetTfpFrame( i );
        title << frame->GetTitle();
        m_menuWindowItem[i]->SetItemLabel( title );
        m_menuWindow->Append( m_menuWindowItem[i] );
        m_menuWindowItem[i]->Check( frame == this );
    }
    m_menuWindow->Append( windows );
}

void TfpFrame::UpdateFileAssociateMenu()
{
    StringVec asslist = recDb::GetAssociatedDbList( m_dbname );
    if( asslist.empty() ) {
        m_menuFileAssociate->Enable( tfpID_FILE_ATTACH_CLOSE, false );
    }
    else {
        m_menuFileAssociate->Enable( tfpID_FILE_ATTACH_CLOSE, true );
        for( size_t i = 0; i < 10; i++ ) {
            int id = tfpID_FILE_ATTACH_CLOSE_0 + i;
            wxMenuItem* item = m_menuFileAssociateClose->FindItem( id );
            if( i >= asslist.size() ) {
                if( item ) {
                    m_menuFileAssociateClose->Delete( item );
                    continue;
                }
                break;
            }
            if( item ) {
                m_menuFileAssociateClose->SetLabel( id, asslist[i] );
            }
            else {
                m_menuFileAssociateClose->Append( id, asslist[i] );
            }
        }
    }
}

void TfpFrame::UpdateFileExternalMenu()
{
    StringVec extlist = recDb::GetExternalDbList();
    if( extlist.empty() ) {
        m_menuFileExternal->Enable( tfpID_FILE_EXTERNAL_CLOSE, false );
    }
    else {
        m_menuFileExternal->Enable( tfpID_FILE_EXTERNAL_CLOSE, true );
        for( size_t i = 0; i < 10; i++ ) {
            int id = tfpID_FILE_EXTERNAL_CLOSE_0 + i;
            wxMenuItem* item = m_menuFileExternalClose->FindItem( id );
            if( i >= extlist.size() ) {
                if( item ) {
                    m_menuFileExternalClose->Delete( item );
                    continue;
                }
                break;
            }
            if( item ) {
                m_menuFileExternalClose->SetLabel( id, extlist[i] );
            }
            else {
                m_menuFileExternalClose->Append( id, extlist[i] );
            }
        }
    }
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
    CloseFile();
    SetNoDatabase();
}

void TfpFrame::OnAttachNewFile( wxCommandEvent& event )
{
    if ( event.GetId() == tfpID_FILE_ATTACH_NEW_FULL ) {
        wxMessageBox( "Create new full file nyd", "OnAttachNewFile" );
        return;
    }
    wxASSERT( event.GetId() == tfpID_FILE_ATTACH_NEW_MEDIA );

    wxString caption = _( "Create TFP Database" );
    wxTextEntryDialog namedlg( this, "Database name", caption );
    if ( namedlg.ShowModal() != wxID_OK ) {
        return;
    }
    wxString dbname = namedlg.GetValue();

    wxFileName fname( recDb::GetFileName() );
    wxString defaultDir( fname.GetPath() );
    wxDirDialog dirdlg( this, caption, defaultDir );
    if ( dirdlg.ShowModal() != wxID_OK ) {
        return;
    }
    wxString path = dirdlg.GetPath();

    wxFileName dbfilename;
    dbfilename.SetPath( path );
    dbfilename.SetName( dbname );
    dbfilename.SetExt( "tfpd" );
    wxString dbpath = dbfilename.GetFullPath();

    recDb::CreateReturn ret = recDb::CreateDbFile( dbpath, recDb::DbType::media_data_only );
    wxString mess;
    switch ( ret )
    {
    case recDb::CreateReturn::OK:
        recDb::OpenAssociateDb( m_dbname, dbpath, dbname );
        return;
    case recDb::CreateReturn::FileExists:
        mess = wxString::Format("Database aready exists.\n%s", dbpath );
        break;
    default:
        mess = wxString::Format( "Create Database Error No %d", ret );
        break;
    }
    wxMessageBox( mess, "Attach Error" );
}

void TfpFrame::OnAttachOpenFile( wxCommandEvent& event )
{
    wxString caption = _( "Select TFP Database to Attach" );
    wxString wildcard = _( "TFP Database (*.tfpd)|*.tfpd" );
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if ( dialog.ShowModal() == wxID_OK ) {
        wxString path = dialog.GetPath();
        wxFileName fname( path );
        wxString dbname = fname.GetName();
        if ( recDb::OpenAssociateDb( m_dbname, path, dbname ).empty() ) {
            wxMessageBox( wxString::Format( "Unable to attach database\n%s", path), "Attach Error" );
        }
        m_changeState = recDb::GetChange();
    }
}

void TfpFrame::OnAttachCloseFile( wxCommandEvent& event )
{
    wxString assdb = m_menuFileAssociateClose->GetLabelText( event.GetId() );
    recDb::CloseAssociateDb( m_dbname, assdb );
}

void TfpFrame::OnExternalOpenFile( wxCommandEvent& event )
{
    wxString caption = _( "Select External TFP Database to Attach" );
    wxString wildcard = _( "TFP Database (*.tfpd)|*.tfpd" );
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK ) {
        wxString path = dialog.GetPath();
        wxFileName fname( path );
        wxString dbname = fname.GetName();
        if( !recDb::OpenExternalDb( path, dbname ) ) {
            wxMessageBox( wxString::Format( "Unable to attach database\n%s", path ), "Attach Error" );
            return;
        }
        TfpFrame* frame = new TfpFrame(
            m_tfpApp, wxDefaultPosition, wxSize( 900, 700 ), "", dbname );
        frame->Show( true );
    }
}

void TfpFrame::OnExternalCloseFile( wxCommandEvent& event )
{
    wxString dbname = m_menuFileExternalClose->GetLabelText( event.GetId() );
    recDb::CloseExternalDb( dbname );
    m_tfpApp->CloseDbnameFrames( dbname );
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

void TfpFrame::OnImportCsv( wxCommandEvent& event )
{
    wxString caption = _( "Select CSV Directory" );
    wxString defaultDir = ".";

    wxDirDialog dialog( this, caption, defaultDir );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        wxString caption = "Import CSV";
        wxString message = "CSV \"" + path + "\"";
        if( recImportCsv( path.ToStdString() ) ) {
            wxMessageBox( message + " Imported OK", caption );
        }
        else {
            wxMessageBox( "Error Importing " + message, caption );
        }
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

void TfpFrame::OnExportCsv( wxCommandEvent& event )
{
    wxString caption = _( "Create or Select Directory" );
    wxString defaultDir = ".";

    wxDirDialog dialog( this, caption, defaultDir );
    if( dialog.ShowModal() == wxID_OK )
    {
        wxString path = dialog.GetPath();
        wxString caption = "Export CSV";
        wxString message = "CSV \"" + path + "\"";
        if( recExportCsv( path.ToStdString() ) ) {
            wxMessageBox( message + " Saved OK", caption );
        }
        else {
            wxMessageBox( "Error Saving " + message, caption );
        }
    }
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
    // Close all windows and exit.
    wxTheApp->Exit();
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
        id = rgAddNewIndividual( this, Sex::male );
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
        id = rgAddNewIndividual( this, Sex::female );
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
            ret = rgAddNewParent( this, m_EditIndLeft, Sex::female );
            break;
        case tfpID_EDIT_NEW_FATHER_LEFT:
            ret = rgAddNewParent( this, m_EditIndLeft, Sex::male );
            break;
        case tfpID_EDIT_NEW_SPOUSE_LEFT:
            id = rgAddNewIndividual( this, Sex::female, 0, "", m_EditFamily );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_MOTHER_LEFT:
            ret = rgAddExistParent( this, m_EditIndLeft, Sex::female );
            break;
        case tfpID_EDIT_EXIST_FATHER_LEFT:
            ret = rgAddExistParent( this, m_EditIndLeft, Sex::male );
            break;
        case tfpID_EDIT_EXIST_SPOUSE_LEFT:
            ret = rgAddExistSpouse( this, m_EditIndLeft, Sex::female );
            break;
        case tfpID_EDIT_DELETE_IND_LEFT:
            ret = rgDeleteIndividual( this, m_EditIndLeft );
            break;
        case tfpID_EDIT_INDIVIDUAL_RIGHT:
            ret = rgEditIndividual( this, m_EditIndRight );
            break;
        case tfpID_EDIT_NEW_MOTHER_RIGHT:
            ret = rgAddNewParent( this, m_EditIndRight, Sex::female );
            break;
        case tfpID_EDIT_NEW_FATHER_RIGHT:
            ret = rgAddNewParent( this, m_EditIndRight, Sex::male );
            break;
        case tfpID_EDIT_NEW_SPOUSE_RIGHT:
            id = rgAddNewIndividual( this, Sex::male, 0, "", m_EditFamily );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_MOTHER_RIGHT:
            ret = rgAddExistParent( this, m_EditIndRight, Sex::female );
            break;
        case tfpID_EDIT_EXIST_FATHER_RIGHT:
            ret = rgAddExistParent( this, m_EditIndRight, Sex::male );
            break;
        case tfpID_EDIT_EXIST_SPOUSE_RIGHT:
            ret = rgAddExistSpouse( this, m_EditIndRight, Sex::female );
            break;
        case tfpID_EDIT_DELETE_IND_RIGHT:
            ret = rgDeleteIndividual( this, m_EditIndRight );
            break;
        case tfpID_EDIT_FAMILY:
            ret = rgEditFamily( this, m_EditFamily );
            break;
        case tfpID_EDIT_NEW_SON:
            id = rgAddNewChild( this, m_EditFamily, Sex::male );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_NEW_DAUR:
            id = rgAddNewChild( this, m_EditFamily, Sex::female );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_SON:
            id = rgAddExistChild( this, m_EditFamily, Sex::male );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EXIST_DAUR:
            id = rgAddExistChild( this, m_EditFamily, Sex::female );
            if( id ) ret = true;
            break;
        case tfpID_EDIT_EVENT_CURRENT:
            ret = rgEditEvent( this, m_editEventID );
            break;
        case tfpID_EDIT_EVENT_SELECT:
            id = rgSelectEvent( this, m_dbname, rgSELSTYLE_None );
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

void TfpFrame::OnEditRefTemplate( wxCommandEvent& event )
{
    idt refID = rgCreateReferenceFromTemplate( this );
    if( refID != 0 ) {
        DisplayHtmPage( "R" + recGetStr( refID ) );
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

void TfpFrame::OnEditGallery( wxCommandEvent& event )
{
    recDb::Begin();
    try {
        unsigned retbutton = 0;
        idt galID = rgSelectGallery( this, rgSELSTYLE_Create, &retbutton );
        if( galID && (retbutton || rgEditGallery( this, galID )) ) {
            recDb::Commit();
            RefreshHtmPage();
        }
        else {
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
        _("Enter the Researcher ID or 0 for new Researcher"),
        _("Researcher ID:"),
        _("Edit Researcher"),
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

void TfpFrame::OnEditRepository( wxCommandEvent& event )
{
    recDb::Begin();
    try {
        unsigned retbutton = 0;
        idt arcID = rgSelectRepository( this, rgSELSTYLE_Create, &retbutton );
        if( arcID && ( retbutton || rgEditRepository( this, arcID ) ) ) {
            recDb::Commit();
            RefreshHtmPage();
        }
        else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void TfpFrame::OnEditAssociate( wxCommandEvent & event )
{
    recDb::Begin();
    try {
        idt assID = rgSelectAssociate( this );
        if ( assID && rgEditAssociate( this, assID ) ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    }
    catch ( wxSQLite3Exception& e ) {
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

/*! \brief Called on a Find Event menu option event.
 */
void TfpFrame::OnFindEventID( wxCommandEvent& event )
{
    idt eveID = rgSelectEvent( this, m_dbname );
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

void TfpFrame::OnListMediaList( wxCommandEvent & event )
{
    DisplayHtmPage( "M" );
}

void TfpFrame::OnListMediaPagedList( wxCommandEvent & event )
{
    DisplayHtmPage( "M,0" );
}

void TfpFrame::OnListMediaDataList( wxCommandEvent & event )
{
    DisplayHtmPage( "MD" );
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
    if( rgSelectEventList( this, m_selEvent ) ) {
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

void TfpFrame::OnListRepositories( wxCommandEvent& event )
{
    DisplayHtmPage( "Rp" );
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

void TfpFrame::OnToolsCompact( wxCommandEvent& event )
{
    recDb::Vacuum();
}

void TfpFrame::OnSystemCheck( wxCommandEvent& event )
{
    // Unsure whether this is required or not.
    wxMessageBox( "Not yet implimented", "OnSystemCheck" );
}

void TfpFrame::OnWindowNew( wxCommandEvent& event )
{
    TfpFrame* frame = new TfpFrame(
        m_tfpApp, wxDefaultPosition, wxSize( 900, 700 ), "", m_dbname );
    frame->Show( true );
}

void TfpFrame::OnWindowClose( wxCommandEvent& event )
{
    Destroy();
}

void TfpFrame::OnSelectWindow( wxCommandEvent& event )
{
    size_t index = event.GetId() - tfpID_WINDOW_01;
    TfpFrame* frame = m_tfpApp->GetTfpFrame( index );
    wxASSERT( frame != nullptr );
    if( frame ) {
        frame->SetFocus();
    }
}

void TfpFrame::OnWindowWindows( wxCommandEvent& event )
{
    wxMessageBox( "Not yet implimented", "OnWindowWindows" );
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
    DoPopupNote( "About" );
}

/*! \brief Called on a Help, About Database menu option event.
 *
 *  Displays a message box with information about the currently.
 *  open database.
 */
void TfpFrame::OnAboutDatabase( wxCommandEvent& event )
{
    StringVec attached = recDb::GetAttachedDbList();
    wxString attached_list;
    for ( auto str: attached ) {
        if ( attached_list.empty() ) {
            attached_list = "\nAttached databases: ";
        }else{
            attached_list += ", ";
        }
        attached_list += str;
    }

    wxMessageBox(
        wxString::Format(
            _("Database \"%s\"\nVersion %s%s"),
            recDb::GetFileName(), recGetCurrentVersionStr(), attached_list
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
        if( m_back[ind] != "Error" ) {
            m_forward.push_back( m_back[ind] );
            m_toolbar->EnableTool( tfpID_FIND_FORWARD, true );
        }
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
    recRecordId rid = recGetRecordId( display );
    if( rid.table == recTable::null_table ) {
        if( display.StartsWith( "FI" ) ) {
            rid.table = recTable::Family;
            rid.id = recIndividual::GetFamilyID( rid.id );
        }
    }
    recDb::Begin();
    try {
        bool ret = false;
        switch( rid.table )
        {
        case recTable::Citation:
            ret = rgEditCitation( this, rid.id );
            break;
        case recTable::Contact:
            ret = rgEditContact( this, rid.id );
            break;
        case recTable::Date:
            ret = rgEditDate( this, rid.id );
            break;
        case recTable::Event:
            ret = rgEditEvent( this, rid.id );
            break;
        case recTable::Eventa:
            ret = rgEditEventa( this, rid.id );
            break;
        case recTable::Family:
            ret = rgEditFamily( this, rid.id );
            break;
        case recTable::Gallery:
            ret = rgEditGallery( this, rid.id );
            break;
        case recTable::Individual:
            ret = rgEditIndividual( this, rid.id );
            break;
        case recTable::Media:
            ret = rgEditMedia( this, rid.id );
            break;
        case recTable::MediaData: {
                // MD<num>,<dbname>
                size_t pos = display.find( ',' );
                if( pos == wxString::npos || display.length() == pos ) {
                    break;
                }
                ret = rgEditMediaData( this, rid.id, display.substr( pos + 1 ) );
            }
            break;
        case recTable::Name:
            ret = rgEditName( this, rid.id );
            break;
        case recTable::Persona:
            ret = rgEditPersona( this, rid.id );
            break;
        case recTable::Place:
            ret = rgEditPlace( this, rid.id );
            break;
        case recTable::Reference:
            ret = rgEditReference( this, rid.id );
            break;
        case recTable::Repository:
            ret = rgEditRepository( this, recGetID( display.Mid( 2 ) ) );
            break;
        case recTable::Researcher:
            ret = rgEditResearcher( this, recGetID( display.Mid( 2 ) ) );
            break;
        default:
            wxMessageBox( "Record \"" + display + "\" not recognised.", "Edit Error" );
        }
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        }
        else {
            recDb::Rollback();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }

}

void TfpFrame::OnPageItemTransfer( wxCommandEvent& event )
{
    wxString disp = GetDisplay();
    if( disp.size() < 2 ) {
        return;
    }
    wxString entity;
    idt record = 0;
    bool success = false;
    if( disp.GetChar( 0 ) == 'R' && recIsCharNumber( disp, 1 ) ) {
        entity = "Reference";
        success = disp.Mid( 1 ).ToLongLong( &record );
    }
    if( !success ) {
        return;
    }
    wxMessageDialog dlg(
        this, _( "Transfer " + entity + " record " + recGetStr( record ) + " from " + m_dbname ),
        "Transfer", wxOK | wxCANCEL | wxCENTRE
    );
    if( dlg.ShowModal() != wxID_OK ) {
        return;
    }
    recDb::Begin();
    try {
        if( rgTransferReference( this, record, m_dbname, "Main" ) != 0 ) {
            recDb::Commit();
        }
        else {
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
    if ( url.StartsWith( "tfp:" ) ) {
        DisplayHtmPage( url.Mid( 4 ) );
        return;
    }
    if ( url.StartsWith( "tfpr:" ) ) {
        DisplayReferenceLinkPage( url.Mid( 5 ) );
        return;
    }
    if ( url.StartsWith( "tfpe:" ) ) {
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
    Sex sex = ( m_ctxmenuref.substr( 0, 1 ) == "H" ) ? Sex::female : Sex::male;

    recDb::Begin();
    try {
        switch( event.GetId() )
        {
        case tfpID_HCTXMENU_EDIT_FAMILY:
            ret = rgEditFamily( this, id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SON:
            if( rgAddNewChild( this, id, Sex::male ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_NEW_DAUR:
            if( rgAddNewChild( this, id, Sex::female ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SON:
            id = rgAddExistChild( this, id, Sex::male );
            if( id ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_DAUR:
            id = rgAddExistChild( this, id, Sex::female );
            if( id ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_INDIVIDUAL:
            ret = rgEditIndividual( this, id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_MOTHER:
            ret = rgAddNewParent( this, id, Sex::female );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_FATHER:
            ret = rgAddNewParent( this, id, Sex::male );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SPOUSE:
            ret = rgAddNewSpouse( this, id, sex, id2 );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_MOTHER:
            ret = rgAddExistParent( this, id, Sex::female );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_FATHER:
            ret = rgAddExistParent( this, id, Sex::male );
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
    Destroy();
}

bool TfpFrame::NewFile()
{
    bool ret = false;
    wxString caption = _( "Create TFP Database" );
    wxString wildcard = _( "TFP Database (*.tfpd)|*.tfpd" );
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK ) {
        wxString path = dialog.GetPath();
        wxString fname = dialog.GetFilename();
        unsigned flags = recDb::CREATE_DB_STD_EXT | recDb::CREATE_DB_ENUM_FN;
        if( recDb::CreateDb( path, flags ) == true ) {
            recDb::Begin();
            try {
                rgSetupDatabase( this, fname );
                recDb::Commit();
            }
            catch( wxSQLite3Exception& e ) {
                recDb::ErrorMessage( e );
                recDb::Rollback();
            }
            SetDatabaseOpen( path );
            DisplayHomePage();
            ret = true;
        }
    }
    return ret;
}

bool TfpFrame::OpenFile()
{
    bool ret = false;
    wxString caption = _("Open Database");
    wxString wildcard = _("TFP Database (*.tfpd)|*.tfpd");
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( this, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if( dialog.ShowModal() == wxID_OK ) {
        ret = OpenFilename( dialog.GetPath() );
    }
    return ret;
}

bool TfpFrame::OpenFilename( const wxString& dbfname )
{
    wxString caption = "Opening " + dbfname;
    try {
        if( !wxFileExists( dbfname ) ) {
            wxMessageBox( _( "File not found!" ), caption );
            return false;
        }
        if( recDb::IsOpen() ) {
            wxMessageDialog dlg(
                this, _( "Current database will be closed first." ),
                caption, wxOK | wxCANCEL | wxCENTRE
            );
            if( dlg.ShowModal() != wxID_OK ) {
                return false;
            }
            recDb::CloseDb();
        }
        recDb::DbType type = recDb::OpenDb( dbfname );
        if( !SetDatabaseMenu( dbfname, type ) ) {
            wxMessageBox( _( "Problem opening database!" ), caption );
            CloseFile();
            return false;
        }
        DisplayHomePage();
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        return false;
    }
    return true;
}

void TfpFrame::CloseFile()
{
    if ( recDb::IsOpen() ) {
        recDb::CloseDb();
    }
    m_changeState = recDb::GetChange();
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
        try {
            wxString path = dialog.GetPath();
            if( tfpReadGedcom( path ) )
            {
                SetDatabaseOpen( path );
                DisplayHomePage();
                ret = true;
            }
            else {
                wxMessageBox( _( "Error Reading GEDCOM File" ), _( "Import" ) );
            }
        }
        catch( wxSQLite3Exception& e ) {
            recDb::ErrorMessage( e );
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
            id = rgCreateDefaultIndEvent( this, indID1, indID2, recEventTypeGrp::fam_union );
            if( id ) ret = true;
        } else if( href.StartsWith( "Eb" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(2) ), 0, recEventTypeGrp::birth );
            if( id ) ret = true;
        } else if( href.StartsWith( "Enb" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(3) ), 0, recEventTypeGrp::nr_birth );
            if( id ) ret = true;
        } else if( href.StartsWith( "Ed" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(2) ), 0, recEventTypeGrp::death );
            if( id ) ret = true;
        } else if( href.StartsWith( "End" ) ) {
            id = rgCreateDefaultIndEvent( this, recGetID( href.Mid(3) ), 0, recEventTypeGrp::nr_death );
            if( id ) ret = true;
        } else if( href.StartsWith( "Eo" ) ) {
            id = rgCreatePersonalEvent( this, recGetID( href.Mid(2) ), recEventType::ET_Occupation );
            if( id ) ret = true;
        } else if( href.StartsWith( "IL" ) ) {
            id = rgAddNewIndividual( this, Sex::male, -1, "", recGetID( href.Mid(2) ) );
            if( id ) ret = true;
        } else if( href.StartsWith( "IR" ) ) {
            id = rgAddNewIndividual( this, Sex::female, -1, "", recGetID( href.Mid(2) ) );
            if( id ) ret = true;
        } else if( href.StartsWith( "IF" ) ) {
            ret = rgAddNewParent( this, recGetID( href.Mid(2) ), Sex::female );
        } else if( href.StartsWith( "IM" ) ) {
            ret = rgAddNewParent( this, recGetID( href.Mid(2) ), Sex::male );
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
            ret = rgSelectEventList( this, m_selEvent );
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
    dlgNote* note = new dlgNote( *this, ref );
    note->Show();
}

void TfpFrame::DoPopupViewer( const wxString& href )
{
    if ( href.StartsWith( "MD" ) ) {
        // Note, format MDn,Am then n is MDataID and m is AssID.
        // m can be zero ("main" database).
        // format MDn,dbname then dname is a currently attached database
        idt mdID, assID;
        wxString dbname;
        recSplitStrRet ret = recSplitStr( href.substr( 2 ), &mdID, &assID, &dbname );
        if ( mdID ) {
            if( ret == recSplitStrRet::associate ) {
                rgViewMedia( this, mdID, assID );
                return;
            }
            if( ret == recSplitStrRet::text ) {
                rgViewMedia( this, mdID, dbname );
                return;
            }
        }
    } else if ( href.StartsWith( "M" ) ) {
        idt medID = recGetID( href.substr( 1 ) );
        if ( medID ) {
            rgViewMedia( this, m_dbname, medID );
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
    size_t c = 0, i, j;
    idt indID;
    ref.Mid( 1 ).ToLongLong( &indID );
    m_ctxmenuPages.clear();
    wxString page;

    menu->Append( cmd_ID + c, wxT("Family") );
    m_ctxmenuPages.push_back( "FI"+recGetStr( indID ) );
    c++;

    wxMenu* parmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_PARENTS, "Parents", parmenu );

    recFamilyVec families = recFamily::GetParentList( indID );
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
    recIndividualVec inds;
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        inds = recIndividual::GetChildren( families[i].FGetID() );
        for( j = 0 ; j < inds.size() ; j++ ) {
            if( inds[j].f_id == indID ) continue;
            sibmenu->Append( cmd_ID + c, inds[j].FGetName() );
            m_ctxmenuPages.push_back( "FI"+recGetStr( inds[j].f_id ) );
            c++;
        }
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_SIBLINGS, false );
    }

    wxMenu* marmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_SPOUSES, "Spouses", marmenu );
    families = recFamily::GetFamilyList( indID );
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
        inds = recIndividual::GetChildren( families[i].FGetID() );
        for( j = 0 ; j < inds.size() ; j++ ) {
            kidmenu->Append( cmd_ID + c, inds[j].FGetName() );
            m_ctxmenuPages.push_back( "FI"+recGetStr( inds[j].f_id ) );
            c++;
        }
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_CHILDREN, false );
    }
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

void TfpFrame::SetMediaDatabase( const wxString& path )
{
    wxFileName dbfile( path );
    m_titleFmt = wxString::Format( "TFP: %s, %%s", dbfile.GetName() );
    SetMenuBar( m_menuMediaDB );
    m_toolbar->EnableTool( tfpID_LIST_SURNAME_INDEX, false );
    m_toolbar->EnableTool( tfpID_LIST_PAGED_EVENTS, false );
    m_toolbar->EnableTool( tfpID_LIST_PAGED_REFERENCES, false );
    m_toolbar->EnableTool( tfpID_LIST_GALLERIES, false );
    m_toolbar->EnableTool( tfpID_GOTO_HOME, true );
    m_showpage->Enable( false );
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
    m_toolbar->EnableTool( tfpID_PAGE_ITEM_TRANSFER, false );
    m_showpage->Enable( false );
    m_back.clear();
    m_toolbar->EnableTool( tfpID_FIND_BACK, false );
    m_forward.clear();
    m_toolbar->EnableTool( tfpID_FIND_FORWARD, false );
    m_browser->SetPage( tfpGetDisplayText( "start", *this ), "" );
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
    recDb::DbType type = recDb::GetDatabaseType( m_dbname );
    if( type != recDb::DbType::full ) {
        return;
    }
    wxString disp = GetDisplay();
    wxUniChar uch = disp.GetChar( 0 );
    m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, m_toolflags.GetFlag( tfpTool::edit ) );
    m_toolbar->EnableTool( tfpID_PAGE_ITEM_TRANSFER, m_toolflags.GetFlag( tfpTool::transfer ) );
    if( m_dbname.CmpNoCase( "Main" ) != 0 ) {
        m_menuOpenDB->EnableTop( 1/* Edit */, false);
        if( uch == 'R' && recIsCharNumber( disp, 1 ) ) {
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_TRANSFER, true );
        }
        return;
    }
    m_menuOpenDB->EnableTop( 1/* Edit */, true );
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
        if( recIsCharDigit( disp, 1 ) ) {
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
        if( recIsCharDigit( disp, 1 ) ) {
            m_editEventID = recGetID( disp.Mid( 1 ) );
            name = recEvent::GetTitle( m_editEventID );
            m_menuEditEvent->SetLabel( tfpID_EDIT_EVENT_CURRENT, name );
            m_menuEditEvent->Enable( tfpID_EDIT_EVENT_CURRENT, true );
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        } else if( disp.size() >= 3 && (
            ( disp.GetChar( 1 ) == 'a' && recIsCharDigit( disp, 2 ))
        ) ) { // Ea<number>
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'P':
        if( disp.size() >= 3 && disp.GetChar( 1 ) == 'a'
            && recIsCharDigit( disp, 2 )
        ) { // Pa<number>
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'G':
        if( recIsCharDigit( disp, 1 ) ) {
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'M':
        if( disp.size() >= 3 && disp.GetChar( 1 ) == 'D'
            && recIsCharDigit( disp, 2 )
            ) { // MD<number>
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        if( recIsCharDigit( disp, 1 ) ) { // M<number>
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    case 'R':
        if( recIsCharDigit( disp, 1 ) ) { // R<number>
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        if( disp.size() >= 3 && disp.GetChar( 1 ) == 'e'
            && recIsCharDigit( disp, 2 )
            ) { // Re<number> 
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        if( disp.size() >= 3 && disp.GetChar( 1 ) == 'p'
            && recIsCharDigit( disp, 2 )
            ) { // Rp<number>
            m_toolbar->EnableTool( tfpID_PAGE_ITEM_EDIT, true );
        }
        break;
    }
}

bool TfpFrame::DisplayHtmPage( const wxString& name )
{
    wxBusyCursor wait;

    wxString norm = tfpNormalisePageName( name );
    wxString text = tfpGetDisplayText( name, *this );
    if( text.empty() ) {
        text = tfpWrErrorPage( norm );
        norm = "Error";
    }
    SetTitle( wxString::Format( m_titleFmt, norm ) );
    PushHtmName( norm );
    m_browser->SetPage( text, "" );
    RefreshEditMenu();
    m_changeState = recDb::GetChange();
    return true;
}

bool TfpFrame::DisplayReferenceLinkPage( const wxString & name )
{
    if ( name.compare( 0, 2, "Pa" ) == 0 && name.size() > 2 ) {
        idt id = recGetID( name.substr( 2 ) );
        if ( id ) {
            recIdVec indIDs = recPersona::GetIndividualIDs( id );
            if ( !indIDs.empty() ) {
                DisplayHtmPage( recIndividual::GetIdStr( indIDs[0] ) );
                return true;
            }
        }
    } else if ( name.compare( 0, 2, "Ea" ) == 0 && name.size() > 2 ) {
        idt id = recGetID( name.substr( 2 ) );
        if ( id ) {
            recIdVec eveIDs = recEventa::GetLinkedEventIDs( id );
            if ( !eveIDs.empty() ) {
                DisplayHtmPage( recEvent::GetIdStr( eveIDs[0] ) );
                return true;
            }
        }
    }
    DisplayHtmPage( name );
    return true;
}

void TfpFrame::RefreshHtmPage()
{
    wxString name = GetCurrentName();
    SetTitle( wxString::Format( m_titleFmt, name ) );
    if( !name.empty() ) {
        wxString text = tfpGetDisplayText( name, *this );
        if( text.empty() ) {
            text = tfpWrErrorPage( name );
            m_back[m_back.size() - 1] = "Error";
        }
        m_browser->SetPage( text, "" );
        RefreshEditMenu();
    }
    m_changeState = recDb::GetChange();
}

bool TfpFrame::DisplayHomePage()
{
    wxString page = recGetHomeDisplay( m_dbname );
    if( page.empty() ) {
        page = "BLANK";
    }
    return DisplayHtmPage( page );
}

void TfpFrame::CreateFullMenuRW()
{
    // create a menu bar for use with an open database
    wxMenu* menuFileAttachNew = new wxMenu;
    menuFileAttachNew->Append( tfpID_FILE_ATTACH_NEW_FULL, _( "&Full" ) );
    menuFileAttachNew->Append( tfpID_FILE_ATTACH_NEW_MEDIA, _( "&Media Only" ) );

    m_menuFileAssociateClose = new wxMenu;

    m_menuFileAssociate = new wxMenu;
    m_menuFileAssociate->Append( tfpID_FILE_ATTACH_NEW, _( "&New..." ), menuFileAttachNew );
    m_menuFileAssociate->Append( tfpID_FILE_ATTACH_OPEN, _( "&Open..." ) );
    m_menuFileAssociate->Append( tfpID_FILE_ATTACH_CLOSE, _( "&Close" ), m_menuFileAssociateClose );

    m_menuFileExternalClose = new wxMenu;

    m_menuFileExternal = new wxMenu;
    m_menuFileExternal->Append( tfpID_FILE_EXTERNAL_OPEN, _( "&Open..." ) );
    m_menuFileExternal->Append( tfpID_FILE_EXTERNAL_CLOSE, _( "&Close" ), m_menuFileExternalClose );

    wxMenu* menuFileImport = new wxMenu;
    menuFileImport->Append( tfpID_IMPORT_GEDCOM, _( "&GEDCOM file..." ) );
    menuFileImport->Append( tfpID_IMPORT_CSV_BACKUP, _( "&CSV Backup..." ) );

    wxMenu* menuFileExport = new wxMenu;
    menuFileExport->Append( tfpID_EXPORT_GEDCOM, _( "&GEDCOM file..." ) );
    menuFileExport->Append( tfpID_EXPORT_HTML, _( "&HTML files..." ) );
    menuFileExport->Append( tfpID_EXPORT_CSV_BACKUP, _( "&CSV Backup..." ) );

    wxMenu* menuFile = new wxMenu;
    menuFile->Append( tfpID_NEW_FILE, _( "&New Database...\tCtrl-N" ) );
    menuFile->Append( tfpID_OPEN_FILE, _( "&Open Database...\tCtrl-O" ) );
    menuFile->Append( tfpID_CLOSE_FILE, _( "&Close Database" ) );
    menuFile->Append( tfpID_FILE_ATTACH_MENU, _( "&Associate Database" ), m_menuFileAssociate );
    menuFile->Append( tfpID_FILE_EXTERNAL_MENU, _( "&External Database" ), m_menuFileExternal );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_FILE_IMPORT_MENU, _( "&Import" ), menuFileImport );
    menuFile->Append( tfpID_FILE_EXPORT_MENU, _( "Expor&t" ), menuFileExport );
    menuFile->AppendSeparator();
    menuFile->Append( tfpID_PRINT, _( "&Print...\tCtrl-P" ) );
    menuFile->Append( tfpID_PREVIEW, _( "Pre&view\tCtrl-Shift-P" ) );
    menuFile->Append( tfpID_PAGE_SETUP, _( "Page Set&up..." ) );
    menuFile->AppendSeparator();
    menuFile->Append( wxID_EXIT, _( "E&xit" ) );

    wxMenu* menuEdIndL = new wxMenu;
    menuEdIndL->Append( tfpID_EDIT_INDIVIDUAL_LEFT, _( "&Edit Individual" ) );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_NEW_MOTHER_LEFT, _( "Add new &Mother" ) );
    menuEdIndL->Append( tfpID_EDIT_NEW_FATHER_LEFT, _( "Add new &Father" ) );
    menuEdIndL->Append( tfpID_EDIT_NEW_SPOUSE_LEFT, _( "Add new &Spouse" ) );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_EXIST_MOTHER_LEFT, _( "Add existing M&other" ) );
    menuEdIndL->Append( tfpID_EDIT_EXIST_FATHER_LEFT, _( "Add existing F&ather" ) );
    menuEdIndL->Append( tfpID_EDIT_EXIST_SPOUSE_LEFT, _( "Add existing S&pouse" ) );
    menuEdIndL->AppendSeparator();
    menuEdIndL->Append( tfpID_EDIT_DELETE_IND_LEFT, _( "&Delete Individual" ) );

    wxMenu* menuEdIndR = new wxMenu;
    menuEdIndR->Append( tfpID_EDIT_INDIVIDUAL_RIGHT, _( "&Edit Individual" ) );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_NEW_MOTHER_RIGHT, _( "Add new &Mother" ) );
    menuEdIndR->Append( tfpID_EDIT_NEW_FATHER_RIGHT, _( "Add new &Father" ) );
    menuEdIndR->Append( tfpID_EDIT_NEW_SPOUSE_RIGHT, _( "Add new &Spouse" ) );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_EXIST_MOTHER_RIGHT, _( "Add existing M&other" ) );
    menuEdIndR->Append( tfpID_EDIT_EXIST_FATHER_RIGHT, _( "Add existing F&ather" ) );
    menuEdIndR->Append( tfpID_EDIT_EXIST_SPOUSE_RIGHT, _( "Add existing S&pouse" ) );
    menuEdIndR->AppendSeparator();
    menuEdIndR->Append( tfpID_EDIT_DELETE_IND_RIGHT, _( "&Delete Individual" ) );

    wxMenu* menuEdFam = new wxMenu;
    menuEdFam->Append( tfpID_EDIT_FAMILY, _( "&Edit Family" ) );
    menuEdFam->AppendSeparator();
    menuEdFam->Append( tfpID_EDIT_NEW_SON, _( "Add new &Son" ) );
    menuEdFam->Append( tfpID_EDIT_NEW_DAUR, _( "Add new &Daughter" ) );
    menuEdFam->AppendSeparator();
    menuEdFam->Append( tfpID_EDIT_EXIST_SON, _( "Add existing S&on" ) );
    menuEdFam->Append( tfpID_EDIT_EXIST_DAUR, _( "Add existing D&aughter" ) );

    m_menuEditInd = new wxMenu;
    m_menuEditInd->Append( tfpID_EDIT_IND_LEFT, "? ?..", menuEdIndL );
    m_menuEditInd->Append( tfpID_EDIT_IND_RIGHT, "? ?..", menuEdIndR );
    m_menuEditInd->Append( tfpID_EDIT_FAMILY_MENU, _( "F&amily" ), menuEdFam );
    m_menuEditInd->AppendSeparator();
    m_menuEditInd->Append( tfpID_EDIT_INDIVIDUAL, _( "Existing &Individual.." ) );
    m_menuEditInd->AppendSeparator();
    m_menuEditInd->Append( tfpID_EDIT_IND_NEW_MALE, _( "Add New &Male..." ) );
    m_menuEditInd->Append( tfpID_EDIT_IND_NEW_FEMALE, _( "Add New &Female..." ) );

    m_menuEditEvent = new wxMenu;
    m_menuEditEvent->Append( tfpID_EDIT_EVENT_CURRENT, _( "None" ) );
    m_menuEditEvent->Append( tfpID_EDIT_EVENT_SELECT, _( "&Select Event" ) );
    m_menuEditEvent->Append( tfpID_EDIT_EVENT_NEW_CON, _( "&New Conclusion Event" ) );

    m_menuEditReference = new wxMenu;
    m_menuEditReference->Append( tfpID_EDIT_REFERENCE, _( "&Reference..." ) );
    m_menuEditReference->Append( tfpID_EDIT_NEW_REFERENCE, _( "&New Reference" ) );
    m_menuEditReference->Append( tfpID_EDIT_REF_TEMPLATE, _( "Reference &Template" ) );

    wxMenu* menuEdCore = new wxMenu;
    menuEdCore->Append( tfpID_EDIT_EVENT_TYPE, _( "&Event Types..." ) );

    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append( tfpID_EDIT_IND_MENU, _( "&Individual" ), m_menuEditInd );
    menuEdit->Append( tfpID_EDIT_EVENT_MENU, _( "&Event" ), m_menuEditEvent );
    menuEdit->Append( tfpID_EDIT_REFERENCE_MENU, _( "&Reference" ), m_menuEditReference );
    menuEdit->Append( tfpID_EDIT_GALLERY, _( "&Gallery..." ) );
    menuEdit->Append( tfpID_EDIT_RESEARCHER, _( "R&esearcher..." ) );
    menuEdit->Append( tfpID_EDIT_REPOSITORY, _( "Rep&ository..." ) );
    menuEdit->Append( tfpID_EDIT_CORE_MENU, _( "&Core Data" ), menuEdCore );
    menuEdit->Append( tfpID_EDIT_ASSOCIATE, _( "&Associate database..." ) );

    wxMenu* menuFind = new wxMenu;
    menuFind->Append( tfpID_FIND_FAMILY_ID, _( "&Family ID..." ) );
    menuFind->Append( tfpID_FIND_INDIVIDUAL_ID, _( "&Individual ID..." ) );
    menuFind->Append( tfpID_FIND_EVENT_ID, _( "&Event ID..." ) );

    wxMenu* menuListMedia = new wxMenu;
    menuListMedia->Append( tfpID_LIST_GALLERIES, _( "&Galleries\tAlt-G" ) );
    menuListMedia->Append( tfpID_LIST_MEDIA_LIST, _( "&All Media\tAlt-M" ) );
    menuListMedia->Append( tfpID_LIST_MEDIA_PAGED_LIST, _( "&Paged Media" ) );
    menuListMedia->AppendSeparator();
    menuListMedia->Append( tfpID_LIST_MEDIADATA_LIST, _( "All Media &Data" ) );

    wxMenu* menuListRef = new wxMenu;
    menuListRef->Append( tfpID_LIST_ALL_REFERENCES, _( "&All References\tAlt-R" ) );
    menuListRef->Append( tfpID_LIST_PAGED_REFERENCES, _( "&Paged References" ) );

    wxMenu* menuListEvent = new wxMenu;
    menuListEvent->Append( tfpID_LIST_ALL_EVENTS, _( "&All Events\tAlt-E" ) );
    menuListEvent->Append( tfpID_LIST_PAGED_EVENTS, _( "&Paged Events" ) );
    menuListEvent->Append( tfpID_LIST_SELECTED_EVENTS, _( "&Selected Events..." ) );
    menuListEvent->AppendSeparator();
    menuListEvent->Append( tfpID_LIST_ALL_EVENTUMS, _( "All Even&tas" ) );
    menuListEvent->Append( tfpID_LIST_PAGED_EVENTUMS, _( "Pa&ged Eventas" ) );
    menuListEvent->Append( tfpID_LIST_SELECTED_EVENTUMS, _( "Se&lected Eventas..." ) );

    wxMenu* menuList = new wxMenu;
    menuList->Append( tfpID_LIST_SURNAME_INDEX, _( "&Surname Index\tAlt-S" ) );
    menuList->Append( tfpID_LIST_PERSONAS, _( "&Persona Index\tAlt-P" ) );
    menuList->Append( tfpID_LIST_INDIVIDUALS, _( "&Individuals\tAlt-I" ) );
    menuList->Append( tfpID_LIST_MEDIA_MENU, _( "&Media" ), menuListMedia );
    menuList->Append( tfpID_LIST_REFERENCE_MENU, _( "&References" ), menuListRef );
    menuList->Append( tfpID_LIST_EVENT_MENU, _( "&Events" ), menuListEvent );
    menuList->Append( tfpID_LIST_RESEARCHERS, _( "Resear&chers\tAlt-C" ) );
    menuList->Append( tfpID_LIST_REPOSITORIES, _( "Rep&ositories\tAlt-O" ) );

    wxMenu* menuChart = new wxMenu;
    menuChart->Append( tfpID_PED_CHART, _( "&Pedigree..." ) );
    menuChart->Append( tfpID_DESC_CHART, _( "&Descendant..." ) );

    wxMenu* menuTools = new wxMenu;
    menuTools->Append( tfpID_SYSTEM_SETTING, _( "&System Options..." ) );
    menuTools->Append( tfpID_USER_SETTING, _( "&User Options..." ) );
    menuTools->Append( tfpID_TOOLS_COMPACT, _( "Compact &Database" ) );
    menuTools->Append( tfpID_TOOL_SYSTEM_CHECK, _( "Systems &Check" ) );

    m_menuWindow = new wxMenu;
    m_menuWindow->Append( tfpID_WINDOW_NEW, _( "&New Window" ) );
    m_menuWindow->Append( tfpID_WINDOW_CLOSE, _( "&Close Window" ) );
    m_menuWindow->AppendSeparator();
    m_menuWindowItem[0] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_01, "&1" );
    m_menuWindowItem[1] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_02, "&2" );
    m_menuWindowItem[2] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_03, "&3" );
    m_menuWindowItem[3] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_04, "&4" );
    m_menuWindowItem[4] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_05, "&5" );
    m_menuWindowItem[5] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_06, "&6" );
    m_menuWindowItem[6] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_07, "&7" );
    m_menuWindowItem[7] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_08, "&8" );
    m_menuWindowItem[8] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_09, "&9" );
    m_menuWindowItem[9] = m_menuWindow->AppendCheckItem( tfpID_WINDOW_10, "1&0" );
    m_menuWindowItemSize = 10;
    m_menuWindow->Append( tfpID_WINDOW_WINDOWS, _( "&Windows..." ) );

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append( tfpID_HELP_WEB_HOME, _( "The Family Pack &Website" ) );
    menuHelp->Append( tfpID_HELP_ABOUT_DB, _( "About &Database" ) );
    menuHelp->Append( wxID_ABOUT, _( "&About \"The Family Pack\"" ) );

    m_menuOpenDB = new wxMenuBar;
    m_menuOpenDB->Append( menuFile, _( "&File" ) );
    m_menuOpenDB->Append( menuEdit, _( "&Edit" ) );
    m_menuOpenDB->Append( menuFind, _( "F&ind" ) );
    m_menuOpenDB->Append( menuList, _( "&List" ) );
    m_menuOpenDB->Append( menuChart, _( "&Chart" ) );
    m_menuOpenDB->Append( menuTools, _( "&Tools" ) );
    m_menuOpenDB->Append( m_menuWindow, _( "&Window" ) );
    m_menuOpenDB->Append( menuHelp, _( "&Help" ) );
}

void TfpFrame::CreateMediaMenu()
{
    // Menu bar for use with MediaData database
    wxMenu* menuMediaFile = new wxMenu;
    menuMediaFile->Append( tfpID_NEW_FILE, _( "&New File\tCtrl-N" ) );
    menuMediaFile->Append( tfpID_OPEN_FILE, _( "&Open File\tCtrl-O" ) );
    menuMediaFile->AppendSeparator();
    menuMediaFile->Append( tfpID_IMPORT_GEDCOM, _( "&Import GEDCOM file" ) );
    menuMediaFile->AppendSeparator();
    menuMediaFile->Append( wxID_EXIT, _( "E&xit" ) );

    wxMenu* menuMediaHelp = new wxMenu;
    menuMediaHelp->Append( tfpID_HELP_WEB_HOME, _( "The Family Pack &Website" ) );
    menuMediaHelp->Append( tfpID_HELP_ABOUT_DB, _( "About &Database" ) );
    menuMediaHelp->Append( wxID_ABOUT, _( "&About \"The Family Pack\"" ) );

    m_menuMediaDB = new wxMenuBar;
    m_menuMediaDB->Append( menuMediaFile, _( "&File" ) );
    m_menuMediaDB->Append( menuMediaHelp, _( "&Help" ) );
}

void TfpFrame::CreateClosedMenu()
{
    // Menu bar for use with closed database
    wxMenu* menuInitFile = new wxMenu;
    menuInitFile->Append( tfpID_NEW_FILE, _( "&New File\tCtrl-N" ) );
    menuInitFile->Append( tfpID_OPEN_FILE, _( "&Open File\tCtrl-O" ) );
    menuInitFile->AppendSeparator();
    menuInitFile->Append( tfpID_IMPORT_GEDCOM, _( "&Import GEDCOM file" ) );
    menuInitFile->Append( tfpID_IMPORT_CSV_BACKUP, _( "Import &CSV Backup..." ) );
    menuInitFile->AppendSeparator();
    menuInitFile->Append( wxID_EXIT, _( "E&xit" ) );

    wxMenu* menuInitHelp = new wxMenu;
    menuInitHelp->Append( tfpID_HELP_WEB_HOME, _( "The Family Pack &Website" ) );
    menuInitHelp->Append( wxID_ABOUT, _( "&About \"The Family Pack\"" ) );

    m_menuClosedDB = new wxMenuBar;
    m_menuClosedDB->Append( menuInitFile, _( "&File" ) );
    m_menuClosedDB->Append( menuInitHelp, _( "&Help" ) );
}

void TfpFrame::CreateFullToolbar()
{
    m_toolbar = CreateToolBar();
    m_showpage = new wxTextCtrl( m_toolbar, tfpID_SHOW_PAGE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
    wxBitmap bmpForward( forward_xpm );
    wxBitmap bmpBack( back_xpm );
    wxBitmap bmpFind( find_xpm );
    wxBitmap bmpEvents( event_xpm );
    wxBitmap bmpRefs( ref_xpm );
    wxBitmap bmpGalleries( gallery_xpm );
    wxBitmap bmpHome( home_xpm );
    wxBitmap bmpTranfer( transfer_xpm );

    m_toolbar->AddTool( tfpID_FIND_BACK, _( "Back" ), bmpBack );
    m_toolbar->AddTool( tfpID_FIND_FORWARD, _( "Forward" ), bmpForward );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_LIST_SURNAME_INDEX, _( "Index" ), bmpFind );
    m_toolbar->AddTool( tfpID_LIST_PAGED_EVENTS, _( "Events" ), bmpEvents );
    m_toolbar->AddTool( tfpID_LIST_PAGED_REFERENCES, _( "References" ), bmpRefs );
    m_toolbar->AddTool( tfpID_LIST_GALLERIES, _( "Galleries" ), bmpGalleries );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_GOTO_HOME, _( "Home" ), bmpHome );
    m_toolbar->AddSeparator();
    m_toolbar->AddControl( m_showpage );
    m_toolbar->AddSeparator();
    m_toolbar->AddTool( tfpID_PAGE_ITEM_EDIT, _( "Edit" ), *imgEditBitmap );
    m_toolbar->AddTool( tfpID_PAGE_ITEM_TRANSFER, _( "Transfer" ), bmpTranfer );
    m_toolbar->Realize();
    SetToolBar( m_toolbar );
}

bool TfpFrame::SetDatabaseMenu( const wxString& dbfname, recDb::DbType type )
{
    switch( type )
    {
    case recDb::DbType::full:
        SetDatabaseOpen( dbfname );
        break;
    case recDb::DbType::media_data_only:
        SetMediaDatabase( dbfname );
        break;
    default:
        SetNoDatabase();
        return false;
    }
    DisplayHomePage();
    return true;
}

// End of tfpFrame.cpp file
