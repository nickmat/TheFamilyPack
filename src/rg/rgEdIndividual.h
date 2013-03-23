/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual entity dialog header.
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

#ifndef RGEDINDIVIDUAL_H
#define RGEDINDIVIDUAL_H

#include <rec/recIndividual.h>
#include <rec/recPersona.h>
#include <rec/recEvent.h>

#include "fbRgDialog.h"

//============================================================================
//                 dlgEditIndPersona dialog
//============================================================================

class rgDlgEditIndividual : public fbRgEditIndividual
{
    DECLARE_EVENT_TABLE()
    enum Page {
        PAGE_Persona, PAGE_Name, PAGE_Event
    };
    enum {
        ID_EDIND_NEW_EVENT = 1200,
        ID_EDIND_EXIST_EVENT,
        ID_EDIND_UNLINK_EVENT,
        ID_EDIND_DELETE_EVENT
    };
    enum NameColumns {
        NC_Number, NC_Type, NC_Name, NC_MAX
    };
    enum EventColumns {
        EC_Number, EC_Role, EC_Title, EC_Date, EC_Place, EC_MAX
    };
public:
    rgDlgEditIndividual( wxWindow* parent, idt indID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void UpdateNameList( idt nameID = 0 );
    void UpdateEventList( idt eveID = 0 );

    void OnPageChanged( wxBookCtrlEvent& event );

    void OnNameAddButton( wxCommandEvent& event );
    void OnNameEditButton( wxCommandEvent& event );
    void OnNameDeleteButton( wxCommandEvent& event );
    void OnNameUpButton( wxCommandEvent& event );
    void OnNameDownButton( wxCommandEvent& event );

    void OnEventAddButton( wxCommandEvent& event );
    void OnNewEvent( wxCommandEvent& event );
    void OnExistingEvent( wxCommandEvent& event );
    void OnEventEditButton( wxCommandEvent& event );
    void OnEventDeleteButton( wxCommandEvent& event );
    void OnUnlinkEvent( wxCommandEvent& event );
    void OnDeleteEvent( wxCommandEvent& event );
    void OnEventUpButton( wxCommandEvent& event );
    void OnEventDownButton( wxCommandEvent& event );
    void OnEventOrderBy( wxCommandEvent& event );

    recIndividual   m_individual;
    recPersona      m_persona;
    recNameVec      m_names;
    recIndEventVec  m_ies;
    recEventOrder   m_order;

    wxString        m_nameStr;
    long            m_currentRow;
};

#endif // RGEDINDIVIDUAL_H
