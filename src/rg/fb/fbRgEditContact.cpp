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

	wxStaticText* m_staticText3;
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("&Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 2 );
	bSizer3->Add( m_choiceType, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonAddType = new wxButton( this, wxID_ANY, _("Add/Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_menuAddEditType = new wxMenu();
	wxMenuItem* m_menuAddType;
	m_menuAddType = new wxMenuItem( m_menuAddEditType, wxID_ANY, wxString( _("Add Type") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEditType->Append( m_menuAddType );

	wxMenuItem* m_menuEditType;
	m_menuEditType = new wxMenuItem( m_menuAddEditType, wxID_ANY, wxString( _("Edit Type") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEditType->Append( m_menuEditType );

	m_buttonAddType->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditContact::m_buttonAddTypeOnContextMenu ), NULL, this );

	bSizer3->Add( m_buttonAddType, 0, wxALL, 5 );


	fgSizer11->Add( bSizer3, 1, wxEXPAND, 5 );

	wxStaticText* m_staticText4;
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("&Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,80 ), wxTE_MULTILINE );
	fgSizer11->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );


	bSizer42->Add( fgSizer11, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer42->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticContactID = new wxStaticText( this, wxID_ANY, _("C0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticContactID->Wrap( -1 );
	m_staticContactID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticContactID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer42->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer42 );
	this->Layout();
	bSizer42->Fit( this );

	// Connect Events
	m_buttonAddType->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditContact::OnAddEditButton ), NULL, this );
	m_menuAddEditType->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditContact::OnAddType ), this, m_menuAddType->GetId());
	m_menuAddEditType->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditContact::OnEditType ), this, m_menuEditType->GetId());
}

fbRgEditContact::~fbRgEditContact()
{
	// Disconnect Events
	m_buttonAddType->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditContact::OnAddEditButton ), NULL, this );

	delete m_menuAddEditType;
}

fbRgEditContactType::fbRgEditContactType( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableRow( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText6;
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("&Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer2->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlName->SetMinSize( wxSize( 250,-1 ) );

	fgSizer2->Add( m_textCtrlName, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText7;
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("&UID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer2->Add( m_staticText7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlUid = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer2->Add( m_textCtrlUid, 0, wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	wxStaticText* m_staticText8;
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Last Changed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer2->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlChanged = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer2->Add( m_textCtrlChanged, 0, wxBOTTOM|wxRIGHT|wxEXPAND, 5 );


	bSizer4->Add( fgSizer2, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline1, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticContactTypeID = new wxStaticText( this, wxID_ANY, _("CT0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticContactTypeID->Wrap( -1 );
	m_staticContactTypeID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticContactTypeID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer4->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );

	this->Centre( wxBOTH );
}

fbRgEditContactType::~fbRgEditContactType()
{
}
