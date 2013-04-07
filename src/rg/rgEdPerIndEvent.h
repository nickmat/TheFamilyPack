/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPerIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventPersona or IndividualEvent record dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     23 November 2012
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

#ifndef RGEDPERINDEVENT_H
#define RGEDPERINDEVENT_H

#include <rec/recEvent.h>

#include "rg/rgDialogs.h"

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgIndEvent ]----------------------------------
//============================================================================

class rgDlgIndEvent : public fbRgPerIndEvent
{
public:
    rgDlgIndEvent( wxWindow* parent, idt ieID, rgSHOWROLE filter );
   
private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void SetRoleList( idt selection );
    idt GetRoleID() const;

    void OnAddRoleButton( wxCommandEvent& event );

    recEvent            m_event;
    recIndividualEvent  m_ie;
    rgSHOWROLE          m_filter;
    recEventTypeRoleVec m_roles;
};

//============================================================================
//-------------------------[ rgDlgPerEvent ]----------------------------------
//============================================================================

class rgDlgPerEvent : public fbRgPerIndEvent
{
public:
    rgDlgPerEvent( wxWindow* parent, idt epID, rgSHOWROLE filter );
   
private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void SetRoleList( idt selection );
    idt GetRoleID() const;

    void OnAddRoleButton( wxCommandEvent& event );

    recEventRecord      m_event;
    recEventPersona     m_ep;
    rgSHOWROLE          m_filter;
    recEventTypeRoleVec m_roles;
};

#endif // RGEDPERINDEVENT_H
