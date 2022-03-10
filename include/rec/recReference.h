/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

//============================================================================
//---------------------------[ recReferenceEntity ]---------------------------
//============================================================================


class recReferenceEntity : public recDbT< recReferenceEntity>
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
    static constexpr const char* s_tablename = "ReferenceEntity";

    idt      f_ref_id;
    Type     f_entity_type;
    idt      f_entity_id;
    int      f_sequence;

    recReferenceEntity() : f_ref_id(0), f_entity_type(TYPE_Unstated), f_entity_id(0), f_sequence(0) {}
    recReferenceEntity( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recReferenceEntity( const recReferenceEntity& re );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recReferenceEntity& r2 ) const;

    idt FGetRefID() const { return f_ref_id; }
    Type FGetEntityType() const { return f_entity_type; }
    idt FGetEntityID() const { return f_entity_id; }
    int FGetSequence() const { return f_sequence; }

    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetEntityType( Type etype ) { f_entity_type = etype; }
    void FSetEntityID( idt entID ) { f_entity_id = entID; }
    void FSetSequence( int seq ) { f_sequence = seq; }

    static void Create( idt refID, Type type, idt entID, int* pseq = NULL );
    static void DeleteType( Type type, idt entityID );

    wxString GetTypeStr() const { return sm_typeStr[f_entity_type]; }
    static wxString GetTypeStr( Type etype ) { return sm_typeStr[etype]; }

    wxString GetEntityIdStr() const; 
    wxString GetEntityStr( const wxString& dbname = "Main" ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};


//============================================================================
//------------------------------[ recReference ]------------------------------
//============================================================================


class recReference : public recDbT<recReference>
{
public:
    static constexpr const char* s_tablename = "Reference";

    idt      f_higher_id;
    wxString f_title;
    wxString f_statement;
    idt      f_res_id;
    wxString f_user_ref;
    wxString f_uid;
    long     f_changed;

    recReference() : f_higher_id(0), f_res_id(0), f_changed(0) {}
    recReference( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recReference( const recReference& ref );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recReference& r2 ) const;

    idt FGetHigherId() const { return f_higher_id; }
    wxString FGetTitle() const { return f_title; }
    wxString FGetStatement() const { return f_statement; }
    idt FGetResId() const { return f_res_id; }
    wxString FGetUserRef() const { return f_user_ref; }
    wxString FGetUid() const { return f_uid; }
    long FGetChanged() const { return f_changed; }

    void FSetHigherId( idt refID ) { f_higher_id = refID; }
    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetStatement( const wxString& statement ) { f_statement = statement; }
    void FSetResId( idt resID ) { f_res_id = resID; }
    void FSetUserRef( const wxString& ur ) { f_user_ref = ur; }
    void FSetUid( const wxString& uid ) { f_uid = uid; }
    void FSetChanged( long jdn ) { f_changed = jdn; }

    static wxString GetIdStr( idt refID ) { return wxString::Format( "R" ID, refID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetTitle( idt refID, const wxString& dbname = "Main" );

    recRefEntVec ReadReferenceEntitys( const wxString& dbname = "Main" );
    static wxSQLite3Table GetTitleList( const wxString& dbname = "Main" );
    static wxSQLite3Table GetTitleList( idt offset, int limit, const wxString& dbname = "Main" );

    static int GetNextEntitySequence( idt refID );
    int GetNextEntitySequence() const { return GetNextEntitySequence( f_id ); }

    static recIdVec GetCitationList( idt refID, const wxString& dbname = "Main" );
    recIdVec GetCitationList( const wxString& dbname = "Main" ) const {
        return GetCitationList( f_id, dbname ); }

    static recIdVec GetPersonaList( idt refID, const wxString& dbname = "Main" );
    recIdVec GetPersonaList( const wxString& dbname = "Main" ) const {
        return GetPersonaList( f_id, dbname ); }
    static int GetPersonaCount( idt refID, const wxString& dbname = "Main" );

    static recIdVec GetMediaList( idt refID, const wxString& dbname = "Main" );
    recIdVec GetMediaList( const wxString& dbname = "Main" ) const {
        return GetMediaList( f_id, dbname ); }
    static int GetMediaCount( idt refID, const wxString& dbname = "Main" );

    static recIdVec GetEventaList( idt refID, const wxString& dbname = "Main" );
    recIdVec GetEventaList( const wxString& dbname = "Main" ) const {
        return GetEventaList( f_id, dbname ); }
    static int GetEventaCount( idt refID, const wxString& dbname = "Main" );

    static recIdVec GetIdVecForEntity(
        idt refID, recReferenceEntity::Type type, const wxString& dbname = "Main" );

    static recIdVec GetPlaceIdVec( idt refID, const wxString& dbname = "Main" )
        { return GetIdVecForEntity( refID, recReferenceEntity::TYPE_Place, dbname ); }
    recIdVec GetPlaceIdVec( const wxString& dbname = "Main" ) const {
        return GetPlaceIdVec( f_id, dbname ); }

    static recIdVec GetDateIdVec( idt refID, const wxString& dbname = "Main" )
        { return GetIdVecForEntity( refID, recReferenceEntity::TYPE_Date, dbname ); }
    recIdVec GetDateIdVec( const wxString& dbname = "Main" ) const {
        return GetDateIdVec( f_id, dbname ); }

    wxString GetChangedDate() const;
    static wxString GetChangedDate( idt refID, const wxString& dbname );

    static idt FindUid(
        idt refID, const wxString& source_db, const wxString& target_db = "Main" );
    idt FindUid( const wxString& target_db = "Main" ) const;

    static void Renumber( idt fromID, idt toID );
    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};


#endif // RECREFERENCE_H
