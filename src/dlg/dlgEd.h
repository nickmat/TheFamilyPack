/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpEdit.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Functions to edit the database header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
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

#ifndef TFPEDIT_H
#define TFPEDIT_H

#include <rec/recDatabase.h>

class recFamily;

extern idt tfpAddNewIndividual( idt famID, Sex sex, const wxString& surname = wxEmptyString );
extern idt tfpAddNewChild( idt famID, Sex sex );
extern bool tfpAddNewParent( idt indID, Sex sex );
extern bool tfpEditIndividual( idt indID );

extern bool tfpEditFamily( idt famID );
extern bool tfpEditReference( idt refID  );
extern bool tfpAddExistSpouse( idt indID, Sex sex );
extern bool tfpAddExistChild( idt famID, Sex sex );
extern idt tfpAddMarriageEvent( const recFamily& family );
extern idt tfpGetExistingMarriageEvent( idt famID );

extern idt tfpPickIndividual( Sex sex = SEX_Unstated );

#define TFP_SELECT_STYLE_CREATE   0x0001
#define TFP_SELECT_STYLE_UNKNOWN  0x0002

extern bool tfpSelectPersona( idt* perID, unsigned style, idt refID );

#endif // TFPEDIT_H

