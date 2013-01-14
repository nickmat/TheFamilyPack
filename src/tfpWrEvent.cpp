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
#include <rec/recFilterEvent.h>
#include <rec/recPersona.h>
#include <rec/recIndividual.h>

#include <rg/rgCompareEvent.h>

#include "tfpWr.h"

static wxString tfpWriteIndEventPage( idt eventID, rgCompareEvent* ce );
static wxString tfpWriteRefEventPage( idt eventID );

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


wxString tfpWriteEventIndex()
{
    static wxString htm;
    static long lastchange(0);

    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    wxSQLite3Table result = recEvent::GetTitleList();
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

wxString tfpWriteEventPagedIndex( idt begCnt )
{
    const int maxrows = 100;
    idt beg = 0, end = 0;
    size_t maxsize = (size_t) recEvent::UserCount();
    int pgcnt = ( maxsize / maxrows ) + 1;

    wxSQLite3Table result = recEvent::GetTitleList( begCnt, maxrows );
    size_t size = (size_t) result.GetRowCount();
    if( size ) {
        result.SetRow( 0 );
        beg = GET_ID( result.GetInt64( 0 ) );
        result.SetRow( size-1 );
        end = GET_ID( result.GetInt64( 0 ) );
    }
    int pgcur = begCnt/maxrows;
    int b1, e1, b2, e2;
    b1 = b2 = e1 = e2 = pgcnt;

    wxString mnu;
    if( pgcnt > 1 ) {
        mnu << "<div class='pagesel'><p>\n";
        if( begCnt != 0 ) {
            mnu <<
                "<a href='tfp:E," << begCnt-maxrows << 
                "'>Prev</a>\n"
            ;
        } else {
            mnu <<
                "<a class='pncur' href='null:'>Prev</a>\n"
            ;
        }
        if( pgcnt > 10 ) {
            if( pgcur < 2 )  { b1 = 5; e1 = pgcnt - 5; }
            else if( pgcur == 2 ) { b1 = 6; e1 = pgcnt - 4; }
            else if( pgcur == 3 ) { b1 = 7; e1 = pgcnt - 3; }
            else if( pgcur == 4 ) { b1 = 8; e1 = pgcnt - 2; }
            else if( pgcur == pgcnt - 5 ) { b1 = 2; e1 = pgcnt - 8; }
            else if( pgcur == pgcnt - 4 ) { b1 = 3; e1 = pgcnt - 7; }
            else if( pgcur == pgcnt - 3 ) { b1 = 4; e1 = pgcnt - 6; }
            else if( pgcur > pgcnt - 3 )  { b1 = 5; e1 = pgcnt - 5; }
            else { b1 = 1; e1 = pgcur - 3; b2 = pgcur + 4; e2 = pgcnt - 1; }
        }
        for( int i = 0 ; i < pgcnt ; i++ ) {
            if(i == b1 ) {
                mnu << " ...\n";
                i = e1;
            }
            if(i == b2 ) {
                mnu << " ...\n";
                i = e2;
            }
            if( i == pgcur ) {
                mnu <<
                    "<a class='pn pncur' href='null:'>" << 
                    i+1 << "</a>\n"
                ;
            } else {
                mnu <<
                    "<a class='pn' href='tfp:E," << i*maxrows << 
                    "'>" << i+1 << "</a>\n"
                ;
            }
        }
        if( begCnt+maxrows < maxsize ) {
            mnu <<
                "<a href='tfp:E," << begCnt+maxrows << 
                "'>Next</a>\n"
            ;
        } else {
            mnu <<
                "<a class='pncur' href='null:'>Next</a>\n"
            ;
        }
        mnu << "</p></div>\n" ;
    }

    wxString htm;
    htm <<
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Event List</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
        "<h1>Event Index from " << recEvent::GetIdStr( beg ) <<
        " to " << recEvent::GetIdStr( end ) << "</h1>" << mnu <<
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
    htm << "</table>\n" << mnu << "<br>\n</div>\n</body>\n</html>\n";

    return htm;
}

wxString tfpWriteEventSelection( recFilterEvent& filter )
{

    wxSQLite3Table* result = filter.GetTable();
    size_t size = (size_t) result->GetRowCount();

    wxString htm =
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Event List</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
        "<h1>Selected Event List</h1>"
    ;

    htm << "<table class='frame'>\n<tr>\n<td class='support'><br>\n";
    long begDate = filter.GetBegDatePt();
    long endDate = filter.GetEndDatePt();
    if( begDate || endDate ) {
        htm << "<p class='nowrap'>\n";
        if( filter.GetBegDatePt() ) {
            htm << 
                "From Date: <b>" << 
                calStrFromJdn( filter.GetBegDatePt(), CALENDAR_SCH_Gregorian ) <<
                "</b><br>\n"
            ;
        }
        if( filter.GetEndDatePt() ) {
            htm << 
                "To Date: <b>" << 
                calStrFromJdn( filter.GetEndDatePt(), CALENDAR_SCH_Gregorian ) <<
                "</b><br>\n"
            ;
        }
        htm << "</p>\n";
    }

    recIdVec typeIDs = filter.GetTypeIDVec();
    htm << "<p class='indent nowrap'>\nEvent Types:<b><br>\n";
    for( size_t i = 0 ; i < typeIDs.size() ; i++ ) {
        htm << recEventType::GetTypeStr( typeIDs[i] ) << "<br>\n";
    }
    htm << "</b></p>\n";

    htm <<
        "</td><td class='frame'>"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th><th>Year</th></tr>\n"
    ;
    for( size_t i = 0 ; i < size ; i++ ) {
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
    htm << "</table>\n";

    htm << "</td>\n</tr>\n</table>\n";

    htm << "</div>\n</body>\n</html>\n";
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

    htm << 
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Event " << eve.GetIdStr() << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"

        "<h1>Conclusion Event " << eve.GetIdStr() << ": " << eve.f_title << "</h1>\n"

        "<table class='data'>\n<tr>\n"
        "<td><b><a href='tfpi:D" << eve.FGetDate1ID() <<
        "'>Date</a>: </b>" << eve.GetDateStr() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b><a href='tfpi:P" << eve.FGetPlaceID() << 
        "'>Place</a>: </b>" << eve.GetAddressStr() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b>Note: </b>" << eve.f_note << "</td>\n"
        "</tr>\n<tr>\n"
        "<td>Group: " << recEventType::GetGroupStr( eve.FGetTypeID() ) <<
        " Type: " << eve.GetTypeStr() << "</td>\n"
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
        << "</div>\n</body>\n</html>\n";

    return htm;
}

wxString tfpWriteRefEventPage( idt eventID )
{
    wxString htm;
    recEvent eve(eventID);
    if( eve.f_id == 0 ) return wxEmptyString;
    idt refID = recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, eventID );

    htm <<
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>Event " << eve.GetIdStr() << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
        "<h1>Evidence Event " << eve.GetIdStr() << ": " << eve.f_title << "</h1>\n"

        "<table class='data'>\n<tr>\n"
        "<td><b><a href='tfpi:D" << eve.FGetDate1ID() <<
        "'>Date</a>: </b>" << eve.GetDateStr() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b><a href='tfpi:P" << eve.FGetPlaceID() << 
        "'>Place</a>: </b>" << eve.GetAddressStr() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b>Note: </b>" << eve.f_note << "</td>\n"
        "</tr>\n<tr>\n"
        "<td>Group: " << recEventType::GetGroupStr( eve.FGetTypeID() ) <<
        " Type: " << eve.GetTypeStr() << "</td>\n"
        "</tr>\n<tr>\n"
        "<td><b><a href='tfp:R" << refID <<
        "'>" << recReference::GetIdStr( refID ) <<
        "</a></b> " << recReference::GetTitle( refID ) << "</td>\n"
        "</tr>\n</table>\n"
    ;

    recEventPersonaVec eps = eve.GetEventPersonas();
    if( !eps.empty() ) {
        htm <<
            "<table class='data'>\n<tr>\n"
            "<th>Role</th><th>ID</th><th>Persona</th><th>Note</th>"
            "<th>Individuals</tr>\n"
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
    htm << "</body>\n</html>\n";
    return htm;
}

// End of tfpWrEvent.cpp Source
