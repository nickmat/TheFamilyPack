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


#include "fbRgEditReference.h"

#include "../../img/ed/copy.xpm"
#include "../../img/ed/cut.xpm"
#include "../../img/ed/paste.xpm"
#include "../../img/ed/redo.xpm"
#include "../../img/ed/undo.xpm"

///////////////////////////////////////////////////////////////////////////

fbRgEditReference::fbRgEditReference( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer20->AddGrowableCol( 1 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* m_staticText401;
	m_staticText401 = new wxStaticText( this, wxID_ANY, _("&Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	fgSizer20->Add( m_staticText401, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer20->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	wxStaticText* m_staticText4;
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Higher Ref:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer20->Add( m_staticText4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlHigherRef = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer20->Add( m_textCtrlHigherRef, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	wxStaticText* m_staticText118;
	m_staticText118 = new wxStaticText( this, wxID_ANY, _("User &Label:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText118->Wrap( -1 );
	fgSizer20->Add( m_staticText118, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_textCtrlUserRef = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer20->Add( m_textCtrlUserRef, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizer49->Add( fgSizer20, 0, wxEXPAND, 5 );

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
	m_toolCut = m_toolBar1->AddTool( wxID_ANY, _("Cut"), wxBitmap( cut_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Cut"), wxEmptyString, NULL );

	m_toolCopy = m_toolBar1->AddTool( wxID_ANY, _("Copy"), wxBitmap( copy_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Copy"), wxEmptyString, NULL );

	m_toolPaste = m_toolBar1->AddTool( wxID_ANY, _("Paste"), wxBitmap( paste_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Paste"), wxEmptyString, NULL );

	m_toolBar1->AddSeparator();

	m_toolUndo = m_toolBar1->AddTool( wxID_ANY, _("Undo"), wxBitmap( undo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Undo"), wxEmptyString, NULL );

	m_toolRedo = m_toolBar1->AddTool( wxID_ANY, _("Redo"), wxBitmap( redo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Redo"), wxEmptyString, NULL );

	m_toolBar1->Realize();

	bSizer53->Add( m_toolBar1, 0, wxEXPAND, 5 );

	m_textCtrlStatement = new wxTextCtrl( m_panelSource, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 600,150 ), wxTE_DONTWRAP|wxTE_MULTILINE|wxHSCROLL );
	m_textCtrlStatement->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer53->Add( m_textCtrlStatement, 1, wxALL|wxEXPAND, 5 );


	m_panelSource->SetSizer( bSizer53 );
	m_panelSource->Layout();
	bSizer53->Fit( m_panelSource );
	m_notebookTop->AddPage( m_panelSource, _("S&ource"), false );
	m_panelView = new wxPanel( m_notebookTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxVERTICAL );

	m_webview = wxWebView::New(m_panelView, wxID_ANY);
	bSizer54->Add( m_webview, 1, wxALL|wxEXPAND, 5 );


	m_panelView->SetSizer( bSizer54 );
	m_panelView->Layout();
	bSizer54->Fit( m_panelView );
	m_notebookTop->AddPage( m_panelView, _("&View"), true );

	bSizer52->Add( m_notebookTop, 1, wxEXPAND|wxALL, 5 );


	m_panelTop->SetSizer( bSizer52 );
	m_panelTop->Layout();
	bSizer52->Fit( m_panelTop );
	m_panelBottom = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxVERTICAL );

	m_notebookBottom = new wxNotebook( m_panelBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelCitation = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1202;
	bSizer1202 = new wxBoxSizer( wxHORIZONTAL );

	m_listCitation = new wxListCtrl( m_panelCitation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer1202->Add( m_listCitation, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer5712;
	bSizer5712 = new wxBoxSizer( wxVERTICAL );

	m_buttonCitationAdd = new wxButton( m_panelCitation, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5712->Add( m_buttonCitationAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonCitationEdit = new wxButton( m_panelCitation, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5712->Add( m_buttonCitationEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonCitationDel = new wxButton( m_panelCitation, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5712->Add( m_buttonCitationDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	wxBoxSizer* bSizer6011;
	bSizer6011 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonCitationUp = new wxButton( m_panelCitation, wxID_ANY, _("&Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer6011->Add( m_buttonCitationUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonCitationDn = new wxButton( m_panelCitation, wxID_ANY, _("Do&wn"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer6011->Add( m_buttonCitationDn, 1, wxBOTTOM|wxRIGHT, 5 );


	bSizer5712->Add( bSizer6011, 1, wxEXPAND, 5 );


	bSizer1202->Add( bSizer5712, 0, wxEXPAND, 5 );


	m_panelCitation->SetSizer( bSizer1202 );
	m_panelCitation->Layout();
	bSizer1202->Fit( m_panelCitation );
	m_notebookBottom->AddPage( m_panelCitation, _("Citation"), false );
	m_panelMedia = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxHORIZONTAL );

	m_listMedia = new wxListCtrl( m_panelMedia, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer120->Add( m_listMedia, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer571;
	bSizer571 = new wxBoxSizer( wxVERTICAL );

	m_buttonMediaAdd = new wxButton( m_panelMedia, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonMediaEdit = new wxButton( m_panelMedia, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonMediaDel = new wxButton( m_panelMedia, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	wxBoxSizer* bSizer601;
	bSizer601 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonMediaUp = new wxButton( m_panelMedia, wxID_ANY, _("&Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer601->Add( m_buttonMediaUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonMediaDn = new wxButton( m_panelMedia, wxID_ANY, _("Do&wn"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer601->Add( m_buttonMediaDn, 1, wxBOTTOM|wxRIGHT, 5 );


	bSizer571->Add( bSizer601, 0, wxEXPAND, 5 );

	m_buttonMediaView = new wxButton( m_panelMedia, wxID_ANY, _("View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer571->Add( m_buttonMediaView, 0, wxBOTTOM|wxRIGHT, 5 );


	bSizer120->Add( bSizer571, 0, wxEXPAND, 5 );


	m_panelMedia->SetSizer( bSizer120 );
	m_panelMedia->Layout();
	bSizer120->Fit( m_panelMedia );
	m_notebookBottom->AddPage( m_panelMedia, _("&Media"), false );
	m_panelPersona = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );

	m_listPersona = new wxListCtrl( m_panelPersona, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer56->Add( m_listPersona, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );

	m_buttonPersonaAdd = new wxButton( m_panelPersona, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_menuAddPersona = new wxMenu();
	wxMenuItem* m_menuAddMale;
	m_menuAddMale = new wxMenuItem( m_menuAddPersona, wxID_ANY, wxString( _("Add &Male Persona") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddPersona->Append( m_menuAddMale );

	wxMenuItem* m_menuAddFemale;
	m_menuAddFemale = new wxMenuItem( m_menuAddPersona, wxID_ANY, wxString( _("Add &Female Persona") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddPersona->Append( m_menuAddFemale );

	wxMenuItem* m_menuAddUnknownPersona;
	m_menuAddUnknownPersona = new wxMenuItem( m_menuAddPersona, wxID_ANY, wxString( _("Add &Unknown Persona") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddPersona->Append( m_menuAddUnknownPersona );

	m_buttonPersonaAdd->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditReference::m_buttonPersonaAddOnContextMenu ), NULL, this );

	bSizer57->Add( m_buttonPersonaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonPersonaEdit = new wxButton( m_panelPersona, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( m_buttonPersonaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonPersonaDel = new wxButton( m_panelPersona, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( m_buttonPersonaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );


	bSizer56->Add( bSizer57, 0, wxEXPAND, 5 );


	m_panelPersona->SetSizer( bSizer56 );
	m_panelPersona->Layout();
	bSizer56->Fit( m_panelPersona );
	m_notebookBottom->AddPage( m_panelPersona, _("&Persona"), false );
	m_panelEventa = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1201;
	bSizer1201 = new wxBoxSizer( wxHORIZONTAL );

	m_listEventa = new wxListCtrl( m_panelEventa, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer1201->Add( m_listEventa, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer5711;
	bSizer5711 = new wxBoxSizer( wxVERTICAL );

	m_buttonEventaAdd = new wxButton( m_panelEventa, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_menuAddEventa = new wxMenu();
	wxMenuItem* m_menuAddGenEventa;
	m_menuAddGenEventa = new wxMenuItem( m_menuAddEventa, wxID_ANY, wxString( _("Add &General Eventa") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEventa->Append( m_menuAddGenEventa );

	wxMenuItem* m_menuAddPerEventa;
	m_menuAddPerEventa = new wxMenuItem( m_menuAddEventa, wxID_ANY, wxString( _("Add Personal &Eventa") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEventa->Append( m_menuAddPerEventa );

	m_buttonEventaAdd->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditReference::m_buttonEventaAddOnContextMenu ), NULL, this );

	bSizer5711->Add( m_buttonEventaAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonEventaEdit = new wxButton( m_panelEventa, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5711->Add( m_buttonEventaEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonEventaDel = new wxButton( m_panelEventa, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5711->Add( m_buttonEventaDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );


	bSizer1201->Add( bSizer5711, 0, wxEXPAND, 5 );


	m_panelEventa->SetSizer( bSizer1201 );
	m_panelEventa->Layout();
	bSizer1201->Fit( m_panelEventa );
	m_notebookBottom->AddPage( m_panelEventa, _("Eventa"), false );
	m_panelEntities = new wxPanel( m_notebookBottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );

	m_listEntities = new wxListCtrl( m_panelEntities, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEntities->SetMinSize( wxSize( -1,200 ) );

	bSizer58->Add( m_listEntities, 1, wxEXPAND|wxALL, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxVERTICAL );

	m_buttonAdd = new wxButton( m_panelEntities, wxID_ANY, _("&Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_menuAddEntity = new wxMenu();
	wxMenuItem* m_menuAddDate;
	m_menuAddDate = new wxMenuItem( m_menuAddEntity, wxID_ANY, wxString( _("&Date") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEntity->Append( m_menuAddDate );

	wxMenuItem* m_menuAddDateAge;
	m_menuAddDateAge = new wxMenuItem( m_menuAddEntity, wxID_ANY, wxString( _("Date A&ge") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEntity->Append( m_menuAddDateAge );

	wxMenuItem* m_menuAddPlace;
	m_menuAddPlace = new wxMenuItem( m_menuAddEntity, wxID_ANY, wxString( _("&Place") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEntity->Append( m_menuAddPlace );

	wxMenuItem* m_menuAddName;
	m_menuAddName = new wxMenuItem( m_menuAddEntity, wxID_ANY, wxString( _("&Name") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAddEntity->Append( m_menuAddName );

	m_buttonAdd->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( fbRgEditReference::m_buttonAddOnContextMenu ), NULL, this );

	bSizer59->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	m_buttonEdit = new wxButton( m_panelEntities, wxID_ANY, _("&Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	m_buttonDel = new wxButton( m_panelEntities, wxID_ANY, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5 );

	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonUp = new wxButton( m_panelEntities, wxID_ANY, _("&Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer60->Add( m_buttonUp, 1, wxBOTTOM|wxRIGHT, 5 );

	m_buttonDn = new wxButton( m_panelEntities, wxID_ANY, _("Do&wn"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer60->Add( m_buttonDn, 1, wxBOTTOM|wxRIGHT, 5 );


	bSizer59->Add( bSizer60, 1, wxEXPAND, 5 );


	bSizer58->Add( bSizer59, 0, 0, 5 );


	m_panelEntities->SetSizer( bSizer58 );
	m_panelEntities->Layout();
	bSizer58->Fit( m_panelEntities );
	m_notebookBottom->AddPage( m_panelEntities, _("Ent&ities"), true );

	bSizer55->Add( m_notebookBottom, 1, wxALL|wxEXPAND, 5 );


	m_panelBottom->SetSizer( bSizer55 );
	m_panelBottom->Layout();
	bSizer55->Fit( m_panelBottom );
	m_splitter1->SplitHorizontally( m_panelTop, m_panelBottom, 275 );
	bSizer49->Add( m_splitter1, 1, wxEXPAND, 5 );

	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer49->Add( m_staticline1, 0, wxEXPAND|wxALL, 0 );

	wxBoxSizer* bSizerDismiss;
	bSizerDismiss = new wxBoxSizer( wxHORIZONTAL );

	m_staticRefID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRefID->Wrap( -1 );
	m_staticRefID->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Times New Roman") ) );

	bSizerDismiss->Add( m_staticRefID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDismiss->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSave1 = new wxButton( this, wxID_OK, _("&Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonSave1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_buttonCancel1 = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDismiss->Add( m_buttonCancel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer49->Add( bSizerDismiss, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer49 );
	this->Layout();
	bSizer49->Fit( this );

	// Connect Events
	m_notebookTop->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnStatementViewChanged ), NULL, this );
	this->Connect( m_toolCut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolCut ) );
	this->Connect( m_toolCopy->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolCopy ) );
	this->Connect( m_toolPaste->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolPaste ) );
	this->Connect( m_toolUndo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolUndo ) );
	this->Connect( m_toolRedo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolRedo ) );
	m_notebookBottom->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnEntityViewChanged ), NULL, this );
	m_buttonCitationAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationAddButton ), NULL, this );
	m_buttonCitationEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationEditButton ), NULL, this );
	m_buttonCitationDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationDeleteButton ), NULL, this );
	m_buttonCitationUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationUpButton ), NULL, this );
	m_buttonCitationDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationDownButton ), NULL, this );
	m_buttonMediaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaAddButton ), NULL, this );
	m_buttonMediaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaEditButton ), NULL, this );
	m_buttonMediaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaDeleteButton ), NULL, this );
	m_buttonMediaUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaUpButton ), NULL, this );
	m_buttonMediaDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaDownButton ), NULL, this );
	m_buttonMediaView->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaViewButton ), NULL, this );
	m_buttonPersonaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaAddButton ), NULL, this );
	m_menuAddPersona->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnAddMalePersona ), this, m_menuAddMale->GetId());
	m_menuAddPersona->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnAddFemalePersona ), this, m_menuAddFemale->GetId());
	m_menuAddPersona->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnAddUnknownPersona ), this, m_menuAddUnknownPersona->GetId());
	m_buttonPersonaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaEditButton ), NULL, this );
	m_buttonPersonaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaDeleteButton ), NULL, this );
	m_buttonEventaAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEventaAddButton ), NULL, this );
	m_menuAddEventa->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnNewEventa ), this, m_menuAddGenEventa->GetId());
	m_menuAddEventa->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnNewPersonalEventa ), this, m_menuAddPerEventa->GetId());
	m_buttonEventaEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEventaEditButton ), NULL, this );
	m_buttonEventaDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEventaDeleteButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnAddEntityButton ), NULL, this );
	m_menuAddEntity->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnNewDate ), this, m_menuAddDate->GetId());
	m_menuAddEntity->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnNewDateAge ), this, m_menuAddDateAge->GetId());
	m_menuAddEntity->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnNewPlace ), this, m_menuAddPlace->GetId());
	m_menuAddEntity->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( fbRgEditReference::OnNewName ), this, m_menuAddName->GetId());
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEditEntityButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDeleteEntityButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnUpEntityButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDownEntityButton ), NULL, this );
}

fbRgEditReference::~fbRgEditReference()
{
	// Disconnect Events
	m_notebookTop->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnStatementViewChanged ), NULL, this );
	this->Disconnect( m_toolCut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolCut ) );
	this->Disconnect( m_toolCopy->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolCopy ) );
	this->Disconnect( m_toolPaste->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolPaste ) );
	this->Disconnect( m_toolUndo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolUndo ) );
	this->Disconnect( m_toolRedo->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbRgEditReference::OnToolRedo ) );
	m_notebookBottom->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( fbRgEditReference::OnEntityViewChanged ), NULL, this );
	m_buttonCitationAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationAddButton ), NULL, this );
	m_buttonCitationEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationEditButton ), NULL, this );
	m_buttonCitationDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationDeleteButton ), NULL, this );
	m_buttonCitationUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationUpButton ), NULL, this );
	m_buttonCitationDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnCitationDownButton ), NULL, this );
	m_buttonMediaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaAddButton ), NULL, this );
	m_buttonMediaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaEditButton ), NULL, this );
	m_buttonMediaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaDeleteButton ), NULL, this );
	m_buttonMediaUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaUpButton ), NULL, this );
	m_buttonMediaDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaDownButton ), NULL, this );
	m_buttonMediaView->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnMediaViewButton ), NULL, this );
	m_buttonPersonaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaAddButton ), NULL, this );
	m_buttonPersonaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaEditButton ), NULL, this );
	m_buttonPersonaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnPersonaDeleteButton ), NULL, this );
	m_buttonEventaAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEventaAddButton ), NULL, this );
	m_buttonEventaEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEventaEditButton ), NULL, this );
	m_buttonEventaDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEventaDeleteButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnAddEntityButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnEditEntityButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDeleteEntityButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnUpEntityButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbRgEditReference::OnDownEntityButton ), NULL, this );

	delete m_menuAddPersona;
	delete m_menuAddEventa;
	delete m_menuAddEntity;
}
