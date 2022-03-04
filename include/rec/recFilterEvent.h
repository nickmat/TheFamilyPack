/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Declares class used to filter events.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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
//-------------------------[ recSelSetEvent ]---------------------------------
//============================================================================

// A class to hold the settings used by a "Select Event" dialog
// The recFilterEvent class does the actual work of creating the list of
// Events from these settings.

class recSelSetEvent
{
public:
    recSelSetEvent( const wxString& dbname = "Main" )
        : m_dbname(dbname), m_grpsEnabled(recET_GRP_FILTER_AllValid),
        m_grpsChecked(0), m_calScheme(CALENDAR_SCH_Gregorian)
    {}

    void Reset( const wxString& dbname );

    wxString GetDbname() const { return m_dbname; }
    unsigned GetGroupsEnabled() const { return m_grpsEnabled; }
    unsigned GetGroupsChecked() const { return m_grpsChecked; }
    bool IsTypeChecked( idt etID ) const;
    CalendarScheme GetCalendarScheme() const { return m_calScheme; }
    wxString GetBegDateStr() const { return m_begDateStr; }
    wxString GetEndDateStr() const { return m_endDateStr; }
    recIdVec GetIndIDs() const { return m_indIDs; }

    void SetGroupsEnabled( unsigned grpsEnabled ) { m_grpsEnabled = grpsEnabled; }
    void SetGroupsChecked( unsigned grpsChecked ) { m_grpsChecked = grpsChecked; }
    void ClearTypeChecked() { m_typesChked.clear(); }
    void AddTypeChecked( idt etID ) { m_typesChked.push_back( etID ); }
    void SetCalendarScheme( CalendarScheme sch ) { m_calScheme = sch; }
    void SetBegDateStr( const wxString& str ) { m_begDateStr = str; }
    void SetEndDateStr( const wxString& str ) { m_endDateStr = str; }
    void SetIndIDs( recIdVec indIDs ) { m_indIDs = indIDs; }
    void ClearIndIDs() { m_indIDs.clear(); }
    void AddIndID( idt indID ) { m_indIDs.push_back( indID ); }

private:
    wxString m_dbname;
    unsigned m_grpsEnabled; // Collection of recET_FILTER_Grp* flags
    unsigned m_grpsChecked; 
    recIdVec m_typesChked;
    CalendarScheme m_calScheme;
    wxString m_begDateStr;
    wxString m_endDateStr;
    recIdVec m_indIDs;
};

//============================================================================
//-------------------------[ recFilterEvent ]---------------------------------
//============================================================================

// A class which, depending on a number of settings, can create a database
// table of Event records.

class recFilterEvent
{
public:
    recFilterEvent( const recSelSetEvent& set );

    unsigned GetGroupsEnabled() const { return m_grpsEnabled; }
    unsigned GetGroupsChecked() const { return m_grpsChecked; }
    size_t GetTypesSize() const { return m_types.size(); }
    idt GetTypeID( size_t index ) const { return m_types[index]; }
    bool GetTypeChecked( size_t index ) const { return m_typeChks[index]; }
    long GetTypeIndexFromID( idt etID ) const;
    long GetBegDatePt() const { return m_begDate; }
    long GetEndDatePt() const { return m_endDate; }
    const recIdVec& GetIndIDs() const { return m_indIDs; }
    wxSQLite3Table* GetTable() { return &m_table; }
    size_t GetTableSize();
    idt GetIdForRow( size_t i );
    recIdVec GetTypeIDVec() const;

    void SetGroupsEnabled( unsigned grpsEnabled ) { m_grpsEnabled = grpsEnabled; }
    void SetGroupsChecked( unsigned grpsChecked ) { m_grpsChecked = grpsChecked; }
    void SetTypeFlag( size_t index, bool flag ) { m_typeChks[index] = flag; }
    void SetTypesChecked( bool chk );
    void SetBegDatePt( long dp ) { m_begDate = dp; }
    void SetEndDatePt( long dp ) { m_endDate = dp; }
    void SetIndIDs( recIdVec indIDs ) { m_indIDs = indIDs; }

