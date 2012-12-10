/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family, FamilyIndividual and Individual records.
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
#include <rec/recPersona.h>

class recIndividual;
typedef std::vector< recIndividual >  recIndividualList;
typedef std::vector< recIndividual >  recIndividualVec;
class recFamily;
typedef std::vector< recFamily >  recFamilyVec;
class recFamilyIndividual;
typedef std::vector< recFamilyIndividual >  recFamIndVec;
class recIndRelationship;
typedef std::vector< recIndRelationship >  recIndRelVec;

//============================================================================
//-------------------------[ recIndividual ]----------------------------------
//============================================================================

enum {
    recInd_FILTER_SexAll        = 0,
    recInd_FILTER_SexUnstated   = 0x0001,
    recInd_FILTER_SexMale       = 0x0002,
    recInd_FILTER_SexFemale     = 0x0004,
    recInd_FILTER_SexUnknown    = 0x0008,
    recInd_FILTER_SexMalePlus   = (recInd_FILTER_SexMale | recInd_FILTER_SexUnstated | recInd_FILTER_SexUnknown),
    recInd_FILTER_SexFemalePlus = (recInd_FILTER_SexFemale | recInd_FILTER_SexUnstated | recInd_FILTER_SexUnknown)
};

class recIndividual : public recDb
{
public:
    wxString f_surname;
    wxString f_given;
    wxString f_epitaph;
    idt      f_fam_id;
    idt      f_per_id;

    recIndividual() {}
    recIndividual( idt id ) : recDb(id) { Read(); }
    recIndividual( const recIndividual& ind );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Individual" );

