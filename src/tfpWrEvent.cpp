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
#include <rec/recIndividual.h>

#include <rg/rgCompareEvent.h>

#include "tfpWr.h"

static wxString tfpWriteIndEventPage( idt eventID, rgCompareEvent* ce );
static wxString tfpWriteRefEventPage( idt eventID );

wxString tfpWriteEventIndex()
{
    static wxString htm;
    static long lastchange(0);

    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    htm = "<html><head><title>Event List</title>"
          "<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>"
          "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>"
          "</head><body>"
          "<h1>Event List</h1>";

    wxSQLite3ResultSet result = recEvent::GetTitleList();

    size_t cnt = 0;
    if( result.GetColumnCount() > 0 )
    {
        while( result.NextRow() )
        {
            htm << "<a href='tfp:E"
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

wxString tfpWriteEventPage( idt eventID, rgCompareEvent* ce )
{
    if( recEvent::IsIndEvent( eventID ) ) {
        return tfpWriteIndEventPage( eventID, ce );
    }
    return tfpWriteRefEventPage( eventID );
}


wxString tfpWriteIndEventPage( idt eventID, rgCompareEvent* ce )
{
    ce->Reset( eventID );
    wxString htm;
    recEvent eve(eventID);
    if( eve.f_id == 0 ) return wxEmptyString;

    htm << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
           "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
           "<html>\n<head>\n"
           "<title>Event " << eve.GetIdStr() << "</title>\n"
           "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
           "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
           "</head>\n<body>\n"

           "<h1>Event " << eve.GetIdStr() << ": " << eve.f_title << "</h1>\n"

           "<table class='data'>\n<tr>\n"
           "<td><b>Date: </b>" << eve.GetDateStr() << "</td>\n"
           "</tr>\n<tr>\n"
           "<td><b>Place: </b>" << eve.GetAddressStr() << "</td>\n"
           "</tr>\n<tr>\n"
           "<td><b>Note: </b>" << eve.f_note << "</td>\n"
           "</tr>\n<tr>\n"
           "<td><b>Group: </b>" << recEventType::GetGroupStr( eve.FGetTypeID() ) <<
           " <b>Type: </b>" << eve.GetTypeStr() << "</td>\n"
           "</tr>\n</table>\n"
    ;

    recIndEventVec ies = eve.GetIndividualEvents();
    if( !ies.empty() ) {
        htm << "<table class='data'>\n<tr>\n"
               "<th>Role</th>\n<th>Individual</th>\n<th>Note</th>\n</tr>\n";
        for( size_t i = 0 ; i < ies.size() ; i++ ) {
            recIndividual ind(ies[i].FGetIndID());
            recPersona per( recIndividual::GetPersona( ind.FGetID() ) );
            htm << "<tr>\n<td>" << recEventTypeRole::GetName( ies[i].FGetRoleID() )
                << "</td>\n<td class='" << GetSexClass( ind.FGetID() ) 
                << "'>\n<b><a href='tfp:I" << ind.FGetID() 
                << "'>" << per.GetNameStr()
                << "</a></b>";
            recIdVec indIDs = per.GetIndividualIDs();
            for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
                htm << " <a href='tfpc:MR" << indIDs[j]
                    << "'><img src='memory:fam.png' alt='Family'></a>";
            }
            htm << "</td>\n<td>" << ies[i].f_note
                << " </td>\n</tr>\n";
        }
        htm << "</table>\n";
    }
    htm << ce->GetRefEventsTable()
        << ce->GetRefDatesTable()
        << ce->GetRefPlacesTable()
        << "</body>\n</html>\n";

    return htm;
}

wxString tfpWriteRefEventPage( idt eventID )
{
    wxString htm;
    recEvent eve(eventID);
    if( eve.f_id == 0 ) return wxEmptyString;

    htm << "<html><head><title>Event " << eve.GetIdStr() << "</title>"
           "<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>"
           "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>"
           "</head><body><h1>Event " << eve.GetIdStr() << " " << eve.f_title << "</h1>"
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
                htm << " <a href='tfp:R" << per.f_ref_id
                    << "'><img src=memory:ref.png></a>";
            }
            recIdVec indIDs = per.GetIndividualIDs();
            for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
                htm << " <a href='tfpc:MR" << indIDs[j]
                    << "'><img src=memory:fam.png></a>";
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
