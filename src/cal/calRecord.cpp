/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calRecord.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Class to hold date as separarate fields.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     20th December 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
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

#include "calendar.h"
#include "calParse.h"
#include "calRecord.h"
#include "calJulian.h"
#include "calGregorian.h"
#include "calFrench.h"


namespace {

calBASE baseLookup[CALENDAR_SCH_Max] = {
    calBASE_NULL,      // CALENDAR_SCH_Unstated
    calBASE_NULL,      // CALENDAR_SCH_Unknown
    calBASE_NULL,      // CALENDAR_SCH_Unlisted
    calBASE_Jdn,       // CALENDAR_SCH_JulianDayNumber
    calBASE_NULL,      // CALENDAR_SCH_JulianDay
    calBASE_NULL,      // CALENDAR_SCH_ModJulianDay
    calBASE_NULL,      // CALENDAR_SCH_RataDie
    calBASE_Julian,    // CALENDAR_SCH_Julian
    calBASE_Gregorian, // CALENDAR_SCH_Gregorian
    calBASE_NULL,      // CALENDAR_SCH_Catholic
    calBASE_NULL,      // CALENDAR_SCH_English
    calBASE_NULL,      // CALENDAR_SCH_Scottish
    calBASE_NULL,      // CALENDAR_SCH_Swedish
    calBASE_French,    // CALENDAR_SCH_FrenchRevolution
};
    
size_t recordSize[calBASE_MAX] = { 0, 1, 3, 3, 3 };

wxString calLatinMonthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

wxString calFrenchMonthName[13] = {
    "Vend", "Brum", "Frim", "Nivo", "Pluv", "Vent",
    "Germ", "Flor", "Prai", "Mess", "Ther", "Fruc", "Comp"
};

} // namespace

calRecord::calRecord( CalendarScheme sch, long r0, long r1, long r2, long r3, long r4 )
{
    m_base = baseLookup[sch];
    m_size = recordSize[m_base];
    m_r[0] = r0;
    m_r[1] = r1;
    m_r[2] = r2;
    m_r[3] = r3;
    m_r[4] = r4;
}

calRecord::calRecord( CalendarScheme sch )
{
    Clear();
    m_base = baseLookup[sch];
    m_size = recordSize[m_base];
}

calRecord::calRecord( CalendarScheme sch, size_t size, const calToken* tokens )
{
    Clear();
    m_base = baseLookup[sch];
    m_size = recordSize[m_base];

    switch( m_base )
    {
    case calBASE_Jdn:
        wxASSERT( size == 1 );
        m_r[0] = tokens[0].GetNumber();
        break;
    case calBASE_Julian:
    case calBASE_Gregorian:
    case calBASE_French:
        switch( size )
        {
        case 1:
            m_r[0] = tokens[0].GetNumber(); // Year
            break;
        case 2:
            m_r[1] = tokens[0].GetNumber(); // Month
            m_r[0] = tokens[1].GetNumber(); // Year
            break;
        case 3:
            m_r[2] = tokens[0].GetNumber(); // Day
            m_r[1] = tokens[1].GetNumber(); // Month
            m_r[0] = tokens[2].GetNumber(); // Year
            break;
        }
        break;
    }
}

calRecord::calRecord( const calRecord& rec )
{
    Copy( rec );
}

void calRecord::Clear()
{
    // Clears only the registers
    m_r[0] = calR_INVALID;
    m_r[1] = calR_INVALID;
    m_r[2] = calR_INVALID;
    m_r[3] = calR_INVALID;
    m_r[4] = calR_INVALID;
}

void calRecord::Copy( const calRecord& rec )
{
    m_base = rec.m_base;
    m_size = rec.m_size;
    m_r[0] = rec.m_r[0];
    m_r[1] = rec.m_r[1];
    m_r[2] = rec.m_r[2];
    m_r[3] = rec.m_r[3];
    m_r[4] = rec.m_r[4];
}

void calRecord::SetR( long r0, long r1, long r2, long r3, long r4 )
{
    m_r[0] = r0;
    m_r[1] = r1;
    m_r[2] = r2;
    m_r[3] = r3;
    m_r[4] = r4;
}

long calRecord::GetR( long* r0, long* r1, long* r2, long* r3, long* r4 )
{
    if( r0 ) *r0 = m_r[0];
    if( r1 ) *r1 = m_r[1];
    if( r2 ) *r2 = m_r[2];
    if( r3 ) *r3 = m_r[3];
    if( r4 ) *r4 = m_r[4];
    return m_r[0];
}

void calRecord::CompleteFieldsAsFirst()
{
    bool set = false;
    for( size_t i = 1 ; i < m_size ; i++ ) {
        if( set || m_r[i] == calR_INVALID ) {
            m_r[i] = 1;
            set = true;
        }
    }
}

void calRecord::CompleteFieldsAsLast()
{
    switch( m_base )
    {
    case calBASE_Jdn:
        break;
    case calBASE_Julian:
        if( m_r[1] == calR_INVALID ) {
            m_r[1] = 12;
            m_r[2] = calR_INVALID;
        }
        if( m_r[2] == calR_INVALID ) {
            m_r[2] = calJulianLastDayInMonth( m_r[1], m_r[0] );
        }
        break;
    case calBASE_Gregorian:
        if( m_r[1] == calR_INVALID ) {
            m_r[1] = 12;
            m_r[2] = calR_INVALID;
        }
        if( m_r[2] == calR_INVALID ) {
            m_r[2] = calGregorianLastDayInMonth( m_r[1], m_r[0] );
        }
        break;
    case calBASE_French:
        if( m_r[1] == calR_INVALID ) {
            m_r[1] = 13;
            m_r[2] = calR_INVALID;
        }
        if( m_r[2] == calR_INVALID ) {
            m_r[2] = calFrenchLastDayInMonth( m_r[1], m_r[0] );
        }
        break;
    }
}

