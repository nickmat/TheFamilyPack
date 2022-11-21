/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Date records.
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

#include <rec/recDate.h>

#include <rec/recEvent.h>
#include <rec/recPlace.h>
#include <rec/recReference.h>

const wxString recDate::s_prefStr[recDate::PREF_Max] = {
    _("Unstated"),       // PREF_Unstated
    _("After"),          // PREF_After
    _("On"),             // PREF_On
    _("On or After"),    // PREF_OrAfter
    _("Before"),         // PREF_Before
    _("Not"),            // PREF_Not
    _("On or Before"),   // PREF_OrBefore
    _("About")           // PREF_About
};

const wxString recDate::s_prefFormat[recDate::PREF_Max] = {
    _("%s"),          // PREF_Unstated
    _("aft %s"),      // PREF_After
    _("%s"),          // PREF_On
    _("%s or aft"),   // PREF_OrAfter
    _("bef %s"),      // PREF_Before
    _("not %s"),      // PREF_Not
    _("%s or bef"),   // PREF_OrBefore
    _("abt %s")       // PREF_About
};

recDate::recDate( const recDate& d )
{
    f_id          = d.f_id;
    f_jdn         = d.f_jdn;
    f_range       = d.f_range;
    f_rel_id      = d.f_rel_id;
    f_type        = d.f_type;
    f_descrip     = d.f_descrip;
    f_record_sch  = d.f_record_sch;
    f_display_sch = d.f_display_sch;
    f_uid = d.f_uid;
    f_changed = d.f_changed;
}

void recDate::Clear()
{
    f_id          = 0;
    f_jdn         = 0;
    f_range       = 0;
    f_rel_id      = 0;
    f_type        = FLG_NULL;
    f_descrip.clear();
    f_record_sch  = CALENDAR_SCH_Unstated;
    f_display_sch = CALENDAR_SCH_Unstated;
    f_uid.clear();
    f_changed = 0;
}

void recDate::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Date"
            " (jdn, range, rel_id, type, descrip, record_sch, display_sch, uid, changed)"
            " VALUES (%ld, %ld, " ID ", %u, '%q', %d, %d, '%q', %ld);",
            UTF8_( dbname ), f_jdn, f_range, f_rel_id, f_type, UTF8_(f_descrip),
            f_record_sch, f_display_sch, UTF8_( f_uid ), f_changed
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Date"
                " (id, jdn, range, rel_id, type, descrip, record_sch, display_sch, uid, changed)"
                " VALUES (" ID ", %ld, %ld, " ID ", %u, '%q', %d, %d, '%q', %ld);",
                UTF8_( dbname ), f_id, f_jdn, f_range, f_rel_id, f_type, UTF8_(f_descrip),
                f_record_sch, f_display_sch, UTF8_( f_uid ), f_changed
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Date SET jdn=%ld, range=%ld, rel_id=" ID ","
                " type=%u, descrip='%q', record_sch=%d, display_sch=%d, uid = '%q', changed = %ld"
                " WHERE id=" ID ";",
                UTF8_( dbname ), f_jdn, f_range, f_rel_id, f_type, UTF8_(f_descrip),
                f_record_sch, f_display_sch, UTF8_( f_uid ), f_changed, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recDate::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT jdn, range, rel_id, type, descrip, record_sch, display_sch, uid, changed"
        " FROM \"%s\".Date WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_jdn         = result.GetInt( 0 );
    f_range       = result.GetInt( 1 );
    f_rel_id      = GET_ID( result.GetInt64( 2 ) );
    f_type        = (TypeFlag) result.GetInt( 3 );
    f_descrip     = result.GetAsString( 4 );
    f_record_sch  = (CalendarScheme) result.GetInt( 5 );
    f_display_sch = (CalendarScheme) result.GetInt( 6 );
    f_uid = result.GetAsString( 7 );
    f_changed = result.GetInt( 8 );
    return true;
}

bool recDate::Equivalent( const recDate& r2 ) const
{
    return
        f_jdn == r2.f_jdn &&
        f_range == r2.f_range &&
        f_rel_id == r2.f_rel_id &&
        f_type == r2.f_type &&
        f_descrip == r2.f_descrip &&
        f_record_sch == r2.f_record_sch &&
        f_display_sch == r2.f_display_sch &&
        f_uid == r2.f_uid &&
        f_changed == r2.f_changed
        ;
}

