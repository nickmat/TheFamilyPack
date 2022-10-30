/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Persona entity dialog.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

#include <wx/tokenzr.h>

#include <rec/recIndividual.h>
#include <rec/recIndPersona.h>
#include <rg/rgDialogs.h>

#include "rgEdReference.h"
#include "rgEdPersona.h"

bool rgEditPersona( wxWindow* parent, idt perID, const wxString& title )
{
    return rgEdit<rgDlgEditPersona>( parent, perID, title );
}

idt rgCreateNamedPersona( wxWindow* wind, idt refID )
{
    wxASSERT( refID!= 0 ); // Must be associated with a reference
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt perID = recPersona::Create( refID );
    idt nameID = rgCreatePersonaName( wind, perID );
    if( nameID == 0 ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recReferenceEntity::Create( refID, recReferenceEntity::TYPE_Name, nameID );

    if( !rgEditPersona( wind, perID, "Create Persona" ) ) {
        recDb::Rollback( savepoint );
        return 0;
    }
    recDb::ReleaseSavepoint( savepoint );
    return perID;
}

bool rgEditIndividualPersona( wxWindow* parent, idt ipaID, const wxString& title )
{
    return rgEdit<rgDlgLinkIndPersona>( parent, ipaID, title );
}

idt rgCreateIndividualPersona( wxWindow* wind, idt indID, idt perID )
{
    recIndividualPersona ipa( 0 );
    ipa.FSetIndID( indID );
    ipa.FSetPerID( perID );
    ipa.FSetConf( 0.999 );
    wxString title = "Create Individual to Persona Link";
    return rgCreate< recIndividualPersona, rgDlgLinkIndPersona>( wind, ipa, title );
}


//============================================================================
//-------------------------[ rgDlgEditPersona ]-------------------------------
//============================================================================

rgDlgEditPersona::rgDlgEditPersona( wxWindow* parent, idt perID )
    : m_persona(perID), m_order(recEO_PerSeq),
    fbRgEditPersona( parent )
{
    wxASSERT( m_persona.FGetRefID() != 0 );

    m_listName->InsertColumn( NC_Number, _("Number") );
    m_listName->InsertColumn( NC_Type, _("Type") );
    m_listName->InsertColumn( NC_Name, _("Name") );

    m_listEventa->InsertColumn( EV_COL_Number, _("Number") );
    m_listEventa->InsertColumn( EV_COL_Role, _("Role") );
    m_listEventa->InsertColumn( EV_COL_Title, _("Title") );
    m_listEventa->InsertColumn( EV_COL_Date, _("Date") );
    m_listEventa->InsertColumn( EV_COL_Place, _("Place") );

    m_listIndividual->InsertColumn( IC_Number, _( "Number" ) );
    m_listIndividual->InsertColumn( IC_Conf, _( "Conf" ) );
    m_listIndividual->InsertColumn( IC_Name, _( "Name" ) );
    m_listIndividual->InsertColumn( IC_Link_Note, _( "Link Note" ) );
}

bool rgDlgEditPersona::TransferDataToWindow()
{
    m_staticPerName->SetLabel( m_persona.GetNameStr() );
    m_staticPerID->SetLabel( m_persona.GetIdStr() );

    m_choiceSex->SetSelection( (int) m_persona.f_sex );

    idt refID = m_persona.FGetRefID();
    wxString reference = recReference::GetIdStr( refID ) + ": "
        + recReference::GetTitle( refID );
    m_textCtrlRef->SetValue( reference );

    m_textCtrlUid->SetValue( m_persona.FGetUid() );
    wxString changed = calStrFromJdn( m_persona.FGetChanged() );
    m_textCtrlChanged->SetValue( changed );

    m_textCtrlNote->SetValue(  m_persona.f_note );

    UpdateNameList();
    UpdateEventaList();
    UpdateIndividualList();
    return true;
}

bool rgDlgEditPersona::TransferDataFromWindow()
{
    m_persona.f_sex = (Sex) m_choiceSex->GetSelection();
    m_persona.f_note = m_textCtrlNote->GetValue();
    m_persona.Save();
    return true;
}

void rgDlgEditPersona::UpdateNameList( idt nameID )
{
    m_names = m_persona.ReadNames();
    m_listName->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_names.size() ; i++ ) {
        m_listName->InsertItem( i, m_names[i].GetIdStr() );
        m_listName->SetItem( i, NC_Type, recNameStyle::GetStyleStr( m_names[i].FGetTypeID() ) );
        m_listName->SetItem( i, NC_Name, m_names[i].GetNameStr() );
        if( nameID == m_names[i].FGetID() ) {
            m_listName->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
    }
    if( m_names.size() ) {
        m_listName->SetColumnWidth( NC_Name, -1 );
    }
    if( row >= 0 ) {
        m_listName->EnsureVisible( row );
    }
    NameButtonsEnable( row );
}

void rgDlgEditPersona::UpdateEventaList( idt eveID )
{
    m_evpers = m_persona.ReadEventaPersonas( m_order );
    m_listEventa->DeleteAllItems();
    int row = -1;
    for( size_t i = 0 ; i < m_evpers.size() ; i++ ) {
        m_listEventa->InsertItem( i, recEventa::GetIdStr( m_evpers[i].f_eventa_id ) );
        m_listEventa->SetItem( i, EV_COL_Role, recEventTypeRole::GetName( m_evpers[i].f_role_id ) );
        m_listEventa->SetItem( i, EV_COL_Title, recEventa::GetTitle( m_evpers[i].f_eventa_id ) );
        m_listEventa->SetItem( i, EV_COL_Date, recEventa::GetDateStr( m_evpers[i].f_eventa_id ) );
        m_listEventa->SetItem( i, EV_COL_Place, recEventa::GetAddressStr( m_evpers[i].f_eventa_id ) );
        if( eveID == m_evpers[i].FGetEventaID() ) {
            m_listEventa->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        if( m_order == recEO_PerSeq && m_evpers[i].FGetPerSeq() != i+1 ) {
            m_evpers[i].FSetPerSeq( i+1 );
            m_evpers[i].Save();
        }
    }
    if( row >= 0 ) {
        m_listEventa->EnsureVisible( row );
    }
    EventaButtonsEnable( row );
}

void rgDlgEditPersona::UpdateIndividualList( idt indID )
{
    m_indLinks = m_persona.GetIndividualIDs();
    m_listIndividual->DeleteAllItems();
    int row = -1;
    double total = 0.0;
    for( size_t i = 0; i < m_indLinks.size(); i++ ) {
        recIndividualPersona ipa( 0 );
        ipa.FSetIndID( m_indLinks[i] );
        ipa.FSetPerID( m_persona.FGetID() );
        if( !ipa.Find() ) {
            continue;
        }
        total += ipa.FGetConf();

        m_listIndividual->InsertItem( i, recIndividual::GetIdStr( m_indLinks[i] ) );
        m_listIndividual->SetItem( i, IC_Conf, recConfToStr( ipa.FGetConf() ) );
        m_listIndividual->SetItem( i, IC_Name, recIndividual::GetName( m_indLinks[i] ) );
        m_listIndividual->SetItem( i, IC_Link_Note, ipa.FGetNote() );

        if( indID == m_indLinks[i] ) {
            m_listIndividual->SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            row = i;
        }
        // Correct errors and gaps in sequence numbers.
        // TODO: requires recIndividualPersona ind_seq field added
    }
    if( !m_indLinks.empty() ) {
        double remain = 1 - total;
        m_listIndividual->InsertItem( m_indLinks.size(), "" );
        m_listIndividual->SetItem( m_indLinks.size(), IC_Conf, recConfToStr( remain ) );
        m_listIndividual->SetItem( m_indLinks.size(), IC_Name, "Other" );
    }
    if( row >= 0 ) {
        m_listIndividual->EnsureVisible( row );
    }
    IndButtonsEnable( row );
}

void rgDlgEditPersona::OnPageChanged( wxBookCtrlEvent& event )
{
    Page page = (Page) m_notebook->GetSelection();
    switch( page )
    {
    case PAGE_Details:
        break;
    case PAGE_Note:
        break;
    case PAGE_Names:
        UpdateNameList();
        break;
    case PAGE_Eventa:
        UpdateEventaList();
        break;
    case PAGE_Individual:
        UpdateIndividualList();
        break;
    default:
        wxASSERT( false );
    }

    PostSizeEvent();
}

void rgDlgEditPersona::NameButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonNameEdit->Disable();
        m_buttonNameDel->Disable();
        m_buttonNameUp->Disable();
        m_buttonNameDn->Disable();
        return;
    }
    m_buttonNameEdit->Enable();
    m_buttonNameDel->Enable();
    if( row == 0 ) {
        m_buttonNameUp->Disable();
    }
    else {
        m_buttonNameUp->Enable();
    }
    if( row == m_listName->GetItemCount() - 1 ) {
        m_buttonNameDn->Disable();
    }
    else {
        m_buttonNameDn->Enable();
    }
}

