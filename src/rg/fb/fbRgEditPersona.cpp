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

	wxStaticText* m_staticText1;
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer64->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticPerName = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerName->Wrap( -1 );
	m_staticPerName->SetFont( wxFont( 10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	bSizer64->Add( m_staticPerName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer63->Add( bSizer64, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );

	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelDetail = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText111;
	m_staticText111 = new wxStaticText( m_panelDetail, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	fgSizer12->Add( m_staticText111, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( m_panelDetail, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	fgSizer12->Add( m_choiceSex, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText83;
	m_staticText83 = new wxStaticText( m_panelDetail, wxID_ANY, _("Reference:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText83->Wrap( -1 );
	fgSizer12->Add( m_staticText83, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

	m_textCtrlRef = new wxTextCtrl( m_panelDetail, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlRef, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	wxStaticText* m_staticText84;
	m_staticText84 = new wxStaticText( m_panelDetail, wxID_ANY, _("UID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText84->Wrap( -1 );
	fgSizer12->Add( m_staticText84, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlUid = new wxTextCtrl( m_panelDetail, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlUid, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );

	wxStaticText* m_staticText86;
	m_staticText86 = new wxStaticText( m_panelDetail, wxID_ANY, _("Changed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText86->Wrap( -1 );
	fgSizer12->Add( m_staticText86, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlChanged = new wxTextCtrl( m_panelDetail, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlChanged, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );


	m_panelDetail->SetSizer( fgSizer12 );
	m_panelDetail->Layout();
	fgSizer12->Fit( m_panelDetail );
	m_notebook->AddPage( m_panelDetail, _("Details"), true );
	m_panelNote = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxVERTICAL );

	m_textCtrlNote = new wxTextCtrl( m_panelNote, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_MULTILINE );
	bSizer66->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );


	m_panelNote->SetSizer( bSizer66 );
	m_panelNote->Layout();
	bSizer66->Fit( m_panelNote );
	m_notebook->AddPage( m_panelNote, _("Note"), false );
	m_panelName = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );

	m_listName = new wxListCtrl( m_panelName, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer71->Add( m_listName, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxVERTICAL );

	m_buttonNameAdd = new wxButton( m_panelName, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_buttonNameAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonNameEdit = new wxButton( m_panelName, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_buttonNameEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonNameDel = new wxButton( m_panelName, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_buttonNameDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	wxBoxSizer* bSizer73;
	bSizer73 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonNameUp = new wxButton( m_panelName, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer73->Add( m_buttonNameUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonNameDn = new wxButton( m_panelName, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer73->Add( m_buttonNameDn, 1, wxBOTTOM|wxRIGHT, 5 );


	bSizer72->Add( bSizer73, 1, wxEXPAND, 5 );


	bSizer71->Add( bSizer72, 0, wxEXPAND, 5 );


	m_panelName->SetSizer( bSizer71 );
	m_panelName->Layout();
	bSizer71->Fit( m_panelName );
	m_notebook->AddPage( m_panelName, _("Names"), false );
	m_panelEventa = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );

	m_listEventa = new wxListCtrl( m_panelEventa, wxID_ANY, wxDefaultPosition, wxSize( 400,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer74->Add( m_listEventa, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxVERTICAL );

	m_buttonEventaAdd = new wxButton( m_panelEventa, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_buttonEventaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonEventaEdit = new wxButton( m_panelEventa, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_buttonEventaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonEventaDel = new wxButton( m_panelEventa, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_buttonEventaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonEventaUp = new wxButton( m_panelEventa, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventaUp->Enable( false );

	bSizer76->Add( m_buttonEventaUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonEventaDn = new wxButton( m_panelEventa, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonEventaDn->Enable( false );

	bSizer76->Add( m_buttonEventaDn, 1, wxBOTTOM|wxRIGHT, 5 );


	bSizer75->Add( bSizer76, 1, wxEXPAND, 5 );

	wxString m_radioBoxEventaOrderChoices[] = { _("Preference"), _("Date Point") };
	int m_radioBoxEventaOrderNChoices = sizeof( m_radioBoxEventaOrderChoices ) / sizeof( wxString );
	m_radioBoxEventaOrder = new wxRadioBox( m_panelEventa, wxID_ANY, _("Order by:-"), wxDefaultPosition, wxDefaultSize, m_radioBoxEventaOrderNChoices, m_radioBoxEventaOrderChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxEventaOrder->SetSelection( 0 );
	bSizer75->Add( m_radioBoxEventaOrder, 0, wxBOTTOM|wxRIGHT, 5 );


	bSizer74->Add( bSizer75, 0, wxEXPAND, 5 );


	m_panelEventa->SetSizer( bSizer74 );
	m_panelEventa->Layout();
	bSizer74->Fit( m_panelEventa );
	m_notebook->AddPage( m_panelEventa, _("Eventa"), false );
	m_panelIndividual = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer741;
	bSizer741 = new wxBoxSizer( wxHORIZONTAL );

	m_listIndividual = new wxListCtrl( m_panelIndividual, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer741->Add( m_listIndividual, 1, wxEXPAND|wxALL, 5 );

	wxBoxSizer* bSizer751;
	bSizer751 = new wxBoxSizer( wxVERTICAL );

	m_buttonIndAdd = new wxButton( m_panelIndividual, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer751->Add( m_buttonIndAdd, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_buttonIndEdit = new wxButton( m_panelIndividual, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer751->Add( m_buttonIndEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonIndDel = new wxButton( m_panelIndividual, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer751->Add( m_buttonIndDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	wxBoxSizer* bSizer761;
	bSizer761 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonIndUp = new wxButton( m_panelIndividual, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonIndUp->Enable( false );

	bSizer761->Add( m_buttonIndUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonIndDn = new wxButton( m_panelIndividual, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_buttonIndDn->Enable( false );

	bSizer761->Add( m_buttonIndDn, 1, wxBOTTOM|wxRIGHT, 5 );


	bSizer751->Add( bSizer761, 0, wxEXPAND, 5 );


	bSizer741->Add( bSizer751, 0, wxEXPAND, 5 );


	m_panelIndividual->SetSizer( bSizer741 );
	m_panelIndividual->Layout();
	bSizer741->Fit( m_panelIndividual );
	m_notebook->AddPage( m_panelIndividual, _("Individual"), false );

	bSizer65->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );


	bSizer63->Add( bSizer65, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer63->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticPerID = new wxStaticText( this, wxID_ANY, _("Pa0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerID->Wrap( -1 );
	m_staticPerID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizerDismiss->Add( m_staticPerID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer63->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer63 );
	this->Layout();
	bSizer63->Fit( this );

	// Connect Events
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditPersona::OnPageChanged ), NULL, this );
	m_listName->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditPersona::OnNameDeselect ), NULL, this );
	m_listName->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditPersona::OnNameSelect ), NULL, this );
	m_buttonNameAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDownButton ), NULL, this );
	m_listEventa->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditPersona::OnEventaDeselect ), NULL, this );
	m_listEventa->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditPersona::OnEventaSelect ), NULL, this );
	m_buttonEventaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaAddButton ), NULL, this );
	m_buttonEventaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaEditButton ), NULL, this );
	m_buttonEventaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaDeleteButton ), NULL, this );
	m_buttonEventaUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaUpButton ), NULL, this );
	m_buttonEventaDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaDownButton ), NULL, this );
	m_radioBoxEventaOrder->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditPersona::OnEventaOrderBy ), NULL, this );
	m_listIndividual->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditPersona::OnIndDeselect ), NULL, this );
	m_listIndividual->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditPersona::OnIndSelect ), NULL, this );
	m_buttonIndAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndAddButton ), NULL, this );
	m_buttonIndEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndEditButton ), NULL, this );
	m_buttonIndDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndDeleteButton ), NULL, this );
	m_buttonIndUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndUpButton ), NULL, this );
	m_buttonIndDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndDownButton ), NULL, this );
}

fbRgEditPersona::~fbRgEditPersona()
{
	// Disconnect Events
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditPersona::OnPageChanged ), NULL, this );
	m_listName->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditPersona::OnNameDeselect ), NULL, this );
	m_listName->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditPersona::OnNameSelect ), NULL, this );
	m_buttonNameAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameAddButton ), NULL, this );
	m_buttonNameEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameEditButton ), NULL, this );
	m_buttonNameDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDeleteButton ), NULL, this );
	m_buttonNameUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameUpButton ), NULL, this );
	m_buttonNameDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnNameDownButton ), NULL, this );
	m_listEventa->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditPersona::OnEventaDeselect ), NULL, this );
	m_listEventa->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditPersona::OnEventaSelect ), NULL, this );
	m_buttonEventaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaAddButton ), NULL, this );
	m_buttonEventaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaEditButton ), NULL, this );
	m_buttonEventaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaDeleteButton ), NULL, this );
	m_buttonEventaUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaUpButton ), NULL, this );
	m_buttonEventaDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnEventaDownButton ), NULL, this );
	m_radioBoxEventaOrder->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fbRgEditPersona::OnEventaOrderBy ), NULL, this );
	m_listIndividual->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditPersona::OnIndDeselect ), NULL, this );
	m_listIndividual->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditPersona::OnIndSelect ), NULL, this );
	m_buttonIndAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndAddButton ), NULL, this );
	m_buttonIndEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndEditButton ), NULL, this );
	m_buttonIndDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndDeleteButton ), NULL, this );
	m_buttonIndUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndUpButton ), NULL, this );
	m_buttonIndDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditPersona::OnIndDownButton ), NULL, this );

}

