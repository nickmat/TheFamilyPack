/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recCsv.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Handle CSV import and export.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th November 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recCsv.h>

#include <rec/recDb.h>

#include <wx/dir.h>
#include <wx/filename.h>

using std::string;

namespace {

    enum class DbFieldType { integer, real, text };
    struct DbField {
        DbField( DbFieldType t, const string& c )
            : type( t ), column( c ) {}

        DbFieldType type;
        string column;
    };
    using DbFieldVec = std::vector<DbField>;

    bool csvReadMediaFile( const string& filename, wxMemoryBuffer buf )
    {
        wxFile infile( filename );
        wxFileOffset fLen = infile.Length();
        void* tmp = buf.GetAppendBuf( fLen );
        size_t iRead = infile.Read( tmp, fLen );
        buf.UngetAppendBuf( iRead );
        return !buf.IsEmpty();
    }

    DbFieldVec csvParseTitles( const string& titles )
    {
        DbFieldVec fields;
        bool inquote = false;
        DbField field( DbFieldType::integer, "" );
        for( auto ch : titles ) {
            if( ch == ' ' ) continue;
            if( ch == '\'' ) {
                inquote = true;
                field.type = DbFieldType::text;
                continue;
            }
            if( ch == ',' || ch == '\n' ) {
                inquote = false;
                fields.push_back( field );
                field.type = DbFieldType::integer;
                field.column.clear();
                continue;
            }
            if( ch == '.' ) {
                field.type = DbFieldType::real;
                continue;
            }
            field.column += ch;
        }
        return fields;
    }

    string csvMakeStatement( const string& table, const DbFieldVec& fields, const string& dbname )
    {
        string insert, value;
        bool first = true;
        for( auto field : fields ) {
            if( !first ) {
                insert += ", ";
                value += ", ";
            }
            insert += field.column;
            value += "?";
            first = false;
        }
        string stmt =
            "INSERT INTO \"" + dbname + "\"." + table + " (" + insert + ")"
            " VALUES (" + value + ");"
            ;
        return stmt;
    }

    bool csvInsertRecords( std::istream& in, const string& table, const string& dbname )
    {
        string titles;
        std::getline( in, titles );
        DbFieldVec fields = csvParseTitles( titles + "\n" );
        string sql = csvMakeStatement( table, fields, dbname );

        recDb::Begin();
        wxSQLite3Statement stmt = recDb::GetDb()->PrepareStatement( sql );

        idt id = 0;
        string text;
        double real = 0.0;
        while( in.peek() != EOF ) {
            int i = 1;
            for( auto field : fields ) {
                switch( field.type )
                {
                case DbFieldType::integer:
                    recCsvRead( in, id );
                    stmt.Bind( i, wxLongLong( id ) );
                    break;
                case DbFieldType::text:
                    recCsvRead( in, text );
                    stmt.Bind( i, text );
                    break;
                case DbFieldType::real:
                    recCsvRead( in, real );
                    stmt.Bind( i, real );
                    break;
                }
                i++;
            }
            stmt.ExecuteUpdate();
            stmt.Reset();
        }
        recDb::Commit();
        return true;
    }

    bool csvReadFile( const wxString& fname, const string& dbname )
    {
        wxFileName fn( fname );
        string table = fn.GetName();
        string filename = fn.GetFullPath();
        std::ifstream ifile( filename );
        if( !ifile ) {
            return false;
        }
        return csvInsertRecords( ifile, table, dbname );
    }

    bool csvImportFiles( const string& csv_dir, const string& dbname )
    {
        wxDir dir( csv_dir );
        wxString filename;
        bool cont = dir.GetFirst( &filename, "*.csv", wxDIR_FILES );
        while( cont ) {
            if( !csvReadFile( csv_dir + filename, dbname ) ) {
                return false;
            }
            cont = dir.GetNext( &filename );
        }
        return true;
    }

    bool EmptyDirectory( const string& path )
    {
        wxDir dir( path );
        if( !dir.IsOpened() ) {
            return false;
        }
        wxString file;
        bool cont = dir.GetFirst( &file );
        while( cont )
        {
            file = dir.GetNameWithSep() + file;
            if( wxFileName::FileExists( file ) ) {
                if( !wxRemoveFile( file ) ) {
                    return false;
                }
            }
            if( wxFileName::DirExists( file ) ) {
                EmptyDirectory( file.ToStdString() );
                if( !wxRmdir( file ) ) {
                    return false;
                }
            }
            cont = dir.GetNext( &file );
        }
        if( dir.HasFiles() || dir.HasSubDirs() ) {
            return false;
        }
        return true;
    }