void rgDlgEditPersona::OnNameDeselect( wxListEvent& event )
{
    NameButtonsEnable( -1 );
}

void rgDlgEditPersona::OnNameSelect( wxListEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    NameButtonsEnable( row );
}

void rgDlgEditPersona::OnNameAddButton( wxCommandEvent& event )
{
    idt nameID = rgCreatePersonaName( this, m_persona.FGetID() );
    if( nameID ) {
        idt refID = m_persona.FGetRefID();
        recReferenceEntity::Create( refID, recReferenceEntity::TYPE_Name, nameID );
        UpdateNameList( nameID );
    }
}

void rgDlgEditPersona::OnNameEditButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    if( rgEditName( this, nameID ) ) {
        UpdateNameList( nameID );
    }
}

void rgDlgEditPersona::OnNameDeleteButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete Name") );
        return;
    }
    idt nameID = m_names[row].FGetID();
    wxString mess = wxString::Format(
        "Remove Name %s: %s\nfrom Persona %s?",
        recName::GetIdStr( nameID ), recName::GetNameStr( nameID ),
        m_persona.GetIdStr()
    );
    int ans = wxMessageBox( mess, _("Delete Name"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    recName::RemoveFromDatabase( nameID );
    UpdateNameList();
}

void rgDlgEditPersona::OnNameUpButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_names[row].FGetSequence();
    m_names[row].FSetSequence( m_names[row-1].FGetSequence() );
    m_names[row].Save();
    m_names[row-1].FSetSequence( seq );
    m_names[row-1].Save();
    UpdateNameList( m_names[row].FGetID() );
}

