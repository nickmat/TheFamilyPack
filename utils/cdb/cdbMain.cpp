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

#include <iostream>
#include <fstream>

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

template <class T>
bool EnterTable( const std::string& fname )
{
    std::ifstream ifile( fname );
    if( !ifile ) {
        return false;
    }
    std::string titles;
    std::getline( ifile, titles ); // Get rid of the title line
    // We could check titles here to detect change in format

    bool ret = true;
    while( ret ) {
        T record( 0 );
        ret = record.CsvRead( ifile );
        if( ret ) {
            record.Save();
        }
    }
    return true;
}


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

    if( true /* parser.Found( "v" ) */ ) { // Set switches while testing
        g_quiet = false;
        g_verbose = true;
    }
    recInitialize();

    if( !g_quiet ) {
        std::cout << g_title << "\n";
    }
    if( g_verbose ) {
        std::cout << "SQLite3 version: " << wxSQLite3Database::GetVersion().c_str() << "\n";
        std::cout << "Database Version: " << recFullVersion << "\n";
        std::cout << "Working Dir: " << wxGetCwd() << "\n";
    }

    // Main prog

    // Get the create.sql script.
    std::string create_sql = recTextFileRead( "data/create.sql" );
    if( create_sql.empty() ) {
        std::cout << "Could not read create.sql file.";
        return EXIT_FAILURE;
    }

    wxString filename = "cd-test.tfpd";
    recDb::DbType dbtype = recDb::DbType::db_null;
    recDb::CreateReturn ret = recDb::CreateDbFile( filename, dbtype );
    switch( ret )
    {
    case recDb::CreateReturn::OK:
        break;
    case recDb::CreateReturn::FileExists:
        std::cout << "File already exists\n";
        return EXIT_FAILURE;
    case recDb::CreateReturn::UnknownType:
        std::cout << "Unknown database type\n";
        return EXIT_FAILURE;
    case recDb::CreateReturn::CannotOpen:
        std::cout << "Unable to create database\n";
        return EXIT_FAILURE;
    }
    if( recDb::OpenDb( filename ) != dbtype ) {
        std::cout << "Error opening database file\n";
        return EXIT_FAILURE;
    }
    try {
        recDb::GetDb()->ExecuteUpdate( create_sql.c_str() );
        recDb::CloseDb();
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        return EXIT_FAILURE;
    }
    // Reopen to check version etc.
    if( recDb::OpenDb( filename ) == recDb::DbType::db_null ) {
        std::cout << "Error creating database file\n";
        return EXIT_FAILURE;
    }

    if( g_verbose ) {
        std::cout << "Created and opened \"" << filename << "\" database file\n";
    }

    // Do all the clever stuff
    if( EnterTable<recContactType>( "data/ContactType.csv" ) ) {
        std::cout << "Reading ContactType.csv\n";
    }
    if( EnterTable<recContactList>( "data/ContactList.csv" ) ) {
        std::cout << "Reading ContactList.csv\n";
    }
    if( EnterTable<recContact>( "data/Contact.csv" ) ) {
        std::cout << "Reading Contact.csv\n";
    }
    if( EnterTable<recResearcher>( "data/Researcher.csv" ) ) {
        std::cout << "Reading Researcher.csv\n";
    }
    if( EnterTable<recRepository>( "data/Repository.csv" ) ) {
        std::cout << "Reading Repository.csv\n";
    }
    if( EnterTable<recCitationPartType>( "data/CitationPartType.csv" ) ) {
        std::cout << "Reading CitationPartType.csv\n";
    }
    if( EnterTable<recCitation>( "data/Citation.csv" ) ) {
        std::cout << "Reading Citation.csv\n";
    }
    if( EnterTable<recCitationPart>( "data/CitationPart.csv" ) ) {
        std::cout << "Reading CitationPart.csv\n";
    }
    if( EnterTable<recDate>( "data/Date.csv" ) ) {
        std::cout << "Reading Date.csv\n";
    }
    if( EnterTable<recRelativeDate>( "data/RelativeDate.csv" ) ) {
        std::cout << "Reading RelativeDate.csv\n";
    }
    if( EnterTable<recPlacePartType>( "data/PlacePartType.csv" ) ) {
        std::cout << "Reading PlacePartType.csv\n";
    }
    if( EnterTable<recPlace>( "data/Place.csv" ) ) {
        std::cout << "Reading Place.csv\n";
    }
    if( EnterTable<recPlacePart>( "data/PlacePart.csv" ) ) {
        std::cout << "Reading PlacePart.csv\n";
    }
    if( EnterTable<recReference>( "data/Reference.csv" ) ) {
        std::cout << "Reading Reference.csv\n";
    }
    if( EnterTable<recReferenceEntity>( "data/ReferenceEntity.csv" ) ) {
        std::cout << "Reading ReferenceEntity.csv\n";
    }

    if( g_verbose ) {
        std::cout << "Closed \"" << filename << "\" database file\n";
    }

    recUninitialize();
    wxUninitialize();
    return EXIT_SUCCESS;
}

/* End of util/cdb/cdbMain.cpp file */
