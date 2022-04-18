/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        test/tdb/tdbMain.cpp
 * Project:     tdb: Create and Manage Test Database.
 * Purpose:     Create and ombine csv storage files for Test Database
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     16th April 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  tdb is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  tdb is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tdb. If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/dir.h>
#include <wx/fileconf.h>

#include <rec/recDb.h>

#include <set>
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::set;

#define VERSION   "0.1.0"
#define PROGNAME  "tdb: Manage Test Database"
#define COPYRIGHT  "2022 Nick Matthews"

const char* g_version = VERSION;
const char* g_progName = PROGNAME;
const char* g_copyright = "Copyright (c) " COPYRIGHT "\n";

#if defined(NDEBUG) || !defined(_DEBUG)
const char* g_title = PROGNAME " - Version " VERSION "\n";
#else
const char* g_title = PROGNAME " - Version " VERSION " Debug\n";
#endif

enum class Table {
    t_null, t_Contact, t_ContactList, t_ContactType, t_Reference, t_Researcher
};

constexpr const char* TablePrefixes[] = {
    "", "C", "CL", "CT", "R", "Re"
};

constexpr const char* TableNames[] = {
    "null", "Contact", "ContactList", "ContactType", "Reference", "Researcher"
};

constexpr size_t tables_size = sizeof( TableNames ) / sizeof( char* );

struct RecordId {
    RecordId() : table( Table::t_null ), id( 0 ) {}

    Table table;
    idt id;
};

std::string TableName( Table table )
{
    return TableNames[static_cast<size_t>(table)];
}

Table TableFromName( const char* name )
{
    for( size_t i = 0; i < tables_size; i++ ) {
        if( strcmp( TableNames[i], name ) == 0 ) {
            return static_cast<Table>(i);
        }
    }
    return Table::t_null;
}

RecordId GetRecordId( const string& str )
{
    RecordId rid;
    size_t pos = 0;
    for( auto ch : str ) {
        if( isalpha( ch ) ) pos++;
        else break;
    }
    for( size_t i = 0; i < tables_size; i++ ) {
        if( str.compare( 0, pos, TablePrefixes[i] ) == 0 ) {
            rid.table = static_cast<Table>(i);
            break;
        }
    }
    rid.id = recGetID( str.substr( pos, string::npos ) );
    return rid;
}

inline RecordId GetRecordId( const wxString& str )
{
    return GetRecordId( string( str ) );
}

class DataSet
{
public:
    void Create( const wxString& records )
    {
        RecordId rid = GetRecordId( records );
        switch( rid.table )
        {
        case Table::t_Contact:
            InsertContact( rid.id );
            break;
        case Table::t_ContactList:
            InsertContactList( rid.id );
            break;
        case Table::t_ContactType:
            InsertContactType( rid.id );
            break;
        case Table::t_Reference:
            InsertReference( rid.id );
            break;
        case Table::t_Researcher:
            InsertResearcher( rid.id );
            break;
        }
    }
    bool WriteCsv( const string& folder ) {
        m_csv_folder = folder;
        bool ret = true;
        ret = ret && WriteTable<recContact>( m_contact );
        ret = ret && WriteTable<recContactList>( m_contact_list );
        ret = ret && WriteTable<recContactType>( m_contact_type );
        ret = ret && WriteTable<recReference>( m_reference );
        ret = ret && WriteTable<recResearcher>( m_researcher );
        return ret;
    }

