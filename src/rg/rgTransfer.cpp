/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgTransfer.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Transfer records from a external database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     6th March 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rg/rgDialogs.h>

#include <rec/recDb.h>

//static idt ReferenceTransfer( idt refID, const wxString& extdb, const wxString& todb, idt assID );
//static idt ResearcherTransfer( idt from_resID, const wxString& fromdb, const wxString& todb );

//static idt ContactListTransfer( idt from_clID, const wxString& fromdb, idt to_clID, const wxString& todb );
//static idt ContactTypeTransfer( idt from_ctID, const wxString& fromdb, const wxString& todb );

//static idt CitationTransfer( idt from_citID, const wxString& fromdb, idt to_refID, const wxString& todb );
//static idt CitationPartTypeTransfer( idt from_cptID, const wxString& fromdb, const wxString& todb );
//static idt RepositoryTransfer( idt from_repID, const wxString& fromdb, const wxString& todb );


idt rgTransferReference( wxWindow* wind, idt refID, const wxString& extdb, const wxString& todb )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    // TODO: Determine the Associate database for any media.

    idt to_assID = 0;
    if( recReference::GetMediaCount( refID, extdb ) > 0 ) {
        to_assID = rgSelectAssociate( wind, todb, rgSELSTYLE_Create, nullptr, "Select Database To Store Media" );
    }
    idt newRefID = recReference::Transfer( refID, extdb, todb, to_assID );
    if( newRefID == 0 ) {
        recDb::Rollback( savepoint );
    }
    else {
        recDb::ReleaseSavepoint( savepoint );
    }
    return newRefID;
}

//=======================================================================================================
// Make these functions member functions for their respective record classes
//  static recRecord::Transfer( ... );

#if 0
idt ReferenceTransfer( idt from_refID, const wxString& fromdb, const wxString& todb, idt assID )
{
    if( from_refID == 0 ) return 0;

    recReference from_ref( from_refID, fromdb );
    idt to_refID = recReference::FindUid( from_ref.FGetUid(), todb );
    recReference to_ref( to_refID, todb );
    if( to_refID != 0 && from_ref.FGetChanged() <= to_ref.FGetChanged() ) {
        return to_refID; // Reference already exists and is up to date.
    }

    idt to_higherID = 0;
    if( from_ref.FGetHigherID() ) {
        recReference from_higher( from_ref.FGetHigherID(), fromdb );
        to_higherID = recReference::FindUid( from_higher.FGetUid(), todb );
        wxASSERT( to_higherID != 0 );
        recReference to_higher( to_higherID, todb );
        to_higherID = ReferenceTransfer( from_ref.FGetHigherID(), fromdb, todb, assID );
    }
    idt to_resID = recResearcher::Transfer( from_ref.FGetResID(), fromdb, todb );

    recReference new_ref( from_ref );
    new_ref.FSetID( to_refID );
    new_ref.FSetHigherID( to_higherID );
    new_ref.FSetResID( to_refID );
    new_ref.Save( todb );
    to_refID = new_ref.FGetID();

    // CitationTransfer
    recIdVec from_IDs = recReference::GetCitationList( from_refID, fromdb );
    recIdVec to_IDs = recReference::GetCitationList( to_refID, todb );
    size_t size = std::max( from_IDs.size(), to_IDs.size() );
    for( size_t i = 0; i < size; i++ ) {
        if( i >= from_IDs.size() ) { // No more to copy.
            recCitation::RemoveFromDatabase( to_IDs[i], todb );
            continue;
        }
        recCitation::Transfer( from_IDs[i], fromdb, to_refID, todb );
    }

    // TODO: MediaTransfer

    // TODO: PersonaTransfer
    // TODO: EventaTransfer
    // TODO: EntitiesTransfer

    return to_refID;
}

idt ResearcherTransfer( idt from_resID, const wxString& fromdb, const wxString& todb )
{
    if( from_resID == 0 ) return 0;
    recResearcher from_res( from_resID, fromdb );
    idt to_resID = recResearcher::FindUid( from_res.FGetUid(), todb );
    recResearcher to_res( to_resID, todb );
    if( to_resID == 0 || from_res.FGetChanged() > to_res.FGetChanged() ) {
        idt to_clID = recContactList::Transfer( from_res.FGetConListID(), fromdb, to_res.FGetConListID(), todb );
        recResearcher new_res( from_res );
        new_res.FSetConListID( to_clID );
        new_res.FSetID( to_resID );
        new_res.Save( todb );
        to_resID = new_res.FGetID();
    }

    return to_resID;
}

idt ContactListTransfer( idt from_clID, const wxString& fromdb, idt to_clID, const wxString& todb )
{
    if( from_clID == 0 ) {
        return 0;
    }
    recContactList from_cl( from_clID, fromdb );
    wxASSERT( from_cl.FGetIndID() == 0 ); // TODO: When Individuals get UID's we can find a new ind_id value.
    recContactVec from_cons = from_cl.GetContacts( fromdb );
    recContactList to_cl( to_clID, todb );
    wxASSERT( to_cl.FGetIndID() == 0 ); // TODO: See above.
    if( to_clID == 0 ) {
        to_cl.Save( todb );
        to_clID = to_cl.FGetID();
    }
    recContactVec to_cons = to_cl.GetContacts( todb );
    size_t size = std::max( from_cons.size(), to_cons.size() );

    for( size_t i = 0; i < size; i++ ) {
        if( i >= from_cons.size() ) { // No more to copy.
            to_cons[i].RemoveFromDatabase( todb );
            continue;
        }
        if( i >= to_cons.size() ) {
            from_cons[i].FSetID( 0 );
            from_cons[i].FSetListID( to_clID );
            idt to_ctID = recContactType::Transfer( from_cons[i].FGetTypeID(), fromdb, todb );
            wxASSERT( to_ctID != 0 );
            from_cons[i].FSetTypeID( to_ctID );
            from_cons[i].Save( todb );
            continue;
        }
        idt to_ctID = recContactType::Transfer( from_cons[i].FGetTypeID(), fromdb, todb );
        wxASSERT( to_ctID != 0 );
        to_cons[i].FSetTypeID( to_ctID );
        to_cons[i].FSetValue( from_cons[i].FGetValue() );
        to_cons[i].Save( todb );
    }
    return to_clID;
}

