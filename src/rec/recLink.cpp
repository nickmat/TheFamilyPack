/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recLink.cpp
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recLink.h>

//============================================================================
//                 recLinkAttribute
//============================================================================

recLinkAttribute::recLinkAttribute( const recLinkAttribute& d )
{
    f_id         = d.f_id;
    f_ref_att_id = d.f_ref_att_id;
    f_ind_att_id = d.f_ind_att_id;
    f_conf       = d.f_conf;
    f_comment    = d.f_comment;
}

void recLinkAttribute::Clear()
{
    f_id         = 0;
    f_ref_att_id = 0;
    f_ind_att_id = 0;
    f_conf       = 0;
    f_comment    = wxEmptyString;
}

void recLinkAttribute::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO LinkAttribute "
            "(ref_att_id, ind_att_id, conf, comment) "
            "VALUES ("ID", "ID", %f, '%q');",
            f_ref_att_id, f_ind_att_id, f_conf, UTF8_(f_comment)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO LinkAttribute "
                "(id, ref_att_id, ind_att_id, conf, comment) "
                "VALUES ("ID", "ID", "ID", %f, '%q');",
                f_id, f_ref_att_id, f_ind_att_id, f_conf, UTF8_(f_comment)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE LinkAttribute SET ref_att_id="ID", ind_att_id="ID", "
                "conf=%f, comment='%q' "
                "WHERE id="ID";",
                f_ref_att_id, f_ind_att_id, f_conf,
                UTF8_(f_comment), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recLinkAttribute::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ref_att_id, ind_att_id, conf, comment "
        "FROM LinkAttribute WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ref_att_id = GET_ID( result.GetInt64( 0 ) );
    f_ind_att_id = GET_ID( result.GetInt64( 1 ) );
    f_conf         = result.GetDouble( 2 );
    f_comment      = result.GetAsString( 3 );
    return true;
}

/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recLinkAttribute::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_ind_att_id == 0 || f_ref_att_id == 0 ) return false; 

    sql.Format(
        "SELECT id, conf, comment FROM LinkAttribute "
        "WHERE ref_att_id="ID" AND ind_att_id="ID";",
        f_ref_att_id, f_ind_att_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id      = GET_ID( result.GetInt64( 0 ) );
    f_conf    = result.GetDouble( 1 );
    f_comment = result.GetAsString( 2 );
    return true;
}

//============================================================================
//                 recLinkEvent
//============================================================================

recLinkEvent::recLinkEvent( const recLinkEvent& d )
{
    f_id           = d.f_id;
    f_ref_event_id = d.f_ref_event_id;
    f_ind_event_id = d.f_ind_event_id;
    f_conf         = d.f_conf;
    f_comment      = d.f_comment;
}

void recLinkEvent::Clear()
{
    f_id           = 0;
    f_ref_event_id = 0;
    f_ind_event_id = 0;
    f_conf         = 0;
    f_comment      = wxEmptyString;
}

void recLinkEvent::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO LinkEvent "
            "(ref_event_id, ind_event_id, conf, comment) "
            "VALUES ("ID", "ID", %f, '%q');",
            f_ref_event_id, f_ind_event_id, f_conf, UTF8_(f_comment)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO LinkEvent "
                "(id, ref_event_id, ind_event_id, conf, comment) "
                "VALUES ("ID", "ID", "ID", %f, '%q');",
                f_id, f_ref_event_id, f_ind_event_id, f_conf, UTF8_(f_comment)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE LinkEvent SET ref_event_id="ID", ind_event_id="ID", "
                "conf=%f, comment='%q' "
                "WHERE id="ID";",
                f_ref_event_id, f_ind_event_id, f_conf,
                UTF8_(f_comment), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recLinkEvent::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ref_event_id, ind_event_id, conf, comment "
        "FROM LinkEvent WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ref_event_id = GET_ID( result.GetInt64( 0 ) );
    f_ind_event_id = GET_ID( result.GetInt64( 1 ) );
    f_conf         = result.GetDouble( 2 );
    f_comment      = result.GetAsString( 3 );
    return true;
}

/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recLinkEvent::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_ind_event_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, conf, comment FROM LinkEvent "
        "WHERE ref_event_id="ID" AND ind_event_id="ID";",
        f_ref_event_id, f_ind_event_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id      = GET_ID( result.GetInt64( 0 ) );
    f_conf    = result.GetDouble( 1 );
    f_comment = result.GetAsString( 2 );
    return true;
}

