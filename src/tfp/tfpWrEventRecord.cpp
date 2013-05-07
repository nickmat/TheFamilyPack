/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrEventRecord.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare EventRecord's.
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
#include <rec/recFilterEvent.h>
#include <rec/recPersona.h>
#include <rec/recIndividual.h>

#include <rg/rgCompareEvent.h>

#include "tfpWr.h"

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

wxString tfpWriteEventRecordIndex()
{
    wxSQLite3Table result = recEventRecord::GetTitleList();
    size_t size = (size_t) result.GetRowCount();

    wxString htm;
    htm <<
        tfpWrHeadTfp( "Event Record List" ) <<
        "<h1>Event Record Index</h1>"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;

    for( size_t i = 0 ; i < size ; i++ ) {
        result.SetRow( i );
        htm << "<tr>\n<td><a href='tfp:ER"
            << result.GetAsString( 0 )
            << "'><b>ER"
            << result.GetAsString( 0 )
            << "</b></a></td>\n<td>"
            << result.GetAsString( 1 )
            << "</td>\n</tr>\n";
    }

    htm << "</table>\n" << tfpWrTailTfp();
    return htm;
}

wxString tfpWriteEventRecordPagedIndex( idt begCnt )
{
    int maxsize = recEvent::UserCount();
    if( maxsize <= tfpWR_PAGE_MAX ) {
        return tfpWriteEventIndex();
    }
    wxString pmenu = tfpWritePagedIndexMenu( begCnt, maxsize, "tfp:ER" );

    wxSQLite3Table result = recEventRecord::GetTitleList( begCnt, tfpWR_PAGE_MAX );
    size_t size = (size_t) result.GetRowCount();
    result.SetRow( 0 );
    idt beg = GET_ID( result.GetInt64( 0 ) );
    result.SetRow( size-1 );
    idt end = GET_ID( result.GetInt64( 0 ) );

    wxString htm;
    htm <<
        tfpWrHeadTfp( "Event Record List" ) <<
        "<h1>Reference Document Index from " << recEventRecord::GetIdStr( beg ) <<
        " to " << recEventRecord::GetIdStr( end ) <<
        "</h1>\n" << pmenu <<
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;
    for( size_t i = 0 ; i < size ; i++ ) {
        result.SetRow( i );
        htm << 
            "<tr><td><a href='tfp:ER" << result.GetAsString( 0 ) <<
            "'><b>ER" << result.GetAsString( 0 ) <<
            "</b></a></td><td> " << result.GetAsString( 1 ) <<
            "</td></tr>\n"
        ;
    }
    htm << 
        "</table>\n" << pmenu <<
        "<br>\n" << tfpWrTailTfp() 
    ;
    return htm;
}

wxString tfpWriteEventRecordPage( idt erID )
{
    wxString htm;
    if( erID == 0 ) return wxEmptyString;
    recEventRecord er(erID);
    idt refID = recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, erID );


    htm <<
        tfpWrHeadTfp( "Event Record " + er.GetIdStr() ) <<
        "<h1>Event Record " << er.GetIdStr() << ": " << er.FGetTitle() << "</h1>\n"
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

    recEventPersonaVec eps = er.GetEventPersonas();
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
                    "<a href='tfpe:EER" << e2 << "," << erID <<
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
    }

    htm << tfpWrTailTfp();
    return htm;
}

// End of src/tfp/tfpWrEventRecord.cpp Source
