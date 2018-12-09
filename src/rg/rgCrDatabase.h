/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCrDatabase.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create database dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9th December 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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

#ifndef SRC_RG_RGCRDATABASE_H
#define SRC_RG_RGCRDATABASE_H


#include "fb/fbRgCreateDatabase.h"

//============================================================================
//-----------------------[ rgDlgCreateDatabase ]------------------------------
//============================================================================

class rgDlgCreateDatabase : public fbRgCreateDatabase
{
public:
    rgDlgCreateDatabase( wxWindow* wnd );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();
};


#endif // SRC_RG_RGCRDATABASE_H
