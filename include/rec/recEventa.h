/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Eventa table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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

#ifndef REC_RECEVENTA_H
#define REC_RECEVENTA_H

#include <rec/recDatabase.h>
#include <rec/recDate.h>
#include <rec/recEventaPersona.h>
#include <rec/recEventType.h>
#include <rec/recEventEventa.h>
#include <rec/recFamEventa.h>
#include <rec/recFamIndEventa.h>
#include <rec/recReference.h>


//============================================================================
//--------------------------[ recEventa ]-------------------------------------
//============================================================================

class recEventa : public recDbT<recEventa>
{
public:
    static constexpr const char* s_tablename = "Event";

    wxString f_title;
    idt      f_ref_id;
    idt      f_type_id;
    idt      f_date1_id;
    idt      f_date2_id;
    idt      f_place_id;
    wxString f_note;
    long     f_date_pt;

    recEventa() : f_ref_id( 0 ), f_type_id( 0 ), f_date1_id( 0 ), f_date2_id( 0 ),
        f_place_id( 0 ), f_date_pt( 0 ) {}
    recEventa( idt id ) : recDbT(id) { Read(); }
    recEventa( const recEventa& event );

    void Clear();
    void Save();
    bool Read();

    wxString FGetTitle() const { return f_title; }
    idt FGetRefID() const { return f_ref_id; }
    idt FGetTypeID() const { return f_type_id; }
    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetNote() const { return f_note; }
    long FGetDatePt() const { return f_date_pt; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetDate1ID( idt date1ID ) { f_date1_id = date1ID; }
    void FSetDate2ID( idt date2ID ) { f_date2_id = date2ID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetDatePt( idt datePt ) { f_date_pt = datePt; }

    void SetDatePt( recDate::DatePoint dp ) { f_date_pt = recDate::GetDatePoint( f_date1_id, dp ); }

    wxString SetAutoTitle( const wxString& name1, const wxString& name2 = wxEmptyString );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "Ea" ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
    recEventTypeGrp GetTypeGroup() const;
    static wxString GetDetailStr( idt eaID );
    static wxString GetTypeStr( idt eaID );
    static wxString GetTitle( idt eaID );
    static wxString GetNote( idt eaID );
    static wxString GetDateStr( idt eaID );
    static wxString GetAddressStr( idt eaID );
    static idt GetRefID( idt eaID );
    static idt GetDate1ID( idt eaID );
    static void UpdateDatePoint( idt eaID );
    void UpdateDatePoint();

    static recEventEventaVec GetEventEventas( idt erID );
    recEventEventaVec GetEventEventas() const { return GetEventEventas( f_id ); }

    static bool IsFamilyEvent( idt eveID );
    bool IsFamilyEvent() const { return IsFamilyEvent( f_id ); }

    static recEventaPersonaVec GetEventaPersonas( idt eaID );
    recEventaPersonaVec GetEventaPersonas() const { return GetEventaPersonas( f_id ); }

    static wxSQLite3Table GetTitleList();
    static wxSQLite3Table GetTitleList( idt offset, int limit );

    // NOTE: Use, void recEventaPersona::SetNextPerSequence( idt eaID );
    static int GetLastPerSeqNumber( idt eventID );
    int GetLastPerSeqNumber() const { return GetLastPerSeqNumber( f_id ); }

    static recFamilyEventaVec GetFamilyEventas( idt eaID );
    recFamilyEventaVec GetFamilyEventas() const { return GetFamilyEventas( f_id ); }

    static recFamilyIndEventaVec GetFamilyIndEventas( idt eaID );
    recFamilyIndEventaVec GetFamilyIndEventas() const { return GetFamilyIndEventas( f_id ); }

    static recIdVec GetLinkedEventIDs( idt eaID );
    recIdVec GetLinkedEventIDs() const { return GetLinkedEventIDs( f_id ); }
    // Commer delimited string of linked Event ID strings.
    static wxString GetLinkedEventIDsStr( idt eaID );
    wxString GetLinkedEventIDsStr() const { return GetLinkedEventIDsStr( f_id ); }

    // Find matching Event records by following the links:-
    // Eventa/Persona(prime Role) -> Persona/Individual link -> Individual/Event(matching role)
    // Depending on the type and group of the event, loosely match Date and Place.
    recIdVec FindLinkedEventsViaInd() const;
    recCheckIdVec FindCheckedLinkedEvents() const;

    void CreateFamilyLink() const;
    static void CreateFamilyLink( idt eaID ) { recEventa ea(eaID); ea.CreateFamilyLink(); }
    void CreatePersonalEvent() const;
    static void CreatePersonalEvent( idt eaID ) { recEventa ea(eaID); ea.CreatePersonalEvent(); }

    static void RemoveDates( idt dateID ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    void RemoveFromDatabase();
    static void RemoveFromDatabase( idt id );
    static void RemoveIncOrphansFromDatabase( idt id );

    static void DeleteIfOrphaned( idt id );
};

#endif // REC_RECEVENTA_H
