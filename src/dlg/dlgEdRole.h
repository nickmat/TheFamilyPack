/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdRole.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Event Role entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22 October 2010
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

#ifndef DLGEDROLE_H
#define DLGEDROLE_H

#include <rec/recEvent.h>

#include "fbDlg.h"
#include "dlgEdReference.h"

class dlgEditRole : public fbDlgEditRole
{
    DECLARE_CLASS( dlgEditRole )
    DECLARE_EVENT_TABLE()

public:
	dlgEditRole( wxWindow* parent, id_t eventID, id_t id = 0 );

    void SetEntities( TfpEntities* entities ) { m_entities = entities; }

    recPersonaEvent* GetPersonaEvent() { return &m_pe; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

	void OnPersonaButton( wxCommandEvent& event );
    void OnPersonaSelect( wxCommandEvent& event );
    void OnRoleButton( wxCommandEvent& event );
    void OnRoleSelect( wxCommandEvent& event );

    recPersonaEvent  m_pe;
    recEvent         m_event;

    TfpEntities*        m_entities;
    recEventTypeRoleVec m_roles;
};

#endif // DLGEDROLE_H
