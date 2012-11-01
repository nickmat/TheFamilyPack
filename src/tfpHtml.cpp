/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpHtml.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     TfpHtml class source.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     23 February 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/wxcrt.h>

#include <rec/recDb.h>

#include "tfpHtml.h"
#include "tfpFrame.h"
#include "tfpWr.h"
#include "dlg/dlgEd.h"


BEGIN_EVENT_TABLE(TfpHtml, wxHtmlWindow)
    EVT_HTML_LINK_CLICKED( wxID_ANY, TfpHtml::OnHtmlLinkClicked )
//    EVT_MENU_RANGE( tfpID_HCTXMENU_BEG, tfpID_HCTXMENU_END, TfpHtml::OnHtmCtxMenu )
    EVT_MENU_RANGE( tfpID_RCTXMENU_BEG, tfpID_RCTXMENU_END, TfpHtml::OnRightCtxMenu )
    EVT_MENU_RANGE( tfpID_INDMENU_BEG, tfpID_INDMENU_END, TfpHtml::OnHtmIndMenu )
END_EVENT_TABLE()


/*! \brief Called on a link in the html control being clicked.
 *
 *  Decodes the href string of the clicked link. If the first
 *  character of the href string is:-
 *
 *  ':' then the remainder of the string is a command.
 *
 *  '!' then the remainder of the string is a web address to be
 *  passed to the default external browser.
 *
 */
void TfpHtml::OnHtmlLinkClicked( wxHtmlLinkEvent& event )
{
    wxString href = event.GetLinkInfo().GetHref();
    const wxMouseEvent *e = event.GetLinkInfo().GetEvent();

    if (e == NULL || e->LeftUp()){
        DoLinkLeft( href );
    }
    if (e == NULL || e->RightUp()){
        DoLinkRight( href );
    }
}

void TfpHtml::DoLinkRight( const wxString& href )
{
    if( href.StartsWith( ":" ) || href.StartsWith( "!" ) ) {
        return;
    }
    if( href.StartsWith( "$" ) ) {
        DoLinkLeft( href );
        return;
    }
    if( href.StartsWith( "^" ) ) {
        DoRightCtxMenu( href.Mid( 1 ) );
        return;
    }
    DoRightCtxMenu( href );
}

