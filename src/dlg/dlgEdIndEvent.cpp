/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual Event dialog.
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

#include <wx/fs_mem.h>

#include <rec/recLink.h>

#include "dlgEdIndEvent.h"
#include "dlgEdRole.h"


//-----------------------------------------------------
//      dlgEditIndEvent
//-----------------------------------------------------

dlgEditIndEvent::dlgEditIndEvent( wxWindow* parent, idt eventID )
    : fbDlgEditIndEvent( parent ), m_event(eventID)
{
    m_date1.ReadID( m_event.FGetDate1ID() );
    if( m_date1.FGetID() == 0 ) {
        m_date1.SetDefaults();
    }
    m_place.ReadID( m_event.FGetPlaceID() );

    m_listPersona->InsertColumn( COL_IndID, _("Individual") );
    m_listPersona->InsertColumn( COL_Name, _("Name") );
    m_listPersona->InsertColumn( COL_Role, _("Role") );
    m_listPersona->InsertColumn( COL_Note, _("Note") );
}

dlgEditIndEvent::~dlgEditIndEvent()
{
    if( !m_dateImageFN.IsEmpty() ) {
        wxMemoryFSHandler::RemoveFile( m_dateImageFN );
    }
    for( size_t i = 0 ; i < m_dateImageFNs.size() ; i++ ) {
        wxMemoryFSHandler::RemoveFile( m_dateImageFNs[i] );
    }
}

bool dlgEditIndEvent::TransferDataToWindow()
{
    wxASSERT( m_event.GetID() != 0 );
    m_staticType->SetLabel( m_event.GetTypeStr() );
    m_staticEventID->SetLabel( m_event.GetIdStr() );
    m_textCtrlTitle->SetValue( m_event.f_title );
    m_textCtrlDate1->SetValue( m_date1.GetStr() );
    m_buttonDate2->Enable( false );
    m_textCtrlAddr->SetValue( m_place.GetAddressStr() );
    m_textCtrlNote->SetValue( m_event.f_note );

    m_ies = m_event.GetIndividualEvents();
    m_individuals.clear();
    recIndividual ind;
    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
//        ind.ReadPersona( m_ies[i].f_per_id );
        ind.ReadID( m_ies[i].FGetIndID() );
        m_individuals.push_back( ind );
        m_listPersona->InsertItem( i, ind.GetIdStr() );
        m_listPersona->SetItem( i, COL_Name, ind.GetFullName() );
        m_listPersona->SetItem( i, COL_Role, recEventTypeRole::GetName( m_ies[i].f_role_id ) );
        m_listPersona->SetItem( i, COL_Note, m_ies[i].f_note );
    }

    m_refEvents = recEvent::FindEquivRefEvents( m_event.f_id );
    for( size_t i = 0 ; i < m_refEvents.size() ; i++ ) {
        idt refID = recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, m_refEvents[i].f_id );
        m_refIDs.push_back( refID );
        // Get list of Persona's for this Reference.
        recIdVec pIDs = recReference::GetPersonaList( refID ); 
        m_personaIDs.insert( m_personaIDs.end(), pIDs.begin(), pIDs.end() );
        recDate date( m_refEvents[i].f_date1_id );
        m_reDate1s.push_back( date );
    }

    for( size_t i = 0 ; i < m_personaIDs.size() ; i++ ) {
        // Get a list of Individual's linked to this Persona.
        recIdVec iIDs = recPersona::GetIndividualIDs( m_personaIDs[i] );
        for( size_t j = 0 ; j < iIDs.size() ; j++ ) {
            // Get current list of Persona's already linked to this Individual, if any.
            recIdVec ipIDs = m_indPerMap[iIDs[j]];
            ipIDs.push_back( m_personaIDs[i] );
            m_indPerMap[iIDs[j]] = ipIDs;
        }
    }

    m_htmlRef->SetPage( WrReferenceEvents() );
    m_htmlDate->SetPage( WrReferenceDates() );
    m_htmlPlace->SetPage( WrReferencePlaces() );
    m_htmlPersona->SetPage( WrReferencePersonas() );
    m_htmlInd->SetPage( WrReferenceIndividuals() );
    return true;
}

