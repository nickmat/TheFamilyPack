/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdFamily.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Family entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010 .. 2021, Nick Matthews.
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
#include <rg/rgDialogs.h>

#include "rgEdFamily.h"

bool rgEditFamily( wxWindow* parent, idt famID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditFamily* dialog = new rgDlgEditFamily( parent, famID );

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
//-------------------------[ rgDlgEditFamily ]--------------------------------
//============================================================================

IMPLEMENT_CLASS( rgDlgEditFamily, wxDialog )

BEGIN_EVENT_TABLE( rgDlgEditFamily, wxDialog )
    EVT_MENU( rgID_DLGEDFAM_EDIT, rgDlgEditFamily::OnEditID )
    EVT_MENU( rgID_DLGEDFAM_REMOVE, rgDlgEditFamily::OnRemoveID )
    EVT_MENU( rgID_DLGEDFAM_DELETE, rgDlgEditFamily::OnDeleteID )
    EVT_MENU( rgID_DLGEDFAM_ADDNEW, rgDlgEditFamily::OnEditID )
    EVT_MENU( rgID_DLGEDFAM_ADDEXIST, rgDlgEditFamily::OnAddExistID )

    EVT_MENU( rgID_DLGEDFAM_ADDNEWSON, rgDlgEditFamily::OnAddChild )
    EVT_MENU( rgID_DLGEDFAM_ADDNEWDAUR, rgDlgEditFamily::OnAddChild )
    EVT_MENU( rgID_DLGEDFAM_ADDEXISTSON, rgDlgEditFamily::OnAddChild )
    EVT_MENU( rgID_DLGEDFAM_ADDEXISTDAUR, rgDlgEditFamily::OnAddChild )

    EVT_MENU( rgID_DLGEDFAM_UNLINK_EVENT, rgDlgEditFamily::OnUnlinkEvent )
    EVT_MENU( rgID_DLGEDFAM_DELETE_EVENT, rgDlgEditFamily::OnDeleteEvent )
END_EVENT_TABLE()

rgDlgEditFamily::rgDlgEditFamily( wxWindow* parent, idt famID )
    : m_family(famID), m_editbutton(EDBUT_Husb), m_order(recEO_DatePt),
    m_currentRow(0), fbRgEditFamily( parent )
{
    m_listChildren->InsertColumn( CC_Number, _("Number"), wxLIST_FORMAT_LEFT, 60 );
    m_listChildren->InsertColumn( CC_Name, _("Name") );
    m_listChildren->InsertColumn( CC_Dates, _("Dates") );

    m_listEvent->InsertColumn( EC_Number, _("Number") );
    m_listEvent->InsertColumn( EC_Title, _("Title") );
    m_listEvent->InsertColumn( EC_Date, _("Date") );
    m_listEvent->InsertColumn( EC_Place, _("Place") );
}

bool rgDlgEditFamily::TransferDataToWindow()
{
    wxASSERT( m_family.FGetID() != 0 );
    UpdateNames();
    UpdateChildList();
    UpdateEventList();
    m_staticFamID->SetLabel( m_family.GetIdStr() );
    return true;
}

bool rgDlgEditFamily::TransferDataFromWindow()
{
    m_family.Save();
    recIndividual ind(m_family.FGetHusbID());
    if( ind.FGetFamID() == 0 ) {
        ind.FSetFamID( m_family.FGetID() );
        ind.Save();
    }
    ind.ReadID( m_family.FGetWifeID() );
    if( ind.FGetFamID() == 0 ) {
        ind.FSetFamID( m_family.FGetID() );
        ind.Save();
    }
    return true;
}

void rgDlgEditFamily::UpdateNames()
{
    wxString str1 = recIndividual::GetName( m_family.FGetHusbID() );
    m_staticHusbName->SetLabel( str1  );

    wxString str2 = recIndividual::GetName( m_family.FGetWifeID() );
    m_staticWifeName->SetLabel( str2  );

    if( str1.size() ) {
        if( str2.size() ) {
            str1 << _(" and ") << str2;
        }
    } else {
        str1 << str2;
    }
    m_staticNames->SetLabel( str1 );
}

void rgDlgEditFamily::UpdateChildList( idt curIndID )
{
    m_fis = m_family.GetChildLinks();
    m_listChildren->DeleteAllItems();
    long row = -1;
    for( size_t i = 0 ; i < m_fis.size() ; i++ ) {
        idt indID = m_fis[i].FGetIndID();
        m_listChildren->InsertItem( i, recIndividual::GetIdStr( indID ) );
        m_listChildren->SetItem( i, CC_Name, recIndividual::GetName( indID ) );
        m_listChildren->SetItem( i, CC_Dates, recIndividual::GetEpitaph( indID ) );
        if( curIndID == indID ) {
            m_listChildren->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_fis[i].FGetSeqChild() != i+1 ) {
            m_fis[i].FSetSeqChild( i+1 );
            m_fis[i].Save();
        }
    }
    if( m_fis.size() ) {
        m_listChildren->SetColumnWidth( CC_Name, -1 );
    }
    if( row >= 0 ) {
        m_listChildren->EnsureVisible( row );
    }
    ChildButtonsEnable( row );
}

void rgDlgEditFamily::UpdateEventList( idt curEveID )
{
    m_fes = m_family.GetEvents();
    m_listEvent->DeleteAllItems();
    long row = -1;
    for( size_t i = 0 ; i < m_fes.size() ; i++ ) {
        idt eveID = m_fes[i].FGetEventID();
        m_listEvent->InsertItem( i, recEvent::GetIdStr( eveID ) );
        m_listEvent->SetItem( i, EC_Title, recEvent::GetTitle( eveID ) );
        m_listEvent->SetItem( i, EC_Date, recEvent::GetDateStr( eveID ) );
        m_listEvent->SetItem( i, EC_Place, recEvent::GetAddressStr( eveID ) );
        if( curEveID == eveID ) {
            m_listEvent->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_order == recEO_FamSeq && m_fes[i].FGetFamSeq() != i+1 ) {
            m_fes[i].FSetFamSeq( i+1 );
            m_fes[i].Save();
        }
    }
    if( row >= 0 ) {
        m_listEvent->EnsureVisible( row );
    }
    EventButtonsEnable( row );
}

void rgDlgEditFamily::OnPageChanged( wxBookCtrlEvent& event )
{
    Page page = (Page) m_notebook->GetSelection();
    switch( page )
    {
    case PAGE_Family:
        break;
        UpdateNames();
    case PAGE_Children:
        UpdateChildList();
        break;
    case PAGE_Events:
        UpdateEventList();
        break;
    default:
        wxASSERT( false );
    }
    PostSizeEvent();
}

void rgDlgEditFamily::OnHusbButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Husb;
    EditSpouseMenu( m_family.f_husb_id );
}

