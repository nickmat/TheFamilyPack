/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
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

#include <rec/recPlace.h>


void recPlace::Clear()
{
    f_date1_id = 0;
    f_date2_id = 0;
}

void recPlace::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO Place (date1_id, date2_id) VALUES ("ID", "ID");",
            f_date1_id, f_date2_id
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO Place (id, date1_id, date2_id)"
			    "VALUES ("ID", "ID", "ID");",
                f_id, f_date1_id, f_date2_id
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE Place SET date1_id="ID", date2_id="ID" WHERE id="ID";", 
                f_date1_id, f_date2_id, f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recPlace::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM Place WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_date1_id = GET_ID( result.GetInt64( 1 ) );
    f_date2_id = GET_ID( result.GetInt64( 2 ) );
	return true;
}

void recPlacePart::Clear()
{
    f_type_id  = 0;
    f_place_id = 0;
    f_val      = wxEmptyString;
    f_sequence = 0;
}

void recPlacePart::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO PlacePart (type_id, place_id, val, sequence) "
            "VALUES ("ID", "ID", '%q', %u);",
            f_type_id, f_place_id, UTF8_(f_val), f_sequence
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO PlacePart (id, type_id, place_id, val, sequence) "
                "VALUES ("ID", "ID", "ID", '%q', %u);",
                f_id, f_type_id, f_place_id, UTF8_(f_val), f_sequence
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE PlacePart SET type_id="ID", place_id="ID", val='%q', sequence=%u "
                "WHERE id="ID";", 
                f_type_id, f_place_id, UTF8_(f_val), f_sequence, f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recPlacePart::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM PlacePart WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_type_id  = GET_ID( result.GetInt64( 1 ) );
    f_place_id = GET_ID( result.GetInt64( 2 ) );
    f_val      = result.GetAsString( 3 );
    f_sequence = result.GetInt( 4 );
	return true;
}

void recPlacePartType::Clear()
{
    f_name = wxEmptyString;
}

void recPlacePartType::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO PlacePartType (name) VALUES ('%q');",
            UTF8_(f_name)
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO PlacePartType (id, name)"
			    "VALUES ("ID", '%q');",
                f_id, UTF8_(f_name)
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE PlacePartType SET name='%q' WHERE id="ID";", 
                UTF8_(f_name), f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recPlacePartType::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM PlacePartType WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_name = result.GetAsString( 1 );
	return true;
}

// End of recPlace.cpp file
