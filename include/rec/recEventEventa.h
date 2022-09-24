/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventEventa records.
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

#ifndef REC_RECEVENTEVENTA_H
#define REC_RECEVENTEVENTA_H

#include <rec/recDatabase.h>


//============================================================================
//--------------------------[ recEventEventa ]--------------------------------
//============================================================================

class recEventEventa : public recDbT<recEventEventa>
{
    idt      f_event_id;
    idt      f_eventa_id;
    double   f_conf;
    wxString f_note;

public:
    static constexpr const char* s_tablename = "EventEventa";
    static constexpr recTable s_table = recTable::EventEventa;

    recEventEventa() : f_event_id(0), f_eventa_id(0), f_conf(0.0) {}
    recEventEventa( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read(dbname); }
    recEventEventa( const recEventEventa& link );
//    recEventEventa( idt eID, idt eaID, double conf = 0.999, const wxString& note = "" )
//        : recDbT(0), f_event_id(eID), f_eventa_id(eaID), f_conf(conf), f_note(note) {}

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recEventEventa& r2 ) const;

    idt FGetEventID() const { return f_event_id; }
    idt FGetEventaID() const { return f_eventa_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetEventID( idt eveID ) { f_event_id = eveID; }
    void FSetEventaID( idt erID ) { f_eventa_id = erID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt eerID ) { return wxString::Format( "EEa" ID, eerID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( 
        idt eID, idt erID, double conf = 0.999, const wxString& note = "",
        const wxString& dbname = "Main" );

    // Ensure all corresponding IndividualEvent links exist, create if not. 
    void NormaliseIndEventLinks( const wxString& dbname = "Main" ) const;

    bool Find( const wxString& dbname = "Main" );
    static idt Find( idt eID, idt erID, const wxString& dbname = "Main" );
};

typedef std::vector< recEventEventa > recEventEventaVec;

#endif // REC_RECEVENTEVENTA_H
