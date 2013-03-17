/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgSelIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Select Event dialog header.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     5th December 2012
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

#ifndef RGSELINDEVENT_H
#define RGSELINDEVENT_H

#include <rec/recFilterEvent.h>

#include "fbRgDialog.h"

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectIndEvent ]-------------------------------------
//-------------------------------------------------------------------------------

class rgDlgSelectIndEvent : public fbRgSelectIndEvent
{
    enum {
        COL_ID, COL_Title, COL_DatePt, /*COL_Type, COL_Grp,*/ COL_MAX
    };
public:
    rgDlgSelectIndEvent( wxWindow* parent, unsigned selstyle, recFilterEvent* fe );

    bool GetCreatePressed() const { return m_create; }
    bool GetUnknownPressed() const { return false; }
    idt GetID() const;

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnIdle( wxIdleEvent& event );
    void OnGroupCheckToggled( wxCommandEvent& event );
    void OnGroupCheckSelect( wxCommandEvent& event );
    void OnButtonGroupSelectAll( wxCommandEvent& event ) { SetGroupAll( true ); }
    void OnButtonGroupClearAll( wxCommandEvent& event ) { SetGroupAll( false ); }
    void OnTypeCheckToggled( wxCommandEvent& event );
    void OnTypeCheckSelect( wxCommandEvent& event );
    void OnButtonTypeSelectAll( wxCommandEvent& event ) { SetTypeAll( true ); }
    void OnButtonTypeClearAll( wxCommandEvent& event ) { SetTypeAll( false ); }
    void OnBegDateText( wxCommandEvent& event );
    void OnEndDateText( wxCommandEvent& event );
    void OnListEventItemDeselected( wxListEvent& event );
    void OnListEventItemSelected( wxListEvent& event );
    void OnCreateButton( wxCommandEvent& event );

    void SetGroupAll( bool check );
    void CreateTypeList();
    void SetTypeAll( bool check );
    void Refresh();

    bool m_create;
    bool m_selList;

    recFilterEvent* m_fe;
    IntVec m_groups;
    long m_begDatePt;
    long m_endDatePt;
};

#endif // RGSELINDEVENT_H
