/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calIslamic.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Islamic Calendar functions.
 * Author:      Nick Matthews
 * Created:     29th March 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include "wx/tokenzr.h"

#include "calendar.h"
#include "calCommon.h"
#include "calIslamic.h"


// Islamic Tabular Calendar

#define BASEDATE_Islamic    1948440L

/*! Returns true if the year is a leap year in the Islamic Calendar.
 */
bool calIslamicIsLeapYear( long year )
{
    return PMod( 14 + 11 * year, 30 ) < 11;
}

/*! Returns the last day of the month for the given month and year
 *  in the Islamic Calendar.
 */
int calIslamicLastDayInMonth( long month, long year )
{
    wxASSERT( month >= 1 && month <= 12 );
    if( month == 12 ) {
        return calIslamicIsLeapYear( year ) ? 30 : 29;
    } else {
        return (month % 2) == 0 ? 29 : 30;
    }
}

/*! Sets jdn to the Julian Day Number for the given day, month and year
 *  in the Islamic Calendar. Always returns true.
 */
bool calIslamicToJdn( long* jdn, long year, long month, long day )
{
    *jdn =
        BASEDATE_Islamic - 1 
        + ( year - 1 ) * 354
        + FDiv( year * 11 + 3, 30 ) 
        + 29 * ( month - 1 )
        + FDiv( month, 2 ) + day;

    return true;
}

/*! Splits the given Julian Day Number date into the day, month and year
 *  for the Julian Calendar.
 */
bool calIslamicFromJdn( long jdn, long* year, long* month, long* day )
{
    *year = FDiv( 30 * ( jdn - BASEDATE_Islamic ) + 10646, 10631 );

    long temp;
    calIslamicToJdn( &temp, *year, 1, 1 );
    *month = FDiv( 11 * ( jdn - temp ) + 330, 325 );

    calIslamicToJdn( &temp, *year, *month, 1 );
    *day = 1 + jdn - temp;

    return true;
}

// End of src/cal/calIslamic.cpp
