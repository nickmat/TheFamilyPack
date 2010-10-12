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

#include <wx/vector.h>
#include <rec/recDatabase.h>

class recIndividual;
typedef wxVector< recIndividual >  recIndividualList;
class recFamily;
typedef wxVector< recFamily >  recFamilyList;
class recFamilyIndividual;
typedef wxVector< recFamilyIndividual >  recFamIndVec;


class recIndividual : public recDb {
public:
    wxString f_surname;
    wxString f_given;
    long     f_birth_jdn;
    wxString f_epitaph;
    Sex      f_sex;
    id_t     f_fam_id;
    id_t     f_per_id;
    id_t     f_birth_id;
    id_t     f_nr_birth_id;
    id_t     f_death_id;
    id_t     f_nr_death_id;
    id_t     f_occ_id;

    recIndividual() {}
    recIndividual( id_t id ) : recDb(id) {}

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Individual" );

    void UpdateDateEpitaph();
    wxString GetFullName() { return f_given + " " + f_surname; }

    static id_t GetDefaultFamily( id_t id ) {
		return ExecuteID( "SELECT fam_id FROM Individual WHERE id="ID";", id ); 
    }
    static wxString GetFullName( id_t id );
    static wxString GetSurname( id_t id );
    static wxString GetDateEpitaph( id_t id );

    static recFamilyList GetFamilyList( id_t ind );
    recFamilyList GetFamilyList() const { return GetFamilyList( f_id ); }
    static recFamilyList GetParentList( id_t indID );
    recFamilyList GetParentList() const { return GetParentList( f_id ); }
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

class recIndividualPersona : public recDb {
public:
    id_t     f_per_id;
    id_t     f_ind_id;
    wxString f_note;

    recIndividualPersona() {}
    recIndividualPersona( id_t id ) : recDb(id) {}

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

class recFamily : public recDb {
public:
    id_t     f_husb_id;
    id_t     f_wife_id;
    id_t     f_event_id;

    recFamily() {}
    recFamily( id_t id ) : recDb(id) {}

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Family" );

    bool ReadParents( id_t ind );
    static recIndividualList GetChildren( id_t fam );
    recIndividualList GetChildren() const { return GetChildren( f_id ); }
    static unsigned GetChildNextSequence( id_t id );
    recFamIndVec GetChildLinks() { return GetChildLinks( f_id ); }
	static recFamIndVec GetChildLinks( id_t famID );
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

class recFamilyIndividual : public recDb {
public:
    id_t     f_fam_id;
    id_t     f_ind_id;
    unsigned f_sequence;

    recFamilyIndividual() {}
    recFamilyIndividual( id_t id ) : recDb(id) {}

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
