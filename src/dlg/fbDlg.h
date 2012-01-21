///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBDLG_H__
#define __FBDLG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class dlgStrTableCtrl;
class tfpListCtrlIndividuals;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditFamily
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditFamily : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticNames;
		wxStaticText* m_staticFamID;
		wxNotebook* m_notebook5;
		wxPanel* m_panel17;
		wxButton* m_buttonHusb;
		wxStaticText* m_staticHusbName;
		wxButton* m_buttonWife;
		wxStaticText* m_staticWifeName;
		wxButton* m_buttonMarr;
		wxStaticText* m_staticMarrEvent;
		wxPanel* m_panel211;
		wxListBox* m_listChild;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDel;
		wxButton* m_buttonUp;
		wxButton* m_button1Dn;
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnHusbButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWifeButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMarriageButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditFamily( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Family"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditFamily();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditFamily1
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditFamily1 : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			tfpID_EDFAM_FAM_ID = 1000,
			tfpID_EDFAM_HUSB_BUT,
			tfpID_EDFAM_HUSB_NAM,
			tfpID_EDFAM_WIFE_BUT,
			tfpID_EDFAM_WIFE_NAM,
			tfpID_EDFAM_MARR_BUT,
			tfpID_EDFAM_MARR_EV,
			tfpID_EDFAM_CHILD_LIST,
			tfpID_EDFAM_ADD,
			tfpID_EDFAM_EDIT,
			tfpID_EDFAM_DELETE,
			tfpID_EDFAM_UP,
			tfpID_EDFAM_DOWN
		};
		
		wxStaticText* m_staticText1;
		wxStaticText* m_staticFamID;
		wxButton* m_buttonHusbID;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticHusbName;
		wxButton* m_buttonWife;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticWifeName;
		wxButton* m_buttonMarr;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticMarrEvent;
		wxListBox* m_listChild;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDel;
		wxButton* m_buttonUp;
		wxButton* m_button1Dn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbDlgEditFamily1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Family"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 414,354 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditFamily1();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgCreateIndividual
