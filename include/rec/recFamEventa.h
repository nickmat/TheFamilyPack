/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyEventa records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th April 2015
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

#ifndef REC_RECFAMEVENTA_H
#define REC_RECFAMEVENTA_H

#include <rec/recDatabase.h>

class recFamilyEventa;
typedef std::vector< recFamilyEventa >   recFamilyEventaVec;

//============================================================================
//--------------------------[ recFamilyEventa ]-------------------------------
//============================================================================

class recFamilyEventa : public recDb
{
    idt      f_fam_id;
    idt      f_eventa_id;
    double   f_conf;
    wxString f_note;

public:
    recFamilyEventa() {}
    recFamilyEventa( idt id ) : recDb(id) { Read(); }
    recFamilyEventa( const recFamilyEventa& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "FamilyEventa" );

    idt FGetFamID() const { return f_fam_id; }
    idt FGetEventaID() const { return f_eventa_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetFamID( idt famID ) { f_fam_id = famID; }
    void FSetEventaID( idt eaID ) { f_eventa_id = eaID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt feaID ) { return wxString::Format( "FEa" ID, feaID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( idt famID, idt eaID, double conf = 0.999, const wxString& note = wxEmptyString );

    bool Find();
    static idt Find( idt famID, idt eaID );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recFamilyEventa& d1, const recFamilyEventa& d2 )
{
    return
        d1.FGetFamID()      == d2.FGetFamID()      &&
        d1.FGetEventaID()   == d2.FGetEventaID()   &&
        d1.FGetConf()       == d2.FGetConf()       &&
        d1.FGetNote()       == d2.FGetNote();
}

inline bool operator==( const recFamilyEventa& d1, const recFamilyEventa& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recFamilyEventa& d1, const recFamilyEventa& d2 )
{
    return !(d1 == d2);
}

#endif // REC_RECFAMEVENTA_H
