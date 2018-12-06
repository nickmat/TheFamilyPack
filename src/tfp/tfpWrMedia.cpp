/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWrMedia.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Media functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3rd November 2018
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

// End of src/tfp/tfpWrMedia.cpp Source
