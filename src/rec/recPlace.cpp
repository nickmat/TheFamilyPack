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


recPlace::recPlace( const recPlace& p )
{
    f_id       = p.f_id;
    f_date1_id = p.f_date1_id;
    f_date2_id = p.f_date2_id;
}

void recPlace::Clear()
{
    f_id       = 0;
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

void recPlace::SetAddress( id_t placeID, const wxString& str )
{
	recPlacePartList ppList = GetPlaceParts( placeID );
	if( ppList.size() == 0 )
	{
		recPlacePart pp;
		pp.Clear();
		pp.f_type_id = recPlacePartType::TYPE_Address;
		pp.f_place_id = placeID;
		pp.f_val = str;
		pp.Save();
	} else {
		ppList[0].f_type_id = recPlacePartType::TYPE_Address;
		ppList[0].f_val = str;
		ppList[0].Save();
		for( size_t i = 1 ; i < ppList.size() ; i++ ) {
			ppList[i].Delete();
		}
	}
}

wxString recPlace::GetAddressStr( id_t id )
{
    if( id == 0 ) return wxEmptyString;

	wxString str;
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    sql.Format(
        "SELECT val FROM PlacePart WHERE place_id="ID" "
        "ORDER BY sequence;", id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() > 0 )
	{
        for( int row = 0 ; row < result.GetRowCount() ; row++ )
		{
            if( row > 0 )
            {
                str << wxT(", ");
            }
            result.SetRow( row );
            str << result.GetAsString( 0 );
		}
    }
    return str;
}

recPlacePartList recPlace::GetPlaceParts( id_t placeID )
{
	wxString str;
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;
	recPlacePart pp;
	recPlacePartList ppList;

    sql.Format(
        "SELECT * FROM PlacePart WHERE place_id="ID" ORDER BY sequence;",
        placeID
    );
    result = s_db->GetTable( sql );

    for( int row = 0 ; row < result.GetRowCount() ; row++ )
	{
        result.SetRow( row );
		pp.f_id       = GET_ID( result.GetInt64( 0 ) );
        pp.f_type_id  = GET_ID( result.GetInt64( 1 ) );
        pp.f_place_id = GET_ID( result.GetInt64( 2 ) );
        pp.f_val      = result.GetAsString( 3 );
        pp.f_sequence = result.GetInt( 4 );
        ppList.push_back( pp );
	}
    return ppList;
}


//----------------------------------------------------------

recPlacePart::recPlacePart( const recPlacePart& pp )
{
    f_id       = pp.f_id;
    f_type_id  = pp.f_type_id;
    f_place_id = pp.f_place_id;
    f_val      = pp.f_val;
    f_sequence = pp.f_sequence;
}

void recPlacePart::Clear()
{
    f_id       = 0;
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

//----------------------------------------------------------

recPlacePartType::recPlacePartType( const recPlacePartType& ppt )
{
    f_id   = ppt.f_id;
    f_name = ppt.f_name;
}

void recPlacePartType::Clear()
{
    f_id   = 0;
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
