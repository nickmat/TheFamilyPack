/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgSelIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select Individual record from list dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
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
#include "dlgSelIndividual.h"
#include "tfpListCtrlInd.h"


dlgSelectIndividual::dlgSelectIndividual( wxWindow* parent )
    : fbDlgSelectIndividual( parent )
{
    m_count = 0;
    m_listInd->InsertColumn( 0, wxT("ID") );
    m_listInd->InsertColumn( 1, wxT("Surname") );
    m_listInd->InsertColumn( 2, wxT("Given name") );
    m_listInd->InsertColumn( 3, wxT("Epitaph") );
}

void dlgSelectIndividual::OnIdle( wxIdleEvent& event )
{
    // TODO: Implement OnIdle
    if( m_listInd->GetSelectedItemCount() > 0 ) {
        m_buttonSave->Enable( true );
    } else {
        m_buttonSave->Enable( false );
    }
}

void dlgSelectIndividual::OnIndividualSelected( wxListEvent& event )
{
    // TODO: Implement OnIndividualSelected
}

idt dlgSelectIndividual::GetSelectedID()
{
    if( m_count > 0 && m_listInd->GetSelectedItemCount() > 0 ) {
        long row = m_listInd->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
        m_table.SetRow( row );
        return GET_ID( m_table.GetInt64( 0 ) );
    }
    return 0;
}

bool dlgSelectIndividual::CreateTable( Sex sex )
{
    m_table = recIndividual::GetNameTable( sex );
    m_count = m_table.GetRowCount();

    if( m_count == 0 ) return false;

    m_listInd->SetTable( &m_table );
    m_listInd->SetItemCount( m_count );
    return true;
}


wxString tfpListCtrlIndividuals::OnGetItemText( long item, long column ) const
{
    mp_table->SetRow( item );
    return mp_table->GetAsString( column );
//  return wxString::Format( wxT("Col: %ld, Row: %ld"), column, item );

}

// End of dlgSelIndividual.cpp file
