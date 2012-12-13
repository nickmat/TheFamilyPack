/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdName.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
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

#ifndef RGEDNAME_H
#define RGEDNAME_H

#include <rec/recName.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgEditName ]----------------------------------
//============================================================================

class rgDlgEditName : public fbRgEditName
{
    enum Columns {
        COL_ID, COL_Type, COL_Value, COL_MAX
    };
public:
    rgDlgEditName( wxWindow* parent, idt nameID );

//    void SetData( idt nameID = 0 ) { m_name.f_id = nameID; }
//    void SetDefault( wxString& name ) {
//        m_haveName = true; m_nameStr = name;
//    }

//    void SetID( idt nameID ) { m_name.f_id = nameID; }
//    void SetPersonaID( idt perID ) { m_name.f_per_id = perID; }
//    void CreateName( const wxString name ) {
//        m_haveName = true; m_nameStr = name;
//    }

//    recName* GetName() { return &m_name; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void UpdateName();

//    void OnPersonaButton( wxCommandEvent& event );
    void OnPartAddButton( wxCommandEvent& event );
    void OnPartEditButton( wxCommandEvent& event );
    void OnPartDeleteButton( wxCommandEvent& event );
    void OnPartUpButton( wxCommandEvent& event );
    void OnPartDownButton( wxCommandEvent& event );

//    bool              m_haveName; // was m_defaultAttr
//    wxString          m_nameStr;

    recName           m_name;
    recNamePartVec    m_parts;
    recNameStyleVec   m_types;
};

#endif // RGEDNAME_H
