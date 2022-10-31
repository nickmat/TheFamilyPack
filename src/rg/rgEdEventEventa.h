/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventEventa.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventEventa record dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7th May 2013
 * Copyright:   Copyright (c) 2013-2015, Nick Matthews.
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

#ifndef RG_RGEDEVENTEVENTA_H
#define RG_RGEDEVENTEVENTA_H

#include <rec/recEventa.h>

#include "fb/fbRgEditEventa.h"

//============================================================================
//--------------------------[ rgDlgEditEventEventa ]--------------------------
//============================================================================

class rgDlgEditEventEventa : public fbRgEditEventEventa
{
public:
    rgDlgEditEventEventa( wxWindow* parent, idt eerID )
        : m_eer(eerID), fbRgEditEventEventa( parent ) {}

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recEventEventa m_eer;
};

#endif // RG_RGEDEVENTEVENTA_H
