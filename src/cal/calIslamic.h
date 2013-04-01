/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calIslamic.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Islamic Tabular (arithmetic) Calendar functions.
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

#ifndef CALISLAMIC_H
#define CALISLAMIC_H

extern bool calIslamicIsLeapYear( long year );

extern int calIslamicLastDayInMonth( long month, long year );

extern bool calIslamicToJdn( long* jdn, long year, long month, long day );

extern bool calIslamicFromJdn( long jdn, long* year, long* month, long* day );

#endif // CALISLAMIC_H