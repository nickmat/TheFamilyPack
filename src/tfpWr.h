/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWr.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen page functions.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

#ifndef TFPWR_H
#define TFPWR_H

#include <rec/recDatabase.h>

// See tfpWr.cpp
extern wxString tfpGetDisplayText( const wxString& name );

// See tfpWrAdmin.cpp
extern wxString tfpWriteResearcherList();

// See tfpWrChart.cpp
extern wxString tfpCreatePedChart( idt indID );
extern wxString tfpCreateDescChart( idt indID );

// See tfpWrEvent.cpp
extern wxString tfpWriteEventIndex();
extern wxString tfpWriteEventPage( idt refID );

// See tfpWrFamily.cpp
extern wxString tfpWriteFamilyPage( idt famID, size_t iL = 0, size_t iR = 0 );
extern wxString tfpWriteFamilyPage( const wxString& str );
extern wxString tfpWriteIndFamilyPage( idt indID );

// See tfpWrIndividual.cpp
extern wxString tfpWriteIndividualPage( idt indID );

// See tfpWrName.cpp
extern wxString tfpWriteIndividualIndex();
extern wxString tfpWritePersonIndex();
extern wxString tfpWriteIndividualList( const wxString& surname );

// See tfpWrNote.cpp
extern wxString tfpWriteDate( idt dateID );
extern wxString tfpWriteAttribute( idt attrID );
extern wxString tfpWritePlace( idt placeID );
extern wxString tfpWriteRelationship( idt rsID );

// See tfpWrReference.cpp
extern wxString tfpWriteReferenceIndex();
extern wxString tfpWriteReferencePage( idt refID );

#endif // TFPWR_H
