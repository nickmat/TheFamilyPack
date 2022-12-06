/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventaPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventaPersona records.
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

#include <rec/recEventaPersona.h>

#include <rec/recEvent.h>
#include <rec/recEventa.h>
#include <rec/recPlace.h>
#include <rec/recIndividual.h>

//============================================================================
//--------------------------[ recEventaPersona ]------------------------------
//============================================================================

recEventaPersona::recEventaPersona( const recEventaPersona& ep )
{
    f_id           = ep.f_id;
    f_eventa_id    = ep.f_eventa_id;
    f_per_id       = ep.f_per_id;
    f_role_id      = ep.f_role_id;
    f_note         = ep.f_note;
    f_per_seq      = ep.f_per_seq;
}

void recEventaPersona::Clear()
{
    f_id           = 0;
    f_eventa_id   = 0;
    f_per_id       = 0;
    f_role_id      = 0;
    f_note         = wxEmptyString;
    f_per_seq      = 0;
}

void recEventaPersona::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".EventaPersona (eventa_id, per_id, role_id, note, per_seq) "
            "VALUES (" ID ", " ID ", " ID ", '%q', %d);",
            UTF8_( dbname ), f_eventa_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".EventaPersona (id, eventa_id, per_id, role_id, note, per_seq) "
                "VALUES (" ID ", " ID ", " ID ", " ID ", '%q', %d);",
                UTF8_( dbname ), f_id, f_eventa_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".EventaPersona SET eventa_id=" ID ", per_id=" ID ", role_id=" ID ", "
                "note='%q', per_seq=%d "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_eventa_id, f_per_id, f_role_id, UTF8_(f_note), f_per_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventaPersona::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT id, eventa_id, per_id, role_id, note, per_seq "
        "FROM \"%s\".EventaPersona WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_eventa_id   = GET_ID( result.GetInt64( 1 ) );
    f_per_id       = GET_ID( result.GetInt64( 2 ) );
    f_role_id      = GET_ID( result.GetInt64( 3 ) );
    f_note         = result.GetAsString( 4 );
    f_per_seq      = result.GetInt( 5 );
    return true;
}

bool recEventaPersona::Equivalent( const recEventaPersona& r2 ) const
{
    return
        f_eventa_id == r2.f_eventa_id &&
        f_per_id == r2.f_per_id &&
        f_role_id == r2.f_role_id &&
        f_note == r2.f_note &&
        f_per_seq == r2.f_per_seq
    ;
}

idt recEventaPersona::CreateLink( idt eaID, idt perID, idt roleID, const wxString & note )
{
    if ( eaID == 0 || perID == 0 ) return 0;
    recEventaPersona ep( 0 );
    ep.FSetRoleID( roleID );
    ep.FSetEventaID( eaID );
    ep.FSetPerID( perID );
    ep.FSetNote( note );
    ep.SetNextPerSequence( eaID );
    ep.Save();
    return ep.FGetID();
}

void recEventaPersona::SetNextPerSequence( idt eaID )
{
    int seq = ExecuteInt(
        "SELECT MAX(per_seq) FROM EventaPersona WHERE eventa_id=" ID ";",
        eaID
    );
    FSetPerSeq( seq + 1 );
}

wxString recEventaPersona::GetRoleStr( idt perID, idt typeID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT ETR.name FROM \"%s\".EventaPersona EP, \"%s\".EventTypeRole ETR"
        " WHERE EP.role_id=ETR.id AND EP.per_id=" ID " AND ETR.type_id=" ID
        " ORDER BY EP.per_seq;",
        UTF8_( dbname ), UTF8_( dbname ), perID, typeID
    );
    return ExecuteStr( sql );
}

bool recEventaPersona::LinkExists( const wxString& dbname ) const
{
    if( f_per_id == 0 || f_eventa_id == 0 || f_role_id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".EventaPersona "
        "WHERE eventa_id=" ID " AND per_id=" ID " AND role_id=" ID ";",
        UTF8_( dbname ), f_eventa_id, f_per_id, f_role_id
    );

    if( s_db->ExecuteScalar( sql ) == 0 ) {
        return false;
    }
    return true;
}

idt recEventaPersona::Transfer( idt from_eapaID, const wxString& fromdb,
    idt to_eaID, idt to_eapaID, const wxString& todb )
{
    if( from_eapaID == 0 ) return 0;

    recEventaPersona from_eapa( from_eapaID, fromdb );
    wxASSERT( from_eapa.FGetID() != 0 );

    recEventaPersona to_eapa( to_eapaID, todb );
    to_eapa.Delete( todb );

    recEventaPersona new_eapa( 0 );
    new_eapa.FSetID( to_eapaID );
    new_eapa.FSetEventaID( to_eaID );
    idt to_perID = recPersona::Transfer( from_eapa.FGetPerID(), fromdb, 0, todb );
    wxASSERT( to_perID != 0 );
    new_eapa.FSetPerID( to_perID );
    idt to_roleID = recEventTypeRole::Transfer( from_eapa.FGetRoleID(), fromdb, todb );
    wxASSERT( to_roleID != 0 );
    new_eapa.FSetRoleID( to_roleID );
    new_eapa.FSetNote( from_eapa.FGetNote() );
    new_eapa.FSetPerSeq( from_eapa.FGetPerSeq() );
    new_eapa.Save( todb );
    to_eapaID = new_eapa.FGetID();

    recEventTypeRole::DeleteIfOrphaned( to_eapaID, todb );
    return to_eapaID;
}

std::string recEventaPersona::CsvTitles()
{
    return std::string(
        "id, eventa_id, per_id, role_id, 'note', per_seq\n"
    );
}

void recEventaPersona::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recEventaPersona ep( id, dbname );
    recCsvWrite( out, ep.FGetID() );
    recCsvWrite( out, ep.FGetEventaID() );
    recCsvWrite( out, ep.FGetPerID() );
    recCsvWrite( out, ep.FGetRoleID() );
    recCsvWrite( out, ep.FGetNote() );
    recCsvWrite( out, ep.FGetPerSeq(), '\n' );
}

bool recEventaPersona::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_eventa_id );
    recCsvRead( in, f_per_id );
    recCsvRead( in, f_role_id );
    recCsvRead( in, f_note );
    recCsvRead( in, f_per_seq );
    return bool( in );
}

bool recEventaPersona::RemoveFromDatabase( idt eapaID, const wxString& dbname )
{
    recEventaPersona eapa( eapaID, dbname );
    bool ret = Delete( eapaID, dbname );
    recEventTypeRole::DeleteIfOrphaned( eapa.FGetRoleID(), dbname );
    return ret;
}


// End of recEventaPersona.cpp file
