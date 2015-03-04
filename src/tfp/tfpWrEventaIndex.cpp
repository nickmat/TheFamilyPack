/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrEventaIndex.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write to screen and compare Eventum's.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th July 2013
 * Copyright:   Copyright (c) 2013-2015, Nick Matthews.
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


wxString tfpWriteEventumIndex()
{
    wxSQLite3Table result = recEventum::GetTitleList();
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
        htm << "<tr>\n<td><a href='tfp:Em"
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

wxString tfpWriteEventumPagedIndex( idt begCnt )
{
    int maxsize = recEvent::UserCount();
    if( maxsize <= tfpWR_PAGE_MAX ) {
        return tfpWriteEventIndex();
    }
    wxString pmenu = tfpWritePagedIndexMenu( begCnt, maxsize, "tfp:Em" );

    wxSQLite3Table result = recEventum::GetTitleList( begCnt, tfpWR_PAGE_MAX );
    size_t size = (size_t) result.GetRowCount();
    result.SetRow( 0 );
    idt beg = GET_ID( result.GetInt64( 0 ) );
    result.SetRow( size-1 );
    idt end = GET_ID( result.GetInt64( 0 ) );

    wxString htm;
    htm <<
        tfpWrHeadTfp( "Event Record List" ) <<
        "<h1>Reference Document Index from " << recEventum::GetIdStr( beg ) <<
        " to " << recEventum::GetIdStr( end ) <<
        "</h1>\n" << pmenu <<
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;
    for( size_t i = 0 ; i < size ; i++ ) {
        result.SetRow( i );
        htm <<
            "<tr><td><a href='tfp:Em" << result.GetAsString( 0 ) <<
            "'><b>Em" << result.GetAsString( 0 ) <<
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

// End of src/tfp/tfpWrEventumIndex.cpp Source