void rgDlgEditPersona::OnNameDownButton( wxCommandEvent& event )
{
    long row = m_listName->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row == m_listName->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_names[row].FGetSequence();
    m_names[row].FSetSequence( m_names[row+1].FGetSequence() );
    m_names[row].Save();
    m_names[row+1].FSetSequence( seq );
    m_names[row+1].Save();
    UpdateNameList( m_names[row].FGetID() );
}

void rgDlgEditPersona::EventaButtonsEnable( long row )
{
    if( row < 0 ) {
        m_buttonEventaEdit->Disable();
        m_buttonEventaDel->Disable();
        m_buttonEventaUp->Disable();
        m_buttonEventaDn->Disable();
        return;
    }
    m_buttonEventaEdit->Enable();
    m_buttonEventaDel->Enable();
    if( row == 0 ) {
        m_buttonEventaUp->Disable();
    }
    else {
        m_buttonEventaUp->Enable();
    }
    if( row == m_listEventa->GetItemCount() - 1 ) {
        m_buttonEventaDn->Disable();
    }
    else {
        m_buttonEventaDn->Enable();
    }
}

void rgDlgEditPersona::OnEventaDeselect( wxListEvent& event )
{
    EventaButtonsEnable( -1 );
}

void rgDlgEditPersona::OnEventaSelect( wxListEvent& event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    EventaButtonsEnable( row );
}

void rgDlgEditPersona::OnEventaAddButton( wxCommandEvent& event )
{
    idt eaID = rgCreateEventa( this, m_persona.FGetRefID() );
    if( eaID ) {
        UpdateEventaList( eaID );
    }
}

