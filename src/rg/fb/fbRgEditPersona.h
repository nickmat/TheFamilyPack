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
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/button.h>
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
		wxStaticText* m_staticPerName;
		wxNotebook* m_notebook;
		wxPanel* m_panelDetail;
		wxChoice* m_choiceSex;
		wxTextCtrl* m_textCtrlRef;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxPanel* m_panelNote;
		wxTextCtrl* m_textCtrlNote;
		wxPanel* m_panelName;
		wxListCtrl* m_listName;
		wxButton* m_buttonNameAdd;
		wxButton* m_buttonNameEdit;
		wxButton* m_buttonNameDel;
		wxButton* m_buttonNameUp;
		wxButton* m_buttonNameDn;
		wxPanel* m_panelEventa;
		wxListCtrl* m_listEventa;
		wxButton* m_buttonEventaAdd;
		wxButton* m_buttonEventaEdit;
		wxButton* m_buttonEventaDel;
		wxButton* m_buttonEventaUp;
		wxButton* m_buttonEventaDn;
		wxRadioBox* m_radioBoxEventaOrder;
		wxPanel* m_panelIndividual;
		wxListCtrl* m_listIndividual;
		wxButton* m_buttonIndAdd;
		wxButton* m_buttonIndEdit;
		wxButton* m_buttonIndDel;
		wxButton* m_buttonIndUp;
		wxButton* m_buttonIndDn;
		wxStaticText* m_staticPerID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnNameDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnNameSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnNameAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNameDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventaDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnEventaSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnEventaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventaUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventaDownButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventaOrderBy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnIndSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnIndAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEventDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndDownButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditPersona( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Persona"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditPersona();

};

