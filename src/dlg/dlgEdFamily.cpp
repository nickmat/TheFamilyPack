/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdFamily.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Family entity dialog.
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

#include <rec/recIndividual.h>
#include <rec/recEvent.h>

#include "dlgEdFamily.h"
#include "dlgEdIndEvent.h"
#include "dlgEd.h"

IMPLEMENT_CLASS( dlgEditFamily, wxDialog )

BEGIN_EVENT_TABLE( dlgEditFamily, wxDialog )
    EVT_MENU( tfpID_DLGEDFAM_EDIT, dlgEditFamily::OnEditID )
    EVT_MENU( tfpID_DLGEDFAM_REMOVE, dlgEditFamily::OnRemoveID )
    EVT_MENU( tfpID_DLGEDFAM_DELETE, dlgEditFamily::OnDeleteID )
    EVT_MENU( tfpID_DLGEDFAM_ADDNEW, dlgEditFamily::OnEditID )
    EVT_MENU( tfpID_DLGEDFAM_ADDEXIST, dlgEditFamily::OnAddExistID )

    EVT_MENU( tfpID_DLGEDFAM_ADDNEWSON, dlgEditFamily::OnAddChild )
    EVT_MENU( tfpID_DLGEDFAM_ADDNEWDAUR, dlgEditFamily::OnAddChild )
    EVT_MENU( tfpID_DLGEDFAM_ADDEXISTSON, dlgEditFamily::OnAddChild )
    EVT_MENU( tfpID_DLGEDFAM_ADDEXISTDAUR, dlgEditFamily::OnAddChild )

    EVT_MENU( tfpID_DLGEDFAM_NEW_EVENT,   dlgEditFamily::OnNewEvent )
    EVT_MENU( tfpID_DLGEDFAM_EXIST_EVENT, dlgEditFamily::OnExistingEvent )
END_EVENT_TABLE()

dlgEditFamily::dlgEditFamily( wxWindow* parent ) : fbDlgEditFamily( parent )
{
    m_child = 0;
    m_family.Clear();

    m_listEvent->InsertColumn( EC_Number, _("Number") );
    m_listEvent->InsertColumn( EC_Title, _("Title") );
    m_listEvent->InsertColumn( EC_Date, _("Date") );
    m_listEvent->InsertColumn( EC_Place, _("Place") );
}