///////////////////////////////////////////////////////////////////////////////
class fbDlgCreateIndividual : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText11;
		wxStaticText* m_staticIndID;
		wxStaticText* m_staticText12;
		wxChoice* m_choiceSex;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textGiven;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textSurname;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_textNote;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbDlgCreateIndividual( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create Individual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,221 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~fbDlgCreateIndividual();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditIndEvent
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditIndEvent : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText17;
		wxStaticText* m_staticType;
		wxStaticText* m_staticText171;
		wxTextCtrl* m_textCtrlTitle;
		wxButton* m_buttonDate1;
		wxTextCtrl* m_textCtrlDate1;
		wxButton* m_buttonDate2;
		wxTextCtrl* m_textCtrlDate2;
		wxButton* m_buttonAddr;
		wxTextCtrl* m_textCtrlAddr;
		wxStaticText* m_staticText1711;
		wxTextCtrl* m_textCtrlNote;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnDate1Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDate2Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddrButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditIndEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 550,320 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~fbDlgEditIndEvent();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditDate
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditDate : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextId;
		wxStaticText* m_staticTextOutput;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_textCtrlDate;
		wxStaticText* m_staticText16;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText40;
		wxChoice* m_choiceOriginal;
		wxStaticText* m_staticText41;
		wxChoice* m_choiceDisplay;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void SetStaticDate( wxIdleEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditDate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Date"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,235 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditDate();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditDateFromAge
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditDateFromAge : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextId;
		wxStaticText* m_staticTextOutput;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrlAge;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlBaseDate;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText4;
		wxChoice* m_choiceDisplay;
		wxRadioBox* m_radioBoxUnits;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void SetStaticDate( wxIdleEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditDateFromAge( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Date from Age"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 264,275 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~fbDlgEditDateFromAge();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditAttribute
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditAttribute : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextId;
		wxStaticText* m_staticTextPersona;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlValue;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbDlgEditAttribute( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Attribute"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,160 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditAttribute();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditNamePart
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditNamePart : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextId;
		wxStaticText* m_staticTextPersona;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlValue;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbDlgEditNamePart( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name Part"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,160 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditNamePart();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditPlace
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditPlace : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			tfpID_EDPLACE_ADDR = 1000
		};
		
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textCtrlAddr;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbDlgEditPlace( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Place"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,110 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditPlace();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditPersona
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditPersona : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticPerName;
		wxStaticText* m_staticPerID;
		wxNotebook* m_notebook;
		wxPanel* m_panel1;
		wxStaticText* m_staticText11;
		wxChoice* m_choiceSex;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlNote;
		wxButton* m_buttonIndLink;
		wxButton* m_buttonIndCreate;
		wxStaticText* m_staticText13;
		wxStaticText* m_staticIndId;
		wxPanel* m_panel2;
		wxListCtrl* m_listName;
		wxButton* m_buttonNameAdd;
		wxButton* m_buttonNameEdit;
		wxButton* m_buttonNameDel;
		wxButton* m_buttonNameUp;
		wxButton* m_buttonNameDn;
		wxPanel* m_panel3;
		wxListCtrl* m_listAttr;
		wxButton* m_buttonAttrAdd;
		wxButton* m_buttonAttrEdit;
		wxButton* m_buttonAttrDel;
		wxButton* m_buttonAttrUp;
		wxButton* m_buttonAttrDn;
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxPanel* m_panel4;
		wxListCtrl* m_listRel;
		wxButton* m_buttonRelAdd;
		wxButton* m_buttonRelEdit;
		wxButton* m_buttonRelDel;
		wxButton* m_buttonRelUp;
		wxButton* m_buttonRelDn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIndLinkButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndCreateButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditPersona( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Persona"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditPersona();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditIndPersona
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditIndPersona : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticPerName;
		wxStaticText* m_staticIndID;
		wxStaticText* m_staticPerID;
		wxNotebook* m_notebook;
		wxPanel* m_panel1;
		wxStaticText* m_staticTextEpitaph;
		wxStaticText* m_staticText11;
		wxChoice* m_choiceSex;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlNote;
		wxPanel* m_panel2;
		wxListCtrl* m_listName;
		wxButton* m_buttonNameAdd;
		wxButton* m_buttonNameEdit;
		wxButton* m_buttonNameDel;
		wxButton* m_buttonNameUp;
		wxButton* m_buttonNameDn;
		wxPanel* m_panel3;
		wxListCtrl* m_listAttr;
		wxButton* m_buttonAttrAdd;
		wxButton* m_buttonAttrEdit;
		wxButton* m_buttonAttrDel;
		wxButton* m_buttonAttrUp;
		wxButton* m_buttonAttrDn;
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxPanel* m_panel4;
		wxListCtrl* m_listRel;
		wxButton* m_buttonRelAdd;
		wxButton* m_buttonRelEdit;
		wxButton* m_buttonRelDel;
		wxButton* m_buttonRelUp;
		wxButton* m_buttonRelDn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttrDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditIndPersona( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Individual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditIndPersona();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditName
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditName : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticName;
		wxStaticText* m_staticNameID;
		wxStaticText* m_staticText1a;
		wxChoice* m_choiceStyle;
		wxStaticText* m_staticText65;
		wxButton* m_buttonPersona;
		wxListCtrl* m_listParts;
		wxButton* m_buttonPartAdd;
		wxButton* m_buttonPartEdit;
		wxButton* m_buttonPartDel;
		wxButton* m_buttonPartUp;
		wxButton* m_buttonPartDn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPersonaButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditName( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditName();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditEvent
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditEvent : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlTitle;
		wxButton* m_buttonDateBeg;
		wxTextCtrl* m_textCtrlDateBeg;
		wxButton* m_buttonDateEnd;
		wxTextCtrl* m_textCtrlDateEnd;
		wxButton* m_buttonPlace;
		wxTextCtrl* m_textCtrlPlace;
		wxListCtrl* m_listPersona;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDel;
		wxButton* m_buttonUp;
		wxButton* m_buttonDn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnDateBegButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDateEndButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlaceButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditEvent();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditRole
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditRole : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticTextEvent;
		wxButton* m_buttonPersona;
		wxTextCtrl* m_textCtrlPersona;
		wxButton* m_buttonRole;
		wxTextCtrl* m_textCtrlRole;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlNote;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPersonaButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRoleButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditRole( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Persona's Role"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,231 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditRole();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditRelationship
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditRelationship : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticRsNumber;
		wxButton* m_buttonPersona1;
		wxTextCtrl* m_textCtrlPersona1;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlDescrip;
		wxButton* m_buttonPersona2;
		wxTextCtrl* m_textCtrlPersona2;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPersona1Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersona2Button( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditRelationship( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Persona's Relationship"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 337,217 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditRelationship();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditReference
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditReference : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			tfpID_EDREF_OnCut = 1000,
			tfpID_EDREF_OnCopy,
			tfpID_EDREF_OnPaste,
			tfpID_EDREF_OnUndo,
			tfpID_EDREF_OnRedo
		};
		
		wxStaticText* m_staticText1;
		wxStaticText* m_staticRefID;
		wxStaticText* m_staticText401;
		wxTextCtrl* m_textCtrlTitle;
		wxToolBar* m_toolBar1;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel7;
		wxTextCtrl* m_textCtrlStatement;
		wxPanel* m_panel11;
		wxNotebook* m_notebook3;
		wxPanel* m_panelPersona;
		wxListCtrl* m_listPersona;
		wxButton* m_buttonPersonaAdd;
		wxButton* m_buttonPersonaEdit;
		wxButton* m_buttonPersonaDel;
		wxPanel* m_panelEntities;
		wxListCtrl* m_listEntities;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDel;
		wxButton* m_buttonUp;
		wxButton* m_buttonDn;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditReference( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Reference"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,500 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditReference();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 186 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbDlgEditReference::m_splitter1OnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgSelectIndividual
///////////////////////////////////////////////////////////////////////////////
class fbDlgSelectIndividual : public wxDialog 
{
	private:
	
	protected:
		tfpListCtrlIndividuals* m_listInd;
		wxStaticLine* m_staticline6;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnIndividualSelected( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgSelectIndividual( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Individual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 485,269 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgSelectIndividual();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgSelectEvent
///////////////////////////////////////////////////////////////////////////////
class fbDlgSelectEvent : public wxDialog 
{
	private:
	
	protected:
		dlgStrTableCtrl* m_listEvent;
		wxStaticLine* m_staticline;
		wxButton* m_buttonSelect;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgSelectEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 485,269 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgSelectEvent();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgSelect
///////////////////////////////////////////////////////////////////////////////
class fbDlgSelect : public wxDialog 
{
	private:
	
	protected:
		dlgStrTableCtrl* m_listCtrl;
		wxStaticLine* m_staticline;
		wxButton* m_buttonCreate;
		wxButton* m_buttonUnknown;
		wxButton* m_buttonSelect;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnCreateButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUnknownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgSelect( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 485,269 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgSelect();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgNote
///////////////////////////////////////////////////////////////////////////////
class fbDlgNote : public wxDialog 
{
	private:
	
	protected:
		wxHtmlWindow* m_htmlWin;
		wxStaticLine* m_staticline;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgNote( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Note"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 342,215 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgNote();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbDlgEditFamEvent
///////////////////////////////////////////////////////////////////////////////
class fbDlgEditFamEvent : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrlTitle;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlType;
		wxButton* m_buttonType;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlDate;
		wxButton* m_buttonDate;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlAddr;
		wxButton* m_buttonAddr;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrlNote;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTypeButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDateButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddrButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbDlgEditFamEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 322,284 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbDlgEditFamEvent();
	
};

#endif //__FBDLG_H__
