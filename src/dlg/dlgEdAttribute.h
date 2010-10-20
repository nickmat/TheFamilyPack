/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdAttribute.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Attribute entity dialog header.
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

#ifndef DLGEDATTRIBUTE_H
#define DLGEDATTRIBUTE_H

#include <rec/recPersona.h>

#include "fbDlg.h"

class dlgEditAttribute : public fbDlgEditAttribute
{
public:
	dlgEditAttribute( wxWindow* parent, id_t attID = 0 );

	void SetText( const wxString& text ) { m_text = text; }
    void SetPersona( id_t perID ) { m_persona = perID; }

	wxString GetText() const { return m_text; }
	recAttribute* GetAttribute() { return &m_attr; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    id_t         m_persona;
	recAttribute m_attr;
    wxString     m_text;
    recAttributeTypeVec  m_typeList;
};

#endif // DLGEDATTRIBUTE_H