void TfpHtml::DoLinkLeft( const wxString& href )
{
    wxUniChar uch0 = href.GetChar( 0 );
    wxUniChar uch1, uch2;
    long cond = recDb::GetChange();

    try {
        switch( uch0.GetValue() )
        {
        case ':': // Program Commands
            if( m_frame ) {
                if( href == ":New" ) {
                    m_frame->NewFile();
                } else if( href == ":Open" ) {
                    m_frame->OpenFile();
                } else if( href == ":Import" ) {
                    m_frame->ImportGedcom();
                } else {
                    wxMessageBox( _("Error: Invalid Command"), _("Link Error") );
                }
            }
            break;
        case '$':  // Context Commands
            uch1 = href.GetChar( 1 );
            switch( uch1.GetValue() )
            {
            case 'I': // Edit the given individual (create if 0)
                uch2 = href.GetChar( 2 );
                switch( uch2.GetValue() )
                {
                case 'L': case 'R':
                    tfpAddNewSpouse( href.Mid(2) );
                    break;
                case 'F': case 'M':
                    tfpAddNewParent( href.Mid(2) );
                    break;
                }
                break;
            case 'M': // Create a popup menu
                DoHtmCtxMenu( href.Mid(2) );
                break;
            case 'R': // Edit reference record
                uch2 = href.GetChar( 2 );
                if( uch2.GetValue() == 'e' ) {
                    tfpEditResearcher( href.Mid(3) );
                } else {
                    tfpEditReference( href.Mid(2) );
                }
                break;
            }
            break;
        case '!':  // Display in external browser
            wxLaunchDefaultBrowser( href.Mid( 1 ) );
            break;
        case '^':  // Display the given reference as a note
            tfpDisplayNote( this, href.Mid( 1 ) );
            break;
        default:   // Display the given reference
            DisplayHtmPage( href );
            break;
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
    if( cond != recDb::GetChange() ) {
        RefreshHtmPage();
    }
}

void TfpHtml::DoHtmCtxMenu( const wxString& ref )
{
    m_ctxmenuref = ref;
    wxMenu* menu = new wxMenu;

    switch( (wxChar) ref.GetChar( 0 ) )
    {
    case 'F': // Edit family record or children
        menu->Append( tfpID_HCTXMENU_EDIT_FAMILY, wxT("Edit Family") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_SON, wxT("Add new Son") );
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_DAUR, wxT("Add new Daughter") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_SON, wxT("Add existing Son") );
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_DAUR, wxT("Add existing Daughter") );
        break;
    case 'H': case 'W': // Edit a Husb or Wife Individual
        menu->Append( tfpID_HCTXMENU_EDIT_INDIVIDUAL, wxT("Edit Individual") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_MOTHER, wxT("Add new Mother") );
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_FATHER, wxT("Add new Father") );
        menu->Append( tfpID_HCTXMENU_EDIT_NEW_SPOUSE, wxT("Add new Spouse") );
        menu->AppendSeparator();
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_MOTHER, wxT("Add existing Mother") );
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_FATHER, wxT("Add existing Father") );
        menu->Append( tfpID_HCTXMENU_EDIT_EXIST_SPOUSE, wxT("Add existing Spouse") );
        break;
    case 'R':
        // Parents, Spouses (Marriage), Siblings, and Children
        // List individuals and jump to the selected individuals family
        AddFamiliesToMenu( ref, menu, tfpID_INDMENU_BEG );
        break;
    default:
        delete menu;
        wxMessageBox( wxT("Error: \"") + ref + wxT("\" Unknown Menu"), wxT("Link Error") );
        return;
    }

    PopupMenu( menu );
    delete menu;
}

int TfpHtml::AddFamiliesToMenu( const wxString& ref, wxMenu* menu, int cmd_ID )
{
    recFamilyVec families;
    size_t c = 0, i, j;
    recIndividualList inds;
    wxLongLong_t indID;
    ref.Mid( 1 ).ToLongLong( &indID );
    m_ctxmenuPages.clear();
    wxString page;


    menu->Append( cmd_ID + c, wxT("Family") );
    m_ctxmenuPages.push_back( "FI"+recGetStr( indID ) );
    c++;

    wxMenu* parmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_PARENTS, "Parents", parmenu );

    families = recIndividual::GetParentList( indID );
    int items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        if( families[i].f_husb_id != 0 ) {
            parmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_husb_id ) );
        }
        if( families[i].f_wife_id != 0 ) {
            parmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_wife_id ) );
        }
        m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
        c++;
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_PARENTS, false );
    }

    wxMenu* sibmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_SIBLINGS, "Siblings", sibmenu );
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        inds = families[i].GetChildren();
        for( j = 0 ; j < inds.size() ; j++ ) {
            if( inds[j].f_id == indID ) continue;
            sibmenu->Append( cmd_ID + c, inds[j].GetFullName() );
            m_ctxmenuPages.push_back( "FI"+recGetStr( inds[j].f_id ) );
            c++;
        }
        inds.empty();
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_SIBLINGS, false );
    }

    wxMenu* marmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_SPOUSES, "Spouses", marmenu );
    families.empty();
    families = recIndividual::GetFamilyList( indID );
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        if( families[i].f_husb_id != 0 && families[i].f_husb_id != indID ) {
            marmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_husb_id ) );
            m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
            c++;
        }
        if( families[i].f_wife_id != 0 && families[i].f_wife_id != indID ) {
            marmenu->Append( cmd_ID + c, recIndividual::GetFullName( families[i].f_wife_id ) );
            m_ctxmenuPages.push_back( "F"+recGetStr( families[i].f_id ) );
            c++;
        }
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_SPOUSES, false );
    }

    wxMenu* kidmenu = new wxMenu;
    menu->Append( tfpID_INDMENU_CHILDREN, "Children", kidmenu );
    items = c;
    for( i = 0 ; i < families.size() ; i++ ) {
        inds.empty();
        inds = families[i].GetChildren();
        for( j = 0 ; j < inds.size() ; j++ ) {
            kidmenu->Append( cmd_ID + c, inds[j].GetFullName() );
            m_ctxmenuPages.push_back( "FI"+recGetStr( inds[j].f_id ) );
            c++;
        }
    }
    if( items == c ) {
        menu->Enable( tfpID_INDMENU_CHILDREN, false );
    }
    families.clear();
    inds.clear();
    return c;
}

