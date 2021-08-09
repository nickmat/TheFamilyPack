/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdFamily.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Family entity dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010 .. 2021, Nick Matthews.
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

#ifndef  RGEDITFAMILY_H
#define  RGEDITFAMILY_H

#include <rec/recIndividual.h>

#include "fbRgDialog.h"

//============================================================================
//-------------------------[ rgDlgEditFamily ]--------------------------------
//============================================================================

class rgDlgEditFamily : public fbRgEditFamily
{
    DECLARE_CLASS( dlgEditFamily )
    DECLARE_EVENT_TABLE()

    enum EDBUT_Type { EDBUT_Husb, EDBUT_Wife };

protected:
    enum {
        rgID_DLGEDFAM_EDIT = 1500,
        rgID_DLGEDFAM_REMOVE,
        rgID_DLGEDFAM_DELETE,
        rgID_DLGEDFAM_ADDNEW,
        rgID_DLGEDFAM_ADDEXIST,
        rgID_DLGEDFAM_ADDNEWSON,
        rgID_DLGEDFAM_ADDNEWDAUR,
        rgID_DLGEDFAM_ADDEXISTSON,
        rgID_DLGEDFAM_ADDEXISTDAUR,
        rgID_DLGEDFAM_UNLINK_EVENT,
        rgID_DLGEDFAM_DELETE_EVENT
    };
    enum Page {
        PAGE_Family, PAGE_Children, PAGE_Events
    };
    enum ChildColumns {
        CC_Number, CC_Name, CC_Dates, CC_MAX
    };
    enum EventColumns {
        EC_Number, EC_Title, EC_Date, EC_Place, EC_MAX
    };
public:
    rgDlgEditFamily( wxWindow* parent, idt famID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();
    void UpdateNames();
    void UpdateChildList( idt indID = 0 );
    void UpdateEventList( idt eveID = 0 );

    void OnPageChanged( wxBookCtrlEvent& event ) override;

    void OnHusbButton( wxCommandEvent& event ) override;
    void OnWifeButton( wxCommandEvent& event ) override;
    void EditSpouseMenu( idt indID );
    void OnEditID( wxCommandEvent& event );
    void OnRemoveID( wxCommandEvent& event );
    void OnDeleteID( wxCommandEvent& event );
    void OnAddExistID( wxCommandEvent& event );

    void ChildButtonsEnable( long row );
    void OnChildAddButton( wxCommandEvent& event ) override;
    void OnAddChild( wxCommandEvent& event );
    void OnChildSelect( wxListEvent& event ) override;
    void OnChildDeselect( wxListEvent& event ) override;
    void OnChildEditButton( wxCommandEvent& event ) override;
    void OnChildDeleteButton( wxCommandEvent& event ) override;
    void OnChildUpButton( wxCommandEvent& event ) override;
    void OnChildDownButton( wxCommandEvent& event ) override;

    void EventButtonsEnable( long row );
    void OnEventAddButton( wxCommandEvent& event ) override;
    void OnEventSelect( wxListEvent& event ) override;
    void OnEventDeselect( wxListEvent& event ) override;
    void OnEventEditButton( wxCommandEvent& event ) override;
	void OnEventDeleteButton( wxCommandEvent& event ) override;
	void OnUnlinkEvent( wxCommandEvent& event );
	void OnDeleteEvent( wxCommandEvent& event );
    void OnEventUpButton( wxCommandEvent& event ) override;
    void OnEventDownButton( wxCommandEvent& event ) override;
    void OnEventOrderBy( wxCommandEvent& event ) override;


    recFamily         m_family;
    recFamIndVec      m_fis;
    recFamilyEventVec m_fes;

    recEventOrder     m_order;
    EDBUT_Type        m_editbutton;
    long              m_currentRow;
};

#endif // RGEDITFAMILY_H
