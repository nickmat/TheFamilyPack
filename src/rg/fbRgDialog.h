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
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/radiobox.h>
#include <wx/listctrl.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////

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
		wxChoice* m_choiceType;
		wxButton* m_buttonBase;
		wxTextCtrl* m_textCtrlBase;
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
		
		fbRgEditRelativeDate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Relative Date"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditRelativeDate();
	
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
		
		fbRgEditEventType( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Event Type"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,300 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditEventType();
	
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
		
	
	public:
		
		fbRgSelectIndEvent( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgSelectIndEvent();
	
};

#endif //__FBRGDIALOG_H__
