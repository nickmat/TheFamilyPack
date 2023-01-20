/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventType record dialog header, GUI only.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
 * Copyright:   Copyright (c) 2012..2023, Nick Matthews.
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

#include "fb/fbRgEditEventRole.h"

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

    void UpdateRoleList( idt roleID );

    void RoleButtonsEnable( long row );
    void OnRoleSelect( wxListEvent& event ) override;
    void OnRoleDeselect( wxListEvent& event ) override;
    void OnButtonRoleAdd( wxCommandEvent& event ) override;
	void OnButtonRoleEdit( wxCommandEvent& event ) override;
	void OnButtonRoleDelete( wxCommandEvent& event ) override;

    recEventType        m_et;
    recEventTypeRoleVec m_roles;
};

#endif // RGEDEVENTTYPE_H
