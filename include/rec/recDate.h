/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDate.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Date records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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

#ifndef RECDATE_H
#define RECDATE_H

#include <rec/recDatabase.h>
#include <cal/calendar.h>

class recDate;
typedef std::vector< recDate >  recDateVec;

class recRelativeDate;

#define recDate_MAX_RECURSION_COUNT  10

enum {
    recD_FILTER_None      = 0x0000,
    recD_FILTER_Reference = 0x0001,
};


//-----------------------------------------------------
//      recDate
//-----------------------------------------------------

class recDate : public recDbT<recDate>
{
public:
    static constexpr const char* s_tablename = "Date";

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

    enum CompareFlag {
        CF_NONE         = 0x0000,
        CF_RangeAfter   = 0x0001, // The compared range is fully after this dates reange
        CF_RangeBefore  = 0x0002, // The compared range is fully before this dates reange
        CF_Overlap      = 0x0004, // Some dates within the (inclusive) range agree.

        CF_AfterOK      = 0x0010, // CF_RangeAfter set but this date has FLG_AFTER set
        CF_BeforeOK     = 0x0020, // CF_RangeBefore set but this date has FLG_BEFORE set
        CF_CompBeforeOK = 0x0040, // CF_RangeAfter set but this date has FLG_BEFORE set
        CF_CompAfterOK  = 0x0080, // CF_RangeAfter set but this date has FLG_AFTER set
        CF_WithinType   = 0x0100  // At lest one of the 4 above flags is set
    };

    static const wxString s_prefStr[PREF_Max];
    static const wxString s_prefFormat[PREF_Max];

    enum class DatePoint { beg, mid, end };