void rgDlgEditPersona::OnEventaEditButton( wxCommandEvent& event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Edit Event"), wxOK | wxCENTRE, this );
        return;
    }
    idt eventID = m_evpers[row].FGetEventaID();
    if( rgEditEventa( this, eventID ) ) {
        UpdateEventaList( eventID );
    }
}

void rgDlgEditPersona::OnEventaDeleteButton( wxCommandEvent& event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("No row selected"), _("Delete From Event") );
        return;
    }
    idt eveID = m_evpers[row].FGetEventaID();
    wxString mess = wxString::Format(
        "Remove %s %s from Event %s\n%s?",
        m_persona.GetNameStr(), m_persona.GetIdStr(),
        recEvent::GetIdStr( eveID ), recEvent::GetTitle( eveID )
    );
    int ans = wxMessageBox( mess, _("Delete From Event"), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    m_evpers[row].Delete();
    UpdateEventaList();
}

void rgDlgEditPersona::OnEventaUpButton( wxCommandEvent& event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Up") );
        return;
    }
    if( row == 0 ) {
        return; // Already at top
    }
    int seq = m_evpers[row].FGetPerSeq();
    m_evpers[row].FSetPerSeq( m_evpers[row-1].FGetPerSeq() );
    m_evpers[row].Save();
    m_evpers[row-1].FSetPerSeq( seq );
    m_evpers[row-1].Save();
    UpdateEventaList( m_evpers[row].FGetEventaID() );
}

void rgDlgEditPersona::OnEventaDownButton( wxCommandEvent& event )
{
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _("Row not selected"), _("Name Down") );
        return;
    }
    if( row == m_listEventa->GetItemCount() - 1 ) {
        return; // Already at bottom
    }
    int seq = m_evpers[row].FGetPerSeq();
    m_evpers[row].FSetPerSeq( m_evpers[row+1].FGetPerSeq() );
    m_evpers[row].Save();
    m_evpers[row+1].FSetPerSeq( seq );
    m_evpers[row+1].Save();
    UpdateEventaList( m_evpers[row].FGetEventaID() );
}

void rgDlgEditPersona::OnEventaOrderBy( wxCommandEvent& event )
{
    switch( event.GetSelection() )
    {
    case 0:
        m_order = recEO_PerSeq;
        m_buttonEventaUp->Enable( true );
        m_buttonEventaDn->Enable( true );
        break;
    case 1:
        m_order = recEO_DatePt;
        m_buttonEventaUp->Enable( false );
        m_buttonEventaDn->Enable( false );
        break;
    default:
        return;
    }
    long row = m_listEventa->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    idt eveID = ( row >= 0 ) ? m_evpers[row].FGetEventaID() : 0;
    UpdateEventaList( eveID );
}

void rgDlgEditPersona::IndButtonsEnable( long row )
{
    // Note, there is an extra row for "Other" confidence value
    // which should be ignored for editing if selected.
    if( row < 0 || row == m_listIndividual->GetItemCount() - 1 ) {
        m_buttonIndEdit->Disable();
        m_buttonIndDel->Disable();
        m_buttonIndUp->Disable();
        m_buttonIndDn->Disable();
        return;
    }
    m_buttonIndEdit->Enable();
    m_buttonIndDel->Enable();
    if( row == 0 || row == m_listIndividual->GetItemCount() - 1 ) {
        m_buttonIndUp->Disable();
    }
    else {
        m_buttonIndUp->Enable();
    }
    if( row >= m_listIndividual->GetItemCount() - 2 ) {
        m_buttonIndDn->Disable();
    }
    else {
        m_buttonIndDn->Enable();
    }
}

void rgDlgEditPersona::OnIndDeselect( wxListEvent& event )
{
    IndButtonsEnable( -1 );
}

void rgDlgEditPersona::OnIndSelect( wxListEvent& event )
{
    long row = m_listIndividual->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    IndButtonsEnable( row );
}

