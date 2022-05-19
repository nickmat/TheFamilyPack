/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdCitPartType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit CitationPartType dialog header.
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

#ifndef RGEDCITPARTTYPE_H
#define RGEDCITPARTTYPE_H

#include "fb/fbRgEditCitation.h"

#include <rec/recCitation.h>

//============================================================================
//----------------------[ rgDlgEditCitationPartType ]-------------------------
//============================================================================

class rgDlgEditCitationPartType : public fbRgEditCitationPartType
{
public:
    rgDlgEditCitationPartType( wxWindow* parent, idt ciptID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recCitationPartType  m_type;
};


#endif // RGEDCITPARTTYPE_H
