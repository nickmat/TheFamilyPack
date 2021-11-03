/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 ~ 2021, Nick Matthews.
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


recReference::recReference( const recReference& r )
{
    f_id        = r.f_id;
    f_higher_id = r.f_higher_id;
    f_title     = r.f_title;
    f_statement = r.f_statement;
    f_user_ref  = r.f_user_ref;
}

void recReference::Clear()
{
    f_id        = 0;
    f_higher_id = 0;
    f_title     = "";
    f_statement = "";
    f_user_ref  = "";
}

void recReference::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Reference (higher_id, title, statement, user_ref)"
            "VALUES (" ID ", '%q', '%q', '%q');",
            f_higher_id, UTF8_(f_title), UTF8_(f_statement), UTF8_(f_user_ref)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Reference (id, higher_id, title, statement, user_ref)"
                " VALUES (" ID ", " ID ", '%q', '%q', '%q');",
                f_id, f_higher_id, UTF8_(f_title), UTF8_(f_statement), UTF8_(f_user_ref)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Reference SET higher_id=" ID ", title = '%q', statement = '%q', user_ref = '%q'"
                " WHERE id=" ID ";",
                f_higher_id, UTF8_(f_title), UTF8_(f_statement), UTF8_(f_user_ref), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recReference::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT higher_id, title, statement, user_ref"
        " FROM Reference WHERE id=" ID ";",
        f_id
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
    f_user_ref  = result.GetAsString( 3 );
    return true;
}

wxString recReference::GetTitle( idt refID )
{
    return ExecuteStr( "SELECT title FROM Reference WHERE id=" ID ";", refID );
}

recRefEntVec recReference::ReadReferenceEntitys()
{
    recRefEntVec vec;
    recReferenceEntity record;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        return vec;
    }

    sql.Format(
        "SELECT id, entity_type, entity_id, sequence FROM ReferenceEntity "
        "WHERE ref_id=" ID " ORDER BY sequence;",
        f_id
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

wxSQLite3Table recReference::GetTitleList()
{
    return s_db->GetTable( "SELECT id, title FROM Reference ORDER BY id;" );
}

wxSQLite3Table recReference::GetTitleList( idt offset, int limit )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM Reference ORDER BY id LIMIT " ID ", %d;",
        offset, limit
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

recIdVec recReference::GetPersonaList( idt refID )
{
    return ExecuteIdVec( "SELECT id FROM Persona WHERE ref_id=" ID ";", refID );
}

int recReference::GetPersonaCount( idt refID )
{
    return ExecuteInt( "SELECT COUNT(*) FROM Persona WHERE ref_id=" ID ";", refID );
}

recIdVec recReference::GetMediaList( idt refID )
{
    return ExecuteIdVec( "SELECT id FROM Media WHERE ref_id=" ID ";", refID );
}

int recReference::GetMediaCount( idt refID )
{
    return ExecuteInt( "SELECT COUNT(*) FROM Media WHERE ref_id=" ID ";", refID );
}

recIdVec recReference::GetEventaList( idt refID )
{
    return ExecuteIdVec( "SELECT id FROM Eventa WHERE ref_id=" ID ";", refID );
}

int recReference::GetEventaCount( idt refID )
{
    return ExecuteInt( "SELECT COUNT(*) FROM Eventa WHERE ref_id=" ID ";", refID );
}

recIdVec recReference::GetIdVecForEntity( idt refID, recReferenceEntity::Type type )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT entity_id FROM ReferenceEntity"
        " WHERE entity_type=%d AND ref_id=" ID ";",
        (int) type, refID
    );
    return ExecuteIdVec( sql );
}

void recReference::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

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
        "UPDATE Reference SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recReference::CsvTitles()
{
    return std::string( "ID, Higher ID, Title, Statement, User Reference\n");
}

void recReference::CsvWrite( std::ostream& out, idt id )
{
    recReference ref( id );
    recCsvWrite( out, ref.FGetID() );
    recCsvWrite( out, ref.FGetHigherId() );
    recCsvWrite( out, ref.FGetTitle() );
    recCsvWrite( out, ref.FGetStatement() );
    recCsvWrite( out, ref.FGetUserRef(), '\n' );
}

//----------------------------------------------------------

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

void recReferenceEntity::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO ReferenceEntity "
            "(ref_id, entity_type, entity_id, sequence)"
            "VALUES (" ID ", %u, " ID ", %d);",
            f_ref_id, f_entity_type, f_entity_id, f_sequence
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO ReferenceEntity "
                "(id, ref_id, entity_type, entity_id, sequence)"
                "VALUES (" ID ", " ID ", %u, " ID ", %d);",
                f_id, f_ref_id, f_entity_type, f_entity_id, f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE ReferenceEntity SET "
                "ref_id=" ID ", entity_type=%u, entity_id=" ID ", sequence=%d "
                "WHERE id=" ID ";",
                f_ref_id, f_entity_type, f_entity_id, f_sequence, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recReferenceEntity::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ref_id, entity_type, entity_id, sequence "
        "FROM ReferenceEntity WHERE id=" ID ";",
        f_id
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

wxString recReferenceEntity::GetEntityStr() const
{
    switch( f_entity_type )
    {
    case TYPE_Place:
        return recPlace::GetAddressStr( f_entity_id );
    case TYPE_Date:
        return recDate::GetStr( f_entity_id );
    case TYPE_Name:
        return recName::GetNameStr( f_entity_id );
    }
    return "[Unknown entity]";
}

idt recReferenceEntity::FindReferenceID( Type type, idt entityID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ref_id FROM ReferenceEntity "
        "WHERE entity_type=%d AND entity_id=" ID ";",
        (int) type, entityID
    );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return GET_ID( result.GetInt64( 0 ) );
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

void recReferenceEntity::Delete( Type type, idt entityID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "DELETE FROM ReferenceEntity WHERE entity_type=%d AND entity_id=" ID ";",
        (int) type, entityID
    );
    s_db->ExecuteUpdate( sql );
}

// End of recReference.cpp file
