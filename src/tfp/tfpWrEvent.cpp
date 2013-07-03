/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrEvent.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Events.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010-2013, Nick Matthews.
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
#include <rec/recEventRecord.h>

//#include <rg/rgCompareEvent.h>

#include "tfpWr.h"

wxString tfpWriteEventPage( idt eventID, rgCompareEvent* ce )
{
//    ce->Reset( eventID );
    wxString htm;
    recEvent eve(eventID);
    if( eve.f_id == 0 ) return wxEmptyString;

    htm << 
#if 0
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Event " << eve.GetIdStr() << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
#endif
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
    htm <<
        "</td>\n</tr>\n<tr>\n"
        "<td><b>Note: </b>" << eve.f_note << "</td>\n</tr>\n"
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
                << "</td>\n<td class='" << GetSexClass( ind.FGetID() ) 
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

    recEveEveRecordVec eers = eve.GetEveEveRecords();
    if( eers.size() ) {
        htm << 
            "<table class='data'>\n<tr>\n"
            "<th>Record</th>\n<th>Conf</th>\n<th>Title</th>\n</tr>\n"
        ;
        for( size_t i = 0 ; i < eers.size() ; i++ ) {
            idt eerID = eers[i].FGetEventRecID();
            htm << 
                "<tr>\n"
                "<td><b><a href='tfp:ER" << eerID << 
                "'>" <<  recEventRecord::GetIdStr( eerID ) << "</a></b></td>\n"
                "<td>" << eers[i].FGetConf() << "</td>\n"
                "<td>" << recEventRecord::GetTitle( eerID ) << "</td>\n"
                "</tr>\n"
            ;
        }
        htm << "</table>\n";
    }

    //htm << ce->GetRefEventsTable()
    //    << ce->GetRefDatesTable()
    //    << ce->GetRefPlacesTable();

    htm << tfpWrTailTfp();

    return htm;
}

// End of tfpWrEvent.cpp Source
