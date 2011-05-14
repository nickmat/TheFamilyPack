/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Event entity dialog header.
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

#ifndef DLGEDEVENT_H
#define DLGEDEVENT_H

#include <rec/recEvent.h>

#include "fbDlg.h"
#include "dlgEdReference.h"

/** Implementing fbDlgEditEvent */
class dlgEditEvent : public fbDlgEditEvent
{
    DECLARE_CLASS( dlgEditEvent )
    DECLARE_EVENT_TABLE()

    enum Columns {
        COL_Persona, COL_Role, COL_Note, COL_MAX
    };
    enum EvDate { EV_DATE_Beg, EV_DATE_End };

public:
    /** Constructor */
    dlgEditEvent( wxWindow* parent );

    void SetData( idt typeID, idt eventID = 0 );
    void SetEntities( TfpEntities* entities ) { mp_entities = entities; }
    void SetDateStrings( TfpEntityStringVec strs ) { m_dateStrings = strs; }
    recEvent* GetEvent() { return &m_event; }

protected:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    // Handlers for fbDlgEditEvent events.
    void OnDateBegButton( wxCommandEvent& event ); // Overide base
    void OnDateEndButton( wxCommandEvent& event ); // Overide base
    void DateSelectButton( EvDate button );
    void OnDateSelect( wxCommandEvent& event );
    void OnAgeSelect( wxCommandEvent& event );
    void OnPlaceButton( wxCommandEvent& event );   // Overide base
    void OnPlaceSelect( wxCommandEvent& event );
    void OnAddButton( wxCommandEvent& event );     // Overide base
    void OnEditButton( wxCommandEvent& event );    // Overide base
    void OnDeleteButton( wxCommandEvent& event );  // Overide base
    void OnUpButton( wxCommandEvent& event );      // Overide base
    void OnDownButton( wxCommandEvent& event );    // Overide base


private:
    recEvent           m_event;
    recEventType       m_etype;
    recEventPersonaVec m_pes;

    TfpEntities*       mp_entities;
    TfpEntityStringVec m_dateStrings;

    EvDate             m_dateButton;
};

#endif // DLGEDEVENT_H
