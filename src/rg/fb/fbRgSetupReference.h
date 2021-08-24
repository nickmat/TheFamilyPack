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
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgSetupReferenceDialog
///////////////////////////////////////////////////////////////////////////////
class fbRgSetupReferenceDialog : public wxDialog
{
	private:

	protected:
		wxListCtrl* m_listMedia;
		wxButton* m_buttonMediaAdd;
		wxButton* m_buttonMediaEdit;
		wxButton* m_buttonMediaDel;
		wxButton* m_buttonMediaView;
		wxTextCtrl* m_textCtrlTemplate;
		wxButton* m_buttonTemplateBrowse;
		wxTextCtrl* m_textCtrlRefTitle;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticRefID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;

		// Virtual event handlers, overide them in your derived class
		virtual void OnMediaDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnMediaSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnMediaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaView( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTemplateBrowse( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgSetupReferenceDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup New Reference"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~fbRgSetupReferenceDialog();

};

