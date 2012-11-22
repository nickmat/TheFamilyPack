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

#include "rgEdEventType.h"
#include "rgEdRole.h"
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

// End of src/rg/rgDilogs.cpp file
