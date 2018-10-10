/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgViewMedia.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     View Media (Image) dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10 October 2018
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

#ifndef SRC_RG_RGVIEWMEDIA_H
#define SRC_RG_RGVIEWMEDIA_H

#include <rec/recMedia.h>

#include "fbRgDialog.h"

class rgViewMediaForm : public fbRgViewMedia
{
public:
    rgViewMediaForm( wxWindow* parent, idt medID );

private:
    recMedia     m_media;
};

#endif // SRC_RG_RGVIEWMEDIA_H
