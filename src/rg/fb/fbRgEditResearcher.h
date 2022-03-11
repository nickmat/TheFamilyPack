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
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditResearcher
///////////////////////////////////////////////////////////////////////////////
class fbRgEditResearcher : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlName;
		wxTextCtrl* m_textCtrlComment;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlUser;
		wxCheckBox* m_checkBoxCurrentUser;
		wxButton* m_buttonIndividual;
		wxTextCtrl* m_textCtrlIndivitual;
		wxListCtrl* m_listContacts;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxStaticText* m_staticResID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnCheckCurrentUsr( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnContactDeselected( wxListEvent& event ) { event.Skip(); }
		virtual void OnContactSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnButtonAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDelete( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditResearcher( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Researcher"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgEditResearcher();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgInvalidUid
///////////////////////////////////////////////////////////////////////////////
class fbRgInvalidUid : public wxDialog
{
	private:

	protected:
		wxButton* m_buttonRestore;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnButtonRestore( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgInvalidUid( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Invalid UID"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgInvalidUid();

};

