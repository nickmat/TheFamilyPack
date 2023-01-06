/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCrIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create database Individual entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010..2023, Nick Matthews.
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

#include <rec/recFamily.h>


idt rgCreateIndividual( 
    wxWindow* parent,
    idt famID,
    Sex sex,
    int privacy,
    unsigned flags, 
    const wxString& name1,
    const wxString& name2
) {
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    idt indID = 0;

    rgDlgCreateIndividual* dialog = new rgDlgCreateIndividual( parent, famID );
    dialog->SetSex( sex );
    dialog->SetPrivacy( privacy );
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
//-------------------------[ rgDlgCreateIndividual ]--------------------------
//============================================================================

rgDlgCreateIndividual::rgDlgCreateIndividual( wxWindow* parent, idt famID )
    : m_individual(0), m_name(0), m_sex( Sex::unstated),
    fbRgCreateIndividual( parent )
{
    wxASSERT( famID != 0 );
    m_individual.FSetFamID( famID );
    m_individual.Save();
    m_name.FSetIndID( m_individual.FGetID() );
    m_name.FSetSequence( 1 );
    m_name.Save();
}

bool rgDlgCreateIndividual::TransferDataToWindow()
{
    wxString idStr = m_individual.GetIdStr() + ", " 
        + recFamily::GetIdStr( m_individual.FGetFamID() );
    m_staticIndID->SetLabel( idStr );
    m_choiceSex->SetSelection( static_cast<int>(m_sex) );
    m_spinPrivacy->SetValue( m_privacy );
    m_textSurname->SetValue( m_surname );
    m_textGiven->SetFocus();
    return true;
}

bool rgDlgCreateIndividual::TransferDataFromWindow()
{
    m_individual.FSetSex( (Sex) m_choiceSex->GetSelection() );
    m_individual.FSetPrivacy( m_spinPrivacy->GetValue() );
    m_individual.FSetNote( m_textNote->GetValue() );

    int seq = m_name.AddNameParts( m_textGiven->GetValue(), NAME_TYPE_Given_name, 0 );
    wxString surname = m_textSurname->GetValue();
    if( surname.empty() ) {
        surname = "?";
    }
    m_name.AddNamePart( surname, NAME_TYPE_Surname, seq );

    m_individual.UpdateNames();
    m_individual.Save();

    return true;
}

// End of src/rg/rgCrIndividual.cpp file
