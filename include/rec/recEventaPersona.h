/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventaPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventaPersona records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015 ~ 2017, Nick Matthews.
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

#ifndef REC_RECEVENTAPERSONA_H
#define REC_RECEVENTAPERSONA_H

#include <rec/recDatabase.h>

//============================================================================
//--------------------------[ recEventaPersona ]------------------------------
//============================================================================

class recEventaPersona : public recDb
{
public:
    idt      f_eventa_id;
    idt      f_per_id;
    idt      f_role_id;
    wxString f_note;
    int      f_per_seq;

    recEventaPersona() {}
    recEventaPersona( idt id ) : recDb(id) { Read(); }
    recEventaPersona( const recEventaPersona& pe );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventaPersona" );

    idt FGetEventaID() const { return f_eventa_id; }
    idt FGetPerID() const { return f_per_id; }
    idt FGetRoleID() const { return f_role_id; }
    wxString FGetNote() const { return f_note; }
    int FGetPerSeq() const { return f_per_seq; }

    void FSetEventaID( idt erID ) { f_eventa_id = erID; }
    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetRoleID( idt roleID ) { f_role_id = roleID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetPerSeq( int perSeq ) { f_per_seq = perSeq; }

    static wxString GetIdStr( idt epID ) { return wxString::Format( "EP" ID, epID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static wxString GetRoleStr( idt perID, idt typeID );
    wxString GetRoleStr( idt typeID ) const { return GetRoleStr( f_per_id, typeID ); }

    /*! Return true if a record exists that matches the
     *  f_per_id, f_event_id and f_role_id.
     */
    bool LinkExists() const;
};

inline bool recEquivalent( const recEventaPersona& r1, const recEventaPersona& r2 )
{
    return
        r1.f_eventa_id == r2.f_eventa_id &&
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_role_id  == r2.f_role_id  &&
        r1.f_note     == r2.f_note     &&
        r1.f_per_seq  == r2.f_per_seq;
}

inline bool operator==( const recEventaPersona& r1, const recEventaPersona& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEventaPersona& r1, const recEventaPersona& r2 )
{
    return !(r1 == r2);
}

typedef std::vector< recEventaPersona >   recEventaPersonaVec;

#endif // REC_RECEVENTAPERSONA_H
