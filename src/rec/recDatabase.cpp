/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
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


#include <rec/recDatabase.h>

#include <cal/calendar.h>

#include <rec/recIndividual.h>
#include <rec/recMediaData.h>
#include <rec/recSystem.h>
#include <rec/recUser.h>
#include <rec/recVersion.h>

#include <wx/filename.h>

#include <iostream>
#include <fstream>

// SQL script to create new database
#include "recDatabaseCreate.h"

extern void recInitialize()
{
    if( recDb::GetDb() == NULL ) {
        recDb::SetDb( new wxSQLite3Database() );
    }
    calInit();
}

extern void recUninitialize()
{
    wxSQLite3Database* db = recDb::GetDb();
    if( db ) {
        delete db;
        recDb::SetDb( NULL );
    }
    calUninit();
}

wxString recGetHomeDisplay( const wxString& dbname )
{
    try {
        if( recUser::TableExists( dbname ) ) {
            idt userID = recGetCurrentUser( dbname );
            return recUser::GetSetting(
                dbname, userID, recUserSetting::Property::home_screen
            );
        }
        // Test for MediaData Only database.
        if( recMediaData::TableExists( dbname ) ) {
            return "MD";
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
    }
    // Give up.
    return "About";
}

wxString recGetDateStr( long jdn )
{
    return calStrFromJdn( jdn, CALENDAR_SCH_Gregorian );
}


wxSQLite3Database*  recDb::s_db = NULL;
recDb::DbType       recDb::s_dbtype = DbType::db_null;
long                recDb::s_change = 0;
long                recDb::s_spnumber = 0;
recExternalDbMap    recDb::s_extdbs;
StringMap           recDb::s_attdbs;

recDb::CreateReturn recDb::CreateDbFile( const wxString& fname, DbType type )
{
    wxFileName dbfile( fname );
    dbfile.SetExt( "tfpd" );
    if ( dbfile.FileExists() ) {
        return CreateReturn::FileExists;
    }
    wxString dbfname = dbfile.GetFullPath();
    wxSQLite3Database db;
    db.Open( dbfname );
    if ( !db.IsOpen() ) {
        return CreateReturn::CannotOpen;
    }
    switch ( type )
    {
    case DbType::full:
        db.ExecuteUpdate( createCommonDb );
        db.ExecuteUpdate( createMediaDb );
        db.ExecuteUpdate( createFullDb );
        break;
    case DbType::media_data_only:
        db.ExecuteUpdate( createCommonDb );
        db.ExecuteUpdate( createMediaDb );
        break;
    case DbType::db_null:
        break;
    default:
        db.Close();
        return CreateReturn::UnknownType;
    }
    db.Close();
    return CreateReturn::OK;
}

bool recDb::CreateDb( const wxString& fname, unsigned flags )
{
    wxFileName dbfile( fname );

    if( flags & CREATE_DB_STD_EXT ) {
        dbfile.SetExt( "tfpd" );
    }

    if( flags & CREATE_DB_ENUM_FN ) {
        wxString fn = dbfile.GetName();
        wxString nfn;

        for( int i = 2 ; dbfile.FileExists() == true ; i++ ) {
            nfn.Printf( "%s(%d)", fn.c_str(), i );
            dbfile.SetName( nfn );
        }
    } else {
        if( dbfile.FileExists() == true ) {
            recMessage( _("File already exists"), _("Create Database") );
            // TODO: replace existing file
            return false;
        }
    }

    if( s_db->IsOpen() ) {
        recMessage( _("Database already open"), _("Create Database") );
        return false;
    }

    wxString dbfname = dbfile.GetFullPath();
    CreateReturn ret = CreateDbFile( dbfname, DbType::full );
    if ( ret == CreateReturn::OK ) {
        s_db->Open( dbfname );
        return true;
    }
    return false;
}

recDb::DbType recDb::OpenDb( const wxString& fname )
{
    if( IsOpen() ) {
        recMessage( _("Database already open."), _("Open Database") );
        return DbType::db_null;
    }

    try {
        s_db->Open( fname, wxEmptyString, WXSQLITE_OPEN_READWRITE );
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        return DbType::db_null;
    }
    if( !IsOpen() ) {
        recMessage( _("Unable to open Database."), _("Open Database") );
        return DbType::db_null;
    }

    DbType type = recVersion::Manage();
    s_extdbs["Main"].dbfilename = s_db->GetDatabaseFilename( "main" );
    s_extdbs["Main"].assIdMap[0] = "Main";
    return type;
}

void recDb::CloseDb() 
{ 
    s_db->Close();
    s_dbtype = DbType::db_null;
    ++s_change;
    s_extdbs.clear();
    s_attdbs.clear();
}

bool recDb::OpenExternalDb( const wxString& fname, const wxString& dbname )
{
    wxString mess_title = _( "Open External Database" );
    wxString cap( dbname.Capitalize() );
    if( s_extdbs.count( cap ) == 1 ) {
        wxString mess = wxString::Format(
            _( "External database \"%s\" already open." ), cap
        );
        recMessage( mess, mess_title );
        return false;
    }
    if( s_attdbs.count( cap ) == 1 ) {
        if( fname.compare( s_attdbs[cap] ) != 0 ) {
            // It's in the list, but a different filename.
            wxString mess = wxString::Format(
                _( "Attached database name \"%s\" already used." ), cap
            );
            recMessage( mess, mess_title );
            return false;
        }
    }
    if( !AttachDb( "Main", fname, cap) ) {
        wxString mess = wxString::Format(
            _( "Unable to attach database \"%s\"." ), cap
        );
        recMessage( mess, mess_title );
        return false;
    }
    s_extdbs[cap].dbfilename = fname;
    s_extdbs[cap].assIdMap[0] = cap;
    return true;
}

StringVec recDb::GetExternalDbList()
{
    StringVec dbnames;
    for( auto& extdb : s_extdbs ) {
        if( extdb.first.CmpNoCase( "Main" ) == 0 ) {
            continue;
        }
        dbnames.push_back( extdb.first );
    }
    return dbnames;
}

void recDb::CloseExternalDb( const wxString& dbname )
{
    wxString cap( dbname.Capitalize() );
    for( size_t i = s_extdbs[cap].assdbs.size(); i > 0; --i ) {
        wxString assdb = s_extdbs[cap].assdbs[i - 1];
        s_extdbs[cap].assdbs.pop_back();
        CloseAssociateDb( cap, assdb );
    }
    s_extdbs[cap].assIdMap.clear();
    s_extdbs.erase( cap );

    DetachDb( cap );
}

wxString recDb::OpenAssociateDb( const wxString& extdb, const wxString& fname, const wxString& dbname )
{
    wxString cap( dbname.Capitalize() );
    if( !AttachDb( extdb, fname, cap ) ) {
        wxString mess = wxString::Format(
            _( "Unable to open \"%s\" database." ), cap
        );
        recMessage( mess, _( "Open Associate Database" ) );
        return wxString();
    }
    s_extdbs[extdb].assdbs.push_back( cap );
    return cap;
}

StringVec recDb::GetAssociatedDbList( const wxString& extdb )
{
    return s_extdbs[extdb].assdbs;
}

idt recDb::GetAssociateDbAssID( const wxString& extdb, const wxString& dbname )
{
    for( auto a : s_extdbs[extdb].assIdMap ) {
        if( a.second == dbname ) {
            return a.first;
        }
    }
    return 0;
}

void recDb::CloseAssociateDb( const wxString& extdb, const wxString& dbname )
{
    wxString cap( dbname.Capitalize() );
    StringVec assvec = s_extdbs[extdb].assdbs;
    for( auto& n = assvec.begin(); n != assvec.end(); n++ ) {
        if( *n == cap ) {
            assvec.erase( n );
            break;
        }
    }
    recIdStringMap assmap = s_extdbs[extdb].assIdMap;
    for( auto& a : assmap ) {
        if( a.second == cap ) {
            assmap.erase( a.first );
            break;
        }
    }
    DetachDb( cap );
}

bool recDb::AttachDb( const wxString& extdb, const wxString& fname, const wxString& dbname )
{
    if( s_attdbs.count( dbname ) == 1 ) {
        return true; // Already attached.
    }
    if( dbname.CmpNoCase( "main" ) == 0 || dbname.CmpNoCase( "temp" ) == 0 ) {
        return false;
    }
    wxFileName dbfile( fname );
    wxFileName dbMain( s_extdbs[extdb].dbfilename );
    dbfile.SetExt( "tfpd" );
    if ( !dbfile.FileExists() ) {
        if ( !dbfile.IsRelative() ) {
            return false;
        }
        wxString dbPath( dbMain.GetPath() );
        dbfile.SetCwd( dbPath );
        if ( !dbfile.FileExists() ) {
            return false;
        }
    }
    if( dbfile.IsRelative() ) {
        dbfile.MakeAbsolute();
    }
    wxString dbfname = dbfile.GetFullPath();
    wxSQLite3StatementBuffer sql;
    sql.Format( "ATTACH DATABASE '%q' AS \"%s\";", UTF8_( dbfname ), UTF8_( dbname ) );
    try {
        s_db->ExecuteUpdate( sql );
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        return false;
    }

    DbType type = recVersion::Manage( dbname );
    if( type == DbType::db_null ) {
        recDb::DetachDb( dbname );
        return false;
    }
    s_attdbs[dbname] = dbfname;
    // Final check to see if attached.
    wxString filename = s_db->GetDatabaseFilename( dbname );
    if( filename.empty() ) {
        return false;
    }
    return true;
}

bool recDb::IsAttachedDb( const wxString& dbname )
{
    if( s_attdbs.count( dbname ) == 1 ) {
        return true;
    }
    return false;
}

bool recDb::DetachDb( const wxString& dbname )
{
    if( !IsAttachedDb( dbname ) ) {
        return false;  // Not attached!
    }
    // Assume removed internally first. Is it in use elsewhere?
    // If so then return true as this is not an error.
    for( auto& external : s_extdbs ) {
        if( external.first == dbname ) {
            return true;
        }
        for( auto& associate : external.second.assdbs ) {
            if( associate == dbname ) {
                return true; 
            }
        }
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "DETACH DATABASE \"%s\";", UTF8_( dbname ) );
    s_db->ExecuteUpdate( sql );

    s_attdbs.erase( dbname );
 
    return true;
}

StringVec recDb::GetAttachedDbList()
{
    wxSQLite3ResultSet result =
        s_db->ExecuteQuery( "PRAGMA database_list;" );

    StringVec vec;
    while( result.NextRow() ) {
        wxString name = result.GetAsString( 1 );
        if( name == "main" ) {
            continue;
        }
        vec.push_back( name );
    }
    return vec;
}

StringVec recDb::GetDatabaseList()
{
    wxSQLite3ResultSet result =
        s_db->ExecuteQuery( "PRAGMA database_list;" );

    StringVec vec;
    while( result.NextRow() ) {
        wxString name = result.GetAsString( 1 );
        vec.push_back( name );
    }
    return vec;
}

wxString recDb::GetFileName()
{
    wxString fn;
    if( s_db ) {
        fn = s_db->GetDatabaseFilename( "main" );
    }
    return fn;
}

recDb::DbType recDb::GetDatabaseType( const wxString& dbname )
{
    recVersion ver( DbType::full, dbname );
    if( !ver.IsEqual( 0, 0, 0, 0 ) ) {
        return DbType::full;
    }
    ver.ReadType( DbType::media_data_only, dbname );
    if( !ver.IsEqual( 0, 0, 0, 0 ) ) {
        return DbType::media_data_only;
    }
    return DbType::db_null;
}

wxString recDb::GetDatabaseTypeDesc( DbType type )
{
    switch( type ) {
    case DbType::full:
        return _("Full");
    case DbType::media_data_only:
        return _("Media Data");
    }
    return _( "Unknown" );
}

bool recDb::WriteCreateScript( const std::string& fname, const wxString& dbname )
{
    std::ofstream ofile( fname, std::ios::trunc );
    if( !ofile ) {
        return false;
    }
    DbType type = GetDatabaseType( dbname );
    switch( type ) {
    case DbType::full:
        ofile << createCommonDb;
        ofile << createMediaDb;
        ofile << createFullDb;
        break;
    case DbType::media_data_only:
        ofile << createCommonDb;
        ofile << createMediaDb;
        break;
    }
    return false;
}

void recDb::ErrorMessage( wxSQLite3Exception& e )
{
    wxString err;
    err << e.GetErrorCode() << ": " << e.GetMessage();
    recMessage( err, _("Database Error") );
}

bool recDb::DeleteRecord( const char* name, idt id, const wxString& dbname )
{
    if( id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "DELETE FROM \"%s\".%q WHERE id=" ID ";", UTF8_( dbname ), name, id );

    if( s_db->ExecuteUpdate( sql ) != 1 ) {
        return false;
    }
    return true;
}

bool recDb::RecordExists( const char* name, idt id, const wxString& dbname )
{
    if( id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM \"%s\".%q WHERE id=" ID ";", UTF8_( dbname ), name, id );

    if( s_db->ExecuteScalar( sql ) != 1 ) {
        return false;
    }
    return true;
}

int recDb::GetUserCount( const char* name, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM \"%s\".%q WHERE id>0;", UTF8_( dbname ), name );

    return s_db->ExecuteScalar( sql );
}

