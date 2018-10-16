/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgViewMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     View Media (Image) dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10 October 2018
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

#include "rg/rgDialogs.h"
#include "rgViewMedia.h"

#include <wx/colour.h>

void rgViewMedia( wxWindow* wind, idt medID )
{
    wxASSERT( medID != 0 );
    rgViewMediaForm* frame = new rgViewMediaForm( wind, medID );
    frame->SetBackgroundColour( *wxWHITE );
    frame->Show();
}

//============================================================================
//-------------------------[ rgViewMediaForm ]--------------------------------
//============================================================================

rgViewMediaForm::rgViewMediaForm( wxWindow* parent, idt medID )
    : m_media(medID), m_scrollEnabled(false), m_upper(10), fbRgViewMedia( parent )
{
    Bind( rgEVT_IMAGE_SCALE, &rgViewMediaForm::OnChangeScale, this );
    Bind( wxEVT_SLIDER, &rgViewMediaForm::OnZoomSlider, this );
    m_lower = 1 / m_upper;
    m_b = m_upper * m_upper;
    m_k = std::log10( m_b );
    m_imageViewer->SetImage( m_media );
    EnableScroll( false );
}

void rgViewMediaForm::SetScale( double scale )
{
    wxString scalestr = wxString::Format( "%.1f", scale * 100 );
    if ( scale > m_upper ) {
        SetScale( m_upper );
        return;
    }
    if ( scale < m_lower ) {
        SetScale( m_lower );
        return;
    }
    m_textCtrlZoom->SetValue( scalestr );
    int thumb = double( 100 ) *( std::log10( scale ) / m_k + 0.5 );
    m_sliderZoom->SetValue( thumb );

}

void rgViewMediaForm::EnableScroll( bool enable )
{
    m_scrollEnabled = enable;
    m_buttonPlus->Enable( enable );
    m_sliderZoom->Enable( enable );
    m_buttonMinus->Enable( enable );
    m_textCtrlZoom->Enable( enable );
    m_button100Percent->Enable( enable );
    m_buttonExport->Enable( enable );
    m_buttonPrint->Enable( enable );
}

void rgViewMediaForm::OnChangeScale( rgImageScaleEvent & event )
{
    SetScale( event.GetScale() );
}

void rgViewMediaForm::OnZoomSlider( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnZoomSlider" );
}

void rgViewMediaForm::OnCheckScroll( wxCommandEvent& event )
{
    if ( !m_scrollEnabled ) {
        wxMessageBox( _( "Scroll view not yet implimented" ), "OnButtonPlus" );
    }
    EnableScroll( !m_scrollEnabled );
}

void rgViewMediaForm::OnButtonPlus( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonPlus" );
}

void rgViewMediaForm::OnButtonMinus( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonMinus" );
}

void rgViewMediaForm::OnSetZoom( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnSetZoom" );
}

void rgViewMediaForm::OnButton100Percent( wxCommandEvent& event )
{
    SetScale( 1.0 );
    wxMessageBox( _( "Not yet implimented" ), "OnSetZoom" );
}

void rgViewMediaForm::OnButtonExport( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonExport" );
}

void rgViewMediaForm::OnButtonPrint( wxCommandEvent& event )
{
    wxMessageBox( _( "Not yet implimented" ), "OnButtonPrint" );
}


// End of src/rg/rgViewMedia.cpp file
