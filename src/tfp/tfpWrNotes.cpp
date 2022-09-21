/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrNotes.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write html notes to screen.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 January 2012
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

#include "tfpWr.h"

#include "tfpFrame.h"
#include "tfpVersion.h"

#include <rec/recCitation.h>
#include <rec/recContact.h>
#include <rec/recDate.h>
#include <rec/recPersona.h>
#include <rec/recPlace.h>
#include <rec/recVersion.h>

namespace { 

wxString GetHtmEditLink( const wxString& link, const wxString& extdb )
{
    wxString htm;
    if( extdb.CmpNoCase( "Main" ) == 0 ) {
        htm <<
            " <a href='tfpe:" << link <<
            "'><img src='memory:edit.png'></a>"
            ;
    }
    return htm;
}

wxString GetHtmDateData( const recDate& date, const wxString& extdb )
{
    wxString htm;
        
    htm << date.GetStr() << "<br><br>"
           "Original Scheme: " << CalendarSchemeName[date.f_record_sch] << "<br>"
           "Display Scheme: " << CalendarSchemeName[date.f_display_sch] << "<br>";

    if( date.f_rel_id ) {
        recRelativeDate rel( date.f_rel_id, extdb );
        recDate base( rel.f_base_id, extdb );
        htm << "<br>Base on " << base.GetIdStr() << "<br>"
            << GetHtmDateData( base, extdb );
    }
    return htm;
}

} // namespace

wxString tfpWriteCitation( idt citID, TfpFrame& frame, tfpDisplay display )
{
    const wxString extdb = frame.GetDbName();
    recCitation cit( citID, extdb );
    if( cit.FGetID() == 0 ) return wxString();
    recRepository arc( cit.FGetRepID(), extdb );

    wxString editbutton;
    if( extdb == "Main" ) {
        if( display == tfpDisplay::note ) {
            editbutton = GetHtmEditLink( cit.GetIdStr(), extdb );
        }
        if( display == tfpDisplay::frame ) {
            frame.SetToolFlag( tfpTool::edit );
        }
    }
    wxString htm;
    htm <<
        tfpWrHeadTfp( "Citation" ) <<
        "<h1>Citation " << cit.GetIdStr() <<
        editbutton <<
        "</h1>\n"
        "<p>" << cit.GetCitationStr( extdb ) << "</p>\n"
        "<p>Comment: " << cit.FGetComment() << "</p>\n"
        << tfpWrTailTfp()
    ;
    return htm;
}

wxString tfpWriteDate( idt dateID, TfpFrame& frame, tfpDisplay display )
{
    const wxString extdb = frame.GetDbName();
    recDate date( dateID, extdb );
    if( date.FGetID() == 0 ) return wxEmptyString;

    wxString editbutton;
    if( extdb == "Main" ) {
        if( display == tfpDisplay::note ) {
            editbutton = GetHtmEditLink( date.GetIdStr(), extdb );
        }
        if( display == tfpDisplay::frame ) {
            frame.SetToolFlag( tfpTool::edit );
        }
    }
    wxString htm;
    htm <<
        tfpWrHeadTfp( "Date" ) <<
        "<h1>Date " << date.GetIdStr() <<
        editbutton <<
        "</h1>\n" <<
        GetHtmDateData( date, extdb ) <<
        tfpWrTailTfp()
        ;

    return htm;
}

wxString tfpWritePlace( idt placeID, TfpFrame& frame, tfpDisplay display )
{
    const wxString extdb = frame.GetDbName();
    recPlace place( placeID, extdb );
    if( place.FGetID() == 0 ) return wxEmptyString;

    wxString editbutton;
    if( extdb == "Main" ) {
        if( display == tfpDisplay::note ) {
            editbutton = GetHtmEditLink( place.GetIdStr(), extdb );
        }
        if( display == tfpDisplay::frame ) {
            frame.SetToolFlag( tfpTool::edit );
        }
    }
    wxString htm;
    htm <<
        tfpWrHeadTfp( "Place" ) <<
        "<h1>Place " << place.GetIdStr() <<
        editbutton <<
        "</h1>\n" <<
        place.GetAddressStr( extdb ) << "\n" <<
        tfpWrTailTfp()
    ;
    return htm;
}