void rgDlgEditFamily::OnWifeButton( wxCommandEvent& event )
{
    m_editbutton = EDBUT_Wife;
    EditSpouseMenu( m_family.f_wife_id );
}

void rgDlgEditFamily::EditSpouseMenu( idt indID )
{
    wxMenu* menu = new wxMenu;

    if( indID != 0 )
    {
        menu->Append( rgID_DLGEDFAM_EDIT,     _("&Edit") );
        menu->Append( rgID_DLGEDFAM_REMOVE,   _("&Remove") );
        menu->Append( rgID_DLGEDFAM_DELETE,   _("&Delete") );
        if( m_family.f_husb_id == 0 || m_family.f_wife_id == 0 ) {
            menu->Enable( rgID_DLGEDFAM_REMOVE, false );
            menu->Enable( rgID_DLGEDFAM_DELETE, false );
        }
    } else {
        menu->Append( rgID_DLGEDFAM_ADDNEW,   _("Add &New") );
        menu->Append( rgID_DLGEDFAM_ADDEXIST, _("Add &Existing") );
    }
    PopupMenu( menu );
    delete menu;
}

void rgDlgEditFamily::OnEditID( wxCommandEvent& event )
{
    idt indID;
    Sex sex;
    int privacy;

    if( m_editbutton == EDBUT_Husb ) {
        indID = m_family.FGetHusbID();
        sex = SEX_Male;
        privacy = recIndividual::GetPrivacy( m_family.FGetWifeID() );
    } else {  // m_editbutton == EDBUT_Wife
        indID = m_family.FGetWifeID();
        sex = SEX_Female;
        privacy = recIndividual::GetPrivacy( m_family.FGetHusbID() );
    }

    if( indID == 0 ) {
        indID = rgAddNewIndividual( this, sex, privacy, "", m_family.FGetID() );
        if( m_editbutton == EDBUT_Husb ) {
            m_family.FSetHusbID( indID );
        } else {
            m_family.FSetWifeID( indID );
        }
    } else {
        rgEditIndividual( this, indID );
    }

    UpdateNames();
}

void rgDlgEditFamily::OnRemoveID( wxCommandEvent& event )
{
    idt indID;

    if( m_editbutton == EDBUT_Husb ) {
        if( m_family.FGetWifeID() == 0 ) {
            return;  // Can't remove both spouses
        }
        indID = m_family.FGetHusbID();
        m_family.FSetHusbID( 0 );
    } else {
        if( m_family.FGetHusbID() == 0 ) {
            return;  // Can't remove both spouses
        }
        indID = m_family.FGetWifeID();
        m_family.FSetWifeID( 0 );
    }
    m_family.Save();
    m_family.RemoveFromEvents( indID );
    recIndividual::Update( indID );
    recIndividual::CreateMissingFamilies();
    UpdateNames();
}

