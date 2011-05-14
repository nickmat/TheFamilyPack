/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgSelIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select Individual record from list dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

#ifndef DLGSELINDIVIDUAL_H
#define DLGSELINDIVIDUAL_H

#include <rec/recDatabase.h>

#include "fbDlg.h"

class dlgSelectIndividual : public fbDlgSelectIndividual
{
public:
    /** Constructor */
    dlgSelectIndividual( wxWindow* parent );

    bool CreateTable( Sex sex = SEX_Unstated );
    idt GetSelectedID();

protected:
    // Handlers for fbDlgSelectIndividual events.
    void OnIdle( wxIdleEvent& event );
    void OnIndividualSelected( wxListEvent& event );


    wxSQLite3Table m_table;
    long           m_count;
};

#endif // DLGSELINDIVIDUAL_H