wxString dlgEditIndEvent::WrReferenceEvents()
{
    wxString htm;

    htm << "<html><head><title>"
        << m_event.f_title << "</title></head>"
           "<body><table>";

    wxASSERT( m_refEvents.size() == m_refIDs.size() );
    for( size_t i = 0 ; i < m_refEvents.size() ; i++ ) {
        idt refID = m_refIDs[i];
        htm << "<tr><td>" << recReference::GetIdStr( m_refIDs[i] )
            << "</td><td>" << recReference::GetTitle( m_refIDs[i] )
            << "</td></tr>"
            << "<tr><td></td><td><table><tr><td>" << m_refEvents[i].GetIdStr()
            << "</td><td>" 
            << m_refEvents[i].f_title << "<br>" << m_refEvents[i].GetDetailStr()
            << "</td></tr>"
        ;
        if( !m_refEvents[i].f_note.IsEmpty() ) {
            htm << "<tr><td colspan=2>" << m_refEvents[i].f_note << "</td></tr>";
        }
        htm << "</table></td></tr>";
    }

    htm << "</table></body></html>";

    return htm;
}

wxString dlgEditIndEvent::WrReferenceDates()
{
    wxString htm;

    if( CreateDateImageFile() ) {
        htm << "<html><head><title>Dates</title></head><body>\n"
               "<table cellspacing=0 cellpadding=0 border=0>\n"
               "<tr><td colspan=4 align=center><font size=+2><b>Dates</b></font></td></tr>\n"
               "<tr>\n<td>" << m_event.GetIdStr() << "</td>\n"
               "<td><img src=\"memory:" << m_dateImageFN << "\"></td>\n"
               "<td nowrap>" << m_date1.GetStr() << "</td>\n</tr>\n";
        for( size_t i = 0 ; i < m_reDate1s.size() ; i++ ) {
            htm << "<tr>\n<td>" << recReference::GetIdStr( m_refIDs[i] ) << "</td>\n"
                   "<td><img src=\"memory:" << m_dateImageFNs[i] << "\"></td>\n"
                   "<td nowrap>" << m_reDate1s[i].GetStr() << "</td>\n</tr>\n";
        }

        htm << "</table>\n</body>\n</html>\n";
    } else {
        htm << "<html><head><body>"
               "No dates recorded"
               "</body></html>";
    }

    return htm;
}

bool dlgEditIndEvent::CreateDateImageFile()
{
    size_t i;
    if( !m_dateImageFN.IsEmpty() ) {
        wxMemoryFSHandler::RemoveFile( m_dateImageFN );
    }
    for( i = 0 ; i < m_dateImageFNs.size() ; i++ ) {
        wxMemoryFSHandler::RemoveFile( m_dateImageFNs[i] );
    }
    m_dateImageFNs.clear();

    long min, max;
    if( m_date1.f_jdn ) {
        min = m_date1.f_jdn;
        max = min + m_date1.f_range;
    } else {
        for( i = 0, min = 0 ; i < m_reDate1s.size() ; i++ ) {
            min = m_reDate1s[i].GetDatePoint();
            if( min ) break;
        }
        if( min == 0 ) {
            return false; // no dates to display
        }
        max = min;
    }        

    wxMemoryDC dc;
    wxBitmap bitmap( 200, 40 );
    dc.SelectObject( bitmap );
    wxColour color;
    dc.SetBackground( *wxWHITE );
    dc.Clear();

    for( i = 0 ; i < m_reDate1s.size() ; i++ ) {
        if( m_reDate1s[i].f_jdn == 0 ) continue;
        min = wxMin( min, m_reDate1s[i].f_jdn );
        max = wxMax( max, m_reDate1s[i].f_jdn + m_reDate1s[i].f_range );
    }
    min -= 365;
    max += 365;
    double scale = (double) 200 / ( max - min );
    DrawDateImage( dc, m_date1, min, scale, *wxBLACK );
    wxString filename = m_event.GetIdStr() + "date.bmp";
    wxMemoryFSHandler::AddFile( filename, bitmap, wxBITMAP_TYPE_BMP );
    m_dateImageFN = filename;

    int beg = ( m_date1.f_jdn - min ) * scale;
    int end = ( m_date1.f_jdn + m_date1.f_range - min ) * scale;
    for( i = 0 ; i < m_reDate1s.size() ; i++ ) {
        dc.Clear();
        dc.SetPen( *wxBLACK );
        if( m_date1.f_range ) {
            dc.DrawLine( beg, 0, beg, 40 );
            dc.DrawLine( end, 0, end, 40 );
        } else {
            dc.DrawLine( beg, 0, beg, 40 );
        }
        unsigned comp = m_date1.GetCompareFlags( m_reDate1s[i] );
        if( comp & recDate::CF_Overlap ) {
            color = *wxGREEN;
        } else if( comp & recDate::CF_WithinType ) {
            color = wxColour( 255, 127, 0 ); // Orange
        } else {
            color = *wxRED;
        }
        DrawDateImage( dc, m_reDate1s[i], min, scale, color );
        filename << m_event.GetIdStr() << "date" << i << ".bmp";
        wxMemoryFSHandler::AddFile( filename, bitmap, wxBITMAP_TYPE_BMP );
        m_dateImageFNs.push_back( filename );
    }

    dc.SelectObject( wxNullBitmap );
    return true;
}

