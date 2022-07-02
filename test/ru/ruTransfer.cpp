/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        test/ru/ruTransfer.cpp
 * Project:     recUnit: Unit test program for the rec library.
 * Purpose:     Test the tranfer of records from one database to another.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th April 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  recUnit is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  recUnit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with recUnit. If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <catch2/catch.hpp>

#include "ruMain.h"

#include <rec/recDb.h>

struct RecordCounts
{
    const char* m_dbname;
    size_t citation = 0;
    size_t citationpart = 0;
    size_t citationparttype = 0;
    size_t contact = 0;
    size_t contactlist = 0;
    size_t contacttype = 0;
    size_t eventa = 0;
    size_t eventapersona = 0;
    size_t eventtype = 0;
    size_t eventtyperole = 0;
    size_t date = 0;
    size_t gallery = 0;
    size_t gallerymedia = 0;
    size_t media = 0;
    size_t mediadata = 0;
    size_t name = 0;
    size_t namepart = 0;
    size_t nameparttype = 0;
    size_t namestyle = 0;
    size_t persona = 0;
    size_t place = 0;
    size_t placepart = 0;
    size_t placeparttype = 0;
    size_t relativedate = 0;
    size_t repository = 0;
    size_t researcher = 0;

    RecordCounts( const char* dbname ) : m_dbname( dbname ) { Reset(); }

    void Reset() {
        citation = recCitation::Count( m_dbname );
        citationpart = recCitationPart::Count( m_dbname );
        citationparttype = recCitationPartType::Count( m_dbname );
        contact = recContact::Count( m_dbname );
        contactlist = recContactList::Count( m_dbname );
        contacttype = recContactType::Count( m_dbname );
        date = recDate::Count( m_dbname );
        eventa = recEventa::Count( m_dbname );
        eventapersona = recEventaPersona::Count( m_dbname );
        eventtype = recEventType::Count( m_dbname );
        eventtyperole = recEventTypeRole::Count( m_dbname );
        gallery = recGallery::Count( m_dbname );
        gallerymedia = recGalleryMedia::Count( m_dbname );
        media = recMedia::Count( m_dbname );
        mediadata = recMediaData::Count( m_dbname );
        name = recName::Count( m_dbname );
        namepart = recNamePart::Count( m_dbname );
        nameparttype = recNamePartType::Count( m_dbname );
        namestyle = recNameStyle::Count( m_dbname );
        persona = recPersona::Count( m_dbname );
        place = recPlace::Count( m_dbname );
        placepart = recPlacePart::Count( m_dbname );
        placeparttype = recPlacePartType::Count( m_dbname );
        relativedate = recRelativeDate::Count( m_dbname );
        repository = recRepository::Count( m_dbname );
        researcher = recResearcher::Count( m_dbname );
    }
    bool Equal( const RecordCounts& rcs ) {
        return
            citation == rcs.citation &&
            citationpart == rcs.citationpart &&
            citationparttype == rcs.citationparttype &&
            contact == rcs.contact &&
            contactlist == rcs.contactlist &&
            contacttype == rcs.contacttype &&
            date == rcs.date &&
            eventa == rcs.eventa &&
            eventapersona == rcs.eventapersona &&
            eventtype == rcs.eventtype &&
            eventtyperole == rcs.eventtyperole &&
            gallery == rcs.gallery &&
            gallerymedia == rcs.gallerymedia &&
            media == rcs.media &&
            mediadata == rcs.media &&
            name == rcs.name &&
            namepart == rcs.namepart &&
            nameparttype == rcs.nameparttype &&
            namestyle == rcs.namestyle &&
            persona == rcs.persona &&
            place == rcs.place &&
            placepart == rcs.placepart &&
            placeparttype == rcs.placeparttype &&
            relativedate == rcs.relativedate &&
            repository == rcs.repository &&
            researcher == rcs.researcher
            ;
    }
};

