/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrIndividual.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen for a Individual function.
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
#include <rec/recEvent.h>
#include <rec/recPersona.h>
#include <rec/recReference.h>

#include "tfpWr.h"

wxString tfpWriteIndividualPage( idt indID )
{
    wxString htm;
    size_t i, j, cnt;
    recIndividual ind( indID );
    recIndividual spouse;

    htm << wxT("<html><head><title>Individual I ")
        << indID << wxT("</title></head>")
           wxT("<body><center><table width=100%>");

    htm << wxT("<tr><td align=right width=120>Name:</td>")
           wxT("<td><font size=+2><b>") << ind.GetFullName()
        << wxT("</b></font> ") << ind.f_epitaph
        << wxT(" <a href=$MR") << indID
        << wxT("><img src=memory:fam.bmp></a></td></tr>");

    htm << wxT("<tr><td align=right>ID, Sex:</td><td><b>I ")
        << indID << wxT(", ") << recGetSexStr( ind.f_sex )
        << wxT("</b></td></tr>");

    if( ind.f_birth_id != 0 ) {
        htm << wxT("<tr><td align=right>Birth:</td><td><b>")
            << recEvent::GetDetailStr( ind.f_birth_id )
            << wxT("</b></td></tr>");
    }
    if( ind.f_nr_birth_id != 0 ) {
        htm << wxT("<tr><td align=right>")
            << recEvent::GetTypeStr( ind.f_nr_birth_id )
            << wxT(":</td><td><b>")
            << recEvent::GetDetailStr( ind.f_nr_birth_id )
            << wxT("</b></td></tr>");
    }
    if( ind.f_death_id != 0 ) {
        htm << wxT("<tr><td align=right>Death:</td><td><b>")
            << recEvent::GetDetailStr( ind.f_death_id )
            << wxT("</b></td></tr>");
    }
    if( ind.f_nr_death_id != 0 ) {
        htm << wxT("<tr><td align=right>")
            << recEvent::GetTypeStr( ind.f_nr_death_id )
            << wxT(":</td><td><b>")
            << recEvent::GetDetailStr( ind.f_nr_death_id )
            << wxT("</b></td></tr>");
    }
    if( ind.f_occ_id != 0 ) {
        htm << wxT("<tr><td align=right>Occupation:</td><td><b>")
            << recAttribute::GetValue( ind.f_occ_id )
            << wxT("</b></td></tr>");
    }
    // Write out Parents
    recFamily parents;
    parents.ReadParents( indID );
    if( parents.f_husb_id != 0 ) {
        htm << wxT("<tr><td align=right>Father:</td><td><b><a href=I")
            << parents.f_husb_id << wxT(">")
            << recIndividual::GetFullName( parents.f_husb_id )
            << wxT("</a></b> ")
            << recIndividual::GetDateEpitaph( parents.f_husb_id )
            << wxT(" <a href=$MR") << parents.f_husb_id
            << wxT("><img src=memory:fam.bmp></a></td></tr>");
    }
    if( parents.f_wife_id != 0 ) {
        htm << wxT("<tr><td align=right>Mother:</td><td><b><a href=I")
            << parents.f_wife_id << wxT(">")
            << recIndividual::GetFullName( parents.f_wife_id )
            << wxT("</a></b> ")
            << recIndividual::GetDateEpitaph( parents.f_wife_id )
            << wxT(" <a href=$MR") << parents.f_wife_id
            << wxT("><img src=memory:fam.bmp></a></td></tr>");
    }

    // Write out Families
    recFamilyList families = recIndividual::GetFamilyList( indID );
    for( i = 0, cnt = 0 ; i < families.size() ; i++ ) {
        idt spouseID = families[i].f_husb_id;
        if( spouseID == indID ) spouseID = 0;
        if( spouseID == 0 ) spouseID = families[i].f_wife_id;
        if( spouseID == 0 || spouseID == indID ) continue;
        cnt++;
        idt famID = families[i].f_id;
        spouse.f_id = spouseID;
        spouse.Read();

        htm << wxT("<tr><td align=right><a href=F")
            << famID << wxT(">Spouse ") << cnt << wxT(":</a></td>")
               wxT("<td><b><a href=I")
            << spouseID << wxT(">")
            << spouse.GetFullName() << wxT("</a></b> ")
            << spouse.f_epitaph
            << wxT(" <a href=$MR") << spouseID
            << wxT("><img src=memory:fam.bmp></a></td></tr>");

        if( families[i].f_event_id != 0 ) {
            htm << wxT("<tr><td align=right>")
                << recEvent::GetTypeStr( families[i].f_event_id )
                << wxT(":</td><td><b>")
                << recEvent::GetDetailStr( families[i].f_event_id )
                << wxT("</b></td></tr>");
        }

        recIndividualList children = families[i].GetChildren();
        for( j = 0 ; j < children.size() ; j++ ) {
            if( j == 0 ) {
                htm << wxT("<tr><td align=right>Children:</td>");
            } else {
                htm << wxT("<tr><td></td>");
            }
            htm << wxT("<td><b><a href=I")
                << children[j].f_id << wxT(">")
                << children[j].GetFullName() << wxT("</a></b> ")
                << children[j].f_epitaph
                << wxT(" <a href=$MR") << children[j].f_id
                << wxT("><img src=memory:fam.bmp></a></td></tr>");
        }
    }

    wxSQLite3Table eTable = ind.GetAttributesTable();
    for( i = 0 ; i < (size_t) eTable.GetRowCount() ; i++ ) {
        eTable.SetRow( i );
        idt attrID = GET_ID( eTable.GetInt64( 0 ) );
        idt typeID = GET_ID( eTable.GetInt64( 1 ) );
        idt refID = recAttribute::FindReferenceID( attrID );

        htm << "<tr><td align=right>"
            << recAttributeType::GetTypeStr( typeID )
            << wxT(":</td><td><b>")
            << eTable.GetAsString( 2 );
        if( refID != 0 ) {
            htm << wxT(" <a href=R") << refID
                << wxT("><img src=memory:ref.bmp></a>");
        }
        htm << "</b></td></tr>";
    }

    eTable = ind.GetEventsTable();
    for( i = 0 ; i < (size_t) eTable.GetRowCount() ; i++ ) {
        eTable.SetRow( i );
        idt eventID = GET_ID( eTable.GetInt64( 0 ) );
        idt roleID = GET_ID( eTable.GetInt64( 1 ) );
        idt refID = recEvent::FindReferenceID( eventID );

        htm << wxT("<tr><td align=right>")
            << recEventTypeRole::GetName( roleID )
            << wxT(":</td><td><b>")
            << recEvent::GetTitle( eventID );
        if( refID != 0 ) {
            htm << wxT(" <a href=R") << refID
                << wxT("><img src=memory:ref.bmp></a>");
        }
        htm << wxT("<br>")
            << recEvent::GetDetailStr( eventID )
            << wxT("</b></td></tr>");
    }

    eTable = ind.GetReferencesTable();
    for( i = 0 ; i < (size_t) eTable.GetRowCount() ; i++ ) {
        eTable.SetRow( i );
        idt refID = GET_ID( eTable.GetInt64( 0 ) );

        htm << wxT("<tr><td align=right>R")
            << refID
            << wxT(":</td><td><b>")
            << eTable.GetAsString( 1 )
            << wxT(" <a href=R") << refID
            << wxT("><img src=memory:ref.bmp></a>")
            << wxT("</b></td></tr>");
    }

    htm << wxT("</table></center></body></html>");

    return htm;
}


// End of tfpWrIndividual.cpp Source
