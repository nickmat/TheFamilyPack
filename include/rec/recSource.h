/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recSource.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Source record header.
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

#ifndef RECSOURCE_H
#define RECSOURCE_H

#include <rec/recDatabase.h>

class recSource;
typedef std::vector< recSource >  recSourceVec;


class recSource : public recDb
{
public:
    id_t     f_higher_id;
    id_t     f_sub_date1_id;
    id_t     f_sub_date2_id;
    id_t     f_sub_place_id;
    id_t     f_loc_place_id;
    id_t     f_res_id;
    wxString f_comments;

    recSource() {}
    recSource( id_t id ) : recDb(id) { Read(); }
    recSource( const recSource& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Source" );

};

inline bool recEquivalent( const recSource& r1, const recSource& r2 )
{
    return
        r1.f_higher_id    == r2.f_higher_id    &&
        r1.f_sub_date1_id == r2.f_sub_date1_id &&
        r1.f_sub_date2_id == r2.f_sub_date2_id &&
        r1.f_sub_place_id == r2.f_sub_place_id &&
        r1.f_loc_place_id == r2.f_loc_place_id &&
        r1.f_res_id       == r2.f_res_id       &&
        r1.f_comments     == r2.f_comments;
}

inline bool operator==( const recSource& r1, const recSource& r2 )
{
    return recEquivalent( r1, r2 ) && r1.f_id == r2.f_id;
}

inline bool operator!=( const recSource& r1, const recSource& r2 )
{
    return !(r1 == r2);
}



#endif // RECSOURCE_H