int recDb::GetCount( const char* name, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM \"%s\".%q;", UTF8_( dbname ), name );

    return s_db->ExecuteScalar( sql );
}

bool recDb::DoesTableExist( const char* table, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".sqlite_master"
        " WHERE type='table' AND name='%q' COLLATE NOCASE;",
        UTF8_( dbname ), table
    );
    if( s_db->ExecuteScalar( sql ) == 1 ) {
        return true;
    }
    return false;
}

recIdVec recDb::GetPositiveIDs( const char* table, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT id FROM \"%s\".%q WHERE id>0;", UTF8_( dbname ), table );

    return ExecuteIdVec( sql );
}

int recDb::ExecuteInt( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetInt( 0 );
}

int recDb::ExecuteInt( const char* format, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ) );
    return ExecuteInt( sql );
}

int recDb::ExecuteInt( const char* format, idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id, UTF8_( dbname ) );
    return ExecuteInt( sql );
}

int recDb::ExecuteInt( const char* format, const wxString& dbname, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ), id );
    return ExecuteInt( sql );
}

idt recDb::ExecuteID( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return GET_ID( result.GetInt64( 0 ) );
}

idt recDb::ExecuteID( const char* format, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ) );
    return ExecuteID( sql );
}

idt recDb::ExecuteID( const char* format, idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id, UTF8_( dbname ) );
    return ExecuteID( sql );
}

