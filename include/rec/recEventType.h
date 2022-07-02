/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventType table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013..2022, Nick Matthews.
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

#ifndef REC_RECEVENTTYPE_H
#define REC_RECEVENTTYPE_H

#include <rec/recEventTypeRole.h>


class recEvent;
typedef std::vector< recEvent >      recEventVec;
class recEventType;
typedef std::vector< recEventType >  recEventTypeVec;
class recEventa;
typedef std::vector< recEventa >    recEventaVec;

//============================================================================
//-------------------------[ recEventType ]-----------------------------------
//============================================================================

class recEventType : public recDbT<recEventType>, public recUidT<recEventType>
{
public:
    static constexpr const char* s_tablename = "EventType";

    enum EType {  // predefined entries, match with recCreate.sql
        ET_Unstated     = 0,
        ET_Birth        = -1,
        ET_Death        = -2,
        ET_Marriage     = -3,
        ET_Baptism      = -4,
        ET_Burial       = -5,
        ET_AdultBaptism = -6,
        ET_Census       = -7,
        ET_Confirmation = -8,
        ET_Divorce      = -9,
        ET_Emigration   = -10,
        ET_Immigration  = -11,
        ET_Graduation   = -12,
        ET_Probate      = -13,
        ET_Will         = -14,
        ET_RegBirth     = -15,
        ET_RegDeath     = -16,
        ET_Residence    = -17,
        ET_Occupation   = -18,
        ET_Condition    = -19,
        ET_CivilPartner = -20,
        ET_Relation     = -21,
        ET_Family       = -22,
        ET_Media        = -23,
        ET_MAX          = 24     // Size of list
    };

    recEventTypeGrp f_grp;
    wxString        f_name;

    recEventType() : f_grp( recEventTypeGrp::unstated ) {}
    recEventType( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recEventType( const recEventType& et );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recEventType& r2 ) const;

    static wxString GetIdStr( idt evID ) { return wxString::Format( "ET" ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    recEventTypeGrp FGetGrp() const { return f_grp; }
    wxString FGetName() const { return f_name; }

    void FSetGrp( recEventTypeGrp grp ) { f_grp = grp; }
    void FSetName( wxString name ) { f_name = name; }

    static wxString GetName( idt typeID, const wxString& dbname = "Main" );

    bool HasDateSpan() const;
    static bool HasDateSpan( idt etID, const wxString& dbname = "Main" );

    wxString GetGroupStr() const {
        return GetGroupValueStr( f_grp ); }
    static wxString GetGroupStr( idt etID, const wxString& dbname = "Main" );
    static wxString GetGroupValueStr( recEventTypeGrp grp );

    static wxArrayString GetGroupStrings( size_t start = 0 );

    static wxString GetTypeStr( idt id, const wxString& dbname = "Main" );
    wxString GetTypeStr() const { return f_name; }
    static recEventTypeGrp GetGroup( idt id, const wxString& dbname = "Main" );

    static recEventTypeVec ReadVec(
        unsigned filter = recET_GRP_FILTER_AllValid, const wxString& dbname = "Main" );

    static recEventTypeRoleVec GetRoles( idt typeID, const wxString& dbname = "Main" );
    recEventTypeRoleVec GetRoles( const wxString& dbname = "Main" ) const {
        return GetRoles( FGetID(), dbname ); }
    static recEventTypeRoleVec GetPrimeRoles(
        idt typeID, int prime = 0, const wxString& dbname = "Main" );

    static idt GetSummaryRole( idt typeID );

    static idt Transfer( idt from_etID, const wxString& fromdb, const wxString& todb );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

    static bool DeleteIfOrphaned( idt etID, const wxString& dbname = "Main" );
};

#endif // REC_RECEVENTTYPE_H
