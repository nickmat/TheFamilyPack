/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdContact.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Contact dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th January 2013
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

#ifndef RGEDCONTACT_H
#define RGEDCONTACT_H

#include <rec/recContact.h>

#include "fb/fbRgEditContact.h"

class rgDlgEditContact : public fbRgEditContact
{
public:
    rgDlgEditContact( wxWindow* parent, idt contactID ) 
        : m_contact(contactID), fbRgEditContact( parent ) {}

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recContact         m_contact;
    recContactTypeVec  m_types;
};

#endif // RGEDCONTACT_H