void recDate::SetDefaults()
{
    // TODO: The default record/display scheme should be a system/user setting.
    Clear();
    f_type = PREF_On;
    f_record_sch = CALENDAR_SCH_Gregorian;
    f_display_sch = CALENDAR_SCH_Gregorian;
}

idt recDate::Create( const wxString& str )
{
    recDate date;
    date.SetDefaults();
    date.SetDate( str );
    date.f_uid = recCreateUid();
    date.f_changed = calGetTodayJdn();
    date.Save();
    return date.f_id;
}

idt recDate::Create( const recRelativeDate& rel )
{
    recDate date;

    date.SetDefaults();
    date.f_rel_id = rel.f_id;
    rel.CalculateDate( &date );
    date.f_uid = recCreateUid();
    date.f_changed = calGetTodayJdn();

    date.Save();
    return date.f_id;
}

idt recDate::Create( idt dateID )
{
    if( dateID == 0 ) {
        return 0;
    }
    recDate date(dateID);
    date.FSetID( 0 );
    date.FSetRelID( 0 );
    date.f_uid = recCreateUid();
    date.f_changed = calGetTodayJdn();

    date.Save();
    return date.FGetID();
}

bool recDate::SetDate( const wxString& str, CalendarScheme scheme )
{
    if( str.empty() ) {
        return false;
    }
    wxString lstr = str.Lower();
    lstr.Trim(true);
    lstr.Trim(false);
    wxString s = lstr;
    TypePrefix prefix = PREF_On;

    if( lstr.StartsWith( "aft ", &s ) ) {
        prefix = PREF_After;
    } else if( lstr.EndsWith( " or aft", &s ) ) {
        prefix = PREF_OrAfter;
    } else if( lstr.StartsWith( "bef ", &s ) ) {
        prefix = PREF_Before;
    } else if( lstr.StartsWith( "not ", &s ) ) {
        prefix = PREF_Not;
    } else if( lstr.EndsWith( " or bef", &s ) ) {
        prefix = PREF_OrBefore;
    } else if( lstr.StartsWith( "abt ", &s ) ) {
        prefix = PREF_About;
    }

    long beg, end;
    if( scheme == CALENDAR_SCH_Unstated ) scheme = f_record_sch;
    bool ret = calStrToJdnRange( &beg, &end, s, scheme );
    if( ret == true )
    {
        f_jdn = beg;
        f_range = end - beg;
        f_type = prefix;
        f_record_sch = scheme;
        f_descrip = wxEmptyString;
    } else {
        f_jdn = 0;
        f_range = 0;
        f_type = PREF_On;
        f_record_sch = scheme;
        f_descrip = str;
    }
    return ret;
}

bool recDate::SetDate( idt dateID, const wxString& str, CalendarScheme sch )
{
    wxASSERT( dateID != 0 );
    recDate date(dateID);
    bool ret = date.SetDate( str, sch );
    date.Save();
    return ret;
}

bool recDate::SetJdnDate( const wxString& str, CalendarScheme scheme )
{
    long beg, end;
    if( scheme == CALENDAR_SCH_Unstated ) scheme = f_record_sch;
    bool ret = calStrToJdnRange( &beg, &end, str, scheme );
    if( ret == true )
    {
        f_jdn = beg;
        f_range = end - beg;
    } else {
        f_jdn = 0;
        f_range = 0;
    }
    return ret;
}

void recDate::Update()
{
    if( f_rel_id == 0 ) return;

    recRelativeDate rel(f_rel_id);
    rel.CalculateDate( this );
}

wxString recDate::GetJdnStr( CalendarScheme scheme ) const
{
    if( scheme == CALENDAR_SCH_Unstated ) scheme = f_display_sch;
    if( f_jdn == 0 )
    {
        return f_descrip;
    }
    return calStrFromJdnRange( f_jdn, f_jdn+f_range, scheme );
}

wxString recDate::GetJdnStr( idt id, CalendarScheme sch )
{
    recDate d( id );
    return d.GetJdnStr( sch );
}

wxString recDate::GetInputJdnStr( idt id )
{
    recDate d( id );
    return d.GetJdnStr( d.f_record_sch );
}

