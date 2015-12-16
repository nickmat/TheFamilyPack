/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyEvent records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015, Nick Matthews.
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

#ifndef REC_RECFAMEVENT_H
#define REC_RECFAMEVENT_H

#include <rec/recDatabase.h>


//============================================================================
//-------------------------[ recFamilyEvent ]---------------------------------
//============================================================================

class recFamilyEvent : public recDb
{
public:
    idt      f_fam_id;
    idt      f_event_id;
    wxString f_note;
    int      f_fam_seq;

    recFamilyEvent() {}
    recFamilyEvent( idt id ) : recDb(id) { Read(); }
    recFamilyEvent( const recFamilyEvent& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "FamilyEvent" );

    idt FGetFamID() const { return f_fam_id; }
    idt FGetEventID() const { return f_event_id; }
    wxString FGetNote() const { return f_note; }
    int FGetFamSeq() const { return f_fam_seq; }

    void FSetFamID( idt famID ) { f_fam_id = famID; }
    void FSetEventID( idt eventID ) { f_event_id = eventID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetFamSeq( int seq ) { f_fam_seq = seq; }

    static wxString GetIdStr( idt feID ) { return wxString::Format( "FE"ID, feID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static idt Create( idt eveID, idt famID, const wxString& note = wxEmptyString );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recFamilyEvent& r1, const recFamilyEvent& r2 )
{
    return
        r1.f_fam_id   == r2.f_fam_id   &&
        r1.f_event_id == r2.f_event_id &&
        r1.f_note     == r2.f_note     &&
        r1.f_fam_seq  == r2.f_fam_seq;
}

inline bool operator==( const recFamilyEvent& d1, const recFamilyEvent& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recFamilyEvent& d1, const recFamilyEvent& d2 )
{
    return !(d1 == d2);
}

typedef std::vector< recFamilyEvent >      recFamilyEventVec;

#endif // REC_RECFAMEVENT_H
