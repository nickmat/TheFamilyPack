/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recEvent.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Event, EventTypes, EventTypeRole and 
 *              RecPersonaEvent records.
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

#include <wx/vector.h>
#include <rec/recDatabase.h>

class recPersonaEvent;
typedef wxVector< recPersonaEvent >  recPersonaEventVec;
class recEventType;
typedef wxVector< recEventType >  recEventTypeVec;
class recEventTypeRole;
typedef wxVector< recEventTypeRole >  recEventTypeRoleVec;


class recEvent : public recDb 
{
public:
    wxString f_title;
    id_t     f_type_id;
    id_t     f_date1_id;
    id_t     f_date2_id;
    id_t     f_place_id;
    wxString f_note;

    recEvent() {}
    recEvent( id_t id ) : recDb(id) { Read(); }
    recEvent( const recEvent& event );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Event" );

    wxString GetDetailStr() const;
    wxString GetTypeStr() const;
    wxString GetDateStr() const;
    wxString GetAddressStr() const;
    static wxString GetDetailStr( id_t id );
    static wxString GetTypeStr( id_t id );
    static wxString GetTitle( id_t id );
    static wxString GetNote( id_t id );

	id_t FindReference() const { return FindReference( f_id ); }
	static id_t FindReference( id_t eventID );

	recPersonaEventVec GetPersonaEvents();

    // Delete Event and remove all references to it.
    bool DeleteFromDb() { return DeleteFromDb( f_id ); }
    static bool DeleteFromDb( id_t id );
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

//----------------------------------------------------------


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
	enum ETYPE_Std {  // predefined entries, match with recCreate.sql 
		ET_Unstated = 0,
        ET_Birth    = -1,	
        ET_Death    = -2,
        ET_Marriage = -3,
        ET_Baptism  = -4,
		ET_Burial   = -5,
		ET_MAX      = 6     // Size of list 
	};

    ETYPE_Grp f_grp;
    wxString  f_name;

    recEventType() {}
    recEventType( id_t id ) : recDb(id) { Read(); }
    recEventType( const recEventType& et );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventType" );

    static wxString GetTypeStr( id_t id );

	static recEventTypeVec ReadAll();
	static id_t Select();
    static recEventTypeRoleVec GetRoles( id_t typeID );
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

//----------------------------------------------------------


class recEventTypeRole : public recDb 
{
public:
	enum Role {  // predefined entries, only given if reqired by the program
		ROLE_Unstated       = 0,
		ROLE_Birth_Born     = -1, 
		ROLE_Death_Died     = -5,
        ROLE_Marriage_Groom = -7,
        ROLE_Marriage_Bride = -8,
		ROLE_MAX            = 5 // size of list
	};

    id_t      f_type_id;
    wxString  f_name;

    recEventTypeRole() {}
    recEventTypeRole( id_t id ) : recDb(id) { Read(); }
    recEventTypeRole( const recEventTypeRole& etr );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventTypeRole" );

	static wxString GetName( id_t roleID );
};

inline bool recEquivalent( const recEventTypeRole& r1, const recEventTypeRole& r2 )
{
    return
        r1.f_type_id == r2.f_type_id &&
        r1.f_name    == r2.f_name;
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


class recPersonaEvent : public recDb 
{
public:
    id_t     f_per_id;
    id_t     f_event_id;
    id_t     f_role_id;
    wxString f_note;

    recPersonaEvent() {}
    recPersonaEvent( id_t id ) : recDb(id) { Read(); }
    recPersonaEvent( const recPersonaEvent& pe );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "PersonaEvent" );
};

inline bool recEquivalent( const recPersonaEvent& r1, const recPersonaEvent& r2 )
{
    return
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_event_id == r2.f_event_id &&
        r1.f_role_id  == r2.f_role_id  &&
        r1.f_note     == r2.f_note;
}

inline bool operator==( const recPersonaEvent& r1, const recPersonaEvent& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recPersonaEvent& r1, const recPersonaEvent& r2 )
{
    return !(r1 == r2);
}


#endif // RECEVENT_H
