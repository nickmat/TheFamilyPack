/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrReference.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Reference Entity functions.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
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

#include <rec/recReference.h>

#include "tfpWr.h"

wxString tfpWriteReferenceIndex()
{
	wxString htm;

	htm = "<html><head><title>Name List</title></head><body>"
		  "<center><h1>Persona Name List Not Yet Done</h1></center></body></html>";

#if 0
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
#endif
    return htm;
}

wxString tfpWriteReferencePage( id_t refID )
{
    wxString htm;
    recReference ref(refID);

    htm << wxT("<html><head><title>R") << refID
        << wxT("</title></head><body><h1>") << ref.f_title
        << wxT("</h1>\n<pre>")
        << ref.f_statement
        << wxT("</pre></body></html>");

    return htm;
}

// End of tfpWrReference.cpp Source
