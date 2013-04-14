/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event, EventTypes, EventTypeRole and
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

#ifndef RECEVENT_H
#define RECEVENT_H

#include <rec/recDatabase.h>
#include <rec/recDate.h>
#include <rec/recReference.h>


class recEvent;
typedef std::vector< recEvent >            recEventVec;
class recEventRecord;
typedef std::vector< recEventRecord >      recEventRecordVec;
class recEventEventRecord;
typedef std::vector< recEventEventRecord > recEveEveRecordVec;
class recEventPersona;
typedef std::vector< recEventPersona >     recEventPersonaVec;
class recEventType;
typedef std::vector< recEventType >        recEventTypeVec;
class recEventTypeRole;
typedef std::vector< recEventTypeRole >    recEventTypeRoleVec;
class recIndividualEvent;
typedef std::vector< recIndividualEvent >  recIndEventVec;
class recFamilyEvent;
typedef std::vector< recFamilyEvent >      recFamilyEventVec;


//============================================================================
//-------------------------[ recEventType ]-----------------------------------
//============================================================================

enum {
    recET_FILTER_GrpNone        = 0x0000,
    recET_FILTER_GrpUnstated    = 0x0001,
    recET_FILTER_GrpBirth       = 0x0002,
    recET_FILTER_GrpNrBirth     = 0x0004,
    recET_FILTER_GrpFamUnion    = 0x0008,
    recET_FILTER_GrpFamOther    = 0x0010,
    recET_FILTER_GrpDeath       = 0x0020,
    recET_FILTER_GrpNrDeath     = 0x0040,
    recET_FILTER_GrpOther       = 0x0080,
    recET_FILTER_GrpPersonal    = 0x0100,
    recET_FILTER_GrpAll         = 0x01ff,
    recET_FILTER_GrpFamily = (recET_FILTER_GrpFamUnion|recET_FILTER_GrpFamOther)
};

class recEventType : public recDb
{
public:
    enum ETYPE_Grp {
        ETYPE_Grp_Unstated, // 0
        ETYPE_Grp_Birth,    // 1
        ETYPE_Grp_Nr_Birth, // 2
        ETYPE_Grp_Union,    // 3
        ETYPE_Grp_Family,   // 4
        ETYPE_Grp_Death,    // 5
        ETYPE_Grp_Nr_Death, // 6
        ETYPE_Grp_Other,    // 7
        ETYPE_Grp_Personal, // 8
        ETYPE_Grp_MAX       // 9
    };

    enum EType {  // predefined entries, match with recCreate.sql
        ET_Unstated     = 0,
        ET_Birth        = -1,
        ET_Death        = -2,
        ET_Marriage     = -3,
        ET_Baptism      = -4,
        ET_Burial       = -5,
        ET_AdultBaptism = -6,
        ET_Census       = -7,
        ET_Confirmation = -8,
        ET_Divorce      = -9,
        ET_Emigration   = -10,
        ET_Immigration  = -11,
        ET_Graduation   = -12,
        ET_Probate      = -13,
        ET_Will         = -14,
        ET_RegBirth     = -15,
        ET_RegDeath     = -16,
        ET_Residence    = -17,
        ET_Occupation   = -18,
        ET_Condition    = -19,
        ET_MAX          = 20     // Size of list
    };

    ETYPE_Grp f_grp;
    wxString  f_name;

    recEventType() {}
    recEventType( idt id ) : recDb(id) { Read(); }
    recEventType( const recEventType& et );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventType" );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "ET"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    ETYPE_Grp FGetGrp() const { return f_grp; }
    wxString FGetName() const { return f_name; }

    void FSetGrp( ETYPE_Grp grp ) { f_grp = grp; }
    void FSetName( wxString name ) { f_name = name; }

    bool HasDateSpan() const;
    static bool HasDateSpan( idt etID );

    wxString GetGroupStr() const { return GetGroupStr( f_grp ); }
    static wxString GetGroupStr( ETYPE_Grp grp );
    static wxString GetGroupStr( idt etID );

    static wxArrayString GetGroupStrings( size_t start = 0 );

    static wxString GetTypeStr( idt id );
    wxString GetTypeStr() const { return f_name; }
    static ETYPE_Grp GetGroup( idt id );
    ETYPE_Grp GetGroup() const { return f_grp; }

    static recEventTypeVec ReadVec( unsigned filter = recET_FILTER_GrpAll );

