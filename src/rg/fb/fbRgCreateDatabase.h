///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBRGCREATEDATABASE_H__
#define __FBRGCREATEDATABASE_H__

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
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/radiobox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgCreateDatabase
///////////////////////////////////////////////////////////////////////////////
class fbRgCreateDatabase : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrlFileName;
		wxButton* m_buttonBrowse;
		wxCheckBox* m_checkBoxAttach;
		wxRadioBox* m_radioBoxType;
		wxRadioBox* m_radioBoxExists;
		wxButton* m_buttonCreate;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBrowseButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckAttached( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreateButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgCreateDatabase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create New Database"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~fbRgCreateDatabase();
	
};

#endif //__FBRGCREATEDATABASE_H__
