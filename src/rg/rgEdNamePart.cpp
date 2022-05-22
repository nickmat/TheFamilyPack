/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdNamePart.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name Part entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#include "rgEdNamePart.h"
#include "rg/rgDialogs.h"

bool rgEditNamePart( wxWindow* wind, idt npID )
{
    wxASSERT( npID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    dlgEditNamePart* dialog = new dlgEditNamePart( wind, npID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateNamePart( wxWindow* wind, idt nameID )
{
    wxASSERT( nameID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recNamePart np(0);
    np.FSetNameID( nameID );
    np.Save();

    idt npID = np.FGetID();
    if( rgEditNamePart( wind, npID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return npID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//-------------------------[ rgDlgEditNamePart ]------------------------------
//============================================================================

bool dlgEditNamePart::TransferDataToWindow()
{
    wxASSERT( m_np.FGetID() != 0 );
    wxASSERT( m_np.FGetNameID() != 0);

    UpdateTypeList( m_np.FGetTypeID() );
    m_textCtrlValue->SetValue( m_np.FGetValue() );

    wxString npIdStr = m_np.GetIdStr();
    wxString nameIdStr = recName::GetIdStr( m_np.FGetNameID() );
    m_staticNamePartID->SetLabel( npIdStr + ":" + nameIdStr );

    return true;
}

bool dlgEditNamePart::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    m_np.FSetTypeID( m_types[type].FGetID() );
    m_np.FSetValue( m_textCtrlValue->GetValue() );
    m_np.Save();
    return true;
}

void dlgEditNamePart::UpdateTypeList( idt nptID )
{
    m_choiceType->Clear();
    m_types = recNamePartType::GetTypeList();
    int i = 0;
    for( auto& style : m_types ) {
        m_choiceType->Append( style.FGetName() );
        if( nptID == style.FGetID() ) {
            m_choiceType->SetSelection( i );
        }
        i++;
    }
}

void dlgEditNamePart::OnAddTypeButton( wxCommandEvent& event )
{
    wxSize s = m_buttonAddType->GetSize();
    m_buttonAddType->PopupMenu( m_menuAddEditType, 0, s.y );
}

void dlgEditNamePart::OnAddType( wxCommandEvent& event )
{
    idt nptID = rgCreateNamePartType( this );
    UpdateTypeList( nptID );
}

void dlgEditNamePart::OnEditType( wxCommandEvent& event )
{
    int type = m_choiceType->GetSelection();
    idt nsID = m_types[type].FGetID();
    rgEditNamePartType( this, nsID );
    UpdateTypeList( nsID );
}

// End of src/rg/rgEdNamePart.cpp file
