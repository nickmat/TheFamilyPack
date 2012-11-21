/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSelect.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Base rgSelect dialog class and other declarations, GUI only.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     19 November 2012
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

#ifndef RGSELECT_H
#define RGSELECT_H

#include <rec/recDatabase.h>

#include "fbRgDialog.h"

class rgSelect : public fbRgSelect
{
public:
    enum StyleFlags {
        SELSTYLE_None          = 0x0000,
        SELSTYLE_CreateButton  = 0x0001,
        SELSTYLE_FilterButton  = 0x0002,
        SELSTYLE_UnknownButton = 0x0004
    };

    /** Constructor */
    rgSelect( wxWindow* parent, wxString* headers, long width,
        const wxString& title = wxEmptyString,
        unsigned style = SELSTYLE_None );

    void SetTable( wxArrayString table );
    void SetCreateButton( bool on = true );
    void SetCreatePressed( bool on = true ) { m_create = on; }
    void SetFilterButton( bool on = true );
    void SetFilterPressed( bool on = true ) { m_filter = on; }
    void SetUnknownButton( bool on = true );
    void SetUnknownPressed( bool on = true ) { m_unknown = on; }
    // Returns the 1st column of the selected row converted to an ID.
    virtual idt GetSelectedID();
    virtual long GetSelectedRow();
    size_t GetCount() const { return m_count; }
    bool GetCreatePressed() const { return m_create; }
    bool GetFilterPressed() const { return m_filter; }
    bool GetUnknownPressed() const { return m_unknown; }

protected:
    void OnIdle( wxIdleEvent& event );
    void OnCreateButton( wxCommandEvent& event );
    void OnFilterButton( wxCommandEvent& event );
    void OnUnknownButton( wxCommandEvent& event );

private:
    wxArrayString  m_table;
    size_t         m_width;
    size_t         m_count;
    bool           m_create;
    bool           m_filter;
    bool           m_unknown;
};


//-------------------------------------------------------------------------------
//-------------------[ dlgSelectEventType ]--------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectEventType : public rgSelect
{
    enum {
        COL_Group, COL_Type, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectEventType( 
        wxWindow* parent = NULL, 
        const wxString& title = _("Select Event Type"),
        unsigned style = SELSTYLE_CreateButton
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, title, style ) {}
};

#endif // RGSELECT_H
