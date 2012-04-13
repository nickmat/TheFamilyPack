/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpHtml.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpHtml class header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     23 February 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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

#ifndef TFPHTML_H
#define TFPHTML_H

#include <wx/html/htmlwin.h>
#include <rec/recDatabase.h>
#include <rec/recUser.h>

typedef std::vector<wxString> StringVec;
class TfpFrame;

class TfpHtml : public wxHtmlWindow
{
    DECLARE_EVENT_TABLE()

public:
    TfpHtml( wxWindow* parent, TfpFrame* frame = NULL ) 
        : wxHtmlWindow( parent ), m_frame(frame) {}
    TfpHtml( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
        : wxHtmlWindow( parent, id, pos, size, style ), m_frame(NULL) {}
    ~TfpHtml() {}

    bool DisplayHtmPage( const wxString& name );
    bool DisplayHomePage() { return DisplayHtmPage( recGetHomeDisplay() ); }
    void DisplayBlankPage( const wxString& name );
    void SetName( const wxString& name ) { m_name = name; }
    void RefreshHtmPage();

private:
    void OnHtmlLinkClicked( wxHtmlLinkEvent& event );

    void DoLinkLeft( const wxString& href );
    void DoLinkRight( const wxString& href );

    void DoHtmCtxMenu( const wxString& ref );
    int AddFamiliesToMenu( const wxString& ref, wxMenu* menu, int cmd_ID );
    void OnHtmCtxMenu( wxCommandEvent& event );
    void OnHtmIndMenu( wxCommandEvent& event );
    void DoRightCtxMenu( const wxString& ref );
    void OnRightCtxMenu( wxCommandEvent& event );

    wxString GetDisplayText( const wxString& name );

    wxString  m_name;        // Current page name
    TfpFrame* m_frame;
    wxString  m_ctxmenuref;
    StringVec m_ctxmenuPages;
};


#endif // TFPHTML_H

