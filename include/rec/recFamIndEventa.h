/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamIndEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyIndEventa records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th April 2015
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

#ifndef REC_RECFAMINDEVENTA_H
#define REC_RECFAMINDEVENTA_H

#include <rec/recDatabase.h>

//============================================================================
//--------------------------[ recFamilyIndEventa ]----------------------------
//============================================================================

class recFamilyIndEventa : public recDb
{
    idt      f_fam_ind_id;
    idt      f_eventa_id;
    double   f_conf;
    wxString f_note;

public:
    recFamilyIndEventa() {}
    recFamilyIndEventa( idt id ) : recDb(id) { Read(); }
    recFamilyIndEventa( const recFamilyIndEventa& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "FamilyIndEventa" );

    idt FGetFamIndID() const { return f_fam_ind_id; }
    idt FGetEventaID() const { return f_eventa_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetFamIndID( idt fiID ) { f_fam_ind_id = fiID; }
    void FSetEventaID( idt eaID ) { f_eventa_id = eaID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt fieaID ) { return wxString::Format( "FIEa"ID, fieaID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( idt fiID, idt eaID, double conf = 0.999, const wxString& note = wxEmptyString );

    bool Find();
    static idt Find( idt fiID, idt eaID );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recFamilyIndEventa& d1, const recFamilyIndEventa& d2 )
{
    return
        d1.FGetFamIndID()   == d2.FGetFamIndID()   &&
        d1.FGetEventaID()   == d2.FGetEventaID()   &&
        d1.FGetConf()       == d2.FGetConf()       &&
        d1.FGetNote()       == d2.FGetNote();
}

inline bool operator==( const recFamilyIndEventa& d1, const recFamilyIndEventa& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recFamilyIndEventa& d1, const recFamilyIndEventa& d2 )
{
    return !(d1 == d2);
}

#endif // REC_RECFAMINDEVENTA_H
