/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgImagePanel.h
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

#ifndef SRC_RG_RGIMAGEPANEL_H
#define SRC_RG_RGIMAGEPANEL_H

#include <wx/panel.h>

#include <rec/recHelper.h>


class rgImagePanel : public wxPanel
{
public:
    rgImagePanel( wxWindow* parent );

    bool SetImage( const wxMemoryBuffer& buf );

private:
    void PaintEvent( wxPaintEvent& evt );
    void OnSize( wxSizeEvent& event );
    void Render( wxDC& dc );

    wxImage  m_image;
    int      m_width;
    int      m_height;
    wxBitmap m_resized;
    int      m_x;
    int      m_y;
};

#endif // SRC_RG_RGIMAGEPANEL_H