/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCrIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create database Individual entity dialog.
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rg/rgDialogs.h>

#include "rgCrIndividual.h"

idt rgCreateIndividual( 
    wxWindow* parent,
    Sex sex,
    unsigned flags, 
    const wxString& name1,
    const wxString& name2
) {
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    idt indID = 0;

    rgDlgCreateIndividual* dialog = new rgDlgCreateIndividual( parent );
    dialog->SetSex( sex );
    if( flags & rgCRNAME_Sur_Given ) {
        dialog->SetSurname( name1 );
        dialog->SetGiven( name2 );
    } else if( name1.size() ) {
        wxString surname;
        wxString given = name1.BeforeLast( ' ', &surname );
        dialog->SetSurname( surname );
        dialog->SetGiven( given );
    }

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        indID = dialog->GetIndID();
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return indID;
}

//============================================================================
//                 rgDlgCreateIndividual dialog
//============================================================================

rgDlgCreateIndividual::rgDlgCreateIndividual( wxWindow* parent )
    : m_individual(0), m_persona(0), m_name(0), m_sex(SEX_Unstated),
    fbRgCreateIndividual( parent )
{
    m_persona.Save();
    m_name.FSetPerID( m_persona.FGetID() );
    m_name.Save();
    m_individual.FSetPerID( m_persona.FGetID() );
    m_individual.Save();
}

bool rgDlgCreateIndividual::TransferDataToWindow()
{
    m_staticIndID->SetLabel( m_individual.GetIdStr() );
    m_choiceSex->SetSelection( m_sex );
    m_textSurname->SetValue( m_surname );
    m_textGiven->SetFocus();
    return true;
}

bool rgDlgCreateIndividual::TransferDataFromWindow()
{
    m_persona.FSetSex( (Sex) m_choiceSex->GetSelection() );
    m_persona.FSetNote( m_textNote->GetValue() );
    m_persona.Save();

    int seq = m_name.AddNameParts( m_textGiven->GetValue(), NAME_TYPE_Given_name, 0 );
    m_name.AddNamePart( m_textSurname->GetValue(), NAME_TYPE_Surname, seq );

    m_individual.Update();
    m_individual.Save();

    return true;
}

// End of src/rg/rgCrIndividual.cpp file
