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
#include <rec/recEvent.h>

class recPersona;
class recAttribute;
class recAttributeType;
class recRelationship;
typedef std::vector< recPersona >        recPersonaVec;
typedef std::vector< recAttribute >      recAttributeVec;
typedef std::vector< recAttributeType >  recAttributeTypeVec;
typedef std::vector< recRelationship >   recRelationshipVec;

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

    static wxString GetIdStr( idt perID ) { return wxString::Format( "Pa"ID, perID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt GetDefaultNameID( idt id );
    idt GetDefaultNameID() const { return GetDefaultNameID( f_id ); }
    static wxString GetNameStr( idt id ) 
        { return recName::GetNameStr( GetDefaultNameID( id ) ); }
    wxString GetNameStr() const { return GetNameStr( f_id ); }

    static recNameVec ReadNames( idt perID );
    recNameVec ReadNames() const { return ReadNames( f_id ); }

    static recAttributeVec ReadAttributes( idt perID );
    recAttributeVec ReadAttributes() const { return ReadAttributes( f_id ); }

    static recEventPersonaVec ReadEventPersonas( idt perID );
    recEventPersonaVec ReadEventPersonas() const { return ReadEventPersonas( f_id ); }

    static recRelationshipVec ReadRelationships( idt perID );
    recRelationshipVec ReadRelationships() { return ReadRelationships( f_id ); }

    static recIdVec GetIndividualIDs( idt perID );
    recIdVec GetIndividualIDs() const { return GetIndividualIDs( f_id ); }
    static wxString GetIndividualIdStr( idt perID );
    wxString GetIndividualIdStr() const { return GetIndividualIdStr( f_id ); }
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
    enum AGrp { 
        AGRP_Unstated,
        AGRP_Occ,
        AGRP_Other
    };
    enum AType  // These match the create.sql file
    {
        ATYPE_Unstated   = 0,
        ATYPE_Occupation = -1,
        ATYPE_Max        = 2
    };

    AGrp     f_grp;
    wxString f_name;

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

//----------------------------------------------------------

class recRelationship : public recDb
{
public:
    idt       f_per1_id;
    idt       f_per2_id;
    wxString  f_descrip;

    recRelationship() {}
    recRelationship( idt id ) : recDb(id) { Read(); }
    recRelationship( const recRelationship& rel );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Relationship" );

    static wxString GetIdStr( idt relID );
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetValue1Str() const;
    wxString GetValue2Str() const;
    static wxString GetValue1Str( idt relID );
    static wxString GetValue2Str( idt relID );

    wxString GetRelOfPersonaStr( idt perID ) const;
    static wxString GetRelOfPersonaStr( idt perID, idt relID );
};

inline bool recEquivalent( const recRelationship& r1, const recRelationship& r2 )
{
    return
        r1.f_per1_id == r2.f_per1_id &&
        r1.f_per2_id == r2.f_per2_id &&
        r1.f_descrip == r2.f_descrip;
}

inline bool operator==( const recRelationship& r1, const recRelationship& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recRelationship& r1, const recRelationship& r2 )
{
    return !(r1 == r2);
}

#endif // RECPERSONA_H
