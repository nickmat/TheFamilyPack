/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        testDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     CppUnit test program for recDb and derived database classes.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     30th September 2010
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

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif // WX_PRECOMP

#include <wx/sstream.h>
#include <wx/filefn.h>

#include <cal/calendar.h>
#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recPersona.h>
#include <rec/recEvent.h>
#include <rec/recReference.h>

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class RecTestCase : public CppUnit::TestCase
{
public:
    RecTestCase() {}

private:
    CPPUNIT_TEST_SUITE( RecTestCase );
        CPPUNIT_TEST( TestDbCreate );
        CPPUNIT_TEST( TestDate );
        CPPUNIT_TEST( TestPlace );
        CPPUNIT_TEST( TestPlacePart );
        CPPUNIT_TEST( TestPlacePartType );
        CPPUNIT_TEST( TestPersona );
        CPPUNIT_TEST( TestAttribute );
        CPPUNIT_TEST( TestAttributeType );
        CPPUNIT_TEST( TestEvent );
        CPPUNIT_TEST( TestEventType );
        CPPUNIT_TEST( TestEventTypeRole );
        CPPUNIT_TEST( TestPersonaEvent );
        CPPUNIT_TEST( TestReference );
        CPPUNIT_TEST( TestReferenceEntity );
        CPPUNIT_TEST( TestShutdown );
    CPPUNIT_TEST_SUITE_END();

    void TestDbCreate();
    void TestDate();
    void TestPlace();
    void TestPlacePart();
    void TestPlacePartType();
    void TestPersona();
    void TestAttribute();
    void TestAttributeType();
    void TestEvent();
    void TestEventType();
    void TestEventTypeRole();
    void TestPersonaEvent();
    void TestReference();
    void TestReferenceEntity();
    void TestShutdown();

    DECLARE_NO_COPY_CLASS(RecTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( RecTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( RecTestCase, "RecTestCase" );

void RecTestCase::TestDbCreate()
{
    wxString fname = "./TestDb.tfpd";
    wxRemoveFile( fname );
    recDb::SetDb( new wxSQLite3Database() );

    bool ret = recDb::CreateDb( fname, 0 );
    CPPUNIT_ASSERT( ret == true );
}

void RecTestCase::TestDate()
{
    id_t id;

    recDate date1;
    date1.f_id = 0;
    date1.f_jdn = 2432814L;
    date1.f_range = 0;
    date1.f_type = recDate::FLG_BEFORE | recDate::FLG_RANGE;
    date1.f_desc = "Good date";
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
    date1.f_desc = "Rubbish period";
    date1.f_record_sch = CALENDAR_SCH_Julian;
    date1.f_display_sch = CALENDAR_SCH_Julian;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    date1.Save();
    CPPUNIT_ASSERT( date1.f_id == id );
    date2.Read();
    CPPUNIT_ASSERT( date1 == date2 );

    date1.f_id = 999;
    date1.f_desc = "whole new start";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    date1.Save();
    CPPUNIT_ASSERT( date1.f_id == 999 );
    date2.f_id = date1.f_id;
    date2.Read();
    CPPUNIT_ASSERT( date1 == date2 );

    date1.f_id = 0;
    date1.f_desc = "This shouldn't be here";
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
    id_t id;

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
    id_t id;

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
    id_t id;

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
    id_t id;

    recPersona persona1;
    persona1.f_id = 0;

    persona1.f_sex = SEX_Male;
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
}

void RecTestCase::TestAttribute()
{
    id_t id;

    recAttribute attr1;
    attr1.f_id = 0;

    attr1.f_per_id = 1;
    attr1.f_type_id = -2;
    attr1.f_val = "Matthews";
    attr1.f_sequence = 3;
    // f_id = 0 so create new record and set f_id to new value.
    attr1.Save();
    id = attr1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recAttribute attr2;
    attr2.f_id = attr1.f_id;
    attr2.Read();  
    CPPUNIT_ASSERT( attr1 == attr2 );

    attr1.f_per_id = 2;
    attr1.f_type_id = -1;
    attr1.f_val = "Nick";
    attr1.f_sequence = 1;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    attr1.Save();
    CPPUNIT_ASSERT( attr1.f_id == id );
    attr2.Read();
    CPPUNIT_ASSERT( attr1 == attr2 );

    attr1.f_id = 999;
    attr1.f_val = "Anything";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    attr1.Save();
    CPPUNIT_ASSERT( attr1.f_id == 999 );
    attr2.f_id = attr1.f_id;
    attr2.Read();
    CPPUNIT_ASSERT( attr1 == attr2 );

    attr1.f_id = 0;
    attr1.f_val = "More";
    attr1.Save();
    CPPUNIT_ASSERT( attr1.f_id != 0 );
    CPPUNIT_ASSERT( attr1.Exists() == true );
    attr1.Delete();
    CPPUNIT_ASSERT( attr1.Exists() == false );

    CPPUNIT_ASSERT( recAttribute::Exists( 999 ) == true );
    recAttribute::Delete( 999 );
    CPPUNIT_ASSERT( recAttribute::Exists( 999 ) == false );
}

void RecTestCase::TestAttributeType()
{
    id_t id;

    recAttributeType attrtype1;
    attrtype1.f_id = 0;

    attrtype1.f_grp = recAttributeType::ATYPE_Grp_Name;
    attrtype1.f_name = "Surname";
    // f_id = 0 so create new record and set f_id to new value.
    attrtype1.Save();
    id = attrtype1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recAttributeType attrtype2;
    attrtype2.f_id = attrtype1.f_id;
    attrtype2.Read();  
    CPPUNIT_ASSERT( attrtype1 == attrtype2 );

    attrtype1.f_grp = recAttributeType::ATYPE_Grp_Occ;
    attrtype1.f_name = "Bricklayer";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    attrtype1.Save();
    CPPUNIT_ASSERT( attrtype1.f_id == id );
    attrtype2.Read();
    CPPUNIT_ASSERT( attrtype1 == attrtype2 );

    attrtype1.f_id = 999;
    attrtype1.f_name = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    attrtype1.Save();
    CPPUNIT_ASSERT( attrtype1.f_id == 999 );
    attrtype2.f_id = attrtype1.f_id;
    attrtype2.Read();
    CPPUNIT_ASSERT( attrtype1 == attrtype2 );

    attrtype1.f_id = 0;
    attrtype1.f_name = "Nor this";
    attrtype1.Save();
    CPPUNIT_ASSERT( attrtype1.f_id != 0 );
    CPPUNIT_ASSERT( attrtype1.Exists() == true );
    attrtype1.Delete();
    CPPUNIT_ASSERT( attrtype1.Exists() == false );

    CPPUNIT_ASSERT( recAttributeType::Exists( 999 ) == true );
    recAttributeType::Delete( 999 );
    CPPUNIT_ASSERT( recAttributeType::Exists( 999 ) == false );
}

void RecTestCase::TestEvent()
{
    id_t id;

    recEvent record1;
    record1.f_id = 0;

    record1.f_type_id = 2;
    record1.f_val = "Marriage";
    record1.f_date1_id = 3;
    record1.f_date2_id = 4;
    record1.f_place_id = 5;
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recEvent record2;
    record2.f_id = record1.f_id;
    record2.Read();  
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_type_id = 20;
    record1.f_val = "Birth";
    record1.f_date1_id = 15;
    record1.f_date2_id = 16;
    record1.f_place_id = 17;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_val = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == 999 );
    record2.f_id = record1.f_id;
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 0;
    record1.f_val = "Nor this";
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id != 0 );
    CPPUNIT_ASSERT( record1.Exists() == true );
    record1.Delete();
    CPPUNIT_ASSERT( record1.Exists() == false );

    CPPUNIT_ASSERT( recEvent::Exists( 999 ) == true );
    recEvent::Delete( 999 );
    CPPUNIT_ASSERT( recEvent::Exists( 999 ) == false );
}

void RecTestCase::TestEventType()
{
    id_t id;

    recEventType record1;
    record1.f_id = 0;

    record1.f_grp = recEventType::ETYPE_Grp_Union;
    record1.f_name = "Marriage";
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recEventType record2;
    record2.f_id = record1.f_id;
    record2.Read();  
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_grp = recEventType::ETYPE_Grp_Nr_Birth;
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
    id_t id;

    recEventTypeRole record1;
    record1.f_id = 0;

    record1.f_type_id = 3;
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

void RecTestCase::TestPersonaEvent()
{
    id_t id;

    recPersonaEvent record1;
    record1.f_id = 0;

    record1.f_per_id = 3;
    record1.f_event_id = 4;
    record1.f_role_id = 5;
    record1.f_note = "Good person";
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recPersonaEvent record2;
    record2.f_id = record1.f_id;
    record2.Read();  
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_per_id = 19;
    record1.f_event_id = 18;
    record1.f_role_id = 17;
    record1.f_note = "Who he?";
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_id = 999;
    record1.f_note = "Not wanted";
    // f_id = 999 which doesn't exists, so create new record with no change to f_id.
    record1.Save();
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

    CPPUNIT_ASSERT( recPersonaEvent::Exists( 999 ) == true );
    recPersonaEvent::Delete( 999 );
    CPPUNIT_ASSERT( recPersonaEvent::Exists( 999 ) == false );
}

void RecTestCase::TestReference()
{
    id_t id;

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
    id_t id;

    recReferenceEntity record1;
    record1.f_id = 0;

    record1.f_ref_id = 3;
    record1.f_entity_type = recReferenceEntity::TYPE_Persona;
    record1.f_entity_id = 5;
    // f_id = 0 so create new record and set f_id to new value.
    record1.Save();
    id = record1.f_id;
    CPPUNIT_ASSERT( id == 1 );

    recReferenceEntity record2;
    record2.f_id = record1.f_id;
    record2.Read();  
    CPPUNIT_ASSERT( record1 == record2 );

    record1.f_ref_id = 10;
    record1.f_entity_type = recReferenceEntity::TYPE_Attribute;
    record1.f_entity_id = 11;
    // f_id = 1 which exists, so amend record leaving f_id to old value.
    record1.Save();
    CPPUNIT_ASSERT( record1.f_id == id );
    record2.Read();
    CPPUNIT_ASSERT( record1 == record2 );

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

void RecTestCase::TestShutdown()
{
    delete recDb::GetDb();
}

// End of testDatabase.cpp
