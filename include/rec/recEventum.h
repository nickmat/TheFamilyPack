/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventum.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Eventum table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#ifndef REC_RECEVENTUM_H
#define REC_RECEVENTUM_H

#include <rec/recDatabase.h>
#include <rec/recEventType.h>
#include <rec/recDate.h>
#include <rec/recReference.h>


//============================================================================
//-------------------------[ recEventum ]-------------------------------------
//============================================================================

class recEventum : public recDb
{
public:
    wxString f_title;
    idt      f_type_id;
    idt      f_date1_id;
    idt      f_date2_id;
    idt      f_place_id;
    wxString f_note;
    long     f_date_pt;

    recEventum() {}
    recEventum( idt id ) : recDb(id) { Read(); }
    recEventum( const recEventum& event );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Eventum" );

    wxString FGetTitle() const { return f_title; }
    idt FGetTypeID() const { return f_type_id; }
    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetNote() const { return f_note; }
    long FGetDatePt() const { return f_date_pt; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetDate1ID( idt date1ID ) { f_date1_id = date1ID; }
    void FSetDate2ID( idt date2ID ) { f_date2_id = date2ID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetDatePt( idt datePt ) { f_date_pt = datePt; }
    void FSetDatePt( recDate::DatePoint dp ) { f_date_pt = recDate::GetDatePoint( f_date1_id, dp ); }

    wxString SetAutoTitle( const wxString& name1, const wxString& name2 = wxEmptyString );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "Em"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

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

    idt FindReferenceID() const { return FindReferenceID( f_id ); }
    static idt FindReferenceID( idt erID ) {
        return recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, erID );
    }
    static recEventEventumVec GetEventEventums( idt erID );
    recEventEventumVec GetEventEventums() const { return GetEventEventums( f_id ); }

    static bool IsFamilyEvent( idt eveID );
    bool IsFamilyEvent() const { return IsFamilyEvent( f_id ); }

    recEventumPersonaVec GetEventumPersonas();
    static wxSQLite3Table GetTitleList();
    static wxSQLite3Table GetTitleList( idt offset, int limit );

    static int GetLastPerSeqNumber( idt eventID );
    int GetLastPerSeqNumber() const { return GetLastPerSeqNumber( f_id ); }

    // Find matching Event records by following the links:-
    // Eventum/Persona(prime Role) -> Persona/Individual link -> Individual/Event(matching role)
    // Depending on the type and group of the event, loosely match Date and Place.
    enum recEVENT_Link { recEVENT_Link_EvEvRec, recEVENT_Link_IndPer };
    recIdVec FindMatchingEvents( recEVENT_Link link = recEVENT_Link_EvEvRec ) const;
    recCheckIdVec FindCheckedMatchingEvents() const;

    static void RemoveDates( idt dateID ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    void RemoveFromDatabase();
    static void RemoveFromDatabase( idt id );
    static void RemoveIncOrphansFromDatabase( idt id );

    static void DeleteIfOrphaned( idt id );
};

#endif // REC_RECEVENTUM_H