    static wxString GetIdStr( idt indID ) { return wxString::Format( "I"ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recIndividualVec ReadVec( unsigned sexfilter = recInd_FILTER_SexAll );

    bool ReadPersona( idt perID );

    void UpdateDateEpitaph();
    void UpdateNames();
    void UpdateDefaultFamily();
    void Update();
    static void Update( idt indID );
    wxString GetFullName() { return f_given + " " + f_surname; }

    static idt GetDefaultFamily( idt id ) {
        if( id == 0 ) return 0;
        return ExecuteID( "SELECT fam_id FROM Individual WHERE id="ID";", id );
    }
    static idt GetPersona( idt indID ) {
        if( indID == 0 ) return 0;
        return ExecuteID( "SELECT per_id FROM Individual WHERE id="ID";", indID );
    }
    idt GetPersona() const { return f_per_id; }


    static wxString GetFullName( idt id );
    static wxString GetSurname( idt id );
    static wxString GetDateEpitaph( idt id );
    static wxString GetFullNameEpitaph( idt id );
    static Sex GetSex( idt id ) { return recPersona::GetSex( GetPersona( id ) ); }
    Sex GetSex() { return recPersona::GetSex( f_per_id ); }

    static idt FindEvent( idt indID, idt roleID );
    idt FindEvent( idt roleID ) const { return FindEvent( f_id, roleID ); }
    static idt FindEvent( idt indID, recEventType::ETYPE_Grp grp );
    idt FindEvent( recEventType::ETYPE_Grp grp ) const { return FindEvent( f_id, grp ); }

    idt GetBirthEvent() const { return FindEvent( recEventTypeRole::ROLE_Birth_Born ); }
    idt GetNrBirthEvent() const { return FindEvent( recEventType::ETYPE_Grp_Nr_Birth ); }
    idt GetDeathEvent() const { return FindEvent( recEventTypeRole::ROLE_Death_Died ); }
    idt GetNrDeathEvent() const { return FindEvent( recEventType::ETYPE_Grp_Nr_Death ); }
    static idt GetBirthEvent( idt id ) { return FindEvent( id, recEventTypeRole::ROLE_Birth_Born ); }
    static idt GetNrBirthEvent( idt id ) { return FindEvent( id, recEventType::ETYPE_Grp_Nr_Birth ); }
    static idt GetDeathEvent( idt id ) { return FindEvent( id, recEventTypeRole::ROLE_Death_Died ); }
    static idt GetNrDeathEvent( idt id ) { return FindEvent( id, recEventType::ETYPE_Grp_Nr_Death ); }

    static recFamilyVec GetFamilyList( idt ind );
    recFamilyVec GetFamilyList() const { return GetFamilyList( f_id ); }
    static recFamilyVec GetParentList( idt indID );
    recFamilyVec GetParentList() const { return GetParentList( f_id ); }

    static recIndEventVec GetEvents( idt indID );
    recIndEventVec GetEvents() const { return GetEvents( f_id ); }

    wxSQLite3Table GetRefEventsTable() const { return GetRefEventsTable( f_per_id ); }
    static wxSQLite3Table GetRefEventsTable( idt perID );

    wxSQLite3Table GetReferencesTable() const { return GetReferencesTable( f_per_id ); }
    static wxSQLite3Table GetReferencesTable( idt perID );

    wxArrayString GetEventIdStrList( idt etrID ) const { GetEventIdStrList( f_per_id, etrID ); }
    static wxArrayString GetEventIdStrList( idt perID, idt etrID );

    static wxSQLite3ResultSet GetSurnameList() {
        return s_db->ExecuteQuery(
            "SELECT surname FROM Individual GROUP BY surname;"
        );
    }
    static wxSQLite3ResultSet GetNameList( wxString name );
    static wxSQLite3Table GetNameTable( Sex sex );

    static recIndRelVec GetIndRelationships( idt indID );
    recIndRelVec GetIndRelationships() const { return GetIndRelationships( f_id ); }

    static int GetMaxEventSeqNumber( idt indID );
    int GetMaxEventSeqNumber() const { return GetMaxEventSeqNumber( f_id ); }

    static bool CreateMissingFamilies();

    // Delete Individual and remove all references to it.
    void DeleteFromDb();
    static void DeleteFromDb( idt id );
};

inline bool recEquivalent( const recIndividual& r1, const recIndividual& r2 )
{
    return
        r1.f_surname     == r2.f_surname      &&
        r1.f_given       == r2.f_given        &&
        r1.f_epitaph     == r2.f_epitaph      &&
        r1.f_fam_id      == r2.f_fam_id       &&
        r1.f_per_id      == r2.f_per_id;
}

inline bool operator==( const recIndividual& r1, const recIndividual& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recIndividual& r1, const recIndividual& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recFamily ]--------------------------------------
//============================================================================

class recFamily : public recDb
{
public:
    idt     f_husb_id;
    idt     f_wife_id;

    recFamily() {}
    recFamily( idt id ) : recDb(id) { Read(); }
    recFamily( const recFamily& family );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Family" );

    idt GetId() const { return f_id; }
    idt GetHusbId() const { return f_husb_id; }
    idt GetWifeId() const { return f_wife_id; }
    static wxString GetIdStr( idt indID ) { return wxString::Format( "F"ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    bool Decode( const wxString& str );
    void SetMemberDefault();

    idt GetMarriageEvent_() const;
    static idt GetUnionEvent( idt famID );
    idt GetUnionEvent() const { return GetUnionEvent( f_id ); }

    bool ReadParents( idt indID );
    static recIndividualList GetChildren( idt famID );
    recIndividualList GetChildren() const { return GetChildren( f_id ); }
    static recIdVec GetChildrenIds( idt famID );
    recIdVec GetChildrenIds() const { return GetChildrenIds( f_id ); }
    static int GetChildNextSequence( idt famID );
    static int GetParentNextSequence( idt indID );
    recFamIndVec GetChildLinks() { return GetChildLinks( f_id ); }
    static recFamIndVec GetChildLinks( idt famID );
    static recFamilyEventVec GetEvents( idt famID );
    recFamilyEventVec GetEvents() const { return GetEvents( f_id ); }

    wxArrayString GetMarriageEventTable() const;

    static int GetMaxEventSeqNumber( idt famID );
    int GetMaxEventSeqNumber() const { return GetMaxEventSeqNumber( f_id ); }

    static void RemoveFromEvents( idt famID, idt indID );
    void RemoveFromEvents( idt indID ) const { RemoveFromEvents( f_id, indID ); }
};

inline bool recEquivalent( const recFamily& r1, const recFamily& r2 )
{
    return
        r1.f_husb_id  == r2.f_husb_id &&
        r1.f_wife_id  == r2.f_wife_id;
}

inline bool operator==( const recFamily& r1, const recFamily& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recFamily& r1, const recFamily& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recFamilyIndividual ]----------------------------
//============================================================================

class recFamilyIndividual : public recDb
{
public:
    idt f_fam_id;
    idt f_ind_id;
    int f_seq_child;
    int f_seq_parent;

    recFamilyIndividual() {}
    recFamilyIndividual( idt id ) : recDb(id) { Read(); }
    recFamilyIndividual( const recFamilyIndividual& fi );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "FamilyIndividual" );

    idt fGetFamID() const { return f_fam_id; }
    idt fGetIndID() const { return f_ind_id; }
    int fGetSeqChild() const { return f_seq_child; }
    int fSetSeqParent() const { return f_seq_parent; }

    void fSetFamID( idt famID ) { f_fam_id = famID; } 
    void fSetIndID( idt indID ) { f_ind_id = indID; } 
    void fSetSeqChild( int seq ) { f_seq_child = seq; }
    void fSetSeqParent( int seq ) { f_seq_parent = seq; }

    bool Find();
};

inline bool recEquivalent( const recFamilyIndividual& r1, const recFamilyIndividual& r2 )
{
    return
        r1.f_fam_id     == r2.f_fam_id     &&
        r1.f_ind_id     == r2.f_ind_id     &&
        r1.f_seq_child  == r2.f_seq_child  &&
        r1.f_seq_parent == r2.f_seq_parent;
}

inline bool operator==( const recFamilyIndividual& r1, const recFamilyIndividual& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recFamilyIndividual& r1, const recFamilyIndividual& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//-------------------------[ recIndRelationship ]-----------------------------
//============================================================================


// This is not based on a table, but is created from the recFamily class
class recIndRelationship
{
public:
    enum Type {
        IRT_Unstated = 0,
        IRT_Father,
        IRT_Mother,
        IRT_Child,
        IRT_MAX
    };

    recIndRelationship() {}
    recIndRelationship( idt indID ) 
        : m_fam_id(0), m_ind1_id(indID), m_ind2_id(0), m_type(IRT_Unstated) {}

    idt GetFamily() const { return m_fam_id; }
    idt GetIndividual1() const { return m_ind1_id; }
    idt GetIndividual2() const { return m_ind2_id; }
    Type GetType() const { return m_type; }
    wxString GetTypeStr() const;

    void SetFamily( idt famID ) { m_fam_id = famID; }
    void SetIndividual1( idt indID ) { m_ind1_id = indID; }
    void SetIndividual2( idt indID ) { m_ind2_id = indID; }
    void SetType( Type type ) { m_type = type; }

private:
    idt  m_fam_id;
    idt  m_ind1_id;
    idt  m_ind2_id;
    Type m_type;

    static const wxString s_TypeStr[IRT_MAX];
};

#endif // RECINDIVIDUAL_H
