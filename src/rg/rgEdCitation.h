/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdCitation.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit Citation Record dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th November 2021
 * Copyright:   Copyright (c) 2021..2022 Nick Matthews.
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

#ifndef RGEDCITATION_H
#define RGEDCITATION_H

#include "fb/fbRgEditCitation.h"

#include <rec/recCitation.h>


//============================================================================
//--------------------------[ rgDlgEditCitation ]-----------------------------
//============================================================================

class rgDlgEditCitation : public fbRgEditCitation
{
    enum PartColumns {
        PC_citID, PC_value, PC_type, PC_comment, PC_MAX
    };
public:
    rgDlgEditCitation( wxWindow* parent, idt citID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void UpdateCitation();
    void UpdateArchive();
    void UpdatePartList( idt cpID );

    void PartsButtonsEnable( long row );
    void OnButtonSelectExtends( wxCommandEvent& event ) override;
    void OnButtonRepository( wxCommandEvent& event ) override;
    void OnSelectRepository( wxCommandEvent& event ) override;
    void OnEditRepository( wxCommandEvent& event ) override;
    void OnPartDeselect( wxListEvent& event ) override;
    void OnPartSelect( wxListEvent& event ) override;
    void OnButtonAdd( wxCommandEvent& event ) override;
    void OnButtonEdit( wxCommandEvent& event ) override;
    void OnButtonDelete( wxCommandEvent& event ) override;
    void OnButtonUp( wxCommandEvent& event ) override;
    void OnButtonDown( wxCommandEvent& event ) override;

    recCitation        m_citation;
    recRepository      m_archive;
    recCitationPartVec m_parts;
};



#endif // RGEDCITATION_H
