/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recSelect.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Various Database Dialog functions, GUI only.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     19 November 2012
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recEvent.h>
#include <rec/recFilterEvent.h>
#include <rec/recIndividual.h>
#include <rg/rgDialogs.h>

#include "rgEdDate.h"
#include "rgEdPlace.h"
#include "rgEdEventType.h"
#include "rgEdRole.h"
#include "rgEdPerIndEvent.h"

#include "rgSelect.h"
#include "rgSelIndEvent.h"


bool rgEditDate( idt dateID )
{
    wxASSERT( dateID != 0 );
    if( recDate::IsRelative( dateID ) ) {
        return rgEditRelativeDate( dateID );
    }
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditDate* dialog = new rgDlgEditDate( NULL, dateID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateDate( const wxString& dateStr )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recDate date(0);
    date.SetDefaults();
    if( dateStr.size() ) {
        date.SetDate( dateStr );
    }
    date.Save();
    idt dateID = date.FGetID();
    if( rgEditDate( dateID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return dateID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

bool rgEditRelativeDate( idt dateID )
{
    wxASSERT( dateID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRelativeDate* dialog = new rgDlgEditRelativeDate( NULL, dateID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateRelativeDate( idt baseID, long value )
{
    wxASSERT( baseID != 0 );

    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recRelativeDate rel(0);
    rel.SetDefaults();
    rel.FSetValue( value );
    rel.FSetBaseID( baseID );
    rel.Save();

    recDate date(0);
    date.SetDefaults();
    date.FSetRelID( rel.FGetID() );
    date.Save();
    idt dateID = date.FGetID();
    if( rgEditRelativeDate( dateID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return dateID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

bool rgEditPlace( idt placeID )
{
    wxASSERT( placeID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditPlace* dialog = new rgDlgEditPlace( NULL, placeID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreatePlace( const wxString& placeStr )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recPlace place(0);
    place.Save();
    idt placeID = place.FGetID();
    recPlacePart pp(0);
    pp.FSetPlaceID( placeID );
    pp.FSetTypeID( recPlacePartType::TYPE_Address );
    pp.FSetValue( placeStr );
    pp.FSetSequence( 1 );
    pp.Save();

    if( rgEditPlace( placeID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return placeID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

bool rgEditEventType( wxWindow* wind, idt etID )
{
    wxASSERT( etID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEventType* dialog = new rgDlgEditEventType( wind, etID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateEventType( wxWindow* wind )
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEventType et(0);
    et.Save();
    idt etID = et.FGetID();
    if( rgEditEventType( wind, etID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        etID = 0;
    }
    return etID;
}

bool rgEditRole( idt roleID )
{
    wxASSERT( roleID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditRole* dialog = new rgDlgEditRole( NULL, roleID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateRole( idt etID )
{
    wxASSERT( etID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEventTypeRole role(0);
    role.FSetTypeID( etID );
    role.Save();
    idt roleID = role.FGetID();
    if( rgEditRole( roleID ) ) {
        recDb::ReleaseSavepoint( savepoint );
    } else {
        recDb::Rollback( savepoint );
        roleID = 0;
    }
    return roleID;
}

idt rgSelectDate( unsigned flag, unsigned* retbutton, unsigned filter, idt id )
{
    idt dateID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    bool cont = true;
    rgDlgSelectDate* dialog = new rgDlgSelectDate( NULL, flag );

    while( cont ) {
        recIdVec dateIDs;
        switch( filter )
        {
        case recD_FILTER_Reference:
            dateIDs = recReference::GetDateIdVec( id );
            break;
        default:
            wxASSERT( false ); // Shouldn't be here
            return 0;
        }
        wxArrayString table;
        for( size_t i = 0 ; i < dateIDs.size() ; i++ ) {
            table.push_back( recDate::GetIdStr( dateIDs[i] ) );        
            table.push_back( recDate::GetStr( dateIDs[i] ) );        
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                dateID = rgCreateDate();
                if( dateID ) {
                    if( retbutton ) *retbutton = rgSELSTYLE_Create;
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                // Create new Event Type
                wxMessageBox( "Not yet implimented", "rgSelectDate" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                dateID = 0;
                break;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            dateID = dateIDs[item];
        }
        cont = false;
    }
    dialog->Destroy();
    return dateID;
}

idt rgSelectPlace( unsigned flag, unsigned* retbutton, unsigned filter, idt id )
{
    idt placeID = 0;
    if( retbutton ) *retbutton = rgSELSTYLE_None;
    bool cont = true;
    rgDlgSelectPlace* dialog = new rgDlgSelectPlace( NULL, flag );

    while( cont ) {
        recIdVec placeIDs;
        switch( filter )
        {
        case recP_FILTER_Reference:
            placeIDs = recReference::GetPlaceIdVec( id );
            break;
        default:
            wxASSERT( false ); // Shouldn't be here
            return 0;
        }
        wxArrayString table;
        for( size_t i = 0 ; i < placeIDs.size() ; i++ ) {
            table.push_back( recPlace::GetIdStr( placeIDs[i] ) );        
            table.push_back( recPlace::GetAddressStr( placeIDs[i] ) );        
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                placeID = rgCreatePlace();
                if( placeID ) {
                    if( retbutton ) *retbutton = rgSELSTYLE_Create;
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                // Create new Event Type
                wxMessageBox( "Not yet implimented", "rgSelectPlace" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                placeID = 0;
                break;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            placeID = placeIDs[item];
        }
        cont = false;
    }
    dialog->Destroy();
    return placeID;
}

idt rgSelectEventType( wxWindow* wind, unsigned flag, unsigned* retbutton, unsigned grpfilter )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectEventType* dialog = new rgDlgSelectEventType( wind, flag );

    while( cont ) {
        recEventTypeVec types = recEventType::ReadVec( grpfilter );
        wxArrayString table;
        for( size_t i = 0 ; i < types.size() ; i++ ) {
            table.push_back( types[i].GetGroupStr() );        
            table.push_back( types[i].FGetName() );        
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                id = rgCreateEventType( wind );
                if( id ) {
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                // Create new Event Type
                wxMessageBox( "Not yet implimented", "rgSelectEventType" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            id = types[item].FGetID();
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

idt rgSelectIndEvent( wxWindow* wind, unsigned selstyle, recFilterEvent* exfilter, bool* ok, idt indID )
{
    idt eveID = 0;
    bool cont = true;
    recFilterEvent* fe = exfilter;
    if( fe == NULL ) {
        fe = new recFilterEvent;
    }
    if( ok ) *ok = false;

    rgDlgSelectIndEvent* dialog = new rgDlgSelectIndEvent( wind, selstyle, fe );
    if( dialog->ShowModal() == wxID_OK ) {
        if( ok ) *ok = true;
        if( dialog->GetCreatePressed() ) {
            eveID = rgCreateIndEvent( wind, indID );
            if( eveID == 0 && ok ) *ok = false;
        } else if( dialog->GetUnknownPressed() ) {
            eveID = 0;
        } else {
            eveID = dialog->GetID();
        }
    }
    dialog->Destroy();
    if( exfilter == NULL ) {
        delete fe;
    }
    return eveID;
}

bool rgSelectIndEventList( wxWindow* wind, recFilterEvent* evefilter )
{
    wxASSERT( evefilter != NULL );
    idt ret = rgSelectIndEvent( wind, rgSELSTYLE_SelList, evefilter );
    if( ret == 0 ) {
        return false;
    }
    return true;
}

idt rgSelectIndividual( recIdVec indIDs, unsigned flag, unsigned* retbutton )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectIndividual* dialog = new rgDlgSelectIndividual( NULL, flag );

    while( cont ) {
        wxArrayString table;
        for( size_t i = 0 ; i < indIDs.size() ; i++ ) {
            table.push_back( recIndividual::GetIdStr( indIDs[i] ) );        
            table.push_back( recIndividual::GetFullName( indIDs[i] ) );        
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                id = rgAddNewIndividual( NULL, SEX_Unstated );
                if( id ) {
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                    indIDs.push_back( id );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                wxMessageBox( "Not yet implimented", "rgSelectIndividual" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            id = indIDs[item];
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

idt rgSelectIndividual( wxWindow* wind, unsigned flag, unsigned* retbutton, unsigned sexfilter )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectIndividual* dialog = new rgDlgSelectIndividual( wind, flag );

    while( cont ) {
        recIndividualVec inds = recIndividual::ReadVec( sexfilter );
        wxArrayString table;
        for( size_t i = 0 ; i < inds.size() ; i++ ) {
            table.push_back( inds[i].GetIdStr() );        
            table.push_back( inds[i].GetFullName() );        
        }
        dialog->SetTable( table );
        if( dialog->ShowModal() == wxID_OK ) {
            if( dialog->GetCreatePressed() ) {
                if( retbutton ) *retbutton = rgSELSTYLE_Create;
                id = rgAddNewIndividual( NULL, SEX_Unstated );
                if( id ) {
                    cont = false;
                } else {
                    dialog->SetCreatePressed( false );
                }
                continue;
            }
            if( dialog->GetFilterPressed() ) {
                wxMessageBox( "Not yet implimented", "rgSelectIndividual" );
                dialog->SetFilterPressed( false );
                continue;
            }
            if( dialog->GetUnknownPressed() ) {
                wxASSERT( false ); // We shouldn't be here, Unknown has no meaning.
                if( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                continue;
            }
            size_t item = (size_t) dialog->GetSelectedRow();
            id = inds[item].FGetID();
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

idt rgSelectIndividual( wxWindow* wind, Sex sex )
{
    unsigned filter;
    switch( sex ) 
    {
    case SEX_Male:
        filter = recInd_FILTER_SexMale;
        break;
    case SEX_Female:
        filter = recInd_FILTER_SexFemale;
        break;
    default:
        filter = recInd_FILTER_SexUnknown;
    }
    return rgSelectIndividual( wind, rgSELSTYLE_None, NULL, filter );
}

// End of src/rg/rgDilogs.cpp file
