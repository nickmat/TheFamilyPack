/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Researcher dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     4 April 2012
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

#ifndef DLGEDRESEARCHER_H
#define DLGEDRESEARCHER_H

#include <rec/recContact.h>
#include <rec/recUser.h>

#include "fbDlg.h"

class dlgEditResearcher : public fbDlgEditResearcher
{
    enum Columns {
        COL_ConID, COL_Type, COL_Value, COL_MAX
    };
public:
    dlgEditResearcher( wxWindow* parent, idt resID );

    recResearcher* GetResearcher() { return &m_researcher; }
    recUser* GetUser() { return &m_user; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnButtonClickAdd( wxCommandEvent& event );
    void OnButtonClickEdit( wxCommandEvent& event );
    void OnButtonClickDelete( wxCommandEvent& event );

    recResearcher     m_researcher;
    recUser           m_user;
    recContactVec     m_styles;
};

#endif // DLGEDRESEARCHER_H
