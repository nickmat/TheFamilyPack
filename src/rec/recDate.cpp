/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Date records.
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

#include <rec/recDate.h>
#include <rec/recEvent.h>
#include <rec/recPlace.h>
#include <rec/recSource.h>

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
}

void recDate::Clear()
{
    f_id          = 0;
    f_jdn         = 0;
    f_range       = 0;
    f_rel_id      = 0;
    f_type        = FLG_NULL;
    f_descrip     = wxEmptyString;
    f_record_sch  = CALENDAR_SCH_Unstated;
    f_display_sch = CALENDAR_SCH_Unstated;
}

void recDate::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Date "
            "(jdn, range, rel_id, type, descrip, record_sch, display_sch) "
            "VALUES (%ld, %ld, "ID", %u, '%q', %d, %d);",
            f_jdn, f_range, f_rel_id, f_type, UTF8_(f_descrip), 
            f_record_sch, f_display_sch
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Date "
                "(id, jdn, range, rel_id, type, descrip, record_sch, display_sch) "
                "VALUES ("ID", %ld, %ld, "ID", %u, '%q', %d, %d);",
                f_id, f_jdn, f_range, f_rel_id, f_type, UTF8_(f_descrip),
                f_record_sch, f_display_sch
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Date SET jdn=%ld, range=%ld, rel_id="ID", "
                "type=%u, descrip='%q', record_sch=%d, display_sch=%d "
                "WHERE id="ID";",
                f_jdn, f_range, f_rel_id, f_type, UTF8_(f_descrip), 
                f_record_sch, f_display_sch, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recDate::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT jdn, range, rel_id, type, descrip, record_sch, display_sch "
        "FROM Date WHERE id="ID";",
        f_id
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
    return true;
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
    date.Save();
    return date.f_id;
}

idt recDate::Create( const recRelativeDate& rel )
{
    recDate date;

    date.SetDefaults();
    date.f_rel_id = rel.f_id;
    rel.CalculateDate( &date );

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

    date.Save();
    return date.FGetID();
}

bool recDate::SetDate( const wxString& str, CalendarScheme scheme )
{
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

wxString recDate::GetStr( idt id )
{
    recDate d( id );
    return d.GetStr();
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

int recDate::GetYear( idt dateID, CalendarScheme sch )
{
    recDate d(dateID);
    return d.GetYear( sch );
}

long recDate::GetDatePoint( DatePoint dp )
{
    long jdn;
    CalendarScheme sch = f_display_sch;

    switch( dp )
    {
    case DATE_POINT_Beg:
        jdn = f_jdn;
        break;
    case DATE_POINT_Mid:
        jdn = f_jdn + ( f_range / 2 );
        break;
    case DATE_POINT_End:
        jdn = f_jdn + f_range;
        break;
    default:
        jdn = 0;
    }
    return jdn;
}

long recDate::GetDatePoint( idt id, DatePoint dp )
{
    recDate date(id);
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

bool recDate::IsUsedAsBase( idt id )
{
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM RelativeDate WHERE base_id="ID";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

// List of all relative dates using dateID as a base. 
recIdVec recDate::GetRelativeIdList( idt dateID )
{
    recIdVec list;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format( "SELECT id FROM RelativeDate WHERE base_id="ID";", dateID );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        list.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return list;
}

bool recDate::IsUsedInEvent( idt id )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM Event WHERE date1_id="ID" OR date2_id="ID";",
        id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

bool recDate::IsUsedInSource( idt id )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM Source WHERE sub_date1_id="ID" OR sub_date2_id="ID";",
        id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

bool recDate::IsUsedInPlace( idt id )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM Place WHERE date1_id="ID" OR date2_id="ID";",
        id, id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) {
        return true;
    }
    return false;
}

void recDate::DeleteIfOrphaned( idt id )
{
    if( id <= 0 ) {
        // Don't delete universal dates.
        return;
    }
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT COUNT(*) FROM RelativeDate WHERE base_id="ID";", id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    sql.Format( "SELECT COUNT(*) FROM Event WHERE date1_id="ID" OR date2_id="ID";", id, id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    sql.Format( "SELECT COUNT(*) FROM EventRecord WHERE date1_id="ID" OR date2_id="ID";", id, id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    sql.Format( "SELECT COUNT(*) FROM Place WHERE date1_id="ID" OR date2_id="ID";", id, id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    sql.Format( "SELECT COUNT(*) FROM Source WHERE sub_date1_id="ID" OR sub_date2_id="ID";", id, id );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    sql.Format(
        "SELECT COUNT(*) FROM ReferenceEntity"
        " WHERE entity_type=4 AND entity_id="ID";",
        id
    );
    if( s_db->ExecuteScalar( sql ) > 0 ) return;

    idt relID = ExecuteID( "SELECT rel_id FROM Date WHERE id="ID";", id );
    if( relID ) {
        idt baseID = ExecuteID( "SELECT base_id FROM RelativeDate WHERE id="ID";", relID );
        recRelativeDate::Delete( relID );
        DeleteIfOrphaned( baseID );
    }
    Delete( id );
}

void recDate::RemoveFromDatabase( idt id )
{
    if( id == 0 ) {
        return;
    }
    if( IsUsedAsBase( id ) ) {
        recIdVec rels = GetRelativeIdList( id );
        for( size_t i = 0 ; i < rels.size() ; i++ ) {
            recRelativeDate::RemoveFromDatabase( rels[i] );
        }
    }
    recEvent::RemoveDates( id );
    recPlace::RemoveDates( id );
    recSource::RemoveDates( id );
    recReferenceEntity::Delete( recReferenceEntity::TYPE_Date, id );
    // If this is a relative date, remove the relative part.
    recDate date(id);
    Delete( date.FGetRelID() ); 
    Delete( id );
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

void recRelativeDate::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO RelativeDate "
            "(val, range, unit, base_id, type, scheme) "
            "VALUES (%ld, %ld, %d, "ID", %d, %d);",
            f_val, f_range, f_unit, f_base_id, f_type, f_scheme
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO RelativeDate "
                "(id, val, range, unit, base_id, type, scheme) "
                "VALUES ("ID", %ld, %ld, %d, "ID", %d, %d);",
                f_id, f_val, f_range, f_unit, f_base_id, f_type, f_scheme
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE RelativeDate SET val=%ld, range=%ld, unit=%d, base_id="ID", "
                "type=%d, scheme=%d "
                "WHERE id="ID";",
                f_val, f_range, f_unit, f_base_id, f_type, f_scheme, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRelativeDate::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT val, range, unit, base_id, type, scheme"
        " FROM RelativeDate WHERE id="ID";",
        f_id
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

idt recRelativeDate::GetParentDate( idt rdID )
{
    return ExecuteID( "SELECT id FROM Date WHERE rel_id="ID";", rdID );
}

void recRelativeDate::RemoveFromDatabase( idt rdID )
{
    recDate::RemoveFromDatabase( GetParentDate( rdID ) );
}

// End of recDate.cpp file