wxString tfpWriteName( idt nameID, TfpFrame& frame, tfpDisplay display )
{
    const wxString extdb = frame.GetDbName();
    recName name( nameID, extdb );
    if( name.FGetID() == 0 ) return wxEmptyString;
    recNamePartVec parts = name.GetParts( extdb );

    wxString editbutton;
    if( extdb == "Main" ) {
        if( display == tfpDisplay::note ) {
            editbutton = GetHtmEditLink( name.GetIdStr(), extdb );
        }
        if( display == tfpDisplay::frame ) {
            frame.SetToolFlag( tfpTool::edit );
        }
    }
    wxString htm;
    htm <<
        tfpWrHeadTfp( "Name" ) <<
        "<h1>Name " << name.GetIdStr() << "<br>\n" <<
        name.GetNameStr( extdb ) <<
        editbutton <<
        "</h1>\n"
        "<p>Name Type: <b>" <<
        recNameStyle::GetStyleStr( name.FGetTypeID(), extdb ) <<
        "</b></p>\n<table class='property'>\n"
    ;

    for( size_t i = 0 ; i < parts.size() ; i++ ) {
        htm <<
            "<tr>\n<td class='label'>" <<
            recNamePartType::GetTypeStr( parts[i].FGetTypeID(), extdb ) <<
            ":</td>\n<td><b>" <<
            parts[i].FGetValue() <<
            "</b></td>\n</tr>\n"
        ;
    }
       
    htm << "</table>\n" << tfpWrTailTfp();

    return htm;
}

wxString tfpWriteContact( idt conID, TfpFrame& frame, tfpDisplay display )
{
    const wxString extdb = frame.GetDbName();
    recContact con( conID );
    if( con.FGetID() == 0 ) return wxString();
    recContactType ct( con.FGetTypeID() );

    wxString editbutton;
    if( extdb == "Main" ) {
        if( display == tfpDisplay::note ) {
            editbutton = GetHtmEditLink( con.GetIdStr(), extdb );
        }
        if( display == tfpDisplay::frame && extdb == "Main" ) {
            frame.SetToolFlag( tfpTool::edit );
        }
    }
    wxString htm = tfpWrHeadTfp( "Contact" );
    htm <<
        "<h1>Contact " << con.GetIdStr() <<
        editbutton <<
        "</h1>\n"
        "<p>\n" << tfpHtmlifyText( con.FGetValue() ) << "\n</p>\n"
        "\n<p><b>Contact Type:</b> " << ct.FGetName() <<
        "\n<br>Type Last Changed: " << ct.GetChangedDate() <<
        "\n<br>Type UID: " << ct.FGetUid() <<
        "\n</p>\n" << tfpWrTailTfp()
        ;

    return htm;
}

wxString tfpWriteAbout()
{
    wxString htm = tfpWrHeadInfo( "About" );

    htm <<
        "<div class='heading'>\n"
        "<a  href='http://thefamilypack.org'>\n"
        "<img src='memory:logo6.png' alt='Logo' />\n"
        "</a>\n"
        "About<br>The Family Pack"
        "<div class='clear'></div>\n"
        "</div>\n"
        "<div class='info'>\n"
        "<table class='plist'>\n"
        "<tr><td class='prop'>Program Version:</td><td>" << tfpHtmVersion << "</td></tr>\n"
        "<tr><td class='prop'>Database Version:</td><td>" << recFullVersion << "</td></tr>\n"
        "<tr><td class='prop'>"
        "Libraries:</td><td>" << wxVERSION_STRING <<
        "<br>" << wxSQLite3Database::GetWrapperVersion() <<
        " and SQLite " << wxSQLite3Database::GetVersion() <<
        "</td></tr>\n"
        "<tr><td class='prop'>Website:</td><td>"
        "<a class='web' href='http://thefamilypack.org'>thefamilypack.org</a>"
        "</td></tr>\n"
        "<tr><td class='prop'>Built by:</td><td>" << tfpGetCompilerVersion() << "</td></tr>\n"
        "<tr><td class='prop'>Runnining under:</td><td>" << wxGetOsDescription() << "</td></tr>\n"
        "</table>\n"
        "<div class='button'>\n"
        "<p>\n"
        "<a href='tfpc:Close'>OK</a>\n"
        "</p>\n"
        "</div>\n"
        "<div class='clear'></div>\n"
        "</div>\n"
        << tfpWrTailInfo() 
    ;
    return htm;
}

// End of tfpWrNote.cpp Source
