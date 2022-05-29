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
//    REQUIRE( from_cit.Equivalent( to_cit ) );

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

TEST_CASE( "Test recRepository::Transfer function", "[recRepository]" )
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

TEST_CASE( "Test recResearcher::Transfer function", "[recResearcher]" )
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
