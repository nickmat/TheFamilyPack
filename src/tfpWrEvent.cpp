/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Events.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include <rec/recEvent.h>
#include <rec/recPersona.h>

#include "tfpWr.h"

wxString tfpWriteEventIndex()
{
    static wxString htm;
    static long lastchange(0);

    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    htm = "<html><head><title>Event List</title></head><body>"
          "<h1>Event List</h1>";

    wxSQLite3ResultSet result = recEvent::GetTitleList();

    size_t cnt = 0;
    if( result.GetColumnCount() > 0 )
    {
        while( result.NextRow() )
        {
            htm << "<a href='E"
                << result.GetAsString( 0 )
                << "'><b>E"
                << result.GetAsString( 0 )
                << "</b></a> "
                << result.GetAsString( 1 )
                << "<br>";
            cnt++;
        }
        htm << "<br><br>Total Events found: " << cnt;
    } else {
        htm << "No Events found!";
    }

    htm << "</body></html>";

    lastchange = recDb::GetChange();
    return htm;
}

wxString tfpWriteEventPage( idt eventID )
{
    wxString htm;
    recEvent eve(eventID);

    htm << "<html><head><title>Event " << eve.GetIdStr() 
        << "</title></head><body>"
           "<h1>Event " << eve.GetIdStr() << " " << eve.f_title << "</h1>"
           "<table><tr><td>Date:</td><td>" << eve.GetDateStr()
        << "</td></tr><tr><td>Place:</td><td>" << eve.GetAddressStr()
        << "</td></tr><tr><td>Note:</td><td>" << eve.f_note
        << "</td></tr></table><br>";

    recEventPersonaVec eps = eve.GetEventPersonas();
    if( !eps.empty() ) {
        htm << "<table>";
        for( size_t i = 0 ; i < eps.size() ; i++ ) {
            recPersona per(eps[i].f_per_id);
            htm << "<tr><td>" << recEventTypeRole::GetName( eps[i].f_role_id )
                << "</td><td><b>" << per.GetNameStr() 
                << "</b>";
            if( per.f_ref_id ) {
                htm << " <a href=R" << per.f_ref_id
                    << "><img src=memory:ref.bmp></a>";
            } 
            recIdVec indIDs = per.GetIndividualIDs();
            for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
                htm << " <a href=$MR" << indIDs[j]
                    << "><img src=memory:fam.bmp></a>";
            }
            htm << "</td><td>" << eps[i].f_note
                << " </td></tr>";
        }
        htm << "</table>";
    }
    htm << "</body></html>";

    return htm;
}

// End of tfpWrEvent.cpp Source
