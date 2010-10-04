/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDate.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Date records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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

#ifndef RECDATE_H
#define RECDATE_H

#include "recDatabase.h"
#include "cal/calendar.h"

class recDate : public recDb {
    static const char* s_tableName;
public:
	enum TypeFlag {
		FLG_NULL   = 0x00, 
		FLG_AFTER  = 0x01, 
		FLG_RANGE  = 0x02, 
		FLG_BEFORE = 0x04
	};

	enum TypePrefix {
		PREF_Unstated = 0,
		PREF_After,
		PREF_On,
		PREF_OrAfter,
		PREF_Before,
		PREF_Not,
		PREF_OrBefore,
		PREF_About,
		PREF_Max
	};
	static const wxString s_prefStr[PREF_Max];
	static const wxString s_prefFormat[PREF_Max];

	long            f_jdn;
	long            f_range;
    unsigned        f_type;         // Set with RecDate::TypeFlag
    wxString        f_desc;
    CalendarScheme  f_record_sch;   // Original convertion scheme
    CalendarScheme  f_display_sch;  // Default display scheme
	                                // See cal/calendar.h for values
    recDate() {}
    recDate( id_t id ) : recDb(id) {}

    const char* GetTableName() { return s_tableName; }
	void Clear();
    void Save();
    bool Read();

    static bool Delete( id_t id ) { return DeleteRecord( s_tableName, id ); }
};

#endif // RECDATE_H
