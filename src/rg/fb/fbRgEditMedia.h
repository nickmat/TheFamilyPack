///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBRGEDITMEDIA_H__
#define __FBRGEDITMEDIA_H__

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
#include <rg/rgImagePanel.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditMedia
///////////////////////////////////////////////////////////////////////////////
class fbRgEditMedia : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrlTitle;
		rgImagePanel* m_imagePanel;
		wxStaticText* m_staticMediaID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
	
	public:
		
		fbRgEditMedia( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Media"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditMedia();
	
};

#endif //__FBRGEDITMEDIA_H__
