/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSelect.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Base rgSelect dialog class and others, GUI only.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
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

#include "rgSelect.h"
#include "rgTableCtrl.h"

rgSelect::rgSelect( 
    wxWindow* parent, wxString* headers, long width, unsigned style,
    const wxString& title )
    : m_create(false), m_filter(false), m_unknown(false), fbRgSelect( parent )
{
    m_width = width;
    int w = 0;
    for( long i = 0 ; i < width ; i++ ) {
        m_listCtrl->InsertColumn( i, headers[i] );
        w += m_listCtrl->GetColumnWidth( i );
    }
    wxSize sz = m_listCtrl->GetClientSize();
    int lcw = sz.GetWidth() - m_listCtrl->GetColumnWidth( width-1 ) - 20;
    m_listCtrl->SetColumnWidth( width-1, lcw );
    m_count = 0;
    if( title == wxEmptyString ) {
        SetTitle( _("Select item") );
    } else {
        SetTitle( title );
    }
    if( style & rgSELSTYLE_Create ){
        m_buttonCreate->Show();
    } else {
        m_buttonCreate->Hide();
    }
    if( style & rgSELSTYLE_Filter ){
        m_buttonFilter->Show();
    } else {
        m_buttonFilter->Hide();
    }
    if( style & rgSELSTYLE_Unknown ){
         m_buttonUnknown->Show();
    } else {
         m_buttonUnknown->Hide();
    }
}

void rgSelect::OnIdle( wxIdleEvent& event )
{
    if( m_listCtrl->GetSelectedItemCount() > 0 ) {
        m_buttonSelect->Enable( true );
    } else {
        m_buttonSelect->Enable( false );
    }
}

void rgSelect::OnCreateButton( wxCommandEvent& event )
{
    m_create = true;
    EndDialog( wxID_OK );
}

void rgSelect::OnFilterButton( wxCommandEvent& event )
{
    m_filter = true;
    EndDialog( wxID_OK );
}

void rgSelect::OnUnknownButton( wxCommandEvent& event )
{
    m_unknown = true;
    EndDialog( wxID_OK );
}


void rgSelect::SetTable( wxArrayString table )
{
    m_table = table;
    m_count = table.size() / m_width;

    m_listCtrl->SetTable( &m_table, m_width );
    m_listCtrl->SetItemCount( m_count );
}

void rgSelect::SetCreateButton( bool on )
{
    if( on ) {
        m_buttonCreate->Show();
    } else {
        m_buttonCreate->Hide();
    }
}

void rgSelect::SetFilterButton( bool on )
{
    if( on ) {
        m_buttonFilter->Show();
    } else {
        m_buttonFilter->Hide();
    }
}

void rgSelect::SetUnknownButton( bool on )
{
    if( on ) {
        m_buttonUnknown->Show();
    } else {
        m_buttonUnknown->Hide();
    }
}

long rgSelect::GetSelectedRow()
{
    return m_listCtrl->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
}

idt rgSelect::GetSelectedID()
{
    if( m_count > 0 && m_listCtrl->GetSelectedItemCount() > 0 ) {
        long row = m_listCtrl->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

        wxLongLong_t id;
        if( !m_table[row*m_width].ToLongLong( &id ) ) {
            return 0;
        }
        return id;
    }
    return 0;
}


//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectDate ]-----------------------------------------
//-------------------------------------------------------------------------------

wxString rgDlgSelectDate::sm_colHeaders[COL_MAX] = { _("ID"), _("Date") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectPlace ]----------------------------------------
//-------------------------------------------------------------------------------

wxString rgDlgSelectPlace::sm_colHeaders[COL_MAX] = { _("ID"), _("Place") };

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectEventType ]--------------------------------------
//-------------------------------------------------------------------------------

wxString rgDlgSelectEventType::sm_colHeaders[COL_MAX] = { _("Group"), _("Type") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectIndEvent ]--------------------------------------
//-------------------------------------------------------------------------------

//wxString rgDlgSelectIndEvent::sm_colHeaders[COL_MAX] = {
//    _("ID"), _("Title")/*, _("Date Point"), _("Type"), _("Group")*/ 
//};

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectIndividual ]-----------------------------------
//-------------------------------------------------------------------------------

wxString rgDlgSelectIndividual::sm_colHeaders[COL_MAX] = { _("ID"), _("Name") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectPersona ]--------------------------------------
//-------------------------------------------------------------------------------

wxString rgDlgSelectPersona::sm_colHeaders[COL_MAX] = { _("ID"), _("Name") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectCreatePersona ]--------------------------------
//-------------------------------------------------------------------------------

BEGIN_EVENT_TABLE( rgDlgSelectCreatePersona, wxDialog )
    EVT_MENU_RANGE( rgID_SELCREATPER_MALE, rgID_SELCREATPER_UNKNOWN, rgDlgSelectCreatePersona::OnCreatePersona )
END_EVENT_TABLE()


void rgDlgSelectCreatePersona::OnCreateButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( rgID_SELCREATPER_MALE, _("Create &Male Persona") );
    menu->Append( rgID_SELCREATPER_FEMALE, _("Create &Female Persona") );
    menu->Append( rgID_SELCREATPER_UNKNOWN, _("Create &Unknown Persona") );
    PopupMenu( menu );
    delete menu;
}

void rgDlgSelectCreatePersona::OnCreatePersona( wxCommandEvent& event )
{
    switch( event.GetId() )
    {
    case rgID_SELCREATPER_MALE:
        m_sex = SEX_Male;
        break;
    case rgID_SELCREATPER_FEMALE:
        m_sex = SEX_Female;
        break;
    case rgID_SELCREATPER_UNKNOWN:
        m_sex = SEX_Unknown;
        break;
    }
    SetCreatePressed();
    EndDialog( wxID_OK );
}


// End of src/rg/rgSelect.cpp file
