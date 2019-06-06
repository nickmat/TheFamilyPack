/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rg/rgImagePanel.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     An Image Panel to display Media objects.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     2nd October 2018
 * Copyright:   Copyright (c) 2018 ~ 2019, Nick Matthews.
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

#ifndef INCLUDE_RG_RGIMAGEPANEL_H
#define INCLUDE_RG_RGIMAGEPANEL_H

#include <wx/panel.h>

#include <rec/recHelper.h>

class recMedia;

class rgImagePanel : public wxScrolledCanvas
{
public:
    rgImagePanel( wxWindow* parent );

    bool SetImage( const wxMemoryBuffer& buf );
    void SetScrollMode( bool scroll );

    void SetScale( double scale );

private:
    void OnPaint( wxPaintEvent& evt );
    void OnSize( wxSizeEvent& event );
    void Render( wxDC& dc );

    wxWindow* m_parent;
    wxImage  m_image;
    bool     m_scroll;
    int      m_width;
    int      m_height;
    wxBitmap m_bitmap;
    int      m_x;
    int      m_y;
};

class rgImageScaleEvent;
wxDECLARE_EVENT( rgEVT_IMAGE_SCALE, rgImageScaleEvent );

class rgImageScaleEvent : public wxCommandEvent
{
public:
    rgImageScaleEvent( wxEventType commandType = rgEVT_IMAGE_SCALE, int id = 0 )
        : wxCommandEvent( commandType, id ) { }

    // You *must* copy here the data to be transported
    rgImageScaleEvent( const rgImageScaleEvent& event )
        : wxCommandEvent( event ) {
        this->SetScale( event.GetScale() );
    }

    // Required for sending with wxPostEvent()
    wxEvent* Clone() const { return new rgImageScaleEvent( *this ); }

    double GetScale() const { return m_scale; }
    void SetScale( double scale ) { m_scale = scale; }

private:
    double m_scale;
};


#endif // INCLUDE_RG_RGIMAGEPANEL_H
