/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recVersion.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Version record.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
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

#include <rec/recVersion.h>
// For updates
#include <rec/recPersona.h>
#include <rec/recLink.h>

// This is the database version this program is designed to work with.
const int recVerMajor    = 0;
const int recVerMinor    = 0;
const int recVerRev      = 9;
const int recVerTest     = 15;
const wxStringCharType* recVerStr = wxS("0.0.9.15");


recVersion::recVersion( const recVersion& v )
{
    f_id       = v.f_id;
    f_major    = v.f_major;
    f_minor    = v.f_minor;
    f_revision = v.f_revision;
}

void recVersion::Clear()
{
    f_id       = 0;
    f_major    = 0;
    f_minor    = 0;
    f_revision = 0;
}

void recVersion::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Version (major, minor, revision, test) "
            "VALUES (%d, %d, %d, %d);",
            f_major, f_minor, f_revision, f_test
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Version (id, major, minor, revision, test) "
                "VALUES ("ID", %d, %d, %d, %d);",
                f_id, f_major, f_minor, f_revision, f_test
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Version SET major=%d, minor=%d, revision=%d, test=%d "
                "WHERE id="ID";",
                f_major, f_minor, f_revision, f_test, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recVersion::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT major, minor, revision, test FROM Version WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_major    = result.GetInt( 0 );
    f_minor    = result.GetInt( 1 );
    f_revision = result.GetInt( 2 );
    f_test     = result.GetInt( 3 );
    return true;
}

wxString recVersion::GetVersionStr()
{
    recVersion v(1);
    return wxString::Format(
        "%d.%d.%d.%d",
        v.f_major, v.f_minor, v.f_revision, v.f_test
    );
}

void recVersion::Set( int major, int minor, int revision, int test )
{
    recVersion v;
    v.f_id = 1;
    v.f_major = major;
    v.f_minor = minor;
    v.f_revision = revision;
    v.f_test = test;
    v.Save();
}    

bool recVersion::IsEqual( int major, int minor, int revision, int test ) const
{
    bool ret = (f_major == major);

    if( minor == -1 ) return ret;
    ret = ret && (f_minor == minor);

    if( revision == -1 ) return ret;
    ret = ret && (f_revision == revision);

    if( test == -1 ) return ret;
    return ret && (f_test == test);
}

bool recVersion::IsMoreThan( int major, int minor, int revision, int test ) const
{
    if( f_major > major ) return true;
    if( f_major < major ) return false;

    if( minor == -1 ) return false;
    if( f_minor > minor ) return true;
    if( f_minor < minor ) return false;

    if( revision == -1 ) return false;
    if( f_revision > revision ) return true;
    if( f_revision < revision ) return false;

    if( test == -1 ) return false;
    if( f_test > test ) return true;
    return false;
}

bool recVersion::IsLessThan( int major, int minor, int revision, int test ) const
{
    if( f_major < major ) return true;
    if( f_major > major ) return false;

    if( minor == -1 ) return false;
    if( f_minor < minor ) return true;
    if( f_minor > minor ) return false;

    if( revision == -1 ) return false;
    if( f_revision < revision ) return true;
    if( f_revision > revision ) return false;

    if( test == -1 ) return false;
    if( f_test < test ) return true;
    return false;
}

