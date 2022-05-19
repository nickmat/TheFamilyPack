/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdCitPart.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit CitationPart dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     18th May 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recCitation.h>

#include <rg/rgDialogs.h>
#include "rgEdCitPart.h"


bool rgEditCitationPart( wxWindow* wind, idt cipID, const wxString& title )
{
    return rgEdit<rgDlgEditCitationPart>( wind, cipID, title );
}

idt rgCreateCitationPart( wxWindow* wind, idt citID )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recCitationPart part( 0 );
    part.FSetCitID( citID );
    part.FSetCitSeq( part.GetNextCitationSeq( citID ) );
    part.Save();
    idt partID = part.FGetID();

    if( rgEditCitationPart( wind, partID, _( "Create Citation Part" ) ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return partID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//------------------------[ rgDlgEditCitationPart ]---------------------------
//============================================================================

rgDlgEditCitationPart::rgDlgEditCitationPart( wxWindow* parent, idt cipID )
    : m_part( cipID ), fbRgEditCitationPart( parent )
{
}

bool rgDlgEditCitationPart::TransferDataToWindow()
{
    UpdatePartType( m_part.FGetTypeID() );
    m_textCtrlValue->SetValue( m_part.FGetValue() );
    m_textCtrlComment->SetValue( m_part.FGetComment() );
    m_staticCipID->SetLabel(
        recCitation::GetIdStr( m_part.FGetCitID() ) + ":" + m_part.GetIdStr()
    );
    return true;
}

bool rgDlgEditCitationPart::TransferDataFromWindow()
{
    int type = m_choiceType->GetSelection();
    if( type <= 0 ) {
        wxMessageBox( _( "Please select a Citation Part Type" ), _( "Citation Part Type Required" ) );
        return false;
    }
    m_part.FSetTypeID( m_types[type-1].FGetID() );
    m_part.FSetValue( m_textCtrlValue->GetValue() );
    m_part.FSetComment( m_textCtrlComment->GetValue() );
    m_part.Save();
    return true;
}

void rgDlgEditCitationPart::UpdatePartType( idt ciptID )
{
    m_types = recCitationPartType::GetList();
    m_choiceType->Clear();
    m_choiceType->Append( _( "<Select Type>" ) );
    m_choiceType->SetSelection( 0 );
    for( size_t i = 0; i < m_types.size(); i++ ) {
        m_choiceType->Append( m_types[i].FGetName() );
        if( ciptID == m_types[i].FGetID() ) {
            m_choiceType->SetSelection( (int)i + 1 );
        }
    }
}

void rgDlgEditCitationPart::OnAddEditButton( wxCommandEvent& event )
{
    wxSize s = m_buttonTypeAdd->GetSize();
    m_buttonTypeAdd->PopupMenu( m_menuAddEditType, 0, s.y );
}

void rgDlgEditCitationPart::OnAddType( wxCommandEvent& event )
{
    idt ciptID = rgCreateCitationPartType( this );
    UpdatePartType( ciptID );
}

void rgDlgEditCitationPart::OnEditType( wxCommandEvent& event )
{
    int type = m_choiceType->GetSelection();
    if( type == 0 ) return; // Nothing selected, silently ignore.

    idt ciptID = m_types[type - 1].FGetID();
    rgEditCitationPartType( this, ciptID );
    UpdatePartType( ciptID );
}


// End of src/rg/rgEdCitPart.cpp file
