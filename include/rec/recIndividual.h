/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family, FamilyIndividual and Individual records.
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

#ifndef RECINDIVIDUAL_H
#define RECINDIVIDUAL_H

#include <vector>

#include <rec/recDatabase.h>
#include <rec/recEvent.h>
#include <rec/recFamEvent.h>
#include <rec/recFamily.h>
//#include <rec/recFamilyIndividual.h>
#include <rec/recPersona.h>

class recIndividual;
typedef std::vector< recIndividual >  recIndividualList;
typedef std::vector< recIndividual >  recIndividualVec;
class recFamily;
typedef std::vector< recFamily >  recFamilyVec;

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

    static wxString GetIdStr( idt indID ) { return wxString::Format( "I" ID, indID ); }
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
    static idt FindGroupEvent( idt indID, recEventTypeGrp grp );
    idt FindGroupEvent( recEventTypeGrp grp ) const { return FindGroupEvent( f_id, grp ); }

    static recIdVec FindEvents( idt indID, idt roleID );
    recIdVec FindEvents( idt roleID ) const { return FindEvents( f_id, roleID ); }
    static recIdVec FindGroupEvents( idt indID, recEventTypeGrp grp );
    recIdVec FindGroupEvents( recEventTypeGrp grp ) const { return FindGroupEvents( f_id, grp ); }

    static idt GetPersonalSummaryIE( idt indID, idt etID );
    idt GetPersonalSummaryIE( idt etID ) const { return GetPersonalSummaryIE( f_id, etID ); }
    static idt GetPersonalSummaryEvent( idt indID, idt etID );
    idt GetPersonalSummaryEvent( idt etID ) const { return GetPersonalSummaryEvent( f_id, etID ); }

    idt GetBirthEvent() const { return FindGroupEvent( recEventTypeGrp::birth ); }
    idt GetNrBirthEvent() const { return FindGroupEvent( recEventTypeGrp::nr_birth ); }
    idt GetDeathEvent() const { return FindGroupEvent( recEventTypeGrp::death ); }
    idt GetNrDeathEvent() const { return FindGroupEvent( recEventTypeGrp::nr_death ); }
    static idt GetBirthEvent( idt id ) { return FindGroupEvent( id, recEventTypeGrp::birth ); }
    static idt GetNrBirthEvent( idt id ) { return FindGroupEvent( id, recEventTypeGrp::nr_birth ); }
    static idt GetDeathEvent( idt id ) { return FindGroupEvent( id, recEventTypeGrp::death ); }
    static idt GetNrDeathEvent( idt id ) { return FindGroupEvent( id, recEventTypeGrp::nr_death ); }

    static idt CreateBirthDate( idt indID );
    static idt CreateDeathDate( idt indID );

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

    static wxSQLite3ResultSet GetNameSet();

    static int GetMaxEventSeqNumber( idt indID );
    int GetMaxEventSeqNumber() const { return GetMaxEventSeqNumber( f_id ); }

    static bool CreateMissingFamilies();

    // Delete Individual and remove all references to it.
    void RemoveFromDatabase() { RemoveFromDatabase( f_id ); }
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


#endif // RECINDIVIDUAL_H
