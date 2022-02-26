/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPlace.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Place, PlacePart and PlacePartType.
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

class recPlace : public recDbT<recPlace>
{
public:
    static constexpr const char* s_tablename = "Place";

    idt  f_date1_id;
    idt  f_date2_id;

    recPlace() : f_date1_id(0), f_date2_id(0) {}
    recPlace( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recPlace( const recPlace& place );

    void Clear();
    void Save();
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recPlace& r2 ) const;

    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    void FSetDate1ID( idt dateID ) { f_date1_id = dateID; }
    void FSetDate2ID( idt dateID ) { f_date2_id = dateID; }

    idt GetDate1ID() const { return f_date1_id; }
    idt GetDate2ID() const { return f_date2_id; }

    static wxString GetIdStr( idt indID ) { return wxString::Format( "P" ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    void SetAddress( const wxString& str ) { return SetAddress( f_id, str ); }
    static void SetAddress( idt placeID, const wxString& str );
    static idt Create( const wxString& str );
    static idt Create( idt placeID ); // Clone

    wxString GetAddressStr( const wxString& dbname = "Main" ) const {
        return GetAddressStr( f_id, dbname ); }
    static wxString GetAddressStr( idt id, const wxString& dbname = "Main" );

    recPlacePartVec GetPlaceParts( const wxString& dbname = "Main" ) const {
        return GetPlaceParts( f_id, dbname ); }
    static recPlacePartVec GetPlaceParts( idt placeID, const wxString& dbname = "Main" );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void RemoveDates( idt dateID );
    static void RemoveFromDatabase( idt placeID );

    static void DeleteIfOrphaned( idt placeID, const wxString& dbname = "Main" );
};


//----------------------------------------------------------

class recPlacePart : public recDbT<recPlacePart>
{
public:
    static constexpr const char* s_tablename = "PlacePart";

    idt      f_type_id;
    idt      f_place_id;
    wxString f_val;
    int      f_sequence;

    recPlacePart() : f_type_id(0), f_place_id(0), f_sequence(0) {}
    recPlacePart( idt id ) : recDbT(id) { Read(); }
    recPlacePart( const recPlacePart& pp );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recPlacePart& r2 ) const;

    idt FGetTypeID() const { return f_type_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetValue() const { return f_val; }
    int FGetSequence() const { return f_sequence; }

    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetValue( const wxString& value ) { f_val = value; }
    void FSetSequence( int seq ) { f_sequence = seq; }

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};


//----------------------------------------------------------

class recPlacePartType : public recDbT<recPlacePartType>
{
public:
    static constexpr const char* s_tablename = "PlacePartType";

    enum Type {
        TYPE_Address = -1,
        TYPE_MAX = 1  // Number of entries
    };

    wxString f_name;

    recPlacePartType() {}
    recPlacePartType( idt id ) : recDbT(id) { Read(); }
    recPlacePartType( const recPlacePartType& ppt );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recPlacePartType& r2 ) const {
        return f_name == r2.f_name;
    }

    wxString FGetName() const { return f_name; }

    void FSetName( const wxString& name ) { f_name = name; }

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};


#endif // RECPLACE_H
