///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBRGDIALOG_H__
#define __FBRGDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class rgRecEventTableCtrl;
class rgStrTableCtrl;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/radiobox.h>
#include <wx/toolbar.h>
#include <wx/webview.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgCreateIndividual
///////////////////////////////////////////////////////////////////////////////
class fbRgCreateIndividual : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText11;
		wxStaticText* m_staticName;
		wxStaticText* m_staticText12;
		wxChoice* m_choiceSex;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textGiven;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textSurname;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_textNote;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticIndID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgCreateIndividual( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create Individual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~fbRgCreateIndividual();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgCreateName
///////////////////////////////////////////////////////////////////////////////
class fbRgCreateName : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlGiven;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlSurname;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticNameID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbRgCreateName( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create Name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgCreateName();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditContact
///////////////////////////////////////////////////////////////////////////////
class fbRgEditContact : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText3;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlValue;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticContactID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
	
	public:
		
		fbRgEditContact( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Contact"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditContact();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditDate
///////////////////////////////////////////////////////////////////////////////
class fbRgEditDate : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticOutput;
		wxStaticText* m_staticText2;
		wxChoice* m_choiceDisplay;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlDate;
		wxStaticText* m_staticText5;
		wxChoice* m_choiceInput;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticDateID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditDate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Date"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditDate();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditEvent
///////////////////////////////////////////////////////////////////////////////
class fbRgEditEvent : public wxDialog 
{
	private:
	
	protected:
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlTitle;
		wxButton* m_buttonDate1;
		wxTextCtrl* m_textCtrlDate1;
		wxButton* m_buttonDate2;
		wxTextCtrl* m_textCtrlDate2;
		wxButton* m_buttonPlace;
		wxTextCtrl* m_textCtrlPlace;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textCtrlNote;
		wxPanel* m_panel2;
		wxListCtrl* m_listPersona;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxStaticLine* m_staticline12;
		wxStaticText* m_staticEventID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnDate1Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDate2Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlaceButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditEvent();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 0 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditEvent::m_splitter1OnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditEventType
///////////////////////////////////////////////////////////////////////////////
class fbRgEditEventType : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText4;
		wxChoice* m_choiceGroup;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlValue;
		wxListCtrl* m_listRole;
		wxButton* m_buttonRoleAdd;
		wxButton* m_buttonRoleEdit;
		wxButton* m_buttonRoleDelete;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticTypeID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonRoleAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonRoleEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonRoleDelete( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditEventType( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event Type"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditEventType();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditFamily
///////////////////////////////////////////////////////////////////////////////
class fbRgEditFamily : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticNames;
		wxNotebook* m_notebook5;
		wxPanel* m_panel17;
		wxButton* m_buttonHusb;
		wxStaticText* m_staticHusbName;
		wxButton* m_buttonWife;
		wxStaticText* m_staticWifeName;
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
		wxStaticText* m_staticFamID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnHusbButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWifeButton( wxCommandEvent& event ) { event.Skip(); }
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
		
		fbRgEditFamily( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Family"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditFamily();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditIndividual
///////////////////////////////////////////////////////////////////////////////
class fbRgEditIndividual : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticPerName;
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
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxRadioBox* m_radioBox3;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticIndID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventOrderBy( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditIndividual( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Individual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditIndividual();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditName
///////////////////////////////////////////////////////////////////////////////
class fbRgEditName : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticName;
		wxStaticText* m_staticText2;
		wxChoice* m_choiceType;
		wxListCtrl* m_listNamePart;
		wxButton* m_buttonPartAdd;
		wxButton* m_buttonPartEdit;
		wxButton* m_buttonPartDel;
		wxButton* m_buttonPartUp;
		wxButton* m_buttonPartDown;
		wxStaticLine* m_staticline12;
		wxStaticText* m_staticNameID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPartAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditName( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditName();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditNamePart
///////////////////////////////////////////////////////////////////////////////
class fbRgEditNamePart : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlValue;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticNamePartID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbRgEditNamePart( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name Part"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditNamePart();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditPersona
///////////////////////////////////////////////////////////////////////////////
class fbRgEditPersona : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticPerName;
		wxNotebook* m_notebook;
		wxPanel* m_panel1;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlNote;
		wxStaticText* m_staticText11;
		wxChoice* m_choiceSex;
		wxButton* m_buttonIndLink;
		wxStaticText* m_staticText13;
		wxStaticText* m_staticIndId;
		wxPanel* m_panel2;
		wxListCtrl* m_listName;
		wxButton* m_buttonNameAdd;
		wxButton* m_buttonNameEdit;
		wxButton* m_buttonNameDel;
		wxButton* m_buttonNameUp;
		wxButton* m_buttonNameDn;
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxRadioBox* m_radioBox3;
		wxPanel* m_panel4;
		wxListCtrl* m_listRel;
		wxButton* m_buttonRelAdd;
		wxButton* m_buttonRelEdit;
		wxButton* m_buttonRelDel;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticPerID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnIndLinkButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOrderBy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRelDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditPersona( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Persona"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditPersona();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditPlace
///////////////////////////////////////////////////////////////////////////////
class fbRgEditPlace : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrlAddr;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticPlaceID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbRgEditPlace( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Place"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditPlace();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditReference
///////////////////////////////////////////////////////////////////////////////
class fbRgEditReference : public wxDialog 
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
		
		wxStaticText* m_staticText401;
		wxTextCtrl* m_textCtrlTitle;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel7;
		wxNotebook* m_notebookTop;
		wxPanel* m_panelSource;
		wxToolBar* m_toolBar1;
		wxTextCtrl* m_textCtrlStatement;
		wxPanel* m_panelView;
		wxWebView* m_webview;
		wxPanel* m_panel11;
		wxNotebook* m_notebookBottom;
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
		wxStaticText* m_staticRefID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnStatementViewChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnTool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEntityViewChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnPersonaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDownEntityButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditReference( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Reference"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditReference();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 265 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditReference::m_splitter1OnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditRelationship
///////////////////////////////////////////////////////////////////////////////
class fbRgEditRelationship : public wxDialog 
{
	private:
	
	protected:
		wxButton* m_buttonPerson1;
		wxTextCtrl* m_textCtrlPersona1;
		wxStaticText* m_staticText75;
		wxTextCtrl* m_textCtrlDescrip;
		wxButton* m_buttonPersona2;
		wxTextCtrl* m_textCtrlPersona2;
		wxStaticLine* m_staticline18;
		wxStaticText* m_staticRsNumber;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPersona1Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersona2Button( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditRelationship( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Relationship"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditRelationship();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditRelativeDate
///////////////////////////////////////////////////////////////////////////////
class fbRgEditRelativeDate : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticOutput;
		wxStaticText* m_staticText2;
		wxChoice* m_choiceDisplay;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceCalc;
		wxButton* m_buttonBase;
		wxTextCtrl* m_textCtrlBase;
		wxStaticText* m_staticText3a;
		wxChoice* m_choicePrecision;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlAge;
		wxStaticText* m_staticText5;
		wxChoice* m_choiceInput;
		wxRadioBox* m_radioUnits;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticDateID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnBaseButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditRelativeDate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Relative Date"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditRelativeDate();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditResearcher
///////////////////////////////////////////////////////////////////////////////
class fbRgEditResearcher : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText64;
		wxTextCtrl* m_textCtrlName;
		wxStaticText* m_staticText65;
		wxTextCtrl* m_textCtrlComment;
		wxButton* m_buttonInd;
		wxStaticText* m_staticIndName;
		wxStaticText* m_staticIndID;
		wxListCtrl* m_listContacts;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxStaticLine* m_staticline14;
		wxStaticText* m_staticResID;
		wxCheckBox* m_checkBoxUser;
		wxStaticText* m_staticUserID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonInd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDelete( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditResearcher( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Researcher"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~fbRgEditResearcher();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditRole
///////////////////////////////////////////////////////////////////////////////
class fbRgEditRole : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticEventType;
		wxStaticText* m_staticEventTypeID;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticTypeGroup;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlValue;
		wxStaticText* m_staticText4;
		wxChoice* m_choicePrime;
		wxCheckBox* m_checkOfficial;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticRoleID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChoicePrime( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditRole( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Role"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditRole();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditSystem
///////////////////////////////////////////////////////////////////////////////
class fbRgEditSystem : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText;
		wxChoice* m_choiceUser;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
	
	public:
		
		fbRgEditSystem( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("System Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditSystem();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditUserSettings
///////////////////////////////////////////////////////////////////////////////
class fbRgEditUserSettings : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticUserName;
		wxStaticText* m_staticText;
		wxTextCtrl* m_textCtrlHome;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticUserID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
	
	public:
		
		fbRgEditUserSettings( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("User Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditUserSettings();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgPerIndEvent
///////////////////////////////////////////////////////////////////////////////
class fbRgPerIndEvent : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticPerInd;
		wxStaticText* m_staticName;
		wxStaticText* m_staticNameID;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticEvent;
		wxStaticText* m_staticEventID;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceRole;
		wxButton* m_buttonAdd;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlNote;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticRoleID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAddRoleButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgPerIndEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Link Individual to Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,231 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgPerIndEvent();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgSelect
///////////////////////////////////////////////////////////////////////////////
class fbRgSelect : public wxDialog 
{
	private:
	
	protected:
		rgStrTableCtrl* m_listCtrl;
		wxStaticLine* m_staticline;
		wxButton* m_buttonCreate;
		wxButton* m_buttonFilter;
		wxButton* m_buttonUnknown;
		wxButton* m_buttonSelect;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnCreateButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFilterButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUnknownButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgSelect( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgSelect();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgSelectIndEvent
///////////////////////////////////////////////////////////////////////////////
class fbRgSelectIndEvent : public wxDialog 
{
	private:
	
	protected:
		wxCheckListBox* m_checkListGrp;
		wxButton* m_buttonSelectGrp;
		wxButton* m_buttonClearGrp;
		wxStaticText* m_staticText37;
		wxTextCtrl* m_textCtrlBegDatePt;
		wxStaticText* m_staticText38;
		wxTextCtrl* m_textCtrlEndDatePt;
		wxCheckListBox* m_checkListType;
		wxButton* m_buttonSelectType;
		wxButton* m_buttonClearType;
		rgRecEventTableCtrl* m_listEvent;
		wxStaticLine* m_staticline8;
		wxButton* m_buttonCreate;
		wxStaticText* m_staticEventCount;
		wxButton* m_buttonSelect;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnGroupCheckSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGroupCheckToggled( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonGroupSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonGroupClearAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBegDateText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEndDateText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeCheckSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeCheckToggled( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonTypeSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonTypeClearAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListEventItemDeselected( wxListEvent& event ) { event.Skip(); }
		virtual void OnListEventItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnCreateButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgSelectIndEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgSelectIndEvent();
	
};

#endif //__FBRGDIALOG_H__
