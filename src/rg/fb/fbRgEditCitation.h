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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/dialog.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditCitation
///////////////////////////////////////////////////////////////////////////////
class fbRgEditCitation : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlCitation;
		wxTextCtrl* m_textCtrlComment;
		wxButton* m_buttonSelectExtends;
		wxTextCtrl* m_textCtrlExtends;
		wxButton* m_buttontRepository;
		wxMenu* m_menuRepository;
		wxTextCtrl* m_textCtrlArchive;
		wxListCtrl* m_listParts;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxButton* m_buttonUp;
		wxButton* m_buttonDown;
		wxStaticText* m_staticRefCiID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnButtonSelectExtends( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonRepository( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectRepository( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditRepository( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPartDeselect( wxListEvent& event ) { event.Skip(); }
		virtual void OnPartSelect( wxListEvent& event ) { event.Skip(); }
		virtual void OnButtonAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDown( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditCitation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Citation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,350 ), long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgEditCitation();

		void m_buttontRepositoryOnContextMenu( wxMouseEvent &event )
		{
			m_buttontRepository->PopupMenu( m_menuRepository, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditRepository
///////////////////////////////////////////////////////////////////////////////
class fbRgEditRepository : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlName;
		wxTextCtrl* m_textCtrlNote;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxListCtrl* m_listContacts;
		wxButton* m_buttonAdd;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;
		wxButton* m_buttonUp;
		wxButton* m_buttonDown;
		wxStaticText* m_staticRepID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnContactDeselected( wxListEvent& event ) { event.Skip(); }
		virtual void OnContactSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnButtonAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDown( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditRepository( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Repository"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgEditRepository();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditCitationPart
///////////////////////////////////////////////////////////////////////////////
class fbRgEditCitationPart : public wxDialog
{
	private:

	protected:
		wxChoice* m_choiceType;
		wxButton* m_buttonTypeAdd;
		wxMenu* m_menuAddEditType;
		wxTextCtrl* m_textCtrlValue;
		wxTextCtrl* m_textCtrlComment;
		wxStaticText* m_staticCipID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnAddEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddType( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditType( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditCitationPart( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Citation Part"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgEditCitationPart();

		void m_buttonTypeAddOnContextMenu( wxMouseEvent &event )
		{
			m_buttonTypeAdd->PopupMenu( m_menuAddEditType, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditCitationPartType
///////////////////////////////////////////////////////////////////////////////
class fbRgEditCitationPartType : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_textCtrlName;
		wxTextCtrl* m_textCtrlComment;
		wxChoice* m_choiceStyle;
		wxStaticLine* m_staticline9;
		wxStaticText* m_staticCiPT_ID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

	public:

		fbRgEditCitationPartType( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Citation Part Type"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~fbRgEditCitationPartType();

};

