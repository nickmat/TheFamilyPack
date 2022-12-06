/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recFamilyIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyIndividual record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     8th January 2022
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
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

#include <rec/recFamilyIndividual.h>

//#include <wx/tokenzr.h>

//============================================================================
//-------------------------[ recFamilyIndividual ]----------------------------
//============================================================================

recFamilyIndividual::recFamilyIndividual( const recFamilyIndividual& fi )
{
    f_id         = fi.f_id;
    f_ind_id     = fi.f_ind_id;
    f_fam_id     = fi.f_fam_id;
    f_seq_child  = fi.f_seq_child;
    f_seq_parent = fi.f_seq_parent;
}

void recFamilyIndividual::Clear()
{
    f_id         = 0;
    f_ind_id     = 0;
    f_fam_id     = 0;
    f_seq_child  = 0;
    f_seq_parent = 0;
}

void recFamilyIndividual::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".FamilyIndividual (fam_id, ind_id, seq_child, seq_parent)"
            " VALUES (" ID ", " ID ", %d, %d);",
            UTF8_( dbname ), f_fam_id, f_ind_id, f_seq_child, f_seq_parent
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".FamilyIndividual (id, fam_id, ind_id, seq_child, seq_parent)"
                " VALUES (" ID ", " ID ", " ID ", %d, %d);",
                UTF8_( dbname ), f_id, f_fam_id, f_ind_id, f_seq_child, f_seq_parent
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".FamilyIndividual SET fam_id=" ID ", ind_id=" ID ","
                " seq_child=%d, seq_parent=%d"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_fam_id, f_ind_id, f_seq_child, f_seq_parent, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamilyIndividual::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ind_id, fam_id, seq_child, seq_parent FROM \"%s\".FamilyIndividual "
        "WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ind_id     = GET_ID( result.GetInt64( 0 ) );
    f_fam_id     = GET_ID( result.GetInt64( 1 ) );
    f_seq_child  = result.GetInt( 2 );
    f_seq_parent = result.GetInt( 3 );
    return true;
}

bool recFamilyIndividual::Equivalent( const recFamilyIndividual& r2 ) const
{
    return
        f_fam_id == r2.f_fam_id &&
        f_ind_id == r2.f_ind_id &&
        f_seq_child == r2.f_seq_child &&
        f_seq_parent == r2.f_seq_parent
    ;
}

bool recFamilyIndividual::Find( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_fam_id == 0 || f_ind_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, seq_child, seq_parent FROM \"%s\".FamilyIndividual "
        "WHERE fam_id=" ID " AND ind_id=" ID ";",
        UTF8_( dbname ), f_fam_id, f_ind_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() == 0 ) {
        f_id = 0;
        f_seq_child = 0;
        f_seq_parent = 0;
        return true;
    }
    result.SetRow( 0 );
    f_id         = GET_ID( result.GetInt64( 0 ) );
    f_seq_child  = result.GetInt( 1 );
    f_seq_parent = result.GetInt( 2 );
    if( result.GetRowCount() != 1 ) return false;
    return true;
}

std::string recFamilyIndividual::CsvTitles()
{
    return std::string( "id, fam_id, ind_id, seq_child, seq_parent\n" );
}

void recFamilyIndividual::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recFamilyIndividual fi( id, dbname );
    recCsvWrite( out, fi.FGetID() );
    recCsvWrite( out, fi.FGetFamID() );
    recCsvWrite( out, fi.FGetIndID() );
    recCsvWrite( out, fi.FGetSeqChild() );
    recCsvWrite( out, fi.FGetSeqParent(), '\n' );
}

bool recFamilyIndividual::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_fam_id );
    recCsvRead( in, f_ind_id );
    recCsvRead( in, f_seq_child );
    recCsvRead( in, f_seq_parent );
    return bool( in );
}

// End of src/rec/recFamilyIndividual.cpp file
