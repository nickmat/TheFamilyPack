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
    t_null, t_Citation, t_CitationPart, t_CitationPartType,
    t_Contact, t_ContactList, t_ContactType,
    t_Reference, t_Repository, t_Researcher
};

constexpr const char* TablePrefixes[] = {
    "", "Ci", "CiP", "CiPT", "C", "CL", "CT", "R", "Rp", "Re"
};

constexpr const char* TableNames[] = {
    "null", "Citation", "CitationPart", "CitationPartType",
    "Contact", "ContactList", "ContactType",
    "Reference", "Repository", "Researcher"
};

constexpr size_t tables_size = sizeof( TableNames ) / sizeof( char* );

struct RecordId {
    RecordId() : table( Table::t_null ), id( 0 ) {}

    Table table;
    idt id;
};

using RecordIdVec = std::vector<RecordId>;

struct AssociateData {
    string m_ass_filename;
    set<idt> m_ass_media_data;
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
    size_t pos = 0;
    for( auto ch : str ) {
        if( isalpha( ch ) ) pos++;
        else break;
    }
    RecordId rid;
    for( size_t i = 0; i < tables_size; i++ ) {
        if( str.compare( 0, pos, TablePrefixes[i] ) == 0 ) {
            rid.table = static_cast<Table>(i);
            break;
        }
    }
    rid.id = recGetID( str.substr( pos, string::npos ) );
    return rid;
}

RecordIdVec GetRecordIDs( const wxString& str )
{
    RecordIdVec rids;
    string records = string( str ) + ' ';
    string s;
    for( auto ch : records ) {
        if( ch == ' ' ) {
            RecordId rid = GetRecordId( s );
            rids.push_back( rid );
            s.clear();
        }
        else {
            s += ch;
        }
    }
    return rids;
}

class DataSet
{
public:
    void SetFolder( const string& folder ) { m_csv_folder = folder; }

    void Create( const wxString& records )
    {
        RecordIdVec rids = GetRecordIDs( records );
        for( RecordId& rid : rids ) {
            switch( rid.table )
            {
            case Table::t_Citation:
                InsertCitation( rid.id );
                break;
            case Table::t_CitationPart:
                InsertCitationPart( rid.id );
                break;
            case Table::t_CitationPartType:
                InsertCitationPartType( rid.id );
                break;
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
            case Table::t_Repository:
                InsertRepository( rid.id );
                break;
            case Table::t_Researcher:
                InsertResearcher( rid.id );
                break;
            }
        }
    }

