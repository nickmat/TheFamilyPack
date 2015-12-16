/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family, FamilyIndividual and Individual records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 - 2015, Nick Matthews.
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
#include <rec/recFamEvent.h>
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
    Sex      f_sex;
    idt      f_fam_id;
    wxString f_note;
    int      f_privacy;
    wxString f_name;
    wxString f_surname;
    wxString f_epitaph;

    recIndividual() {}
    recIndividual( idt id ) : recDb(id) { Read(); }
    recIndividual( const recIndividual& ind );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Individual" );

    static wxString GetIdStr( idt indID ) { return wxString::Format( "I"ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }
    static idt GetIdFromStr( const wxString& str ) { return recIdFromStr( "I", str ); }
    static recIdVec GetIdVecFromStr( const wxString& str ) { return recIdVecFromStr( "I", str ); }

    Sex FGetSex() const { return f_sex; }
    idt FGetFamID() const { return f_fam_id; }
    wxString FGetNote() const { return f_note; }
    int FGetPrivacy() const { return f_privacy; }
    wxString FGetName() const { return f_name; }
    wxString FGetSurname() const { return f_surname; }
    wxString FGetEpitaph() const { return f_epitaph; }

    void FSetSex( Sex sex ) { f_sex = sex; }
    void FSetFamID( idt famID ) { f_fam_id = famID; }
    void FSetNote( const wxString& note ) { f_note = note; }
    void FSetPrivacy( int privacy ) { f_privacy = privacy; }
    void FSetName( const wxString& name ) { f_name = name; }
    void FSetSurname( const wxString& surname ) { f_surname = surname; }
    void FSetEpitaph( const wxString& epitaph ) { f_epitaph = epitaph; }

    static Sex GetSex( idt indID );
    static idt GetFamilyID( idt indID );
    static int GetPrivacy( idt indID );
    static wxString GetName( idt indID );
    static wxString GetSurname( idt indID );
    static wxString GetEpitaph( idt indID );

    static recIndividualVec ReadVec( unsigned sexfilter = recInd_FILTER_SexAll );
    static recIdVec GetIdVec();

    static idt GetNameID( idt indID ) { return recName::GetDefaultNameID( indID, 0 ); }
    idt GetNameID() const { return recName::GetDefaultNameID( f_id, 0 ); }
    static wxString GetNameStr( idt indID ) { return recName::GetDefaultNameStr( indID, 0 ); }
    wxString GetNameStr() const { return recName::GetDefaultNameStr( f_id, 0 ); }
    static wxString GetDescriptionStr( idt indID );
    wxString GetDescriptionStr() const { return GetDescriptionStr( f_id ); }


    static recNameVec GetNames( idt indID ) { return recName::GetNames( indID, 0 ); }
    recNameVec GetNames() const { return recName::GetNames( f_id, 0 ); }

    void UpdateEpitaph();
    static void UpdateEpitaph( idt indID );
    void UpdateNames();
    void UpdateDefaultFamily();
    void Update();
    static void Update( idt indID );

    static idt FindEvent( idt indID, idt roleID );
    idt FindEvent( idt roleID ) const { return FindEvent( f_id, roleID ); }
    static idt FindGroupEvent( idt indID, recET_GRP grp );
    idt FindGroupEvent( recET_GRP grp ) const { return FindGroupEvent( f_id, grp ); }

    static recIdVec FindEvents( idt indID, recET_GRP grp );
    recIdVec FindEvents( recET_GRP grp ) const { return FindEvents( f_id, grp ); }

    static idt GetPersonalEvent( idt indID, idt etID );
    idt GetPersonalEvent( idt etID ) const { return GetPersonalEvent( f_id, etID ); }

    idt GetBirthEvent() const { return FindGroupEvent( recET_GRP_Birth ); }
    idt GetNrBirthEvent() const { return FindGroupEvent( recET_GRP_NrBirth ); }
    idt GetDeathEvent() const { return FindGroupEvent( recET_GRP_Death ); }
    idt GetNrDeathEvent() const { return FindGroupEvent( recET_GRP_NrDeath ); }
    static idt GetBirthEvent( idt id ) { return FindGroupEvent( id, recET_GRP_Birth ); }
    static idt GetNrBirthEvent( idt id ) { return FindGroupEvent( id, recET_GRP_NrBirth ); }
    static idt GetDeathEvent( idt id ) { return FindGroupEvent( id, recET_GRP_Death ); }
    static idt GetNrDeathEvent( idt id ) { return FindGroupEvent( id, recET_GRP_NrDeath ); }

    static recFamilyVec GetFamilyList( idt indID );
    recFamilyVec GetFamilyList() const { return GetFamilyList( f_id ); }
    static recFamilyVec GetParentList( idt indID );
    recFamilyVec GetParentList() const { return GetParentList( f_id ); }

    static recIndEventVec GetEvents( idt indID, recEventOrder order = recEO_DatePt );
    recIndEventVec GetEvents( recEventOrder order = recEO_DatePt ) const
        { return GetEvents( f_id, order ); }

    wxSQLite3ResultSet GetEventaSet() const { return GetEventaSet( f_id ); }
    static wxSQLite3ResultSet GetEventaSet( idt indID );

    wxSQLite3ResultSet GetReferenceSet() const { return GetReferenceSet( f_id ); }
    static wxSQLite3ResultSet GetReferenceSet( idt indID );

    static wxSQLite3ResultSet GetNameSet( wxString name );
    static wxSQLite3ResultSet GetNameSet( Sex sex );
    static wxSQLite3ResultSet GetSurnameSet();

    static recIndRelVec GetIndRelationships( idt indID );
    recIndRelVec GetIndRelationships() const { return GetIndRelationships( f_id ); }

    static int GetMaxEventSeqNumber( idt indID );
    int GetMaxEventSeqNumber() const { return GetMaxEventSeqNumber( f_id ); }

    static bool CreateMissingFamilies();

    // Delete Individual and remove all references to it.
    void RemoveFromDatabase();
    static void RemoveFromDatabase( idt id );
};

