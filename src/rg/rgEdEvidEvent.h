/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEvidEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Event entity dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25th February 2013
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

#ifndef RGEDEVIDEVENT_H
#define RGEDEVIDEVENT_H

#include "rgEdEvent.h"
#include "rgEdReference.h"

//============================================================================
//-------------------------[ rgDlgEditEvidEvent ]-----------------------------
//============================================================================

/** Implementing rgDlgEditEvidEvent */
class rgDlgEditEvidEvent : public fbRgEditEvent
{
    DECLARE_EVENT_TABLE()
public:
    rgDlgEditEvidEvent( rgDlgEditReference* parent, idt eventID );

protected:
    enum Columns {
        COL_PerID, COL_Name, COL_Role, COL_Note, COL_MAX
    };
    enum {
        ID_EDEE_OPTN_EDIT = 1500,
        ID_EDEE_OPTN_UNLINK,
        ID_EDEE_OPTN_CREATE,
        ID_EDEE_OPTN_CREATE_REL
    };

    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void ListLinkedPersona();
    void EditRow( long row );
    void DeleteRow( long row );

    void OnDate1Button( wxCommandEvent& event );
    void OnDate2Button( wxCommandEvent& event );
    void OnPlaceButton( wxCommandEvent& event );

    void OnOptnEdit( wxCommandEvent& event );
    void OnOptnUnlink( wxCommandEvent& event );
    void OnOptnCreate( wxCommandEvent& event );
    void OnOptnCreateRel( wxCommandEvent& event );

    void OnAddButton( wxCommandEvent& event );

    recEventRecord  m_event;
    idt  m_date1ID;
    idt  m_date2ID;
    idt  m_placeID;

private:
    enum Button {
        EEEB_Date1, EEEB_Date2, EEEB_Place
    };
    Button              m_button;
    rgDlgEditReference* m_refDialog;

    recEventPersonaVec  m_eps;
    recPersonaVec       m_personas;
};

#endif // RGEDEVIDEVENT_H
