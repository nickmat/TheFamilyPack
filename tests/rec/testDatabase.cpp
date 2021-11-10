/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        testDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     CppUnit test program for recDb and derived database classes.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     30th September 2010
 * Copyright:   Copyright (c) 2010-2015, Nick Matthews.
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

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif // WX_PRECOMP

#include <wx/sstream.h>
#include <wx/filefn.h>

#include <rec/recDb.h>

// Set to 0 avoid wxSQLite3 execptions which may cause memory leaks
// or 1 otherwise
#define ALLOW_SQL_MEMORY_LEAK 0

#define TEST_FILENAME "./TestDb.tfpd"

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class RecTestCase : public CppUnit::TestCase
{
public:
    RecTestCase() {}

    virtual void setUp();
    virtual void tearDown();

private:
    void AddTestData();

    CPPUNIT_TEST_SUITE( RecTestCase );
        // The order of these are significant as records
        // are created that are used in later tests.
        CPPUNIT_TEST( TestDbCreate );
        CPPUNIT_TEST( TestSystem );
        CPPUNIT_TEST( TestContactList );
        CPPUNIT_TEST( TestDate );
        CPPUNIT_TEST( TestPlace );
        CPPUNIT_TEST( TestPlacePart );
        CPPUNIT_TEST( TestPlacePartType );
        CPPUNIT_TEST( TestPersona );
        CPPUNIT_TEST( TestEvent );
        CPPUNIT_TEST( TestEventType );
        CPPUNIT_TEST( TestEventTypeRole );
        CPPUNIT_TEST( TestEventaPersona );
        CPPUNIT_TEST( TestReference );
        CPPUNIT_TEST( TestReferenceEntity );
        CPPUNIT_TEST( TestIndividual );
        CPPUNIT_TEST( TestLinkPersona );
        CPPUNIT_TEST( TestFamily );
        CPPUNIT_TEST( TestFamilyIndividual );
    CPPUNIT_TEST_SUITE_END();

    void TestDbCreate();
    void TestSystem();
    void TestContactList();
    void TestDate();
    void TestPlace();
    void TestPlacePart();
    void TestPlacePartType();
    void TestPersona();
    void TestEvent();
    void TestEventType();
    void TestEventTypeRole();
    void TestEventaPersona();
    void TestReference();
    void TestReferenceEntity();
    void TestIndividual();
    void TestLinkPersona();
    void TestFamily();
    void TestFamilyIndividual();

    DECLARE_NO_COPY_CLASS(RecTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( RecTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( RecTestCase, "RecTestCase" );

void RecTestCase::setUp()
{
    recInitialize();
    wxString fname = TEST_FILENAME;
    wxRemoveFile( fname );
    recDb::CreateDb( fname, 0 );
}

void RecTestCase::tearDown()
{
    recDb::CloseDb();
    recUninitialize();
}

void RecTestCase::AddTestData()
{
    const char* sql =
        "BEGIN;\n"
        "INSERT INTO Event"
        " (id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt)"
        " VALUES(1, 'Test 1', 0, -1, 0, 0, 0, '', 0);\n"
        "INSERT INTO Event"
        " (id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt)"
        " VALUES(19, 'Test 19', 0, -1, 0, 0, 0, '', 0);\n"

        "INSERT INTO Eventa"
        " (id, title, type_id, date1_id, date2_id, place_id, note, date_pt)"
        " VALUES(1, 'Test 1', -1, 0, 0, 0, '', 0);\n"
        "INSERT INTO Eventa"
        " (id, title, type_id, date1_id, date2_id, place_id, note, date_pt)"
        " VALUES(19, 'Test 19', -1, 0, 0, 0, '', 0);\n"

        "INSERT INTO Persona (id, sex, ref_id, note) VALUES(4, 0, 0, '');\n"
        "INSERT INTO Individual"
        " (id, sex, fam_id, note, privacy, name, surname, epitaph)"
        " VALUES (3, 1, 0, 'Note', 0, 'Name', 'Surname', '');\n"

        "INSERT INTO Persona (id, sex, ref_id, note) VALUES(19, 0, 0, '');\n"
        "INSERT INTO Individual"
        " (id, sex, fam_id, note, privacy, name, surname, epitaph)"
        " VALUES (20, 1, 0, 'Note', 0, 'Name', 'Surname', '');\n"

        "INSERT INTO Persona (id, sex, ref_id, note) VALUES(3, 0, 0, '');\n"
        "INSERT INTO Persona (id, sex, ref_id, note) VALUES(20, 0, 0, '');\n"
        "COMMIT;\n"
    ;
    recDb::GetDb()->ExecuteUpdate( sql );
}

void RecTestCase::TestDbCreate()
{
    // Shutdown the current db
    recDb::CloseDb();

    wxString fname = "./Temp.tfpd";
    wxRemoveFile( fname );

    bool ret = recDb::CreateDb( fname, 0 );
    CPPUNIT_ASSERT( ret == true );
}

void RecTestCase::TestSystem()
{
    // The System table has a fixed number of entries created when
    // the database is created, so is treated diferently to the others.

    idt user;
    CPPUNIT_ASSERT_NO_THROW( user = recGetCurrentUser() );
    CPPUNIT_ASSERT_NO_THROW( recSetCurrentUser( 123 ) );
    CPPUNIT_ASSERT( recGetCurrentUser() == 123 );
    recSetCurrentUser( user );
}

void RecTestCase::TestContactList()
{
    recContactList record1;
    record1.FSetID( 0 );
    record1.FSetIndID( 3 );  // Doesn't exist so will cause an exception on Save()
#if ALLOW_SQL_MEMORY_LEAK
    // id = 0 so create new record and set id to new value.
    CPPUNIT_ASSERT_THROW( record1.Save(), wxSQLite3Exception );
#endif
    recIndividual ind(0);
    ind.FSetID(3);
    CPPUNIT_ASSERT_NO_THROW( ind.Save() );
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    idt id = record1.FGetID();
    CPPUNIT_ASSERT( id > 0 );

    recContactList record2;
    record2.FSetID( record1.FGetID() );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetIndID( 0 );
    // id exists, so amend record leaving id to old value.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.f_id == id );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 999 );
    record1.FSetIndID( 3 );
    // id = 999 which doesn't exists, so create new record with no change to id.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.FGetID() == 999 );
    record2.FSetID( record1.FGetID() );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 0 );
    record1.FSetIndID( 0 );
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.FGetID() != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    CPPUNIT_ASSERT_NO_THROW( record1.Delete() );
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recContactList::Exists( 999 ) == true );
    recContactList::Delete( 999 );
    CPPUNIT_ASSERT( recContactList::Exists( 999 ) == false );
}

void RecTestCase::TestDate()
{
    idt id;

    recDate date1;
    date1.f_id = 0;
    date1.f_jdn = 2432814L;
    date1.f_range = 0;
    date1.f_rel_id = 0;
    date1.f_type = recDate::FLG_BEFORE | recDate::FLG_RANGE;
    date1.f_descrip = "Good date";
    date1.f_record_sch = CALENDAR_SCH_Gregorian;
    date1.f_display_sch = CALENDAR_SCH_Gregorian;
    // f_id = 0 so create new record and set f_id to new value.
    date1.Save();
    id = date1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recDate date2;
    date2.f_id = date1.f_id;
    date2.Read();
    CPPUNIT_ASSERT( date1 == date2 );

    date1.f_jdn = 2432999L;
    date1.f_range = 12;
    date1.f_type = recDate::FLG_RANGE;
    date1.f_descrip = "Rubbish period";
    date1.f_record_sch = CALENDAR_SCH_Julian;
    date1.f_display_sch = CALENDAR_SCH_Julian;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    date1.Save();
    CPPUNIT_ASSERT( date1.f_id == id );
    date2.Read();
    CPPUNIT_ASSERT( date1 == date2 );

    date1.f_id = 999;
    date1.f_descrip = "whole new start";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    date1.Save();
    CPPUNIT_ASSERT( date1.f_id == 999 );
    date2.f_id = date1.f_id;
    date2.Read();
    CPPUNIT_ASSERT( date1 == date2 );

    date1.f_id = 0;
    date1.f_descrip = "This shouldn't be here";
    date1.Save();
    CPPUNIT_ASSERT( date1.f_id != 0 );
    CPPUNIT_ASSERT( date1.Exists() == true );
    date1.Delete();
    CPPUNIT_ASSERT( date1.Exists() == false );

    CPPUNIT_ASSERT( recDate::Exists( 999 ) == true );
    recDate::Delete( 999 );
    CPPUNIT_ASSERT( recDate::Exists( 999 ) == false );
}

void RecTestCase::TestPlace()
{
    idt id;

    recPlace place1;
    place1.f_id = 0;

    place1.f_date1_id = 3;
    place1.f_date2_id = 7;
    // f_id = 0 so create new record and set f_id to new value.
    place1.Save();
    id = place1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recPlace place2;
    place2.f_id = place1.f_id;
    place2.Read();
    CPPUNIT_ASSERT( place1 == place2 );

    place1.f_date1_id = 10;
    place1.f_date2_id = 11;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    place1.Save();
    CPPUNIT_ASSERT( place1.f_id == id );
    place2.Read();
    CPPUNIT_ASSERT( place1 == place2 );

    place1.f_id = 999;
    place1.f_date1_id = 22;
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    place1.Save();
    CPPUNIT_ASSERT( place1.f_id == 999 );
    place2.f_id = place1.f_id;
    place2.Read();
    CPPUNIT_ASSERT( place1 == place2 );

    place1.f_id = 0;
    place1.f_date1_id = 33;
    place1.Save();
    CPPUNIT_ASSERT( place1.f_id != 0 );
    CPPUNIT_ASSERT( place1.Exists() == true );
    place1.Delete();
    CPPUNIT_ASSERT( place1.Exists() == false );

    CPPUNIT_ASSERT( recPlace::Exists( 999 ) == true );
    recPlace::Delete( 999 );
    CPPUNIT_ASSERT( recPlace::Exists( 999 ) == false );
}

void RecTestCase::TestPlacePart()
{
    idt id;

    recPlacePart pp1;
    pp1.f_id = 0;

    pp1.f_type_id = 3;
    pp1.f_place_id = 7;
    pp1.f_val = "74 High St";
    pp1.f_sequence = 1;
    // f_id = 0 so create new record and set f_id to new value.
    pp1.Save();
    id = pp1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recPlacePart pp2;
    pp2.f_id = pp1.f_id;
    pp2.Read();
    CPPUNIT_ASSERT( pp1 == pp2 );

    pp1.f_type_id = 4;
    pp1.f_place_id = 5;
    pp1.f_val = "Bluebell View";
    pp1.f_sequence = 3;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    pp1.Save();
    CPPUNIT_ASSERT( pp1.f_id == id );
    pp2.Read();
    CPPUNIT_ASSERT( pp1 == pp2 );

    pp1.f_id = 999;
    pp1.f_val = "Shouldn't be here";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    pp1.Save();
    CPPUNIT_ASSERT( pp1.f_id == 999 );
    pp2.f_id = pp1.f_id;
    pp2.Read();
    CPPUNIT_ASSERT( pp1 == pp2 );

    pp1.f_id = 0;
    pp1.f_val = "more errors";
    pp1.Save();
    CPPUNIT_ASSERT( pp1.f_id != 0 );
    CPPUNIT_ASSERT( pp1.Exists() == true );
    pp1.Delete();
    CPPUNIT_ASSERT( pp1.Exists() == false );

    CPPUNIT_ASSERT( recPlacePart::Exists( 999 ) == true );
    recPlacePart::Delete( 999 );
    CPPUNIT_ASSERT( recPlacePart::Exists( 999 ) == false );
}

void RecTestCase::TestPlacePartType()
{
    idt id;

    recPlacePartType ppt1;
    ppt1.f_id = 0;

    ppt1.f_name = "Town";
    // f_id = 0 so create new record and set f_id to new value.
    ppt1.Save();
    id = ppt1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recPlacePartType ppt2;
    ppt2.f_id = ppt1.f_id;
    ppt2.Read();
    CPPUNIT_ASSERT( ppt1 == ppt2 );

    ppt1.f_name = "Village";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    ppt1.Save();
    CPPUNIT_ASSERT( ppt1.f_id == id );
    ppt2.Read();
    CPPUNIT_ASSERT( ppt1 == ppt2 );

    ppt1.f_id = 999;
    ppt1.f_name = "Parish";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    ppt1.Save();
    CPPUNIT_ASSERT( ppt1.f_id == 999 );
    ppt2.f_id = ppt1.f_id;
    ppt2.Read();
    CPPUNIT_ASSERT( ppt1 == ppt2 );

    ppt1.f_id = 0;
    ppt1.f_name = "County";
    ppt1.Save();
    CPPUNIT_ASSERT( ppt1.f_id != 0 );
    CPPUNIT_ASSERT( ppt1.Exists() == true );
    ppt1.Delete();
    CPPUNIT_ASSERT( ppt1.Exists() == false );

    CPPUNIT_ASSERT( recPlacePartType::Exists( 999 ) == true );
    recPlacePartType::Delete( 999 );
    CPPUNIT_ASSERT( recPlacePartType::Exists( 999 ) == false );
}

void RecTestCase::TestPersona()
{
    idt id;

    recPersona persona1;
    persona1.f_id = 0;

    persona1.f_sex = SEX_Male;
    persona1.f_ref_id = 10;
    persona1.f_note = "Someone";
    // f_id = 0 so create new record and set f_id to new value.
    persona1.Save();
    id = persona1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recPersona persona2;
    persona2.f_id = persona1.f_id;
    persona2.Read();
    CPPUNIT_ASSERT( persona1 == persona2 );

    persona1.f_sex = SEX_Female;
    persona1.f_ref_id = 22;
    persona1.f_note = "Another one";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    persona1.Save();
    CPPUNIT_ASSERT( persona1.f_id == id );
    persona2.Read();
    CPPUNIT_ASSERT( persona1 == persona2 );

    persona1.f_id = 999;
    persona1.f_note = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    persona1.Save();
    CPPUNIT_ASSERT( persona1.f_id == 999 );
    persona2.f_id = persona1.f_id;
    persona2.Read();
    CPPUNIT_ASSERT( persona1 == persona2 );

    persona1.f_id = 0;
    persona1.f_note = "Nor this";
    persona1.Save();
    CPPUNIT_ASSERT( persona1.f_id != 0 );
    CPPUNIT_ASSERT( persona1.Exists() == true );
    persona1.Delete();
    CPPUNIT_ASSERT( persona1.Exists() == false );

    CPPUNIT_ASSERT( recPersona::Exists( 999 ) == true );
    recPersona::Delete( 999 );
    CPPUNIT_ASSERT( recPersona::Exists( 999 ) == false );

    // Create some records for later testing, Pa1 is already there
    recPersona per(0);
    per.FSetID( 3 );
    per.Save();
    per.FSetID( 4 );
    per.Save();
    per.FSetID( 19 );
    per.Save();
    per.FSetID( 20 );
    per.Save();
}


void RecTestCase::TestEvent()
{
    idt id;

    recEvent record1;
    record1.FSetID( 0 );

    record1.FSetTitle( "Marriage" );
    record1.FSetTypeID( 10000 ); // Type doesn't exist - should cause exception
    record1.FSetDate1ID( 3 );
    record1.FSetDate2ID( 4 );
    record1.FSetPlaceID( 5 );
    record1.FSetNote( "Good one" );
    record1.FSetDatePt( 2430792 );
#if ALLOW_SQL_MEMORY_LEAK
    // f_id = 0 so create new record and set f_id to new value.
    CPPUNIT_ASSERT_THROW( record1.Save(), wxSQLite3Exception );
#endif
    record1.FSetTypeID( recEventType::ET_Marriage ); // Correct record
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    id = record1.FGetID();
    CPPUNIT_ASSERT( id == 1 );

    recEvent record2;
    record2.FSetID( record1.FGetID() );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetTitle( "Birth" );
    record1.FSetTypeID( recEventType::ET_Birth );
    record1.FSetDate1ID( 15 );
    record1.FSetDate2ID( 16 );
    record1.FSetPlaceID( 17 );
    record1.FSetNote( "And another" );
    record1.FSetDatePt( 2439876 );
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.FGetID() == id );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 999 );
    record1.FSetTitle( "Not wanted" );
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.FGetID() == 999 );
    record2.FSetID( record1.FGetID() );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 0 );
    record1.FSetTitle( "Nor this" );
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.FGetID() != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    CPPUNIT_ASSERT_NO_THROW( record1.Delete() );
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recEvent::Exists( 999 ) == true );
    CPPUNIT_ASSERT_NO_THROW( recEvent::Delete( 999 ) );
    CPPUNIT_ASSERT( recEvent::Exists( 999 ) == false );
    // This leaves vaid Birth Event E1 in the database for use later
    // Create some more records for later testing.
    record1.Clear();
    record1.FSetID( 3 );
    record1.Save();
    record1.FSetID( 4 );
    record1.Save();
    record1.FSetID( 19 );
    record1.Save();
    record1.FSetID( 20 );
    record1.Save();
}

