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


#include "fbRgEditCitation.h"

///////////////////////////////////////////////////////////////////////////

fbRgEditCitation::fbRgEditCitation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->AddGrowableRow( 1 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText64;
	m_staticText64 = new wxStaticText( this, wxID_ANY, _("Citation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	fgSizer12->Add( m_staticText64, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlCitation = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlCitation, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText65;
	m_staticText65 = new wxStaticText( this, wxID_ANY, _("C&omment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	fgSizer12->Add( m_staticText65, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlComment = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( m_textCtrlComment, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonSelectExtends = new wxButton( this, wxID_ANY, _("E&xtends:"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	fgSizer12->Add( m_buttonSelectExtends, 0, wxBOTTOM|wxRIGHT, 5 );

	m_textCtrlExtends = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlExtends, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );

	m_buttontRepository = new wxButton( this, wxID_ANY, _("Reposi&tory"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT );
	m_menuRepository = new wxMenu();
	wxMenuItem* m_menuSelectRep;
	m_menuSelectRep = new wxMenuItem( m_menuRepository, wxID_ANY, wxString( _("&Select") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuRepository->Append( m_menuSelectRep );

	wxMenuItem* m_menuEditRep;
	m_menuEditRep = new wxMenuItem( m_menuRepository, wxID_ANY, wxString( _("&Edit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuRepository->Append( m_menuEditRep );

	m_buttontRepository->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditCitation::m_buttontRepositoryOnContextMenu ), NULL, this );

	fgSizer12->Add( m_buttontRepository, 0, wxBOTTOM|wxRIGHT, 5 );

	m_textCtrlArchive = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlArchive, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );


	bSizer4->Add( fgSizer12, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("&Parts:") ), wxHORIZONTAL );

	m_listParts = new wxListCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 300,125 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	sbSizer1->Add( m_listParts, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );

	m_buttonAdd = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonAdd, 0, wxTOP|wxBOTTOM, 5 );

	m_buttonEdit = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonEdit, 0, wxBOTTOM, 5 );

	m_buttonDelete = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonDelete, 0, wxBOTTOM, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonUp = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonDown = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("Do&wn"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonDown, 1, wxBOTTOM, 5 );


	bSizer50->Add( bSizer12, 1, wxEXPAND, 5 );


	sbSizer1->Add( bSizer50, 0, wxEXPAND, 0 );


	bSizer4->Add( sbSizer1, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline14;
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline14, 0, wxEXPAND | wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticRefCiID = new wxStaticText( this, wxID_ANY, _("R0:Ci0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRefCiID->Wrap( -1 );
	m_staticRefCiID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticRefCiID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer4->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonSelectExtends->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonSelectExtends ), NULL, this );
	m_buttontRepository->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonRepository ), NULL, this );
	m_menuRepository->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditCitation::OnSelectRepository ), this, m_menuSelectRep->GetId());
	m_menuRepository->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditCitation::OnEditRepository ), this, m_menuEditRep->GetId());
	m_listParts->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditCitation::OnPartDeselect ), NULL, this );
	m_listParts->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditCitation::OnPartSelect ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonAdd ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonEdit ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonDelete ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonUp ), NULL, this );
	m_buttonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonDown ), NULL, this );
}

fbRgEditCitation::~fbRgEditCitation()
{
	// Disconnect Events
	m_buttonSelectExtends->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonSelectExtends ), NULL, this );
	m_buttontRepository->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonRepository ), NULL, this );
	m_listParts->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditCitation::OnPartDeselect ), NULL, this );
	m_listParts->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditCitation::OnPartSelect ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonAdd ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonEdit ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonDelete ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonUp ), NULL, this );
	m_buttonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitation::OnButtonDown ), NULL, this );

	delete m_menuRepository;
}

