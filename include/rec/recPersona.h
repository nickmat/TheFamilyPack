/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Persona, Attribute and AttributeType records.
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

#ifndef RECPERSONA_H
#define RECPERSONA_H

#include <wx/vector.h>
#include <rec/recDatabase.h>

class recPersona;
class recAttribute;
class recAttributeType;
typedef wxVector< recPersona >  recPersonaList;
typedef wxVector< recAttribute >  recAttributeList;
typedef wxVector< recAttributeType >  recAttributeTypeVec;

class recPersona : public recDb
{
public:
    Sex      f_sex;
    wxString f_note;

    recPersona() {}
    recPersona( id_t id ) : recDb(id) { Read(); }
    recPersona( const recPersona& persona );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Persona" );

    static wxString GetSurname( id_t id );
    static wxString GetGivenName( id_t id );
    static wxString GetFullName( id_t id ) 
        { return GetGivenName( id ) + " " + GetSurname( id ); }
    wxString GetFullName() const { return GetFullName( f_id ); }
	static recAttributeList ReadAttributes( id_t perID );
    recAttributeList ReadAttributes() const { return ReadAttributes( f_id ); }

    static recIdVec GetIndividualIDs( id_t perID );
    recIdVec GetIndividualIDs() const { return GetIndividualIDs( f_id ); }
};

inline bool recEquivalent( const recPersona& r1, const recPersona& r2 )
{
    return
        r1.f_sex  == r2.f_sex  &&
        r1.f_note == r2.f_note;
}

inline bool operator==( const recPersona& r1, const recPersona& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recPersona& r1, const recPersona& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

enum StdAttrType  // These match the create.sql file
{
    ATTR_TYPE_Unstated   = 0,
    ATTR_TYPE_Given_name = -1,
    ATTR_TYPE_Surname    = -2,
    ATTR_TYPE_Post_name  = -3,
	ATTR_TYPE_Occupation = -4,
    ATTR_TYPE_Max        = 5
};

class recAttribute : public recDb
{
public:
    id_t      f_per_id;
    id_t      f_type_id;
    wxString  f_val;
    unsigned  f_sequence;

    recAttribute() {}
    recAttribute( id_t id ) : recDb(id) { Read(); }
    recAttribute( const recAttribute& attr );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Attribute" );

    static wxString GetValue( id_t id );
	static recAttributeList ConvertStrToList( const wxString& str, id_t type = ATTR_TYPE_Given_name );
    static wxSQLite3ResultSet GetSurnameList() {
        return s_db->ExecuteQuery( 
            "SELECT val FROM Attribute WHERE type_id=-2 GROUP BY val;"
        );
    }
};

inline bool recEquivalent( const recAttribute& r1, const recAttribute& r2 )
{
    return
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_val      == r2.f_val      &&
        r1.f_sequence == r2.f_sequence;
}

inline bool operator==( const recAttribute& r1, const recAttribute& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recAttribute& r1, const recAttribute& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recAttributeType : public recDb 
{
public:
	enum ATYPE_Grp { 
		ATYPE_Grp_Unstated, ATYPE_Grp_Name, ATYPE_Grp_Title, 
		ATYPE_Grp_Occ, ATYPE_Grp_Other
	};

	ATYPE_Grp f_grp;
    wxString  f_name;

    recAttributeType() {}
    recAttributeType( id_t id ) : recDb(id) { Read(); }
    recAttributeType( const recAttributeType& at );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "AttributeType" );

    static wxString GetTypeStr( id_t id );

    static recAttributeTypeVec GetTypeList();
};

inline bool recEquivalent( const recAttributeType& r1, const recAttributeType& r2 )
{
    return
        r1.f_grp   == r2.f_grp &&
        r1.f_name == r2.f_name;
}

inline bool operator==( const recAttributeType& r1, const recAttributeType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recAttributeType& r1, const recAttributeType& r2 )
{
    return !(r1 == r2);
}

#endif // RECPERSONA_H
