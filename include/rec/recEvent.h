/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 .. 2021, Nick Matthews.
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

#ifndef REC_RECEVENT_H
#define REC_RECEVENT_H

#include <rec/recDatabase.h>
#include <rec/recDate.h>
#include <rec/recIndEvent.h>
#include <rec/recEventType.h>
#include <rec/recEventEventa.h>
#include <rec/recEventa.h>


//============================================================================
//-------------------------[ recEvent ]---------------------------------------
//============================================================================

class recEvent : public recDbT<recEvent>
{
public:
    static constexpr const char* s_tablename = "Event";

    wxString f_title;
    idt      f_higher_id;
    idt      f_type_id;
    idt      f_date1_id;
    idt      f_date2_id;
    idt      f_place_id;
    wxString f_note;
    long     f_date_pt;
    wxString f_user_ref;

    recEvent() : f_higher_id(0), f_type_id(0), f_date1_id(0), f_date2_id(0),
        f_place_id(0), f_date_pt(0) {}
    recEvent( idt id ) : recDbT(id) { Read(); }
    recEvent( const recEvent& event );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recEvent& r2 ) const;

    wxString FGetTitle() const { return f_title; }
    idt FGetHigherID() const { return f_higher_id; }
    idt FGetTypeID() const { return f_type_id; }
    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetNote() const { return f_note; }
    long FGetDatePt() const { return f_date_pt; }
    wxString FGetUserRef() const { return f_user_ref; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetHigherID( idt eveID ) { f_higher_id = eveID; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetDate1ID( idt date1ID ) { f_date1_id = date1ID; }
    void FSetDate2ID( idt date2ID ) { f_date2_id = date2ID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetDatePt( idt datePt ) { f_date_pt = datePt; }
    void FSetDatePt( recDate::DatePoint dp ) { f_date_pt = recDate::GetDatePoint( f_date1_id, dp ); }
    void FSetUserRef( const wxString& ur ) { f_user_ref = ur; }

    static wxString GetIdStr( idt evID ) { return wxString::Format( "E" ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    idt CreateFromEventa( const recEventa& eventa );
    static idt CreateFromEventa( idt erID );

    void CreateRolesFromEventa( idt eaID ) const { CreateRolesFromEventa( f_id, eaID ); }
    static void CreateRolesFromEventa( idt eID, idt eaID );

    wxString SetAutoTitle( const wxString& name1, const wxString& name2 = wxEmptyString );
    static void SetDatePeriodToInclude( idt eventID, idt dateID );

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
    recET_GRP GetTypeGroup() const;
    static wxString GetDetailStr( idt evID );
    static wxString GetTypeStr( idt evID );
    static wxString GetTitle( idt evID );
    static wxString GetNote( idt evID );
    static wxString GetDateStr( idt evID );
    static wxString GetAddressStr( idt evID );
    static idt GetDate1ID( idt evID );
    static void UpdateDatePoint( idt evID );
    void UpdateDatePoint();

    static recEventVec GetLowerEvents( idt eventID );
    recEventVec GetLowerEvents() const { return GetLowerEvents( f_id ); }

    static recEventaVec FindEquivRefEvents( idt eveID );
    recEventaVec FindEquivRefEvents() const { return FindEquivRefEvents( f_id ); }

    static recIdVec GetReferenceIDs( idt eveID );
    recIdVec GetReferenceIDs() const { return GetReferenceIDs( f_id ); }

    static recEventaVec GetEventasIncludeLower( idt eveID );
    recEventaVec GetEventasIncludeLower() const { return GetEventasIncludeLower( f_id ); }

    static recEventEventaVec GetEventEventas( idt eveID );
    recEventEventaVec GetEventEventas() const { return GetEventEventas( f_id ); }

    static bool IsFamilyEvent( idt eveID );
    bool IsFamilyEvent() const { return IsFamilyEvent( f_id ); }

    static recIndEventVec GetIndividualEvents( idt eID );
    recIndEventVec GetIndividualEvents() const { return GetIndividualEvents( f_id ); }

    static wxSQLite3Table GetTitleList();
    static wxSQLite3Table GetTitleList( idt offset, int limit );

    static void RemoveDates( idt dateID ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    void RemoveFromDatabase();
    static void RemoveFromDatabase( idt id );
    static void RemoveIncOrphansFromDatabase( idt id );

    static void DeleteIfOrphaned( idt id );
};

#endif // REC_RECEVENT_H
