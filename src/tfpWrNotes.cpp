/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrNotes.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to write html notes to screen.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 January 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recRelationship.h>
#include <rec/recPersona.h>

#include "tfpWr.h"

namespace { 

wxString GetHtmDateData( const recDate& date )
{
    wxString htm;
        
    htm << date.GetStr() << "<br><br>"
           "Original Scheme: " << CalendarSchemeName[date.f_record_sch] << "<br>"
           "Display Scheme: " << CalendarSchemeName[date.f_display_sch] << "<br>";

    if( date.f_rel_id ) {
        recRelativeDate rel( date.f_rel_id );
        recDate base( rel.f_base_id );
        htm << "<br>Base on " << base.GetIdStr() << "<br>"
            << GetHtmDateData( base );
    }
    return htm;
}

} // namespace

#if 0
wxString tfpWriteAttribute( idt attrID )
{
#if 0
    wxString htm;
    recAttribute attr(attrID);
    if( attr.f_id == 0 ) return wxEmptyString;

    htm << "<html><head><title>Place</title></head><body>"
           "<h1>Attribute " << attr.GetIdStr() << "</h1>"
        << recAttributeType::GetTypeStr( attr.f_type_id )
        << ": " << attr.f_val
       
        << "</body></html>";

    return htm;
#endif
    wxString htm;

    htm << "<html><head><title>Place</title></head><body>"
           "<h1>Attribute </h1>"
           "</body></html>";

    return htm;
}
#endif

wxString tfpWriteDate( idt dateID )
{
    wxString htm;
    recDate date(dateID);
    if( date.f_id == 0 ) return wxEmptyString;

    htm << "<html><head><title>Date</title></head><body>"
           "<h1>Date " << date.GetIdStr() << "</h1>"
        << GetHtmDateData( date );
       
    htm << "</body></html>";

    return htm;
}

wxString tfpWritePlace( idt placeID )
{
    wxString htm;
    recPlace place(placeID);
    if( place.f_id == 0 ) return wxEmptyString;

    htm << "<html><head><title>Place</title></head><body>"
           "<h1>Place " << place.GetIdStr() << "</h1>"
        << place.GetAddressStr();
       
    htm << "</body></html>";

    return htm;
}

wxString tfpWriteRelationship( idt rsID )
{
    wxString htm;
    recRelationship rs(rsID);
    if( rs.f_id == 0 ) return wxEmptyString;

    htm << "<html><head><title>Relationship</title></head><body>"
           "<h1>Relationship " << rs.GetIdStr() << "</h1>"
        << recPersona::GetIdStr( rs.f_per1_id ) << " and "
        << recPersona::GetIdStr( rs.f_per2_id ) << " have the relationship "
        << rs.f_descrip << ", so:<br><br>"
        << rs.GetValue1Str() << "<br><br>"
        << rs.GetValue2Str()
           
        << "</body></html>";

    return htm;
}

// End of tfpWrNote.cpp Source
