/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recEventEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventEventa records.
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

#include <rec/recEventEventa.h>

#include <rec/recEventa.h>
#include <rec/recIndividual.h>

//============================================================================
//--------------------------[ recEventEventa ]--------------------------------
//============================================================================

recEventEventa::recEventEventa( const recEventEventa& d )
{
    f_id           = d.f_id;
    f_event_id     = d.f_event_id;
    f_eventa_id    = d.f_eventa_id;
    f_conf         = d.f_conf;
    f_note         = d.f_note;
}

void recEventEventa::Clear()
{
    f_id           = 0;
    f_event_id     = 0;
    f_eventa_id    = 0;
    f_conf         = 0;
    f_note         = "";
}

void recEventEventa::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO EventEventa "
            "(event_id, eventa_id, conf, note) "
            "VALUES (" ID ", " ID ", %f, '%q');",
            f_event_id, f_eventa_id, f_conf, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO EventEventa "
                "(id, event_id, eventa_id, conf, note) "
                "VALUES (" ID ", " ID ", " ID ", %f, '%q');",
                f_id, f_event_id, f_eventa_id, f_conf, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE EventEventa SET event_id=" ID ", eventa_id=" ID ", "
                "conf=%f, note='%q' "
                "WHERE id=" ID ";",
                f_event_id, f_eventa_id, f_conf,
                UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recEventEventa::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT event_id, eventa_id, conf, note "
        "FROM EventEventa WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_event_id     = GET_ID( result.GetInt64( 0 ) );
    f_eventa_id   = GET_ID( result.GetInt64( 1 ) );
    f_conf         = result.GetDouble( 2 );
    f_note         = result.GetAsString( 3 );
    return true;
}

bool recEventEventa::Equivalent( const recEventEventa& r2 ) const
{
    return
        FGetEventID() == r2.FGetEventID() &&
        FGetEventaID() == r2.FGetEventaID() &&
        FGetConf() == r2.FGetConf() &&
        FGetNote() == r2.FGetNote()
    ;
}

idt recEventEventa::Create( idt eID, idt eaID, double conf, const wxString& note )
{
    recEventEventa eea(eID, eaID, conf, note);
    eea.Save();
    return eea.FGetID();
}

void recEventEventa::NormaliseIndEventLinks() const
{
    wxASSERT( FGetID() != 0 );

    recEventaPersonaVec eps = recEventa::GetEventaPersonas( FGetEventaID() );
    recIndEventVec ies = recEvent::GetIndividualEvents( FGetEventID() );
    for( size_t i = 0 ; i < eps.size() ; i++ ) {
        recIdVec indIDs = recPersona::GetIndividualIDs( eps[i].FGetPerID() );
        for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
            bool ok = false;
            for( size_t k = 0 ; k < ies.size() ; k++ ) {
                if( indIDs[j] == ies[k].FGetIndID() ) {
                    ok = true;
                    break;
                } else {
                    ok = false;
                }
            }
            if( ! ok ) {
                // Create an IndividualEvent to match EventaPersona.
                // TODO: Check for, and set, higher_id field.
                recIndividualEvent ie(0);
                ie.FSetIndID( indIDs[j] );
                ie.FSetEventID( FGetEventID() );
                ie.FSetRoleID( eps[i].FGetRoleID() );
                ie.FSetNote( eps[i].FGetNote() );
                ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indIDs[j] ) + 1 );
                ie.Save();
            }
        }
    }
}

/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recEventEventa::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_event_id == 0 || f_eventa_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, conf, note FROM EventEventa "
        "WHERE event_id=" ID " AND eventa_id=" ID ";",
        f_event_id, f_eventa_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_conf = result.GetDouble( 1 );
    f_note = result.GetAsString( 2 );
    return true;
}

/*! Given the Event id and Eventa id, find the matching record id.
 */
idt recEventEventa::Find( idt eID, idt erID )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( eID == 0 || erID == 0 ) return 0; // Only find single record

    sql.Format(
        "SELECT id FROM EventEventa "
        "WHERE event_id=" ID " AND eventa_id=" ID ";",
        eID, erID
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        return 0;
    }
    result.SetRow( 0 );
    return GET_ID( result.GetInt64( 0 ) );
}

// End of recEvent.cpp file
