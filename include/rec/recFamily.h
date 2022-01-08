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

    idt     f_husb_id;
    idt     f_wife_id;

    recFamily() : f_husb_id(0), f_wife_id(0) {}
    recFamily( idt id ) : recDbT(id) { Read(); }
    recFamily( const recFamily& family );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recFamily& r2 ) const;

    idt FGetHusbID() const { return f_husb_id; }
    idt FGetWifeID() const { return f_wife_id; }

    void FSetHusbID( idt hID ) { f_husb_id = hID; }
    void FSetWifeID( idt wID ) { f_wife_id = wID; }

    static wxString GetIdStr( idt indID ) { return wxString::Format( "F" ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    recIdVec GetCoupleAsIdVec() const;
    static recIdVec GetCoupleAsIdVec( idt famID );

    static recIdVec GetFamilyIdVec();
    static recFamilyVec GetFamilyVec();

    bool Decode( const wxString& str );

    static idt GetUnionEvent( idt famID );
    idt GetUnionEvent() const { return GetUnionEvent( f_id ); }

    idt GetSpouseID( idt indID ) const;
    static idt Find( idt ind1ID, idt ind2ID );
    void Find() { f_id = Find( f_husb_id, f_wife_id ); Read(); }
    static recIdVec FindVec( const recIdVec& ind1IDs, const recIdVec& ind2IDs );

    bool ReadParents( idt indID );
    static recFamilyVec GetFamilyList( idt indID );
    static recFamilyVec GetParentList( idt indID );

    static recIdVec GetChildrenIds( idt famID );
    recIdVec GetChildrenIds() const { return GetChildrenIds( f_id ); }
    static int GetChildCount( idt famID );
    int GetChildCount() const { return GetChildCount( f_id ); }
    static int GetChildNextSequence( idt famID );
    static int GetParentNextSequence( idt indID );
    recFamIndVec GetChildLinks() { return GetChildLinks( f_id ); }
    static recFamIndVec GetChildLinks( idt famID );
    static recFamilyEventVec GetEvents( idt famID );
    recFamilyEventVec GetEvents() const { return GetEvents( f_id ); }
    static recIdVec GetEventIDs( idt famID );
    recIdVec GetEventIDs() const { return GetEventIDs( f_id ); }

    static int GetMaxEventSeqNumber( idt famID );
    int GetMaxEventSeqNumber() const { return GetMaxEventSeqNumber( f_id ); }

    bool IsSingleton() const;
    static bool IsSingleton( idt famID ) { recFamily fam(famID); return fam.IsSingleton(); }

    static idt FindOrCreate( idt ind1ID, idt ind2ID );

    static void RemoveFromEvents( idt famID, idt indID );
    void RemoveFromEvents( idt indID ) const { RemoveFromEvents( f_id, indID ); }

    static void RemoveFromDatabase( idt famID );
    void RemoveFromDatabase() { RemoveFromDatabase( f_id ); }
};


#endif // RECINDIVIDUAL_H
