/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventaPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventaPersona records.
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

#ifndef REC_RECEVENTAPERSONA_H
#define REC_RECEVENTAPERSONA_H

#include <rec/recDatabase.h>

//============================================================================
//--------------------------[ recEventaPersona ]------------------------------
//============================================================================

class recEventaPersona : public recDbT<recEventaPersona>
{
public:
    static constexpr const char* s_tablename = "EventaPersona";
    static constexpr recTable s_table = recTable::EventaPersona;

    idt      f_eventa_id;
    idt      f_per_id;
    idt      f_role_id;
    wxString f_note;
    int      f_per_seq;

    recEventaPersona() 
        : f_eventa_id(0), f_per_id(0), f_role_id(0), f_per_seq(0) {}
    recEventaPersona( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read(dbname); }
    recEventaPersona( const recEventaPersona& pe );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recEventaPersona& r2 ) const;

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

    static idt CreateLink( idt eaID, idt perID, idt roleID, const wxString& note = "" );
    void SetNextPerSequence( idt eaID );

    static wxString GetIdStr( idt epID ) { return PrefixId( epID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static wxString GetRoleStr( idt perID, idt typeID, const wxString& dbname = "Main" );
    wxString GetRoleStr( idt typeID, const wxString& dbname = "Main" ) const {
        return GetRoleStr( f_per_id, typeID, dbname ); }

    /*! Return true if a record exists that matches the
     *  f_per_id, f_event_id and f_role_id.
     */
    bool LinkExists( const wxString& dbname = "Main" ) const;

    static idt Transfer(
        idt from_eapaID, const wxString& fromdb,
        idt to_eaID, idt to_eapaID, const wxString& todb
    );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static bool RemoveFromDatabase( idt eapaID, const wxString& dbname = "Main" );
};

typedef std::vector< recEventaPersona >   recEventaPersonaVec;

#endif // REC_RECEVENTAPERSONA_H