bool recVersion::TestForUpgrade()
{
    if( IsLessThan( 0, 0, 9, 0 ) ) {
        recDb::Message(
            wxString::Format(
                _("Cannot read old database version %s file."),
                GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( IsMoreThan( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        recDb::Message(
            wxString::Format(
                _("Cannot read future database version %s file."),
                GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    return true;
}

//============================================================================
//                 Code to upgrade old versions
//============================================================================

#include <cal/calendar.h>

static void UpgradeTest0_0_9_0to0_0_9_1()
{
    char* sql =
        "ALTER TABLE Event RENAME TO OldEvent;\n"
        "CREATE TABLE Event (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  title TEXT,\n"
        "  type_id INTEGER,\n"
        "  date1_id INTEGER,\n"
        "  date2_id INTEGER,\n"
        "  place_id INTEGER,\n"
        "  note TEXT\n"
        ");\n"
        "INSERT INTO Event"
        " (id, title, type_id, date1_id, date2_id, place_id, note)"
        " SELECT id, title, type_id, date1_id, date2_id, place_id, note FROM OldEvent;"
        "DROP TABLE OldEvent;"

        "ALTER TABLE EventPersona RENAME TO OldEventPersona;\n"
        "CREATE TABLE EventPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  event_id INTEGER,\n"
        "  per_id INTEGER,\n"
        "  role_id INTEGER,\n"
        "  note TEXT,\n"
        "  sequence INTEGER\n"
        ");\n"
        "INSERT INTO EventPersona\n"
        " (id, event_id, per_id, role_id, note, sequence)\n"
        " SELECT id, event_id, per_id, role_id, note, 0 FROM OldEventPersona;\n"
        "DROP TABLE OldEventPersona;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( sql );
    recVersion::Set( 0, 0, 9, 1 );
    recDb::Commit();
}


static void UpgradeTest0_0_9_1to0_0_9_2()
{
    char* sql =
        "CREATE TABLE LinkPersona (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
        "  ind_per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  comment TEXT\n"
        ");\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( sql );

    recLinkPersona lp;
    char* query =
        "SELECT IP.per_id, I.per_id, IP.note "
        "FROM IndividualPersona IP, Individual I "
        "WHERE IP.ind_id=I.id AND NOT IP.per_id=I.per_id;"
    ;
    wxSQLite3ResultSet result = recDb::GetDb()->ExecuteQuery( query );
    while( result.NextRow() ) {
        lp.f_id = 0;
        lp.f_ref_per_id = GET_ID( result.GetInt64( 0 ) );
        lp.f_ind_per_id = GET_ID( result.GetInt64( 1 ) );
        lp.f_conf = 0.999;
        lp.f_comment = result.GetAsString( 2 );
        lp.Save();
    }
    recVersion::Set( 0, 0, 9, 2 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_2to0_0_9_3()
{
    char* sql =
        "DROP TABLE IndividualPersona;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( sql );
    recVersion::Set( 0, 0, 9, 3 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_3to0_0_9_4()
{
    char* query =
        "ALTER TABLE Individual RENAME TO OldIndividual;\n"
        "CREATE TABLE Individual (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  surname TEXT,\n"
        "  given TEXT,\n"
        "  birth_jdn INTEGER,\n"
        "  epitaph TEXT,\n"
        "  sex INTEGER,\n"
        "  fam_id INTEGER,\n"
        "  per_id INTEGER\n"
        ");\n"
        "INSERT INTO Individual\n"
        " (id, surname, given, birth_jdn, epitaph, sex, fam_id, per_id)"
        " SELECT id, surname, given, birth_jdn, epitaph, sex, fam_id, per_id"
        " FROM OldIndividual;\n"
        "DROP TABLE OldIndividual;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 4 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_4to0_0_9_5()
{
    char* query =
        "ALTER TABLE Family RENAME TO OldFamily;\n"
        "CREATE TABLE Family (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  husb_id INTEGER,\n"
        "  wife_id INTEGER\n"
        ");\n"
        "INSERT INTO Family"
        " (id, husb_id, wife_id)"
        " SELECT id, husb_id, wife_id"
        " FROM OldFamily;\n"
        "DROP TABLE OldFamily;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 5 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_5to0_0_9_6()
{
    char* sql =
        "CREATE TABLE LinkEvent (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_event_id INTEGER NOT NULL,\n"
        "  ind_event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  comment TEXT\n"
        ");\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( sql );

    sql = "CREATE TEMP TABLE EventIdList AS SELECT id FROM Event;";
    recDb::GetDb()->ExecuteUpdate( sql );

    char* query =
        "SELECT entity_id FROM ReferenceEntity WHERE entity_type=2;"
    ;
    wxSQLite3ResultSet result = recDb::GetDb()->ExecuteQuery( query );
    while( result.NextRow() ) {
        recDb::DeleteRecord( "EventIdList", GET_ID( result.GetInt64( 0 ) ) );
    }

    sql = 
        "INSERT INTO LinkEvent\n"
        " (ref_event_id, ind_event_id, comment)\n"
        " SELECT id, 0, '' FROM EventIdList;\n"
        "DROP TABLE EventIdList;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( sql );

    recVersion::Set( 0, 0, 9, 6 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_6to0_0_9_7()
{
    recDb::Begin();

    recEventTypeRole role(0);
    role.f_id = -8; // Bride at Marriage
    role.Read();
    role.f_prime = 2;
    role.Save();
    role.f_id = -37; // Wife at Divorce
    role.Read();
    role.f_prime = 2;
    role.Save();

    recVersion::Set( 0, 0, 9, 7 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_7to0_0_9_8()
{
    char* query =
        "INSERT INTO AttributeType (id, grp, name) VALUES(-2, 100,'Condition');"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 8 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_8to0_0_9_9()
{
    char* query =
        "INSERT INTO EventType (id, grp, name) VALUES(-15, 2, 'Register Birth');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-50, -15, 1, 0, 'Born');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-51, -15, 0, 0, 'Parent');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-52, -15, 0, 0, 'Registrant');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-53, -15, 0, 1, 'Registrar');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-54, -15, 0, 0, 'Mentioned');\n"

        "INSERT INTO EventType (id, grp, name) VALUES(-16, 6, 'Register Death');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-55, -16, 1, 0, 'Died');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-56, -16, 0, 0, 'Registrant');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-57, -16, 0, 1, 'Registrar');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-58, -16, 0, 0, 'Mentioned');\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 9 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_9to0_0_9_10()
{
    char* query =
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-59, -3, 3, 0, 'Spouse');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-60, -15, 0, 0, 'Mother');\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 10 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_10to0_0_9_11()
{
    char* query =
        "INSERT INTO EventType (id, grp, name) VALUES(-17, 7, 'Residence');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-61, -17, 0, 0, 'Family');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-62, -17, 0, 0, 'Visitor');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-63, -17, 0, 0, 'Lodger');\n"
        "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-64, -17, 0, 0, 'Boarder');\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 11 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_11to0_0_9_12()
{
    char* query =
        "ALTER TABLE LinkEvent RENAME TO OldLinkEvent;\n"
        "CREATE TABLE LinkEvent (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_event_id INTEGER NOT NULL,\n"
        "  ind_event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  comment TEXT\n"
        ");\n"
        "INSERT INTO LinkEvent"
        " (id, ref_event_id, ind_event_id, conf, comment)"
        " SELECT id, ref_event_id, ind_event_id, 0.999, comment"
        " FROM OldLinkEvent;\n"
        "DROP TABLE OldLinkEvent;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 12 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_12to0_0_9_13()
{
    char* query =
        "ALTER TABLE Individual RENAME TO OldIndividual;\n"
        "CREATE TABLE Individual (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  surname TEXT,\n"
        "  given TEXT,\n"
        "  epitaph TEXT,\n"
        "  fam_id INTEGER,\n"
        "  per_id INTEGER\n"
        ");\n"
        "INSERT INTO Individual"
        " (id, surname, given, epitaph, fam_id, per_id)"
        " SELECT id, surname, given, epitaph, fam_id, per_id"
        " FROM OldIndividual;\n"
        "DROP TABLE OldIndividual;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 13 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_13to0_0_9_14()
{
    char* query =
        "ALTER TABLE Date RENAME TO OldDate;\n"

        "CREATE TABLE RelativeDate (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  val INTEGER,\n"
        "  range INTEGER,\n"
        "  unit INTEGER,\n"
        "  base_id INTEGER NOT NULL REFERENCES Date(id),\n"
        "  type INTEGER,\n"
        "  scheme INTEGER\n"
        ");\n"
        "CREATE TABLE Date (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  jdn INTEGER,\n"
        "  range INTEGER,\n"
        "  rel_id INTEGER,\n"
        "  type INTEGER,\n"
        "  descrip TEXT,\n"
        "  record_sch INTEGER,\n"
        "  display_sch INTEGER\n"
        ");\n"
        // Put all base dates back
        "INSERT INTO Date"
        " (id, jdn, range, rel_id, type, descrip, record_sch, display_sch)"
        " SELECT id, jdn, range, 0, type, descrip, record_sch, display_sch"
        " FROM OldDate;\n"


        "CREATE TABLE TempRelativeDate (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  val INTEGER,\n"
        "  range INTEGER,\n"
        "  unit INTEGER,\n"
        "  base_id INTEGER NOT NULL REFERENCES Date(id),\n"
        "  type INTEGER,\n"
        "  scheme INTEGER,\n"
        "  orig_id INTEGER\n"
        ");\n"

        "INSERT INTO TempRelativeDate"
        " (val, range, unit, base_id, type, scheme, orig_id)"
        " SELECT jdn, range, base_unit, base_id, base_style, record_sch, id"
        " FROM OldDate WHERE base_id<>0;\n"

        "INSERT INTO RelativeDate"
        " (id, val, range, unit, base_id, type, scheme)"
        " SELECT id, val, range, unit, base_id, type, scheme"
        " FROM TempRelativeDate;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id, val, range, unit, base_id, type, scheme, orig_id"
        " FROM TempRelativeDate;"
    );
    wxSQLite3Table table = recDb::GetDb()->GetTable( sql );

    for( int i = 0 ; i < table.GetRowCount() ; i++ )
    {
        table.SetRow( i );
        idt relDateID = GET_ID( table.GetInt64( 0 ) );
        long relValue = table.GetInt( 1 );
        long relRange = table.GetInt( 2 );
        CalendarUnit unit = (CalendarUnit) table.GetInt( 3 );
        idt baseDateID = GET_ID( table.GetInt64( 4 ) );
        int relType = table.GetInt( 5 );
        CalendarScheme relSch = (CalendarScheme) table.GetInt( 6 );
        idt newDateID = GET_ID( table.GetInt64( 7 ) );
        sql.Format(
            "SELECT jdn, range, type"
            " FROM Date WHERE id="ID";",
            baseDateID
        );
        wxSQLite3Table table2 = recDb::GetDb()->GetTable( sql );

        long jdn1 = table2.GetInt( 0 );
        long jdn2 = jdn1 + table2.GetInt( 1 );
        int baseType = table2.GetInt( 2 );

        switch( table.GetInt( 5 ) )
        {
        case 1: //recRelativeDate::TYPE_AgeRoundDown:
            if( !calAddToJdn( jdn1, -(relValue+relRange), unit, relSch ) ) {
                return;
            }
            jdn1++;
            if( !calAddToJdn( jdn2, -relValue, unit, relSch ) ) {
                return;
            }
            break;
        default:
            return;
        }

        sql.Format(
            "UPDATE Date SET jdn=%ld, range=%ld, rel_id="ID" "
            "WHERE id="ID";",
            jdn1, jdn2 - jdn1, relDateID, newDateID
        );
        recDb::GetDb()->ExecuteUpdate( sql );

    }
    query =
        "DROP TABLE TempRelativeDate;\n"
        "DROP TABLE OldDate;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( query );

    recVersion::Set( 0, 0, 9, 14 );
    recDb::Commit();
}

static void UpgradeTest0_0_9_14to0_0_9_15()
{
    char* query =
        "ALTER TABLE LinkEvent RENAME TO OldLinkEvent;\n"
        "CREATE TABLE LinkEvent (\n"
        "  id INTEGER PRIMARY KEY,\n"
        "  ref_event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  ind_event_id INTEGER NOT NULL REFERENCES Event(id),\n"
        "  conf FLOAT NOT NULL,\n"
        "  comment TEXT\n"
        ");\n"
        "INSERT INTO LinkEvent"
        " (id, ref_event_id, ind_event_id, conf, comment)"
        " SELECT id, ref_event_id, ind_event_id, conf, comment"
        " FROM OldLinkEvent WHERE ref_event_id<>0;\n"
        "DROP TABLE OldLinkEvent;\n"
    ;
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( query );
    recVersion::Set( 0, 0, 9, 15 );
    recDb::Commit();
}


static void UpgradeRev0_0_9toCurrent( int test )
{
    switch( test )
    {
    case 0:
        UpgradeTest0_0_9_0to0_0_9_1();
    case 1: // Fall thru intended
        UpgradeTest0_0_9_1to0_0_9_2();
    case 2:
        UpgradeTest0_0_9_2to0_0_9_3();
    case 3:
        UpgradeTest0_0_9_3to0_0_9_4();
    case 4:
        UpgradeTest0_0_9_4to0_0_9_5();
    case 5:
        UpgradeTest0_0_9_5to0_0_9_6();
    case 6:
        UpgradeTest0_0_9_6to0_0_9_7();
    case 7:
        UpgradeTest0_0_9_7to0_0_9_8();
    case 8:
        UpgradeTest0_0_9_8to0_0_9_9();
    case 9:
        UpgradeTest0_0_9_9to0_0_9_10();
    case 10:
        UpgradeTest0_0_9_10to0_0_9_11();
    case 11:
        UpgradeTest0_0_9_11to0_0_9_12();
    case 12:
        UpgradeTest0_0_9_12to0_0_9_13();
    case 13:
        UpgradeTest0_0_9_13to0_0_9_14();
    case 14:
        UpgradeTest0_0_9_14to0_0_9_15();
    }
}


bool recVersion::DoUpgrade()
{
    wxASSERT( f_id == 1 );
    if( TestForUpgrade() == false ) return false;

    try {
        if( IsEqual( 0, 0, 9 ) ) {
            UpgradeRev0_0_9toCurrent( f_test );
            Read();
        }
    }
    catch( wxSQLite3Exception& e ) {
        ErrorMessage( e );
        Rollback();
        return false;
    }

    wxASSERT( IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) );
    return true;
}


// End of recVersion.cpp file
