/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfpWr.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write html display screens.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     11th November 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
 * Website:     http://thefamilypack.org
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


wxString tfpGetDisplayText( const wxString& name )
{
    wxUniChar uch, uch1;
    wxLongLong_t num;
    bool success;
    wxString ErrorPage = "<html><head><title>Error</title></head>"
        "<body><h1>Error writing [%s]</h1><p>%s</p></body></html>";

    wxASSERT( name.size() > 0 );
    uch = name.GetChar( 0 );
    switch( uch.GetValue() )
    {
    case 'C':  // Chart reference
        success = name.Mid(2).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format(
                ErrorPage, name, _("Invalid Individual ID link")
            );
        }
        switch( (wxChar) name.GetChar( 1 ) )
        {
        case 'D':
            return tfpCreateDescChart( num );
        case 'P':
            return tfpCreatePedChart( num );
        }
        return wxString::Format(
            ErrorPage, name, _("Invalid Chart link reference")
        );
    case 'D':  // Date
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format(
                ErrorPage, name, _("Invalid Date ID link")
            );
        }
        return tfpWriteDate( num );
    case 'E':  // Reference Document
        if( name == "E" ) {
            return tfpWriteEventIndex();
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format(
                ErrorPage, name, _("Invalid Reference Document ID link")
            );
        }
        return tfpWriteEventPage( num );
    case 'F':  // Family reference
        if( name.GetChar( 1 ) == 'I' ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                return wxString::Format(
                    ErrorPage, name, _("Invalid Individual ID link")
                );
            }
            return tfpWriteIndFamilyPage( num );
        }
        return tfpWriteFamilyPage( name.Mid(1) );
    case 'I':  // Individual reference
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format(
                ErrorPage, name, _("Invalid Individual ID link")
            );
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
            return wxString::Format(
                ErrorPage, name, _("Invalid Place ID link")
            );
        }
        return tfpWritePlace( num );
    case 'R':  // Reference Document
        if( name == "R" ) {
            return tfpWriteReferenceIndex();
        }
        if( name == "Re" ) {
            return tfpWriteResearcherList();
        }
        uch1 = name.GetChar( 1 );
        if( !wxIsdigit( uch1 ) ) {
            success = name.Mid(2).ToLongLong( &num );
            if( !success ) {
                return wxString::Format(
                    ErrorPage, name, _("Invalid ID link")
                );
            }
            switch( uch1.GetValue() )
            {
            case 's':
                return tfpWriteRelationship( num );
            default:
                return wxString::Format(
                    ErrorPage, name, _("Invalid ID link")
                );
            }
        }
        success = name.Mid(1).ToLongLong( &num );
        if( !success || num < 1 ) {
            return wxString::Format(
                ErrorPage, name, _("Invalid Reference Document ID link")
            );
        }
        return tfpWriteReferencePage( num );
    }
    return wxString::Format(
        ErrorPage, name, _("Invalid Display Name")
    );
}

// End of tfpWr.cpp file

