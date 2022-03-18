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
#include <rg/rgImagePanel.h>
#include <wx/splitter.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditMedia
///////////////////////////////////////////////////////////////////////////////
class fbRgEditMedia : public wxDialog
{
	private:
		wxStaticText* m_staticText14;

	protected:
		wxTextCtrl* m_textCtrlTitle;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panelNote;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_textCtrlNote;
		wxPanel* m_panelImage;
		rgImagePanel* m_imagePanel;
		wxStaticText* m_staticText;
		wxStaticText* m_staticText_mdID;
		wxSpinCtrl* m_spinCtrlPrivacy;
		wxStaticText* m_staticTextRefID;
		wxStaticText* m_staticTextRefTitle;
		wxStaticText* m_staticMediaID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnImageLeftDClick( wxMouseEvent& event ) { event.Skip(); }


	public:

		fbRgEditMedia( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Media"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditMedia();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 100 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditMedia::m_splitter1OnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditMediaData
///////////////////////////////////////////////////////////////////////////////
class fbRgEditMediaData : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlTitle;
		wxTextCtrl* m_textCtrlFile;
		wxChoice* m_choiceFileType;
		wxTextCtrl* m_textCtrlCopyright;
		wxSpinCtrl* m_spinPrivacy;
		wxStaticText* m_staticText151;
		wxTextCtrl* m_textCtrlUid;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textCtrlChanged;
		wxPanel* m_panelImage;
		rgImagePanel* m_imagePanel;
		wxStaticText* m_staticMediaDataID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnImageLeftDClick( wxMouseEvent& event ) { event.Skip(); }


	public:

		fbRgEditMediaData( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Media Data"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditMediaData();

};

