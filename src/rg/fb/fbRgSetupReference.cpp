///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
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


#include "fbRgSetupReference.h"

///////////////////////////////////////////////////////////////////////////

fbRgSetupReferenceDialog::fbRgSetupReferenceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_listMedia = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer20->Add( m_listMedia, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );

	wxBoxSizer* bSizer571;
	bSizer571 = new wxBoxSizer( wxVERTICAL );

	m_buttonMediaAdd = new wxButton( this, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_buttonMediaEdit = new wxButton( this, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_buttonMediaDel = new wxButton( this, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizer571->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonMediaView = new wxButton( this, wxID_ANY, _("&View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaView, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer20->Add( bSizer571, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer20, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText6;
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Template:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer2->Add( m_staticText6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );

	m_textCtrlTemplate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlTemplate, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxLEFT, 5 );

	m_buttonTemplateBrowse = new wxButton( this, wxID_ANY, _("&Browse..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_buttonTemplateBrowse, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	wxStaticText* m_staticText7;
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Ref. Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer2->Add( m_staticText7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlRefTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlRefTitle, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxLEFT, 5 );


	bSizer16->Add( fgSizer2, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer16->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticRefID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRefID->Wrap( -1 );
	m_staticRefID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticRefID, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave1 = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizer16->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer16 );
	this->Layout();
	bSizer16->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_listMedia->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgSetupReferenceDialog::OnMediaDeselect ), NULL, this );
	m_listMedia->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgSetupReferenceDialog::OnMediaSelect ), NULL, this );
	m_buttonMediaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaAddButton ), NULL, this );
	m_buttonMediaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaEditButton ), NULL, this );
	m_buttonMediaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaDeleteButton ), NULL, this );
	m_buttonMediaView->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaView ), NULL, this );
	m_buttonTemplateBrowse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnTemplateBrowse ), NULL, this );
}

fbRgSetupReferenceDialog::~fbRgSetupReferenceDialog()
{
	// Disconnect Events
	m_listMedia->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgSetupReferenceDialog::OnMediaDeselect ), NULL, this );
	m_listMedia->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgSetupReferenceDialog::OnMediaSelect ), NULL, this );
	m_buttonMediaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaAddButton ), NULL, this );
	m_buttonMediaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaEditButton ), NULL, this );
	m_buttonMediaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaDeleteButton ), NULL, this );
	m_buttonMediaView->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnMediaView ), NULL, this );
	m_buttonTemplateBrowse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSetupReferenceDialog::OnTemplateBrowse ), NULL, this );

}