wxString recDate::GetStr( CalendarScheme scheme ) const
{
    if( scheme == CALENDAR_SCH_Unstated ) scheme = f_display_sch;
    if( f_jdn == 0 ) {
        return f_descrip;
    }

    return wxString::Format(
        s_prefFormat[GetTypePrefix()],
        calStrFromJdnRange( f_jdn, f_jdn+f_range, scheme )
    );
}

wxString recDate::GetStr( idt id, const wxString& dbname )
{
    recDate d( id, dbname );
    return d.GetStr();
}

wxString recDate::GetPeriodStr( const recDate& date2 ) const
{
    wxString str2 = date2.GetStr();
    if( str2.empty() ) {
        return GetStr();
    }
    return GetStr() + " To " + str2;
}

wxString recDate::GetPeriodStr( idt d1ID, idt d2ID )
{
    wxString str2 = recDate::GetStr( d2ID );
    if( str2.empty() ) {
        return recDate::GetStr( d1ID );
    }
    return recDate::GetStr( d1ID ) + " To " + str2;
}

int recDate::GetYear( CalendarScheme scheme )
{
    long jdn;
    int year;
    CalendarScheme sch = (scheme == CALENDAR_SCH_Unstated) ? f_display_sch : scheme;

    jdn =  f_jdn + ( f_range / 2 );
    if( jdn == 0  ) {
        return 0;
    }
    calYearFromJdn( &year, jdn, sch );
    return year;
}

int recDate::GetYear( idt dateID, const wxString& dbname, CalendarScheme sch )
{
    recDate d( dateID, dbname );
    return d.GetYear( sch );
}

long recDate::GetDatePoint( DatePoint dp )
{
    long jdn;
    CalendarScheme sch = f_display_sch;

    switch( dp )
    {
    case DatePoint::beg:
        jdn = f_jdn;
        break;
    case DatePoint::mid:
        jdn = f_jdn + ( f_range / 2 );
        break;
    case DatePoint::end:
        jdn = f_jdn + f_range;
        break;
    default:
        jdn = 0;
    }
    return jdn;
}

long recDate::GetDatePoint( idt id, DatePoint dp, const wxString& dbname )
{
    recDate date( id, dbname );
    return date.GetDatePoint( dp );
}

unsigned recDate::GetCompareFlags( const recDate& date ) const
{
    unsigned flags = CF_NONE;

    if( (f_jdn+f_range) < date.f_jdn ) flags |= CF_RangeAfter;
    if( (f_jdn) > (date.f_jdn+date.f_range) ) flags |= CF_RangeBefore;
    if( !(flags & CF_RangeAfter) && !(flags & CF_RangeBefore) ) flags |= CF_Overlap;

    if( flags & CF_RangeAfter ) {
        if( f_type & FLG_AFTER ) flags |= CF_AfterOK;
        if( date.f_type & FLG_BEFORE ) flags |= CF_CompBeforeOK;
    }
    if( flags & CF_RangeBefore ) {
        if( f_type & FLG_BEFORE ) flags |= CF_CompBeforeOK;
        if( date.f_type & FLG_AFTER ) flags |= CF_CompAfterOK;
    }
    if( flags & ( CF_AfterOK | CF_BeforeOK | CF_CompBeforeOK | CF_CompAfterOK ) ) {
        flags |= CF_WithinType;
    }

    return flags;
}

bool recDate::IsOverlap( const recDate& date ) const
{
    unsigned flags = GetCompareFlags( date );
    return ( flags & recDate::CF_Overlap ) != 0;
}

bool recDate::IsConsistent( const recDate& date ) const
{
    unsigned flags = GetCompareFlags( date );
    return ( flags & recDate::CF_Overlap || flags & recDate::CF_WithinType ) != 0;
}

bool recDate::IsRelative( idt dateID, const wxString& dbname )
{
    recDate date( dateID, dbname );
    return date.IsRelative();
}

bool recDate::IsUsedAsBase( idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM \"%s\".RelativeDate WHERE base_id=" ID ";", UTF8_( dbname ), id );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

// List of all relative dates using dateID as a base.
recIdVec recDate::GetRelativeIdList( idt dateID, const wxString& dbname )
{
    recIdVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT id FROM \"%s\".RelativeDate WHERE base_id=" ID ";", UTF8_( dbname ), dateID );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        list.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return list;
}

