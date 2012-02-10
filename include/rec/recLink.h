/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recLink.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Link records.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
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

#ifndef RECLINK_H
#define RECLINK_H

#include <rec/recDatabase.h>

//============================================================================
//                 recLinkEvent
//============================================================================

class recLinkEvent : public recDb
{
public:
    idt      f_ref_event_id;
    idt      f_ind_event_id;
    double   f_conf;
    wxString f_comment;

    recLinkEvent() {}
    recLinkEvent( idt id ) : recDb(id) { Read(); }
    recLinkEvent( const recLinkEvent& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "LinkEvent" );

    bool Find();

    static recIdVec FindEquivRefEvents( idt indEventID );
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recLinkEvent& d1, const recLinkEvent& d2 )
{
    return
        d1.f_ref_event_id == d2.f_ref_event_id &&
        d1.f_ind_event_id == d2.f_ind_event_id &&
        d1.f_conf         == d2.f_conf         &&
        d1.f_comment      == d2.f_comment;
}

inline bool operator==( const recLinkEvent& d1, const recLinkEvent& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recLinkEvent& d1, const recLinkEvent& d2 )
{
    return !(d1 == d2);
}

//============================================================================
//                 recLinkPersona
//============================================================================


class recLinkPersona : public recDb
{
public:
    idt      f_ref_per_id;
    idt      f_ind_per_id;
    double   f_conf;
    wxString f_comment;

    recLinkPersona() {}
    recLinkPersona( idt id ) : recDb(id) { Read(); }
    recLinkPersona( const recLinkPersona& link );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "LinkPersona" );

    bool Find();
};

/*! The two entities are equal, ignoring the record id.
 */
inline bool recEquivalent( const recLinkPersona& d1, const recLinkPersona& d2 )
{
    return
        d1.f_ref_per_id  == d2.f_ref_per_id &&
        d1.f_ind_per_id  == d2.f_ind_per_id &&
        d1.f_conf        == d2.f_conf       &&
        d1.f_comment     == d2.f_comment;
}

inline bool operator==( const recLinkPersona& d1, const recLinkPersona& d2 )
{
    return recEquivalent( d1, d2 ) && d1.f_id == d2.f_id;
}

inline bool operator!=( const recLinkPersona& d1, const recLinkPersona& d2 )
{
    return !(d1 == d2);
}

#endif // RECLINK_H
