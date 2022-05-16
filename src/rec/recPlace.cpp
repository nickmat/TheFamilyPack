/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recPlace.h>

#include <rec/recEvent.h>
#include <rec/recReference.h>


recPlace::recPlace( const recPlace& p )
{
    f_id       = p.f_id;
    f_date1_id = p.f_date1_id;
    f_date2_id = p.f_date2_id;
}

void recPlace::Clear()
{
    f_id       = 0;
    f_date1_id = 0;
    f_date2_id = 0;
}

void recPlace::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Place (date1_id, date2_id)"
            " VALUES (" ID ", " ID ");",
            UTF8_( dbname ), f_date1_id, f_date2_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Place (id, date1_id, date2_id)"
                " VALUES (" ID ", " ID ", " ID ");",
                UTF8_( dbname ), f_id, f_date1_id, f_date2_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Place SET date1_id=" ID ", date2_id=" ID
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_date1_id, f_date2_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recPlace::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT * FROM \"%s\".Place WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_date1_id = GET_ID( result.GetInt64( 1 ) );
    f_date2_id = GET_ID( result.GetInt64( 2 ) );
    return true;
}

bool recPlace::Equivalent( const recPlace& r2 ) const
{
    return
        f_date1_id == r2.f_date1_id &&
        f_date2_id == r2.f_date2_id
    ;
}

void recPlace::SetAddress( idt placeID, const wxString& str )
{
    recPlacePartVec ppList = GetPlaceParts( placeID );
    if( ppList.size() == 0 )
    {
        recPlacePart pp;
        pp.Clear();
        pp.f_type_id = recPlacePartType::TYPE_Address;
        pp.f_place_id = placeID;
        pp.f_val = str;
        pp.Save();
    } else {
        ppList[0].f_type_id = recPlacePartType::TYPE_Address;
        ppList[0].f_val = str;
        ppList[0].Save();
        for( size_t i = 1 ; i < ppList.size() ; i++ ) {
            ppList[i].Delete();
        }
    }
}

idt recPlace::Create( const wxString& str )
{
    recPlace place(0);
    place.Save();
    place.SetAddress( str );
    return place.FGetID();
}

idt recPlace::Create( idt placeID )
{
    if( placeID == 0 ) {
        return 0;
    }
    return Create( GetAddressStr( placeID ) );
}

wxString recPlace::GetAddressStr( idt id, const wxString& dbname )
{
    if( id == 0 ) return wxEmptyString;

    wxString str;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    sql.Format(
        "SELECT val FROM \"%s\".PlacePart WHERE place_id=" ID " "
        "ORDER BY sequence;", UTF8_( dbname ), id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() > 0 )
    {
        for( int row = 0 ; row < result.GetRowCount() ; row++ )
        {
            if( row > 0 )
            {
                str << wxT(", ");
            }
            result.SetRow( row );
            str << result.GetAsString( 0 );
        }
    }
    return str;
}

recPlacePartVec recPlace::GetPlaceParts(
    idt placeID, const wxString& dbname )
{
    wxString str;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    recPlacePart pp;
    recPlacePartVec ppList;

    sql.Format(
        "SELECT * FROM \"%s\".PlacePart"
        " WHERE place_id=" ID " ORDER BY sequence;",
        UTF8_( dbname ), placeID
    );
    result = s_db->GetTable( sql );

    for( int row = 0 ; row < result.GetRowCount() ; row++ )
    {
        result.SetRow( row );
        pp.f_id       = GET_ID( result.GetInt64( 0 ) );
        pp.f_type_id  = GET_ID( result.GetInt64( 1 ) );
        pp.f_place_id = GET_ID( result.GetInt64( 2 ) );
        pp.f_val      = result.GetAsString( 3 );
        pp.f_sequence = result.GetInt( 4 );
        ppList.push_back( pp );
    }
    return ppList;
}

recIdVec recPlace::GetPlacePartIDs( idt placeID, const wxString& dbname )
{
    return ExecuteIdVec(
        "SELECT id FROM \"%s\".PlacePart WHERE place_id=" ID
        " ORDER BY sequence;",
        UTF8_( dbname ), placeID
    );
}

void recPlace::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE PlacePart SET place_id=" ID " WHERE place_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Event SET place_id=" ID " WHERE place_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Eventa SET place_id=" ID " WHERE place_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE ReferenceEntity SET entity_id=" ID
        " WHERE entity_type=3 AND entity_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Place SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recPlace::CsvTitles()
{
    return std::string(
        "ID, Start Date, End Date\n"
    );
}

void recPlace::CsvWrite( std::ostream& out, idt id )
{
    recPlace place( id );
    recCsvWrite( out, place.FGetID() );
    recCsvWrite( out, place.FGetDate1ID() );
    recCsvWrite( out, place.FGetDate2ID(), '\n' );
}

bool recPlace::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_date1_id );
    recCsvRead( in, f_date2_id );
    return bool( in );
}

void recPlace::RemoveDates( idt dateID )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Place SET date1_id=0 WHERE date1_id=" ID ";"
        "UPDATE Place SET date2_id=0 WHERE date2_id=" ID ";",
        dateID, dateID
    );
    s_db->ExecuteUpdate( sql );
}

