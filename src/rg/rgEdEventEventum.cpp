/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventEventum.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventEventum record dialog header.
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
#include "rgEdEventEventum.h"

bool rgEditEventEventum( wxWindow* wind, idt eerID )
{
    wxASSERT( eerID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgEditEventEventum* dialog = new rgDlgEditEventEventum( wind, eerID );

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

idt rgCreateIndEventEventum( wxWindow* wind, idt eID, idt erID )
{
    wxASSERT( eID != 0 && erID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt eerID = recEventEventum::Create( eID, erID );

    if( rgEditEventEventum( wind, eerID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return eerID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

idt rgFindOrCreateIndEvent(
    wxWindow* wind, idt erID, double conf, idt indID, idt roleID )
{
    wxASSERT( erID != 0 );
    wxASSERT( indID != 0 );
    idt eID = 0;
    recIdVec eIDs;
    recEventum er(erID);
    recET_GRP grp = er.GetTypeGroup();

    switch( grp )
    {
    case recET_GRP_Birth:
    case recET_GRP_Death:
        eID = recIndividual::FindEvent( indID, grp );
        if( eID == 0 ) {
            eID = recEvent::CreateFromEventum( erID );
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
            sse.AddIndID( indID );

            eID = rgSelectEvent( wind, rgSELSTYLE_None, &sse );
        }
        break;
#if 0
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
            eID = rgSelectEvent( wind, rgSELSTYLE_None, &sse );
        }
        break;
#endif
    }

    if( eID ) {
        // Now we have an Event, create the Event Eventum links
        recEventEventum::Create( eID, erID, conf );
        recIndividualEvent::Create( indID, eID, roleID );
    }

    return eID;
}

//============================================================================
//-------------------------[ rgDlgEditEventEventum ]--------------------------
//============================================================================

bool rgDlgEditEventEventum::TransferDataToWindow()
{
    wxASSERT( m_eer.FGetID() != 0 );

    idt eID = m_eer.FGetEventID();
    wxString eStr = recEvent::GetIdStr( eID ) + ": " + recEvent::GetTitle( eID );
    m_staticEvent->SetLabel( eStr );

    idt erID = m_eer.FGetEventumID();
    wxString erStr = recEventum::GetIdStr( erID )
        + ": " + recEventum::GetTitle( erID );
    m_staticEventum->SetLabel( erStr );

    idt rID = recEventum::FindReferenceID( erID );
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

bool rgDlgEditEventEventum::TransferDataFromWindow()
{
    double conf;
    m_textCtrlConf->GetValue().ToDouble( &conf );
    m_eer.FSetConf( conf );
    m_eer.FSetNote( m_textCtrlNote->GetValue() );

    m_eer.Save();
    return true;
}

// End of src/rg/rgEdEventEventum.cpp file
