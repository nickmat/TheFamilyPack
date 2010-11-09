/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgRecTableCtrl.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     dlgRecTableCtrl class to display a wxSQLite3Table list header.
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

#ifndef DLGRECTABLECTRL_H
#define DLGRECTABLECTRL_H

#include <wx/listctrl.h>

class wxSQLite3Table;

class dlgRecTableCtrl : public wxListCtrl
{
public:
    dlgRecTableCtrl(
        wxWindow *parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxLC_ICON,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxListCtrlNameStr
    ) : wxListCtrl( parent, id, pos, size, style, validator, name ),
        m_table(NULL) {}

    void SetTable( wxSQLite3Table* table ) { m_table = table; }

private:
    wxString OnGetItemText( long item, long column ) const;

    wxSQLite3Table* m_table;
};

class dlgStrTableCtrl : public wxListCtrl
{
public:
    dlgStrTableCtrl(
        wxWindow *parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxLC_ICON,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxListCtrlNameStr
    ) : wxListCtrl( parent, id, pos, size, style, validator, name ),
        m_width(0), m_strTable(NULL) {}

    void SetTable( wxArrayString* table, size_t width ) { 
        m_strTable = table; m_width = width; 
    }

private:
    wxString OnGetItemText( long item, long column ) const;

    size_t         m_width;
    wxArrayString* m_strTable;
};

#endif // DLGRECTABLECTRL_H