/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual entity dialog.
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

#include <rec/recLink.h>
#include <rg/rgDialogs.h>

#include "rgEdIndividual.h"

bool rgEditIndividual( wxWindow* parent, idt indID  )
{
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgEditIndividual* dialog = new rgDlgEditIndividual( parent, indID );
    recDb::Savepoint( savepoint );

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
//                 rgDlgEditIndividual dialog
//============================================================================

BEGIN_EVENT_TABLE( rgDlgEditIndividual, wxDialog )
    EVT_MENU( ID_EDIND_NEW_EVENT,   rgDlgEditIndividual::OnNewEvent )
    EVT_MENU( ID_EDIND_EXIST_EVENT, rgDlgEditIndividual::OnExistingEvent )
    EVT_MENU( ID_EDIND_UNLINK_EVENT, rgDlgEditIndividual::OnUnlinkEvent )
    EVT_MENU( ID_EDIND_DELETE_EVENT, rgDlgEditIndividual::OnDeleteEvent )
END_EVENT_TABLE()

rgDlgEditIndividual::rgDlgEditIndividual( wxWindow* parent, idt indID )
    : fbRgEditIndividual( parent ), m_individual(indID)
{
    m_persona.ReadID( m_individual.GetPersona() );

    m_listName->InsertColumn( NC_Number, _("Number") );
    m_listName->InsertColumn( NC_Type, _("Type") );
    m_listName->InsertColumn( NC_Name, _("Name") );

    m_listEvent->InsertColumn( EC_Number, _("Number") );
    m_listEvent->InsertColumn( EC_Role, _("Role") );
    m_listEvent->InsertColumn( EC_Title, _("Title") );
    m_listEvent->InsertColumn( EC_Date, _("Date") );
    m_listEvent->InsertColumn( EC_Place, _("Place") );
 
    m_listRel->InsertColumn( RC_Family, _("Family") );         // Number
    m_listRel->InsertColumn( RC_Ind, _("Individual") );        // Number
    m_listRel->InsertColumn( RC_Relation, _("Relationship") ); // Text
}

bool rgDlgEditIndividual::TransferDataToWindow()
{
    if( m_individual.f_id == 0 ) {
        m_individual.Save();
        m_persona.Save();
        m_individual.f_per_id = m_persona.f_id;
    } else {
        m_individual.Read();
        m_persona.f_id = m_individual.f_per_id;
        m_persona.Read();
    }

    m_nameStr = m_persona.GetNameStr();
    m_staticPerName->SetLabel( m_nameStr );
    m_staticIndID->SetLabel( m_individual.GetIdStr() );
//    m_staticPerID->SetLabel( m_persona.GetIdStr() );

    m_staticTextEpitaph->SetLabel( m_individual.f_epitaph );
    m_choiceSex->SetSelection( (int) m_persona.f_sex );
    m_textCtrlNote->SetValue(  m_persona.f_note );

    m_names = m_persona.ReadNames();
    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        m_listName->InsertItem( i, m_names[i].GetIdStr() );
        m_listName->SetItem( i, NC_Type, recNameStyle::GetStyleStr( m_names[i].f_style_id ) );
        m_listName->SetItem( i, NC_Name, m_names[i].GetNameStr() );
    }
    m_listName->SetColumnWidth( NC_Number, 60 );
    if( m_names.size() ) {
        m_listName->SetColumnWidth( NC_Name, wxLIST_AUTOSIZE );
    }
    m_ies = m_individual.GetEvents();
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        m_listEvent->InsertItem( i, recEvent::GetIdStr( m_ies[i].FGetEventID() ) );
        m_listEvent->SetItem( i, EC_Role, recEventTypeRole::GetName( m_ies[i].FGetRoleID() ) );
        m_listEvent->SetItem( i, EC_Title, recEvent::GetTitle( m_ies[i].FGetEventID() ) );
        m_listEvent->SetItem( i, EC_Date, recEvent::GetDateStr( m_ies[i].FGetEventID() ) );
        m_listEvent->SetItem( i, EC_Place, recEvent::GetAddressStr( m_ies[i].FGetEventID() ) );
    }

    m_relationships = m_individual.GetIndRelationships();
    for( size_t i = 0 ; i < m_relationships.size() ; i++ ) {
        m_listRel->InsertItem( i, recFamily::GetIdStr( m_relationships[i].GetFamily() ) );
        m_listRel->SetItem( i, RC_Ind, recIndividual::GetFullName( m_relationships[i].GetIndividual2() ) );
        m_listRel->SetItem( i, RC_Relation, m_relationships[i].GetTypeStr() );
    }

    m_notebook->SetSelection( 0 );
    m_textCtrlNote->SetFocus();
    return true;
}

bool rgDlgEditIndividual::TransferDataFromWindow()
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
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        if( m_ies[i].FGetIndSeq() != i+1 ) {
            m_ies[i].FSetIndSeq( i+1 );
            m_ies[i].Save();
        }
    }
    m_individual.Update();
    m_individual.Save();
    return true;
}

void rgDlgEditIndividual::OnNameAddButton( wxCommandEvent& event )
{
    idt nameID = rgCreateName( m_persona.FGetID() );
    if( nameID ) {
        recName name(nameID);
        int row = m_names.size();
        m_listName->InsertItem( row, name.GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( name.f_style_id ) );
        m_listName->SetItem( row, NC_Name, name.GetNameStr() );
        m_names.push_back( name );
    }
}

