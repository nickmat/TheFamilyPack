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
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>
#include <rg/rgImagePanel.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgViewMedia
///////////////////////////////////////////////////////////////////////////////
class fbRgViewMedia : public wxFrame
{
	private:

	protected:
		wxCheckBox* m_checkScroll;
		wxButton* m_buttonMinus;
		wxSlider* m_sliderZoom;
		wxButton* m_buttonPlus;
		wxStaticText* m_staticTextZoom;
		wxTextCtrl* m_textCtrlZoom;
		wxButton* m_button100Percent;
		wxButton* m_buttonExport;
		wxButton* m_buttonPrint;
		rgImagePanel* m_imageViewer;

		// Virtual event handlers, overide them in your derived class
		virtual void OnCheckScroll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonMinus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoomSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnButtonPlus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetZoom( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButton100Percent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonExport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonPrint( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgViewMedia( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("View Image"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~fbRgViewMedia();

};

