/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Researcher dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th January 2013
 * RCS-ID:      $Id$
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

#include <rec/recSystem.h>
#include <rec/recIndividual.h>

#include <rg/rgDialogs.h>
#include "rgEdResearcher.h"
#include "rgCommon.h"

bool rgEditResearcher( idt resID  )
{
    wxASSERT( resID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditResearcher* dialog = new rgDlgEditResearcher( NULL, resID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateResearcher()
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContactList list(0);
    list.Save();

    recResearcher res(0);
    res.FSetConListID( list.FGetID() );
    res.Save();
    idt resID = res.FGetID();

    if( rgEditResearcher( resID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return resID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//-------------------------[ rgDlgEditResearcher ]----------------------------
//============================================================================

rgDlgEditResearcher::rgDlgEditResearcher( wxWindow* parent, idt resID )
    : m_researcher(resID), fbRgEditResearcher( parent )
{
    m_user.ReadID( m_user.FindFirst( m_researcher.FGetID() ) );
    m_list.ReadID( m_researcher.FGetConListID() );
    m_contacts = m_researcher.GetContacts();

    wxListItem itemCol;
    itemCol.SetText( _("ID") );
    m_listContacts->InsertColumn( COL_ConID, itemCol );
    itemCol.SetText( _("Type") );
    m_listContacts->InsertColumn( COL_Type, itemCol );
    itemCol.SetText( _("Value") );
    m_listContacts->InsertColumn( COL_Value, itemCol );
}

bool rgDlgEditResearcher::TransferDataToWindow()
{
    wxASSERT( m_researcher.FGetID() != 0 );

    m_textCtrlName->SetValue( m_researcher.FGetName() );
    m_textCtrlComment->SetValue( m_researcher.FGetComments() );
    idt indID = m_list.FGetIndID();
    m_staticIndName->SetLabel( recIndividual::GetFullName( indID ) );
    m_staticIndID->SetLabel( recIndividual::GetIdStr( indID ) );

    for( size_t i = 0 ; i < m_contacts.size() ; i++ ) {
        m_listContacts->InsertItem( i, m_contacts[i].GetIdStr() );
        m_listContacts->SetItem( i, COL_Type, m_contacts[i].GetTypeStr() );
        m_listContacts->SetItem( i, COL_Value, m_contacts[i].FGetValue() );
    }

    m_staticResID->SetLabel( m_researcher.GetIdStr() );

    if( m_user.FGetResID() ) {
        m_staticUserID->SetLabel( m_user.GetIdStr() );
        m_checkBoxUser->SetValue( true );
    } else {
        m_staticUserID->SetLabel( wxEmptyString );
        m_checkBoxUser->SetValue( false );
    }

    return true;
}

bool rgDlgEditResearcher::TransferDataFromWindow()
{
    m_researcher.FSetName( m_textCtrlName->GetValue() );
    m_researcher.FSetComments( m_textCtrlComment->GetValue() );

    if( m_checkBoxUser->GetValue() == true ) {
        if( m_user.FGetID() == 0 ) {
            // Create a new user.
            m_user.FSetResID( m_researcher.FGetID() );
            m_user.Save();
        }
    } else {
        if( m_user.FGetID() != 0 ) {
            // Remove user if not current.
            if( m_user.FGetID() != recGetCurrentUser() ) {
                // TODO: Remove user's settings.
                m_user.Delete();
            }
        }
    }

    m_researcher.Save();
    return true;
}

void rgDlgEditResearcher::AddIndLink()
{
    idt indID = rgSelectIndividual();
    if( indID == 0 ) {
        return;
    }
    m_list.FSetIndID( 0 );
    // Look for an existing list for the new Individual
    idt newCLID = recContactList::FindIndID( indID );
    if( newCLID ) {
        // Add Contacts 
        m_list.Assimilate( newCLID );
    }
    m_list.FSetIndID( indID );
    m_list.Save();
    m_staticIndName->SetLabel( recIndividual::GetFullName( indID ) );
    m_staticIndID->SetLabel( recIndividual::GetIdStr( indID ) );
}

void rgDlgEditResearcher::OnOptnChange( wxCommandEvent& event )
{
    AddIndLink();
}

void rgDlgEditResearcher::OnOptnUnlink( wxCommandEvent& event )
{
    // TODO: Currently the Researcher retains the contact list
    // and the Individual will no longer have a contact list.
    // We should give the option for the list to be retained by the
    // Researcher or by the Individual, or duplicated and held by both.
    // If duplicated we should advise that both lists should be checked
    // and inapproriate contacts deleted.
    m_list.FSetIndID( 0 );
    m_staticIndName->SetLabel( "" );
    m_staticIndID->SetLabel( "" );
}

void rgDlgEditResearcher::OnButtonInd( wxCommandEvent& event )
{
    if( m_list.FGetIndID() == 0 ) {
        AddIndLink();
        return;
    }
    wxMenu* menu = new wxMenu;
    wxMenuItem* optnChange = menu->Append( wxID_ANY, _("&Change") );
    wxMenuItem* optnUnlink = menu->Append( wxID_ANY, _("&Unlink") );
    rgCONNECT_MI( optnChange, rgDlgEditResearcher::OnOptnChange );
    rgCONNECT_MI( optnUnlink, rgDlgEditResearcher::OnOptnUnlink );
    PopupMenu( menu );
    rgDISCONNECT_MI( optnChange, rgDlgEditResearcher::OnOptnChange );
    rgDISCONNECT_MI( optnUnlink, rgDlgEditResearcher::OnOptnUnlink );
    delete menu;
}

void rgDlgEditResearcher::OnButtonAdd( wxCommandEvent& event )
{
    idt conID = rgCreateContact( m_list.FGetID() );
    if( conID ) {
        recContact con(conID);
        int row = m_contacts.size();
        m_listContacts->InsertItem( row, con.GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, con.GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, con.FGetValue() );
        m_contacts.push_back( con );
    }
}

void rgDlgEditResearcher::OnButtonEdit( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Contact") );
        return;
    }
    if( rgEditContact( m_contacts[row].FGetID() ) ) {
        m_contacts[row].Read();
        m_listContacts->SetItem( row, COL_ConID, m_contacts[row].GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, m_contacts[row].GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, m_contacts[row].FGetValue() );
    }
}

void rgDlgEditResearcher::OnButtonDelete( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listContacts->DeleteItem( row );
        m_contacts[row].Delete();
        m_contacts.erase( m_contacts.begin() + row );
    } else {
        wxMessageBox( _("No row selected"), _("Delete Contact") );
    }
}

// End of src/rg/rgEdResearcher.cpp file
