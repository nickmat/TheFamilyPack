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
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditEventEventa
///////////////////////////////////////////////////////////////////////////////
class fbRgEditEventEventa : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticEvent;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticEventa;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticRef;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlConf;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrlNote;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticEvEvRecID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgEditEventEventa( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Link Event to Eventa"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditEventEventa();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditEventa
///////////////////////////////////////////////////////////////////////////////
class fbRgEditEventa : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlTitle;
		wxNotebook* m_notebook7;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrlType;
		wxButton* m_buttonDate1;
		wxTextCtrl* m_textCtrlDate1;
		wxButton* m_buttonDate2;
		wxTextCtrl* m_textCtrlDate2;
		wxButton* m_buttonPlace;
		wxTextCtrl* m_textCtrlPlace;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxPanel* m_panel25;
		wxTextCtrl* m_textCtrlNote;
		wxPanel* m_panel2;
		wxListCtrl* m_listPersona;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxPanel* m_panel26;
		wxListCtrl* m_listConclusion;
		wxButton* m_buttonAddCon;
		wxButton* m_buttonEditCon;
		wxButton* m_buttonDeleteCon;
		wxStaticLine* m_staticline12;
		wxStaticText* m_staticEventaID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnDate1Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDate2Button( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlaceButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddPer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditPer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeletePer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddCon( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditCon( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteCon( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditEventa( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Eventa"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditEventa();

};

