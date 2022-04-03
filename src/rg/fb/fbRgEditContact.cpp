///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "fbRgEditContact.h"

///////////////////////////////////////////////////////////////////////////

fbRgEditContact::fbRgEditContact( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->AddGrowableRow( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 2 );
	fgSizer11->Add( m_choiceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALIGN_RIGHT|wxALL, 5 );

	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,80 ), wxTE_MULTILINE );
	fgSizer11->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );


	bSizer42->Add( fgSizer11, 1, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer42->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticContactID = new wxStaticText( this, wxID_ANY, _("C0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticContactID->Wrap( -1 );
	m_staticContactID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticContactID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer42->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer42 );
	this->Layout();
	bSizer42->Fit( this );
}

fbRgEditContact::~fbRgEditContact()
{
}
