/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recIndividual.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Individual record.
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
#include <rec/recPersona.h>

class recIndividual;
typedef std::vector< recIndividual >  recIndividualVec;

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

class recIndividual : public recDbT< recIndividual>
{
public:
    static constexpr const char* s_tablename = "Individual";

    Sex      f_sex;
    idt      f_fam_id;
    wxString f_note;
    int      f_privacy;
    wxString f_name;
    wxString f_surname;
    wxString f_epitaph;

    recIndividual() : f_sex( Sex::unstated), f_fam_id(0), f_privacy(0) {}
    recIndividual( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recIndividual( const recIndividual& ind );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recIndividual& r2 ) const;

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

    static Sex GetSex( idt indID, const wxString& dbname = "Main" );
    static idt GetFamilyID( idt indID, const wxString& dbname = "Main" );
    static int GetPrivacy( idt indID, const wxString& dbname = "Main" );
    static wxString GetName( idt indID, const wxString& dbname = "Main" );
    static wxString GetSurname( idt indID, const wxString& dbname = "Main" );
    static wxString GetEpitaph( idt indID, const wxString& dbname = "Main" );

    static recIndividualVec ReadVec( unsigned sexfilter = recInd_FILTER_SexAll, const wxString& dbname = "Main" );
    static recIdVec GetIdVec( const wxString& dbname = "Main" );

    static idt GetNameID( idt indID, const wxString& dbname = "Main" ) {
        return recName::GetDefaultNameID( indID, 0, dbname ); }
    idt GetNameID( const wxString& dbname = "Main" ) const {
        return recName::GetDefaultNameID( f_id, 0, dbname ); }
    static wxString GetNameStr( idt indID, const wxString& dbname = "Main" ) {
        return recName::GetDefaultNameStr( indID, 0, dbname ); }
    wxString GetNameStr( const wxString& dbname = "Main" ) const {
        return recName::GetDefaultNameStr( f_id, 0, dbname ); }
    static wxString GetDescriptionStr( idt indID, const wxString& dbname = "Main" );
    wxString GetDescriptionStr( const wxString& dbname = "Main" ) const {
        return GetDescriptionStr( f_id, dbname ); }

    static recNameVec GetNames( idt indID, const wxString& dbname = "Main" ) {
        return recName::GetNames( indID, 0, dbname ); }
    recNameVec GetNames( const wxString& dbname = "Main" ) const {
        return recName::GetNames( f_id, 0, dbname ); }

    void UpdateEpitaph( const wxString& dbname = "Main" );
    static void UpdateEpitaph( idt indID, const wxString& dbname = "Main" );
    void UpdateNames( const wxString& dbname = "Main" );
    void UpdateDefaultFamily( const wxString& dbname = "Main" );
    void Update( const wxString& dbname = "Main" );
    static void Update( idt indID, const wxString& dbname = "Main" );

    static recIndividualVec GetChildren( idt famID, const wxString& dbname = "Main" );

    static idt FindEvent( idt indID, idt roleID, const wxString& dbname = "Main" );
    idt FindEvent( idt roleID, const wxString& dbname = "Main" ) const {
        return FindEvent( f_id, roleID, dbname ); }
    static idt FindGroupEvent( idt indID, recEventTypeGrp grp, const wxString& dbname = "Main" );
    idt FindGroupEvent( recEventTypeGrp grp, const wxString& dbname = "Main" ) const {
        return FindGroupEvent( f_id, grp, dbname ); }

    static recIdVec FindEvents( idt indID, idt roleID, const wxString& dbname = "Main" );
    recIdVec FindEvents( idt roleID, const wxString& dbname = "Main" ) const {
        return FindEvents( f_id, roleID, dbname ); }
    static recIdVec FindGroupEvents( idt indID, recEventTypeGrp grp, const wxString& dbname = "Main" );
    recIdVec FindGroupEvents( recEventTypeGrp grp, const wxString& dbname = "Main" ) const {
        return FindGroupEvents( f_id, grp, dbname ); }

    static idt GetPersonalSummaryIE( idt indID, idt etID, const wxString& dbname = "Main" );
    idt GetPersonalSummaryIE( idt etID, const wxString& dbname = "Main" ) const {
        return GetPersonalSummaryIE( f_id, etID, dbname ); }
    static idt GetPersonalSummaryEvent( idt indID, idt etID, const wxString& dbname = "Main" );
    idt GetPersonalSummaryEvent( idt etID, const wxString& dbname = "Main" ) const {
        return GetPersonalSummaryEvent( f_id, etID, dbname ); }

    idt GetBirthEvent( const wxString& dbname = "Main" ) const {
        return FindGroupEvent( recEventTypeGrp::birth, dbname ); }
    idt GetNrBirthEvent( const wxString& dbname = "Main" ) const {
        return FindGroupEvent( recEventTypeGrp::nr_birth, dbname ); }
    idt GetDeathEvent( const wxString& dbname = "Main" ) const {
        return FindGroupEvent( recEventTypeGrp::death, dbname ); }
    idt GetNrDeathEvent( const wxString& dbname = "Main" ) const {
        return FindGroupEvent( recEventTypeGrp::nr_death, dbname ); }
    static idt GetBirthEvent( idt id, const wxString& dbname = "Main" ) {
        return FindGroupEvent( id, recEventTypeGrp::birth, dbname ); }
    static idt GetNrBirthEvent( idt id, const wxString& dbname = "Main" ) {
        return FindGroupEvent( id, recEventTypeGrp::nr_birth, dbname ); }
    static idt GetDeathEvent( idt id, const wxString& dbname = "Main" ) {
        return FindGroupEvent( id, recEventTypeGrp::death, dbname ); }
    static idt GetNrDeathEvent( idt id, const wxString& dbname = "Main" ) {
        return FindGroupEvent( id, recEventTypeGrp::nr_death, dbname ); }

    static idt CreateBirthDate( idt indID, const wxString& dbname = "Main" );
    static idt CreateDeathDate( idt indID, const wxString& dbname = "Main" );

    static recIndEventVec GetEvents(
        idt indID, recEventOrder order = recEO_DatePt, const wxString& dbname = "Main" );
    recIndEventVec GetEvents( 
        recEventOrder order = recEO_DatePt, const wxString& dbname = "Main" ) const {
        return GetEvents( f_id, order, dbname ); }

    wxSQLite3ResultSet GetEventaSet( const wxString& dbname = "Main" ) const {
        return GetEventaSet( f_id, dbname ); }
    static wxSQLite3ResultSet GetEventaSet( idt indID, const wxString& dbname = "Main" );

    wxSQLite3ResultSet GetReferenceSet( const wxString& dbname = "Main" ) const {
        return GetReferenceSet( f_id, dbname ); }
    static wxSQLite3ResultSet GetReferenceSet( idt indID, const wxString& dbname = "Main" );

    static wxSQLite3ResultSet GetNameSet( const wxString& dbname = "Main" );

    static int GetMaxEventSeqNumber( idt indID, const wxString& dbname = "Main" );
    int GetMaxEventSeqNumber( const wxString& dbname = "Main" ) const {
        return GetMaxEventSeqNumber( f_id, dbname ); }

    static bool CreateMissingFamilies( const wxString& dbname = "Main" );

    // Delete Individual and remove all references to it.
    void RemoveFromDatabase( const wxString& dbname = "Main" ) {
        RemoveFromDatabase( f_id, dbname ); }
    static void RemoveFromDatabase( idt id, const wxString& dbname = "Main" );
};


#endif // RECINDIVIDUAL_H
