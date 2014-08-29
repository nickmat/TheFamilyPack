///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
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

#include "../img/ed/copy.xpm"
#include "../img/ed/cut.xpm"
#include "../img/ed/paste.xpm"
#include "../img/ed/redo.xpm"
#include "../img/ed/undo.xpm"

///////////////////////////////////////////////////////////////////////////

fbRgCreateIndividual::fbRgCreateIndividual( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer92->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticName->Wrap( -1 );
	m_staticName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer92->Add( m_staticName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer92->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer92->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	bSizer92->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer91->Add( bSizer92, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer16->AddGrowableCol( 1 );
	fgSizer16->AddGrowableRow( 2 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, _("Given Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer16->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textGiven = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_textGiven->SetMaxLength( 0 ); 
	fgSizer16->Add( m_textGiven, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, _("Surname:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer16->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textSurname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_textSurname->SetMaxLength( 0 ); 
	fgSizer16->Add( m_textSurname, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer16->Add( m_staticText23, 0, wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,50 ), wxTE_MULTILINE );
	fgSizer16->Add( m_textNote, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer91->Add( fgSizer16, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer91->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticIndID = new wxStaticText( this, wxID_ANY, _("I0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndID->Wrap( -1 );
	m_staticIndID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticIndID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer91->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer91 );
	this->Layout();
	bSizer91->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgCreateIndividual::OnIdle ) );
}

fbRgCreateIndividual::~fbRgCreateIndividual()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgCreateIndividual::OnIdle ) );
	
}

fbRgCreateName::fbRgCreateName( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->AddGrowableCol( 1 );
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
	
	m_textCtrlGiven = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 280,-1 ), 0 );
	fgSizer7->Add( m_textCtrlGiven, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Surname:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer7->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSurname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	fgSizer7->Add( m_textCtrlSurname, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer1->Add( fgSizer7, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_checkFullName = new wxCheckBox( this, wxID_ANY, _("Edit Full Name"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer20->Add( m_checkFullName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	m_staticNameID = new wxStaticText( this, wxID_ANY, _("N0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNameID->Wrap( -1 );
	m_staticNameID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	fgSizer20->Add( m_staticNameID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	m_checkExtend = new wxCheckBox( this, wxID_ANY, _("Edit Persona"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer20->Add( m_checkExtend, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 2 );
	
	m_staticPerIndID = new wxStaticText( this, wxID_ANY, _("Pa0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerIndID->Wrap( -1 );
	m_staticPerIndID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	fgSizer20->Add( m_staticPerIndID, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 2 );
	
	
	bSizerDismiss->Add( fgSizer20, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
}

fbRgCreateName::~fbRgCreateName()
{
}

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
	m_staticContactID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
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
	
	wxString m_choiceDisplayChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian"), _("French Revolutionary") };
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
	
	wxString m_choiceInputChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian"), _("French Revolutionary") };
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

fbRgEditEvent::fbRgEditEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer114->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 350,-1 ), 0 );
	bSizer114->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer114, 0, wxEXPAND, 5 );
	
	m_notebook6 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	
	
	m_panel1->SetSizer( fgSizer10 );
	m_panel1->Layout();
	fgSizer10->Fit( m_panel1 );
	m_notebook6->AddPage( m_panel1, _("Details"), true );
	m_panel23 = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer115;
	bSizer115 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrlNote = new wxTextCtrl( m_panel23, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE );
	bSizer115->Add( m_textCtrlNote, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	m_panel23->SetSizer( bSizer115 );
	m_panel23->Layout();
	bSizer115->Fit( m_panel23 );
	m_notebook6->AddPage( m_panel23, _("Note"), false );
	m_panel2 = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_listIndividual = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxSize( 400,100 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer21->Add( m_listIndividual, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer211->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonAddInd = new wxButton( m_panel2, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer211->Add( m_buttonAddInd, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonEditInd = new wxButton( m_panel2, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer211->Add( m_buttonEditInd, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_buttonDelInd = new wxButton( m_panel2, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer211->Add( m_buttonDelInd, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer21->Add( bSizer211, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer21 );
	m_panel2->Layout();
	bSizer21->Fit( m_panel2 );
	m_notebook6->AddPage( m_panel2, _("Individuals"), false );
	m_panel24 = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer212;
	bSizer212 = new wxBoxSizer( wxVERTICAL );
	
	m_listRecord = new wxListCtrl( m_panel24, wxID_ANY, wxDefaultPosition, wxSize( 400,100 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer212->Add( m_listRecord, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2111;
	bSizer2111 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer2111->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonAddRec = new wxButton( m_panel24, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2111->Add( m_buttonAddRec, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonEditRec = new wxButton( m_panel24, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2111->Add( m_buttonEditRec, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_buttonDelRec = new wxButton( m_panel24, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2111->Add( m_buttonDelRec, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer212->Add( bSizer2111, 0, wxEXPAND, 5 );
	
	
	m_panel24->SetSizer( bSizer212 );
	m_panel24->Layout();
	bSizer212->Fit( m_panel24 );
	m_notebook6->AddPage( m_panel24, _("Records"), false );
	
	bSizer1->Add( m_notebook6, 1, wxEXPAND | wxALL, 5 );
	
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
	m_buttonAddInd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnAddInd ), NULL, this );
	m_buttonEditInd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnEditInd ), NULL, this );
	m_buttonDelInd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDeleteInd ), NULL, this );
	m_buttonAddRec->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnAddRecord ), NULL, this );
	m_buttonEditRec->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnEditRecord ), NULL, this );
	m_buttonDelRec->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDeleteRecord ), NULL, this );
}

fbRgEditEvent::~fbRgEditEvent()
{
	// Disconnect Events
	m_buttonDate1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDate1Button ), NULL, this );
	m_buttonDate2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDate2Button ), NULL, this );
	m_buttonPlace->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnPlaceButton ), NULL, this );
	m_buttonAddInd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnAddInd ), NULL, this );
	m_buttonEditInd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnEditInd ), NULL, this );
	m_buttonDelInd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDeleteInd ), NULL, this );
	m_buttonAddRec->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnAddRecord ), NULL, this );
	m_buttonEditRec->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnEditRecord ), NULL, this );
	m_buttonDelRec->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEvent::OnDeleteRecord ), NULL, this );
	
}

