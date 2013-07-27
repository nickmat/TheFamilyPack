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

//============================================================================
//-------------------------[ recSelSetEvent ]---------------------------------
//============================================================================

bool recSelSetEvent::IsTypeChecked( idt etID ) const
{
    for( size_t i = 0 ; i < m_typesChked.size() ; i++ ) {
        if( m_typesChked[i] == etID ) {
            return true;
        }
    }
    return false;
}

//============================================================================
//-------------------------[ recFilterEvent ]---------------------------------
//============================================================================

recFilterEvent::recFilterEvent( const recSelSetEvent& set )
    : m_begDate(0), m_endDate(0)
{
    m_grpsEnabled = set.GetGroupsEnabled();
    m_grpsChecked = set.GetGroupsChecked();

    recEventTypeVec ets = recEventType::ReadVec( m_grpsEnabled & m_grpsChecked );
    for( size_t i = 0 ; i < ets.size() ; i++ ) {
        idt etID = ets[i].FGetID();
        bool chk = set.IsTypeChecked( etID );
        AddTypeIDs( etID, chk );
    }

    CalendarScheme sch = set.GetCalendarScheme();
    long jdn1, jdn2;
    wxString str = set.GetBegDateStr();
    if( calStrToJdnRange( &jdn1, &jdn2, str, sch ) ) {
        m_begDate = jdn1;
    }
    str = set.GetEndDateStr();
    if( calStrToJdnRange( &jdn1, &jdn2, str, sch ) ) {
        m_endDate = jdn2;
    }

    m_indIDs = set.GetIndIDs();
}

long recFilterEvent::GetTypeIndexFromID( idt etID ) const
{
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        if( m_types[i] == etID ) {
            return (long) i;
        }
    }
    return -1;
}

void recFilterEvent::CreateEventTable()
{
    wxString sql;
    wxString tc = GetTypeCondition();
    wxString dc = GetDateCondition();
    wxString indc = GetIndCondition();
    wxString indt;
    if( indc.size() ) {
        indt = ", IndividualEvent IE";
    }

    if( m_types.size() == 0 || tc.size() == 0 ) {
        sql << ";";
    } else {
        sql << "SELECT DISTINCT E.id, E.title, E.date_pt"
               " FROM Event E" << indt <<
               " WHERE E.id<>0" << tc << dc << indc <<
               " ORDER BY E.date_pt, E.id;";
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

wxString recFilterEvent::GetIndCondition()
{
    wxString sql;
    if( m_indIDs.size() ) {
        sql << " AND E.id=IE.event_id AND (";
        for( size_t i = 0 ; i < m_indIDs.size() ; i++ ) {
            if( i > 0 ) {
                sql << " OR";
            }
            sql << " IE.ind_id=" << m_indIDs[i];
        }
        sql << " )";
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

recIdVec recFilterEvent::GetTypeIDVec() const
{
    recIdVec typeIDs;
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        if( m_typeChks[i] ) {
            typeIDs.push_back( m_types[i] );
        }
    }
    return typeIDs;
}

void recFilterEvent::SetTypesChecked( bool chk )
{
    for( size_t i = 0 ; i < m_typeChks.size() ; i++ ) {
        m_typeChks[i] = chk;
    }
}

void recFilterEvent::AddTypeIDs( idt typeID, bool chk )
{
    m_types.push_back( typeID ); 
    m_typeChks.push_back( chk );
}

void recFilterEvent::ResetTypeIDs( bool chk )
{
    ClearTypeIDs();
    recEventTypeVec ets = recEventType::ReadVec( m_grpsEnabled & m_grpsChecked );
    for( size_t i = 0 ; i < ets.size() ; i++ ) {
        AddTypeIDs( ets[i].FGetID(), chk );
    }
}

// End of src/rec/recFilterEvent.cpp file
