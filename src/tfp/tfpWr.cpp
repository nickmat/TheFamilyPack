/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWr.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write HTML screen support functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21st January 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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
#include "tfpVersion.h"

#include <rec/recAssociate.h>
#include <rec/recContact.h>
#include <rec/recIndividual.h>
#include <rec/recMediaData.h>
#include <rec/recSystem.h>
#include <rec/recUser.h>

#include <wx/fs_mem.h>
#include <wx/mstream.h>
#include <wx/tokenzr.h>

wxString tfpWrHead( const wxString& title, const wxString& css )
{
    wxString htm;
    htm <<
        "<!DOCTYPE html>\n"
        "<html>\n<head>\n"
        "<title>" << title << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        ;
    if ( css.size() ) {
        wxStringTokenizer tokenizer( css, ";" );
        while ( tokenizer.HasMoreTokens() ) {
            wxString file = tokenizer.GetNextToken();
            htm <<
                "<link rel='stylesheet' type='text/css' href='memory:" << file <<
                ".css'>\n"
                ;
        }
    }
    htm << "</head>\n<body>\n";
    return htm;
}

wxString tfpWrTail()
{
    return "</body>\n</html>\n";
}

wxString tfpWrHeadTfp( const wxString& title, const wxString& css )
{
    wxString css_list( "tfp" );
    if ( !css.empty() ) {
        css_list += ";" + css;
    }
    return tfpWrHead( title, css_list ) + "<div class='tfp'>\n";
}

wxString tfpWrHeadInfo( const wxString& title, const wxString& css )
{
    wxString css_list( "info" );
    if ( !css.empty() ) {
        css_list += ";" + css;
    }
    return tfpWrHead( title, css_list );
}

wxString tfpWrErrorPage( const wxString& name )
{
    return wxString::Format(
        "<html>\n<head><title>Error</title></head>\n"
        "<body><h1>Error</h1><p>Page [%s] not understood.</p></body>\n</html>",
        name
    );
}

wxString tfpWrStartPage()
{
    wxString htm =
        tfpWrHead( "Startup", "tfp") <<
        "<table class='logo'>\n"
        "<tr>\n"
        "<td>\n"
        "<img src='memory:logo6.png'>\n"
        "</td>\n"
        "<td class='title'>\n"
        "<font size='+4'><b>The Family Pack</b></font>\n"
        "</td>\n"
        "</tr>\n"
        "</table>\n"
        "<div class='pagesel control'>\n"
        "<p>\n"
        "<br><br><b>Actions:-</b><br>\n"
        "<a href='tfpc:Open'>Open an existing Database</a>\n"
        "<br>\n"
        "<a href='tfpc:New'>Create a new Database</a>\n"
        "<br>\n"
        "<a href='tfpc:Import'>Import a GEDCOM file</a>\n"
        "</p>\n"
        "</div>\n"
        "<p>\n"
        "<a class='web' href='http://thefamilypack.org'>http://thefamilypack.org</a><br>\n"
        "<br>\n"
        "<b>TFP</b> " << tfpHtmVersion << "\n"
#ifdef _DEBUG
        "<br><br><a href='tfpc:Test'>Test html page</a>\n"
#endif
        "</p>\n"
        << tfpWrTail()
    ;
    return htm;
}

wxString tfpWritePagedIndexMenu( idt begCnt, size_t maxsize, const wxString prefix )
{
    int maxrows = tfpWR_PAGE_MAX;
    idt beg = 0, end = 0;
    int pgcnt = ( maxsize / maxrows ) + 1;

    int pgcur = begCnt/maxrows;
    int b1, e1, b2, e2;
    b1 = b2 = e1 = e2 = pgcnt;

    wxString mnu;
    if( pgcnt > 1 ) {
        mnu << "<div class='pagesel'><p>\n";
        if( begCnt != 0 ) {
            mnu <<
                "<a href='" << prefix << "," << begCnt-maxrows << 
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
                    "<a class='pn' href='" << prefix << "," << i*maxrows << 
                    "'>" << i+1 << "</a>\n"
                ;
            }
        }
        if( begCnt+maxrows < maxsize ) {
            mnu <<
                "<a href='" << prefix << "," << begCnt+maxrows << 
                "'>Next</a>\n"
            ;
        } else {
            mnu <<
                "<a class='pncur' href='null:'>Next</a>\n"
            ;
        }
        mnu << "<a class='pn' href='" << prefix << "'>All</a>\n</p></div>\n";
    }
    return mnu;
}

