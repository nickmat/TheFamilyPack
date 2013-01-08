/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calMath.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     General mathmatical functions.
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

#include <cmath>

#include "calMath.h"

double const calPi = 3.141592653589793;


#define calMINSEARCH_MAX 370

// CC3 p20
long calMinSearch( long start, calLongSearchFunc func )
{
    for( long i = 0, d = start ; i < calMINSEARCH_MAX ; i++, d++ ) {
        if( func( d ) ) {
            return d;
        }
    }
    wxASSERT( false ); // Should have calulated a better start.
    return 0;
}

int calSignum( double n )
{
    if( n > 0 ) return 1;
    if( n < 0 ) return -1;
    return 0;
}

double calMod( double x, double y )
{
    return x - y * floor( x / y ); 
} 


// End of src/cal/calMath.cpp
