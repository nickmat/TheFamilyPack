/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgSelect.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select record from list dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     27 November 2010
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

#ifndef DLGSELECT_H
#define DLGSELECT_H

#include <rec/recDatabase.h>

#include "fbDlg.h"


class dlgSelect : public fbDlgSelect
{
public:
    /** Constructor */
    dlgSelect( wxWindow* parent, wxString* headers, long width );

    void SetTable( wxArrayString table ); 
    // Returns the 1st column of the selected row converted to an ID.
    virtual id_t GetSelectedID();
    virtual long GetSelectedRow();

protected:
    // For fbDlgSelect to enable select button.
    void OnIdle( wxIdleEvent& event );

private:
    wxArrayString  m_table;
    size_t         m_width;
    size_t         m_count;
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectPersona ]-------------------------------------------
//-------------------------------------------------------------------------------
#
class dlgSelectPersona : public dlgSelect
{
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    dlgSelectPersona( wxWindow* parent );
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectName ]-------------------------------------------
//-------------------------------------------------------------------------------
#
class dlgSelectName : public dlgSelect
{
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    dlgSelectName( wxWindow* parent ) 
        : dlgSelect( parent, sm_colHeaders, COL_MAX ) {}

//    bool CreateRefNameTable( id_t refID );
};

#endif // DLGSELECT_H
