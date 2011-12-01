/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpVersion.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Version constants, functions and revision history.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     24 September 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#include "tfpVersion.h"

#ifdef _DEBUG
#define VERSION   wxS("0.3.0.1 alpha debug")
#else
#define VERSION   wxS("0.3.0.1 alpha")
#endif

/*! A string containing the current version number.
 */
const wxChar* tfpVersion = VERSION;

/*! A string containing a long hand version name and copyright message.
 */
const wxChar* tfpTitle = wxS("The Family Pack - Version ") VERSION wxS("\n")
                         wxS("Copyright (c) 2010, 2011 Nick Matthews\n\n" );

/*************************************************************************//**

 \file

 Program: The Family Pack.  Store and display genealogical data.

 Source code revision history

 27apr05  v0.1.0    Initial version of "The Family" for DOS. Not released.
                    Writes family tree charts in HTML from a given GEDCOM file.

 17dec05  v0.2.0    Version of "The Family Pack" for Win32 command line. Not released.

 30aug07  v0.3.0.0  Pre-alpha test version for wxWidgets (MSW). Not released

 Active   v0.3.0.1  First public alpha version


Routemap

 v0.3.0.x     Alpha versions developing a working database definition

 v0.3.1       First public beta version

 From this point the versioning sytem will use a Major, Minor, Revision system
 where an even Minor number indicates a stable release with only (mostly?) bug
 fixes applied, whilst odd Minor numbers are used for developing new features
 and are therefore less stable.

 v0.3.x       Beta versions developing a working User Interface

 v0.4.0       First usable beta (From this point, Databases will be maintained
              across upgrades)

 v0.4.x       Bug fixes to v0.4.0

 v0.5.x       Further development

 v1.0.0       First completed stable version

***************************************************************************/

/*! Returns a string representing the compiler name and version.
 *  Only working for Visual C++ so far.
 */
wxString tfpGetCompilerVersion()
{
#ifdef __VISUALC__
    return wxString::Format( wxT("Visual C++ version %d"), __VISUALC__ );
#else
    return wxT("Unknown compiler");
#endif
}

// End of tfpVersion.cpp Source