wxString tfpGetIndSexClass( idt indID, Sex pref, const wxString& dbname )
{
    return tfpGetSexClass( recIndividual::GetSex( indID, dbname ), pref );
}

wxString tfpGetSexClass( Sex sex, Sex pref )
{
    if( sex == Sex::unstated ) {
        sex = pref;
    }
    switch( sex ) {
    case Sex::male:
        return "male";
    case Sex::female:
        return "fem";
    }
    return "neut";
}

wxString tfpGetRowClass( int row )
{
    return ( row % 2 ) ? "odd" : "even";
}

wxString tfpGetEpitaphPlus(
    idt indID, GetEpitaphPrefix prefix, const wxString& dbname )
{
    wxString epitaph = recIndividual::GetEpitaph( indID, dbname );
    wxString prefixStr;

    if( epitaph.size() ) {
        switch( prefix )
        {
        case GetEpitaphPrefix::spaces:
            prefixStr = "&nbsp;&nbsp;";
            break;
        case GetEpitaphPrefix::newline:
            prefixStr = "<br>\n";
            break;
        }
    }
    wxString ret;
    ret << 
        prefixStr << epitaph <<
        "&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
        "'><img src=memory:fam.png></a>"
    ;
    return ret;
}

wxString tfpNormaliseSpaces( const wxString& str )
{
    wxString out(str);
    for(;;) {
        size_t pos = out.find( "%20" );
        if( pos == wxString::npos ) {
            break;
        }
        out.replace( pos, 3, " " );
    }
    return out;
}

wxString tfpGetMediaDataFile( idt mdID, idt assID, const wxString& extdb )
{
    wxString assDb = recAssociate::GetAttachedName( assID, extdb );
    if( assDb.empty() ) {
        return wxString();
    }
    wxString filename = recMediaData::GetFileName( assDb, mdID ) + ".bmp";
    // Read into the virtual file system, unless it already exists.
    wxFileSystem fs;
    wxString memfilename = "memory:" + filename;
    wxString fn = fs.FindFirst( memfilename );
    if ( fn.empty() ) {
        recMediaData md( assDb, mdID );
        wxMemoryBuffer buf = md.FGetData();
        wxMemoryInputStream stream( buf.GetData(), buf.GetDataLen() );
        wxImage image( stream, wxBITMAP_TYPE_JPEG );
        double scale = 200.0 / image.GetHeight();
        int width = scale * image.GetWidth();
        wxBitmap bmp = wxBitmap( image.Scale( width, 200 ) );
        wxMemoryFSHandler::AddFile( filename, bmp, wxBITMAP_TYPE_BMP );
    }
    return memfilename;
}

wxString tfpNormalisePageName( const wxString& name )
{
    wxString uname = name.Upper();
    if( uname.compare( 0, 2, "AR" ) == 0 ||
        uname.compare( 0, 2, "CI" ) == 0 ||
        uname.compare( 0, 2, "EA" ) == 0 ||
        uname.compare( 0, 2, "PA" ) == 0 ||
        uname.compare( 0, 2, "RE" ) == 0 ||
        uname.compare( "ABOUT" ) == 0 ||
        uname.compare( "START" ) == 0 
        )
    {
        return uname.Capitalize();
    }
    if( uname.compare( 0, 3, "NI+" ) == 0 ||
        uname.compare( 0, 3, "NP+" ) == 0 )
    {
        // Don't capitalize the name part.
        return uname.Mid( 0, 3 ) + name.Mid( 3 );
    }
    return uname;
}

