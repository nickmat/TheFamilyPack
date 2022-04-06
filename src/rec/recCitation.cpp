/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recCitation.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Citation records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
 * Copyright:   Copyright (c) 2021..2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recCitation.h>
#include <rec/recContact.h>

#include <cal/calendar.h>


//============================================================================
//                 recCitation
//============================================================================

recCitation::recCitation( const recCitation& cit )
{
    f_id = cit.f_id;
    f_higher_id = cit.f_higher_id;
    f_ref_id = cit.f_ref_id;
    f_ref_seq = cit.f_ref_seq;
    f_rep_id = cit.f_rep_id;
    f_comment = cit.f_comment;
    f_uid = cit.f_uid;
    f_changed = cit.f_changed;
}

void recCitation::Clear()
{
    f_id = 0;
    f_higher_id = 0;
    f_ref_id = 0;
    f_ref_seq = 0;
    f_rep_id = 0;
    f_comment.clear();
    f_uid.clear();
    f_changed = 0;
}

void recCitation::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Citation (higher_id, ref_id, ref_seq, rep_id, comment, uid, changed)"
            " VALUES (" ID ", " ID ", %d, " ID ", '%q', '%q', %ld); ",
            UTF8_( dbname ), f_higher_id, f_ref_id, f_ref_seq, f_rep_id, UTF8_( f_comment ),
            UTF8_( f_uid ), f_changed
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
                "INSERT INTO \"%s\".Citation (id, higher_id, ref_id, ref_seq, rep_id, comment, uid, changed)"
                " VALUES (" ID ", " ID ", " ID ", %d, " ID ", '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, f_higher_id, f_ref_id, f_ref_seq, f_rep_id, UTF8_( f_comment ),
                UTF8_( f_uid ), f_changed
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Citation SET higher_id=" ID ", ref_id=" ID ", ref_seq=%d,"
                " rep_id=" ID ", comment='%q', uid = '%q', changed = %ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_higher_id, f_ref_id, f_ref_seq, f_rep_id, UTF8_( f_comment ),
                UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitation::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT higher_id, ref_id, ref_seq, rep_id, comment, uid, changed"
        " FROM \"%s\".Citation WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_higher_id = GET_ID( result.GetInt64( 0 ) );
    f_ref_id = GET_ID( result.GetInt64( 1 ) );
    f_ref_seq = result.GetInt( 2 );
    f_rep_id = GET_ID( result.GetInt64( 3 ) );
    f_comment = result.GetAsString( 4 );
    f_uid = result.GetAsString( 5 );
    f_changed = result.GetInt( 6 );
    return true;
}

bool recCitation::Equivalent( const recCitation& r2 ) const
{
    return
        f_higher_id == r2.f_higher_id &&
        f_ref_id == r2.f_ref_id &&
        f_ref_seq == r2.f_ref_seq &&
        f_rep_id == r2.f_rep_id &&
        f_comment == r2.f_comment &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

int recCitation::GetNextRefSequence( idt refID ) const
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(ref_seq) FROM Citation WHERE ref_id=" ID ";",
        refID
    );
    return s_db->ExecuteScalar( sql ) + 1;
}


recCitationPartVec recCitation::GetPartList( idt citID, const wxString& dbname )
{
    recCitationPartVec list;
    if( citID == 0 ) {
        return list;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, type_id, val, cit_seq, comment FROM \"%s\".CitationPart"
        " WHERE cit_id=" ID " ORDER BY cit_seq;",
        UTF8_( dbname ), citID
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recCitationPart part( 0 );
    part.FSetCitID( citID );
    while( result.NextRow() ) {
        part.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        part.FSetTypeID( GET_ID( result.GetInt64( 1 ) ) );
        part.FSetValue( result.GetAsString( 2 ) );
        part.FSetCitSeq( result.GetInt( 3 ) );
        part.FSetComment( result.GetAsString( 4 ) );
        list.push_back( part );
    }
    return list;
}

wxString recCitation::GetCitationStr( idt citID, const wxString& dbname )
{
    recCitation cit( citID, dbname );
    return cit.GetCitationStr( dbname );
}

wxString recCitation::GetCitationStr( const wxString& dbname ) const
{
    wxString citation;
    if( f_id == 0 ) {
        return citation;
    }
    if( f_higher_id ) {
        citation = recCitation::GetCitationStr( f_higher_id, dbname );
    }
    else {
        recRepository rep( f_rep_id, dbname );
        citation = rep.FGetName();
    }
    recCitationPartVec parts = GetPartList( dbname );
    for( const auto& part : parts ) {
        citation += ", " + part.FGetValue();
    }
    return citation;
}

void recCitation::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE CitationPart SET cit_id=" ID " WHERE cit_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Citation SET higher_id=" ID " WHERE higher_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Citation SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recCitation::CsvTitles()
{
    return std::string(
        "ID, Higher ID, Reference ID, Reference Sequence, Repository ID, Comment, UID, Last Changed\n" );
}

void recCitation::CsvWrite( std::ostream& out, idt id )
{
    recCitation cit( id );
    recCsvWrite( out, cit.FGetID() );
    recCsvWrite( out, cit.FGetHigherID() );
    recCsvWrite( out, cit.FGetRefID() );
    recCsvWrite( out, cit.FGetRefSeq() );
    recCsvWrite( out, cit.FGetRepID() );
    recCsvWrite( out, cit.FGetComment() );
    recCsvWrite( out, cit.FGetUid() );
    recCsvWrite( out, cit.FGetChanged(), '\n' );
}

bool recCitation::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_higher_id );
    recCsvRead( in, f_ref_id );
    recCsvRead( in, f_ref_seq );
    recCsvRead( in, f_rep_id );
    recCsvRead( in, f_comment );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