bool dlgEditFamily::TransferDataToWindow()
{
    wxASSERT( m_family.f_id != 0 );
    m_family.Read();
    if( m_child > 0 ) {
        recFamilyIndividual fi;
        fi.Clear();
        fi.f_fam_id = m_family.f_id;
        fi.f_ind_id = m_child;
        fi.f_seq_child = 1;
        fi.f_seq_parent = 1;
        fi.Save();
    }

    wxString str;

    str << wxT("F") << m_family.f_id;
    m_staticFamID->SetLabel( str  );

    str = recIndividual::GetFullName( m_family.f_husb_id );
    m_staticHusbName->SetLabel( str  );

    str = recIndividual::GetFullName( m_family.f_wife_id );
    m_staticWifeName->SetLabel( str  );

    m_childlinks = m_family.GetChildLinks();
    wxArrayString list;
    if( m_childlinks.size() > 0 )
    {
        for( size_t i = 0 ; i < m_childlinks.size() ; i++ )
        {
            list.Add( recIndividual::GetFullName( m_childlinks[i].f_ind_id ) );
        }
        m_listChild->InsertItems( list, 0 );
    }
    m_fes = m_family.GetEvents();
    for( size_t i = 0 ; i < m_fes.size() ; i++ ) {
        idt eveID = m_fes[i].FGetEventID();
        m_listEvent->InsertItem( i, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( i, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( i, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( i, EC_Place, recEvent::GetAddressStr( eveID ) );
    }
    return true;
}

bool dlgEditFamily::TransferDataFromWindow()
{
    m_family.Save();
    recIndividual ind(m_family.f_husb_id);
    if( ind.f_fam_id == 0 ) {
        ind.f_fam_id = m_family.f_id;
        ind.Save();
    }
    ind.ReadID( m_family.f_wife_id );
    if( ind.f_fam_id == 0 ) {
        ind.f_fam_id = m_family.f_id;
        ind.Save();
    }

    for( size_t i = 0 ; i < m_childlinks.size() ; i++ ) {
        m_childlinks[i].fSetSeqChild( i+1 );
        m_childlinks[i].Save();
    }

    for( size_t i = 0 ; i < m_fes.size() ; i++ ) {
        if( m_fes[i].FGetFamSeq() != i+1 ) {
            m_fes[i].FSetFamSeq( i+1 );
            m_fes[i].Save();
        }
    }
    return true;
}

void dlgEditFamily::OnHusbButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Husb;
    EditSpouseMenu( m_family.f_husb_id );
}

void dlgEditFamily::OnWifeButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Wife;
    EditSpouseMenu( m_family.f_wife_id );
}

void dlgEditFamily::EditSpouseMenu( idt indID )
{
    wxMenu* menu = new wxMenu;

    if( indID != 0 )
    {
        menu->Append( tfpID_DLGEDFAM_EDIT,     _("&Edit") );
        menu->Append( tfpID_DLGEDFAM_REMOVE,   _("&Remove") );
        menu->Append( tfpID_DLGEDFAM_DELETE,   _("&Delete") );
    } else {
        menu->Append( tfpID_DLGEDFAM_ADDNEW,   _("Add &New") );
        menu->Append( tfpID_DLGEDFAM_ADDEXIST, _("Add &Existing") );
    }
    PopupMenu( menu );
    delete menu;
}

void dlgEditFamily::OnEditID( wxCommandEvent& event )
{
    idt indID;
    Sex sex;

    if( m_editbutton == EDBUT_Husb ) {
        indID = m_family.f_husb_id;
        sex = SEX_Male;
    } else {  // m_editbutton == EDBUT_Wife
        indID = m_family.f_wife_id;
        sex = SEX_Female;
    }

    if( indID == 0 ) {
        indID = tfpAddNewIndividual( m_family.f_id, sex );
        if( m_editbutton == EDBUT_Husb ) {
            m_family.f_husb_id = indID;
        } else {
            m_family.f_wife_id = indID;
        }
    } else {
        tfpEditIndividual( indID );
    }

    m_staticHusbName->SetLabel( recIndividual::GetFullName( m_family.f_husb_id ) );
    m_staticWifeName->SetLabel( recIndividual::GetFullName( m_family.f_wife_id ) );
}

void dlgEditFamily::OnRemoveID( wxCommandEvent& event )
{
    idt indID;

    if( m_editbutton == EDBUT_Husb ) {
        if( m_family.f_wife_id == 0 ) {
            return;  // Can't remove both spouses
        }
        indID = m_family.f_husb_id;
        m_family.f_husb_id = 0;
        m_staticHusbName->SetLabel( wxEmptyString );
    } else {
        if( m_family.f_husb_id == 0 ) {
            return;  // Can't remove both spouses
        }
        indID = m_family.f_wife_id;
        m_family.f_wife_id = 0;
        m_staticWifeName->SetLabel( wxEmptyString );
    }
    m_family.Save();
    recIndividual::Update( indID );
}

void dlgEditFamily::OnDeleteID( wxCommandEvent& event )
{
    if( m_editbutton == EDBUT_Husb ) {
       wxMessageBox( _("NYD for Delete Husband"), _("OnDeleteID") );
    } else {
       wxMessageBox( _("NYD for Delete Wife"), _("OnDeleteID") );
    }
}

void dlgEditFamily::OnAddExistID( wxCommandEvent& event )
{
    if( m_editbutton == EDBUT_Husb ) {
       wxMessageBox( _("NYD for Add Existing Husband"), _("OnDeleteID") );
    } else {
       wxMessageBox( _("NYD for Add Existing Wife"), _("OnDeleteID") );
    }
}

void dlgEditFamily::OnChildAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;

    menu->Append( tfpID_DLGEDFAM_ADDNEWSON,    _("Add New &Son") );
    menu->Append( tfpID_DLGEDFAM_ADDNEWDAUR,   _("Add New &Daughter") );
    menu->AppendSeparator();
    menu->Append( tfpID_DLGEDFAM_ADDEXISTSON,  _("Add &Existing Son") );
    menu->Append( tfpID_DLGEDFAM_ADDEXISTDAUR, _("Add E&xisting Daughter") );

    PopupMenu( menu );
    delete menu;
}

