/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdContact.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Contact dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th January 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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

#include "rgEdContact.h"
#include "rg/rgDialogs.h"

#include <cal/calendar.h>


bool rgEditContact( wxWindow* wind, idt conID )
{
    wxASSERT( conID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditContact* dialog = new rgDlgEditContact( wind, conID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateContact( wxWindow* wind, idt clID )
{
    wxASSERT( clID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContact con(0);
    con.FSetListID( clID );
    con.Save();

    idt conID = con.FGetID();
    if( rgEditContact( wind, conID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return conID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

static bool rgEditContactType( wxWindow* wind, idt ctID )
{
    wxASSERT( ctID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    rgDlgEditContactType dialog( wind, ctID );

    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        return true;
    }
    recDb::Rollback( savepoint );
    return false;
}

static idt rgCreateContactType( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recContactType ct( 0 );
    ct.FSetUid( recCreateUid() );
    ct.FSetChanged( calGetTodayJdn() );
    ct.Save();

    idt ctID = ct.FGetID();
    if( rgEditContactType( wind, ctID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return ctID;
    }
    recDb::Rollback( savepoint );
    return 0;
}


//============================================================================
//-------------------------[ rgEditContact ]----------------------------------
//============================================================================

bool rgDlgEditContact::TransferDataToWindow()
{
    wxASSERT( m_contact.FGetID() != 0 );
    wxASSERT( m_contact.FGetListID() != 0 );


    m_textCtrlValue->SetValue( m_contact.FGetValue() );

    m_staticContactID->SetLabel( m_contact.GetIdStr() );

    UpdateTypeList( m_contact.FGetTypeID() );
    return true;
}

bool rgDlgEditContact::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type <= 0 ) {
        wxMessageBox( _("Please select a Contact Type"), _("Contact Type Required") );
        return false;
    }
    m_contact.FSetTypeID( m_types[type-1].FGetID() );
    m_contact.FSetValue( m_textCtrlValue->GetValue() );
    m_contact.Save();
    return true;
}

void rgDlgEditContact::UpdateTypeList( idt ctID )
{
    m_types = recContactType::GetList();
    m_choiceType->Clear();
    m_choiceType->Append( _( "<Select Type>" ) );
    m_choiceType->SetSelection( 0 );
    for( size_t i = 0; i < m_types.size(); i++ ) {
        m_choiceType->Append( m_types[i].FGetName() );
        if( ctID == m_types[i].FGetID() ) {
            m_choiceType->SetSelection( int( i + 1 ) );
        }
    }
}

void rgDlgEditContact::OnAddEditButton( wxCommandEvent& event )
{
    wxSize s = m_buttonAddType->GetSize();
    m_buttonAddType->PopupMenu( m_menuAddEditType, 0, s.y );
}

void rgDlgEditContact::OnAddType( wxCommandEvent& event )
{
    idt ctID = rgCreateContactType( this );
    UpdateTypeList( ctID );
}

void rgDlgEditContact::OnEditType( wxCommandEvent& event )
{
    int type = m_choiceType->GetSelection();
    idt ctID = m_types[type - 1].FGetID();
    rgEditContactType( this, ctID );
    UpdateTypeList( ctID );
}


//============================================================================
//-----------------------[ rgEditContactType ]--------------------------------
//============================================================================

bool rgDlgEditContactType::TransferDataToWindow()
{
    m_textCtrlName->SetValue( m_contacttype.FGetName() );
    m_textCtrlUid->SetValue( m_contacttype.FGetUid() );
    wxString changed = calStrFromJdn( m_contacttype.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );

    m_staticContactTypeID->SetLabel( m_contacttype.GetIdStr() );
    return true;
}

bool rgDlgEditContactType::TransferDataFromWindow()
{
    m_contacttype.FSetName( m_textCtrlName->GetValue() );
    m_contacttype.Save();
    return true;
}

// End of src/rg/rgEdContact.cpp file
