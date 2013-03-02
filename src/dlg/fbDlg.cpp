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


#include "fbDlg.h"

///////////////////////////////////////////////////////////////////////////

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
	m_textCtrlNote->SetMinSize( wxSize( 350,50 ) );
	
	bSizer212->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer21->Add( bSizer212, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer21 );
	m_panel1->Layout();
	bSizer21->Fit( m_panel1 );
	m_notebook->AddPage( m_panel1, _("Persona"), true );
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
	m_notebook->AddPage( m_panel21, _("Events"), false );
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
