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

#include <rec/recFilterEvent.h>
#include <rec/recIndividual.h>

class rgDlgEditReference;

// See src/rg/rgCrName.cpp
enum {
    rgCRNAME_Default   = 0x000, // Use default settings to decode name1 string.
    rgCRNAME_Sur_Given = 0x001  // If given, name1 is surname, name2 is given name.
};
extern idt rgCreateName( wxWindow* wind, idt perID,
    unsigned flags = rgCRNAME_Default, 
    const wxString& name1 = wxEmptyString,
    const wxString& name2 = wxEmptyString,
    recNameStyle::Style type = recNameStyle::NS_Default );

// See src/rg/rgEdContact.cpp
extern bool rgEditContact( wxWindow* wind, idt conID );
extern idt rgCreateContact( wxWindow* wind, idt clID );

// See src/rg/rgEdDate.cpp
extern bool rgEditDate( wxWindow* wind, idt dateID );
extern idt rgCreateDate( wxWindow* wind, const wxString& dateStr = wxEmptyString );

// See src/rg/rgEdEvent.cpp
extern bool rgEditEvent( wxWindow* wind, idt eveID );
extern idt rgCreateIndEvent( wxWindow* wind, idt ind1ID, idt ind2ID = 0, idt famID = 0 );

// See src/rg/rgEdEventType.cpp
extern bool rgEditEventType( wxWindow* wind, idt etID );
extern idt rgCreateEventType( wxWindow* wind );

// See src/rg/rgEdEvidEvent.cpp
extern bool rgEditEvidEvent( rgDlgEditReference* wind, idt eveID );
extern idt rgCreateEvidEvent( rgDlgEditReference* wind );
extern idt rgCreateEvidPerEvent( rgDlgEditReference* wind, const wxString& role );

// See src/rg/rgEdFamily.cpp
extern bool rgEditFamily( wxWindow* wind, idt famID );

// See src/rg/rgEdIndividual.cpp
extern bool rgEditIndividual( wxWindow* wind, idt indID );

// See src/rg/rgEdName.cpp
extern bool rgEditName( wxWindow* wind, idt nameID );

// See src/rg/rgEdNamePart.cpp
extern bool rgEditNamePart( wxWindow* wind, idt npID );
extern idt rgCreateNamePart( wxWindow* wind, idt nameID, const wxString& npStr = wxEmptyString );

// See src/rg/rgEdPerIndEvent.cpp
enum rgSHOWROLE {
    rgSHOWROLE_All,
    rgSHOWROLE_PrimeAll,
    rgSHOWROLE_PrimeMale,
    rgSHOWROLE_PrimeFemale
};
extern bool rgEditIndEventRole( wxWindow* wind, idt ieID, rgSHOWROLE filter = rgSHOWROLE_All );
extern bool rgCreateIndEventRole( wxWindow* wind, idt indID, idt eveID, idt roleID );
extern bool rgEditPerEventRole( wxWindow* wind, idt epID, rgSHOWROLE filter = rgSHOWROLE_All );
extern bool rgCreatePerEventRole( wxWindow* wind, idt perID, idt eveID, idt roleID );

// See src/rg/rgEdPersona.cpp
extern bool rgEditPersona( rgDlgEditReference* wind, idt perID );
//extern idt rgCreatePersona( wxWindow* parent );

// See src/rg/rgEdPlace.cpp
extern bool rgEditPlace( wxWindow* wind, idt placeID );
extern idt rgCreatePlace( wxWindow* wind, const wxString& placeStr = wxEmptyString );

// See src/rg/rgEdReference.cpp
extern bool rgEditReference( wxWindow* wind, idt refID );
extern idt rgCreateReference( wxWindow* wind );

// See src/rg/rgEdRelationship.cpp
extern bool rgEditPerRelationship( rgDlgEditReference* wind, idt relID );
extern idt rgCreatePerRelationship( 
    rgDlgEditReference* wind, 
    int per1ID, const wxString& descrip = wxEmptyString, idt per2ID = 0 );
inline idt rgCreatePerRelationship( 
    rgDlgEditReference* wind, 
    const wxString& descrip = wxEmptyString ) 
    { return rgCreatePerRelationship( wind, 0, descrip ); }

// See src/rg/rgEdRelDate.cpp
extern bool rgEditRelativeDate( wxWindow* wind, idt dateID );
extern idt rgCreateRelativeDate( wxWindow* wind, idt baseID, long value = 0 );

// See src/rg/rgEdResearcher.cpp
extern bool rgEditResearcher( wxWindow* wind, idt conID );
extern idt rgCreateResearcher( wxWindow* wind );

// See src/rg/rgEdRole.cpp
extern bool rgEditRole( wxWindow* wind, idt roleID );
extern idt rgCreateRole( wxWindow* wind, idt etID );

// See src/rg/rgEdSystem.cpp
extern bool rgEditSystemSettings( wxWindow* wind );

// See src/rg/rgEdUser.cpp
extern bool rgEditUserSettings( wxWindow* wind );

// See src/rg/rgIndividual.cpp
extern idt rgAddNewIndividual( 
    wxWindow* wind, Sex sex, const wxString& surname = wxEmptyString, idt famID = 0 );
extern bool rgAddNewParent( wxWindow* wind, idt indID, Sex sex );
extern bool rgAddExistParent( wxWindow* wind, idt indID, Sex sex );
extern bool rgAddNewSpouse( wxWindow* wind, idt indID, Sex sex );
extern bool rgAddExistSpouse( wxWindow* wind, idt indID, Sex sex );
extern idt rgAddNewChild( wxWindow* wind, idt famID, Sex sex );
extern idt rgAddExistChild( wxWindow* wind, idt famID, Sex sex );
extern bool rgDeleteIndividual( wxWindow* wind, idt indID );

enum {
    rgSELSTYLE_None       = 0x0000,
    rgSELSTYLE_Create     = 0x0001,   // Show Create button
    rgSELSTYLE_Filter     = 0x0002,   // Show Filter button
    rgSELSTYLE_Unknown    = 0x0004,   // Show Unknown button (for Unknown value)
    rgSELSTYLE_SelList    = 0x0100    // Selects the full list
};

// See src/rg/rgSelect.cpp
extern idt rgSelectDate( 
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned filter = 0, idt = 0 );
extern idt rgSelectPlace( 
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned filter = 0, idt = 0 );
extern idt rgSelectEventType( 
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned grpfilter = recET_FILTER_GrpAll );
extern idt rgSelectIndividual(
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned sexfilter = recInd_FILTER_SexAll );
extern idt rgSelectIndividual( wxWindow* wind, Sex sex );
extern idt rgSelectIndividual(
    wxWindow* wind,
    recIdVec indIDs,
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL );

// See src/rg/rgSelIndEvent.cpp
extern bool rgSelectIndEventList( wxWindow* wind, recFilterEvent* exfilter );
extern idt rgSelectIndEvent( 
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_None, 
    recFilterEvent* filter = NULL,
    bool* ok = NULL,
    idt indID = 0 );

#endif // RGDIALOGS_H
