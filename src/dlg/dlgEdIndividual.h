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

class dlgEditIndividual : public fbDlgEditIndividual
{
    DECLARE_CLASS( dlgEditIndividual )
    DECLARE_EVENT_TABLE()

public:
    dlgEditIndividual( wxWindow* parent );

    void SetIndividualID( idt indID ) { m_individual.f_id = indID; }
    void SetFamilyID( idt famID ) { m_fam_id = famID; }
    void SetSex( Sex sex ) { m_sex = sex; }
    void SetSurname( const wxString& name ) { m_surname = name; }
    idt GetIndividualID() const { return m_individual.f_id; }
    idt GetFamilyID() const { return m_fam_id; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnEventActivated( wxListEvent& event );

    void UpdateEventDetails();

    idt           m_fam_id;
    Sex            m_sex;

    recIndividual  m_individual;
    recPersona     m_persona;
    recName        m_name;
    wxString       m_surname;
    wxString       m_given;
 //   recAttribute   m_occAttr;
 //   recEvent       m_birthEvent;
 //   recEvent       m_nrbirthEvent;
 //   recEvent       m_deathEvent;
 //   recEvent       m_nrdeathEvent;
};

#endif // DLGEDINDIVIDUAL_H
