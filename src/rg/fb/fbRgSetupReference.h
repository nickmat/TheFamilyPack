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
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
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
		wxMenu* m_popupAddMedia;
		wxMenuItem* m_opAddNewMedia;
		wxMenuItem* m_opAddExistingMedia;
		wxButton* m_buttonMediaEdit;
		wxButton* m_buttonMediaDel;
		wxButton* m_buttonMediaUp;
		wxButton* m_buttonMediaDn;
		wxButton* m_buttonMediaView;
		wxTextCtrl* m_textCtrlTemplate;
		wxButton* m_buttonTemplateBrowse;
		wxTextCtrl* m_textCtrlRefTitle;
		wxStaticText* m_staticRefID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, overide them in your derived class
		virtual void OnMediaDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnMediaSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnMediaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddNewMedia( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddExistingMedia( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaViewButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTemplateBrowse( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgSetupReferenceDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup New Reference"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~fbRgSetupReferenceDialog();

		void m_buttonMediaAddOnContextMenu( wxMouseEvent &event )
		{
			m_buttonMediaAdd->PopupMenu( m_popupAddMedia, event.GetPosition() );
		}

};

