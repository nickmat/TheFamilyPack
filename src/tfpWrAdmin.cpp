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

    htm << "<html><head><title>Researchers</title>"
           "<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>"
           "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>"
           "</head><body>"
           "<h1>Researchers</h1><table>";
    for( size_t i = 0 ; i < list.size() ; i++ ) {
        recContactList cl( list[i].FGetConListID() );
        idt userID = list[i].GetUserID();

        htm << "<tr><td>";
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
                    << ":</td><td>" << contacts[j].GetHtmlValue( "!" )
                    << "</td></tr>";
            }
            htm << "</table></td></tr>";
        }
    }

    htm << "</table></body></html>";

    return htm;
}

// End of tfpWrName.cpp Source
