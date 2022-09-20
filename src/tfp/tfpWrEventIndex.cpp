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
#include <rec/recFilterEvent.h>


wxString tfpWriteEventIndex( const wxString& extdb )
{
    static wxString htm;
    static long lastchange(0);

    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    wxSQLite3Table result = recEvent::GetTitleList( extdb );
    size_t size = (size_t) result.GetRowCount();

    htm =
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Event List</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
        "<h1>Event Index</h1>"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;

    for( size_t i = 0 ; i < size ; i++ ) {
        result.SetRow( i );
        htm << "<tr>\n<td><a href='tfp:E"
            << result.GetAsString( 0 )
            << "'><b>E"
            << result.GetAsString( 0 )
            << "</b></a></td>\n<td>"
            << result.GetAsString( 1 )
            << "</td>\n</tr>\n";
    }
    htm << "</table>\n</div>\n</body>\n</html>\n";

    lastchange = recDb::GetChange();
    return htm;
}

wxString tfpWriteEventPagedIndex( idt begCnt, const wxString& extdb )
{
    int maxsize = recEvent::UserCount( extdb );
    if( maxsize <= tfpWR_PAGE_MAX ) {
        return tfpWriteEventIndex( extdb );
    }
    wxString pmenu = tfpWritePagedIndexMenu( begCnt, maxsize, "tfp:E" );

    wxSQLite3Table result = recEvent::GetTitleList( begCnt, tfpWR_PAGE_MAX, extdb );
    size_t size = (size_t) result.GetRowCount();
    result.SetRow( 0 );
    idt beg = GET_ID( result.GetInt64( 0 ) );
    result.SetRow( size-1 );
    idt end = GET_ID( result.GetInt64( 0 ) );

    wxString htm;
    htm <<
        tfpWrHeadTfp( "Event List" ) <<
        "<h1>Event Index from " << recEvent::GetIdStr( beg ) <<
        " to " << recEvent::GetIdStr( end ) <<
        "</h1>\n" << pmenu <<
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;
    for( size_t i = 0 ; i < size ; i++ ) {
        result.SetRow( i );
        htm << 
            "<tr><td><a href='tfp:E" << result.GetAsString( 0 ) <<
            "'><b>E" << result.GetAsString( 0 ) <<
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

wxString tfpWriteEventSelection( TfpFrame& frame )
{
    recSelSetEvent& filter = frame.GetSelectedSetEvents();
    recFilterEvent fe( filter );

    fe.CreateEventTable( filter.GetDbname() );
    wxSQLite3Table* result = fe.GetTable();
    size_t size = (size_t) result->GetRowCount();

    wxString htm;

    htm << tfpWrHeadTfp( "Event List" ) <<
        "<h1>Selected Event List</h1>\n"
        "<table class='frame'>\n<tr>\n<td class='support'><br>\n";
    wxString begDate = filter.GetBegDateStr();
    wxString endDate = filter.GetEndDateStr();
    if( begDate.size() || endDate.size() ) {
        htm << "<p class='nowrap'>\n";
        if( begDate.size() ) {
            htm << "From Date: <b>" << begDate << "</b><br>\n";
        }
        if( endDate.size() ) {
            htm << "To Date: <b>" << endDate << "</b><br>\n";
        }
        htm << "</p>\n";
    }

    recIdVec typeIDs = fe.GetTypeIDVec();
    htm << "<p class='indent nowrap'>\nEvent Types:<b><br>\n";
    for( size_t i = 0; i < typeIDs.size(); i++ ) {
        htm << recEventType::GetTypeStr( typeIDs[i] ) << "<br>\n";
    }
    htm << 
        "</b></p>\n"
        "</td><td class='frame'>"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th><th>Year</th></tr>\n"
        ;
    for( size_t i = 0; i < size; i++ ) {
        result->SetRow( i );
        long jdn = result->GetInt( 2 );
        wxString yearStr;
        if( jdn ) {
            int year;
            calYearFromJdn( &year, jdn, CALENDAR_SCH_Gregorian );
            yearStr << year;
        }

        htm << "<tr>\n<td><a href='tfp:E"
            << result->GetAsString( 0 )
            << "'><b>E"
            << result->GetAsString( 0 )
            << "</b></a></td>\n<td>"
            << result->GetAsString( 1 )
            << "</td>\n<td>"
            << yearStr
            << "</td>\n</tr>\n";
    }
    htm <<
        "</table>\n"
        "</td>\n</tr>\n</table>\n" << tfpWrTailTfp()
    ;
    return htm;
}

// End of tfpWrEventIndex.cpp Source
