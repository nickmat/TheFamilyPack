/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calAstro.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     General astronomy functions header.
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

#ifndef CALASTRO_H
#define CALASTRO_H

extern const double calMeanTropicalYear;

extern const double calSpring; // 0 degrees
extern const double calSummer; // 90 degrees
extern const double calAutumn; // 180 degrees
extern const double calWinter; // 270 degrees

extern const double calJ2000;  // 1 Jan 2000 (G) plus 12 hours

extern double calEquationOfTime( double moment );

extern double calSolarLongtitude( double moment );

extern double calEstimatePriorSolarLongitude( double season, double moment );

#endif // CALASTRO_H