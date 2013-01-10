/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrAdmin.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Administration Info functions.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     7 April 2012
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

#include <rec/recContact.h>
#include <rec/recUser.h>
#include <rec/recSystem.h>
#include <rec/recIndividual.h>

#include "tfpWr.h"


wxString tfpWriteResearcherList()
{
    wxString htm;
    recResearcherVec list = recResearcher::GetResearchers();
    idt curUserID = recGetCurrentUser();

    htm << 
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Researchers</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
        "<h1>Researchers</h1>\n"
    ;

    for( size_t i = 0 ; i < list.size() ; i++ ) {
        size_t note = ( list[i].FGetComments().size() ) ? 1 : 0;
        recContactList cl( list[i].FGetConListID() );
        idt userID = list[i].GetUserID();
        recContactVec contacts = list[i].GetContacts();
        size_t csize = contacts.size() + note;

        htm << 
            "<table class='data'>\n"
            "<tr><th>Name</th><th colspan='3'>Details</th></tr>\n"

            "<tr>\n<td rowspan='" << csize << "'>" << list[i].FGetName() <<
            "</td>\n"
        ;
        if( note ) {
            htm << 
                "<td colspan='3'>" << list[i].FGetComments() <<
                "</td>\n</tr>\n"
            ;
        }
        if( csize ) {
            for( size_t j = 0 ; j < contacts.size() ; j++ ) {
                if( j > 0 || note == 1 ) {
                    htm << "<tr>\n";
                }
                htm <<
                    "<td><b><a href='tfpe:C" << contacts[j].FGetID() <<
                    "'>" << contacts[j].GetIdStr() <<
                    "</a></b></td>\n<td>" << contacts[j].GetTypeStr() <<
                    "</td>\n<td>" << contacts[j].GetHtmlValue() <<
                    "</td>\n</tr>\n"
                ;
            }
        } else {
            htm << "<td colspan='3'></td>\n</tr>\n";
        }
        htm <<
            "<tr>\n<td colspan='4' class='status'>\n"
            "<b><a href='tfpe:Re" << list[i].FGetID() <<
            "'>" << list[i].GetIdStr() << 
            "</a></b>"
        ;
        if( userID ) {
            htm << 
                ", <b>" << recUser::GetIdStr( userID ) <<
                "</b>"
            ;
            if( userID == curUserID ) {
                htm << " [Current User]";
            }
        }
        htm << "</td>\n</tr>\n</table>\n";
#if 0
        if( cl.FGetIndID() ) {
            htm << "<a href='tfp:FI" << cl.FGetIndID()
                << "'>" << list[i].FGetName() << "</a>";
        } else {
            htm << list[i].FGetName();
        }
        htm << "</td><td>" << list[i].GetIdStr();
        if( cl.FGetIndID() ) {
            htm << ", " << recIndividual::GetIdStr( cl.FGetIndID() );
        }
        if( userID ) {
            htm << ", " << recUser::GetIdStr( userID );
            if( userID == curUserID ) {
                htm << "*";
            }
        }

        htm << "</td><td><a href='tfpe:Re" << list[i].FGetID()
            << "'><img src=memory:edit.png></a></td><td>" << list[i].FGetComments()
            << "</td></tr>";

        recContactVec contacts = list[i].GetContacts();
        if( contacts.size() ) {
            htm << "<tr><td></td><td colspan=3><table>";

            for( size_t j = 0 ; j < contacts.size() ; j++ ) {
                htm << "<tr><td valign=top align=right>" << contacts[j].GetTypeStr()
                    << ":</td><td>" << contacts[j].GetHtmlValue()
                    << "</td></tr>";
            }
            htm << "</table></td></tr>";
        }
#endif
    }

    htm << "</div></body></html>";

    return htm;
}

// End of tfpWrName.cpp Source
