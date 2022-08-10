/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        util/cdm/cdmMain.cpp
 * Project:     cdm: Common Data Management.
 * Purpose:     Create csv storage files fo TFP Common Data
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     27th October 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  cdm is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  cdm is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with cdm. If not, see <http://www.gnu.org/licenses/>.
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
#include <wx/textfile.h>

#include <rec/recDb.h>

#include <iostream>
#include <fstream>

#define VERSION   "0.1.0"
#define PROGNAME  "cdm - TFP Common Data Management"

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

using TableMap = std::map<std::string, idt>;

template <class T>
idt RenumberTable( idt next_id ) {
    recIdVec pos_ids = T::PositiveIDs();
    for( idt id : pos_ids ) {
        T::Renumber( id, next_id );
        --next_id;
    }
    return next_id;
}

template <class T>
bool WriteTable( const std::string& fname, idt start_id )
{
    std::ofstream ofile( fname, std::ios::app );
    if( !ofile ) {
        return false;
    }
    if( ofile.tellp() == 0 ) {
        ofile << T::CsvTitles();
    }
    while( T::Exists( start_id ) ) {
        T::CsvWrite( ofile, start_id );
        --start_id;
    }
    return true;
}

TableMap ReadMasterList( std::string& titles)
{
    TableMap master;
    std::ifstream infile( "tables.csv" );
    if( !infile ) {
        return master;
    }
    getline( infile, titles );

    while( !infile.eof() ) {
        std::string str;
        recCsvRead( infile, str );
        if( str.empty() ) {
            break;
        }
        idt next;
        recCsvRead( infile, next );
        master[str] = next;
    }
    return master;
}

bool WriteMasterList( const TableMap& master, const std::string& titles )
{
    std::ofstream ofile( "tables.csv", std::ios::trunc );
    if( !ofile ) {
        return false;
    }

    ofile << titles + "\n";
    for( auto ent : master ) {
        recCsvWrite( ofile, ent.first );
        recCsvWrite( ofile, ent.second, '\n' );
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
    if( true /* parser.Found( "v" ) */ ) {
        g_quiet = false;
        g_verbose = true;
    }
    recInitialize();

    if( ! g_quiet ) {
        std::cout << g_title << "\n";
    }
    if( g_verbose ) {
        std::cout << "SQLite3 version: " << wxSQLite3Database::GetVersion() << "\n";
        std::cout << "Database Version: " << recFullVersion << "\n";
        std::cout << "Working Dir: " << wxGetCwd() << "\n";
    }

    std::string titles;
    TableMap tables = ReadMasterList( titles );
    if( tables.empty() ) {
        std::cout << "\nERROR: Can't read tables.csv\n";
        return EXIT_FAILURE;
    }
    std::cout << titles << "\n";
    for( auto table : tables ) {
        std::cout << table.first << ": " << table.second << "\n";
    }
    TableMap tables_out = tables;

    wxString inputDb( "input.tfpd" );
    if( !wxFileExists( inputDb ) || recDb::OpenDb( inputDb ) != recDb::DbType::full ) {
        std::cout << "\nERROR: Can't open input.tfpd\n";
        recUninitialize();
        return EXIT_FAILURE;
    }

    recDb::Begin();
    try {
        tables_out["Citation"] = RenumberTable<recCitation>( tables["Citation"] );
        tables_out["CitationPartType"] =
            RenumberTable<recCitationPartType>( tables["CitationPartType"] );
        tables_out["CitationPart"] = RenumberTable<recCitationPart>( tables["CitationPart"] );
        tables_out["Contact"] = RenumberTable<recContact>( tables["Contact"] );
        tables_out["ContactList"] = RenumberTable<recContactList>( tables["ContactList"] );
        tables_out["ContactType"] = RenumberTable<recContactType>( tables["ContactType"] );
        tables_out["Date"] = RenumberTable<recDate>( tables["Date"] );
        tables_out["Place"] = RenumberTable<recPlace>( tables["Place"] );
        tables_out["PlacePart"] = RenumberTable<recPlacePart>( tables["PlacePart"] );
        tables_out["PlacePartType"] = RenumberTable<recPlacePart>( tables["PlacePartType"] );
        tables_out["Reference"] = RenumberTable<recReference>( tables["Reference"] );
        tables_out["ReferenceEntity"] = 
            RenumberTable<recReferenceEntity>( tables["ReferenceEntity"] );
        tables_out["RelativeDate"] = RenumberTable<recRelativeDate>( tables["RelativeDate"] );
        tables_out["Repository"] = RenumberTable<recRepository>( tables["Repository"] );
        tables_out["Researcher"] = RenumberTable<recResearcher>( tables["Researcher"] );
        recDb::Commit();
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        recUninitialize();
        return EXIT_FAILURE;
    }

    recDb::WriteCreateScript( "data/create.sql", "Main" );
    if( tables_out["Citation"] != tables["Citation"] ) {
        WriteTable<recCitation>( "data/Citation.csv", tables["Citation"] );
    }
    if( tables_out["CitationPartType"] != tables["CitationPartType"] ) {
        WriteTable<recCitationPartType>( "data/CitationPartType.csv", tables["CitationPartType"] );
    }
    if( tables_out["CitationPart"] != tables["CitationPart"] ) {
        WriteTable<recCitationPart>( "data/CitationPart.csv", tables["CitationPart"] );
    }
    if( tables_out["Contact"] != tables["Contact"] ) {
        WriteTable<recContact>( "data/Contact.csv", tables["Contact"] );
    }
    if( tables_out["ContactList"] != tables["ContactList"] ) {
        WriteTable<recContactList>( "data/ContactList.csv", tables["ContactList"] );
    }
    if( tables_out["ContactType"] != tables["ContactType"] ) {
        WriteTable<recContactType>( "data/ContactType.csv", tables["ContactType"] );
    }
    if( tables_out["Date"] != tables["Date"] ) {
        WriteTable<recDate>( "data/Date.csv", tables["Date"] );
    }
    if( tables_out["Place"] != tables["Place"] ) {
        WriteTable<recPlace>( "data/Place.csv", tables["Place"] );
    }
    if( tables_out["PlacePart"] != tables["PlacePart"] ) {
        WriteTable<recPlacePart>( "data/PlacePart.csv", tables["PlacePart"] );
    }
    if( tables_out["PlacePartType"] != tables["PlacePartType"] ) {
        WriteTable<recPlacePart>( "data/PlacePartType.csv", tables["PlacePartType"] );
    }
    if( tables_out["Reference"] != tables["Reference"] ) {
        WriteTable<recReference>( "data/Reference.csv", tables["Reference"] );
    }
    if( tables_out["ReferenceEntity"] != tables["ReferenceEntity"] ) {
        WriteTable<recReferenceEntity>( "data/ReferenceEntity.csv", tables["ReferenceEntity"] );
    }
    if( tables_out["RelativeDate"] != tables["RelativeDate"] ) {
        WriteTable<recRelativeDate>( "data/RelativeDate.csv", tables["RelativeDate"] );
    }
    if( tables_out["Repository"] != tables["Repository"] ) {
        WriteTable<recRepository>( "data/Repository.csv", tables["Repository"] );
    }
    if( tables_out["Researcher"] != tables["Researcher"] ) {
        WriteTable<recResearcher>( "data/Researcher.csv", tables["Researcher"] );
    }

    WriteMasterList( tables_out, titles );

    recUninitialize();
    wxUninitialize();
    return EXIT_SUCCESS;
}

/* End of util/cdm/cdmMain.cpp file */
