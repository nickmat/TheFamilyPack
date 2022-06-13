/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Media records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018..2022, Nick Matthews.
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

#include <rec/recMedia.h>

#include <rec/recAssociate.h>
#include <rec/recGallery.h>
#include <rec/recGalleryMedia.h>
#include <rec/recMediaData.h>

recMedia::recMedia( const recMedia& n )
{
    f_id = n.f_id;
    f_data_id = n.f_data_id;
    f_ass_id = n.f_ass_id;
    f_ref_id = n.f_ref_id;
    f_ref_seq = n.f_ref_seq;
    f_privacy = n.f_privacy;
    f_title = n.f_title;
    f_note = n.f_note;
}

void recMedia::Clear()
{
    f_id = 0;
    f_data_id = 0;
    f_ass_id = 0;
    f_ref_id = 0;
    f_ref_seq = 0;
    f_privacy = 0;
    f_title.clear();
    f_note.clear();
}

void recMedia::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Media (data_id, ass_id, ref_id, ref_seq, privacy, title, note)"
            " VALUES (" ID ", " ID ", " ID ", %d, %d, '%q', '%q');",
            UTF8_( dbname ), f_data_id, f_ass_id, f_ref_id, f_ref_seq, f_privacy, UTF8_( f_title ), UTF8_( f_note )
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Media (id, data_id, ass_id, ref_id, ref_seq, privacy, title, note)"
                " VALUES (" ID ", " ID ", " ID ", " ID ", %d, %d, '%q', '%q');",
                UTF8_( dbname ), f_id, f_data_id, f_ass_id, f_ref_id, f_ref_seq, f_privacy, UTF8_( f_title ), UTF8_( f_note )
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Media"
                " SET data_id=" ID ", ass_id=" ID ", ref_id=" ID ", ref_seq=%d, privacy=%d,"
                " title='%q', note='%q' WHERE id=" ID ";",
                UTF8_( dbname ), f_data_id, f_ass_id, f_ref_id, f_ref_seq, f_privacy, UTF8_( f_title ), UTF8_( f_note ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recMedia::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT data_id, ass_id, ref_id, ref_seq, privacy, title, note"
        " FROM \"%s\".Media WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_data_id = GET_ID( result.GetInt64( 0 ) );
    f_ass_id = GET_ID( result.GetInt64( 1 ) );
    f_ref_id = GET_ID( result.GetInt64( 2 ) );
    f_ref_seq = result.GetInt( 3 );
    f_privacy = result.GetInt( 4 );
    f_title = result.GetAsString( 5 );
    f_note = result.GetAsString( 6 );
    return true;
}

bool recMedia::Equivalent( const recMedia& r2 ) const
{
    return
        f_data_id == r2.f_data_id &&
        f_ass_id == r2.f_ass_id   &&
        f_ref_id == r2.f_ref_id   &&
        f_ref_seq == r2.f_ref_seq &&
        f_privacy == r2.f_privacy &&
        f_title == r2.f_title     &&
        f_note == r2.f_note
    ;
}

idt recMedia::Create( idt mdID, idt assID, idt refID )
{
    recMedia med( 0 );
    recMediaData md( mdID, assID );

    med.f_data_id = mdID;
    med.f_ass_id = assID;
    med.f_ref_id = refID;
    med.f_ref_seq = recMedia::GetNextRefSeq( refID );
    med.f_privacy = md.FGetPrivacy();
    med.f_title = md.FGetTitle();
    med.Save();
    return med.f_id;
}

int recMedia::GetNextRefSeq( idt refID )
{
    return ExecuteInt( "SELECT MAX(ref_seq) FROM Media WHERE ref_id=" ID ";", refID ) + 1;
}

wxString recMedia::GetTitle( idt medID, const wxString& dbname )
{
    return ExecuteStr( "SELECT title FROM \"%s\".Media WHERE id=" ID ";", UTF8_( dbname ), medID );
}

wxSQLite3Table recMedia::GetMediaList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, ass_id, ref_id, title FROM \"%s\".Media"
        " WHERE NOT id=0 ORDER BY id;",
        UTF8_( dbname )
    );
    return s_db->GetTable( sql );
}

wxSQLite3Table recMedia::GetMediaList( idt offset, int limit, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, ass_id, ref_id, title FROM \"%s\".Media"
        " WHERE NOT id=0 ORDER BY id LIMIT " ID ", %d;",
        UTF8_( dbname ), offset, limit
    );
    return s_db->GetTable( sql );
}

recIdVec recMedia::GetGalleryMediaList( idt medID, const wxString& dbname )
{
    return ExecuteIdVec(
        "SELECT id FROM \"%s\".GalleryMedia WHERE med_id=" ID ";",
        UTF8_( dbname ), medID
    );
}

