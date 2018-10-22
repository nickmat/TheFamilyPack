/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Name:        src/rg/rgImagePanel.cpp
* Project:     The Family Pack: Genealogy data storage and display program.
* Purpose:     An Image Panel to display Media objects.
* Author:      Nick Matthews
* Website:     http://thefamilypack.org
* Created:     2nd October 2018
* Copyright:   Copyright (c) 2018, Nick Matthews.
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

#include "rgImagePanel.h"

#include <wx/mstream.h>

#include <rec/recMedia.h>
#include <rec/recMediaData.h>


wxDEFINE_EVENT( rgEVT_IMAGE_SCALE, rgImageScaleEvent );

rgImagePanel::rgImagePanel( wxWindow* parent )
    : m_parent( parent ), m_scroll(false), m_width( -1 ), m_height( -1 ), m_x( 0 ), m_y( 0 ),
    wxScrolledCanvas( parent )
{
    SetScrollRate( 10, 10 );
    SetBackgroundColour( *wxWHITE );
    Bind( wxEVT_PAINT, &rgImagePanel::OnPaint, this );
    Bind( wxEVT_SIZE, &rgImagePanel::OnSize, this );
}

bool rgImagePanel::SetImage( const wxMemoryBuffer& buf )
{
    wxMemoryInputStream stream( buf.GetData(), buf.GetDataLen() );
    m_image.LoadFile( stream, wxBITMAP_TYPE_JPEG );
    if ( !m_image.Ok() ) {
        return false;
    }
    m_width = m_image.GetWidth();
    m_height = m_image.GetHeight();
    m_bitmap = wxBitmap( m_image );
    if ( m_scroll ) {
        SetVirtualSize( m_bitmap.GetWidth(), m_bitmap.GetHeight() );
    } else {
        SetVirtualSize( 0, 0 );
    }
    return true;
}

bool rgImagePanel::SetImage( const recMedia& med )
{
    assert( med.FGetAssID() == 0 ); // Don't use external data yet.
    recMediaData md( med.FGetID() );
    return SetImage( md.FGetData() );
}

void rgImagePanel::SetScrollMode( bool scroll )
{
    if ( scroll == m_scroll ) {
        return;
    }
    m_scroll = scroll;
    if ( !m_bitmap.IsOk() ) {
        return;
    }
    if ( scroll ) {
        SetVirtualSize( m_bitmap.GetWidth(), m_bitmap.GetHeight() );
    } else {
        SetVirtualSize( 0, 0 );
    }
    Refresh();
}

void rgImagePanel::OnPaint( wxPaintEvent& evt )
{
    wxPaintDC dc( this );
    Render( dc );
}

void rgImagePanel::OnSize( wxSizeEvent& event )
{
    Refresh();
    event.Skip();
}

void rgImagePanel::Render( wxDC& dc )
{
    int neww, newh;
    dc.GetSize( &neww, &newh );
    if ( !m_scroll && ( neww != m_width || newh != m_height ) )
    {
        int h = m_image.GetHeight();
        int w = m_image.GetWidth();
        double scale = double( newh ) / h;
        m_width = scale * w;
        if ( m_width > neww ) {
            scale = double( neww ) / w;
            m_width = scale * w;
        }
        m_height = scale * h;
        if ( m_width < 1 ) {
            m_width = 1;
        }
        if ( m_height < 1 ) {
            m_height = 1;
        }
        m_x = ( neww - m_width ) / 2;
        m_y = ( newh - m_height ) / 2;
        m_bitmap = wxBitmap( m_image.Scale( m_width, m_height ) );

        rgImageScaleEvent event;
        event.SetScale( scale );
        wxPostEvent( m_parent, event );
    } else if ( m_scroll ) {
        PrepareDC( dc );
        m_x = ( neww > m_width ) ? ( neww - m_width ) / 2 : 0;
        m_y = ( newh > m_height ) ? ( newh - m_height ) / 2 : 0;
    }
    dc.DrawBitmap( m_bitmap, m_x, m_y, false );
}

// End of src/rg/rgImagePanel.cpp file
