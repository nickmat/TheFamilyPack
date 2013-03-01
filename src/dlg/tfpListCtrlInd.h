/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpListCtrlInd.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     List control to select Individual header.
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

#ifndef TFPLISTCTRLIND_H
#define TFPLISTCTRLIND_H
#if 0
#include <wx/listctrl.h>

class wxSQLite3Table;

class tfpListCtrlIndividuals : public wxListCtrl
{
public:
    tfpListCtrlIndividuals(
        wxWindow *parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxLC_ICON,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxListCtrlNameStr
    ) : wxListCtrl( parent, id, pos, size, style, validator, name ) {}

    void SetTable( wxSQLite3Table* table ) { mp_table = table; }

private:
    virtual wxString OnGetItemText( long item, long column ) const;

    wxSQLite3Table* mp_table;
};
#endif
#endif // TFPLISTCTRLIND_H