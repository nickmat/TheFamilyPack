///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBRGEDITGALLERY_H__
#define __FBRGEDITGALLERY_H__

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
		wxNotebook* m_notebook;
		wxTextCtrl* m_textCtrlNote;
		wxListCtrl* m_listImage;
		wxButton* m_buttonImageAdd;
		wxButton* m_buttonImageEdit;
		wxButton* m_buttonImageDel;
		wxButton* m_buttonImageUp;
		wxButton* m_buttonImageDn;
		wxButton* m_buttonViewImage;
		wxStaticText* m_staticGalID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewImage( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditGallery( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Gallery"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditGallery();
	
};

#endif //__FBRGEDITGALLERY_H__