void recPlace::RemoveFromDatabase( idt placeID )
{
    recEvent::RemovePlace( placeID );

    recPlacePartVec parts = recPlace::GetPlaceParts( placeID );
    for( size_t i = 0 ; i < parts.size() ; i++ ) {
        parts[i].Delete();
    }
    recReferenceEntity::DeleteType( recReferenceEntity::TYPE_Place, placeID );
    Delete( placeID );
}

void recPlace::DeleteIfOrphaned( idt id, const wxString& dbname )
{
    if( id <= 0 ) {
        // Don't delete universal places.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format( 
        "SELECT COUNT(*) FROM \"%s\".Event WHERE place_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Eventa WHERE place_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    // TODO: Ensure Place is removed from reference statement.
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".ReferenceEntity"
        " WHERE entity_type=3 AND entity_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    recPlacePartVec pps = GetPlaceParts( id, dbname );
    for( size_t i = 0 ; i < pps.size() ; i++ ) {
        pps[i].Delete( dbname );
    }
    recPlace place( id, dbname );
    place.Delete( dbname );
    recDate::DeleteIfOrphaned( place.f_date1_id, dbname );
    recDate::DeleteIfOrphaned( place.f_date2_id, dbname );
}

//----------------------------------------------------------

recPlacePart::recPlacePart( const recPlacePart& pp )
{
    f_id       = pp.f_id;
    f_type_id  = pp.f_type_id;
    f_place_id = pp.f_place_id;
    f_val      = pp.f_val;
    f_sequence = pp.f_sequence;
}

void recPlacePart::Clear()
{
    f_id       = 0;
    f_type_id  = 0;
    f_place_id = 0;
    f_val      = wxEmptyString;
    f_sequence = 0;
}

void recPlacePart::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".PlacePart (type_id, place_id, val, sequence)"
            " VALUES (" ID ", " ID ", '%q', %u);",
            UTF8_( dbname ), f_type_id, f_place_id, UTF8_(f_val), f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".PlacePart (id, type_id, place_id, val, sequence)"
                " VALUES (" ID ", " ID ", " ID ", '%q', %u);",
                UTF8_( dbname ), f_id, f_type_id, f_place_id, UTF8_(f_val), f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".PlacePart"
                " SET type_id=" ID ", place_id=" ID ", val='%q', sequence=%u"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_type_id, f_place_id, UTF8_(f_val), f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recPlacePart::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT type_id, place_id, val, sequence"
        " FROM \"%s\".PlacePart WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_type_id  = GET_ID( result.GetInt64( 0 ) );
    f_place_id = GET_ID( result.GetInt64( 1 ) );
    f_val      = result.GetAsString( 2 );
    f_sequence = result.GetInt( 3 );
    return true;
}

bool recPlacePart::Equivalent( const recPlacePart& r2 ) const
{
    return
        f_type_id == r2.f_type_id &&
        f_place_id == r2.f_place_id &&
        f_val == r2.f_val &&
        f_sequence == r2.f_sequence
    ;
}

void recPlacePart::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE PlacePart SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recPlacePart::CsvTitles()
{
    return std::string( "ID, Type ID, Place ID, Value, Sequence\n" );
}

void recPlacePart::CsvWrite( std::ostream& out, idt id )
{
    recPlacePart pp( id );
    recCsvWrite( out, pp.FGetID() );
    recCsvWrite( out, pp.FGetTypeID() );
    recCsvWrite( out, pp.FGetPlaceID() );
    recCsvWrite( out, pp.FGetValue() );
    recCsvWrite( out, pp.FGetSequence(), '\n' );
}

bool recPlacePart::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_type_id );
    recCsvRead( in, f_place_id );
    recCsvRead( in, f_val );
    recCsvRead( in, f_sequence );
    return bool( in );
}

//----------------------------------------------------------

recPlacePartType::recPlacePartType( const recPlacePartType& ppt )
{
    f_id   = ppt.f_id;
    f_name = ppt.f_name;
    f_uid = ppt.f_uid;
    f_changed = ppt.f_changed;
}

void recPlacePartType::Clear()
{
    f_id   = 0;
    f_name.clear();
    f_uid.clear();
    f_changed = 0;
}

void recPlacePartType::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".PlacePartType (name, uid, changed) VALUES ('%q', '%q', %ld);",
            UTF8_( dbname ), UTF8_( f_name ), UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    }
    else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".PlacePartType (id, name, uid, changed) "
                "VALUES (" ID ", '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, UTF8_( f_name ), UTF8_( f_uid ), f_changed
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".PlacePartType SET name='%q', uid='%q', changed=%ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_( f_name ), UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recPlacePartType::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, uid, changed FROM \"%s\".PlacePartType WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name = result.GetAsString( 0 );
    f_uid = result.GetAsString( 1 );
    f_changed = result.GetInt( 2 );
    return true;
}

bool recPlacePartType::Equivalent( const recPlacePartType& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

void recPlacePartType::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE PlacePart SET type_id=" ID " WHERE type_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE PlacePartType SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recPlacePartType::CsvTitles()
{
    return std::string( "ID, Name, UID, Last Changed\n" );
}

void recPlacePartType::CsvWrite( std::ostream& out, idt id )
{
    recPlacePartType ppt( id );
    recCsvWrite( out, ppt.FGetID() );
    recCsvWrite( out, ppt.FGetName() );
    recCsvWrite( out, ppt.FGetUid() );
    recCsvWrite( out, ppt.FGetChanged(), '\n' );
}

bool recPlacePartType::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

// End of recPlace.cpp file
