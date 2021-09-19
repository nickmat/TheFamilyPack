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


#include "fbRgEditMedia.h"

///////////////////////////////////////////////////////////////////////////

fbRgEditMedia::fbRgEditMedia( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* m_staticText2;
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer2->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer2->Add( m_textCtrlTitle, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH|wxSP_NO_XP_THEME );
	m_splitter1->SetSashGravity( 0 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditMedia::m_splitter1OnIdle ), NULL, this );

	m_panelNote = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( m_panelNote, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer9->Add( m_staticText7, 0, wxALL, 5 );

	m_textCtrlNote = new wxTextCtrl( m_panelNote, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE );
	bSizer9->Add( m_textCtrlNote, 1, wxALL|wxEXPAND, 5 );


	m_panelNote->SetSizer( bSizer9 );
	m_panelNote->Layout();
	bSizer9->Fit( m_panelNote );
	m_panelImage = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_imagePanel = new rgImagePanel( m_panelImage);
	m_imagePanel->SetMinSize( wxSize( 500,250 ) );

	bSizer10->Add( m_imagePanel, 1, wxALL|wxEXPAND, 5 );


	m_panelImage->SetSizer( bSizer10 );
	m_panelImage->Layout();
	bSizer10->Fit( m_panelImage );
	m_splitter1->SplitHorizontally( m_panelNote, m_panelImage, 100 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND|wxALL, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText = new wxStaticText( this, wxID_ANY, _("Reference ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	bSizer8->Add( m_staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlRefID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_textCtrlRefID, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_staticTextRefTitle = new wxStaticText( this, wxID_ANY, _("RefTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRefTitle->Wrap( -1 );
	bSizer8->Add( m_staticTextRefTitle, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );


	bSizer1->Add( bSizer8, 0, 0, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("File:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer4->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlFile = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_textCtrlFile, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );


	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticMediaID = new wxStaticText( this, wxID_ANY, _("M00"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticMediaID->Wrap( -1 );
	m_staticMediaID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticMediaID, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


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

fbRgEditMedia::~fbRgEditMedia()
{
}

fbRgEditMediaData::fbRgEditMediaData( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	wxStaticText* m_staticText2;
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	fgSizer1->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	wxStaticText* m_staticText13;
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("File:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer1->Add( m_staticText13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_textCtrlFile = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textCtrlFile, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );


	bSizer8->Add( fgSizer1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* m_staticText17;
	m_staticText17 = new wxStaticText( this, wxID_ANY, _("File Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer15->Add( m_staticText17, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	wxArrayString m_choiceFileTypeChoices;
	m_choiceFileType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceFileTypeChoices, 0 );
	m_choiceFileType->SetSelection( 0 );
	bSizer15->Add( m_choiceFileType, 0, wxALL, 5 );

	wxStaticText* m_staticText14;
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Copyright:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer15->Add( m_staticText14, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_textCtrlCopyright = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_textCtrlCopyright, 2, wxALL, 5 );

	wxStaticText* m_staticText15;
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("Privacy:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer15->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_spinPrivacy = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer15->Add( m_spinPrivacy, 0, wxALL, 5 );


	bSizer8->Add( bSizer15, 0, wxEXPAND, 5 );

	m_panelImage = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_imagePanel = new rgImagePanel( m_panelImage);
	m_imagePanel->SetMinSize( wxSize( 500,250 ) );

	bSizer10->Add( m_imagePanel, 1, wxEXPAND|wxALL, 5 );


	m_panelImage->SetSizer( bSizer10 );
	m_panelImage->Layout();
	bSizer10->Fit( m_panelImage );
	bSizer8->Add( m_panelImage, 1, wxALL|wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticMediaDataID = new wxStaticText( this, wxID_ANY, _("A0:MD0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticMediaDataID->Wrap( -1 );
	m_staticMediaDataID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticMediaDataID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave = new wxButton( this, wxID_OK, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer8->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer8 );
	this->Layout();
	bSizer8->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_imagePanel->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( fbRgEditMediaData::OnLeftDClick ), NULL, this );
}

fbRgEditMediaData::~fbRgEditMediaData()
{
	// Disconnect Events
	m_imagePanel->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( fbRgEditMediaData::OnLeftDClick ), NULL, this );

}
