/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCrIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create database Individual entity dialog header.
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

#ifndef RGCRINDIVIDUAL_H
#define RGCRINDIVIDUAL_H

#include <rec/recIndividual.h>
#include <rec/recPersona.h>
#include <rec/recName.h>

#include "fbRgDialog.h"

//============================================================================
//                 dlgCreateIndividual dialog
//============================================================================

class rgDlgCreateIndividual : public fbRgCreateIndividual
{
public:
    rgDlgCreateIndividual( wxWindow* parent );

    idt GetIndID() const { return m_individual.FGetID(); }

    void SetSex( Sex sex ) { m_sex = sex; }
    void SetGiven( const wxString& name ) { m_given = name; }
    void SetSurname( const wxString& name ) { m_surname = name; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    Sex            m_sex;
    wxString       m_given;
    wxString       m_surname;

    recIndividual  m_individual;
    recPersona     m_persona;
    recName        m_name;
};

#endif // RGCRINDIVIDUAL_H