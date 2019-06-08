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


#include "fbRgEditGallery.h"

///////////////////////////////////////////////////////////////////////////

fbRgEditGallery::fbRgEditGallery( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* m_staticText1;
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("&Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_textCtrlTitle, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* m_panelNote;
	m_panelNote = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrlNote = new wxTextCtrl( m_panelNote, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer4->Add( m_textCtrlNote, 1, wxEXPAND|wxALL, 5 );


	m_panelNote->SetSizer( bSizer4 );
	m_panelNote->Layout();
	bSizer4->Fit( m_panelNote );
	m_notebook->AddPage( m_panelNote, _("&Note"), false );
	wxPanel* m_panelMedia;
	m_panelMedia = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_listImage = new wxListCtrl( m_panelMedia, wxID_ANY, wxDefaultPosition, wxSize( 300,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer5->Add( m_listImage, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_buttonImageAdd = new wxButton( m_panelMedia, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_popupAddMedia = new wxMenu();
	wxMenuItem* m_opAddNewMedia;
	m_opAddNewMedia = new wxMenuItem( m_popupAddMedia, wxID_ANY, wxString( _("&New Image") ) , _("Add an external image to the Gallery"), wxITEM_NORMAL );
	m_popupAddMedia->Append( m_opAddNewMedia );

	wxMenuItem* m_opAddExistingMedia;
	m_opAddExistingMedia = new wxMenuItem( m_popupAddMedia, wxID_ANY, wxString( _("&Existing Image") ) , _("Add an image from the database to the Gallery"), wxITEM_NORMAL );
	m_popupAddMedia->Append( m_opAddExistingMedia );

	m_buttonImageAdd->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditGallery::m_buttonImageAddOnContextMenu ), NULL, this );

	bSizer6->Add( m_buttonImageAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_buttonImageEdit = new wxButton( m_panelMedia, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_buttonImageEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_buttonImageRemove = new wxButton( m_panelMedia, wxID_ANY, _("&Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_buttonImageRemove, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonImageUp = new wxButton( m_panelMedia, wxID_ANY, _("&Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer7->Add( m_buttonImageUp, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_buttonImageDn = new wxButton( m_panelMedia, wxID_ANY, _("&Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer7->Add( m_buttonImageDn, 1, wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );

	m_buttonViewImage = new wxButton( m_panelMedia, wxID_ANY, _("&View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_buttonViewImage, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizer5->Add( bSizer6, 0, wxEXPAND, 5 );


	m_panelMedia->SetSizer( bSizer5 );
	m_panelMedia->Layout();
	bSizer5->Fit( m_panelMedia );
	m_notebook->AddPage( m_panelMedia, _("&Images"), true );

	bSizer3->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticGalID = new wxStaticText( this, wxID_ANY, _("G0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticGalID->Wrap( -1 );
	m_staticGalID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticGalID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	// Connect Events
	m_buttonImageAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaAddButton ), NULL, this );
	m_popupAddMedia->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditGallery::OnAddNewMedia ), this, m_opAddNewMedia->GetId());
	m_popupAddMedia->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditGallery::OnAddExistingMedia ), this, m_opAddExistingMedia->GetId());
	m_buttonImageEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaEditButton ), NULL, this );
	m_buttonImageRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaRemoveButton ), NULL, this );
	m_buttonImageUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaUpButton ), NULL, this );
	m_buttonImageDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaDownButton ), NULL, this );
	m_buttonViewImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnViewImage ), NULL, this );
}

fbRgEditGallery::~fbRgEditGallery()
{
	// Disconnect Events
	m_buttonImageAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaAddButton ), NULL, this );
	m_buttonImageEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaEditButton ), NULL, this );
	m_buttonImageRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaRemoveButton ), NULL, this );
	m_buttonImageUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaUpButton ), NULL, this );
	m_buttonImageDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnMediaDownButton ), NULL, this );
	m_buttonViewImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditGallery::OnViewImage ), NULL, this );

	delete m_popupAddMedia;
}
