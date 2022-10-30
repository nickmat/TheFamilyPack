/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Persona entity dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     9 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

#ifndef RGEDPERSONA_H
#define RGEDPERSONA_H

#include <rec/recPersona.h>

#include "fb/fbRgEditPersona.h"


//============================================================================
//-------------------------[ rgDlgEditPersona ]-------------------------------
//============================================================================

class rgDlgEditPersona : public fbRgEditPersona
{
    enum Page {
        PAGE_Details, PAGE_Note, PAGE_Names, PAGE_Eventa, PAGE_Individual
    };
    enum NameColumns {
        NC_Number, NC_Type, NC_Name, NC_MAX
    };
    enum EventColumns {
        EV_COL_Number, EV_COL_Role, EV_COL_Title, EV_COL_Date, EV_COL_Place, EV_COL_MAX
    };
    enum IndColumns {
        IC_Number, IC_Conf, IC_Name, IC_Link_Note, IC_MAX
    };
public:
    rgDlgEditPersona( wxWindow* parent, idt perID );

    void SetPersonaID( idt perID ) { m_persona.f_id = perID; }

    recPersona* GetPersona() { return &m_persona; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void UpdateNameList( idt nameID = 0 );
    void UpdateEventaList( idt eveID = 0 );
    void UpdateIndividualList( idt indID = 0 );

    void OnPageChanged( wxBookCtrlEvent& event ) override;

    void NameButtonsEnable( long row );
    void OnNameDeselect( wxListEvent& event ) override;
    void OnNameSelect( wxListEvent& event ) override;
    void OnNameAddButton( wxCommandEvent& event ) override;
    void OnNameEditButton( wxCommandEvent& event ) override;
    void OnNameDeleteButton( wxCommandEvent& event ) override;
    void OnNameUpButton( wxCommandEvent& event ) override;
    void OnNameDownButton( wxCommandEvent& event ) override;

    void EventaButtonsEnable( long row );
    void OnEventaDeselect( wxListEvent& event ) override;
    void OnEventaSelect( wxListEvent& event ) override;
    void OnEventaAddButton( wxCommandEvent& event ) override;
    void OnEventaEditButton( wxCommandEvent& event ) override;
    void OnEventaDeleteButton( wxCommandEvent& event ) override;
    void OnEventaUpButton( wxCommandEvent& event ) override;
    void OnEventaDownButton( wxCommandEvent& event ) override;
    void OnEventaOrderBy( wxCommandEvent& event ) override;

    void IndButtonsEnable( long row );
    void OnIndDeselect( wxListEvent& event ) override;
    void OnIndSelect( wxListEvent& event ) override;
    void OnIndAddButton( wxCommandEvent& event ) override;
    void OnIndEditButton( wxCommandEvent& event ) override;
    void OnIndDeleteButton( wxCommandEvent& event ) override;
    void OnIndUpButton( wxCommandEvent& event ) override;
    void OnIndDownButton( wxCommandEvent& event ) override;

    recPersona          m_persona;
    recNameVec          m_names;
    recEventaPersonaVec m_evpers;
    recEventOrder       m_order;
    recIdVec            m_indLinks;
};

//============================================================================
//---------------------------[ rgDlgLinkIndPersona ]--------------------------
//============================================================================

class rgDlgLinkIndPersona : public fbRgLinkIndPersona
{
public:
    rgDlgLinkIndPersona( wxWindow* parent, idt ipaID )
        : m_ipa( ipaID ), fbRgLinkIndPersona( parent ) {}

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    recIndividualPersona m_ipa;
};


#endif // RGEDPERSONA_H
