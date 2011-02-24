/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recName.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Name, NamePart, NamePartType and NameStyle records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22 November 2010
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

#ifndef RECNAME_H
#define RECNAME_H

#include <wx/vector.h>
#include <rec/recDatabase.h>

class recName;
class recNameStyle;
class recNamePart;
class recNamePartType;
typedef wxVector< recName >  recNameVec;
typedef wxVector< recNameStyle >  recNameStyleVec;
typedef wxVector< recNamePart >  recNamePartVec;
typedef wxVector< recNamePartType >  recNamePartTypeVec;

//----------------------------------------------------------

enum recStdNameType  // These match the create.sql file
{
    NAME_TYPE_Unstated   = 0,
    NAME_TYPE_Given_name = -1,
    NAME_TYPE_Surname    = -2,
    NAME_TYPE_Post_name  = -3,
    NAME_TYPE_Max        = 4
};

class recName : public recDb
{
public:
    id_t      f_per_id;
    id_t      f_style_id;

    recName() {}
    recName( id_t id ) : recDb(id) { Read(); }
    recName( const recName& attr );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Name" );

    void AddNameParts( const wxString& nameStr ) const;
//    void UpdateNameParts( wxString& nameStr );
//    bool RemoveNameParts();

    bool FindPersona( id_t perID, id_t styleID = 0 );
    wxString GetNamePart( id_t nptID );
//    static wxString GetValue( id_t id );
//  static recNameList ConvertStrToList( const wxString& str, id_t type = NAME_TYPE_Given_name );

    static wxString GetSurname( id_t id );
    static wxString GetGivenName( id_t id );
    static wxString GetFullName( id_t id )
        { return GetGivenName( id ) + " " + GetSurname( id ); }
    wxString GetFullName() const { return GetFullName( f_id ); }

    static recNamePartVec GetParts( id_t nameID );
    recNamePartVec GetParts() const { return GetParts( f_id ); }
};

inline bool recEquivalent( const recName& r1, const recName& r2 )
{
    return
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_style_id == r2.f_style_id;
}

inline bool operator==( const recName& r1, const recName& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recName& r1, const recName& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recNamePart : public recDb
{
public:
    id_t      f_name_id;
    id_t      f_type_id;
    wxString  f_val;
    unsigned  f_sequence;

    recNamePart() {}
    recNamePart( id_t id ) : recDb(id) { Read(); }
    recNamePart( const recNamePart& attr );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NamePart" );

    static wxString GetValue( id_t id );
    static recNamePartVec ConvertStrToList( const wxString& str, id_t type = NAME_TYPE_Given_name );
    static wxSQLite3ResultSet GetSurnameList() {
        return s_db->ExecuteQuery(
            "SELECT val FROM NamePart WHERE type_id=-2 GROUP BY val;"
        );
    }
};

inline bool recEquivalent( const recNamePart& r1, const recNamePart& r2 )
{
    return
        r1.f_name_id  == r2.f_name_id  &&
        r1.f_type_id  == r2.f_type_id  &&
        r1.f_val      == r2.f_val      &&
        r1.f_sequence == r2.f_sequence;
}

inline bool operator==( const recNamePart& r1, const recNamePart& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recNamePart& r1, const recNamePart& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recNamePartType : public recDb
{
public:
    enum NTYPE_Grp {
        NTYPE_Grp_Unstated, NTYPE_Grp_Name, NTYPE_Grp_Title,
        NTYPE_Grp_Other
    };

    NTYPE_Grp f_grp;
    wxString  f_name;

    recNamePartType() {}
    recNamePartType( id_t id ) : recDb(id) { Read(); }
    recNamePartType( const recNamePartType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NameType" );

    static wxString GetTypeStr( id_t id );

    static recNamePartTypeVec GetTypeList();
};

inline bool recEquivalent( const recNamePartType& r1, const recNamePartType& r2 )
{
    return
        r1.f_grp   == r2.f_grp &&
        r1.f_name == r2.f_name;
}

inline bool operator==( const recNamePartType& r1, const recNamePartType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recNamePartType& r1, const recNamePartType& r2 )
{
    return !(r1 == r2);
}

//----------------------------------------------------------

class recNameStyle : public recDb
{
public:
    enum Style {
        NS_Default = 0,
        NS_Birth  = -1,
        NS_Married = -2,
        NS_Alias   = -3,
        NS_MAX    = 4
    };

    wxString  f_name;

    recNameStyle() {}
    recNameStyle( id_t id ) : recDb(id) { Read(); }
    recNameStyle( const recNameStyle& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NameStyle" );

    static wxString GetStyleStr( id_t id );

    static recNameStyleVec GetStyleList();
};

inline bool recEquivalent( const recNameStyle& r1, const recNameStyle& r2 )
{
    return
        r1.f_name == r2.f_name;
}

inline bool operator==( const recNameStyle& r1, const recNameStyle& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recNameStyle& r1, const recNameStyle& r2 )
{
    return !(r1 == r2);
}

#endif // RECNAME_H
