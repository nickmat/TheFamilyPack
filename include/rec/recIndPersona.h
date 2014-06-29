/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recIndPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 IndividualPersona table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010-2013, Nick Matthews.
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

#ifndef REC_RECINDPERSONA_H
#define REC_RECINDPERSONA_H

#include <rec/recDatabase.h>
#include <rec/recEvent.h>

//============================================================================
//-------------------------[ recIndividualPersona ]---------------------------
//============================================================================

class recIndividualPersona : public recDb
{
public:
    idt      f_ind_id;
    idt      f_per_id;
    double   f_conf;
    wxString f_note;

    recIndividualPersona() {}
    recIndividualPersona( idt id ) : recDb(id) { Read(); }
    recIndividualPersona( const recIndividualPersona& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "IndividualPersona" );

    idt FGetIndID() const { return f_ind_id; }
    idt FGetPerID() const { return f_per_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    bool Find();
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recIndividualPersona& d1, const recIndividualPersona& d2 )
{
    return
        d1.f_ind_id == d2.f_ind_id &&
        d1.f_per_id == d2.f_per_id &&
        d1.f_conf   == d2.f_conf   &&
        d1.f_note   == d2.f_note;
}

inline bool operator==( const recIndividualPersona& d1, const recIndividualPersona& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recIndividualPersona& d1, const recIndividualPersona& d2 )
{
    return !(d1 == d2);
}

#endif // REC_RECINDPERSONA_H
