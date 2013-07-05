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

bool rgEditPersonaRelationship( wxWindow* wind, idt relID )
{
    wxASSERT( relID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRelationship* dialog = new rgDlgEditRelationship( wind, relID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreatePersonaRelationship( 
    wxWindow* wind, idt refID, const wxString& descrip, idt per1ID, idt per2ID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    if( per1ID == 0 ) {
        per1ID = rgSelectPersona( wind, refID );
    }
    if( per1ID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    if( per2ID == 0 ) {
        per2ID = rgSelectPersona( wind, refID );
    }
    if( per2ID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }

    recRelationship rel(0);
    rel.FSetPer1ID( per1ID );
    rel.FSetPer2ID( per2ID );
    rel.FSetDescrip( descrip );
    rel.Save();
    idt relID = rel.FGetID();

    if( rgEditPersonaRelationship( wind, relID ) ) {
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

rgDlgEditRelationship::rgDlgEditRelationship( wxWindow* parent, idt relID )
    : m_rel(relID), fbRgEditRelationship( parent )
{
    m_refID = recRelationship::FindReferenceID( relID );
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
    idt perID = rgSelectPersona( this, m_refID );
    if( perID ) {
        m_rel.FSetPer1ID( perID );
        m_textCtrlPersona1->SetValue( recPersona::GetNameStr( perID ) );
    }
}

void rgDlgEditRelationship::OnPersona2Button( wxCommandEvent& event )
{
    idt perID = rgSelectPersona( this, m_refID );
    if( perID ) {
        m_rel.FSetPer2ID( perID );
        m_textCtrlPersona2->SetValue( recPersona::GetNameStr( perID ) );
    }
}

// End of dlgEdRelationship.cpp file
