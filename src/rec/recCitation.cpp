/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recCitation.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Citation records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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


//============================================================================
//                 recCitation
//============================================================================

recCitation::recCitation( const recCitation& cit )
{
    f_id = cit.f_id;
    f_ref_id = cit.f_ref_id;
    f_ref_seq = cit.f_ref_seq;
    f_rep_id = cit.f_rep_id;
    f_comment = cit.f_comment;
}

void recCitation::Clear()
{
    f_id = 0;
    f_ref_id = 0;
    f_ref_seq = 0;
    f_rep_id = 0;
    f_comment.clear();
}

void recCitation::Save()
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Citation (ref_id, ref_seq, rep_id, comment)"
            " VALUES (" ID ", %d, " ID ", '%q'); ",
            f_ref_id, f_ref_seq, f_rep_id, UTF8_( f_comment )
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
                "INSERT INTO Citation (id, ref_id, ref_seq, rep_id, comment)"
                " VALUES (" ID ", " ID ", %d, " ID ", '%q');",
                f_id, f_ref_id, f_ref_seq, f_rep_id, UTF8_( f_comment )
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE Citation SET ref_id=" ID ", ref_seq=%d, rep_id=" ID ", comment='%q'"
                " WHERE id=" ID ";",
                f_ref_id, f_ref_seq, f_rep_id, UTF8_( f_comment ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitation::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ref_id, ref_seq, rep_id, comment"
        " FROM Citation WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ref_id = GET_ID( result.GetInt64( 0 ) );
    f_ref_seq = result.GetInt( 1 );
    f_rep_id = GET_ID( result.GetInt64( 2 ) );
    f_comment = result.GetAsString( 3 );
    return true;
}

bool recCitation::Equivalent( const recCitation& r2 ) const
{
    return
        f_ref_id == r2.f_ref_id &&
        f_ref_seq == r2.f_ref_seq &&
        f_rep_id == r2.f_rep_id &&
        f_comment == r2.f_comment
        ;
}

recCitationPartVec recCitation::GetPartList( idt citID )
{
    recCitationPartVec list;
    if( citID == 0 ) {
        return list;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, type_id, val, cit_seq, comment FROM CitationPart"
        " WHERE cit_id=" ID " ORDER BY cit_seq;",
        citID
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recCitationPart part( 0 );
    part.FSetCitId( citID );
    while( result.NextRow() ) {
        part.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        part.FSetTypeId( GET_ID( result.GetInt64( 1 ) ) );
        part.FSetVal( result.GetAsString( 2 ) );
        part.FSetCitSeq( result.GetInt( 3 ) );
        part.FSetComment( result.GetAsString( 4 ) );
        list.push_back( part );
    }
    return list;
}

wxString recCitation::GetCitationStr( idt citID )
{
    recCitation cit( citID );
    return cit.GetCitationStr();
}

wxString recCitation::GetCitationStr() const
{
    wxString citation;
    if( f_id == 0 ) {
        return citation;
    }
    recRepository rep( f_rep_id );
    citation = rep.FGetName();
    recCitationPartVec parts = GetPartList();
    for( const auto& part : parts ) {
        citation += ", " + part.FGetVal();
    }
    return wxString();
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
}

void recRepository::Clear()
{
    f_id = 0;
    f_name.clear();
    f_note.clear();
    f_con_list_id = 0;
}

void recRepository::Save()
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Repository (name, note, con_list_id)"
            " VALUES ('%q', '%q', " ID ");",
            UTF8_( f_name ), UTF8_( f_note ), f_con_list_id
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
                "INSERT INTO Repository (id, name, note, con_list_id)"
                " VALUES (" ID ", '%q', '%q', " ID ");",
                f_id, UTF8_( f_name ), UTF8_( f_note ), f_con_list_id
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE Repository SET name='%q', note='%q', con_list_id=" ID
                " WHERE id=" ID ";",
                UTF8_( f_name ), UTF8_( f_note ), f_con_list_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRepository::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, note, con_list_id"
        " FROM Repository WHERE id=" ID ";",
        f_id
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
    return true;
}

bool recRepository::Equivalent( const recRepository& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_note == r2.f_note &&
        f_con_list_id == r2.f_con_list_id;
}

