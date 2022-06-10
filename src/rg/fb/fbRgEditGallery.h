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
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditGallery
///////////////////////////////////////////////////////////////////////////////
class fbRgEditGallery : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlTitle;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxNotebook* m_notebook;
		wxTextCtrl* m_textCtrlNote;
		wxListCtrl* m_listImage;
		wxButton* m_buttonImageAdd;
		wxMenu* m_popupAddMedia;
		wxButton* m_buttonImageEdit;
		wxButton* m_buttonImageRemove;
		wxButton* m_buttonImageUp;
		wxButton* m_buttonImageDn;
		wxButton* m_buttonViewImage;
		wxStaticText* m_staticGalID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnMediaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddNewMedia( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddExistingMedia( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaRemoveButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewImage( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditGallery( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Gallery"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditGallery();

		void m_buttonImageAddOnContextMenu( wxMouseEvent &event )
		{
			m_buttonImageAdd->PopupMenu( m_popupAddMedia, event.GetPosition() );
		}

};

