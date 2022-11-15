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


using std::string;

namespace {

    bool csvWriteMediaData( const string& csv_dir ) {
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


bool recExportCsv( const string& path )
{
    wxDir dir( path );
    if( dir.HasFiles() || dir.HasSubDirs() ) {
        return false;
    }
    string pathsep = dir.GetNameWithSep();
    recDb::WriteCreateScript( pathsep + "create.sql", "Main" );

    bool ret = csvWriteMediaData( pathsep );
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
