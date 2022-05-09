/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recEventTypeRole.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 EventTypeRole records.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     14th December 2015
 * Copyright:   Copyright (c) 2015..2022, Nick Matthews.
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

#ifndef REC_RECEVENTTYPEROLE_H
#define REC_RECEVENTTYPEROLE_H

#include <rec/recDatabase.h>

//============================================================================
//-------------------------[ recEventTypeRole ]-------------------------------
//============================================================================

class recEventTypeRole : public recDbT<recEventTypeRole>
{
public:
    static constexpr const char* s_tablename = "EventTypeRole";

    enum Role {  // predefined entries, only given if required by the program
        ROLE_Unstated               = 0,
        ROLE_Birth_Born             = -1,
        ROLE_Birth_Mother           = -2,
        ROLE_Baptism_Baptised       = -21,
        ROLE_Baptism_Parent         = -22,
        ROLE_Burial_Deceased        = -26,
        ROLE_Census_Listed          = -32,
        ROLE_Condition_Summary      = -67,
        ROLE_Death_Died             = -5,
        ROLE_Family_Child           = -76,
        ROLE_Family_Husband         = -73,
        ROLE_Family_Partner         = -75,
        ROLE_Family_Wife            = -74,
        ROLE_Marriage_Bride         = -8,
        ROLE_Marriage_FatherOfBride = -13,
        ROLE_Marriage_FatherOfGroom = -11,
        ROLE_Marriage_Groom         = -7,
        ROLE_Marriage_Officiate     = -9,
        ROLE_Marriage_Spouse        = -59,  // If we don't know their gender.
        ROLE_Marriage_Witness       = -10,
        ROLE_RegBirth_Born          = -50,
        ROLE_RegBirth_Parent        = -51,
        ROLE_RegBirth_Mother        = -60,
        ROLE_RegDeath_Died          = -55,
        ROLE_Residence_Boarder      = -64,
        ROLE_Residence_Family       = -61,
        ROLE_Residence_Inmate       = -86,
        ROLE_Residence_Lodger       = -63,
        ROLE_Residence_Resident     = -87, // Anything not currently defined
        ROLE_Residence_Staff        = -85,
        ROLE_Residence_Summary      = -77,
        ROLE_Residence_Visitor      = -62,
        ROLE_Occupation_Summary     = -65,
        ROLE_Media_Subject          = -88,
        ROLE_Media_Producer         = -89,
        ROLE_Media_Commentator      = -90,
        ROLE_MAX                    = 36 // size of list
    };
    enum Prime {
        PRIME_Ignore = -1,
        PRIME_None   = 0,
        PRIME_First  = 1,
        PRIME_Second = 2,
        PRIME_Any    = 3,
        PRIME_MAX    = 4
    };
    enum SelectFilter {
        SF_All,
        SF_Prime,
        SF_Prime1,
        SF_Prime2
    };

    idt       f_type_id;
    int       f_prime;
    bool      f_official;
    wxString  f_name;

    recEventTypeRole() : f_type_id(0), f_prime(false), f_official(false) {}
    recEventTypeRole( idt id, const wxString& dbname = "Main" ) : recDbT(id) { Read( dbname ); }
    recEventTypeRole( const recEventTypeRole& etr );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recEventTypeRole& r2 ) const;

    idt FGetTypeID() const { return f_type_id; }
    int FGetPrime() const { return f_prime; }
    bool FGetOfficial() const { return f_official; }
    wxString FGetName() const { return f_name; }

    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetPrime( int prime ) { f_prime = prime; }
    void FSetOfficial( bool official ) { f_official = official; }
    void FSetName( const wxString& name ) { f_name = name; }

    static wxString GetIdStr( idt evID ) { return wxString::Format( "Ro" ID, evID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetName( idt roleID, const wxString& dbname = "Main" );
    wxString GetPrimeStr() const;

    static wxString GetTypeAndRoleStr( idt roleID );
    static idt Select( idt typeID, SelectFilter sf = SF_All );

    static idt Find( const wxString& name, idt type, Prime prime = PRIME_Ignore, TriLogic official = TRILOGIC_both );
    static idt FindOrCreate( const wxString& name, idt type, Prime prime = PRIME_First, bool official = false );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );
};

typedef std::vector< recEventTypeRole >    recEventTypeRoleVec;

#endif // REC_RECEVENTTYPEROLE_H
