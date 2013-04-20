/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recgui.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the rec lib GUI interface functions.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22 October 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
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

#include <wx/progdlg.h>
#include <rec/recInterface.h>
#include <rec/recVersion.h>

void recMessage( const wxString& mess, const wxString& func )
{
    wxMessageBox( mess, func );
}

void* recGetProgressDlg( const wxString& title, const wxString& message, int style )
{
    return new wxProgressDialog( title, message, 100, NULL, style );
}

bool recProgressPulse( void* progress, const wxString& message )
{
    if( progress == NULL ) return true;
    return ((wxProgressDialog*)progress)->Pulse( message );
}

void recProgressSetRange( void* progress, int maximum )
{
    if( progress ) {
        ((wxProgressDialog*)progress)->SetRange( maximum );
    }
}

bool recProgressUpdate( void* progress, int value, const wxString& message )
{
    if( progress == NULL ) return true;
    return ((wxProgressDialog*)progress)->Update( value, message );
}

void recProgressClose( void* progress )
{
    if( progress ) {
        ((wxProgressDialog*)progress)->Destroy();
    }
}

int recGetSingleChoiceIndex( const wxString& caption, const wxArrayString& choices )
{
    return wxGetSingleChoiceIndex( wxEmptyString, caption, choices );
}

bool recPermissionToUpgrade()
{
    recVersion v;
    wxString mess = wxString::Format(
        _("Upgrade database from version from V%s to V%s"), 
        v.GetVersionStr(), recVerStr
    );
    int ans = wxMessageBox( mess, _("Upgrade Database"), wxYES_NO | wxCANCEL );
    if( ans == wxYES ) {
        return true;
    }
    return false; 
}

// End of recgui.cpp file
