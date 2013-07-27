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

#include <rec/recEvent.h>
#include <rec/recEventRecord.h>
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

idt rgSelectDate( wxWindow* wind, unsigned flag, unsigned* retbutton, unsigned filter, idt id )
{
    idt dateID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    bool cont = true;
    rgDlgSelectDate* dialog = new rgDlgSelectDate( wind, flag );

    while( cont ) {
        recIdVec dateIDs;
        switch( filter )
        {
        case recD_FILTER_Reference:
            dateIDs = recReference::GetDateIdVec( id );
            break;
        default:
            wxASSERT( false ); // Shouldn't be here
            return 0;
        }
        wxArrayString table;
        for( size_t i = 0 ; i < dateIDs.size() ; i++ ) {
            table.push_back( recDate::GetIdStr( dateIDs[i] ) );
            table.push_back( recDate::GetStr( dateIDs[i] ) );
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                dateID = rgCreateDate( wind );
                if( dateID ) {
                    if( retbutton ) *retbutton = rgSELSTYLE_Create;
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                // Create new Event Type
                wxMessageBox( "Not yet implimented", "rgSelectDate" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                dateID = 0;
                break;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            dateID = dateIDs[item];
        }
        cont = false;
    }
    dialog->Destroy();
    return dateID;
}

wxString rgDlgSelectDate::sm_colHeaders[COL_MAX] = { _("ID"), _("Date") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectPlace ]----------------------------------------
//-------------------------------------------------------------------------------

#include <rec/recPlace.h>

idt rgSelectPlace( 
    wxWindow* wind, unsigned flag, unsigned* retbutton, unsigned filter, idt id )
{
    idt placeID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    bool cont = true;
    rgDlgSelectPlace* dialog = new rgDlgSelectPlace( wind, flag );

    while( cont ) {
        recIdVec placeIDs;
        switch( filter )
        {
        case recP_FILTER_Reference:
            placeIDs = recReference::GetPlaceIdVec( id );
            break;
        default:
            wxASSERT( false ); // Shouldn't be here
            return 0;
        }
        wxArrayString table;
        for( size_t i = 0 ; i < placeIDs.size() ; i++ ) {
            table.push_back( recPlace::GetIdStr( placeIDs[i] ) );
            table.push_back( recPlace::GetAddressStr( placeIDs[i] ) );
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                placeID = rgCreatePlace( wind );
                if( placeID ) {
                    if( retbutton ) *retbutton = rgSELSTYLE_Create;
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                // Create new Event Type
                wxMessageBox( "Not yet implimented", "rgSelectPlace" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                placeID = 0;
                break;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            placeID = placeIDs[item];
        }
        cont = false;
    }
    dialog->Destroy();
    return placeID;
}

wxString rgDlgSelectPlace::sm_colHeaders[COL_MAX] = { _("ID"), _("Place") };

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectEventType ]--------------------------------------
//-------------------------------------------------------------------------------

idt rgSelectEventType( wxWindow* wind, unsigned flag, unsigned* retbutton, unsigned grpfilter )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectEventType* dialog = new rgDlgSelectEventType( wind, flag );

    while( cont ) {
        recEventTypeVec types = recEventType::ReadVec( grpfilter );
        wxArrayString table;
        for( size_t i = 0 ; i < types.size() ; i++ ) {
            table.push_back( types[i].GetGroupStr() );
            table.push_back( types[i].FGetName() );
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                id = rgCreateEventType( wind );
                if( id ) {
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                // Create new Event Type
                wxMessageBox( "Not yet implimented", "rgSelectEventType" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            id = types[item].FGetID();
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

wxString rgDlgSelectEventType::sm_colHeaders[COL_MAX] = { _("Group"), _("Type") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectIndividual ]-----------------------------------
//-------------------------------------------------------------------------------

idt rgSelectIndividual( wxWindow* wind, unsigned flag, unsigned* retbutton, unsigned sexfilter )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectIndividual* dialog = new rgDlgSelectIndividual( wind, flag );

    while( cont ) {
        recIndividualVec inds = recIndividual::ReadVec( sexfilter );
        wxArrayString table;
        for( size_t i = 0 ; i < inds.size() ; i++ ) {
            table.push_back( inds[i].GetIdStr() );
            table.push_back( inds[i].FGetName() );
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                id = rgAddNewIndividual( wind, SEX_Unstated );
                if( id ) {
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                wxMessageBox( "Not yet implimented", "rgSelectIndividual" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            id = inds[item].FGetID();
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

idt rgSelectIndividual( wxWindow* wind, Sex sex )
{
    unsigned filter;
    switch( sex )
    {
    case SEX_Male:
        filter = recInd_FILTER_SexMale;
        break;
    case SEX_Female:
        filter = recInd_FILTER_SexFemale;
        break;
    default:
        filter = recInd_FILTER_SexUnknown;
    }
    return rgSelectIndividual( wind, rgSELSTYLE_None, NULL, filter );
}

idt rgSelectIndividual( wxWindow* wind, recIdVec indIDs, unsigned flag, unsigned* retbutton )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectIndividual* dialog = new rgDlgSelectIndividual( wind, flag );

    while( cont ) {
        wxArrayString table;
        for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
            table.push_back( recIndividual::GetIdStr( indIDs[i] ) );
            table.push_back( recIndividual::GetName( indIDs[i] ) );
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                id = rgAddNewIndividual( wind, SEX_Unstated );
                if( id ) {
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                    indIDs.push_back( id );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                wxMessageBox( "Not yet implimented", "rgSelectIndividual" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            id = indIDs[item];
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

wxString rgDlgSelectIndividual::sm_colHeaders[COL_MAX] = { _("ID"), _("Name") };

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectPersona ]--------------------------------------
//-------------------------------------------------------------------------------

idt rgSelectPersona( 
    wxWindow* wind, idt refID, unsigned style, rgSELPER flag, unsigned* retbutton )
{
    idt perID = 0;
    rgDlgSelectPersona* dialog = new rgDlgSelectPersona( wind, style );

    for(;;) {
        recIdVec perIDs = recReference::GetPersonaList( refID );
        wxArrayString table;
        for( size_t i = 0 ; i < perIDs.size() ; i++ ) {
            table.push_back( recPersona::GetIdStr( perIDs[i] ) );
            table.push_back( recPersona::GetNameStr( perIDs[i] ) );
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                if( flag & rgSELPER_CreateUnnamed ) {
                    perID = recPersona::Create( refID );
                } else {
                    perID = rgCreateNamedPersona( wind, refID );
                    if( perID == 0 ) {
                        continue;
                    }
                }
                break;
            }
            if( dialog->GetFilterPressed() ) {
                wxMessageBox( "Not yet implimented", "rgSelectIndividual" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            perID = perIDs[item];
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        break;
    }
    dialog->Destroy();
    return perID;
}

BEGIN_EVENT_TABLE( rgDlgSelectPersona, wxDialog )
    EVT_MENU_RANGE( rgID_SELCREATPER_MALE, rgID_SELCREATPER_UNKNOWN, rgDlgSelectPersona::OnCreatePersona )
END_EVENT_TABLE()

wxString rgDlgSelectPersona::sm_colHeaders[COL_MAX] = { _("ID"), _("Name") };

void rgDlgSelectPersona::OnCreateButton( wxCommandEvent& event )
{
    wxMenu* menu = new wxMenu;
    menu->Append( rgID_SELCREATPER_MALE, _("Create &Male Persona") );
    menu->Append( rgID_SELCREATPER_FEMALE, _("Create &Female Persona") );
    menu->Append( rgID_SELCREATPER_UNKNOWN, _("Create &Unknown Persona") );
    PopupMenu( menu );
    delete menu;
}

void rgDlgSelectPersona::OnCreatePersona( wxCommandEvent& event )
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

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectEventRecord ]----------------------------------
//-------------------------------------------------------------------------------

idt rgSelectEquivalentEventRecord( wxWindow* wind, idt eventID )
{
    recEventRecordVec ers = recEvent::FindEquivRefEvents( eventID );
    if( ers.size() == 0 ) {
        return 0;
    }
    rgDlgSelectEventRecord* dialog = new rgDlgSelectEventRecord( wind, rgSELSTYLE_None );
    wxArrayString table;
    for( size_t i = 0 ; i < ers.size() ; i++ ) {
        table.push_back( ers[i].GetIdStr() );
        table.push_back( ers[i].FGetTitle() );
    }
    dialog->SetTable( table );
    idt id = 0;
    if( dialog->ShowModal() == wxID_OK ) {
        size_t item = (size_t) dialog->GetSelectedRow();
        id = ers[item].FGetID();
    }
    return id;
}

wxString rgDlgSelectEventRecord::sm_colHeaders[COL_MAX] = { _("ID"), _("Title") };


// End of src/rg/rgSelect.cpp file
