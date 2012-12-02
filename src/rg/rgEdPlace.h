/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPlace.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Place dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#ifndef RGEDPLACE_H
#define RGEDPLACE_H

#include <rec/recPlace.h>

#include "fbRgDialog.h"

class rgDlgEditPlace : public fbRgEditPlace
{
public:
    rgDlgEditPlace( wxWindow* parent, idt placeID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recPlace     m_place;
    recPlacePart m_pp;
};

#endif // RGEDPLACE_H
