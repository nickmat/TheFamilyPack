/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdContact.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Contact dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     4 April 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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

#include "dlgEdContact.h"

dlgEditContact::dlgEditContact( wxWindow* parent, idt contactID )
    : m_contact(contactID), fbDlgEditContact( parent )
{
}

bool dlgEditContact::TransferDataToWindow()
{
    if( m_contact.f_id == 0 ) {
        m_contact.Save();
    } else {
        m_contact.Read();
    }

    m_staticContactListID->SetLabel( recContactList::GetIdStr( m_contact.FGetListID() ) );
    m_staticContactID->SetLabel( m_contact.GetIdStr() );

    m_types = recContactType::GetList();
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        if( i == 0 ) {
            m_choiceType->Append( "<Select Type>" );
        } else {
            m_choiceType->Append( m_types[i].FGetName() );
        }
        if( m_contact.FGetTypeID() == m_types[i].FGetID() ) {
            m_choiceType->SetSelection( (int) i );
        }
    }

    m_textCtrlValue->SetValue( m_contact.FGetValue() );

    return true;
}

bool dlgEditContact::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type <= 0 ) {
        wxMessageBox( "Please select a Contact Type", "Contact Type Required" );
        return false;
    }
    m_contact.FSetTypeID( m_types[type].FGetID() );
    m_contact.FSetValue( m_textCtrlValue->GetValue() );
    m_contact.Save();
    return true;
}

// End of dlgEditNamePart.cpp file
