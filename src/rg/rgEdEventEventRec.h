/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventEventRec.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventEventRecord record dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7th May 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#ifndef RG_RGEDEVENTEVENTREC_H
#define RG_RGEDEVENTEVENTREC_H

#include <rec/recEventRecord.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgEditEventEventRec ]-------------------------
//============================================================================

class rgDlgEditEventEventRec : public fbRgEditEventEventRec
{
public:
    rgDlgEditEventEventRec( wxWindow* parent, idt eerID )
        : m_eer(eerID), fbRgEditEventEventRec( parent ) {}
   
private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recEventEventRecord m_eer;
};

#endif // RG_RGEDEVENTEVENTREC_H