void rgDlgEditFamily::OnDeleteID( wxCommandEvent& event )
{
    if( m_editbutton == EDBUT_Husb ) {
        if( m_family.FGetWifeID() == 0 ) {
            return;  // Can't remove both spouses
        }
        if( rgDeleteIndividual( this, m_family.FGetHusbID() ) ) {
            m_family.FSetHusbID( 0 );
        }
    } else {
        if( m_family.FGetHusbID() == 0 ) {
            return;  // Can't remove both spouses
        }
        if( rgDeleteIndividual( this, m_family.FGetWifeID() ) ) {
            m_family.FSetWifeID( 0 );
        }
    }
    UpdateNames();
}

void rgDlgEditFamily::OnAddExistID( wxCommandEvent& event )
{
    if( m_editbutton == EDBUT_Husb ) {
        rgAddExistSpouse( this, m_family.FGetWifeID(), SEX_Male );
    } else {
        rgAddExistSpouse( this, m_family.FGetHusbID(), SEX_Female );
    }
    m_family.Read();
    UpdateNames();
}

void rgDlgEditFamily::ChildButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonEdit->Disable();
        m_buttonDel->Disable();
        m_buttonUp->Disable();
        m_buttonDn->Disable();
        return;
    }
    m_buttonEdit->Enable();
    m_buttonDel->Enable();
    if( row == 0 ) {
        m_buttonUp->Disable();
    } else {
        m_buttonUp->Enable();
    }
    if( row == m_listChildren->GetItemCount() - 1 ) {
        m_buttonDn->Disable();
    } else {
        m_buttonDn->Enable();
    }
}

void rgDlgEditFamily::OnChildAddButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;

    menu->Append( rgID_DLGEDFAM_ADDNEWSON,    _("Add New &Son") );
    menu->Append( rgID_DLGEDFAM_ADDNEWDAUR,   _("Add New &Daughter") );
    menu->AppendSeparator();
    menu->Append( rgID_DLGEDFAM_ADDEXISTSON,  _("Add &Existing Son") );
    menu->Append( rgID_DLGEDFAM_ADDEXISTDAUR, _("Add E&xisting Daughter") );

    PopupMenu( menu );
    delete menu;
}

void rgDlgEditFamily::OnAddChild( wxCommandEvent& event )
{
    idt indID = 0;

    switch( event.GetId() )
    {
    case rgID_DLGEDFAM_ADDNEWSON:
        indID = rgAddNewChild( this, m_family.FGetID(), SEX_Male );
        break;
    case rgID_DLGEDFAM_ADDNEWDAUR:
        indID = rgAddNewChild( this, m_family.FGetID(), SEX_Female );
        break;
    case rgID_DLGEDFAM_ADDEXISTSON:
        indID = rgAddExistChild( this, m_family.FGetID(), SEX_Male );
        break;
    case rgID_DLGEDFAM_ADDEXISTDAUR:
        indID = rgAddExistChild( this, m_family.FGetID(), SEX_Female );
        break;
    }
    if( indID ) {
        UpdateChildList( indID );
    }
}

void rgDlgEditFamily::OnChildSelect( wxListEvent& event )
{
    long row = m_listChildren->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    ChildButtonsEnable( row );
}

void rgDlgEditFamily::OnChildDeselect( wxListEvent& event )
{
    ChildButtonsEnable( -1 );
}

void rgDlgEditFamily::OnChildEditButton( wxCommandEvent& event )
{
    long row = m_listChildren->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row == wxNOT_FOUND ) {
        wxMessageBox( _("Row not selected"), _("Edit Children") );
        return;
    }
    idt indID = m_fis[row].FGetIndID();
    if( rgEditIndividual( this, indID ) ) {
        UpdateChildList( indID );
    }
}

void rgDlgEditFamily::OnChildDeleteButton( wxCommandEvent& event )
{
    long row = m_listChildren->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row == wxNOT_FOUND ) {
        wxMessageBox( _("Row not selected"), _("Remove Children") );
        return;
    }
    m_fis[row].Delete();
    UpdateChildList();
}

void rgDlgEditFamily::OnChildUpButton( wxCommandEvent& event )
{
    long row = m_listChildren->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_fis[row].FGetSeqChild();
    m_fis[row].FSetSeqChild( m_fis[row-1].FGetSeqChild() );
    m_fis[row].Save();
    m_fis[row-1].FSetSeqChild( seq );
    m_fis[row-1].Save();
    UpdateChildList( m_fis[row].FGetIndID() );
}