    static recEventTypeRoleVec GetRoles( idt typeID );
    recEventTypeRoleVec GetRoles() const { return GetRoles( FGetID() ); }
    static recEventTypeRoleVec GetPrimeRoles( idt typeID, int prime = 0 );
};

inline bool recEquivalent( const recEventType& r1, const recEventType& r2 )
{
    return
        r1.f_grp  == r2.f_grp  &&
        r1.f_name == r2.f_name;
}

inline bool operator==( const recEventType& r1, const recEventType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEventType& r1, const recEventType& r2 )
{
    return !(r1 == r2);
}


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

    wxString SetAutoTitle( const wxString& name1, const wxString& name2 = wxEmptyString );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "E"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
    recEventType::ETYPE_Grp GetTypeGroup() const;
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
//-------------------------[ recEventRecord ]---------------------------------
//============================================================================

class recEventRecord : public recDb
{
public:
    wxString f_title;
    idt      f_type_id;
    idt      f_date1_id;
    idt      f_date2_id;
    idt      f_place_id;
    wxString f_note;
    long     f_date_pt;

    recEventRecord() {}
    recEventRecord( idt id ) : recDb(id) { Read(); }
    recEventRecord( const recEventRecord& event );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventRecord" );

    wxString FGetTitle() const { return f_title; }
    idt FGetTypeID() const { return f_type_id; }
    idt FGetDate1ID() const { return f_date1_id; }
    idt FGetDate2ID() const { return f_date2_id; }
    idt FGetPlaceID() const { return f_place_id; }
    wxString FGetNote() const { return f_note; }
    long FGetDatePt() const { return f_date_pt; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetDate1ID( idt date1ID ) { f_date1_id = date1ID; }
    void FSetDate2ID( idt date2ID ) { f_date2_id = date2ID; }
    void FSetPlaceID( idt placeID ) { f_place_id = placeID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetDatePt( idt datePt ) { f_date_pt = datePt; }
    void FSetDatePt( recDate::DatePoint dp ) { f_date_pt = recDate::GetDatePoint( f_date1_id, dp ); }

    wxString SetAutoTitle( const wxString& name1, const wxString& name2 = wxEmptyString );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "ER"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
    recEventType::ETYPE_Grp GetTypeGroup() const;
    static wxString GetDetailStr( idt evID );
    static wxString GetTypeStr( idt evID );
    static wxString GetTitle( idt evID );
    static wxString GetNote( idt evID );
    static wxString GetDateStr( idt evID );
    static wxString GetAddressStr( idt evID );
    static idt GetDate1ID( idt evID );
    static void UpdateDatePoint( idt evID );
    void UpdateDatePoint();

    idt FindReferenceID() const { return FindReferenceID( f_id ); }
    static idt FindReferenceID( idt eventID ) {
        return recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, eventID );
    }
    static recIdVec FindRealEventIDs( idt erID );
    recIdVec FindRealEventIDs() const { return FindRealEventIDs( f_id ); }
    static recEveEveRecordVec GetEveEveRecords( idt erID );
    recEveEveRecordVec GetEveEveRecords() const { return GetEveEveRecords( f_id ); }

    static bool IsFamilyEvent( idt eveID );
    bool IsFamilyEvent() const { return IsFamilyEvent( f_id ); }

    recEventPersonaVec GetEventPersonas();
    static wxSQLite3Table GetTitleList();
    static wxSQLite3Table GetTitleList( idt offset, int limit );

    static int GetLastPerSeqNumber( idt eventID );
    int GetLastPerSeqNumber() const { return GetLastPerSeqNumber( f_id ); }

    static void RemoveDates( idt dateID ); // removes date if found, replacing with 0
    static void RemovePlace( idt placeID ); // removes place if found, replacing with 0

    // Delete Event and remove all references to it.
    void RemoveFromDatabase();
    static void RemoveFromDatabase( idt id );
    static void RemoveIncOrphansFromDatabase( idt id );

    static void DeleteIfOrphaned( idt id );
};

inline bool recEquivalent( const recEventRecord& r1, const recEventRecord& r2 )
{
    return
        r1.f_title    == r2.f_title    &&
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_date1_id == r2.f_date1_id &&
        r1.f_date2_id == r2.f_date2_id &&
        r1.f_place_id == r2.f_place_id &&
        r1.f_note     == r2.f_note     &&
        r1.f_date_pt  == r2.f_date_pt;
}

inline bool operator==( const recEventRecord& r1, const recEventRecord& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEventRecord& r1, const recEventRecord& r2 )
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

    bool Find();
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

#endif // RECEVENT_H