void RecTestCase::TestEventType()
{
    idt id;

    recEventType record1;
    record1.f_id = 0;

    record1.f_grp = recET_GRP_FamUnion;
    record1.f_name = "Marriage";
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recEventType record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_grp = recET_GRP_NrBirth;
    record1.f_name = "Christening";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_name = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_name = "Nor this";
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recEventType::Exists( 999 ) == true );
    recEventType::Delete( 999 );
    CPPUNIT_ASSERT( recEventType::Exists( 999 ) == false );
}

void RecTestCase::TestEventTypeRole()
{
    idt id;

    recEventTypeRole record1;
    record1.f_id = 0;

    record1.f_type_id = 3;
    record1.f_prime = true;
    record1.f_official = false;
    record1.f_name = "Bride";
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recEventTypeRole record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_type_id = 4;
    record1.f_name = "Groom";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_name = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_name = "Nor this";
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recEventTypeRole::Exists( 999 ) == true );
    recEventTypeRole::Delete( 999 );
    CPPUNIT_ASSERT( recEventTypeRole::Exists( 999 ) == false );
}

void RecTestCase::TestEventaPersona()
{
    idt id;
    CPPUNIT_ASSERT_NO_THROW( AddTestData() );

    recEventaPersona record1;
    record1.FSetID( 0 );

    record1.FSetEventaID( 1 );    // Needs to exist
    record1.FSetPerID( 3 );      // Needs to exist
    record1.FSetRoleID( 10000 ); // Doesn't exist, make Save() throw
    record1.FSetNote( "Good person" );
    record1.FSetPerSeq( 123 );
#if ALLOW_SQL_MEMORY_LEAK
    // f_id = 0 so create new record and set f_id to new value.
    CPPUNIT_ASSERT_THROW( record1.Save(), wxSQLite3Exception );
#endif
    record1.FSetRoleID( recEventTypeRole::ROLE_Birth_Born ); // Correct record
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    id = record1.FGetID();
    CPPUNIT_ASSERT( id == 1 );

    recEventaPersona record2;
    record2.FSetID( record1.FGetID() );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetEventaID( 19 );    // Needs to exist
    record1.FSetPerID( 20 );      // Needs to exist
    record1.FSetRoleID( recEventTypeRole::ROLE_Baptism_Baptised );
    record1.FSetNote( "Who he?" );
    record1.FSetPerSeq( 321 );
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.f_id == id );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 999 );
    record1.FSetNote( "Not wanted" );
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.FSetID( record1.FGetID() );
    CPPUNIT_ASSERT_NO_THROW( record2.Read() );
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 0 );
    record1.FSetNote( "Nor this" );
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    CPPUNIT_ASSERT_NO_THROW( record1.Delete() );
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recEventaPersona::Exists( 999 ) == true );
    CPPUNIT_ASSERT_NO_THROW( recEventaPersona::Delete( 999 ) );
    CPPUNIT_ASSERT( recEventaPersona::Exists( 999 ) == false );
}

