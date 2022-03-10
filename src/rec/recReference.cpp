/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
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

#include <rec/recReference.h>
#include <rec/recName.h>
#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recEventa.h>
#include <rec/recEvent.h>
#include <rec/recEventType.h>


//============================================================================
//------------------------------[ recReference ]------------------------------
//============================================================================

recReference::recReference( const recReference& r )
{
    f_id        = r.f_id;
    f_higher_id = r.f_higher_id;
    f_title     = r.f_title;
    f_statement = r.f_statement;
    f_res_id    = r.f_res_id;
    f_user_ref  = r.f_user_ref;
    f_uid       = r.f_uid;
    f_changed   = r.f_changed;
}

void recReference::Clear()
{
    f_id = 0;
    f_higher_id = 0;
    f_title.clear();
    f_statement.clear();
    f_res_id = 0;
    f_user_ref.clear();
    f_uid.clear();
    f_changed = 0;
}

void recReference::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Reference (higher_id, title, statement, res_id, user_ref, uid, changed)"
            "VALUES (" ID ", '%q', '%q', " ID ", '%q', '%q', %ld);",
            UTF8_( dbname ), f_higher_id, UTF8_(f_title), UTF8_(f_statement), f_res_id, UTF8_(f_user_ref),
            UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Reference (id, higher_id, title, statement, res_id, user_ref, uid, changed)"
                " VALUES (" ID ", " ID ", '%q', '%q', " ID ", '%q', '%q', %ld);",
                UTF8_( dbname ), f_id, f_higher_id, UTF8_(f_title), UTF8_(f_statement),
                f_res_id, UTF8_(f_user_ref), UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Reference SET higher_id=" ID ", title = '%q', statement = '%q',"
                " res_id = " ID ", user_ref = '%q', uid = '%q', changed = %ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_higher_id, UTF8_(f_title), UTF8_(f_statement),
                f_res_id, UTF8_(f_user_ref), UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recReference::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT higher_id, title, statement, res_id, user_ref, uid, changed"
        " FROM \"%s\".Reference WHERE id=" ID ";",
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
    f_title     = result.GetAsString( 1 );
    f_statement = result.GetAsString( 2 );
    f_res_id    = GET_ID( result.GetInt64( 3 ) );
    f_user_ref  = result.GetAsString( 4 );
    f_uid       = result.GetAsString( 5 );
    f_changed   = result.GetInt( 6 );
    return true;
}

bool recReference::Equivalent( const recReference& r2 ) const
{
    return
        f_higher_id == r2.f_higher_id &&
        f_title == r2.f_title &&
        f_statement == r2.f_statement &&
        f_res_id == r2.f_res_id &&
        f_user_ref == r2.f_user_ref &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

wxString recReference::GetTitle( idt refID, const wxString& dbname )
{
    return ExecuteStr( 
        "SELECT title FROM \"%s\".Reference WHERE id=" ID ";",
        UTF8_( dbname ), refID
    );
}

recRefEntVec recReference::ReadReferenceEntitys( const wxString& dbname )
{
    recRefEntVec vec;
    recReferenceEntity record;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        return vec;
    }

    sql.Format(
        "SELECT id, entity_type, entity_id, sequence FROM \"%s\".ReferenceEntity "
        "WHERE ref_id=" ID " ORDER BY sequence;",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    vec.reserve( result.GetRowCount() );
    record.f_ref_id = f_id;
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        record.f_id = GET_ID( result.GetInt64( 0 ) );
        record.f_entity_type = (recReferenceEntity::Type) result.GetInt( 1 );
        record.f_entity_id = GET_ID( result.GetInt64( 2 ) );
        record.f_sequence = (unsigned) result.GetInt( 3 );
        vec.push_back( record );
    }
    return vec;
}

wxSQLite3Table recReference::GetTitleList( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM \"%s\".Reference ORDER BY id;",
        UTF8_( dbname )
    );
    return s_db->GetTable( sql );
}

wxSQLite3Table recReference::GetTitleList( idt offset, int limit, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM \"%s\".Reference ORDER BY id LIMIT " ID ", %d;",
        UTF8_( dbname ), offset, limit
    );
    return s_db->GetTable( sql );
}

