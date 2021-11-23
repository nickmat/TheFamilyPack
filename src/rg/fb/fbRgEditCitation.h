///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
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
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditArchive
///////////////////////////////////////////////////////////////////////////////
class fbRgEditArchive : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlName;
		wxTextCtrl* m_textCtrlNote;
		wxListCtrl* m_listContacts;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxStaticText* m_staticArcID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;

		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDelete( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditArchive( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Archive"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~fbRgEditArchive();

};

