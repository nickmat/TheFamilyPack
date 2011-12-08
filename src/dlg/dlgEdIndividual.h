/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndividual.h
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

#ifndef DLGEDINDIVIDUAL_H
#define DLGEDINDIVIDUAL_H

#include <rec/recIndividual.h>
#include <rec/recPersona.h>
#include <rec/recEvent.h>

#include "fbDlg.h"

//============================================================================
//                 dlgCreateIndividual dialog
//============================================================================

class dlgCreateIndividual : public fbDlgCreateIndividual
{
public:
    dlgCreateIndividual( wxWindow* parent, idt famID );

    void SetSex( Sex sex ) { m_sex = sex; }
    void SetSurname( const wxString& name ) { m_surname = name; }

    idt GetIndividualID() const { return m_individual.f_id; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    Sex            m_sex;
    wxString       m_surname;

    recIndividual  m_individual;
    recPersona     m_persona;
    recName        m_name;
};


//============================================================================
//                 dlgEditIndPersona dialog
//============================================================================

class dlgEditIndPersona : public fbDlgEditIndPersona
{
    enum Columns {
        COL_Type, COL_Value, COL_MAX
    };
    enum EventColumns {
        EV_COL_Number, EV_COL_Role, EV_COL_Title, EV_COL_Date, EV_COL_Place, EV_COL_MAX
    };
public:
    dlgEditIndPersona( wxWindow* parent, idt indID );

//    void SetPersonaID( idt perID ) { m_persona.f_id = perID; }

    recPersona* GetPersona() { return &m_persona; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnNameAddButton( wxCommandEvent& event );
    void OnNameEditButton( wxCommandEvent& event );
    void OnNameDeleteButton( wxCommandEvent& event );
    void OnNameUpButton( wxCommandEvent& event );
    void OnNameDownButton( wxCommandEvent& event );

    void OnAttrAddButton( wxCommandEvent& event );
    void OnAttrEditButton( wxCommandEvent& event );
    void OnAttrDeleteButton( wxCommandEvent& event );
    void OnAttrUpButton( wxCommandEvent& event );
    void OnAttrDownButton( wxCommandEvent& event );

    void OnEventAddButton( wxCommandEvent& event );
    void OnEventEditButton( wxCommandEvent& event );
    void OnEventDeleteButton( wxCommandEvent& event );
    void OnEventUpButton( wxCommandEvent& event );
    void OnEventDownButton( wxCommandEvent& event );

    void OnRelAddButton( wxCommandEvent& event );
    void OnRelEditButton( wxCommandEvent& event );
    void OnRelDeleteButton( wxCommandEvent& event );
    void OnRelUpButton( wxCommandEvent& event );
    void OnRelDownButton( wxCommandEvent& event );

    recIndividual      m_individual;
    recPersona         m_persona;
    recNameVec         m_names;
    recAttributeVec    m_attributes;
    recEventPersonaVec m_evpers;
    recRelationshipVec m_relationships;

    wxString           m_nameStr;
};

#endif // DLGEDINDIVIDUAL_H