    void InsertContact( idt conID ) {
        m_contact.insert( conID );
        recContact con( conID );
        InsertContactType( con.FGetTypeID() );
    }
    void InsertContactList( idt clID ) {
        m_contact_list.insert( clID );
        recIdVec conIDs = recContactList::GetContactIDs( clID );
        for( auto conID : conIDs ) {
            InsertContact( conID );
        }
    }
    void InsertContactType( idt ctID ) {
        m_contact_type.insert( ctID );
    }
    void InsertReference( idt refID ) {
        m_reference.insert( refID );
        recReference ref( refID );
        idt higherID = ref.FGetHigherID();
        if( higherID != 0 ) {
            InsertReference( higherID );
        }
        idt resID = ref.FGetResID();
        if( resID != 0 ) {
            InsertResearcher( resID );
        }
        // TODO: A lot more records to add.
    }
    void InsertResearcher( int resID ) {
        m_researcher.insert( resID );
        recResearcher res( resID );
        idt clID = res.FGetConListID();
        if( clID != 0 ) {
            InsertContactList( clID );
        }
    }

private:  
    template <class T>
    bool WriteTable( const set<idt>& list )
    {
        if( list.empty() ) {
            return true;
        }
        string fname = m_csv_folder + T::TableName() + ".csv";
        std::ofstream ofile( fname, std::ios::trunc );
        if( !ofile ) {
            return false;
        }
        ofile << T::CsvTitles();
        for( idt id : list ) {
            T::CsvWrite( ofile, id );
        }
        return true;
    }

    string   m_csv_folder;
    set<idt> m_contact;
    set<idt> m_contact_list;
    set<idt> m_contact_type;
    set<idt> m_reference;
    set<idt> m_researcher;
};

template <class T>
bool EnterTable( const std::string& folder )
{
    string fname = folder + T::TableName() + ".csv";
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

int main( int argc, char** argv )
{
    string configfname;
    for( int i = 1; i < argc; i++ ) {
        string arg = argv[i];
        if( arg == "--version" ) {
            std::cout << g_title;
            continue;
        }
        if( arg == "--help" || arg == "-h" ) {
            std::cout << "Usage not yet written";
            continue;
        }
        configfname = arg;
    }

    wxInitializer initializer;
    recInitialize();

    DataSet dset;

    wxFileName configName( configfname );
    configName.MakeAbsolute();
    if( !configName.FileExists() ) {
        std::cout << "Input file \"" << configName.GetFullPath() << "\" not found.\n";
        return EXIT_FAILURE;
    }
    wxFileConfig conf( "", "", configName.GetFullPath(), "", wxCONFIG_USE_LOCAL_FILE );

    wxString inDbFile = conf.Read( "/Input/Input-Database" );
    wxString inRecords = conf.Read( "/Input/Records" );
    wxString csvFolder = conf.Read( "/Csv/Folder" );
    if( !csvFolder.empty() && *csvFolder.rbegin() != '/' ) {
        csvFolder += "/";
    }
    wxString outDbFile = conf.Read( "/Output/Output-Database" );

    if( recDb::OpenDb( inDbFile ) == recDb::DbType::full ) {
        dset.Create( inRecords );
        if( wxDir::Exists( csvFolder ) ) {
            wxDir::Remove( csvFolder, wxPATH_RMDIR_RECURSIVE );
        }
        wxDir::Make( csvFolder );
        wxDir csv( csvFolder );
        dset.WriteCsv( string(csvFolder) );
        recDb::CloseDb();
    }
    if( wxDir::Exists( csvFolder ) ) {
        if( wxFileExists( outDbFile ) ) {
            wxRemoveFile( outDbFile );
        }
        recDb::DbType dbtype = recDb::DbType::full;
        recDb::CreateReturn create_ret = recDb::CreateDbFile( outDbFile, dbtype );
        if( create_ret != recDb::CreateReturn::OK ) {
            std::cout << "Unable to create Output file \"" << outDbFile << "\"\n";
            return EXIT_FAILURE;
        }
        if( recDb::OpenDb( outDbFile ) != dbtype ) {
            std::cout << "Error opening output database file\n";
            return EXIT_FAILURE;
        }
        bool ret = true;
        string folder = string( csvFolder );
        ret = ret && EnterTable<recContactList>( folder );
        ret = ret && EnterTable<recContactType>( folder );
        ret = ret && EnterTable<recContact>( folder );
        ret = ret && EnterTable<recReference>( folder );
        ret = ret && EnterTable<recResearcher>( folder );
        if( !ret ) {
            std::cout << "Error entering output database.\n";
            return EXIT_FAILURE;
        }
    }

    recUninitialize();
    return EXIT_SUCCESS;
}


/* End of test/tdb/tdbMain.cpp file */