void dlgEditFamily::OnAddChild( wxCommandEvent& event )
{
    idt ret = 0;

    switch( event.GetId() )
    {
    case tfpID_DLGEDFAM_ADDNEWSON:
        ret = tfpAddNewChild( m_family.f_id, SEX_Male );
        break;
    case tfpID_DLGEDFAM_ADDNEWDAUR:
        ret = tfpAddNewChild( m_family.f_id, SEX_Female );
        break;
    case tfpID_DLGEDFAM_ADDEXISTSON:
    case tfpID_DLGEDFAM_ADDEXISTDAUR:
        // TODO:
        wxMessageBox( _("Not yet implimented"), _("OnAddChild") );
        return;
    }

    if( ret != 0 ) {
        recFamilyIndividual fi;
        fi.Clear();
        fi.f_fam_id = m_family.f_id;
        fi.f_ind_id = ret;
        fi.Find();
        m_childlinks.push_back( fi );
        m_listChild->Append( recIndividual::GetFullName( ret ) );
    }
}

void dlgEditFamily::OnChildEditButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEditButton") );
}

void dlgEditFamily::OnChildDeleteButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnDeleteButton") );
}

void dlgEditFamily::OnChildUpButton( wxCommandEvent& event )
{
    int item = m_listChild->GetSelection();
    if( item == wxNOT_FOUND || item == 0 ) {
        return;
    }

    recFamilyIndividual fi = m_childlinks[item];
    m_childlinks[item] = m_childlinks[item-1];
    m_childlinks[item-1] = fi;

    m_listChild->Delete( item );
    m_listChild->Insert(
        recIndividual::GetFullName( m_childlinks[item-1].f_ind_id ), item - 1
    );
    m_listChild->SetSelection( item - 1 );
}

void dlgEditFamily::OnChildDownButton( wxCommandEvent& event )
{
    int item = m_listChild->GetSelection();
    if( item == wxNOT_FOUND || item == m_listChild->GetCount() - 1 ) {
        return;
    }

    recFamilyIndividual fi = m_childlinks[item];
    m_childlinks[item] = m_childlinks[item+1];
    m_childlinks[item+1] = fi;

    m_listChild->Delete( item );
    m_listChild->Insert(
        recIndividual::GetFullName( m_childlinks[item+1].f_ind_id ), item + 1
    );
    m_listChild->SetSelection( item + 1 );
}


void dlgEditFamily::OnEventAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( tfpID_DLGEDFAM_NEW_EVENT, _("&New Event") );
    menu->Append( tfpID_DLGEDFAM_EXIST_EVENT, _("&Existing Event") );
    PopupMenu( menu );
    delete menu;
}

