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
#include <wx/statline.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditAssociate
///////////////////////////////////////////////////////////////////////////////
class fbRgEditAssociate : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlName;
		wxTextCtrl* m_textCtrlComment;
		wxStaticText* m_staticAssID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgEditAssociate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Associate Database"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~fbRgEditAssociate();

};

