/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdFamily.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Family entity dialog header.
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

#ifndef  DLGEDITFAMILY_H
#define  DLGEDITFAMILY_H

#include <rec/recIndividual.h>

#include "fbDlg.h"

class dlgEditFamily : public fbDlgEditFamily
{
    DECLARE_CLASS( dlgEditFamily )
    DECLARE_EVENT_TABLE()

    enum EDBUT_Type { EDBUT_Husb, EDBUT_Wife };

protected:
    enum {
        tfpID_DLGEDFAM_EDIT = 1500,
        tfpID_DLGEDFAM_REMOVE,
        tfpID_DLGEDFAM_DELETE,
        tfpID_DLGEDFAM_ADDNEW,
        tfpID_DLGEDFAM_ADDEXIST,
        tfpID_DLGEDFAM_ADDNEWSON,
        tfpID_DLGEDFAM_ADDNEWDAUR,
        tfpID_DLGEDFAM_ADDEXISTSON,
        tfpID_DLGEDFAM_ADDEXISTDAUR,
        tfpID_DLGEDFAM_NEW_EVENT,
        tfpID_DLGEDFAM_EXIST_EVENT
    };
    enum EventColumns {
        EC_Number, EC_Title, EC_Date, EC_Place, EC_MAX
    };
public:
    dlgEditFamily( wxWindow* parent );

    void SetFamilyID( idt famID ) { m_family.f_id = famID; }
    void SetFamily( const recFamily& family ) { m_family = family; }
    void SetChildID( idt childID ) { m_child = childID; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnHusbButton( wxCommandEvent& event );
    void OnWifeButton( wxCommandEvent& event );
    void EditSpouseMenu( idt indID );
    void OnEditID( wxCommandEvent& event );
    void OnRemoveID( wxCommandEvent& event );
    void OnDeleteID( wxCommandEvent& event );
    void OnAddExistID( wxCommandEvent& event );

    void OnChildAddButton( wxCommandEvent& event );
    void OnAddChild( wxCommandEvent& event );

    void OnChildEditButton( wxCommandEvent& event );
    void OnChildDeleteButton( wxCommandEvent& event );
    void OnChildUpButton( wxCommandEvent& event );
    void OnChildDownButton( wxCommandEvent& event );

    void OnEventAddButton( wxCommandEvent& event );
    void OnNewEvent( wxCommandEvent& event );
	void OnExistingEvent( wxCommandEvent& event );
	void OnEventEditButton( wxCommandEvent& event );
	void OnEventDeleteButton( wxCommandEvent& event );
	void OnEventUpButton( wxCommandEvent& event );
	void OnEventDownButton( wxCommandEvent& event );


    idt            m_child;
    EDBUT_Type     m_editbutton;

    recFamily         m_family;
    recFamIndVec      m_childlinks;
    recFamilyEventVec m_fes;

};

#endif // DLGEDITFAMILY_H
