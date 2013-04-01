/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calMath.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     General mathmatical functions header.
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

#ifndef CALMATH_H
#define CALMATH_H

// We use our own value of pi for consistancy.
extern const double calPi;

typedef bool (*calLongSearchFunc)( long value, long constant );

extern long calMinSearch( long start, calLongSearchFunc func, long constant );

extern int calSignum( double n );

extern double calMod( double x, double y );


// Inline functions

double inline calDegToRad( double deg ) { return deg * calPi / 180; }

double inline calRadToDeg( double rad ) { return rad * 180 / calPi; }

#endif // CALMATH_H