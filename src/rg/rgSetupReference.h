/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSetupReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Setup Creation of database Reference entity header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     23rd August 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#ifndef RGSETUPREFERENCE_H
#define RGSETUPREFERENCE_H

#include <rec/recReference.h>

#include "fb/fbRgSetupReference.h"

//============================================================================
//-------------------------[ rgDlgSetupReference ]-----------------------------
//============================================================================

class rgDlgSetupReference : public fbRgSetupReferenceDialog
{
public:
    /** Constructor */
    rgDlgSetupReference( wxWindow* parent, idt refID );

private:
    enum MediaColumn {
        MED_COL_Number, MED_COL_Title, MED_COL_MAX
    };

    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void UpdateMedias( idt medID = 0 );

    void OnMediaDeselect( wxListEvent& event ) override;
    void OnMediaSelect( wxListEvent& event ) override;
    void OnMediaAddButton( wxCommandEvent& event ) override;
    void OnAddNewMedia( wxCommandEvent& event ) override;
    void OnAddExistingMedia( wxCommandEvent& event ) override;
    void OnMediaEditButton( wxCommandEvent& event ) override;
    void OnMediaDeleteButton( wxCommandEvent& event ) override;
    void OnMediaView( wxCommandEvent& event ) override;
    void OnTemplateBrowse( wxCommandEvent& event ) override;

    recReference  m_reference;
    recIdVec      m_mediaIDs;
    wxString      m_template;
};

#endif // RGSETUPREFERENCE_H
