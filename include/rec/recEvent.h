/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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
    static constexpr recTable s_table = recTable::Event;

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
    recEvent( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recEvent( const recEvent& event );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
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
    void FSetUserRef( const wxString& ur ) { f_user_ref = ur; }

    void SetDatePt( recDate::DatePoint dp, const wxString& dbname = "Main" ) {
        f_date_pt = recDate::GetDatePoint( f_date1_id, dp, dbname ); }

    static wxString GetIdStr( idt evID ) { return wxString::Format( "E" ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    idt CreateFromEventa( const recEventa& eventa, const wxString& dbname = "Main" );
    static idt CreateFromEventa( idt erID, const wxString& dbname = "Main" );

    void CreateRolesFromEventa( idt eaID, const wxString& dbname = "Main" ) const {
        CreateRolesFromEventa( f_id, eaID, dbname ); }
    static void CreateRolesFromEventa( idt eID, idt eaID, const wxString& dbname = "Main" );

    wxString SetAutoTitle(
        const wxString& name1, const wxString& name2 = wxEmptyString, const wxString& dbname = "Main" );
    static void SetDatePeriodToInclude( idt eventID, idt dateID, const wxString& dbname = "Main" );

    wxString GetDetailStr( const wxString& dbname = "Main" ) const;
    wxString GetTypeStr( const wxString& dbname = "Main" ) const;
    wxString GetDateStr( const wxString& dbname = "Main" ) const;
    wxString GetAddressStr( const wxString& dbname = "Main" ) const;
    recEventTypeGrp GetTypeGroup( const wxString& dbname = "Main" ) const;
    static wxString GetDetailStr( idt evID, const wxString& dbname = "Main" );
    static wxString GetTypeStr( idt evID, const wxString& dbname = "Main" );
    static wxString GetTitle( idt evID, const wxString& dbname = "Main" );
    static wxString GetNote( idt evID, const wxString& dbname = "Main" );
    static wxString GetDateStr( idt evID, const wxString& dbname = "Main" );
    static wxString GetAddressStr( idt evID, const wxString& dbname = "Main" );
    static idt GetDate1ID( idt evID, const wxString& dbname = "Main" );
    static void UpdateDatePoint( idt evID, const wxString& dbname = "Main" );
    void UpdateDatePoint( const wxString& dbname = "Main" );

    static recIdVec GetTypeOfIDs( idt etID, const wxString& dbname = "Main" );

    static recEventVec GetLowerEvents( idt eventID, const wxString& dbname = "Main" );
    recEventVec GetLowerEvents( const wxString& dbname = "Main" ) const {
        return GetLowerEvents( f_id, dbname ); }

    static recEventaVec FindEquivRefEvents( idt eveID, const wxString& dbname = "Main" );
    recEventaVec FindEquivRefEvents( const wxString& dbname = "Main" ) const {
        return FindEquivRefEvents( f_id, dbname ); }

    static recIdVec GetReferenceIDs( idt eveID, const wxString& dbname = "Main" );
    recIdVec GetReferenceIDs( const wxString& dbname = "Main" ) const {
        return GetReferenceIDs( f_id, dbname ); }

    static recEventaVec GetEventasIncludeLower( idt eveID, const wxString& dbname = "Main" );
    recEventaVec GetEventasIncludeLower( const wxString& dbname = "Main" ) const {
        return GetEventasIncludeLower( f_id, dbname ); }

    static recEventEventaVec GetEventEventas( idt eveID, const wxString& dbname = "Main" );
    recEventEventaVec GetEventEventas( const wxString& dbname = "Main" ) const {
        return GetEventEventas( f_id, dbname ); }

    static bool IsFamilyEvent( idt eveID, const wxString& dbname = "Main" );
    bool IsFamilyEvent( const wxString& dbname = "Main" ) const {
        return IsFamilyEvent( f_id, dbname ); }

    static recIndEventVec GetIndividualEvents( idt eID, const wxString& dbname = "Main" );
    recIndEventVec GetIndividualEvents( const wxString& dbname = "Main" ) const {
        return GetIndividualEvents( f_id, dbname ); }

    static wxSQLite3Table GetTitleList( const wxString& dbname = "Main" );
    static wxSQLite3Table GetTitleList( idt offset, int limit, const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );

    static void RemoveDates( idt dateID, const wxString& dbname = "Main" ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID, const wxString& dbname = "Main" ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    void RemoveFromDatabase( const wxString& dbname = "Main" );
    static void RemoveFromDatabase( idt id, const wxString& dbname = "Main" );
    static void RemoveIncOrphansFromDatabase( idt id, const wxString& dbname = "Main" );

    static void DeleteIfOrphaned( idt id, const wxString& dbname = "Main" );
};

#endif // REC_RECEVENT_H
