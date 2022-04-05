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
#include <wx/choice.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditContact
///////////////////////////////////////////////////////////////////////////////
class fbRgEditContact : public wxDialog
{
	private:

	protected:
		wxChoice* m_choiceType;
		wxButton* m_buttonAddType;
		wxMenu* m_menuAddEditType;
		wxTextCtrl* m_textCtrlValue;
		wxStaticText* m_staticContactID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnAddEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddType( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditType( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditContact( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Contact"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~fbRgEditContact();

		void m_buttonAddTypeOnContextMenu( wxMouseEvent &event )
		{
			m_buttonAddType->PopupMenu( m_menuAddEditType, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditContactType
///////////////////////////////////////////////////////////////////////////////
class fbRgEditContactType : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlName;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxStaticText* m_staticContactTypeID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgEditContactType( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Contact Type"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditContactType();

};

