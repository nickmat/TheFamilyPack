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
class recName;
class recNameStyle;
class recNameType;
typedef wxVector< recPersona >  recPersonaList;
typedef wxVector< recAttribute >  recAttributeList;
typedef wxVector< recAttributeType >  recAttributeTypeVec;
typedef wxVector< recName >  recNameList;
typedef wxVector< recNameStyle >  recNameStyleVec;
typedef wxVector< recNameType >  recNameTypeVec;

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
	static recNameList ReadNames( id_t perID );
    recNameList ReadNames() const { return ReadNames( f_id ); }

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

enum recStdAttrType  // These match the create.sql file
{
    ATTR_TYPE_Unstated   = 0,
	ATTR_TYPE_Occupation = -1,
    ATTR_TYPE_Max        = 2
};

class recAttribute : public recDb
{
public:
    id_t      f_per_id;
    id_t      f_type_id;
    wxString  f_val;

    recAttribute() {}
    recAttribute( id_t id ) : recDb(id) { Read(); }
    recAttribute( const recAttribute& attr );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Attribute" );

    static wxString GetValue( id_t id );
//	static recAttributeList ConvertStrToList( const wxString& str, id_t type );
};

inline bool recEquivalent( const recAttribute& r1, const recAttribute& r2 )
{
    return
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_val      == r2.f_val;
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
		ATYPE_Grp_Unstated, ATYPE_Grp_Occ, 
        ATYPE_Grp_Other
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

//----------------------------------------------------------

enum recStdNameType  // These match the create.sql file
{
    NAME_TYPE_Unstated   = 0,
    NAME_TYPE_Given_name = -1,
    NAME_TYPE_Surname    = -2,
    NAME_TYPE_Post_name  = -3,
    NAME_TYPE_Max        = 4
};

class recName : public recDb
{
public:
    id_t      f_per_id;
    id_t      f_type_id;
    wxString  f_val;
    id_t      f_style_id;
    unsigned  f_sequence;

    recName() {}
    recName( id_t id ) : recDb(id) { Read(); }
    recName( const recName& attr );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Name" );

    static wxString GetValue( id_t id );
	static recNameList ConvertStrToList( const wxString& str, id_t type = NAME_TYPE_Given_name );
    static wxSQLite3ResultSet GetSurnameList() {
        return s_db->ExecuteQuery( 
            "SELECT val FROM Name WHERE type_id=-2 GROUP BY val;"
        );
    }
};

inline bool recEquivalent( const recName& r1, const recName& r2 )
{
    return
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_val      == r2.f_val      &&
        r1.f_style_id == r2.f_style_id &&
        r1.f_sequence == r2.f_sequence;
}

inline bool operator==( const recName& r1, const recName& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recName& r1, const recName& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recNameStyle : public recDb 
{
public:
    wxString  f_name;

    recNameStyle() {}
    recNameStyle( id_t id ) : recDb(id) { Read(); }
    recNameStyle( const recNameStyle& at );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NameStyle" );

    static wxString GetStyleStr( id_t id );

    static recNameStyleVec GetStyleList();
};

inline bool recEquivalent( const recNameStyle& r1, const recNameStyle& r2 )
{
    return
        r1.f_name == r2.f_name;
}

inline bool operator==( const recNameStyle& r1, const recNameStyle& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recNameStyle& r1, const recNameStyle& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recNameType : public recDb 
{
public:
	enum NTYPE_Grp { 
		NTYPE_Grp_Unstated, NTYPE_Grp_Name, NTYPE_Grp_Title, 
		NTYPE_Grp_Other
	};

	NTYPE_Grp f_grp;
    wxString  f_name;

    recNameType() {}
    recNameType( id_t id ) : recDb(id) { Read(); }
    recNameType( const recNameType& at );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NameType" );

    static wxString GetTypeStr( id_t id );

    static recNameTypeVec GetTypeList();
};

inline bool recEquivalent( const recNameType& r1, const recNameType& r2 )
{
    return
        r1.f_grp   == r2.f_grp &&
        r1.f_name == r2.f_name;
}

inline bool operator==( const recNameType& r1, const recNameType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recNameType& r1, const recNameType& r2 )
{
    return !(r1 == r2);
}

#endif // RECPERSONA_H
