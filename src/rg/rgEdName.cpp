/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
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

//#include <wx/tokenzr.h>

#include "rgEdName.h"
#include "rg/rgDialogs.h"


bool rgEditName( idt nameID )
{
    wxASSERT( nameID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditName* dialog = new rgDlgEditName( NULL, nameID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

//============================================================================
//-------------------------[ rgDlgEditName ]----------------------------------
//============================================================================

rgDlgEditName::rgDlgEditName( wxWindow* parent, idt nameID ) 
    : m_name(nameID), fbRgEditName( parent )
{
    wxSize sz = m_listNamePart->GetClientSize();
    //                             ID   Type  scrollbar
    int valwidth = sz.GetWidth() - 70 - 100 - 20;
    if( valwidth < 100 ) valwidth = 100;

    m_listNamePart->InsertColumn( COL_ID, _("ID"), wxLIST_FORMAT_LEFT, 70 );
    m_listNamePart->InsertColumn( COL_Type, _("Type"), wxLIST_FORMAT_LEFT, 100 );
    m_listNamePart->InsertColumn( COL_Value, _("Value"), wxLIST_FORMAT_LEFT, valwidth );
}

bool rgDlgEditName::TransferDataToWindow()
{
    wxASSERT( m_name.FGetID() != 0 );

    m_types = recNameStyle::GetStyleList();
    for( size_t i = 0 ; i < m_types.size() ; i++ ) {
        m_choiceType->Append( m_types[i].FGetName() );
        if( m_name.FGetTypeID() == m_types[i].FGetID() ) {
            m_choiceType->SetSelection( (int) i );
        }
    }

    m_parts = m_name.GetParts();
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        m_listNamePart->InsertItem( i, recNamePart::GetIdStr( m_parts[i].FGetID() ) );
        m_listNamePart->SetItem( i, COL_Type, recNamePartType::GetTypeStr( m_parts[i].FGetTypeID() ) );
        m_listNamePart->SetItem( i, COL_Value, m_parts[i].FGetValue() );
    }

    m_staticNameID->SetLabel( m_name.GetIdStr() );
    UpdateName();
    return true;
}

bool rgDlgEditName::TransferDataFromWindow()
{
    int i = m_choiceType->GetSelection();
    m_name.FSetTypeID( m_types[i].FGetID() );
    m_name.Save();
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        m_parts[i].FSetNameSeq( i+1 );
        m_parts[i].Save();
    }
    return true;
}

void rgDlgEditName::UpdateName()
{
    wxString name;
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        if( i > 0 ) {
            name << " ";
        }
        name << m_parts[i].FGetValue();
    }
    m_staticName->SetLabel( name );
}

void rgDlgEditName::OnPartAddButton( wxCommandEvent& event )
{
    idt npID = rgCreateNamePart( m_name.FGetID() );
    if( npID ) {
        recNamePart np(npID);
        int row = m_parts.size();
        m_listNamePart->InsertItem( row, np.GetIdStr() );
        m_listNamePart->SetItem( row, COL_Type, recNamePartType::GetTypeStr( np.FGetTypeID() ) );
        m_listNamePart->SetItem( row, COL_Value, np.FGetValue() );
        m_parts.push_back( np );
        UpdateName();
    }
}

void rgDlgEditName::OnPartEditButton( wxCommandEvent& event )
{
    long row = m_listNamePart->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name Part") );
        return;
    }
    idt npID = m_parts[row].FGetID();
    if( rgEditNamePart( npID ) ) {
        recNamePart np(npID);
        m_listNamePart->SetItem( row, COL_ID, np.GetIdStr() );
        m_listNamePart->SetItem( row, COL_Type, recNamePartType::GetTypeStr( np.FGetTypeID() ) );
        m_listNamePart->SetItem( row, COL_Value, np.FGetValue() );
        m_parts[row] = np;
        UpdateName();
    }
}

void rgDlgEditName::OnPartDeleteButton( wxCommandEvent& event )
{
    long row = m_listNamePart->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Name Part") );
        return;
    }
    idt npID = m_parts[row].FGetID();
    m_listNamePart->DeleteItem( row );
    m_parts[row].Delete();
    m_parts.erase( m_parts.begin() + row );
    UpdateName();
}

void rgDlgEditName::OnPartUpButton( wxCommandEvent& event )
{
    long row = m_listNamePart->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Part Up") );
        return;
    }
    if( row > 0 ) {
        recNamePart np = m_parts[row];
        m_parts[row] = m_parts[row-1];
        m_parts[row-1] = np;

        m_listNamePart->SetItem( row, COL_ID, m_parts[row].GetIdStr() );
        m_listNamePart->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].FGetTypeID() ) );
        m_listNamePart->SetItem( row, COL_Value, m_parts[row].FGetValue() );
        --row;
        m_listNamePart->SetItem( row, COL_ID, m_parts[row].GetIdStr() );
        m_listNamePart->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].FGetTypeID() ) );
        m_listNamePart->SetItem( row, COL_Value, m_parts[row].FGetValue() );

        m_listNamePart->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
        UpdateName();
    }
}

void rgDlgEditName::OnPartDownButton( wxCommandEvent& event )
{
    long row = m_listNamePart->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Part Down") );
        return;
    }
    if( row < m_listNamePart->GetItemCount()-1 ) {
        recNamePart np = m_parts[row];
        m_parts[row] = m_parts[row+1];
        m_parts[row+1] = np;

        m_listNamePart->SetItem( row, COL_ID, m_parts[row].GetIdStr() );
        m_listNamePart->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].FGetTypeID() ) );
        m_listNamePart->SetItem( row, COL_Value, m_parts[row].FGetValue() );
        row++;
        m_listNamePart->SetItem( row, COL_ID, m_parts[row].GetIdStr() );
        m_listNamePart->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].FGetTypeID() ) );
        m_listNamePart->SetItem( row, COL_Value, m_parts[row].FGetValue() );

        m_listNamePart->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
        UpdateName();
    }
}

// End of src/rg/rgEdName.cpp file
