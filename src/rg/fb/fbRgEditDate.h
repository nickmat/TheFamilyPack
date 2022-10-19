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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/radiobox.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditDate
///////////////////////////////////////////////////////////////////////////////
class fbRgEditDate : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticOutput;
		wxChoice* m_choiceDisplay;
		wxChoice* m_choiceType;
		wxTextCtrl* m_textCtrlDate;
		wxChoice* m_choiceInput;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticDateID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }


	public:

		fbRgEditDate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Date"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditDate();

};

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditRelativeDate
///////////////////////////////////////////////////////////////////////////////
class fbRgEditRelativeDate : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticOutput;
		wxStaticText* m_staticText2;
		wxChoice* m_choiceDisplay;
		wxStaticText* m_staticText3;
		wxChoice* m_choiceCalc;
		wxButton* m_buttonBase;
		wxTextCtrl* m_textCtrlBase;
		wxStaticText* m_staticText3a;
		wxChoice* m_choicePrecision;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlAge;
		wxStaticText* m_staticText5;
		wxChoice* m_choiceInput;
		wxRadioBox* m_radioUnits;
		wxTextCtrl* m_textCtrlUid;
		wxTextCtrl* m_textCtrlChanged;
		wxStaticText* m_staticDateID;
		wxButton* m_buttonSave;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnBaseButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		fbRgEditRelativeDate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Relative Date"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~fbRgEditRelativeDate();

};

