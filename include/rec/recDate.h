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

#include <rec/recDatabase.h>
#include <cal/calendar.h>

class recDate : public recDb 
{
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
    recDate( id_t id ) : recDb(id) { Read(); }

	void Clear();
    void Save();
    bool Read();
    /*! Impliments the member functions:
     *
     *  // Returns table name string.\n
     *  const char* GetTableName() const;
     *
     *  // Delete the current record.\n
     *  bool Delete();
     *
     *  // Return true if current record exists.\n
     *  bool Exists();
     *
     *  // Delete the given record, static function.\n
     *  static bool Delete( id_t id );
     *
     *  // Return true if given record exists, static function.\n
     *  static bool Exists( id_t id );
     */
    TABLE_NAME_MEMBERS( "Date" );

    void SetDefaults();
	bool SetDate( const wxString& str, CalendarScheme sch = CALENDAR_SCH_Unstated );
    wxString GetStr( CalendarScheme sch = CALENDAR_SCH_Unstated ) const;
    static wxString GetStr( id_t id );
	int GetYear( CalendarScheme sch = CALENDAR_SCH_Unstated );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recDate& d1, const recDate& d2 )
{
    return
        d1.f_jdn == d2.f_jdn && 
        d1.f_range == d2.f_range &&
        d1.f_type == d2.f_type &&
        d1.f_desc == d2.f_desc &&
        d1.f_record_sch == d2.f_record_sch &&
        d1.f_display_sch == d2.f_display_sch;
}

inline bool operator==( const recDate& d1, const recDate& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recDate& d1, const recDate& d2 )
{
    return !(d1 == d2);
}

#endif // RECDATE_H
