/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recRelationship.cpp
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include <rec/recRelationship.h>
#include <rec/recPersona.h>


recRelationship::recRelationship( const recRelationship& attr )
{
    f_id      = attr.f_id;
    f_per1_id = attr.f_per1_id;
    f_per2_id = attr.f_per2_id;
    f_descrip = attr.f_descrip;
}

void recRelationship::Clear()
{
    f_id      = 0;
    f_per1_id = 0;
    f_per2_id = 0;
    f_descrip = wxEmptyString;
}

void recRelationship::Save()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO Relationship (per1_id, per2_id, descrip)"
            "VALUES ("ID", "ID", '%q');",
            f_per1_id, f_per2_id, UTF8_(f_descrip)
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO Relationship (id, per1_id, per2_id, descrip)"
                "VALUES ("ID", "ID", "ID", '%q', %u);",
                f_id, f_per1_id, f_per2_id, UTF8_(f_descrip)
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE Relationship SET per1_id="ID", per2_id="ID", descrip='%q' WHERE id="ID";",
                f_per1_id, f_per2_id, UTF8_(f_descrip), f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recRelationship::Read()
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format( "SELECT per1_id, per2_id, descrip FROM Relationship WHERE id="ID";", f_id );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_per1_id = GET_ID( result.GetInt64( 0 ) );
    f_per2_id = GET_ID( result.GetInt64( 1 ) );
    f_descrip = result.GetAsString( 2 );
    return true;
}

wxString recRelationship::GetIdStr( idt relID )
{
    return wxString::Format( "Rs"ID, relID );
}

wxString recRelationship::GetValue1Str() const
{
    wxString str;

    str << recPersona::GetNameStr( f_per1_id )
        << _(" is the ")
        << f_descrip
        << _(" of ")
        << recPersona::GetNameStr( f_per2_id );

    return str;
}

wxString recRelationship::GetValue1Str( idt relID )
{
    recRelationship rel(relID);
    return rel.GetValue1Str();
}

wxString recRelationship::GetValue2Str() const
{
    wxString str;

    str << recPersona::GetNameStr( f_per2_id )
        << _(" has ")
        << f_descrip
        << _(" who is ")
        << recPersona::GetNameStr( f_per1_id );

    return str;
}

wxString recRelationship::GetValue2Str( idt relID )
{
    recRelationship rel(relID);
    return rel.GetValue2Str();
}

wxString recRelationship::GetRelOfPersonaStr( idt perID ) const
{
    wxString str;

    if( perID == f_per1_id ) {
        str << f_descrip
            << _(" of ")
            << recPersona::GetNameStr( f_per2_id );
    } else if( perID == f_per2_id ) {
        str << f_descrip
            << _(" is ")
            << recPersona::GetNameStr( f_per1_id );
    } else {
        str << _("None");
    }
    return str;
}

wxString recRelationship::GetRelOfPersonaStr( idt perID, idt relID )
{
    recRelationship rel(relID);
    return rel.GetRelOfPersonaStr( perID );
}

// End of recRelationship.cpp file
