/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCrName.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Create database Name entity dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     12th December 2012
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

#ifndef RGCRNAME_H
#define RGCRNAME_H

#include <rec/recName.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgCreateName ]--------------------------------
//============================================================================

class rgDlgCreateName : public fbRgCreateName
{
public:
    rgDlgCreateName( wxWindow* parent ) 
        : m_name(0), fbRgCreateName( parent ) {}

    idt GetNameID() const { return m_name.FGetID(); }

    void SetIndividualID( idt indID ) { m_name.FSetIndID( indID ); }
    void SetPersonaID( idt perID ) { m_name.FSetPerID( perID ); }
    void SetNextSequence() { m_name.SetNextSequence(); }
    void SetGiven( const wxString& given ) { m_given = given; }
    void SetSurname( const wxString& sur ) { m_surname = sur; }
    void SetTypeID( idt typeID ) { m_name.FSetTypeID( typeID ); }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    wxString  m_given;
    wxString  m_surname;

    recName          m_name;
    recNameStyleVec  m_types;
};

#endif // RGCRNAME_H
