/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdRelationship.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Relationship entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     13 July 2011
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

#ifndef DLGEDRELATIONSHIP_H
#define DLGEDRELATIONSHIP_H

#include <rec/recEvent.h>

#include "fbDlg.h"
#include "dlgEdReference.h"

class dlgEditRelationship : public fbDlgEditRelationship
{
public:
    dlgEditRelationship( wxWindow* parent, idt relID = 0 );

    void SetPersona1ID( idt perID ) { m_rel.f_per1_id = perID; }
    void SetPersona2ID( idt perID ) { m_rel.f_per2_id = perID; }

    recRelationship* GetRelationship() { return &m_rel; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnPersona1Button( wxCommandEvent& event );
    void OnPersona2Button( wxCommandEvent& event );

    recRelationship  m_rel;
};

#endif // DLGEDRELATIONSHIP_H
