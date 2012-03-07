/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdNamePart.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Name Part entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 November 2010
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

#ifndef DLGEDNAMEPART_H
#define DLGEDNAMEPART_H

#include <rec/recName.h>

#include "fbDlg.h"

class dlgEditNamePart : public fbDlgEditNamePart
{
public:
    dlgEditNamePart( wxWindow* parent );

    void SetNamePartID( idt npID ) { m_np.f_id = npID; }
    void SetNameID( idt nameID ) { m_np.f_name_id = nameID; }
    void SetValue( const wxString& val ) { m_np.f_val = val; }

    recNamePart* GetNamePart() { return &m_np; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recNamePart         m_np;
    recNamePartTypeVec  m_types;
};

#endif // DLGEDNAMEPART_H
