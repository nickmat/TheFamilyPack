/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdNamePart.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name Part entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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

#ifndef RGEDNAMEPART_H
#define RGEDNAMEPART_H

#include <rec/recName.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgEditNamePart ]------------------------------
//============================================================================

class dlgEditNamePart : public fbRgEditNamePart
{
public:
    dlgEditNamePart( wxWindow* parent, idt npID )
        : m_np(npID), fbRgEditNamePart( parent )
    {}

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recNamePart         m_np;
    recNamePartTypeVec  m_types;
};

#endif // RGEDNAMEPART_H