void calRecord::RemoveFieldsIfFirst()
{
    switch( m_base )
    {
    case calBASE_Jdn:
        break;
    case calBASE_Julian:
    case calBASE_Gregorian:
    case calBASE_French:
        if( m_r[2] ==  1 ) {
            m_r[2] = calR_INVALID;
            if( m_r[1] == 1 ) {
                m_r[1] = calR_INVALID;
            }
        }
        break;
    }
}

void calRecord::RemoveFieldsIfLast()
{
    switch( m_base )
    {
    case calBASE_Jdn:
        break;
    case calBASE_Julian:
        if( m_r[2] == calJulianLastDayInMonth( m_r[1], m_r[0] ) ) {
            m_r[2] = calR_INVALID;
            if( m_r[1] == 12 ) {
                m_r[1] = calR_INVALID;
            }
        }
        break;
    case calBASE_Gregorian:
        if( m_r[2] == calGregorianLastDayInMonth( m_r[1], m_r[0] ) ) {
            m_r[2] = calR_INVALID;
            if( m_r[1] == 12 ) {
                m_r[1] = calR_INVALID;
            }
        }
        break;
    case calBASE_French:
        if( m_r[2] == calFrenchLastDayInMonth( m_r[1], m_r[0] ) ) {
            m_r[2] = calR_INVALID;
            if( m_r[1] == 13 ) {
                m_r[1] = calR_INVALID;
            }
        }
        break;
    }
}

bool calRecord::ConvertToJdn( long* jdn ) const
{
    DMYDate dmy;

    switch( m_base )
    {
    case calBASE_Jdn:
        *jdn = m_r[0];
        return true;
    case calBASE_Julian:
        dmy.SetDMY( m_r[2], m_r[1], m_r[0] );
        return calJulianToJdn( jdn, dmy );
    case calBASE_Gregorian:
        dmy.SetDMY( m_r[2], m_r[1], m_r[0] );
        return calGregorianToJdn( jdn, dmy );
    case calBASE_French:
        return calFrenchToJdn( jdn, m_r[0], m_r[1], m_r[2] );
    }
    return false;
}

bool calRecord::ConvertFromJdn( long jdn )
{
    DMYDate dmy;

    switch( m_base )
    {
    case calBASE_Jdn:
        m_r[0] = jdn;
        return true;
    case calBASE_Julian:
        if( !calJulianFromJdn( jdn, &dmy ) ) break;
        m_r[0] = dmy.year;
        m_r[1] = dmy.month;
        m_r[2] = dmy.day;
        return true;
    case calBASE_Gregorian:
        if( !calGregorianFromJdn( jdn, &dmy ) ) break;
        m_r[0] = dmy.year;
        m_r[1] = dmy.month;
        m_r[2] = dmy.day;
        return true;
    case calBASE_French:
        return calFrenchFromJdn( jdn, &m_r[0], &m_r[1], &m_r[2] );
    }
    return false;
}


bool calRecord::ConvertRangeStartToJdn( long* jdn )
{
    if( m_r[m_size-1] == calR_INVALID ) {
        CompleteFieldsAsFirst();
    }
    return ConvertToJdn( jdn );
}

bool calRecord::ConvertRangeEndToJdn( long* jdn )
{
    if( m_r[m_size-1] == calR_INVALID ) {
        CompleteFieldsAsLast();
    }
    return ConvertToJdn( jdn );
}

wxString calRecord::GetStr()
{
    wxString str;

    switch( m_base )
    {
    case calBASE_Jdn:
        if( m_r[0] != calR_INVALID ) {
            str << m_r[0];
        }
        break;
    case calBASE_Julian:
    case calBASE_Gregorian:
        if( m_r[2] != calR_INVALID ) {
            str << m_r[2] << " ";
        }
        if( m_r[1] != calR_INVALID ) {
            str << calLatinMonthName[m_r[1]-1] << " ";
        }
        if( m_r[0] != calR_INVALID ) {
            str << m_r[0];
        }
        break;
    case calBASE_French:
        if( m_r[2] != calR_INVALID ) {
            str << m_r[2] << " ";
        }
        if( m_r[1] != calR_INVALID ) {
            str << calFrenchMonthName[m_r[1]-1] << " ";
        }
        if( m_r[0] != calR_INVALID ) {
            str << m_r[0];
        }
        break;
    default:
        str << _("Not available");
    }
    return str;
}

bool calRecord::ConvertToRange( long* jdn1, long* jdn2 ) const
{
    bool ok;

    if( m_r[m_size-1] == calR_INVALID ) {
        calRecord rec(*this);
        ok = rec.ConvertRangeStartToJdn( jdn1 );
        if( ok ) {
            rec = *this;
            ok = rec.ConvertRangeEndToJdn( jdn2 );
        }
    } else {
        ok = ConvertToJdn( jdn1 );
        *jdn2 = *jdn1;
    }
    return ok;
}

bool calRecord::operator==( const calRecord& rec )
{
    return
        m_base == rec.m_base &&
        m_r[0] == rec.m_r[0] &&
        m_r[1] == rec.m_r[1] &&
        m_r[2] == rec.m_r[2] &&
        m_r[3] == rec.m_r[3] &&
        m_r[4] == rec.m_r[4];
}

// End of src/cal/calRecord.cpp
