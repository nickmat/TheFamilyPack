/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recUpgrade.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage upgrading between database versions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd April 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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

// This is the database full version that this program is designed to work with.
const int recVerMajor = 0;
const int recVerMinor = 0;
const int recVerRev = 10;
const int recVerTest = 31;                       // <<======<<<<
const char* recFullVersion = "TFPD-v0.0.10.31";  // <<======<<<<

// This is the database Media-only version that this program can work with.
// If the full version matches, then this is assumed to match as well.
// If one is full and one Media-only then these should match.
const int recMediaVerMajor = 0;
const int recMediaVerMinor = 0;
const int recMediaVerRev = 0;
const int recMediaVerTest = 4;                   // <<======<<<<
const char* recMediaVersion = "MDD-v0.0.0.4";    // <<======<<<<

wxString recGetCurrentVersionStr()
{
    recDb::DbType type = recDb::GetDatabaseType( "Main" );
    return recGetCurrentVersionStr( type );
}

wxString recGetCurrentVersionStr( recDb::DbType type )
{
    switch( type ) {
    case recDb::DbType::full:
        return recFullVersion;
    case recDb::DbType::media_data_only:
        return recMediaVersion;
    }
    return _( "Unknown database type" );
}

//============================================================================
//                 Code to upgrade old versions
//============================================================================

namespace {

    void mdUpgradeTest0_0_0_1to0_0_0_2( const wxString& dbname )
    {
        // MediaData Version 0.0.0.1 to 0.0.0.2
        // Add title and type fields to MediaData

        wxString update = "BEGIN;\n";

        update <<
            "INSERT INTO MediaData (id, data, type, privacy, file) VALUES(0, '', 0, 0, '');\n"

            "UPDATE \"" << dbname << "\".Version SET test=2 WHERE id=2;\n"
            "COMMIT;\n"
            ;
        recDb::GetDb()->ExecuteUpdate( update );
    }

    void mdUpgradeTest0_0_0_2to0_0_0_3( const wxString& dbname )
    {
        // MediaData Version 0.0.0.2 to 0.0.0.3
        // Add record id=0

        wxString update;

        update <<
            "PRAGMA foreign_keys=OFF;\n"
            "BEGIN;\n"

            "INSERT INTO \"" << dbname << "\".MediaData (id, data, type, privacy, file) VALUES(0, '', 0, 0, '');\n"

            "UPDATE \"" << dbname << "\".Version SET test=3 WHERE id=2;\n"
            "COMMIT;\n"
            ;

        recDb::GetDb()->ExecuteUpdate( update );
    }

    void mdUpgradeTest0_0_0_3to0_0_0_4( const wxString& dbname )
    {
        // MediaData Version 0.0.0.3 to 0.0.0.4
        // Add uid and changed fields to MediaData

        wxString update = "BEGIN;\n";

        update <<
            "CREATE TABLE \"" << dbname << "\".NewMediaData (\n"
            "  id INTEGER PRIMARY KEY,\n"
            "  title TEXT NULL,\n"
            "  data BLOB NOT NULL,\n"
            "  type INTEGER NOT NULL,\n"
            "  privacy INTEGER NOT NULL,\n"
            "  copyright TEXT NULL,\n"
            "  file TEXT NOT NULL,\n"
            "  uid TEXT NOT NULL,\n"
            "  changed INTEGER NOT NULL\n"
            ");\n"
            "INSERT INTO \"" << dbname << "\".NewMediaData"
            " (id, title, data, type, privacy, copyright, file, uid, changed)"
            " SELECT id, title, data, type, privacy, copyright, file, '', 2459655"
            " FROM \"" << dbname << "\".MediaData;\n"
            "DROP TABLE \"" << dbname << "\".MediaData;\n"
            "ALTER TABLE \"" << dbname << "\".NewMediaData RENAME TO MediaData;\n"
            ;

        // Fill MediaData table uid field
        wxString query = "SELECT id FROM \"" + dbname + "\".MediaData WHERE id>0;\n"; // Get mdID list
        wxSQLite3Table table = recDb::GetDb()->GetTable( query );
        size_t size = (size_t) table.GetRowCount();
        for( size_t i = 0; i < size; i++ ) {
            table.SetRow( i );
            update <<
                "UPDATE \"" << dbname << "\".MediaData"
                " SET uid='" << recCreateUid() << "'"
                " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
        }

        update <<
            "UPDATE \"" << dbname << "\".Version SET test=4 WHERE id=2;\n"
            "COMMIT;\n"
            ;
        recDb::GetDb()->ExecuteUpdate( update );
    }

    void mdUpgradeRev0_0_0toCurrent( int test, const wxString& dbname )
    {
        switch( test )
        {
        case 1: mdUpgradeTest0_0_0_1to0_0_0_2( dbname );  // Fall thru intended
        case 2: mdUpgradeTest0_0_0_2to0_0_0_3( dbname );
        case 3: mdUpgradeTest0_0_0_3to0_0_0_4( dbname );
        }
    }

} // namspace

