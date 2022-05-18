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
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgCreateName
///////////////////////////////////////////////////////////////////////////////
class fbRgCreateName : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlGiven;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlSurname;
		wxStaticLine* m_staticline1;
		wxCheckBox* m_checkFullName;
		wxStaticText* m_staticNameID;
		wxCheckBox* m_checkExtend;
		wxStaticText* m_staticPerIndID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgCreateName( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create Name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgCreateName();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditName
///////////////////////////////////////////////////////////////////////////////
class fbRgEditName : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticName;
		wxStaticText* m_staticText2;
		wxChoice* m_choiceType;
		wxListCtrl* m_listNamePart;
		wxButton* m_buttonPartAdd;
		wxButton* m_buttonPartEdit;
		wxButton* m_buttonPartDel;
		wxButton* m_buttonPartUp;
		wxButton* m_buttonPartDown;
		wxStaticLine* m_staticline12;
		wxStaticText* m_staticNameID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnPartAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartUpButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDownButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditName( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditName();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditNamePart
///////////////////////////////////////////////////////////////////////////////
class fbRgEditNamePart : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlValue;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticNamePartID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgEditNamePart( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name Part"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditNamePart();

};

