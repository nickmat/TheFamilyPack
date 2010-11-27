/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdName.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 November 2010
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

#ifndef DLGEDNAME_H
#define DLGEDNAME_H

#include <rec/recName.h>

#include "fbDlg.h"

class dlgEditName : public fbDlgEditName
{
    enum Columns {
        COL_Type, COL_Value, COL_MAX
    };
public:
    dlgEditName( wxWindow* parent );

    void SetData( id_t nameID = 0 ) { m_name.f_id = nameID; }
    void SetDefault( wxString& name ) {
        m_haveName = true; m_nameStr = name;
    }

    recName* GetName() { return &m_name; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnNameAddButton( wxCommandEvent& event );
    void OnNameEditButton( wxCommandEvent& event );
    void OnNameDeleteButton( wxCommandEvent& event );
    void OnNameUpButton( wxCommandEvent& event );
    void OnNameDownButton( wxCommandEvent& event );

    bool              m_haveName; // was m_defaultAttr
    wxString          m_nameStr;

    recName           m_name;
    recNamePartVec    m_parts;
    recNameStyleVec   m_styles;
};

#endif // DLGEDNAME_H
