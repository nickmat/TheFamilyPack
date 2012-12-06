/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgTableCtrl.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Sub classes of wxListCtrl to work with database.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
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

#include <rec/recEvent.h>

#include "rgTableCtrl.h"

void rgRecTableCtrl::SetTable( wxSQLite3Table* table ) 
{
    m_table = table;
    SetItemCount( table->GetRowCount() );
}

wxString rgRecTableCtrl::OnGetItemText( long item, long column ) const
{
    m_table->SetRow( item );
    return m_table->GetAsString( column );
}

void rgRecEventTableCtrl::SetTable( wxSQLite3Table* table ) 
{
    m_table = table;
    SetItemCount( table->GetRowCount() );
}

wxString rgRecEventTableCtrl::OnGetItemText( long item, long column ) const
{
    long dp;

    m_table->SetRow( item );
    switch( column )
    {
    case 0:
        return recEvent::GetIdStr( GET_ID( m_table->GetInt64( 0 ) ) );
    case 2:
        dp = m_table->GetInt( 2 );
        if( dp == 0 ) {
            return wxEmptyString;
        }
        return calStrFromJdn( dp, CALENDAR_SCH_Gregorian );
    default:
        return m_table->GetAsString( column );
    }
}

wxString rgStrTableCtrl::OnGetItemText( long item, long column ) const
{
    return m_strTable->Item( m_width * item + column );
}

// End of src/rg/rgTableCtrl.cpp file.