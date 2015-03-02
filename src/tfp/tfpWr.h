/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWr.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen page functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7th October 2010
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
class rgCompareEvent;
class recSelSetEvent;

// See tfpWr.cpp
extern wxString tfpWrHeadTfp( const wxString& title, const wxString& css = wxEmptyString );
extern wxString tfpWrTailTfp();
#define tfpWR_PAGE_MAX 100
extern wxString tfpWritePagedIndexMenu( idt begCnt, size_t maxsize, const wxString prefix );
extern wxString GetSexClass( idt indID, Sex pref = SEX_Unknown );
extern wxString tfpGetSexClass( Sex sex, Sex pref = SEX_Unknown );
extern wxString wxGetRowClass( int row );
enum GET_EPITAPH_Prefix { GE_None, GE_Spaces, GE_NewLine };
extern wxString tfpGetEpitaphPlus( idt indID, GET_EPITAPH_Prefix prefix = GE_Spaces );
extern wxString tfpNormaliseSpaces( const wxString& str );

// See tfpWrAdmin.cpp
extern wxString tfpWriteResearcherList();

// See tfpWrChart.cpp
extern wxString tfpCreatePedChart( idt indID );
extern wxString tfpCreateDescChart( idt indID );

// See tfpWrEvent.cpp
extern wxString tfpWriteEventPage( idt eveID, rgCompareEvent* ce );

// See tfpWrEventIndex.cpp
extern wxString tfpWriteEventIndex();
extern wxString tfpWriteEventPagedIndex( idt begCnt );
extern wxString tfpWriteEventSelection( recSelSetEvent& filter );

// See tfpWrEventum.cpp
extern wxString tfpWriteEventumPage( idt erID );

// See tfpWrEventumIndex.cpp
extern wxString tfpWriteEventumIndex();
extern wxString tfpWriteEventumPagedIndex( idt begCnt );

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
extern wxString tfpWritePlace( idt placeID );
extern wxString tfpWriteName( idt nameID );
extern wxString tfpWriteRelationship( idt rsID );

// See tfpWrPersona.cpp
extern wxString tfpWritePersonaPage( idt perID );

// See tfpWrReference.cpp
extern wxString tfpWriteReferenceIndex();
extern wxString tfpWriteReferencePagedIndex( idt begCnt );
extern wxString tfpWriteReferencePage( idt refID );

#endif // TFPWR_H
