/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual Event dialog header.
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

#ifndef RGEDEVENT_H
#define RGEDEVENT_H

#include <rec/recEvent.h>
#include <rec/recIndividual.h>

#include "fbRgDialog.h"


//============================================================================
//-------------------------[ rgDlgEditEvent ]---------------------------------
//============================================================================

class rgDlgEditEvent : public fbRgEditEvent
{
public:
    rgDlgEditEvent( wxWindow* parent, idt eventID );

protected:
    enum Columns {
        COL_IndID, COL_Name, COL_Role, COL_Note, COL_MAX
    };
    virtual void ListLinkedPersona();
    virtual void EditRow( long row );
    virtual void DeleteRow( long row );

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnDate1Button( wxCommandEvent& event );
    void OnDate2Button( wxCommandEvent& event );
    void OnPlaceButton( wxCommandEvent& event );

    void OnAddButton( wxCommandEvent& event );
    void OnEditButton( wxCommandEvent& event );
    void OnDeleteButton( wxCommandEvent& event );

    recEvent  m_event;
    idt  m_date1ID;
    idt  m_date2ID;
    idt  m_placeID;

private:
    recIndEventVec    m_ies;
    recIndividualVec  m_individuals;
};

#endif // RGEDEVENT_H