bool recCitation::RemoveFromDatabase( idt citID, const wxString& dbname )
{
    if( citID <= 0  ) return false; // Don't remove common data.
    
    wxSQLite3StatementBuffer sql;

    // Can't delete if it has children, delete them first.
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Citation WHERE higher_id=" ID ";",
        UTF8_( dbname ), citID
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    recCitation cit( citID, dbname );
    recCitationPartVec parts = GetPartList( citID, dbname );
    Delete( citID, dbname );
    for( auto& part : parts ) {
        part.Delete( dbname );
        recCitationPartType::DeleteIfOrphaned( part.FGetTypeID(), dbname );
    }
    recRepository::DeleteIfOrphaned( cit.FGetRepID(), dbname );
    return true;
}

//============================================================================
//                 recRepository
//============================================================================

recRepository::recRepository( const recRepository& cp )
{
    f_id = cp.f_id;
    f_name = cp.f_name;
    f_note = cp.f_note;
    f_con_list_id = cp.f_con_list_id;
    f_uid = cp.f_uid;
    f_changed = cp.f_changed;
}

void recRepository::Clear()
{
    f_id = 0;
    f_name.clear();
    f_note.clear();
    f_con_list_id = 0;
    f_uid.clear();
    f_changed = 0;
}

void recRepository::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Repository (name, note, con_list_id, uid, changed)"
            " VALUES ('%q', '%q', " ID ", '%q', %ld);",
            UTF8_( dbname ), UTF8_( f_name ), UTF8_( f_note ),
            f_con_list_id, UTF8_( f_uid ), f_changed
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
                "INSERT INTO \"%s\".Repository (id, name, note, con_list_id, uid, changed)"
                " VALUES (" ID ", '%q', '%q', " ID ", '%q', %ld);",
                UTF8_( dbname ), f_id, UTF8_( f_name ), UTF8_( f_note ),
                f_con_list_id, UTF8_( f_uid ), f_changed
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Repository SET name='%q', note='%q', con_list_id=" ID ","
                " uid = '%q', changed = %ld WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_( f_name ), UTF8_( f_note ),
                f_con_list_id, UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRepository::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, note, con_list_id, uid, changed"
        " FROM \"%s\".Repository WHERE id=" ID ";",
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
    f_note = result.GetAsString( 1 );
    f_con_list_id = GET_ID( result.GetInt64( 2 ) );
    f_uid = result.GetAsString( 3 );
    f_changed = result.GetInt( 4 );
    return true;
}

bool recRepository::Equivalent( const recRepository& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_note == r2.f_note &&
        f_con_list_id == r2.f_con_list_id &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

recRepositoryVec recRepository::GetFullList( const wxString& dbname )
{
    recRepositoryVec list;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT id, name, note, con_list_id, uid, changed FROM \"%s\".Repository"
        " WHERE NOT id=0 ORDER BY id;", UTF8_( dbname )
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recRepository arch( 0 );
    while( result.NextRow() ) {
        arch.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        arch.FSetName( result.GetAsString( 1 ) );
        arch.FSetNote( result.GetAsString( 2 ) );
        arch.FSetConListID( GET_ID( result.GetInt64( 3 ) ) );
        arch.FSetUid( result.GetAsString( 4 ) );
        arch.FSetChanged( result.GetInt( 5 ) );
        list.push_back( arch );
    }
    return list;
}

void recRepository::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Citation SET rep_id=" ID " WHERE rep_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Repository SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recRepository::CsvTitles()
{
    return std::string( "ID, Name, Note, Contact List ID\n" );
}

void recRepository::CsvWrite( std::ostream& out, idt id )
{
    recRepository rep( id );
    recCsvWrite( out, rep.FGetID() );
    recCsvWrite( out, rep.FGetName() );
    recCsvWrite( out, rep.FGetNote() );
    recCsvWrite( out, rep.FGetConListID(), '\n' );
}

bool recRepository::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    recCsvRead( in, f_note );
    recCsvRead( in, f_con_list_id );
    return bool( in );
}