void RecTestCase::TestReference()
{
    idt id;

    recReference record1;
    record1.f_id = 0;

    record1.f_title = "A Good Start";
    record1.f_statement = "Lots of facts and figures";
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recReference record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_title = "Routine Stuff";
    record1.f_statement = "Mundane bits and pieces";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_statement = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_statement = "Nor this";
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recReference::Exists( 999 ) == true );
    recReference::Delete( 999 );
    CPPUNIT_ASSERT( recReference::Exists( 999 ) == false );
}

void RecTestCase::TestReferenceEntity()
{
    idt id;

    recReferenceEntity record1;
    record1.f_id = 0;

    record1.f_ref_id = 3;
    record1.f_entity_type = recReferenceEntity::TYPE_Name;
    record1.f_entity_id = 5;
    record1.f_sequence = 1;
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recReferenceEntity record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );
#if 0
    record1.f_ref_id = 10;
    record1.f_entity_type = recReferenceEntity::TYPE_Relationship;
    record1.f_entity_id = 11;
    record1.f_sequence = 2;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );
#endif
    record1.f_id = 999;
    record1.f_entity_id = 8888;
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_entity_id = 7777;
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recReferenceEntity::Exists( 999 ) == true );
    recReferenceEntity::Delete( 999 );
    CPPUNIT_ASSERT( recReferenceEntity::Exists( 999 ) == false );
}

