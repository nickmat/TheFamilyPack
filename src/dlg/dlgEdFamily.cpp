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
END_EVENT_TABLE()

dlgEditFamily::dlgEditFamily( wxWindow* parent ) : fbDlgEditFamily( parent )
{
    m_child = 0;
    m_family.Clear();
}

bool dlgEditFamily::TransferDataToWindow()
{
    if( m_family.f_id == 0 ) {
        m_family.Save();
    } else {
        m_family.Read();
    }
    if( m_child > 0 ) {
        recFamilyIndividual fi;
        fi.Clear();
        fi.f_fam_id = m_family.f_id;
        fi.f_ind_id = m_child;
        fi.f_sequence = 1;
        fi.Save();
    }

    wxString str;

    str << wxT("F") << m_family.f_id;
    m_staticFamID->SetLabel( str  );

    str = recIndividual::GetFullName( m_family.f_husb_id );
    m_staticHusbName->SetLabel( str  );

    str = recIndividual::GetFullName( m_family.f_wife_id );
    m_staticWifeName->SetLabel( str  );

    str = recEvent::GetDetailStr( m_family.GetMarriageEvent() );
    m_staticMarrEvent->SetLabel( str  );

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
    return true;
}

bool dlgEditFamily::TransferDataFromWindow()
{
    m_family.Save();
    for( size_t i = 0 ; i < m_childlinks.size() ; i++ ) {
        m_childlinks[i].f_sequence = i+1;
        m_childlinks[i].Save();
    }
    return true;

}

void dlgEditFamily::OnHusbButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Husb;
    EditIDMenu( m_family.f_husb_id );
}

void dlgEditFamily::OnWifeButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Wife;
    EditIDMenu( m_family.f_wife_id );
}

void dlgEditFamily::OnMarriageButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Marr;
    EditIDMenu( m_family.GetMarriageEvent() );
}

void dlgEditFamily::EditIDMenu( idt editID )
{
    wxMenu* menu = new wxMenu;

    if( editID != 0 )
    {
        menu->Append( tfpID_DLGEDFAM_EDIT,     _("&Edit") );
        menu->Append( tfpID_DLGEDFAM_REMOVE,   _("&Remove") );
        menu->Append( tfpID_DLGEDFAM_DELETE,   _("&Delete") );
        if( m_editbutton == EDBUT_Marr ) {
            if( recEvent::FindReferenceID( m_family.GetMarriageEvent() ) == 0 ) {
                menu->Enable( tfpID_DLGEDFAM_REMOVE, false );
            } else {
                menu->Enable( tfpID_DLGEDFAM_DELETE, false );
            }
        }
    } else {
        menu->Append( tfpID_DLGEDFAM_ADDNEW,   _("Add &New") );
        menu->Append( tfpID_DLGEDFAM_ADDEXIST, _("Add &Existing") );
    }
    PopupMenu( menu );
    delete menu;
}

void dlgEditFamily::OnEditID( wxCommandEvent& event )
{
    idt ret;

    switch( m_editbutton )
    {
    case EDBUT_Husb:
        if( m_family.f_husb_id == 0 ) {
            // Add Husband
            ret = tfpAddNewIndividual( m_family.f_id, SEX_Male );
            if( ret ) {
                m_family.f_husb_id = ret;
            }
        } else {
            // Edit Husband
            tfpEditIndividual( m_family.f_husb_id );
        }
        m_staticHusbName->SetLabel(
            recIndividual::GetFullName( m_family.f_husb_id )
        );
        break;
    case EDBUT_Wife:
        if( m_family.f_wife_id == 0 ) {
            // Add Wife
            ret = tfpAddNewIndividual( m_family.f_id, SEX_Female );
            if( ret ) {
                m_family.f_wife_id = ret;
            }
        } else {
            // Edit Wife
            tfpEditIndividual( m_family.f_wife_id );
        }
        m_staticWifeName->SetLabel(
            recIndividual::GetFullName( m_family.f_wife_id )
        );
        break;
    case EDBUT_Marr:
        if( m_family.GetMarriageEvent() == 0 ) {
            // Add marriage
            ret = tfpAddMarriageEvent( m_family.f_id );
            if( ret ) {
                wxString str = recEvent::GetDetailStr( m_family.GetMarriageEvent() );
                m_staticMarrEvent->SetLabel( str  );
            }
        } else {
            // Edit marriage
            //wxMessageBox( wxT("NYI Edit Marriage"), wxT("OnEditID") );
            if( EditEvent( &ret ) ) {
                m_staticMarrEvent->SetLabel(
                    recEvent::GetDetailStr( ret )
                );
            }
        }
        break;
    }
}

