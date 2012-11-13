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
    dlgCreateIndividual( wxWindow* parent, idt indID );

    void SetSex( Sex sex ) { m_sex = sex; }
    void SetSurname( const wxString& name ) { m_surname = name; }

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
    DECLARE_EVENT_TABLE()
    enum {
        ID_EDIND_NEW_EVENT = 1200,
        ID_EDIND_EXIST_EVENT
    };
    enum Columns {
        COL_Type, COL_Value, COL_MAX
    };
    enum NameColumns {
        NC_Number, NC_Type, NC_Name, NC_MAX
    };
    enum EventColumns {
        EC_Number, EC_Role, EC_Title, EC_Date, EC_Place, EC_MAX
    };
    enum RelColumns {
        RC_Family, RC_Ind, RC_Relation, RC_MAX
    };
public:
    dlgEditIndPersona( wxWindow* parent, idt indID );

    recPersona* GetPersona() { return &m_persona; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

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
    recIndEventVec     m_ies;
    recIndRelVec       m_relationships;

    wxString           m_nameStr;
};

#endif // DLGEDINDIVIDUAL_H
