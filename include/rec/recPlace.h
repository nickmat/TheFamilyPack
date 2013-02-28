/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPlace.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Place, PlacePart and PlacePartType.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#ifndef RECPLACE_H
#define RECPLACE_H


#include <rec/recDatabase.h>

class recPlace;
typedef std::vector< recPlace > recPlaceVec;
class recPlacePart;
typedef std::vector< recPlacePart > recPlacePartVec;

enum {
    recP_FILTER_None      = 0x0000,
    recP_FILTER_Reference = 0x0001,
};

class recPlace : public recDb
{
public:
    idt  f_date1_id;
    idt  f_date2_id;

    recPlace() {}
    recPlace( idt id ) : recDb(id) { Read(); }
    recPlace( const recPlace& place );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Place" );

    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    void FSetDate1ID( idt dateID ) { f_date1_id = dateID; }
    void FSetDate2ID( idt dateID ) { f_date2_id = dateID; }

    idt GetDate1ID() const { return f_date1_id; }
    idt GetDate2ID() const { return f_date2_id; }

    static wxString GetIdStr( idt indID ) { return wxString::Format( "P"ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    void SetAddress( const wxString& str ) { return SetAddress( f_id, str ); }
    static void SetAddress( idt placeID, const wxString& str );
    static idt Create( const wxString& str );

    wxString GetAddressStr() const { return GetAddressStr( f_id ); }
    static wxString GetAddressStr( idt id );

    recPlacePartVec GetPlaceParts() const { return GetPlaceParts( f_id ); }
    static recPlacePartVec GetPlaceParts( idt placeID );

    static void RemoveDates( idt dateID );
    static void RemoveFromDatabase( idt placeID );

    static void DeleteIfOrphaned( idt placeID );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recPlace& r1, const recPlace& r2 )
{
    return
        r1.f_date1_id == r2.f_date1_id &&
        r1.f_date2_id == r2.f_date2_id;
}

inline bool operator==( const recPlace& r1, const recPlace& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recPlace& r1, const recPlace& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------


class recPlacePart : public recDb
{
public:
    idt      f_type_id;
    idt      f_place_id;
    wxString f_val;
    int      f_sequence;

    recPlacePart() {}
    recPlacePart( idt id ) : recDb(id) { Read(); }
    recPlacePart( const recPlacePart& pp );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "PlacePart" );

    idt FGetTypeID() const { return f_type_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetValue() const { return f_val; }
    int FGetSequence() const { return f_sequence; }

    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetValue( const wxString& value ) { f_val = value; }
    void FSetSequence( int seq ) { f_sequence = seq; }
};

inline bool recEquivalent( const recPlacePart& r1, const recPlacePart& r2 )
{
    return
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_place_id == r2.f_place_id &&
        r1.f_val      == r2.f_val      &&
        r1.f_sequence == r2.f_sequence;
}

inline bool operator==( const recPlacePart& r1, const recPlacePart& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recPlacePart& r1, const recPlacePart& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------


class recPlacePartType : public recDb
{
public:
    enum Type {
        TYPE_Address = -1,
        TYPE_MAX = 1  // Number of entries
    };

    wxString f_name;

    recPlacePartType() {}
    recPlacePartType( idt id ) : recDb(id) { Read(); }
    recPlacePartType( const recPlacePartType& ppt );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "PlacePartType" );

    wxString FGetName() const { return f_name; }

    void FSetName( const wxString& name ) { f_name = name; }
};

inline bool recEquivalent( const recPlacePartType& r1, const recPlacePartType& r2 )
{
    return
        r1.f_name == r2.f_name;
}

inline bool operator==( const recPlacePartType& r1, const recPlacePartType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recPlacePartType& r1, const recPlacePartType& r2 )
{
    return !(r1 == r2);
}


#endif // RECPLACE_H
