/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Name index functions.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

#include <rec/recIndividual.h>
#include <rec/recPersona.h>

#include "tfpWr.h"


static wxString WriteIndex( wxSQLite3ResultSet& table )
{
	wxString htm = 
		"<html><head><title>Surname Index</title></head><body>"
		"<center><h1>Surname Index</h1>";

    if( table.GetColumnCount() > 0 )
	{
        wxChar letter = wxChar('\0');
        wxString name = wxEmptyString;
        int count = 1;
        bool row1st = true;

		htm << wxT("<table border=1>");
        while( table.NextRow() )
		{
            name = table.GetAsString( 0 );
            if( name.length() == 0 ) {
                name = "?";
            }
            if( name.GetChar(0) != letter )
            {
                letter = name.GetChar(0);
                if( row1st == true )
                {
                    row1st = false;
                } else {
                    // End prevous line
                    htm << wxT("</tr>");
                }
                // Start new line
                htm << wxT("<tr><td><a href='N") << letter << wxT("'><b>") << letter << wxT("</b></a></td><td>");
                count = 1;
            }
            if( count != 1 )
            {
                htm << wxT(", ");
            }
            htm << wxT("<a href='N") << name << wxT("'><b>") << name << wxT("</b></a>");
            count++;
		}
		htm << wxT("</tr></table>");
    } else {
        htm << wxT("No Names found!");
    }

    htm << wxT("</center></body></html>");

    return htm;
}

wxString tfpWriteIndividualIndex()
{
    static wxString htm;
    static long lastchange(0);
    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    wxSQLite3ResultSet table = recIndividual::GetSurnameList();

    htm = WriteIndex( table );
    lastchange = recDb::GetChange();
    return htm;
}

wxString tfpWritePersonIndex()
{
    static wxString htm;
    static long lastchange(0);
    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    wxSQLite3ResultSet table = recNamePart::GetSurnameList();

    htm = WriteIndex( table );
    lastchange = recDb::GetChange();
    return htm;
}

wxString tfpWriteIndividualList( const wxString& surname )
{
	wxString htm;

    htm << wxT("<html><head><title>Name List</title></head><body>")
        << wxT("<center><h1>") << surname << wxT("</h1>");

    wxSQLite3ResultSet result = recIndividual::GetNameList( surname );

    if( result.GetColumnCount() > 0 )
	{
		htm << wxT("<table border=1>");
        while( result.NextRow() )
		{
            htm << wxT("<tr><td><a href='F") 
				<< result.GetAsString( 3 ) 
				<< wxT("'><b>")

			    << result.GetAsString( 1 ) << wxT(" ")
				<< result.GetAsString( 0 )

			    << wxT("</b></a> ")
				<< result.GetAsString( 2 )
				<< wxT("</td></tr>");
		}
		htm << wxT("</table>");
    } else {
        htm << wxT("No Names found!");
    }

    htm << wxT("</center></body></html>");

    return htm;
}

// End of tfpWrName.cpp Source
