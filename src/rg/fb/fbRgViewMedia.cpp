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


#include "fbRgViewMedia.h"

///////////////////////////////////////////////////////////////////////////

fbRgViewMedia::fbRgViewMedia( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxToolBar* m_toolBar;
	m_toolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	m_checkScroll = new wxCheckBox( m_toolBar, wxID_ANY, _("Scroll:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxCHK_2STATE );
	m_toolBar->AddControl( m_checkScroll );
	m_toolBar->AddSeparator();

	m_buttonMinus = new wxButton( m_toolBar, wxID_ANY, _("-"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	m_toolBar->AddControl( m_buttonMinus );
	m_sliderZoom = new wxSlider( m_toolBar, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_toolBar->AddControl( m_sliderZoom );
	m_buttonPlus = new wxButton( m_toolBar, wxID_ANY, _("+"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	m_toolBar->AddControl( m_buttonPlus );
	m_toolBar->AddSeparator();

	m_staticTextZoom = new wxStaticText( m_toolBar, wxID_ANY, _("Zoom:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextZoom->Wrap( -1 );
	m_toolBar->AddControl( m_staticTextZoom );
	m_textCtrlZoom = new wxTextCtrl( m_toolBar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_toolBar->AddControl( m_textCtrlZoom );
	m_toolBar->AddSeparator();

	m_button100Percent = new wxButton( m_toolBar, wxID_ANY, _("100%"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	m_toolBar->AddControl( m_button100Percent );
	m_toolBar->AddSeparator();

	m_buttonExport = new wxButton( m_toolBar, wxID_ANY, _("Export"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	m_toolBar->AddControl( m_buttonExport );
	m_buttonPrint = new wxButton( m_toolBar, wxID_ANY, _("Print"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	m_toolBar->AddControl( m_buttonPrint );
	m_toolBar->Realize();

	bSizer1->Add( m_toolBar, 0, wxEXPAND, 5 );

	m_imageViewer = new rgImagePanel( this );
	m_imageViewer->SetMinSize( wxSize( 600,400 ) );

	bSizer1->Add( m_imageViewer, 1, wxALL|wxEXPAND, 0 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_checkScroll->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnCheckScroll ), NULL, this );
	m_buttonMinus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonMinus ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( fbRgViewMedia::OnZoomSlider ), NULL, this );
	m_buttonPlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonPlus ), NULL, this );
	m_textCtrlZoom->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( fbRgViewMedia::OnSetZoom ), NULL, this );
	m_button100Percent->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButton100Percent ), NULL, this );
	m_buttonExport->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonExport ), NULL, this );
	m_buttonPrint->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonPrint ), NULL, this );
}

fbRgViewMedia::~fbRgViewMedia()
{
	// Disconnect Events
	m_checkScroll->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnCheckScroll ), NULL, this );
	m_buttonMinus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonMinus ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( fbRgViewMedia::OnZoomSlider ), NULL, this );
	m_buttonPlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonPlus ), NULL, this );
	m_textCtrlZoom->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( fbRgViewMedia::OnSetZoom ), NULL, this );
	m_button100Percent->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButton100Percent ), NULL, this );
	m_buttonExport->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonExport ), NULL, this );
	m_buttonPrint->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgViewMedia::OnButtonPrint ), NULL, this );

}
