/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Reference Entity functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
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

#include <rec/recReference.h>
#include <rec/recPersona.h>
#include <rec/recIndividual.h>
#include <rec/recEvent.h>

#include "tfpWr.h"

static wxString GetHref( const recReferenceEntity& ref )
{
    wxString idStr = recGetStr( ref.FGetEntityID() );
    switch( ref.FGetEntityType() )
    {
    case recReferenceEntity::TYPE_Event:
        return "tfp:Em" + idStr;
    case recReferenceEntity::TYPE_Place:
        return "tfpi:P" + idStr;
    case recReferenceEntity::TYPE_Date:
        return "tfpi:D" + idStr;
    case recReferenceEntity::TYPE_Relationship:
        return "tfpi:Rs" + idStr;
    case recReferenceEntity::TYPE_Name:
        return "tfpi:N" + idStr;
    }
    return "";
}

wxString tfpWriteReferenceIndex()
{
    static wxString htm;
    static long lastchange(0);

    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }
    wxSQLite3Table result = recReference::GetTitleList();

    htm = tfpWrHeadTfp( "Reference List" );
    htm << "<h1>Reference List</h1>\n";

    htm <<
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;
    for( int i = 0 ; i < result.GetRowCount() ; i++ ) {
        result.SetRow( i );
        htm << 
            "<tr><td><a href='tfp:R" << result.GetAsString( 0 ) <<
            "'><b>R" << result.GetAsString( 0 ) <<
            "</b></a></td><td> " << result.GetAsString( 1 ) <<
            "</td></tr>\n"
        ;
    }
    htm << 
        "</table>\n<p>\nTotal References found: " <<
        result.GetRowCount() <<
        "\n</p>\n"
    ;

    htm << tfpWrTailTfp();

    lastchange = recDb::GetChange();
    return htm;
}

wxString tfpWriteReferencePagedIndex( idt begCnt )
{
    int maxsize = recReference::UserCount();
    if( maxsize <= tfpWR_PAGE_MAX ) {
        return tfpWriteReferenceIndex();
    }
    wxString pmenu = tfpWritePagedIndexMenu( begCnt, maxsize, "tfp:R" );

    wxSQLite3Table result = recReference::GetTitleList( begCnt, tfpWR_PAGE_MAX );
    size_t size = (size_t) result.GetRowCount();
    result.SetRow( 0 );
    idt beg = GET_ID( result.GetInt64( 0 ) );
    result.SetRow( size-1 );
    idt end = GET_ID( result.GetInt64( 0 ) );

    wxString htm;
    htm <<
        tfpWrHeadTfp( "Reference List" ) <<
        "<h1>Reference Document Index from " << recReference::GetIdStr( beg ) <<
        " to " << recReference::GetIdStr( end ) <<
        "</h1>\n" << pmenu <<
        "<table class='data'>\n"
        "<tr><th>ID</th><th>Title</th></tr>\n"
    ;
    for( size_t i = 0 ; i < size ; i++ ) {
        result.SetRow( i );
        htm << 
            "<tr><td><a href='tfp:R" << result.GetAsString( 0 ) <<
            "'><b>R" << result.GetAsString( 0 ) <<
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

wxString tfpWriteReferencePage( idt refID )
{
    wxString htm;
    recReference ref(refID);
    if( ref.f_id == 0 ) return wxEmptyString;
    recIdVec indIDs;

    htm <<
        tfpWrHeadTfp( "Reference " + ref.GetIdStr(), "tab" ) <<
        "<h1>" << ref.GetIdStr() << ": " << ref.f_title << "</h1>\n"
    ;

    if( ref.f_statement.compare( 0, 9, "<!-- HTML" ) == 0 ) {
        htm <<
            "</div>\n" << ref.f_statement << "\n<div class='tfp'>\n"
        ;
    } else { // treat as text
        htm << "<pre>"
            << ref.f_statement
            << "</pre>";
    }

    htm << "<hr>\n<table class='data'>\n";
    recIdVec perIDs = ref.GetPersonaList();
    if( perIDs.size() ) {
        htm <<
            "<tr><th colspan='5'>Persona</th></tr>\n"
        ;
        for( size_t i = 0 ; i < perIDs.size() ; i++ ) {
            recPersona per(perIDs[i]);
            htm <<
                "<tr><td>" << per.GetIdStr() <<
                "</td><td>" << per.GetNameStr() <<
                "</td><td>" << recGetSexStr( per.FGetSex() ) <<
                "</td><td>" << per.FGetNote() <<
                "</td><td><b>"
            ;
            recIdVec indIDs = per.GetIndividualIDs(); 
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
            htm << "</b></td></tr>\n";
        }
    } else {
        htm << "<tr><th>No Persona Entered</th></tr>\n";
    }
    htm << "</table>\n<table class='data'>\n";

    recRefEntVec res = ref.ReadReferenceEntitys();
    if( res.size() ) {
        htm << "<tr><th colspan='3'>Reference Entities</th></tr>\n";
        for( size_t i = 0 ; i < res.size() ; i++ ) {
            htm <<
                "<tr><td>" << res[i].GetTypeStr() <<
                "</td><td><b><a href='" << GetHref( res[i] ) <<
                "'>" << res[i].GetEntityIdStr() <<
                "</a></b></td><td>" << res[i].GetEntityStr() <<
                "</td></tr>\n"
            ;
        }
    } else {
        htm << "<tr><th>No Reference Entities Entered</th></tr>\n";
    }
    htm << "</table>\n" << tfpWrTailTfp();

    return htm;
}

// End of tfpWrReference.cpp Source
