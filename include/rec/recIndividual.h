/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family, FamilyIndividual, Individual and
 *              IndividualPersona records.
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

#ifndef RECINDIVIDUAL_H
#define RECINDIVIDUAL_H

#include <vector>

#include <rec/recDatabase.h>
#include <rec/recEvent.h>

class recIndividual;
typedef std::vector< recIndividual >  recIndividualList;
class recFamily;
typedef std::vector< recFamily >  recFamilyList;
class recFamilyIndividual;
typedef std::vector< recFamilyIndividual >  recFamIndVec;


class recIndividual : public recDb
{
public:
    wxString f_surname;
    wxString f_given;
    long     f_birth_jdn;
    wxString f_epitaph;
    Sex      f_sex;
    idt     f_fam_id;
    idt     f_per_id;
    idt     f_birth_id;
    idt     f_nr_birth_id;
    idt     f_death_id;
    idt     f_nr_death_id;
    idt     f_occ_id;

    recIndividual() {}
    recIndividual( idt id ) : recDb(id) { Read(); }
    recIndividual( const recIndividual& ind );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Individual" );

    static wxString GetIdStr( idt indID ) { return wxString::Format( "I"ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    void UpdateDateEpitaph();
    void UpdateNames();
    wxString GetFullName() { return f_given + " " + f_surname; }

    static idt GetDefaultFamily( idt id ) {
        return ExecuteID( "SELECT fam_id FROM Individual WHERE id="ID";", id );
    }
    static idt GetDefaultPersonaId( idt id ) {
        return ExecuteID( "SELECT per_id FROM Individual WHERE id="ID";", id );
    }
    static wxString GetFullName( idt id );
    static wxString GetSurname( idt id );
    static wxString GetDateEpitaph( idt id );

    static recFamilyList GetFamilyList( idt ind );
    recFamilyList GetFamilyList() const { return GetFamilyList( f_id ); }
    static recFamilyList GetParentList( idt indID );
    recFamilyList GetParentList() const { return GetParentList( f_id ); }

    recEventPersonaVec GetEventPersonaVec() const
        { return GetEventPersonaVec( f_id ); }
    static recEventPersonaVec GetEventPersonaVec( idt id );

    wxSQLite3Table GetEventsTable() const { return GetEventsTable( f_id ); }
    static wxSQLite3Table GetEventsTable( idt id );

    wxSQLite3Table GetAttributesTable() const { return GetAttributesTable( f_id ); }
    static wxSQLite3Table GetAttributesTable( idt id );

    wxArrayString GetEventIdStrList( idt etrID ) const { GetEventIdStrList( f_id, etrID ); }
    static wxArrayString GetEventIdStrList( idt indID, idt etrID );

    static wxSQLite3ResultSet GetSurnameList() {
        return s_db->ExecuteQuery(
            "SELECT surname FROM Individual GROUP BY surname;"
        );
    }
    static wxSQLite3ResultSet GetNameList( wxString name );
    static wxSQLite3Table GetNameTable( Sex sex );

    static void AddMissingFamilies();
};

inline bool recEquivalent( const recIndividual& r1, const recIndividual& r2 )
{
    return
        r1.f_surname     == r2.f_surname      &&
        r1.f_given       == r2.f_given        &&
        r1.f_birth_jdn   == r2.f_birth_jdn    &&
        r1.f_epitaph     == r2.f_epitaph      &&
        r1.f_sex         == r2.f_sex          &&
        r1.f_fam_id      == r2.f_fam_id       &&
        r1.f_per_id      == r2.f_per_id       &&
        r1.f_birth_id    == r2.f_birth_id     &&
        r1.f_nr_birth_id == r2.f_nr_birth_id  &&
        r1.f_death_id    == r2.f_death_id     &&
        r1.f_nr_death_id == r2.f_nr_death_id  &&
        r1.f_occ_id      == r2.f_occ_id;
}

inline bool operator==( const recIndividual& r1, const recIndividual& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recIndividual& r1, const recIndividual& r2 )
{
    return !(r1 == r2);
}


//----------------------------------------------------------

class recIndividualPersona : public recDb
{
public:
    idt     f_per_id;
    idt     f_ind_id;
    wxString f_note;

    recIndividualPersona() {}
    recIndividualPersona( idt id ) : recDb(id) { Read(); }
    recIndividualPersona( const recIndividualPersona& ip );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "IndividualPersona" );

    bool Find();
};

inline bool recEquivalent( const recIndividualPersona& r1, const recIndividualPersona& r2 )
{
    return
        r1.f_per_id == r2.f_per_id  &&
        r1.f_ind_id == r2.f_ind_id  &&
        r1.f_note   == r2.f_note;
}

inline bool operator==( const recIndividualPersona& r1, const recIndividualPersona& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recIndividualPersona& r1, const recIndividualPersona& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recFamily : public recDb
{
public:
    idt     f_husb_id;
    idt     f_wife_id;
    idt     f_event_id;

    recFamily() {}
    recFamily( idt id ) : recDb(id) { Read(); }
    recFamily( const recFamily& family );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Family" );

    bool ReadParents( idt ind );
    static recIndividualList GetChildren( idt fam );
    recIndividualList GetChildren() const { return GetChildren( f_id ); }
    static recIdList GetChildrenIds( idt fam );
    recIdList GetChildrenIds() const { return GetChildrenIds( f_id ); }
    static unsigned GetChildNextSequence( idt id );
    recFamIndVec GetChildLinks() { return GetChildLinks( f_id ); }
    static recFamIndVec GetChildLinks( idt famID );

    wxArrayString GetMarriageEventTable() const;
};

inline bool recEquivalent( const recFamily& r1, const recFamily& r2 )
{
    return
        r1.f_husb_id  == r2.f_husb_id  &&
        r1.f_wife_id  == r2.f_wife_id  &&
        r1.f_event_id == r2.f_event_id;
}

inline bool operator==( const recFamily& r1, const recFamily& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recFamily& r1, const recFamily& r2 )
{
    return !(r1 == r2);
}


//----------------------------------------------------------

class recFamilyIndividual : public recDb
{
public:
    idt     f_fam_id;
    idt     f_ind_id;
    unsigned f_sequence;

    recFamilyIndividual() {}
    recFamilyIndividual( idt id ) : recDb(id) { Read(); }
    recFamilyIndividual( const recFamilyIndividual& fi );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "FamilyIndividual" );

    bool Find();
};

inline bool recEquivalent( const recFamilyIndividual& r1, const recFamilyIndividual& r2 )
{
    return
        r1.f_fam_id   == r2.f_fam_id  &&
        r1.f_ind_id   == r2.f_ind_id  &&
        r1.f_sequence == r2.f_sequence;
}

inline bool operator==( const recFamilyIndividual& r1, const recFamilyIndividual& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recFamilyIndividual& r1, const recFamilyIndividual& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

#endif // RECINDIVIDUAL_H