void dlgEditIndEvent::DrawDateImage( 
    wxDC& dc, const recDate& date, long start, double scale, const wxColour& color )
{
    int beg = ( date.f_jdn - start ) * scale;
    int end = ( date.f_jdn + date.f_range - start ) * scale;
    int taper = 365 * scale;
    dc.SetPen( color );
    dc.SetBrush( color );
    if( date.f_type & recDate::FLG_BEFORE ) {
        wxRect r( beg-taper, 10, taper, 20 );
        dc.GradientFillLinear( r, *wxWHITE, color, wxRIGHT );
    }
    if( date.f_range ) {
        dc.DrawRectangle( wxRect( beg, 10, end-beg, 20 ) );
        dc.DrawLine( beg, 0, beg, 40 );
        dc.DrawLine( end, 0, end, 40 );
    } else {
        dc.DrawLine( beg, 0, beg, 40 );
   }
    if( date.f_type & recDate::FLG_AFTER ) {
        wxRect r( end, 10, taper, 20 );
        dc.GradientFillLinear( r, *wxWHITE, color, wxLEFT );
    }
}

wxString dlgEditIndEvent::WrReferencePlaces()
{
    wxString htm;

    // TODO: Create places list
    htm << "<html><head><body>"
           "Places - Not yet written"
           "</body></html>";
    return htm;
}

wxString dlgEditIndEvent::WrReferencePersonas()
{
    wxString htm;

    htm << "<html><head><title>"
        << m_event.f_title << "</title></head>"
           "<body><table>";

    idt prevRefID = 0; 
    for( size_t i = 0 ; i < m_personaIDs.size() ; i++ ) {
        recPersona per(m_personaIDs[i]);
        htm << "<tr><td>" << ( ( prevRefID == per.FGetRefID() ) ? 
                "" : recReference::GetIdStr( per.FGetRefID() ) )
            << "</td><td>" << per.GetIdStr()
            << "</td><td>" << per.GetNameStr()
            << "</td></tr>"
        ;
        if( !per.FGetNote().IsEmpty() ) {
            htm << "<tr><td></td><td>" <<per.FGetNote() << "</td></tr>";
        }
        prevRefID = per.FGetRefID();
    }

    htm << "</table></body></html>";

    return htm;
}

wxString dlgEditIndEvent::WrReferenceIndividuals()
{
    wxString htm;

    htm << "<html><head><title>"
        << m_event.f_title << "</title></head>"
           "<body><table>";

    IndPerMap::iterator it;
    for( it = m_indPerMap.begin() ; it != m_indPerMap.end() ; it++ ) {
        recIndividual ind((*it).first);

        htm << "<tr><td>" << ind.GetIdStr()
            << "</td><td>" << ind.GetFullName()
            << "</td><td>" << recIdVecToStr<recPersona>( (*it).second )
            << "</td></tr>"
        ;
    }

    htm << "</table></body></html>";

    return htm;
}

