/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 ~ 2021, Nick Matthews.
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

#include <vector>

#include <rec/recDatabase.h>

class recReferenceEntity;
typedef std::vector< recReferenceEntity >  recRefEntVec;

//-----------------------------------------------------
//      recReferenceEntity
//-----------------------------------------------------


class recReferenceEntity : public recDb
{
public:
    enum Type {
        TYPE_Unstated      = 0,
        TYPE_Source        = 1,
        TYPE_Spare3        = 2, // Was Event[a]
        TYPE_Place         = 3,
        TYPE_Date          = 4,
        TYPE_Spare2        = 5, // Was Relationship
        TYPE_Spare         = 6, // Was Attribute
        TYPE_Name          = 7,
        TYPE_MAX           = 8
    };
    static const wxString sm_typeStr[TYPE_MAX];

    idt      f_ref_id;
    Type     f_entity_type;
    idt      f_entity_id;
    int      f_sequence;

    recReferenceEntity() {}
    recReferenceEntity( idt id ) : recDb(id) { Read(); }
    recReferenceEntity( const recReferenceEntity& re );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "ReferenceEntity" );

    idt FGetRefID() const { return f_ref_id; }
    Type FGetEntityType() const { return f_entity_type; }
    idt FGetEntityID() const { return f_entity_id; }
    int FGetSequence() const { return f_sequence; }

    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetEntityType( Type etype ) { f_entity_type = etype; }
    void FSetEntityID( idt entID ) { f_entity_id = entID; }
    void FSetSequence( int seq ) { f_sequence = seq; }

    static void Create( idt refID, Type type, idt entID, int* pseq = NULL );
    static void Delete( Type type, idt entityID );

    wxString GetTypeStr() const { return sm_typeStr[f_entity_type]; }
    static wxString GetTypeStr( Type etype ) { return sm_typeStr[etype]; }

    wxString GetEntityIdStr() const; 
    wxString GetEntityStr() const; 

    static idt FindReferenceID( Type type, idt entityID );

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
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

//-----------------------------------------------------
//      recReference
//-----------------------------------------------------

class recReference : public recDb
{
public:
    idt      f_higher_id;
    wxString f_title;
    wxString f_statement;
    idt      f_res_id;
    wxString f_user_ref;

    recReference() {}
    recReference( idt id ) : recDb(id) { Read(); }
    recReference( const recReference& ref );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Reference" );
    bool Equivalent( const recReference& r2 ) const;

    idt FGetHigherId() const { return f_higher_id; }
    wxString FGetTitle() const { return f_title; }
    wxString FGetStatement() const { return f_statement; }
    idt FGetResId() const { return f_res_id; }
    wxString FGetUserRef() const { return f_user_ref; }

    idt FSetHigherId( idt refID ) { f_higher_id = refID; }
    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetStatement( const wxString& statement ) { f_statement = statement; }
    idt FSetResId( idt resID ) { f_res_id = resID; }
    void FSetUserRef( const wxString& ur ) { f_user_ref = ur; }

    static wxString GetIdStr( idt refID ) { return wxString::Format( "R" ID, refID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetTitle( idt refID );

    recRefEntVec ReadReferenceEntitys();
    static wxSQLite3Table GetTitleList();
    static wxSQLite3Table GetTitleList( idt offset, int limit );

    static int GetNextEntitySequence( idt refID );
    int GetNextEntitySequence() const { return GetNextEntitySequence( f_id ); }

    static recIdVec GetCitationList( idt refID );
    recIdVec GetCitationList() const { return GetCitationList( f_id ); }

    static recIdVec GetPersonaList( idt refID );
    recIdVec GetPersonaList() const { return GetPersonaList( f_id ); }
    static int GetPersonaCount( idt refID );

    static recIdVec GetMediaList( idt refID );
    recIdVec GetMediaList() const { return GetMediaList( f_id ); }
    static int GetMediaCount( idt refID );

    static recIdVec GetEventaList( idt refID );
    recIdVec GetEventaList() const { return GetEventaList( f_id ); }
    static int GetEventaCount( idt refID );

    static recIdVec GetIdVecForEntity( idt refID, recReferenceEntity::Type type );

    static recIdVec GetPlaceIdVec( idt refID ) 
        { return GetIdVecForEntity( refID, recReferenceEntity::TYPE_Place ); }
    recIdVec GetPlaceIdVec() const { return GetPlaceIdVec( f_id ); }

    static recIdVec GetDateIdVec( idt refID ) 
        { return GetIdVecForEntity( refID, recReferenceEntity::TYPE_Date ); }
    recIdVec GetDateIdVec() const { return GetDateIdVec( f_id ); }

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};

inline bool operator==( const recReference& r1, const recReference& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recReference& r1, const recReference& r2 )
{
    return !(r1 == r2);
}

#endif // RECREFERENCE_H
