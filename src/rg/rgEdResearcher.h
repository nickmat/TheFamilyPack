/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdResearcher.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Researcher dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th January 2013
 * Copyright:   Copyright (c) 2013 .. 2021, Nick Matthews.
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

#include <rec/recResearcher.h>
#include <rec/recUser.h>

#include "fb/fbRgEditResearcher.h"
#include "rgSelect.h"

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
    void UpdateIndividual();
    void UpdateContacts( idt conID );

    void OnIndButton( wxCommandEvent& event ) override;

    void ContactButtonsEnable( int row );
    void OnContactDeselected( wxListEvent& event ) override;
    void OnContactSelected( wxListEvent& event ) override;
    void OnButtonAdd( wxCommandEvent& event ) override;
    void OnButtonEdit( wxCommandEvent& event ) override;
    void OnButtonDelete( wxCommandEvent& event ) override;

    recResearcher  m_researcher;
    recContactList m_list;
    recContactVec  m_contacts;
    idt            m_userID;
    idt            m_currentUserID;
};

//============================================================================
//-------------------------[ rgDlgSelectResearcher ]--------------------------
//============================================================================

class rgDlgSelectResearcher : public rgSelect
{
    enum {
        COL_ID, COL_Name, COL_comment, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectResearcher(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _( "Select Researcher" )
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};


#endif // RGEDRESEARCHER_H
