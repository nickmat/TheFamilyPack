/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Persona entity dialog header.
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

#ifndef DLGEDPERSONA_H
#define DLGEDPERSONA_H

#include <rec/recPersona.h>

#include "fbDlg.h"
#include "dlgEdReference.h"


class dlgEditPersona : public fbDlgEditPersona
{
    enum Columns {
        COL_Type, COL_Value, COL_MAX
    };
public:
    dlgEditPersona( wxWindow* parent );

    void SetPersonaID( idt perID ) { m_persona.f_id = perID; }

    recPersona* GetPersona() { return &m_persona; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnIndLinkButton( wxCommandEvent& event );
    void OnIndCreateButton( wxCommandEvent& event );

    void OnNameAddButton( wxCommandEvent& event );
    void OnNameEditButton( wxCommandEvent& event );
    void OnNameDeleteButton( wxCommandEvent& event );
    void OnNameUpButton( wxCommandEvent& event );
    void OnNameDownButton( wxCommandEvent& event );

    void OnAttrAddButton( wxCommandEvent& event );
    void OnAttrEditButton( wxCommandEvent& event );
    void OnAttrDeleteButton( wxCommandEvent& event );
    void OnAttrUpButton( wxCommandEvent& event );
    void OnAttrDownButton( wxCommandEvent& event );

    wxString GetIndLinksString() const;

    recPersona        m_persona;
    recIdVec          m_indLinks;
    recNameVec        m_names;
    recAttributeVec   m_attributes;

    wxString          m_nameStr;
};

#endif // DLGEDPERSONA_H
