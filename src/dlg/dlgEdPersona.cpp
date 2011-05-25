/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Persona entity dialog.
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

#include <wx/tokenzr.h>

#include <rec/recIndividual.h>

#include "dlgEdPersona.h"
#include "dlgEdName.h"
#include "dlgEdAttribute.h"
#include "dlgEd.h"



dlgEditPersona::dlgEditPersona( wxWindow* parent ) : fbDlgEditPersona( parent )
{
    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listName->InsertColumn( 0, itemCol );
    m_listAttr->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Value") );
    m_listName->InsertColumn( 1, itemCol );
    m_listAttr->InsertColumn( 1, itemCol );

    m_persona.Clear();
}

bool dlgEditPersona::TransferDataToWindow()
{
    if( m_persona.f_id == 0 ) {
        m_persona.Save();
    } else {
        m_persona.Read();
    }
    m_nameStr = recName::GetFullName( m_persona.f_name_id );
    m_staticPerName->SetLabel( m_nameStr );

    m_choiceSex->SetSelection( (int) m_persona.f_sex );
    m_textCtrlNote->SetValue(  m_persona.f_note );

    m_indLinks = m_persona.GetIndividualIDs();
    m_staticIndId->SetLabel( GetIndLinksString() );

    m_names = m_persona.ReadNames();
    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        m_listName->InsertItem( i, recNameStyle::GetStyleStr( m_names[i].f_style_id ) );
        m_listName->SetItem( i, COL_Value, m_names[i].GetFullName() );
    }

    m_attributes = m_persona.ReadAttributes();
    for( size_t i = 0 ; i < m_attributes.size() ; i++ ) {
        m_listAttr->InsertItem( i, recAttributeType::GetTypeStr( m_attributes[i].f_type_id ) );
        m_listAttr->SetItem( i, COL_Value, m_attributes[i].f_val );
    }

    return true;
}

bool dlgEditPersona::TransferDataFromWindow()
{
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.f_note = m_textCtrlNote->GetValue();
    m_persona.Save();

    return true;
}

void dlgEditPersona::OnIndLinkButton( wxCommandEvent& event )
{
    idt indID = tfpPickIndividual();
    if( indID == 0 ) return;

    recIndividualPersona ip;
    ip.Clear();
    ip.f_per_id = m_persona.f_id;
    ip.f_ind_id = indID;
    ip.Save();

    wxString ind;
    ind << "I " << indID;
    m_staticIndId->SetLabel( ind );
}

void dlgEditPersona::OnIndCreateButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnIndCreateButton")
    );
    // TODO: Add code
}

void dlgEditPersona::OnNameAddButton( wxCommandEvent& event )
{
    const wxString savepoint = "PerAddName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetPersonaID( m_persona.f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recName* name = dialog->GetName();
        int row = m_names.size();
        m_listName->InsertItem( row, recNameStyle::GetStyleStr( name->f_style_id ) );
        m_listName->SetItem( row, COL_Value, name->GetFullName() );
        m_names.push_back( *name );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditPersona::OnNameEditButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }

    const wxString savepoint = "PerEdName";
    dlgEditName* dialog = new dlgEditName( NULL );
    dialog->SetData( m_names[row].f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recName* name = dialog->GetName();
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( name->f_style_id ) );
        m_listName->SetItem( row, COL_Value, name->GetFullName() );
        m_names[row] = *name;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditPersona::OnNameDeleteButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listName->DeleteItem( row );
        m_names[row].DeleteAll();
        m_names.erase( m_names.begin() + row );
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Name") );
    }
}

void dlgEditPersona::OnNameUpButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row > 0 ) {
        recName attr = m_names[row];
        m_names[row] = m_names[row-1];
        m_names[row-1] = attr;

        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetFullName() );
        --row;
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetFullName() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditPersona::OnNameDownButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row < (long) m_listName->GetItemCount() - 1 ) {
        recName name = m_names[row];
        m_names[row] = m_names[row+1];
        m_names[row+1] = name;

        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetFullName() );
        row++;
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetFullName() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditPersona::OnAttrAddButton( wxCommandEvent& event )
{
    const wxString savepoint = "PerAddAttr";
    dlgEditAttribute* dialog = new dlgEditAttribute( NULL );
    dialog->SetPersonaID( m_persona.f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recAttribute* attr = dialog->GetAttribute();
        int row = m_attributes.size();
        m_listAttr->InsertItem( row, recAttributeType::GetTypeStr( attr->f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, attr->f_val );
        m_attributes.push_back( *attr );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditPersona::OnAttrEditButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Attribute") );
        return;
    }

    const wxString savepoint = "PerEdAttr";
    dlgEditAttribute* dialog = new dlgEditAttribute( NULL );
    dialog->SetAttributeID( m_attributes[row].f_id );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recAttribute* attr = dialog->GetAttribute();
        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( attr->f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, attr->f_val );
        m_attributes[row] = *attr;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditPersona::OnAttrDeleteButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listAttr->DeleteItem( row );
        m_attributes[row].Delete();
        m_attributes.erase( m_attributes.begin() + row );
    } else {
        wxMessageBox( _("No row selected"), _("Delete Attribute") );
    }
}

void dlgEditPersona::OnAttrUpButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Attribute Up") );
        return;
    }
    if( row > 0 ) {
        recAttribute attr = m_attributes[row];
        m_attributes[row] = m_attributes[row-1];
        m_attributes[row-1] = attr;

        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );
        --row;
        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );

        m_listAttr->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void dlgEditPersona::OnAttrDownButton( wxCommandEvent& event )
{
    long row = m_listAttr->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Attribute Down") );
        return;
    }
    if( row < (long) m_listAttr->GetItemCount() - 1 ) {
        recAttribute attr = m_attributes[row];
        m_attributes[row] = m_attributes[row+1];
        m_attributes[row+1] = attr;

        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );
        row++;
        m_listAttr->SetItem( row, COL_Type, recAttributeType::GetTypeStr( m_attributes[row].f_type_id ) );
        m_listAttr->SetItem( row, COL_Value, m_attributes[row].f_val );

        m_listAttr->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

wxString dlgEditPersona::GetIndLinksString() const
{
    wxString txt;

    for( size_t i = 0 ; i < m_indLinks.size() ; i++ ) {
        if( i > 0 ) {
            txt << wxT(", ");
        }
        txt << wxT("I ") << m_indLinks[i];
    }
    return txt;
}

// End of dlgEdPersona.cpp file
