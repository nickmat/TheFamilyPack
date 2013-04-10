/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recUpgrade.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage upgrading between database versions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd April 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <rec/recVersion.h>

// This is the database version that this program is designed to work with.
const int recVerMajor    = 0;
const int recVerMinor    = 0;
const int recVerRev      = 10;
const int recVerTest     = 3;
const wxStringCharType* recVerStr = wxS("TFPD-0.0.10.3");

//============================================================================
//                 Code to upgrade old versions
//============================================================================

namespace {

void UpgradeRev0_0_9to10( int test )
{
    if( test < 25 ) {
        throw wxSQLite3Exception( 0, _("Cannot handle old database version.") );
    }
    wxASSERT( test == 25 );
    // Version 0.0.9.25 to 0.0.10.0
    // Change to Core Data only, only affects new databases.
    // Removed intitial F1 family record for new databases. 
    char* query =
        "BEGIN;\n"
        "UPDATE Version SET revision=10, test=0 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_0to0_0_10_1()
{
    // Version 0.0.10.0 to 0.0.10.1
    // Split the Event table into Event and a new EventRecord table.
    char* query =
        "BEGIN;\n"
        "ALTER TABLE Event RENAME TO OldEvent;\n"

        "CREATE TABLE Event (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
        "  date1_id INTEGER NOT NULL,\n"
        "  date2_id INTEGER NOT NULL,\n"
        "  place_id INTEGER NOT NULL,\n"
        "  note TEXT NOT NULL,\n"
        "  date_pt INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO Event (id, title, type_id, date1_id,"
        " date2_id, place_id, note, date_pt)"
        " SELECT E.id, E.title, E.type_id, E.date1_id,"
        " E.date2_id, E.place_id, E.note, E.date_pt"
        " FROM OldEvent E, IndividualEvent IE"
        " WHERE E.id=IE.event_id GROUP BY E.id;\n"

        "CREATE TABLE EventRecord (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
        "  date1_id INTEGER NOT NULL,\n"
        "  date2_id INTEGER NOT NULL,\n"
        "  place_id INTEGER NOT NULL,\n"
        "  note TEXT NOT NULL,\n"
        "  date_pt INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO EventRecord (id, title, type_id, date1_id,"
        " date2_id, place_id, note, date_pt)"
        " SELECT E.id, E.title, E.type_id, E.date1_id,"
        " E.date2_id, E.place_id, E.note, E.date_pt"
        " FROM OldEvent E, EventPersona EP"
        " WHERE E.id=EP.event_id GROUP BY E.id;\n"

        "DROP TABLE OldEvent;\n"
        "UPDATE Version SET test=1 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_1to0_0_10_2()
{
    // Version 0.0.10.1 to 0.0.10.2
    // Add a new EventEventRecord table.
    char* query1 =
        "BEGIN;\n"

        "CREATE TABLE EventEventRecord (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  event_rec_id INTEGER NOT NULL REFERENCES EventRecord(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  note TEXT\n"
        ");\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query1 );

    wxSQLite3ResultSet ids = recDb::GetDb()->ExecuteQuery( "SELECT id FROM Event;" );
    while( ids.NextRow() ) {
        idt eventID = GET_ID( ids.GetInt64( 0 ) );
        wxSQLite3StatementBuffer sql;
        sql.Format(
            "SELECT id FROM "
            "  EventRecord "
            "JOIN "
            "  (SELECT DISTINCT event_id FROM "
            "   (SELECT EP.event_id, LP.ind_per_id FROM "
            "   LinkPersona LP, EventPersona EP, Event E, EventTypeRole R "
            "   WHERE LP.ref_per_id=EP.per_id AND EP.role_id=R.id AND E.id="ID" "
            "    AND R.type_id=E.type_id AND NOT R.prime=0) "
            "  JOIN "
            "   (SELECT I.per_id FROM IndividualEvent IE, Individual I"
            "    WHERE IE.ind_id=I.id AND IE.event_id="ID") "
            "  ON ind_per_id=per_id) "
            "ON id=event_id;",
            eventID, eventID
        );
        wxSQLite3ResultSet result = recDb::GetDb()->ExecuteQuery( sql );
        while( result.NextRow() ) {
            wxSQLite3StatementBuffer sql2;
            sql2.Format(
                "INSERT INTO EventEventRecord "
                "(event_id, event_rec_id, conf, note) "
                "VALUES ("ID", "ID", 0.999, '');",
                eventID, GET_ID( result.GetInt64( 0 ) )
            );
            recDb::GetDb()->ExecuteUpdate( sql2 );
        }
    }

    char* query =
        "UPDATE Version SET test=2 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_2to0_0_10_3()
{
    // Version 0.0.10.2 to 0.0.10.3
    // Add column higher_id to table Event.
    // Change column event_id to event_rec_id in table EventPersona.

    char* query =
        "BEGIN;\n"

        "ALTER TABLE Event RENAME TO OldEvent;\n"
        "CREATE TABLE Event (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  higher_id INTEGER NOT NULL,\n"
        "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
        "  date1_id INTEGER NOT NULL,\n"
        "  date2_id INTEGER NOT NULL,\n"
        "  place_id INTEGER NOT NULL,\n"
        "  note TEXT NOT NULL,\n"
        "  date_pt INTEGER NOT NULL\n"
        ");\n"
        "INSERT INTO Event"
        " (id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt)"
        " SELECT id, title, 0, type_id, date1_id, date2_id, place_id, note, date_pt"
        " FROM OldEvent;\n"
        "DROP TABLE OldEvent;\n"

        "ALTER TABLE EventPersona RENAME TO OldEventPersona;\n"
        "CREATE TABLE EventPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  event_rec_id INTEGER NOT NULL REFERENCES EventRecord(id),\n"
        "  per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
        "  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),\n"
        "  note TEXT NOT NULL,\n"
        "  per_seq INTEGER NOT NULL\n"
        ");\n"
        "INSERT INTO EventPersona"
        " (id, event_rec_id, per_id, role_id, note, per_seq)"
        " SELECT id, event_id, per_id, role_id, note, per_seq"
        " FROM OldEventPersona;\n"
        "DROP TABLE OldEventPersona;\n"

        "UPDATE Version SET test=3 WHERE id=1;\n"
        "COMMIT;\n"
        "VACUUM;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeRev0_0_10toCurrent( int test )
{
    switch( test )
    {
    case 0: UpgradeTest0_0_10_0to0_0_10_1();  // Fall thru intended
    case 1: UpgradeTest0_0_10_1to0_0_10_2();
    case 2: UpgradeTest0_0_10_2to0_0_10_3();
    }
}

} // namespace

bool recDoUpgrade()
{
    recVersion v;
    if( v.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        return true; // Already current vertion
    }
    if( v.IsLessThan( 0, 0, 9, 25 ) ) {
        recMessage(
            wxString::Format(
                _("Cannot read old database version %s file."),
                v.GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( v.IsMoreThan( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        recMessage(
            wxString::Format(
                _("Cannot read future database version %s file."),
                v.GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( recPermissionToUpgrade() == false ) {
        return false;
    }

    try {
        if( v.IsEqual( 0, 0, 9 ) ) {
            UpgradeRev0_0_9to10( v.FGetTest() );
            v.Read();
        }
        if( v.IsEqual( 0, 0, 10 ) ) {
            UpgradeRev0_0_10toCurrent( v.FGetTest() );
            v.Read();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        return false;
    }

    wxASSERT( v.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) );
    return true;
}

// End of recVersion.cpp file
