/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recVersion.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Version record.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
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

#include <rec/recVersion.h>

const int recVerMajor    = 0;
const int recVerMinor    = 0;
const int recVerRev      = 9;
const int recVerTest     = 0;
const wxStringCharType* recVerStr = wxS("0.0.9.0");


recVersion::recVersion( const recVersion& v )
{
    f_id       = v.f_id;
    f_major    = v.f_major;
    f_minor    = v.f_minor;
    f_revision = v.f_revision;
}

void recVersion::Clear()
{
    f_id       = 0;
    f_major    = 0;
    f_minor    = 0;
    f_revision = 0;
}

void recVersion::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Version (major, minor, revision, test) "
            "VALUES (%d, %d, %d, %d);",
            f_major, f_minor, f_revision, f_test
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Version (id, major, minor, revision, test) "
                "VALUES ("ID", %d, %d, %d, %d);",
                f_id, f_major, f_minor, f_revision, f_test
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Version SET major=%d, minor=%d, revision=%d, test=%d "
                "WHERE id="ID";",
                f_major, f_minor, f_revision, f_test, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recVersion::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT major, minor, revision, test FROM Version WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_major    = result.GetInt( 0 );
    f_minor    = result.GetInt( 1 );
    f_revision = result.GetInt( 2 );
    f_test     = result.GetInt( 3 );
    return true;
}

wxString recVersion::GetVersionStr()
{
    recVersion v(1);
    return wxString::Format(
        "%d.%d.%d.%d",
        v.f_major, v.f_minor, v.f_revision, v.f_test
    );
}


bool recVersion::IsEqual( int major, int minor, int revision, int test ) const
{
    bool ret = (f_major == major);

    if( minor == -1 ) return ret;
    ret = ret && (f_minor == minor);

    if( revision == -1 ) return ret;
    ret = ret && (f_revision == revision);

    if( test == -1 ) return ret;
    return ret && (f_test == test);
}

bool recVersion::IsMoreThan( int major, int minor, int revision, int test ) const
{
    if( f_major > major ) return true;
    if( f_major < major ) return false;

    if( minor == -1 ) return false;
    if( f_minor > minor ) return true;
    if( f_minor < minor ) return false;

    if( revision == -1 ) return false;
    if( f_revision > revision ) return true;
    if( f_revision < revision ) return false;

    if( test == -1 ) return false;
    if( f_test > test ) return true;
    return false;
}

bool recVersion::IsLessThan( int major, int minor, int revision, int test ) const
{
    if( f_major < major ) return true;
    if( f_major > major ) return false;

    if( minor == -1 ) return false;
    if( f_minor < minor ) return true;
    if( f_minor > minor ) return false;

    if( revision == -1 ) return false;
    if( f_revision < revision ) return true;
    if( f_revision > revision ) return false;

    if( test == -1 ) return false;
    if( f_test < test ) return true;
    return false;
}

#if 0
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

static const char* upgrade0_0_8_2 = 
    "ALTER TABLE Attribute ADD COLUMN sequence INTEGER;\n"
    "ALTER TABLE Name ADD COLUMN sequence INTEGER;\n"
;

static const char* upgrade0_0_8_3 = 
    "BEGIN;\n"
    "ALTER TABLE Persona RENAME TO OldPersona;\n"
    "CREATE TABLE Persona (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  sex INTEGER,\n"
    "  note TEXT\n"
    ");\n"
    "INSERT INTO Persona"
    " (id, sex, note)"
    " SELECT id, sex, note FROM OldPersona;\n"
    "DROP TABLE OldPersona;\n"
    "UPDATE Version SET major=0, minor=0, revision=8, test=4 WHERE id=1;\n"
    "COMMIT;\n"
;
#endif


bool recVersion::TestForUpgrade() 
{
    if( IsLessThan( 0, 0, 9, 0 ) ) {
        wxMessageBox(
            wxString::Format( 
                _("Cannot read old database version %s file."),
                GetVersionStr() 
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( IsMoreThan( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        wxMessageBox(
            wxString::Format( 
                _("Cannot read future database version %s file."),
                GetVersionStr() 
            ),
            _("Upgrade Test")
        );
        return false;
    }
    return true;
}


bool recVersion::DoUpgrade() 
{
    wxASSERT( f_id == 1 );
    if( TestForUpgrade() == false ) return false;
#if 0
    try {
        if( ver.f_test == 3 ) {
            recDb::GetDb()->ExecuteUpdate( upgrade0_0_8_3 ); // To 0.0.8.4
            Read();
        }
    }
    catch( wxSQLite3Exception& e ) {
        recDb::ErrorMessage( e );
        recDb::Rollback();
        return false;
    }
#endif
    wxASSERT( IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) );
    return true;
}


// End of recVersion.cpp file