void recRepository::DeleteIfOrphaned( idt repID, const wxString& dbname )
{
    if( repID <= 0 ) return;

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Citation WHERE rep_id=" ID ";",
        UTF8_( dbname ), repID
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    recRepository rep( repID, dbname );
    Delete( repID, dbname );

    recContactList::RemoveFromDatabase( rep.FGetConListID(), dbname );
}

//============================================================================
//                 recCitationPart
//============================================================================

recCitationPart::recCitationPart( const recCitationPart& cp )
{
    f_id = cp.f_id;
    f_cit_id = cp.f_cit_id;
    f_type_id = cp.f_type_id;
    f_val = cp.f_val;
    f_cit_seq = cp.f_cit_seq;
    f_comment = cp.f_comment;
}

void recCitationPart::Clear()
{
    f_id = 0;
    f_cit_id = 0;
    f_type_id = 0;
    f_val.clear();
    f_cit_seq = 0;
    f_comment.clear();
}

void recCitationPart::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".CitationPart (cit_id, type_id, val, cit_seq, comment)"
            " VALUES (" ID ", " ID ", '%q', %d, '%q');",
            UTF8_( dbname ), f_cit_id, f_type_id, UTF8_( f_val ), f_cit_seq, UTF8_( f_comment )
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
                "INSERT INTO \"%s\".CitationPart (id, cit_id, type_id, val, cit_seq, comment)"
                " VALUES (" ID ", " ID ", " ID ", '%q', %d, '%q');",
                UTF8_( dbname ), f_id, f_cit_id, f_type_id, UTF8_( f_val ),
                f_cit_seq, UTF8_( f_comment )
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".CitationPart SET cit_id=" ID ", type_id=" ID ", val='%q',"
                " cit_seq=%d, comment='%q'"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_cit_id, f_type_id, UTF8_( f_val ),
                f_cit_seq, UTF8_( f_comment ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitationPart::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT cit_id, type_id, val, cit_seq, comment"
        " FROM \"%s\".CitationPart WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_cit_id = GET_ID( result.GetInt64( 0 ) );
    f_type_id = GET_ID( result.GetInt64( 1 ) );
    f_val = result.GetAsString( 2 );
    f_cit_seq = result.GetInt( 3 );
    f_comment = result.GetAsString( 4 );
    return true;
}

bool recCitationPart::Equivalent( const recCitationPart& r2 ) const
{
    return
        f_cit_id == r2.f_cit_id &&
        f_type_id == r2.f_type_id &&
        f_val == r2.f_val &&
        f_cit_seq == r2.f_cit_seq &&
        f_comment == r2.f_comment;
}

int recCitationPart::GetNextCitationSeq( idt citID ) const
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(cit_seq) FROM CitationPart WHERE cit_id=" ID ";",
        citID
    );
    return s_db->ExecuteScalar( sql ) + 1;
}

void recCitationPart::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE CitationPart SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recCitationPart::CsvTitles()
{
    return std::string(
        "ID, Citation ID, Citation Part Type, Value, Citation Sequence, Comment\n" );
}

void recCitationPart::CsvWrite( std::ostream& out, idt id )
{
    recCitationPart cip( id );
    recCsvWrite( out, cip.FGetID() );
    recCsvWrite( out, cip.FGetCitID() );
    recCsvWrite( out, cip.FGetTypeID() );
    recCsvWrite( out, cip.FGetValue() );
    recCsvWrite( out, cip.FGetCitSeq() );
    recCsvWrite( out, cip.FGetComment(), '\n' );
}

bool recCitationPart::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_cit_id );
    recCsvRead( in, f_type_id );
    recCsvRead( in, f_val );
    recCsvRead( in, f_cit_seq );
    recCsvRead( in, f_comment );
    return bool( in );
}

void recCitationPart::RemoveFromDatabase( idt cpID, const wxString& dbname )
{
    if( cpID <= 0 ) return;
    recCitationPart cp( cpID, dbname );
    cp.RemoveFromDatabase( dbname );
}

