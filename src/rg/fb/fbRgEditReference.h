///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FBRGEDITREFERENCE_H__
#define __FBRGEDITREFERENCE_H__

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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/panel.h>
#include <wx/webview.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/splitter.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class fbRgEditReference
///////////////////////////////////////////////////////////////////////////////
class fbRgEditReference : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrlTitle;
		wxTextCtrl* m_textCtrlUserRef;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panelTop;
		wxNotebook* m_notebookTop;
		wxPanel* m_panelSource;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_toolCut; 
		wxToolBarToolBase* m_toolCopy; 
		wxToolBarToolBase* m_toolPaste; 
		wxToolBarToolBase* m_toolUndo; 
		wxToolBarToolBase* m_toolRedo; 
		wxTextCtrl* m_textCtrlStatement;
		wxPanel* m_panelView;
		wxWebView* m_webview;
		wxPanel* m_panelBottom;
		wxNotebook* m_notebookBottom;
		wxPanel* m_panelMedia;
		wxListCtrl* m_listMedia;
		wxButton* m_buttonMediaAdd;
		wxButton* m_buttonMediaEdit;
		wxButton* m_buttonMediaDel;
		wxPanel* m_panelPersona;
		wxListCtrl* m_listPersona;
		wxButton* m_buttonPersonaAdd;
		wxMenu* m_menuAddPersona;
		wxButton* m_buttonPersonaEdit;
		wxButton* m_buttonPersonaDel;
		wxPanel* m_panelEntities;
		wxListCtrl* m_listEntities;
		wxButton* m_buttonAdd;
		wxMenu* m_menuAddEntity;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDel;
		wxButton* m_buttonUp;
		wxButton* m_buttonDn;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticRefID;
		wxButton* m_buttonSave1;
		wxButton* m_buttonCancel1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnStatementViewChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnToolCut( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolCopy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolPaste( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolUndo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolRedo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEntityViewChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnMediaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaAddButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddMalePersona( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddFemalePersona( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddUnknownPersona( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaEditButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPersonaDeleteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewSource( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewDate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewDateAge( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewPlace( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewName( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewEventa( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewPersonalEventa( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpEntityButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDownEntityButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fbRgEditReference( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Reference"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~fbRgEditReference();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 265 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( fbRgEditReference::m_splitter1OnIdle ), NULL, this );
		}
		
		void m_buttonPersonaAddOnContextMenu( wxMouseEvent &event )
		{
			m_buttonPersonaAdd->PopupMenu( m_menuAddPersona, event.GetPosition() );
		}
		
		void m_buttonAddOnContextMenu( wxMouseEvent &event )
		{
			m_buttonAdd->PopupMenu( m_menuAddEntity, event.GetPosition() );
		}
	
};

#endif //__FBRGEDITREFERENCE_H__
