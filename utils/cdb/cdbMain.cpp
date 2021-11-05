/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        util/cdb/cdbMain.cpp
 * Project:     cdb: Common Database Build, Program to create TFP common data.
 * Purpose:     Build Common Database files from csv files.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     27th October 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  cdb is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  cdb is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with cdb. If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <time.h>
#include <vector>
#include <wx/ffile.h>
#include <wx/cmdline.h>
//#include <wx/sstream.h>
#include <wx/textfile.h>

#include <rec/recDb.h>

#define VERSION   "0.1.0"
#define PROGNAME  "cdb - TFP Common Database Build"

const wxString g_version = VERSION;
const wxString g_progName = PROGNAME;

#ifdef NDEBUG
const wxString g_title = PROGNAME " - Version " VERSION "\n"
                         "Copyright (c) 2021 Nick Matthews\n\n";
#else
const wxString g_title = PROGNAME " - Version " VERSION " Debug\n"
                         "Copyright (c) 2021 Nick Matthews\n\n";
#endif

bool g_verbose = false;
bool g_quiet   = false;


/*#*************************************************************************
 **  main
 **  ~~~~
 */

int main( int argc, char** argv )
{
    static const wxCmdLineEntryDesc desc[] = {
        { wxCMD_LINE_SWITCH, "h", "help", "show this help message",
            wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
        { wxCMD_LINE_SWITCH, "v", "verbose", "be verbose" },
        { wxCMD_LINE_SWITCH, "q", "quiet",   "be quiet" },
        { wxCMD_LINE_NONE }
    };

    wxInitializer initializer;
    if( !initializer )
    {
        fprintf( stderr, "Failed to initialize the wxWidgets library, aborting." );
        return EXIT_FAILURE;
    }

    wxCmdLineParser parser( desc, argc, argv );
    parser.SetLogo( g_title );

    int cmd = parser.Parse();
    if( cmd < 0 ) {
        wxUninitialize();
        return EXIT_SUCCESS;
    }
    if( cmd > 0 ) {
        wxUninitialize();
        return EXIT_FAILURE;
    }

    if( parser.Found( "q" ) ) {
        g_quiet = true;
    }

    if( true /* parser.Found( "v" ) */ ) {
        g_quiet = false;
        g_verbose = true;
    }
    recInitialize();

    if( !g_quiet ) {
        std::cout << g_title << "\n";
    }
    if( g_verbose ) {
        std::cout << "SQLite3 version: " << wxSQLite3Database::GetVersion() << "\n";
        std::cout << "Database Version: " << recFullVersion << "\n";
        std::cout << "Working Dir: " << wxGetCwd() << "\n";
    }

    // Main prog



    recUninitialize();
    wxUninitialize();
    return EXIT_SUCCESS;
}

/* End of util/cdb/cdbMain.cpp file */
