/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recPersona.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Persona records.
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
#include <rec/recAttribute.h>
#include <rec/recRelationship.h>

class recPersona;
typedef std::vector< recPersona >  recPersonaVec;


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

#endif // RECPERSONA_H
