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

    if( date.f_base_id ) {
        recDate base( date.f_base_id );
        htm << "<br>Base on " << base.GetIdStr() << "<br>"
            << GetHtmDateData( base );
    }
    return htm;
}

} // namespace

wxString tfpWriteAttribute( idt attrID )
{
    wxString htm;
    recAttribute attr(attrID);
    if( attr.f_id == 0 ) return wxEmptyString;

    htm << "<html><head><title>Place</title></head><body>"
           "<h1>Attribute " << attr.GetIdStr() << "</h1>"
        << recAttributeType::GetTypeStr( attr.f_type_id )
        << ": " << attr.f_val
       
        << "</body></html>";

    return htm;
}

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


wxString tfpGetDisplayText( const wxString& name )
{
    wxUniChar uch, uch1;
    wxLongLong_t num;
    bool success;

    uch = name.GetChar( 0 );
    switch( uch.GetValue() )
    {
    case 'A':  // Attribute
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Attribute ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteAttribute( num );
    case 'C':  // Chart reference
        success = name.Mid(2).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Individual ID link"), _("Link Error") );
            return wxEmptyString;
        }
        switch( (wxChar) name.GetChar( 1 ) )
        {
        case 'D':
            return tfpCreateDescChart( num );
        case 'P':
            return tfpCreatePedChart( num );
        }
        wxMessageBox( _("Error: Invalid Chart link reference"), _("Link Error") );
        return wxEmptyString;
    case 'D':  // Date
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Date ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteDate( num );
    case 'E':  // Reference Document
        if( name == "E" ) {
            return tfpWriteEventIndex();
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Reference Document ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteEventPage( num );
    case 'F':  // Family reference
        if( name.GetChar( 1 ) == 'I' ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success || num < 1 ) {
                wxMessageBox( _("Error: Invalid Individual ID link"), _("Link Error") );
                return wxEmptyString;
            }
            return tfpWriteIndFamilyPage( num );
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Family ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteFamilyPage( num );
    case 'I':  // Individual reference
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Individual ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteIndividualPage( num );
    case 'N':  // Name index
        if( name == "N" ) {
            return tfpWriteIndividualIndex();
        }
        if( name == "N*" ) {
            return tfpWriteIndividualList( wxEmptyString );
        }
        return tfpWriteIndividualList( name.Mid( 1 ) );
    case 'P':  // Place
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Place ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWritePlace( num );
    case 'R':  // Reference Document
        if( name == "R" ) {
            return tfpWriteReferenceIndex();
        }
        uch1 = name.GetChar( 1 );
        if( !wxIsdigit( uch1 ) ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                wxMessageBox( _("Error: Invalid ID link"), _("Link Error") );
                return wxEmptyString;
            }
            switch( uch1.GetValue() )
            {
            case 's':
                return tfpWriteRelationship( num );
            default:
                wxMessageBox( _("Error: Invalid ID link"), _("Link Error") );
                return wxEmptyString;
            }
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            wxMessageBox( _("Error: Invalid Reference Document ID link"), _("Link Error") );
            return wxEmptyString;
        }
        return tfpWriteReferencePage( num );
    }
    wxMessageBox( _("Error: Invalid Display Name ")+name, _("Link Error") );
    return wxEmptyString;
}

// End of tfpWrNote.cpp Source