bool recDate::IsUsedInEvent( idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Event WHERE date1_id=" ID " OR date2_id=" ID ";",
        UTF8_( dbname ), id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

bool recDate::IsUsedInPlace( idt id, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Place WHERE date1_id=" ID " OR date2_id=" ID ";",
        UTF8_( dbname ), id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

idt recDate::Transfer( idt from_dateID, const wxString& fromdb, const wxString& todb )
{
    if( from_dateID == 0 ) return 0;

    recDate from_date( from_dateID, fromdb );
    wxASSERT( from_date.FGetID() != 0 );

    idt to_dateID = from_dateID;
    if( to_dateID > 0 ) {
        to_dateID = recDate::FindUid( from_date.FGetUid(), todb );
    }
    recDate to_date( to_dateID, todb );

    idt to_rdID = from_date.FGetRelID();
    if( to_rdID > 0 ) {
        to_rdID = to_date.FGetRelID();
    }
    to_rdID = recRelativeDate::Transfer( from_date.FGetRelID(), fromdb, to_rdID, todb);
    if( to_date.FGetRelID() != 0 && to_rdID == 0 ) {
        // No longer is a relative date
        recRelativeDate::RemoveFromDatabase( to_date.FGetRelID(), todb );
    }

    recDate new_date( from_date );
    new_date.FSetID( to_dateID );
    new_date.FSetRelID( to_rdID );
    new_date.Save( todb );

    return new_date.FGetID();
}

void recDate::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE RelativeDate SET base_id=" ID " WHERE base_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Event SET date1_id=" ID " WHERE date1_id=" ID "; "
        "UPDATE Event SET date2_id=" ID " WHERE date2_id=" ID ";",
        to_id, id, to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Eventa SET date1_id=" ID " WHERE date1_id=" ID "; "
        "UPDATE Eventa SET date2_id=" ID " WHERE date2_id=" ID ";",
        to_id, id, to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Place SET date1_id=" ID " WHERE date1_id=" ID "; "
        "UPDATE Place SET date2_id=" ID " WHERE date2_id=" ID ";",
        to_id, id, to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE ReferenceEntity SET entity_id=" ID
        " WHERE entity_type=4 AND entity_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE Date SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recDate::CsvTitles()
{
    return std::string(
        "ID, Start Date, Range, Relative ID, Type Flags, Description,"
        " Recorded Scheme, Display Scheme, UID, Last Changed\n"
    );
}

void recDate::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recDate date( id, dbname );
    recCsvWrite( out, date.FGetID() );
    recCsvWrite( out, date.FGetJdn() );
    recCsvWrite( out, date.FGetRange() );
    recCsvWrite( out, date.FGetRelID() );
    recCsvWrite( out, date.FGetType() );
    recCsvWrite( out, date.FGetDescrip() );
    recCsvWrite( out, date.FGetRecordSch() );
    recCsvWrite( out, date.FGetDisplaySch() );
    recCsvWrite( out, date.FGetUid() );
    recCsvWrite( out, date.FGetChanged(), '\n' );
}

bool recDate::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_jdn );
    recCsvRead( in, f_range );
    recCsvRead( in, f_rel_id );
    recCsvRead( in, f_type );
    recCsvRead( in, f_descrip );
    recCsvRead( in, (int&) f_record_sch );
    recCsvRead( in, (int&) f_display_sch );
    recCsvRead( in, f_uid );
    recCsvRead( in, f_changed );
    return bool( in );
}

bool recDate::DeleteIfOrphaned( idt id, const wxString& dbname )
{
    if( id <= 0 ) { // Don't delete common dates.
        return false;
    }

    wxSQLite3StatementBuffer sql;
    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".RelativeDate WHERE base_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Event"
        " WHERE date1_id=" ID " OR date2_id=" ID ";",
        UTF8_( dbname ), id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Eventa"
        " WHERE date1_id=" ID " OR date2_id=" ID ";",
        UTF8_( dbname ), id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".Place"
        " WHERE date1_id=" ID " OR date2_id=" ID ";",
        UTF8_( dbname ), id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".ReferenceEntity"
        " WHERE entity_type=4 AND entity_id=" ID ";",
        UTF8_( dbname ), id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return false;

    idt relID = ExecuteID(
        "SELECT rel_id FROM \"%s\".Date WHERE id=" ID ";",
        UTF8_( dbname ), id
    );
    if( relID ) {
        idt baseID = ExecuteID(
            "SELECT base_id FROM \"%s\".RelativeDate WHERE id=" ID ";",
            UTF8_( dbname ), relID
        );
        recRelativeDate::Delete( relID, dbname );
        DeleteIfOrphaned( baseID, dbname );
    }
    return Delete( id, dbname );
}

