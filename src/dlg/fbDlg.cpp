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


#include "dlgRecTableCtrl.h"
#include "tfpListCtrlInd.h"

#include "fbDlg.h"

#include "../img/ed/copy.xpm"
#include "../img/ed/cut.xpm"
#include "../img/ed/paste.xpm"
#include "../img/ed/redo.xpm"
#include "../img/ed/undo.xpm"

///////////////////////////////////////////////////////////////////////////

fbDlgCreateIndividual::fbDlgCreateIndividual( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Individual ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticIndID = new wxStaticText( this, wxID_ANY, _("I 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndID->Wrap( -1 );
	m_staticIndID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticIndID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer1->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	m_choiceSex->SetMinSize( wxSize( 70,-1 ) );
	
	bSizer1->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizer1, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableRow( 2 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, _("Given Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textGiven = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	m_textGiven->SetMaxLength( 0 ); 
	fgSizer2->Add( m_textGiven, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, _("Surname:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textSurname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	m_textSurname->SetMaxLength( 0 ); 
	fgSizer2->Add( m_textSurname, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_MULTILINE );
	m_textNote->SetMaxLength( 0 ); 
	fgSizer2->Add( m_textNote, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSave, 0, wxALL, 7 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxALL, 7 );
	
	
	bSizer->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
}

fbDlgCreateIndividual::~fbDlgCreateIndividual()
{
}

fbDlgEditIndPersona::fbDlgEditIndPersona( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticPerName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerName->Wrap( -1 );
	m_staticPerName->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticPerName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticIndID = new wxStaticText( this, wxID_ANY, _("I0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndID->Wrap( -1 );
	m_staticIndID->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticIndID, 0, wxALL, 5 );
	
	m_staticPerID = new wxStaticText( this, wxID_ANY, _("Pa0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerID->Wrap( -1 );
	bSizer1->Add( m_staticPerID, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextEpitaph = new wxStaticText( m_panel1, wxID_ANY, _("Dates"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextEpitaph->Wrap( -1 );
	m_staticTextEpitaph->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer211->Add( m_staticTextEpitaph, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer211->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( m_panel1, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer211->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	m_choiceSex->SetMinSize( wxSize( 70,-1 ) );
	
	bSizer211->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer21->Add( bSizer211, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer212;
	bSizer212 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( m_panel1, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer212->Add( m_staticText12, 0, wxALL, 5 );
	
	m_textCtrlNote = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textCtrlNote->SetMaxLength( 0 ); 
	m_textCtrlNote->SetMinSize( wxSize( 350,50 ) );
	
	bSizer212->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer21->Add( bSizer212, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer21 );
	m_panel1->Layout();
	bSizer21->Fit( m_panel1 );
	m_notebook->AddPage( m_panel1, _("Persona"), false );
	m_panel2 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listName = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listName->SetMinSize( wxSize( -1,125 ) );
	
	bSizer22->Add( m_listName, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonNameAdd = new wxButton( m_panel2, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonNameAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonNameEdit = new wxButton( m_panel2, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonNameEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonNameDel = new wxButton( m_panel2, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonNameDel, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer2211;
	bSizer2211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonNameUp = new wxButton( m_panel2, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2211->Add( m_buttonNameUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer2211->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonNameDn = new wxButton( m_panel2, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2211->Add( m_buttonNameDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer221->Add( bSizer2211, 1, wxEXPAND, 5 );
	
	
	bSizer22->Add( bSizer221, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer22 );
	m_panel2->Layout();
	bSizer22->Fit( m_panel2 );
	m_notebook->AddPage( m_panel2, _("Names"), false );
	m_panel21 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer222;
	bSizer222 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEvent = new wxListCtrl( m_panel21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEvent->SetMinSize( wxSize( -1,125 ) );
	
	bSizer222->Add( m_listEvent, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2212;
	bSizer2212 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEventAdd = new wxButton( m_panel21, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventEdit = new wxButton( m_panel21, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonEventDel = new wxButton( m_panel21, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer22111;
	bSizer22111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonEventUp = new wxButton( m_panel21, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer22111->Add( m_buttonEventUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer22111->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonEventDn = new wxButton( m_panel21, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer22111->Add( m_buttonEventDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer2212->Add( bSizer22111, 1, wxEXPAND, 5 );
	
	
	bSizer222->Add( bSizer2212, 0, wxEXPAND, 5 );
	
	
	m_panel21->SetSizer( bSizer222 );
	m_panel21->Layout();
	bSizer222->Fit( m_panel21 );
	m_notebook->AddPage( m_panel21, _("Events"), true );
	m_panel4 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listRel = new wxListCtrl( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listRel->SetMinSize( wxSize( -1,125 ) );
	
	bSizer24->Add( m_listRel, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonRelAdd = new wxButton( m_panel4, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer241->Add( m_buttonRelAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonRelEdit = new wxButton( m_panel4, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer241->Add( m_buttonRelEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonRelDel = new wxButton( m_panel4, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer241->Add( m_buttonRelDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer2411;
	bSizer2411 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonRelUp = new wxButton( m_panel4, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2411->Add( m_buttonRelUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer2411->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonRelDn = new wxButton( m_panel4, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2411->Add( m_buttonRelDn, 0, wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer241->Add( bSizer2411, 1, wxEXPAND, 5 );
	
	
	bSizer24->Add( bSizer241, 0, wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer24 );
	m_panel4->Layout();
	bSizer24->Fit( m_panel4 );
	m_notebook->AddPage( m_panel4, _("Relationships"), false );
	
	bSizer2->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	m_buttonNameAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventDownButton ), NULL, this );
	m_buttonRelAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelAddButton ), NULL, this );
	m_buttonRelEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelEditButton ), NULL, this );
	m_buttonRelDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelDeleteButton ), NULL, this );
	m_buttonRelUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelUpButton ), NULL, this );
	m_buttonRelDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelDownButton ), NULL, this );
}

fbDlgEditIndPersona::~fbDlgEditIndPersona()
{
	// Disconnect Events
	m_buttonNameAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnEventDownButton ), NULL, this );
	m_buttonRelAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelAddButton ), NULL, this );
	m_buttonRelEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelEditButton ), NULL, this );
	m_buttonRelDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelDeleteButton ), NULL, this );
	m_buttonRelUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelUpButton ), NULL, this );
	m_buttonRelDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndPersona::OnRelDownButton ), NULL, this );
	
}

fbDlgEditPersona::fbDlgEditPersona( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticPerName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerName->Wrap( -1 );
	m_staticPerName->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticPerName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticPerID = new wxStaticText( this, wxID_ANY, _("P 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerID->Wrap( -1 );
	m_staticPerID->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticPerID, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer211->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( m_panel1, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer211->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	m_choiceSex->SetMinSize( wxSize( 70,-1 ) );
	
	bSizer211->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer21->Add( bSizer211, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer212;
	bSizer212 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( m_panel1, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer212->Add( m_staticText12, 0, wxALL, 5 );
	
	m_textCtrlNote = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textCtrlNote->SetMaxLength( 0 ); 
	m_textCtrlNote->SetMinSize( wxSize( 350,50 ) );
	
	bSizer212->Add( m_textCtrlNote, 0, wxALL, 5 );
	
	
	bSizer21->Add( bSizer212, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer213;
	bSizer213 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2131;
	bSizer2131 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonIndLink = new wxButton( m_panel1, wxID_ANY, _("Link"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonIndLink->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer2131->Add( m_buttonIndLink, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonIndCreate = new wxButton( m_panel1, wxID_ANY, _("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonIndCreate->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer2131->Add( m_buttonIndCreate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( m_panel1, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer2131->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticIndId = new wxStaticText( m_panel1, wxID_ANY, _("I 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndId->Wrap( -1 );
	m_staticIndId->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer2131->Add( m_staticIndId, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer213->Add( bSizer2131, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( bSizer213, 0, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer21 );
	m_panel1->Layout();
	bSizer21->Fit( m_panel1 );
	m_notebook->AddPage( m_panel1, _("Persona"), true );
	m_panel2 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listName = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listName->SetMinSize( wxSize( -1,125 ) );
	
	bSizer22->Add( m_listName, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonNameAdd = new wxButton( m_panel2, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonNameAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonNameEdit = new wxButton( m_panel2, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonNameEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonNameDel = new wxButton( m_panel2, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonNameDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer2211;
	bSizer2211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonNameUp = new wxButton( m_panel2, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2211->Add( m_buttonNameUp, 0, wxALL, 5 );
	
	m_buttonNameDn = new wxButton( m_panel2, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2211->Add( m_buttonNameDn, 0, wxALL, 5 );
	
	
	bSizer221->Add( bSizer2211, 1, wxEXPAND, 5 );
	
	
	bSizer22->Add( bSizer221, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer22 );
	m_panel2->Layout();
	bSizer22->Fit( m_panel2 );
	m_notebook->AddPage( m_panel2, _("Name"), false );
	m_panel21 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer222;
	bSizer222 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEvent = new wxListCtrl( m_panel21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEvent->SetMinSize( wxSize( -1,125 ) );
	
	bSizer222->Add( m_listEvent, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer2212;
	bSizer2212 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEventAdd = new wxButton( m_panel21, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventEdit = new wxButton( m_panel21, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventDel = new wxButton( m_panel21, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer22111;
	bSizer22111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonEventUp = new wxButton( m_panel21, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer22111->Add( m_buttonEventUp, 0, wxALL, 5 );
	
	m_buttonEventDn = new wxButton( m_panel21, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer22111->Add( m_buttonEventDn, 0, wxALL, 5 );
	
	
	bSizer2212->Add( bSizer22111, 1, wxEXPAND, 5 );
	
	
	bSizer222->Add( bSizer2212, 0, wxEXPAND, 5 );
	
	
	m_panel21->SetSizer( bSizer222 );
	m_panel21->Layout();
	bSizer222->Fit( m_panel21 );
	m_notebook->AddPage( m_panel21, _("Events"), false );
	m_panel4 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listRel = new wxListCtrl( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listRel->SetMinSize( wxSize( -1,125 ) );
	
	bSizer24->Add( m_listRel, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonRelAdd = new wxButton( m_panel4, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer241->Add( m_buttonRelAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonRelEdit = new wxButton( m_panel4, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer241->Add( m_buttonRelEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonRelDel = new wxButton( m_panel4, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer241->Add( m_buttonRelDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer2411;
	bSizer2411 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonRelUp = new wxButton( m_panel4, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2411->Add( m_buttonRelUp, 0, wxALL, 5 );
	
	m_buttonRelDn = new wxButton( m_panel4, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer2411->Add( m_buttonRelDn, 0, wxALL, 5 );
	
	
	bSizer241->Add( bSizer2411, 1, wxEXPAND, 5 );
	
	
	bSizer24->Add( bSizer241, 0, wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer24 );
	m_panel4->Layout();
	bSizer24->Fit( m_panel4 );
	m_notebook->AddPage( m_panel4, _("Relationships"), false );
	
	bSizer2->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	m_buttonIndLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndLinkButton ), NULL, this );
	m_buttonIndCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndCreateButton ), NULL, this );
	m_buttonNameAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventDownButton ), NULL, this );
	m_buttonRelAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelAddButton ), NULL, this );
	m_buttonRelEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelEditButton ), NULL, this );
	m_buttonRelDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelDeleteButton ), NULL, this );
	m_buttonRelUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelUpButton ), NULL, this );
	m_buttonRelDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelDownButton ), NULL, this );
}

fbDlgEditPersona::~fbDlgEditPersona()
{
	// Disconnect Events
	m_buttonIndLink->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndLinkButton ), NULL, this );
	m_buttonIndCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndCreateButton ), NULL, this );
	m_buttonNameAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnNameDownButton ), NULL, this );
	m_buttonEventAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEventDownButton ), NULL, this );
	m_buttonRelAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelAddButton ), NULL, this );
	m_buttonRelEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelEditButton ), NULL, this );
	m_buttonRelDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelDeleteButton ), NULL, this );
	m_buttonRelUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelUpButton ), NULL, this );
	m_buttonRelDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnRelDownButton ), NULL, this );
	
}

fbDlgEditFamily::fbDlgEditFamily( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticNames = new wxStaticText( this, wxID_ANY, _("Name and Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNames->Wrap( -1 );
	m_staticNames->SetFont( wxFont( 8, 74, 90, 92, false, wxT("MS Shell Dlg 2") ) );
	
	bSizer2->Add( m_staticNames, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticFamID = new wxStaticText( this, wxID_ANY, _("F0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticFamID->Wrap( -1 );
	m_staticFamID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer2->Add( m_staticFamID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	m_notebook5 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel17 = new wxPanel( m_notebook5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer21->AddGrowableCol( 1 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_buttonHusb = new wxButton( m_panel17, wxID_ANY, _("Husband:"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_RIGHT );
	fgSizer21->Add( m_buttonHusb, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALIGN_RIGHT|wxALL, 5 );
	
	m_staticHusbName = new wxStaticText( m_panel17, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticHusbName->Wrap( -1 );
	fgSizer21->Add( m_staticHusbName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonWife = new wxButton( m_panel17, wxID_ANY, _("Wife:"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_RIGHT );
	fgSizer21->Add( m_buttonWife, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticWifeName = new wxStaticText( m_panel17, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticWifeName->Wrap( -1 );
	fgSizer21->Add( m_staticWifeName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_panel17->SetSizer( fgSizer21 );
	m_panel17->Layout();
	fgSizer21->Fit( m_panel17 );
	m_notebook5->AddPage( m_panel17, _("Family"), true );
	m_panel211 = new wxPanel( m_notebook5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listChild = new wxListBox( m_panel211, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_HSCROLL|wxLB_NEEDED_SB|wxLB_SINGLE ); 
	bSizer127->Add( m_listChild, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( m_panel211, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( m_panel211, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonDel = new wxButton( m_panel211, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( m_panel211, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer121->Add( m_buttonUp, 0, wxALL, 5 );
	
	
	bSizer121->Add( 0, 0, 1, wxEXPAND, 0 );
	
	m_button1Dn = new wxButton( m_panel211, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer121->Add( m_button1Dn, 0, wxALL, 5 );
	
	
	bSizer111->Add( bSizer121, 1, wxEXPAND, 5 );
	
	
	bSizer127->Add( bSizer111, 0, wxEXPAND, 5 );
	
	
	m_panel211->SetSizer( bSizer127 );
	m_panel211->Layout();
	bSizer127->Fit( m_panel211 );
	m_notebook5->AddPage( m_panel211, _("Children"), false );
	m_panel21 = new wxPanel( m_notebook5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer222;
	bSizer222 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEvent = new wxListCtrl( m_panel21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEvent->SetMinSize( wxSize( 300,130 ) );
	
	bSizer222->Add( m_listEvent, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2212;
	bSizer2212 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEventAdd = new wxButton( m_panel21, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventAdd, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventEdit = new wxButton( m_panel21, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEventDel = new wxButton( m_panel21, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2212->Add( m_buttonEventDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer22111;
	bSizer22111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonEventUp = new wxButton( m_panel21, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer22111->Add( m_buttonEventUp, 0, wxALL, 5 );
	
	
	bSizer22111->Add( 0, 0, 1, wxEXPAND, 0 );
	
	m_buttonEventDn = new wxButton( m_panel21, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer22111->Add( m_buttonEventDn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer2212->Add( bSizer22111, 1, wxEXPAND, 5 );
	
	
	bSizer222->Add( bSizer2212, 0, wxEXPAND, 5 );
	
	
	m_panel21->SetSizer( bSizer222 );
	m_panel21->Layout();
	bSizer222->Fit( m_panel21 );
	m_notebook5->AddPage( m_panel21, _("Events"), false );
	
	bSizer1->Add( m_notebook5, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxALL, 7 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 7 );
	
	
	bSizer1->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_buttonHusb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnHusbButton ), NULL, this );
	m_buttonWife->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnWifeButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildDeleteButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildUpButton ), NULL, this );
	m_button1Dn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildDownButton ), NULL, this );
	m_buttonEventAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventDownButton ), NULL, this );
}

fbDlgEditFamily::~fbDlgEditFamily()
{
	// Disconnect Events
	m_buttonHusb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnHusbButton ), NULL, this );
	m_buttonWife->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnWifeButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildDeleteButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildUpButton ), NULL, this );
	m_button1Dn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnChildDownButton ), NULL, this );
	m_buttonEventAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventAddButton ), NULL, this );
	m_buttonEventEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventEditButton ), NULL, this );
	m_buttonEventDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventDeleteButton ), NULL, this );
	m_buttonEventUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventUpButton ), NULL, this );
	m_buttonEventDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamily::OnEventDownButton ), NULL, this );
	
}

fbDlgEditFamily1::fbDlgEditFamily1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Family ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticFamID = new wxStaticText( this, tfpID_EDFAM_FAM_ID, _("F0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticFamID->Wrap( -1 );
	m_staticFamID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer2->Add( m_staticFamID, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_buttonHusbID = new wxButton( this, tfpID_EDFAM_HUSB_BUT, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer2->Add( m_buttonHusbID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Husband:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer2->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticHusbName = new wxStaticText( this, tfpID_EDFAM_HUSB_NAM, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticHusbName->Wrap( -1 );
	fgSizer2->Add( m_staticHusbName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonWife = new wxButton( this, tfpID_EDFAM_WIFE_BUT, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer2->Add( m_buttonWife, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Wife:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer2->Add( m_staticText9, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticWifeName = new wxStaticText( this, tfpID_EDFAM_WIFE_NAM, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticWifeName->Wrap( -1 );
	fgSizer2->Add( m_staticWifeName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonMarr = new wxButton( this, tfpID_EDFAM_MARR_BUT, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer2->Add( m_buttonMarr, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Marriage:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer2->Add( m_staticText12, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticMarrEvent = new wxStaticText( this, tfpID_EDFAM_MARR_EV, _("Event"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticMarrEvent->Wrap( -1 );
	fgSizer2->Add( m_staticMarrEvent, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Children:") ), wxHORIZONTAL );
	
	m_listChild = new wxListBox( this, tfpID_EDFAM_CHILD_LIST, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE ); 
	sbSizer1->Add( m_listChild, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( this, tfpID_EDFAM_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( this, tfpID_EDFAM_EDIT, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonDel = new wxButton( this, tfpID_EDFAM_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( this, tfpID_EDFAM_UP, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonUp, 0, wxALL, 5 );
	
	m_button1Dn = new wxButton( this, tfpID_EDFAM_DOWN, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_button1Dn, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	sbSizer1->Add( bSizer11, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
}

fbDlgEditFamily1::~fbDlgEditFamily1()
{
}

fbDlgEditDate::fbDlgEditDate( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextId = new wxStaticText( this, wxID_ANY, _("D 0:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextId->Wrap( -1 );
	fgSizer3->Add( m_staticTextId, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticTextOutput = new wxStaticText( this, wxID_ANY, _("*"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOutput->Wrap( -1 );
	m_staticTextOutput->SetFont( wxFont( 11, 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticTextOutput, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer3->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlDate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlDate->SetMaxLength( 0 ); 
	fgSizer3->Add( m_textCtrlDate, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer3->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Unstated"), _("After"), _("On"), _("On or after"), _("Before"), _("Not"), _("On or before"), _("About") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 2 );
	fgSizer3->Add( m_choiceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText40 = new wxStaticText( this, wxID_ANY, _("Original:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	fgSizer3->Add( m_staticText40, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxString m_choiceOriginalChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceOriginalNChoices = sizeof( m_choiceOriginalChoices ) / sizeof( wxString );
	m_choiceOriginal = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceOriginalNChoices, m_choiceOriginalChoices, 0 );
	m_choiceOriginal->SetSelection( 3 );
	fgSizer3->Add( m_choiceOriginal, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, _("Display:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	fgSizer3->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxString m_choiceDisplayChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 3 );
	fgSizer3->Add( m_choiceDisplay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer131->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( m_buttonSave, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( m_buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( bSizer131, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditDate::SetStaticDate ) );
}

fbDlgEditDate::~fbDlgEditDate()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditDate::SetStaticDate ) );
	
}

fbDlgEditDateFromAge::fbDlgEditDateFromAge( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextId = new wxStaticText( this, wxID_ANY, _("D 0:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextId->Wrap( -1 );
	fgSizer11->Add( m_staticTextId, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticTextOutput = new wxStaticText( this, wxID_ANY, _("*"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOutput->Wrap( -1 );
	m_staticTextOutput->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer11->Add( m_staticTextOutput, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Age:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText5->Wrap( -1 );
	fgSizer11->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlAge = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlAge->SetMaxLength( 0 ); 
	fgSizer11->Add( m_textCtrlAge, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("On:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer11->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlBaseDate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlBaseDate->SetMaxLength( 0 ); 
	m_textCtrlBaseDate->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer11->Add( m_textCtrlBaseDate, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Unstated"), _("After"), _("On"), _("On or after"), _("Before"), _("Not"), _("On or before"), _("About") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 2 );
	fgSizer11->Add( m_choiceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Based on:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxString m_choiceDisplayChoices[] = { _("Unstated"), _("Julian Day Number"), _("Julian"), _("Gregorian") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 3 );
	fgSizer11->Add( m_choiceDisplay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer11, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxUnitsChoices[] = { _("Years"), _("Months"), _("Weeks"), _("Days") };
	int m_radioBoxUnitsNChoices = sizeof( m_radioBoxUnitsChoices ) / sizeof( wxString );
	m_radioBoxUnits = new wxRadioBox( this, wxID_ANY, _("Set age units:"), wxDefaultPosition, wxDefaultSize, m_radioBoxUnitsNChoices, m_radioBoxUnitsChoices, 1, wxRA_SPECIFY_ROWS );
	m_radioBoxUnits->SetSelection( 0 );
	bSizer12->Add( m_radioBoxUnits, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer12, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditDateFromAge::SetStaticDate ) );
}

fbDlgEditDateFromAge::~fbDlgEditDateFromAge()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditDateFromAge::SetStaticDate ) );
	
}

fbDlgEditPlace::fbDlgEditPlace( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Place:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer47->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlAddr = new wxTextCtrl( this, tfpID_EDPLACE_ADDR, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_textCtrlAddr->SetMaxLength( 0 ); 
	bSizer47->Add( m_textCtrlAddr, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND|wxALIGN_RIGHT, 5 );
	
	
	bSizer11->Add( bSizer47, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer131->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizer131, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
}

fbDlgEditPlace::~fbDlgEditPlace()
{
}

fbDlgEditName::fbDlgEditName( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticName = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticName->Wrap( -1 );
	m_staticName->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticNameID = new wxStaticText( this, wxID_ANY, _("N 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNameID->Wrap( -1 );
	m_staticNameID->SetFont( wxFont( 10, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticNameID, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1a;
	bSizer1a = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1a = new wxStaticText( this, wxID_ANY, _("Style:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1a->Wrap( -1 );
	bSizer1a->Add( m_staticText1a, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceStyleChoices;
	m_choiceStyle = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStyleChoices, 0 );
	m_choiceStyle->SetSelection( 0 );
	bSizer1a->Add( m_choiceStyle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1a->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText65 = new wxStaticText( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	bSizer1a->Add( m_staticText65, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonPersona = new wxButton( this, wxID_ANY, _("Pa0"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1a->Add( m_buttonPersona, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizer1a, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listParts = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listParts->SetMinSize( wxSize( 300,-1 ) );
	
	bSizer2->Add( m_listParts, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonPartAdd = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_buttonPartAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonPartEdit = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_buttonPartEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonPartDel = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_buttonPartDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonPartUp = new wxButton( this, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer211->Add( m_buttonPartUp, 0, wxALL, 5 );
	
	m_buttonPartDn = new wxButton( this, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer211->Add( m_buttonPartDn, 0, wxALL, 5 );
	
	
	bSizer21->Add( bSizer211, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer21, 0, wxEXPAND, 5 );
	
	
	bSizer->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	m_buttonPersona->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPersonaButton ), NULL, this );
	m_buttonPartAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartAddButton ), NULL, this );
	m_buttonPartEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartEditButton ), NULL, this );
	m_buttonPartDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartDeleteButton ), NULL, this );
	m_buttonPartUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartUpButton ), NULL, this );
	m_buttonPartDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartDownButton ), NULL, this );
}

fbDlgEditName::~fbDlgEditName()
{
	// Disconnect Events
	m_buttonPersona->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPersonaButton ), NULL, this );
	m_buttonPartAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartAddButton ), NULL, this );
	m_buttonPartEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartEditButton ), NULL, this );
	m_buttonPartDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartDeleteButton ), NULL, this );
	m_buttonPartUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartUpButton ), NULL, this );
	m_buttonPartDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditName::OnPartDownButton ), NULL, this );
	
}

fbDlgEditNamePart::fbDlgEditNamePart( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticNameID = new wxStaticText( this, wxID_ANY, _("N0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNameID->Wrap( -1 );
	m_staticNameID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer11->Add( m_staticNameID, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticNamePartID = new wxStaticText( this, wxID_ANY, _("NP0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNamePartID->Wrap( -1 );
	m_staticNamePartID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer11->Add( m_staticNamePartID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer11->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 2 );
	fgSizer11->Add( m_choiceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer11->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlValue->SetMaxLength( 0 ); 
	fgSizer11->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	
	fgSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( fgSizer11, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonSave, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer1->Add( bSizer12, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
}

fbDlgEditNamePart::~fbDlgEditNamePart()
{
}

fbDlgEditEvent::fbDlgEditEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 5, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Event Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer4->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticType = new wxStaticText( this, wxID_ANY, _("Birth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticType->Wrap( -1 );
	m_staticType->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	fgSizer4->Add( m_staticType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer4->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_textCtrlTitle->SetMaxLength( 0 ); 
	m_textCtrlTitle->SetMinSize( wxSize( 350,-1 ) );
	
	fgSizer4->Add( m_textCtrlTitle, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonDateBeg = new wxButton( this, wxID_ANY, _("Date Start:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonDateBeg, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDateBeg = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlDateBeg->SetMaxLength( 0 ); 
	fgSizer4->Add( m_textCtrlDateBeg, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDateEnd = new wxButton( this, wxID_ANY, _("Date End:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonDateEnd, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDateEnd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlDateEnd->SetMaxLength( 0 ); 
	fgSizer4->Add( m_textCtrlDateEnd, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonPlace = new wxButton( this, wxID_ANY, _("Place:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonPlace, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPlace = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlPlace->SetMaxLength( 0 ); 
	fgSizer4->Add( m_textCtrlPlace, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer20->Add( fgSizer4, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Personas:") ), wxHORIZONTAL );
	
	m_listPersona = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listPersona->SetMinSize( wxSize( -1,125 ) );
	
	sbSizer1->Add( m_listPersona, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonDel = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( this, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonUp, 0, wxALL, 5 );
	
	m_buttonDn = new wxButton( this, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonDn, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	sbSizer1->Add( bSizer11, 0, wxEXPAND, 5 );
	
	
	bSizer20->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer20->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer20->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer20 );
	this->Layout();
	bSizer20->Fit( this );
	
	// Connect Events
	m_buttonDateBeg->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDateBegButton ), NULL, this );
	m_buttonDateEnd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDateEndButton ), NULL, this );
	m_buttonPlace->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnPlaceButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDeleteButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnUpButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDownButton ), NULL, this );
}

fbDlgEditEvent::~fbDlgEditEvent()
{
	// Disconnect Events
	m_buttonDateBeg->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDateBegButton ), NULL, this );
	m_buttonDateEnd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDateEndButton ), NULL, this );
	m_buttonPlace->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnPlaceButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDeleteButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnUpButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditEvent::OnDownButton ), NULL, this );
	
}

fbDlgEditIndEvent::fbDlgEditIndEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME );
	m_splitter->SetSashGravity( 0 );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditIndEvent::m_splitterOnIdle ), NULL, this );
	m_splitter->SetMinimumPaneSize( 1 );
	
	m_panel1 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter6 = new wxSplitterWindow( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME );
	m_splitter6->SetSashGravity( 0 );
	m_splitter6->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditIndEvent::m_splitter6OnIdle ), NULL, this );
	m_splitter6->SetMinimumPaneSize( 1 );
	
	m_panel11 = new wxPanel( m_splitter6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer111;
	fgSizer111 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer111->AddGrowableCol( 1 );
	fgSizer111->AddGrowableRow( 5 );
	fgSizer111->SetFlexibleDirection( wxBOTH );
	fgSizer111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText17 = new wxStaticText( m_panel11, wxID_ANY, _("Event type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer111->Add( m_staticText17, 0, wxALIGN_RIGHT|wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer1111;
	bSizer1111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticType = new wxStaticText( m_panel11, wxID_ANY, _("Birth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticType->Wrap( -1 );
	m_staticType->SetFont( wxFont( 9, 74, 90, 92, false, wxT("MS Shell Dlg 2") ) );
	
	bSizer1111->Add( m_staticType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1111->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticEventID = new wxStaticText( m_panel11, wxID_ANY, _("E0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticEventID->Wrap( -1 );
	m_staticEventID->SetFont( wxFont( 11, 72, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizer1111->Add( m_staticEventID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer111->Add( bSizer1111, 1, wxEXPAND, 5 );
	
	m_staticText171 = new wxStaticText( m_panel11, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText171->Wrap( -1 );
	fgSizer111->Add( m_staticText171, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( m_panel11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlTitle->SetMaxLength( 0 ); 
	fgSizer111->Add( m_textCtrlTitle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDate1 = new wxButton( m_panel11, wxID_ANY, _("Date:"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_RIGHT );
	fgSizer111->Add( m_buttonDate1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDate1 = new wxTextCtrl( m_panel11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlDate1->SetMaxLength( 0 ); 
	fgSizer111->Add( m_textCtrlDate1, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonDate2 = new wxButton( m_panel11, wxID_ANY, _("End Date:"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_RIGHT );
	fgSizer111->Add( m_buttonDate2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDate2 = new wxTextCtrl( m_panel11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_READONLY );
	m_textCtrlDate2->SetMaxLength( 0 ); 
	fgSizer111->Add( m_textCtrlDate2, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonPlace = new wxButton( m_panel11, wxID_ANY, _("Place:"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_RIGHT );
	fgSizer111->Add( m_buttonPlace, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAddr = new wxTextCtrl( m_panel11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	m_textCtrlAddr->SetMaxLength( 0 ); 
	fgSizer111->Add( m_textCtrlAddr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1711 = new wxStaticText( m_panel11, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1711->Wrap( -1 );
	fgSizer111->Add( m_staticText1711, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlNote = new wxTextCtrl( m_panel11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_MULTILINE );
	m_textCtrlNote->SetMaxLength( 0 ); 
	fgSizer111->Add( m_textCtrlNote, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	m_panel11->SetSizer( fgSizer111 );
	m_panel11->Layout();
	fgSizer111->Fit( m_panel11 );
	m_panel12 = new wxPanel( m_splitter6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_listPersona = new wxListCtrl( m_panel12, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES|wxSUNKEN_BORDER );
	m_listPersona->SetMinSize( wxSize( -1,125 ) );
	
	bSizer12->Add( m_listPersona, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAdd = new wxButton( m_panel12, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonEdit = new wxButton( m_panel12, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonDel = new wxButton( m_panel12, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	
	bSizer12->Add( bSizer121, 0, wxEXPAND, 5 );
	
	
	m_panel12->SetSizer( bSizer12 );
	m_panel12->Layout();
	bSizer12->Fit( m_panel12 );
	m_splitter6->SplitHorizontally( m_panel11, m_panel12, 230 );
	bSizer11->Add( m_splitter6, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer11 );
	m_panel1->Layout();
	bSizer11->Fit( m_panel1 );
	m_panel3 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook6 = new wxNotebook( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM );
	m_panelRef = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlRef = new wxHtmlWindow( m_panelRef, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer131->Add( m_htmlRef, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelRef->SetSizer( bSizer131 );
	m_panelRef->Layout();
	bSizer131->Fit( m_panelRef );
	m_notebook6->AddPage( m_panelRef, _("References"), true );
	m_panelDates = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlDate = new wxHtmlWindow( m_panelDates, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer132->Add( m_htmlDate, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelDates->SetSizer( bSizer132 );
	m_panelDates->Layout();
	bSizer132->Fit( m_panelDates );
	m_notebook6->AddPage( m_panelDates, _("Dates"), false );
	m_panelPlaces = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer133;
	bSizer133 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlPlace = new wxHtmlWindow( m_panelPlaces, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer133->Add( m_htmlPlace, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelPlaces->SetSizer( bSizer133 );
	m_panelPlaces->Layout();
	bSizer133->Fit( m_panelPlaces );
	m_notebook6->AddPage( m_panelPlaces, _("Places"), false );
	m_panelPersona = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer134;
	bSizer134 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlPersona = new wxHtmlWindow( m_panelPersona, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer134->Add( m_htmlPersona, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelPersona->SetSizer( bSizer134 );
	m_panelPersona->Layout();
	bSizer134->Fit( m_panelPersona );
	m_notebook6->AddPage( m_panelPersona, _("Persona"), false );
	m_panelInd = new wxPanel( m_notebook6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer135;
	bSizer135 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlInd = new wxHtmlWindow( m_panelInd, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer135->Add( m_htmlInd, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelInd->SetSizer( bSizer135 );
	m_panelInd->Layout();
	bSizer135->Fit( m_panelInd );
	m_notebook6->AddPage( m_panelInd, _("Individuals"), false );
	
	bSizer13->Add( m_notebook6, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel3->SetSizer( bSizer13 );
	m_panel3->Layout();
	bSizer13->Fit( m_panel3 );
	m_splitter->SplitVertically( m_panel1, m_panel3, 370 );
	bSizer1->Add( m_splitter, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 7 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 7 );
	
	
	bSizer1->Add( bSizer14, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonDate1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDate1Button ), NULL, this );
	m_buttonDate2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDate2Button ), NULL, this );
	m_buttonPlace->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnPlaceButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDeleteButton ), NULL, this );
}

fbDlgEditIndEvent::~fbDlgEditIndEvent()
{
	// Disconnect Events
	m_buttonDate1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDate1Button ), NULL, this );
	m_buttonDate2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDate2Button ), NULL, this );
	m_buttonPlace->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnPlaceButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDeleteButton ), NULL, this );
	
}

fbDlgEditFamEvent::fbDlgEditFamEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer52->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlTitle->SetMaxLength( 0 ); 
	bSizer52->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( bSizer52, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALIGN_RIGHT|wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlType = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlType->SetMaxLength( 0 ); 
	m_textCtrlType->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer3->Add( m_textCtrlType, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonType = new wxButton( this, wxID_ANY, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer3->Add( m_buttonType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlDate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlDate->SetMaxLength( 0 ); 
	m_textCtrlDate->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer3->Add( m_textCtrlDate, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonDate = new wxButton( this, wxID_ANY, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer3->Add( m_buttonDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlAddr = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_READONLY );
	m_textCtrlAddr->SetMaxLength( 0 ); 
	m_textCtrlAddr->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer3->Add( m_textCtrlAddr, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonAddr = new wxButton( this, wxID_ANY, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer3->Add( m_buttonAddr, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer53->Add( m_staticText5, 0, wxALL, 5 );
	
	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	m_textCtrlNote->SetMaxLength( 0 ); 
	bSizer53->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer11->Add( bSizer53, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer131->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizer131, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	// Connect Events
	m_buttonType->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamEvent::OnTypeButton ), NULL, this );
	m_buttonDate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamEvent::OnDateButton ), NULL, this );
	m_buttonAddr->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamEvent::OnAddrButton ), NULL, this );
}

fbDlgEditFamEvent::~fbDlgEditFamEvent()
{
	// Disconnect Events
	m_buttonType->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamEvent::OnTypeButton ), NULL, this );
	m_buttonDate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamEvent::OnDateButton ), NULL, this );
	m_buttonAddr->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditFamEvent::OnAddrButton ), NULL, this );
	
}

fbDlgEditRole::fbDlgEditRole( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableRow( 3 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Event:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer4->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticTextEvent = new wxStaticText( this, wxID_ANY, _("Birth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextEvent->Wrap( -1 );
	m_staticTextEvent->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	fgSizer4->Add( m_staticTextEvent, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonPersona = new wxButton( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonPersona, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPersona = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlPersona->SetMaxLength( 0 ); 
	m_textCtrlPersona->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer4->Add( m_textCtrlPersona, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonRole = new wxButton( this, wxID_ANY, _("Role:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonRole, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRole = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlRole->SetMaxLength( 0 ); 
	m_textCtrlRole->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer4->Add( m_textCtrlRole, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer4->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	m_textCtrlNote->SetMaxLength( 0 ); 
	fgSizer4->Add( m_textCtrlNote, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer20->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer20->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer20->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer20 );
	this->Layout();
	
	// Connect Events
	m_buttonPersona->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRole::OnPersonaButton ), NULL, this );
	m_buttonRole->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRole::OnRoleButton ), NULL, this );
}

fbDlgEditRole::~fbDlgEditRole()
{
	// Disconnect Events
	m_buttonPersona->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRole::OnPersonaButton ), NULL, this );
	m_buttonRole->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRole::OnRoleButton ), NULL, this );
	
}

fbDlgEditRelationship::fbDlgEditRelationship( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->AddGrowableRow( 2 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticRsNumber = new wxStaticText( this, wxID_ANY, _("Rs0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRsNumber->Wrap( -1 );
	m_staticRsNumber->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer1->Add( m_staticRsNumber, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonPersona1 = new wxButton( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_buttonPersona1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPersona1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlPersona1->SetMaxLength( 0 ); 
	m_textCtrlPersona1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer1->Add( m_textCtrlPersona1, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Is the:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlDescrip = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	m_textCtrlDescrip->SetMaxLength( 0 ); 
	fgSizer1->Add( m_textCtrlDescrip, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPersona2 = new wxButton( this, wxID_ANY, _("Of"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_buttonPersona2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPersona2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlPersona2->SetMaxLength( 0 ); 
	m_textCtrlPersona2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer1->Add( m_textCtrlPersona2, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizer2, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	m_buttonPersona1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRelationship::OnPersona1Button ), NULL, this );
	m_buttonPersona2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRelationship::OnPersona2Button ), NULL, this );
}

fbDlgEditRelationship::~fbDlgEditRelationship()
{
	// Disconnect Events
	m_buttonPersona1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRelationship::OnPersona1Button ), NULL, this );
	m_buttonPersona2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditRelationship::OnPersona2Button ), NULL, this );
	
}

fbDlgEditReference::fbDlgEditReference( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Reference ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer14->Add( m_staticText1, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	m_staticRefID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRefID->Wrap( -1 );
	m_staticRefID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer14->Add( m_staticRefID, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer20->Add( bSizer14, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText401 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	bSizer41->Add( m_staticText401, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlTitle->SetMaxLength( 0 ); 
	bSizer41->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer20->Add( bSizer41, 0, wxEXPAND, 5 );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH|wxSP_NO_XP_THEME );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditReference::m_splitter1OnIdle ), NULL, this );
	
	m_panel7 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	
	m_notebookTop = new wxNotebook( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM );
	m_panelSource = new wxPanel( m_notebookTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );
	
	m_toolBar1 = new wxToolBar( m_panelSource, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_toolBar1->AddTool( tfpID_EDREF_OnCut, wxEmptyString, wxBitmap( cut_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Cut"), wxEmptyString, NULL ); 
	
	m_toolBar1->AddTool( tfpID_EDREF_OnCopy, _("tool"), wxBitmap( copy_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Copy"), wxEmptyString, NULL ); 
	
	m_toolBar1->AddTool( tfpID_EDREF_OnPaste, _("tool"), wxBitmap( paste_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Paste"), wxEmptyString, NULL ); 
	
	m_toolBar1->AddSeparator(); 
	
	m_toolBar1->AddTool( tfpID_EDREF_OnUndo, _("tool"), wxBitmap( undo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Undo"), wxEmptyString, NULL ); 
	
	m_toolBar1->AddTool( tfpID_EDREF_OnRedo, _("tool"), wxBitmap( redo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Redo"), wxEmptyString, NULL ); 
	
	m_toolBar1->Realize(); 
	
	bSizer121->Add( m_toolBar1, 0, wxEXPAND, 5 );
	
	m_textCtrlStatement = new wxTextCtrl( m_panelSource, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_DONTWRAP|wxTE_MULTILINE );
	m_textCtrlStatement->SetMaxLength( 0 ); 
	m_textCtrlStatement->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer121->Add( m_textCtrlStatement, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelSource->SetSizer( bSizer121 );
	m_panelSource->Layout();
	bSizer121->Fit( m_panelSource );
	m_notebookTop->AddPage( m_panelSource, _("Source"), true );
	m_panelView = new wxPanel( m_notebookTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlView = new wxHtmlWindow( m_panelView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	bSizer122->Add( m_htmlView, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelView->SetSizer( bSizer122 );
	m_panelView->Layout();
	bSizer122->Fit( m_panelView );
	m_notebookTop->AddPage( m_panelView, _("View"), false );
	
	bSizer39->Add( m_notebookTop, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel7->SetSizer( bSizer39 );
	m_panel7->Layout();
	bSizer39->Fit( m_panel7 );
	m_panel11 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer79;
	bSizer79 = new wxBoxSizer( wxVERTICAL );
	
	m_notebookBottom = new wxNotebook( m_panel11, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelPersona = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listPersona = new wxListCtrl( m_panelPersona, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listPersona->SetMinSize( wxSize( -1,125 ) );
	
	bSizer22->Add( m_listPersona, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonPersonaAdd = new wxButton( m_panelPersona, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonPersonaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonPersonaEdit = new wxButton( m_panelPersona, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonPersonaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonPersonaDel = new wxButton( m_panelPersona, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( m_buttonPersonaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer22->Add( bSizer221, 0, wxEXPAND, 5 );
	
	
	m_panelPersona->SetSizer( bSizer22 );
	m_panelPersona->Layout();
	bSizer22->Fit( m_panelPersona );
	m_notebookBottom->AddPage( m_panelPersona, _("Persona"), false );
	m_panelEntities = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listEntities = new wxListCtrl( m_panelEntities, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEntities->SetMinSize( wxSize( -1,125 ) );
	
	bSizer40->Add( m_listEntities, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( m_panelEntities, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( m_panelEntities, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonDel = new wxButton( m_panelEntities, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( m_panelEntities, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonUp, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonDn = new wxButton( m_panelEntities, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonDn, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer11->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	bSizer40->Add( bSizer11, 0, wxEXPAND, 5 );
	
	
	m_panelEntities->SetSizer( bSizer40 );
	m_panelEntities->Layout();
	bSizer40->Fit( m_panelEntities );
	m_notebookBottom->AddPage( m_panelEntities, _("Entities"), true );
	
	bSizer79->Add( m_notebookBottom, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel11->SetSizer( bSizer79 );
	m_panel11->Layout();
	bSizer79->Fit( m_panel11 );
	m_splitter1->SplitHorizontally( m_panel7, m_panel11, 225 );
	bSizer20->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer20->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer20->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer20 );
	this->Layout();
	
	// Connect Events
	m_notebookTop->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler( fbDlgEditReference::OnStatementViewChanging ), NULL, this );
	this->Connect( tfpID_EDREF_OnCut, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnCopy, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnPaste, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnUndo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnRedo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	m_buttonPersonaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnPersonaAddButton ), NULL, this );
	m_buttonPersonaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnPersonaEditButton ), NULL, this );
	m_buttonPersonaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnPersonaDeleteButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDeleteButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnUpButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDownButton ), NULL, this );
}

fbDlgEditReference::~fbDlgEditReference()
{
	// Disconnect Events
	m_notebookTop->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler( fbDlgEditReference::OnStatementViewChanging ), NULL, this );
	this->Disconnect( tfpID_EDREF_OnCut, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnCopy, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnPaste, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnUndo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnRedo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	m_buttonPersonaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnPersonaAddButton ), NULL, this );
	m_buttonPersonaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnPersonaEditButton ), NULL, this );
	m_buttonPersonaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnPersonaDeleteButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDeleteButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnUpButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDownButton ), NULL, this );
	
}

fbDlgSelectIndividual::fbDlgSelectIndividual( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listInd = new tfpListCtrlIndividuals( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL|wxLC_VRULES );
	bSizer22->Add( m_listInd, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizer21->Add( bSizer22, 1, wxEXPAND, 5 );
	
	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer21->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonSave, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer21->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer21 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgSelectIndividual::OnIdle ) );
	m_listInd->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( fbDlgSelectIndividual::OnIndividualSelected ), NULL, this );
}

fbDlgSelectIndividual::~fbDlgSelectIndividual()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbDlgSelectIndividual::OnIdle ) );
	m_listInd->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( fbDlgSelectIndividual::OnIndividualSelected ), NULL, this );
	
}

fbDlgSelect::fbDlgSelect( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listCtrl = new dlgStrTableCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL|wxLC_VRULES );
	bSizer2->Add( m_listCtrl, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonCreate = new wxButton( this, wxID_ANY, _("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCreate, 0, wxALL, 5 );
	
	m_buttonUnknown = new wxButton( this, wxID_ANY, _("Unknown"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonUnknown, 0, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSelect = new wxButton( this, wxID_OK, _("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSelect, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgSelect::OnIdle ) );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgSelect::OnCreateButton ), NULL, this );
	m_buttonUnknown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgSelect::OnUnknownButton ), NULL, this );
}

fbDlgSelect::~fbDlgSelect()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbDlgSelect::OnIdle ) );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgSelect::OnCreateButton ), NULL, this );
	m_buttonUnknown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgSelect::OnUnknownButton ), NULL, this );
	
}

fbDlgEditResearcher::fbDlgEditResearcher( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Researcher ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticResID = new wxStaticText( this, wxID_ANY, _("Re0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticResID->Wrap( -1 );
	m_staticResID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticResID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticUserID = new wxStaticText( this, wxID_ANY, _("U0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUserID->Wrap( -1 );
	m_staticUserID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticUserID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxUser = new wxCheckBox( this, wxID_ANY, _("User"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_checkBoxUser, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizer1, 0, wxEXPAND, 5 );
	
	m_splitter4 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH|wxSP_NO_XP_THEME );
	m_splitter4->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditResearcher::m_splitter4OnIdle ), NULL, this );
	
	m_panel29 = new wxPanel( m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableRow( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText21 = new wxStaticText( m_panel29, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textName = new wxTextCtrl( m_panel29, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	m_textName->SetMaxLength( 0 ); 
	fgSizer2->Add( m_textName, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText22 = new wxStaticText( m_panel29, wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textComment = new wxTextCtrl( m_panel29, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_MULTILINE|wxTE_WORDWRAP );
	m_textComment->SetMaxLength( 0 ); 
	fgSizer2->Add( m_textComment, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText23 = new wxStaticText( m_panel29, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textIndID = new wxTextCtrl( m_panel29, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textIndID->SetMaxLength( 0 ); 
	bSizer21->Add( m_textIndID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticIndName = new wxStaticText( m_panel29, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndName->Wrap( -1 );
	bSizer21->Add( m_staticIndName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer2->Add( bSizer21, 1, wxEXPAND, 5 );
	
	
	m_panel29->SetSizer( fgSizer2 );
	m_panel29->Layout();
	fgSizer2->Fit( m_panel29 );
	m_panel30 = new wxPanel( m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer137;
	bSizer137 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listContacts = new wxListCtrl( m_panel30, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer137->Add( m_listContacts, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer138;
	bSizer138 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( m_panel30, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer138->Add( m_buttonAdd, 0, wxALL, 5 );
	
	m_buttonEdit = new wxButton( m_panel30, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer138->Add( m_buttonEdit, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_buttonDelete = new wxButton( m_panel30, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer138->Add( m_buttonDelete, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer137->Add( bSizer138, 0, wxEXPAND, 5 );
	
	
	m_panel30->SetSizer( bSizer137 );
	m_panel30->Layout();
	bSizer137->Fit( m_panel30 );
	m_splitter4->SplitHorizontally( m_panel29, m_panel30, 0 );
	bSizer->Add( m_splitter4, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT, 7 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonCancel, 0, wxALL, 7 );
	
	
	bSizer->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditResearcher::OnButtonClickAdd ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditResearcher::OnButtonClickEdit ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditResearcher::OnButtonClickDelete ), NULL, this );
}

fbDlgEditResearcher::~fbDlgEditResearcher()
{
	// Disconnect Events
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditResearcher::OnButtonClickAdd ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditResearcher::OnButtonClickEdit ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditResearcher::OnButtonClickDelete ), NULL, this );
	
}

fbDlgEditContact::fbDlgEditContact( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->AddGrowableRow( 2 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("List ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( 8, 74, 90, 90, false, wxT("MS Shell Dlg 2") ) );
	
	fgSizer11->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer139;
	bSizer139 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticContactListID = new wxStaticText( this, wxID_ANY, _("CL0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticContactListID->Wrap( -1 );
	m_staticContactListID->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizer139->Add( m_staticContactListID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer139->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticContactID = new wxStaticText( this, wxID_ANY, _("Ct0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticContactID->Wrap( -1 );
	m_staticContactID->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizer139->Add( m_staticContactID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer11->Add( bSizer139, 1, wxEXPAND, 5 );
	
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
	
	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textCtrlValue->SetMaxLength( 0 ); 
	fgSizer11->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	
	fgSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( fgSizer11, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonSave, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer1->Add( bSizer12, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
}

fbDlgEditContact::~fbDlgEditContact()
{
}

fbDlgEditSystem::fbDlgEditSystem( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->AddGrowableRow( 1 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText = new wxStaticText( this, wxID_ANY, _("Current User:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	fgSizer11->Add( m_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxArrayString m_choiceUserChoices;
	m_choiceUser = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUserChoices, 0 );
	m_choiceUser->SetSelection( 0 );
	fgSizer11->Add( m_choiceUser, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	fgSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( fgSizer11, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonSave, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer1->Add( bSizer12, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
}

fbDlgEditSystem::~fbDlgEditSystem()
{
}

fbDlgEditUserSettings::fbDlgEditUserSettings( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 1 );
	fgSizer11->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("User:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer11->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer150;
	bSizer150 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticUserName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUserName->Wrap( -1 );
	m_staticUserName->SetFont( wxFont( 10, 74, 90, 92, false, wxT("MS Shell Dlg 2") ) );
	
	bSizer150->Add( m_staticUserName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer150->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticUserID = new wxStaticText( this, wxID_ANY, _("U0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUserID->Wrap( -1 );
	m_staticUserID->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Times New Roman") ) );
	
	bSizer150->Add( m_staticUserID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer11->Add( bSizer150, 1, wxEXPAND, 5 );
	
	m_staticText = new wxStaticText( this, wxID_ANY, _("Home Page:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	fgSizer11->Add( m_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlHome = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlHome->SetMaxLength( 0 ); 
	fgSizer11->Add( m_textCtrlHome, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( fgSizer11, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonSave, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer1->Add( bSizer12, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
}

fbDlgEditUserSettings::~fbDlgEditUserSettings()
{
}