recRepositoryVec recRepository::GetFullList()
{
    recRepositoryVec list;
    wxSQLite3ResultSet result = s_db->ExecuteQuery(
        "SELECT id, name, note, con_list_id FROM Repository"
        " ORDER BY id;"
    );

    recRepository arch( 0 );
    while( result.NextRow() ) {
        arch.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        arch.FSetName( result.GetAsString( 1 ) );
        arch.FSetNote( result.GetAsString( 2 ) );
        arch.FSetConListId( GET_ID( result.GetInt64( 3 ) ) );
        list.push_back( arch );
    }
    return list;
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

void recCitationPart::Save()
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO CitationPart (cit_id, type_id, val, cit_seq, comment)"
            " VALUES (" ID ", " ID ", '%q', %d, '%q');",
            f_cit_id, f_type_id, UTF8_( f_val ), f_cit_seq, UTF8_( f_comment )
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
                "INSERT INTO CitationPart (id, cit_id, type_id, val, cit_seq, comment)"
                " VALUES (" ID ", " ID ", " ID ", '%q', %d, '%q');",
                f_id, f_cit_id, f_type_id, UTF8_( f_val ),
                f_cit_seq, UTF8_( f_comment )
            );
        }
        else {
            // Update existing record
            sql.Format(
                "UPDATE CitationPart SET cit_id=" ID ", type_id=" ID ", val='%q',"
                " cit_seq=%d, comment='%q'"
                " WHERE id=" ID ";",
                f_cit_id, f_type_id, UTF8_( f_val ),
                f_cit_seq, UTF8_( f_comment ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitationPart::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT cit_id, type_id, val, cit_seq, comment"
        " FROM CitationPart WHERE id=" ID ";",
        f_id
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

//============================================================================
//                 recCitationPartType
//============================================================================

recCitationPartType::recCitationPartType( const recCitationPartType& cpt )
{
    f_id   = cpt.f_id;
    f_name = cpt.f_name;
    f_style = cpt.f_style;
    f_comment = cpt.f_comment;
}

void recCitationPartType::Clear()
{
    f_id = 0;
    f_name.clear();
    f_style = 0;
    f_comment.clear();
}

void recCitationPartType::Save()
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO CitationPartType (name, style, comment)"
            " VALUES ('%q', %d, '%q');",
            UTF8_(f_name), f_style, UTF8_( f_comment)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO CitationPartType (id, name, style, comment) "
                "VALUES (" ID ", '%q', %d, '%q');",
                f_id, UTF8_(f_name), f_style, UTF8_( f_comment )
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE CitationPartType SET name='%q', style=%d, comment='%q'"
                " WHERE id=" ID ";",
                UTF8_(f_name), f_style, UTF8_( f_comment ), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recCitationPartType::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( 
        "SELECT name, style, comment FROM CitationPartType WHERE id=" ID ";",
        f_id
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
    return true;
}

bool recCitationPartType::Equivalent( const recCitationPartType& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_style == r2.f_style &&
        f_comment == r2.f_comment
        ;
}

wxString recCitationPartType::GetStr( idt id )
{
    recCitationPartType cpt( id );
    return cpt.f_name;
}

recCitationPartTypeVec recCitationPartType::GetList()
{
    recCitationPartType cpt;
    recCitationPartTypeVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
    int i;

    // Put standard entries in list.
    sql.Format(
        "SELECT id, name, style, comment FROM CitationPartType "
        "WHERE id<=0 ORDER BY id DESC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        cpt.f_id = GET_ID( result.GetInt64( 0 ) );
        cpt.f_name = result.GetAsString( 1 );
        cpt.f_style = result.GetInt( 2 );
        cpt.f_comment = result.GetAsString( 3 );
        list.push_back( cpt );
    }

    // Put user entries in list.
    sql.Format(
        "SELECT id, name, style, comment FROM CitationPartType "
        "WHERE id>0 ORDER BY id ASC;"
    );
    result = s_db->GetTable( sql );

    for( i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        cpt.f_id = GET_ID( result.GetInt64( 0 ) );
        cpt.f_name = result.GetAsString( 1 );
        cpt.f_style = result.GetInt( 2 );
        cpt.f_comment = result.GetAsString( 3 );
        list.push_back( cpt );
    }
    return list;
}

// End of src/rec/recCitation.cpp file