int recReference::GetNextEntitySequence( idt refID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT MAX(sequence) FROM ReferenceEntity WHERE ref_id=" ID ";",
        refID
    );
    return ExecuteInt( sql ) + 1;
}

recIdVec recReference::GetCitationList( idt refID, const wxString& dbname )
{
    return ExecuteIdVec( 
        "SELECT id FROM \"%s\".Citation WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

recIdVec recReference::GetPersonaList( idt refID, const wxString& dbname )
{
    return ExecuteIdVec( 
        "SELECT id FROM \"%s\".Persona WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

int recReference::GetPersonaCount( idt refID, const wxString& dbname )
{
    return ExecuteInt(
        "SELECT COUNT(*) FROM \"%s\".Persona WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

recIdVec recReference::GetMediaList( idt refID, const wxString& dbname )
{
    return ExecuteIdVec(
        "SELECT id FROM \"%s\".Media WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

int recReference::GetMediaCount( idt refID, const wxString& dbname )
{
    return ExecuteInt(
        "SELECT COUNT(*) FROM \"%s\".Media WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

recIdVec recReference::GetEventaList( idt refID, const wxString& dbname )
{
    return ExecuteIdVec(
        "SELECT id FROM \"%s\".Eventa WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

int recReference::GetEventaCount( idt refID, const wxString& dbname )
{
    return ExecuteInt(
        "SELECT COUNT(*) FROM \"%s\".Eventa WHERE ref_id=" ID ";",
        UTF8_( dbname ), refID
    );
}

recIdVec recReference::GetIdVecForEntity( 
    idt refID, recReferenceEntity::Type type, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT entity_id FROM \"%s\".ReferenceEntity"
        " WHERE entity_type=%d AND ref_id=" ID ";",
        UTF8_( dbname ), (int) type, refID
    );
    return ExecuteIdVec( sql );
}

wxString recReference::GetChangedDate() const
{
    return calStrFromJdn( f_changed, CALENDAR_SCH_Gregorian );
}

wxString recReference::GetChangedDate( idt refID, const wxString& dbname )
{
    long jdn = recDb::ExecuteInt(
        "SELECT changed FROM \"%s\".Reference WHERE id=" ID ";",
        UTF8_( dbname ), refID
    );
    return calStrFromJdn( jdn, CALENDAR_SCH_Gregorian );
}

void recReference::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Citation SET ref_id=" ID " WHERE ref_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Media SET ref_id=" ID " WHERE ref_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Persona SET ref_id=" ID " WHERE ref_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Eventa SET ref_id=" ID " WHERE ref_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE ReferenceEntity SET ref_id=" ID " WHERE ref_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Reference SET higher_id=" ID " WHERE higher_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Reference SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recReference::CsvTitles()
{
    return std::string( "ID, Higher ID, Title, Statement, Researcher ID, User Reference, UID, Last Changed\n");
}

void recReference::CsvWrite( std::ostream& out, idt id )
{
    recReference ref( id );
    recCsvWrite( out, ref.FGetID() );
    recCsvWrite( out, ref.FGetHigherId() );
    recCsvWrite( out, ref.FGetTitle() );
    recCsvWrite( out, ref.FGetStatement() );
    recCsvWrite( out, ref.FGetResId() );
    recCsvWrite( out, ref.FGetUserRef() );
    recCsvWrite( out, ref.FGetUid() );
    recCsvWrite( out, ref.FGetChanged(), '\n' );
}

bool recReference::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_higher_id );
    recCsvRead( in, f_title );
    recCsvRead( in, f_statement );
    recCsvRead( in, f_res_id );
    recCsvRead( in, f_user_ref );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

//============================================================================
//---------------------------[ recReferenceEntity ]---------------------------
//============================================================================

const wxString recReferenceEntity::sm_typeStr[recReferenceEntity::TYPE_MAX] = {
    _("Default"),      // TYPE_Unstated
    _("Source"),       // TYPE_Source
    _("Spare3"),       // TYPE_Event
    _("Place"),        // TYPE_Place
    _("Date"),         // TYPE_Date
    _("Spare2"),       // TYPE_Relationship 
    _("Spare"),        // TYPE_Attribute
    _("Name")          // TYPE_Name
};

recReferenceEntity::recReferenceEntity( const recReferenceEntity& re )
{
    f_id          = re.f_id;
    f_ref_id      = re.f_ref_id;
    f_entity_type = re.f_entity_type;
    f_entity_id   = re.f_entity_id;
    f_sequence    = re.f_sequence;
}

void recReferenceEntity::Clear()
{
    f_id          = 0;
    f_ref_id      = 0;
    f_entity_type = TYPE_Unstated;
    f_entity_id   = 0;
    f_sequence    = 0;
}

void recReferenceEntity::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".ReferenceEntity "
            "(ref_id, entity_type, entity_id, sequence)"
            "VALUES (" ID ", %u, " ID ", %d);",
            UTF8_( dbname ), f_ref_id, f_entity_type, f_entity_id, f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".ReferenceEntity "
                "(id, ref_id, entity_type, entity_id, sequence)"
                "VALUES (" ID ", " ID ", %u, " ID ", %d);",
                UTF8_( dbname ), f_id, f_ref_id, f_entity_type, f_entity_id, f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".ReferenceEntity SET "
                "ref_id=" ID ", entity_type=%u, entity_id=" ID ", sequence=%d "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_ref_id, f_entity_type, f_entity_id, f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recReferenceEntity::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ref_id, entity_type, entity_id, sequence "
        "FROM \"%s\".ReferenceEntity WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ref_id      = GET_ID( result.GetInt64( 0 ) );
    f_entity_type = (Type) result.GetInt( 1 );
    f_entity_id   = GET_ID( result.GetInt64( 2 ) );
    f_sequence    = result.GetInt( 3 );
    return true;
}

bool recReferenceEntity::Equivalent( const recReferenceEntity& r2 ) const
{
    return
        f_ref_id == r2.f_ref_id &&
        f_entity_type == r2.f_entity_type &&
        f_entity_id == r2.f_entity_id;
}

void recReferenceEntity::Create( idt refID, Type type, idt entID, int* pseq )
{
    recReferenceEntity re;
    re.f_id = 0;
    re.f_ref_id = refID;
    re.f_entity_type = type;
    re.f_entity_id = entID;
    if( pseq ) {
        re.f_sequence = ++(*pseq);
    } else {
        re.f_sequence = recReference::GetNextEntitySequence( refID );
    }
    re.Save();
}

wxString recReferenceEntity::GetEntityIdStr() const
{
    switch( f_entity_type )
    {
    case TYPE_Place:
        return recPlace::GetIdStr( f_entity_id );
    case TYPE_Date:
        return recDate::GetIdStr( f_entity_id );
    case TYPE_Name:
        return recName::GetIdStr( f_entity_id );
    }
    return recGetIDStr( f_entity_id );
}

wxString recReferenceEntity::GetEntityStr( const wxString& dbname ) const
{
    switch( f_entity_type )
    {
    case TYPE_Place:
        return recPlace::GetAddressStr( f_entity_id, dbname );
    case TYPE_Date:
        return recDate::GetStr( f_entity_id, dbname );
    case TYPE_Name:
        return recName::GetNameStr( f_entity_id, dbname );
    }
    return "[Unknown entity]";
}

void recReferenceEntity::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE ReferenceEntity SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recReferenceEntity::CsvTitles()
{
    return std::string( "ID, Reference ID, Entity Type, Entity ID, Sequence\n" );
}

void recReferenceEntity::CsvWrite( std::ostream& out, idt id )
{
    recReferenceEntity re( id );
    recCsvWrite( out, re.FGetID() );
    recCsvWrite( out, re.FGetRefID() );
    recCsvWrite( out, re.FGetEntityType() );
    recCsvWrite( out, re.FGetEntityID() );
    recCsvWrite( out, re.FGetSequence(), '\n' );
}

bool recReferenceEntity::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_ref_id );
    recCsvRead( in, (int&) f_entity_type );
    recCsvRead( in, f_entity_id );
    recCsvRead( in, f_sequence );
    return bool( in );
}

void recReferenceEntity::DeleteType( Type type, idt entityID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "DELETE FROM ReferenceEntity WHERE entity_type=%d AND entity_id=" ID ";",
        (int) type, entityID
    );
    s_db->ExecuteUpdate( sql );
}


// End of recReference.cpp file
