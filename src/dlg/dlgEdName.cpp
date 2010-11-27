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

dlgEditName::dlgEditName( wxWindow* parent ) : fbDlgEditName( parent )
{
    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listName->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Value") );
    m_listName->InsertColumn( 1, itemCol );

    m_name.Clear();
    m_haveName = false;
}

bool dlgEditName::TransferDataToWindow()
{
    if( m_name.f_id == 0 ) {
        m_name.Save();
    } else {
        m_name.Read();
    }


    if( m_haveName == true ) {
        m_staticName->SetLabel( m_nameStr );
//        recName name(0);
//        name.Save();
        recNamePart np;
        int seq = 0;
        wxStringTokenizer tk( m_nameStr );
        while( tk.HasMoreTokens() ) {
            np.Clear();
            np.f_name_id = m_name.f_id;
            np.f_val = tk.GetNextToken();
            np.f_type_id = tk.HasMoreTokens() ?
                NAME_TYPE_Given_name : NAME_TYPE_Surname;
            np.f_sequence = ++seq;
            np.Save();
            m_parts.push_back( np );
        }
    } else {
        m_staticName->SetLabel( m_name.GetFullName() );
    }

    m_styles = recNameStyle::GetStyleList();
    for( size_t i = 0 ; i < m_styles.size() ; i++ ) {
        m_choiceStyle->Append( m_styles[i].f_name );
        if( m_name.f_style_id == m_styles[i].f_id ) {
            m_choiceStyle->SetSelection( (int) i );
        }
    }

    m_parts = m_name.GetParts();
    for( size_t i = 0 ; i < m_parts.size() ; i++ ) {
        m_listName->InsertItem( i, recNamePartType::GetTypeStr( m_parts[i].f_type_id ) );
        m_listName->SetItem( i, COL_Value, m_parts[i].f_val );
    }

    return true;
}

bool dlgEditName::TransferDataFromWindow()
{
    int i = m_choiceStyle->GetSelection();
    m_name.f_style_id = m_styles[i].f_id;
    m_name.Save();
    return true;
}

void dlgEditName::OnNameAddButton( wxCommandEvent& event )
{
    wxMessageBox( wxT("OnNameAddButton Needs rewrite"), wxT("dlgEditName") );
#if 0
    const wxString savepoint = "PerAddName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetPersona( m_persona.f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recName* name = dialog->GetName();
        int row = m_names.size();
        m_listName->InsertItem( row, recNamePartType::GetTypeStr( name->f_type_id ) );
        m_listName->SetItem( row, COL_Value, name->f_val );
        m_names.push_back( *name );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditName::OnNameEditButton( wxCommandEvent& event )
{
    wxMessageBox( wxT("OnNameAddButton Needs rewrite"), wxT("dlgEditName") );
#if 0
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }

    const wxString savepoint = "PerEdName";
    dlgEditName* dialog = new dlgEditName( NULL, m_names[row].f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recName* name = dialog->GetName();
        m_listName->SetItem( row, COL_Type, recNameType::GetTypeStr( name->f_type_id ) );
        m_listName->SetItem( row, COL_Value, name->f_val );
        m_names[row] = *name;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
#endif
}

void dlgEditName::OnNameDeleteButton( wxCommandEvent& event )
{
    wxMessageBox( wxT("OnNameDeleteButton Needs rewrite"), wxT("dlgEditName") );
#if 0
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listName->DeleteItem( row );
        m_names[row].Delete();
        m_names.erase( m_names.begin() + row );
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Name") );
    }
#endif
}

void dlgEditName::OnNameUpButton( wxCommandEvent& event )
{
    wxMessageBox( wxT("OnNameUpButton Needs rewrite"), wxT("dlgEditName") );
#if 0
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( wxT("Row not selected"), wxT("Name Up") );
        return;
    }
    if( row > 0 ) {
        recName attr = m_names[row];
        m_names[row] = m_names[row-1];
        m_names[row-1] = attr;

        m_listName->SetItem( row, COL_Type, recNameType::GetTypeStr( m_names[row].f_type_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].f_val );
        --row;
        m_listName->SetItem( row, COL_Type, recNameType::GetTypeStr( m_names[row].f_type_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].f_val );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
#endif
}

void dlgEditName::OnNameDownButton( wxCommandEvent& event )
{
    wxMessageBox( wxT("OnNameDownButton Needs rewrite"), wxT("dlgEditName") );
#if 0
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( wxT("Row not selected"), wxT("Name Up") );
        return;
    }
    if( row < (long) m_listName->GetItemCount() - 1 ) {
        recName name = m_names[row];
        m_names[row] = m_names[row+1];
        m_names[row+1] = name;

        m_listName->SetItem( row, COL_Type, recNameType::GetTypeStr( m_names[row].f_type_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].f_val );
        row++;
        m_listName->SetItem( row, COL_Type, recNameType::GetTypeStr( m_names[row].f_type_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].f_val );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
#endif
}


// End of dlgEdName.cpp file
