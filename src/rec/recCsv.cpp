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

    // Note, both csv_dir and tfpd_dir can be assumed to end with file separators.
    bool csvImportMediaData( const string& csv_dir, const string& tfpd_dir )
    {
        if( !recAssociate::CsvReadTableFile( csv_dir ) ) {
            return false;
        }
        recIdVec assIDs = recAssociate::IdVec( recDb::Coverage::all );
        string md_dir, md_db;
        for( idt assID : assIDs ) {
            if( assID == 0 ) {
                md_dir = csv_dir;
                md_db = "Main";
            }
            else {
                md_dir = csv_dir + "ass" + recGetStr( assID ) + recFileSep();
                recAssociate ass( assID );
                wxFileName tfpd_file( wxString( tfpd_dir ) + ass.FGetPath() + ".tfpd" );
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
            }
            bool ret = recMediaData::CsvReadTableFile( md_dir, md_db );
            recIdVec mdIDs = recMediaData::IdVec( recDb::Coverage::notzero, md_db );
            string image_dir = md_dir + "image" + recFileSep();
            for( idt mdID : mdIDs ) {
                recMediaData md( mdID, md_db );
                string filename = image_dir + "md" + recIdToStr( mdID ) + ".jpg";
                if( md.ImportData( filename ) ) {
                    md.Save( md_db );
                }
            }
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
    recDb::CreateReturn dbret = recDb::CreateDbFile( dbfname, dbtype );
    if( dbret != recDb::CreateReturn::OK ) {
        return false;
    }
    wxSQLite3Database db;
    db.Open( dbfname );
    if( !db.IsOpen() ) {
        return false;
    }
    db.ExecuteUpdate( create_sql );
    db.Close();

    // Reopen to check version etc.
    if( recDb::OpenDb( dbfname ) != recDb::DbType::full ) {
        return false;
    }

    wxFileName tfpd_fn( dbfname.c_str() );
    string tfpd_dir = tfpd_fn.GetPathWithSep();
 
    bool ret = true;
    ret = ret && csvImportMediaData( path, tfpd_dir );
    ret = ret && recCitation::CsvReadTableFile( path );
    ret = ret && recRepository::CsvReadTableFile( path );
    ret = ret && recCitationPart::CsvReadTableFile( path );
    ret = ret && recCitationPartType::CsvReadTableFile( path );
    ret = ret && recContactList::CsvReadTableFile( path );
    ret = ret && recContactType::CsvReadTableFile( path );
    ret = ret && recContact::CsvReadTableFile( path );
    ret = ret && recDate::CsvReadTableFile( path );
    ret = ret && recRelativeDate::CsvReadTableFile( path );
    ret = ret && recEvent::CsvReadTableFile( path );
    ret = ret && recEventa::CsvReadTableFile( path );
    ret = ret && recEventaPersona::CsvReadTableFile( path );
    ret = ret && recEventEventa::CsvReadTableFile( path );
    ret = ret && recEventType::CsvReadTableFile( path );
    ret = ret && recEventTypeRole::CsvReadTableFile( path );
    ret = ret && recFamilyEvent::CsvReadTableFile( path );
    ret = ret && recFamilyEventa::CsvReadTableFile( path );
    ret = ret && recFamily::CsvReadTableFile( path );
    ret = ret && recFamilyIndividual::CsvReadTableFile( path );
    ret = ret && recFamilyIndEventa::CsvReadTableFile( path );
    ret = ret && recGallery::CsvReadTableFile( path );
    ret = ret && recGalleryMedia::CsvReadTableFile( path );
    ret = ret && recIndividualEvent::CsvReadTableFile( path );
    ret = ret && recIndividual::CsvReadTableFile( path );
    ret = ret && recIndividualPersona::CsvReadTableFile( path );
    ret = ret && recMedia::CsvReadTableFile( path );
    ret = ret && recName::CsvReadTableFile( path );
    ret = ret && recNamePart::CsvReadTableFile( path );
    ret = ret && recNamePartType::CsvReadTableFile( path );
    ret = ret && recNameStyle::CsvReadTableFile( path );
    ret = ret && recPersona::CsvReadTableFile( path );
    ret = ret && recPlace::CsvReadTableFile( path );
    ret = ret && recPlacePart::CsvReadTableFile( path );
    ret = ret && recPlacePartType::CsvReadTableFile( path );
    ret = ret && recReferenceEntity::CsvReadTableFile( path );
    ret = ret && recReference::CsvReadTableFile( path );
    ret = ret && recResearcher::CsvReadTableFile( path );
    ret = ret && recSystem::CsvReadTableFile( path );
    ret = ret && recUserSetting::CsvReadTableFile( path );
    ret = ret && recUser::CsvReadTableFile( path );
    return ret;
}

bool recExportCsv( const string& path )
{
    wxDir dir( path );
    if( dir.HasFiles() || dir.HasSubDirs() ) {
        return false;
    }
    string pathsep = dir.GetNameWithSep();
    string sig_fname = pathsep + recSigFileName;
    string sig_content = string(recSignature) + "\n";
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
