/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        calGregorian.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Gregorian Calendar functions.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     28 September 2010
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

#ifndef CALGREGORIAN_H
#define CALGREGORIAN_H

class DMYDate;

// Gregorian (New Style)
extern bool calGregorianIsLeapYear( int year );
extern int calGregorianLastDayInMonth( int month, int year );
//extern bool calGregorianToJdn( long& jdn, int day, int month, int year );
extern bool calGregorianToJdn( long& jdn, const DMYDate& dmy );
//extern bool calGregorianFromJdn( long jdn, int& day, int& month, int& year );
extern bool calGregorianFromJdn( long jdn, DMYDate& dmy );

#endif // CALGREGORIAN_H