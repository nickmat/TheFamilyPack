/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrFamily.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Family page functions.
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

#include "tfpWr.h"


wxString tfpWriteFamilyPage( idt famID )
{
    size_t i;
    wxString htm;

    recFamily fam, husbFam, wifeFam;
    recIndividual husb, wife;

    fam.f_id = famID;
    fam.Read();
    husb.f_id = fam.f_husb_id;
    husb.Read();
    husbFam.ReadParents( husb.f_id );
    wife.f_id = fam.f_wife_id;
    wife.Read();
    wifeFam.ReadParents( wife.f_id );
    recIndividualList kids = fam.GetChildren();
    recFamilyList husbWives = recIndividual::GetFamilyList( husb.f_id );
    recFamilyList wifeHusbs = recIndividual::GetFamilyList( wife.f_id );

    htm << wxT("<html><head><title>Family F") << famID << wxT("</title></head>")
           wxT("<body><center>")
           wxT("<table border=1>")
           wxT("<tr><td align=center width=255>");

    // Husband's Father
    if( fam.f_husb_id != 0 ) {
        if( husbFam.f_husb_id == 0 ) {
            htm << wxT("<a href=$IM") << fam.f_husb_id
                << wxT("><img src=memory:edit.bmp></a>");
        } else {
            htm << wxT("<b><a href=F") << husbFam.f_id << wxT(">")
                << recIndividual::GetFullName( husbFam.f_husb_id )
                << wxT("</a></b><br>")
                << recIndividual::GetDateEpitaph( husbFam.f_husb_id );
        }
    } else {
        htm << wxT("&nbsp;");
    }
    htm << wxT("</td><td align=center width=255>");

    // Wife's Father
    if( fam.f_wife_id != 0 ) {
        if( wifeFam.f_husb_id == 0 ) {
            htm << wxT("<a href=$IM") << fam.f_wife_id
                << wxT("><img src=memory:edit.bmp></a>");
        } else {
            htm << wxT("<b><a href='F") << wifeFam.f_id << wxT("'>")
                << recIndividual::GetFullName( wifeFam.f_husb_id )
                << wxT("</a></b><br>")
                << recIndividual::GetDateEpitaph( wifeFam.f_husb_id );
        }
    }
    htm << wxT("</td></tr><tr><td align=center width=255>");

    // Husband's Mother
    if( fam.f_husb_id != 0 ) {
        if( husbFam.f_wife_id == 0 ) {
            htm << wxT("<a href=$IF") << fam.f_husb_id
                << wxT("><img src=memory:edit.bmp></a>");
        } else {
            htm << wxT("<b><a href=F") << husbFam.f_id << wxT(">")
                << recIndividual::GetFullName( husbFam.f_wife_id )
                << wxT("</a></b><br>")
                << recIndividual::GetDateEpitaph( husbFam.f_wife_id );
        }
    } else {
        htm << wxT("&nbsp;");
   }
    htm << wxT("</td><td align=center width=255>");

    // Wife's Mother
    if( fam.f_wife_id != 0 ) {
        if( wifeFam.f_wife_id == 0 ) {
            htm << wxT("<a href=$IF") << fam.f_wife_id
                << wxT("><img src=memory:edit.bmp></a>");
        } else {
            htm << wxT("<b><a href='F") << wifeFam.f_id << wxT("'>")
                << recIndividual::GetFullName( wifeFam.f_wife_id )
                << wxT("</a></b><br>")
                << recIndividual::GetDateEpitaph( wifeFam.f_wife_id );
        }
    }
    htm << wxT("</td></tr></table><br>&nbsp;");

    // Marriage details
    htm << wxT("<table><tr><td align=center width=540>")
        << wxT(" m. ") << recEvent::GetDetailStr( fam.f_event_id )
        << wxT("</td></tr></table>");

    // Family spouses
    htm << wxT("<table border=1><tr><td colspan=2 align=center width=270>");
    if( fam.f_husb_id == 0 ) {
        htm << wxT("<a href=$IH") << fam.f_wife_id
            << wxT("><img src=memory:edit.bmp></a>");
    } else {
        htm << wxT("<font size=+1><b>")
            << recIndividual::GetFullName( fam.f_husb_id )
            << wxT("</b></font><br>")
            << recIndividual::GetDateEpitaph( fam.f_husb_id );
    }
    htm << wxT("</td><td colspan=2 align=center width=270>");
    if( fam.f_wife_id == 0 ) {
        htm << wxT("<a href=$IW") << fam.f_husb_id
            << wxT("><img src=memory:edit.bmp></a>");
    } else {
        htm << wxT("<font size=+1><b>")
            << recIndividual::GetFullName( fam.f_wife_id )
            << wxT("</b></font><br>")
            << recIndividual::GetDateEpitaph( fam.f_wife_id );
    }
    // Write default Events
    htm << wxT("</td></tr><font size=-1><tr align=left><td width=60><b>Birth</b></td><td width=210>")
        << recEvent::GetDetailStr( husb.f_birth_id )
        << wxT("</td><td width=60><b>Birth</b></td><td width=210>")
        << recEvent::GetDetailStr( wife.f_birth_id )
        << wxT("</td></tr>");

    htm << wxT("<tr align=left><td width=60><b>Baptism</b></td><td width=210>")
        << recEvent::GetDetailStr( husb.f_nr_birth_id )
        << wxT("</td><td width=60><b>Baptism</b></td><td width=210>")
        << recEvent::GetDetailStr( wife.f_nr_birth_id )
        << wxT("</td></tr>");

    htm << wxT("<tr align=left><td width=60><b>Death</b></td><td width=210>")
        << recEvent::GetDetailStr( husb.f_death_id )
        << wxT("</td><td width=60><b>Death</b></td><td width=210>")
        << recEvent::GetDetailStr( wife.f_death_id )
        << wxT("</td></tr>");

    htm << wxT("<tr align=left><td width=60><b>Burial</b></td><td width=210>")
        << recEvent::GetDetailStr( husb.f_nr_death_id )
        << wxT("</td><td width=60><b>Burial</b></td><td width=210>")
        << recEvent::GetDetailStr( wife.f_nr_death_id )
        << wxT("</td></tr>");

    htm << wxT("<tr align=left><td width=60><b>Occ</b></td><td width=210>")
        << recAttribute::GetValue( husb.f_occ_id )
        << wxT("</td><td width=60><b>Occ</b></td><td width=210>")
        << recAttribute::GetValue( wife.f_occ_id )
        << wxT("</td></tr></font>")

        << wxT("</table>");

    // Write status, Edit and chart links
    htm << wxT("<table><tr><td align=left width=80>");

    if( fam.f_husb_id != 0 ) {
        htm << wxT("<a href=$MH") << fam.f_husb_id
            << wxT("><img src=memory:menu.bmp></a> <b>I ")
            << fam.f_husb_id << wxT("</b>");
    }
    htm << wxT("</td><td align=center width=110>");
    if( fam.f_husb_id != 0 ) {
        htm << wxT("<a href=I") << fam.f_husb_id
            << wxT("><img src=memory:ind.bmp></a>");
    }
    if( husbFam.f_husb_id != 0 || husbFam.f_wife_id != 0 )
    {
        htm << wxT("&nbsp<a href=CP") << fam.f_husb_id
            << wxT("><img src=memory:pcht.bmp></a>");
    }
    if( kids.size() > 0 )
    {
        htm << wxT("&nbsp;<a href=CD") << fam.f_husb_id
            << wxT("><img src=memory:dcht.bmp></a>");
    }
    htm << wxT("</td>");

    htm << wxT("<td align=center width=160>");
    if( fam.f_id != 0 ) {
        htm << wxT("<a href=$MF") << fam.f_id
            << wxT("><img src=memory:menu.bmp></a> <b>F")
            << fam.f_id << wxT("</b>");
    }

    htm << wxT("</td><td align=center width=110>");

    if( fam.f_wife_id != 0 ) {
        htm << wxT("<a href=I") << fam.f_wife_id
            << wxT("><img src=memory:ind.bmp></a>");
    }
    if( wifeFam.f_husb_id != 0 || wifeFam.f_wife_id != 0 )
    {
        htm << wxT("&nbsp<a href=CP") << fam.f_wife_id
            << wxT("><img src=memory:pcht.bmp></a>");
    }
    if( kids.size() > 0 ) {
        htm << wxT("&nbsp<a href=CD") << fam.f_wife_id
            << wxT("><img src=memory:dcht.bmp></a>");
    }
    htm << wxT("</td><td align=right width=80>");

    if( fam.f_wife_id != 0 ) {
        htm << wxT("<b> I ") << fam.f_wife_id << wxT("</b>")
            << wxT(" <a href=$MW") << fam.f_wife_id
            << wxT("><img src=memory:menu.bmp></a>");
    }
    htm << wxT("</td></tr></table>");

    if( kids.size() > 0 ) {
        htm << wxT("<br>&nbsp;<table border=1>");
        for( i = 0 ; i < kids.size() ; i++ ) {
            htm << wxT("<tr><td align=center width=300><b><a href='F")
                << kids[i].f_fam_id << wxT("'>")                // FamID,
                << kids[i].GetFullName()
                << wxT("</a></b>&nbsp;&nbsp;")
                << kids[i].f_epitaph
                << wxT("</td></tr>");
        }
        htm << wxT("</table>");
    }

    if( husbWives.size() > 1 || wifeHusbs.size() > 1 ) {
        htm << wxT("<br>&nbsp;<table><tr><td align=left valign=top width=270>");
        if( husbWives.size() > 1 ) {
            htm << wxT("<table>");
            for( i = 0 ; i < husbWives.size() ; i++ ) {
                if( husbWives[i].f_wife_id == wife.f_id ) continue;
                htm << wxT("<tr><td align=left width=270><b><a href='F")
                    << husbWives[i].f_id << wxT("'>");                     // FamID,
                if( husbWives[i].f_wife_id == 0 ) {
                    htm << wxT("[Unknown]");
                } else {
                    htm << recIndividual::GetFullName( husbWives[i].f_wife_id );   //  Name
                }
                htm << wxT("</a></b>&nbsp;&nbsp;")
                    << recIndividual::GetDateEpitaph( husbWives[i].f_wife_id )
                    << wxT("</td></tr>");
            }
            htm << wxT("</table>");
        }
        htm << wxT("</td><td align=right valign=top width=270>");
        if( wifeHusbs.size() > 1 ) {
            htm << wxT("<table>");
            for( i = 0 ; i < wifeHusbs.size() ; i++ ) {
                if( wifeHusbs[i].f_husb_id == husb.f_id ) continue;
                htm << wxT("<tr><td align=right width=270><b><a href='F")
                    << wifeHusbs[i].f_id << wxT("'>");                     // FamID,
                if( wifeHusbs[i].f_husb_id == 0 ) {
                    htm << wxT("[Unknown]");
                } else {
                    htm << recIndividual::GetFullName( wifeHusbs[i].f_husb_id );  //  Name
                }
                htm << wxT("</a></b>&nbsp;&nbsp;")
                    << recIndividual::GetDateEpitaph( wifeHusbs[i].f_husb_id )
                    << wxT("</td></tr>");
            }
            htm << wxT("</table>");
        }
        htm << wxT("</td></tr></table>");
    }

    htm << wxT("</center></body></html>");

    return htm;
}


wxString tfpWriteIndFamilyPage( idt indID )
{
    return tfpWriteFamilyPage( recIndividual::GetDefaultFamily( indID ) );
}

// End of tfpWrFam.cpp Source
