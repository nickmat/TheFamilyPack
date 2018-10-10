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


rgImagePanel::rgImagePanel( wxWindow* parent )
   : m_width(-1), m_height(-1), m_x(0), m_y(0),  wxPanel( parent )
{
    Bind( wxEVT_PAINT, &rgImagePanel::PaintEvent, this );
    Bind( wxEVT_SIZE, &rgImagePanel::OnSize, this );
}

bool rgImagePanel::SetImage( const wxMemoryBuffer& buf )
{
    wxMemoryInputStream stream( buf.GetData(), buf.GetDataLen() );
    m_image.LoadFile( stream, wxBITMAP_TYPE_JPEG );
    if ( m_image.Ok() ) {
        return true;
    }
    return false;
}

bool rgImagePanel::SetImage( const recMedia& med )
{
    assert( med.FGetAssID() == 0 ); // Don't use external data yet.
    recMediaData md( med.FGetID() );
    return SetImage( md.FGetData() );
}

void rgImagePanel::PaintEvent( wxPaintEvent& evt )
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc( this );
    Render( dc );
}

void rgImagePanel::Render( wxDC& dc )
{
    int neww, newh;
    dc.GetSize( &neww, &newh );

    if ( neww != m_width || newh != m_height )
    {
        int h = m_image.GetHeight();
        int w = m_image.GetWidth();
        double scale = 1.0;
        if ( h > newh ) {
            scale = double( newh ) / h;
        }
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
        m_resized = wxBitmap( m_image.Scale( m_width, m_height /*, wxIMAGE_QUALITY_HIGH*/ ) );
    }
    dc.DrawBitmap( m_resized, m_x, m_y, false );
}

void rgImagePanel::OnSize( wxSizeEvent& event ) {
    Refresh();
    event.Skip();
}


// End of src/rg/rgImagePanel.cpp file