    bool csvImportMediaData( idt mdID, const string& fname, const string& dbname )
    {
        wxMemoryBuffer buf;
        wxFile infile( fname );
        wxFileOffset fLen = infile.Length();
        void* tmp = buf.GetAppendBuf( fLen );
        size_t iRead = infile.Read( tmp, fLen );
        buf.UngetAppendBuf( iRead );
        if( buf.IsEmpty() ) {
            return false;
        }
        wxSQLite3StatementBuffer sql;
        sql.Format(
            "UPDATE \"%s\".MediaData SET data=x'%q' WHERE id=" ID ";",
            dbname.c_str(), UTF8_( GetBlobFormatStr( buf ) ), mdID
        );
        recDb::GetDb()->ExecuteUpdate( sql );
        return true;
    }

    // Note, both csv_dir and tfpd_dir can be assumed to end with file separators.
    bool csvImportMediaData( const string& csv_dir, const string& tfpd_dir )
    {
        recIdVec assIDs = recAssociate::IdVec( recDb::Coverage::all );
        string md_dir; // CSV directory
        string md_db;  // MediaData database attached name 
        for( idt assID : assIDs ) {
            if( assID == 0 ) {
                md_dir = csv_dir;
                md_db = "Main";
            }
            else {
                // We need to create a new media-only database without using record classes
                md_dir = csv_dir + "ass" + recGetStr( assID ) + recFileSep();
                string path = recDb::ExecuteStr( "SELECT path FROM \"%s\".Associate WHERE id=" ID ";", "Main", assID);
                wxFileName tfpd_file( wxString( tfpd_dir ) + path + ".tfpd" );
                wxString tfpd_fn = tfpd_file.GetFullPath();
                recDb::DbType dbtype = recDb::DbType::db_null;
                recDb::CreateReturn create_ret;
                create_ret = recDb::CreateDbFile( tfpd_fn, dbtype );
                if( create_ret != recDb::CreateReturn::OK ) {
                    wxString message = "Unable to create database \"" + tfpd_fn + "\"";
                    recMessage( message, "ImportMediaData" );
                    continue;
                }
                std::string create_sql = recTextFileRead( md_dir + "create.sql" );
                if( create_sql.empty() ) {
                    recMessage( "Unable to read create file", "ImportMediaData");
                    continue;
                }
                wxSQLite3Database db;
                db.Open( tfpd_fn );
                if( !db.IsOpen() ) {
                    continue;
                }
                db.ExecuteUpdate( create_sql );
                db.Close();
                md_db = recDb::OpenAssociateDb( "Main", tfpd_fn, tfpd_file.GetName() );
                if( md_db.empty() ) return false;
                if( !csvImportFiles( md_dir, md_db ) ) return false;  // Read in MediaData files
            }
            recIdVec mdIDs = recMediaData::IdVec( recDb::Coverage::notzero, md_db );
            string image_dir = md_dir + "image" + recFileSep();
            recDb::Begin();
            for( idt mdID : mdIDs ) {
                string filename = image_dir + "md" + recIdToStr( mdID ) + ".jpg";
                csvImportMediaData( mdID, filename, md_db );
            }
            recDb::Commit();
        }
        return true;
    }

    bool csvExportMediaData( const string& csv_dir )
    {
        string md_dir, image_dir, md_fname, image_fn;
        recIdVec assIDs = recAssociate::IdVec( recDb::Coverage::all );
        for( idt assID : assIDs ) {
            if( assID == 0 ) {
                md_dir = csv_dir;
            }
            else {
                md_dir = csv_dir + "ass" + recGetStr( assID ) + recFileSep();
                wxDir::Make( md_dir );
            }
            wxString assdb = recAssociate::GetAttachedName( assID, "Main" );

            recDb::Coverage cover = recDb::Coverage::rnotzero;
            if( recMediaData::Count( cover, assdb ) == 0 ) {
                continue;
            }
            bool ret = recMediaData::CsvWriteTableFile( md_dir, cover, assdb );
            if( !ret ) {
                continue;
            }
            if( assID != 0 ) {
                string create_fn = md_dir + "create.sql";
                recDb::WriteCreateScript( create_fn, recDb::DbType::media_data_only );
            }

            image_dir = md_dir + "image" + recFileSep();
            wxDir::Make( image_dir );

            recIdVec list = recMediaData::IdVec( recDb::Coverage::rnotzero, assdb );
            for( idt mdID : list ) {
                recMediaData md( mdID, assID );
                image_fn = image_dir + "md" + recGetStr( mdID ) + ".jpg";
                md.ExportData( image_fn );
            }
        }
        return true;
    }

} // namespace

