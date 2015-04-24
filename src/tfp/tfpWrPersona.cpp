/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrPersona.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen for a Persona record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     1 March 2015
 * Copyright:   Copyright (c) 2015, Nick Matthews.
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

#include <rec/recEventa.h>
#include <rec/recIndividual.h>
#include <rec/recPersona.h>

wxString tfpWritePersonaPage( idt perID )
{
    wxString htm;
    recPersona per( perID );

    htm <<
        tfpWrHeadTfp( "Persona " + per.GetIdStr() ) <<

        // Persona record
        "<table class='data'>\n<tr>\n"
        "<th colspan='2'>Persona's Details</th>\n</tr>\n<tr>\n"
        "<td>Name:</td>\n<td class='subject " << tfpGetSexClass( per.FGetSex() ) <<
        "'>" << per.GetNameStr() <<
        "</td>\n</tr>\n<tr>\n"
        "<td colspan='2'>ID: <b>" << per.GetIdStr() <<
        "</b> Sex: <b>" << recGetSexStr( per.FGetSex() ) <<
        "</b></td>\n</tr>\n<tr>\n"
        "<td>Note:</td><td>" << per.FGetNote() << "</td>\n</tr>\n<tr>\n"
        "<td><b><a href='tfp:R" << per.FGetRefID() <<
        "'>" << recReference::GetIdStr( per.FGetRefID() ) <<
        "</a></b></td><td>" << recReference::GetTitle( per.FGetRefID() ) <<
        "</td></tr></table>\n"
    ;
    // Individual Links
    recIdVec indIDs = per.GetIndividualIDs();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='2'>Individual Links</th>";
    for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
        htm << "</tr>\n<tr>\n"
            "<td><b><a href='tfp:I" << indIDs[i] <<
            "'>" << recIndividual::GetIdStr( indIDs[i] ) <<
            "</a></b></td><td class='" << tfpGetIndSexClass( indIDs[i] ) <<
            "'>" << recIndividual::GetDescriptionStr( indIDs[i] ) <<
            "</td>";
    }
    htm << "</tr>\n</table>\n";
    // Names
    recNameVec names = per.ReadNames();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='3'>Names</th>";
    for( size_t i = 0 ; i < names.size() ; i++ ) {
        htm << "</tr>\n<tr>\n"
            "<td><b><a href='tfpi:N" << names[i].FGetID() <<
            "'>" << names[i].GetIdStr() <<
            "</a></b></td><td>" << recNameStyle::GetStyleStr( names[i].FGetTypeID() ) <<
            "</td><td>" << names[i].GetNameStr() <<
            "</td>";
    }
    htm << "</tr>\n</table>\n";

    // Eventa
    recEventaPersonaVec eps = per.ReadEventaPersonas();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='4'>Eventa</th>\n";
    for( size_t i = 0 ; i < eps.size() ; i++ ) {
        idt eaID = eps[i].FGetEventaID();
        recEventa ea( eaID );
        wxString cat1, cat2, dStr, pStr;
        if( ea.FGetDate1ID() || ea.FGetPlaceID() ) {
            cat1 = "<br>\n";
        }
        if( ea.FGetDate1ID() && ea.FGetPlaceID() ) {
            cat2 = ", ";
        }
        if( ea.FGetDate1ID() ) {
            dStr <<
                "<a href='tfpi:D" << ea.FGetDate1ID() <<
                "'>" << ea.GetDateStr() <<
                "</a>"
            ;
        }
        if( ea.FGetPlaceID() ) {
            pStr <<
                "<a href='tfpi:P" << ea.FGetPlaceID() <<
                "'>" << ea.GetAddressStr() <<
                "</a>"
            ;
        }
        htm <<
            "</tr>\n<tr>\n" <<
            "<td><b><a href='tfp:Ea" << eaID <<
            "'>" << ea.GetIdStr() <<
            "</a></b></td>\n<td>" << ea.GetTypeStr() <<
            ":</td>\n<td>" << recEventTypeRole::GetName( eps[i].FGetRoleID() ) <<
            "</td><td>" << ea.FGetTitle() <<
            cat1 << dStr << cat2 << pStr
        ;
        if( !ea.FGetNote().IsEmpty() ) {
            htm << "<br>\n" << eps[i].FGetNote();
        }
        htm << "</td>\n";
    }
    htm << "</tr>\n</table>\n" << tfpWrTailTfp();

    return htm;
}

// End of src/tfp/tfpWrPersona.cpp Source
