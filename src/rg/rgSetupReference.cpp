/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSetupReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Setup Creation of database Reference entity.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     23rd August 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#include "rgSetupReference.h"

#include <rg/rgDialogs.h>

#include <rec/recMedia.h>

//============================================================================
//-------------------------[ rgDlgSetupReference ]-----------------------------
//============================================================================


rgDlgSetupReference::rgDlgSetupReference( wxWindow* parent, idt refID )
    : m_reference( refID ), fbRgSetupReferenceDialog( parent )
{
    m_listMedia->InsertColumn( MED_COL_Number, _( "Number" ) );
    m_listMedia->InsertColumn( MED_COL_Title, _( "Title" ) );
}

bool rgDlgSetupReference::TransferDataToWindow()
{
    return false;
}

bool rgDlgSetupReference::TransferDataFromWindow()
{
    return false;
}

void rgDlgSetupReference::UpdateMedias( idt medID )
{
}

void rgDlgSetupReference::OnMediaDeselect( wxListEvent& event )
{
}

void rgDlgSetupReference::OnMediaSelect( wxListEvent& event )
{
}

void rgDlgSetupReference::OnMediaAddButton( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnMediaEditButton( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnMediaDeleteButton( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnMediaView( wxCommandEvent& event )
{
}

void rgDlgSetupReference::OnTemplateBrowse( wxCommandEvent& event )
{
}


// End of src/rg/rgSetupReference.cpp file
