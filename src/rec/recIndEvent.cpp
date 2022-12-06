/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recIndEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 IndividualEvent records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015..2022, Nick Matthews.
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

#include <rec/recIndEvent.h>

#include <rec/recIndividual.h>


//============================================================================
//-------------------------[ recIndividualEvent ]-----------------------------
//============================================================================

recIndividualEvent::recIndividualEvent( const recIndividualEvent& ep )
{
    f_id        = ep.f_id;
    f_higher_id = ep.f_higher_id;
    f_ind_id    = ep.f_ind_id;
    f_event_id  = ep.f_event_id;
    f_role_id   = ep.f_role_id;
    f_note      = ep.f_note;
    f_ind_seq   = ep.f_ind_seq;
}

void recIndividualEvent::Clear()
{
    f_id        = 0;
    f_higher_id = 0;
    f_ind_id    = 0;
    f_event_id  = 0;
    f_role_id   = 0;
    f_note      = "";
    f_ind_seq   = 0;
}

void recIndividualEvent::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".IndividualEvent"
            " (higher_id, ind_id, event_id, role_id, note, ind_seq)"
            " VALUES (" ID ", " ID ", " ID ", " ID ", '%q', %d);",
            UTF8_( dbname ), f_higher_id, f_ind_id, f_event_id,
            f_role_id, UTF8_(f_note), f_ind_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".IndividualEvent"
                " (id, higher_id, ind_id, event_id, role_id, note, ind_seq) "
                "VALUES (" ID ", " ID ", " ID ", " ID ", " ID ", '%q', %d);",
                UTF8_( dbname ), f_id, f_higher_id, f_ind_id, f_event_id,
                f_role_id, UTF8_(f_note), f_ind_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".IndividualEvent"
                " SET higher_id=" ID ", ind_id=" ID ", event_id=" ID ", role_id=" ID ","
                " note='%q', ind_seq=%d"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_higher_id, f_ind_id, f_event_id, f_role_id,
                UTF8_(f_note), f_ind_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recIndividualEvent::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT higher_id, ind_id, event_id, role_id, note, ind_seq "
        "FROM \"%s\".IndividualEvent WHERE id=" ID ";",
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
    f_ind_id    = GET_ID( result.GetInt64( 1 ) );
    f_event_id  = GET_ID( result.GetInt64( 2 ) );
    f_role_id   = GET_ID( result.GetInt64( 3 ) );
    f_note      = result.GetAsString( 4 );
    f_ind_seq   = result.GetInt( 5 );
    return true;
}

bool recIndividualEvent::Equivalent( const recIndividualEvent& r2 ) const
{
    return
        f_higher_id == r2.f_higher_id &&
        f_ind_id == r2.f_ind_id &&
        f_event_id == r2.f_event_id &&
        f_role_id == r2.f_role_id &&
        f_note == r2.f_note &&
        f_ind_seq == r2.f_ind_seq
    ;
}

idt recIndividualEvent::Create( idt indID, idt eID, idt roleID, const wxString& note )
{
    recIndividualEvent ie(0);
    ie.FSetIndID( indID );
    ie.FSetEventID( eID );
    ie.FSetRoleID( roleID );
    ie.FSetNote( note );
    ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indID ) + 1 );
    ie.Save();
    return ie.FGetID();
}

bool recIndividualEvent::Find(
    idt indID, idt eveID, idt roleID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 || eveID == 0 ) {
        Clear();
        return false;
    }

    if( roleID == 0 ) {
        sql.Format(
            "SELECT id, higher_id, role_id, note, ind_seq"
            " FROM \"%s\".IndividualEvent"
            " WHERE ind_id=" ID " AND event_id=" ID ";",
            UTF8_( dbname ), indID, eveID
        );
    } else {
        sql.Format(
            "SELECT id, higher_id, role_id, note, ind_seq"
            " FROM \"%s\".IndividualEvent"
            " WHERE ind_id=" ID " AND event_id=" ID " AND role_id=" ID ";",
            UTF8_( dbname ), indID, eveID, roleID
        );
    }
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_id        = GET_ID( result.GetInt64( 0 ) );
    f_higher_id = GET_ID( result.GetInt64( 1 ) );
    f_ind_id    = indID;
    f_event_id  = eveID;
    f_role_id   = GET_ID( result.GetInt64( 2 ) );
    f_note      = result.GetAsString( 3 );
    f_ind_seq   = result.GetInt( 4 );
    return true;
}

recIdVec recIndividualEvent::GetLowerIndEventIDs( idt ieID, const wxString& dbname )
{
    return recDb::ExecuteIdVec(
        "SELECT id FROM \"%s\".IndividualEvent WHERE higher_id=" ID ";",
        UTF8_( dbname ), ieID
    );
}

recIndEventVec recIndividualEvent::GetLowerIndEvents( idt ieID, const wxString& dbname )
{
    recIndEventVec vec;
    recIndividualEvent record;
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT IE.id, IE.ind_id, IE.event_id, IE.role_id, IE.note, IE.ind_seq"
        " FROM \"%s\".IndividualEvent IE, \"%s\".Event E"
        " WHERE IE.event_id=E.id AND IE.higher_id=" ID
        " ORDER BY E.date_pt;",
        UTF8_( dbname ), UTF8_( dbname ), ieID
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    record.FSetHigherID( ieID );
    while( result.NextRow() ) {
        record.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        record.FSetIndID( GET_ID( result.GetInt64( 1 ) ) );
        record.FSetEventID( GET_ID( result.GetInt64( 2 ) ) );
        record.FSetRoleID( GET_ID( result.GetInt64( 3 ) ) );
        record.FSetNote( result.GetAsString( 4 ) );
        record.FSetIndSeq( result.GetInt( 5 ) );
        vec.push_back( record );
    }
    return vec;
}

wxString recIndividualEvent::GetRoleStr( idt indID, idt typeID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ETR.name FROM \"%s\".IndividualEvent IE, \"%s\".EventTypeRole ETR"
        " WHERE IE.role_id=ETR.id AND IE.ind_id=" ID " AND ETR.type_id=" ID
        " ORDER BY IE.ind_seq;",
        UTF8_( dbname ), UTF8_( dbname ), indID, typeID
    );
    return ExecuteStr( sql );
}

std::string recIndividualEvent::CsvTitles()
{
    return std::string(
        "id, higher_id, ind_id, event_id, role_id, 'note', ind_seq\n"
    );
}

void recIndividualEvent::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recIndividualEvent ie( id, dbname );
    recCsvWrite( out, ie.FGetID() );
    recCsvWrite( out, ie.FGetIndID() );
    recCsvWrite( out, ie.FGetHigherID() );
    recCsvWrite( out, ie.FGetEventID() );
    recCsvWrite( out, ie.FGetRoleID() );
    recCsvWrite( out, ie.FGetNote() );
    recCsvWrite( out, ie.FGetIndSeq(), '\n' );
}

bool recIndividualEvent::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_ind_id );
    recCsvRead( in, f_higher_id );
    recCsvRead( in, f_event_id );
    recCsvRead( in, f_role_id );
    recCsvRead( in, f_note );
    recCsvRead( in, f_ind_seq );
    return bool( in );
}

// End of recIndEvent.cpp file
