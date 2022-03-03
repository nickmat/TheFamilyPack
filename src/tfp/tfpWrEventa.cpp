/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Eventa's.
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

#include <rec/recEvent.h>
#include <rec/recEventa.h>
#include <rec/recFamily.h>
#include <rec/recIndividual.h>
#include <rec/recPersona.h>

static wxString GetSexClassPer( idt perID )
{
    return tfpGetSexClass( recPersona::GetSex( perID ) );
}

static wxString DisplayFamilyConclusions( const recEventa& ea, const wxString& extdb )
{
    wxString htm;
    recFamilyEventaVec feas = ea.GetFamilyEventas( extdb );
    htm <<
        "<table class='data'>\n"
        "<tr>\n<th>ID</th><th>Relationship</th><th>Names</th><th>Confidence</th><th>Note</th>\n</tr>\n"
    ;
    for( size_t i = 0 ; i < feas.size() ; i++ ) {
        recFamily fam(feas[i].FGetFamID(), extdb );
        htm << 
            "<tr><td><a href='tfp:F" << fam.FGetID() <<
            "'><b>" << fam.GetIdStr() <<
            "</b></a></td><td>Union</td><td>"
        ;

        if( fam.FGetHusbID() ) {
            htm << recIndividual::GetDescriptionStr( fam.FGetHusbID(), extdb );
            if( fam.FGetWifeID() ) {
                htm << "<br>";
            }
        }
        if( fam.FGetWifeID() ) {
            htm << recIndividual::GetDescriptionStr( fam.FGetWifeID(), extdb );
        }
        htm <<
            "</td><td>" << feas[i].FGetConf() <<
            "</td><td>" << feas[i].FGetNote() <<
            "</td></tr>\n"
        ;
    }
    recFamilyIndEventaVec fieas = ea.GetFamilyIndEventas( extdb );
    for( size_t i = 0 ; i < fieas.size() ; i++ ) {
        recFamilyIndividual fi(fieas[i].FGetFamIndID());
        htm << 
            "<tr><td><a href='tfp:F" << fi.FGetFamID() <<
            "'><b>" << recFamily::GetIdStr( fi.FGetFamID() ) <<
            "</b></a></td><td>Child</td><td>"
            << recIndividual::GetDescriptionStr( fi.FGetIndID(), extdb ) <<
            "</td><td>" << fieas[i].FGetConf() <<
            "</td><td>" << fieas[i].FGetNote() <<
            "</td></tr>\n"
        ;

    }
    htm << "</table>\n";
    return htm;
}

static wxString DisplayConclusions( const recEventa& er, const wxString& extdb )
{
    idt erID = er.FGetID();
    wxString htm;
    recIdVec eveIDs = er.GetLinkedEventIDs( extdb );
    if( eveIDs.size() ) {
        htm <<
            "<table class='data'>\n"
            "<tr>\n<th>Event ID</th><th>Title</th></tr>\n"
        ;
        for( size_t i = 0 ; i < eveIDs.size() ; i++ ) {
            idt eID = eveIDs[i];
            htm << "<tr>\n<td><a href='tfp:E" << eID << "'><b>"
                << recEvent::GetIdStr( eID ) << "</b></a></td>\n<td>"
                << recEvent::GetTitle( eID, extdb ) <<
                "</td>\n</tr>\n"
            ;
        }
        htm << "</table>\n";
    } else {
        // There is no matching Event, so create opportunity to add one
        // with "Create matching Event" button.
        htm <<
            "<table class='data'>\n"
            "<tr>\n<th>Event</th><th>Title</th></tr>\n"
            "<tr>\n<td><a href='tfpe:cE" << erID <<
            "'><img src='memory:blank.png' width='80' height='20' alt='Add Event'></a>"
            "</td>\n<td>" << recEventa::GetTitle( erID, extdb ) <<
            "</td>\n</tr>\n"
            "</table>\n"
        ;
    }
    return htm;
}


wxString tfpWriteEventaPage( idt erID, const wxString& extdb )
{
    wxString htm;
    if( erID == 0 ) return wxEmptyString;
    recEventa er( erID, extdb );
    recEventTypeGrp grp = er.GetTypeGroup( extdb );
    idt refID = er.FGetRefID();

    htm <<
        tfpWrHeadTfp( "Eventa " + er.GetIdStr() ) <<
        "<h1>Eventa " << er.GetIdStr() << ": " << er.FGetTitle() << "</h1>\n"
        "<table class='data'>\n<tr>\n<td>"
    ;
    if( er.FGetDate1ID() ) {
        htm <<
            "<b><a href='tfpi:D" << er.FGetDate1ID() <<
            "'>Date</a>: </b>" << er.GetDateStr( extdb )
        ;
    } else {
        htm << "<b>Date:</b>";
    }
    htm << "</td>\n</tr>\n<tr>\n<td>";
    if( er.FGetPlaceID() ) {
        htm <<
            "<b><a href='tfpi:P" << er.FGetPlaceID() <<
            "'>Place</a>: </b>" << er.GetAddressStr( extdb )
        ;
    } else {
        htm << "<b>Place:</b>";
    }
    htm <<
        "</td>\n</tr>\n<tr>\n"
        "<td><b>Note: </b>" << er.FGetNote() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b>Group:</b> " << recEventType::GetGroupStr( er.FGetTypeID(), extdb ) <<
        " <b>Type:</b> " << er.GetTypeStr( extdb ) << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b><a href='tfp:R" << refID <<
        "'>Reference: " << recReference::GetIdStr( refID ) <<
        "</a></b> " << recReference::GetTitle( refID, extdb ) << "</td>\n"
        "</tr>\n</table>\n"
    ;

    recEventaPersonaVec eps = er.GetEventaPersonas( extdb );
    if( !eps.empty() ) {
        htm <<
            "<table class='data'>\n<tr>\n"
            "<th>Role</th><th>ID</th><th>Persona</th><th>Note</th>"
            "<th>Individuals</th></tr>\n"
        ;
        for( size_t i = 0 ; i < eps.size() ; i++ ) {
            recPersona per( eps[i].FGetPerID() );
            recIdVec indIDs = per.GetIndividualIDs( extdb );
            htm <<
                "<tr>\n<td>" <<
                recEventTypeRole::GetName( eps[i].FGetRoleID(), extdb ) <<
                "</td>\n<td><b><a href='tfp:Pa" << recGetStr( per.FGetID() ) <<
                "'>" << per.GetIdStr() <<
                "</a></b></td>\n<td class='" << GetSexClassPer( per.FGetID() ) <<
                "'>" << per.GetNameStr( extdb ) <<
                "</td>\n<td>" << eps[i].FGetNote() <<
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

    if( grp == recEventTypeGrp::fam_relation ) {
        htm << DisplayFamilyConclusions( er, extdb );
    } else {
        htm << DisplayConclusions( er, extdb );
    }

    htm << tfpWrTailTfp();
    return htm;
}

// End of src/tfp/tfpWrEventa.cpp Source
