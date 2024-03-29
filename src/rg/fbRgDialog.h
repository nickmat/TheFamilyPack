///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class rgRecEventTableCtrl;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/radiobox.h>
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
		wxStaticText* m_staticText13;
		wxSpinCtrl* m_spinPrivacy;
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

		// Virtual event handlers, override them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }


	public:

		fbRgCreateIndividual( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create Individual"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~fbRgCreateIndividual();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditEvent
///////////////////////////////////////////////////////////////////////////////
class fbRgEditEvent : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlTitle;
		wxNotebook* m_notebook6;
		wxPanel* m_panel1;
		wxStaticText* m_staticType;
		wxButton* m_buttonDate1;
		wxTextCtrl* m_textCtrlDate1;
		wxButton* m_buttonDate2;
		wxTextCtrl* m_textCtrlDate2;
		wxButton* m_buttonPlace;
		wxTextCtrl* m_textCtrlPlace;
		wxTextCtrl* m_textCtrlUserRef;
		wxPanel* m_panel23;
		wxTextCtrl* m_textCtrlNote;
		wxPanel* m_panel2;
		wxListCtrl* m_listIndividual;
		wxButton* m_buttonAddInd;
		wxButton* m_buttonEditInd;
		wxButton* m_buttonDelInd;
		wxPanel* m_panel24;
		wxListCtrl* m_listRecord;
		wxButton* m_buttonAddRec;
		wxButton* m_buttonEditRec;
		wxButton* m_buttonDelRec;
		wxStaticLine* m_staticline12;
		wxStaticText* m_staticEventID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnDate1Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDate2Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlaceButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddInd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditInd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteInd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddRecord( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditRecord( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteRecord( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditEvent();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditFamily
///////////////////////////////////////////////////////////////////////////////
class fbRgEditFamily : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticNames;
		wxNotebook* m_notebook;
		wxPanel* m_panel17;
		wxButton* m_buttonHusb;
		wxStaticText* m_staticHusbName;
		wxButton* m_buttonWife;
		wxStaticText* m_staticWifeName;
		wxPanel* m_panel211;
		wxListCtrl* m_listChildren;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDel;
		wxButton* m_buttonUp;
		wxButton* m_buttonDn;
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxRadioBox* m_radioBox3;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticFamID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;

		// Virtual event handlers, override them in your derived class
		virtual void OnPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnHusbButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWifeButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnChildSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnChildAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChildDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnEventSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventOrderBy( wxCommandEvent& event ) { event.Skip(); }


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
		wxSpinCtrl* m_spinPrivacy;
		wxStaticText* m_staticText13;
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

		// Virtual event handlers, override them in your derived class
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
		wxButton* m_buttonRole;
		wxChoice* m_choiceRole;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlNote;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticRoleID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnRoleButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgPerIndEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Link Individual to Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,250 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgPerIndEvent();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgSelectEvent
///////////////////////////////////////////////////////////////////////////////
class fbRgSelectEvent : public wxDialog
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
		wxStaticText* m_staticText115;
		wxTextCtrl* m_textCtrlIndID;
		rgRecEventTableCtrl* m_listEvent;
		wxStaticLine* m_staticline8;
		wxButton* m_buttonCreate;
		wxStaticText* m_staticEventCount;
		wxButton* m_buttonSelect;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
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
		virtual void OnIndIdText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListEventItemDeselected( wxListEvent& event ) { event.Skip(); }
		virtual void OnListEventItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnCreateButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgSelectEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,550 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgSelectEvent();

};

