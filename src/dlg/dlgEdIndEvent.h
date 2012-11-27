/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        dlgEdIndEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Individual Event dialog header.
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

#ifndef DLGEDINDEVENT_H
#define DLGEDINDEVENT_H

#include <rec/recEvent.h>
#include <rec/recDate.h>
#include <rec/recPlace.h>
#include <rec/recIndividual.h>
#include <rec/recPersona.h>

#include "fbDlg.h"

typedef std::vector< wxString >  StringVec;

#include <map>
typedef std::map< idt, recIdVec > IndPerMap;

//-----------------------------------------------------
//      dlgEditIndEvent
//-----------------------------------------------------

class dlgEditIndEvent : public fbDlgEditIndEvent
{
    enum Columns {
        COL_IndID, COL_Name, COL_Role, COL_Note, COL_MAX
    };
public:
    dlgEditIndEvent( wxWindow* parent, idt eventID );
    ~dlgEditIndEvent();

private:
    bool TransferDataToWindow();
    void ListLinkedIndividuals();
    wxString WrReferenceEvents();
    wxString WrReferenceDates();
    bool CreateDateImageFile();
    static void DrawDateImage( 
        wxDC& dc, const recDate& date, long start, double scale, const wxColour& color );
    wxString WrReferencePlaces();
    wxString WrReferencePersonas();
    wxString WrReferenceIndividuals();
    bool TransferDataFromWindow();

    void OnDate1Button( wxCommandEvent& event );
    void OnDate2Button( wxCommandEvent& event );
    void OnPlaceButton( wxCommandEvent& event );

    void OnAddButton( wxCommandEvent& event );
    void OnEditButton( wxCommandEvent& event );
    void OnDeleteButton( wxCommandEvent& event );

    recEvent  m_event;
    recDate   m_date1;
    recPlace  m_place;

    recIndEventVec     m_ies;
    recIndividualList  m_individuals;

    recEventVec m_refEvents;
    recIdVec    m_refIDs;
    recIdVec    m_personaIDs;
    IndPerMap   m_indPerMap;
    recDateVec  m_reDate1s;
    StringVec   m_dateImageFNs;

    wxString    m_dateImageFN;
};

//-----------------------------------------------------
//      dlgEditFamEvent
//-----------------------------------------------------

class dlgEditFamEvent : public fbDlgEditFamEvent
{
public:
    dlgEditFamEvent(
        wxWindow* parent, idt eventID,
        recEventType::ETYPE_Grp grp = recEventType::ETYPE_Grp_Unstated );

    idt GetEventID() const { return m_event.f_id; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void OnTypeButton( wxCommandEvent& event );
    void OnDateButton( wxCommandEvent& event );
    void OnAddrButton( wxCommandEvent& event );

    recEventType::ETYPE_Grp m_grp;
    recEvent  m_event;
};


#endif // DLGEDINDEVENT_H
