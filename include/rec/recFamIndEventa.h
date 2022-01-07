/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamIndEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyIndEventa records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th April 2015
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

#ifndef REC_RECFAMINDEVENTA_H
#define REC_RECFAMINDEVENTA_H

#include <rec/recDatabase.h>

class recFamilyIndEventa;
typedef std::vector< recFamilyIndEventa >   recFamilyIndEventaVec;

//============================================================================
//--------------------------[ recFamilyIndEventa ]----------------------------
//============================================================================

class recFamilyIndEventa : public recDbT<recFamilyIndEventa>
{
    idt      f_fam_ind_id;
    idt      f_eventa_id;
    double   f_conf;
    wxString f_note;

public:
    static constexpr const char* s_tablename = "FamilyIndEventa";

    recFamilyIndEventa() : f_fam_ind_id(0), f_eventa_id(0), f_conf(0.0) {}
    recFamilyIndEventa( idt id ) : recDbT(id) { Read(); }
    recFamilyIndEventa( const recFamilyIndEventa& link );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recFamilyIndEventa& r2 ) const;

    idt FGetFamIndID() const { return f_fam_ind_id; }
    idt FGetEventaID() const { return f_eventa_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetFamIndID( idt fiID ) { f_fam_ind_id = fiID; }
    void FSetEventaID( idt eaID ) { f_eventa_id = eaID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt fieaID ) { return wxString::Format( "FIEa" ID, fieaID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( idt fiID, idt eaID, double conf = 0.999, const wxString& note = wxEmptyString );

    bool Find();
    static idt Find( idt fiID, idt eaID );
};

#endif // REC_RECFAMINDEVENTA_H
