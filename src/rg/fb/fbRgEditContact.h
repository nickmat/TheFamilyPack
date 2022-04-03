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
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

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

