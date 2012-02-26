/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgNote.cpp
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recDatabase.h>

#include "dlgNote.h"
#include "tfpWr.h"


void dlgNote::SetDisplay( const wxString& name )
{
    m_name = name;
    m_cond = recDb::GetChange();
}

bool dlgNote::TransferDataToWindow()
{
    m_htmlWin->DisplayHtmPage( m_name );
    return true;
}

void dlgNote::OnIdle( wxIdleEvent& event )
{
    if( m_cond != recDb::GetChange() ) {
        m_htmlWin->RefreshHtmPage();
    }
}

void dlgNote::OnClose( wxCloseEvent& event )
{
    Destroy();
}

// End of dlgNote.cpp file
