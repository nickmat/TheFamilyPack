/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calFrench.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     French Revolutionary Calendar functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     8th December 2013
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


#include "calFrench.h"
#include "calRecord.h"
#include "calAstro.h"
#include "calMath.h"

namespace {

#define BASEDATE_French 2375840L  // 22 Sep 1792 (G)

const double ParisLongitude = 2.3375;

double MidnightInParis( long jdn )
{
    double jdnp1 = jdn + 1;
    double universalfromlocal = jdnp1 - ParisLongitude / 360;
    double localfromapparent = jdnp1 - calEquationOfTime( universalfromlocal );
    return localfromapparent - ParisLongitude / 360;
}

bool fnyoobMinFunc( long jdn, long constant )
{
    return constant <= calSolarLongtitude( MidnightInParis( jdn ) );
}

long FrenchNewYearOnOrBefore( long jdn )
{
    double approx = 
        calEstimatePriorSolarLongitude( calAutumn, MidnightInParis( jdn ) );
    return calMinSearch( (long) approx - 1, fnyoobMinFunc, calAutumn );
}

} // namespace

long calFrenchLastDayInMonth( long month, long year )
{
    if( month == 13 ) {
        calRecord rec( CALENDAR_SCH_FrenchRevolution, year+1, 1, 1 );
        long jdn;
        rec.ConvertToJdn( &jdn );
        rec.ConvertFromJdn( jdn-1 );
        return rec.GetR( 2 );
    } else {
        return 30;
    }
}

// CC3 p242
bool calFrenchToJdn( long* jdn, long year, long month, long day )
{
    long approx = BASEDATE_French + 180 + (long) ( calMeanTropicalYear * ( year-1 ) );

    long newyear = FrenchNewYearOnOrBefore( approx );

    *jdn = newyear - 1 + 30 * (month-1) + day;

    return true;
}

// CC3 p242
bool calFrenchFromJdn( long jdn, long* year, long* month, long* day )
{
    long newyear = FrenchNewYearOnOrBefore( jdn );

    double y = ( (double) (newyear - BASEDATE_French) ) / calMeanTropicalYear;
    *year = floor( y + 1.5 );  

    *month = ( jdn - newyear ) / 30 + 1;

    *day = ( jdn - newyear ) % 30 + 1;

    return true;
}

// End of src/cal/calFrench.cpp
