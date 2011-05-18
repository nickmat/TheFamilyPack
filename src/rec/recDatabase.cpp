/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

// SQL script to create new database
#include "generated/recSql.ci"

static const char* upgrade0_0_8_0 = 
    "ALTER TABLE Date RENAME TO OldDate;\n"
    "CREATE TABLE Date (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  jdn INTEGER,\n"
    "  range INTEGER,\n"
    "  base_id INTEGER,\n"
    "  base_unit INTEGER,\n"
    "  base_style INTEGER,\n"
    "  type INTEGER,\n"
    "  desc TEXT,\n"
    "  record_sch INTEGER,\n"
    "  display_sch INTEGER\n"
    ");\n"
    "INSERT INTO Date"
    " (id, jdn, range, base_id, base_unit, base_style, type, desc, record_sch, display_sch)"
    " SELECT id, jdn, range, 0, 0, 0, type, desc, record_sch, display_sch FROM OldDate;"
    "DROP TABLE OldDate;"
;

static const char* upgrade0_0_8_1 = 
    "ALTER TABLE Date RENAME TO OldDate;\n"
    "CREATE TABLE Date (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  jdn INTEGER,\n"
    "  range INTEGER,\n"
    "  base_id INTEGER,\n"
    "  base_unit INTEGER,\n"
    "  base_style INTEGER,\n"
    "  type INTEGER,\n"
    "  descrip TEXT,\n"
    "  record_sch INTEGER,\n"
    "  display_sch INTEGER\n"
    ");\n"
    "INSERT INTO Date"
    " (id, jdn, range, base_id, base_unit, base_style, type, descrip, record_sch, display_sch)"
    " SELECT id, jdn, range, base_id, base_unit, base_style, type, desc, record_sch, display_sch FROM OldDate;"
    "DROP TABLE OldDate;"

    // These tables have not yet been used so no need to copy data
    "DROP TABLE RepositorySource;"
    "CREATE TABLE RepositorySource (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  repos_id INTEGER,\n"
    "  source_id INTEGER,\n"
    "  call_num TEXT,\n"
    "  descrip TEXT\n"
    ");\n"
    "DROP TABLE Contact;"
    "CREATE TABLE Contact (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  ind_id INTEGER,\n"
    "  res_id INTEGER,\n"
    "  repos_id INTEGER,\n"
    "  type_id TEXT,\n"
    "  val TEXT\n"
    ");\n"
;

wxSQLite3Database* recDb::s_db = NULL;

wxString recGetSexStr( Sex sex )
{
    static wxString sexarray[] = {
        _("Unstated"), _("Male"), _("Female"), _("Unknown")
    };
    return sexarray[sex];
}
static bool UpgradeMajor( recVersion& ver ) 
{
    wxMessageBox(
        wxString::Format( 
            _("Cannot read database version %s file."),
            ver.GetVersionStr() 
        ),
        _("Upgrade Major")
    );
    return false;
}

static bool UpgradeMinor( recVersion& ver ) 
{
    wxMessageBox(
        wxString::Format( 
            _("Cannot read database version %s file."),
            ver.GetVersionStr() 
        ),
        _("Upgrade Minor")
    );
    return false;
}

static bool UpgradeRevision( recVersion& ver ) 
{
    wxMessageBox(
        wxString::Format( 
            _("Cannot read database version %s file."),
            ver.GetVersionStr() 
        ),
        _("Upgrade Revision")
    );
    return false;
}

static bool UpgradeTest( recVersion& ver ) 
{
    // We can only deal with version 0,0,8,0
    if( !ver.IsEqual( 0, 0, 8 ) || ver.IsMoreThan( 0, 0, 8, 1 ) ) {
        wxMessageBox(
            wxString::Format( 
                _("Cannot read database version %s file."),
                ver.GetVersionStr() 
            ),
            _("Upgrade Test")
        );
        return false;
    }

    try {
        if( ver.f_test == 0 ) {
            // Upgrade 0.0.8.0 to 0.0.8.1
            recDb::Begin();
            recDb::GetDb()->ExecuteUpdate( upgrade0_0_8_0 );
            ver.f_test = 1;
            ver.Save();
            recDb::Commit();
        }
        if( ver.f_test == 1 ) {
            // Upgrade 0.0.8.0 to 0.0.8.1
            recDb::Begin();
            recDb::GetDb()->ExecuteUpdate( upgrade0_0_8_1 );
            ver.f_test = 2;
            ver.Save();
            recDb::Commit();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        return false;
    }
    return true;
}


bool recDb::CreateDb( wxString& fname, unsigned flags )
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
            wxMessageBox( _("File already exists"), _("Create Database") );
            // TODO: replace existing file
            return false;
        }
    }

    if( s_db->IsOpen() ) {
        wxMessageBox( _("Database already open"), _("Create Database") );
        return false;
    }

    fname = dbfile.GetFullPath();
    s_db->Open( fname );
    s_db->ExecuteUpdate( createdb );
    return true;
}

bool recDb::OpenDb( const wxString& fname )
{
    if( IsOpen() ) {
        wxMessageBox( _("Database already open"), _("Open Database") );
        return false;
    }
    bool success = true;

    s_db->Open( fname );
    recVersion ver(1);
    if( !ver.IsEqual( recVerMajor, recVerMinor, recVerRevision, recVerTest ) ) {
        // Versions differ
        if( ver.IsEqual( recVerMajor, recVerMinor, recVerRevision ) ) {
            // Only the test differs.
            success = UpgradeTest( ver ); // Succeeds if converts to a standard db
        }
        if( success && ver.IsLessThan( recVerMajor ) ) {
            success = UpgradeMajor( ver );
        }
        if( success && ver.IsLessThan( recVerMajor, recVerMinor ) ) {
            success = UpgradeMinor( ver );
        }
        if( ver.IsMoreThan(  recVerMajor, recVerMinor ) ) {
            wxMessageBox(
                wxString::Format( 
                    _("Cannot read database version %s file."),
                    ver.GetVersionStr() 
                ),
                _("Open Database")
            );
            success = false;
        }
        if( success && ver.IsLessThan( recVerMajor, recVerMinor, recVerRevision ) ) {
            success = UpgradeRevision( ver );
        }
    }
    if( success == false ) {
        CloseDb();
    }
    return success;
}

void recDb::ErrorMessage( wxSQLite3Exception& e )
{
    wxString err;
    err << e.GetErrorCode() << ": " << e.GetMessage();
    wxMessageBox( err, _("Database Error") );
}

bool recDb::DeleteRecord( const char* name, idt id )
{
    if( id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "DELETE FROM %q WHERE id="ID";", name, id );

    if( s_db->ExecuteUpdate( sql ) != 1 ) {
        return false;
    }
    return true;
}

bool recDb::RecordExists( const char* name, idt id )
{
    if( id == 0 ) {
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format( "SELECT COUNT(*) FROM %q WHERE id="ID";", name, id );

    if( s_db->ExecuteScalar( sql ) != 1 ) {
        return false;
    }
    return true;
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

// End of recDatabase.cpp file
