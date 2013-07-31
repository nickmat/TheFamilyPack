/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual Event dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
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

private:
    enum ColInd {
        COL_IndID, COL_Name, COL_Role, COL_Note, COL_MAX
    };
    enum ColRecord {
        COL_RecID, COL_RefID, COL_RefTitle
    };

    bool TransferDataToWindow();
    void ListLinkedIndividuals();
    void ListEventums();
    bool TransferDataFromWindow();

    void OnDate1Button( wxCommandEvent& event );
    void OnDate2Button( wxCommandEvent& event );
    void OnPlaceButton( wxCommandEvent& event );

    void OnAddInd( wxCommandEvent& event );
    void OnEditInd( wxCommandEvent& event );
    void OnDelInd( wxCommandEvent& event );

    void OnAddRecord( wxCommandEvent& event );
    void OnEditRecord( wxCommandEvent& event );
    void OnDeleteRecord( wxCommandEvent& event );

    recEvent  m_event;
    idt       m_date1ID;
    idt       m_date2ID;
    idt       m_placeID;

    recIndEventVec     m_ies;
    recEventEventumVec m_eers;
};

#endif // RGEDEVENT_H