    void InsertAssociate( idt assID ) {
        m_associate.insert( assID );
    }
    void InsertAssociatedMediaData( idt assID, idt mdID ) {
        m_ads[assID].m_ass_media_data.insert(mdID);
    }
    void SetAssociatedFileName( idt assID, string fname ) {
        m_ads[assID].m_ass_filename = fname;
    }
    void InsertCitation( idt citID ) {
        m_citation.insert( citID );
        recCitation cit( citID );
        idt higherID = cit.FGetHigherID();
        if( higherID != 0 ) {
            InsertCitation( higherID );
        }
        idt repID = cit.FGetRepID();
        if( repID != 0 ) {
            InsertRepository( repID );
        }
        recIdVec cpIDs = recCitation::GetCitationPartIDs( citID );
        for( idt cpID : cpIDs ) {
            InsertCitationPart( cpID );
        }
    }
    void InsertCitationPart( idt cpID ) {
        m_citation_part.insert( cpID );
        recCitationPart cp( cpID );
        InsertCitationPartType( cp.FGetTypeID() );
    }
    void InsertCitationPartType( idt cptID ) {
        m_citation_part_type.insert( cptID );
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
    void InsertDate( idt dateID ) {
        m_date.insert( dateID );
        recDate date( dateID );
        idt rdID = date.FGetRelID();
        if( rdID ) {
            InsertRelativeDate( rdID );
        }
    }
    void InsertEventa( idt eaID ) {
        m_eventa.insert( eaID );
        // Note dates and places are saved elsewhere
        recEventa ea( eaID );
        idt etID = ea.FGetTypeID();
        if( etID ) {
            InsertEventType( etID );
        }
        recIdVec epIDs = recEventa::GetEventaPersonaIDs( eaID );
        for( idt epID : epIDs ) {
            InsertEventaPersona( epID );
        }
    }
    void InsertEventaPersona( idt epID ) {
        m_eventa_persona.insert( epID );
        recEventaPersona ep( epID );
        idt etrID = ep.FGetRoleID();
        if( etrID ) {
            InsertEventTypeRole( etrID );
        }
    }
    void InsertEventType( idt etID ) {
        m_event_type.insert( etID );
    }
    void InsertEventTypeRole( idt etrID ) {
        m_event_type_role.insert( etrID );
        // EventType ID already included 
    }
    void InsertMedia( idt medID ) {
        m_media.insert( medID );
        recMedia med( medID );
        idt assID = med.FGetAssID();
        if( assID ) {
            InsertAssociate( assID );
        }
        idt mdID = med.FGetDataID();
        if( mdID ) {
            InsertAssociatedMediaData( assID, mdID );
        }
        // We don't normally include galleries.
    }
    void InsertName( idt namID ) {
        m_name.insert( namID );
        recName nam( namID );
        idt nsID = nam.FGetTypeID();
        if( nsID ) {
            InsertNameStyle( nsID );
        }
        recIdVec npIDs = recName::GetNamePartListID( namID );
        for( idt npID : npIDs ) {
            InsertNamePart( npID );
        }
    }
    void InsertNamePart( idt npID ) {
        m_name_part.insert( npID );
        recNamePart np( npID );
        idt nptID = np.FGetTypeID();
        if( nptID ) {
            InsertNamePartType( nptID );
        }
    }
    void InsertNamePartType( idt nptID ) {
        m_name_part_type.insert( nptID );
    }
    void InsertNameStyle( idt nsID ) {
        m_name_style.insert( nsID );
    }
    void InsertPersona( idt perID ) {
        m_persona.insert( perID );
        recIdVec namIDs = recPersona::GetNameListID( perID );
        for( idt namID : namIDs ) {
            InsertName( namID );
        }
    }
    void InsertPlace( idt placeID ) {
        m_place.insert( placeID );
        recPlace place( placeID );
        idt date1ID = place.FGetDate1ID();
        if( date1ID ) {
            InsertDate( date1ID );
        }
        idt date2ID = place.FGetDate2ID();
        if( date2ID ) {
            InsertDate( date2ID );
        }
        recIdVec ppIDs = recPlace::GetPlacePartIDs( placeID );
        for( idt ppID : ppIDs ) {
            InsertPlacePart( ppID );
        }
    }
    void InsertPlacePart( idt ppID ) {
        m_place_part.insert( ppID );
        recPlacePart pp( ppID );
        idt pptID = pp.FGetTypeID();
        if( pptID ) {
            InsertPlacePartType( pptID );
        }
    }
    void InsertPlacePartType( idt pptID ) {
        m_place_part_type.insert( pptID );
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
        recIdVec citIDs = recReference::GetCitationList( refID );
        for( idt citID : citIDs ) {
            InsertCitation( citID );
        }
        recIdVec medIDs = recReference::GetMediaList( refID );
        for( idt medID : medIDs ) {
            InsertMedia( medID );
        }
        recIdVec paIDs = recReference::GetPersonaList( refID );
        for( idt paID : paIDs ) {
            InsertPersona( paID );
        }
        recIdVec dateIDs = recReference::GetDateList( refID );
        for( idt dateID : dateIDs ) {
            InsertDate( dateID );
        }
        recIdVec placeIDs = recReference::GetPlaceList( refID );
        for( idt placeID : placeIDs ) {
            InsertPlace( placeID );
        }
        recIdVec entIDs = recReference::GetEntityList( refID );
        for( idt entID : entIDs ) {
            InsertReferenceEntity( entID );
        }
        recIdVec eaIDs = recReference::GetEventaList( refID );
        for( idt eaID : eaIDs ) {
            InsertEventa( eaID );
        }
    }
    void InsertReferenceEntity( idt entID ) {
        m_reference_entity.insert( entID );
        // Note, the entities referenced by this record have
        // been inserted into their respective sets separately
    }
    void InsertRelativeDate( idt rdID ) {
        m_relative_date.insert( rdID );
        recRelativeDate rd( rdID );
        idt baseID = rd.FGetBaseID();
        if( baseID ) {
            InsertDate( baseID );
        }
    }
    void InsertRepository( idt repID ) {
        m_repository.insert( repID );
        recRepository rep( repID );
        idt clID = rep.FGetConListID();
        if( clID != 0 ) {
            InsertContactList( clID );
        }
    }
    void InsertResearcher( int resID ) {
        m_researcher.insert( resID );
        recResearcher res( resID );
        idt clID = res.FGetConListID();
        if( clID != 0 ) {
            InsertContactList( clID );
        }
    }

    bool WriteCsv() {
        bool ret = WriteMediaData();
        ret = ret && WriteTableCsv<recAssociate>( m_associate );
        ret = ret && WriteTableCsv<recCitation>( m_citation );
        ret = ret && WriteTableCsv<recCitationPart>( m_citation_part );
        ret = ret && WriteTableCsv<recCitationPartType>( m_citation_part_type );
        ret = ret && WriteTableCsv<recContact>( m_contact );
        ret = ret && WriteTableCsv<recContactList>( m_contact_list );
        ret = ret && WriteTableCsv<recContactType>( m_contact_type );
        ret = ret && WriteTableCsv<recDate>( m_date );
        ret = ret && WriteTableCsv<recEventa>( m_eventa );
        ret = ret && WriteTableCsv<recEventaPersona>( m_eventa_persona );
        ret = ret && WriteTableCsv<recEventType>( m_event_type );
        ret = ret && WriteTableCsv<recEventTypeRole>( m_event_type_role );
        ret = ret && WriteTableCsv<recMedia>( m_media );
        ret = ret && WriteTableCsv<recName>( m_name );
        ret = ret && WriteTableCsv<recNamePart>( m_name_part );
        ret = ret && WriteTableCsv<recNamePartType>( m_name_part_type );
        ret = ret && WriteTableCsv<recNameStyle>( m_name_style );
        ret = ret && WriteTableCsv<recPersona>( m_persona );
        ret = ret && WriteTableCsv<recPlace>( m_place );
        ret = ret && WriteTableCsv<recPlacePart>( m_place_part );
        ret = ret && WriteTableCsv<recPlacePartType>( m_place_part_type );
        ret = ret && WriteTableCsv<recReference>( m_reference );
        ret = ret && WriteTableCsv<recReferenceEntity>( m_reference_entity );
        ret = ret && WriteTableCsv<recRelativeDate>( m_relative_date );
        ret = ret && WriteTableCsv<recRepository>( m_repository );
        ret = ret && WriteTableCsv<recResearcher>( m_researcher );
        return ret;
    }

    bool WriteTfpd() {
        bool ret = EnterAssMediaData();
        ret = ret && EnterTable<recCitation>();
        ret = ret && EnterTable<recCitationPart>();
        ret = ret && EnterTable<recCitationPartType>();
        ret = ret && EnterTable<recContact>();
        ret = ret && EnterTable<recContactList>();
        ret = ret && EnterTable<recContactType>();
        ret = ret && EnterTable<recDate>();
        ret = ret && EnterTable<recEventa>();
        ret = ret && EnterTable<recEventaPersona>();
        ret = ret && EnterTable<recEventType>();
        ret = ret && EnterTable<recEventTypeRole>();
        ret = ret && EnterTable<recMedia>();
        ret = ret && EnterTable<recName>();
        ret = ret && EnterTable<recNamePart>();
        ret = ret && EnterTable<recNamePartType>();
        ret = ret && EnterTable<recNameStyle>();
        ret = ret && EnterTable<recPersona>();
        ret = ret && EnterTable<recPlace>();
        ret = ret && EnterTable<recPlacePart>();
        ret = ret && EnterTable<recPlacePartType>();
        ret = ret && EnterTable<recReference>();
        ret = ret && EnterTable<recReferenceEntity>();
        ret = ret && EnterTable<recRelativeDate>();
        ret = ret && EnterTable<recRepository>();
        ret = ret && EnterTable<recResearcher>();
        return ret;
    }

private:
    bool WriteMediaData() {
        if( m_ads.empty() ) {
            return true;
        }
        string md_folder, image_folder, md_fname, image_fn;
        for( auto& id_set : m_ads ) {
            idt assID = id_set.first;
            if( assID == 0 ) {
                md_folder = m_csv_folder;
            }
            else {
                md_folder = m_csv_folder + "ass" + recGetStr( assID ) + "/";
                wxDir::Make( md_folder );
            }
            image_folder = md_folder + "image/";
            wxDir::Make( image_folder );

            md_fname = md_folder + recMediaData::TableName() + ".csv";
            std::ofstream md_ofile( md_fname, std::ios::trunc );
            if( !md_ofile ) {
                return false;
            }
            md_ofile << recMediaData::CsvTitles();
            for( idt mdID : id_set.second.m_ass_media_data ) {
                recMediaData md( mdID, assID );
                md.CsvWrite( md_ofile );
                image_fn = image_folder + "md" + recGetStr( mdID ) + ".jpg";
                md.ExportData( image_fn );
            }
        }
        return true;
    }

    bool EnterAssMediaData() {
        if( !EnterTable<recAssociate>() ) {
            return false;
        }
        string md_folder, image_folder, md_fname, image_fn;
        for( auto& ad : m_ads ) {
            idt assID = ad.first;
            if( assID ) {
                if( !ad.second.m_ass_filename.empty() ) {
                    recAssociate ass( assID );
                    if( ass.FGetID() == 0 ) {
                        return false;
                    }
                    ass.FSetPath( ad.second.m_ass_filename );
                    ass.Save();
                }
                md_folder = m_csv_folder + "ass" + recGetStr( assID ) + "/";
            }
            else {
                md_folder = m_csv_folder;
            }
            if( !EnterTableMediaData( assID, md_folder ) ) {
                return false;
            }
        }
        return true;
    }
    bool EnterTableMediaData( idt assID, const string& folder ) {
        wxString assdb = recAssociate::GetAttachedName( assID, "Main");

        string fname = folder + recMediaData::TableName() + ".csv";
        std::ifstream ifile( fname );
        if( !ifile ) {
            return false;
        }
        std::string titles;
        std::getline( ifile, titles ); // Get rid of the title line
        // We could check titles here to detect change in format

        bool ret = true;
        while( ret ) {
            recMediaData md( 0 );
            ret = md.CsvRead( ifile );
            if( ret ) {
                idt mdID = md.FGetID();
                wxString mdimage = folder + "image/md" + recGetStr( mdID ) + ".jpg";
                md.ImportData( mdimage );
                md.Save( assdb );
            }
        }
        return true;
    }

    template <class T>
    bool WriteTableCsv( const set<idt>& list )
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

    template <class T>
    bool EnterTable()
    {
        string fname = m_csv_folder + T::TableName() + ".csv";
        std::ifstream ifile( fname );
        if( !ifile ) {
            return true; // Not an error if it doesn't exist
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

    string   m_csv_folder;
    std::map<idt, AssociateData> m_ads;
    set<idt> m_associate;
    set<idt> m_citation;
    set<idt> m_citation_part;
    set<idt> m_citation_part_type;
    set<idt> m_contact;
    set<idt> m_contact_list;
    set<idt> m_contact_type;
    set<idt> m_date;
    set<idt> m_eventa;
    set<idt> m_eventa_persona;
    set<idt> m_event_type;
    set<idt> m_event_type_role;
    set<idt> m_media;
    set<idt> m_name;
    set<idt> m_name_part;
    set<idt> m_name_part_type;
    set<idt> m_name_style;
    set<idt> m_persona;
    set<idt> m_place;
    set<idt> m_place_part;
    set<idt> m_place_part_type;
    set<idt> m_reference;
    set<idt> m_reference_entity;
    set<idt> m_relative_date;
    set<idt> m_repository;
    set<idt> m_researcher;
};


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
    wxImage::AddHandler( new wxPNGHandler );
    wxImage::AddHandler( new wxJPEGHandler );
    wxImage::AddHandler( new wxGIFHandler );
    wxImage::AddHandler( new wxXPMHandler );
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
    dset.SetFolder( string( csvFolder ) );
    wxString outDbFile = conf.Read( "/Output/Output-Database" );
    wxString outDbAss1File = conf.Read( "/Output/Output-Ass1" );

    if( recDb::OpenDb( inDbFile ) == recDb::DbType::full ) {
        dset.Create( inRecords );
        if( wxDir::Exists( csvFolder ) ) {
            wxDir::Remove( csvFolder, wxPATH_RMDIR_RECURSIVE );
        }
        wxDir::Make( csvFolder );
        dset.WriteCsv();
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
        if( !outDbAss1File.empty() ) {
            if( wxFileExists( outDbAss1File ) ) {
                wxRemoveFile( outDbAss1File );
            }
            recDb::DbType dbtype = recDb::DbType::media_data_only;
            recDb::CreateReturn create_ret = recDb::CreateDbFile( outDbAss1File, dbtype );
            if( create_ret != recDb::CreateReturn::OK ) {
                std::cout << "Unable to create Output Associate file \"" << outDbAss1File << "\"\n";
                return EXIT_FAILURE;
            }
            wxFileName ass_fname( outDbAss1File );
            dset.SetAssociatedFileName( 1, string( ass_fname.GetName() ) );
        }
        if( !dset.WriteTfpd() ) {
            std::cout << "Error entering output database.\n";
            return EXIT_FAILURE;
        }
    }

    recUninitialize();
    return EXIT_SUCCESS;
}


/* End of test/tdb/tdbMain.cpp file */