    void ClearTypeIDs() { m_types.clear(); m_typeChks.clear(); }
    void AddTypeIDs( idt typeID, bool chk = true );
    void ResetTypeIDs( bool chk );

    void CreateEventTable( const wxString& dbname );

private:
    wxString GetTypeCondition();
    wxString GetDateCondition();
    wxString GetIndCondition();

    unsigned m_grpsEnabled; // Collection of recET_FILTER_Grp* flags
    unsigned m_grpsChecked; 
    recIdVec m_types;
    BoolVec  m_typeChks;
    long     m_begDate;
    long     m_endDate;
    recIdVec m_indIDs;

    wxSQLite3Table m_table;
};


#if 0
class recFilterEvent
{
public:
    enum FE_Class { FE_All, FE_Ind, FE_Ref, FE_Max };
    enum recFE_FLAG {
        recFE_FLAG_EnableNul  = 0x0001,
        recFE_FLAG_EnableInd  = 0x0002,
        recFE_FLAG_EnableFam  = 0x0004,
        recFE_FLAG_EnableIndM = 0x0008,
        recFE_FLAG_ShowNul    = 0x0100,
        recFE_FLAG_ShowInd    = 0x0200,
        recFE_FLAG_ShowFam    = 0x0400,
        recFE_FLAG_ShowIndM   = 0x0800,
        recFE_FLAG_Default    = 0x0006
    };

    recFilterEvent( unsigned flag = recFE_FLAG_Default );

    bool GetGroupEnabled( size_t index ) const { return m_groupEnabled[index]; }
    bool GetGroupChecked( size_t index ) const { return m_groupChecked[index]; }
    idt GetTypeID( size_t index ) const { return m_types[index]; }
    bool GetTypeChecked( size_t index ) const { return m_typeChks[index]; }
    size_t GetTypesSize() const { return m_types.size(); }
    long GetTypeIndexFromID( idt etID ) const;
    wxString GetBegDatePtStr() const { return m_begDateStr; }
    wxString GetEndDatePtStr() const { return m_endDateStr; }
    long GetBegDatePt() const { return m_begDate; }
    long GetEndDatePt() const { return m_endDate; }
    idt GetIndID() const { return m_indID; }
    wxSQLite3Table* GetTable() { return &m_table; }
    size_t GetTableSize();
    idt GetIdForRow( size_t i );
    recIdVec GetTypeIDVec() const;

    void SetFEClass( FE_Class fec ) { m_class = fec; }
    void SetGroupEnabled( size_t index, bool flag ) { m_groupEnabled[index] = flag; }
    void SetGroupChecked( size_t index, bool flag ) { m_groupChecked[index] = flag; }
    void SetTypeFlag( size_t index, bool flag ) { m_typeChks[index] = flag; }
    void SetTypesChecked( bool chk );
    void SetBegDatePtStr( const wxString& str ) { m_begDateStr = str; }
    void SetEndDatePtStr( const wxString& str ) { m_endDateStr = str; }
    void SetBegDatePt( long dp ) { m_begDate = dp; }
    void SetEndDatePt( long dp ) { m_endDate = dp; }
    void SetIndID( idt indID ) { m_indID = indID; }

    void ClearTypeIDs() { m_types.clear(); m_typeChks.clear(); }
    void AddTypeIDs( idt typeID, bool chk = true );
    void ResetTypeIDs( unsigned grpfilter, bool chk );

    void CreateEventTable();

private:
    wxString GetTypeCondition();
    wxString GetDateCondition();
    wxString GetIndCondition();


    FE_Class       m_class;
    bool           m_groupEnabled[recEventType::ETYPE_Grp_MAX];
    bool           m_groupChecked[recEventType::ETYPE_Grp_MAX];
    recIdVec       m_types;
    BoolVec        m_typeChks;
    idt            m_indID;
    long           m_begDate;
    long           m_endDate;

    wxSQLite3Table m_table;

    wxString       m_begDateStr;
    wxString       m_endDateStr;
};
#endif

#endif // RECFILTEREVENT_H
