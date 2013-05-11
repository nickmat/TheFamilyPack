/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdEventEventRec.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit an EventEventRecord record dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7th May 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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
#include <rec/recReference.h>

#include "rg/rgDialogs.h"
#include "rgEdEventEventRec.h"

bool rgEditEventEventRecord( wxWindow* wind, idt eerID )
{
    wxASSERT( eerID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    bool ret = false;
    rgDlgEditEventEventRec* dialog = new rgDlgEditEventEventRec( wind, eerID );

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

idt rgCreateIndEventEventRecord( wxWindow* wind, idt eID, idt erID )
{
    wxASSERT( eID != 0 && erID != 0 );
    const wxString savepoint = recDb::GetSavepointStr();
    recDb::Savepoint( savepoint );

    idt eerID = recEventEventRecord::Create( eID, erID );

    if( rgEditEventEventRecord( wind, eerID ) ) {
        recDb::ReleaseSavepoint( savepoint );
        return eerID;
    }
    recDb::Rollback( savepoint );
    return 0;
}

//============================================================================
//-------------------------[ rgDlgEditEventEventRec ]-------------------------
//============================================================================

bool rgDlgEditEventEventRec::TransferDataToWindow()
{
    wxASSERT( m_eer.FGetID() != 0 );

    idt eID = m_eer.FGetEventID();
    wxString eStr = recEvent::GetIdStr( eID ) + ": " + recEvent::GetTitle( eID );
    m_staticEvent->SetLabel( eStr );

    idt erID = m_eer.FGetEventRecID();
    wxString erStr = recEventRecord::GetIdStr( erID ) 
        + ": " + recEventRecord::GetTitle( erID );
    m_staticEventRec->SetLabel( erStr );

    idt rID = recEventRecord::FindReferenceID( erID );
    wxString rStr = recReference::GetIdStr( rID ) 
        + ": " + recReference::GetTitle( rID );
    m_staticRef->SetLabel( rStr );

    wxString confStr;
    confStr << m_eer.FGetConf();
    m_textCtrlConf->SetValue( confStr );
    m_textCtrlNote->SetValue( m_eer.FGetNote() );

    m_staticEvEvRecID->SetLabel( m_eer.GetIdStr() );
    return true;
}

bool rgDlgEditEventEventRec::TransferDataFromWindow()
{
    double conf;
    m_textCtrlConf->GetValue().ToDouble( &conf );
    m_eer.FSetConf( conf );
    m_eer.FSetNote( m_textCtrlNote->GetValue() );

    m_eer.Save();
    return true;
}

// End of src/rg/rgEdEventEventRec.cpp file
