/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Events.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
 * Copyright:   Copyright (c) 2010-2015, Nick Matthews.
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

#include <rec/recEvent.h>
#include <rec/recEventa.h>
#include <rec/recIndividual.h>
#include <rec/recPersona.h>

#include <rg/rgCompareEvent.h>

wxString tfpWriteEventPage( idt eventID, rgCompareEvent* ce )
{
    if( ce ) ce->Reset( eventID );
    wxString htm;
    recEvent eve(eventID);
    if( eve.f_id == 0 ) return wxEmptyString;

    htm <<
        tfpWrHeadTfp( "Event " + eve.GetIdStr() ) <<

        "<h1>Event " << eve.GetIdStr() << ": " << eve.f_title << "</h1>\n"
        "<table class='data'>\n"
        "<tr>\n<td>"
        "<b>Type:</b> " << eve.GetTypeStr() <<
        " &nbsp; <b>Group:</b> " << recEventType::GetGroupStr( eve.FGetTypeID() ) <<
        "</td>\n</tr>\n"
        "<tr>\n<td>"
    ;
    if( eve.FGetDate1ID() ) {
        htm <<
            "<b><a href='tfpi:D" << eve.FGetDate1ID() <<
            "'>Date</a>: </b>" << eve.GetDateStr()
        ;
    } else {
        htm << "<b>Date:</b>";
    }
    htm << "</td>\n</tr>\n<tr>\n<td>";
    if( eve.FGetPlaceID() ) {
        htm <<
            "<b><a href='tfpi:P" << eve.FGetPlaceID() <<
            "'>Place</a>: </b>" << eve.GetAddressStr()
        ;
    } else {
        htm << "<b>Place:</b>";
    }
    if( eve.FGetHigherID() ) {
        htm <<
            "</td>\n</tr>\n<tr>\n"
            "<td><b><a href='tfp:E" << eve.FGetHigherID() <<
            "'>Part of: " << recEvent::GetIdStr( eve.FGetHigherID() ) <<
            "</a></b> " << recEvent::GetTitle( eve.FGetHigherID() )
        ;
    }
    htm <<
        "</td>\n</tr>\n"
        "<tr>\n<td><b>Note: </b>" << eve.FGetNote() << "</td>\n</tr>\n"
        "<tr>\n<td><b>User Ref: </b>" << eve.FGetUserRef() << "</td>\n</tr>\n"
        "</table>\n"
    ;

    recIndEventVec ies = eve.GetIndividualEvents();
    if( !ies.empty() ) {
        htm << "<table class='data'>\n<tr>\n"
               "<th>Role</th>\n<th>Individual</th>\n<th>Note</th>\n</tr>\n";
        for( size_t i = 0 ; i < ies.size() ; i++ ) {
            recIndividual ind(ies[i].FGetIndID());
            htm
                << "<tr>\n<td>" << recEventTypeRole::GetName( ies[i].FGetRoleID() )
                << "</td>\n<td class='" << tfpGetIndSexClass( ind.FGetID() )
                << "'>\n<b><a href='tfp:I" << ind.FGetID()
                << "'>" << ind.FGetName()
                << "</a></b>"
               << " <a href='tfpc:MR" << ind.FGetID()
               << "'><img src='memory:fam.png' alt='Family'></a>"
               << "</td>\n<td>" << ies[i].f_note
               << " </td>\n</tr>\n"
           ;
        }
        htm << "</table>\n";
    }

    recEventEventaVec eers = eve.GetEventEventas();
    if( eers.size() ) {
        htm <<
            "<table class='data'>\n<tr>\n"
            "<th>Record</th>\n<th>Conf</th>\n<th>Title</th>\n</tr>\n"
        ;
        for( size_t i = 0 ; i < eers.size() ; i++ ) {
            idt eerID = eers[i].FGetEventaID();
            htm <<
                "<tr>\n"
                "<td><b><a href='tfp:Ea" << eerID <<
                "'>" <<  recEventa::GetIdStr( eerID ) << "</a></b></td>\n"
                "<td>" << eers[i].FGetConf() << "</td>\n"
                "<td>" << recEventa::GetTitle( eerID ) << "</td>\n"
                "</tr>\n"
            ;
        }
        htm << "</table>\n";
    }

    // List lower (included) events
    recEventVec es = eve.GetLowerEvents();
    if( es.size() ) {
        htm <<
            "<table class='data'>\n<tr>\n"
            "<th colspan='3'>Included Events</th>\n";
        for( size_t i = 0 ; i < es.size() ; i++ ) {
            wxString cat1, cat2, dStr, pStr;
            if( es[i].FGetDate1ID() || es[i].FGetPlaceID() ) {
                cat1 = "<br>\n";
            }
            if( es[i].FGetDate1ID() && es[i].FGetPlaceID() ) {
                cat2 = ", ";
            }
            if( es[i].FGetDate1ID() ) {
                dStr <<
                    "<a href='tfpi:D" << es[i].FGetDate1ID() <<
                    "'>" << es[i].GetDateStr() <<
                    "</a>"
                ;
            }
            if( es[i].FGetPlaceID() ) {
                pStr <<
                    "<a href='tfpi:P" << es[i].FGetPlaceID() <<
                    "'>" << es[i].GetAddressStr() <<
                    "</a>"
                ;
            }
            htm <<
                "</tr>\n<tr>\n" <<
                "<td><b><a href='tfp:E" << es[i].FGetID() <<
                "'>" << es[i].GetIdStr() <<
                "</a></b></td>\n<td>" << es[i].GetTypeStr() <<
                "</td><td>" << es[i].FGetTitle() <<
                cat1 << dStr << cat2 << pStr
            ;
            if( es[i].FGetNote().size() ) {
                htm << "<br>\n" << ies[i].FGetNote();
            }
            htm << "</td>\n";
        }
        htm << "</tr>\n</table>\n";
    }

    if( ce ) {
        htm <<
            ce->GetRefEventsTable() <<
            ce->GetRefDatesTable() <<
            ce->GetRefPlacesTable()
        ;
    } else {
        htm << "<p><a href='tfp:E^" << eventID << "'>Show Eventas</a></p>\n";
    }

    htm << tfpWrTailTfp();

    return htm;
}

// End of tfpWrEvent.cpp Source