void TfpHtml::OnHtmIndMenu( wxCommandEvent& event )
{
    size_t i = event.GetId() - tfpID_INDMENU_BEG;
    DisplayHtmPage( m_ctxmenuPages[i] );
}

void TfpHtml::OnHtmCtxMenu( wxCommandEvent& event )
{
    bool ret = false;
    Sex sex;
    idt id = recGetID( m_ctxmenuref.Mid(1) );
    recFamily fam(id);
    if( id == 0 && m_ctxmenuref.StartsWith( "F0," ) ) {
        fam.Decode( m_ctxmenuref );
    }

    recDb::Begin();
    try {
        switch( event.GetId() )
        {
        case tfpID_HCTXMENU_EDIT_FAMILY:
            ret = tfpEditFamily( fam );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SON:
            if( tfpAddNewChild( id, SEX_Male ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_NEW_DAUR:
            if( tfpAddNewChild( id, SEX_Female ) != 0 ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SON:
            ret = tfpAddExistChild( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_DAUR:
            ret = tfpAddExistChild( id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_INDIVIDUAL:
            ret = tfpEditIndividual( id );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_MOTHER:
            ret = tfpAddNewParent( id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_FATHER:
            ret = tfpAddNewParent( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_NEW_SPOUSE:
            sex = ( m_ctxmenuref.GetChar(0) == 'H' ) ? SEX_Female : SEX_Male;
            id = tfpAddNewIndividual( recIndividual::GetDefaultFamily( id ), sex );
            if( id ) ret = true;
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_MOTHER:
            ret = tfpAddExistParent( id, SEX_Female );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_FATHER:
            ret = tfpAddExistParent( id, SEX_Male );
            break;
        case tfpID_HCTXMENU_EDIT_EXIST_SPOUSE:
            sex = ( m_ctxmenuref.GetChar(0) == 'H' ) ? SEX_Female : SEX_Male;
            ret = tfpAddExistSpouse( id, sex );
            break;
        case tfpID_HCTXMENU_EDIT_REFERENCE:
            ret = tfpEditReference( id );
            break;
        case tfpID_HCTXMENU_EDIT_EVENT:
            ret = tfpEditEvent( id );
            break;
        }
        if( ret == true ) {
            recDb::Commit();
            RefreshHtmPage();
        } else {
            recDb::Rollback();
        }
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }
}

void TfpHtml::DoRightCtxMenu( const wxString& ref )
{
    m_ctxmenuref = ref;
    wxMenu* menu = new wxMenu;

    menu->Append( tfpID_RCTXMENU_DISPLAY, "Display " + ref );
    menu->Append( tfpID_RCTXMENU_DISPLAY_NOTE, _("Display as Note") );

    if( wxIsdigit( ref.GetChar( 1 ) ) ) {
        if( ref.StartsWith( "R" ) ) {
            menu->Append( tfpID_HCTXMENU_EDIT_REFERENCE, "Edit " + ref );
        }
        if( ref.StartsWith( "E" ) ) {
            menu->Append( tfpID_HCTXMENU_EDIT_EVENT, "Edit " + ref );
        }
        if( ref.StartsWith( "I" ) ) {
            menu->Append( tfpID_HCTXMENU_EDIT_INDIVIDUAL, "Edit " + ref );
        }
    }
    PopupMenu( menu );
    delete menu;
}

void TfpHtml::OnRightCtxMenu( wxCommandEvent& event )
{
    int menuid = event.GetId();

    if( menuid == tfpID_RCTXMENU_DISPLAY ) {
        DoLinkLeft( m_ctxmenuref );
    }
    if( menuid == tfpID_RCTXMENU_DISPLAY_NOTE ) {
        DoLinkLeft( "^" + m_ctxmenuref );
    }
}

wxString TfpHtml::GetDisplayText( const wxString& name )
{
    wxUniChar uch, uch1;
    wxLongLong_t num;
    bool success;

    wxASSERT( name.size() > 0 );
    uch = name.GetChar( 0 );
    switch( uch.GetValue() )
    {
    case 'A':  // Attribute
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Attribute ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteAttribute( num );
    case 'C':  // Chart reference
        success = name.Mid(2).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Individual ID link"), _("Link Error") );
            return wxEmptyString;
        }
        switch( (wxChar) name.GetChar( 1 ) )
        {
        case 'D':
            return tfpCreateDescChart( num );
        case 'P':
            return tfpCreatePedChart( num );
        }
        wxMessageBox( _("Error: Invalid Chart link reference"), _("Link Error") );
        return wxEmptyString;
    case 'D':  // Date
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Date ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteDate( num );
    case 'E':  // Reference Document
        if( name == "E" ) {
            return tfpWriteEventIndex();
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Reference Document ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteEventPage( num );
    case 'F':  // Family reference
        if( name.GetChar( 1 ) == 'I' ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                wxMessageBox( _("Error: Invalid Individual ID link"), _("Link Error") );
                return wxEmptyString;
            }
            return tfpWriteIndFamilyPage( num );
        }
        return tfpWriteFamilyPage( name.Mid(1) );
    case 'I':  // Individual reference
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Individual ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteIndividualPage( num );
    case 'N':  // Name index
        if( name == "N" ) {
            return tfpWriteIndividualIndex();
        }
        if( name == "N*" ) {
            return tfpWriteIndividualList( wxEmptyString );
        }
        return tfpWriteIndividualList( name.Mid( 1 ) );
    case 'P':  // Place
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Place ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWritePlace( num );
    case 'R':  // Reference Document
        if( name == "R" ) {
            return tfpWriteReferenceIndex();
        }
        if( name == "Re" ) {
            return tfpWriteResearcherList();
        }
        uch1 = name.GetChar( 1 );
        if( !wxIsdigit( uch1 ) ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                wxMessageBox( _("Error: Invalid ID link"), _("Link Error") );
                return wxEmptyString;
            }
            switch( uch1.GetValue() )
            {
            case 's':
                return tfpWriteRelationship( num );
            default:
                wxMessageBox( _("Error: Invalid ID link"), _("Link Error") );
                return wxEmptyString;
            }
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Reference Document ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteReferencePage( num );
    }
    wxMessageBox( _("Error: Invalid Display Name ")+name, _("Link Error") );
    return wxEmptyString;
}

void TfpHtml::DisplayBlankPage( const wxString& name )
{
    wxString txt;
    txt << "<html><head><title>" << name << "</title></head><body>" 
        << name << " Not Found.</body></html>";
    SetPage( txt );
}

bool TfpHtml::DisplayHtmPage( const wxString& name )
{
    wxString text = GetDisplayText( name );
    if( !text.IsEmpty() )
    {
        if( m_frame ) {
            m_frame->PushHtmName( name );
        }
        m_name = name;
        SetPage( text );
        return true;
    }
    return false;
}

void TfpHtml::RefreshHtmPage()
{
    if( !m_name.IsEmpty() ) {
        SetPage( GetDisplayText( m_name ) );
    }
}


// End of tfpHtml.cpp file

