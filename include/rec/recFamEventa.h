/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyEventa records.
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

#ifndef REC_RECFAMEVENTA_H
#define REC_RECFAMEVENTA_H

#include <rec/recDatabase.h>

class recFamilyEventa;
typedef std::vector< recFamilyEventa >   recFamilyEventaVec;

//============================================================================
//--------------------------[ recFamilyEventa ]-------------------------------
//============================================================================

class recFamilyEventa : public recDbT<recFamilyEventa>
{
    idt      f_fam_id;
    idt      f_eventa_id;
    double   f_conf;
    wxString f_note;

public:
    static constexpr const char* s_tablename = "FamilyEventa";
    static constexpr recTable s_table = recTable::FamilyEventa;

    recFamilyEventa() : f_fam_id(0), f_eventa_id(0), f_conf(0.0) {}
    recFamilyEventa( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recFamilyEventa( const recFamilyEventa& link );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recFamilyEventa& r2 ) const;

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

    bool Find( const wxString& dbname = "Main" );
    static idt Find( idt famID, idt eaID, const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};


#endif // REC_RECFAMEVENTA_H