idt recDb::ExecuteID( const char* format, const wxString& dbname, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ), id );
    return ExecuteID( sql );
}

recIdVec recDb::ExecuteIdVec( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    recIdVec ids;
    while( result.NextRow() ) {
        ids.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return ids;
}

recIdVec recDb::ExecuteIdVec( const char* format, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ) );
    return ExecuteIdVec( sql );
}

recIdVec recDb::ExecuteIdVec( const char* format, idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id, UTF8_( dbname ) );
    return ExecuteIdVec( sql );
}

recIdVec recDb::ExecuteIdVec( const char* format, const wxString& dbname, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ), id );
    return ExecuteIdVec( sql );
}

wxString recDb::ExecuteStr( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

wxString recDb::ExecuteStr( const char* format, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ) );
    return ExecuteStr( sql );
}

wxString recDb::ExecuteStr( const char* format, idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id, UTF8_( dbname ) );
    return ExecuteStr( sql );
}

wxString recDb::ExecuteStr( const char* format, const wxString& dbname, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, UTF8_( dbname ), id );
    return ExecuteStr( sql );
}

idt recUid::DoFindUid( const wxString& uid, const char* table, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT id FROM \"%s\".%s WHERE uid='%q';",
        UTF8_( dbname ), table, UTF8_( uid )
    );
    return recDb::ExecuteID( sql );
}

wxString recUid::DoGetChangedDate( idt id, const char* table, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT changed FROM \"%s\".%s WHERE id=" ID ";",
        UTF8_( dbname ), table, id
    );
    long jdn = recDb::ExecuteInt( sql );
    return recGetDateStr( jdn );
}


// End of recDatabase.cpp file
