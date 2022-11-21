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

class recEventa : public recDbT<recEventa>, public recUidT<recEventa>
{
public:
    static constexpr const char* s_tablename = "Eventa";
    static constexpr recTable s_table = recTable::Eventa;

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
    recEventa( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recEventa( const recEventa& event );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );

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

    wxString SetAutoTitle(
        const wxString& name1, const wxString& name2 = "", const wxString& dbname = "Main" );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "Ea" ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetDetailStr( const wxString& dbname = "Main" ) const;
    wxString GetTypeStr( const wxString& dbname = "Main" ) const;
    wxString GetDateStr( const wxString& dbname = "Main" ) const;
    wxString GetAddressStr( const wxString& dbname = "Main" ) const;
    recEventTypeGrp GetTypeGroup( const wxString& dbname = "Main" ) const;
    static wxString GetDetailStr( idt eaID, const wxString& dbname = "Main" );
    static wxString GetTypeStr( idt eaID, const wxString& dbname = "Main" );
    static wxString GetTitle( idt eaID, const wxString& dbname = "Main" );
    static wxString GetNote( idt eaID, const wxString& dbname = "Main" );
    static wxString GetDateStr( idt eaID, const wxString& dbname = "Main" );
    static wxString GetAddressStr( idt eaID, const wxString& dbname = "Main" );
    static idt GetRefID( idt eaID, const wxString& dbname = "Main" );
    static idt GetDate1ID( idt eaID, const wxString& dbname = "Main" );
    static void UpdateDatePoint( idt eaID, const wxString& dbname = "Main" );
    void UpdateDatePoint( const wxString& dbname = "Main" );

    static recEventEventaVec GetEventEventas( idt erID, const wxString& dbname = "Main" );
    recEventEventaVec GetEventEventas( const wxString& dbname = "Main" ) const {
        return GetEventEventas( f_id, dbname ); }

    static bool IsFamilyEvent( idt eveID, const wxString& dbname = "Main" );
    bool IsFamilyEvent( const wxString& dbname = "Main" ) const {
        return IsFamilyEvent( f_id, dbname ); }

    static recEventaPersonaVec GetEventaPersonas( idt eaID, const wxString& dbname = "Main" );
    recEventaPersonaVec GetEventaPersonas( const wxString& dbname = "Main" ) const {
        return GetEventaPersonas( f_id, dbname ); }

    static wxSQLite3Table GetTitleList( const wxString& dbname = "Main" );
    static wxSQLite3Table GetTitleList( idt offset, int limit, const wxString& dbname = "Main" );

    // NOTE: Use, void recEventaPersona::SetNextPerSequence( idt eaID );
    static int GetLastPerSeqNumber( idt eventID );
    int GetLastPerSeqNumber() const { return GetLastPerSeqNumber( f_id ); }

    static recFamilyEventaVec GetFamilyEventas( idt eaID, const wxString& dbname = "Main" );
    recFamilyEventaVec GetFamilyEventas( const wxString& dbname = "Main" ) const {
        return GetFamilyEventas( f_id, dbname ); }

    static recFamilyIndEventaVec GetFamilyIndEventas( idt eaID, const wxString& dbname = "Main" );
    recFamilyIndEventaVec GetFamilyIndEventas( const wxString& dbname = "Main" ) const {
        return GetFamilyIndEventas( f_id, dbname ); }

    static recIdVec GetLinkedEventIDs( idt eaID, const wxString& dbname = "Main" );
    recIdVec GetLinkedEventIDs( const wxString& dbname = "Main" ) const {
        return GetLinkedEventIDs( f_id, dbname ); }
    // Commer delimited string of linked Event ID strings.
    static wxString GetLinkedEventIDsStr( idt eaID, const wxString& dbname = "Main" );
    wxString GetLinkedEventIDsStr( const wxString& dbname = "Main" ) const {
        return GetLinkedEventIDsStr( f_id, dbname ); }

    // Find matching Event records by following the links:-
    // Eventa/Persona(prime Role) -> Persona/Individual link -> Individual/Event(matching role)
    // Depending on the type and group of the event, loosely match Date and Place.
    recIdVec FindLinkedEventsViaInd( const wxString& dbname = "Main" ) const;
    recCheckIdVec FindCheckedLinkedEvents( const wxString& dbname = "Main" ) const;

    void CreateFamilyLink() const;
    static void CreateFamilyLink( idt eaID ) { recEventa ea(eaID); ea.CreateFamilyLink(); }
    void CreatePersonalEvent() const;
    static void CreatePersonalEvent( idt eaID ) { recEventa ea(eaID); ea.CreatePersonalEvent(); }

    static recIdVec GetEventaPersonaIDs( idt eaID, const wxString& dbname = "Main" );
    recIdVec GetEventaPersonaIDs( const wxString& dbname = "Main" ) const {
        return GetEventaPersonaIDs( f_id, dbname );
    }

    static idt Transfer(
        idt from_eaID, const wxString& fromdb, idt to_refID, const wxString& todb );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static void RemoveDates( idt dateID, const wxString& dbname = "Main" ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID, const wxString& dbname = "Main" ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    static bool RemoveFromDatabase( idt id, const wxString& dbname = "Main" );

    static bool DeleteIfOrphaned( idt id, const wxString& dbname = "Main" );
};

#endif // REC_RECEVENTA_H
