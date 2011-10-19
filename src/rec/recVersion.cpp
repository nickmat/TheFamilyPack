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
// For updates
#include <rec/recPersona.h>
#include <rec/recLink.h>

// This is the database version this program is designed to work with.
const int recVerMajor    = 0;
const int recVerMinor    = 0;
const int recVerRev      = 9;
const int recVerTest     = 2;
const wxStringCharType* recVerStr = wxS("0.0.9.2");


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

void recVersion::Set( int major, int minor, int revision, int test )
{
    recVersion v;
    v.f_id = 1;
    v.f_major = major;
    v.f_minor = minor;
    v.f_revision = revision;
    v.f_test = test;
    v.Save();
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

bool recVersion::TestForUpgrade()
{
    if( IsLessThan( 0, 0, 9, 0 ) ) {
        recDb::Message(
            wxString::Format(
                _("Cannot read old database version %s file."),
                GetVersionStr()
            ),
            _("Upgrade Test")
        );
        return false;
    }
    if( IsMoreThan( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        recDb::Message(
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

//============================================================================
//                 Code to upgrade old versions
//============================================================================

static const char* upgrade0_0_9_0 =
    "BEGIN;\n"

    "ALTER TABLE Event RENAME TO OldEvent;\n"
    "CREATE TABLE Event (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  title TEXT,\n"
    "  type_id INTEGER,\n"
    "  date1_id INTEGER,\n"
    "  date2_id INTEGER,\n"
    "  place_id INTEGER,\n"
    "  note TEXT\n"
    ");\n"
    "INSERT INTO Event"
    " (id, title, type_id, date1_id, date2_id, place_id, note)"
    " SELECT id, title, type_id, date1_id, date2_id, place_id, note FROM OldEvent;"
    "DROP TABLE OldEvent;"

    "ALTER TABLE EventPersona RENAME TO OldEventPersona;\n"
    "CREATE TABLE EventPersona (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  event_id INTEGER,\n"
    "  per_id INTEGER,\n"
    "  role_id INTEGER,\n"
    "  note TEXT,\n"
    "  sequence INTEGER\n"
    ");\n"
    "INSERT INTO EventPersona"
    " (id, event_id, per_id, role_id, note, sequence)"
    " SELECT id, event_id, per_id, role_id, note, 0 FROM OldEventPersona;"
    "DROP TABLE OldEventPersona;"

    "UPDATE Version SET major=0, minor=0, revision=9, test=1 WHERE id=1;\n"
    "COMMIT;\n"
    ;

static const char* upgrade0_0_9_1 =
    "CREATE TABLE LinkPersona (\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  ref_per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
    "  ind_per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
    "  conf FLOAT NOT NULL,\n"
    "  comment TEXT\n"
    ");\n"
    ;

static void UpgradeData0_0_9_1() // To 0.0.9.2
{
    recDb::Begin();
    recDb::GetDb()->ExecuteUpdate( upgrade0_0_9_1 );

    recLinkPersona lp;
    const char* query =
        "SELECT IP.per_id, I.per_id, IP.note "
        "FROM IndividualPersona IP, Individual I "
        "WHERE IP.ind_id=I.id AND NOT IP.per_id=I.per_id;"
        ;
    wxSQLite3ResultSet result = recDb::GetDb()->ExecuteQuery( query );
    while( result.NextRow() ) {
        lp.f_id = 0;
        lp.f_ref_per_id = GET_ID( result.GetInt64( 0 ) );
        lp.f_ind_per_id = GET_ID( result.GetInt64( 1 ) );
        lp.f_conf = 0.999;
        lp.f_comment = result.GetAsString( 2 );
        lp.Save();
    }
    recVersion::Set( 0, 0, 9, 2);
    recDb::Commit();
}


bool recVersion::DoUpgrade()
{
    wxASSERT( f_id == 1 );
    if( TestForUpgrade() == false ) return false;

    try {
        if( IsEqual( 0, 0, 9, 0 ) ) {
            s_db->ExecuteUpdate( upgrade0_0_9_0 ); // To 0.0.9.1
            Read();
        }
        if( IsEqual( 0, 0, 9, 1 ) ) {
            UpgradeData0_0_9_1();
            Read();
        }
    }
    catch( wxSQLite3Exception& e ) {
        ErrorMessage( e );
        Rollback();
        return false;
    }

    wxASSERT( IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) );
    return true;
}


// End of recVersion.cpp file
