/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recIndPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 IndividualPersona table.
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

#ifndef REC_RECINDPERSONA_H
#define REC_RECINDPERSONA_H

#include <rec/recDatabase.h>
#include <rec/recEvent.h>

//============================================================================
//-------------------------[ recIndividualPersona ]---------------------------
//============================================================================

class recIndividualPersona : public recDbT<recIndividualPersona>
{
public:
    static constexpr const char* s_tablename = "IndividualPersona";
    static constexpr recTable s_table = recTable::IndividualPersona;

    idt      f_ind_id;
    idt      f_per_id;
    double   f_conf;
    wxString f_note;

    recIndividualPersona() : f_ind_id(0), f_per_id(0), f_conf(0.0) {}
    recIndividualPersona( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recIndividualPersona( const recIndividualPersona& link );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recIndividualPersona& r2 ) const;

    idt FGetIndID() const { return f_ind_id; }
    idt FGetPerID() const { return f_per_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt ipaID ) { return PrefixId( ipaID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    bool Find( const wxString& dbname = "Main" );
};

#endif // REC_RECINDPERSONA_H
