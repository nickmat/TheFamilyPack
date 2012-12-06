/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recFilterEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Impliments class used to filter events.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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

#include <rec/recFilterEvent.h>

recFilterEvent::recFilterEvent()
{
    for( size_t i = 0 ; i < recEventType::ETYPE_Grp_MAX ; i++ ) {
        m_groupChks[i] = true;
    }
    m_begDate = m_endDate = 0;
}

void recFilterEvent::CreateEventTable()
{
    wxASSERT( m_class == FE_Ind ); // TODO: filter on Ref events
    wxString sql;
    wxString tc = GetTypeCondition();
    wxString dc = GetDateCondition();
    if( m_types.size() == 0 || tc.size() == 0 ) {
        sql << ";";
    } else {
        sql << "SELECT DISTINCT E.id, E.title, E.date_pt"
               " FROM Event E, IndividualEvent IE"
               " WHERE IE.event_id=E.id" << tc << dc <<
               " ORDER BY date_pt, E.id;";
    }
    m_table = recDb::GetDb()->GetTable( sql );
}

wxString recFilterEvent::GetTypeCondition()
{
    wxString sql;
    int count = 0;
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        if( m_typeChks[i] ) {
            if( count > 0 ) {
                sql << " OR";
            }
            sql << " type_id=" << m_types[i];
            count++;
        }
    }
    if( count == 0 ) {
        return wxEmptyString;
    }
    if( count == 1 ) {
        return " AND" + sql;
    }
    return " AND (" + sql + " )";
}

wxString recFilterEvent::GetDateCondition()
{
    wxString sql;
    if( m_begDate ) {
        sql << " AND date_pt>=" << m_begDate;
    }
    if( m_endDate ) {
        sql << " AND date_pt<=" << m_endDate;
    }
    return sql;
}

size_t recFilterEvent::GetTableSize()
{
    if( m_table.IsOk() ) {
        return m_table.GetRowCount(); 
    }
    return 0;
}

idt recFilterEvent::GetIdForRow( size_t i )
{
    m_table.SetRow( i );
    return GET_ID( m_table.GetInt64( 0 ) ); 
}


// End of src/rec/recFilterEvent.cpp file