void RecTestCase::TestIndividual()
{
    idt id;

    recIndividual record1;
    record1.f_id = 0;

    record1.FSetSex( SEX_Male );
    record1.f_surname     = "Matthews";
    record1.f_name        = "Nick Matthews";
    record1.f_epitaph     = "(1948-)";
    record1.f_note        = "A Note";
    record1.f_fam_id      = 4;
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id > 0 );

    recIndividual record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetSex( SEX_Male );
    record1.f_surname     = "Bloggs";
    record1.f_name        = "Fred Bloggs";
    record1.f_epitaph     = "(1948-)";
    record1.f_fam_id      = 18;
//    record1.f_per_id      = 17;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_surname = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_surname = "Nor this";
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recIndividual::Exists( 999 ) == true );
    recIndividual::Delete( 999 );
    CPPUNIT_ASSERT( recIndividual::Exists( 999 ) == false );

    // Create some records for later testing
    recIndividual ind(0);
    ind.FSetID( 6 );
    ind.Save();
    ind.FSetID( 12 );
    ind.Save();
}

void RecTestCase::TestLinkPersona()
{
    idt id;
    CPPUNIT_ASSERT_NO_THROW( AddTestData() );

    recIndividualPersona record1;
    record1.f_id = 0;

    record1.f_ind_id = 3;
    record1.f_per_id = 4;
    record1.f_conf = 0.5;
    record1.f_note = "This is he";
    // f_id = 0 so create new record and set f_id to new value.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recIndividualPersona record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_ind_id = 20;
    record1.f_per_id = 19;
    record1.f_conf = 0.333;
    record1.f_note = "And maybe me";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_note = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    CPPUNIT_ASSERT_NO_THROW( record1.Save() );
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_note = "Nor this";
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recIndividualPersona::Exists( 999 ) == true );
    recIndividualPersona::Delete( 999 );
    CPPUNIT_ASSERT( recIndividualPersona::Exists( 999 ) == false );
}

