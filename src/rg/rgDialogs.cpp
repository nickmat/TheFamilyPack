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
#include <rec/recIndividual.h>

#include "rgEdEventType.h"
#include "rgEdRole.h"
#include "rgEdPerIndEvent.h"

#include "rgSelect.h"


bool rgEditEventType( idt etID )
{
    wxASSERT( etID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );
    bool ret = false;

    rgDlgEditEventType* dialog = new rgDlgEditEventType( NULL, etID );

    if( dialog->ShowModal() == wxID_OK ) {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgCreateEventType()
{
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    recEventType et(0);
    et.Save();
    idt etID = et.FGetID();
    if( rgEditEventType( etID ) ) {
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

bool rgEditIndEventRole( idt ieID, rgSHOWROLE filter )
{
    wxASSERT( ieID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgIndEvent* dialog = new rgDlgIndEvent( NULL, ieID, filter );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

bool rgCreateIndEventRole( idt indID, idt eveID, idt roleID )
{
    wxASSERT( eveID != 0 ); // TODO: Select an Event from list
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    if( indID == 0 ) {
        indID = rgSelectIndividual( rgSELSTYLE_None );
        if( indID == 0 ) {
            recDb::Rollback( savepoint );
            return false;
        }
    }
    recIndividualEvent ie(0);
    ie.FSetIndID( indID );
    ie.FSetEventID( eveID );
    ie.FSetRoleID( roleID );
    ie.FSetIndSeq( recIndividual::GetMaxEventSeqNumber( indID ) );
    ie.Save();
    if( roleID == 0 ) {
        if( ! rgEditIndEventRole( ie.FGetID() ) ) {
            recDb::Rollback( savepoint );
            return false;
        }
    }
    recDb::ReleaseSavepoint( savepoint );
    return true;
}

bool rgEditPerEventRole( idt epID, rgSHOWROLE filter )
{
    wxASSERT( epID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgPerEvent* dialog = new rgDlgPerEvent( NULL, epID, filter );

    recDb::Savepoint( savepoint );
    if( dialog->ShowModal() == wxID_OK )
    {
        recDb::ReleaseSavepoint( savepoint );
        ret = true;
    } else {
        recDb::Rollback( savepoint );
    }
    dialog->Destroy();
    return ret;
}

idt rgSelectEventType( unsigned flag, unsigned* retbutton, unsigned grpfilter )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectEventType* dialog = new rgDlgSelectEventType( NULL, flag );

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
                id = rgCreateEventType();
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

idt rgSelectIndividual( unsigned flag, unsigned* retbutton, unsigned sexfilter )
{
    idt id = 0;
    bool cont = true;
    rgDlgSelectIndividual* dialog = new rgDlgSelectIndividual( NULL, flag );

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
                id = rgCreateEventType();
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
            id = inds[item].FGetID();
        }
        if( retbutton ) *retbutton = rgSELSTYLE_None;
        cont = false;
    }
    dialog->Destroy();
    return id;
}

// End of src/rg/rgDilogs.cpp file