void rgDlgEditIndividual::OnNameEditButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    if( rgEditName( nameID ) ) {
        recName name( nameID );
        m_listName->SetItem( row, NC_Number, name.GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( name.FGetTypeID() ) );
        m_listName->SetItem( row, NC_Name, name.GetNameStr() );
        m_names[row] = name;
    }
}

void rgDlgEditIndividual::OnNameDeleteButton( wxCommandEvent& event )
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

void rgDlgEditIndividual::OnNameUpButton( wxCommandEvent& event )
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

        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );
        --row;
        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void rgDlgEditIndividual::OnNameDownButton( wxCommandEvent& event )
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

        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );
        row++;
        m_listName->SetItem( row, NC_Number, m_names[row].GetIdStr() );
        m_listName->SetItem( row, NC_Type, recNameStyle::GetStyleStr( m_names[row].f_style_id ) );
        m_listName->SetItem( row, NC_Name, m_names[row].GetNameStr() );

        m_listName->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void rgDlgEditIndividual::OnEventAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( ID_EDIND_NEW_EVENT, _("&New Event") );
    menu->Append( ID_EDIND_EXIST_EVENT, _("&Existing Event") );
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditIndividual::OnNewEvent( wxCommandEvent& event )
{
    idt eveID = rgCreateIndEvent( m_individual.FGetID() );
    if( eveID ) {
        recIndividualEvent ie;
        ie.Find( m_individual.FGetID(), eveID );
        m_ies.push_back( ie );
        int row = m_listEvent->GetItemCount();
        m_listEvent->InsertItem( row, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( ie.FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );
    }
}

void rgDlgEditIndividual::OnExistingEvent( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt eveID = rgSelectIndEvent( /*rgSELSTYLE_Create, NULL, NULL, m_individual.FGetID()*/ );

    recIndividualEvent ie(0);
    ie.FSetEventID( eveID );
    ie.FSetIndID( m_individual.FGetID() );
    ie.Save();

    if( ! rgEditIndEventRole( ie.FGetID(), rgSHOWROLE_All )  ) {
        recDb::Rollback( savepoint );
        return;
    }

    if( rgEditEvent( eveID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        ie.Read();
        int row = m_ies.size();
        m_listEvent->InsertItem( row, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( ie.FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );
        m_ies.push_back( ie );
    } else {
        recDb::Rollback( savepoint );
    }
}

void rgDlgEditIndividual::OnEventEditButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event") );
        return;
    }
    idt eveID = m_ies[row].FGetEventID();
    if( rgEditEvent( eveID ) ) {
        m_listEvent->SetItem( row, EC_Number, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( m_ies[row].FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );
    }
}

void rgDlgEditIndividual::OnEventDeleteButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_currentRow = row;
        wxMenu* menu = new wxMenu;
        menu->Append( ID_EDIND_UNLINK_EVENT, _("&Unlink Event") );
        menu->Append( ID_EDIND_DELETE_EVENT, _("&Delete Event") );
        PopupMenu( menu );
        delete menu;
    } else {
        wxMessageBox( _("No row selected"), _("Delete Event") );
    }
}

void rgDlgEditIndividual::OnUnlinkEvent( wxCommandEvent& event )
{
    m_listEvent->DeleteItem( m_currentRow );
    recIndividualEvent::Delete( m_ies[m_currentRow].FGetID() );
    m_ies.erase( m_ies.begin() + m_currentRow );
}

void rgDlgEditIndividual::OnDeleteEvent( wxCommandEvent& event )
{
    int ans = wxMessageBox( 
        _("Remove Event completely from database?"), _("Delete Event"),
        wxYES_NO | wxCANCEL, this
    );
    if( ans != wxYES ) {
        return;
    }
    m_listEvent->DeleteItem( m_currentRow );
    recEvent::RemoveIncOrphansFromDatabase( m_ies[m_currentRow].FGetEventID() );
    m_ies.erase( m_ies.begin() + m_currentRow );
}

void rgDlgEditIndividual::OnEventUpButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Event Up") );
        return;
    }
    if( row > 0 ) {
        recIndividualEvent ie = m_ies[row];
        m_ies[row] = m_ies[row-1];
        m_ies[row-1] = ie;

        idt eveID = m_ies[row].FGetEventID();
        m_listEvent->SetItem( row, EC_Number, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( m_ies[row].FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );

        --row;
        eveID = m_ies[row].FGetEventID();
        m_listEvent->SetItem( row, EC_Number, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( m_ies[row].FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );

        m_listEvent->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void rgDlgEditIndividual::OnEventDownButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Event Down") );
        return;
    }
    if( row < (long) m_listEvent->GetItemCount() - 1 ) {
        recIndividualEvent ie = m_ies[row];
        m_ies[row] = m_ies[row+1];
        m_ies[row+1] = ie;

        idt eveID = m_ies[row].FGetEventID();
        m_listEvent->SetItem( row, EC_Number, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( m_ies[row].FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );

        row++;
        eveID = m_ies[row].FGetEventID();
        m_listEvent->SetItem( row, EC_Number, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row, EC_Role, recEventTypeRole::GetName( m_ies[row].FGetRoleID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eveID ) );

        m_listEvent->SetItemState( row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void rgDlgEditIndividual::OnRelAddButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelAddButton") );
}

void rgDlgEditIndividual::OnRelEditButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelEditButton") );
}

void rgDlgEditIndividual::OnRelDeleteButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelDeleteButton") );
}

void rgDlgEditIndividual::OnRelUpButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelUpButton") );
}

void rgDlgEditIndividual::OnRelDownButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnRelDownButton") );
}


// End of src/rg/rgEdIndividual.cpp
