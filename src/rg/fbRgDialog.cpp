///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
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


#include "rgTableCtrl.h"

#include "fbRgDialog.h"

///////////////////////////////////////////////////////////////////////////

fbRgCreateName::fbRgCreateName( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer7->Add( m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	fgSizer7->Add( m_choiceType, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Given Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer7->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlGiven = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	fgSizer7->Add( m_textCtrlGiven, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Surname:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer7->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSurname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	fgSizer7->Add( m_textCtrlSurname, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer7, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticNameID = new wxStaticText( this, wxID_ANY, _("N0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNameID->Wrap( -1 );
	m_staticNameID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticNameID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

fbRgCreateName::~fbRgCreateName()
{
}

fbRgEditName::fbRgEditName( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer11->Add( m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticName->Wrap( -1 );
	m_staticName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer11->Add( m_staticName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer11->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	fgSizer11->Add( m_choiceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer11, 0, 0, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listNamePart = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listNamePart->SetMinSize( wxSize( 300,150 ) );
	
	bSizer12->Add( m_listNamePart, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonPartAdd = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_buttonPartAdd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonPartEdit = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_buttonPartEdit, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonPartDel = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_buttonPartDel, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonPartUp = new wxButton( this, wxID_ANY, _("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonPartUp->SetMinSize( wxSize( 35,-1 ) );
	
	bSizer38->Add( m_buttonPartUp, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonPartDown = new wxButton( this, wxID_ANY, _("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonPartDown->SetMinSize( wxSize( 35,-1 ) );
	
	bSizer38->Add( m_buttonPartDown, 1, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer37->Add( bSizer38, 0, wxEXPAND, 5 );
	
	
	bSizer12->Add( bSizer37, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer12, 1, wxEXPAND, 5 );
	
	m_staticline12 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline12, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticNameID = new wxStaticText( this, wxID_ANY, _("N0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNameID->Wrap( -1 );
	m_staticNameID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticNameID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonPartAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartAddButton ), NULL, this );
	m_buttonPartEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartEditButton ), NULL, this );
	m_buttonPartDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartDeleteButton ), NULL, this );
	m_buttonPartUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartUpButton ), NULL, this );
	m_buttonPartDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartDownButton ), NULL, this );
}

fbRgEditName::~fbRgEditName()
{
	// Disconnect Events
	m_buttonPartAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartAddButton ), NULL, this );
	m_buttonPartEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartEditButton ), NULL, this );
	m_buttonPartDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartDeleteButton ), NULL, this );
	m_buttonPartUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartUpButton ), NULL, this );
	m_buttonPartDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditName::OnPartDownButton ), NULL, this );
	
}

