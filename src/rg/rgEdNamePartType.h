/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdNamePartType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit NamePartType dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21st May 2022
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

#ifndef RGEDNAMEPARTTYPE_H
#define RGEDNAMEPARTTYPE_H

#include "fb/fbRgEditName.h"

#include <rec/recName.h>

//============================================================================
//------------------------[ rgDlgEditNamePartType ]---------------------------
//============================================================================

class rgDlgEditNamePartType : public fbRgEditNamePartType
{
public:
    rgDlgEditNamePartType( wxWindow* parent, idt nptID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recNamePartType  m_type;
};


#endif // RGEDNAMEPARTTYPE_H