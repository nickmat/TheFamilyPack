/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
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

#ifndef RECREFERENCE_H
#define RECREFERENCE_H

#include <wx/vector.h>
#include <rec/recDatabase.h>

class recReferenceEntity;
typedef wxVector< recReferenceEntity >  recRefEntVec;

class recReference : public recDb
{
public:
    wxString f_title;
    wxString f_statement;

    recReference() {}
    recReference( id_t id ) : recDb(id) { Read(); }
    recReference( const recReference& ref );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Reference" );

    recRefEntVec ReadReferenceEntitys();
    static wxSQLite3ResultSet GetTitleList();
};

inline bool recEquivalent( const recReference& r1, const recReference& r2 )
{
    return
        r1.f_title  == r2.f_title  &&
        r1.f_statement == r2.f_statement;
}

inline bool operator==( const recReference& r1, const recReference& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recReference& r1, const recReference& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recReferenceEntity : public recDb 
{
public:
    enum Type {
        TYPE_Unstated,   // 0
        TYPE_Source,     // 1
        TYPE_Event,      // 2
        TYPE_Place,      // 3
        TYPE_Date,       // 4
        TYPE_Name,       // 5
        TYPE_Persona,    // 6
        TYPE_Attribute,  // 7
        TYPE_MAX         // 8
    };
    static const wxString sm_typeStr[TYPE_MAX];

    id_t     f_ref_id;
    Type     f_entity_type;
    id_t     f_entity_id;
    unsigned f_sequence;

    recReferenceEntity() {}
    recReferenceEntity( id_t id ) : recDb(id) { Read(); }
    recReferenceEntity( const recReferenceEntity& re );

	void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "ReferenceEntity" );

    wxString GetTypeStr() { return sm_typeStr[f_entity_type]; }
    static wxString GetTypeStr( Type etype ) { return sm_typeStr[etype]; }
};

inline bool recEquivalent( const recReferenceEntity& r1, const recReferenceEntity& r2 )
{
    return
        r1.f_ref_id      == r2.f_ref_id      &&
        r1.f_entity_type == r2.f_entity_type &&
        r1.f_entity_id   == r2.f_entity_id;
}

inline bool operator==( const recReferenceEntity& r1, const recReferenceEntity& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recReferenceEntity& r1, const recReferenceEntity& r2 )
{
    return !(r1 == r2);
}

#endif // RECREFERENCE_H
