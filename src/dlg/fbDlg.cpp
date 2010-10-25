///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
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


#include "tfpListCtrlInd.h"

#include "fbDlg.h"

#include "../img/ed/copy.xpm"
#include "../img/ed/cut.xpm"
#include "../img/ed/paste.xpm"
#include "../img/ed/redo.xpm"
#include "../img/ed/undo.xpm"

///////////////////////////////////////////////////////////////////////////

fbDlgEditFamily::fbDlgEditFamily( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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

fbDlgEditFamily::~fbDlgEditFamily()
{
}

fbDlgEditIndividual::fbDlgEditIndividual( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Individual ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer14->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticIndID = new wxStaticText( this, tfpID_EDIND_IND_ID, _("I 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndID->Wrap( -1 );
	m_staticIndID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer14->Add( m_staticIndID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer20->Add( bSizer14, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 3, 4, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableRow( 0 );
	fgSizer2->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText40 = new wxStaticText( m_panel1, wxID_ANY, _("Given Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	fgSizer2->Add( m_staticText40, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textGiven = new wxTextCtrl( m_panel1, tfpID_EDIND_GIVEN, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer2->Add( m_textGiven, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText41 = new wxStaticText( m_panel1, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	fgSizer2->Add( m_staticText41, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( m_panel1, tfpID_EDIND_SEX, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	m_choiceSex->SetMinSize( wxSize( 70,-1 ) );
	
	fgSizer2->Add( m_choiceSex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText42 = new wxStaticText( m_panel1, wxID_ANY, _("Surname:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	fgSizer2->Add( m_staticText42, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textSurname = new wxTextCtrl( m_panel1, tfpID_EDIND_SURNAME, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer2->Add( m_textSurname, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText43 = new wxStaticText( m_panel1, wxID_ANY, _("Occupation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	fgSizer2->Add( m_staticText43, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxRIGHT, 5 );
	
	m_textOccAttr = new wxTextCtrl( m_panel1, tfpID_EDIND_OCC, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer2->Add( m_textOccAttr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel1->SetSizer( fgSizer2 );
	m_panel1->Layout();
	fgSizer2->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, _("Attributes"), true );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listCtrl = new wxListCtrl( m_panel3, tfpID_EDIND_EVENTS, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listCtrl->SetMinSize( wxSize( -1,100 ) );
	
	bSizer26->Add( m_listCtrl, 1, wxALL, 5 );
	
	m_panel3->SetSizer( bSizer26 );
	m_panel3->Layout();
	bSizer26->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, _("Events"), false );
	
	bSizer21->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	bSizer20->Add( bSizer21, 1, wxEXPAND, 5 );
	
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
}

fbDlgEditIndividual::~fbDlgEditIndividual()
{
}

fbDlgEditIndEvent::fbDlgEditIndEvent( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, _("Event type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer3->Add( m_staticText17, 0, wxALIGN_RIGHT|wxALL|wxALIGN_BOTTOM, 5 );
	
	m_staticTextType = new wxStaticText( this, tfpID_EDINDEV_TYPE, _("Birth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextType->Wrap( -1 );
	m_staticTextType->SetFont( wxFont( 11, 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticTextType, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer3->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlDate = new wxTextCtrl( this, tfpID_EDINDEV_DATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_textCtrlDate, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonDate = new wxButton( this, tfpID_EDINDEV_DATE_BUT, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer3->Add( m_buttonDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer3->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlAddr = new wxTextCtrl( this, tfpID_EDINDEV_ADDR, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer3->Add( m_textCtrlAddr, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonAddr = new wxButton( this, tfpID_EDINDEV_ADDR_BUT, _("..."), wxDefaultPosition, wxSize( 25,-1 ), 0 );
	fgSizer3->Add( m_buttonAddr, 0, wxALL, 5 );
	
	bSizer11->Add( fgSizer3, 0, wxEXPAND, 5 );
	
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
	m_buttonDate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDateButton ), NULL, this );
	m_buttonAddr->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnAddrButton ), NULL, this );
}

fbDlgEditIndEvent::~fbDlgEditIndEvent()
{
	// Disconnect Events
	m_buttonDate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnDateButton ), NULL, this );
	m_buttonAddr->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditIndEvent::OnAddrButton ), NULL, this );
	
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

fbDlgEditAttribute::fbDlgEditAttribute( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextId = new wxStaticText( this, wxID_ANY, _("A 0:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextId->Wrap( -1 );
	m_staticTextId->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticTextId, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticTextPersona = new wxStaticText( this, wxID_ANY, _("P 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPersona->Wrap( -1 );
	m_staticTextPersona->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticTextPersona, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxArrayString m_choiceTypeChoices;
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 2 );
	fgSizer3->Add( m_choiceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_textCtrlValue, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
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
}

fbDlgEditAttribute::~fbDlgEditAttribute()
{
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

fbDlgEditPersona::fbDlgEditPersona( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer14->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticPerName = new wxStaticText( this, tfpID_EDIND_IND_ID, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticPerName->Wrap( -1 );
	m_staticPerName->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer14->Add( m_staticPerName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText411 = new wxStaticText( this, wxID_ANY, _("Sex:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	bSizer14->Add( m_staticText411, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceSexChoices[] = { _("Unstated"), _("Male"), _("Female"), _("Unknown") };
	int m_choiceSexNChoices = sizeof( m_choiceSexChoices ) / sizeof( wxString );
	m_choiceSex = new wxChoice( this, tfpID_EDPER_SEX, wxDefaultPosition, wxDefaultSize, m_choiceSexNChoices, m_choiceSexChoices, 0 );
	m_choiceSex->SetSelection( 0 );
	m_choiceSex->SetMinSize( wxSize( 70,-1 ) );
	
	bSizer14->Add( m_choiceSex, 0, wxALL, 5 );
	
	bSizer20->Add( bSizer14, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer21->Add( m_staticText11, 0, wxALL, 5 );
	
	m_textCtrlNote = new wxTextCtrl( this, tfpID_EDPER_NOTE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textCtrlNote->SetMinSize( wxSize( 350,50 ) );
	
	bSizer21->Add( m_textCtrlNote, 0, wxALL, 5 );
	
	bSizer20->Add( bSizer21, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonIndLink = new wxButton( this, tfpID_EDPER_IND_LINK, _("Link"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonIndLink->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer31->Add( m_buttonIndLink, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonIndCreate = new wxButton( this, tfpID_EDPER_IND_CREATE, _("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonIndCreate->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer31->Add( m_buttonIndCreate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Individual:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer31->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticIndId = new wxStaticText( this, tfpID_EDIND_IND_ID, _("I 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticIndId->Wrap( -1 );
	m_staticIndId->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer31->Add( m_staticIndId, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer30->Add( bSizer31, 1, wxEXPAND, 5 );
	
	bSizer20->Add( bSizer30, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Attributes:") ), wxHORIZONTAL );
	
	m_listAttr = new wxListCtrl( this, tfpID_EDPER_ATTR_LIST, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listAttr->SetMinSize( wxSize( -1,125 ) );
	
	sbSizer1->Add( m_listAttr, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( this, tfpID_EDPER_ATTR_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( this, tfpID_EDPER_ATTR_EDIT, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonDel = new wxButton( this, tfpID_EDPER_ATTR_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( this, tfpID_EDPER_ATTR_UP, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonUp, 0, wxALL, 5 );
	
	m_buttonDn = new wxButton( this, tfpID_EDPER_ATTR_DOWN, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
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
	
	// Connect Events
	m_buttonIndLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndLinkButton ), NULL, this );
	m_buttonIndCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndCreateButton ), NULL, this );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnDeleteButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnUpButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnDownButton ), NULL, this );
}

fbDlgEditPersona::~fbDlgEditPersona()
{
	// Disconnect Events
	m_buttonIndLink->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndLinkButton ), NULL, this );
	m_buttonIndCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnIndCreateButton ), NULL, this );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnDeleteButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnUpButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditPersona::OnDownButton ), NULL, this );
	
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
	m_textCtrlTitle->SetMinSize( wxSize( 350,-1 ) );
	
	fgSizer4->Add( m_textCtrlTitle, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonDateBeg = new wxButton( this, wxID_ANY, _("Date Start:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonDateBeg, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDateBeg = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer4->Add( m_textCtrlDateBeg, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDateEnd = new wxButton( this, wxID_ANY, _("Date End:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonDateEnd, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDateEnd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer4->Add( m_textCtrlDateEnd, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonPlace = new wxButton( this, wxID_ANY, _("Place:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonPlace, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlPlace = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
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
	m_textCtrlPersona->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer4->Add( m_textCtrlPersona, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_buttonRole = new wxButton( this, wxID_ANY, _("Role:"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_buttonRole, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRole = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlRole->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	fgSizer4->Add( m_textCtrlRole, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Note:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer4->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
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

fbDlgEditReference::fbDlgEditReference( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Reference ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer14->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticRefID = new wxStaticText( this, wxID_ANY, _("R0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticRefID->Wrap( -1 );
	m_staticRefID->SetFont( wxFont( 11, 72, 90, 92, false, wxEmptyString ) );
	
	bSizer14->Add( m_staticRefID, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer20->Add( bSizer14, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText401 = new wxStaticText( this, wxID_ANY, _("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	bSizer41->Add( m_staticText401, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( m_textCtrlTitle, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer20->Add( bSizer41, 0, wxEXPAND, 5 );
	
	m_toolBar1 = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_toolBar1->AddTool( tfpID_EDREF_OnCut, wxEmptyString, wxBitmap( cut_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Cut"), wxEmptyString ); 
	m_toolBar1->AddTool( tfpID_EDREF_OnCopy, _("tool"), wxBitmap( copy_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Copy"), wxEmptyString ); 
	m_toolBar1->AddTool( tfpID_EDREF_OnPaste, _("tool"), wxBitmap( paste_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Paste"), wxEmptyString ); 
	m_toolBar1->AddSeparator(); 
	m_toolBar1->AddTool( tfpID_EDREF_OnUndo, _("tool"), wxBitmap( undo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Undo"), wxEmptyString ); 
	m_toolBar1->AddTool( tfpID_EDREF_OnRedo, _("tool"), wxBitmap( redo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Redo"), wxEmptyString ); 
	m_toolBar1->Realize();
	
	bSizer20->Add( m_toolBar1, 0, wxEXPAND, 5 );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditReference::m_splitter1OnIdle ), NULL, this );
	
	m_panel7 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrlStatement = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_DONTWRAP|wxTE_MULTILINE );
	m_textCtrlStatement->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer39->Add( m_textCtrlStatement, 1, wxALL|wxEXPAND, 5 );
	
	m_panel7->SetSizer( bSizer39 );
	m_panel7->Layout();
	bSizer39->Fit( m_panel7 );
	m_panel8 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel8, wxID_ANY, _("Entities:") ), wxHORIZONTAL );
	
	m_listEntities = new wxListCtrl( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_listEntities->SetMinSize( wxSize( -1,125 ) );
	
	sbSizer1->Add( m_listEntities, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAdd = new wxButton( m_panel8, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonEdit = new wxButton( m_panel8, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_buttonDel = new wxButton( m_panel8, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonDel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUp = new wxButton( m_panel8, wxID_ANY, _("Up"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonUp, 0, wxALL, 5 );
	
	m_buttonDn = new wxButton( m_panel8, wxID_ANY, _("Down"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	bSizer12->Add( m_buttonDn, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer12, 1, wxEXPAND, 5 );
	
	sbSizer1->Add( bSizer11, 0, wxEXPAND, 5 );
	
	bSizer40->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_panel8->SetSizer( bSizer40 );
	m_panel8->Layout();
	bSizer40->Fit( m_panel8 );
	m_splitter1->SplitHorizontally( m_panel7, m_panel8, 186 );
	bSizer20->Add( m_splitter1, 1, wxEXPAND, 5 );
	
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
	this->Connect( tfpID_EDREF_OnCut, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnCopy, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnPaste, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnUndo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Connect( tfpID_EDREF_OnRedo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnAddButton ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnEditButton ), NULL, this );
	m_buttonDel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDeleteButton ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnUpButton ), NULL, this );
	m_buttonDn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDownButton ), NULL, this );
}

fbDlgEditReference::~fbDlgEditReference()
{
	// Disconnect Events
	this->Disconnect( tfpID_EDREF_OnCut, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnCopy, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnPaste, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnUndo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	this->Disconnect( tfpID_EDREF_OnRedo, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnTool ) );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnAddButton ), NULL, this );
	m_buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnEditButton ), NULL, this );
	m_buttonDel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDeleteButton ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnUpButton ), NULL, this );
	m_buttonDn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fbDlgEditReference::OnDownButton ), NULL, this );
	
}