void RecTestCase::TestFamily()
{
    idt id;

    recFamily record1;
    record1.f_id = 0;

    record1.f_husb_id  = 3;
    record1.f_wife_id  = 4;
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    // Database is created with initial default family, so this is 2.
    CPPUNIT_ASSERT( id == 2 );

    recFamily record2;
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_husb_id  = 16;
    record1.f_wife_id  = 15;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_husb_id = 8888;
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_husb_id = 7777;
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recFamily::Exists( 999 ) == true );
    recFamily::Delete( 999 );
    CPPUNIT_ASSERT( recFamily::Exists( 999 ) == false );

    // Create some records for later testing
    recFamily fam(0);
    fam.FSetID( 5 );
    fam.Save();
    fam.FSetID( 11 );
    fam.Save();
}

void RecTestCase::TestFamilyIndividual()
{
    idt id;

    recFamilyIndividual record1;
    record1.FSetID( 0 );

    record1.FSetFamID( 5 );
    record1.FSetIndID( 6 );
    record1.FSetSeqChild( 1 );
    record1.FSetSeqParent( 2 );
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.FGetID();
    CPPUNIT_ASSERT( id == 1 );

    recFamilyIndividual record2;
    record2.FSetID( record1.FGetID() );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetFamID( 11 );
    record1.FSetIndID( 12 );
    record1.FSetSeqChild( 3 );
    record1.FSetSeqParent( 4 );
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.FGetID() == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 999 );
    record1.FSetSeqChild( 8 );
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.FGetID() == 999 );
    record2.FSetID( record1.FGetID() );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.FSetID( 0 );
    record1.FSetSeqChild( 7 );
    record1.Save();
    CPPUNIT_ASSERT( record1.FGetID() != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recFamilyIndividual::Exists( 999 ) == true );
    recFamilyIndividual::Delete( 999 );
    CPPUNIT_ASSERT( recFamilyIndividual::Exists( 999 ) == false );
}

// End of testDatabase.cpp
