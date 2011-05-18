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

    enum BaseStyle {
        BASE_STYLE_Unstated,
        BASE_STYLE_AgeRoundDown,
        BASE_STYLE_Max
    };

    static int      sm_count;       // Limit the number of recusive lookups 

    long            f_jdn;
    long            f_range;
    idt             f_base_id;
    CalendarAgeUnit f_base_unit;
    BaseStyle       f_base_style;
    unsigned        f_type;         // Set with RecDate::TypeFlag
    wxString        f_descrip;
    CalendarScheme  f_record_sch;   // Original convertion scheme
    CalendarScheme  f_display_sch;  // Default display scheme
                                    // See cal/calendar.h for values
    recDate() {}
    recDate( idt id ) : recDb(id) { Read(); }
    recDate( const recDate& date );

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
     *  static bool Delete( idt id );
     *
     *  // Return true if given record exists, static function.\n
     *  static bool Exists( idt id );
     */
    TABLE_NAME_MEMBERS( "Date" );

    void SetDefaults();
    bool SetDate( const wxString& str, CalendarScheme sch = CALENDAR_SCH_Unstated );
    wxString GetJdnStr( CalendarScheme sch = CALENDAR_SCH_Unstated ) const;
    static wxString GetJdnStr( idt id );
    wxString GetStr( CalendarScheme sch = CALENDAR_SCH_Unstated ) const;
    static wxString GetStr( idt id );
    int GetYear( CalendarScheme sch = CALENDAR_SCH_Unstated );

    unsigned GetTypePrefix() const {
        return f_type & ( FLG_AFTER | FLG_RANGE | FLG_BEFORE ); 
    }

};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recDate& d1, const recDate& d2 )
{
    return
        d1.f_jdn         == d2.f_jdn        &&
        d1.f_range       == d2.f_range      &&
        d1.f_base_id     == d2.f_base_id    &&
        d1.f_base_unit   == d2.f_base_unit  &&
        d1.f_base_style  == d2.f_base_style &&
        d1.f_type        == d2.f_type       &&
        d1.f_descrip     == d2.f_descrip    &&
        d1.f_record_sch  == d2.f_record_sch &&
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
