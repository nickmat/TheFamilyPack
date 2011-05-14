/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgSelEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select Event record from list dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     6 November 2010
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
#include "dlgSelEvent.h"
#include "dlgRecTableCtrl.h"

dlgSelectEvent::dlgSelectEvent( wxWindow* parent )
    : fbDlgSelectEvent( parent )
{
    m_count = 0;
    m_listEvent->InsertColumn( 0, _("ID") );
    m_listEvent->InsertColumn( 1, _("Title") );
    m_listEvent->InsertColumn( 2, _("Date") );
    m_listEvent->InsertColumn( 3, _("Place") );
}

void dlgSelectEvent::OnIdle( wxIdleEvent& event )
{
    if( m_listEvent->GetSelectedItemCount() > 0 ) {
        m_buttonSelect->Enable( true );
    } else {
        m_buttonSelect->Enable( false );
    }
}

idt dlgSelectEvent::GetSelectedID()
{
    if( m_count > 0 && m_listEvent->GetSelectedItemCount() > 0 ) {
        long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

        wxLongLong_t id;
        if( !m_table[row*COL_MAX].ToLongLong( &id ) ) {
            return 0;
        }
        return id;
    }
    return 0;
}

bool dlgSelectEvent::CreateMarriageTable( idt famID )
{
    recFamily fam(famID);
    m_table = fam.GetMarriageEventTable();
    m_count = m_table.size() / COL_MAX;

    if( m_count == 0 ) return false;

    m_listEvent->SetTable( &m_table, COL_MAX );
    m_listEvent->SetItemCount( m_count );
    return true;
}


// End of dlgSelIndividual.cpp file
