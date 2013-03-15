/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Persona entity dialog header.
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

#ifndef RGEDPERSONA_H
#define RGEDPERSONA_H

#include <rec/recPersona.h>

#include "fbRgDialog.h"


//============================================================================
//-------------------------[ rgDlgEditPersona ]-------------------------------
//============================================================================

class rgDlgEditPersona : public fbRgEditPersona
{
    enum Page {
        PAGE_Persona, PAGE_Name, PAGE_Event, PAGE_Rel
    };
    enum Columns {
        COL_Type, COL_Value, COL_MAX
    };
    enum EventColumns {
        EV_COL_Number, EV_COL_Role, EV_COL_Title, EV_COL_Date, EV_COL_Place, EV_COL_MAX
    };
public:
    rgDlgEditPersona( rgDlgEditReference* parent, idt perID );

    void SetPersonaID( idt perID ) { m_persona.f_id = perID; }

    recPersona* GetPersona() { return &m_persona; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    wxString GetIndLinksString() const;
    void UpdateNameList( idt nameID = 0 );
    void UpdateEventList( idt eveID = 0 );
    void UpdateRelList( idt relID = 0 );

    void OnPageChanged( wxNotebookEvent& event );

    void OnIndLinkButton( wxCommandEvent& event );

    void OnNameAddButton( wxCommandEvent& event );
    void OnNameEditButton( wxCommandEvent& event );
    void OnNameDeleteButton( wxCommandEvent& event );
    void OnNameUpButton( wxCommandEvent& event );
    void OnNameDownButton( wxCommandEvent& event );

    void OnEventAddButton( wxCommandEvent& event );
    void OnEventEditButton( wxCommandEvent& event );
    void OnEventDeleteButton( wxCommandEvent& event );
    void OnEventUpButton( wxCommandEvent& event );
    void OnEventDownButton( wxCommandEvent& event );
    void OnOrderBy( wxCommandEvent& event );

    void OnRelAddButton( wxCommandEvent& event );
    void OnRelEditButton( wxCommandEvent& event );
    void OnRelDeleteButton( wxCommandEvent& event );

    rgDlgEditReference* m_refDialog;

    recPersona          m_persona;
    recIdVec            m_indLinks;
    recNameVec          m_names;
    recEventPersonaVec  m_evpers;
    recEventOrder       m_order;
    recRelationshipVec  m_relationships;

    wxString            m_nameStr;
};

#endif // RGEDPERSONA_H
