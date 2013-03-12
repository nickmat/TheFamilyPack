/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdContact.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Contact dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th January 2013
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

#include "rgEdContact.h"
#include "rg/rgDialogs.h"

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

//============================================================================
//-------------------------[ rgEditContact ]----------------------------------
//============================================================================

bool rgDlgEditContact::TransferDataToWindow()
{
    wxASSERT( m_contact.FGetID() != 0 );
    wxASSERT( m_contact.FGetListID() != 0 );

    m_types = recContactType::GetList();
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        if( i == 0 ) {
            m_choiceType->Append( _("<Select Type>") );
        } else {
            m_choiceType->Append( m_types[i].FGetName() );
        }
        if( m_contact.FGetTypeID() == m_types[i].FGetID() ) {
            m_choiceType->SetSelection( (int) i );
        }
    }

    m_textCtrlValue->SetValue( m_contact.FGetValue() );

//    m_staticContactListID->SetLabel( recContactList::GetIdStr( m_contact.FGetListID() ) );
    m_staticContactID->SetLabel( m_contact.GetIdStr() );

    return true;
}

bool rgDlgEditContact::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type <= 0 ) {
        wxMessageBox( _("Please select a Contact Type"), _("Contact Type Required") );
        return false;
    }
    m_contact.FSetTypeID( m_types[type].FGetID() );
    m_contact.FSetValue( m_textCtrlValue->GetValue() );
    m_contact.Save();
    return true;
}

// End of src/rg/rgEdContact.cpp file
