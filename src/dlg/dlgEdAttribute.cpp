/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdAttribute.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Attribute entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include "dlgEdAttribute.h"

dlgEditAttribute::dlgEditAttribute( wxWindow* parent, id_t id ) 
    : fbDlgEditAttribute( parent )
{
    m_persona = 0;
    m_attr.f_id = id;
    m_attr.Read();
}

bool dlgEditAttribute::TransferDataToWindow()
{
	if( m_attr.f_id == 0 )
	{
		m_attr.Clear();
        m_attr.f_per_id = m_persona;
		m_attr.Save();
	} else {
		m_attr.Read();
        m_persona = m_attr.f_per_id;
		m_text = m_attr.f_val;
	}
    m_textCtrlValue->SetValue( m_text );

    wxString idStr = wxString::Format( "A "ID":", m_attr.f_id );
    m_staticTextId->SetLabel( idStr );
    wxString perStr = wxString::Format( "P "ID, m_attr.f_per_id );
    m_staticTextPersona->SetLabel( perStr );

    m_typeList = recAttributeType::GetTypeList();
    for( size_t i = 0 ; i < m_typeList.size() ; i++ ) {
        m_choiceType->Append( m_typeList[i].f_name );
        if( m_attr.f_type_id == m_typeList[i].f_id ) {
            m_choiceType->SetSelection( (int) i );
        }
    }
	return true;
}

bool dlgEditAttribute::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type < 0 ) {
        m_attr.f_type_id = 0;
    } else {
        m_attr.f_type_id = m_typeList[type].f_id;
    }
    m_attr.f_val = m_textCtrlValue->GetValue();

	m_attr.Save();
	return true;
}

dlgEditName::dlgEditName( wxWindow* parent, id_t id ) 
    : fbDlgEditName( parent )
{
    m_persona = 0;
    m_name.f_id = id;
    m_name.Read();
}

bool dlgEditName::TransferDataToWindow()
{
	if( m_name.f_id == 0 )
	{
		m_name.Clear();
        m_name.f_per_id = m_persona;
		m_name.Save();
	} else {
		m_name.Read();
        m_persona = m_name.f_per_id;
		m_text = m_name.f_val;
	}
    m_textCtrlValue->SetValue( m_text );

    wxString idStr = wxString::Format( "A "ID":", m_name.f_id );
    m_staticTextId->SetLabel( idStr );
    wxString perStr = wxString::Format( "P "ID, m_name.f_per_id );
    m_staticTextPersona->SetLabel( perStr );

    m_typeList = recNameType::GetTypeList();
    for( size_t i = 0 ; i < m_typeList.size() ; i++ ) {
        m_choiceType->Append( m_typeList[i].f_name );
        if( m_name.f_type_id == m_typeList[i].f_id ) {
            m_choiceType->SetSelection( (int) i );
        }
    }
	return true;
}

bool dlgEditName::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type < 0 ) {
        m_name.f_type_id = 0;
    } else {
        m_name.f_type_id = m_typeList[type].f_id;
    }
    m_name.f_val = m_textCtrlValue->GetValue();

	m_name.Save();
	return true;
}

// End of dlgEdAttribute.cpp file
