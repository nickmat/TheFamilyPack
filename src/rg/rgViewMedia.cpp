/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgViewMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     View Media (Image) dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10 October 2018
 * Copyright:   Copyright (c) 2018..2022, Nick Matthews.
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

#include "rg/rgDialogs.h"
#include "rgViewMedia.h"

#include <wx/colour.h>


void rgViewMedia( wxWindow* wind, const wxString& extdb, idt medID )
{
    wxASSERT( medID != 0 );
    rgViewMediaFrame* frame = new rgViewMediaFrame( wind, extdb, medID );
    frame->SetBackgroundColour( *wxWHITE );
    frame->Show();
}

void rgViewMedia( wxWindow* wind, idt mdID, idt assID )
{
    rgViewMediaFrame* frame = new rgViewMediaFrame( wind, mdID, assID );
    frame->SetBackgroundColour( *wxWHITE );
    frame->Show();
}

void rgViewMedia( wxWindow* wind, idt mdID, const wxString& dbname )
{
    rgViewMediaFrame* frame = new rgViewMediaFrame( wind, mdID, dbname );
    frame->SetBackgroundColour( *wxWHITE );
    frame->Show();
}


//============================================================================
//-------------------------[ rgViewMediaForm ]--------------------------------
//============================================================================

rgViewMediaFrame::rgViewMediaFrame( wxWindow* parent, const wxString& extdb, idt medID )
    : m_media( medID, extdb ), m_scrollEnabled(false), m_upper(4), m_prevThumb(-1),
    fbRgViewMedia( parent )
{
    m_mediadata.ReadID( m_media.FGetDataID(), m_media.FGetAssID(), extdb );
    Bind( rgEVT_IMAGE_SCALE, &rgViewMediaFrame::OnChangeScale, this );
    m_lower = 1 / m_upper;
    m_b = m_upper * m_upper;
    m_k = std::log10( m_b );
    m_imageViewer->SetImage( m_mediadata.FGetData() );
    EnableScroll( false );
}

rgViewMediaFrame::rgViewMediaFrame( wxWindow * parent, idt mdID, idt assID )
    : m_media( recMediaData::FindMedia(mdID, assID) ), m_mediadata(mdID, assID),
    m_scrollEnabled( false ), m_upper( 4 ), m_prevThumb( -1 ),
    fbRgViewMedia( parent )
{
    Bind( rgEVT_IMAGE_SCALE, &rgViewMediaFrame::OnChangeScale, this );
    m_lower = 1 / m_upper;
    m_b = m_upper * m_upper;
    m_k = std::log10( m_b );
    m_imageViewer->SetImage( m_mediadata.FGetData() );
    EnableScroll( false );
}

rgViewMediaFrame::rgViewMediaFrame( wxWindow* parent, idt mdID, const wxString& dbname )
    : m_media(0), m_mediadata(mdID,dbname),
    m_scrollEnabled( false ), m_upper( 4 ), m_prevThumb( -1 ),
    fbRgViewMedia( parent )
{
    Bind( rgEVT_IMAGE_SCALE, &rgViewMediaFrame::OnChangeScale, this );
    m_lower = 1 / m_upper;
    m_b = m_upper * m_upper;
    m_k = std::log10( m_b );
    m_imageViewer->SetImage( m_mediadata.FGetData() );
    EnableScroll( false );
}
void rgViewMediaFrame::SetToolbarScale( double scale )
{
    wxString scalestr = wxString::Format( "%.1f", scale * 100 );
    m_textCtrlZoom->SetValue( scalestr );
    int thumb = ScaleToThumb( scale );
    m_sliderZoom->SetValue( thumb );
    m_prevThumb = thumb;
}

void rgViewMediaFrame::EnableScroll( bool enable )
{
    m_scrollEnabled = enable;
    m_buttonPlus->Enable( enable );
    m_sliderZoom->Enable( enable );
    m_buttonMinus->Enable( enable );
    m_staticTextZoom->Enable( enable );
    m_textCtrlZoom->Enable( enable );
    m_button100Percent->Enable( enable );
}

double rgViewMediaFrame::ThumbToScale( int thumb )
{
    return std::pow( m_b, ( double( thumb ) / 100 ) - 0.5 );
}

int rgViewMediaFrame::ScaleToThumb( double scale )
{
    return double( 100 ) *( std::log10( scale ) / m_k + 0.5 );
}

void rgViewMediaFrame::OnChangeScale( rgImageScaleEvent & event )
{
    SetToolbarScale( event.GetScale() );
}

void rgViewMediaFrame::OnZoomSlider( wxScrollEvent& event )
{
    int thumb = event.GetInt();
    if ( thumb == m_prevThumb ) {
        return; // Ignore if nothing changes
    }
    double scale = ThumbToScale( thumb );
    m_imageViewer->SetScale( scale );
}

void rgViewMediaFrame::OnCheckScroll( wxCommandEvent& event )
{
    bool scroll = ( event.GetInt() != 0 );
    m_imageViewer->SetScrollMode( scroll );
    EnableScroll( scroll );
}

void rgViewMediaFrame::OnButtonPlus( wxCommandEvent& event )
{
    int thumb = m_sliderZoom->GetValue() + m_stepThumb;
    if( thumb > 100 ){
        thumb = 100;
    }
    if ( thumb == m_prevThumb ) {
        return; // Ignore if nothing changes
    }
    double scale = ThumbToScale( thumb );
    m_imageViewer->SetScale( scale );
}

void rgViewMediaFrame::OnButtonMinus( wxCommandEvent& event )
{
    int thumb = m_sliderZoom->GetValue() - m_stepThumb;
    if ( thumb < 0 ) {
        thumb = 0;
    }
    if ( thumb == m_prevThumb ) {
        return; // Ignore if nothing changes
    }
    double scale = ThumbToScale( thumb );
    m_imageViewer->SetScale( scale );
}

void rgViewMediaFrame::OnSetZoom( wxCommandEvent& event )
{
    wxString zoomStr = m_textCtrlZoom->GetValue();
    double zoom;
    if ( zoomStr.ToDouble( &zoom ) ) {
        double scale = zoom / 100;
        m_imageViewer->SetScale( scale );
    }
}

void rgViewMediaFrame::OnButton100Percent( wxCommandEvent& event )
{
    m_imageViewer->SetScale( 1.0 );
}

void rgViewMediaFrame::OnButtonExport( wxCommandEvent& event )
{
    wxString caption = _( "Save Image" );
    wxString wildcard = _( "JPEG (*.jpg)|*." );
    wxString defaultDir = ".";

    wxFileName fn( m_mediadata.FGetFile() );
    fn.SetExt( "jpg" );
    wxString defaultFName = fn.GetFullName();

    wxFileDialog dialog(
        this, caption, defaultDir, defaultFName, wildcard,
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );
    if( dialog.ShowModal() == wxID_OK ) {
        m_mediadata.ExportData( dialog.GetPath() );
    }
}

void rgViewMediaFrame::OnButtonPrint( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonPrint" );
}

// End of src/rg/rgViewMedia.cpp file
