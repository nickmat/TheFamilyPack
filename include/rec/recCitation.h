/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recCitation.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the Citation records header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th November 2021
 * Copyright:   Copyright (c) 2021, Nick Matthews.
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

#ifndef RECCITATION_H
#define RECCITATION_H

#include <rec/recDatabase.h>

class recCitationPartType;
typedef std::vector< recCitationPartType >  recCitationPartTypeVec;

//============================================================================
//                 recCitationPart
//============================================================================

class recCitationPart : public recDb
{
public:
    idt     f_type_id;
    idt     f_source_id;
    wxString f_val;

    recCitationPart() {}
    recCitationPart( idt id ) : recDb(id) { Read(); }
    recCitationPart( const recCitationPart& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "CitationPart" );

};

inline bool recEquivalent( const recCitationPart& r1, const recCitationPart& r2 )
{
    return
        r1.f_type_id   == r2.f_type_id   &&
        r1.f_source_id == r2.f_source_id &&
        r1.f_val       == r2.f_val;
}

inline bool operator==( const recCitationPart& r1, const recCitationPart& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recCitationPart& r1, const recCitationPart& r2 )
{
    return !(r1 == r2);
}

//============================================================================
//                 recCitationPartType
//============================================================================

class recCitationPartType : public recDb
{
public:
    wxString  f_name;

    recCitationPartType() {}
    recCitationPartType( idt id ) : recDb(id) { Read(); }
    recCitationPartType( const recCitationPartType& at );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "CitationPartType" );

    static wxString GetStr( idt id );

    static recCitationPartTypeVec GetList();
};

inline bool recEquivalent( const recCitationPartType& r1, const recCitationPartType& r2 )
{
    return
        r1.f_name == r2.f_name;
}

inline bool operator==( const recCitationPartType& r1, const recCitationPartType& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recCitationPartType& r1, const recCitationPartType& r2 )
{
    return !(r1 == r2);
}


#endif // RECCITATION_H
