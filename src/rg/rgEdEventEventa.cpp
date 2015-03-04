/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventEventa record dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7th May 2013
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

#include <rec/recEvent.h>
#include <rec/recReference.h>
#include <rec/recIndividual.h>

#include "rg/rgDialogs.h"
#include "rgEdEventEventa.h"

bool rgEditEventEventa( wxWindow* wind, idt eerID )
{
    wxASSERT( eerID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgEditEventEventa* dialog = new rgDlgEditEventEventa( wind, eerID );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateIndEventEventa( wxWindow* wind, idt eID, idt erID )
{
    wxASSERT( eID != 0 && erID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt eerID = recEventEventa::Create( eID, erID );

    if( rgEditEventEventa( wind, eerID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return eerID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

idt rgFindOrCreateIndEvent(
    wxWindow* wind, idt erID, double conf, idt id, idt roleID )
{
    wxASSERT( erID != 0 );
    wxASSERT( id != 0 ); // id is either indID or famID, depending on event type
    idt eID = 0;
    recIdVec eIDs;
    recEventa er(erID);
    recET_GRP grp = er.GetTypeGroup();

    switch( grp )
    {
    case recET_GRP_Birth:
    case recET_GRP_Death:
        eID = recIndividual::FindEvent( id, roleID );
        if( eID == 0 ) {
            eID = recEvent::CreateFromEventa( erID );
        }
        eIDs.push_back( eID );
        break;
    case recET_GRP_NrBirth:
    case recET_GRP_NrDeath:
    case recET_GRP_Other:
        {
            recSelSetEvent sse;
            sse.SetGroupsEnabled(
                recET_GRP_FILTER_NrBirth |
                recET_GRP_FILTER_NrDeath |
                recET_GRP_FILTER_Other
            );
            sse.SetGroupsChecked( recEventTypeGrpToFilter( grp ) );
            sse.AddTypeChecked( er.FGetTypeID() );
            sse.AddIndID( id );

            unsigned button;
            eID = rgSelectEvent( wind, rgSELSTYLE_Create, &sse, &button );
            if( button == rgSELSTYLE_Create ) {
                eID = recEvent::CreateFromEventa( erID );
            }
        }
        break;
    case recET_GRP_FamUnion:
    case recET_GRP_FamOther:
        {
            recSelSetEvent sse;
            sse.SetGroupsEnabled(
                recET_GRP_FILTER_FamUnion |
                recET_GRP_FILTER_FamOther
            );
            sse.SetGroupsChecked( recEventTypeGrpToFilter( grp ) );
            sse.AddTypeChecked( er.FGetTypeID() );
            recIdVec indIDs = recFamily::GetCoupleAsIdVec( id );
            for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
                sse.AddIndID( indIDs[i] );
            }
            unsigned button;
            eID = rgSelectEvent( wind, rgSELSTYLE_Create, &sse, &button );
            if( button == rgSELSTYLE_Create ) {
                eID = recEvent::CreateFromEventa( erID );
                recFamilyEvent::Create( eID, id );
            }
        }
        break;
    default:
        wxASSERT( false ); // Shouldn't be here.
    }

    if( eID ) {
        // Now we have an Event, create the Event Eventa links
        idt eemID = recEventEventa::Create( eID, erID, conf );
        NormaliseEventEventaLinks( eemID );
    }

    return eID;
}

void NormaliseEventEventaLinks( idt eemID )
{
    recEventEventa eem(eemID);
    wxASSERT( eem.FGetID() != 0 );

    recEventaPersonaVec emps = recEventa::GetEventaPersonas( eem.FGetEventaID() );
    recIndEventVec ies = recEvent::GetIndividualEvents( eem.FGetEventID() );
    for( size_t i = 0 ; i < emps.size() ; i++ ) {
        recIdVec indIDs = recPersona::GetIndividualIDs( emps[i].FGetPerID() );
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
                // Create an IndividualEvent to match EventaPersona
                recIndividualEvent ie(0);
                ie.FSetIndID( indIDs[j] );
                ie.FSetEventID( eem.FGetEventID() );
                ie.FSetRoleID( emps[i].FGetRoleID() );
                ie.FSetNote( emps[i].FGetNote() );
                ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indIDs[j] ) + 1 );
                ie.Save();
            }
        }
    }
}

//============================================================================
//--------------------------[ rgDlgEditEventEventa ]--------------------------
//============================================================================

bool rgDlgEditEventEventa::TransferDataToWindow()
{
    wxASSERT( m_eer.FGetID() != 0 );

    idt eID = m_eer.FGetEventID();
    wxString eStr = recEvent::GetIdStr( eID ) + ": " + recEvent::GetTitle( eID );
    m_staticEvent->SetLabel( eStr );

    idt erID = m_eer.FGetEventaID();
    wxString erStr = recEventa::GetIdStr( erID )
        + ": " + recEventa::GetTitle( erID );
    m_staticEventa->SetLabel( erStr );

    idt rID = recEventa::FindReferenceID( erID );
    wxString rStr = recReference::GetIdStr( rID )
        + ": " + recReference::GetTitle( rID );
    m_staticRef->SetLabel( rStr );

    wxString confStr;
    confStr << m_eer.FGetConf();
    m_textCtrlConf->SetValue( confStr );
    m_textCtrlNote->SetValue( m_eer.FGetNote() );

    m_staticEvEvRecID->SetLabel( m_eer.GetIdStr() );
    return true;
}

bool rgDlgEditEventEventa::TransferDataFromWindow()
{
    double conf;
    m_textCtrlConf->GetValue().ToDouble( &conf );
    m_eer.FSetConf( conf );
    m_eer.FSetNote( m_textCtrlNote->GetValue() );

    m_eer.Save();
    return true;
}

// End of src/rg/rgEdEventEventa.cpp file
