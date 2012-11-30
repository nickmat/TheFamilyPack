/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rg/rgDialogs.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Various Database Dialog function prototypes, GUI only.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
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

#ifndef RGDIALOGS_H
#define RGDIALOGS_H

#include <rec/recEvent.h>
#include <rec/recIndividual.h>

extern bool rgEditDate( idt dateID );
extern idt rgCreateDate( const wxString& dateStr = wxEmptyString );
extern bool rgEditRelativeDate( idt dateID );
extern idt rgCreateRelativeDate( idt baseID, long value = 0 );
extern bool rgEditEventType( idt etID );
extern idt rgCreateEventType();
extern bool rgEditRole( idt roleID );
extern idt rgCreateRole( idt etID );

enum rgSHOWROLE {
    rgSHOWROLE_All,
    rgSHOWROLE_PrimeAll,
    rgSHOWROLE_PrimeMale,
    rgSHOWROLE_PrimeFemale
};
extern bool rgEditIndEventRole( idt ieID, rgSHOWROLE filter = rgSHOWROLE_All );
extern bool rgCreateIndEventRole( idt indID, idt eveID, idt roleID );
extern bool rgEditPerEventRole( idt epID, rgSHOWROLE filter = rgSHOWROLE_All );

enum {
    rgSELSTYLE_None       = 0x0000,
    rgSELSTYLE_Create     = 0x0001,   // Show Create button
    rgSELSTYLE_Filter     = 0x0002,   // Show Filter button
    rgSELSTYLE_Unknown    = 0x0004,   // Show Unknown button (for Unknown value)
};
extern idt rgSelectDate( 
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned filter = 0, idt = 0 );
extern idt rgSelectEventType( 
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned grpfilter = recET_FILTER_GrpAll );
extern idt rgSelectIndividual( 
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned sexfilter = recInd_FILTER_SexAll );

#endif // RGDIALOGS_H