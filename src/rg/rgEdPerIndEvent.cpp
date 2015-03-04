/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPerIndEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventaPersona or IndividualEvent record dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     23 November 2012
 * Copyright:   Copyright (c) 2012-2015, Nick Matthews.
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

#include <rec/recIndividual.h>

#include "rgEdPerIndEvent.h"


bool rgEditIndEventRole( wxWindow* wind, idt ieID, rgSHOWROLE filter )
{
    wxASSERT( ieID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgIndEvent* dialog = new rgDlgIndEvent( wind, ieID, filter );

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

bool rgCreateIndEventRole( wxWindow* wind, idt indID, idt eveID, idt roleID )
{
    wxASSERT( eveID != 0 ); // TODO: Select an Event from list
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    if( indID == 0 ) {
        indID = rgSelectIndividual( wind, rgSELSTYLE_None );
        if( indID == 0 ) {
            recDb::Rollback( savepoint );
            return false;
        }
    }
    recIndividualEvent ie(0);
    ie.FSetIndID( indID );
    ie.FSetEventID( eveID );
    ie.FSetRoleID( roleID );
    ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indID ) );
    ie.Save();
    if( roleID == 0 ) {
        if( ! rgEditIndEventRole( wind, ie.FGetID() ) ) {
            recDb::Rollback( savepoint );
            return false;
        }
    }
    recDb::ReleaseSavepoint( savepoint );
    return true;
}

