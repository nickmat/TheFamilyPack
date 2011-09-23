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
#include <rec/recPersona.h>

#include "tfpWr.h"

wxString tfpWriteReferenceIndex()
{
    wxString htm;

    htm << "<html><head><title>Reference List</title></head><body>"
           "<center><h1>Reference List</h1>";

    wxSQLite3ResultSet result = recReference::GetTitleList();

    if( result.GetColumnCount() > 0 )
    {
        htm << "<table border=1>";
        while( result.NextRow() )
        {
            htm << "<tr><td><a href='R"
                << result.GetAsString( 0 )
                << "'><b>R"
                << result.GetAsString( 0 )
                << "</b></a> </td><td> "
                << result.GetAsString( 1 )
                << "</td></tr>";
        }
        htm << "</table>";
    } else {
        htm << "No References found!";
    }

    htm << "</center></body></html>";

    return htm;
}

wxString tfpWriteReferencePage( idt refID )
{
    wxString htm;
    recReference ref(refID);
    recIdVec perIDs = ref.GetPersonaList();
    recIdVec indIDs;

    htm << "<html><head><title>R" << refID
        << "</title></head><body><h1>" << ref.f_title << "</h1>\n";

    if( ref.f_statement.compare( 0, 9, "<!-- HTML" ) == 0 ) {
        htm << ref.f_statement;
    } else { // treat as text
        htm << "<pre>"
            << ref.f_statement
            << "</pre>";
    }
    htm << "<a href=$R" << refID
        << "><img src=memory:edit.bmp></a><br>";

    for( size_t i = 0 ; i < perIDs.size() ; i++ ) {
        htm << recPersona::GetNameStr( perIDs[i] );
        indIDs = recPersona::GetIndividualIDs( perIDs[i] );
        for( size_t j = 0 ; j < indIDs.size() ; j++ ) {
            htm << " <a href=I" << indIDs[j]
                << "><img src=memory:ind.bmp></a>";
        }
        htm << "<br>";
    }

    htm << "</body></html>";

    return htm;
}

// End of tfpWrReference.cpp Source
