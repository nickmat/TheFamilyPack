/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Reference entity dialog header.
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

#ifndef DLGEDREFERENCE_H
#define DLGEDREFERENCE_H

#include <vector>

#include <rec/recReference.h>

#include "fbDlg.h"

struct TfpEntity {
    recReferenceEntity rec;
    idt                owner;
    int                index;  // Temporary index value, -1 if not used
};

typedef std::vector< TfpEntity >  TfpEntities;

extern int tfpGetEntityIndex( TfpEntities* array, int ind );

struct TfpEntityString {
    wxString m_str;
    int      m_index;
    idt      m_id;
};

typedef std::vector< TfpEntityString > TfpEntityStringVec;

class dlgEditReference : public fbDlgEditReference
{
    DECLARE_EVENT_TABLE()
protected:
    enum Column {
        COL_Type, COL_Value, COL_MAX
    };
    enum {
        ID_EDREF_NEW_SOURCE = 1100,
        ID_EDREF_NEW_EVENT,
        ID_EDREF_NEW_PLACE,
        ID_EDREF_NEW_DATE,
        ID_EDREF_NEW_DATE_AGE,
        ID_EDREF_NEW_NAME,
        ID_EDREF_NEW_REL,
        ID_EDREF_NEW_ATTR
    };

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    // Handlers for fbDlgEditReference events.
    void OnTool( wxCommandEvent& event );
    void OnAddButton( wxCommandEvent& event );
    void OnEditButton( wxCommandEvent& event );
    void OnDeleteButton( wxCommandEvent& event );
    void OnUpButton( wxCommandEvent& event );
    void OnDownButton( wxCommandEvent& event );

    void DoCut();
    void DoCopy();
    void DoPaste();
    void DoUndo();
    void DoRedo();

    void OnNewSource( wxCommandEvent& event );
    void OnNewDate( wxCommandEvent& event );
    void OnNewDateAge( wxCommandEvent& event );
    void OnNewPlace( wxCommandEvent& event );
    void OnNewRelationship( wxCommandEvent& event );
    void OnNewEvent( wxCommandEvent& event );
    void OnNewAttribute( wxCommandEvent& event );
    void OnNewName( wxCommandEvent& event );

    void DoEditDate( idt id, long row );
    void DoEditPlace( idt id, long row );
    void DoEditRelationship( idt id, long row );
    void DoEditEvent( idt id, long row );
    void DoEditAttribute( idt id, long row );
    void DoEditName( idt id, long row );

public:
    /** Constructor */
    dlgEditReference( wxWindow* parent );

    void SetID( idt id ) { m_reference.f_id = id; }

    bool  DoNewDate( idt* dateID );
    bool  DoNewDateAge( idt* dateID );
    bool  DoNewPlace( idt* placeID );
private:
    void InsertListItem( long row, const TfpEntity& ent );

    idt SelectCreatePersona();
    bool SelectDate( idt* dateID, const wxString& title, unsigned style );
    bool SelectPlace( idt* placeID, const wxString& title, unsigned style );
    idt SelectName();

    TfpEntityStringVec GetDateEntityStringVec();

    recReference  m_reference;
    TfpEntities   m_entities;
};

#endif // DLGEDREFERENCE_H
