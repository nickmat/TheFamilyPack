/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 IndividualEvent records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015 ~ 2016, Nick Matthews.
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

class recIndividualEvent : public recDb
{
public:
    idt      f_ind_id;
    idt      f_higher_id;
    idt      f_event_id;
    idt      f_role_id;
    wxString f_note;
    int      f_ind_seq;

    recIndividualEvent() {}
    recIndividualEvent( idt id ) : recDb(id) { Read(); }
    recIndividualEvent( const recIndividualEvent& pe );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "IndividualEvent" );

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

    static wxString GetIdStr( idt ieID ) { return wxString::Format( "IE"ID, ieID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static idt Create( idt indID, idt eID, idt roleID, const wxString& note = wxEmptyString );

    bool Find( idt indID, idt eveID, idt roleID = 0 );

    static recIdVec GetLowerIndEventIDs( idt ieID );
    recIdVec GetLowerIndEventIDs() const { return GetLowerIndEventIDs( f_id ); }
    static recIndEventVec GetLowerIndEvents( idt ieID );
    recIndEventVec GetLowerIndEvents() const { return GetLowerIndEvents( f_id ); }

    static wxString GetRoleStr( idt indID, idt typeID );
    wxString GetRoleStr( idt typeID ) const { return GetRoleStr( f_ind_id, typeID ); }
};

inline bool recEquivalent( const recIndividualEvent& r1, const recIndividualEvent& r2 )
{
    return
        r1.f_higher_id == r2.f_higher_id &&
        r1.f_ind_id    == r2.f_ind_id    &&
        r1.f_event_id  == r2.f_event_id  &&
        r1.f_role_id   == r2.f_role_id   &&
        r1.f_note      == r2.f_note      &&
        r1.f_ind_seq   == r2.f_ind_seq
    ;
}

inline bool operator==( const recIndividualEvent& r1, const recIndividualEvent& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recIndividualEvent& r1, const recIndividualEvent& r2 )
{
    return !(r1 == r2);
}


#endif // REC_RECINDEVENT_H
