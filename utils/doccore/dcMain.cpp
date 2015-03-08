/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        util/doccore/dcMain.cpp
 * Project:     DocCore: Program to create webpage documenting TFP common data.
 * Purpose:     The source file for the create core data tables program.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     25th November 2012
 * Copyright:   Copyright (c) 2012 - 2014, Nick Matthews.
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
#include <rec/recDb.h>

#define VERSION   "0.1.0"
#define PROGNAME  "doccore - Create core data html tables"

const wxString g_version = VERSION;
const wxString g_progName = PROGNAME;

#ifdef NDEBUG
const wxString g_title = PROGNAME " - Version " VERSION "\n"
                         "Copyright (c) 2012 Nick Matthews\n\n";
#else
const wxString g_title = PROGNAME " - Version " VERSION " Debug\n"
                         "Copyright (c) 2012 Nick Matthews\n\n";
#endif

bool g_verbose = false;
bool g_quiet   = false;

struct NavPair {
    NavPair( const wxString& p, const wxString& n ) : path(p), name(n) {}
    wxString path;
    wxString name;
};
typedef std::vector<NavPair> NavVec;

/***************************************************************************
 **  GetTodayStr  Return the current date as a htm marked up string.
 **  ~~~~~~~~~~~  
 */

wxString GetTodayStr()
{
    static wxString month[] = { 
        "January", "Febuary", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    time_t now;
    time( &now );
    struct tm* tp = localtime( &now );
    wxString str;

    str << tp->tm_mday
        << "<sup>";

    switch( tp->tm_mday )
    {
    case 1: case 21: case 31:
        str << "st";
        break;
    case 2: case 22:
        str << "nd";
        break;
    case 3: case 23:
        str << "rd";
        break;
    default:
        str << "th";
    }
    str << "</sup> "
        << month[ tp->tm_mon ]
        << " " 
        << tp->tm_year + 1900;

   return str;
}

wxString GetHtmBeg( const wxString& title, int level, const NavVec& nps )
{
    wxString lstr;
    for( int i = 0 ; i < level ; i++ ) {
        lstr << "../";
    }
    wxString htm;
    htm <<
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">"
        "<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>\n"
        "<head>\n"
        "<title>TFPD - " << title << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />\n"
        "<meta name='Generator' content='doccore from The Family Pack' />\n"
        "<link rel='icon' type='image/png' href='" << lstr << "logo1.png' />\n"
        "<link rel='stylesheet' type='text/css' href='" << lstr << "tfp.css' />\n"
        "</head>\n"
        "<body>\n"
        "<h1><a  href='" << lstr << "index.htm'><img id='logo' src='" << lstr << "tfp5.gif' alt='Logo' /></a>\n"
        "The Family Pack<br/>Core Data: Event Types</h1>\n"
        "<div id='page' class='database'>\n"
        "<div id='crumbs'>\n"
    ;
    for( size_t i = 0 ; i < nps.size() ; i++ ) {
        wxString lclass;
        if( i > 0 ) lclass << " level" << i; 
        htm << "<a href='" << nps[i].path 
            << "' class='m-item";
        if( i+3 == nps.size() ) htm << lclass << " thispage";
        else if( i+2 == nps.size() ) htm << " prev";
        else if( i+1 == nps.size() ) htm << " next";
        else htm << lclass;
        htm << "'>" << nps[i].name << "</a>\n";
    }
    htm << "</div>\n<div id='content' class='nomenu'>\n\n"
        "<blockquote>\n"
        "<p>\n"
        "<!-- Quote -->\n"
        "</p>\n"
        "<p class='attribute'><!-- Attr --></p>\n"
        "</blockquote>\n\n"
    ;
    return htm;
}

wxString GetHtmEnd( int level )
{
    wxString lstr;
    for( int i = 0 ; i < level ; i++ ) {
        lstr << "../";
    }
    wxString htm;
    htm << "</div>\n"
        "<hr />\n"
        "<div id='valid'>\n"
        "<p>\n"
        "<a href='http://validator.w3.org/check?uri=referer'><img\n"
        "src='" << lstr << "valid-xhtml10-blue.png'\n"
        "alt='Valid XHTML 1.0 Strict' height='31' width='88' /></a>\n"
        "</p>\n"
        "</div>\n"
        "<div id='create-date'><p>" << GetTodayStr() << "</p></div>\n"
        "</div>\n"
        "<!-- Start of StatCounter Code for Default Guide -->\n"
        "<script type=\"text/javascript\">\n"
        "/*<![CDATA[*/\n"
        "var sc_project=9849896;\n"
        "var sc_invisible=1;\n"
        "var sc_security=\"8230fdb2\";\n"
        "var scJsHost = ((\"https:\" == document.location.protocol) ?\n"
        "\"https://secure.\" : \"http://www.\");\n"
        "document.write(\"<sc\"+\"ript type='text/javascript' src='\" +\n"
        "scJsHost+\n"
        "\"statcounter.com/counter/counter.js'></\"+\"script>\");\n"
        "/*]]>*/\n"
        "</script>\n"
        "<noscript><div class=\"statcounter\"><a title=\"free hit\n"
        "counters\" href=\"http://statcounter.com/\"\n"
        "target=\"_blank\"><img class=\"statcounter\"\n"
        "src=\"http://c.statcounter.com/9849896/0/8230fdb2/1/\"\n"
        "alt=\"free hit counters\" /></a></div></noscript>\n"
        "<!-- End of StatCounter Code for Default Guide -->\n"

        "</body>\n</html>\n"
    ;
    return htm;
}

wxString WrTblEventType( int* order )
{
    wxString htm;
    htm <<
        "<table class='basic core'>\n"
        "<tr><th colspan='0'>EventType Core Data</th></tr>\n"
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
        "<tr><th colspan='0'>EventTypeRole Core Data</th></tr>\n"
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
    NavVec nps;
    nps.push_back( NavPair( "../../index.htm", "Home" ) );
    nps.push_back( NavPair( "../common.htm", "Common Data" ) );
    nps.push_back( NavPair( "core.htm", "Core" ) );
    nps.push_back( NavPair( "ets.htm", "Event Types" ) );
    nps.push_back( NavPair( "core.htm", "&lt;&lt;" ) );
    nps.push_back( NavPair( "../place/places.htm", "&gt;&gt;" ) );

    wxString htm;
    htm << GetHtmBeg( "Core Data: Event Types", 2, nps )
        << WrTblEventType( grporder ) 
        << WrTblEventTypeRole( grporder ) 
        << GetHtmEnd( 2 );
    OutputFile( htm, outfn );

    if( htm.IsEmpty() ) {
        ok = false;
    }
    delete recDb::GetDb();
    wxUninitialize();
    if( ok ) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/* End of util/doccore/dcMain.cpp file */
