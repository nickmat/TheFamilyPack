///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBDLG_H__
#define __FBDLG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
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

#endif //__FBDLG_H__
