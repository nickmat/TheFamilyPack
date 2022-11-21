/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recFamEventa.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 FamilyEventa records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th April 2015
 * Copyright:   Copyright (c) 2015..2022, Nick Matthews.
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

#include <rec/recFamIndEventa.h>

//============================================================================
//--------------------------[ recFamilyIndEventa ]----------------------------
//============================================================================

recFamilyIndEventa::recFamilyIndEventa( const recFamilyIndEventa& d )
{
    f_id           = d.f_id;
    f_fam_ind_id   = d.f_fam_ind_id;
    f_eventa_id    = d.f_eventa_id;
    f_conf         = d.f_conf;
    f_note         = d.f_note;
}

void recFamilyIndEventa::Clear()
{
    f_id           = 0;
    f_fam_ind_id   = 0;
    f_eventa_id    = 0;
    f_conf         = 0;
    f_note         = wxEmptyString;
}

void recFamilyIndEventa::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".FamilyIndEventa "
            "(fam_ind_id, eventa_id, conf, note) "
            "VALUES (" ID ", " ID ", %f, '%q');",
            UTF8_( dbname ), f_fam_ind_id, f_eventa_id, f_conf, UTF8_(f_note)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".FamilyIndEventa "
                "(id, fam_ind_id, eventa_id, conf, note) "
                "VALUES (" ID ", " ID ", " ID ", %f, '%q');",
                UTF8_( dbname ), f_id, f_fam_ind_id, f_eventa_id, f_conf, UTF8_(f_note)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".FamilyIndEventa SET fam_id=" ID ", eventa_id=" ID ", "
                "conf=%f, note='%q' "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_fam_ind_id, f_eventa_id, f_conf,
                UTF8_(f_note), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamilyIndEventa::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT fam_ind_id, eventa_id, conf, note "
        "FROM \"%s\".FamilyIndEventa WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_fam_ind_id   = GET_ID( result.GetInt64( 0 ) );
    f_eventa_id    = GET_ID( result.GetInt64( 1 ) );
    f_conf         = result.GetDouble( 2 );
    f_note         = result.GetAsString( 3 );
    return true;
}

bool recFamilyIndEventa::Equivalent( const recFamilyIndEventa& r2 ) const
{
    return
        FGetFamIndID() == r2.FGetFamIndID() &&
        FGetEventaID() == r2.FGetEventaID() &&
        FGetConf() == r2.FGetConf() &&
        FGetNote() == r2.FGetNote()
    ;
}

idt recFamilyIndEventa::Create( idt fiID, idt eaID, double conf, const wxString& note )
{
    recFamilyIndEventa fiea(0);

    fiea.FSetFamIndID( fiID );
    fiea.FSetEventaID( eaID );
    fiea.FSetConf( conf );
    fiea.FSetNote( note );
    fiea.Save();

    return fiea.FGetID();
}


/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recFamilyIndEventa::Find( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_fam_ind_id == 0 || f_eventa_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, conf, note FROM \"%s\".FamilyIndEventa "
        "WHERE fam_ind_id=" ID " AND eventa_id=" ID ";",
        UTF8_( dbname ), f_fam_ind_id, f_eventa_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_conf = result.GetDouble( 1 );
    f_note = result.GetAsString( 2 );
    return true;
}

/*! Given the Event id and Eventa id, find the matching record id.
 */
idt recFamilyIndEventa::Find( idt fiID, idt eaID, const wxString& dbname )
{
    recFamilyIndEventa fiea(0);

    fiea.FSetFamIndID( fiID );
    fiea.FSetEventaID( eaID );
    fiea.Find( dbname );
    return fiea.FGetID();
}

std::string recFamilyIndEventa::CsvTitles()
{
    return std::string(
        "ID, FamilyIndividual ID, Eventa ID, Confidence, Note\n"
    );
}

void recFamilyIndEventa::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recFamilyIndEventa fie( id, dbname );
    recCsvWrite( out, fie.FGetID() );
    recCsvWrite( out, fie.FGetFamIndID() );
    recCsvWrite( out, fie.FGetEventaID() );
    recCsvWrite( out, fie.FGetConf() );
    recCsvWrite( out, fie.FGetNote(), '\n' );
}

bool recFamilyIndEventa::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_fam_ind_id );
    recCsvRead( in, f_eventa_id );
    recCsvRead( in, f_conf );
    recCsvRead( in, f_note );
    return bool( in );
}


// End of include/rec/recFamEventa.cpp file