inline bool recEquivalent( const recIndividual& r1, const recIndividual& r2 )
{
    return
        r1.f_sex     == r2.f_sex     &&
        r1.f_fam_id  == r2.f_fam_id  &&
        r1.f_note    == r2.f_note    &&
        r1.f_privacy == r2.f_privacy &&
        r1.f_name    == r2.f_name    &&
        r1.f_surname == r2.f_surname &&
        r1.f_epitaph == r2.f_epitaph;
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

    idt FGetHusbID() const { return f_husb_id; }
    idt FGetWifeID() const { return f_wife_id; }

    void FSetHusbID( idt hID ) { f_husb_id = hID; }
    void FSetWifeID( idt wID ) { f_wife_id = wID; }

    static wxString GetIdStr( idt indID ) { return wxString::Format( "F"ID, indID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    recIdVec GetCoupleAsIdVec() const;
    static recIdVec GetCoupleAsIdVec( idt famID );

    static recIdVec GetFamilyIdVec();
    static recFamilyVec GetFamilyVec();

    bool Decode( const wxString& str );

    static idt GetUnionEvent( idt famID );
    idt GetUnionEvent() const { return GetUnionEvent( f_id ); }

    idt GetSpouseID( idt indID ) const;
    static idt Find( idt ind1ID, idt ind2ID );
    void Find() { f_id = Find( f_husb_id, f_wife_id ); Read(); }
    static recIdVec FindVec( const recIdVec& ind1IDs, const recIdVec& ind2IDs );

    bool ReadParents( idt indID );
    static recIndividualList GetChildren( idt famID );
    recIndividualList GetChildren() const { return GetChildren( f_id ); }
    static recIdVec GetChildrenIds( idt famID );
    recIdVec GetChildrenIds() const { return GetChildrenIds( f_id ); }
    static int GetChildCount( idt famID );
    int GetChildCount() const { return GetChildCount( f_id ); }
    static int GetChildNextSequence( idt famID );
    static int GetParentNextSequence( idt indID );
    recFamIndVec GetChildLinks() { return GetChildLinks( f_id ); }
    static recFamIndVec GetChildLinks( idt famID );
    static recFamilyEventVec GetEvents( idt famID );
    recFamilyEventVec GetEvents() const { return GetEvents( f_id ); }
    static recIdVec GetEventIDs( idt famID );
    recIdVec GetEventIDs() const { return GetEventIDs( f_id ); }

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

    idt FGetFamID() const { return f_fam_id; }
    idt FGetIndID() const { return f_ind_id; }
    int FGetSeqChild() const { return f_seq_child; }
    int FSetSeqParent() const { return f_seq_parent; }

    void FSetFamID( idt famID ) { f_fam_id = famID; }
    void FSetIndID( idt indID ) { f_ind_id = indID; }
    void FSetSeqChild( int seq ) { f_seq_child = seq; }
    void FSetSeqParent( int seq ) { f_seq_parent = seq; }

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
