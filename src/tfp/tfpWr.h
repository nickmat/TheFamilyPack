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

class TfpFrame;

// See tfpWr.cpp
extern wxString tfpWrHead( const wxString& title, const wxString& css = wxEmptyString );
extern wxString tfpWrTail();
extern wxString tfpWrHeadTfp( const wxString& title, const wxString& css = wxEmptyString );
inline wxString tfpWrTailTfp() { return "</div>\n" + tfpWrTail(); }
extern wxString tfpWrHeadInfo( const wxString& title, const wxString& css = wxEmptyString );
inline wxString tfpWrTailInfo() { return tfpWrTail(); }
extern wxString tfpWrErrorPage( const wxString& name );
extern wxString tfpWrStartPage();
#define tfpWR_PAGE_MAX 100
extern wxString tfpWritePagedIndexMenu( idt begCnt, size_t maxsize, const wxString prefix );
extern wxString tfpGetIndSexClass( idt indID, Sex pref = Sex::unknown, const wxString& dbname = "Main" );
extern wxString tfpGetSexClass( Sex sex, Sex pref = Sex::unknown );
extern wxString tfpGetRowClass( int row );
enum class GetEpitaphPrefix { none, spaces, newline };
extern wxString tfpGetEpitaphPlus( idt indID, GetEpitaphPrefix prefix = GetEpitaphPrefix::none, const wxString& dbname = "Main" );
extern wxString tfpNormaliseSpaces( const wxString& str );
extern wxString tfpGetMediaDataFile( idt mdID, idt assID, const wxString& dbname = "Main" );

extern wxString tfpNormalisePageName( const wxString& name );
extern wxString tfpGetDisplayText( const wxString& pagename, const wxString& dbname, TfpFrame* frame = nullptr  );

// See tfpWrAdmin.cpp
extern wxString tfpWriteResearcherList( const wxString& extdb );

// See tfpWrArchive.cpp
extern wxString tfpWriteArchiveIndex( const wxString& dbname );
extern wxString tfpWriteArchive( idt arcID, const wxString& dbname );

// See tfpWrChart.cpp
extern wxString tfpCreatePedChart( idt indID, const wxString& dbname );
extern wxString tfpCreateDescChart( idt indID, const wxString& dbname );

// See tfpWrEvent.cpp
extern wxString tfpWriteEventPage( idt eveID, TfpFrame* frame );

// See tfpWrEventa.cpp
extern wxString tfpWriteEventaPage( idt erID, const wxString& dbname );

// See tfpWrEventaIndex.cpp
extern wxString tfpWriteEventaIndex();
extern wxString tfpWriteEventaPagedIndex( idt begCnt );

// See tfpWrEventIndex.cpp
extern wxString tfpWriteEventIndex();
extern wxString tfpWriteEventPagedIndex( idt begCnt );
extern wxString tfpWriteEventSelection( TfpFrame* frame );

// See tfpWrFamily.cpp
extern wxString tfpWriteFamilyPage( idt famID, const wxString& extdb, size_t iL = 0, size_t iR = 0 );
extern wxString tfpWriteFamilyPage( const wxString& str, const wxString& extdb );
extern wxString tfpWriteIndFamilyPage( idt indID, const wxString& extdb );

// See tfpWrGallery.cpp
extern wxString tfpWriteGalleryList();
extern wxString tfpWriteGalleryPage( idt galID );

// See tfpWrIndividual.cpp
extern wxString tfpWriteIndividualPage( idt indID, const wxString& extdb );

// See tfpWrMedia.cpp
extern wxString tfpWriteMediaPage( idt medID, const wxString& extdb );
extern wxString tfpWriteMediaIndex( const wxString& extdb );
extern wxString tfpWriteMediaPagedIndex( idt begCnt, const wxString& extdb );
extern wxString tfpWriteMediaDataPage( const wxString& href, const wxString& extdb );
extern wxString tfpWriteMediaDataIndex( const wxString& extdb );

// See tfpWrName.cpp
extern wxString tfpWriteSurnameIndex( recSurnameGroup sng );
extern wxString tfpWriteNameList( const wxString& sname, recSurnameGroup sng );
extern wxString tfpWriteIndividualList();

// See tfpWrNote.cpp
extern wxString tfpWriteCitation( idt citID, const wxString& dbname );
extern wxString tfpWriteDate( idt dateID, const wxString& dbname );
extern wxString tfpWritePlace( idt placeID, const wxString& dbname );
extern wxString tfpWriteName( idt nameID, const wxString& dbname );
extern wxString tfpWriteAbout();

// See tfpWrPersona.cpp
extern wxString tfpWritePersonaPage( idt perID );

// See tfpWrReference.cpp
extern wxString tfpWriteReferenceIndex( const wxString& dbname );
extern wxString tfpWriteReferencePagedIndex( idt begCnt, const wxString& dbname );
extern wxString tfpWriteReferencePage( idt refID, const wxString& dbname );

#endif // TFPWR_H
