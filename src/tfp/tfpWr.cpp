/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWr.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write HTML screen support functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21st January 2013
 * Copyright:   Copyright (c) 2013 ~ 2018, Nick Matthews.
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

#include <rec/recContact.h>
#include <rec/recIndividual.h>
#include <rec/recMediaData.h>
#include <rec/recSystem.h>
#include <rec/recUser.h>

#include <wx/fs_mem.h>
#include <wx/mstream.h>
#include <wx/tokenzr.h>

wxString tfpWrHeadTfp( const wxString& title, const wxString& css )
{
    wxString htm;
    htm <<
        "<!DOCTYPE html>\n"
        "<html>\n<head>\n"
        "<title>" << title << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
    ;
    if( css.size() ) {
        wxStringTokenizer tokenizer( css, ";" );
        while ( tokenizer.HasMoreTokens() ) {
            wxString file = tokenizer.GetNextToken();
            htm <<
                "<link rel='stylesheet' type='text/css' href='memory:" << file <<
                ".css'>\n"
            ;
        }
    }
    htm << "</head>\n<body>\n<div class='tfp'>\n";
    return htm;
}

wxString tfpWrTailTfp()
{
    return "</div>\n</body>\n</html>\n";
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

wxString tfpGetIndSexClass( idt indID, Sex pref )
{
    return tfpGetSexClass( recIndividual::GetSex( indID ), pref );
}

wxString tfpGetSexClass( Sex sex, Sex pref )
{
    if( sex == SEX_Unstated ) {
        sex = pref;
    }
    switch( sex ) {
    case SEX_Male: 
        return "male";
    case SEX_Female: 
        return "fem";
    }
    return "neut";
}

wxString tfpGetRowClass( int row )
{
    return ( row % 2 ) ? "odd" : "even";
}

wxString tfpGetEpitaphPlus( idt indID,  GET_EPITAPH_Prefix prefix )
{
    wxString epitaph = recIndividual::GetEpitaph( indID );
    wxString prefixStr;

    if( epitaph.size() ) {
        switch( prefix )
        {
        case GE_Spaces:
            prefixStr = "&nbsp;&nbsp;";
            break;
        case GE_NewLine:
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

wxString tfpGetMediaDataFile( idt mdID, idt assID )
{
    assert( assID == 0 );
    wxString filename = recMediaData::GetFileName( mdID ) + ".bmp";
    // Read into the virtual file system, unless it already exists.
    wxFileSystem fs;
    wxString memfilename = "memory:" + filename;
    wxString fn = fs.FindFirst( memfilename );
    if ( fn.empty() ) {
        recMediaData md( mdID );
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

// End of src/tfp/tfpWr.cpp Source
