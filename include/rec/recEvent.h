/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event, EventTypeRole and
 *              RecEventPersona records.
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

#ifndef REC_RECEVENT_H
#define REC_RECEVENT_H

#include <rec/recDatabase.h>
#include <rec/recEventType.h>
#include <rec/recDate.h>
#include <rec/recReference.h>

enum recE_ {
    recE_FILTER_None      = 0x0000,
    recE_FILTER_Reference = 0x0001,
};

//============================================================================
//-------------------------[ recEvent ]---------------------------------------
//============================================================================

class recEvent : public recDb
{
public:
    wxString f_title;
    idt      f_higher_id;
    idt      f_type_id;
    idt      f_date1_id;
    idt      f_date2_id;
    idt      f_place_id;
    wxString f_note;
    long     f_date_pt;

    recEvent() {}
    recEvent( idt id ) : recDb(id) { Read(); }
    recEvent( const recEvent& event );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Event" );

    wxString FGetTitle() const { return f_title; }
    idt FGetHigherID() const { return f_higher_id; }
    idt FGetTypeID() const { return f_type_id; }
    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetNote() const { return f_note; }
    long FGetDatePt() const { return f_date_pt; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetHigherID( idt eveID ) { f_higher_id = eveID; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetDate1ID( idt date1ID ) { f_date1_id = date1ID; }
    void FSetDate2ID( idt date2ID ) { f_date2_id = date2ID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetDatePt( idt datePt ) { f_date_pt = datePt; }
    void FSetDatePt( recDate::DatePoint dp ) { f_date_pt = recDate::GetDatePoint( f_date1_id, dp ); }

    static wxString GetIdStr( idt evID ) { return wxString::Format( "E"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt CreateFromEventRecord( idt erID );

    wxString SetAutoTitle( const wxString& name1, const wxString& name2 = wxEmptyString );
    static void SetDatePeriodToInclude( idt eventID, idt dateID );

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
    recET_GRP GetTypeGroup() const;
    static wxString GetDetailStr( idt evID );
    static wxString GetTypeStr( idt evID );
    static wxString GetTitle( idt evID );
    static wxString GetNote( idt evID );
    static wxString GetDateStr( idt evID );
    static wxString GetAddressStr( idt evID );
    static idt GetDate1ID( idt evID );
    static void UpdateDatePoint( idt evID );
    void UpdateDatePoint();

    static recEventRecordVec FindEquivRefEvents( idt evetID );
    static recEveEveRecordVec GetEveEveRecords( idt eveID );
    recEveEveRecordVec GetEveEveRecords() const { return GetEveEveRecords( f_id ); }

    static bool IsFamilyEvent( idt eveID );
    bool IsFamilyEvent() const { return IsFamilyEvent( f_id ); }

    recIndEventVec GetIndividualEvents();
    static wxSQLite3Table GetTitleList();
    static wxSQLite3Table GetTitleList( idt offset, int limit );

    static void RemoveDates( idt dateID ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    void RemoveFromDatabase();
    static void RemoveFromDatabase( idt id );
    static void RemoveIncOrphansFromDatabase( idt id );

    static void DeleteIfOrphaned( idt id );
};

inline bool recEquivalent( const recEvent& r1, const recEvent& r2 )
{
    return
        r1.f_title     == r2.f_title     &&
        r1.f_higher_id == r2.f_higher_id &&
        r1.f_type_id   == r2.f_type_id   &&
        r1.f_date1_id  == r2.f_date1_id  &&
        r1.f_date2_id  == r2.f_date2_id  &&
        r1.f_place_id  == r2.f_place_id  &&
        r1.f_note      == r2.f_note      &&
        r1.f_date_pt   == r2.f_date_pt;
}

inline bool operator==( const recEvent& r1, const recEvent& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEvent& r1, const recEvent& r2 )
{
    return !(r1 == r2);
}


//============================================================================
//-------------------------[ recEventEventRecord ]----------------------------
//============================================================================

class recEventEventRecord : public recDb
{
    idt      f_event_id;
    idt      f_event_rec_id;
    double   f_conf;
    wxString f_note;

public:
    recEventEventRecord() {}
    recEventEventRecord( idt id ) : recDb(id) { Read(); }
    recEventEventRecord( const recEventEventRecord& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventEventRecord" );

    idt FGetEventID() const { return f_event_id; }
    idt FGetEventRecID() const { return f_event_rec_id; }
    double FGetConf() const { return f_conf; }
    wxString FGetNote() const { return f_note; }

    void FSetEventID( idt eveID ) { f_event_id = eveID; }
    void FSetEventRecID( idt erID ) { f_event_rec_id = erID; }
    void FSetConf( double conf ) { f_conf = conf; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt eerID ) { return wxString::Format( "EER"ID, eerID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt Create( idt eID, idt erID, double conf = 0.999, const wxString& note = wxEmptyString );

    bool Find();
    static idt Find( idt eID, idt erID );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recEventEventRecord& d1, const recEventEventRecord& d2 )
{
    return
        d1.FGetEventID()    == d2.FGetEventID()    &&
        d1.FGetEventRecID() == d2.FGetEventRecID() &&
        d1.FGetConf()       == d2.FGetConf()       &&
        d1.FGetNote()       == d2.FGetNote();
}

inline bool operator==( const recEventEventRecord& d1, const recEventEventRecord& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recEventEventRecord& d1, const recEventEventRecord& d2 )
{
    return !(d1 == d2);
}

//============================================================================
//-------------------------[ recEventTypeRole ]-------------------------------
//============================================================================

class recEventTypeRole : public recDb
{
public:
    enum Role {  // predefined entries, only given if reqired by the program
        ROLE_Unstated               = 0,
        ROLE_Birth_Born             = -1,
        ROLE_Birth_Mother           = -2,
        ROLE_Baptism_Baptised       = -21,
        ROLE_Baptism_Parent         = -22,
        ROLE_Census_Listed          = -32,
        ROLE_Death_Died             = -5,
        ROLE_Burial_Deceased        = -26,
        ROLE_Marriage_Bride         = -8,
        ROLE_Marriage_FatherOfBride = -13,
        ROLE_Marriage_FatherOfGroom = -11,
        ROLE_Marriage_Groom         = -7,
        ROLE_Marriage_Officiate     = -9,
        ROLE_Marriage_Spouse        = -59,  // If we don't know their gender.
        ROLE_Marriage_Witness       = -10,
        ROLE_RegBirth_Born          = -50,
        ROLE_RegBirth_Parent        = -51,
        ROLE_RegBirth_Mother        = -60,
        ROLE_RegDeath_Died          = -55,
        ROLE_Residence_Boarder      = -64,
        ROLE_Residence_Family       = -61,
        ROLE_Residence_Lodger       = -63,
        ROLE_Residence_Visitor      = -62,
        ROLE_Occupation             = -65,
        ROLE_Condition              = -67,
        ROLE_MAX                    = 24 // size of list
    };
    enum Prime {
        PRIME_Ignore = -1,
        PRIME_None   = 0,
        PRIME_First  = 1,
        PRIME_Second = 2,
        PRIME_Any    = 3,
        PRIME_MAX    = 4
    };
    enum SelectFilter {
        SF_All,
        SF_Prime,
        SF_Prime1,
        SF_Prime2
    };

    idt       f_type_id;
    int       f_prime;
    bool      f_official;
    wxString  f_name;

    recEventTypeRole() {}
    recEventTypeRole( idt id ) : recDb(id) { Read(); }
    recEventTypeRole( const recEventTypeRole& etr );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventTypeRole" );

    idt FGetTypeID() const { return f_type_id; }
    int FGetPrime() const { return f_prime; }
    bool FGetOfficial() const { return f_official; }
    wxString FGetName() const { return f_name; }

    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetPrime( int prime ) { f_prime = prime; }
    void FSetOfficial( bool official ) { f_official = official; }
    void FSetName( const wxString& name ) { f_name = name; }

    static wxString GetIdStr( idt evID ) { return wxString::Format( "Ro"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetName( idt roleID );
    wxString GetPrimeStr() const;

    static wxString GetTypeAndRoleStr( idt roleID );
    static idt Select( idt typeID, SelectFilter sf = SF_All );

    static idt Find( const wxString& name, idt type, Prime prime = PRIME_Ignore, TriLogic official = TRILOGIC_both );
    static idt FindOrCreate( const wxString& name, idt type, Prime prime = PRIME_First, bool official = false );
};

inline bool recEquivalent( const recEventTypeRole& r1, const recEventTypeRole& r2 )
{
    return
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_prime    == r2.f_prime    &&
        r1.f_official == r2.f_official &&
        r1.f_name     == r2.f_name;
}

inline bool operator==( const recEventTypeRole& r1, const recEventTypeRole& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEventTypeRole& r1, const recEventTypeRole& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recEventPersona ]--------------------------------
//============================================================================

class recEventPersona : public recDb
{
public:
    idt      f_event_rec_id;
    idt      f_per_id;
    idt      f_role_id;
    wxString f_note;
    int      f_per_seq;

    recEventPersona() {}
    recEventPersona( idt id ) : recDb(id) { Read(); }
    recEventPersona( const recEventPersona& pe );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventPersona" );

    idt FGetEventRecID() const { return f_event_rec_id; }
    idt FGetPerID() const { return f_per_id; }
    idt FGetRoleID() const { return f_role_id; }
    wxString FGetNote() const { return f_note; }
    int FGetPerSeq() const { return f_per_seq; }

    void FSetEventRecID( idt erID ) { f_event_rec_id = erID; }
    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetRoleID( idt roleID ) { f_role_id = roleID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetPerSeq( int perSeq ) { f_per_seq = perSeq; }

    static wxString GetIdStr( idt epID ) { return wxString::Format( "EP"ID, epID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static wxString GetRoleStr( idt perID, idt typeID );
    wxString GetRoleStr( idt typeID ) const { return GetRoleStr( f_per_id, typeID ); }

    /*! Return true if a record exists that matches the
     *  f_per_id, f_event_id and f_role_id.
     */
    bool LinkExists() const;
};

inline bool recEquivalent( const recEventPersona& r1, const recEventPersona& r2 )
{
    return
        r1.f_event_rec_id == r2.f_event_rec_id &&
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_role_id  == r2.f_role_id  &&
        r1.f_note     == r2.f_note     &&
        r1.f_per_seq  == r2.f_per_seq;
}

inline bool operator==( const recEventPersona& r1, const recEventPersona& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEventPersona& r1, const recEventPersona& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recIndividualEvent ]-----------------------------
//============================================================================

class recIndividualEvent : public recDb
{
public:
    idt      f_ind_id;
    idt      f_event_id;
    idt      f_role_id;
    wxString f_note;
    int      f_ind_seq;

    recIndividualEvent() {}
    recIndividualEvent( idt id ) : recDb(id) { Read(); }
    recIndividualEvent( const recIndividualEvent& pe );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "IndividualEvent" );

    idt FGetIndID() const { return f_ind_id; }
    idt FGetEventID() const { return f_event_id; }
    idt FGetRoleID() const { return f_role_id; }
    wxString FGetNote() const { return f_note; }
    int FGetIndSeq() const { return f_ind_seq; }

    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetEventID( idt eventID ) { f_event_id = eventID; }
    void FSetRoleID( idt roleID ) { f_role_id = roleID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetIndSeq( int indSeq ) { f_ind_seq = indSeq; }

    static wxString GetIdStr( idt ieID ) { return wxString::Format( "IE"ID, ieID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static idt Create( idt indID, idt eID, idt roleID, const wxString& note = wxEmptyString );

    bool Find( idt indID, idt eveID );

    static wxString GetRoleStr( idt indID, idt typeID );
    wxString GetRoleStr( idt typeID ) const { return GetRoleStr( f_ind_id, typeID ); }
};

inline bool recEquivalent( const recIndividualEvent& r1, const recIndividualEvent& r2 )
{
    return
        r1.f_ind_id   == r2.f_ind_id   &&
        r1.f_event_id == r2.f_event_id &&
        r1.f_role_id  == r2.f_role_id  &&
        r1.f_note     == r2.f_note     &&
        r1.f_ind_seq  == r2.f_ind_seq;
}

inline bool operator==( const recIndividualEvent& r1, const recIndividualEvent& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recIndividualEvent& r1, const recIndividualEvent& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recFamilyEvent ]---------------------------------
//============================================================================

class recFamilyEvent : public recDb
{
public:
    idt      f_fam_id;
    idt      f_event_id;
    wxString f_note;
    int      f_fam_seq;

    recFamilyEvent() {}
    recFamilyEvent( idt id ) : recDb(id) { Read(); }
    recFamilyEvent( const recFamilyEvent& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "FamilyEvent" );

    idt FGetFamID() const { return f_fam_id; }
    idt FGetEventID() const { return f_event_id; }
    wxString FGetNote() const { return f_note; }
    int FGetFamSeq() const { return f_fam_seq; }

    void FSetFamID( idt famID ) { f_fam_id = famID; }
    void FSetEventID( idt eventID ) { f_event_id = eventID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetFamSeq( int seq ) { f_fam_seq = seq; }

    static wxString GetIdStr( idt feID ) { return wxString::Format( "FE"ID, feID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recFamilyEvent& r1, const recFamilyEvent& r2 )
{
    return
        r1.f_fam_id   == r2.f_fam_id   &&
        r1.f_event_id == r2.f_event_id &&
        r1.f_note     == r2.f_note     &&
        r1.f_fam_seq  == r2.f_fam_seq;
}

inline bool operator==( const recFamilyEvent& d1, const recFamilyEvent& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recFamilyEvent& d1, const recFamilyEvent& d2 )
{
    return !(d1 == d2);
}

#endif // REC_RECEVENT_H
