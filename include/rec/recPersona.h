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

#include <rec/recDatabase.h>
#include <rec/recReference.h>
#include <rec/recName.h>

class recPersona;
class recAttribute;
class recAttributeType;
typedef std::vector< recPersona >        recPersonaVec;
typedef std::vector< recAttribute >      recAttributeVec;
typedef std::vector< recAttributeType >  recAttributeTypeVec;

class recPersona : public recDb
{
public:
    Sex      f_sex;
    idt      f_ref_id;
    wxString f_note;

    recPersona() {}
    recPersona( idt id ) : recDb(id) { Read(); }
    recPersona( const recPersona& persona );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Persona" );

    static idt GetDefaultNameID( idt id );
    idt GetDefaultNameID() const { return GetDefaultNameID( f_id ); }
    static wxString GetNameStr( idt id ) 
        { return recName::GetNameStr( GetDefaultNameID( id ) ); }
    wxString GetNameStr() const { return GetNameStr( f_id ); }

    static recAttributeVec ReadAttributes( idt perID );
    recAttributeVec ReadAttributes() const { return ReadAttributes( f_id ); }
    static recNameVec ReadNames( idt perID );
    recNameVec ReadNames() const { return ReadNames( f_id ); }

    static recIdVec GetIndividualIDs( idt perID );
    recIdVec GetIndividualIDs() const { return GetIndividualIDs( f_id ); }
};

inline bool recEquivalent( const recPersona& r1, const recPersona& r2 )
{
    return
        r1.f_sex     == r2.f_sex     &&
        r1.f_ref_id  == r2.f_ref_id  &&
        r1.f_note    == r2.f_note;
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
    idt       f_per_id;
    idt       f_type_id;
    wxString  f_val;
    unsigned  f_sequence;

    recAttribute() {}
    recAttribute( idt id ) : recDb(id) { Read(); }
    recAttribute( const recAttribute& attr );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Attribute" );

    static wxString GetValue( idt id );

    idt FindReferenceID() const { return FindReferenceID( f_id ); }
    static idt FindReferenceID( idt eventID ) {
        return recReferenceEntity::FindReferenceID( recReferenceEntity::TYPE_Attribute, eventID );
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
        ATYPE_Grp_Unstated, ATYPE_Grp_Occ,
        ATYPE_Grp_Other
    };

    ATYPE_Grp f_grp;
    wxString  f_name;

    recAttributeType() {}
    recAttributeType( idt id ) : recDb(id) { Read(); }
    recAttributeType( const recAttributeType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "AttributeType" );

    static wxString GetTypeStr( idt id );

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
