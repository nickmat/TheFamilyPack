/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgViewMedia.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     View Media (Image) dialog header.
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

#ifndef SRC_RG_RGVIEWMEDIA_H
#define SRC_RG_RGVIEWMEDIA_H

#include <rec/recMedia.h>
#include <rec/recMediaData.h>

#include "fb/fbRgViewMedia.h"

class rgViewMediaFrame : public fbRgViewMedia
{
public:
    rgViewMediaFrame( wxWindow* parent, const wxString& extdb, idt medID );
    rgViewMediaFrame( wxWindow* parent, idt mdID, idt assID );
    rgViewMediaFrame( wxWindow* parent, idt mdID, const wxString& dbname );

    void SetToolbarScale( double scale );

private:
    void EnableScroll( bool enable );
    double ThumbToScale( int thumb );
    int ScaleToThumb( double scale );

    void OnChangeScale( rgImageScaleEvent& event );
    // Virtual event handlers
    void OnCheckScroll( wxCommandEvent& event ) override;
    void OnZoomSlider( wxScrollEvent& event ) override;
    void OnButtonPlus( wxCommandEvent& event ) override;
    void OnButtonMinus( wxCommandEvent& event ) override;
    void OnSetZoom( wxCommandEvent& event ) override;
    void OnButton100Percent( wxCommandEvent& event ) override;
    void OnButtonExport( wxCommandEvent& event ) override;
    void OnButtonPrint( wxCommandEvent& event ) override;

    recMediaData m_mediadata;
    recMedia m_media;
    bool     m_scrollEnabled;
    double   m_upper;
    // below are constants based on m_upper
    double   m_lower; // 1 / m_upper
    double   m_b;     // m_upper * m_upper
    double   m_k;     // log10( m_b )
    int       m_prevThumb;
    const int m_stepThumb = 5;
};

#endif // SRC_RG_RGVIEWMEDIA_H