recIdVec recLinkEvent::FindEquivRefEventIDs( idt indEventID )
{
    recIdVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT DISTINCT event_id FROM"
        " (SELECT EP.event_id, LP.ind_per_id FROM"
        " LinkPersona LP, EventPersona EP, Event E, EventTypeRole R"
        " WHERE LP.ref_per_id=EP.per_id AND EP.role_id=R.id AND E.id="ID" "
        "  AND R.type_id=E.type_id AND NOT R.prime=0) "
        "JOIN "
        " (SELECT per_id FROM EventPersona WHERE event_id="ID") "
        "ON ind_per_id=per_id;",
        indEventID, indEventID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        vec.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return vec;
}

recEventVec recLinkEvent::FindEquivRefEvents( idt indEventID )
{
    recEventVec vec;
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id, title, type_id, date1_id, date2_id, place_id, note FROM "
        "  Event "
        "JOIN "
        "  (SELECT DISTINCT event_id FROM "
        "   (SELECT EP.event_id, LP.ind_per_id FROM "
        "   LinkPersona LP, EventPersona EP, Event E, EventTypeRole R "
        "   WHERE LP.ref_per_id=EP.per_id AND EP.role_id=R.id AND E.id="ID" "
        "    AND R.type_id=E.type_id AND NOT R.prime=0) "
        "  JOIN "
        "   (SELECT per_id FROM EventPersona WHERE event_id="ID") "
        "  ON ind_per_id=per_id) "
        "ON id=event_id;",
        indEventID, indEventID
    );
    result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        recEvent e(0);
        e.f_id       = GET_ID( result.GetInt64( 0 ) );
        e.f_title    = result.GetAsString( 1 );
        e.f_type_id  = GET_ID( result.GetInt64( 2 ) );
        e.f_date1_id = GET_ID( result.GetInt64( 3 ) );
        e.f_date2_id = GET_ID( result.GetInt64( 4 ) );
        e.f_place_id = GET_ID( result.GetInt64( 5 ) );
        e.f_note     = result.GetAsString( 6 );
        vec.push_back( e );
    }
    return vec;
}


//============================================================================
//                 recLinkPersona
//============================================================================

recLinkPersona::recLinkPersona( const recLinkPersona& d )
{
    f_id          = d.f_id;
    f_ref_per_id  = d.f_ref_per_id;
    f_ind_per_id  = d.f_ind_per_id;
    f_conf        = d.f_conf;
    f_comment     = d.f_comment;
}

void recLinkPersona::Clear()
{
    f_id          = 0;
    f_ref_per_id  = 0;
    f_ind_per_id  = 0;
    f_conf        = 0;
    f_comment     = wxEmptyString;
}

void recLinkPersona::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO LinkPersona "
            "(ref_per_id, ind_per_id, conf, comment) "
            "VALUES ("ID", "ID", %f, '%q');",
            f_ref_per_id, f_ind_per_id, f_conf, UTF8_(f_comment)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO LinkPersona "
                "(id, ref_per_id, ind_per_id, conf, comment) "
                "VALUES ("ID", "ID", "ID", %f, '%q');",
                f_id, f_ref_per_id, f_ind_per_id, f_conf, UTF8_(f_comment)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE LinkPersona SET ref_per_id="ID", ind_per_id="ID", "
                "conf=%f, comment='%q' "
                "WHERE id="ID";",
                f_ref_per_id, f_ind_per_id, f_conf,
                UTF8_(f_comment), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recLinkPersona::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT ref_per_id, ind_per_id, conf, comment "
        "FROM LinkPersona WHERE id="ID";",
        f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_ref_per_id  = GET_ID( result.GetInt64( 0 ) );
    f_ind_per_id  = GET_ID( result.GetInt64( 1 ) );
    f_conf        = result.GetDouble( 2 );
    f_comment     = result.GetAsString( 3 );
    return true;
}

/*! Given the per_id and ind_id settings, find the matching record
 *  and read in the full record.
 */
bool recLinkPersona::Find()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_ref_per_id == 0 || f_ind_per_id == 0 ) return false; // Only find single record

    sql.Format(
        "SELECT id, conf, comment FROM LinkPersona "
        "WHERE ref_per_id="ID" AND ind_per_id="ID";",
        f_ref_per_id, f_ind_per_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) return false;
    result.SetRow( 0 );
    f_id   = GET_ID( result.GetInt64( 0 ) );
    f_conf = result.GetDouble( 1 );
    f_comment = result.GetAsString( 2 );
    return true;
}

// End of recLink.cpp file
