/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdPlace.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Place entity dialog header.
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

#ifndef DLGEDPLACE_H
#define DLGEDPLACE_H

#include <rec/recPlace.h>

#include "fbDlg.h"

class dlgEditPlace : public fbDlgEditPlace
{
public:
    dlgEditPlace( wxWindow* parent, id_t id = 0 );

    void SetText( const wxString& text ) { m_text = text; }

    wxString GetText() const { return m_text; }
    recPlace* GetPlace() { return &m_place; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recPlace  m_place;
    wxString  m_text;
};

#endif // DLGEDPLACE_H
