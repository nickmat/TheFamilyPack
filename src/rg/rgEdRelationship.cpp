/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdRelationship.cpp
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

#include "rg/rgDialogs.h"
#include "rgEdRelationship.h"
#include "rgEdReference.h"

bool rgEditPerRelationship( rgDlgEditReference* parent, idt relID )
{
    wxASSERT( relID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRelationship* dialog = new rgDlgEditRelationship( parent, relID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreatePerRelationship( rgDlgEditReference* parent, const wxString& descrip )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID1 = parent->SelectCreatePersona();
    if( perID1 == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    idt perID2 = parent->SelectCreatePersona();
    if( perID2 == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    recRelationship rel(0);
    rel.FSetPer1ID( perID1 );
    rel.FSetPer2ID( perID2 );
    rel.FSetDescrip( descrip );
    rel.Save();
    idt relID = rel.FGetID();

    if( rgEditPerRelationship( parent, relID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        relID = 0;
    }
    return relID;
}


//============================================================================
//-------------------------[ rgDlgEditRelationship ]--------------------------
//============================================================================

rgDlgEditRelationship::rgDlgEditRelationship( rgDlgEditReference* parent, idt relID )
    : m_refDialog(parent), m_rel(relID), fbRgEditRelationship( parent )
{
}

bool rgDlgEditRelationship::TransferDataToWindow()
{
    m_textCtrlPersona1->SetValue( recPersona::GetNameStr( m_rel.f_per1_id ) );
    m_textCtrlDescrip->SetValue( m_rel.f_descrip );
    m_textCtrlPersona2->SetValue( recPersona::GetNameStr( m_rel.f_per2_id ) );

    m_staticRsNumber->SetLabel( m_rel.GetIdStr() );

    return true;
}

bool rgDlgEditRelationship::TransferDataFromWindow()
{
    m_rel.f_descrip = m_textCtrlDescrip->GetValue();

    m_rel.Save();
    return true;
}

void rgDlgEditRelationship::OnPersona1Button( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet written"), _("OnPersona1Button") );
}

void rgDlgEditRelationship::OnPersona2Button( wxCommandEvent& event )
{
    wxMessageBox( _("Not yet written"), _("OnPersona2Button") );
}

// End of dlgEdRelationship.cpp file
