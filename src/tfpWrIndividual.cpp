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
    idt id;
    recIndividual ind( indID );
    recPersona per( ind.f_per_id );
    recIndividual spouse;

    htm << "<html><head><title>Individual "
        << ind.GetIdStr() << "</title></head>"
           "<body><center><table width=100%>";

    // Name
    htm << "<tr><td align=right width=120>Name:</td>"
           "<td><font size=+2><b>" << ind.GetFullName()
        << "</b></font> " << ind.f_epitaph
        << " <a href=$MR" << indID
        << "><img src=memory:fam.bmp></a></td></tr>";

    // Sex
    htm << "<tr><td align=right>ID, Sex:</td><td><b>"
        << ind.GetIdStr() << ", " << recGetSexStr( per.f_sex )
        << "</b></td></tr>";

    // Occupation
    id = per.GetOccAttribute();
    if( id != 0 ) {
        htm << "<tr><td align=right>Occupation:</td><td><b>"
            << recAttribute::GetValue( id )
            << "</b></td></tr>";
    }

    // All Events
    recEventPersonaVec eps = per.ReadEventPersonas();
    for( i = 0 ; i < eps.size() ; i++ ) {
        htm << "<tr><td align=right>"
            << recEvent::GetTypeStr( eps[i].f_event_id )
            << ":</td><td><b>"
            << recEvent::GetDetailStr( eps[i].f_event_id )
            << "</b> <a href=E" << eps[i].f_event_id
            << "><img src=memory:eve.bmp></a></td></tr>";
    }

    // Write out Parents
    recFamilyVec parents = ind.GetParentList();
    // Fathers
    for( i = 0 ; i < parents.size() ; i++ ) {
        if( parents[i].f_husb_id != 0 ) {
            htm << "<tr><td align=right>Father:</td><td><b><a href=I"
                << parents[i].f_husb_id << ">"
                << recIndividual::GetFullName( parents[i].f_husb_id )
                << "</a></b> "
                << recIndividual::GetDateEpitaph( parents[i].f_husb_id )
                << " <a href=$MR" << parents[i].f_husb_id
                << "><img src=memory:fam.bmp></a></td></tr>";
        }
    }
    // Mothers
    for( i = 0 ; i < parents.size() ; i++ ) {
        if( parents[i].f_wife_id != 0 ) {
            htm << "<tr><td align=right>Mother:</td><td><b><a href=I"
                << parents[i].f_wife_id << ">"
                << recIndividual::GetFullName( parents[i].f_wife_id )
                << "</a></b> "
                << recIndividual::GetDateEpitaph( parents[i].f_wife_id )
                << " <a href=$MR" << parents[i].f_wife_id
                << "><img src=memory:fam.bmp></a></td></tr>";
        }
    }

    // Write out Families
    recFamilyVec families = recIndividual::GetFamilyList( indID );
    for( i = 0, cnt = 0 ; i < families.size() ; i++ ) {
        idt spouseID = families[i].f_husb_id;
        if( spouseID == indID ) spouseID = 0;
        if( spouseID == 0 ) spouseID = families[i].f_wife_id;
        if( spouseID == 0 || spouseID == indID ) continue;
        cnt++;
        idt famID = families[i].f_id;
        spouse.f_id = spouseID;
        spouse.Read();

        // Spouse name
        htm << "<tr><td align=right><a href=F"
            << famID << ">Spouse " << cnt << ":</a></td>"
               "<td><b><a href=I"
            << spouseID << ">"
            << spouse.GetFullName() << "</a></b> "
            << spouse.f_epitaph
            << " <a href=$MR" << spouseID
            << "><img src=memory:fam.bmp></a></td></tr>";

        // Union event (marriage)
        idt marEvID = families[i].GetMarriageEvent();
        if( marEvID != 0 ) {
            htm << "<tr><td align=right>"
                << recEvent::GetTypeStr( marEvID )
                << ":</td><td><b>"
                << recEvent::GetDetailStr( marEvID )
                << "</b> <a href=E" << marEvID
                << "><img src=memory:eve.bmp></a></td></tr>";
        }

        // Children
        recIndividualList children = families[i].GetChildren();
        for( j = 0 ; j < children.size() ; j++ ) {
            if( j == 0 ) {
                htm << "<tr><td align=right>Children:</td>";
            } else {
                htm << "<tr><td></td>";
            }
            htm << "<td><b><a href=I"
                << children[j].f_id << ">"
                << children[j].GetFullName() << "</a></b> "
                << children[j].f_epitaph
                << " <a href=$MR" << children[j].f_id
                << "><img src=memory:fam.bmp></a></td></tr>";
        }
    }

    wxSQLite3Table eTable = ind.GetRefAttributesTable();
    for( i = 0 ; i < (size_t) eTable.GetRowCount() ; i++ ) {
        eTable.SetRow( i );
        idt attrID = GET_ID( eTable.GetInt64( 0 ) );
        idt typeID = GET_ID( eTable.GetInt64( 1 ) );
        idt refID = recAttribute::FindReferenceID( attrID );

        htm << "<tr><td align=right>"
            << recAttributeType::GetTypeStr( typeID )
            << ":</td><td><b>"
            << eTable.GetAsString( 2 );
        if( refID != 0 ) {
            htm << " <a href=" << recReference::GetIdStr( refID )
                << "><img src=memory:ref.bmp></a>";
        }
        htm << "</b></td></tr>";
    }
    eTable = ind.GetRefEventsTable();
    for( i = 0 ; i < (size_t) eTable.GetRowCount() ; i++ ) {
        eTable.SetRow( i );
        idt eventID = GET_ID( eTable.GetInt64( 0 ) );
        idt roleID = GET_ID( eTable.GetInt64( 1 ) );
        idt refID = recEvent::FindReferenceID( eventID );

        htm << "<tr><td align=right>"
            << recEventTypeRole::GetName( roleID )
            << ":</td><td><b>"
            << recEvent::GetTitle( eventID );
        if( refID != 0 ) {
            htm << " <a href=" << recReference::GetIdStr( refID )
                << "><img src=memory:ref.bmp></a>";
        }
        htm << "<br>"
            << recEvent::GetDetailStr( eventID )
            << "</b></td></tr>";
    }

    eTable = ind.GetReferencesTable();
    for( i = 0 ; i < (size_t) eTable.GetRowCount() ; i++ ) {
        eTable.SetRow( i );
        idt refID = GET_ID( eTable.GetInt64( 0 ) );

        htm << "<tr><td align=right>"
            << recReference::GetIdStr( refID )
            << ":</td><td><b>"
            << eTable.GetAsString( 1 )
            << " <a href=" << recReference::GetIdStr( refID )
            << "><img src=memory:ref.bmp></a>"
            << "</b></td></tr>";
    }

    htm << "</table></center></body></html>";

    return htm;
}


// End of tfpWrIndividual.cpp Source
