/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrArchive.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Archive record functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     12th November 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tfpWr.h"

#include <rec/recCitation.h>
#include <rec/recContact.h>


wxString tfpWriteArchiveIndex()
{
    wxString htm = tfpWrHeadTfp( "Archive Index" );
    htm <<
        "<h1>Archive List</h1>\n"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Archive</th><th>Note</th></tr>\n"
        ;
    recRepositoryVec list = recRepository::GetFullList();
    for( auto arch : list ) {
        htm <<
            "<tr><td><b><a href='tfp:" << arch.GetIdStr() << "'>" << arch.GetIdStr() <<
            "</a></b></td><td>" << arch.FGetName() <<
            "</td><td>" << arch.FGetNote() <<
            "</td></tr>\n"
            ;
    }
    htm << "</table>\n" << tfpWrTailTfp();
    return htm;
}

wxString tfpWriteArchive( idt arcID )
{
    wxString htm;
    recRepository arc( arcID );
    if( arc.FGetID() == 0 ) {
        return htm;
    }
    htm <<
        tfpWrHeadTfp( "Archive" ) <<
        "<h1>Archive " << arc.GetIdStr() <<
        "<br>\n" << arc.FGetName() <<
        "</h1>\n"
        "<table class='data'>\n"
        "<tr><th colspan='3'>Details</th></tr>\n"
        "<tr><td colspan='3'>" << arc.FGetNote() <<
        "</td></tr>\n"
        ;
    recContactVec contacts = recContactList::GetContacts( arc.FGetConListId() );
    for( auto cont : contacts ) {
        htm <<
            "<tr><td><b>" << cont.GetIdStr() <<
            "</b></td><td>" << recContactType::GetTypeStr( cont.FGetTypeID() ) <<
            "</td><td>" << cont.GetHtmlValue() <<
            "</td></tr>\n"
            ;
    }
    htm << "</table>\n" << tfpWrTailTfp();
    return htm;
}

// End of src/tfp/tfpWrArchive.cpp Source