TEST_CASE( "Test recCitation::Transfer function", "[Citation]" )
{
    // Also includes test for [CitationPart]
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recCitation::Exists( 1, g_maindb ) );
    REQUIRE( recCitation::Exists( 1, g_extdb1 ) );
    recCitation from_cit( 1, g_extdb1 );

    idt to_id = recCitation::Transfer( 1, g_extdb1, 0, g_maindb );
    REQUIRE( to_id == 1 );
    recCitation to_cit( 1, g_maindb );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.citation == rc_main.citation + 1 );
    REQUIRE( rcnew.citationpart == rc_main.citationpart + 6 );
    REQUIRE( rcnew.citationparttype == rc_main.citationparttype + 6 );
    REQUIRE( rcnew.repository == rc_main.repository + 1 );

    REQUIRE( recCitation::RemoveFromDatabase( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recCitationPartType::Transfer function", "[CitationPartType]" )
{
    int cnt_main = recCitationPartType::Count( g_maindb );
    int cnt_extdb = recCitationPartType::Count( g_extdb1 );

    REQUIRE( !recCitationPartType::Exists( 1, g_maindb ) );
    REQUIRE( recCitationPartType::Exists( 2, g_extdb1 ) );
    recCitationPartType from_cpt( 2, g_extdb1 );

    idt to_id = recCitationPartType::Transfer( 2, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recCitationPartType to_cpt( 1, g_maindb );
    REQUIRE( from_cpt.Equivalent( to_cpt ) );

    // We don't have any common data for this yet.
    // to_id = recCitationPartType::Transfer( -4, g_extdb1, g_maindb );
    // REQUIRE( to_id == -4 );

    REQUIRE( recCitationPartType::DeleteIfOrphaned( 1, g_maindb ) );

    REQUIRE( recCitationPartType::Count( g_maindb ) == cnt_main );
    REQUIRE( recCitationPartType::Count( g_extdb1 ) == cnt_extdb );
}

TEST_CASE( "Test recContactList::Transfer function", "[ContactList]" )
{
    int cnt_cl_main = recContactList::Count( g_maindb );
    int cnt_c_main = recContact::Count( g_maindb );
    int cnt_ct_main = recContactType::Count( g_maindb );
    int cnt_cl_extdb = recContactList::Count( g_extdb1 );
    int cnt_c_extdb = recContact::Count( g_extdb1 );
    int cnt_ct_extdb = recContactType::Count( g_extdb1 );

    REQUIRE( !recContactList::Exists( 1, g_maindb ) );
    REQUIRE( recContactList::Exists( 2, g_extdb1 ) );
    recContactList from_cl( 2, g_extdb1 );
    recIdVec from_conIDs = from_cl.GetContactIDs( g_extdb1 );
    REQUIRE( from_conIDs.size() == 3 );

    idt to_id = recContactList::Transfer( 2, g_extdb1, 0, g_maindb );
    REQUIRE( to_id == 1 );
    recContactList to_cl( to_id, g_maindb );
    REQUIRE( to_cl.Equivalent( from_cl ) );
    recIdVec to_conIDs = to_cl.GetContactIDs( g_maindb );
    REQUIRE( to_conIDs.size() == 3 );

    // Add a new contact to extdb
    recContact new_con( 0 );
    new_con.FSetListID( 2 );
    new_con.FSetTypeID( -2 );
    new_con.FSetValue( "0123 456789" );
    new_con.Save( g_extdb1 );
    from_conIDs = from_cl.GetContactIDs( g_extdb1 );
    REQUIRE( from_conIDs.size() == 4 );

    recContactList::Transfer( 2, g_extdb1, 1, g_maindb );
    to_conIDs = recContactList::GetContactIDs( to_id, g_maindb );
    REQUIRE( to_conIDs.size() == 4 );

    recContact::RemoveFromDatabase( new_con.FGetID(), g_extdb1 );
    from_conIDs = from_cl.GetContactIDs( g_extdb1 );
    REQUIRE( from_conIDs.size() == 3 );

    recContactList::Transfer( 2, g_extdb1, 1, g_maindb );
    to_conIDs = recContactList::GetContactIDs( to_id, g_maindb );
    REQUIRE( to_conIDs.size() == 3 );

    REQUIRE( recContactList::RemoveFromDatabase( to_id, g_maindb ) );

    REQUIRE( recContactList::Count( g_maindb ) == cnt_cl_main );
    REQUIRE( recContact::Count( g_maindb ) == cnt_c_main );
    REQUIRE( recContactType::Count( g_maindb ) == cnt_ct_main );
    REQUIRE( recContactList::Count( g_extdb1 ) == cnt_cl_extdb );
    REQUIRE( recContact::Count( g_extdb1 ) == cnt_c_extdb );
    REQUIRE( recContactType::Count( g_extdb1 ) == cnt_ct_extdb );
}

TEST_CASE( "Test recContactType::Transfer function", "[ContactType]" )
{
    int cnt_main = recContactType::Count( g_maindb );
    int cnt_extdb = recContactType::Count( g_extdb1 );

    REQUIRE( !recContactType::Exists( 1, g_maindb ) );
    REQUIRE( recContactType::Exists( 2, g_extdb1 ) );
    recContactType from_ct( 2, g_extdb1 );

    idt to_id = recContactType::Transfer( 2, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recContactType to_ct( 1, g_maindb );
    REQUIRE( from_ct.Equivalent( to_ct ) );

    to_id = recContactType::Transfer( -4, g_extdb1, g_maindb );
    REQUIRE( to_id == -4 );

    REQUIRE( recContactType::DeleteIfOrphaned( 1, g_maindb ) );

    REQUIRE( recContactType::Count( g_maindb ) == cnt_main );
    REQUIRE( recContactType::Count( g_extdb1 ) == cnt_extdb );
}

TEST_CASE( "Test recDate::Transfer function", "[Date]" )
{
    const idt tbase_date = 5982;
    const idt t1_date = 5990;
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recDate::Exists( 1, g_maindb ) );
    REQUIRE( recDate::Exists( t1_date, g_extdb1 ) );
    recDate from_date1( tbase_date, g_extdb1 );
    recDate from_date2( t1_date, g_extdb1 );

    idt to_id = recDate::Transfer( t1_date, g_extdb1, g_maindb );
    REQUIRE( to_id == 2 );
    recDate to_date1( 1, g_maindb ); // Base date
    recDate to_date2( 2, g_maindb ); // t1 date

    REQUIRE( from_date1.FGetJdn() == to_date1.FGetJdn() );
    REQUIRE( from_date2.FGetJdn() == to_date2.FGetJdn() );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.date == rc_main.date + 2 );
    REQUIRE( rcnew.relativedate == rc_main.relativedate + 1 );

    // Remove Base date removes all relative dates
    recDate::RemoveFromDatabase( 1, g_maindb ); 
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recEventTypeRole::Transfer function", "[EventTypeRole]" )
{
    const idt t1_role = 335;
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recEventTypeRole::Exists( 1, g_maindb ) );
    REQUIRE( recEventTypeRole::Exists( t1_role, g_extdb1 ) );
    recEventTypeRole from_role( t1_role, g_extdb1 );

    idt to_id = recEventTypeRole::Transfer( t1_role, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recEventTypeRole to_role( 1, g_maindb );
    REQUIRE( from_role.FGetName() == to_role.FGetName() );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.eventtyperole == rc_main.eventtyperole + 1 );

    REQUIRE( recEventTypeRole::DeleteIfOrphaned( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recEventType::Transfer function", "[EventType]" )
{
    // We only have core data entries for recEventType at this time
    // so add a test record.
    REQUIRE( !recEventType::Exists( 1, g_extdb1 ) );
    recEventType et( 0 );
    et.FSetGrp( recEventTypeGrp::other );
    et.FSetName( "Test" );
    et.FSetUid( recCreateUid() );
    et.FSetChanged( calGetTodayJdn() );
    et.Save( g_extdb1 );

    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recEventType::Exists( 1, g_maindb ) );
    REQUIRE( recEventType::Exists( 1, g_extdb1 ) );
    recEventType from_et( 1, g_extdb1 );

    idt to_id = recEventType::Transfer( 1, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recEventType to_et( 1, g_maindb );
    REQUIRE( from_et.Equivalent( to_et ) );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.eventtype == rc_main.eventtype + 1 );

    REQUIRE( recEventType::DeleteIfOrphaned( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );

    // Remove test record.
    REQUIRE( recEventType::Delete( 1, g_extdb1 ) );
}

TEST_CASE( "Test recGallery::Transfer function", "[Gallery]" )
{
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recGallery::Exists( 1, g_maindb ) );
    REQUIRE( recGallery::Exists( 1, g_extdb1 ) );
    recGallery from_gal( 1, g_extdb1 );

    idt to_id = recGallery::Transfer( 1, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recGallery to_gal( 1, g_maindb );
    REQUIRE( from_gal.Equivalent( to_gal ) );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.gallery == rc_main.gallery + 1 );

    REQUIRE( recGallery::DeleteIfOrphaned( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recMedia::Transfer function with Gallery", "[Media][Gallery]" )
{
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    idt to_medID = recMedia::Transfer( 1, g_extdb1, 0, g_maindb, 0 );
    REQUIRE( to_medID == 1 );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.gallery == rc_main.gallery + 1 );
    REQUIRE( rcnew.gallerymedia == rc_main.gallerymedia + 1 );
    REQUIRE( rcnew.media == rc_main.media + 1 );
    REQUIRE( rcnew.mediadata == rc_main.mediadata + 1 );

    REQUIRE( recMedia::RemoveFromDatabase( to_medID, recMedia::DataInc::always, g_maindb ) );

    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recMedia::Transfer function", "[Media]" )
{
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );
    wxString todb = recAssociate::GetAttachedName( 1, g_maindb );
    REQUIRE( !todb.empty() );
    int to_count = recMediaData::Count( todb );

    idt to_medID = recMedia::Transfer( 56, g_extdb1, 0, g_maindb, 1 );
    REQUIRE( to_medID == 1 );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.media == rc_main.media + 1 );
    REQUIRE( recMediaData::Count( todb ) == to_count + 1 );

    REQUIRE( recMedia::RemoveFromDatabase( to_medID, recMedia::DataInc::always, g_maindb ) );

    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
    REQUIRE( recMediaData::Count( todb ) == to_count );
}

TEST_CASE( "Test recMediaData::Transfer function", "[MediaData]" )
{
    wxString todb = recAssociate::GetAttachedName( 1, g_maindb );
    REQUIRE( !todb.empty() );
    wxString fromdb = recAssociate::GetAttachedName( 1, g_extdb1 );
    REQUIRE( !fromdb.empty() );

    int to_count = recMediaData::Count( todb );

    REQUIRE( !recMediaData::Exists( 1, todb ) );
    REQUIRE( recMediaData::Exists( 2, fromdb ) );

    wxSQLite3Table result = recMediaData::GetMediaDataList( todb );

    idt to_mdID = recMediaData::Transfer( 2, fromdb, todb );
    REQUIRE( to_mdID == 1 );
    REQUIRE( recMediaData::Exists( 1, todb ) );

    recMediaData::Delete( 1, todb );

    REQUIRE( recMediaData::Count( todb ) == to_count );
}

TEST_CASE( "Test recName::Transfer function", "[Name]" )
{
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recName::Exists( 1, g_maindb ) );
    REQUIRE( recName::Exists( 4217, g_extdb1 ) );

    idt to_namID = recName::Transfer( 4217, g_extdb1, 0, 0, 0, g_maindb );
    REQUIRE( to_namID == 1 );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.name == rc_main.name + 1 );
    REQUIRE( rcnew.namepart == rc_main.namepart + 3 );

    REQUIRE( recName::RemoveFromDatabase( to_namID, g_maindb ) );

    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recNamePartType::Transfer function", "[NamePartType]" )
{
    // We only have core data entries for recNamePartType at this time
    // so add a test record.
    REQUIRE( !recNamePartType::Exists( 1, g_extdb1 ) );
    recNamePartType npt( 0 );
    npt.FSetGroup( recNamePartType::NPTypeGrp::other );
    npt.FSetName( "Test" );
    npt.FSetUid( recCreateUid() );
    npt.FSetChanged( calGetTodayJdn() );
    npt.Save( g_extdb1 );

    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recNamePartType::Exists( 1, g_maindb ) );
    REQUIRE( recNamePartType::Exists( 1, g_extdb1 ) );
    recNamePartType from_npt( 1, g_extdb1 );

    idt to_id = recNamePartType::Transfer( 1, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recNamePartType to_npt( 1, g_maindb );
    REQUIRE( from_npt.Equivalent( to_npt ) );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.nameparttype == rc_main.nameparttype + 1 );

    REQUIRE( recNamePartType::DeleteIfOrphaned( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );

    // Remove test record.
    REQUIRE( recNamePartType::Delete( 1, g_extdb1 ) );
}

TEST_CASE( "Test recNameStyle::Transfer function", "[NameStyle]" )
{
    // We only have core data entries for recNameStyle at this time
    // so add a test record.
    REQUIRE( !recNameStyle::Exists( 1, g_extdb1 ) );
    recNameStyle ns( 0 );
    ns.FSetName( "Test" );
    ns.FSetUid( recCreateUid() );
    ns.FSetChanged( calGetTodayJdn() );
    ns.Save( g_extdb1 );

    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recNameStyle::Exists( 1, g_maindb ) );
    REQUIRE( recNameStyle::Exists( 1, g_extdb1 ) );
    recNameStyle from_ns( 1, g_extdb1 );

    idt to_id = recNameStyle::Transfer( 1, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recNameStyle to_ns( 1, g_maindb );
    REQUIRE( from_ns.Equivalent( to_ns ) );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.namestyle == rc_main.namestyle + 1 );

    REQUIRE( recNameStyle::DeleteIfOrphaned( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );

    // Remove test record.
    REQUIRE( recNameStyle::Delete( 1, g_extdb1 ) );
}

TEST_CASE( "Test recPersona::Transfer function", "[Persona]" )
{
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recPersona::Exists( 1, g_maindb ) );
    REQUIRE( recPersona::Exists( 11, g_extdb1 ) );

    idt to_perID = recPersona::Transfer( 11, g_extdb1, 0, g_maindb );
    REQUIRE( to_perID == 1 );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.name == rc_main.name + 1 );
    REQUIRE( rcnew.namepart == rc_main.namepart + 3 );
    REQUIRE( rcnew.persona == rc_main.persona + 1 );

    REQUIRE( recPersona::RemoveFromDatabase( to_perID, g_maindb ) );

    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recPlace::Transfer function", "[Place]" )
{
    const idt tplace = 5402;
    const idt tpp = 5402;
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recPlace::Exists( 1, g_maindb ) );
    REQUIRE( !recPlacePart::Exists( 1, g_maindb ) );
    REQUIRE( recPlace::Exists( tplace, g_extdb1 ) );
    REQUIRE( recPlacePart::Exists( tpp, g_extdb1 ) );
    recPlace from_place( tplace, g_extdb1 );
    recPlacePart from_pp( tpp, g_extdb1 );

    idt to_id = recPlace::Transfer( tplace, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recPlace to_place( 1, g_maindb ); 
    recPlacePart to_pp( 1, g_maindb );

    REQUIRE( from_place.FGetUid() == to_place.FGetUid() );
    REQUIRE( from_pp.FGetValue() == to_pp.FGetValue() );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.place == rc_main.place + 1 );
    REQUIRE( rcnew.placepart == rc_main.placepart + 1 );

    // Remove Base date removes all relative dates
    recPlace::DeleteIfOrphaned( 1, g_maindb );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

TEST_CASE( "Test recRepository::Transfer function", "[Repository]" )
{
    int cnt_main = recRepository::Count( g_maindb );
    int cnt_extdb = recRepository::Count( g_extdb1 );

    REQUIRE( !recRepository::Exists( 1, g_maindb ) );
    REQUIRE( recRepository::Exists( 1, g_extdb1 ) );
    recRepository from_rep( 1, g_extdb1 );

    idt to_id = recRepository::Transfer( 1, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recRepository to_rep( 1, g_maindb );
    REQUIRE( from_rep.CompareUID( to_rep ) == recMatchUID::equal );

    REQUIRE( recRepository::DeleteIfOrphaned( 1, g_maindb ) );

    REQUIRE( recRepository::Count( g_maindb ) == cnt_main );
    REQUIRE( recRepository::Count( g_extdb1 ) == cnt_extdb );
}

TEST_CASE( "Test recResearcher::Transfer function", "[Researcher]" )
{
    RecordCounts rc_main( g_maindb ), rc_extdb( g_extdb1 );

    REQUIRE( !recResearcher::Exists( 1, g_maindb ) );
    REQUIRE( recResearcher::Exists( 1, g_extdb1 ) );
    recResearcher from_res( 1, g_extdb1 );

    idt to_id = recResearcher::Transfer( 1, g_extdb1, g_maindb );
    REQUIRE( to_id == 1 );
    recResearcher to_res( 1, g_maindb );
    //    REQUIRE( from_res.Equivalent( to_res ) );

    RecordCounts rcnew( g_maindb );
    REQUIRE( rcnew.researcher == rc_main.researcher + 1 );

    REQUIRE( recResearcher::DeleteIfOrphaned( to_id, g_maindb ) );
    rcnew.Reset();
    REQUIRE( rcnew.Equal( rc_main ) );
}

/* End of test/ru/ruTransfer.cpp file */
