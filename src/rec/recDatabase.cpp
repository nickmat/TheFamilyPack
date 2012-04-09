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

wxSQLite3Database* recDb::s_db = NULL;
recDb::Environment recDb::s_env = recDb::ENV_GUI;
wxString           recDb::s_fname;
long               recDb::s_change = 0;

idt recGetID( const wxString& str )
{
    idt id = 0;
    str.ToLongLong( &id );  
    return id;
}

wxString recGetSexStr( Sex sex )
{
    static wxString sexarray[] = {
        _("Unstated"), _("Male"), _("Female"), _("Unknown")
    };
    return sexarray[sex];
}

wxString recHTMLifyStr( const wxString& str )
{
    wxString htm;
    wxString::const_iterator it;
    for( it = str.begin() ; it != str.end() ; it++ ) {
        switch( (*it).GetValue() )
        {
        case '\n':
            htm << "<br>";
            break;
        case '&':
            htm << "&amp;";
            break;
        case '<':
            htm << "&lt;";
            break;
        case '>':
            htm << "&gt;";
            break;
        default:
            htm << *it;
        }
    }
    return htm;
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
            Message( _("File already exists"), _("Create Database") );
            // TODO: replace existing file
            return false;
        }
    }

    if( s_db->IsOpen() ) {
        Message( _("Database already open"), _("Create Database") );
        return false;
    }

    wxString dbfname = dbfile.GetFullPath();
    s_db->Open( dbfname );
    s_db->ExecuteUpdate( createdb );
    dbfile.Normalize();
    s_fname = dbfile.GetFullPath();
    return true;
}

bool recDb::OpenDb( const wxString& fname )
{
    if( IsOpen() ) {
        Message( _("Database already open"), _("Open Database") );
        return false;
    }
    bool success = true;
    s_fname = fname;

    s_db->Open( fname );
    recVersion ver(1);
    if( !ver.IsEqual( recVerMajor, recVerMinor, recVerRev, recVerTest ) ) {
        success = ver.DoUpgrade();
    }
    if( success == false ) {
        CloseDb();
    }
    return success;
}

void recDb::Message( const wxString& mess, const wxString& func )
{
    switch( s_env )
    {
    case ENV_GUI:
        wxMessageBox( mess, func );
        break;
    case ENV_CmdLine:
        wxPrintf( "%s: %s\n", func, mess );
        break;
    }
}

void recDb::ErrorMessage( wxSQLite3Exception& e )
{
    wxString err;
    err << e.GetErrorCode() << ": " << e.GetMessage();
    Message( err, _("Database Error") );
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
