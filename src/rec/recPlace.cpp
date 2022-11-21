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
    f_uid = p.f_uid;
    f_changed = p.f_changed;
}

void recPlace::Clear()
{
    f_id       = 0;
    f_date1_id = 0;
    f_date2_id = 0;
    f_uid.clear();
    f_changed = 0;
}

void recPlace::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Place (date1_id, date2_id, uid, changed)"
            " VALUES (" ID ", " ID ", '%q', %ld);",
            UTF8_( dbname ), f_date1_id, f_date2_id, UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Place (id, date1_id, date2_id, uid, changed)"
                " VALUES (" ID ", " ID ", " ID ", '%q', %ld);",
                UTF8_( dbname ), f_id, f_date1_id, f_date2_id, UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Place SET date1_id=" ID ", date2_id=" ID ", uid = '%q', changed = %ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_date1_id, f_date2_id, UTF8_( f_uid ), f_changed, f_id
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
        "SELECT date1_id, date2_id, uid, changed FROM \"%s\".Place WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_date1_id = GET_ID( result.GetInt64( 0 ) );
    f_date2_id = GET_ID( result.GetInt64( 1 ) );
    f_uid = result.GetAsString( 2 );
    f_changed = result.GetInt( 3 );
    return true;
}

bool recPlace::Equivalent( const recPlace& r2 ) const
{
    return
        f_date1_id == r2.f_date1_id &&
        f_date2_id == r2.f_date2_id &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
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
    place.FSetUid( recCreateUid() );
    place.FSetChanged( calGetTodayJdn() );
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

idt recPlace::Transfer( idt from_placeID, const wxString& fromdb, const wxString& todb )
{
    if( from_placeID == 0 ) return 0;

    recPlace from_place( from_placeID, fromdb );

    idt to_placeID = from_placeID;
    if( to_placeID > 0 ) {
        to_placeID = recPlace::FindUid( from_place.FGetUid(), todb );
    }
    recPlace to_place( to_placeID, todb );

    recPlace new_place( 0 );
    new_place.FSetID( to_placeID );
    new_place.FSetDate1ID( recDate::Transfer( from_place.FGetDate1ID(), fromdb, todb ) );
    new_place.FSetDate2ID( recDate::Transfer( from_place.FGetDate2ID(), fromdb, todb ) );
    new_place.FSetUid( from_place.FGetUid() );
    recMatchUID match = from_place.CompareUID( to_place );
    if( match == recMatchUID::unequal || match == recMatchUID::younger ) {
        new_place.FSetChanged( from_place.FGetChanged() );
    }
    else {
        new_place.FSetChanged( to_place.FGetChanged() );
    }
    new_place.Save( todb );
    to_placeID = new_place.FGetID();

    recDate::DeleteIfOrphaned( to_place.FGetDate1ID(), todb );
    recDate::DeleteIfOrphaned( to_place.FGetDate2ID(), todb );

    recIdVec from_ppIDs = recPlace::GetPlacePartIDs( from_placeID, fromdb );
    recIdVec to_ppIDs = recPlace::GetPlacePartIDs( to_placeID, todb );
    size_t size = std::max( from_ppIDs.size(), to_ppIDs.size() );
    for( size_t i = 0; i < size; i++ ) {
        if( i >= from_ppIDs.size() ) { // No more to copy.
            recPlacePart::RemoveFromDatabase( to_ppIDs[i], todb );
            continue;
        }
        if( i >= to_ppIDs.size() ) {
            recPlacePart::Transfer( from_ppIDs[i], fromdb, to_placeID, 0, todb );
            continue;
        }
        recPlacePart::Transfer( from_ppIDs[i], fromdb, to_placeID, to_ppIDs[i], todb);
    }
    return to_placeID;
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
        "ID, Start Date, End Date, UID, Last Changed\n"
    );
}

void recPlace::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recPlace place( id, dbname );
    recCsvWrite( out, place.FGetID() );
    recCsvWrite( out, place.FGetDate1ID() );
    recCsvWrite( out, place.FGetDate2ID() );
    recCsvWrite( out, place.FGetUid() );
    recCsvWrite( out, place.FGetChanged(), '\n' );
}

bool recPlace::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_date1_id );
    recCsvRead( in, f_date2_id );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

