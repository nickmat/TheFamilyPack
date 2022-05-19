/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdRepository.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit Repository dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     18th May 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef RGEDREPOSITORY_H
#define RGEDREPOSITORY_H

#include "fb/fbRgEditCitation.h"
#include "rgSelect.h"

#include <rec/recCitation.h>
#include <rec/recContact.h>


//============================================================================
//-------------------------[ rgDlgEditRepository ]----------------------------
//============================================================================

class rgDlgEditRepository : public fbRgEditRepository
{
    enum Columns {
        COL_ConID, COL_Type, COL_Value, COL_MAX
    };
public:
    rgDlgEditRepository( wxWindow* parent, idt resID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void UpdateContacts( idt conID );

    void ContactButtonsEnable( int row );
    void OnContactDeselected( wxListEvent& event ) override;
    void OnContactSelected( wxListEvent& event ) override;
    void OnButtonAdd( wxCommandEvent& event ) override;
    void OnButtonEdit( wxCommandEvent& event ) override;
    void OnButtonDelete( wxCommandEvent& event ) override;
    void OnButtonUp( wxCommandEvent& event ) override;
    void OnButtonDown( wxCommandEvent& event ) override;

    recRepository  m_archive;
    recContactList m_list;
    recContactVec  m_contacts;
};


//============================================================================
//--------------------------[ rgDlgSelectArchive ]----------------------------
//============================================================================

class rgDlgSelectArchive : public rgSelect
{
    enum {
        COL_ID, COL_Name, COL_comment, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectArchive(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _( "Select Archive" )
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};


#endif // RGEDREPOSITORY_H