bool recDate::RemoveFromDatabase( idt id, const wxString& dbname )
{
    if( id <= 0 ) { // Don't remove common dates
        return false;
    }
    if( IsUsedAsBase( id, dbname ) ) {
        recIdVec rels = GetRelativeIdList( id, dbname );
        for( size_t i = 0; i < rels.size(); i++ ) {
            idt dID = recRelativeDate::GetParentDate( rels[i], dbname );
            recDate::RemoveFromDatabase( dID, dbname );
        }
    }
    recEvent::RemoveDates( id, dbname );
    recEventa::RemoveDates( id, dbname );
    recPlace::RemoveDates( id, dbname );
    recReferenceEntity::DeleteType( recReferenceEntity::TYPE_Date, id, dbname );
    recDate date( id, dbname );
    bool ret = Delete( id, dbname );
    if( date.FGetRelID() != 0 ) {
        recRelativeDate::RemoveFromDatabase( date.FGetRelID(), dbname );
    }
    return ret;
}


//-----------------------------------------------------
//      recRelativeDate
//-----------------------------------------------------


recRelativeDate::recRelativeDate( const recRelativeDate& d )
{
    f_id      = d.f_id;
    f_val     = d.f_val;
    f_range   = d.f_range;
    f_base_id = d.f_base_id;
    f_unit    = d.f_unit;
    f_type    = d.f_type;
    f_scheme  = d.f_scheme;
}

void recRelativeDate::Clear()
{
    f_id      = 0;
    f_val     = 0;
    f_range   = 0;
    f_base_id = 0;
    f_unit    = CALENDAR_UNIT_Unstated;
    f_type    = TYPE_Unstated;
    f_scheme  = CALENDAR_SCH_Unstated;
}

void recRelativeDate::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".RelativeDate "
            "(val, range, unit, base_id, type, scheme) "
            "VALUES (%ld, %ld, %d, " ID ", %d, %d);",
            UTF8_( dbname ), f_val, f_range, f_unit, f_base_id, f_type, f_scheme
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".RelativeDate "
                "(id, val, range, unit, base_id, type, scheme) "
                "VALUES (" ID ", %ld, %ld, %d, " ID ", %d, %d);",
                UTF8_( dbname ), f_id, f_val, f_range, f_unit, f_base_id, f_type, f_scheme
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".RelativeDate SET val=%ld, range=%ld, unit=%d, base_id=" ID ", "
                "type=%d, scheme=%d "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_val, f_range, f_unit, f_base_id, f_type, f_scheme, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRelativeDate::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT val, range, unit, base_id, type, scheme"
        " FROM \"%s\".RelativeDate WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_val     = result.GetInt( 0 );
    f_range   = result.GetInt( 1 );
    f_unit    = (CalendarUnit) result.GetInt( 2 );
    f_base_id = GET_ID( result.GetInt64( 3 ) );
    f_type    = (Type) result.GetInt( 4 );
    f_scheme  = (CalendarScheme) result.GetInt( 5 );
    return true;
}

/*! The two entities are equal, ignoring the record id.
 */
bool recRelativeDate::Equivalent( const recRelativeDate& r2 ) const
{
    return
        f_val == r2.f_val &&
        f_range == r2.f_range &&
        f_unit == r2.f_unit &&
        f_base_id == r2.f_base_id &&
        f_type == r2.f_type &&
        f_scheme == r2.f_scheme
    ;
}

idt recRelativeDate::GetParentDate( idt rdID, const wxString& dbname )
{
    return ExecuteID(
        "SELECT id FROM \"%s\".Date WHERE rel_id=" ID ";",
        UTF8_( dbname ), rdID
    );
}

