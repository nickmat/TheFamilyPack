/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Declares class used to filter events.
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

#ifndef RECFILTEREVENT_H
#define RECFILTEREVENT_H

#include <rec/recEvent.h>

//============================================================================
//-------------------------[ recFilterEvent ]---------------------------------
//============================================================================

class recFilterEvent
{
public:
    enum FE_Class { FE_All, FE_Ind, FE_Ref, FE_Max };
    enum recFE_FLAG {
        recFE_FLAG_EnableNul = 0x0001,
        recFE_FLAG_EnableInd = 0x0002,
        recFE_FLAG_EnableFam = 0x0004,
        recFE_FLAG_ShowNul   = 0x0100,
        recFE_FLAG_ShowInd   = 0x0200,
        recFE_FLAG_ShowFam   = 0x0400,
        recFE_FLAG_Default   = 0x0006
    };

    recFilterEvent( unsigned flag = recFE_FLAG_Default );

    bool GetGroupEnabled( size_t index ) const { return m_groupEnabled[index]; }
    bool GetGroupChecked( size_t index ) const { return m_groupChecked[index]; }
    size_t GetTypesSize() const { return m_types.size(); }
    wxString GetBegDatePtStr() const { return m_begDateStr; }
    wxString GetEndDatePtStr() const { return m_endDateStr; }
    long GetBegDatePt() const { return m_begDate; }
    long GetEndDatePt() const { return m_endDate; }
    wxSQLite3Table* GetTable() { return &m_table; }
    size_t GetTableSize();
    idt GetIdForRow( size_t i );
    recIdVec GetTypeIDVec() const;

    void SetFEClass( FE_Class fec ) { m_class = fec; }
    void SetGroupEnabled( size_t index, bool flag ) { m_groupEnabled[index] = flag; }
    void SetGroupChecked( size_t index, bool flag ) { m_groupChecked[index] = flag; }
    void SetTypeFlag( size_t index, bool flag ) { m_typeChks[index] = flag; }
    void SetBegDatePtStr( const wxString& str ) { m_begDateStr = str; }
    void SetEndDatePtStr( const wxString& str ) { m_endDateStr = str; }
    void SetBegDatePt( long dp ) { m_begDate = dp; }
    void SetEndDatePt( long dp ) { m_endDate = dp; }

    void ClearTypeIDs() { m_types.clear(); m_typeChks.clear(); }
    void AddTypeIDs( idt typeID ) { m_types.push_back( typeID ); m_typeChks.push_back( true ); }

    void CreateEventTable();

private:
    wxString GetTypeCondition();
    wxString GetDateCondition();


    FE_Class       m_class;
    bool           m_groupEnabled[recEventType::ETYPE_Grp_MAX];
    bool           m_groupChecked[recEventType::ETYPE_Grp_MAX];
    recIdVec       m_types;
    BoolVec        m_typeChks;
    wxString       m_begDateStr;
    wxString       m_endDateStr;
    long           m_begDate;
    long           m_endDate;
    wxSQLite3Table m_table;
};


#endif // RECFILTEREVENT_H