void recPlace::RemoveDates( idt dateID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE \"%s\".Place SET date1_id=0 WHERE date1_id=" ID ";"
        "UPDATE \"%s\".Place SET date2_id=0 WHERE date2_id=" ID ";",
        UTF8_( dbname ), dateID, UTF8_( dbname ), dateID
    );
    s_db->ExecuteUpdate( sql );
}

bool recPlace::RemoveFromDatabase( idt placeID, const wxString& dbname )
{
    if( placeID <= 0 ) { // Don't remove common places
        return false;
    }
    recPlacePartVec parts = recPlace::GetPlaceParts( placeID, dbname );
    for( size_t i = 0 ; i < parts.size() ; i++ ) {
        parts[i].Delete( dbname );
    }
    recEvent::RemovePlace( placeID, dbname );
    recEventa::RemovePlace( placeID, dbname );
    recReferenceEntity::DeleteType( recReferenceEntity::TYPE_Place, placeID, dbname );
    return Delete( placeID, dbname );
}

void recPlace::DeleteIfOrphaned( idt id, const wxString& dbname )
{
    if( id <= 0 ) { // Don't delete common places.
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

int recPlacePart::SetNextSequence( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT MAX(sequence) FROM \"%s\".PlacePart WHERE place_id=" ID ";",
        UTF8_( dbname ), f_place_id
    );

    f_sequence = s_db->ExecuteScalar( sql ) + 1;
    return f_sequence;
}

idt recPlacePart::Transfer( idt from_ppID, const wxString& fromdb, idt to_placeID, idt to_ppID, const wxString& todb )
{
    if( from_ppID == 0 ) return 0;

    recPlacePart from_pp( from_ppID, fromdb );
    wxASSERT( from_pp.FGetID() != 0 );

    recPlacePart to_pp( to_ppID, todb );
    to_pp.Delete( todb );
    
    recPlacePart new_pp( 0 );
    if( from_ppID > 0 ) {
        new_pp.FSetID( to_ppID );
    }
    else {
        new_pp.FSetID( from_ppID );
    }
    new_pp.FSetTypeID( recPlacePartType::Transfer( from_pp.FGetTypeID(), fromdb, todb ) );
    new_pp.FSetPlaceID( to_placeID );
    new_pp.FSetValue( from_pp.FGetValue() );
    new_pp.FSetSequence( from_pp.FGetSequence() );
    new_pp.Save( todb );
    to_ppID = new_pp.FGetID();

    recPlacePartType::DeleteIfOrphaned( to_pp.FGetTypeID(), todb);
    return to_ppID;
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

void recPlacePart::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recPlacePart pp( id, dbname );
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

bool recPlacePart::RemoveFromDatabase( idt ppID, const wxString& dbname )
{
    recPlacePart pp( ppID, dbname );
    bool ret = pp.Delete( dbname );
    recPlacePartType::DeleteIfOrphaned( pp.FGetTypeID(), dbname );
    return ret;
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

idt recPlacePartType::Transfer( idt from_pptID, const wxString& fromdb, const wxString& todb )
{
    if( from_pptID == 0 ) return 0;

    recPlacePartType from_ppt( from_pptID, fromdb );
    idt to_pptID = from_pptID;
    if( to_pptID > 0 ) {
        to_pptID = recPlacePartType::FindUid( from_ppt.FGetUid(), todb );
    }

    recPlacePartType to_ppt( to_pptID, todb );
    recMatchUID match = from_ppt.CompareUID( to_ppt );
    if( match == recMatchUID::unequal || match == recMatchUID::younger ) {
        recPlacePartType new_ppt( from_ppt );
        new_ppt.FSetID( to_pptID );
        new_ppt.Save( todb );
        to_pptID = new_ppt.FGetID();
    }
    return to_pptID;
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

void recPlacePartType::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recPlacePartType ppt( id, dbname );
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

bool recPlacePartType::DeleteIfOrphaned( idt pptID, const wxString& dbname )
{
    if( pptID <= 0 ) return false;

    int cnt = ExecuteInt(
        "SELECT COUNT(*) FROM \"%s\".PlacePart WHERE type_id=" ID ";",
        dbname, pptID
    );
    if( cnt > 0 ) return false;

    return Delete( pptID, dbname );
}

// End of recPlace.cpp file
