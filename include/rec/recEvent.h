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

class recEventPersona;
typedef std::vector< recEventPersona >  recEventPersonaVec;
class recEventType;
typedef std::vector< recEventType >  recEventTypeVec;
class recEventTypeRole;
typedef std::vector< recEventTypeRole >  recEventTypeRoleVec;

//-----------------------------------------------------
//      recEvent
//-----------------------------------------------------

class recEvent : public recDb
{
public:
    wxString f_title;
    idt      f_type_id;
    idt      f_date1_id;
    idt      f_date2_id;
    idt      f_place_id;
    wxString f_note;

    recEvent() {}
    recEvent( idt id ) : recDb(id) { Read(); }
    recEvent( const recEvent& event );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Event" );

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
    static long GetDatePoint( idt evID );

    idt FindReferenceID() const { return FindReferenceID( f_id ); }
    static idt FindReferenceID( idt eventID ) {
        return recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Event, eventID );
    }

    recEventPersonaVec GetEventPersonas();

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
        r1.f_note     == r2.f_note;
}

inline bool operator==( const recEvent& r1, const recEvent& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEvent& r1, const recEvent& r2 )
{
    return !(r1 == r2);
}

//-----------------------------------------------------
//      recEventType
//-----------------------------------------------------

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
        ETYPE_Grp_MAX       // 8
    };
 //   enum ETYPE_Std {  // predefined entries, match with recCreate.sql
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
        ET_MAX          = 15     // Size of list
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


//-----------------------------------------------------
//      recEventTypeRole
//-----------------------------------------------------

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
        ROLE_Marriage_Witness       = -10,
        ROLE_MAX                    = 12 // size of list
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

//----------------------------------------------------------


class recEventPersona : public recDb
{
public:
    idt      f_event_id;
    idt      f_per_id;
    idt      f_role_id;
    wxString f_note;
    long     f_sequence;

    recEventPersona() {}
    recEventPersona( idt id ) : recDb(id) { Read(); }
    recEventPersona( const recEventPersona& pe );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventPersona" );

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
        r1.f_sequence == r2.f_sequence;
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
