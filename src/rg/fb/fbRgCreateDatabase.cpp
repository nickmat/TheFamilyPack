///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "fbRgCreateDatabase.h"

///////////////////////////////////////////////////////////////////////////

fbRgCreateDatabase::fbRgCreateDatabase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* m_staticText;
	m_staticText = new wxStaticText( this, wxID_ANY, _("&File Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	bSizer3->Add( m_staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFileName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	bSizer3->Add( m_textCtrlFileName, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_buttonBrowse = new wxButton( this, wxID_ANY, _("&Browse..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonBrowse, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( bSizer3, 0, 0, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxAttach = new wxCheckBox( this, wxID_ANY, _("&Attach to Current"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_checkBoxAttach, 0, wxALL|wxEXPAND, 5 );
	
	wxString m_radioBoxTypeChoices[] = { _("Full"), _("Media Only") };
	int m_radioBoxTypeNChoices = sizeof( m_radioBoxTypeChoices ) / sizeof( wxString );
	m_radioBoxType = new wxRadioBox( this, wxID_ANY, _("&Database Type:"), wxDefaultPosition, wxDefaultSize, m_radioBoxTypeNChoices, m_radioBoxTypeChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxType->SetSelection( 0 );
	bSizer6->Add( m_radioBoxType, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );
	
	wxString m_radioBoxExistsChoices[] = { _("Cancel"), _("Replace"), _("Add Number") };
	int m_radioBoxExistsNChoices = sizeof( m_radioBoxExistsChoices ) / sizeof( wxString );
	m_radioBoxExists = new wxRadioBox( this, wxID_ANY, _("&If Database Exists:"), wxDefaultPosition, wxDefaultSize, m_radioBoxExistsNChoices, m_radioBoxExistsChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxExists->SetSelection( 0 );
	bSizer4->Add( m_radioBoxExists, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxStaticLine* m_staticline;
	m_staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonCreate = new wxButton( this, wxID_ANY, _("C&reate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonCreate, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( bSizer5, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );
	
	// Connect Events
	m_buttonBrowse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnBrowseButton ), NULL, this );
	m_checkBoxAttach->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnCheckAttached ), NULL, this );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnCreateButton ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnCancelButton ), NULL, this );
}

fbRgCreateDatabase::~fbRgCreateDatabase()
{
	// Disconnect Events
	m_buttonBrowse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnBrowseButton ), NULL, this );
	m_checkBoxAttach->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnCheckAttached ), NULL, this );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnCreateButton ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgCreateDatabase::OnCancelButton ), NULL, this );
	
}
