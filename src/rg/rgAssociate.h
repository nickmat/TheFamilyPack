/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Name:        src/rg/rgAssociate.h
* Project:     The Family Pack: Genealogy data storage and display program.
* Purpose:     Edit and create database Assicate database entity dialogs.
* Author:      Nick Matthews
* Website:     http://thefamilypack.org
* Created:     12th June 2019
* Copyright:   Copyright (c) 2019..2021 Nick Matthews.
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

#ifndef RGASSOCIATE_H
#define RGASSOCIATE_H

#include "fb/fbRgEditAssociate.h"
#include "rgSelect.h"

#include <rec/recAssociate.h>

//-------------------------------------------------------------------------------
//-------------------[ rgDlgEditAssociate ]-----------------------------------------
//-------------------------------------------------------------------------------

class rgDlgEditAssociate : public fbRgEditAssociate
{
public:
    rgDlgEditAssociate( wxWindow* parent, idt assID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recAssociate m_ass;
};

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectAssociate ]-----------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectAssociate : public rgSelect
{
    enum {
        COL_ID, COL_Path, COL_comment, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectAssociate(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _( "Select Associate Database" )
        ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};

#endif // RGASSOCIATE_H