bool recDoMediaUpgrade( const wxString& dbname )
{
    recVersion ver( recDb::DbType::media_data_only, dbname );
    if( ver.IsEqual( recMediaVerMajor, recMediaVerMinor, recMediaVerRev, recMediaVerTest ) ) {
        return true; // Already current version
    }
    wxString verstr = ver.GetVersionStr();
    if( ver.IsMoreThan( recMediaVerMajor, recMediaVerMinor, recMediaVerRev, recMediaVerTest ) ) {
        recMessage(
            wxString::Format(
                _( "Cannot read future media database version %s file." ),
                verstr
            ),
            _( "Upgrade Test" )
        );
        return false;
    }
    if( recPermissionToUpgrade( verstr, recMediaVersion ) == false ) {
        return false;
    }

    try {
        if( ver.IsEqual( 0, 0, 0 ) ) {
            mdUpgradeRev0_0_0toCurrent( ver.FGetTest(), dbname );
            ver.ReadType( recDb::DbType::media_data_only );
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        return false;
    }

    wxASSERT( ver.IsEqual( recMediaVerMajor, recMediaVerMinor, recMediaVerRev, recMediaVerTest ) );
    return true;
}


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
            "   WHERE LP.ref_per_id=EP.per_id AND EP.role_id=R.id AND E.id=" ID " "
            "    AND R.type_id=E.type_id AND NOT R.prime=0) "
            "  JOIN "
            "   (SELECT I.per_id FROM IndividualEvent IE, Individual I"
            "    WHERE IE.ind_id=I.id AND IE.event_id=" ID ") "
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
                "VALUES (" ID ", " ID ", 0.999, '');",
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
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_3to0_0_10_4()
{
    // Version 0.0.10.3 to 0.0.10.4
    // Add column ind_id to table Name.

    char* query =
        "BEGIN;\n"

        "ALTER TABLE Name RENAME TO OldName;\n"
        "CREATE TABLE Name (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ind_id INTEGER NOT NULL,\n"
        "  per_id INTEGER NOT NULL,\n"
        "  style_id INTEGER NOT NULL REFERENCES NameStyle(id),\n"
        "  sequence INTEGER\n"
        ");\n"
        "INSERT INTO Name"
        " (id, ind_id, per_id, style_id, sequence)"
        " SELECT N.id, 0, N.per_id, N.style_id, N.sequence"
        " FROM OldName N, Persona P WHERE"
        " N.per_id=P.id AND P.ref_id<>0;\n"
        "INSERT INTO Name"
        " (id, ind_id, per_id, style_id, sequence)"
        " SELECT N.id, I.id, 0, N.style_id, N.sequence"
        " FROM OldName N, Persona P, Individual I"
        " WHERE N.per_id=P.id AND P.ref_id=0 AND P.id=I.per_id;\n"
        "DROP TABLE OldName;\n"

        "UPDATE Version SET test=4 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_4to0_0_10_5()
{
    // Version 0.0.10.4 to 0.0.10.5
    // Remove columns fam_id and per_id from the Individual table and add columns
    // sex and note.
    // Rename LinkPersona table to IndividualPersona and rename columns ind_per_id
    // and ref_per_id to ind_id and per_id respectively.

    char* query =
        "BEGIN;\n"

        "CREATE TABLE IndividualPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ind_id INTEGER NOT NULL REFERENCES Individual(id),\n"
        "  per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  note TEXT\n"
        ");\n"
        "INSERT INTO IndividualPersona"
        " (id, ind_id, per_id, conf, note)"
        " SELECT L.id, I.id, L.ref_per_id, L.conf, L.comment"
        " FROM LinkPersona L, Individual I WHERE"
        " L.ind_per_id=I.per_id;\n"
        "DROP TABLE LinkPersona;\n"

        "ALTER TABLE Individual RENAME TO OldIndividual;\n"
        "CREATE TABLE Individual (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  sex INTEGER NOT NULL,\n"
        "  name TEXT,\n"
        "  surname TEXT,\n"
        "  epitaph TEXT,\n"
        "  note TEXT NOT NULL,\n"
        "  fam_id INTEGER NOT NULL\n"
        ");\n"
        "INSERT INTO Individual"
        " (id, sex, name, surname, epitaph, note, fam_id)"
        " SELECT I.id, P.sex, I.given, I.surname, I.epitaph, P.note, I.fam_id"
        " FROM OldIndividual I, Persona P WHERE"
        " I.per_id=P.id;\n"
        "DELETE FROM Persona WHERE ref_id=0;\n"
        "DROP TABLE OldIndividual;\n"

        "UPDATE Version SET test=5 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_5to0_0_10_6()
{
    // Version 0.0.10.5 to 0.0.10.6
    // Rename table EventRecord to Eventum
    // Rename table EventEventRecord to EventEventum
    // Rename column EventEvetum.event_rec_id to eventum_id
    // Rename table EventPersona to EventumPersona
    // Rename column EventumPersona.event_rec_id to eventum_id

    char* query =
        "BEGIN;\n"

        "ALTER TABLE EventRecord RENAME TO Eventum;\n"

        "CREATE TABLE EventEventum (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  eventum_id INTEGER NOT NULL REFERENCES Eventum(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  note TEXT\n"
        ");\n"
        "INSERT INTO EventEventum"
        " (id, event_id, eventum_id, conf, note)"
        " SELECT id, event_id, event_rec_id, conf, note"
        " FROM EventEventRecord;\n"
        "DROP TABLE EventEventRecord;\n"

        "CREATE TABLE EventumPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  eventum_id INTEGER NOT NULL REFERENCES Eventum(id),\n"
        "  per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
        "  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),\n"
        "  note TEXT NOT NULL,\n"
        "  per_seq INTEGER NOT NULL\n"
        ");\n"
        "INSERT INTO EventumPersona"
        " (id, eventum_id, per_id, role_id, note, per_seq)"
        " SELECT id, event_rec_id, per_id, role_id, note, per_seq"
        " FROM EventPersona;\n"
        "DROP TABLE EventPersona;\n"

        "UPDATE Version SET test=6 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_6to0_0_10_7()
{
    // Version 0.0.10.6 to 0.0.10.7
    // Changeing Eventum term to Eventa
    // Rename table Eventum to Eventa
    // Rename table EventEventum to EventEventa
    // Rename column EventEveta.eventum_id to eventa_id
    // Rename table EventumPersona to EventaPersona
    // Rename column EventaPersona.eventum_id to eventa_id

    char* query =
        "BEGIN;\n"

        "ALTER TABLE Eventum RENAME TO Eventa;\n"

        "CREATE TABLE EventEventa (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  note TEXT\n"
        ");\n"
        "INSERT INTO EventEventa"
        " (id, event_id, eventa_id, conf, note)"
        " SELECT id, event_id, eventum_id, conf, note"
        " FROM EventEventum;\n"
        "DROP TABLE EventEventum;\n"

        "CREATE TABLE EventaPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
        "  per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
        "  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),\n"
        "  note TEXT NOT NULL,\n"
        "  per_seq INTEGER NOT NULL\n"
        ");\n"
        "INSERT INTO EventaPersona"
        " (id, eventa_id, per_id, role_id, note, per_seq)"
        " SELECT id, eventum_id, per_id, role_id, note, per_seq"
        " FROM EventumPersona;\n"
        "DROP TABLE EventumPersona;\n"

        "UPDATE Version SET test=7 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_7to0_0_10_8()
{
    // Version 0.0.10.7 to 0.0.10.8
    // Add EventType rows and their EventTypeRole rows
    // for the Relation and Family events.

    char* query =
        "BEGIN;\n"

        "INSERT INTO EventType (id, grp, name) VALUES(-21, 9, 'Relation');"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-72, -21, 1, 0, 'Subject');"

        "INSERT INTO EventType (id, grp, name) VALUES(-22, 10, 'Family');"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-73, -22, 1, 0, 'Husband');"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-74, -22, 2, 0, 'Wife');"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-75, -22, 3, 0, 'Partner');"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-76, -22, 0, 0, 'Child');"

        "UPDATE Version SET test=8 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_8to0_0_10_9()
{
    // Version 0.0.10.8 to 0.0.10.9
    // Add FamilyEventa and FamilyIndEventa tables.
    // These are new so there is no data to move.

    char* query =
        "BEGIN;\n"

        "CREATE TABLE FamilyEventa (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  fam_id INTEGER NOT NULL REFERENCES Family(id),\n"
        "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  note TEXT\n"
        ");\n"
        "CREATE TABLE FamilyIndEventa (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  fam_ind_id INTEGER NOT NULL REFERENCES FamilyIndividual(id),\n"
        "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  note TEXT\n"
        ");\n"

        "UPDATE Version SET test=9 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_9to0_0_10_10()
{
    // Version 0.0.10.9 to 0.0.10.10
    // Add privacy column to Individual table.
    // Default value is 0 (no privacy).

    char* query =
        "BEGIN;\n"

        "ALTER TABLE Individual RENAME TO OldIndividual;\n"
        "CREATE TABLE Individual (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  sex INTEGER NOT NULL,\n"
        "  fam_id INTEGER NOT NULL,\n"
        "  note TEXT NOT NULL,\n"
        "  privacy INTEGER NOT NULL,\n"
        "  name TEXT,\n"
        "  surname TEXT,\n"
        "  epitaph TEXT\n"
        ");\n"
        "INSERT INTO Individual\n"
        " (id, sex, fam_id, note, privacy, name, surname, epitaph)\n"
        " SELECT id, sex, fam_id, note, 0, name, surname, epitaph\n"
        " FROM OldIndividual;\n"
        "DROP TABLE OldIndividual;\n"

        "UPDATE Version SET test=10 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_10to0_0_10_11()
{
    // Version 0.0.10.10 to 0.0.10.11
    // Remove Relationship table (We now use Family Event group).
    // Data is removed, no attempt to transfer.

    char* query =
        "BEGIN;\n"

        "DELETE FROM ReferenceEntity WHERE entity_type=5;\n"
        "DROP TABLE Relationship;\n"

        "UPDATE Version SET test=11 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_11to0_0_10_12()
{
    // Version 0.0.10.11 to 0.0.10.12
    // Add user_ref column to Event and Reference tables.
    // Default value is NULL.

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
        "  date_pt INTEGER NOT NULL,\n"
        "  user_ref TEXT\n"
        ");\n"

        "INSERT INTO Event\n"
        " (id, title, higher_id, type_id, date1_id, date2_id,\n"
        "  place_id, note, date_pt, user_ref)\n"
        " SELECT id, title, higher_id, type_id, date1_id, date2_id,\n"
        "  place_id, note, date_pt, NULL\n"
        " FROM OldEvent;\n"
        "DROP TABLE OldEvent;\n"

        "ALTER TABLE Reference RENAME TO OldReference;\n"
        "CREATE TABLE Reference (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  statement TEXT NOT NULL,\n"
        "  user_ref TEXT\n"
        ");\n"

        "INSERT INTO Reference\n"
        " (id, title, statement, user_ref)\n"
        " SELECT id, title, statement, NULL\n"
        " FROM OldReference;\n"
        "DROP TABLE OldReference;\n"

        "UPDATE Version SET test=12 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_12to0_0_10_13()
{
    // Version 0.0.10.12 to 0.0.10.13
    // Add higher_id column to IndividualEvent table.
    // Default value is 0.

    char* query =
        "BEGIN;\n"

        "ALTER TABLE IndividualEvent RENAME TO OldIndividualEvent;\n"

        "CREATE TABLE IndividualEvent (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  higher_id INTEGER NOT NULL,\n"
        "  ind_id INTEGER NOT NULL REFERENCES Individual(id),\n"
        "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),\n"
        "  note TEXT NOT NULL,\n"
        "  ind_seq INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO IndividualEvent\n"
        " (id, higher_id, ind_id, event_id, role_id, note, ind_seq)\n"
        " SELECT id, 0, ind_id, event_id, role_id, note, ind_seq\n"
        " FROM OldIndividualEvent;\n"
        "DROP TABLE OldIndividualEvent;\n"

        "UPDATE Version SET test=13 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_13to0_0_10_14()
{
    // Version 0.0.10.13 to 0.0.10.14
    // Changes and additions to EventTypeRole records.

    char* query =
        "BEGIN;\n"

        // Residence
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-77, -17, 1, 0, 'Summary');\n"
        "UPDATE EventTypeRole SET prime=1 WHERE id=-61;\n"  // Was prime = 0
        "UPDATE EventTypeRole SET prime=1 WHERE id=-62;\n"
        "UPDATE EventTypeRole SET prime=1 WHERE id=-63;\n"
        "UPDATE EventTypeRole SET prime=1 WHERE id=-64;\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-85, -17, 1, 0, 'Staff');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-86, -17, 1, 0, 'Inmate');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-87, -17, 1, 0, 'Resident');\n"

        // Occupation (name was 'Occupation')
        "UPDATE EventTypeRole SET name='Summary' WHERE id=-65;\n"

        // Condition
        "UPDATE EventTypeRole SET name='Summary' WHERE id=-67;\n" // Was name = 'Condition'
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-78, -19, 1, 0, 'Single');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-79, -19, 1, 0, 'Married');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-80, -19, 1, 0, 'Partner');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-81, -19, 1, 0, 'Civil Partner');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-82, -19, 1, 0, 'Widowed');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-83, -19, 1, 0, 'Divorced');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-84, -19, 1, 0, 'Separated');\n"

        "UPDATE Version SET test=14 WHERE id=1;\n"
        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_14to0_0_10_15()
{
    // Version 0.0.10.14 to 0.0.10.15
    // Add seed Family F1 record if it doesn't exist.

    int cnt = recDb::GetDb()->ExecuteScalar( "SELECT COUNT(*) FROM Family WHERE id=1;" );
    wxString query;

    query << "BEGIN;\n";
    if ( cnt == 0 ) {
        query << "INSERT INTO Family (id, husb_id, wife_id) VALUES(1, 0, 0);\n";
    }
    query <<
        "UPDATE Version SET test=15 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_15to0_0_10_16()
{
    // Version 0.0.10.15 to 0.0.10.16
    // Add Media and othe tables.
    // No existing data is affected.

    char* query =
        "BEGIN;\n"

        "CREATE TABLE Associate (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  path TEXT NULL\n"
        ");\n"
        "INSERT INTO Associate (id) VALUES(0);\n"
        "CREATE TABLE Gallery (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  title TEXT NOT NULL,\n"
        "  note TEXT NULL\n"
        ");\n"
        "CREATE TABLE GalleryMedia (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  title TEXT NULL,\n"
        "  gal_id INT NOT NULL REFERENCES Gallery(id),\n"
        "  med_id INT NOT NULL REFERENCES Media(id),\n"
        "  med_seq INT NOT NULL\n"
        ");\n"
        "CREATE TABLE Media (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  data_id INT NOT NULL REFERENCES MediaData(id),\n"
        "  ass_id INT NOT NULL REFERENCES Associate(id),\n"
        "  ref_id INT NOT NULL REFERENCES Reference(id),\n"
        "  privacy INT NOT NULL,\n"
        "  title TEXT NULL,\n"
        "  note, TEXT NULL\n"
        ");\n"
        "CREATE TABLE MediaData (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  data BLOB NOT NULL,\n"
        "  privacy INT NOT NULL,\n"
        "  copyright TEXT NULL,\n"
        "  file TEXT NOT NULL\n"
        ");\n"

        "UPDATE Version SET test=16 WHERE id=1;\n"
        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_16to0_0_10_17()
{
    // Version 0.0.10.16 to 0.0.10.17
    // Add EventType and EventTypeRole records for Media Event.

    char* query =
        "BEGIN;\n"

        "INSERT INTO EventType (id, grp, name) VALUES(-23, 7, 'Media');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-88, -23, 1, 0, 'Subject');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-89, -23, 0, 0, 'Producer');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-90, -23, 0, 0, 'Commentator');\n"

        "UPDATE Version SET test=17 WHERE id=1;\n"
        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_17to0_0_10_18()
{
    // Version 0.0.10.17 to 0.0.10.18
    // Add ref_id field to Eventa records.
    // Remove Eventa records from ReferenceEntity table.

    char* query =
        "BEGIN;\n"

        "ALTER TABLE Eventa RENAME TO OldEventa;\n"
        "CREATE TABLE Eventa (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
        "  date1_id INTEGER NOT NULL,\n"
        "  date2_id INTEGER NOT NULL,\n"
        "  place_id INTEGER NOT NULL,\n"
        "  note TEXT NOT NULL,\n"
        "  date_pt INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO Eventa\n"
        " (id, title, ref_id, type_id, date1_id, date2_id,\n"
        "  place_id, note, date_pt)\n"
        " SELECT E.id, E.title, RE.ref_id, E.type_id, E.date1_id,\n"
        "  E.date2_id, E.place_id, E.note, E.date_pt\n"
        " FROM OldEventa E, ReferenceEntity RE\n"
        " WHERE E.id=RE.entity_id AND RE.entity_type=2;\n"
        "DROP TABLE OldEventa;\n"

        "DELETE FROM ReferenceEntity WHERE entity_type=2;\n"

        "UPDATE Version SET test=18 WHERE id=1;\n"
        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_18to0_0_10_19()
{
    // Version 0.0.10.18 to 0.0.10.19
    // Add Version record 2, the Media-only version number.
    // Initialised at Version 0.0.0.1

    char* query =
        "BEGIN;\n"
        "INSERT INTO Version ( id, major, minor, revision, test ) VALUES( 2, 0, 0, 0, 1 );\n"
        "UPDATE Version SET test=19 WHERE id=1;\n"
        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( query );
}

void UpgradeTest0_0_10_19to0_0_10_20( const wxString& dbname )
{
    // Version 0.0.10.19 to 0.0.10.20
    // NOTE: Change in format of updating tables
    // 1) Now allow for updating attached databases.
    // 2) Use recommended order of operations:-
    //     Create new table.
    //     Copy data across.
    //     Drop old table.
    //     Rename new into old.

    // Update Associate and Media tables

    wxString update = "BEGIN;\n";

    update << "CREATE TABLE " << dbname << ".NewAssociate (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  path TEXT NULL,\n"
        "  comment TEXT NULL\n"
        ");\n"
        "INSERT INTO " << dbname << ".NewAssociate"
        " (id, path, comment)"
        " SELECT id, path, ' '"
        " FROM " << dbname << ".Associate;\n"
        "DROP TABLE " << dbname << ".Associate;\n"
        "ALTER TABLE " << dbname << ".NewAssociate RENAME TO Associate;\n"

        "CREATE TABLE " << dbname << ".NewMedia (\n"
        "  id INTEGER PRIMARY KEY NOT NULL,\n"
        "  data_id INT NOT NULL REFERENCES MediaData(id),\n"
        "  ass_id INT NOT NULL REFERENCES Associate(id),\n"
        "  ref_id INT NOT NULL REFERENCES Reference(id),\n"
        "  ref_seq INT NOT NULL,\n"
        "  privacy INT NOT NULL,\n"
        "  title TEXT NULL,\n"
        "  note, TEXT NULL\n"
        ");\n"
        "INSERT INTO " << dbname << ".NewMedia"
        " (id, data_id, ass_id, ref_id, ref_seq, privacy, title, note)"
        " SELECT id, data_id, ass_id, ref_id, 1, privacy, title, note"
        " FROM " << dbname << ".Media;\n"
        "DROP TABLE " << dbname << ".Media;\n"
        "ALTER TABLE " << dbname << ".NewMedia RENAME TO Media;\n"

        "UPDATE " << dbname << ".Version SET test=20 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
    // Update to MediaData required as well.
    mdUpgradeTest0_0_0_1to0_0_0_2( dbname );
}

void UpgradeTest0_0_10_20to0_0_10_21( const wxString& dbname )
{
    // Version 0.0.10.20 to 0.0.10.21
    // NOTE: Change in format of updating tables
    // 1) Now allow for updating attached databases.
    // 2) Use recommended order of operations:-
    //     Create new table.
    //     Copy data across.
    //     Drop old table.
    //     Rename new into old.

    // Update Reference table, add higher_id field.

    wxString update = "BEGIN;\n";

    update << "CREATE TABLE " << dbname << ".NewReference (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  higher_id INTEGER,\n"
        "  title TEXT NOT NULL,\n"
        "  statement TEXT NOT NULL,\n"
        "  user_ref TEXT\n"
        ");\n"

        "INSERT INTO " << dbname << ".NewReference"
        " (id, higher_id, title, statement, user_ref)"
        " SELECT id, 0, title, statement, user_ref"
        " FROM " << dbname << ".Reference;\n"
        "DROP TABLE " << dbname << ".Reference;\n"
        "ALTER TABLE " << dbname << ".NewReference RENAME TO Reference;\n"

        "UPDATE " << dbname << ".Version SET test=21 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_21to0_0_10_22( const wxString& dbname )
{
    // Version 0.0.10.21 to 0.0.10.22
    // Remove Source table.
    // Rename Repository and RepsitorySource
    // to Archive and ArchiveReference
    // Remove access field and rename comments field to note
    // for Archive table.
    // CitationPart table source_id field removed
    // and ref_id field added.
    // CitationPart and CitationPartType tables redifined.
    // Note: none of the above tables have been actively
    // used and so no data will be tranfered.
    // Any data they may have held will be lost.

    // Update Reference table, add res_id field.

    wxString update = "BEGIN;\n";

    update
        << "DROP TABLE " << dbname << ".Source;\n"
        << "DROP TABLE " << dbname << ".Repository;\n"
        << "DROP TABLE " << dbname << ".RepositorySource;\n"
        << "DROP TABLE " << dbname << ".CitationPart;\n"
        << "DROP TABLE " << dbname << ".CitationPartType;\n"

        "CREATE TABLE Archive (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  note TEXT,\n"
        "  con_list_id INTEGER NOT NULL REFERENCES ContactList(id)\n"
        ");\n"
        "CREATE TABLE ArchiveReference (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  archive_id INTEGER NOT NULL REFERENCES Archive(id),\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  call_num TEXT,\n"
        "  note TEXT\n"
        ");\n"
        "CREATE TABLE CitationPart (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  type_id INTEGER NOT NULL REFERENCES CitationPartType(id),\n"
        "  val TEXT NOT NULL\n"
        ");\n"
        "CREATE TABLE CitationPartType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL\n"
        ");\n"

        "CREATE TABLE " << dbname << ".NewReference (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  higher_id INTEGER,\n"
        "  title TEXT NOT NULL,\n"
        "  statement TEXT NOT NULL,\n"
        "  res_id INTEGER NULL REFERENCES Researcher(id),\n"
        "  user_ref TEXT NULL\n"
        ");\n"

        "INSERT INTO " << dbname << ".NewReference"
        " (id, higher_id, title, statement, res_id, user_ref)"
        " SELECT id, higher_id, title, statement, 0, user_ref"
        " FROM " << dbname << ".Reference;\n"
        "DROP TABLE " << dbname << ".Reference;\n"
        "ALTER TABLE " << dbname << ".NewReference RENAME TO Reference;\n"

        "UPDATE " << dbname << ".Version SET test=22 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_22to0_0_10_23( const wxString& dbname )
{
    // Version 0.0.10.22 to 0.0.10.23
    // Remove Archive and ArchiveReference table.
    // Add Citation table.
    // Add fields to CitationPart, cit_seq, con_list_id and note.
    // Add fields to CitationPartType, style and comment.

    // Note: none of the above tables have been actively
    // used and so no data will be tranfered.
    // Any data they may have held will be lost.

    wxString update = "BEGIN;\n";

    update
        << "DROP TABLE " << dbname << ".Archive;\n"
        << "DROP TABLE " << dbname << ".ArchiveReference;\n"
        << "DROP TABLE " << dbname << ".CitationPart;\n"
        << "DROP TABLE " << dbname << ".CitationPartType;\n"

        "CREATE TABLE " << dbname << ".Citation (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  ref_seq INTEGER NOT NULL\n"
        ");\n"
        "CREATE TABLE " << dbname << ".CitationPart (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  cit_id INTEGER NOT NULL REFERENCES Citation(id),\n"
        "  type_id INTEGER NOT NULL REFERENCES CitationPartType(id),\n"
        "  val TEXT NOT NULL,\n"
        "  cit_seq INTEGER NOT NULL,\n"
        "  con_list_id INTEGER NULL,\n"
        "  note TEXT NULL\n"
        ");\n"
        "CREATE TABLE " << dbname << ".CitationPartType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  style INTEGER NOT NULL,\n"
        "  comment TEXT NULL\n"
        ");\n"

        "UPDATE " << dbname << ".Version SET test=23 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_23to0_0_10_24( const wxString& dbname )
{
    // Version 0.0.10.23 to 0.0.10.24
    // Add Repository table.
    // Add fields to Citation table, rep_id and comment.
    // Remove con_list_id field from CitationPart
    // and rename note to comment.

    // Note: none of the above tables have been actively
    // used and so no data will be tranfered.
    // Any data they may have held will be lost.

    wxString update = "BEGIN;\n";

    update
        << "DROP TABLE " << dbname << ".Citation;\n"
        << "DROP TABLE " << dbname << ".CitationPart;\n"

        "CREATE TABLE " << dbname << ".Citation (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  ref_seq INTEGER NOT NULL,\n"
        "  rep_id INTEGER NOT NULL REFERENCES Repository(id),\n"
        "  comment TEXT NULL\n"
        ");\n"
        "CREATE TABLE " << dbname << ".CitationPart (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  cit_id INTEGER NOT NULL REFERENCES Citation(id),\n"
        "  type_id INTEGER NOT NULL REFERENCES CitationPartType(id),\n"
        "  val TEXT NOT NULL,\n"
        "  cit_seq INTEGER NOT NULL,\n"
        "  comment TEXT NULL\n"
        ");\n"
        "CREATE TABLE " << dbname << ".Repository (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  note TEXT NULL,\n"
        "  con_list_id INTEGER NULL REFERENCES ContactList(id)\n"
        ");\n"

        "UPDATE " << dbname << ".Version SET test=24 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_24to0_0_10_25( const wxString& dbname )
{
    // Version 0.0.10.24 to 0.0.10.25

    // Add higher_id field to Citation table.

    wxString update = "BEGIN;\n";

    update <<
        "CREATE TABLE " << dbname << ".NewCitation (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  higher_id INTEGER NOT NULL,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  ref_seq INTEGER NOT NULL,\n"
        "  rep_id INTEGER NOT NULL REFERENCES Repository(id),\n"
        "  comment TEXT NULL\n"
        ");\n"

        "INSERT INTO " << dbname << ".NewCitation"
        " (id, higher_id, ref_id, ref_seq, rep_id, comment)\n"
        " SELECT id, 0, ref_id, ref_seq, rep_id, comment\n"
        " FROM " << dbname << ".Citation;\n"

        "DROP TABLE " << dbname << ".Citation;\n"
        "ALTER TABLE " << dbname << ".NewCitation RENAME TO Citation;\n"

        "UPDATE " << dbname << ".Version SET test=25 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_25to0_0_10_26( const wxString& dbname )
{
    // Version 0.0.10.25 to 0.0.10.26

    // Change to initial common records.
    // No longer seeded with blank Family F1
    // If we want it we will have to add it after creation.
    // Anonymous researcher now part of common data.
    // Create new researcher after database creation, if required.
    // Researcher record can have a null con_list_id (but not 0)

    wxString update = "BEGIN;\n";

    update <<
        "DELETE FROM " << dbname << ".ContactList WHERE id=0;\n"
        "DELETE FROM " << dbname << ".Researcher WHERE id=0;\n"
        "DELETE FROM " << dbname << ".User WHERE id=0;\n"
        "DELETE FROM " << dbname << ".UserSetting WHERE user_id=0;\n"

        "CREATE TABLE " << dbname << ".NewResearcher (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  comments TEXT,\n"
        "  con_list_id INTEGER REFERENCES ContactList(id)\n"
        ");\n"

        "INSERT INTO " << dbname << ".NewResearcher"
        " (id, name, comments, con_list_id)\n"
        " SELECT id, name, comments, con_list_id\n"
        " FROM " << dbname << ".Researcher;\n"

        "DROP TABLE " << dbname << ".Researcher;\n"
        "ALTER TABLE " << dbname << ".NewResearcher RENAME TO Researcher;\n"

        "INSERT INTO " << dbname << ".Researcher (id, name, comments, con_list_id)"
        " VALUES(-1, 'Anonymous', NULL, NULL);\n"
        "INSERT INTO " << dbname << ".Researcher (id, name, comments, con_list_id)"
        " VALUES(0, '', NULL, NULL);\n"

        "UPDATE " << dbname << ".Version SET test=26 WHERE id=1;\n"

        "COMMIT;\n"
        ;
    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_26to0_0_10_27( const wxString& dbname )
{
    // Version 0.0.10.26 to 0.0.10.27

    // Add field 'uid' to Reference.
    // Add field 'changed' to Reference.

    wxString update = "BEGIN;\n";

    update <<

        // Add field 'changed' to Reference.
        "CREATE TABLE \"" << dbname << "\".NewReference (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  higher_id INTEGER,\n"
        "  title TEXT NOT NULL,\n"
        "  statement TEXT NOT NULL,\n"
        "  res_id INTEGER NULL REFERENCES Researcher(id),\n"
        "  user_ref TEXT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewReference"
        " (id, higher_id, title, statement, res_id, user_ref, uid, changed)\n"
        " SELECT id, higher_id, title, statement, res_id, user_ref, '', 2459647\n"
        " FROM \"" << dbname << "\".Reference;\n"

        "DROP TABLE \"" << dbname << "\".Reference;\n"
        "ALTER TABLE \"" << dbname << "\".NewReference RENAME TO Reference;\n"
        ;

    // Fill Reference table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Reference;\n"; // Get refID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Reference"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n";
    }

    update <<
        "UPDATE \"" << dbname << "\".Version SET test=27 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_27to0_0_10_28( const wxString& dbname )
{
    // Version 0.0.10.27 to 0.0.10.28

    // Add field 'uid' to Researcher.
    wxString update =
        "PRAGMA foreign_keys=OFF;\n"
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewResearcher (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  comment TEXT,\n"
        "  con_list_id INTEGER REFERENCES ContactList(id),\n"
        "  uid TEXT NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewResearcher"
        " (id, name, comment, con_list_id, uid)\n"
        " SELECT id, name, comments, con_list_id, ''\n"
        " FROM \"" << dbname << "\".Researcher;\n"

        "DROP TABLE \"" << dbname << "\".Researcher;\n"
        "ALTER TABLE \"" << dbname << "\".NewResearcher RENAME TO Researcher;\n"
        ;

    // Fill Researcher table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Researcher WHERE id>0;\n"; // Get resID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Researcher"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
        ;
    }
    update << "UPDATE \"" << dbname << "\".Researcher"
        " SET uid='E16C3575699D77C1BABD0C582A44C6FA3E4A' WHERE id=-1;\n"
        ;

    update <<
        "UPDATE \"" << dbname << "\".Version SET test=28 WHERE id=1;\n"
        "COMMIT;\n"
        "PRAGMA foreign_keys=ON;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_28to0_0_10_29( const wxString& dbname )
{
    // Version 0.0.10.28 to 0.0.10.29

    // Add field 'uid' to Researcher.
    wxString update;

    update <<
        "PRAGMA foreign_keys=OFF;\n"
        "BEGIN;\n"

        "INSERT INTO \"" << dbname << "\".Citation (id, higher_id, ref_id, ref_seq, rep_id) VALUES(0,0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".CitationPart (id, cit_id, type_id, val, cit_seq) VALUES(0,0,0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".CitationPartType (id, name, style) VALUES(0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".Contact (id, type_id, list_id, val) VALUES(0,0,0,'');\n"
        "INSERT INTO \"" << dbname << "\".Date (id) VALUES(0);\n"
        "INSERT INTO \"" << dbname << "\".Event (\n"
        "  id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt)\n"
        "  VALUES(0,'',0,0,0,0,0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".Eventa (\n"
        "  id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt)\n"
        "  VALUES(0,'',0,0,0,0,0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".EventaPersona (\n"
        "  id, eventa_id, per_id, role_id, note, per_seq)\n"
        "  VALUES(0,0,0,0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".EventEventa (id, event_id, eventa_id, conf) VALUES(0,0,0,'');\n"
        "INSERT INTO \"" << dbname << "\".Family (id) VALUES(0);\n"
        "INSERT INTO \"" << dbname << "\".FamilyEvent (id, fam_id, event_id, fam_seq) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".FamilyEventa (id, fam_id, eventa_id, conf) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".FamilyIndEventa (id, fam_ind_id, eventa_id, conf) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".FamilyIndividual (\n"
        "  id, fam_id, ind_id, seq_child,seq_parent) VALUES(0,0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".Gallery (id, title) VALUES(0,'');\n"
        "INSERT INTO \"" << dbname << "\".GalleryMedia (id, gal_id, med_id, med_seq) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".Individual (id, sex, fam_id, note, privacy) VALUES(0,0,0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".IndividualEvent (\n"
        "  id, higher_id, ind_id, event_id, role_id, note, ind_seq)\n"
        "  VALUES(0,0,0,0,0,'',0);\n"
        "INSERT INTO \"" << dbname << "\".IndividualPersona (id, ind_id, per_id, conf) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".Media (\n"
        "  id, data_id, ass_id, ref_id, ref_seq, privacy)\n"
        "  VALUES(0,0,0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".Name (id, ind_id, per_id, style_id) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".NamePart (id, name_id, type_id, sequence) VALUES(0,0,0,0);\n"
        "INSERT INTO \"" << dbname << "\".Persona (id) VALUES(0);\n"
        "INSERT INTO \"" << dbname << "\".Place (id) VALUES(0);\n"
        "INSERT INTO \"" << dbname << "\".PlacePart (id) VALUES(0);\n"
        "INSERT INTO \"" << dbname << "\".Reference (id, title, statement, uid, changed)\n"
        "  VALUES(0,'','','',0);\n"
        "INSERT INTO \"" << dbname << "\".ReferenceEntity (id) VALUES(0);\n"
        "INSERT INTO \"" << dbname << "\".RelativeDate (id, base_id) VALUES(0,0);\n"
        "INSERT INTO \"" << dbname << "\".Repository (id, name) VALUES(0,'');\n"

        "UPDATE \"" << dbname << "\".Version SET test=29 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );

    // Update to MediaData required as well.
    mdUpgradeTest0_0_0_2to0_0_0_3( dbname );
}

void UpgradeTest0_0_10_29to0_0_10_30( const wxString& dbname )
{
    // Version 0.0.10.29 to 0.0.10.30

    // Add field 'uid' to Repository.
    // Add field 'changed' to Repository.

    wxString update = "BEGIN;\n";

    update <<

        // Add field 'changed' to Repository.
        "CREATE TABLE \"" << dbname << "\".NewRepository (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  note TEXT NULL,\n"
        "  con_list_id INTEGER NULL REFERENCES ContactList(id),\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INT NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewRepository"
        " (id, name, note, con_list_id, uid, changed)\n"
        " SELECT id, name, note, con_list_id, '', 0\n"
        " FROM \"" << dbname << "\".Repository;\n"

        "DROP TABLE \"" << dbname << "\".Repository;\n"
        "ALTER TABLE \"" << dbname << "\".NewRepository RENAME TO Repository;\n"
        ;

    // Fill Reference table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Repository WHERE NOT id=0;\n"; // Get refID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Repository"
            " SET uid='" << recCreateUid() << "', changed=2459654"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n";
    }

    update <<
        "UPDATE \"" << dbname << "\".Version SET test=30 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_30to0_0_10_31( const wxString& dbname )
{
    // Version 0.0.10.30 to 0.0.10.31
    // Add uid and changed fields to MediaData.

    wxString update; 
    update <<
        "BEGIN;\n"
        "UPDATE \"" << dbname << "\".Version SET test=31 WHERE id=1;\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( update );

    // Update to MediaData.
    mdUpgradeTest0_0_0_3to0_0_0_4( dbname );
}


void UpgradeRev0_0_10toCurrent( int test, const wxString& dbname )
{
    switch( test )
    {
    case 0: UpgradeTest0_0_10_0to0_0_10_1();  // Fall thru intended
    case 1: UpgradeTest0_0_10_1to0_0_10_2();
    case 2: UpgradeTest0_0_10_2to0_0_10_3();
    case 3: UpgradeTest0_0_10_3to0_0_10_4();
    case 4: UpgradeTest0_0_10_4to0_0_10_5();
    case 5: UpgradeTest0_0_10_5to0_0_10_6();
    case 6: UpgradeTest0_0_10_6to0_0_10_7();
    case 7: UpgradeTest0_0_10_7to0_0_10_8();
    case 8: UpgradeTest0_0_10_8to0_0_10_9();
    case 9: UpgradeTest0_0_10_9to0_0_10_10();
    case 10: UpgradeTest0_0_10_10to0_0_10_11();
    case 11: UpgradeTest0_0_10_11to0_0_10_12();
    case 12: UpgradeTest0_0_10_12to0_0_10_13();
    case 13: UpgradeTest0_0_10_13to0_0_10_14();
    case 14: UpgradeTest0_0_10_14to0_0_10_15();
    case 15: UpgradeTest0_0_10_15to0_0_10_16();
    case 16: UpgradeTest0_0_10_16to0_0_10_17();
    case 17: UpgradeTest0_0_10_17to0_0_10_18();
    case 18: UpgradeTest0_0_10_18to0_0_10_19();
    case 19: UpgradeTest0_0_10_19to0_0_10_20( dbname );
    case 20: UpgradeTest0_0_10_20to0_0_10_21( dbname );
    case 21: UpgradeTest0_0_10_21to0_0_10_22( dbname );
    case 22: UpgradeTest0_0_10_22to0_0_10_23( dbname );
    case 23: UpgradeTest0_0_10_23to0_0_10_24( dbname );
    case 24: UpgradeTest0_0_10_24to0_0_10_25( dbname );
    case 25: UpgradeTest0_0_10_25to0_0_10_26( dbname );
    case 26: UpgradeTest0_0_10_26to0_0_10_27( dbname );
    case 27: UpgradeTest0_0_10_27to0_0_10_28( dbname );
    case 28: UpgradeTest0_0_10_28to0_0_10_29( dbname );
    case 29: UpgradeTest0_0_10_29to0_0_10_30( dbname );
    case 30: UpgradeTest0_0_10_30to0_0_10_31( dbname );
    }
}

} // namespace


bool recDoFullUpgrade( const wxString& dbname )
{
    recVersion ver( recDb::DbType::full, dbname );
    if ( ver.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        return true; // Already current version
    }
    wxString verstr = ver.GetVersionStr();
    if ( ver.IsLessThan( 0, 0, 9, 25 ) ) {
        recMessage(
            wxString::Format(
                _( "Cannot read old database version %s file." ),
                verstr
                ),
            _( "Upgrade Test" )
            );
        return false;
    }
    if ( ver.IsMoreThan( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        recMessage(
            wxString::Format(
                _( "Cannot read future database version %s file." ),
                verstr
                ),
            _( "Upgrade Test" )
            );
        return false;
    }
    if ( recPermissionToUpgrade( verstr, recFullVersion ) == false ) {
        return false;
    }

    try {
        if ( ver.IsEqual( 0, 0, 9 ) ) {
            UpgradeRev0_0_9to10( ver.FGetTest() );
            ver.ReadType( recDb::DbType::full );
        }
        if ( ver.IsEqual( 0, 0, 10 ) ) {
            UpgradeRev0_0_10toCurrent( ver.FGetTest(), dbname );
            ver.ReadType( recDb::DbType::full );
        }
    }
    catch ( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        return false;
    }

    wxASSERT( ver.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) );
    return true;
}

// End of recVersion.cpp file
