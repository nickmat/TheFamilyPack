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
    recResearcherVec list =
        recResearcher::GetResearchers( recDb::Coverage::userfirst, extdb );
    idt curUserID = recGetCurrentUser( extdb );

    wxString htm = tfpWrHeadTfp( "Researcher Index" );
    htm <<
        "<h1>Repository List</h1>\n"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Name</th><th>Comment</th><th>User</th></tr>\n"
        ;
    for( auto res : list ) {
        idt userID = res.GetUserID();
        htm <<
            "<tr><td><b><a href='tfp:" << res.GetIdStr() <<
            "'>" << res.GetIdStr() <<
            "</a></b></td><td>" << res.FGetName() <<
            "</td><td>" << res.FGetComment() <<
            "</td><td>"
            ;
        if( userID ) {
            htm << recUser::GetIdStr( userID );
            if( userID == curUserID ) {
                htm << " [Current]";
            }
        }
        htm << "</td></tr>\n";
    }
    htm << "</table>\n" << tfpWrTailTfp();
    return htm;
}

wxString tfpWriteResearcher( idt reID, const wxString& extdb )
{
    recResearcher re( reID );
    if( re.FGetID() == 0 ) {
        return wxString();
    }
    size_t note = (re.FGetComment().empty()) ? 0 : 1;
    recContactVec contacts = re.GetContacts( extdb );
    size_t csize = contacts.size() + note + 1;
    idt userID = re.GetUserID( extdb );
    idt curUserID = recGetCurrentUser( extdb );

    wxString htm;

    htm <<
        tfpWrHeadTfp( "Researcher" ) <<
        "<h1>Reseacher " << re.GetIdStr() <<
        "<br>\n" << re.FGetName() <<
        "</h1>\n"
        "<table class='data'>\n"
        "<tr><th colspan='3'>Details</th></tr>\n"
        ;
    if( note ) {
        htm <<
            "<tr><td colspan='3'>" << re.FGetComment() <<
            "</td>\n</tr>\n"
            ;
    }
    for( auto& con: contacts ) {
        htm <<
            "<tr><td><b><a href='tfpe:C" << con.FGetID() <<
            "'>" << con.GetIdStr() <<
            "</a></b></td>\n"
            "<td>" << con.GetTypeStr( extdb ) <<
            "</td>\n<td>" << con.GetHtmlValue() <<
            "</td>\n</tr>\n"
            ;
    }
    htm <<
        "<tr><td colspan='2'>Date Last Changed: " << re.GetChangedDate() <<
        " </td><td>UID: " << re.FGetUid() <<
        "</td></tr>\n"
        ;
    if( userID ) {
        htm <<
            "<tr>\n<td colspan='3' class='status'>\n"
            "<b>" << recUser::GetIdStr( userID ) <<
            "</b>"
            ;
        if( userID == curUserID ) {
            htm << " [Current User]";
        }
        htm << "</td>\n</tr>\n";
    }
    htm << "</table>\n" << tfpWrTailTfp();

    return htm;
}


// End of src/tfp/tfpWrAdmin.cpp Source
