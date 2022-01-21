/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfp/tfpWr.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen page functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7th October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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
extern wxString tfpWrHead( const wxString& title, const wxString& css = wxEmptyString );
extern wxString tfpWrTail();
extern wxString tfpWrHeadTfp( const wxString& title, const wxString& css = wxEmptyString );
inline wxString tfpWrTailTfp() { return "</div>\n" + tfpWrTail(); }
extern wxString tfpWrHeadInfo( const wxString& title, const wxString& css = wxEmptyString );
inline wxString tfpWrTailInfo() { return tfpWrTail(); }
extern wxString tfpWrErrorPage( const wxString& name );
#define tfpWR_PAGE_MAX 100
extern wxString tfpWritePagedIndexMenu( idt begCnt, size_t maxsize, const wxString prefix );
extern wxString tfpGetIndSexClass( idt indID, Sex pref = Sex::unknown );
extern wxString tfpGetSexClass( Sex sex, Sex pref = Sex::unknown );
extern wxString tfpGetRowClass( int row );
enum GET_EPITAPH_Prefix { GE_None, GE_Spaces, GE_NewLine };
extern wxString tfpGetEpitaphPlus( idt indID, GET_EPITAPH_Prefix prefix = GE_Spaces );
extern wxString tfpNormaliseSpaces( const wxString& str );
extern wxString tfpGetMediaDataFile( idt mdID, idt assID );

// See tfpWrAdmin.cpp
extern wxString tfpWriteResearcherList();

// See tfpWrArchive.cpp
extern wxString tfpWriteArchiveIndex();
extern wxString tfpWriteArchive( idt arcID );

// See tfpWrChart.cpp
extern wxString tfpCreatePedChart( idt indID );
extern wxString tfpCreateDescChart( idt indID );

// See tfpWrEvent.cpp
extern wxString tfpWriteEventPage( idt eveID, rgCompareEvent* ce );

// See tfpWrEventa.cpp
extern wxString tfpWriteEventaPage( idt erID );

// See tfpWrEventaIndex.cpp
extern wxString tfpWriteEventaIndex();
extern wxString tfpWriteEventaPagedIndex( idt begCnt );

// See tfpWrEventIndex.cpp
extern wxString tfpWriteEventIndex();
extern wxString tfpWriteEventPagedIndex( idt begCnt );
extern wxString tfpWriteEventSelection( recSelSetEvent& filter );

// See tfpWrFamily.cpp
extern wxString tfpWriteFamilyPage( idt famID, size_t iL = 0, size_t iR = 0 );
extern wxString tfpWriteFamilyPage( const wxString& str );
extern wxString tfpWriteIndFamilyPage( idt indID );

// See tfpWrGallery.cpp
extern wxString tfpWriteGalleryList();
extern wxString tfpWriteGalleryPage( idt galID );

// See tfpWrIndividual.cpp
extern wxString tfpWriteIndividualPage( idt indID );

// See tfpWrMedia.cpp
extern wxString tfpWriteMediaPage( idt medID );
extern wxString tfpWriteMediaIndex();
extern wxString tfpWriteMediaPagedIndex( idt begCnt );
extern wxString tfpWriteMediaDataPage( const wxString& href );
extern wxString tfpWriteMediaDataIndex();

// See tfpWrName.cpp
extern wxString tfpWriteSurnameIndex( recSurnameGroup sng );
extern wxString tfpWriteNameList( const wxString& sname, recSurnameGroup sng );
extern wxString tfpWriteIndividualList();

// See tfpWrNote.cpp
extern wxString tfpWriteCitation( idt citID );
extern wxString tfpWriteDate( idt dateID );
extern wxString tfpWritePlace( idt placeID );
extern wxString tfpWriteName( idt nameID );
extern wxString tfpWriteAbout();

// See tfpWrPersona.cpp
extern wxString tfpWritePersonaPage( idt perID );

// See tfpWrReference.cpp
extern wxString tfpWriteReferenceIndex();
extern wxString tfpWriteReferencePagedIndex( idt begCnt );
extern wxString tfpWriteReferencePage( idt refID );

#endif // TFPWR_H
