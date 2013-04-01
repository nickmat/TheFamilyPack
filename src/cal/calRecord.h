/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calRecord.h
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

#ifndef CALRECORD_H
#define CALRECORD_H

#include "calendar.h"

class calToken;

// These are the current base calendars
enum calBASE {
    calBASE_NULL,
    calBASE_Jdn,
    calBASE_Julian,
    calBASE_Gregorian,
    calBASE_French,
    calBASE_Islamic,
    calBASE_Hebrew,
    calBASE_MAX
};

class calRecord 
{
    long    m_r[calR_MAX];
    size_t  m_size;
    calBASE m_base;

public:
    calRecord( CalendarScheme sch );
    calRecord( CalendarScheme sch, long r0, long r1 = calR_INVALID, long r2 = calR_INVALID, long r3 = calR_INVALID, long r4 = calR_INVALID );
    calRecord( CalendarScheme sch, size_t size, const calToken* tokens );
    calRecord( const calRecord& record );

    void SetR( size_t i, long v ) { m_r[i] = v; }
    void SetR( long r0, long r1 = calR_INVALID, long r2 = calR_INVALID, long r3 = calR_INVALID, long r4 = calR_INVALID );

    long GetR( size_t i ) const { return m_r[i]; }
    // returns r0
    long GetR( long* r0 = NULL, long* r1 = NULL, long* r2 = NULL, long* r3 = NULL, long* r4 = NULL );
    wxString GetStr();

    void CompleteFieldsAsFirst();
    void CompleteFieldsAsLast();
    void RemoveFieldsIfFirst();
    void RemoveFieldsIfLast();

    bool ConvertToJdn( long* jdn ) const;
    bool ConvertFromJdn( long jdn );

    // Incomplete dates are handled as ranges
    bool ConvertToRange( long* jdn1, long* jdn2 ) const;
    bool ConvertRangeStartToJdn( long* jdn );
    bool ConvertRangeEndToJdn( long* jdn );

    bool operator==( const calRecord& rep );

private:
    void Copy( const calRecord& rep );
    void Clear();
};

#endif // CALRECORD_H