/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdName.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name entity dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#include "fb/fbRgEditName.h"

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

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void UpdateName();

    void OnPartAddButton( wxCommandEvent& event );
    void OnPartEditButton( wxCommandEvent& event );
    void OnPartDeleteButton( wxCommandEvent& event );
    void OnPartUpButton( wxCommandEvent& event );
    void OnPartDownButton( wxCommandEvent& event );

    recName           m_name;
    recNamePartVec    m_parts;
    recNameStyleVec   m_types;
};

#endif // RGEDNAME_H
