/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCommon.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Common defines etc. used by recgui library.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th January 2013
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

#ifndef RGCOMMON_H
#define RGCOMMON_H

// Using these macros makes creating popup menus tidier

#define rgCONNECT_MI( OPTN, FUNC ) Connect(       \
    (OPTN)->GetId(), wxEVT_COMMAND_MENU_SELECTED, \
    wxCommandEventHandler( FUNC ), NULL, this )

#define rgDISCONNECT_MI( OPTN, FUNC ) Connect(    \
    (OPTN)->GetId(), wxEVT_COMMAND_MENU_SELECTED, \
    wxCommandEventHandler( FUNC ), NULL, this )


#endif // RGCOMMON_H