idt recMedia::Transfer(
    idt from_medID, const wxString& fromdb, idt to_refID, const wxString& todb, idt to_assID )
{
    if( from_medID == 0 ) return 0;
    recMedia from_med( from_medID, fromdb );
    wxString md_fromdb = recAssociate::GetAttachedName( from_med.FGetAssID(), fromdb );
    wxString md_todb = recAssociate::GetAttachedName( to_assID, todb );
    idt to_mdID = recMediaData::Transfer( from_med.FGetDataID(), md_fromdb, md_todb );
    // Don't transfer just media record if we can't transfer the data.
    if( to_mdID == 0 ) {
        return 0;
    }
    recMedia to_med( from_med );
    to_med.FSetDataID( to_mdID );
    to_med.FSetAssID( to_assID );
    to_med.FSetRefID( to_refID );
    to_med.FSetRefSeq( recMedia::GetNextRefSeq( to_refID ) );
    if( to_med.FGetID() > 0 ) {
        to_med.FSetID( 0 );
    }
    to_med.Save( todb );
    idt to_medID = to_med.FGetID();

    // List GalleryMedia links and step thru them.
    recIdVec from_gmIDs = recMedia::GetGalleryMediaList( from_medID, fromdb );
    recIdVec to_gmIDs = recMedia::GetGalleryMediaList( to_medID, fromdb );
    size_t size = std::max( from_gmIDs.size(), to_gmIDs.size() );
    for( size_t i = 0; i < size; i++ ) {
        if( i >= from_gmIDs.size() ) { // No more to copy.
            recGalleryMedia gm( to_gmIDs[i], todb );
            gm.Delete( todb );
            recGallery::DeleteIfOrphaned( gm.FGetGalID(), todb );
            continue;
        }
        if( i >= to_gmIDs.size() ) {
            recGalleryMedia gm( from_gmIDs[i], fromdb );
            gm.FSetMedID( to_medID );
            idt to_gal = recGallery::Transfer( gm.FGetGalID(), fromdb, todb );
            wxASSERT( to_gal != 0 );
            gm.FSetGalID( to_gal );
            gm.SetNextMedSequence( to_gal, todb );
            gm.FSetID( 0 );
            gm.Save( todb );
            continue;
        }
        recGalleryMedia gm( to_gmIDs[i], todb );
        idt to_gal = recGallery::Transfer( gm.FGetGalID(), fromdb, todb );
        wxASSERT( to_gal != 0 );
        gm.FSetGalID( to_gal );
        gm.Save( todb );
    }
    return to_med.FGetID();
}

std::string recMedia::CsvTitles()
{
    return std::string(
        "ID, Data ID, Associate ID, Reference ID, Reference Sequence, Privacy, Title, Note\n"
    );
}

void recMedia::CsvWrite( std::ostream& out, idt id )
{
    recMedia med( id );
    recCsvWrite( out, med.FGetID() );
    recCsvWrite( out, med.FGetDataID() );
    recCsvWrite( out, med.FGetAssID() );
    recCsvWrite( out, med.FGetRefID() );
    recCsvWrite( out, med.FGetRefSeq() );
    recCsvWrite( out, med.FGetPrivacy() );
    recCsvWrite( out, med.FGetTitle() );
    recCsvWrite( out, med.FGetNote(), '\n' );
}

bool recMedia::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_data_id );
    recCsvRead( in, f_ass_id );
    recCsvRead( in, f_ref_id );
    recCsvRead( in, f_ref_seq );
    recCsvRead( in, f_privacy );
    recCsvRead( in, f_title );
    recCsvRead( in, f_note );
    return bool( in );
}

bool recMedia::RemoveFromDatabase( idt medID, DataInc data, const wxString& dbname )
{
    if( medID <= 0 ) return false;
    recMedia med( medID, dbname );
    bool ret = Delete( medID, dbname );
    if( data != DataInc::omit ) {
        idt mdID = med.FGetDataID();
        if( mdID > 0 ) {
            idt assID = med.FGetAssID();
            wxString datadb = recAssociate::GetAttachedName( assID, dbname );
            if( data == DataInc::always ) {
                recMediaData::Delete( mdID, datadb );
            }
            else if( data == DataInc::orphan ) {
                if( recMediaData::IsOrphaned( mdID, assID, dbname ) &&
                    recMediaData::IsOrphaned( mdID, 0, datadb ) )
                {
                    recMediaData::Delete( mdID, datadb );
                }
            }
            else {
                assert( false ); // Unknown DataInc. Should not be here!
            }
        }
    }
    recIdVec gmIDs = GetGalleryMediaList( medID, dbname );
    for( idt gmID : gmIDs ) {
        recGalleryMedia gm( gmID );
        gm.Delete( dbname );
        recGallery::DeleteIfOrphaned( gm.FGetGalID(), dbname );
    }
    return ret;
}

// End of recMedia.cpp file
