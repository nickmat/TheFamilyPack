/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpNote.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Display html text as a note.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 January 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#include "tfpNote.h"

#include "tfpFrame.h"
#include "tfpWr.h"

#include <rec/recDatabase.h>
#include <rg/rgDialogs.h>

#include <wx/webview.h>
#include <wx/webviewfshandler.h>


dlgNote::dlgNote( TfpFrame& parent, const wxString& name )
    : m_frame( parent ), m_name( name ), m_cond( recDb::GetChange() ),
    m_browser( wxWebView::New( this, tfpID_BROWSER ) ),
    wxDialog(
        (wxWindow*) &parent, wxID_ANY, "Note " + name, wxDefaultPosition, wxSize( 450, 300 ),
        wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
    )
{
    wxBoxSizer* bSizer1 = new wxBoxSizer( wxVERTICAL );
    bSizer1->Add( m_browser, 1, wxALL | wxEXPAND, 0 );
    SetSizer( bSizer1 );
    Layout();

    SetPosition( wxGetMousePosition() );

    // Connect Events
    Connect( wxEVT_COMMAND_WEBVIEW_NAVIGATING, wxWebViewEventHandler( dlgNote::OnNavigationRequest ) );
    Connect( wxEVT_IDLE, wxIdleEventHandler( dlgNote::OnIdle ) );
    Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( dlgNote::OnClose ) );
}

dlgNote::~dlgNote()
{
    // Disconnect Events
    Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( dlgNote::OnClose ) );
    Disconnect( wxEVT_IDLE, wxIdleEventHandler( dlgNote::OnIdle ) );
    Disconnect( wxEVT_COMMAND_WEBVIEW_NAVIGATING, wxWebViewEventHandler( dlgNote::OnNavigationRequest ) );
}

bool dlgNote::TransferDataToWindow()
{
    m_browser->SetPage( tfpGetDisplayText( m_name, m_frame, tfpDisplay::note ), "" );
    return true;
}

void dlgNote::OnNavigationRequest( wxWebViewEvent& evt )
{
    wxString url = evt.GetURL();
    if ( url == "tfpc:Close" ) {
        Close();
        return;
    }
    if ( url.StartsWith( "http:" ) || url.StartsWith( "https:" ) ) {
        Close();
        wxLaunchDefaultBrowser( url );
        return;
    }
    if( !url.StartsWith( "tfpe:" ) ) {
        return;
    }

    recDb::Begin();
    try {
        bool ret = false;

        if( url.StartsWith( "tfpe:D" ) ) {
            ret = rgEditDate( this, recGetID( url.Mid(6) ) );
        }
        else if( url.StartsWith( "tfpe:P" ) ) {
            ret = rgEditPlace( this, recGetID( url.Mid(6) ) );
        }
        else if ( url.StartsWith( "tfpe:N" ) ) {
            ret = rgEditName( this, recGetID( url.Mid( 6 ) ) );
        }
        else if( url.StartsWith( "tfpe:Ci" ) ) {
            ret = rgEditCitation( this, recGetID( url.Mid( 7 ) ) );
        }
        else if( url.StartsWith( "tfpe:C" ) ) {
            ret = rgEditContact( this, recGetID( url.Mid( 6 ) ) );
        }
        if( ret == true ) {
            recDb::Commit();
            wxString text = tfpGetDisplayText( m_name, m_frame, tfpDisplay::note );
            m_browser->SetPage( text, "" );
            m_cond = recDb::GetChange();
        } else {
            recDb::Rollback();
        }
    } 
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void dlgNote::OnIdle( wxIdleEvent& event )
{
    if( m_cond != recDb::GetChange() ) {
        if( recDb::IsOpen() ) {
            m_browser->SetPage( tfpGetDisplayText( m_name, m_frame, tfpDisplay::note ), "" );
            m_cond = recDb::GetChange();
        } else {
            Close( true );
        }
    }
}

void dlgNote::OnClose( wxCloseEvent& event )
{
    Destroy();
}

// End of dlgNote.cpp file
