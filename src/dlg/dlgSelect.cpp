/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgSelect.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select record from list dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     27 November 2010
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

#include "rec/recIndividual.h"
#include "dlgSelect.h"
#include "dlgRecTableCtrl.h"

dlgSelect::dlgSelect( wxWindow* parent, wxString* headers, long width )
    : fbDlgSelect( parent )
{
    m_width = width;
    for( long i = 0 ; i < width ; i++ ) {
        m_listCtrl->InsertColumn( 0, headers[i] );
    }
    m_count = 0;
}

void dlgSelect::OnIdle( wxIdleEvent& event )
{
    if( m_listCtrl->GetSelectedItemCount() > 0 ) {
        m_buttonSelect->Enable( true );
    } else {
        m_buttonSelect->Enable( false );
    }
}

void dlgSelect::SetTable( wxArrayString table )
{
    m_table = table;
    m_count = table.size() / m_width;

    m_listCtrl->SetTable( &m_table, m_width );
    m_listCtrl->SetItemCount( m_count );
}

long dlgSelect::GetSelectedRow()
{
    return m_listCtrl->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
}

idt dlgSelect::GetSelectedID()
{
    if( m_count > 0 && m_listCtrl->GetSelectedItemCount() > 0 ) {
        long row = m_listCtrl->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

        wxLongLong_t id;
        if( !m_table[row*m_width].ToLongLong( &id ) ) {
            return 0;
        }
        return id;
    }
    return 0;
}

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectPersona ]-------------------------------------------
//-------------------------------------------------------------------------------

wxString dlgSelectPersona::sm_colHeaders[COL_MAX] = { _("ID"), _("Name") };

dlgSelectPersona::dlgSelectPersona( wxWindow* parent )
    : dlgSelect( parent, sm_colHeaders, COL_MAX )
{
    SetTitle( _("Select Persona") );
}

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectName ]-------------------------------------------
//-------------------------------------------------------------------------------

//#include <rec/recReference.h>

wxString dlgSelectName::sm_colHeaders[COL_MAX] = { _("ID"), _("Name") };
#if 0
bool dlgSelectName::CreateRefNameTable( idt refID )
{
    wxArrayString table = recReferenceEntity::GetNameTable( refID );

    if( table.size() == 0 ) {
        return false;
    }
    SetTable( table );

    return true;
}
#endif
// End of dlgSelIndividual.cpp file
