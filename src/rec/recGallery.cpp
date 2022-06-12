/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recGallery.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Gallery records.
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

#include <rec/recGallery.h>

#include <rec/recGalleryMedia.h>


recGallery::recGallery( const recGallery& gal )
{
    f_id = gal.f_id;
    f_title = gal.f_title;
    f_note = gal.f_note;
    f_uid = gal.f_uid;
    f_changed = gal.f_changed;
}

void recGallery::Clear()
{
    f_id = 0;
    f_title.clear();
    f_note.clear();
    f_uid.clear();
    f_changed = 0;
}

void recGallery::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Gallery (title, note, uid, changed)"
            " VALUES ('%q', '%q', '%q', %ld);",
            UTF8_( dbname ), UTF8_( f_title ), UTF8_( f_note ), UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if ( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Gallery (id, title, note, uid, changed) "
                "VALUES (" ID ", '%q', '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, UTF8_( f_title ), UTF8_( f_note ),
                UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Gallery SET title='%q', note='%q', uid='%q', changed=%ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_( f_title ), UTF8_( f_note ),
                UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recGallery::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT title, note, uid, changed FROM \"%s\".Gallery WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if ( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_title = result.GetAsString( 0 );
    f_note = result.GetAsString( 1 );
    f_uid = result.GetAsString( 2 );
    f_changed = result.GetInt( 3 );
    return true;
}

bool recGallery::Equivalent( const recGallery& r2 ) const
{
    return
        f_title == r2.f_title &&
        f_note == r2.f_note &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
    ;
}

recGalleryVec recGallery::GetGalleries( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title, note, uid, changed FROM \"%s\".Gallery WHERE NOT id=0 ORDER BY id",
        UTF8_( dbname )
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    recGalleryVec gals;
    recGallery gal( 0 );
    while ( result.NextRow() ) {
        gal.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        gal.FSetTitle( result.GetAsString( 1 ) );
        gal.FSetNote( result.GetAsString( 2 ) );
        gal.FSetUid( result.GetAsString( 3 ) );
        gal.FSetChanged( result.GetInt( 4 ) );
        gals.push_back( gal );
    }
    return gals;
}

recMediaVec recGallery::GetMediaVec( idt galID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT M.id, M.data_id, M.ass_id, M.ref_id, M.privacy, M.title, M.note"
        " FROM \"%s\".Media M, \"%s\".GalleryMedia GM"
        " WHERE M.id=GM.med_id AND GM.gal_id=" ID
        " ORDER BY GM.med_seq;",
        UTF8_( dbname ), UTF8_( dbname ), galID
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recMediaVec meds;
    recMedia med( 0 );
    while ( result.NextRow() ) {
        med.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        med.FSetDataID( GET_ID( result.GetInt64( 1 ) ) );
        med.FSetAssID( GET_ID( result.GetInt64( 2 ) ) );
        med.FSetRefID( GET_ID( result.GetInt64( 3 ) ) );
        med.FSetPrivacy( result.GetInt( 4 ) );
        med.FSetTitle( result.GetAsString( 5 ) );
        med.FSetNote( result.GetAsString( 6 ) );
        meds.push_back( med );
    }
    return meds;
}

recGalleryMediaMediaVec recGallery::GetGalleryMediaMediaVec( idt galID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT M.id, M.data_id, M.ass_id, M.ref_id, M.privacy, M.title, M.note,"
        " GM.id, GM.title, GM.med_seq FROM \"%s\".Media M, \"%s\".GalleryMedia GM"
        " WHERE M.id=GM.med_id AND GM.gal_id=" ID
        " ORDER BY GM.med_seq;",
        UTF8_( dbname ), UTF8_( dbname ), galID
        );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recGalleryMediaMedia gmm;
    recGalleryMedia& gm = gmm.GetGalleryMedia();
    gm.FSetGalID( galID );
    recMedia& med = gmm.GetMedia();
    recGalleryMediaMediaVec gmms;
    while ( result.NextRow() ) {
        med.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        med.FSetDataID( GET_ID( result.GetInt64( 1 ) ) );
        med.FSetAssID( GET_ID( result.GetInt64( 2 ) ) );
        med.FSetRefID( GET_ID( result.GetInt64( 3 ) ) );
        med.FSetPrivacy( result.GetInt( 4 ) );
        med.FSetTitle( result.GetAsString( 5 ) );
        med.FSetNote( result.GetAsString( 6 ) );
        gm.FSetID( GET_ID( result.GetInt64( 7 ) ) );
        gm.FSetTitle( result.GetAsString( 8 ) );
        gm.FSetMedID( med.FGetID() );
        gm.FSetMedSeq( GET_ID( result.GetInt64( 9 ) ) );
        gmms.push_back( gmm );
    }
    return gmms;
}

std::string recGallery::CsvTitles()
{
    return std::string( "ID, Title, Note, UID, Changed\n" );
}

void recGallery::CsvWrite( std::ostream& out, idt id )
{
    recGallery gal( id );
    recCsvWrite( out, gal.FGetID() );
    recCsvWrite( out, gal.FGetTitle() );
    recCsvWrite( out, gal.FGetNote() );
    recCsvWrite( out, gal.FGetUid() );
    recCsvWrite( out, gal.FGetChanged(), '\n' );
}

bool recGallery::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_title );
    recCsvRead( in, f_note );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

bool recGallery::DeleteIfOrphaned( idt galID, const wxString& dbname )
{
    if( galID <= 0 ) return false;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".GalleryMedia WHERE gal_id=" ID ";",
        UTF8_( dbname ), galID
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    if( !Delete( galID, dbname ) ) return false;

    return true;
}

// End of src/rec/recGallery.cpp file
