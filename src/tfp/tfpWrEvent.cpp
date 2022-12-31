/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Events.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
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

#include <rec/recEvent.h>
#include <rec/recEventa.h>
#include <rec/recIndividual.h>
#include <rec/recPersona.h>

#include <rg/rgCompareEvent.h>

wxString tfpWriteEventPage( idt eventID, TfpFrame& frame )
{
    const wxString& extdb = frame.GetDbName();
    rgCompareEvent& ce = frame.GetCompareEventData();
    wxString htm;
    recEvent eve( eventID, extdb );
    if( eve.FGetID() == 0 ) return htm;
    ce.Reset( eventID, extdb );

    htm <<
        tfpWrHeadTfp( "Event " + eve.GetIdStr() ) <<

        // Add a higher Event record here.

        "<table class='data'>\n"

        "<tr>\n<td class='status'>\n"
        "<b>Event: " << eve.GetIdStr() << "</b>"
        "</td>\n</tr>\n"

        "<tr>\n<td class='title'>\n" << eve.FGetTitle() << "\n</td>\n</tr>\n"
        "<tr>\n<td>"
        "<b>Type:</b> " << eve.GetTypeStr( extdb ) <<
        " &nbsp; <b>Group:</b> " << recEventType::GetGroupStr( eve.FGetTypeID(), extdb ) <<
        "</td>\n</tr>\n";

    if( eve.FGetDate1ID() ) {
        htm <<
            "<tr>\n<td>"
            "<b><a href='tfpi:D" << eve.FGetDate1ID() <<
            "'>Date</a>: </b>" << eve.GetDateStr( extdb ) <<
            "</td>\n</tr>\n"
        ;
    }
    if( eve.FGetPlaceID() ) {
        htm <<
            "<tr>\n<td>"
            "<b><a href='tfpi:P" << eve.FGetPlaceID() <<
            "'>Place</a>: </b>" << eve.GetAddressStr( extdb ) <<
            "</td>\n</tr>\n"
        ;
    }
    if( !eve.FGetNote().empty() ) {
        htm <<
            "<tr>\n<td><b>Note: </b>" << eve.FGetNote() << "</td>\n</tr>\n"
        ;
    }
    if( !eve.FGetUserRef().empty() ) {
        htm <<
            "<tr>\n<td><b>User Ref: </b>" << eve.FGetUserRef() << "</td>\n</tr>\n"
        ;
    }
    htm << "</table>\n";


    recIndEventVec ies = eve.GetIndividualEvents( extdb );
    for( auto& ie : ies ) {
        idt indID = ie.FGetIndID();
        wxASSERT( indID != 0 );
        recIndividual ind( indID, extdb );
        htm << "<table class='data'>";
        if( ie.FGetHigherID() != 0 ) {
            recIndividualEvent hi_ie( ie.FGetHigherID(), extdb );
            std::string hi_eaStr = recEvent::PrefixId( hi_ie.FGetEventID() );
            htm <<
                "\n<th colspan='4'>Higher Linked Individual Event</th>"
                "\n<tr><td>\n" << ind.FGetName() <<
                "\n</td><td>\n" << recEventTypeRole::GetName( hi_ie.FGetRoleID(), extdb ) <<
                "\n</td><td>\n" << hi_ie.FGetNote() <<
                "\n</td><td>\n<a href='tfp:" << hi_eaStr << "'><b>" << hi_eaStr << "</b></a>"
                "\n</td></tr>\n"
                ;
        }
        htm <<
            "\n<tr><td  colspan='4' class='status'>\n"
            "<b>Individual: " << ind.PrefixId() << "</b>"
            "\n</td></tr>\n"
            "\n<tr><td class='" << tfpGetIndSexClass( indID, Sex::unknown, extdb ) << "'>\n"
            "<b><a href='tfp:" << ind.PrefixId() << "'>" << ind.FGetName() <<
            "</a></b> " << ind.FGetEpitaph() << " <a href='tfpc:MR" << indID <<
            "'><img src='memory:fam.png' alt='Family'></a>"
            "\n</td><td>\n" << recEventTypeRole::GetName( ie.FGetRoleID(), extdb ) <<
            "\n</td><td>\n" << ie.FGetNote() <<
            "\n</td><td>\n"
            "\n</td></tr>\n"
            ;

        recIndEventVec low_ies = ie.GetLowerIndEvents( extdb );
        if( !low_ies.empty() ) {
            htm << "<th colspan='4'>Linked Individual Events</th>\n";
        }
        for( auto& low_ie : low_ies ) {
            if( low_ie.FGetIndID() != indID ) {
                htm <<
                    "<tr><td colspan='4'>\nERROR! linked to individual " <<
                    recIndividual::PrefixId( low_ie.FGetIndID() ) <<
                    "\n</td></tr>\n"
                    ;
                continue;
            }
            std::string low_eaStr = recEvent::PrefixId( low_ie.FGetEventID() );
            htm <<
                "\n<tr><td>\n" << ind.FGetName() <<
                "\n</td><td>\n" << recEventTypeRole::GetName( low_ie.FGetRoleID(), extdb ) <<
                "\n</td><td>\n" << low_ie.FGetNote() <<
                "\n</td><td>\n<a href='tfp:" << low_eaStr << "'><b>" << low_eaStr << "</b></a>"
                "\n</td></tr>\n"
                ;
        }

        htm << "</table>\n";
    }

    htm << "<hr>\n";

    recEventEventaVec eeas = eve.GetEventEventas( extdb );
    if( eeas.size() ) {
        htm <<
            "<table class='data'>\n<tr>\n"
            "<th colspan='2'>Reference Document</th>\n"
            "<th colspan='2'>Eventa</th>\n"
            "<th>Conf</th>\n</tr>\n"
        ;
        for( size_t i = 0 ; i < eeas.size() ; i++ ) {
            idt eaID = eeas[i].FGetEventaID();
            idt refID = recEventa::GetRefID( eaID, extdb );
            wxString refTitle = recReference::GetTitle( refID, extdb );
            htm <<
                "<tr>\n"
                "<td><b><a href='tfp:R" << refID <<
                "'>" << recReference::GetIdStr( refID ) << "</a></b></td>\n"
                "<td>" << refTitle << "</td>\n"
                "<td><b><a href='tfp:Ea" << eaID <<
                "'>" <<  recEventa::GetIdStr( eaID ) << "</a></b></td>\n"
                "<td>" << recEventa::GetTitle( eaID, extdb ) << "</td>\n"
                "<td>" << eeas[i].FGetConf() << "</td>\n"
                "</tr>\n"
            ;
        }
        htm << "</table>\n";
    }

    // List lower (included) events
    recEventVec es = eve.GetLowerEvents( extdb );
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
                "</a></b></td>\n<td>" << es[i].GetTypeStr( extdb ) <<
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

    htm << ce.GetRefDatesTable() << ce.GetRefPlacesTable() << tfpWrTailTfp();

    return htm;
}

// End of tfpWrEvent.cpp Source
