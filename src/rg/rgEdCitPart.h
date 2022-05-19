/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdCitPart.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit CitationPart dialog header.
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

#ifndef RGEDCITPART_H
#define RGEDCITPART_H

#include "fb/fbRgEditCitation.h"

#include <rec/recCitation.h>


//============================================================================
//------------------------[ rgDlgEditCitationPart ]---------------------------
//============================================================================

class rgDlgEditCitationPart : public fbRgEditCitationPart
{
public:
    rgDlgEditCitationPart( wxWindow* parent, idt cipID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void UpdatePartType( idt ciptID );

    void OnAddEditButton( wxCommandEvent& event ) override;
    void OnAddType( wxCommandEvent& event ) override;
    void OnEditType( wxCommandEvent& event ) override;

    recCitationPart        m_part;
    recCitationPartTypeVec m_types;
};


#endif // RGEDCITPART_H