bool dlgEditIndEvent::TransferDataFromWindow()
{
    wxASSERT( m_event.f_type_id != 0 );

    m_event.f_title = m_textCtrlTitle->GetValue();
    wxString str = m_textCtrlDate1->GetValue();
    if( str.IsEmpty() ) {
        m_date1.Delete();
        m_event.f_date1_id = 0;
    } else {
        m_date1.SetDate( str );
        m_date1.Save();
        m_event.f_date1_id = m_date1.f_id;
    }
    m_event.f_date2_id = 0;
    str = m_textCtrlAddr->GetValue();
    if( str.IsEmpty() ) {
        m_place.DeleteAll();
        m_event.f_place_id = 0;
    } else {
        m_place.Save();
        m_place.SetAddress( str );
        m_event.f_place_id = m_place.f_id;
    }
    m_event.f_note = m_textCtrlNote->GetValue();

    m_event.UpdateDatePoint(); 
    m_event.Save();

    for( size_t i = 0 ; i < m_ies.size() ; i++ ) {
        m_ies[i].FSetIndSeq( i + 1 );
        m_ies[i].Save();
    }

    return true;
}

void dlgEditIndEvent::OnDate1Button( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDate1Button")
    );
}

void dlgEditIndEvent::OnDate2Button( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDate2Button")
    );
}

void dlgEditIndEvent::OnPlaceButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nPlace"),
        wxT("OnPlaceButton")
    );
}

void dlgEditIndEvent::OnAddButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnAddButton")
    );
#if 0
// Copied from Name dialog for as example code
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
#endif
}

void dlgEditIndEvent::OnEditButton( wxCommandEvent& event )
{
    long row = m_listPersona->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Individual") );
        return;
    }

    const wxString savepoint = "EdIndRole";
    dlgEditIndRole* dialog = new dlgEditIndRole( NULL, m_ies[row].FGetID() );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        recIndividualEvent* ie = dialog->GetIndividualEvent();
        m_listPersona->SetItem( row, COL_Role, recEventTypeRole::GetName( ie->FGetRoleID() ) );
        m_listPersona->SetItem( row, COL_Note, ie->FGetNote() );
        m_ies[row] = *ie;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
}

void dlgEditIndEvent::OnDeleteButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnDeleteButton")
    );
#if 0
// Copied from Name dialog for as example code
    long row = m_listParts->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row >= 0 ) {
        m_listParts->DeleteItem( row );
        m_parts[row].Delete();
        m_parts.erase( m_parts.begin() + row );
        UpdateName();
    } else {
        wxMessageBox( wxT("No row selected"), wxT("Delete Name") );
    }
#endif
}

void dlgEditIndEvent::OnUpButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnUpButton")
    );
#if 0
// Copied from Name dialog for as example code
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
#endif
}

void dlgEditIndEvent::OnDownButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented"),
        wxT("OnDownButton")
    );
#if 0
// Copied from Name dialog for as example code
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
#endif
}

//-----------------------------------------------------
//      dlgEditFamEvent
//-----------------------------------------------------

dlgEditFamEvent::dlgEditFamEvent(
    wxWindow* parent, idt eventID, recEventType::ETYPE_Grp grp
    ) : fbDlgEditFamEvent(parent), m_grp(grp)
{
    m_event.f_id = eventID;
}


bool dlgEditFamEvent::TransferDataToWindow()
{
    if( m_event.f_id == 0 ) {
        m_event.Clear();
        m_event.Save();
    } else {
        m_event.Read();
    }
    m_textCtrlTitle->SetValue( m_event.f_title );
    m_textCtrlType->SetValue( recEventType::GetTypeStr( m_event.f_type_id ) );
    m_textCtrlDate->SetValue( recDate::GetStr( m_event.f_date1_id ) );
    m_textCtrlAddr->SetValue( recPlace::GetAddressStr( m_event.f_place_id ) );
    m_textCtrlNote->SetValue( m_event.f_note );

    return true;
}


bool dlgEditFamEvent::TransferDataFromWindow()
{
    m_event.f_title = m_textCtrlTitle->GetValue();
    m_event.f_note = m_textCtrlNote->GetValue();
    m_event.Save();

    return true;
}

void dlgEditFamEvent::OnTypeButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nType"),
        wxT("OnTypeButton")
    );
}

void dlgEditFamEvent::OnDateButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nDate"),
        wxT("OnDateButton")
    );
}

void dlgEditFamEvent::OnAddrButton( wxCommandEvent& event )
{
    wxMessageBox(
        wxT("Not yet implimented\nAddress"),
        wxT("OnAddrButton")
    );
}


// End of dlgEdIndEvent.cpp file
