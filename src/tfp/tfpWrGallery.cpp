/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrGallery.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Gallery functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th October 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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
#include <rec/recGallery.h>
#include <rec/recGalleryMedia.h>
#include <rec/recMedia.h>
#include <rec/recMediaData.h>
#include <rec/recReference.h>


wxString tfpWriteGalleryList()
{
    recGalleryVec gals = recGallery::GetGalleries();

    wxString htm = tfpWrHeadTfp( "Galleries" );
    if ( gals.empty() ) {
        htm << "<h1>No Galleries Found</h1>\n";
    } else {
        htm <<
            "<h1>Gallery List</h1>\n"
            "<table class='data'>\n"
            "<tr><th>ID</th><th>Title</th></tr>\n"
        ;
        for ( auto gal : gals ) {
            htm << "<tr>\n<td><a href='tfp:G"
                << gal.FGetID()
                << "'><b>G"
                << gal.FGetID()
                << "</b></a></td>\n<td>"
                << gal.FGetTitle()
                << "</td>\n</tr>\n";
        }
        htm << "</table>\n";
    }
    htm << tfpWrTailTfp();
    return htm;
}

wxString tfpWriteGalleryPage( idt galID )
{
    wxString htm;
    recGallery gal( galID );
    if ( gal.FGetID() == 0 ) {
        return htm;
    }
    
    recGalleryMediaMediaVec gmms = gal.GetGalleryMediaMediaVec();
    bool started = false;
    htm << tfpWrHeadTfp( "Gallery " + gal.GetIdStr(), "tab" )
        << "<h1>" << gal.GetIdStr() << ": " << gal.FGetTitle() << "</h1>\n"
        << "<p>" << gal.FGetNote() << "</p>\n"
        "<table class='media'>\n"
    ;
    if ( !gal.FGetNote().empty() ) {
        htm << "<tr>\n<td colspan='3'>" << gal.FGetNote() << "</td>\n</tr>\n";
        started = true;
    }
    if ( !gmms.empty() ) {
        for ( auto gmm : gmms ) {
            if ( started ) {
                htm << "<tr>\n<td colspan='3' class='gap'>&nbsp;</td>\n</tr>\n";
            } else {
                started = true;
            }
            recMedia& med = gmm.GetMedia();
            wxString fn = tfpGetMediaDataFile( med.FGetDataID(), med.FGetAssID() );
            recReference ref( med.FGetRefID() );
            htm << "<tr>\n<td rowspan='2'><a href='tfpv:M"
                << med.FGetID()
                << "'><img src='" << fn << "' alt='' height='200' /></a></td>"
                "<td><a href='tfp:M" << med.FGetID()
                << "'><b>" << med.GetIdStr()
                << "</b></a></td>\n<td class='title'>" << gmm.GetTitle()
                << "</td>\n</tr>\n"
                "<tr>\n<td colspan='2'>" << ref.FGetStatement()
                << "</td>\n</tr>\n"
            ;
        }
    } 
    if ( !started ) {
        htm << "<tr>\n<td>Empty Gallery.</td>\n</tr>\n";
    }
    htm << "</table>\n" << tfpWrTailTfp();
    return htm;
}

// End of src/tfp/tfpWrGallery.cpp Source
