/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrAdmin.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Administration Info functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7 April 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#include <rec/recContact.h>
#include <rec/recResearcher.h>
#include <rec/recUser.h>
#include <rec/recSystem.h>
#include <rec/recIndividual.h>


wxString tfpWriteResearcherList( const wxString& extdb )
{
    wxString htm;
    recResearcherVec list = recResearcher::GetResearchers( recDb::Coverage::all, extdb );
    idt curUserID = recGetCurrentUser( extdb );

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
        size_t note = ( list[i].FGetComment().empty() ) ? 0 : 1;
        recContactList cl( list[i].FGetConListID(), extdb );
        idt userID = list[i].GetUserID( extdb );
        recContactVec contacts = list[i].GetContacts( extdb );
        size_t csize = contacts.size() + note + 1;

        htm << 
            "<table class='data'>\n"
            "<tr><th>Name</th><th colspan='3'>Details</th></tr>\n"

            "<tr>\n<td rowspan='" << csize << "'>" << list[i].FGetName() <<
            "</td>\n"
        ;
        if( note ) {
            htm << 
                "<td colspan='3'>" << list[i].FGetComment() <<
                "</td>\n</tr>\n"
            ;
        }
        htm <<
            "<td colspan='3'><b>UID:</b> " << list[i].FGetUid() <<
            "</td>\n</tr>\n"
            ;
        if( csize ) {
            for( size_t j = 0 ; j < contacts.size() ; j++ ) {
                if( j > 0 || note == 1 ) {
                    htm << "<tr>\n";
                }
                htm <<
                    "<td><b><a href='tfpe:C" << contacts[j].FGetID() <<
                    "'>" << contacts[j].GetIdStr() <<
                    "</a></b></td>\n<td>" << contacts[j].GetTypeStr( extdb ) <<
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
    }

    htm << "</div></body></html>";

    return htm;
}

// End of src/tfp/tfpWrAdmin.cpp Source
