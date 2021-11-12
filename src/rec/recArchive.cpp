/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recArchive.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Archive database records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#include <rec/recArchive.h>

//============================================================================
//                 recArchive
//============================================================================

recArchive::recArchive( const recArchive& at )
{
    f_id = at.f_id;
    f_name = at.f_name;
    f_note = at.f_note;
    f_con_list_id = at.f_con_list_id;
}

void recArchive::Clear()
{
    f_id = 0;
    f_name.clear();
    f_note.clear();
    f_con_list_id = 0;
}

void recArchive::Save()
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Archive (name, note, con_list_id)"
            " VALUES ('%q', '%q', " ID ");",
            UTF8_(f_name), UTF8_(f_note), f_con_list_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Archive (id, name, note, con_list_id)"
                " VALUES (" ID ", '%q', '%q', " ID ");",
                f_id, UTF8_(f_name), UTF8_(f_note), f_con_list_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Archive SET name='%q', note='%q', con_list_id=" ID
                " WHERE id=" ID ";",
                UTF8_(f_name), UTF8_(f_note), f_con_list_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recArchive::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT name, note, con_list_id FROM Archive WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_name = result.GetAsString( 0 );
    f_note = result.GetAsString( 1 );
    f_con_list_id = GET_ID( result.GetInt64( 2 ) );
    return true;
}

bool recArchive::Equivalent( const recArchive& r2 ) const
{
    return
        f_name == r2.f_name &&
        f_note == r2.f_note &&
        f_con_list_id == r2.f_con_list_id;
}

recArchiveVec recArchive::GetFullList()
{
    recArchiveVec list;
    wxSQLite3ResultSet result = s_db->ExecuteQuery(
        "SELECT id, name, note, con_list_id FROM Archive"
        " ORDER BY id;"
    );

    recArchive arch( 0 );
    while( result.NextRow() ) {
        arch.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        arch.FSetName( result.GetAsString( 1 ) );
        arch.FSetNote( result.GetAsString( 2 ) );
        arch.FSetConListId( GET_ID( result.GetInt64( 3 ) ) );
        list.push_back( arch );
    }
    return list;
}

//============================================================================
//                 recArchiveReference
//============================================================================

recArchiveReference::recArchiveReference( const recArchiveReference& at )
{
    f_id         = at.f_id;
    f_archive_id = at.f_archive_id;
    f_ref_id     = at.f_ref_id;
    f_call_num   = at.f_call_num;
    f_note       = at.f_note;
}

void recArchiveReference::Clear()
{
    f_id = 0;
    f_archive_id = 0;
    f_ref_id = 0;
    f_call_num.clear();
    f_note.clear();
}

void recArchiveReference::Save()
{
    wxSQLite3StatementBuffer sql;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO ArchiveReference (archive_id, ref_id, call_num, note)"
            " VALUES (" ID ", " ID ", '%q', '%q');",
            f_archive_id, f_ref_id, UTF8_(f_call_num), UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO ArchiveReference (id, archive_id, ref_id, call_num, note)"
                " VALUES (" ID ", " ID ", " ID ", '%q', '%q');",
                f_id, f_archive_id, f_ref_id, UTF8_(f_call_num), UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE ArchiveReference SET archive_id=" ID ", ref_id=" ID ","
                " call_num='%q', note='%q' WHERE id=" ID ";",
                f_archive_id, f_ref_id, UTF8_(f_call_num), UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recArchiveReference::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT archive_id, ref_id, call_num, note FROM ArchiveReference WHERE id=" ID ";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_archive_id  = GET_ID( result.GetInt64( 0 ) );
    f_ref_id = GET_ID( result.GetInt64( 1 ) );
    f_call_num = result.GetAsString( 2 );
    f_note = result.GetAsString( 3 );
    return true;
}

bool recArchiveReference::Equivalent( const recArchiveReference& r2 ) const
{
    return
        f_archive_id == r2.f_archive_id &&
        f_ref_id == r2.f_ref_id &&
        f_call_num == r2.f_call_num &&
        f_note == r2.f_note;
}

// End of src/rec/recArchive.cpp file