void dlgEditFamily::OnNewEvent( wxCommandEvent& event )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt typeID = recEventType::Select( recEventType::SF_Family );
    if( typeID == 0 ) {
        recDb::Rollback( savepoint );
        return;
    }

    recEvent eve(0);
    eve.f_type_id = typeID;
    eve.SetAutoTitle( 
        recIndividual::GetFullName( m_family.f_husb_id ),
        recIndividual::GetFullName( m_family.f_wife_id )
    );
    eve.Save();

    recIndividualEvent ie(0);
    ie.FSetEventID( eve.GetID() );
    if( m_family.f_husb_id ) {
        ie.FSetIndID( m_family.f_husb_id );
        idt roleID = recEventTypeRole::Select( typeID, recEventTypeRole::SF_Prime1 );
        if( roleID == 0 ) {
            recDb::Rollback( savepoint );
            return;
        }
        ie.FSetRoleID( roleID );
        ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( m_family.f_husb_id ) );
        ie.Save();
    }
    if( m_family.f_wife_id ) {
        ie.FSetID( 0 );
        ie.FSetIndID( m_family.f_wife_id );
        idt roleID = recEventTypeRole::Select( typeID, recEventTypeRole::SF_Prime2 );
        if( roleID == 0 ) {
            recDb::Rollback( savepoint );
            return;
        }
        ie.FSetRoleID( roleID );
        ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( m_family.f_wife_id ) );
        ie.Save();
    }
    recFamilyEvent fe(0);
    fe.FSetFamID( m_family.FGetID() );
    fe.FSetEventID( eve.FGetID() );
    fe.FSetFamSeq( m_family.GetMaxEventSeqNumber() );
    fe.Save();

    dlgEditIndEvent* dialog = new dlgEditIndEvent( this, eve.GetID() );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        eve.Read();
        int row = m_fes.size();
        m_listEvent->InsertItem( row, recEvent::GetIdStr( eve.GetID() ) );
        m_listEvent->SetItem( row, EC_Title, recEvent::GetTitle( eve.GetID() ) );
        m_listEvent->SetItem( row, EC_Date, recEvent::GetDateStr( eve.GetID() ) );
        m_listEvent->SetItem( row, EC_Place, recEvent::GetAddressStr( eve.GetID() ) );
        m_fes.push_back( fe );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditFamily::OnExistingEvent( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( _("Not yet implimented"), _("OnExistingEvent") );
}

void dlgEditFamily::OnEventEditButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event") );
        return;
    }

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    dlgEditIndEvent* dialog = 
        new dlgEditIndEvent( NULL, m_fes[row].FGetEventID() );

    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditFamily::OnEventDeleteButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        int ans = wxMessageBox( 
            _("Remove Event completely from database?"), _("Delete Event"),
            wxYES_NO | wxCANCEL, this
        );
        if( ans != wxYES ) {
            return;
        }
        m_listEvent->DeleteItem( row );
        recEvent::DeleteFromDb( m_fes[row].FGetEventID() );
        m_fes.erase( m_fes.begin() + row );
    } else {
        wxMessageBox( _("No row selected"), _("Delete Event") );
    }
}

void dlgEditFamily::OnEventUpButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Move Event up") );
        return;
    }
    if( row != 0 ) {
        recFamilyEvent temp = m_fes[row];
        m_fes[row] = m_fes[row-1];
        m_fes[row-1] = temp;

        m_listEvent->DeleteItem( row );
        idt eveID = m_fes[row-1].FGetEventID();
        m_listEvent->InsertItem( row-1, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row-1, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row-1, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row-1, EC_Place, recEvent::GetAddressStr( eveID ) );

        long state = wxLIST_STATE_SELECTED;
        m_listEvent->SetItemState( row-1, state, state );
        m_listEvent->EnsureVisible( row-1 );
    }
}

void dlgEditFamily::OnEventDownButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Move Event down") );
        return;
    }
    if( row < m_listEvent->GetItemCount()-1 ) {
        recFamilyEvent temp = m_fes[row];
        m_fes[row] = m_fes[row+1];
        m_fes[row+1] = temp;

        m_listEvent->DeleteItem( row );
        idt eveID = m_fes[row+1].FGetEventID();
        m_listEvent->InsertItem( row+1, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( row+1, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( row+1, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( row+1, EC_Place, recEvent::GetAddressStr( eveID ) );

        long state = wxLIST_STATE_SELECTED;
        m_listEvent->SetItemState( row+1, state, state );
        m_listEvent->EnsureVisible( row+1 );
    }
}



// End of dlgEdFamily.cpp