void rgDlgEditFamily::OnChildDownButton( wxCommandEvent& event )
{
    long row = m_listChildren->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == m_listChildren->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_fis[row].FGetSeqChild();
    m_fis[row].FSetSeqChild( m_fis[row+1].FGetSeqChild() );
    m_fis[row].Save();
    m_fis[row+1].FSetSeqChild( seq );
    m_fis[row+1].Save();
    UpdateChildList( m_fis[row].FGetIndID() );
}


void rgDlgEditFamily::EventButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonEventEdit->Disable();
        m_buttonEventDel->Disable();
        m_buttonEventUp->Disable();
        m_buttonEventDn->Disable();
        return;
    }
    m_buttonEventEdit->Enable();
    m_buttonEventDel->Enable();
    if( row == 0 ) {
        m_buttonEventUp->Disable();
    }
    else {
        m_buttonEventUp->Enable();
    }
    if( row == m_listEvent->GetItemCount() - 1 ) {
        m_buttonEventDn->Disable();
    }
    else {
        m_buttonEventDn->Enable();
    }
}

void rgDlgEditFamily::OnEventAddButton( wxCommandEvent& event )
{
    idt eveID; 
    if( m_family.FGetHusbID() == 0 ) {
        eveID = rgCreateIndEvent( this, m_family.FGetWifeID(), m_family.FGetHusbID(), m_family.FGetID() );
    } else {
        eveID = rgCreateIndEvent( this, m_family.FGetHusbID(), m_family.FGetWifeID(), m_family.FGetID() );
    }
    if( eveID ) {
        UpdateEventList( eveID );
    }
}

void rgDlgEditFamily::OnEventSelect( wxListEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    EventButtonsEnable( row );
}

void rgDlgEditFamily::OnEventDeselect( wxListEvent& event )
{
    EventButtonsEnable( -1 );
}

void rgDlgEditFamily::OnEventEditButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event") );
        return;
    }
    idt eveID = m_fes[row].FGetEventID();
    if( rgEditEvent( this, eveID ) ) {
        UpdateEventList( eveID );
    }
}

void rgDlgEditFamily::OnEventDeleteButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_currentRow = row;
        wxMenu* menu = new wxMenu;
        menu->Append( rgID_DLGEDFAM_UNLINK_EVENT, _("&Unlink Event") );
        menu->Append( rgID_DLGEDFAM_DELETE_EVENT, _("&Delete Event") );
        PopupMenu( menu );
        delete menu;
    } else {
        wxMessageBox( _("No row selected"), _("Delete Event") );
    }
}

void rgDlgEditFamily::OnUnlinkEvent( wxCommandEvent& event )
{
    recFamilyEvent::Delete( m_fes[m_currentRow].FGetID() );
    UpdateEventList();
}

void rgDlgEditFamily::OnDeleteEvent( wxCommandEvent& event )
{
    int ans = wxMessageBox( 
        _("Remove Event completely from database?"), _("Delete Event"),
        wxYES_NO | wxCANCEL, this
    );
    if( ans != wxYES ) {
        return;
    }
    recEvent::RemoveIncOrphansFromDatabase( m_fes[m_currentRow].FGetEventID() );
    UpdateEventList();
}

void rgDlgEditFamily::OnEventUpButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Event Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_fes[row].FGetFamSeq();
    m_fes[row].FSetFamSeq( m_fes[row-1].FGetFamSeq() );
    m_fes[row].Save();
    m_fes[row-1].FSetFamSeq( seq );
    m_fes[row-1].Save();
    UpdateEventList( m_fes[row].FGetEventID() );
}

void rgDlgEditFamily::OnEventDownButton( wxCommandEvent& event )
{
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Event Down") );
        return;
    }
    if( row == m_listEvent->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_fes[row].FGetFamSeq();
    m_fes[row].FSetFamSeq( m_fes[row+1].FGetFamSeq() );
    m_fes[row].Save();
    m_fes[row+1].FSetFamSeq( seq );
    m_fes[row+1].Save();
    UpdateEventList( m_fes[row].FGetEventID() );
}

void rgDlgEditFamily::OnEventOrderBy( wxCommandEvent& event )
{
    switch( event.GetSelection() )
    {
    case 0:
        m_order = recEO_DatePt;
        m_buttonEventUp->Enable( false );
        m_buttonEventDn->Enable( false );
        break;
    case 1:
        m_order = recEO_FamSeq;
        m_buttonEventUp->Enable( true );
        m_buttonEventDn->Enable( true );
        break;
    default:
        return;
    }
    long row = m_listEvent->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    idt eveID = ( row >= 0 ) ? m_fes[row].FGetEventID() : 0;
    UpdateEventList( eveID );
}

// End of src/rg/rgEdFamily.cpp
