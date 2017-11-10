/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrName.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Name index functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
 * Copyright:   Copyright (c) 2010 ~ 2017, Nick Matthews.
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

#include <set>


static const char* GetSurnameGroupCode( recSurnameGroup sng )
{
    const char* code[recSG_MAX] = { "D", "I", "P", "A" };
    return code[sng];
}

static wxString WriteIndex( wxSQLite3ResultSet& table, recSurnameGroup sng )
{
    const char* title[recSG_MAX] = {
        "Individual Default",
        "Individual",
        "Persona",
        "All"
    };
    const char* sng_code = GetSurnameGroupCode( sng );
    const char* sng_lcode = ( sng == recSG_Individual ) ? "D" : sng_code;

    wxString htm = tfpWrHeadTfp( "Surname Index" );
    htm << "<h1>" << title[sng] << " Surname Index</h1>\n";

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
                    "'>" << letter <<
                    "</td>\n<td class='" << rowclass <<
                    "'>"
                ;
                count = 1;
            }
            if( count != 1 )
            {
                htm << ", ";
            }
            htm << 
                "\n<a href='tfp:N" << sng_code << "+" << name <<
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

wxString tfpWriteSurnameIndex( recSurnameGroup sng )
{
    static wxString htm[recSG_MAX];
    static long lastchange[recSG_MAX] = { 0, 0, 0, 0 };
    if ( !htm[sng].empty() && recDb::GetChange() == lastchange[sng] ) {
        return htm[sng];
    }

    wxSQLite3ResultSet table = recName::GetSurnameIndex( sng );

    htm[sng] = WriteIndex( table, sng );
    lastchange[sng] = recDb::GetChange();
    return htm[sng];
}

struct NameEntry
{
    idt m_id;
    wxString m_surname;
    wxString m_full;
    wxString m_epitaph;
    idt m_style_id;

    bool operator<( const NameEntry& x ) const
    {
        if ( m_surname != x.m_surname ) {
            return m_surname < x.m_surname;
        }
        if ( m_full != x.m_full ) {
            return m_full < x.m_full;
        }
        return m_id < x.m_id;
    }
};

wxString tfpWriteNameList( const wxString& sname, recSurnameGroup sng )
{
    recNameVec names = recName::GetNameList( sname, sng );
    std::set<NameEntry> order;
    NameEntry ent;
    for( auto name : names ) {
        if ( name.FGetIndID() != 0 ) {
            ent.m_id = name.FGetIndID();
            ent.m_epitaph = recIndividual::GetEpitaph( ent.m_id );
        } else {
            ent.m_id = name.FGetPerID();
            ent.m_epitaph = "";
        }
        ent.m_id = ( name.FGetIndID() == 0 ) ? name.FGetPerID() : name.FGetIndID();
        ent.m_surname = name.GetSurname();
        ent.m_full = name.GetNameStr();
        ent.m_style_id = name.FGetTypeID();
        order.insert( ent );
    }
    char sng_letter = ( sng == recSG_Persona ) ? 'P' : 'I';

    wxString htm = tfpWrHeadTfp( "Name List" );
    htm << "<h1>" << sname << "</h1>\n";

    htm << "<table class='data'>\n";
    int row = 0;
    for ( auto entry : order ) {
        wxString rowclass = tfpGetRowClass( ++row );
        wxString id_str = ( sng != recSG_Persona ) ?
            recIndividual::GetIdStr( entry.m_id ) : recPersona::GetIdStr( entry.m_id );
        htm <<
            "<tr>\n<td class='" << rowclass <<
            "'><a href='tfp:" << id_str <<
            "'><b>" << id_str <<
            "</b></a></td>\n"
        ;
        if ( sng == recSG_Persona ) {
            wxString ref_str = recReference::GetIdStr( recPersona::GetRefID( entry.m_id ) );
            htm <<
                "<td class='" << rowclass <<
                "'><a href='tfp:Pa" << entry.m_id <<
                "'><b>" << entry.m_full <<
                "</b></a></td>\n<td class='" << rowclass <<
                "'>" << recNameStyle::GetStyleStr( entry.m_style_id ) <<
                "</td>\n<td class='" << rowclass <<
                "'><a href='tfp:" << ref_str <<
                "'><b>" << ref_str << "</b>"
            ;
        } else {
            htm <<
                "<td class='" << rowclass <<
                "'><a href='tfp:FI" << entry.m_id <<
                "'><b>" << entry.m_full <<
                "</b></a> " << entry.m_epitaph <<
                "&nbsp;&nbsp;\n<a href='tfpc:MR" << entry.m_id <<
                "'><img src=memory:fam.png></a>"
                "</td>\n<td class='" << rowclass <<
                "'>" << recNameStyle::GetStyleStr( entry.m_style_id )
            ;
        }
        htm << "</td>\n</tr>\n";
    }
    htm << "</table>\n";

    htm << tfpWrTailTfp();
    return htm;
}

wxString tfpWriteIndividualList()
{
    wxString htm = tfpWrHeadTfp( "Name List" );
    htm << "<h1>Individual List</h1>\n";

    wxSQLite3ResultSet result = recIndividual::GetNameSet();

    int row = 0;
    if ( !result.Eof() )
    {
        htm << "<table class='data'>\n";
        while ( result.NextRow() )
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
