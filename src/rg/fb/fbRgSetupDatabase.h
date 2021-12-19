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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgSetupDatabase
///////////////////////////////////////////////////////////////////////////////
class fbRgSetupDatabase : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlUserName;
		wxButton* m_buttonContacts;
		wxComboBox* m_comboBoxHomePage;
		wxStaticText* m_staticDbName;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnContactsButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgSetupDatabase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Database"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgSetupDatabase();

};

