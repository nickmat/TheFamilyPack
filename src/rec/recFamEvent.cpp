/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recFamEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyEvent records.
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

#include <rec/recFamEvent.h>

#include <rec/recFamily.h>


//============================================================================
//-------------------------[ recFamilyEvent ]---------------------------------
//============================================================================

recFamilyEvent::recFamilyEvent( const recFamilyEvent& ep )
{
    f_id       = ep.f_id;
    f_fam_id   = ep.f_fam_id;
    f_event_id = ep.f_event_id;
    f_note     = ep.f_note;
    f_fam_seq  = ep.f_fam_seq;
}

void recFamilyEvent::Clear()
{
    f_id       = 0;
    f_fam_id   = 0;
    f_event_id = 0;
    f_note     = wxEmptyString;
    f_fam_seq  = 0;
}

void recFamilyEvent::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".FamilyEvent (fam_id, event_id, note, fam_seq) "
            "VALUES (" ID ", " ID ", '%q', %d);",
            UTF8_( dbname ), f_fam_id, f_event_id, UTF8_(f_note), f_fam_seq
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".FamilyEvent (id, fam_id, event_id, note, fam_seq) "
                "VALUES (" ID ", " ID ", " ID ", '%q', %d);",
                UTF8_( dbname ), f_id, f_fam_id, f_event_id, UTF8_(f_note), f_fam_seq
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".FamilyEvent SET fam_id=" ID ", event_id=" ID ", note='%q',"
                " fam_seq=%d WHERE id=" ID ";",
                UTF8_( dbname ), f_fam_id, f_event_id, UTF8_(f_note), f_fam_seq, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamilyEvent::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT fam_id, event_id, note, fam_seq"
        " FROM \"%s\".FamilyEvent WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_fam_id   = GET_ID( result.GetInt64( 0 ) );
    f_event_id = GET_ID( result.GetInt64( 1 ) );
    f_note     = result.GetAsString( 2 );
    f_fam_seq  = result.GetInt( 3 );
    return true;
}

bool recFamilyEvent::Equivalent( const recFamilyEvent& r2 ) const
{
    return
        f_fam_id == r2.f_fam_id &&
        f_event_id == r2.f_event_id &&
        f_note == r2.f_note &&
        f_fam_seq == r2.f_fam_seq
    ;
}

idt recFamilyEvent::Create( idt eveID, idt famID, const wxString& note )
{
    recFamilyEvent fe(0);
    fe.FSetEventID( eveID );
    fe.FSetFamID( famID );
    fe.FSetNote( note );
    fe.FSetFamSeq( recFamily::GetMaxEventSeqNumber( famID ) + 1 );
    fe.Save();
    return fe.FGetID();
}

std::string recFamilyEvent::CsvTitles()
{
    return std::string(
        "ID, Family ID, Event ID, Note, Family Sequence\n"
    );
}

void recFamilyEvent::CsvWrite( std::ostream& out, idt id )
{
    recFamilyEvent fe( id );
    recCsvWrite( out, fe.FGetID() );
    recCsvWrite( out, fe.FGetFamID() );
    recCsvWrite( out, fe.FGetEventID() );
    recCsvWrite( out, fe.FGetNote() );
    recCsvWrite( out, fe.FGetFamSeq(), '\n' );
}

bool recFamilyEvent::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_fam_id );
    recCsvRead( in, f_event_id );
    recCsvRead( in, f_note );
    recCsvRead( in, f_fam_seq );
    return bool( in );
}

// End of recEvent.cpp file
