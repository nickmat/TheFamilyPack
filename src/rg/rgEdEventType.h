/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventType record dialog header, GUI only.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
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

#ifndef RGEDEVENTTYPE_H
#define RGEDEVENTTYPE_H

#include <rec/recEvent.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgEditEventType ]-----------------------------
//============================================================================

class rgDlgEditEventType : public fbRgEditEventType
{
    enum RoleCols {
        RC_Number, RC_Name, RC_Prime, RC_Official, RC_MAX
    };

public:
    rgDlgEditEventType( wxWindow* parent, idt etID );
   
private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

	void OnButtonRoleAdd( wxCommandEvent& event );
	void OnButtonRoleEdit( wxCommandEvent& event );
	void OnButtonRoleDelete( wxCommandEvent& event );

    recEventType        m_et;
    recEventTypeRoleVec m_roles;
};

#endif // RGEDEVENTTYPE_H
