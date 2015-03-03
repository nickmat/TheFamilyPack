/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Name index functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
 * Copyright:   Copyright (c) 2010-2015, Nick Matthews.
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
    wxString htm = tfpWrHeadTfp( "Surname Index" );
    htm << "<h1>Surname Index</h1>\n";

    if( table.GetColumnCount() > 0 )
    {
        wxChar letter = wxChar('\0');
        wxString name;
        wxString rowclass;
        int count = 1, row = 0;
        bool row1st = true;

        htm << "<table class='data'>\n";
        while( table.NextRow() )
        {
            name = table.GetAsString( 0 );
            if( name.length() == 0 ) {
                name = "?";
            }
            if( name.GetChar(0) != letter )
            {
                rowclass = tfpGetRowClass( ++row );
                letter = name.GetChar(0);
                if( row1st == true )
                {
                    row1st = false;
                } else {
                    // End prevous line
                    htm << "\n</td>\n</tr>\n";
                }
                // Start new line
                htm <<
                    "<tr>\n<td class='" << rowclass <<
                    "'><a href='tfp:N" << letter <<
                    "'><b>" << letter <<
                    "</b></a></td>\n<td class='" << rowclass <<
                    "'>"
                ;
                count = 1;
            }
            if( count != 1 )
            {
                htm << ", ";
            }
            htm << 
                "\n<a href='tfp:N" << name <<
                "'><b>" << name <<
                "</b></a>"
            ;
            count++;
        }
        htm << "</tr>\n</table>\n";
    } else {
        htm << "<p>No Names found!</p>\n";
    }

    htm << tfpWrTailTfp();

    return htm;
}

wxString tfpWriteIndividualIndex()
{
    static wxString htm;
    static long lastchange(0);
    if( !htm.IsEmpty() && recDb::GetChange() == lastchange ) {
        return htm;
    }

    wxSQLite3ResultSet table = recIndividual::GetSurnameSet();

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

wxString tfpWriteIndividualList( const wxString& sname )
{
    wxString surname = tfpNormaliseSpaces( sname );

    wxString htm = tfpWrHeadTfp( "Name List" );
    htm << "<h1>" << surname << "</h1>\n";

    wxSQLite3ResultSet result = recIndividual::GetNameSet( surname );

    int row = 0;
    if( ! result.Eof() )
    {
        htm << "<table class='data'>\n";
        while( result.NextRow() )
        {
            wxString rowclass = tfpGetRowClass( ++row );
            idt indID = GET_ID( result.GetInt64( 2 ) );
            htm << 
                "<tr>\n<td class='" << rowclass <<
                "'>\n<a href='tfp:I" << indID <<
                "'><b>" << recIndividual::GetIdStr( indID ) <<
                "</b></a>\n</td>\n<td class='" << rowclass <<
                "'>\n<a href='tfp:FI" << indID <<
                "'><b>" << result.GetAsString( 0 ) <<
                "</b></a> " << result.GetAsString( 1 ) <<
                "&nbsp;&nbsp;\n<a href='tfpc:MR" << indID <<
                "'><img src=memory:fam.png></a>\n</td>\n</tr>\n";
        }
        htm << "</table>\n";
    } else {
        htm << "<p>No Names found!</p>\n";
    }

    htm << tfpWrTailTfp();

    return htm;
}

// End of tfpWrName.cpp Source
