/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCompareEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Class used to display linked Individual Event data.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     10th December 2012
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

#include <wx/fs_mem.h>

#include "rg/rgCompareEvent.h"

rgCompareEvent::~rgCompareEvent()
{
    UnloadFiles();
}

void rgCompareEvent::Reset( idt eveID )
{
    UnloadFiles();
    m_event.ReadID( eveID );
    m_date1.ReadID( m_event.FGetDate1ID() );
    m_date2.ReadID( m_event.FGetDate2ID() );
    m_place.ReadID( m_event.FGetPlaceID() );

    m_ies.clear();
    m_individuals.clear();
    m_refEvents.clear();
    m_refIDs.clear();
    m_personaIDs.clear();
    m_indPerMap.clear();
    m_reDate1s.clear();
    m_rePlaces.clear();

    // The list of events we will be comparing with.
    m_refEvents = recEvent::FindEquivRefEvents( m_event.f_id );
    for( size_t i = 0 ; i < m_refEvents.size() ; i++ ) {
        idt refID = recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, m_refEvents[i].f_id );
        m_refIDs.push_back( refID );
        // Get list of Persona's for this Reference.
        recIdVec pIDs = recReference::GetPersonaList( refID ); 
        m_personaIDs.insert( m_personaIDs.end(), pIDs.begin(), pIDs.end() );
        recDate date( m_refEvents[i].FGetDate1ID() );
        m_reDate1s.push_back( date );
        recPlace place( m_refEvents[i].FGetPlaceID() );
        m_rePlaces.push_back( place );
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
}

wxString rgCompareEvent::GetRefEventsTable()
{
    wxASSERT( m_refIDs.size() == m_refEvents.size() );
    wxString htm;

    if( m_refIDs.size() ) {
        htm << 
            "<table class='data'>\n"
            "<tr>\n"
            "<th colspan='2'>Reference Document</th>\n"
            "<th colspan='2'>Reference Event</th>\n"
            "</tr>\n"
        ;
        for( size_t i = 0 ; i < m_refIDs.size() ; i++ ) {
            htm << 
                "<tr>\n"
                "<td><b><a href='tfp:R" << m_refIDs[i] << 
                "'>" << recReference::GetIdStr( m_refIDs[i] ) << "</a></b></td>\n"
                "<td>" << recReference::GetTitle( m_refIDs[i] ) << "</td>\n"
                "<td><b><a href='tfp:ER" << m_refEvents[i].FGetID() <<
                "'>" << m_refEvents[i].GetIdStr() << "</a></b></td>\n"
                "<td>" << m_refEvents[i].FGetTitle() << "</td>\n"
                "</tr>\n"
            ;
        }
        htm << "</table>\n";
    } else {
        htm << 
            "<table class='data'>\n<tr>\n"
            "<th>No Reference Event Records available</th>\n"
            "</tr>\n</table>\n"
        ;
    }

    return htm;
}

wxString rgCompareEvent::GetRefDatesTable()
{
    wxString htm;

    if( CreateDateImageFile() ) {
        htm << 
            "<table class='data diag'>\n"
            "<tr>\n"
            "<th colspan='2'>Date</th>\n"
            "<th colspan='2'>Reference Document</th>\n"
            "</tr>\n<tr>\n"
            "<td>" << m_date1.GetStr() << "</td>\n"
            "<td class='diag'><img src='memory:" << m_dateImageFN << "' alt=''></td>\n"
            "<td><b>" << m_event.GetIdStr() << "</b></td>\n"
            "<td></td>"
            "</tr>\n"
        ;
        for( size_t i = 0 ; i < m_reDate1s.size() ; i++ ) {
            htm << 
                "<tr>\n"
                "<td>" << m_reDate1s[i].GetStr() << "</td>\n"
                "<td class='diag'><img src='memory:" << m_dateImageFNs[i] << "' alt=''></td>\n"
                "<td><b><a href='tfp:R" << m_refIDs[i] <<
                "'>" << recReference::GetIdStr( m_refIDs[i] ) <<
                "</a>: <a href='tfp:ER" << m_refEvents[i].FGetID() <<
                "'>" << m_refEvents[i].GetIdStr() << "</a></b></td>\n"
                "<td>" << recReference::GetTitle( m_refIDs[i] ) << "</td>\n"
                "</tr>\n"
            ;
        }
        htm << "</table>\n";
    } else {
        htm << 
            "<table class='data'>\n<tr>\n"
            "<th>No Reference dates available</th>\n"
            "</tr>\n</table>\n"
        ;
    }

    return htm;
}

bool rgCompareEvent::CreateDateImageFile()
{
    if( m_reDate1s.size() == 0 ) return false;
    static long unique = 0;
    UnloadFiles();
    size_t i;
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
    wxString filename;
    filename << ++unique << "date.bmp";
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
        filename.clear();
        filename << ++unique << "date" << i << ".bmp";
        wxMemoryFSHandler::AddFile( filename, bitmap, wxBITMAP_TYPE_BMP );
        m_dateImageFNs.push_back( filename );
    }

    dc.SelectObject( wxNullBitmap );
    return true;
}

void rgCompareEvent::DrawDateImage( 
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

wxString rgCompareEvent::GetRefPlacesTable()
{
    wxString htm;

    if( m_rePlaces.size() ) {
        htm << 
            "<table class='data'>\n"
            "<tr>\n"
            "<th>Place</th>\n"
            "<th colspan='2'>Reference Document</th>\n"
            "</tr>\n<tr>\n"
            "<td>" << m_place.GetAddressStr() << "</td>\n"
            "<td><b>" << m_event.GetIdStr() << "</b></td>\n"
            "<td></td>"
            "</tr>\n"
        ;
        for( size_t i = 0 ; i < m_rePlaces.size() ; i++ ) {
            if( m_rePlaces[i].FGetID() == 0 ) continue;
            htm << 
                "<tr>\n"
                "<td>" << m_rePlaces[i].GetAddressStr() << "</td>\n"
                "<td><b><a href='tfp:R" << m_refIDs[i] <<
                "'>" << recReference::GetIdStr( m_refIDs[i] ) <<
                "</a>: <a href='tfp:ER" << m_refEvents[i].FGetID() <<
                "'>" << m_refEvents[i].GetIdStr() << "</a></b></td>\n"
                "<td>" << recReference::GetTitle( m_refIDs[i] ) << "</td>\n"
                "</tr>\n"
            ;
        }
        htm << "</table>\n";
    } else {
        htm << 
            "<table class='data'>\n<tr>\n"
            "<th>No Reference places available</th>\n"
            "</tr>\n</table>\n"
        ;
    }

    return htm;
}



void rgCompareEvent::UnloadFiles()
{
    if( !m_dateImageFN.IsEmpty() ) {
        wxMemoryFSHandler::RemoveFile( m_dateImageFN );
        m_dateImageFN = wxEmptyString;
    }
    for( size_t i = 0 ; i < m_dateImageFNs.size() ; i++ ) {
        wxMemoryFSHandler::RemoveFile( m_dateImageFNs[i] );
    }
    m_dateImageFNs.clear();
}


// End of src/rg/rgCompareEvent.cpp file.
