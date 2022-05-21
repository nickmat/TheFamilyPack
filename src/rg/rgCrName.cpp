/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCrName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create database Name entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#include <rec/recPersona.h>

#include "rgCrName.h"
#include "rg/rgDialogs.h"

idt rgCreateName( 
    wxWindow* wind,
    idt indID,
    idt perID,
    unsigned flags, 
    const wxString& name1,
    const wxString& name2,
    idt typeID
) {
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    idt nameID = 0;
    unsigned editEx = flags & rgCRNAME_EditExtend;

    rgDlgCreateName* dialog = new rgDlgCreateName( wind, indID, perID, editEx );

    if( flags & rgCRNAME_Sur_Given ) {
        dialog->SetSurname( name1 );
        dialog->SetGiven( name2 );
    } else if( name1.size() ) {
        wxString surname;
        wxString given = name1.BeforeLast( ' ', &surname );
        dialog->SetSurname( surname );
        dialog->SetGiven( given );
    }
    dialog->SetTypeID( typeID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        nameID = dialog->GetNameID();
        if( dialog->GetEditFullName() ) {
            rgEditName( wind, nameID );
        }
        if( dialog->GetEditExtend() ) {
            if( perID ) {
                rgEditPersona( wind, perID );
            }
            if( indID ) {
                rgEditIndividual( wind, indID );
            }
        }
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return nameID;
}

//============================================================================
//-------------------------[ rgDlgCreateName ]--------------------------------
//============================================================================

rgDlgCreateName::rgDlgCreateName(
    wxWindow* parent, idt indID, idt perID, unsigned editEx 
    ) : m_name(0), m_editFullName(false), m_editExtend(false),
    fbRgCreateName( parent )
{
    wxASSERT( (indID == 0) != (perID == 0) ); // One, and only one, must be zero
    m_name.FSetIndID( indID );
    m_name.FSetPerID( perID );
    m_name.SetNextSequence();
    if( ! editEx ){
        m_checkExtend->Enable( false );
    }
}

bool rgDlgCreateName::TransferDataToWindow()
{
    wxASSERT( m_name.FGetID() == 0 );
    m_name.Save();
    UpdateNameStyle( m_name.FGetStyleID() );
    m_textCtrlGiven->SetValue( m_given );
    m_textCtrlSurname->SetValue( m_surname );
    m_staticNameID->SetLabel( m_name.GetIdStr() );
    if( m_name.FGetPerID() ) {
        m_staticPerIndID->SetLabel( recPersona::GetIdStr( m_name.FGetPerID() ) );
    } else {
        m_staticPerIndID->SetLabel( recIndividual::GetIdStr( m_name.FGetIndID() ) );
        m_checkExtend->SetLabel( _("Edit Individual") );
    }
    return true;
}

bool rgDlgCreateName::TransferDataFromWindow()
{
    int i = m_choiceStyle->GetSelection();
    m_name.FSetStyleID( m_styles[i].FGetID() );
    m_name.Save();

    int seq = m_name.AddNameParts( m_textCtrlGiven->GetValue(), NAME_TYPE_Given_name, 0 );
    m_name.AddNamePart( m_textCtrlSurname->GetValue(), NAME_TYPE_Surname, seq );

    m_editFullName = m_checkFullName->GetValue();
    m_editExtend = m_checkExtend->GetValue();
    return true;
}

void rgDlgCreateName::UpdateNameStyle( idt nsID )
{
    m_choiceStyle->Clear();
    m_styles = recNameStyle::GetStyleList();
    int i = 0;
    for( auto& style : m_styles ) {
        m_choiceStyle->Append( style.FGetName() );
        if( nsID == style.FGetID() ) {
            m_choiceStyle->SetSelection( i );
        }
        i++;
    }
}

void rgDlgCreateName::OnAddStyleButton( wxCommandEvent& event )
{
    wxSize s = m_buttonAddStyle->GetSize();
    m_buttonAddStyle->PopupMenu( m_menuAddEditStyle, 0, s.y );
}

void rgDlgCreateName::OnAddStyle( wxCommandEvent& event )
{
    idt nsID = rgCreateNameStyle( this );
    UpdateNameStyle( nsID );
}

void rgDlgCreateName::OnEditStyle( wxCommandEvent& event )
{
    int type = m_choiceStyle->GetSelection();
    if( type == 0 ) return; // Default can't be edited, silently ignore.

    idt nsID = m_styles[type].FGetID();
    rgEditNameStyle( this, nsID );
    UpdateNameStyle( nsID );
}

// End of src/rg/rgCrName.cpp file
