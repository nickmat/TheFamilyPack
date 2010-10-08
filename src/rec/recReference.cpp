/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Reference and ReferenceEntity records.
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

#include <rec/recReference.h>


void recReference::Clear()
{
    f_id = 0;
    f_title     = wxEmptyString;
    f_statement = wxEmptyString;
}

void recReference::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
            "INSERT INTO Reference (title, statement)"
            "VALUES ('%q', '%q');",
            UTF8_(f_title), UTF8_(f_statement)
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
                "INSERT INTO Reference (id, title, statement)"
                "VALUES ("ID", '%q', '%q');",
                f_id, UTF8_(f_title), UTF8_(f_statement)
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE Reference SET title='%q', statement='%q' WHERE id="ID";",
                UTF8_(f_title), UTF8_(f_statement), f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recReference::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

    sql.Format( "SELECT * FROM Reference WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_title     = result.GetAsString( 1 );
    f_statement = result.GetAsString( 2 );
	return true;
}

//----------------------------------------------------------

void recReferenceEntity::Clear()
{
    f_id = 0;
    f_ref_id      = 0;
    f_entity_type = TYPE_Unstated;
    f_entity_id   = 0;
}

void recReferenceEntity::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
            "INSERT INTO ReferenceEntity (ref_id, entity_type, entity_id)"
            "VALUES ("ID", %u, "ID");",
            f_ref_id, f_entity_type, f_entity_id
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
                "INSERT INTO ReferenceEntity (id, ref_id, entity_type, entity_id)"
                "VALUES ("ID", "ID", %u, "ID");",
                f_id, f_ref_id, f_entity_type, f_entity_id
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE ReferenceEntity SET "
                "ref_id="ID", entity_type=%u, entity_id="ID" WHERE id="ID";",
                f_ref_id, f_entity_type, f_entity_id, f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recReferenceEntity::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

    sql.Format( "SELECT * FROM ReferenceEntity WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_ref_id      = GET_ID( result.GetInt64( 1 ) );
    f_entity_type = (Type) result.GetInt( 2 );
    f_entity_id   = GET_ID( result.GetInt64( 3 ) );
	return true;
}

// End of recReference.cpp file
