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

#include <vector>
#include <rec/recDatabase.h>

class recName;
class recNameStyle;
class recNamePart;
class recNamePartType;
typedef std::vector< recName >          recNameVec;
typedef std::vector< recNameStyle >     recNameStyleVec;
typedef std::vector< recNamePart >      recNamePartVec;
typedef std::vector< recNamePartType >  recNamePartTypeVec;

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
    idt  f_per_id;
    idt  f_style_id;
    int  f_sequence;

    recName() {}
    recName( idt id ) : recDb(id) { Read(); }
    recName( const recName& name );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Name" );

    idt FGetPerID() const { return f_per_id; }
    idt FGetTypeID() const { return f_style_id; }
    int FGetNameSeq() const { return f_sequence; }

    void FSetPerID( idt perID ) { f_per_id = perID; }
    void FSetTypeID( idt typeID ) { f_style_id = typeID; }
    void FSetPerSeq( int perSeq ) { f_sequence = perSeq; }

    static wxString GetIdStr( idt nameID ) { return wxString::Format( "N"ID, nameID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static idt CreateName( const wxString& nameStr, idt style = 0 );

    int AddNameParts( const wxString& nameStr, recStdNameType type = NAME_TYPE_Unstated, int seq = 0 ) const;
    int AddNamePart( const wxString& nameStr, recStdNameType type, int seq ) const;

    // Delete Name and remove all references to it.
    static void RemoveFromDatabase( idt id );
    void RemoveFromDatabase() { RemoveFromDatabase( f_id ); Clear(); }

    static wxString GetNameStr( idt id );
    wxString GetNameStr() const { return GetNameStr( f_id ); }



    static wxString GetNamePartStr( idt nameID, idt partID );
    wxString GetNamePartStr( idt partID ) const
        { return GetNamePartStr( f_id, partID ); }
    static wxString GetSurname( idt id ) 
        { return GetNamePartStr( id, NAME_TYPE_Surname ); }
    wxString GetSurname() const { return GetNamePartStr( NAME_TYPE_Surname ); }

    bool FindPersona( idt perID, idt styleID = 0 );

    static recNamePartVec GetParts( idt nameID );
    recNamePartVec GetParts() const { return GetParts( f_id ); }
};

inline bool recEquivalent( const recName& r1, const recName& r2 )
{
    return
        r1.f_per_id   == r2.f_per_id   &&
        r1.f_style_id == r2.f_style_id &&
        r1.f_sequence == r2.f_sequence;
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
    idt       f_name_id;
    idt       f_type_id;
    wxString  f_val;
    int       f_sequence;

    recNamePart() {}
    recNamePart( idt id ) : recDb(id) { Read(); }
    recNamePart( const recNamePart& attr );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NamePart" );

    idt FGetNameID() const { return f_name_id; }
    idt FGetTypeID() const { return f_type_id; }
    wxString FGetValue() const { return f_val; }
    int FGetNameSeq() const { return f_sequence; }

    void FSetNameID( idt nameID ) { f_name_id = nameID; }
    void FSetTypeID( idt typeID ) { f_type_id = typeID; }
    void FSetValue( const wxString& val ) { f_val = val; }
    void FSetNameSeq( int nameSeq ) { f_sequence = nameSeq; }

    static wxString GetIdStr( idt npID ) { return wxString::Format( "NP"ID, npID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetValue( idt id );
    static recNamePartVec ConvertStrToList( const wxString& str, idt type = NAME_TYPE_Given_name );
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
    recNamePartType( idt id ) : recDb(id) { Read(); }
    recNamePartType( const recNamePartType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NameType" );

    NTYPE_Grp FGetGroup() const { return f_grp; }
    wxString FGetName() const { return f_name; }

    void FSetGroup( NTYPE_Grp group ) { f_grp = group; }
    void FSetName( const wxString& name ) { f_name = name; }

    static wxString GetIdStr( idt nptID ) { return wxString::Format( "NPT"ID, nptID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetTypeStr( idt id );

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
        NS_Default = 0, // Recorded (ie Name as recorded in documents)
        NS_Birth   = -1,
        NS_Married = -2,
        NS_Alias   = -3,
        NS_MAX     = 4
    };

    wxString  f_name;

    recNameStyle() {}
    recNameStyle( idt id ) : recDb(id) { Read(); }
    recNameStyle( const recNameStyle& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "NameStyle" );

    wxString FGetName() const { return f_name; }

    void FSetName( const wxString& name ) { f_name = name; }

    static wxString GetIdStr( idt ntID ) { return wxString::Format( "NT"ID, ntID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetStyleStr( idt id );

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
