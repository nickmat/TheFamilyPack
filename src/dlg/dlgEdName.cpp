/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name entity dialog.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 November 2010
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

#include <wx/tokenzr.h>

#include "dlgEdName.h"
#include "dlgEdNamePart.h"
#include "dlgEdPersona.h"

dlgEditName::dlgEditName( wxWindow* parent ) : fbDlgEditName( parent )
{
    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listParts->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Value") );
    m_listParts->InsertColumn( 1, itemCol );

    m_name.Clear();
    m_haveName = false;
}

bool dlgEditName::TransferDataToWindow()
{
    if( m_name.f_id == 0 ) {
        m_name.Save();
        if( m_haveName == true ) {
            m_name.AddNameParts( m_nameStr );
        }
    } else {
        m_name.Read();
    }

    wxString nID( "N" );
    nID << m_name.f_id;
    m_staticNameID->SetLabel( nID );

    m_styles = recNameStyle::GetStyleList();
    for( size_t i = 0 ; i < m_styles.size() ; i++ ) {
        m_choiceStyle->Append( m_styles[i].f_name );
        if( m_name.f_style_id == m_styles[i].f_id ) {
            m_choiceStyle->SetSelection( (int) i );
        }
    }
    wxString pID( "Pa" );
    pID << m_name.f_per_id;
    m_buttonPersona->SetLabel( pID );

    m_parts = m_name.GetParts();
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        m_listParts->InsertItem( i, recNamePartType::GetTypeStr( m_parts[i].f_type_id ) );
        m_listParts->SetItem( i, COL_Value, m_parts[i].f_val );
    }
    UpdateName();
    return true;
}

bool dlgEditName::TransferDataFromWindow()
{
    int i = m_choiceStyle->GetSelection();
    m_name.f_style_id = m_styles[i].f_id;
    m_name.Save();
    int seq = 0;
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        m_parts[i].f_sequence = ++seq;
        m_parts[i].Save();
    }
    return true;
}

void dlgEditName::UpdateName()
{
    wxString name;
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        if( i > 0 ) {
            name << " ";
        }
        name << m_parts[i].f_val;
    }
    m_staticName->SetLabel( name );
}

void dlgEditName::OnPersonaButton( wxCommandEvent& event )
{
    const wxString savepoint = "NameEdPer";
    dlgEditPersona* dialog = new dlgEditPersona( NULL );
    dialog->SetPersonaID( m_name.f_per_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditName::OnPartAddButton( wxCommandEvent& event )
{
    const wxString savepoint = "NameAddPart";
    dlgEditNamePart* dialog = new dlgEditNamePart( NULL );
    dialog->SetNameID( m_name.f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recNamePart* np = dialog->GetNamePart();
        int row = m_parts.size();
        m_listParts->InsertItem( row, recNamePartType::GetTypeStr( np->f_type_id ) );
        m_listParts->SetItem( row, COL_Value, np->f_val );
        m_parts.push_back( *np );
        UpdateName();
   } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditName::OnPartEditButton( wxCommandEvent& event )
{
    long row = m_listParts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }

    const wxString savepoint = "NameEdPart";
    dlgEditNamePart* dialog = new dlgEditNamePart( NULL );
    dialog->SetNamePartID( m_parts[row].f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recNamePart* np = dialog->GetNamePart();
        m_listParts->SetItem( row, COL_Type, recNamePartType::GetTypeStr( np->f_type_id ) );
        m_listParts->SetItem( row, COL_Value, np->f_val );
        m_parts[row] = *np;
        UpdateName();
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditName::OnPartDeleteButton( wxCommandEvent& event )
{
    long row = m_listParts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listParts->DeleteItem( row );
        m_parts[row].Delete();
        m_parts.erase( m_parts.begin() + row );
        UpdateName();
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Name") );
    }
}

void dlgEditName::OnPartUpButton( wxCommandEvent& event )
{
    long row = m_listParts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( wxT("Row not selected"), wxT("NamePart Up") );
        return;
    }
    if( row > 0 ) {
        recNamePart part = m_parts[row];
        m_parts[row] = m_parts[row-1];
        m_parts[row-1] = part;

        m_listParts->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].f_type_id ) );
        m_listParts->SetItem( row, COL_Value, m_parts[row].f_val );
        --row;
        m_listParts->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].f_type_id ) );
        m_listParts->SetItem( row, COL_Value, m_parts[row].f_val );

        m_listParts->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
        UpdateName();
    }
}

void dlgEditName::OnPartDownButton( wxCommandEvent& event )
{
    long row = m_listParts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( wxT("Row not selected"), wxT("NamePart Down") );
        return;
    }
    if( row < m_listParts->GetItemCount()-1 ) {
        recNamePart part = m_parts[row];
        m_parts[row] = m_parts[row+1];
        m_parts[row+1] = part;

        m_listParts->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].f_type_id ) );
        m_listParts->SetItem( row, COL_Value, m_parts[row].f_val );
        row++;
        m_listParts->SetItem( row, COL_Type, recNamePartType::GetTypeStr( m_parts[row].f_type_id ) );
        m_listParts->SetItem( row, COL_Value, m_parts[row].f_val );

        m_listParts->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
        UpdateName();
    }
}


// End of dlgEdName.cpp file
