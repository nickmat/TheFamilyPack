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

#include <vector>

#include <rec/recDatabase.h>
#include <rec/recReference.h>


class recEvent;
typedef std::vector< recEvent >          recEventVec;
class recEventPersona;
typedef std::vector< recEventPersona >   recEventPersonaVec;
class recEventType;
typedef std::vector< recEventType >      recEventTypeVec;
class recEventTypeRole;
typedef std::vector< recEventTypeRole >  recEventTypeRoleVec;

//============================================================================
//-------------------------[ recEvent ]---------------------------------------
//============================================================================

class recEvent : public recDb
{
public:
    wxString f_title;
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

    static wxString GetIdStr( idt evID ) { return wxString::Format( "E"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
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

    recEventPersonaVec GetEventPersonas();
    static wxSQLite3ResultSet GetTitleList();

    static int GetLastPersonaSeqNumber( idt eventID );
    int GetLastPersonaSeqNumber() const { return GetLastPersonaSeqNumber( f_id ); }

    // Delete Event and remove all references to it.
    bool DeleteFromDb() { return DeleteFromDb( f_id ); }
    static bool DeleteFromDb( idt id );
};

inline bool recEquivalent( const recEvent& r1, const recEvent& r2 )
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

inline bool operator==( const recEvent& r1, const recEvent& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEvent& r1, const recEvent& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recEventType ]-----------------------------------
//============================================================================

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
        ETYPE_Grp_Lifetime, // 8
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
    enum SelectFilter {
        SF_All,
        SF_Individual,
        SF_Family
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

    static wxString GetTypeStr( idt id );
    wxString GetTypeStr() const { return f_name; }
    static ETYPE_Grp GetGroup( idt id );
    ETYPE_Grp GetGroup() const { return f_grp; }

    static recEventTypeVec ReadAll();
    static recEventTypeVec ReadAllIndividual();
    static recEventTypeVec ReadAllFamily();
    static idt Select( SelectFilter sf = SF_All );
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
    static wxString GetTypeAndRoleStr( idt roleID );
    static idt Select( idt typeID, SelectFilter sf = SF_All );
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
    idt      f_event_id;
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

    idt FGetEventID() const { return f_event_id; }
    idt FGetPerID() const { return f_per_id; }
    idt FGetRoleID() const { return f_role_id; }
    wxString FGetNote() const { return f_note; }
    int FGetPerSeq() const { return f_per_seq; }

    void FSetEventID( idt eventID ) { f_event_id = eventID; }
    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetRoleID( idt roleID ) { f_role_id = roleID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetPerSeq( int perSeq ) { f_per_seq = perSeq; }

    static wxString GetIdStr( idt epID ) { return wxString::Format( "EP"ID, epID ); }
    wxString GetIdStr() const { return GetIdStr( FGetID() ); }

    static wxString GetRoleStr( idt roleID ) 
        { return ExecuteStr( "SELECT name FROM EventTypeRole WHERE id="ID";", roleID ); }
    wxString GetRoleStr() const { return GetRoleStr( f_role_id ); }

    /*! Return true if a record exists that matches the
     *  f_per_id, f_event_id and f_role_id.
     */
    bool LinkExists() const;
};

inline bool recEquivalent( const recEventPersona& r1, const recEventPersona& r2 )
{
    return
        r1.f_event_id == r2.f_event_id &&
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


#endif // RECEVENT_H
