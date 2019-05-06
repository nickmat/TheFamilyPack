/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Media functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd November 2018
 * Copyright:   Copyright (c) 2018 ~ 2019, Nick Matthews.
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

#include <rec/recAssociate.h>
#include <rec/recMedia.h>
#include <rec/recMediaData.h>
#include <rec/recReference.h>


wxString tfpWriteMediaPage( idt medID )
{
    wxString htm;
    recMedia med( medID );
    if ( med.FGetID() == 0 ) {
        return htm;
    }
    recAssociate ass( med.FGetAssID() );
    recMediaData md( med.FGetDataID() );
    wxString fn = tfpGetMediaDataFile( med.FGetDataID(), med.FGetAssID() );
    wxString dataPath = ( med.FGetAssID() == 0 ) ? "Main" : ass.FGetPath();
    dataPath += ": " + md.FGetFile();
    wxString dataIdStr = ass.GetIdStr() + ":" + md.GetIdStr();
    wxString copyright = md.FGetCopyright();
    if ( copyright.empty() ) {
        copyright = "None";
    }

    htm << tfpWrHeadTfp( "Media " + med.GetIdStr(), "tab" ) <<
        "<table class='data'>\n"
        "<tr>\n"
        "<th colspan='2'>Media Details</th>\n"
        "</tr>\n"
        "<tr>\n"
        "<td>Title:</td>\n"
        "<td>" << med.FGetTitle() << "</td>\n"
        "</tr>\n"
        "<tr>\n"
        "<td colspan='2' class='media'><a href = 'tfpv:M" << med.FGetID() << "'>"
        "<img src='" << fn << "' alt='' height='200' /></a></td>\n"
        "</tr>\n"
        "<tr>\n"
        "<td colspan='2'>ID: <b>" << med.GetIdStr() << "</b>"
        " Privacy: <b>" << med.FGetPrivacy() << "</b></td>\n"
        "</tr>\n"
        "<tr>\n"
        "<td>Note:</td>\n"
        "<td>" << med.FGetNote() << "</td>\n"
        "</tr>\n"
        "<tr>\n"
        "<td>Reference:</td>\n"
        "<td><b><a href='tfp:R" << med.FGetRefID() <<
        "'>" << recReference::GetIdStr( med.FGetRefID() ) <<
        "</a></b> " << recReference::GetTitle( med.FGetRefID() ) << "</td>\n"
        "</tr>\n"
        "<tr>\n"
        "<th colspan='2'>Media Data Details</th>\n"
        "</tr>\n"
        "<tr>\n"
        "<td>Path:</td>\n"
        "<td><b>" << dataPath << "</b></td>\n"
        "</tr>\n"
        "<tr>\n"
        "<td colspan='2'>ID: <b>" << dataIdStr << "</b>"
        " Privacy: <b>" << md.FGetPrivacy() << "</b>"
        " Copyright: <b>" << copyright << "</b></td>\n"
        "</tr>\n"
        "</table>\n" << tfpWrTailTfp()
    ;
    return htm;
}

wxString tfpWriteMediaIndex()
{
    static wxString htm;
    static long lastchange( 0 );

    if ( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }
    wxSQLite3Table result = recMedia::GetMediaList();

    htm <<
        tfpWrHeadTfp( "Media List" ) <<
        "<h1>Media List</h1>\n"
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Database</th><th>Reference</th><th>Title</th></tr>\n"
    ;
    for ( int i = 0; i < result.GetRowCount(); i++ ) {
        result.SetRow( i );
        htm <<
            "<tr><td><a href='tfp:M" << result.GetAsString( 0 ) <<
            "'><b>M" << result.GetAsString( 0 ) <<
            "</b></a></td><td>" << recAssociate::GetPath( GET_ID( result.GetInt64( 1 ) ) ) <<
            "</td><td><a href='tfp:R" << result.GetAsString( 2 ) <<
            "'><b>R" << result.GetAsString( 2 ) <<
            "</b></a></td><td> " << result.GetAsString( 3 ) <<
            "</td></tr>\n"
        ;
    }
    htm << "</table>\n" << tfpWrTailTfp();

    lastchange = recDb::GetChange();
    return htm;
}

wxString tfpWriteMediaPagedIndex( idt begCnt )
{
    int maxsize = recMedia::UserCount();
    if ( maxsize <= tfpWR_PAGE_MAX ) {
        return tfpWriteMediaIndex();
    }
    wxString pmenu = tfpWritePagedIndexMenu( begCnt, maxsize, "tfp:M" );

    wxSQLite3Table result = recMedia::GetMediaList( begCnt, tfpWR_PAGE_MAX );
    size_t size = (size_t)result.GetRowCount();
    result.SetRow( 0 );
    idt beg = GET_ID( result.GetInt64( 0 ) );
    result.SetRow( size - 1 );
    idt end = GET_ID( result.GetInt64( 0 ) );

    wxString htm;
    htm <<
        tfpWrHeadTfp( "Media List" ) <<
        "<h1>Media Index from " << recReference::GetIdStr( beg ) <<
        " to " << recReference::GetIdStr( end ) <<
        "</h1>\n" << pmenu <<
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Database</th><th>Reference</th><th>Title</th></tr>\n"
    ;
    for ( size_t i = 0; i < size; i++ ) {
        result.SetRow( i );
        htm <<
            "<tr><td><a href='tfp:M" << result.GetAsString( 0 ) <<
            "'><b>M" << result.GetAsString( 0 ) <<
            "</b></a></td><td>" << recAssociate::GetPath( GET_ID( result.GetInt64( 1 ) ) ) <<
            "</td><td><a href='tfp:R" << result.GetAsString( 2 ) <<
            "'><b>R" << result.GetAsString( 2 ) <<
            "</b></a></td><td> " << result.GetAsString( 3 ) <<
            "</td></tr>\n"
        ;
    }
    htm <<
        "</table>\n" << pmenu <<
        "<br>\n" << tfpWrTailTfp()
    ;
    return htm;
}

// End of src/tfp/tfpWrMedia.cpp Source
