/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpVersion.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Version constants, functions and revision history.
 * Author:      Nick Matthews
 * Created:     24 September 2010
 * Copyright:   Copyright (c) 2010..2023, Nick Matthews.
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

#define VERSION_STATUS   " pre-alpha"

#ifdef _DEBUG
#define VERSION_CONFIG   " debug"
#else
#define VERSION_CONFIG   ""
#endif

#define RELEASE_NUM   " R7"
#define VERSION_NUM   "0.3.0.1.1" RELEASE_NUM


#define VERSION   VERSION_NUM VERSION_STATUS VERSION_CONFIG " " __DATE__

/*! A string containing the current full version number.
 */
const char* tfpVersion = VERSION;

/*! A string containing the current full version number formated for html.
 */
const char* tfpHtmVersion = 
    "<b>" VERSION_NUM "</b>" VERSION_STATUS VERSION_CONFIG " " __DATE__;

/*! A string containing a long hand version name and copyright message.
 */
const char* tfpTitle = "The Family Pack - Version " VERSION "\n"
                         "Copyright (c) 2010..2023 Nick Matthews\n\n";

/*************************************************************************//**

 \file

 Program: The Family Pack.  Store and display genealogical data.

 Source code revision history

 27apr05  v0.1.0    Initial version of "The Family" for DOS. Not released.
                    Writes family tree charts in HTML from a given GEDCOM file.

 17dec05  v0.2.0    Version of "The Family Pack" for Win32 command line. Not released.

 30aug07  v0.3.0.0  Pre-alpha test version for wxWidgets (MSW). Not released

 28mar13  v0.3.0.1.0  First public pre-alpha release.

 12aug21  v0.3.0.1.1 R1  Extend calendar system, add Islamic tabular calendar.
                    Split events into conclusion events "Event" and evidence
                    events "Eventa". (Other names were used and rejected.)
                    Add "Media" table to hold scans and photos.
                    Devise "Media-only" database and allow these to be attached.
                      to the "Full" database - to avoid size bloat of database.
                    Add Gallery object to show collections of photos.
                    Create  media viewer window to separately show built-in
                      photos and resize them.
                    Remove "Relationship" table.
                    Export GEDCOM file option added.
                    Page names are no longer case sensitive.

14jan22  v0.3.0.1.1 R2  Improve Create Database with new Setup Database dialog.
                    Active the source Citataion records with new dialogs.
                    Update Reference dialog which now allows for a hierarchy.

23jan22  v0.3.0.1.1 R3  Fix problems opening databases and new windows.

 4nov22  v0.3.0.1.1 R4  Add 'Windows' menu to main menu to handle multiple open
                    windows onto the database or attached databases.
                    Display attached (External) databases.
                    Compare and transfer records between databases.
                    Improve the consistant removal of records.
                    Add uid and changed fields to Reference and subordinate
                    tables.

 11dec22  v0.3.0.1.1 R5  Add Export/Import as csv and image files (for use as backup
                    and git friendly format).

 11feb23  v0.3.0.1.1 R6  Add new "Family as an Event" page to show evidence links.
                    Update the CMake build system files and use them for Windows.

  active  v0.3.0.1.1 R7 Add HistoryGen script language (based on Glich).

 See also webpage http://thefamilypack.org/dev/routemap.htm

***************************************************************************/

/*! Returns a string representing the compiler name and version.
 *  Works for Visual C++ and GCC so far.
 */
wxString tfpGetCompilerVersion()
{
#if defined(__VISUALC__)
    return wxString::Format( _("Visual C++ version %d"), __VISUALC__ );
#elif defined(__GNUC__)
    return wxString::Format( 
        _("GCC compiler version %d.%d.%d"),
        __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__
    );
#else
    return _("Unknown compiler");
#endif
}

// End of tfpVersion.cpp Source
