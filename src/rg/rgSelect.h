/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSelect.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Base rgSelect dialog class and other declarations, GUI only.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19 November 2012
 * Copyright:   Copyright (c) 2012-2015, Nick Matthews.
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

#include "fb/fbRgSelect.h"
#include "rg/rgDialogs.h"

class rgSelect : public fbRgSelect
{
public:
    /** Constructor */
    rgSelect( wxWindow* parent, wxString* headers, long width,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = wxEmptyString );

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
//-------------------[ rgDlgSelectDate ]-----------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectDate : public rgSelect
{
    enum {
        COL_ID, COL_Date, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectDate(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _("Select Date")
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectPlace ]----------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectPlace : public rgSelect
{
    enum {
        COL_ID, COL_Place, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectPlace(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _("Select Place")
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
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
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _("Select Event Type")
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectIndividual ]-----------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectIndividual : public rgSelect
{
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectIndividual(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _("Select Individual")
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectPersona ]--------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectPersona : public rgSelect
{
    DECLARE_EVENT_TABLE()
    enum {
        COL_ID, COL_Name, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectPersona(
        wxWindow* parent, unsigned style = rgSELSTYLE_None,
        const wxString& title = _("Select Persona") )
        : m_sex(SEX_Unstated),
        rgSelect( parent, sm_colHeaders, COL_MAX, style, title )
    {}

    Sex GetSex() const { return m_sex; }

private:
    enum {
        rgID_SELCREATPER_MALE = 1200,
        rgID_SELCREATPER_FEMALE,
        rgID_SELCREATPER_UNKNOWN
    };
    void OnCreateButton( wxCommandEvent& event );
    void OnCreatePersona( wxCommandEvent& event );

    Sex m_sex;
};

//-------------------------------------------------------------------------------
//------------------------[ rgDlgSelectEventa ]----------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectEventa : public rgSelect
{
    enum {
        COL_ID, COL_Title, COL_MAX
    };
    static wxString sm_colHeaders[COL_MAX];
public:
    rgDlgSelectEventa(
        wxWindow* parent = NULL,
        unsigned style = rgSELSTYLE_None,
        const wxString& title = _("Select Eventa")
    ) : rgSelect( parent, sm_colHeaders, COL_MAX, style, title ) {}
};

#endif // RGSELECT_H