void recCitationPart::RemoveFromDatabase( const wxString& dbname )
{
    if( FGetID() <= 0 ) return;
    Delete( FGetID(), dbname );
    recCitationPartType::DeleteIfOrphaned( FGetTypeID(), dbname );
}


//============================================================================
//                 recCitationPartType
//============================================================================

recCitationPartType::recCitationPartType( const recCitationPartType& cpt )
{
    f_id   = cpt.f_id;
    f_name = cpt.f_name;
    f_style = cpt.f_style;
    f_comment = cpt.f_comment;
    f_uid = cpt.f_uid;
    f_changed = cpt.f_changed;
}

void recCitationPartType::Clear()
{
    f_id = 0;
    f_name.clear();
    f_style = 0;
    f_comment.clear();
    f_uid.clear();
    f_changed = 0;
}

void recCitationPartType::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".CitationPartType (name, style, comment, uid, changed)"
            " VALUES ('%q', %d, '%q', '%q', %ld);",
            UTF8_( dbname ), UTF8_(f_name), f_style, UTF8_( f_comment), UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".CitationPartType (id, name, style, comment, uid, changed) "
                "VALUES (" ID ", '%q', %d, '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, UTF8_(f_name), f_style, UTF8_( f_comment ), UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".CitationPartType"
                " SET name='%q', style=%d, comment='%q', uid = '%q', changed = %ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_name), f_style, UTF8_( f_comment ), UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitationPartType::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( 
        "SELECT name, style, comment, uid, changed FROM \"%s\".CitationPartType WHERE id=" ID ";",
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
    f_style = result.GetInt( 1 );
    f_comment = result.GetAsString( 2 );
    f_uid = result.GetAsString( 3 );
    f_changed = result.GetInt( 4 );
    return true;
}

bool recCitationPartType::Equivalent( const recCitationPartType& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_style == r2.f_style &&
        f_comment == r2.f_comment &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

wxString recCitationPartType::GetStr( idt id, const wxString& dbname )
{
    recCitationPartType cpt( id, dbname );
    return cpt.f_name;
}

recCitationPartTypeVec recCitationPartType::GetList( const wxString& dbname )
{
    recCitationPartType cpt;
    recCitationPartTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, name, style, comment, uid, changed FROM \"%s\".CitationPartType "
        "WHERE id<=0 ORDER BY id DESC;", UTF8_( dbname )
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        cpt.f_id = GET_ID( result.GetInt64( 0 ) );
        cpt.f_name = result.GetAsString( 1 );
        cpt.f_style = result.GetInt( 2 );
        cpt.f_comment = result.GetAsString( 3 );
        cpt.f_uid = result.GetAsString( 4 );
        cpt.f_changed = result.GetInt( 5 );
        list.push_back( cpt );
    }

    // Put user entries in list.
    sql.Format(
        "SELECT id, name, style, comment, uid, changed FROM \"%s\".CitationPartType "
        "WHERE id>0 ORDER BY id ASC;", UTF8_( dbname )
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        cpt.f_id = GET_ID( result.GetInt64( 0 ) );
        cpt.f_name = result.GetAsString( 1 );
        cpt.f_style = result.GetInt( 2 );
        cpt.f_comment = result.GetAsString( 3 );
        cpt.f_uid = result.GetAsString( 4 );
        cpt.f_changed = result.GetInt( 5 );
        list.push_back( cpt );
    }
    return list;
}

void recCitationPartType::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE CitationPart SET type_id=" ID " WHERE type_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE CitationPartType SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recCitationPartType::CsvTitles()
{
    return std::string( "ID, Name, Style, Comment, UID, Last Changed\n" );
}

void recCitationPartType::CsvWrite( std::ostream& out, idt id )
{
    recCitationPartType cipt( id );
    recCsvWrite( out, cipt.FGetID() );
    recCsvWrite( out, cipt.FGetName() );
    recCsvWrite( out, cipt.FGetStyle() );
    recCsvWrite( out, cipt.FGetComment() );
    recCsvWrite( out, cipt.FGetUid() );
    recCsvWrite( out, cipt.FGetChanged(), '\n' );
}

bool recCitationPartType::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_name );
    recCsvRead( in, f_style );
    recCsvRead( in, f_comment );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

void recCitationPartType::DeleteIfOrphaned( idt cptID, const wxString& dbname )
{
    if( cptID <= 0 ) return;

    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".CitationPart WHERE type_id=" ID ";",
        UTF8_( dbname ), cptID
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    Delete( cptID, dbname );
}

// End of src/rec/recCitation.cpp file