    long            f_jdn;
    long            f_range;
    idt             f_rel_id;
    unsigned        f_type;         // Set with RecDate::TypePrefix
    wxString        f_descrip;
    CalendarScheme  f_record_sch;   // Original convertion scheme
    CalendarScheme  f_display_sch;  // Default display scheme
                                    // See cal/calendar.h for values
    recDate() : f_jdn(0), f_range(0), f_rel_id(0), f_type(FLG_NULL),
        f_record_sch(CALENDAR_SCH_Unstated),
        f_display_sch(CALENDAR_SCH_Unstated) {}
    recDate( idt id ) : recDbT(id) { Read(); }
    recDate( const recDate& date );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recDate& r2 ) const;

    long FGetJdn() const { return f_jdn; }
    long FGetRange() const { return f_range; }
    idt FGetRelID() const { return f_rel_id; }
    unsigned FGetType() const { return f_type; }
    wxString FGetDescrip() const { return f_descrip; }
    CalendarScheme FGetRecordSch() const { return f_record_sch; }
    CalendarScheme FGetDisplaySch() const { return f_display_sch; }

    void FSetJdn( long jdn ) { f_jdn = jdn; }
    void FSetRange( long range ) { f_range = range; }
    void FSetRelID( idt relID ) { f_rel_id = relID; }
    void FSetType( unsigned type ) { f_type = type; }
    void FSetDescrip( const wxString& descrip ) { f_descrip = descrip; }
    void FSetRecordSch( CalendarScheme sch ) { f_record_sch = sch; }
    void FSetDisplaySch( CalendarScheme sch ) { f_display_sch = sch; }

    long GetEndJdn() const { return f_jdn + f_range; }
    void SetEndJdn( long jdn ) { f_range = jdn - f_jdn; }

    static wxString GetIdStr( idt indID ) { return wxString::Format( "D" ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    void SetDefaults();
    static idt Create( const wxString& str ); // Using default settings
    static idt Create( const recRelativeDate& rel ); 
    static idt Create( idt dateID ); // Clone and make absolute.

    bool SetDate( const wxString& str, CalendarScheme sch = CALENDAR_SCH_Unstated );
    static bool SetDate( idt dateID, const wxString& str, CalendarScheme sch = CALENDAR_SCH_Unstated );
    
    bool SetJdnDate( const wxString& str, CalendarScheme sch = CALENDAR_SCH_Unstated );
    void Update(); // Does nothing if not relative date.

    wxString GetJdnStr( CalendarScheme sch = CALENDAR_SCH_Unstated ) const;
    static wxString GetJdnStr( idt id, CalendarScheme sch = CALENDAR_SCH_Unstated  );

    wxString GetInputJdnStr() const { return GetJdnStr( f_record_sch ); }
    static wxString GetInputJdnStr( idt id );

    wxString GetStr( CalendarScheme sch = CALENDAR_SCH_Unstated ) const;
    static wxString GetStr( idt id );
    wxString GetPeriodStr( const recDate& date2 ) const;
    static wxString GetPeriodStr( idt d1ID, idt d2ID );

    int GetYear( CalendarScheme sch = CALENDAR_SCH_Unstated );
    static int GetYear( idt id, CalendarScheme sch = CALENDAR_SCH_Unstated );
    long GetDatePoint( DatePoint dp = DatePoint::mid );
    static long GetDatePoint( idt id, DatePoint dp = DatePoint::mid );

    unsigned GetTypePrefix() const {
        return f_type & ( FLG_AFTER | FLG_RANGE | FLG_BEFORE ); 
    }

    // See enum CompareFlag
    unsigned GetCompareFlags( const recDate& date ) const;

    // Return true if there is any overlap in date ranges
    bool IsOverlap( const recDate& date ) const;
    bool IsOverlap( idt dateID ) const { recDate date(dateID); return IsOverlap(date); }
    static bool IsOverlap( idt d1ID, idt d2ID ) { recDate date(d1ID); return date.IsOverlap(d2ID); }
    // Return true if either About or constant with Before and After (or overlap)
    bool IsConsistent( const recDate& date ) const;
    bool IsConsistent( idt dateID ) const { recDate date(dateID); return IsConsistent(date); }
    static bool IsConsistent( idt d1ID, idt d2ID ) { recDate date(d1ID); return date.IsConsistent(d2ID); }

    bool IsRelative() const { return ( f_rel_id != 0 ); }
    static bool IsRelative( idt dateID ) { recDate date(dateID); return date.IsRelative(); }
    bool IsUsedAsBase() const { return IsUsedAsBase( f_id ); }
    static bool IsUsedAsBase( idt dateID );
    static recIdVec GetRelativeIdList( idt id );
    bool IsUsedInEvent() const { return IsUsedInEvent( f_id ); }
    static bool IsUsedInEvent( idt dateID );
    bool IsUsedInSource() const { return IsUsedInSource( f_id ); }
    static bool IsUsedInSource( idt dateID );
    bool IsUsedInPlace() const { return IsUsedInPlace( f_id ); }
    static bool IsUsedInPlace( idt dateID );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void DeleteIfOrphaned( idt dateID );
    static void RemoveFromDatabase( idt dateID );
};


//-----------------------------------------------------
//      recRelativeDate
//-----------------------------------------------------

class recRelativeDate : public recDbT<recRelativeDate>
{
public:
    static constexpr const char* s_tablename = "RelativeDate";

    enum Type {
        TYPE_Unstated,
        TYPE_AgeRoundDown,
        TYPE_Duration,
        TYPE_AddToStart,
        TYPE_AddToEnd,
        TYPE_Max
    };

    long            f_val;
    long            f_range;
    CalendarUnit    f_unit;
    idt             f_base_id;
    Type            f_type;
    CalendarScheme  f_scheme;

    recRelativeDate() : f_val(0), f_range(0), f_base_id(0),
        f_unit( CALENDAR_UNIT_Unstated ),
        f_type( TYPE_Unstated ) ,
        f_scheme( CALENDAR_SCH_Unstated ) {}
    recRelativeDate( idt id ) : recDbT(id) { Read(); }
    recRelativeDate( const recRelativeDate& date );

    void Clear();
    void Save();
    bool Read();
    bool Equivalent( const recRelativeDate& r2 ) const;

    long FGetVal() const { return f_val; }
    long FGetValue() const { return f_val; }
    long FGetRange() const { return f_range; }
    CalendarUnit FGetUnit() const { return f_unit; }
    idt FGetBaseID() const { return f_base_id; }
    Type FGetType() const { return f_type; }
    CalendarScheme FGetScheme() const { return f_scheme; }

    void FSetVal( long val ) { f_val = val; }
    void FSetValue( long val ) { f_val = val; }
    void FSetRange( long range ) { f_range = range; }
    void FSetUnit( CalendarUnit unit ) { f_unit = unit; }
    void FSetBaseID( idt baseID ) { f_base_id = baseID; }
    void FSetType( Type type ) { f_type = type; }
    void FSetScheme( CalendarScheme sch ) { f_scheme = sch; } 

    static idt GetParentDate( idt rdID );

    void SetDefaults();

    static wxString GetIdStr( idt rdID ) { return wxString::Format( "RD" ID, rdID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    bool CalculateDate( recDate* date ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static void RemoveFromDatabase( idt rdID );
};


#endif // RECDATE_H
