/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 IndividualEvent records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015..2022, Nick Matthews.
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

#ifndef REC_RECINDEVENT_H
#define REC_RECINDEVENT_H

#include <rec/recDatabase.h>

class recIndividualEvent;
typedef std::vector< recIndividualEvent >  recIndEventVec;

//============================================================================
//-------------------------[ recIndividualEvent ]-----------------------------
//============================================================================

class recIndividualEvent : public recDbT<recIndividualEvent>
{
public:
    static constexpr const char* s_tablename = "IndividualEvent";
    static constexpr recTable s_table = recTable::IndividualEvent;

    idt      f_ind_id;
    idt      f_higher_id;
    idt      f_event_id;
    idt      f_role_id;
    wxString f_note;
    int      f_ind_seq;

    recIndividualEvent() : f_ind_id(0), f_higher_id(0),
        f_event_id(0), f_role_id(0), f_ind_seq(0) {}
    recIndividualEvent( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recIndividualEvent( const recIndividualEvent& pe );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recIndividualEvent& r2 ) const;

    idt FGetHigherID() const { return f_higher_id; }
    idt FGetIndID() const { return f_ind_id; }
    idt FGetEventID() const { return f_event_id; }
    idt FGetRoleID() const { return f_role_id; }
    wxString FGetNote() const { return f_note; }
    int FGetIndSeq() const { return f_ind_seq; }

    void FSetHigherID( idt ieID ) { f_higher_id = ieID; }
    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetEventID( idt eventID ) { f_event_id = eventID; }
    void FSetRoleID( idt roleID ) { f_role_id = roleID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetIndSeq( int indSeq ) { f_ind_seq = indSeq; }

    static wxString GetIdStr( idt ieID ) { return wxString::Format( "IE" ID, ieID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static idt Create( idt indID, idt eID, idt roleID, const wxString& note = wxEmptyString );

    bool Find( idt indID, idt eveID, idt roleID = 0, const wxString& dbname = "Main" );

    static recIdVec GetLowerIndEventIDs( idt ieID, const wxString& dbname = "Main" );
    recIdVec GetLowerIndEventIDs( const wxString& dbname = "Main" ) const {
        return GetLowerIndEventIDs( f_id, dbname ); }
    static recIndEventVec GetLowerIndEvents( idt ieID, const wxString& dbname = "Main" );
    recIndEventVec GetLowerIndEvents( const wxString& dbname = "Main" ) const {
        return GetLowerIndEvents( f_id, dbname ); }

    static wxString GetRoleStr( idt indID, idt typeID, const wxString& dbname = "Main" );
    wxString GetRoleStr( idt typeID, const wxString& dbname = "Main" ) const {
        return GetRoleStr( f_ind_id, typeID, dbname ); }

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id, const wxString& dbname = "Main" );
    bool CsvRead( std::istream& in );
};

#endif // REC_RECINDEVENT_H