fbRgEditNamePart::fbRgEditNamePart( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer7->Add( m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	fgSizer7->Add( m_choiceType, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer7->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	fgSizer7->Add( m_textCtrlValue, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer7, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticNamePartID = new wxStaticText( this, wxID_ANY, _("NP0:N0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNamePartID->Wrap( -1 );
	m_staticNamePartID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticNamePartID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

fbRgEditNamePart::~fbRgEditNamePart()
{
}

fbRgEditDate::fbRgEditDate( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Output:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer11->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticOutput = new wxStaticText( this, wxID_ANY, _("Date String"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticOutput->Wrap( -1 );
	m_staticOutput->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer11->Add( m_staticOutput, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Calendar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer11->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceDisplayChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 3 );
	fgSizer11->Add( m_choiceDisplay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Precision:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceTypeChoices[] = { _("After"), _("On"), _("On or after"), _("Before"), _("Not"), _("On or before"), _("About") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 1 );
	fgSizer11->Add( m_choiceType, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Input Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	fgSizer11->Add( m_textCtrlDate, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Calendar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer11->Add( m_staticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceInputChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceInputNChoices = sizeof( m_choiceInputChoices ) / sizeof( wxString );
	m_choiceInput = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceInputNChoices, m_choiceInputChoices, 0 );
	m_choiceInput->SetSelection( 3 );
	fgSizer11->Add( m_choiceInput, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer11, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticDateID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticDateID->Wrap( -1 );
	m_staticDateID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticDateID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditDate::OnIdle ) );
}

fbRgEditDate::~fbRgEditDate()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditDate::OnIdle ) );
	
}

fbRgEditRelativeDate::fbRgEditRelativeDate( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Output:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer11->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticOutput = new wxStaticText( this, wxID_ANY, _("Date String"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticOutput->Wrap( -1 );
	m_staticOutput->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer11->Add( m_staticOutput, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Output calendar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer11->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceDisplayChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 3 );
	fgSizer11->Add( m_choiceDisplay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Calculation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Age, round down"), _("Duration"), _("Add to start"), _("Add to end") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	fgSizer11->Add( m_choiceType, 0, wxALL, 5 );
	
	m_buttonBase = new wxButton( this, wxID_ANY, _("Base Date:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer11->Add( m_buttonBase, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBase = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), wxTE_READONLY );
	m_textCtrlBase->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer11->Add( m_textCtrlBase, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAge = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( m_textCtrlAge, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Calendar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer11->Add( m_staticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceInputChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceInputNChoices = sizeof( m_choiceInputChoices ) / sizeof( wxString );
	m_choiceInput = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceInputNChoices, m_choiceInputChoices, 0 );
	m_choiceInput->SetSelection( 3 );
	fgSizer11->Add( m_choiceInput, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer11, 0, wxEXPAND, 5 );
	
	wxString m_radioUnitsChoices[] = { _("Years"), _("Months"), _("Weeks"), _("Days") };
	int m_radioUnitsNChoices = sizeof( m_radioUnitsChoices ) / sizeof( wxString );
	m_radioUnits = new wxRadioBox( this, wxID_ANY, _("Unit:"), wxDefaultPosition, wxDefaultSize, m_radioUnitsNChoices, m_radioUnitsChoices, 1, wxRA_SPECIFY_ROWS );
	m_radioUnits->SetSelection( 0 );
	bSizer1->Add( m_radioUnits, 0, wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticDateID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticDateID->Wrap( -1 );
	m_staticDateID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticDateID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditRelativeDate::OnIdle ) );
	m_buttonBase->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRelativeDate::OnBaseButton ), NULL, this );
}

fbRgEditRelativeDate::~fbRgEditRelativeDate()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditRelativeDate::OnIdle ) );
	m_buttonBase->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRelativeDate::OnBaseButton ), NULL, this );
	
}

fbRgEditPlace::fbRgEditPlace( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Place:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer11->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAddr = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	m_textCtrlAddr->SetMaxLength( 0 ); 
	bSizer11->Add( m_textCtrlAddr, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer11, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticPlaceID = new wxStaticText( this, wxID_ANY, _("P0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPlaceID->Wrap( -1 );
	m_staticPlaceID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticPlaceID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

fbRgEditPlace::~fbRgEditPlace()
{
}

fbRgPerIndEvent::fbRgPerIndEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 3 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticPerInd = new wxStaticText( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerInd->Wrap( -1 );
	fgSizer3->Add( m_staticPerInd, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticName->Wrap( -1 );
	m_staticName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer12->Add( m_staticName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticNameID = new wxStaticText( this, wxID_ANY, _("I0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNameID->Wrap( -1 );
	m_staticNameID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxEmptyString ) );
	
	bSizer12->Add( m_staticNameID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer3->Add( bSizer12, 1, wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Event:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticEvent = new wxStaticText( this, wxID_ANY, _("Birth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEvent->Wrap( -1 );
	m_staticEvent->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer13->Add( m_staticEvent, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticEventID = new wxStaticText( this, wxID_ANY, _("E0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventID->Wrap( -1 );
	m_staticEventID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxEmptyString ) );
	
	bSizer13->Add( m_staticEventID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer3->Add( bSizer13, 1, wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Role:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_choiceRoleChoices;
	m_choiceRole = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceRoleChoices, 0 );
	m_choiceRole->SetSelection( 0 );
	bSizer14->Add( m_choiceRole, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonAdd = new wxButton( this, wxID_ANY, _("Add Role"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonAdd, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer3->Add( bSizer14, 1, wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	m_textCtrlNote->SetMaxLength( 0 ); 
	fgSizer3->Add( m_textCtrlNote, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticRoleID = new wxStaticText( this, wxID_ANY, _("IE0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRoleID->Wrap( -1 );
	m_staticRoleID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxEmptyString ) );
	
	bSizerDismiss->Add( m_staticRoleID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	// Connect Events
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgPerIndEvent::OnAddRoleButton ), NULL, this );
}

fbRgPerIndEvent::~fbRgPerIndEvent()
{
	// Disconnect Events
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgPerIndEvent::OnAddRoleButton ), NULL, this );
	
}

fbRgEditEventType::fbRgEditEventType( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxArrayString m_choiceGroupChoices;
	m_choiceGroup = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceGroupChoices, 0 );
	m_choiceGroup->SetSelection( 0 );
	fgSizer11->Add( m_choiceGroup, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlValue->SetMaxLength( 0 ); 
	fgSizer11->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( fgSizer11, 0, wxEXPAND, 5 );
	
	m_listRole = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer1->Add( m_listRole, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonRoleAdd = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonRoleAdd, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonRoleEdit = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonRoleEdit, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonRoleDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonRoleDelete, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer16, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTypeID = new wxStaticText( this, wxID_ANY, _("ET0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTypeID->Wrap( -1 );
	m_staticTypeID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticTypeID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_buttonRoleAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventType::OnButtonRoleAdd ), NULL, this );
	m_buttonRoleEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventType::OnButtonRoleEdit ), NULL, this );
	m_buttonRoleDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventType::OnButtonRoleDelete ), NULL, this );
}

fbRgEditEventType::~fbRgEditEventType()
{
	// Disconnect Events
	m_buttonRoleAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventType::OnButtonRoleAdd ), NULL, this );
	m_buttonRoleEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventType::OnButtonRoleEdit ), NULL, this );
	m_buttonRoleDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventType::OnButtonRoleDelete ), NULL, this );
	
}

fbRgEditRole::fbRgEditRole( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Event:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 74, 90, 90, false, wxT("MS Shell Dlg 2") ) );
	
	fgSizer11->Add( m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5 );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticEventType = new wxStaticText( this, wxID_ANY, _("Event Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventType->Wrap( -1 );
	m_staticEventType->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 74, 90, 92, false, wxT("MS Shell Dlg 2") ) );
	
	bSizer111->Add( m_staticEventType, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer111->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticEventTypeID = new wxStaticText( this, wxID_ANY, _("ET0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventTypeID->Wrap( -1 );
	m_staticEventTypeID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizer111->Add( m_staticEventTypeID, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	fgSizer11->Add( bSizer111, 1, wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 74, 90, 90, false, wxT("MS Shell Dlg 2") ) );
	
	fgSizer11->Add( m_staticText2, 0, wxALL, 5 );
	
	m_staticTypeGroup = new wxStaticText( this, wxID_ANY, _("Type Group"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTypeGroup->Wrap( -1 );
	m_staticTypeGroup->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 74, 90, 92, false, wxT("MS Shell Dlg 2") ) );
	
	fgSizer11->Add( m_staticTypeGroup, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Role:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlValue->SetMaxLength( 0 ); 
	fgSizer11->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Prime:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_choicePrimeChoices;
	m_choicePrime = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choicePrimeChoices, 0 );
	m_choicePrime->SetSelection( 0 );
	bSizer112->Add( m_choicePrime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkOfficial = new wxCheckBox( this, wxID_ANY, _("Official"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer112->Add( m_checkOfficial, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer112->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer11->Add( bSizer112, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( fgSizer11, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticRoleID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRoleID->Wrap( -1 );
	m_staticRoleID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticRoleID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_choicePrime->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fbRgEditRole::OnChoicePrime ), NULL, this );
}

fbRgEditRole::~fbRgEditRole()
{
	// Disconnect Events
	m_choicePrime->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fbRgEditRole::OnChoicePrime ), NULL, this );
	
}

fbRgSelect::fbRgSelect( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listCtrl = new rgStrTableCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,300 ), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL|wxLC_VRULES|wxALWAYS_SHOW_SB|wxVSCROLL );
	bSizer2->Add( m_listCtrl, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonCreate = new wxButton( this, wxID_ANY, _("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCreate, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonFilter = new wxButton( this, wxID_ANY, _("Filter"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonFilter, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonUnknown = new wxButton( this, wxID_ANY, _("Unknown"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonUnknown, 0, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 10 );
	
	m_buttonSelect = new wxButton( this, wxID_OK, _("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSelect, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgSelect::OnIdle ) );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelect::OnCreateButton ), NULL, this );
	m_buttonFilter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelect::OnFilterButton ), NULL, this );
	m_buttonUnknown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelect::OnUnknownButton ), NULL, this );
}

fbRgSelect::~fbRgSelect()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgSelect::OnIdle ) );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelect::OnCreateButton ), NULL, this );
	m_buttonFilter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelect::OnFilterButton ), NULL, this );
	m_buttonUnknown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelect::OnUnknownButton ), NULL, this );
	
}

fbRgSelectIndEvent::fbRgSelectIndEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Event Group") ), wxHORIZONTAL );
	
	wxArrayString m_checkListGrpChoices;
	m_checkListGrp = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( -1,110 ), m_checkListGrpChoices, wxLB_NEEDED_SB );
	sbSizer1->Add( m_checkListGrp, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonSelectGrp = new wxButton( this, wxID_ANY, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonSelectGrp, 0, wxALL, 5 );
	
	m_buttonClearGrp = new wxButton( this, wxID_ANY, _("Clear All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonClearGrp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	sbSizer1->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	bSizer28->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Date Points") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer13->AddGrowableCol( 1 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText37 = new wxStaticText( this, wxID_ANY, _("Dates After:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	fgSizer13->Add( m_staticText37, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textCtrlBegDatePt = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer13->Add( m_textCtrlBegDatePt, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText38 = new wxStaticText( this, wxID_ANY, _("Dates Before:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	fgSizer13->Add( m_staticText38, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlEndDatePt = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer13->Add( m_textCtrlEndDatePt, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizer3->Add( fgSizer13, 0, wxEXPAND, 5 );
	
	
	bSizer28->Add( sbSizer3, 0, wxEXPAND, 5 );
	
	
	bSizer27->Add( bSizer28, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Event Type") ), wxHORIZONTAL );
	
	wxArrayString m_checkListTypeChoices;
	m_checkListType = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( -1,110 ), m_checkListTypeChoices, wxLB_NEEDED_SB );
	sbSizer2->Add( m_checkListType, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonSelectType = new wxButton( this, wxID_ANY, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonSelectType, 0, wxALL, 5 );
	
	m_buttonClearType = new wxButton( this, wxID_ANY, _("Clear All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonClearType, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	sbSizer2->Add( bSizer12, 1, wxEXPAND, 0 );
	
	
	bSizer27->Add( sbSizer2, 1, wxEXPAND|wxLEFT, 5 );
	
	
	bSizer1->Add( bSizer27, 1, wxEXPAND, 0 );
	
	m_listEvent = new rgRecEventTableCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL );
	bSizer1->Add( m_listEvent, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline8 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline8, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonCreate = new wxButton( this, wxID_ANY, _("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCreate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticEventCount = new wxStaticText( this, wxID_ANY, _("0 Events"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventCount->Wrap( -1 );
	bSizerDismiss->Add( m_staticEventCount, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSelect = new wxButton( this, wxID_OK, _("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSelect, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgSelectIndEvent::OnIdle ) );
	m_checkListGrp->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectIndEvent::OnGroupCheckSelect ), NULL, this );
	m_checkListGrp->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectIndEvent::OnGroupCheckToggled ), NULL, this );
	m_buttonSelectGrp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonGroupSelectAll ), NULL, this );
	m_buttonClearGrp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonGroupClearAll ), NULL, this );
	m_textCtrlBegDatePt->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectIndEvent::OnBegDateText ), NULL, this );
	m_textCtrlEndDatePt->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectIndEvent::OnEndDateText ), NULL, this );
	m_checkListType->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectIndEvent::OnTypeCheckSelect ), NULL, this );
	m_checkListType->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectIndEvent::OnTypeCheckToggled ), NULL, this );
	m_buttonSelectType->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonTypeSelectAll ), NULL, this );
	m_buttonClearType->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonTypeClearAll ), NULL, this );
	m_listEvent->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgSelectIndEvent::OnListEventItemDeselected ), NULL, this );
	m_listEvent->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgSelectIndEvent::OnListEventItemSelected ), NULL, this );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnCreateButton ), NULL, this );
}

