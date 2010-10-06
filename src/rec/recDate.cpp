/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Date records.
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

#include <rec/recDate.h>

const wxString recDate::s_prefStr[recDate::PREF_Max] = {
    _("Unstated"),       // PREF_Unstated
    _("After"),          // PREF_After
    _("On"),             // PREF_On
    _("On or After"),    // PREF_OrAfter
    _("Before"),         // PREF_Before
    _("Not"),            // PREF_Not
    _("On or Before"),   // PREF_OrBefore
	_("About")           // PREF_About
};

const wxString recDate::s_prefFormat[recDate::PREF_Max] = {
    _("%s"),          // PREF_Unstated
    _("aft %s"),      // PREF_After
    _("%s"),          // PREF_On
    _("%s or aft"),   // PREF_OrAfter
    _("bef %s"),      // PREF_Before
    _("not %s"),      // PREF_Not
    _("%s or bef"),   // PREF_OrBefore
	_("abt %s")       // PREF_About
};


void recDate::Clear()
{
    f_jdn = 0;
    f_range = 0;
    f_type = FLG_NULL;
    f_desc = wxEmptyString;
    f_record_sch = CALENDAR_SCH_Unstated;
    f_display_sch = CALENDAR_SCH_Unstated;
}

void recDate::Save()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

	if( f_id == 0 )
	{
		// Add new record
	    sql.Format( 
		    "INSERT INTO Date (jdn, range, type, desc, record_sch, display_sch) "
            "VALUES (%ld, %ld, %u, '%q', %d, %d);",
            f_jdn, f_range, f_type, UTF8_(f_desc), f_record_sch, f_display_sch
	    );
    	s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
	} else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
	        sql.Format( 
		        "INSERT INTO Date (id, jdn, range, type, desc, record_sch, display_sch) "
                "VALUES ("ID", %ld, %ld, %u, '%q', %d, %d);",
                f_id, f_jdn, f_range, f_type, UTF8_(f_desc), f_record_sch, f_display_sch
	        );
        } else {
    		// Update existing record
            sql.Format( 
                "UPDATE Date SET jdn=%ld, range=%ld, type=%u, desc='%q', record_sch=%d, display_sch=%d "
                "WHERE id="ID";", 
                f_jdn, f_range, f_type, UTF8_(f_desc), f_record_sch, f_display_sch, f_id
            );
        }
    	s_db->ExecuteUpdate( sql );
	}
}

bool recDate::Read()
{
	wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
		Clear();
        return false;
    }

	sql.Format( "SELECT * FROM Date WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 ) 
    {
		Clear();
        return false;
    }
    result.SetRow( 0 ); 
    f_jdn         = result.GetInt( 1 );
    f_range       = result.GetInt( 2 );
    f_type        = (TypeFlag) result.GetInt( 3 );
    f_desc        = result.GetAsString( 4 );
    f_record_sch  = (CalendarScheme) result.GetInt( 5 );
    f_display_sch = (CalendarScheme) result.GetInt( 6 );
	return true;
}

// End of recDate.cpp file
