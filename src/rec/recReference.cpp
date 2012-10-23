/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recReference.h>
#include <rec/recName.h>


recReference::recReference( const recReference& r )
{
    f_id        = r.f_id;
    f_title     = r.f_title;
    f_statement = r.f_statement;
}

void recReference::Clear()
{
    f_id        = 0;
    f_title     = wxEmptyString;
    f_statement = wxEmptyString;
}

void recReference::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Reference (title, statement)"
            "VALUES ('%q', '%q');",
            UTF8_(f_title), UTF8_(f_statement)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Reference (id, title, statement)"
                "VALUES ("ID", '%q', '%q');",
                f_id, UTF8_(f_title), UTF8_(f_statement)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Reference SET title='%q', statement='%q' WHERE id="ID";",
                UTF8_(f_title), UTF8_(f_statement), f_id
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

    sql.Format( "SELECT * FROM Reference WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_title     = result.GetAsString( 1 );
    f_statement = result.GetAsString( 2 );
    return true;
}

wxString recReference::GetTitle( idt refID )
{
    return ExecuteStr( "SELECT title FROM Reference WHERE id="ID";", refID );
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
        "WHERE ref_id="ID" ORDER BY sequence;",
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

wxSQLite3ResultSet recReference::GetTitleList()
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, title FROM Reference ORDER BY id;"
    );
    return s_db->ExecuteQuery( sql );
}

recIdVec recReference::GetPersonaList( idt refID )
{
    recIdVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id FROM Persona WHERE ref_id="ID";",
        refID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        vec.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return vec;
}

int recReference::GetPersonaCount( idt refID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM Persona WHERE ref_id="ID";",
        refID
    );
    return s_db->ExecuteScalar( sql );
}


//----------------------------------------------------------

const wxString recReferenceEntity::sm_typeStr[recReferenceEntity::TYPE_MAX] = {
    _("Default"),      // TYPE_Unstated
    _("Source"),       // TYPE_Source
    _("Event"),        // TYPE_Event
    _("Place"),        // TYPE_Place
    _("Date"),         // TYPE_Date
    _("Relationship"), // TYPE_Relationship
    _("Attribute"),    // TYPE_Attribute
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
            "VALUES ("ID", %u, "ID", %d);",
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
                "VALUES ("ID", "ID", %u, "ID", %d);",
                f_id, f_ref_id, f_entity_type, f_entity_id, f_sequence
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE ReferenceEntity SET "
                "ref_id="ID", entity_type=%u, entity_id="ID", sequence=%d "
                "WHERE id="ID";",
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
        "FROM ReferenceEntity WHERE id="ID";",
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
    re.f_sequence = ++(*pseq);
    re.Save();
}



idt recReferenceEntity::FindReferenceID( Type type, idt entityID )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ref_id FROM ReferenceEntity "
        "WHERE entity_type=%d AND entity_id="ID";",
        (int) type, entityID
    );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return GET_ID( result.GetInt64( 0 ) );
}

// End of recReference.cpp file
