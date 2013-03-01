/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPersona.cpp
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
#include <rec/recLink.h>
#include <rg/rgDialogs.h>

#include "rgEdPersona.h"

bool rgEditPersona( wxWindow* parent, idt perID )
{
    wxASSERT( perID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditPersona* dialog = new rgDlgEditPersona( parent, perID );

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
//-------------------------[ rgDlgEditPersona ]-------------------------------
//============================================================================

rgDlgEditPersona::rgDlgEditPersona( wxWindow* parent, idt perID )
    : m_persona(perID), fbRgEditPersona( parent )
{
    wxListItem itemCol;
    itemCol.SetText( wxT("Type") );
    m_listName->InsertColumn( 0, itemCol );
    m_listRel->InsertColumn( 0, itemCol );
    itemCol.SetText( wxT("Value") );
    m_listName->InsertColumn( 1, itemCol );
    m_listRel->InsertColumn( 1, itemCol );

    m_listEvent->InsertColumn( EV_COL_Number, _("Number") );
    m_listEvent->InsertColumn( EV_COL_Role, _("Role") );
    m_listEvent->InsertColumn( EV_COL_Title, _("Title") );
    m_listEvent->InsertColumn( EV_COL_Date, _("Date") );
    m_listEvent->InsertColumn( EV_COL_Place, _("Place") );
}

bool rgDlgEditPersona::TransferDataToWindow()
{
    m_nameStr = m_persona.GetNameStr();
    m_staticPerName->SetLabel( m_nameStr );
    m_staticPerID->SetLabel( m_persona.GetIdStr() );

    m_choiceSex->SetSelection( (int) m_persona.f_sex );
    m_textCtrlNote->SetValue(  m_persona.f_note );

    m_indLinks = m_persona.GetIndividualIDs();
    m_staticIndId->SetLabel( GetIndLinksString() );

    m_names = m_persona.ReadNames();
    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        m_listName->InsertItem( i, recNameStyle::GetStyleStr( m_names[i].f_style_id ) );
        m_listName->SetItem( i, COL_Value, m_names[i].GetNameStr() );
    }
    m_evpers = m_persona.ReadEventPersonas();
    for( size_t i = 0 ; i < m_evpers.size() ; i++ ) {
        m_listEvent->InsertItem( i, recEvent::GetIdStr( m_evpers[i].f_event_id ) );
        m_listEvent->SetItem( i, EV_COL_Role, recEventTypeRole::GetName( m_evpers[i].f_role_id ) );
        m_listEvent->SetItem( i, EV_COL_Title, recEvent::GetTitle( m_evpers[i].f_event_id ) );
        m_listEvent->SetItem( i, EV_COL_Date, recEvent::GetDateStr( m_evpers[i].f_event_id ) );
        m_listEvent->SetItem( i, EV_COL_Place, recEvent::GetAddressStr( m_evpers[i].f_event_id ) );
    }

    m_relationships = m_persona.ReadRelationships();
    for( size_t i = 0 ; i < m_relationships.size() ; i++ ) {
        m_listRel->InsertItem( i, m_relationships[i].GetIdStr() );
        m_listRel->SetItem( i, COL_Value, m_relationships[i].GetRelOfPersonaStr( m_persona.f_id ) );
    }

    return true;
}

bool rgDlgEditPersona::TransferDataFromWindow()
{
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.f_note = m_textCtrlNote->GetValue();
    m_persona.Save();

    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        if( m_names[i].f_sequence != i+1 ) {
            m_names[i].f_sequence = i+1;
            m_names[i].Save();
        }
    }
    return true;
}

void rgDlgEditPersona::OnIndLinkButton( wxCommandEvent& event )
{
    idt indID = rgSelectIndividual();
    if( indID == 0 ) return;

    recLinkPersona lp(0);
    lp.f_ref_per_id = m_persona.f_id;
    lp.f_ind_per_id = recIndividual::GetPersona( indID );
    lp.f_conf = 0.999;
    lp.Save();

    m_staticIndId->SetLabel( recIndividual::GetIdStr( indID ) );
}

void rgDlgEditPersona::OnNameAddButton( wxCommandEvent& event )
{
    idt nameID = rgCreateName( m_persona.FGetID() );
    if( nameID ) {
        recName name(nameID);
        int row = m_names.size();
        m_listName->InsertItem( row, recNameStyle::GetStyleStr( name.FGetTypeID() ) );
        m_listName->SetItem( row, COL_Value, name.GetNameStr() );
        m_names.push_back( name );
    }
}

void rgDlgEditPersona::OnNameEditButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    if( rgEditName( nameID ) ) {
        recName name( nameID );
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( name.FGetTypeID() ) );
        m_listName->SetItem( row, COL_Value, name.GetNameStr() );
        m_names[row] = name;
    }
}

void rgDlgEditPersona::OnNameDeleteButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        int ans = wxMessageBox( 
            _("Remove Name completely from database?"), _("Delete Event"),
            wxYES_NO | wxCANCEL, this
        );
        if( ans != wxYES ) {
            return;
        }
        m_listName->DeleteItem( row );
        m_names[row].RemoveFromDatabase();
        m_names.erase( m_names.begin() + row );
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Name") );
    }
}

void rgDlgEditPersona::OnNameUpButton( wxCommandEvent& event )
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
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );
        --row;
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void rgDlgEditPersona::OnNameDownButton( wxCommandEvent& event )
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
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );
        row++;
        m_listName->SetItem( row, COL_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, COL_Value, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

wxString rgDlgEditPersona::GetIndLinksString() const
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
