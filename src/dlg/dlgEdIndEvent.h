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

#include "fbDlg.h"

class dlgEditIndEvent : public fbDlgEditIndEvent
{
public:
	dlgEditIndEvent( wxWindow* parent );

	void SetEvent( recEvent* pEvent ) { m_pEvent = pEvent; }

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

	void OnDateButton( wxCommandEvent& event );
	void OnAddrButton( wxCommandEvent& event );

	recEvent* m_pEvent;
	recDate   m_date1;
	recPlace  m_place;
};


#endif // DLGEDINDEVENT_H