wxString tfpGetDisplayText( const wxString& pagename, const wxString& dbname, TfpFrame* frame )
{
    wxString name = pagename.Upper();
    wxASSERT( name.size() > 0 );
    wxLongLong_t num, num1 = 0, num2 = 0;
    bool success, success1 = false, success2 = false;

    success = name.Mid( 1 ).ToLongLong( &num );
    if( name.size() > 1 ) {
        success1 = name.Mid( 2 ).ToLongLong( &num1 );
    }
    if( name.size() > 2 ) {
        success2 = name.Mid( 3 ).ToLongLong( &num2 );
    }

    try {
        if( name.compare( "ABOUT" ) == 0 ) {
            return tfpWriteAbout();
        }
        if( name.compare( "START" ) == 0 ) {
            return tfpWrStartPage();
        }
        if( name.compare( "AR" ) == 0 ) {
            return tfpWriteArchiveIndex();
        }
        if( name.compare( 0, 2, "AR" ) == 0 && success1 ) {
            return tfpWriteArchive( num1 );
        }
        if( name.compare( 0, 2, "CD" ) == 0 && success1 ) {
            return tfpCreateDescChart( num1 );
        }
        if( name.compare( 0, 2, "CI" ) == 0 && success1 ) {
            return tfpWriteCitation( num1 );
        }
        if( name.compare( 0, 2, "CP" ) == 0 && success1 ) {
            return tfpCreatePedChart( num1 );
        }
        if( name.compare( 0, 1, "D" ) == 0 && success ) {
            return tfpWriteDate( num );
        }
        if( name.compare( "E" ) == 0 ) {
            return tfpWriteEventIndex();
        }
        if( name.compare( "E$") == 0 ) {
            return tfpWriteEventSelection( frame );
        }
        if( name.compare( "EA" ) == 0 ) {
            return tfpWriteEventaIndex();
        }
        // We don't have a Eventa filter yet!
        //    if( name.compare( "EA$" ) == 0 ) {
        //        return tfpWriteEventaSelection( m_erFilter );
        //    }
        if( name.compare( 0, 2, "EA" ) == 0 && success1 ) {
            return tfpWriteEventaPage( num1 );
        }
        if( name.compare( 0, 3, "EA," ) == 0 && success2 ) {
            return tfpWriteEventaPagedIndex( num2 );
        }
        if( name.compare( 0, 1, "E" ) == 0 && success ) {
            return tfpWriteEventPage( num, frame );
        }
        if( name.compare( 0, 2, "E," ) == 0 && success1 ) {
            return tfpWriteEventPagedIndex( num1 );
        }
        if( name.compare( 0, 2, "FI" ) == 0 && success1 ) {
            return tfpWriteIndFamilyPage( num1, dbname );
        }
        if( name.compare( 0, 1, "F" ) == 0 ) {
            // Note, Family Page may have alternate parents
            // so name string requires further decoding.
            return tfpWriteFamilyPage( name.Mid( 1 ), dbname );
        }
        if( name.compare( "G" ) == 0 ) {
            return tfpWriteGalleryList();
        }
        if( name.compare( 0, 1, "G" ) == 0 && success ) {
            return tfpWriteGalleryPage( num );
        }
        if( name.compare( 0, 1, "I" ) == 0 && success ) {
            return tfpWriteIndividualPage( num, dbname );
        }
        if( name.compare( "M" ) == 0 ) {
            return tfpWriteMediaIndex( dbname );
        }
        if( name.compare( "MD" ) == 0 ) {
            return tfpWriteMediaDataIndex( dbname );
        }
        if( name.compare( 0, 2, "M," ) == 0 && success1 ) {
            return tfpWriteMediaPagedIndex( num1, dbname );
        }
        if( name.compare( 0, 2, "MD" ) == 0 ) {
            return tfpWriteMediaDataPage( name, dbname );
        }
        if( name.compare( 0, 1, "M" ) == 0 && success ) {
            return tfpWriteMediaPage( num );
        }
        if( name.compare( "NI" ) == 0 ) {
            return tfpWriteSurnameIndex( recSG_Individual );
        }
        if( name.compare( "NP" ) == 0 ) {
            return tfpWriteSurnameIndex( recSG_Persona );
        }
        if( name.compare( "ND*" ) == 0 ) {
            return tfpWriteIndividualList();
        }
        if( name.compare( 0, 3, "NI+" ) == 0 && !success2 ) {
            return tfpWriteNameList( pagename.Mid( 3 ), recSG_Individual );
        }
        if( name.compare( 0, 3, "NP+" ) == 0 && !success2 ) {
            return tfpWriteNameList( pagename.Mid( 3 ), recSG_Persona );
        }
        if( name.compare( 0, 1, "N" ) == 0 && success ) {
            return tfpWriteName( num );
        }
        if( name.compare( 0, 2, "PA" ) == 0 ) {
            return tfpWritePersonaPage( num1 );
        }
        if( name.compare( 0, 1, "P" ) == 0 && success ) {
            return tfpWritePlace( num );
        }
        if( name.compare( "R" ) == 0 ) {
            return tfpWriteReferenceIndex( dbname );
        }
        if( name.compare( 0, 2, "R," ) == 0 && success1 ) {
            return tfpWriteReferencePagedIndex( num1, dbname );
        }
        if( name.compare( 0, 1, "R" ) == 0 && success ) {
            return tfpWriteReferencePage( num, dbname );
        }
        if( name.compare( "RE" ) == 0 ) {
            return tfpWriteResearcherList();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
    }

    return tfpWrErrorPage( name );
}

// End of src/tfp/tfpWr.cpp Source