fbRgLinkIndPersona::fbRgLinkIndPersona( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText10;
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer2->Add( m_staticText10, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlInd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	fgSizer2->Add( m_textCtrlInd, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );

	wxStaticText* m_staticText11;
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer2->Add( m_staticText11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlPersona = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer2->Add( m_textCtrlPersona, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText12;
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Reference:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer2->Add( m_staticText12, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlReference = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer2->Add( m_textCtrlReference, 0, wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );

	wxStaticText* m_staticText13;
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("Confidence:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer2->Add( m_staticText13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlConf = new wxTextCtrl( this, wxID_ANY, _("99.9%"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlConf, 0, wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText14;
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer2->Add( m_staticText14, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,50 ), wxTE_MULTILINE|wxTE_WORDWRAP );
	fgSizer2->Add( m_textCtrlNote, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );


	bSizer15->Add( fgSizer2, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer15->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticIndPerID = new wxStaticText( this, wxID_ANY, _("IPa0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndPerID->Wrap( -1 );
	m_staticIndPerID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizerDismiss->Add( m_staticIndPerID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer15->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer15 );
	this->Layout();
	bSizer15->Fit( this );

	this->Centre( wxBOTH );
}

fbRgLinkIndPersona::~fbRgLinkIndPersona()
{
}
