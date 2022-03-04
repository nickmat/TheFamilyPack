/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Reference Entity functions.
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

#include <rec/recReference.h>

#include <rec/recCitation.h>
#include <rec/recEvent.h>
#include <rec/recIndividual.h>
#include <rec/recMedia.h>
#include <rec/recPersona.h>

#include "tfpWr.h"

static wxString GetHref( const recReferenceEntity& ref )
{
    wxString idStr = recGetStr( ref.FGetEntityID() );
    switch( ref.FGetEntityType() )
    {
    case recReferenceEntity::TYPE_Place:
        return "tfpi:P" + idStr;
    case recReferenceEntity::TYPE_Date:
        return "tfpi:D" + idStr;
    case recReferenceEntity::TYPE_Name:
        return "tfpi:N" + idStr;
    }
    return "";
}

wxString tfpWriteReferenceIndex( const wxString& dbname )
{
    static wxString htm;
    static long lastchange(0);

    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }
    wxSQLite3Table result = recReference::GetTitleList( dbname );

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

wxString tfpWriteReferencePagedIndex( idt begCnt, const wxString& dbname )
{
    int maxsize = recReference::UserCount( dbname );
    if( maxsize <= tfpWR_PAGE_MAX ) {
        return tfpWriteReferenceIndex( dbname );
    }
    wxString pmenu = tfpWritePagedIndexMenu( begCnt, maxsize, "tfp:R" );

    wxSQLite3Table result = recReference::GetTitleList( begCnt, tfpWR_PAGE_MAX, dbname );
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

wxString tfpWriteReferencePage( idt refID, const wxString& dbname )
{
    wxString htm;
    recReference ref( refID, dbname );
    if( ref.FGetID() == 0 ) return wxEmptyString;
    recIdVec indIDs;

    htm <<
        tfpWrHeadTfp( "Reference " + ref.GetIdStr(), "tab" ) <<
        "<h1>" << ref.GetIdStr() << ": " << ref.FGetTitle() << "</h1>\n"
    ;

    if( ref.FGetStatement().compare( 0, 9, "<!-- HTML" ) == 0 ) {
        htm <<
            "</div>\n" << ref.FGetStatement() << "\n<div class='tfp'>\n"
        ;
    } else { // treat as text
        htm << "<pre>"
            << ref.FGetStatement()
            << "</pre>";
    }

    htm <<
        "<div>\n<p><b>User Ref:</b> " << ref.FGetUserRef() << "</p>\n</div>\n"
        "<hr>\n"
    ;

    recIdVec citIDs = ref.GetCitationList( refID, dbname );
    htm << "<table class='data'>\n";
    if( !citIDs.empty() ) {
        htm << "<table class='data'>\n<tr><th colspan='3'>Citation</th></tr>\n";
        for( idt citID : citIDs ) {
            recCitation cit( citID, dbname );
            htm <<
                "<tr><td><b><a href='tfpi:" << cit.GetIdStr() <<
                "'>" << cit.GetIdStr() <<
                "</a></b></td><td>" << cit.GetCitationStr( dbname ) <<
                "</td><td>" << cit.FGetComment() <<
                "</td></tr>\n"
            ;
        }
    }
    else {
        htm << "<tr><th>No Citation Entered</th></tr>\n";
    }
    htm << "</table>\n";

    recIdVec medIDs = ref.GetMediaList( refID, dbname );
    htm << "<table class='media'>\n";
    if( !medIDs.empty() ) {
        htm << "<tr><th colspan='3'>Media</th></tr>\n";
        for( idt medID : medIDs ) {
            recMedia med( medID, dbname );
            wxString fn = tfpGetMediaDataFile( med.FGetDataID(), med.FGetAssID(), dbname );
            htm << "<tr>\n<td rowspan='2'>";
            if( fn.empty() ) {
                htm << med.GetDataIdStr() << " Not Found.";
            }
            else {
                htm << "<a href = 'tfpv:M" << med.FGetID()
                    << "'><img src='" << fn << "' alt='' height='200' /></a>";
            }
            htm <<
                "</td>"
                "<td><a href='tfp:M" << med.FGetID()
                << "'><b>" << med.GetIdStr()
                << "</b></a></td>\n<td class='title'>" << med.FGetTitle()
                << "</td>\n</tr>\n"
                "<tr>\n<td colspan='2'>" << med.FGetNote()
                << "</td>\n</tr>\n"
                ;
        }
    }
    else {
        htm << "<tr><th>No Media Entered</th></tr>\n";
    }
    htm << "</table>\n";

    htm << "<table class='data'>\n";
    recIdVec perIDs = ref.GetPersonaList( dbname );
    if( perIDs.size() ) {
        htm << "<tr><th colspan='5'>Persona</th></tr>\n";
        for( size_t i = 0 ; i < perIDs.size() ; i++ ) {
            recPersona per(perIDs[i], dbname );
            htm <<
                "<tr><td><b><a href='tfp:Pa" << recGetStr( per.FGetID() ) <<
                "'>" << per.GetIdStr() <<
                "</a></b></td><td>" << per.GetNameStr( dbname ) <<
                "</td><td>" << recGetSexStr( per.FGetSex() ) <<
                "</td><td>" << per.FGetNote() <<
                "</td><td><b>"
            ;
            recIdVec indIDs = per.GetIndividualIDs( dbname );
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

    recIdVec eaIDs = ref.GetEventaList( dbname );
    if ( !eaIDs.empty() ) {
        htm << "<tr><th colspan='4'>Eventa</th></tr>\n";
        for ( idt eaID : eaIDs ) {
            recEventa ea( eaID, dbname );
            htm <<
                "<tr><td><b><a href='tfp:Ea" << recGetStr( ea.FGetID() ) <<
                "'>" << ea.GetIdStr() <<
                "</a></b></td><td>" << ea.FGetTitle() <<
                "</td><td>" << ea.FGetNote() <<
                "</td><td><b>"
            ;
            recIdVec eveIDs = ea.GetLinkedEventIDs( dbname );
            for ( idt eveID : eveIDs ) {
                if ( eveID != *eveIDs.begin() ) {
                    htm << ", ";
                }
                htm <<
                    "<a href='tfp:E" << eveID <<
                    "'>" << recEvent::GetIdStr( eveID ) <<
                    "</a>"
                ;
            }
        }
    } else {
        htm << "<tr><th>No Eventa Entered</th></tr>\n";
    }
    htm << "</table>\n<table class='data'>\n";

    recRefEntVec res = ref.ReadReferenceEntitys( dbname );
    if( res.size() ) {
        htm << "<tr><th colspan='3'>Reference Entities</th></tr>\n";
        for( size_t i = 0 ; i < res.size() ; i++ ) {
            htm <<
                "<tr><td>" << res[i].GetTypeStr() <<
                "</td><td><b><a href='" << GetHref( res[i] ) <<
                "'>" << res[i].GetEntityIdStr() <<
                "</a></b></td><td>" << res[i].GetEntityStr( dbname ) <<
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
