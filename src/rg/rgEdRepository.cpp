/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdRepository.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit Repository dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     18th May 2022
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

#include <rec/recCitation.h>

#include <rg/rgDialogs.h>
#include "rgEdRepository.h"

#include <cal/calendar.h>


bool rgEditRepository( wxWindow* wind, idt arcID, const wxString& title )
{
    wxASSERT( arcID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRepository dialog( wind, arcID );
    if( !title.empty() ) {
        dialog.SetTitle( title );
    }

    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    }
    else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

idt rgCreateRepository( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContactList list( 0 );
    list.Save();

    recRepository arc( 0 );
    arc.FSetConListID( list.FGetID() );
    arc.FSetUid( recCreateUid() );
    arc.FSetChanged( calGetTodayJdn() );
    arc.Save();
    idt arcID = arc.FGetID();

    if( rgEditRepository( wind, arcID, _( "Create Archive" ) ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return arcID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

idt rgSelectRepository( wxWindow* wind, unsigned flag, unsigned* retbutton, const wxString& title )
{
    idt arcID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    rgDlgSelectArchive dialog( wind, flag, title );

    bool cont = true;
    while( cont ) {
        recRepositoryVec vec = recRepository::GetFullList();
        wxArrayString table;
        for( auto arc : vec ) {
            table.push_back( arc.GetIdStr() );
            table.push_back( arc.FGetName() );
            table.push_back( arc.FGetNote() );
        }
        dialog.SetTable( table );
        if( vec.size() == 1 ) {
            dialog.SetSelectedRow( 0 );
        }
        if( dialog.ShowModal() == wxID_OK ) {
            if( dialog.GetCreatePressed() ) {
                arcID = rgCreateRepository( wind );
                if( arcID ) {
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
                arcID = 0;
                break;
            }
            size_t item = (size_t) dialog.GetSelectedRow();
            arcID = vec[item].FGetID();
        }
        cont = false;
    }

    return arcID;
}

//============================================================================
//-------------------------[ rgDlgEditRepository ]----------------------------
//============================================================================

rgDlgEditRepository::rgDlgEditRepository( wxWindow* parent, idt arcID )
    : m_archive( arcID ), fbRgEditRepository( parent )
{
    m_list.ReadID( m_archive.FGetConListID() );
    m_contacts = m_list.GetContacts();

    wxListItem itemCol;
    itemCol.SetText( _( "ID" ) );
    m_listContacts->InsertColumn( COL_ConID, itemCol );
    itemCol.SetText( _( "Type" ) );
    m_listContacts->InsertColumn( COL_Type, itemCol );
    itemCol.SetText( _( "Value" ) );
    m_listContacts->InsertColumn( COL_Value, itemCol );
}

bool rgDlgEditRepository::TransferDataToWindow()
{
    wxASSERT( m_archive.FGetID() != 0 );

    m_textCtrlName->SetValue( m_archive.FGetName() );
    m_textCtrlNote->SetValue( m_archive.FGetNote() );
    m_textCtrlUid->SetValue( m_archive.FGetUid() );
    wxString changed = calStrFromJdn( m_archive.FGetChanged(), CALENDAR_SCH_Gregorian );
    m_textCtrlChanged->SetValue( changed );
    m_staticRepID->SetLabel( m_archive.GetIdStr() );
    UpdateContacts( -1 );
    return true;
}

bool rgDlgEditRepository::TransferDataFromWindow()
{
    m_archive.FSetName( m_textCtrlName->GetValue() );
    m_archive.FSetNote( m_textCtrlNote->GetValue() );
    m_archive.FSetChanged( calGetTodayJdn() );

    m_archive.Save();
    return true;
}

void rgDlgEditRepository::UpdateContacts( idt conID )
{
    m_contacts = m_archive.GetContacts();
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

void rgDlgEditRepository::ContactButtonsEnable( int row )
{
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

void rgDlgEditRepository::OnContactDeselected( wxListEvent& event )
{
    ContactButtonsEnable( -1 );
}

void rgDlgEditRepository::OnContactSelected( wxListEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    ContactButtonsEnable( row );
}

void rgDlgEditRepository::OnButtonAdd( wxCommandEvent& event )
{
    idt conID = rgCreateContact( this, m_list.FGetID() );
    if( conID ) {
        recContact con( conID );
        int row = m_contacts.size();
        m_listContacts->InsertItem( row, con.GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, con.GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, con.FGetValue() );
        m_contacts.push_back( con );
    }
}

void rgDlgEditRepository::OnButtonEdit( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Edit Contact" ) );
        return;
    }
    if( rgEditContact( this, m_contacts[row].FGetID() ) ) {
        m_contacts[row].Read();
        m_listContacts->SetItem( row, COL_ConID, m_contacts[row].GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, m_contacts[row].GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, m_contacts[row].FGetValue() );
    }
}

void rgDlgEditRepository::OnButtonDelete( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listContacts->DeleteItem( row );
        m_contacts[row].Delete();
        m_contacts.erase( m_contacts.begin() + row );
    }
    else {
        wxMessageBox( _( "No row selected" ), _( "Delete Contact" ) );
    }
}

void rgDlgEditRepository::OnButtonUp( wxCommandEvent& event )
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

void rgDlgEditRepository::OnButtonDown( wxCommandEvent& event )
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
//--------------------------[ rgDlgSelectArchive ]----------------------------
//============================================================================

wxString rgDlgSelectArchive::sm_colHeaders[COL_MAX] = {
    _( "ID" ), _( "Name" ), _( "Comment" )
};

// End of src/rg/rgEdRepository.cpp file
