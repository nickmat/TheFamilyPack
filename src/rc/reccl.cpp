/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/reccl.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the rec lib command line interface functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22 October 2012
 * Copyright:   Copyright (c) 2012..2021, Nick Matthews.
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

#include <rec/recInterface.h>

void recMessage( const wxString& mess, const wxString& func )
{
    wxPrintf( "%s: %s\n", func, mess );
}

void* recGetProgressDlg( const wxString& title, const wxString& message, int style )
{
    return NULL;
}

bool recProgressPulse( void* progress, const wxString& message )
{
    return true;
}

void recProgressSetRange( void* progress, int maximum )
{
    return;
}

bool recProgressUpdate( void* progress, int value, const wxString& message )
{
    return true;
}

void recProgressClose( void* progress )
{
    return;
}

int recGetSingleChoiceIndex( const wxString& caption, const wxArrayString& choices )
{
    return 0;
}

bool recPermissionToUpgrade( const wxString& from, const wxString& to )
{
    return false; // Can't upgrade from the command line.
}

// End of reccl.cpp file
