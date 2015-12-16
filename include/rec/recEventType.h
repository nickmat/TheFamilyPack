/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventType.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventType table.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     20th April 2013
 * Copyright:   Copyright (c) 2013-2015, Nick Matthews.
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

    wxString GetGroupStr() const { return GetGroupValueStr( f_grp ); }
    static wxString GetGroupStr( idt etID );
    static wxString GetGroupValueStr( recET_GRP grp );

    static wxArrayString GetGroupStrings( size_t start = 0 );

    static wxString GetTypeStr( idt id );
    wxString GetTypeStr() const { return f_name; }
    static recET_GRP GetGroup( idt id );

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