fbRgEditRepository::fbRgEditRepository( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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

	wxStaticText* m_staticText64;
	m_staticText64 = new wxStaticText( this, wxID_ANY, _("&Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	fgSizer12->Add( m_staticText64, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( m_textCtrlName, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText65;
	m_staticText65 = new wxStaticText( this, wxID_ANY, _("N&ote:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	fgSizer12->Add( m_staticText65, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE|wxTE_WORDWRAP );
	fgSizer12->Add( m_textCtrlNote, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText15;
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("UID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer12->Add( m_staticText15, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlUid = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlUid, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxStaticText* m_staticText16;
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Changed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer12->Add( m_staticText16, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

	m_textCtrlChanged = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer12->Add( m_textCtrlChanged, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );


	bSizer48->Add( fgSizer12, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Con&tacts:") ), wxHORIZONTAL );

	m_listContacts = new wxListCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 300,125 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	sbSizer1->Add( m_listContacts, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );

	m_buttonAdd = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonAdd, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonEdit = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonEdit, 0, wxBOTTOM|wxLEFT, 5 );

	m_buttonDelete = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_buttonDelete, 0, wxBOTTOM|wxLEFT, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonUp = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("&Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer13->Add( m_buttonUp, 0, wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	m_buttonDown = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("Do&wn"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer13->Add( m_buttonDown, 0, wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer50->Add( bSizer13, 0, wxEXPAND, 5 );


	sbSizer1->Add( bSizer50, 0, wxEXPAND, 5 );


	bSizer48->Add( sbSizer1, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline14;
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer48->Add( m_staticline14, 0, wxEXPAND | wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticRepID = new wxStaticText( this, wxID_ANY, _("Rp0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRepID->Wrap( -1 );
	m_staticRepID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticRepID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer48->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer48 );
	this->Layout();
	bSizer48->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_listContacts->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditRepository::OnContactDeselected ), NULL, this );
	m_listContacts->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditRepository::OnContactSelected ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonAdd ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonEdit ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonDelete ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonUp ), NULL, this );
	m_buttonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonDown ), NULL, this );
}

fbRgEditRepository::~fbRgEditRepository()
{
	// Disconnect Events
	m_listContacts->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( fbRgEditRepository::OnContactDeselected ), NULL, this );
	m_listContacts->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fbRgEditRepository::OnContactSelected ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonAdd ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonEdit ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonDelete ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonUp ), NULL, this );
	m_buttonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditRepository::OnButtonDown ), NULL, this );

}

fbRgEditCitationPart::fbRgEditCitationPart( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText10;
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("&Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer3->Add( m_staticText10, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	bSizer14->Add( m_choiceType, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonTypeAdd = new wxButton( this, wxID_ANY, _("&Add/Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_menuAddEditType = new wxMenu();
	wxMenuItem* m_menuAddType;
	m_menuAddType = new wxMenuItem( m_menuAddEditType, wxID_ANY, wxString( _("&Add Type") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEditType->Append( m_menuAddType );

	wxMenuItem* m_menuEditType;
	m_menuEditType = new wxMenuItem( m_menuAddEditType, wxID_ANY, wxString( _("&Edit Type") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEditType->Append( m_menuEditType );

	m_buttonTypeAdd->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditCitationPart::m_buttonTypeAddOnContextMenu ), NULL, this );

	bSizer14->Add( m_buttonTypeAdd, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );


	fgSizer3->Add( bSizer14, 1, wxEXPAND, 5 );

	wxStaticText* m_staticText11;
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("&Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer3->Add( m_staticText11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	fgSizer3->Add( m_textCtrlValue, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText13;
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("C&omment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer3->Add( m_staticText13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlComment = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_textCtrlComment, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );


	bSizer9->Add( fgSizer3, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline3;
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer9->Add( m_staticline3, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticCipID = new wxStaticText( this, wxID_ANY, _("Ci0:CiP0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCipID->Wrap( -1 );
	m_staticCipID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticCipID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer9->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonTypeAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitationPart::OnAddEditButton ), NULL, this );
	m_menuAddEditType->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditCitationPart::OnAddType ), this, m_menuAddType->GetId());
	m_menuAddEditType->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditCitationPart::OnEditType ), this, m_menuEditType->GetId());
}

fbRgEditCitationPart::~fbRgEditCitationPart()
{
	// Disconnect Events
	m_buttonTypeAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditCitationPart::OnAddEditButton ), NULL, this );

	delete m_menuAddEditType;
}

fbRgEditCitationPartType::fbRgEditCitationPartType( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableRow( 1 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText14;
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("&Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer4->Add( m_staticText14, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	fgSizer4->Add( m_textCtrlName, 0, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText15;
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("C&omment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer4->Add( m_staticText15, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlComment = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlComment, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText18;
	m_staticText18 = new wxStaticText( this, wxID_ANY, _("St&yle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer4->Add( m_staticText18, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	wxArrayString m_choiceStyleChoices;
	m_choiceStyle = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStyleChoices, 0 );
	m_choiceStyle->SetSelection( 0 );
	fgSizer4->Add( m_choiceStyle, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText* m_staticText17;
	m_staticText17 = new wxStaticText( this, wxID_ANY, _("UID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer4->Add( m_staticText17, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlUid = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer4->Add( m_textCtrlUid, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );

	m_staticText181 = new wxStaticText( this, wxID_ANY, _("Changed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText181->Wrap( -1 );
	fgSizer4->Add( m_staticText181, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlChanged = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer4->Add( m_textCtrlChanged, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );


	bSizer12->Add( fgSizer4, 1, wxEXPAND, 5 );

	m_staticline9 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer12->Add( m_staticline9, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticCiPT_ID = new wxStaticText( this, wxID_ANY, _("CiPT0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCiPT_ID->Wrap( -1 );
	m_staticCiPT_ID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticCiPT_ID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer12->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer12 );
	this->Layout();
	bSizer12->Fit( this );

	this->Centre( wxBOTH );
}

fbRgEditCitationPartType::~fbRgEditCitationPartType()
{
}
