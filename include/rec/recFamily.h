/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamily.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     8th January 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef RECFAMILY_H
#define RECFAMILY_H

#include <rec/recDatabase.h>

#include <rec/recFamilyIndividual.h>


class recFamily;
typedef std::vector< recFamily >  recFamilyVec;

//============================================================================
//-------------------------[ recFamily ]--------------------------------------
//============================================================================

class recFamily : public recDbT<recFamily>
{
public:
    static constexpr const char* s_tablename = "Family";
    static constexpr recTable s_table = recTable::Family;

    idt     f_husb_id;
    idt     f_wife_id;

    recFamily() : f_husb_id(0), f_wife_id(0) {}
    recFamily( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recFamily( const recFamily& family );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recFamily& r2 ) const;

    idt FGetHusbID() const { return f_husb_id; }
    idt FGetWifeID() const { return f_wife_id; }

    void FSetHusbID( idt hID ) { f_husb_id = hID; }
    void FSetWifeID( idt wID ) { f_wife_id = wID; }

    static wxString GetIdStr( idt indID ) { return wxString::Format( "F" ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    recIdVec GetCoupleAsIdVec() const;
    static recIdVec GetCoupleAsIdVec( idt famID, const wxString& dbname = "Main" );

    static recIdVec GetFamilyIdVec( const wxString& dbname = "Main" );
    static recFamilyVec GetFamilyVec( const wxString& dbname = "Main" );

    bool Decode( const wxString& str, const wxString& dbname = "Main" );

    static idt GetUnionEvent( idt famID, const wxString& dbname = "Main" );
    idt GetUnionEvent( const wxString& dbname = "Main" ) const {
        return GetUnionEvent( f_id, dbname ); }

    idt GetSpouseID( idt indID ) const;
    static idt Find( idt ind1ID, idt ind2ID, const wxString& dbname = "Main" );
    void Find( const wxString& dbname = "Main" ) {
        f_id = Find( f_husb_id, f_wife_id, dbname ); Read( dbname ); }
    static recIdVec FindVec(
        const recIdVec& ind1IDs, const recIdVec& ind2IDs, const wxString& dbname = "Main" );

    bool ReadParents( idt indID, const wxString& dbname = "Main" );
    static recFamilyVec GetFamilyList( idt indID, const wxString& dbname = "Main" );
    static recFamilyVec GetParentList( idt indID, const wxString& dbname = "Main" );

    static recIdVec GetChildrenIds( idt famID, const wxString& dbname = "Main" );
    recIdVec GetChildrenIds( const wxString& dbname = "Main" ) const {
        return GetChildrenIds( f_id, dbname ); }
    static int GetChildCount( idt famID, const wxString& dbname = "Main" );
    int GetChildCount( const wxString& dbname = "Main" ) const {
        return GetChildCount( f_id, dbname ); }
    static int GetChildNextSequence( idt famID, const wxString& dbname = "Main" );
    static int GetParentNextSequence( idt indID, const wxString& dbname = "Main" );
    recFamIndVec GetChildLinks( const wxString& dbname = "Main" ) {
        return GetChildLinks( f_id, dbname ); }
    static recFamIndVec GetChildLinks( idt famID, const wxString& dbname = "Main" );
    static recFamilyEventVec GetEvents( idt famID, const wxString& dbname = "Main" );
    recFamilyEventVec GetEvents( const wxString& dbname = "Main" ) const {
        return GetEvents( f_id, dbname ); }
    static recIdVec GetEventIDs( idt famID, const wxString& dbname = "Main" );
    recIdVec GetEventIDs( const wxString& dbname = "Main" ) const {
        return GetEventIDs( f_id, dbname ); }

    static int GetMaxEventSeqNumber( idt famID, const wxString& dbname = "Main" );
    int GetMaxEventSeqNumber( const wxString& dbname = "Main" ) const {
        return GetMaxEventSeqNumber( f_id, dbname ); }

    bool IsSingleton( const wxString& dbname = "Main" ) const;
    static bool IsSingleton( idt famID, const wxString& dbname = "Main" ) {
        recFamily fam( famID, dbname );
        return fam.IsSingleton( dbname );
    }

    static idt FindOrCreate( idt ind1ID, idt ind2ID, const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void RemoveFromEvents( idt famID, idt indID, const wxString& dbname = "Main" );
    void RemoveFromEvents( idt indID, const wxString& dbname = "Main" ) const {
        RemoveFromEvents( f_id, indID, dbname ); }

    static void RemoveFromDatabase( idt famID, const wxString& dbname = "Main" );
    void RemoveFromDatabase( const wxString& dbname = "Main" ) {
        RemoveFromDatabase( f_id, dbname ); }
};


#endif // RECFAMILY_H
