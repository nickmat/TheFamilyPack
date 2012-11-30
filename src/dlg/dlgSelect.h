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

class dlgEditReference;


class dlgSelect : public fbDlgSelect
{
public:
    enum StyleFlags {
        SELSTYLE_None          = 0x0000,
        SELSTYLE_CreateButton  = 0x0001,
        SELSTYLE_UnknownButton = 0x0002,
    };

    /** Constructor */
    dlgSelect( wxWindow* parent, wxString* headers, long width,
        const wxString& title = wxEmptyString,
        unsigned style = SELSTYLE_None );

    void SetTable( wxArrayString table );
    void SetCreateButton( bool on = true );
    void SetUnknownButton( bool on = true );
    // Returns the 1st column of the selected row converted to an ID.
    virtual idt GetSelectedID();
    virtual long GetSelectedRow();
    size_t GetCount() const { return m_count; }
    bool GetCreatePressed() const { return m_create; }
    bool GetUnknownPressed() const { return m_unknown; }

protected:
    // For fbDlgSelect to enable select button.
    void OnIdle( wxIdleEvent& event );
    void OnCreateButton( wxCommandEvent& event );
    void SetCreatePressed( bool on = true ) { m_create = on; }
    void OnUnknownButton( wxCommandEvent& event );
    void SetUnknownPressed( bool on = true ) { m_create = on; }

private:
    wxArrayString  m_table;
    size_t         m_width;
    size_t         m_count;
    bool           m_create;
    bool           m_unknown;
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectPersona ]----------------------------------------
//-------------------------------------------------------------------------------

class dlgSelectPersona : public dlgSelect
{
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    dlgSelectPersona( wxWindow* parent, const wxString& title = wxEmptyString );
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectCreatePersona ]----------------------------------
//-------------------------------------------------------------------------------

class dlgSelectCreatePersona : public dlgSelectPersona
{
    DECLARE_EVENT_TABLE()
public:
    dlgSelectCreatePersona( 
        wxWindow* parent, idt refID, const wxString& title = wxEmptyString )
        : m_referenceID(refID), m_personaID(0), 
        dlgSelectPersona( parent, title )
    {}

    idt GetPersonaID() const { return m_personaID; }
protected:
    enum {
        ID_SELCREATPER_MALE = 1200,
        ID_SELCREATPER_FEMALE,
        ID_SELCREATPER_UNKNOWN
    };
    void OnCreateButton( wxCommandEvent& event );
    void OnCreatePersona( wxCommandEvent& event );
private:
    idt  m_referenceID;
    idt  m_personaID;
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectIndividual ]-------------------------------------
//-------------------------------------------------------------------------------

class dlgSelectIndividual : public dlgSelect
{
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    dlgSelectIndividual( 
        wxWindow* parent, 
        const wxString& title = _("Select Individual"), 
        unsigned style = SELSTYLE_None 
    ) : dlgSelect( parent, sm_colHeaders, COL_MAX, title, style ) {}
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectPlace ]------------------------------------------
//-------------------------------------------------------------------------------

class dlgSelectPlace : public dlgSelect
{
    enum {
        COL_ID, COL_Place, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    dlgSelectPlace( 
        wxWindow* parent = NULL, 
        const wxString& title = _("Select Place"),
        unsigned style = SELSTYLE_None
    ) : dlgSelect( parent, sm_colHeaders, COL_MAX, title, style ) {}
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectPlaceEx ]----------------------------------------
//-------------------------------------------------------------------------------

class dlgSelectPlaceEx : public dlgSelectPlace
{
public:
    dlgSelectPlaceEx( 
        wxWindow* parent, 
        dlgEditReference* dlgEdRef,
        const wxString& title, 
        unsigned style
    ) : m_dlgEdRef( dlgEdRef ), dlgSelectPlace( parent, title, style ) {}
   
    idt GetPlaceID() const { return m_placeID; }

protected:
    void OnCreateButton( wxCommandEvent& event );

private:
    idt               m_placeID;
    dlgEditReference* m_dlgEdRef;
};

//-------------------------------------------------------------------------------
//-------------------[ dlgSelectName ]-------------------------------------------
//-------------------------------------------------------------------------------

class dlgSelectName : public dlgSelect
{
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    dlgSelectName( wxWindow* parent )
        : dlgSelect( parent, sm_colHeaders, COL_MAX ) {}
};

#endif // DLGSELECT_H
