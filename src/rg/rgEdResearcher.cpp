/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Researcher dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th January 2013
 * Copyright:   Copyright (c) 2013 .. 2022, Nick Matthews.
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

#include <cal/calendar.h>

#include <rec/recSystem.h>
#include <rec/recIndividual.h>

#include <rg/rgDialogs.h>
#include "rgEdResearcher.h"

bool rgEditResearcher( wxWindow* wind, idt resID  )
{
    if( !recResearcher::Exists( resID ) ) {
        wxMessageBox( 
            "Researcher " + recResearcher::GetIdStr(resID) + " not found.",
            "Error"
        );
        return false;
    }
    wxASSERT( resID != 0 );


    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    rgDlgEditResearcher dialog( wind, resID );

    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        return true;
    }
    recDb::Rollback( savepoint );
    return false;
}

idt rgCreateResearcher( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContactList list(0);
    list.Save();

    recResearcher res(0);
    res.FSetConListID( list.FGetID() );
    res.FSetUid( recCreateUid() );
    res.Save();
    idt resID = res.FGetID();

    if( rgEditResearcher( wind, resID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return resID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

recCorrectUid rgCorrectInvalidUid( wxWindow* wind )
{
    rgDlgRecoverInvalidUid dialog( wind );
    return static_cast<recCorrectUid>(dialog.ShowModal());
}

idt rgSelectResearcher( wxWindow* wind, unsigned flag, unsigned* retbutton, const wxString& title )
{
    idt resID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    rgDlgSelectResearcher dialog( wind, flag, title );

    bool cont = true;
    while( cont ) {
        recResearcherVec vec = recResearcher::GetResearchers( recDb::Coverage::userfirst );
        wxArrayString table;
        for( auto res : vec ) {
            table.push_back( res.GetIdStr() );
            table.push_back( res.FGetName() );
            table.push_back( res.FGetComment() );
        }
        dialog.SetTable( table );
        if( vec.size() == 1 ) {
            dialog.SetSelectedRow( 0 );
        }
        if( dialog.ShowModal() == wxID_OK ) {
            if( dialog.GetCreatePressed() ) {
                resID = rgCreateResearcher( wind );
                if( resID ) {
                    if( retbutton ) *retbutton = rgSELSTYLE_Create;
                    break;
                }
                else {
                    dialog.SetCreatePressed( false );
                    continue;
                }
            }
            if( dialog.GetUnknownPressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                resID = 0;
                break;
            }
            size_t item = (size_t)dialog.GetSelectedRow();
            resID = vec[item].FGetID();
        }
        cont = false;
    }

    return resID;
}

//============================================================================
//-------------------------[ rgDlgEditResearcher ]----------------------------
//============================================================================

rgDlgEditResearcher::rgDlgEditResearcher( wxWindow* parent, idt resID )
    : m_researcher(resID), fbRgEditResearcher( parent )
{
    m_original_uid = m_researcher.FGetUid();
    m_list.ReadID( m_researcher.FGetConListID() );
    m_contacts = m_researcher.GetContacts();
    m_userID = m_researcher.GetUserID();
    m_currentUserID = recGetCurrentUser();

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
    m_textCtrlComment->SetValue( m_researcher.FGetComment() );
    m_textCtrlUid->SetValue( m_researcher.FGetUid() );

    m_textCtrlUser->SetValue( recUser::GetIdStr( m_userID ) );
    m_checkBoxCurrentUser->SetValue( m_userID == m_currentUserID );
    UpdateIndividual();
    wxString changed = calStrFromJdn( m_researcher.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );
    m_staticResID->SetLabel( m_researcher.GetIdStr() );
    UpdateContacts( -1 );
    return true;
}

bool rgDlgEditResearcher::TransferDataFromWindow()
{
    wxString uid = m_textCtrlUid->GetValue();
    if( recCheckUid( uid ) ) {
        m_researcher.FSetUid( uid );
    }
    else {
        recCorrectUid action = rgCorrectInvalidUid( this );
        switch( action )
        {
        case recCorrectUid::restore:
            m_researcher.FSetUid( m_original_uid );
            break;
        case recCorrectUid::create:
            m_researcher.FSetUid( recCreateUid() );
            break;
        default: // recCorrectUid::cancel
            return false;
        }
    }
    m_researcher.FSetName( m_textCtrlName->GetValue() );
    m_researcher.FSetComment( m_textCtrlComment->GetValue() );
    m_researcher.FSetChanged( calGetTodayJdn() );
    m_researcher.Save();

    bool set_curr = m_checkBoxCurrentUser->GetValue();
    if( set_curr && m_userID != m_currentUserID ) {
        if( m_userID == 0 ) {
            recUser user;
            user.FSetResID( m_researcher.FGetID() );
            user.Save();
            m_userID = user.FGetID();
        }
        recSetCurrentUser( m_userID );
    }
    if( !set_curr ) {
        if( m_currentUserID == 0 || m_userID == m_currentUserID ) {
            m_currentUserID = -1; // Anonymous
        }
        recSetCurrentUser( m_currentUserID );
    }

    return true;
}

void rgDlgEditResearcher::UpdateIndividual()
{
    idt indID = m_list.FGetIndID();
    wxString indName;
    if( indID == 0 ) {
        indName = "< Linked to Individual in Database >";
    }
    else {
        indName << recIndividual::GetIdStr( indID ) <<
            ": " << recIndividual::GetName( indID );
    }
    m_textCtrlIndivitual->SetLabel( indName );
}

void rgDlgEditResearcher::UpdateContacts( idt conID )
{
    m_contacts = m_researcher.GetContacts();
    m_listContacts->DeleteAllItems();
    int row = -1;
    for( size_t i = 0; i < m_contacts.size(); i++ ) {
        m_listContacts->InsertItem( i, m_contacts[i].GetIdStr() );
        m_listContacts->SetItem( i, COL_Type, m_contacts[i].GetTypeStr() );
        m_listContacts->SetItem( i, COL_Value, m_contacts[i].FGetValue() );
        if( conID == m_contacts[i].FGetID() ) {
            m_listContacts->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    m_listContacts->SetColumnWidth( COL_Value, -1 );
    if( row >= 0 ) {
        m_listContacts->EnsureVisible( row );
    }
    ContactButtonsEnable( row );
}

void rgDlgEditResearcher::OnIndButton( wxCommandEvent& event )
{
    // TODO: More work to do about sharing and combining contacts
    // when changing links between Researchers and Individuals.
    int indID = rgSelectIndividual( this );
    if( indID == 0 ) {
        return;
    }
    m_list.FSetIndID( indID );
    m_list.Save();
    UpdateIndividual();
    UpdateContacts( -1 );
}

void rgDlgEditResearcher::ContactButtonsEnable( int row )
{
    // TODO: Add list sequence field to Contact table
    if( row < 0 ) {
        m_buttonEdit->Disable();
        m_buttonDelete->Disable();
        m_buttonUp->Disable();
        m_buttonDown->Disable();
        return;
    }
    m_buttonEdit->Enable();
    m_buttonDelete->Enable();
    if( row == 0 ) {
        m_buttonUp->Disable();
    }
    else {
        m_buttonUp->Enable();
    }
    if( row == m_listContacts->GetItemCount() - 1 ) {
        m_buttonDown->Disable();
    }
    else {
        m_buttonDown->Enable();
    }
}

void rgDlgEditResearcher::OnContactDeselected( wxListEvent& event )
{
    ContactButtonsEnable( -1 );
}

void rgDlgEditResearcher::OnContactSelected( wxListEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    ContactButtonsEnable( row );
}

void rgDlgEditResearcher::OnButtonAdd( wxCommandEvent& event )
{
    idt conID = rgCreateContact( this, m_list.FGetID() );
    if( conID ) {
        UpdateContacts( conID );
    }
}

void rgDlgEditResearcher::OnButtonEdit( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    wxASSERT( row != wxNOT_FOUND ); // Should not have been enabled then!
    idt conID = m_contacts[row].FGetID();
    if( rgEditContact( this, conID ) ) {
        UpdateContacts( conID );
    }
}

void rgDlgEditResearcher::OnButtonDelete( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    wxASSERT( row != wxNOT_FOUND ); // Should not have been enabled then!
    idt conID = m_contacts[row].FGetID();
    wxMessageDialog dlg(
        this,
        m_contacts[row].GetIdStr() + ": " +
        m_contacts[row].GetTypeStr() + ":\n" +
        m_contacts[row].FGetValue() +
        "\n Remove Citation from database?",
        "Confirm Delete", wxOK | wxCANCEL | wxCENTRE
    );
    if( dlg.ShowModal() == wxID_OK ) {
        m_contacts[row].Delete();
        UpdateContacts( -1 );
    }
}

void rgDlgEditResearcher::OnButtonUp( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Edit Entity" ) );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_contacts[row].FGetListSeq();
    m_contacts[row].FSetListSeq( m_contacts[row - 1].FGetListSeq() );
    m_contacts[row].Save();
    m_contacts[row - 1].FSetListSeq( seq );
    m_contacts[row - 1].Save();
    UpdateContacts( m_contacts[row].FGetID() );
}

void rgDlgEditResearcher::OnButtonDown( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Edit Entity" ) );
        return;
    }
    if( row == m_listContacts->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_contacts[row].FGetListSeq();
    m_contacts[row].FSetListSeq( m_contacts[row + 1].FGetListSeq() );
    m_contacts[row].Save();
    m_contacts[row + 1].FSetListSeq( seq );
    m_contacts[row + 1].Save();
    UpdateContacts( m_contacts[row].FGetID() );
}

//============================================================================
//-------------------------[ rgDlgSelectResearcher ]--------------------------
//============================================================================

wxString rgDlgSelectResearcher::sm_colHeaders[COL_MAX] = {
    _( "ID" ), _( "Name" ), _( "Comment" )
};


// End of src/rg/rgEdResearcher.cpp file
