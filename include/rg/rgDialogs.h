/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rg/rgDialogs.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Various Database Dialog function prototypes, GUI only.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
 * Copyright:   Copyright (c) 2012 .. 2021, Nick Matthews.
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

template<class D> bool rgEdit( wxWindow* parent, idt id, const wxString& title )
{
    if( !id ) return false;
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    D dialog( parent, id );
    if( !title.empty() ) {
        dialog.SetTitle( title );
    }
    if( dialog.ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        return true;
    }
    recDb::Rollback( savepoint );
    return false;
}

template<class R, class D> idt rgCreate( wxWindow* wind, const wxString& title )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    R rec( 0 );
    rec.Save();
    idt recID = rec.FGetID();

    if( rgEdit<D>( wind, recID, title ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return recID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

class rgDlgEditReference;
class rgRefData;

enum {  // Used for popup menus, we put them here to ensure unique values.
    rgID_START = 2000,

    rgID_PERINDEVENT_CREATE_ROLE, // src/rg/rgEdPerIndEvent.cpp
    rgID_PERINDEVENT_EDIT_ROLE,

    rgID_LAST
};

enum {
    rgSELSTYLE_None       = 0x0000,
    rgSELSTYLE_Create     = 0x0001,   // Show Create button
    rgSELSTYLE_Filter     = 0x0002,   // Show Filter button
    rgSELSTYLE_Unknown    = 0x0004,   // Show Unknown button (for Unknown value)
    rgSELSTYLE_SelList    = 0x0100    // Selects the full list
};

// See src/rg/rgAssociate.cpp
extern bool rgEditAssociate( wxWindow* wind, idt assID );
extern idt rgCreateAssociate( wxWindow* wind );
extern idt rgSelectAssociate(
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create,
    unsigned* retbutton = NULL,
    const wxString& title = ""
);

// See src/rg/rgEdCitation.cpp
extern bool rgEditCitation( wxWindow* wind, idt citID, const wxString& title = "" );
extern idt rgCreateCitation( wxWindow* wind, idt refID );
extern bool rgEditArchive( wxWindow* wind, idt citID, const wxString& title = "" );
extern idt rgCreateArchive( wxWindow* wind );
extern idt rgSelectArchive(
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create,
    unsigned* retbutton = NULL,
    const wxString& title = ""
);
extern bool rgEditCitationPart( wxWindow* wind, idt cipID, const wxString& title = "" );
extern idt rgCreateCitationPart( wxWindow* wind, idt citID );
extern bool rgEditCitationPartType( wxWindow* wind, idt ciptID, const wxString& title = "" );
extern idt rgCreateCitationPartType( wxWindow* wind );

// See src/rg/rgCrName.cpp
enum {
    rgCRNAME_Default    = 0x0000, // Use default settings to decode name1 string.
    rgCRNAME_Sur_Given  = 0x0001, // If given, name1 is surname, name2 is given name.
    rgCRNAME_EditExtend = 0x0100  // If set, allow Edit Persona/Individual check box.
};
extern idt rgCreateName( wxWindow* wind, idt indID, idt perID,
    unsigned flags, const wxString& name1, const wxString& name2, idt typeID );
inline idt rgCreatePersonaName( wxWindow* wind, idt perID,
    unsigned flags = rgCRNAME_Default,
    const wxString& name1 = wxEmptyString,
    const wxString& name2 = wxEmptyString,
    idt typeID = (idt) recNameStyle::NS_Default )
    { return rgCreateName( wind, 0, perID, flags, name1, name2, typeID ); }
inline idt rgCreateIndividualName( wxWindow* wind, idt indID,
    unsigned flags = rgCRNAME_Default,
    const wxString& name1 = wxEmptyString,
    const wxString& name2 = wxEmptyString,
    idt typeID = (idt) recNameStyle::NS_Default )
    { return rgCreateName( wind, indID, 0, flags, name1, name2, typeID ); }

// See src/rg/rgEdContact.cpp
extern bool rgEditContact( wxWindow* wind, idt conID );
extern idt rgCreateContact( wxWindow* wind, idt clID );

// See src/rg/rgEdDate.cpp
extern bool rgEditDate( wxWindow* wind, idt dateID );
extern idt rgCreateDate( wxWindow* wind, const wxString& dateStr = wxEmptyString );

// See src/rg/rgEdEvent.cpp
extern bool rgEditEvent( wxWindow* wind, idt eveID );
extern idt rgCreateIndEvent(
    wxWindow* wind, idt ind1ID, idt ind2ID = 0, idt famID = 0,
    unsigned grpfilter = recET_GRP_FILTER_All );
extern idt rgCreateDefaultIndEvent(
    wxWindow* wind, idt ind1ID, idt ind2ID, recET_GRP grp );
extern idt rgCreatePersonalEvent( wxWindow* wind, idt ind1ID, recEventType::EType etype );
extern idt rgCreateEventFromRecord( wxWindow* wind, idt erID );

// See src/rg/rgEdEventEventa.cpp
extern bool rgEditEventEventa( wxWindow* wind, idt eerID );
extern idt rgCreateIndEventEventa( wxWindow* wind, idt eID, idt erID );
extern idt rgFindOrCreateIndEvent(
    wxWindow* wind,
    idt erID,
    double conf,
    idt id,  // Individual or Family depending on Event Group
    idt roleID );

// See src/rg/rgEdEventType.cpp
extern bool rgEditEventType( wxWindow* wind, idt etID );
extern idt rgCreateEventType( wxWindow* wind );

// See src/rg/rgEdEventa.cpp
extern bool rgEditEventa( wxWindow* wind, idt eveID );
extern idt rgCreateEventa( wxWindow* wind, idt refID );
extern idt rgCreatePersonalEventa( wxWindow* wind, idt refID, const wxString& role );

// See src/rg/rgEdFamily.cpp
extern bool rgEditFamily( wxWindow* wind, idt famID );

// See src/rg/rgEdGallery.cpp
extern bool rgEditGallery( wxWindow* parent, idt galID );

// See src/rg/rgEdIndividual.cpp
extern bool rgEditIndividual( wxWindow* wind, idt indID );

// See src/rg/rgEdMedia.cpp
extern bool rgEditMedia( wxWindow* wind, idt medID );
extern bool rgEditMediaData( wxWindow* wind, idt mdID, const wxString& dbname );

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
extern bool rgEditPersona( wxWindow* wind, idt perID );
extern idt rgCreateNamedPersona( wxWindow* parent, idt refID );

// See src/rg/rgEdPlace.cpp
extern bool rgEditPlace( wxWindow* wind, idt placeID );
extern idt rgCreatePlace( wxWindow* wind, const wxString& placeStr = wxEmptyString );

// See src/rg/rgEdReference.cpp
extern bool rgEditReference( wxWindow* wind, idt refID );
extern idt rgCreateReference( wxWindow* wind );
extern idt rgCreateReferenceFromTemplate( wxWindow* wind );
extern bool rgSelectDateFromReference(
    wxWindow* wind, idt* dateID, idt refID, const wxString& title, unsigned style );
extern bool rgSelectPlaceFromReference(
    wxWindow* wind, idt* placeID, idt refID, const wxString& title, unsigned style );

// See src/rg/rgEdRelDate.cpp
extern bool rgEditRelativeDate( wxWindow* wind, idt dateID );
extern idt rgCreateRelativeDate( wxWindow* wind, idt baseID, long value = 0 );

// See src/rg/rgEdResearcher.cpp
extern bool rgEditResearcher( wxWindow* wind, idt conID );
extern idt rgCreateResearcher( wxWindow* wind );
extern idt rgSelectResearcher(
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create,
    unsigned* retbutton = NULL,
    const wxString& title = ""
);

// See src/rg/rgEdRole.cpp
extern bool rgEditRole( wxWindow* wind, idt roleID );
extern idt rgCreateRole( wxWindow* wind, idt etID );

// See src/rg/rgEdSystem.cpp
extern bool rgEditSystemSettings( wxWindow* wind );

// See src/rg/rgEdUser.cpp
extern bool rgEditUserSettings( wxWindow* wind );

// See src/rg/rgEdIndividual.cpp
extern idt rgAddNewIndividual(
    wxWindow* wind, Sex sex, int privacy = 0, const wxString& surname = wxEmptyString, idt famID = 0 );
extern bool rgAddNewParent( wxWindow* wind, idt indID, Sex sex );
extern bool rgAddExistParent( wxWindow* wind, idt indID, Sex sex );
extern bool rgAddNewSpouse( wxWindow* wind, idt indID, Sex sex, idt famID );
extern bool rgAddExistSpouse( wxWindow* wind, idt indID, Sex sex );
extern idt rgAddNewChild( wxWindow* wind, idt famID, Sex sex );
extern idt rgAddExistChild( wxWindow* wind, idt famID, Sex sex );
extern bool rgDeleteIndividual( wxWindow* wind, idt indID );

// See src/rg/RefTemplate.cpp
extern bool rgEnterTemplateData(
    wxWindow* parent, const wxString& reftemplate, rgRefData& data );

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
    unsigned grpfilter = recET_GRP_FILTER_All );

extern idt rgSelectIndividual(
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_Create, unsigned* retbutton = NULL,
    unsigned sexfilter = recInd_FILTER_SexAll );
extern idt rgSelectIndividual( wxWindow* wind, Sex sex );
extern idt rgSelectIndividual(
    wxWindow* wind,
    recIdVec indIDs,
    unsigned style = rgSELSTYLE_Create, unsigned* retbutton = NULL );

enum rgSELPER {
    rgSELPER_Default = 0x00,
    rgSELPER_CreateUnnamed = 0x01
};
extern idt rgSelectPersona(
    wxWindow* wind,
    idt refID,
    unsigned style = rgSELSTYLE_Create,
    rgSELPER flag = rgSELPER_Default,
    unsigned* retbutton = NULL );

extern idt rgSelectEquivalentEventa( wxWindow* wind, idt eventID );

// See src/rg/rgSelIndEvent.cpp
extern bool rgSelectEventList( wxWindow* wind, recSelSetEvent* exfilter );
extern idt rgSelectEvent(
    wxWindow* wind,
    unsigned flag = rgSELSTYLE_None,
    recSelSetEvent* filter = NULL,
    unsigned* button = NULL );

// See scr/rg/rgSetupDatabase.cpp
extern bool rgSetupDatabase( wxWindow* wind, const wxString& daname );

// See scr/rg/rgSetupReference.cpp
extern idt rgGetRefSetupData( wxWindow* parent, idt assID );

// See src/rg/rgViewMedia.cpp
extern void rgViewMedia( wxWindow* wind, idt medID );
extern void rgViewMedia( wxWindow* wind, idt mdID, idt assID );
extern void rgViewMedia( wxWindow* wind, idt mdID, const wxString& dbname );

#endif // RGDIALOGS_H
