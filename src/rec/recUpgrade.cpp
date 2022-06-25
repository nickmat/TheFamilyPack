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
const int recVerTest = 43;                       // <<======<<<<
const char* recFullVersion = "TFPD-v0.0.10.43";  // <<======<<<<

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

void UpgradeTest0_0_10_31to0_0_10_32( const wxString& dbname )
{
    // Version 0.0.10.31 to 0.0.10.32

    // Add field 'uid' to ContactType.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewContactType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewContactType"
        " (id, name, uid, changed)\n"
        " SELECT id, name, '', 2459664\n"
        " FROM \"" << dbname << "\".ContactType;\n"

        "DROP TABLE \"" << dbname << "\".ContactType;\n"
        "ALTER TABLE \"" << dbname << "\".NewContactType RENAME TO ContactType;\n"
        ;

    // Fill ContactType table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".ContactType WHERE id>0;\n"; // Get ctID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".ContactType"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".ContactType"
        " SET changed=0 WHERE id=0;\n"
        "UPDATE \"" << dbname << "\".ContactType"
        " SET uid='88815CB7641A5C15A6B47B40E69DE654DD52' WHERE id=-1;\n"
        "UPDATE \"" << dbname << "\".ContactType"
        " SET uid='7143E6D4D916C849F2B4FC6554AE5B421483' WHERE id=-2;\n"
        "UPDATE \"" << dbname << "\".ContactType"
        " SET uid='D5914CBACD1E86412EB4771C1E015BCBD882' WHERE id=-3;\n"
        "UPDATE \"" << dbname << "\".ContactType"
        " SET uid='2A56952B37D688AD0F795B059A82619E857A' WHERE id=-4;\n"
        "UPDATE \"" << dbname << "\".ContactType"
        " SET uid='0913E9393D6F676F74252E9F18516D201CFD' WHERE id=-5;\n"
        "UPDATE \"" << dbname << "\".ContactType"
        " SET uid='D717ACECD3D1DF6E663C9788BFB330350F50' WHERE id=-6;\n"

        "UPDATE \"" << dbname << "\".Version SET test=32 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_32to0_0_10_33( const wxString& dbname )
{
    // Version 0.0.10.32 to 0.0.10.33

    // Add field 'uid' to Citation.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewCitation (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  higher_id INTEGER NOT NULL,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  ref_seq INTEGER NOT NULL,\n"
        "  rep_id INTEGER NOT NULL REFERENCES Repository(id),\n"
        "  comment TEXT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewCitation"
        " (id, higher_id, ref_id, ref_seq, rep_id, comment, uid, changed)\n"
        " SELECT id, higher_id, ref_id, ref_seq, rep_id, comment, '', 2459669\n"
        " FROM \"" << dbname << "\".Citation;\n"

        "DROP TABLE \"" << dbname << "\".Citation;\n"
        "ALTER TABLE \"" << dbname << "\".NewCitation RENAME TO Citation;\n"
        ;

    // Fill Citation table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Citation WHERE id>0;\n"; // Get citID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Citation"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".Citation"
        " SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=33 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_33to0_0_10_34( const wxString& dbname )
{
    // Version 0.0.10.33 to 0.0.10.34

    // Add field 'uid' and 'changed' to CitationPartType.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewCitationPartType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  style INTEGER NOT NULL,\n"
        "  comment TEXT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewCitationPartType"
        " (id, name, style, comment, uid, changed)\n"
        " SELECT id, name, style, comment, '', 2459671\n"
        " FROM \"" << dbname << "\".CitationPartType;\n"

        "DROP TABLE \"" << dbname << "\".CitationPartType;\n"
        "ALTER TABLE \"" << dbname << "\".NewCitationPartType RENAME TO CitationPartType;\n"
        ;

    // Fill CitationPartType table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".CitationPartType WHERE id>0;\n"; // Get id list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".CitationPartType"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".CitationPartType"
        " SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=34 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_34to0_0_10_35( const wxString& dbname )
{
    // Version 0.0.10.34 to 0.0.10.35

    // Add field'changed' to Researcher
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewResearcher (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  comment TEXT,\n"
        "  con_list_id INTEGER REFERENCES ContactList(id),\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewResearcher"
        " (id, name, comment, con_list_id, uid, changed)\n"
        " SELECT id, name, comment, con_list_id, uid, 2459675\n"
        " FROM \"" << dbname << "\".Researcher;\n"

        "DROP TABLE \"" << dbname << "\".Researcher;\n"
        "ALTER TABLE \"" << dbname << "\".NewResearcher RENAME TO Researcher;\n"

        "UPDATE \"" << dbname << "\".Researcher"
        " SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=35 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_35to0_0_10_36( const wxString& dbname )
{
    // Version 0.0.10.35 to 0.0.10.36

    // Add field 'list_seq' to Contact
    wxString update = "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewContact (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  type_id INTEGER NOT NULL REFERENCES ContactType(id),\n"
        "  list_id INTEGER NOT NULL REFERENCES ContactList(id),\n"
        "  list_seq INTEGER NOT NULL,\n"
        "  val TEXT NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewContact\n"
        " (id, type_id, list_id, list_seq, val)\n"
        " SELECT id, type_id, list_id, 0, val\n"
        " FROM \"" << dbname << "\".Contact;\n"

        "DROP TABLE \"" << dbname << "\".Contact;\n"
        "ALTER TABLE \"" << dbname << "\".NewContact RENAME TO Contact;\n"
        ;

    // Write in list_seq sequence numbers
    wxString query = "SELECT id FROM \"" + dbname + "\".ContactList WHERE NOT id=0;\n"; // Get id list
    wxSQLite3Table table1 = recDb::GetDb()->GetTable( query );
    size_t size1 = (size_t) table1.GetRowCount();
    for( size_t i = 0; i < size1; i++ ) {
        table1.SetRow( i );
        query =
            "SELECT id FROM \"" + dbname + "\".Contact"
            " WHERE list_id=" + table1.GetAsString( 0 ) +
            " ORDER BY id;\n";
        wxSQLite3Table table2 = recDb::GetDb()->GetTable( query );
        size_t size2 = (size_t) table2.GetRowCount();
        for( size_t j = 0; j < size2; j++ ) {
            table2.SetRow( j );
            update <<
                "UPDATE \"" << dbname << "\".Contact"
                " SET list_seq=" << (j + 1) <<
                " WHERE id=" << table2.GetAsString( 0 ) << ";\n"
                ;
        }
    }

    update <<
        "UPDATE \"" << dbname << "\".Version SET test=36 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_36to0_0_10_37( const wxString& dbname )
{
    // Version 0.0.10.36 to 0.0.10.37

    // Add field 'uid' and 'changed' to NamePartType and NameStyle.
    wxString update =
        "BEGIN;\n";

    // Add uid and changed fields to NamePartType table.
    update <<
        "CREATE TABLE \"" << dbname << "\".NewNamePartType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  grp INTEGER NOT NULL,\n"
        "  name TEXT NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewNamePartType"
        " (id, grp, name, uid, changed)\n"
        " SELECT id, grp, name, '', 2459671\n"
        " FROM \"" << dbname << "\".NamePartType;\n"

        "DROP TABLE \"" << dbname << "\".NamePartType;\n"
        "ALTER TABLE \"" << dbname << "\".NewNamePartType RENAME TO NamePartType;\n"
        ;

    // Fill NamePartType table uid field
    // Do positive numbers
    wxString query = "SELECT id FROM \"" + dbname + "\".NamePartType WHERE id>0;\n"; // Get nptID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".NamePartType"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    // Do negative numbers
    update <<
        "UPDATE \"" << dbname << "\".NamePartType"
        " SET changed=0 WHERE id=0;\n"
        "UPDATE \"" << dbname << "\".NamePartType"
        " SET uid='D078B79DEA7D7C5E6954D9BD9A3F77951583' WHERE id=-1;\n"
        "UPDATE \"" << dbname << "\".NamePartType"
        " SET uid='C8FA1239479F03CE5A4A9D9462DA1074599E' WHERE id=-2;\n"
        "UPDATE \"" << dbname << "\".NamePartType"
        " SET uid='B4FC970919A55CBD630EC6A9109F692342B8' WHERE id=-3;\n"
        ;

    // Add uid and changed fields to NameStyle table.
    update <<
        "CREATE TABLE \"" << dbname << "\".NewNameStyle (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewNameStyle"
        " (id, name, uid, changed)\n"
        " SELECT id, name, '', 2459671\n"
        " FROM \"" << dbname << "\".NameStyle;\n"

        "DROP TABLE \"" << dbname << "\".NameStyle;\n"
        "ALTER TABLE \"" << dbname << "\".NewNameStyle RENAME TO NameStyle;\n"
        ;


    // Fill NameStyle table uid field
    // Do positive numbers
    query = "SELECT id FROM \"" + dbname + "\".NameStyle WHERE id>0;\n"; // Get nptID list
    table = recDb::GetDb()->GetTable( query );
    size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".NameStyle"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    // Do negative numbers
    update <<
        "UPDATE \"" << dbname << "\".NameStyle"
        " SET changed=0 WHERE id=0;\n"
        "UPDATE \"" << dbname << "\".NameStyle"
        " SET uid='9E8D131956EFBA85EE89134A9EBD43004DF8' WHERE id=-1;\n"
        "UPDATE \"" << dbname << "\".NameStyle"
        " SET uid='CCEF089DAD05903B8825EF5FC8F5A5DA140B' WHERE id=-2;\n"
        "UPDATE \"" << dbname << "\".NameStyle"
        " SET uid='67F2C0CDB179EE99E6D3C4B82C9BAAAEEB5B' WHERE id=-3;\n"

        "UPDATE \"" << dbname << "\".Version SET test=37 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_37to0_0_10_38( const wxString& dbname )
{
    // Version 0.0.10.37 to 0.0.10.38

    // Add field 'uid' and 'changed' to PlacePartType.
    wxString update =
        "BEGIN;\n";

    // Add uid and changed fields to NamePartType table.
    update <<
        "CREATE TABLE \"" << dbname << "\".NewPlacePartType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  name TEXT NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INT NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewPlacePartType"
        " (id, name, uid, changed)\n"
        " SELECT id, IFNULL(name,'') name, '', 2459716\n"
        " FROM \"" << dbname << "\".PlacePartType;\n"

        "DROP TABLE \"" << dbname << "\".PlacePartType;\n"
        "ALTER TABLE \"" << dbname << "\".NewPlacePartType RENAME TO PlacePartType;\n"
        ;

    // Fill PlacePartType table uid field
    // Do positive numbers
    wxString query = "SELECT id FROM \"" + dbname + "\".PlacePartType WHERE id>0;\n"; // Get pptID list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".PlacePartType"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    // Do negative numbers
    update <<
        "UPDATE \"" << dbname << "\".PlacePartType"
        " SET changed=0 WHERE id=0;\n"
        "UPDATE \"" << dbname << "\".PlacePartType"
        " SET uid='73D067F49E86C542C3E237AFC50BE77F8A11' WHERE id=-1;\n"

        "UPDATE \"" << dbname << "\".Version SET test=38 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_38to0_0_10_39( const wxString& dbname )
{
    // Version 0.0.10.38 to 0.0.10.39

    // Add field 'uid' and 'changed' to Gallery.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewGallery (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  note TEXT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewGallery"
        " (id, title, note, uid, changed)\n"
        " SELECT id, title, note, '', 2459740\n"
        " FROM \"" << dbname << "\".Gallery;\n"

        "DROP TABLE \"" << dbname << "\".Gallery;\n"
        "ALTER TABLE \"" << dbname << "\".NewGallery RENAME TO Gallery;\n"
        ;

    // Fill Gallery table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Gallery WHERE id>0;\n"; // Get id list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Gallery"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".Gallery"
        " SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=39 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_39to0_0_10_40( const wxString& dbname )
{
    // Version 0.0.10.39 to 0.0.10.40

    // Add field 'uid' and 'changed' to EventType and EventTypeRole.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewEventType (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  grp INTEGER NOT NULL,\n"
        "  name TEXT NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        // Remove null values on record 0.
        "UPDATE \"" << dbname << "\".EventType SET grp=0, name='' WHERE id=0;\n"

        "INSERT INTO \"" << dbname << "\".NewEventType"
        " (id, grp, name, uid, changed)\n"
        " SELECT id, grp, name, '', 2459752\n"
        " FROM \"" << dbname << "\".EventType;\n"

        "DROP TABLE \"" << dbname << "\".EventType;\n"
        "ALTER TABLE \"" << dbname << "\".NewEventType RENAME TO EventType;\n"
        ;

    // Fill EventType table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".EventType WHERE id>0;\n"; // Get id list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".EventType"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".EventType SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".EventType SET uid='30AB007B03C8BF584A53124EB8D652697E84' WHERE id=-1;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='9D456F509BCB5CBEFB891695B48FAB5E9C75' WHERE id=-2;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='4C763908AD6A87F5453ADE212EAF8472E793' WHERE id=-3;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='70933A4FE1C53D2726E2DDBE540D2C0BD1AC' WHERE id=-4;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='B280BF2B8CE00795F1DF2572BB7BAB026E62' WHERE id=-5;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='A2938143B96EDAE92E402CAECDE1FDCCA288' WHERE id=-6;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='8B2158196ACCDF1AB4A438F6B97922193FF6' WHERE id=-7;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='D749C38DB0A5B8862A7F67C71348A3825AC9' WHERE id=-8;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='5F22AAF1C26A49037BC21DB918000317D900' WHERE id=-9;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='188C09CBB315B850871C14E6E3167B91EA13' WHERE id=-10;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='601CCC7985405F97C9405751B33F44DE4188' WHERE id=-11;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='C9325D190689AB25609F681A3AFC3CD59873' WHERE id=-12;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='A958ED4A33C1A8068631D92812401B2E2DB6' WHERE id=-13;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='A43B77FAA6606717D17B864945ADB042D3D9' WHERE id=-14;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='8C347D7CE909C4E123C578F3C1F934CA5BF9' WHERE id=-15;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='45131053450AAFF043D1FFA2B57573DCD75C' WHERE id=-16;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='904EB30BB56D46F20BF15D3BD1EC60D27932' WHERE id=-17;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='7ACC2C0D44AB258632F2F7200B1ABEDD14C1' WHERE id=-18;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='2B9BFD3E4222364938364518EACEF34BA58F' WHERE id=-19;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='DEA4143114BEEC17045BBA744FBD1CBD0ED7' WHERE id=-20;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='789B829792C6BF41E9E2DA2DADD73119249C' WHERE id=-21;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='52EEDA65F1A6102CC9599D265B3C181A0046' WHERE id=-22;\n"
        "UPDATE \"" << dbname << "\".EventType SET uid='C86CC13C6CCFDB2DB805A8AB0B3FC11FAE3A' WHERE id=-23;\n"

        "CREATE TABLE \"" << dbname << "\".NewEventTypeRole (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
        "  prime INTEGER NOT NULL,\n"
        "  official INTEGER NOT NULL,\n"
        "  name TEXT NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        // Remove null values on record 0.
        "UPDATE \"" << dbname << "\".EventTypeRole SET type_id=0, prime=0, official=0, name='' WHERE id=0;\n"

        "INSERT INTO \"" << dbname << "\".NewEventTypeRole"
        " (id, type_id, prime, official, name, uid, changed)\n"
        " SELECT id, type_id, prime, official, name, '', 2459752\n"
        " FROM \"" << dbname << "\".EventTypeRole;\n"

        "DROP TABLE \"" << dbname << "\".EventTypeRole;\n"
        "ALTER TABLE \"" << dbname << "\".NewEventTypeRole RENAME TO EventTypeRole;\n"
        ;

    // Fill EventTypeRole table uid field
    query = "SELECT id FROM \"" + dbname + "\".EventTypeRole WHERE id>0;\n"; // Get user id list
    table = recDb::GetDb()->GetTable( query );
    size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".EventTypeRole"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".EventTypeRole SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='6294C833BCF9D2E0F8DDDEC4946441F901B4' WHERE id=-1;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='59D8C78FC6E8102B214147C6A0A25012832F' WHERE id=-2;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='527A6A76412AFF9C8DE1ABA399D8304655AE' WHERE id=-3;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='3C0E358DFDDFF7989230FE002F9FC61AE523' WHERE id=-4;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='2753766036C229794AEE257200EA8DAEDECA' WHERE id=-5;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='3721F9AED08D02AB242268E6517D2EDB74A7' WHERE id=-6;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='EBBCF29CE75DEB1B57A2C0196245C14C0518' WHERE id=-7;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='370B504243943119A9A74C8B481A9CD2ECEA' WHERE id=-8;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='74B2CDEFCED43777C94C3DD493B37D0F2A7C' WHERE id=-9;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='BE6933D1F76F2CD6B62F4F0275A505B59D64' WHERE id=-10;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='047FB29EE359BE626B2F8ED84BDC3BC455EF' WHERE id=-11;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='1358514D43426F30E12BE41CF39C9FAD1453' WHERE id=-12;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='9C3E06785825611CD76CED8C310016348965' WHERE id=-13;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='D13491A16857D377E16AD3E3187D2063590A' WHERE id=-14;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='66C12CF765541AAA50FB4CED3C9BBE866681' WHERE id=-15;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='ADDBF1757B7C467F7C1B9305317B29B26070' WHERE id=-16;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='9D964DB5D4BB2BA65C4D23D8809EEE4F9488' WHERE id=-17;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='1E4068FB67D4DE9AB3171DC7CC0E14162677' WHERE id=-18;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='C56BCF2BBBBC3A8F1D10CAB43A33E746AF66' WHERE id=-19;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='5B1E1118786681C12A4C06EDF10AD1251C3F' WHERE id=-20;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='6B6CB578797164D8C2EA6809B94E261E9254' WHERE id=-21;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='D46C5E4B8857CEE439D11F1C69394B7F2BDD' WHERE id=-22;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='25E14F730376D3D6E86BAA72B1192AADFA15' WHERE id=-23;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='603C86B8542C0EA4C6E64D3EAD9663BAA3C8' WHERE id=-24;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='B7DDBF0EE6D66C6CA696FE1A2D68B9EB8292' WHERE id=-25;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='980587CF544175E55A02BA7C343E629CE49A' WHERE id=-26;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='86D47917CAB0A4836583EBC67ADD38B76A63' WHERE id=-27;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='3D79C782650F98F9C103D4D03289520A83AB' WHERE id=-28;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='2F802E3F827490E491ED7F022CD5F80D8B12' WHERE id=-29;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='8A152316FCA79A363BCC83E9F9682B6CB6B3' WHERE id=-30;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='53534D02E6C94872325323C5B09F6DFB828C' WHERE id=-31;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='45D36CC7EC0B39D46B9205885571883960F3' WHERE id=-32;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='AFFB9AFE5A2A54653A0752B2812A3FF19F2A' WHERE id=-33;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='30A9EDE2C9D197F2FA47498E6CCB3A217509' WHERE id=-34;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='06A3B3281C6E916F44A056F4D5E924F816F1' WHERE id=-35;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='722D3DC4759ECC67704C1F5305433BB249DC' WHERE id=-36;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='F50834023F0CBF1600EFFFD37C43A5FE7611' WHERE id=-37;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='F6CE7D384D38B6006131E3CF05029B1AB466' WHERE id=-38;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='38B130B59F7FC9F78E52235B2CC1F447328B' WHERE id=-39;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='D7F462E3E16E2FDCF54E7BB64D10AED8C149' WHERE id=-40;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='84100E33B6EBA4030BF2859F30569C2484FC' WHERE id=-41;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='1D27D815BDBE87F4DEE93921CC0A489C029E' WHERE id=-42;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='85A72F1867C30005C3E3C8AFC0CAF5BFFDB4' WHERE id=-43;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='23F148EE526D13BFFF0AA38DF2B066C6E28C' WHERE id=-44;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='3E937C13782A350FB56C12FCBF425DB18464' WHERE id=-45;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='6778DE2C39CA3D81399AD3861ED4C6B03EDB' WHERE id=-46;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='F2A598516179B89FBA44F72AD8D15BC59954' WHERE id=-47;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='0E0546B7FE61E3437C721612E1655E29780A' WHERE id=-48;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='1B7C454890F1695FF87CC63D098178B0962E' WHERE id=-49;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='81451C911D32C7F7AE4125C8F88565559382' WHERE id=-50;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='194C35B62D872374E52277B84817980ED69E' WHERE id=-51;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='5C7BA6874EF0DADD5600A8C1ACD90A6BB244' WHERE id=-52;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='1B380CD1A593F789B787103EB4619B1539FE' WHERE id=-53;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='7CEC5F925775C9847E3FE2E3A126565B6C2A' WHERE id=-54;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='0683188FDAB4D0DFC94FE19146ED05E514E5' WHERE id=-55;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='2E01C860F7DB33A2F192F3C6306F9F5CD429' WHERE id=-56;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='2C0354516E3368917EE7470E470CD49BEAD8' WHERE id=-57;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='E4EB7D2283DE5E6E569DB2BCA6FE2DFAC786' WHERE id=-58;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='ACFCFE744A4FC5CCEFDFD0B68B922513ED45' WHERE id=-59;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='1A7EFE1584ED9579D7A90B11AF44C8F67765' WHERE id=-60;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='40D36C4B1F763EAA61A334B78A4410374B93' WHERE id=-61;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='4658360D56D2A8225A4FFE76A69F63E47C4F' WHERE id=-62;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='071F0D3B669300A890AD29F5C19834C1B8E6' WHERE id=-63;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='E427AC312363F7B9CE2FC710764EE9711032' WHERE id=-64;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='26DD261E46203A04BAFC9DB4719C91AC3C49' WHERE id=-65;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='701D3345C19A06D5335E80EB9165D7AAAEED' WHERE id=-66;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='43EE52E796C6CD2A07D2F971BFDE0049E63F' WHERE id=-67;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='B3B8F286F54F9EF2609FFD1477A7391A3899' WHERE id=-68;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='DF91CF34FA1D3B04B1DA951605E1AE2EC179' WHERE id=-69;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='99555FED0E1A2E0F265AE943DF4CDA2A7A88' WHERE id=-70;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='36827CA6269ADED1C61EB60E58C2AE05BE32' WHERE id=-71;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='EACEDD6D072E2075FBE3797E2BB99AD9F839' WHERE id=-72;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='62ED6136546784602D2DD587186137C0ABE9' WHERE id=-73;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='AD2AC696CE92F21DE36A9D5527018955E77A' WHERE id=-74;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='7D21EC88162CAB80E13C536AC415E7F9126F' WHERE id=-75;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='0E4989ADFD94E53CED9BEED67C3D01BD0281' WHERE id=-76;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='FA93BB7BC8AF566CE5CA22698208154D22E1' WHERE id=-77;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='09231B6FAA16992813B9436123347E69E5B1' WHERE id=-78;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='74D4E342FA0DBFADBD9E8953F8574F2BE0FF' WHERE id=-79;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='2E6CF9CC1BEC5B1FE187F5F510336FE4C816' WHERE id=-80;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='07E388D822E3C225FF5E7608750D8A345118' WHERE id=-81;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='E07B5A82032DCC4B117EEA9807C76CF4BD14' WHERE id=-82;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='4288622410FBDDD10352C29510EC3B89759A' WHERE id=-83;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='08EDD626A4C65860FDC1D57897E4D3168250' WHERE id=-84;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='47C012FC3246F3ED916EBDDE8ECFC7ED1813' WHERE id=-85;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='2A91334CAF9E75291AEB13CDE2C7EC64038F' WHERE id=-86;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='44821AA9C75ED4ECC7F5DDDDDA615CE35E61' WHERE id=-87;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='A9C3A735798018D815129BFE7617F01F8D5E' WHERE id=-88;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='8D27BA1F504D7471241D7BD9DB27D3BE37B7' WHERE id=-89;\n"
        "UPDATE \"" << dbname << "\".EventTypeRole SET uid='25A5B0991319C04ADE60A87908D1BF8BCBEA' WHERE id=-90;\n"

        "UPDATE \"" << dbname << "\".Version SET test=40 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_40to0_0_10_41( const wxString& dbname )
{
    // Version 0.0.10.40 to 0.0.10.41

    // Add field 'uid' and 'changed' to Persona.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  sex INTEGER NOT NULL,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  note TEXT,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        // Remove null values on record 0.
        "UPDATE \"" << dbname << "\".Persona SET sex=0, ref_id=0, note='' WHERE id=0;\n"

        "INSERT INTO \"" << dbname << "\".NewPersona"
        " (id, sex, ref_id, note, uid, changed)\n"
        " SELECT id, sex, ref_id, note, '', 2459754\n"
        " FROM \"" << dbname << "\".Persona;\n"

        "DROP TABLE \"" << dbname << "\".Persona;\n"
        "ALTER TABLE \"" << dbname << "\".NewPersona RENAME TO Persona;\n"
        ;

    // Fill EventType table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Persona WHERE id>0;\n"; // Get id list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Persona"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".Persona SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=41 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_41to0_0_10_42( const wxString& dbname )
{
    // Version 0.0.10.41 to 0.0.10.42

    // Add fields 'uid' and 'changed' to Eventa.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewEventa (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT NOT NULL,\n"
        "  ref_id INTEGER NOT NULL REFERENCES Reference(id),\n"
        "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
        "  date1_id INTEGER NOT NULL REFERENCES Date(id),\n"
        "  date2_id INTEGER NOT NULL REFERENCES Date(id),\n"
        "  place_id INTEGER NOT NULL REFERENCES Place(id),\n"
        "  note TEXT NOT NULL,\n"
        "  date_pt INTEGER NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        "INSERT INTO \"" << dbname << "\".NewEventa"
        " (id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt, uid, changed)\n"
        " SELECT id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt, '', 2459755\n"
        " FROM \"" << dbname << "\".Eventa;\n"

        "DROP TABLE \"" << dbname << "\".Eventa;\n"
        "ALTER TABLE \"" << dbname << "\".NewEventa RENAME TO Eventa;\n"
        ;

    // Fill Eventa table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Eventa WHERE id>0;\n"; // Get id list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Eventa"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".Eventa SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=42 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
}

void UpgradeTest0_0_10_42to0_0_10_43( const wxString& dbname )
{
    // Version 0.0.10.42 to 0.0.10.43

    // Add fields 'uid' and 'changed' to Date and Place.
    wxString update =
        "BEGIN;\n";

    update <<
        "CREATE TABLE \"" << dbname << "\".NewDate (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  jdn INTEGER NOT NULL,\n"
        "  range INTEGER NOT NULL,\n"
        "  rel_id INTEGER NOT NULL REFERENCES RelativeDate(id),\n"
        "  type INTEGER NOT NULL,\n"
        "  descrip TEXT NOT NULL,\n"
        "  record_sch INTEGER NOT NULL,\n"
        "  display_sch INTEGER NOT NULL,\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INTEGER NOT NULL\n"
        ");\n"

        // Remove null values on record 0.
        "UPDATE \"" << dbname << "\".Date SET jdn=0, range=0, rel_id=0,"
        " type=0, descrip='', record_sch=0, display_sch=0"
        " WHERE id=0;"

        "INSERT INTO \"" << dbname << "\".NewDate"
        " (id, jdn, range, rel_id, type, descrip, record_sch, display_sch, uid, changed)\n"
        " SELECT id, jdn, range, rel_id, type, descrip, record_sch, display_sch, '', 2459756\n"
        " FROM \"" << dbname << "\".Date;\n"

        "DROP TABLE \"" << dbname << "\".Date;\n"
        "ALTER TABLE \"" << dbname << "\".NewDate RENAME TO Date;\n"
        ;

    // Fill Date table uid field
    wxString query = "SELECT id FROM \"" + dbname + "\".Date WHERE id>0;\n"; // Get id list
    wxSQLite3Table table = recDb::GetDb()->GetTable( query );
    size_t size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Date"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".Date SET changed=0 WHERE id=0;\n"

        "CREATE TABLE \"" << dbname << "\".NewPlace (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  date1_id INTEGER NOT NULL REFERENCES Date(id),\n"
        "  date2_id INTEGER NOT NULL REFERENCES Date(id),\n"
        "  uid TEXT NOT NULL,\n"
        "  changed INT NOT NULL\n"
        ");\n"

        // Remove null values on record 0.
        "UPDATE \"" << dbname << "\".Place SET date1_id=0, date2_id=0 WHERE id=0;"

        "INSERT INTO \"" << dbname << "\".NewPlace"
        " (id, date1_id, date2_id, uid, changed)\n"
        " SELECT id, date1_id, date2_id, '', 2459755\n"
        " FROM \"" << dbname << "\".Place;\n"

        "DROP TABLE \"" << dbname << "\".Place;\n"
        "ALTER TABLE \"" << dbname << "\".NewPlace RENAME TO Place;\n"
        ;

    // Fill Place table uid field
    query = "SELECT id FROM \"" + dbname + "\".Place WHERE id>0;\n"; // Get id list
    table = recDb::GetDb()->GetTable( query );
    size = (size_t) table.GetRowCount();
    for( size_t i = 0; i < size; i++ ) {
        table.SetRow( i );
        update << "UPDATE \"" << dbname << "\".Place"
            " SET uid='" << recCreateUid() << "'"
            " WHERE id=" << table.GetAsString( 0 ) << ";\n"
            ;
    }
    update <<
        "UPDATE \"" << dbname << "\".Place SET changed=0 WHERE id=0;\n"

        "UPDATE \"" << dbname << "\".Version SET test=43 WHERE id=1;\n"
        "COMMIT;\n"
        ;

    recDb::GetDb()->ExecuteUpdate( update );
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
    case 31: UpgradeTest0_0_10_31to0_0_10_32( dbname );
    case 32: UpgradeTest0_0_10_32to0_0_10_33( dbname );
    case 33: UpgradeTest0_0_10_33to0_0_10_34( dbname );
    case 34: UpgradeTest0_0_10_34to0_0_10_35( dbname );
    case 35: UpgradeTest0_0_10_35to0_0_10_36( dbname );
    case 36: UpgradeTest0_0_10_36to0_0_10_37( dbname );
    case 37: UpgradeTest0_0_10_37to0_0_10_38( dbname );
    case 38: UpgradeTest0_0_10_38to0_0_10_39( dbname );
    case 39: UpgradeTest0_0_10_39to0_0_10_40( dbname );
    case 40: UpgradeTest0_0_10_40to0_0_10_41( dbname );
    case 41: UpgradeTest0_0_10_41to0_0_10_42( dbname );
    case 42: UpgradeTest0_0_10_42to0_0_10_43( dbname );
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
