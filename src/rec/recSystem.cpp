/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recSystem.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 System records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     30 March 2012
 * Copyright:   Copyright (c) 2012 ~ 2017, Nick Matthews.
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

#include <rec/recSystem.h>

//============================================================================
//                 recSystem
//============================================================================

recSystem::recSystem( const recSystem& r2 )
{
    f_id       = r2.f_id;
    f_val      = r2.f_val;
}

void recSystem::Clear()
{
    f_id       = 0;
    f_val      = wxEmptyString;
}

void recSystem::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".System (val) VALUES ('%q');",
            UTF8_( dbname ), UTF8_(f_val)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() ) {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".System (id, val)"
                " VALUES (" ID " '%q');",
                UTF8_( dbname ), f_id, UTF8_(f_val)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".System SET val='%q' WHERE id=" ID ";",
                UTF8_( dbname ), UTF8_(f_val), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recSystem::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT val FROM \"%s\".System WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_val = result.GetAsString( 0 );
    return true;
}

bool recSystem::Equivalent( const recSystem& r2 ) const
{ 
    return f_val == r2.f_val;
}

wxString recSystem::GetPropertyValue( Property sp, const wxString& dbname )
{
    recSystem sys((idt) sp, dbname );
    return sys.FGetValue();
}

idt recSystem::GetPropertyValueID( Property sp, const wxString& dbname )
{
    recSystem sys((idt) sp, dbname );
    return recGetID( sys.FGetValue() );
}

void recSystem::SetProperyValue( Property sp, const wxString& value )
{
    recSystem sys((idt) sp);
    sys.FSetValue( value );
    sys.Save();
}

void recSystem::SetProperyValue( Property sp, idt id )
{
    recSystem sys((idt) sp);
    sys.FSetValue( recGetStr( id ) );
    sys.Save();
}

std::string recSystem::CsvTitles()
{
    return std::string( "ID, Value\n" );
}

void recSystem::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recSystem sys( id, dbname );
    recCsvWrite( out, sys.FGetID() );
    recCsvWrite( out, sys.FGetValue(), '\n' );
}

bool recSystem::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_val );
    return bool( in );
}

// End of recSystem.cpp file
