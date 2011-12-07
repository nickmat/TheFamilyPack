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

int recDate::sm_count = 0;

recDate::recDate( const recDate& d )
{
    f_id          = d.f_id;
    f_jdn         = d.f_jdn;
    f_range       = d.f_range;
    f_base_id     = d.f_base_id;
    f_base_unit   = d.f_base_unit;
    f_base_style  = d.f_base_style;
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
    f_base_id     = 0;
    f_base_unit   = CALENDAR_UNIT_Unstated;
    f_base_style  = BASE_STYLE_Unstated;
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
            "(jdn, range, base_id, base_unit, base_style, type, descrip, record_sch, display_sch) "
            "VALUES (%ld, %ld, "ID", %d, %d, %u, '%q', %d, %d);",
            f_jdn, f_range, f_base_id, f_base_unit, f_base_style, f_type, UTF8_(f_descrip), 
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
                "(id, jdn, range, base_id, base_unit, base_style, type, descrip, record_sch, display_sch) "
                "VALUES ("ID", %ld, %ld, "ID", %d, %d, %u, '%q', %d, %d);",
                f_id, f_jdn, f_range, f_base_id, f_base_unit, f_base_style, f_type, UTF8_(f_descrip),
                f_record_sch, f_display_sch
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Date SET jdn=%ld, range=%ld, base_id="ID", base_unit=%d, "
                "base_style=%d, type=%u, descrip='%q', record_sch=%d, display_sch=%d "
                "WHERE id="ID";",
                f_jdn, f_range, f_base_id, f_base_unit, f_base_style, f_type, UTF8_(f_descrip), 
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
        "SELECT jdn, range, base_id, base_unit, base_style, type, descrip, record_sch, display_sch "
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
    f_base_id     = GET_ID( result.GetInt64( 2 ) );
    f_base_unit   = (CalendarUnit) result.GetInt( 3 );
    f_base_style  = (BaseStyle) result.GetInt( 4 );
    f_type        = (TypeFlag) result.GetInt( 5 );
    f_descrip     = result.GetAsString( 6 );
    f_record_sch  = (CalendarScheme) result.GetInt( 7 );
    f_display_sch = (CalendarScheme) result.GetInt( 8 );
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
    bool ret = calStrToJdnRange( beg, end, s, scheme );
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

wxString recDate::GetJdnStr( CalendarScheme scheme ) const
{
    long jdn1, jdn2;
    unsigned prefix;
    if( scheme == CALENDAR_SCH_Unstated ) scheme = f_display_sch;
    sm_count = recDate_MAX_RECURSION_COUNT;
    GetJdn1Jdn2( jdn1, jdn2, prefix, scheme );
    if( jdn1 == 0 )
    {
        return f_descrip;
    }
    return calStrFromJdnRange( jdn1, jdn2, scheme );
}

wxString recDate::GetJdnStr( idt id )
{
    recDate d( id );
    return d.GetJdnStr();
}

wxString recDate::GetStr( CalendarScheme scheme ) const
{
    long jdn1, jdn2;
    unsigned prefix;
    if( scheme == CALENDAR_SCH_Unstated ) scheme = f_display_sch;
    sm_count = recDate_MAX_RECURSION_COUNT;
    GetJdn1Jdn2( jdn1, jdn2, prefix, scheme );
    if( jdn1 == 0 )
    {
        return f_descrip;
    }

    return wxString::Format(
        s_prefFormat[prefix],
        calStrFromJdnRange( jdn1, jdn2, scheme )
    );
}

wxString recDate::GetStr( idt id )
{
    recDate d( id );
    return d.GetStr();
}

int recDate::GetYear( CalendarScheme scheme )
{
    long jdn, jdn1, jdn2;
    unsigned prefix;
    int year;
    CalendarScheme sch = (scheme == CALENDAR_SCH_Unstated) ? f_display_sch : scheme;
    sm_count = recDate_MAX_RECURSION_COUNT;

    GetJdn1Jdn2( jdn1, jdn2, prefix, sch );
    jdn = ( jdn1 + jdn2 ) / 2;
    if( jdn == 0  ) {
        return 0;
    }
    calYearFromJdn( year, jdn, sch );
    return year;
}

int recDate::GetYear( idt dateID, CalendarScheme sch )
{
    recDate d(dateID);
    return d.GetYear( sch );
}

long recDate::GetDatePoint( DatePoint dp )
{
    long jdn, jdn1, jdn2;
    unsigned prefix;
    CalendarScheme sch = f_display_sch;
    sm_count = recDate_MAX_RECURSION_COUNT;

    GetJdn1Jdn2( jdn1, jdn2, prefix, sch );
    switch( dp )
    {
    case DATE_POINT_Beg:
        jdn = jdn1;
        break;
    case DATE_POINT_Mid:
        jdn = ( jdn1 + jdn2 ) / 2;
        break;
    case DATE_POINT_End:
        jdn = jdn2;
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

void recDate::GetJdn1Jdn2( long& jdn1, long& jdn2, unsigned& prefix, CalendarScheme scheme ) const
{
    --sm_count;
    if( sm_count == 0 ) {
        wxASSERT( false ); // This shoudn't happen.
        jdn1 = jdn2 = 0;
        return;
    }
    if( f_base_id == 0 ) {
        jdn1 = f_jdn;
        jdn2 = f_jdn + f_range;
        prefix = GetTypePrefix();
    } else {
        recDate base( f_base_id );
        base.GetJdn1Jdn2( jdn1, jdn2, prefix, scheme );
        switch( f_base_style )
        {
        case BASE_STYLE_AgeRoundDown:
            calAddToJdn( jdn1, -(f_jdn+f_range), f_base_unit, scheme );
            jdn1++;
            calAddToJdn( jdn2, -f_jdn, f_base_unit, scheme );
            break;
        }
        prefix |= GetTypePrefix();
    }
}

// End of recDate.cpp file
