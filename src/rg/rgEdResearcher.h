/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Researcher dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th January 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#ifndef RGEDRESEARCHER_H
#define RGEDRESEARCHER_H

#include <rec/recContact.h>
#include <rec/recUser.h>

#include "fbRgDialog.h"

class rgDlgEditResearcher : public fbRgEditResearcher
{
    enum Columns {
        COL_ConID, COL_Type, COL_Value, COL_MAX
    };
public:
    rgDlgEditResearcher( wxWindow* parent, idt resID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void AddIndLink();
    void OnOptnChange( wxCommandEvent& event );
    void OnOptnUnlink( wxCommandEvent& event );

    void OnButtonInd( wxCommandEvent& event );
    void OnButtonAdd( wxCommandEvent& event );
    void OnButtonEdit( wxCommandEvent& event );
    void OnButtonDelete( wxCommandEvent& event );


    recResearcher  m_researcher;
    recUser        m_user;
    recContactList m_list;
    recContactVec  m_contacts;
};

#endif // RGEDRESEARCHER_H
