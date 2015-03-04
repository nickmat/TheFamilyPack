/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Eventum's.
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

wxString GetSexClassPer( idt perID )
{
    Sex sex = recPersona::GetSex( perID );
    switch( sex ) {
    case SEX_Male:
        return "male";
    case SEX_Female:
        return "fem";
    }
    return "neut";
}

wxString tfpWriteEventumPage( idt erID )
{
    wxString htm;
    if( erID == 0 ) return wxEmptyString;
    recEventum er(erID);
    idt refID = recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, erID );


    htm <<
        tfpWrHeadTfp( "Eventum " + er.GetIdStr() ) <<
        "<h1>Eventum " << er.GetIdStr() << ": " << er.FGetTitle() << "</h1>\n"
        "<table class='data'>\n<tr>\n<td>"
    ;
    if( er.FGetDate1ID() ) {
        htm <<
            "<b><a href='tfpi:D" << er.FGetDate1ID() <<
            "'>Date</a>: </b>" << er.GetDateStr()
        ;
    } else {
        htm << "<b>Date:</b>";
    }
    htm << "</td>\n</tr>\n<tr>\n<td>";
    if( er.FGetPlaceID() ) {
        htm <<
            "<b><a href='tfpi:P" << er.FGetPlaceID() <<
            "'>Place</a>: </b>" << er.GetAddressStr()
        ;
    } else {
        htm << "<b>Place:</b>";
    }
    htm <<
        "</td>\n</tr>\n<tr>\n"
        "<td><b>Note: </b>" << er.FGetNote() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b>Group:</b> " << recEventType::GetGroupStr( er.FGetTypeID() ) <<
        " <b>Type:</b> " << er.GetTypeStr() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b><a href='tfp:R" << refID <<
        "'>Reference: " << recReference::GetIdStr( refID ) <<
        "</a></b> " << recReference::GetTitle( refID ) << "</td>\n"
        "</tr>\n</table>\n"
    ;

    recEventumPersonaVec eps = er.GetEventumPersonas();
    if( eps.size() ) {
        htm <<
            "<table class='data'>\n<tr>\n"
            "<th>Role</th><th>ID</th><th>Persona</th><th>Note</th>"
            "<th>Individuals</th></tr>\n"
        ;
        for( size_t i = 0 ; i < eps.size() ; i++ ) {
            recPersona per( eps[i].FGetPerID() );
            recIdVec indIDs = per.GetIndividualIDs();
            htm <<
                "<tr>\n<td>" <<
                recEventTypeRole::GetName( eps[i].FGetRoleID() ) <<
                "</td>\n<td>" << per.GetIdStr() <<
                "</td>\n<td class='" << GetSexClassPer( per.FGetID() ) <<
                "'>" << per.GetNameStr() <<
                "</td>\n<td>" << eps[i].f_note <<
                " </td>\n<td><b>"
            ;
            for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
                if( j > 0 ) {
                    htm << ", ";
                }
                htm <<
                    "<a href='tfp:I" << indIDs[j] <<
                    "'>" << recIndividual::GetIdStr( indIDs[j] ) <<
                    "</a>"
                ;
            }
            htm << "</b></td>\n</tr>\n";
        }
        htm << "</table>\n";
    }

    recCheckIdVec ces = er.FindCheckedMatchingEvents();
    if( ces.size() ) {
        htm <<
            "<table class='data'>\n"
            "<tr>\n<th>Direct Link</th><th>Indirect Link</th><th>Title</th></tr>\n"
        ;
        for( size_t i = 0 ; i < ces.size() ; i++ ) {
            idt e1 = ces[i].GetFirstID();
            idt e2 = ces[i].GetSecondID();
            idt eID = ( e1 ) ? e1 : e2;
            wxString eIdStr = recEvent::GetIdStr( eID );
            htm << "<tr>\n<td>";
            if( e1 ) {
                htm <<
                    "<a href='tfp:E" << e1 <<
                    "'><b>" << eIdStr << "</b></a>"
                ;
            } else {
                htm <<
                    "<a href='tfpe:cEER" << e2 << "," << erID <<
                    "'><img src='memory:blank.png' width='80' height='20' alt='Add Direct Link'></a>"
                ;
            }
            htm << "</td>\n<td>";
            if( e2 ) {
                htm <<
                    "<a href='tfp:E" << e2 <<
                    "'><b>" << eIdStr << "</b></a>"
                ;
            }
            htm <<
                "</td>\n<td>" << recEvent::GetTitle( eID ) <<
                "</td>\n</tr>\n"
            ;
        }
        htm << "</table>\n";
    } else {
        // There is no matching Event, see if we need one.
        // Get list of all Individuals linked to the linked Persona.
        htm <<
            "<table class='data'>\n"
            "<tr>\n<th>Event</th><th>Title</th></tr>\n"
            "<tr>\n<td><a href='tfpe:cE" << erID <<
            "'><img src='memory:blank.png' width='80' height='20' alt='Add Event'></a>"
            "</td>\n<td>" << recEventum::GetTitle( erID ) <<
            "</td>\n</tr>\n"
            "</table>\n"
        ;
    }

    htm << tfpWrTailTfp();
    return htm;
}

// End of src/tfp/tfpWrEventa.cpp Source
