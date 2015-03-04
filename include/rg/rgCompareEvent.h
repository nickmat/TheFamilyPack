/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgCompareEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Class used to display linked Individual Event data.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21 November 2012
 * Copyright:   Copyright (c) 2010-2015, Nick Matthews.
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

#ifndef RGCOMPAREEVENT_H
#define RGCOMPAREEVENT_H

#include <rec/recEvent.h>
#include <rec/recEventa.h>
#include <rec/recIndividual.h>
#include <rec/recPlace.h>

#include <map>

typedef std::map< idt, recIdVec > IndPerMap;

class rgCompareEvent
{
public:
    rgCompareEvent() {};
    ~rgCompareEvent();

    void Reset( idt eveID );

    wxString GetRefDatesTable();
    wxString GetRefPlacesTable();
    wxString GetRefEventsTable();

private:
    void UnloadFiles();
    bool CreateDateImageFile();
    static void DrawDateImage(
        wxDC& dc, const recDate& date, long start, double scale, const wxColour& color );

    recEvent  m_event;
    recDate   m_date1;
    recDate   m_date2;
    recPlace  m_place;

    recIndEventVec    m_ies;
    recIndividualVec  m_individuals;
    recEventumVec     m_refEvents;

    recIdVec    m_refIDs;
    recIdVec    m_personaIDs;
    IndPerMap   m_indPerMap;
    recDateVec  m_reDate1s;
    recPlaceVec m_rePlaces;

    wxString    m_dateImageFN;
    StringVec   m_dateImageFNs;
};

#endif // RGCOMPAREEVENT_H
