/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdArchive.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Archive dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th November 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

//#include <rec/recSystem.h>
//#include <rec/recIndividual.h>

#include <rg/rgDialogs.h>
#include "rgEdArchive.h"
#include "rgCommon.h"

bool rgEditArchive( wxWindow* wind, idt arcID  )
{
    wxASSERT( arcID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditArchive dialog( wind, arcID );

    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    return ret;
}

idt rgCreateArchive( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContactList list(0);
    list.Save();

    recRepository arc(0);
    arc.FSetConListId( list.FGetID() );
    arc.Save();
    idt arcID = arc.FGetID();

    if( rgEditArchive( wind, arcID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return arcID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//-------------------------[ rgDlgEditArchive ]----------------------------
//============================================================================

rgDlgEditArchive::rgDlgEditArchive( wxWindow* parent, idt arcID )
    : m_archive(arcID), fbRgEditArchive( parent )
{
    m_list.ReadID( m_archive.FGetConListId() );
    m_contacts = m_list.GetContacts();

    wxListItem itemCol;
    itemCol.SetText( _("ID") );
    m_listContacts->InsertColumn( COL_ConID, itemCol );
    itemCol.SetText( _("Type") );
    m_listContacts->InsertColumn( COL_Type, itemCol );
    itemCol.SetText( _("Value") );
    m_listContacts->InsertColumn( COL_Value, itemCol );
}

bool rgDlgEditArchive::TransferDataToWindow()
{
    wxASSERT( m_archive.FGetID() != 0 );

    m_textCtrlName->SetValue( m_archive.FGetName() );
    m_textCtrlNote->SetValue( m_archive.FGetNote() );

    for( size_t i = 0 ; i < m_contacts.size() ; i++ ) {
        m_listContacts->InsertItem( i, m_contacts[i].GetIdStr() );
        m_listContacts->SetItem( i, COL_Type, m_contacts[i].GetTypeStr() );
        m_listContacts->SetItem( i, COL_Value, m_contacts[i].FGetValue() );
    }

    m_staticArcID->SetLabel( m_archive.GetIdStr() );

    return true;
}

bool rgDlgEditArchive::TransferDataFromWindow()
{
    m_archive.FSetName( m_textCtrlName->GetValue() );
    m_archive.FSetNote( m_textCtrlNote->GetValue() );

    m_archive.Save();
    return true;
}

void rgDlgEditArchive::OnButtonAdd( wxCommandEvent& event )
{
    idt conID = rgCreateContact( this, m_list.FGetID() );
    if( conID ) {
        recContact con(conID);
        int row = m_contacts.size();
        m_listContacts->InsertItem( row, con.GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, con.GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, con.FGetValue() );
        m_contacts.push_back( con );
    }
}

void rgDlgEditArchive::OnButtonEdit( wxCommandEvent& event )
{
    long row = m_listContacts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Contact") );
        return;
    }
    if( rgEditContact( this, m_contacts[row].FGetID() ) ) {
        m_contacts[row].Read();
        m_listContacts->SetItem( row, COL_ConID, m_contacts[row].GetIdStr() );
        m_listContacts->SetItem( row, COL_Type, m_contacts[row].GetTypeStr() );
        m_listContacts->SetItem( row, COL_Value, m_contacts[row].FGetValue() );
    }
}

void rgDlgEditArchive::OnButtonDelete( wxCommandEvent& event )
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

// End of src/rg/rgEdArchive.cpp file
