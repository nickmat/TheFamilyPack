/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calHebrew.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Hebrew Calendar functions.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     30th March 2013
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

#ifndef CALHEBREW_H
#define CALHEBREW_H

extern bool calHebrewIsLeapYear( int year );

extern int calHebrewLastDayInMonth( int month, int year );

extern bool calHebrewToJdn( long* jdn, long year, long month, long day );

extern bool calHebrewFromJdn( long jdn, long* year, long* month, long* day );

#endif // CALHEBREW_H