bool recImportCsv( const string& csv_dir, const std::string& dbfname )
{
    string path = recEndWithFileSep( csv_dir );

    // Get the create.sql script.
    std::string create_sql = recTextFileRead( path + "create.sql" );
    if( create_sql.empty() ) {
        return false;
    }

    recDb::DbType dbtype = recDb::DbType::db_null;
    unsigned flags = recGetCreateProtocolFlag();
    if( !recDb::CreateDb( dbfname, dbtype, flags ) ) {
        return false;
    }
    string actual_dbfname = recDb::GetFileName();
    recDb::GetDb()->ExecuteUpdate( create_sql );

    wxFileName tfpd_fn( actual_dbfname.c_str() );
    string tfpd_dir = tfpd_fn.GetPathWithSep();

    bool ret = csvImportFiles( path, "Main" );
    ret = ret && csvImportMediaData( path, tfpd_dir );

    // Close and reopen to check version etc.
    recDb::CloseDb();
    if( ret == false ) {
        return false;
    }
    if( recDb::OpenDb( actual_dbfname ) != recDb::DbType::full ) {
        return false;
    }
    return true;
}

bool recExportCsv( const string& path )
{
    wxDir dir( path );
    string pathsep = dir.GetNameWithSep();
    string sig_fname = pathsep + recSigFileName;
    string sig_content = string(recSignature) + "\n";
    if( dir.HasFiles() || dir.HasSubDirs() ) {
        string sig = recTextFileRead( sig_fname );
        if( sig == sig_content ) {
            // We have selected an existing CSV directory
            if( !EmptyDirectory( path ) ) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    if( !recTextFileWrite( sig_fname, sig_content ) ) {
        return false;
    }
    recDb::WriteCreateScript( pathsep + "create.sql", "Main" );

    bool ret = csvExportMediaData( pathsep );
    ret = ret && recAssociate::CsvWriteTableFile( path );
    ret = ret && recCitation::CsvWriteTableFile( path );
    ret = ret && recRepository::CsvWriteTableFile( path );
    ret = ret && recCitationPart::CsvWriteTableFile( path );
    ret = ret && recCitationPartType::CsvWriteTableFile( path );
    ret = ret && recContactList::CsvWriteTableFile( path );
    ret = ret && recContactType::CsvWriteTableFile( path );
    ret = ret && recContact::CsvWriteTableFile( path );
    ret = ret && recDate::CsvWriteTableFile( path );
    ret = ret && recRelativeDate::CsvWriteTableFile( path );
    ret = ret && recEvent::CsvWriteTableFile( path );
    ret = ret && recEventa::CsvWriteTableFile( path );
    ret = ret && recEventaPersona::CsvWriteTableFile( path );
    ret = ret && recEventEventa::CsvWriteTableFile( path );
    ret = ret && recEventType::CsvWriteTableFile( path );
    ret = ret && recEventTypeRole::CsvWriteTableFile( path );
    ret = ret && recFamilyEvent::CsvWriteTableFile( path );
    ret = ret && recFamilyEventa::CsvWriteTableFile( path );
    ret = ret && recFamily::CsvWriteTableFile( path );
    ret = ret && recFamilyIndividual::CsvWriteTableFile( path );
    ret = ret && recFamilyIndEventa::CsvWriteTableFile( path );
    ret = ret && recGallery::CsvWriteTableFile( path );
    ret = ret && recGalleryMedia::CsvWriteTableFile( path );
    ret = ret && recIndividualEvent::CsvWriteTableFile( path );
    ret = ret && recIndividual::CsvWriteTableFile( path );
    ret = ret && recIndividualPersona::CsvWriteTableFile( path );
    ret = ret && recMedia::CsvWriteTableFile( path );
    ret = ret && recName::CsvWriteTableFile( path );
    ret = ret && recNamePart::CsvWriteTableFile( path );
    ret = ret && recNamePartType::CsvWriteTableFile( path );
    ret = ret && recNameStyle::CsvWriteTableFile( path );
    ret = ret && recPersona::CsvWriteTableFile( path );
    ret = ret && recPlace::CsvWriteTableFile( path );
    ret = ret && recPlacePart::CsvWriteTableFile( path );
    ret = ret && recPlacePartType::CsvWriteTableFile( path );
    ret = ret && recReferenceEntity::CsvWriteTableFile( path );
    ret = ret && recReference::CsvWriteTableFile( path );
    ret = ret && recResearcher::CsvWriteTableFile( path );
    ret = ret && recSystem::CsvWriteTableFile( path );
    ret = ret && recUserSetting::CsvWriteTableFile( path );
    ret = ret && recUser::CsvWriteTableFile( path );
    return ret;
}


// End of recCsv.cpp file
