/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgNote.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Display html text as a note.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 January 2012
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#ifndef DLGNOTE_H
#define DLGNOTE_H

#include "fbDlg.h"

class dlgNote : public fbDlgNote
{
public:
    dlgNote( wxWindow* parent ) : m_cond(0), fbDlgNote( parent ) {}

//    void SetText( const wxString& text ) { m_text = text; }
    bool SetDisplay( const wxString& name );

private:
    wxString GetBlankDisplay( const wxString& name );

    bool TransferDataToWindow();

    void OnIdle( wxIdleEvent& event );
    void OnHtmlLinkClicked( wxHtmlLinkEvent& event );
    void OnClose( wxCloseEvent& event );


    wxString m_name;
    wxString m_text;
    long     m_cond;
};

#endif // DLGNOTE_H