void dlgEditFamily::OnRemoveID( wxCommandEvent& event )
{
    switch( m_editbutton )
    {
    case EDBUT_Husb:
        m_family.f_husb_id = 0;
        m_staticHusbName->SetLabel( wxEmptyString );
        break;
    case EDBUT_Wife:
        m_family.f_wife_id = 0;
        m_staticWifeName->SetLabel( wxEmptyString );
        break;
    case EDBUT_Marr:
        m_staticMarrEvent->SetLabel( wxEmptyString );
        break;
    }
}

void dlgEditFamily::OnDeleteID( wxCommandEvent& event )
{
    wxString mes;
    idt id, evID;

    switch( m_editbutton )
    {
    case EDBUT_Husb:
        // TODO:
       wxMessageBox(
           wxT("NYI for Delete Husband"),
           wxT("OnDeleteID") );
        break;
    case EDBUT_Wife:
        // TODO:
       wxMessageBox(
           wxT("NYI for Delete Wife"),
           wxT("OnDeleteID") );
        break;
    case EDBUT_Marr:
        evID = m_family.GetMarriageEvent();
        id = recEvent::FindReferenceID( evID );
        if( id == 0 ) {
            if( !recEvent::DeleteFromDb( evID ) ) {
                mes << _("Unable to delete E")
                    << evID << "\n"
                    << _(" from database");
                wxMessageBox( mes, _("Delete Marriage Event") );
            }
        } else {
            mes << _("Event is owned by Reference R")
                << id << ".\n"
                << _("Edit Reference to delete Event E")
                << evID;
            wxMessageBox( mes, _("Delete Marriage Event") );
        }
        break;
    }
}

void dlgEditFamily::OnAddExistID( wxCommandEvent& event )
{
    switch( m_editbutton )
    {
    case EDBUT_Husb:
        // TODO:
       wxMessageBox(
           wxT("NYI for Add Existing Husband"),
           wxT("OnAddExistID") );
        break;
    case EDBUT_Wife:
        // TODO:
       wxMessageBox(
           wxT("NYI for Add Existing Wife"),
           wxT("OnAddExistID") );
        break;
    case EDBUT_Marr:
        idt id = tfpGetExistingMarriageEvent( m_family.f_id );
        if( id == 0 ) {
            wxMessageBox(
                _("Unable to find suitabe event"),
                _("Add Marriage Event")
            );
            return;
        }
        m_staticMarrEvent->SetLabel( recEvent::GetDetailStr( id ) );
        break;
    }
}

bool dlgEditFamily::EditEvent( idt* pEventID )
{
    const wxString savepoint = "EdFamEvent";
    bool ret = false;
    dlgEditFamEvent* dialog = new dlgEditFamEvent(
        NULL, m_family.GetMarriageEvent(), recEventType::ETYPE_Grp_Union
    );
    recDb::Savepoint( savepoint );

    if( dialog->ShowModal() == wxID_OK ) {
        ret = true;
        *pEventID = dialog->GetEventID();
        recEventPersona pe(0);
        pe.f_per_id = m_family.f_husb_id;
        pe.f_event_id = dialog->GetEventID();
        pe.f_role_id = recEventTypeRole::ROLE_Marriage_Groom;
        if( pe.LinkExists() == false ) {
            pe.Save();
        }
        pe.Clear();
        pe.f_per_id = m_family.f_wife_id;
        pe.f_event_id = dialog->GetEventID();
        pe.f_role_id = recEventTypeRole::ROLE_Marriage_Bride;
        if( pe.LinkExists() == false ) {
            pe.Save();
        }
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        *pEventID = m_family.GetMarriageEvent();
    }
    dialog->Destroy();
    return ret;
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
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventAddButton") );
}

void dlgEditFamily::OnEventEditButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventEditButton") );
}

void dlgEditFamily::OnEventDeleteButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventDeleteButton") );
}

void dlgEditFamily::OnEventUpButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventUpButton") );
}

void dlgEditFamily::OnEventDownButton( wxCommandEvent& event )
{
    // TODO:
    wxMessageBox( wxT("Not yet implimented"), wxT("OnEventDownButton") );
}



// End of dlgEdFamily.cpp
