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
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/radiobox.h>
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditPersona
///////////////////////////////////////////////////////////////////////////////
class fbRgEditPersona : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticPerName;
		wxNotebook* m_notebook;
		wxPanel* m_panel1;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlNote;
		wxStaticText* m_staticText11;
		wxChoice* m_choiceSex;
		wxButton* m_buttonIndLink;
		wxStaticText* m_staticText13;
		wxStaticText* m_staticIndId;
		wxPanel* m_panel2;
		wxListCtrl* m_listName;
		wxButton* m_buttonNameAdd;
		wxButton* m_buttonNameEdit;
		wxButton* m_buttonNameDel;
		wxButton* m_buttonNameUp;
		wxButton* m_buttonNameDn;
		wxPanel* m_panel21;
		wxListCtrl* m_listEvent;
		wxButton* m_buttonEventAdd;
		wxButton* m_buttonEventEdit;
		wxButton* m_buttonEventDel;
		wxButton* m_buttonEventUp;
		wxButton* m_buttonEventDn;
		wxRadioBox* m_radioBox3;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticPerID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;

		// Virtual event handlers, override them in your derived class
		virtual void OnPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnIndLinkButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOrderBy( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditPersona( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Persona"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditPersona();

};

