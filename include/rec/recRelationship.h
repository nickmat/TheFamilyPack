/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recRelationship.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Relationship records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     19 October 2011
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

#ifndef RECRELATIONSHIP_H
#define RECRELATIONSHIP_H

#include <rec/recDatabase.h>

class recRelationship;
typedef std::vector< recRelationship >  recRelationshipVec;


class recRelationship : public recDb
{
public:
    idt       f_per1_id;
    idt       f_per2_id;
    wxString  f_descrip;

    recRelationship() {}
    recRelationship( idt id ) : recDb(id) { Read(); }
    recRelationship( const recRelationship& rel );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Relationship" );

    idt FGetPer1ID() const { return f_per1_id; }
    idt FGetPer2ID() const { return f_per2_id; }
    wxString FGetDescrip() const { return f_descrip; }
 
    void FSetPer1ID( idt perID ) { f_per1_id = perID; }
    void FSetPer2ID( idt perID ) { f_per2_id = perID; }
    void FSetDescrip( const wxString& descrip ) { f_descrip = descrip; }

    static wxString GetIdStr( idt relID ) { return wxString::Format( "Rs"ID, relID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetValue1Str() const;
    wxString GetValue2Str() const;
    static wxString GetValue1Str( idt relID );
    static wxString GetValue2Str( idt relID );

    wxString GetRelOfPersonaStr( idt perID ) const;
    static wxString GetRelOfPersonaStr( idt perID, idt relID );
};

inline bool recEquivalent( const recRelationship& r1, const recRelationship& r2 )
{
    return
        r1.f_per1_id == r2.f_per1_id &&
        r1.f_per2_id == r2.f_per2_id &&
        r1.f_descrip == r2.f_descrip;
}

inline bool operator==( const recRelationship& r1, const recRelationship& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recRelationship& r1, const recRelationship& r2 )
{
    return !(r1 == r2);
}

#endif // RECRELATIONSHIP_H
