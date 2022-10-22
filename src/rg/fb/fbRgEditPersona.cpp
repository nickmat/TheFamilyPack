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


#include "fbRgEditPersona.h"

///////////////////////////////////////////////////////////////////////////

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
	m_staticPerName->SetFont( wxFont( 10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

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
	m_staticIndId->SetFont( wxFont( 10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

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

	bSizer65->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );


	bSizer63->Add( bSizer65, 1, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer63->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticPerID = new wxStaticText( this, wxID_ANY, _("Pa0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerID->Wrap( -1 );
	m_staticPerID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

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

}