fbRgSelectIndEvent::~fbRgSelectIndEvent()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgSelectIndEvent::OnIdle ) );
	m_checkListGrp->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectIndEvent::OnGroupCheckSelect ), NULL, this );
	m_checkListGrp->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectIndEvent::OnGroupCheckToggled ), NULL, this );
	m_buttonSelectGrp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonGroupSelectAll ), NULL, this );
	m_buttonClearGrp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonGroupClearAll ), NULL, this );
	m_textCtrlBegDatePt->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectIndEvent::OnBegDateText ), NULL, this );
	m_textCtrlEndDatePt->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectIndEvent::OnEndDateText ), NULL, this );
	m_checkListType->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectIndEvent::OnTypeCheckSelect ), NULL, this );
	m_checkListType->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectIndEvent::OnTypeCheckToggled ), NULL, this );
	m_buttonSelectType->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonTypeSelectAll ), NULL, this );
	m_buttonClearType->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnButtonTypeClearAll ), NULL, this );
	m_listEvent->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgSelectIndEvent::OnListEventItemDeselected ), NULL, this );
	m_listEvent->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgSelectIndEvent::OnListEventItemSelected ), NULL, this );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectIndEvent::OnCreateButton ), NULL, this );
	
}

fbRgEditEvent::fbRgEditEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditEvent::m_splitter1OnIdle ), NULL, this );
	m_splitter1->SetMinimumPaneSize( 1 );
	
	m_panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 6, 2, 0, 0 );
	fgSizer10->AddGrowableCol( 1 );
	fgSizer10->AddGrowableRow( 5 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, _("Event Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer10->Add( m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticType = new wxStaticText( m_panel1, wxID_ANY, _("Birth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticType->Wrap( -1 );
	m_staticType->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer10->Add( m_staticType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer10->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonDate1 = new wxButton( m_panel1, wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer10->Add( m_buttonDate1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDate1 = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_textCtrlDate1, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonDate2 = new wxButton( m_panel1, wxID_ANY, _("End Date:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer10->Add( m_buttonDate2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDate2 = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_textCtrlDate2, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPlace = new wxButton( m_panel1, wxID_ANY, _("Place:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer10->Add( m_buttonPlace, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPlace = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_textCtrlPlace, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( m_panel1, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer10->Add( m_staticText6, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlNote = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textCtrlNote->SetMinSize( wxSize( -1,50 ) );
	
	fgSizer10->Add( m_textCtrlNote, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( fgSizer10 );
	m_panel1->Layout();
	fgSizer10->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_listPersona = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listPersona->SetMinSize( wxSize( 400,100 ) );
	
	bSizer21->Add( m_listPersona, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAdd = new wxButton( m_panel2, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer211->Add( m_buttonAdd, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonEdit = new wxButton( m_panel2, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer211->Add( m_buttonEdit, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_buttonDelete = new wxButton( m_panel2, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer211->Add( m_buttonDelete, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer21->Add( bSizer211, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer21 );
	m_panel2->Layout();
	bSizer21->Fit( m_panel2 );
	m_splitter1->SplitHorizontally( m_panel1, m_panel2, 0 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	m_staticline12 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline12, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticEventID = new wxStaticText( this, wxID_ANY, _("E0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventID->Wrap( -1 );
	m_staticEventID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticEventID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonDate1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDate1Button ), NULL, this );
	m_buttonDate2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDate2Button ), NULL, this );
	m_buttonPlace->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnPlaceButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnEditButton ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDeleteButton ), NULL, this );
}

fbRgEditEvent::~fbRgEditEvent()
{
	// Disconnect Events
	m_buttonDate1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDate1Button ), NULL, this );
	m_buttonDate2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDate2Button ), NULL, this );
	m_buttonPlace->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnPlaceButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnEditButton ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDeleteButton ), NULL, this );
	
}
