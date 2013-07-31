/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventType table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <rec/recDatabase.h>


class recEvent;
typedef std::vector< recEvent >      recEventVec;
class recEventType;
typedef std::vector< recEventType >  recEventTypeVec;
class recEventum;
typedef std::vector< recEventum >    recEventumVec;

class recEventTypeRole;
typedef std::vector< recEventTypeRole >    recEventTypeRoleVec;
class recEventEventum;
typedef std::vector< recEventEventum >     recEventEventumVec;
class recEventumPersona;
typedef std::vector< recEventumPersona >   recEventumPersonaVec;
class recIndividualEvent;
typedef std::vector< recIndividualEvent >  recIndEventVec;
class recFamilyEvent;
typedef std::vector< recFamilyEvent >      recFamilyEventVec;

enum {
    recET_FILTER_GrpUnstated    = 0x0001,
    recET_FILTER_GrpBirth       = 0x0002,
    recET_FILTER_GrpNrBirth     = 0x0004,
    recET_FILTER_GrpFamUnion    = 0x0008,
    recET_FILTER_GrpFamOther    = 0x0010,
    recET_FILTER_GrpDeath       = 0x0020,
    recET_FILTER_GrpNrDeath     = 0x0040,
    recET_FILTER_GrpOther       = 0x0080,
    recET_FILTER_GrpPersonal    = 0x0100,

    recET_FILTER_GrpNone        = 0x0000,
    recET_FILTER_GrpAll         = 0x01ff,
    recET_FILTER_GrpAllValid    = 0x01fe,
    recET_FILTER_GrpFamily = (recET_FILTER_GrpFamUnion|recET_FILTER_GrpFamOther)
};

enum recET_GRP_FILTER {
    recET_GRP_FILTER_Unstated    = 0x0001,
    recET_GRP_FILTER_Birth       = 0x0002,
    recET_GRP_FILTER_NrBirth     = 0x0004,
    recET_GRP_FILTER_FamUnion    = 0x0008,
    recET_GRP_FILTER_FamOther    = 0x0010,
    recET_GRP_FILTER_Death       = 0x0020,
    recET_GRP_FILTER_NrDeath     = 0x0040,
    recET_GRP_FILTER_Other       = 0x0080,
    recET_GRP_FILTER_Personal    = 0x0100,

    recET_GRP_FILTER_None        = 0x0000,
    recET_GRP_FILTER_All         = 0x01ff,
    recET_GRP_FILTER_AllValid    = 0x01fe,
    recET_GRP_FILTER_Family = (recET_GRP_FILTER_FamUnion|recET_GRP_FILTER_FamOther)
};

enum recET_GRP {
    recET_GRP_Unstated, // 0
    recET_GRP_Birth,    // 1
    recET_GRP_NrBirth,  // 2
    recET_GRP_FamUnion, // 3
    recET_GRP_FamOther, // 4
    recET_GRP_Death,    // 5
    recET_GRP_NrDeath,  // 6
    recET_GRP_Other,    // 7
    recET_GRP_Personal, // 8
    recET_GRP_MAX       // 9
};

inline recET_GRP_FILTER recEventTypeGrpToFilter( recET_GRP grp ) { return  recET_GRP_FILTER(1 << grp); }

//============================================================================
//-------------------------[ recEventType ]-----------------------------------
//============================================================================

class recEventType : public recDb
{
public:
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
        ET_MAX          = 20     // Size of list
    };

    recET_GRP f_grp;
    wxString  f_name;

    recEventType() {}
    recEventType( idt id ) : recDb(id) { Read(); }
    recEventType( const recEventType& et );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "EventType" );

    static wxString GetIdStr( idt evID ) { return wxString::Format( "ET"ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    recET_GRP FGetGrp() const { return f_grp; }
    wxString FGetName() const { return f_name; }

    void FSetGrp( recET_GRP grp ) { f_grp = grp; }
    void FSetName( wxString name ) { f_name = name; }

    static wxString GetName( idt typeID );

    bool HasDateSpan() const;
    static bool HasDateSpan( idt etID );

    wxString GetGroupStr() const { return GetGroupStr( f_grp ); }
    static wxString GetGroupStr( idt etID );
    static wxString GetGroupValueStr( recET_GRP grp );

    static wxArrayString GetGroupStrings( size_t start = 0 );

    static wxString GetTypeStr( idt id );
    wxString GetTypeStr() const { return f_name; }
    static recET_GRP GetGroup( idt id );
//    recET_GRP GetGroup() const { return f_grp; }

    static recEventTypeVec ReadVec( unsigned filter = recET_GRP_FILTER_AllValid );

    static recEventTypeRoleVec GetRoles( idt typeID );
    recEventTypeRoleVec GetRoles() const { return GetRoles( FGetID() ); }
    static recEventTypeRoleVec GetPrimeRoles( idt typeID, int prime = 0 );
};

inline bool recEquivalent( const recEventType& r1, const recEventType& r2 )
{
    return
        r1.f_grp  == r2.f_grp  &&
        r1.f_name == r2.f_name;
}

inline bool operator==( const recEventType& r1, const recEventType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recEventType& r1, const recEventType& r2 )
{
    return !(r1 == r2);
}

#endif // REC_RECEVENTTYPE_H