void recRelativeDate::SetDefaults()
{
    // TODO: The default scheme should be a system/user setting.
    Clear();
    f_range = 1;
    f_scheme = CALENDAR_SCH_Gregorian;
}


bool recRelativeDate::CalculateDate( recDate* date ) const
{
    recDate base( f_base_id );
    long jdn1 = base.f_jdn;
    long jdn2 = jdn1 + base.f_range + 1;

    switch( f_type )
    {
    case TYPE_AgeRoundDown:
        if( !calAddToJdn( &jdn1, -(f_val+f_range), f_unit, f_scheme ) ) {
            return false;
        }
        jdn1++;
        if( !calAddToJdn( &jdn2, -f_val, f_unit, f_scheme ) ) {
            return false;
        }
        break;
    case TYPE_Duration:
        if( !calAddToJdn( &jdn1, f_val, f_unit, f_scheme ) ) {
            return false;
        }
        if( !calAddToJdn( &jdn2, f_val, f_unit, f_scheme ) ) {
            return false;
        }
        break;
    case TYPE_AddToStart:
        if( !calAddToJdn( &jdn1, f_val, f_unit, f_scheme ) ) {
            return false;
        }
        break;
    case TYPE_AddToEnd:
        if( !calAddToJdn( &jdn2, f_val, f_unit, f_scheme ) ) {
            return false;
        }
        break;
    default:
        return false;
    }
    if( jdn1 == jdn2 ) {
        // Can't deal with zero length ranges
        return false;
    }
    if( jdn1 > jdn2 ) {
        long temp = jdn1;
        jdn1 = jdn2;
        jdn2 = temp;
    }
    date->f_jdn = jdn1;
    date->f_range = jdn2 - jdn1 - 1;
    date->f_type |= base.f_type;
    date->f_record_sch = f_scheme;
    return true;
}

idt recRelativeDate::Transfer( idt from_rdID, const wxString& fromdb, idt to_rdID, const wxString& todb )
{
    if( from_rdID == 0 ) return 0;

    recRelativeDate from_rd( from_rdID, fromdb );
    wxASSERT( from_rd.FGetID() != 0 );
    idt to_baseID = recDate::Transfer( from_rd.FGetBaseID(), fromdb, todb );

    recRelativeDate to_rd( from_rd );
    to_rd.FSetID( to_rdID );
    to_rd.FSetBaseID( to_baseID );
    to_rd.Save( todb );

    return to_rd.FGetID();
}

void recRelativeDate::Renumber( idt id, idt to_id )
{
    if( id == 0 ) {
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "UPDATE Date SET rel_id=" ID " WHERE rel_id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );

    sql.Format(
        "UPDATE RelativeDate SET id=" ID " WHERE id=" ID ";",
        to_id, id );
    s_db->ExecuteUpdate( sql );
}

std::string recRelativeDate::CsvTitles()
{
    return std::string( "ID, Value, Range, Unit, Base ID, Type, Scheme\n" );
}

void recRelativeDate::CsvWrite( std::ostream& out, idt id, const wxString& dbname )
{
    recRelativeDate rel( id, dbname );
    recCsvWrite( out, rel.FGetID() );
    recCsvWrite( out, rel.FGetVal() );
    recCsvWrite( out, rel.FGetRange() );
    recCsvWrite( out, rel.FGetUnit() );
    recCsvWrite( out, rel.FGetBaseID() );
    recCsvWrite( out, rel.FGetType() );
    recCsvWrite( out, rel.FGetScheme(), '\n' );
}

bool recRelativeDate::CsvRead( std::istream& in )
{
    recCsvRead( in, f_id );
    recCsvRead( in, f_val );
    recCsvRead( in, f_range );
    recCsvRead( in, (int&) f_unit );
    recCsvRead( in, f_base_id );
    recCsvRead( in, (int&) f_type );
    recCsvRead( in, (int&) f_scheme );
    return bool( in );
}

void recRelativeDate::RemoveFromDatabase( idt rdID, const wxString& dbname )
{
    if( rdID <= 0 ) { // Don't delete common dates.
        return;
    }
    recRelativeDate rd( rdID, dbname );
    rd.Delete( dbname );
    recDate::DeleteIfOrphaned( rd.FGetBaseID(), dbname );
}


// End of recDate.cpp file
