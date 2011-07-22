/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdRelationship.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Relationship entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     13 July 2011
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

#include <rec/recPersona.h>

#include "dlgEdRelationship.h"


dlgEditRelationship::dlgEditRelationship( wxWindow* parent, idt relID )
    : fbDlgEditRelationship( parent )
{
    m_rel.Clear();
    m_rel.f_id = relID;
}

bool dlgEditRelationship::TransferDataToWindow()
{
    if( m_rel.f_id == 0 ) {
        m_rel.Save();
    } else {
        m_rel.Read();
    }

    wxString idStr = wxString::Format( "Rs"ID, m_rel.f_id );
    m_staticRsNumber->SetLabel( idStr );

    m_textCtrlPersona1->SetValue( recPersona::GetNameStr( m_rel.f_per1_id ) );
    m_textCtrlDescrip->SetValue( m_rel.f_descrip );
    m_textCtrlPersona2->SetValue( recPersona::GetNameStr( m_rel.f_per2_id ) );

    return true;
}

bool dlgEditRelationship::TransferDataFromWindow()
{
    m_rel.f_descrip = m_textCtrlDescrip->GetValue();

    m_rel.Save();
    return true;
}

void dlgEditRelationship::OnPersona1Button( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet written"), _("OnPersona1Button") );
}

void dlgEditRelationship::OnPersona2Button( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet written"), _("OnPersona2Button") );
}

// End of dlgEdRelationship.cpp file