fbRgEditEventEventum::fbRgEditEventEventum( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 4 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Event:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer3->Add( m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticEvent = new wxStaticText( this, wxID_ANY, _("E0: Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEvent->Wrap( -1 );
	m_staticEvent->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticEvent, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Eventum:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticEventum = new wxStaticText( this, wxID_ANY, _("Em0: Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventum->Wrap( -1 );
	m_staticEventum->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticEventum, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Reference:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticRef = new wxStaticText( this, wxID_ANY, _("R0: Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRef->Wrap( -1 );
	m_staticRef->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticRef, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Confidence:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlConf = new wxTextCtrl( this, wxID_ANY, _("0.999"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_textCtrlConf, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer3->Add( m_staticText5, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,50 ), wxTE_MULTILINE|wxTE_WORDWRAP );
	fgSizer3->Add( m_textCtrlNote, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticEvEvRecID = new wxStaticText( this, wxID_ANY, _("EEm0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEvEvRecID->Wrap( -1 );
	m_staticEvEvRecID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxEmptyString ) );
	
	bSizerDismiss->Add( m_staticEvEvRecID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
	bSizer11->Fit( this );
}

fbRgEditEventEventum::~fbRgEditEventEventum()
{
}

fbRgEditEventum::fbRgEditEventum( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer118->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 350,-1 ), 0 );
	bSizer118->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer118, 0, wxEXPAND, 5 );
	
	m_notebook7 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	
	m_buttonDate1 = new wxButton( m_panel1, wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer10->Add( m_buttonDate1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticDate1 = new wxStaticText( m_panel1, wxID_ANY, _("Date1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticDate1->Wrap( -1 );
	fgSizer10->Add( m_staticDate1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDate2 = new wxButton( m_panel1, wxID_ANY, _("End Date:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer10->Add( m_buttonDate2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticDate2 = new wxStaticText( m_panel1, wxID_ANY, _("Date2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticDate2->Wrap( -1 );
	fgSizer10->Add( m_staticDate2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonPlace = new wxButton( m_panel1, wxID_ANY, _("Place:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer10->Add( m_buttonPlace, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticPlace = new wxStaticText( m_panel1, wxID_ANY, _("Place"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPlace->Wrap( -1 );
	fgSizer10->Add( m_staticPlace, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_panel1->SetSizer( fgSizer10 );
	m_panel1->Layout();
	fgSizer10->Fit( m_panel1 );
	m_notebook7->AddPage( m_panel1, _("Details"), true );
	m_panel25 = new wxPanel( m_notebook7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrlNote = new wxTextCtrl( m_panel25, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE );
	bSizer120->Add( m_textCtrlNote, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	m_panel25->SetSizer( bSizer120 );
	m_panel25->Layout();
	bSizer120->Fit( m_panel25 );
	m_notebook7->AddPage( m_panel25, _("Note"), false );
	m_panel2 = new wxPanel( m_notebook7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_listPersona = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxSize( 400,100 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer21->Add( m_listPersona, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer211->Add( 0, 0, 1, wxEXPAND, 5 );
	
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
	m_notebook7->AddPage( m_panel2, _("Persona"), false );
	m_panel26 = new wxPanel( m_notebook7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer212;
	bSizer212 = new wxBoxSizer( wxVERTICAL );
	
	m_listConclusion = new wxListCtrl( m_panel26, wxID_ANY, wxDefaultPosition, wxSize( 400,100 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer212->Add( m_listConclusion, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2111;
	bSizer2111 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer2111->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonAddCon = new wxButton( m_panel26, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2111->Add( m_buttonAddCon, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonEditCon = new wxButton( m_panel26, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2111->Add( m_buttonEditCon, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_buttonDeleteCon = new wxButton( m_panel26, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2111->Add( m_buttonDeleteCon, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer212->Add( bSizer2111, 0, wxEXPAND, 5 );
	
	
	m_panel26->SetSizer( bSizer212 );
	m_panel26->Layout();
	bSizer212->Fit( m_panel26 );
	m_notebook7->AddPage( m_panel26, _("Conclusions"), false );
	
	bSizer1->Add( m_notebook7, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline12 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline12, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticEventumID = new wxStaticText( this, wxID_ANY, _("Em0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventumID->Wrap( -1 );
	m_staticEventumID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticEventumID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	m_buttonDate1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDate1Button ), NULL, this );
	m_buttonDate2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDate2Button ), NULL, this );
	m_buttonPlace->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnPlaceButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnAddPer ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnEditPer ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDeletePer ), NULL, this );
	m_buttonAddCon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnAddCon ), NULL, this );
	m_buttonEditCon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnEditCon ), NULL, this );
	m_buttonDeleteCon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDeleteCon ), NULL, this );
}

fbRgEditEventum::~fbRgEditEventum()
{
	// Disconnect Events
	m_buttonDate1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDate1Button ), NULL, this );
	m_buttonDate2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDate2Button ), NULL, this );
	m_buttonPlace->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnPlaceButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnAddPer ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnEditPer ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDeletePer ), NULL, this );
	m_buttonAddCon->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnAddCon ), NULL, this );
	m_buttonEditCon->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnEditCon ), NULL, this );
	m_buttonDeleteCon->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditEventum::OnDeleteCon ), NULL, this );
	
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
	
	m_listRole = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 300,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL );
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
	bSizer1->Fit( this );
	
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

fbRgEditFamily::fbRgEditFamily( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer117;
	bSizer117 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticNames = new wxStaticText( this, wxID_ANY, _("Name and Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNames->Wrap( -1 );
	m_staticNames->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer118->Add( m_staticNames, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer117->Add( bSizer118, 0, wxEXPAND, 5 );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel17 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer17->AddGrowableCol( 1 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_buttonHusb = new wxButton( m_panel17, wxID_ANY, _("Husband:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer17->Add( m_buttonHusb, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALIGN_RIGHT|wxALL, 5 );
	
	m_staticHusbName = new wxStaticText( m_panel17, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticHusbName->Wrap( -1 );
	fgSizer17->Add( m_staticHusbName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonWife = new wxButton( m_panel17, wxID_ANY, _("Wife:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer17->Add( m_buttonWife, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticWifeName = new wxStaticText( m_panel17, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticWifeName->Wrap( -1 );
	fgSizer17->Add( m_staticWifeName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_panel17->SetSizer( fgSizer17 );
	m_panel17->Layout();
	fgSizer17->Fit( m_panel17 );
	m_notebook->AddPage( m_panel17, _("Family"), true );
	m_panel211 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listChildren = new wxListCtrl( m_panel211, wxID_ANY, wxDefaultPosition, wxSize( 350,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer119->Add( m_listChildren, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( m_panel211, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer120->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( m_panel211, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer120->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonDel = new wxButton( m_panel211, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer120->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( m_panel211, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer121->Add( m_buttonUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer121->Add( 0, 0, 1, wxEXPAND, 0 );
	
	m_buttonDn = new wxButton( m_panel211, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer121->Add( m_buttonDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer120->Add( bSizer121, 1, wxEXPAND, 5 );
	
	
	bSizer119->Add( bSizer120, 0, wxEXPAND, 5 );
	
	
	m_panel211->SetSizer( bSizer119 );
	m_panel211->Layout();
	bSizer119->Fit( m_panel211 );
	m_notebook->AddPage( m_panel211, _("Children"), false );
	m_panel21 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEvent = new wxListCtrl( m_panel21, wxID_ANY, wxDefaultPosition, wxSize( 350,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer122->Add( m_listEvent, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxBoxSizer* bSizer123;
	bSizer123 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEventAdd = new wxButton( m_panel21, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer123->Add( m_buttonEventAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventEdit = new wxButton( m_panel21, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer123->Add( m_buttonEventEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonEventDel = new wxButton( m_panel21, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer123->Add( m_buttonEventDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer1211;
	bSizer1211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonEventUp = new wxButton( m_panel21, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventUp->Enable( false );
	
	bSizer1211->Add( m_buttonEventUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer1211->Add( 0, 0, 1, wxEXPAND, 0 );
	
	m_buttonEventDn = new wxButton( m_panel21, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventDn->Enable( false );
	
	bSizer1211->Add( m_buttonEventDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer123->Add( bSizer1211, 1, wxEXPAND, 5 );
	
	wxString m_radioBox3Choices[] = { _("Date Point"), _("Preference") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( m_panel21, wxID_ANY, _("Order by:-"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox3->SetSelection( 0 );
	bSizer123->Add( m_radioBox3, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer122->Add( bSizer123, 0, wxEXPAND, 5 );
	
	
	m_panel21->SetSizer( bSizer122 );
	m_panel21->Layout();
	bSizer122->Fit( m_panel21 );
	m_notebook->AddPage( m_panel21, _("Events"), false );
	
	bSizer117->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer117->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticFamID = new wxStaticText( this, wxID_ANY, _("F0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticFamID->Wrap( -1 );
	m_staticFamID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticFamID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer117->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer117 );
	this->Layout();
	bSizer117->Fit( this );
	
	// Connect Events
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditFamily::OnPageChanged ), NULL, this );
	m_buttonHusb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnHusbButton ), NULL, this );
	m_buttonWife->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnWifeButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildDeleteButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildUpButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildDownButton ), NULL, this );
	m_buttonEventAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventDownButton ), NULL, this );
	m_radioBox3->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditFamily::OnEventOrderBy ), NULL, this );
}

fbRgEditFamily::~fbRgEditFamily()
{
	// Disconnect Events
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditFamily::OnPageChanged ), NULL, this );
	m_buttonHusb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnHusbButton ), NULL, this );
	m_buttonWife->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnWifeButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildDeleteButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildUpButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnChildDownButton ), NULL, this );
	m_buttonEventAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditFamily::OnEventDownButton ), NULL, this );
	m_radioBox3->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditFamily::OnEventOrderBy ), NULL, this );
	
}

fbRgEditIndividual::fbRgEditIndividual( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer99;
	bSizer99 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer99->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticPerName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerName->Wrap( -1 );
	m_staticPerName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer99->Add( m_staticPerName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer98->Add( bSizer99, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextEpitaph = new wxStaticText( m_panel1, wxID_ANY, _("Dates"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextEpitaph->Wrap( -1 );
	m_staticTextEpitaph->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer102->Add( m_staticTextEpitaph, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer102->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( m_panel1, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer102->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	bSizer102->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer101->Add( bSizer102, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer103;
	bSizer103 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( m_panel1, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer103->Add( m_staticText12, 0, wxALL, 5 );
	
	m_textCtrlNote = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 350,100 ), wxTE_MULTILINE );
	bSizer103->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer101->Add( bSizer103, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer101 );
	m_panel1->Layout();
	bSizer101->Fit( m_panel1 );
	m_notebook->AddPage( m_panel1, _("Individual"), true );
	m_panel2 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer104;
	bSizer104 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listName = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxSize( 300,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer104->Add( m_listName, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonNameAdd = new wxButton( m_panel2, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer105->Add( m_buttonNameAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonNameEdit = new wxButton( m_panel2, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer105->Add( m_buttonNameEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonNameDel = new wxButton( m_panel2, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer105->Add( m_buttonNameDel, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonNameUp = new wxButton( m_panel2, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer106->Add( m_buttonNameUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer106->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonNameDn = new wxButton( m_panel2, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer106->Add( m_buttonNameDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer105->Add( bSizer106, 1, wxEXPAND, 5 );
	
	
	bSizer104->Add( bSizer105, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer104 );
	m_panel2->Layout();
	bSizer104->Fit( m_panel2 );
	m_notebook->AddPage( m_panel2, _("Names"), false );
	m_panel21 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer107;
	bSizer107 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEvent = new wxListCtrl( m_panel21, wxID_ANY, wxDefaultPosition, wxSize( 300,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer107->Add( m_listEvent, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer108;
	bSizer108 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEventAdd = new wxButton( m_panel21, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer108->Add( m_buttonEventAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventEdit = new wxButton( m_panel21, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer108->Add( m_buttonEventEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonEventDel = new wxButton( m_panel21, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer108->Add( m_buttonEventDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer109;
	bSizer109 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonEventUp = new wxButton( m_panel21, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventUp->Enable( false );
	
	bSizer109->Add( m_buttonEventUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer109->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonEventDn = new wxButton( m_panel21, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventDn->Enable( false );
	
	bSizer109->Add( m_buttonEventDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer108->Add( bSizer109, 1, wxEXPAND, 5 );
	
	wxString m_radioBox3Choices[] = { _("Date Point"), _("Preference") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( m_panel21, wxID_ANY, _("Order by:-"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox3->SetSelection( 0 );
	bSizer108->Add( m_radioBox3, 0, wxALL, 5 );
	
	
	bSizer107->Add( bSizer108, 0, wxEXPAND, 5 );
	
	
	m_panel21->SetSizer( bSizer107 );
	m_panel21->Layout();
	bSizer107->Fit( m_panel21 );
	m_notebook->AddPage( m_panel21, _("Events"), false );
	
	bSizer100->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizer98->Add( bSizer100, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer98->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticIndID = new wxStaticText( this, wxID_ANY, _("I0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndID->Wrap( -1 );
	m_staticIndID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticIndID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer98->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer98 );
	this->Layout();
	bSizer98->Fit( this );
	
	// Connect Events
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditIndividual::OnPageChanged ), NULL, this );
	m_buttonNameAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventDownButton ), NULL, this );
	m_radioBox3->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditIndividual::OnEventOrderBy ), NULL, this );
}

fbRgEditIndividual::~fbRgEditIndividual()
{
	// Disconnect Events
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditIndividual::OnPageChanged ), NULL, this );
	m_buttonNameAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditIndividual::OnEventDownButton ), NULL, this );
	m_radioBox3->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditIndividual::OnEventOrderBy ), NULL, this );
	
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

fbRgEditPersona::fbRgEditPersona( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer64->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticPerName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerName->Wrap( -1 );
	m_staticPerName->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer64->Add( m_staticPerName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer63->Add( bSizer64, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( m_panel1, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer68->Add( m_staticText12, 0, wxALL, 5 );
	
	m_textCtrlNote = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_MULTILINE );
	bSizer68->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer113->Add( bSizer68, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer67->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( m_panel1, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer67->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	bSizer67->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer113->Add( bSizer67, 0, 0, 5 );
	
	
	bSizer66->Add( bSizer113, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonIndLink = new wxButton( m_panel1, wxID_ANY, _("Link"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( m_buttonIndLink, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText13 = new wxStaticText( m_panel1, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer70->Add( m_staticText13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticIndId = new wxStaticText( m_panel1, wxID_ANY, _("I0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndId->Wrap( -1 );
	m_staticIndId->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer70->Add( m_staticIndId, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer69->Add( bSizer70, 0, wxEXPAND, 5 );
	
	
	bSizer66->Add( bSizer69, 0, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer66 );
	m_panel1->Layout();
	bSizer66->Fit( m_panel1 );
	m_notebook->AddPage( m_panel1, _("Persona"), true );
	m_panel2 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listName = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer71->Add( m_listName, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonNameAdd = new wxButton( m_panel2, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_buttonNameAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonNameEdit = new wxButton( m_panel2, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_buttonNameEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonNameDel = new wxButton( m_panel2, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_buttonNameDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer73;
	bSizer73 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonNameUp = new wxButton( m_panel2, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer73->Add( m_buttonNameUp, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonNameDn = new wxButton( m_panel2, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer73->Add( m_buttonNameDn, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer72->Add( bSizer73, 1, wxEXPAND, 5 );
	
	
	bSizer71->Add( bSizer72, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer71 );
	m_panel2->Layout();
	bSizer71->Fit( m_panel2 );
	m_notebook->AddPage( m_panel2, _("Name"), false );
	m_panel21 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEvent = new wxListCtrl( m_panel21, wxID_ANY, wxDefaultPosition, wxSize( 400,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer74->Add( m_listEvent, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEventAdd = new wxButton( m_panel21, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_buttonEventAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventEdit = new wxButton( m_panel21, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_buttonEventEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonEventDel = new wxButton( m_panel21, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_buttonEventDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonEventUp = new wxButton( m_panel21, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventUp->Enable( false );
	
	bSizer76->Add( m_buttonEventUp, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonEventDn = new wxButton( m_panel21, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventDn->Enable( false );
	
	bSizer76->Add( m_buttonEventDn, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer75->Add( bSizer76, 1, wxEXPAND, 5 );
	
	wxString m_radioBox3Choices[] = { _("Date Point"), _("Preference") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( m_panel21, wxID_ANY, _("Order by:-"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox3->SetSelection( 0 );
	bSizer75->Add( m_radioBox3, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer74->Add( bSizer75, 0, wxEXPAND, 5 );
	
	
	m_panel21->SetSizer( bSizer74 );
	m_panel21->Layout();
	bSizer74->Fit( m_panel21 );
	m_notebook->AddPage( m_panel21, _("Events"), false );
	m_panel4 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer77;
	bSizer77 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listRel = new wxListCtrl( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer77->Add( m_listRel, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer78;
	bSizer78 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonRelAdd = new wxButton( m_panel4, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer78->Add( m_buttonRelAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonRelEdit = new wxButton( m_panel4, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer78->Add( m_buttonRelEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonRelDel = new wxButton( m_panel4, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer78->Add( m_buttonRelDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer77->Add( bSizer78, 0, wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer77 );
	m_panel4->Layout();
	bSizer77->Fit( m_panel4 );
	m_notebook->AddPage( m_panel4, _("Relationships"), false );
	
	bSizer65->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizer63->Add( bSizer65, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer63->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticPerID = new wxStaticText( this, wxID_ANY, _("Pa0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerID->Wrap( -1 );
	m_staticPerID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxEmptyString ) );
	
	bSizerDismiss->Add( m_staticPerID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer63->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer63 );
	this->Layout();
	bSizer63->Fit( this );
	
	// Connect Events
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditPersona::OnPageChanged ), NULL, this );
	m_buttonIndLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndLinkButton ), NULL, this );
	m_buttonNameAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventDownButton ), NULL, this );
	m_radioBox3->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditPersona::OnOrderBy ), NULL, this );
	m_buttonRelAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnRelAddButton ), NULL, this );
	m_buttonRelEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnRelEditButton ), NULL, this );
	m_buttonRelDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnRelDeleteButton ), NULL, this );
}

fbRgEditPersona::~fbRgEditPersona()
{
	// Disconnect Events
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditPersona::OnPageChanged ), NULL, this );
	m_buttonIndLink->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndLinkButton ), NULL, this );
	m_buttonNameAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventDownButton ), NULL, this );
	m_radioBox3->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditPersona::OnOrderBy ), NULL, this );
	m_buttonRelAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnRelAddButton ), NULL, this );
	m_buttonRelEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnRelEditButton ), NULL, this );
	m_buttonRelDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnRelDeleteButton ), NULL, this );
	
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

fbRgEditReference::fbRgEditReference( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText401 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	bSizer51->Add( m_staticText401, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer49->Add( bSizer51, 0, wxEXPAND, 5 );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH|wxSP_NO_XP_THEME );
	m_splitter1->SetSashGravity( 0.75 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditReference::m_splitter1OnIdle ), NULL, this );
	
	m_panelTop = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxVERTICAL );
	
	m_notebookTop = new wxNotebook( m_panelTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM );
	m_panelSource = new wxPanel( m_notebookTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer( wxVERTICAL );
	
	m_toolBar1 = new wxToolBar( m_panelSource, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_toolCut = m_toolBar1->AddTool( tfpID_EDREF_OnCut, _("Cut"), wxBitmap( cut_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Cut"), wxEmptyString, NULL ); 
	
	m_toolCopy = m_toolBar1->AddTool( tfpID_EDREF_OnCopy, _("Copy"), wxBitmap( copy_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Copy"), wxEmptyString, NULL ); 
	
	m_toolPaste = m_toolBar1->AddTool( tfpID_EDREF_OnPaste, _("Paste"), wxBitmap( paste_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Paste"), wxEmptyString, NULL ); 
	
	m_toolBar1->AddSeparator(); 
	
	m_toolUndo = m_toolBar1->AddTool( tfpID_EDREF_OnUndo, _("Undo"), wxBitmap( undo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Undo"), wxEmptyString, NULL ); 
	
	m_toolRedo = m_toolBar1->AddTool( tfpID_EDREF_OnRedo, _("Redo"), wxBitmap( redo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Redo"), wxEmptyString, NULL ); 
	
	m_toolBar1->Realize(); 
	
	bSizer53->Add( m_toolBar1, 0, wxEXPAND, 5 );
	
	m_textCtrlStatement = new wxTextCtrl( m_panelSource, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 600,150 ), wxTE_DONTWRAP|wxTE_MULTILINE|wxHSCROLL );
	m_textCtrlStatement->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer53->Add( m_textCtrlStatement, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelSource->SetSizer( bSizer53 );
	m_panelSource->Layout();
	bSizer53->Fit( m_panelSource );
	m_notebookTop->AddPage( m_panelSource, _("Source"), true );
	m_panelView = new wxPanel( m_notebookTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxVERTICAL );
	
	m_webview = wxWebView::New(m_panelView, wxID_ANY);
	bSizer54->Add( m_webview, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelView->SetSizer( bSizer54 );
	m_panelView->Layout();
	bSizer54->Fit( m_panelView );
	m_notebookTop->AddPage( m_panelView, _("View"), false );
	
	bSizer52->Add( m_notebookTop, 1, wxEXPAND|wxALL, 5 );
	
	
	m_panelTop->SetSizer( bSizer52 );
	m_panelTop->Layout();
	bSizer52->Fit( m_panelTop );
	m_panelBottom = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxVERTICAL );
	
	m_notebookBottom = new wxNotebook( m_panelBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelPersona = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listPersona = new wxListCtrl( m_panelPersona, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer56->Add( m_listPersona, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonPersonaAdd = new wxButton( m_panelPersona, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( m_buttonPersonaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonPersonaEdit = new wxButton( m_panelPersona, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( m_buttonPersonaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonPersonaDel = new wxButton( m_panelPersona, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( m_buttonPersonaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer56->Add( bSizer57, 0, wxEXPAND, 5 );
	
	
	m_panelPersona->SetSizer( bSizer56 );
	m_panelPersona->Layout();
	bSizer56->Fit( m_panelPersona );
	m_notebookBottom->AddPage( m_panelPersona, _("Persona"), false );
	m_panelEntities = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEntities = new wxListCtrl( m_panelEntities, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEntities->SetMinSize( wxSize( -1,150 ) );
	
	bSizer58->Add( m_listEntities, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( m_panelEntities, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( m_panelEntities, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonDel = new wxButton( m_panelEntities, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( m_panelEntities, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer60->Add( m_buttonUp, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonDn = new wxButton( m_panelEntities, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer60->Add( m_buttonDn, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer59->Add( bSizer60, 1, wxEXPAND, 5 );
	
	
	bSizer58->Add( bSizer59, 0, 0, 5 );
	
	
	m_panelEntities->SetSizer( bSizer58 );
	m_panelEntities->Layout();
	bSizer58->Fit( m_panelEntities );
	m_notebookBottom->AddPage( m_panelEntities, _("Entities"), true );
	
	bSizer55->Add( m_notebookBottom, 1, wxEXPAND|wxALL, 5 );
	
	
	m_panelBottom->SetSizer( bSizer55 );
	m_panelBottom->Layout();
	bSizer55->Fit( m_panelBottom );
	m_splitter1->SplitHorizontally( m_panelTop, m_panelBottom, 265 );
	bSizer49->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer49->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticRefID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRefID->Wrap( -1 );
	m_staticRefID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticRefID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer49->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer49 );
	this->Layout();
	bSizer49->Fit( this );
	
	// Connect Events
	m_notebookTop->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnStatementViewChanged ), NULL, this );
	this->Connect( m_toolCut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Connect( m_toolCopy->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Connect( m_toolPaste->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Connect( m_toolUndo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Connect( m_toolRedo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	m_notebookBottom->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnEntityViewChanged ), NULL, this );
	m_buttonPersonaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaAddButton ), NULL, this );
	m_buttonPersonaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaEditButton ), NULL, this );
	m_buttonPersonaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaDeleteButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnAddEntityButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEditEntityButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDeleteEntityButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnUpEntityButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDownEntityButton ), NULL, this );
}

fbRgEditReference::~fbRgEditReference()
{
	// Disconnect Events
	m_notebookTop->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnStatementViewChanged ), NULL, this );
	this->Disconnect( m_toolCut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Disconnect( m_toolCopy->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Disconnect( m_toolPaste->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Disconnect( m_toolUndo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	this->Disconnect( m_toolRedo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnTool ) );
	m_notebookBottom->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnEntityViewChanged ), NULL, this );
	m_buttonPersonaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaAddButton ), NULL, this );
	m_buttonPersonaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaEditButton ), NULL, this );
	m_buttonPersonaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaDeleteButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnAddEntityButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEditEntityButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDeleteEntityButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnUpEntityButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDownEntityButton ), NULL, this );
	
}

fbRgEditRelationship::fbRgEditRelationship( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer13->AddGrowableCol( 1 );
	fgSizer13->AddGrowableRow( 1 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_buttonPerson1 = new wxButton( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer13->Add( m_buttonPerson1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPersona1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	m_textCtrlPersona1->SetMaxLength( 0 ); 
	m_textCtrlPersona1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer13->Add( m_textCtrlPersona1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText75 = new wxStaticText( this, wxID_ANY, _("Is the:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText75->Wrap( -1 );
	fgSizer13->Add( m_staticText75, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlDescrip = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,50 ), wxTE_MULTILINE|wxTE_WORDWRAP );
	fgSizer13->Add( m_textCtrlDescrip, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPersona2 = new wxButton( this, wxID_ANY, _("Of:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer13->Add( m_buttonPersona2, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlPersona2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlPersona2->SetMaxLength( 0 ); 
	m_textCtrlPersona2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer13->Add( m_textCtrlPersona2, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, 5 );
	
	
	bSizer1->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	m_staticline18 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline18, 0, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticRsNumber = new wxStaticText( this, wxID_ANY, _("Rs0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRsNumber->Wrap( -1 );
	m_staticRsNumber->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticRsNumber, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_buttonPerson1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRelationship::OnPersona1Button ), NULL, this );
	m_buttonPersona2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRelationship::OnPersona2Button ), NULL, this );
}

fbRgEditRelationship::~fbRgEditRelationship()
{
	// Disconnect Events
	m_buttonPerson1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRelationship::OnPersona1Button ), NULL, this );
	m_buttonPersona2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRelationship::OnPersona2Button ), NULL, this );
	
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
	
	wxString m_choiceDisplayChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian"), _("French Revolutionary") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 3 );
	fgSizer11->Add( m_choiceDisplay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Calculation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceCalcChoices[] = { _("Age, round down"), _("Duration"), _("Add to start"), _("Add to end") };
	int m_choiceCalcNChoices = sizeof( m_choiceCalcChoices ) / sizeof( wxString );
	m_choiceCalc = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceCalcNChoices, m_choiceCalcChoices, 0 );
	m_choiceCalc->SetSelection( 0 );
	fgSizer11->Add( m_choiceCalc, 0, wxALL, 5 );
	
	m_buttonBase = new wxButton( this, wxID_ANY, _("Base Date:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer11->Add( m_buttonBase, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBase = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), wxTE_READONLY );
	m_textCtrlBase->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer11->Add( m_textCtrlBase, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText3a = new wxStaticText( this, wxID_ANY, _("Precision:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3a->Wrap( -1 );
	fgSizer11->Add( m_staticText3a, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choicePrecisionChoices[] = { _("After"), _("On"), _("On or after"), _("Before"), _("Not"), _("On or before"), _("About") };
	int m_choicePrecisionNChoices = sizeof( m_choicePrecisionChoices ) / sizeof( wxString );
	m_choicePrecision = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choicePrecisionNChoices, m_choicePrecisionChoices, 0 );
	m_choicePrecision->SetSelection( 1 );
	fgSizer11->Add( m_choicePrecision, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAge = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( m_textCtrlAge, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Calendar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer11->Add( m_staticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceInputChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian"), _("French Revolutionary") };
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
	bSizer1->Fit( this );
	
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

fbRgEditResearcher::fbRgEditResearcher( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->AddGrowableRow( 1 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText64 = new wxStaticText( this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	fgSizer12->Add( m_staticText64, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( m_textCtrlName, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText65 = new wxStaticText( this, wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	fgSizer12->Add( m_staticText65, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlComment = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	fgSizer12->Add( m_textCtrlComment, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonInd = new wxButton( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer12->Add( m_buttonInd, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticIndName = new wxStaticText( this, wxID_ANY, _("Individual"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndName->Wrap( -1 );
	m_staticIndName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer54->Add( m_staticIndName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer54->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticIndID = new wxStaticText( this, wxID_ANY, _("I0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndID->Wrap( -1 );
	m_staticIndID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizer54->Add( m_staticIndID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer12->Add( bSizer54, 1, wxEXPAND, 5 );
	
	
	bSizer48->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listContacts = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 300,125 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer49->Add( m_listContacts, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonAdd, 0, wxALL, 5 );
	
	m_buttonEdit = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonEdit, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonDelete, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer49->Add( bSizer50, 0, wxEXPAND, 5 );
	
	
	bSizer48->Add( bSizer49, 1, wxEXPAND, 5 );
	
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer48->Add( m_staticline14, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticResID = new wxStaticText( this, wxID_ANY, _("Re0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticResID->Wrap( -1 );
	m_staticResID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticResID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxUser = new wxCheckBox( this, wxID_ANY, _("User"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_checkBoxUser, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticUserID = new wxStaticText( this, wxID_ANY, _("U0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUserID->Wrap( -1 );
	m_staticUserID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizerDismiss->Add( m_staticUserID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer48->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer48 );
	this->Layout();
	bSizer48->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonInd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonInd ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonAdd ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonEdit ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonDelete ), NULL, this );
}

fbRgEditResearcher::~fbRgEditResearcher()
{
	// Disconnect Events
	m_buttonInd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonInd ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonAdd ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonEdit ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditResearcher::OnButtonDelete ), NULL, this );
	
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

fbRgEditSystem::fbRgEditSystem( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer14->AddGrowableCol( 1 );
	fgSizer14->AddGrowableRow( 1 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText = new wxStaticText( this, wxID_ANY, _("Current User:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	fgSizer14->Add( m_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxArrayString m_choiceUserChoices;
	m_choiceUser = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), m_choiceUserChoices, 0 );
	m_choiceUser->SetSelection( 0 );
	fgSizer14->Add( m_choiceUser, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	fgSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer81->Add( fgSizer14, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer81->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer81->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer81 );
	this->Layout();
	bSizer81->Fit( this );
}

fbRgEditSystem::~fbRgEditSystem()
{
}

fbRgEditUserSettings::fbRgEditUserSettings( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer15->AddGrowableCol( 1 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("User:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer15->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticUserName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUserName->Wrap( -1 );
	m_staticUserName->SetFont( wxFont( 10, 74, 90, 92, false, wxT("MS Shell Dlg 2") ) );
	
	fgSizer15->Add( m_staticUserName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText = new wxStaticText( this, wxID_ANY, _("Home Page:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	fgSizer15->Add( m_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlHome = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	m_textCtrlHome->SetMaxLength( 0 ); 
	fgSizer15->Add( m_textCtrlHome, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer83->Add( fgSizer15, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer83->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );
	
	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticUserID = new wxStaticText( this, wxID_ANY, _("U0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUserID->Wrap( -1 );
	m_staticUserID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 72, 90, 92, false, wxEmptyString ) );
	
	bSizerDismiss->Add( m_staticUserID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave1 = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer83->Add( bSizerDismiss, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer83 );
	this->Layout();
	bSizer83->Fit( this );
}

fbRgEditUserSettings::~fbRgEditUserSettings()
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

fbRgSelectEvent::fbRgSelectEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	
	wxBoxSizer* bSizer124;
	bSizer124 = new wxBoxSizer( wxVERTICAL );
	
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
	
	
	bSizer124->Add( sbSizer2, 1, wxEXPAND|wxLEFT, 5 );
	
	wxBoxSizer* bSizer125;
	bSizer125 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText115 = new wxStaticText( this, wxID_ANY, _("Individual ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText115->Wrap( -1 );
	bSizer125->Add( m_staticText115, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlIndID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer125->Add( m_textCtrlIndID, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer124->Add( bSizer125, 0, wxEXPAND, 5 );
	
	
	bSizer27->Add( bSizer124, 1, wxEXPAND, 5 );
	
	
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
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgSelectEvent::OnIdle ) );
	m_checkListGrp->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectEvent::OnGroupCheckSelect ), NULL, this );
	m_checkListGrp->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectEvent::OnGroupCheckToggled ), NULL, this );
	m_buttonSelectGrp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonGroupSelectAll ), NULL, this );
	m_buttonClearGrp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonGroupClearAll ), NULL, this );
	m_textCtrlBegDatePt->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectEvent::OnBegDateText ), NULL, this );
	m_textCtrlEndDatePt->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectEvent::OnEndDateText ), NULL, this );
	m_checkListType->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectEvent::OnTypeCheckSelect ), NULL, this );
	m_checkListType->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectEvent::OnTypeCheckToggled ), NULL, this );
	m_buttonSelectType->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonTypeSelectAll ), NULL, this );
	m_buttonClearType->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonTypeClearAll ), NULL, this );
	m_textCtrlIndID->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectEvent::OnIndIdText ), NULL, this );
	m_listEvent->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgSelectEvent::OnListEventItemDeselected ), NULL, this );
	m_listEvent->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgSelectEvent::OnListEventItemSelected ), NULL, this );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnCreateButton ), NULL, this );
}

fbRgSelectEvent::~fbRgSelectEvent()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgSelectEvent::OnIdle ) );
	m_checkListGrp->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectEvent::OnGroupCheckSelect ), NULL, this );
	m_checkListGrp->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectEvent::OnGroupCheckToggled ), NULL, this );
	m_buttonSelectGrp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonGroupSelectAll ), NULL, this );
	m_buttonClearGrp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonGroupClearAll ), NULL, this );
	m_textCtrlBegDatePt->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectEvent::OnBegDateText ), NULL, this );
	m_textCtrlEndDatePt->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectEvent::OnEndDateText ), NULL, this );
	m_checkListType->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fbRgSelectEvent::OnTypeCheckSelect ), NULL, this );
	m_checkListType->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( fbRgSelectEvent::OnTypeCheckToggled ), NULL, this );
	m_buttonSelectType->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonTypeSelectAll ), NULL, this );
	m_buttonClearType->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnButtonTypeClearAll ), NULL, this );
	m_textCtrlIndID->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( fbRgSelectEvent::OnIndIdText ), NULL, this );
	m_listEvent->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgSelectEvent::OnListEventItemDeselected ), NULL, this );
	m_listEvent->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgSelectEvent::OnListEventItemSelected ), NULL, this );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgSelectEvent::OnCreateButton ), NULL, this );
	
}