void rgDlgEditPersona::OnIndAddButton( wxCommandEvent& event )
{
    unsigned sexfilter = 0;
    if( m_persona.FGetSex() == Sex::male ) {
        sexfilter |= recInd_FILTER_SexMalePlus;
    }
    if( m_persona.FGetSex() == Sex::female ) {
        sexfilter |= recInd_FILTER_SexFemalePlus;
    }
    idt indID = rgSelectIndividual( this, rgSELSTYLE_Create, nullptr, sexfilter );
    if( rgCreateIndividualPersona( this, indID, m_persona.FGetID() ) ) {
        UpdateIndividualList( indID );
    }
}

void rgDlgEditPersona::OnIndEditButton( wxCommandEvent& event )
{
    long row = m_listIndividual->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Edit Individual" ) );
        return;
    }
    idt indID = m_indLinks[row];
    idt ipaID = recIndividualPersona::Find( indID, m_persona.FGetID() );
    if( rgEditIndividualPersona( this, ipaID ) ) {
        UpdateIndividualList( indID );
    }
}

void rgDlgEditPersona::OnIndDeleteButton( wxCommandEvent& event )
{
    long row = m_listIndividual->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    if( row < 0 ) {
        wxMessageBox( _( "No row selected" ), _( "Delete Individual Link" ) );
        return;
    }
    idt indID = m_indLinks[row];
    idt perID = m_persona.FGetID();
    idt ipaID = recIndividualPersona::Find( indID, perID );
    wxString mess = wxString::Format(
        "Remove Link %s from Database?\nIndividual %s: %s\nPersona %s: %s",
        recIndividualPersona::GetIdStr( ipaID),
        recIndividual::GetIdStr( indID ),
        recIndividual::GetNameStr( indID ),
        recPersona::GetIdStr( perID ),
        recPersona::GetNameStr( perID )
        );
    int ans = wxMessageBox( mess, _( "Delete Individual Link" ), wxYES_NO | wxCANCEL, this );
    if( ans != wxYES ) {
        return;
    }
    recIndividualPersona::Delete( ipaID );
    UpdateIndividualList();
}

void rgDlgEditPersona::OnIndUpButton( wxCommandEvent& event )
{
    // TODO: requires recIndividualPersona ind_seq field added
    wxMessageBox( _( "Not yet implimented" ), "OnIndUpButton" );
}

void rgDlgEditPersona::OnIndDownButton( wxCommandEvent& event )
{
    // TODO: requires recIndividualPersona ind_seq field added
    wxMessageBox( _( "Not yet implimented" ), "OnIndDownButton" );
}


//============================================================================
//---------------------------[ rgDlgLinkIndPersona ]--------------------------
//============================================================================

bool rgDlgLinkIndPersona::TransferDataToWindow()
{
    m_staticIndPerID->SetLabel( m_ipa.GetIdStr() );
    wxString indStr = recIndividual::GetIdStr( m_ipa.FGetIndID() ) + ": " +
        recIndividual::GetName( m_ipa.FGetIndID() );
    m_textCtrlInd->SetValue( indStr );
    wxString perStr = recPersona::GetIdStr( m_ipa.FGetPerID() ) + ": " +
        recPersona::GetNameStr( m_ipa.FGetPerID() );
    m_textCtrlPersona->SetValue( perStr );
    idt refID = recPersona::GetRefID( m_ipa.FGetPerID() );
    wxString refStr = recReference::GetIdStr( refID ) + ": " +
        recReference::GetTitle( refID );
    m_textCtrlReference->SetValue( refStr );
    m_textCtrlConf->SetValue( recConfToStr( m_ipa.FGetConf() ) );
    m_textCtrlNote->SetValue( m_ipa.FGetNote() );
    return true;
}

bool rgDlgLinkIndPersona::TransferDataFromWindow()
{
    wxString conf = m_textCtrlConf->GetValue();
    m_ipa.FSetConf( recConfFromStr( conf.ToStdString() ) );   
    m_ipa.FSetNote( m_textCtrlNote->GetValue() );
    m_ipa.Save();
    return true;
}


// End of dlgEdPersona.cpp file
