/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        util/doccore/dcMain.cpp
 * Project:     DocCore: Program to create webpage documenting TFP common data.
 * Purpose:     The source file for the create core data tables program.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25th November 2012
 * Copyright:   Copyright (c) 2012 ~ 2018, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  doccore is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  doccore is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with doccore.  If not, see <http://www.gnu.org/licenses/>.
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

#include <time.h>
#include <vector>
#include <wx/ffile.h>
#include <wx/cmdline.h>
//#include <wx/sstream.h>
#include <wx/textfile.h>

#include <rec/recDb.h>

#define VERSION   "0.2.1"
#define PROGNAME  "doccore - Create core data html tables"

const wxString g_version = VERSION;
const wxString g_progName = PROGNAME;

#ifdef NDEBUG
const wxString g_title = PROGNAME " - Version " VERSION "\n"
                         "Copyright (c) 2012 ~ 2018 Nick Matthews\n\n";
#else
const wxString g_title = PROGNAME " - Version " VERSION " Debug\n"
                         "Copyright (c) 2012 ~ 2018 Nick Matthews\n\n";
#endif

bool g_verbose = false;
bool g_quiet   = false;


wxString GetFileContents( const wxString& filename )
{
    wxString text;
    wxTextFile file( filename );
    file.Open();
    for ( ;;) {
        text += file.GetNextLine();
        if ( file.Eof() ) {
            break;
        }
        text += "\n";
    }
    return text;
}

wxString GetHtmBeg( const wxString& existing )
{
    size_t pos = existing.find( "<div id='content'" );
    if ( pos == wxString::npos ) {
        return wxString();
    }
    wxString htm = existing.substr( 0, pos );
    htm <<
        "<div id='content'>\n\n"
        "<blockquote>\n"
        "<p>\n"
        "<!-- Quote -->\n"
        "</p>\n"
        "<p class='attribute'><!-- Attr --></p>\n"
        "</blockquote>\n\n"
        ;
    return htm;
}

wxString GetHtmEnd( const wxString& existing )
{
    size_t pos = existing.find( "</div><!--id=content-->" );
    if ( pos == wxString::npos ) {
        return wxString();
    }
    return existing.substr( pos );
}

wxString WrTblEventType( int* order )
{
    wxString htm;
    htm <<
        "<table class='basic core'>\n"
        "<tr><th colspan='4'>EventType Core Data</th></tr>\n"
        "<tr><th>[id]</th><th>[grp]</th><th>[name]</th><th></th></tr>\n"
        "<tr><td>0</td><td>NULL</td><td>NULL</td><td>Place holder for invalid Event Type.</td></tr>\n"
    ;
    for( size_t i = 0 ; order[i] != 0 ; i++ ) {
        unsigned flag = 0x0001 << order[i];
        recEventTypeVec ets = recEventType::ReadVec( flag );
        for( size_t j = 0 ; j < ets.size() ; j++ ) {
            idt etID = ets[j].FGetID();
            htm << "<tr><td>" << etID 
                << "</td><td>" << ets[j].FGetGrp();
            if( j == 0 ) {
                htm << " \"" << ets[0].GetGroupStr() << "\"";
            }
            htm << "</td><td>" << ets[j].FGetName()
                << "</td><td>";
            if( etID == -19 ) {
                htm << "Marital Status";
            }
            htm << "</td></tr>\n";
        }
    }
    htm << "</table>\n";
    return htm;
}

wxString WrTblEventTypeRole( int* order )
{
    wxString htm;
    htm <<
        "<table class='basic core'>\n"
        "<tr><th colspan='5'>EventTypeRole Core Data</th></tr>\n"
        "<tr><th>[id]</th><th>[type_id]</th><th>[prime]</th><th>[official]</th><th>[name]</th></tr>\n"
        "<tr><td>0</td><td>NULL</td><td>NULL</td><td>NULL</td><td>NULL</td></tr>\n"
    ;
    for( size_t i = 0 ; order[i] != 0 ; i++ ) {
        unsigned flag = 0x0001 << order[i];
        recEventTypeVec ets = recEventType::ReadVec( flag );
        for( size_t j = 0 ; j < ets.size() ; j++ ) {
            recEventTypeRoleVec etrs = recEventType::GetRoles( ets[j].FGetID() );
            for( size_t k = 0 ; k < etrs.size() ; k++ ) {
                idt roleID = etrs[k].FGetID();
                htm << "<tr><td>" << roleID 
                    << "</td><td>" << etrs[k].FGetTypeID()
                ;
                if( k == 0 ) {
                    htm << " \"" << ets[j].FGetName() << "\"";
                }
                htm << "</td><td>" << etrs[k].FGetPrime()
                    << "</td><td>" << ( etrs[k].FGetOfficial() ? "Yes" : "" )
                    << "</td><td>" << etrs[k].FGetName()
                    << "</td></tr>\n"
                ;
            }
        }
    }
    htm << "</table>\n";
    return htm;
}

bool OutputFile( const wxString& text, const wxString& filename )
{
    wxFFile outfile;
    if( outfile.Open( filename, "w" ) ) {
        outfile.Write( text );
        return true;
    }
    return false;
}

void CreateNewDatabase()
{
    wxString fname = "./CoreDb.tfpd";
    wxRemoveFile( fname );
    bool ret = recDb::CreateDb( fname, 0 );
    wxASSERT( ret == true );
}

/*#*************************************************************************
 **  main
 **  ~~~~
 */

int main( int argc, char** argv )
{
    wxString projfn;
    wxString patchfn;
    wxString outfn;
    bool ok = true;
    static const wxCmdLineEntryDesc desc[] = {
        { wxCMD_LINE_SWITCH, "h", "help", "show this help message",
            wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
        { wxCMD_LINE_SWITCH, "v", "verbose", "be verbose" },
        { wxCMD_LINE_SWITCH, "q", "quiet",   "be quiet" },
        { wxCMD_LINE_OPTION, "O", "outfile", "output file name"},
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
    parser.Found( "O", &outfn );
    if( outfn == "" ) {
        outfn = "ets.htm";
    }
    recDb::SetDb( new wxSQLite3Database() );

    if( ! g_quiet ) {
        wxPrintf( "%s", g_title );
    }
    if( g_verbose ) {
        wxPrintf( "Output project file [%s]\n", outfn );
        wxPrintf( "SQLite3 version: %s\n", wxSQLite3Database::GetVersion() );
        wxPrintf( "Database Version %s\n", recVerStr );
    }

    int grporder[] = { 1, 2, 5, 6, 8, 9, 7, 3, 10, 4, 0 };

    CreateNewDatabase();

    wxString existing = GetFileContents( outfn );
    wxString htm;
    htm << GetHtmBeg( existing )
        << WrTblEventType( grporder ) 
        << WrTblEventTypeRole( grporder ) 
        << GetHtmEnd( existing )
        ;
    OutputFile( htm, outfn );

    if( htm.IsEmpty() ) {
        ok = false;
    }
    wxUninitialize();
    if( ok ) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/* End of util/doccore/dcMain.cpp file */