idt ContactTypeTransfer( idt from_ctID, const wxString& fromdb, const wxString& todb )
{
    if( from_ctID == 0 ) return 0;
    recContactType from_ct( from_ctID, fromdb );
    idt to_ctID = recContactType::FindUid( from_ct.FGetUid(), todb );
    recContactType to_ct( to_ctID, todb );
    if( to_ctID == 0 || from_ct.FGetChanged() > to_ct.FGetChanged() ) {
        from_ct.FSetID( to_ctID );
        from_ct.Save( todb );
        to_ctID = from_ct.FGetID();
    }
    return to_ctID;
}

idt CitationTransfer( idt from_citID, const wxString& fromdb, idt to_refID, const wxString& todb )
{
    if( from_citID == 0 ) return 0;
    recCitation from_cit( from_citID, fromdb );
    idt to_higherID = 0;
    if( from_cit.FGetHigherID() ) {
        recCitation from_higher( from_cit.FGetHigherID(), fromdb );
        to_higherID = recCitation::FindUid( from_higher.FGetUid(), todb );
        wxASSERT( to_higherID != 0 );
        recCitation to_higher( to_higherID, todb );
        to_higherID = CitationTransfer( from_cit.FGetHigherID(), fromdb, to_higher.FGetRefID(), todb );
    }
    idt to_repID = recRepository::Transfer( from_cit.FGetRepID(), fromdb, todb );

    idt to_citID = recCitation::FindUid( from_cit.FGetUid(), todb );
    recCitation to_cit( to_citID, todb );
    if( to_citID == 0 || from_cit.FGetChanged() > to_cit.FGetChanged() ) {
        recCitation new_cit( from_cit );
        new_cit.FSetID( to_citID );
        new_cit.FSetHigherID( to_higherID );
        new_cit.FSetRefID( to_refID );
        new_cit.FSetRepID( to_repID );
        new_cit.Save( todb );
        to_citID = new_cit.FGetID();
    }

    recCitationPartVec from_cps = recCitation::GetPartList( from_citID, fromdb );
    recCitationPartVec to_cps = recCitation::GetPartList( to_citID, fromdb );
    size_t size = std::max( from_cps.size(), to_cps.size() );
    for( size_t i = 0; i < size; i++ ) {
        if( i >= from_cps.size() ) { // No more to copy.
            to_cps[i].RemoveFromDatabase( todb );
            continue;
        }
        if( i >= to_cps.size() ) {
            from_cps[i].FSetID( 0 );
            from_cps[i].FSetCitID( to_citID );
            idt to_cptID = recCitationPartType::Transfer( from_cps[i].FGetTypeID(), fromdb, todb );
            wxASSERT( to_cptID != 0 );
            from_cps[i].FSetTypeID( to_cptID );
            from_cps[i].Save( todb );
            continue;
        }
        idt to_cptID = recCitationPartType::Transfer( from_cps[i].FGetTypeID(), fromdb, todb );
        wxASSERT( to_cptID != 0 );
        to_cps[i].FSetTypeID( to_cptID );
        to_cps[i].FSetValue( from_cps[i].FGetValue() );
        to_cps[i].Save( todb );
    }
    return to_citID;
}

idt CitationPartTypeTransfer( idt from_cptID, const wxString& fromdb, const wxString& todb )
{
    if( from_cptID == 0 ) return 0;
    recCitationPartType from_cpt( from_cptID, fromdb );
    idt to_cptID = recCitationPartType::FindUid( from_cpt.FGetUid(), todb );
    recCitationPartType to_cpt( to_cptID, todb );
    if( to_cptID == 0 || from_cpt.FGetChanged() > to_cpt.FGetChanged() ) {
        from_cpt.FSetID( to_cptID );
        from_cpt.Save( todb );
        to_cptID = from_cpt.FGetID();
    }
    return to_cptID;
}

idt RepositoryTransfer( idt from_repID, const wxString& fromdb, const wxString& todb )
{
    if( from_repID == 0 ) return 0;
    recRepository from_rep( from_repID, fromdb );
    idt to_repID = recRepository::FindUid( from_rep.FGetUid(), todb );
    recRepository to_rep( to_repID, todb );
    if( to_repID == 0 || from_rep.FGetChanged() > to_rep.FGetChanged() ) {
        idt to_clID = recContactList::Transfer( from_rep.FGetConListID(), fromdb, to_rep.FGetConListID(), todb );
        recRepository new_rep( from_rep );
        new_rep.FSetConListID( to_clID );
        new_rep.FSetID( to_repID );
        new_rep.Save( todb );
        to_repID = new_rep.FGetID();
    }

    return to_repID;
}
#endif

// End of src/rg/rgTransfer.cpp file
