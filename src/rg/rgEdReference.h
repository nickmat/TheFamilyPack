/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     26th February 2013
 * Copyright:   Copyright (c) 2013 ~ 2018, Nick Matthews.
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

#include "fb/fbRgEditReference.h"

//============================================================================
//-------------------------[ rgDlgEditReference ]-----------------------------
//============================================================================

class rgDlgEditReference : public fbRgEditReference
{
public:
    /** Constructor */
    rgDlgEditReference( wxWindow* parent, idt refID );

private:
    enum class TPage { source, view, MAX };
    enum class BPage { citation, media, persona, eventa, entity, MAX };
    enum CitationColumn {
        CIT_COL_Number, CIT_COL_Citation, CIT_COL_MAX
    };
    enum MediaColumn {
        MED_COL_Number, MED_COL_Title, MED_COL_MAX
    };
    enum PersonaColumn {
        PER_COL_Number, PER_COL_Name, PER_COL_Individuals, PER_COL_MAX
    };
    enum EventaColumn {
        EA_COL_Number, EA_COL_Title, EA_COL_Event, EA_COL_MAX
    };
    enum EntityColumn {
        ENT_COL_Type, ENT_COL_Number, ENT_COL_Value, ENT_COL_MAX
    };

    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void UpdateHtml();
    void UpdateCitations( idt citID = 0 );
    void UpdateMedias( idt medID = 0 );
    void UpdatePersonas( idt perID = 0 );
    void UpdateEventas( idt eaID = 0 );
    void UpdateEntities( idt reID = 0 );

    wxString GetSelectedText() const;

	void OnStatementViewChanged( wxBookCtrlEvent& event ) override;
    void OnToolCut( wxCommandEvent& event ) override;
    void OnToolCopy( wxCommandEvent& event ) override;
    void OnToolPaste( wxCommandEvent& event ) override;
    void OnToolUndo( wxCommandEvent& event ) override;
    void OnToolRedo( wxCommandEvent& event ) override;

    void OnEntityViewChanged( wxBookCtrlEvent& event ) override;
    // Citation tab buttons
    void OnCitationAddButton( wxCommandEvent& event ) override;
    void OnCitationEditButton( wxCommandEvent& event ) override;
    void OnCitationDeleteButton( wxCommandEvent& event ) override;
    void OnCitationUpButton( wxCommandEvent& event ) override;
    void OnCitationDownButton( wxCommandEvent& event ) override;
    // Media tab buttons
    void OnMediaAddButton( wxCommandEvent& event ) override;
    void OnMediaEditButton( wxCommandEvent& event ) override;
    void OnMediaDeleteButton( wxCommandEvent& event ) override;
    void OnMediaUpButton( wxCommandEvent& event ) override;
    void OnMediaDownButton( wxCommandEvent& event ) override;
    void OnMediaViewButton( wxCommandEvent& event ) override;
    // Persona tab buttons
    void OnPersonaAddButton( wxCommandEvent& event ) override;
    void OnAddMalePersona( wxCommandEvent& event ) override;
    void OnAddFemalePersona( wxCommandEvent& event ) override;
    void OnAddUnknownPersona( wxCommandEvent& event ) override;
    void AddPersona( Sex sex );
    void OnPersonaEditButton( wxCommandEvent& event ) override;
    void OnPersonaDeleteButton( wxCommandEvent& event ) override;
    // Eventa tab buttons
    void OnEventaAddButton( wxCommandEvent& event ) override;
    void OnNewEventa( wxCommandEvent& event ) override;
    void OnNewPersonalEventa( wxCommandEvent& event ) override;
    void OnEventaEditButton( wxCommandEvent& event ) override;
    void OnEventaDeleteButton( wxCommandEvent& event ) override;
    // Entity tab buttons
    void OnAddEntityButton( wxCommandEvent& event ) override;
    void OnNewDate( wxCommandEvent& event ) override;
    void OnNewDateAge( wxCommandEvent& event ) override;
    void OnNewPlace( wxCommandEvent& event ) override;
    void OnNewName( wxCommandEvent& event ) override;
    void OnEditEntityButton( wxCommandEvent& event ) override;
    void OnDeleteEntityButton( wxCommandEvent& event ) override;
    void OnUpEntityButton( wxCommandEvent& event ) override;
    void OnDownEntityButton( wxCommandEvent& event ) override;

    idt CreateRefEntity( recReferenceEntity::Type type, idt entID );
    void InsertEntityListItem( size_t row );

    recReference  m_reference;
    recIdVec      m_citationIDs;
    recIdVec      m_mediaIDs;
    recIdVec      m_personaIDs;
    recIdVec      m_eventaIDs;
    recRefEntVec  m_entities;
};

#endif // RGEDREFERENCE_H
