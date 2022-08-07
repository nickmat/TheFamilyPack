/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Persona records.
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

#ifndef RECPERSONA_H
#define RECPERSONA_H

#include <rec/recDatabase.h>
#include <rec/recReference.h>
#include <rec/recName.h>
#include <rec/recEvent.h>
#include <rec/recEventaPersona.h>

class recPersona;
typedef std::vector< recPersona >  recPersonaVec;


enum recEventOrder {
    recEO_DatePt,
    recEO_PerSeq,
    recEO_FamSeq
};

class recPersona : public recDbT<recPersona>, public recUidT<recPersona>
{
public:
    static constexpr const char* s_tablename = "Persona";

    Sex      f_sex;
    idt      f_ref_id;
    wxString f_note;

    recPersona() : f_sex( Sex::unstated ), f_ref_id(0) {}
    recPersona( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recPersona( const recPersona& persona );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recPersona& r2 ) const;

    Sex FGetSex() const { return f_sex; }
    idt FGetRefID() const { return f_ref_id; }
    wxString FGetNote() const { return f_note; }

    void FSetSex( Sex sex ) { f_sex = sex; }
    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt perID ) { return wxString::Format( "Pa" ID, perID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( idt refID, Sex sex = Sex::unstated );

    static Sex GetSex( idt id, const wxString& dbname = "Main" );
    static idt GetRefID( idt id, const wxString& dbname = "Main" );

    static idt GetNameID( idt perID ) { return recName::GetDefaultNameID( 0, perID ); }
    idt GetNameID() const { return recName::GetDefaultNameID( 0, f_id ); }
    static wxString GetNameStr( idt perID, const wxString& dbname = "Main" ) {
        return recName::GetDefaultNameStr( 0, perID, dbname ); }
    wxString GetNameStr( const wxString& dbname = "Main" ) const {
        return recName::GetDefaultNameStr( 0, f_id, dbname ); }

    static recNameVec ReadNames( idt perID, const wxString& dbname = "Main" );
    recNameVec ReadNames( const wxString& dbname = "Main" ) const {
        return ReadNames( f_id, dbname ); }

    static recIdVec GetNameListID( idt perID, const wxString& dbname = "Main" );
    recIdVec GetNameListID( const wxString& dbname = "Main" ) const {
        return GetNameListID( f_id, dbname );
    }

    static recEventaPersonaVec ReadEventaPersonas(
        idt perID, recEventOrder order = recEO_DatePt, const wxString& dbname = "Main" );
    recEventaPersonaVec ReadEventaPersonas(
        recEventOrder order = recEO_DatePt, const wxString& dbname = "Main" ) const
        { return ReadEventaPersonas( f_id, order, dbname ); }

    static int GetMaxEventaSeqNumber( idt perID );
    int GetMaxEventaSeqNumber() const { return GetMaxEventaSeqNumber( f_id ); }

    // Get a list of linked to Individual's
    static recIdVec GetIndividualIDs( idt perID, const wxString& dbname = "Main" );
    recIdVec GetIndividualIDs( const wxString& dbname = "Main" ) const {
        return GetIndividualIDs( f_id, dbname ); }
    // Commer delimited string of linked Individual ID strings.
    static wxString GetIndividualIdStr( idt perID, const wxString& dbname = "Main" );
    wxString GetIndividualIdStr( const wxString& dbname = "Main" ) const {
        return GetIndividualIdStr( f_id, dbname ); }

    // Find all Persona ID's that link an Individual to a Reference
    static recIdVec FindIndividualReferenceLink(
        idt indID, idt refID, const wxString& dbname = "Main" );

    static recIdVec GetEventaPersonaIDs( idt eaID, const wxString& dbname = "Main" );
    recIdVec GetEventaPersonaIDs( const wxString& dbname = "Main" ) const {
        return GetEventaPersonaIDs( f_id, dbname );
    }

    static idt Transfer(
        idt from_perID, const wxString& fromdb, idt to_refID, const wxString& todb );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    // Delete Persona record and remove all records that reference it.
    bool RemoveFromDatabase( const wxString& dbname = "Main" );
    static bool RemoveFromDatabase( idt id, const wxString& dbname = "Main" );
};

#endif // RECPERSONA_H
