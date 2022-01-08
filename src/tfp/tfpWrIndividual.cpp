/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen for an Individual function.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
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
#include <rec/recMedia.h>
#include <rec/recName.h>
#include <rec/recPersona.h>
#include <rec/recReference.h>

wxString tfpWriteIndividualPage( idt indID )
{
    wxString htm;
    recIndividual ind( indID );
    if( ind.FGetID() == 0 ) return htm;
    recFamilyVec parents = recFamily::GetParentList( indID );
    recFamilyVec families = recFamily::GetFamilyList( indID );
    wxASSERT( families.size() > 0 );
    recIndividual spouse;
    bool single = ( families.size() > 1 || families[0].GetSpouseID( indID ) ||
        families[0].GetChildCount() ) ? false : true;

    htm << 
        tfpWrHeadTfp( ind.GetIdStr(), "tab" ) <<

        // Individual record
        "<table class='data'>\n<tr>\n"
        "<th colspan='2'>Individual's Details</th>\n</tr>\n<tr>\n"
        "<td>Name:</td><td class='subject " << tfpGetIndSexClass( ind.FGetID() ) <<
        "'><a href='tfp:F" << ind.FGetFamID() <<
        "'>" << ind.FGetName() <<
        "</a> " << ind.FGetEpitaph() <<
        " <a href='tfpc:MR" << indID << "'><img src=memory:fam.png></a>\n"
    ;
    if( parents.size() ) {
        htm << "&nbsp;<a href='tfp:CP" << indID
            << "'><img src='memory:pcht.png' alt='Pedigree'></a>\n";
    }
    if( ! single ) {
        htm << "&nbsp;<a href='tfp:CD" << indID
            << "'><img src='memory:dcht.png' alt='Descendants'></a>\n";
    }
    htm <<
        "</td></tr>\n<tr>\n"
        "<td colspan='2'>ID: <b>" << ind.GetIdStr() <<
        "</b> Sex: <b>" << recGetSexStr( ind.FGetSex() ) <<
        "</b> Privacy: <b>" << ind.FGetPrivacy() << "</b></td>\n"
        "</tr>\n<tr>\n"
        "<td>Note:</td><td><pre>" << ind.FGetNote() << "</pre></td>\n"
        "</tr>\n</table>\n"
    ;
    // Names
    recNameVec names = ind.GetNames();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='3'>Names</th>\n";
    for( size_t i = 0 ; i < names.size() ; i++ ) {
        htm << "</tr>\n<tr>\n"
            "<td><b><a href='tfpi:N" << names[i].FGetID() <<
            "'>" << names[i].GetIdStr() <<
            "</a></b></td><td>" << recNameStyle::GetStyleStr( names[i].FGetTypeID() ) <<
            "</td><td>" << names[i].GetNameStr() <<
            "</td>";
    }
    // Parents
    if( parents.size() ) {
        htm <<
            "</tr>\n<tr>\n"
            "<th colspan='3'>Parents</th>\n"
        ;
    }
    for( size_t i = 0 ; i < parents.size() ; i++ ) {
        idt hID = parents[i].FGetHusbID();
        if( hID != 0 ) {
            htm <<
                "</tr>\n<tr>\n"
                "<td><b>" << recIndividual::GetIdStr( hID ) <<
                "</b></td>\n<td>Father:"
                "</td>\n<td class='" << tfpGetIndSexClass( hID ) <<
                "'><a href='tfp:I" << hID <<
                "'>" << recIndividual::GetName( hID ) <<
                "</a> " << recIndividual::GetEpitaph( hID ) <<
                " <a href='tfpc:MR" << hID <<
                "'><img src=memory:fam.png></a></td>\n"
            ;
        }
        idt wID = parents[i].FGetWifeID();
        if( wID != 0 ) {
            htm <<
                "</tr>\n<tr>\n"
                "<td><b>" << recIndividual::GetIdStr( wID ) <<
                "</b></td>\n<td>Mother:"
                "</td>\n<td class='" << tfpGetIndSexClass( wID ) <<
                "'><a href='tfp:I" << wID <<
                "'>" << recIndividual::GetName( wID ) <<
                "</a> " << recIndividual::GetEpitaph( wID ) <<
                " <a href='tfpc:MR" << wID <<
                "'><img src=memory:fam.png></a></td>\n"
            ;
        }
    }
    for( size_t i = 0 ; i < families.size() ; i++ ) {
        idt famID = families[i].FGetID();
        idt spouseID = families[i].GetSpouseID( indID );
        recIndividualVec children = recIndividual::GetChildren( famID );
        if( spouseID == 0 && children.size() == 0 ) {
            // Family is single individual
            continue;
        }
        spouse.ReadID( spouseID );

        htm <<
            "</tr>\n<tr>\n"
            "<th colspan='3'>Family " << i+1 << "</th>\n"
            "</tr>\n<tr>\n"
        ;
        // Spouse name
        if( spouseID ) {
            htm <<
                "<td><b><a href='tfp:I" << spouseID <<
                "'>" << recIndividual::GetIdStr( spouseID ) <<
                "</a></b></td>\n<td><a href='tfp:F" << famID <<
                "'>Spouse " << i+1 << "</a>:</td>\n"
                "<td class='" << tfpGetIndSexClass( spouseID ) <<
                "'><a href='tfp:I" << spouseID <<
                "'>" << spouse.FGetName() <<
                "</a></b> " << spouse.f_epitaph <<
                " <a href='tfpc:MR" << spouseID <<
                "'><img src=memory:fam.png></a></td>\n"
            ;
        }
        // Union event (marriage)
        idt marEvID = families[i].GetUnionEvent();
        if( marEvID != 0 ) {
            htm <<
                "</tr>\n<tr>\n" <<
                "<td><b><a href='tfp:E" << marEvID <<
                "'>" << recEvent::GetIdStr( marEvID ) <<
                "</a></b></td>\n<td>" << recEvent::GetTypeStr( marEvID ) <<
                ":</td>\n<td><b>" << recEvent::GetDetailStr( marEvID ) <<
                "</b></td>\n"
            ;
        }
        // Children
        for( size_t j = 0 ; j < children.size() ; j++ ) {
            idt cID = children[j].FGetID();
            htm <<
                "</tr>\n<tr>\n" <<
                "<td><b><a href='tfp:I" << cID <<
                "'>" << children[j].GetIdStr() <<
                "</a></b></td>\n"
            ;
            if( j == 0 ) {
                htm <<
                    "<td rowspan='" << children.size() <<
                    "'>Children:</td>\n"
                ;
            }
            htm <<
                "<td class='" << tfpGetIndSexClass( cID ) <<
                "'><a href='tfp:I" << cID <<
                "'>" << children[j].FGetName() <<
                "</a> " << children[j].FGetEpitaph() <<
                " <a href='tfpc:MR" << cID <<
                "'><img src=memory:fam.png></a></td>\n"
            ;
        }
    }
    htm << "</tr>\n</table>\n";

    // All Events
    recIndEventVec ies = ind.GetEvents();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='4'>Events</th>\n";
    for( size_t i = 0 ; i < ies.size() ; i++ ) {
        idt eveID = ies[i].FGetEventID();
        recEvent eve( eveID );
        wxString cat1, cat2, dStr, pStr;
        if( eve.FGetDate1ID() || eve.FGetPlaceID() ) {
            cat1 = "<br>\n";
        }
        if( eve.FGetDate1ID() && eve.FGetPlaceID() ) {
            cat2 = ", ";
        }
        if( eve.FGetDate1ID() ) {
            dStr <<
                "<a href='tfpi:D" << eve.FGetDate1ID() <<
                "'>" << eve.GetDateStr() <<
                "</a>"
            ;
        }
        if( eve.FGetPlaceID() ) {
            pStr <<
                "<a href='tfpi:P" << eve.FGetPlaceID() <<
                "'>" << eve.GetAddressStr() <<
                "</a>"
            ;
        }
        htm <<
            "</tr>\n<tr>\n" <<
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << eve.GetIdStr() <<
            "</a></b></td>\n<td>" << eve.GetTypeStr() <<
            ":</td>\n<td>" << recEventTypeRole::GetName( ies[i].FGetRoleID() ) <<
            "</td><td>" << eve.FGetTitle() <<
            cat1 << dStr << cat2 << pStr
        ;
        if( !eve.FGetNote().IsEmpty() ) {
            htm << "<br>\n" << ies[i].FGetNote();
        }
        htm << "</td>\n";
    }
    htm << "</tr>\n</table>\n";

    // Get linked Eventas
    wxSQLite3ResultSet eSet = ind.GetEventaSet();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='4'>Eventas</th>\n";
    while( eSet.NextRow() ) {
        idt erID = GET_ID( eSet.GetInt64( 0 ) );
        recEventa er( erID );
        idt roleID = GET_ID( eSet.GetInt64( 1 ) );
        idt refID = er.FGetRefID();

        wxString cat1, cat2, dStr, pStr;
        if( er.FGetDate1ID() || er.FGetPlaceID() ) {
            cat1 = "<br>\n";
        }
        if( er.FGetDate1ID() && er.FGetPlaceID() ) {
            cat2 = ", ";
        }
        if( er.FGetDate1ID() ) {
            dStr <<
                "<a href='tfpi:D" << er.FGetDate1ID() <<
                "'>" << er.GetDateStr() <<
                "</a>"
            ;
        }
        if( er.FGetPlaceID() ) {
            pStr <<
                "<a href='tfpi:P" << er.FGetPlaceID() <<
                "'>" << er.GetAddressStr() <<
                "</a>"
            ;
        }
        htm <<
            "</tr>\n<tr>\n" <<
            "<td><b><a href='tfp:R" << refID <<
            "'>" << recReference::GetIdStr( refID ) <<
            "</a>: <a href='tfp:Ea" << erID <<
            "'>" << er.GetIdStr() <<
            "</b></td>\n<td>" << er.GetTypeStr() <<
            ":</td>\n<td>" << recEventTypeRole::GetName( roleID ) <<
            "</td><td>" << er.FGetTitle() <<
            cat1 << dStr << cat2 << pStr
        ;
        if( er.FGetNote().size() ) {
            htm << "<br>\n" << er.FGetNote();
        }
        htm << "</td>\n";
    }
    htm << "</tr>\n</table>\n";


    // List all References for linked Personas
    eSet = ind.GetReferenceSet();
    htm <<
        "<table class='data'>\n<tr>\n"
        "<th colspan='2'>Reference Links</th>\n";
    while( eSet.NextRow() ) {
        idt refID = GET_ID( eSet.GetInt64( 0 ) );
        htm <<
            "</tr>\n<tr>\n" <<
            "<td><b><a href='tfp:R" << refID <<
            "'>" << recReference::GetIdStr( refID ) <<
            "</a></b></td>\n<td>" << eSet.GetAsString( 1 ) <<
            "</td>\n"
        ;
    }
    htm << "</tr>\n</table>\n";

    recIdVec mes = ind.FindEvents( recEventTypeRole::ROLE_Media_Subject );
    bool started = false;
    if ( !mes.empty() ) {
        htm << "<table class='media'>\n";
        for ( idt meID : mes ) {
            recIdVec refs = recEvent::GetReferenceIDs( meID );
            recIndividualEvent ie( 0 );
            ie.Find( indID, meID, recEventTypeRole::ROLE_Media_Subject );
            for ( idt refID : refs ) {
                recIdVec medIDs = recReference::GetMediaList( refID );
                if ( !medIDs.empty() ) {
                    recMedia med( medIDs[0] );
                    wxString fn = tfpGetMediaDataFile( med.FGetDataID(), med.FGetAssID() );
                    wxString title = ie.FGetNote();
                    if ( title.empty() ) {
                        title = med.FGetTitle();
                    }
                    if ( started ) {
                        htm << "<tr>\n<td colspan='3' class='gap'>&nbsp;</td>\n</tr>\n";
                    } else {
                        started = true;
                    }
                    htm << "<tr>\n<td rowspan='2'>";
                    if( fn.empty() ) {
                        htm << med.GetDataIdStr() << " Not Found.";
                    }
                    else {
                        htm << "<a href = 'tfpv:M" << med.FGetID()
                            << "'><img src='" << fn << "' alt='' height='200' /></a>";
                    }
                    htm << 
                        "</td><td><a href='tfp:M" << med.FGetID()
                        << "'><b>" << med.GetIdStr()
                        << "</b></a></td>\n<td class='title'>" << title
                        << "</td>\n</tr>\n"
                        "<tr>\n<td colspan='2'>" << med.FGetNote()
                        << "</td>\n</tr>\n"
                    ;
                }
            }
        }
        htm << "</table>\n";
    }

    htm << tfpWrTailTfp();

    return htm;
}


// End of tfpWrIndividual.cpp Source
