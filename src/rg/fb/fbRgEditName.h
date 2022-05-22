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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
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
		wxChoice* m_choiceStyle;
		wxButton* m_buttonAddStyle;
		wxMenu* m_menuAddEditStyle;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlGiven;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlSurname;
		wxCheckBox* m_checkFullName;
		wxCheckBox* m_checkExtend;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticNameID;
		wxStaticText* m_staticPerIndID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnAddStyleButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddStyle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditStyle( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgCreateName( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create Name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgCreateName();

		void m_buttonAddStyleOnContextMenu( wxMouseEvent &event )
		{
			m_buttonAddStyle->PopupMenu( m_menuAddEditStyle, event.GetPosition() );
		}

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
		wxChoice* m_choiceType;
		wxButton* m_buttonAddType;
		wxMenu* m_menuAddEditType;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlValue;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticNamePartID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnAddTypeButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddType( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditType( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditNamePart( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name Part"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditNamePart();

		void m_buttonAddTypeOnContextMenu( wxMouseEvent &event )
		{
			m_buttonAddType->PopupMenu( m_menuAddEditType, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditNameStyle
///////////////////////////////////////////////////////////////////////////////
class fbRgEditNameStyle : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlStyle;
		wxTextCtrl* m_textCtrlUid;
		wxStaticText* m_staticText161;
		wxTextCtrl* m_textCtrlChanged;
		wxStaticLine* m_staticline4;
		wxStaticText* m_staticNameStyleID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgEditNameStyle( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Name Style"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgEditNameStyle();

};

