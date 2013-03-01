/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     26th February 2013
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

#ifndef RGEDREFERENCE_H
#define RGEDREFERENCE_H

#include <rec/recReference.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgEditReference ]-----------------------------
//============================================================================

class rgDlgEditReference : public fbRgEditReference
{
    DECLARE_EVENT_TABLE()
protected:
    enum EntityColumn {
        ENT_COL_Type, ENT_COL_Number, ENT_COL_Value, ENT_COL_MAX
    };
    enum PersonaColumn {
        PER_COL_Number, PER_COL_Name, PER_COL_Individuals, PER_COL_MAX
    };
    enum {
        ID_EDREF_NEW_SOURCE = 1100,
        ID_EDREF_NEW_NAME,
        ID_EDREF_NEW_DATE,
        ID_EDREF_NEW_DATE_AGE,
        ID_EDREF_NEW_PLACE,
        ID_EDREF_NEW_EVENT,
        ID_EDREF_NEW_PER_EVENT,
        ID_EDREF_NEW_REL
    };

    bool TransferDataToWindow();
    void UpdateHtml();
    void ListEntities();
    void ListPersonas();
    void UpdateLists() { ListPersonas(); ListEntities(); }
    bool TransferDataFromWindow();
    // Handlers for fbDlgEditReference events.
    void OnTool( wxCommandEvent& event );
    void DoCut();
    void DoCopy();
    void DoPaste();
    void DoUndo();
    void DoRedo();

	void OnStatementViewChanging( wxNotebookEvent& event );
    // Persona tab buttons
    void OnPersonaAddButton( wxCommandEvent& event );
    void OnPersonaEditButton( wxCommandEvent& event );
    void OnPersonaDeleteButton( wxCommandEvent& event );
    // Entity tab buttons
    void OnAddEntityButton( wxCommandEvent& event );
    void OnNewSource( wxCommandEvent& event );
    void OnNewName( wxCommandEvent& event );
    void OnNewDate( wxCommandEvent& event );
    void OnNewDateAge( wxCommandEvent& event );
    void OnNewPlace( wxCommandEvent& event );
    void OnNewEvent( wxCommandEvent& event );
    void OnNewPersonalEvent( wxCommandEvent& event );
    void OnNewRelationship( wxCommandEvent& event );
    void OnEditEntityButton( wxCommandEvent& event );
    void OnDeleteEntityButton( wxCommandEvent& event );
    void OnUpEntityButton( wxCommandEvent& event );
    void OnDownEntityButton( wxCommandEvent& event );

public:
    /** Constructor */
    rgDlgEditReference( wxWindow* parent, idt refID );

    bool SelectDate( idt* dateID, const wxString& title, unsigned style );
    bool SelectPlace( idt* placeID, const wxString& title, unsigned style );
    idt SelectCreatePersona();

    void CreateRefEntity( recReferenceEntity::Type type, idt entID );
    void InsertEntityListItem( size_t row );
    void UpdateSequence();

    recReference  m_reference;
    recRefEntVec  m_entities;
    recIdVec      m_personaIDs;
    wxString      m_htmlText;
};

#endif // RGEDREFERENCE_H