bool rgEditPerEventRole( wxWindow* wind, idt epID, rgSHOWROLE filter )
{
    wxASSERT( epID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgPerEvent* dialog = new rgDlgPerEvent( wind, epID, filter );

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

bool rgCreatePerEventRole( wxWindow* wind, idt perID, idt erID, idt roleID )
{
    wxASSERT( perID != 0 ); // TODO: Select a Persona from a list
    wxASSERT( erID != 0 ); // TODO: Select an Event from a list
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    recEventaPersona ep(0);
    ep.FSetPerID( perID );
    ep.FSetEventaID( erID );
    ep.FSetRoleID( roleID );
    ep.FSetPerSeq( recIndividual::GetMaxEventSeqNumber( perID ) );
    ep.Save();
    if( roleID == 0 ) {
        if( ! rgEditPerEventRole( wind, ep.FGetID() ) ) {
            recDb::Rollback( savepoint );
            return false;
        }
    }
    recDb::ReleaseSavepoint( savepoint );
    return true;
}

//============================================================================
//-------------------------[ rgDlgIndEvent ]----------------------------------
//============================================================================

rgDlgIndEvent::rgDlgIndEvent( wxWindow* parent, idt ieID, rgSHOWROLE filter )
    : m_ie(ieID), m_filter(filter), fbRgPerIndEvent( parent )
{
    m_event.ReadID( m_ie.FGetEventID() );
}

bool rgDlgIndEvent::TransferDataToWindow()
{
    wxASSERT( m_ie.FGetID() != 0 );
    wxASSERT( m_ie.FGetEventID() != 0 );
    wxASSERT( m_ie.FGetIndID() != 0 );

    m_staticName->SetLabel( recIndividual::GetName( m_ie.FGetIndID() ) );
    m_staticNameID->SetLabel( recIndividual::GetIdStr( m_ie.FGetIndID() ) );

    SetRoleList( m_ie.FGetRoleID() );

    m_textCtrlNote->SetValue( m_ie.FGetNote() );
    m_staticRoleID->SetLabel( m_ie.GetIdStr() );
    return true;
}

bool rgDlgIndEvent::TransferDataFromWindow()
{
    m_ie.FSetRoleID( GetRoleID() );
    m_ie.FSetNote( m_textCtrlNote->GetValue() );

    m_ie.Save();
    return true;
}
void rgDlgIndEvent::SetRoleList( idt selection )
{
    m_staticEvent->SetLabel( m_event.FGetTitle() );
    m_staticEventID->SetLabel( m_event.GetIdStr() );

    switch( m_filter )
    {
    case rgSHOWROLE_All:
        m_roles = recEventType::GetRoles( m_event.FGetTypeID() );
        break;
    case rgSHOWROLE_PrimeAll:
        m_roles = recEventType::GetPrimeRoles( m_event.FGetTypeID() );
        break;
    case rgSHOWROLE_PrimeMale:
        m_roles = recEventType::GetPrimeRoles( m_event.FGetTypeID(), -1 );
        break;
    case rgSHOWROLE_PrimeFemale:
        m_roles = recEventType::GetPrimeRoles( m_event.FGetTypeID(), -2 );
        break;
    default:
        wxASSERT( false );
    }

    wxArrayString roleStrs;
    int sel = 0;
    for( size_t i = 0 ; i < m_roles.size() ; i++ ) {
        roleStrs.push_back( m_roles[i].FGetName() );
        if( m_roles[i].FGetID() == selection ) {
            sel = i;
        }
    }
    m_choiceRole->Set( roleStrs );
    m_choiceRole->SetSelection( sel );
}

idt rgDlgIndEvent::GetRoleID() const
{
    int sel = m_choiceRole->GetSelection();
    if( sel >= 0 && sel < (int) m_roles.size() ) {
        return m_roles[sel].FGetID();
    }
    return 0;
}

void rgDlgIndEvent::OnAddRoleButton( wxCommandEvent& event )
{
    idt roleID = rgCreateRole( this, m_event.FGetTypeID() );
    if( roleID ) {
        SetRoleList( roleID );
    }
}

//============================================================================
//-------------------------[ rgDlgPerEvent ]----------------------------------
//============================================================================

rgDlgPerEvent::rgDlgPerEvent( wxWindow* parent, idt epID, rgSHOWROLE filter )
    : m_ep(epID), m_filter(filter), fbRgPerIndEvent( parent )
{
    m_event.ReadID( m_ep.FGetEventaID() );
}

bool rgDlgPerEvent::TransferDataToWindow()
{
    wxASSERT( m_ep.FGetID() != 0 );
    wxASSERT( m_ep.FGetEventaID() != 0 );
    wxASSERT( m_ep.FGetPerID() != 0 );

    m_staticPerInd->SetLabel( "Persona:" );

    m_staticName->SetLabel( recPersona::GetNameStr( m_ep.FGetPerID() ) );
    m_staticNameID->SetLabel( recPersona::GetIdStr( m_ep.FGetPerID() ) );

    SetRoleList( m_ep.FGetRoleID() );

    m_textCtrlNote->SetValue( m_ep.FGetNote() );
    m_staticRoleID->SetLabel( m_ep.GetIdStr() );
    return true;
}

bool rgDlgPerEvent::TransferDataFromWindow()
{
    m_ep.FSetRoleID( GetRoleID() );
    m_ep.FSetNote( m_textCtrlNote->GetValue() );

    m_ep.Save();
    return true;
}
void rgDlgPerEvent::SetRoleList( idt selection )
{
    m_staticEvent->SetLabel( m_event.FGetTitle() );
    m_staticEventID->SetLabel( m_event.GetIdStr() );

    switch( m_filter )
    {
    case rgSHOWROLE_All:
        m_roles = recEventType::GetRoles( m_event.FGetTypeID() );
        break;
    case rgSHOWROLE_PrimeAll:
        m_roles = recEventType::GetPrimeRoles( m_event.FGetTypeID() );
        break;
    case rgSHOWROLE_PrimeMale:
        m_roles = recEventType::GetPrimeRoles( m_event.FGetTypeID(), -1 );
        break;
    case rgSHOWROLE_PrimeFemale:
        m_roles = recEventType::GetPrimeRoles( m_event.FGetTypeID(), -2 );
        break;
    default:
        wxASSERT( false );
    }

    wxArrayString roleStrs;
    int sel = 0;
    for( size_t i = 0 ; i < m_roles.size() ; i++ ) {
        roleStrs.push_back( m_roles[i].FGetName() );
        if( m_roles[i].FGetID() == selection ) {
            sel = i;
        }
    }
    m_choiceRole->Set( roleStrs );
    m_choiceRole->SetSelection( sel );
}

idt rgDlgPerEvent::GetRoleID() const
{
    int sel = m_choiceRole->GetSelection();
    if( sel >= 0 && sel < (int) m_roles.size() ) {
        return m_roles[sel].FGetID();
    }
    return 0;
}

void rgDlgPerEvent::OnAddRoleButton( wxCommandEvent& event )
{
    idt roleID = rgCreateRole( this, m_event.FGetTypeID() );
    if( roleID ) {
        SetRoleList( roleID );
    }
}

// End of src/rg/rgEdPerIndEvent.cpp file
