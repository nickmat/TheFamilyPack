/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 ~ 2019, Nick Matthews.
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

#include <wx/filename.h>

#include <rec/recDatabase.h>
#include <rec/recVersion.h>
#include <rec/recIndividual.h>
#include <cal/calendar.h>

// SQL script to create new database
#include "recDatabaseCreate.h"

extern void recInitialize()
{
    if( recDb::GetDb() == NULL ) {
        recDb::SetDb( new wxSQLite3Database() );
    }
    recDb::AddAssociate( 0, "Main" );
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

wxSQLite3Database*  recDb::s_db = NULL;
recDb::DatabaseType recDb::s_dbtype = DT_NULL;
long                recDb::s_change = 0;
long                recDb::s_spnumber = 0;
recAssMap           recDb::s_assmap;


recDb::CreateReturn recDb::CreateDbFile( const wxString& fname, DatabaseType type )
{
    wxFileName dbfile( fname );
    dbfile.SetExt( "tfpd" );
    if ( dbfile.FileExists() ) {
        return CR_FileExists;
    }
    wxString dbfname = dbfile.GetFullPath();
    wxSQLite3Database db;
    db.Open( dbfname );
    if ( !db.IsOpen() ) {
        return CR_CannotOpen;
    }
    switch ( type )
    {
    case DT_Full:
        db.ExecuteUpdate( createCommonDb );
        db.ExecuteUpdate( createMediaDb );
        db.ExecuteUpdate( createFullDb );
        break;
    case DT_MediaOnly:
        db.ExecuteUpdate( createCommonDb );
        db.ExecuteUpdate( createMediaDb );
        break;
    default:
        db.Close();
        return CR_UnknownType;
    }
    db.Close();
    return CR_OK;
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
    CreateReturn ret = CreateDbFile( dbfname, DT_Full );
    if ( ret == CR_OK ) {
        s_db->Open( dbfname );
        return true;
    }
    return false;
}

recDb::DatabaseType recDb::OpenDb( const wxString& fname )
{
    if( IsOpen() ) {
        recMessage( _("Database already open."), _("Open Database") );
        return DT_NULL;
    }

    try {
        s_db->Open( fname, wxEmptyString, WXSQLITE_OPEN_READWRITE );
    } catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        return DT_NULL;
    }
    if( !IsOpen() ) {
        recMessage( _("Unable to open Database."), _("Open Database") );
        return DT_NULL;
    }

//    bool success = recVersion::Manage();
    DatabaseType type = recVersion::Manage();
    if( type == DT_NULL ) {
        CloseDb();
    }
    return type;
}

bool recDb::AttachDb( const wxString& fname, const wxString& dbname )
{
    wxFileName dbfile( fname );
    dbfile.SetExt( "tfpd" );
    if ( !dbfile.FileExists() ) {
        if ( !dbfile.IsRelative() ) {
            return false;
        }
        wxFileName dbMain( recDb::GetFileName() );
        wxString dbPath( dbMain.GetPath() );
        dbfile.SetCwd( dbPath );
        if ( !dbfile.FileExists() ) {
            return false;
        }
    }
    wxString dbfname = dbfile.GetFullPath();
    wxSQLite3StatementBuffer sql;
    sql.Format( "ATTACH DATABASE '%q' AS '%q';", UTF8_( dbfname ), UTF8_( dbname ) );
    s_db->ExecuteUpdate( sql );
    return true;
}

bool recDb::DetachDb( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "DETACH DATABASE '%q';", UTF8_( dbname ) );
    s_db->ExecuteUpdate( sql );
    for ( auto a : s_assmap ) {
        if ( a.second == dbname ) {
            s_assmap.erase( a.first );
            break;
        }
    }
    return true;
}

StringVec recDb::GetAttachedDbList()
{
    wxSQLite3ResultSet result =
        s_db->ExecuteQuery( "PRAGMA database_list;" );

    StringVec vec;
    while ( result.NextRow() ) {
        wxString name = result.GetAsString( 1 );
        if ( name == "main" ) {
            continue;
        }
        vec.push_back( name );
    }
    return vec;
}

idt recDb::GetAttachedDbAssID( const wxString& dbname )
{
    for ( auto a : s_assmap ) {
        if ( a.second == dbname ) {
            return a.first;
        }
    }
    return 0;
}

void recDb::CloseDb() 
{ 
    s_db->Close();
    s_dbtype = DT_NULL;
    ++s_change;
    s_assmap.clear();
    s_assmap[0] = "Main";
}

bool recDb::GlobalUpdate()
{
    recIndividualVec inds = recIndividual::ReadVec();
    for( size_t i = 0 ; i < inds.size() ; i++ ) {
        inds[i].Update();
        inds[i].Save();
    }
    bool ok = recIndividual::CreateMissingFamilies();
    return ok;
}

wxString recDb::GetFileName()
{
    wxString fn;
    if( s_db ) {
        fn = s_db->GetDatabaseFilename( "main" );
    }
    return fn;
}

void recDb::ErrorMessage( wxSQLite3Exception& e )
{
    wxString err;
    err << e.GetErrorCode() << ": " << e.GetMessage();
    recMessage( err, _("Database Error") );
}

bool recDb::DeleteRecord( const char* name, idt id )
{
    if( id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "DELETE FROM %q WHERE id=" ID ";", name, id );

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
    sql.Format( "SELECT COUNT(*) FROM %q.%q WHERE id=" ID ";", UTF8_( dbname ), name, id );

    if( s_db->ExecuteScalar( sql ) != 1 ) {
        return false;
    }
    return true;
}

int recDb::GetUserCount( const char* name )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM %q WHERE id>0;", name );

    return s_db->ExecuteScalar( sql );
}

int recDb::GetCount( const char* name )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM %q;", name );

    return s_db->ExecuteScalar( sql );
}

int recDb::ExecuteInt( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetInt( 0 );
}

int recDb::ExecuteInt( const char* format, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetInt( 0 );
}

idt recDb::ExecuteID( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return GET_ID( result.GetInt64( 0 ) );
}

idt recDb::ExecuteID( const char* format, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return GET_ID( result.GetInt64( 0 ) );
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

recIdVec recDb::ExecuteIdVec( const char* format, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id );
    return ExecuteIdVec( sql );
}

wxString recDb::ExecuteStr( const wxSQLite3StatementBuffer& sql )
{
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

wxString recDb::ExecuteStr( const char* format, idt id )
{
    wxSQLite3StatementBuffer sql;
    sql.Format( format, id );

    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );
    return result.GetAsString( 0 );
}

// End of recDatabase.cpp file
