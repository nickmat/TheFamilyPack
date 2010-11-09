/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgRecTableCtrl.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     dlgRecTableCtrl class to display a wxSQLite3Table list.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     7 November 2010
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/wxsqlite3.h>

#include "dlgRecTableCtrl.h"


wxString dlgRecTableCtrl::OnGetItemText( long item, long column ) const 
{
    m_table->SetRow( item );
    return m_table->GetAsString( column );
}

wxString dlgStrTableCtrl::OnGetItemText( long item, long column ) const 
{
    return m_strTable->Item( m_width * item + column );
}

// End of dlgRecTableCtrl.cpp file.