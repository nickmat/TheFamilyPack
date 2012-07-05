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

#include <wx/tokenzr.h>

#include <rec/recIndividual.h>
#include <rec/recEvent.h>
#include <rec/recPersona.h>

#include "tfpWr.h"

#define BIRTH    recEventTypeRole::ROLE_Birth_Born
#define NR_BIRTH recEventType::ETYPE_Grp_Nr_Birth
#define DEATH    recEventTypeRole::ROLE_Death_Died
#define NR_DEATH recEventType::ETYPE_Grp_Nr_Death

wxString tfpWriteFamilyPage( idt famID, size_t iL, size_t iR, idt indID )
{
    size_t i;
    wxString htm;

    recFamily fam(famID);
    if( famID == 0 ) {
        Sex sex = recIndividual::GetSex( indID );
        if( sex == SEX_Female ) {
            fam.f_wife_id = indID;
        } else {
            fam.f_husb_id = indID;
        }
    }
    recIndividual husb( fam.f_husb_id );
    recIndividual wife( fam.f_wife_id );
    recFamilyVec husbFams = husb.GetParentList();
    recFamilyVec wifeFams = wife.GetParentList();

    idt hPerID = husb.GetPersona();
    idt wPerID = wife.GetPersona();

    recIndividualList kids = fam.GetChildren();
    recFamilyVec husbWives = recIndividual::GetFamilyList( husb.f_id );
    recFamilyVec wifeHusbs = recIndividual::GetFamilyList( wife.f_id );

    htm << "<html><head><title>Family F" << famID << "</title></head>"
           "<body><center>"
           "<table border=1>"
           "<tr><td align=center width=255>";

    // Husband's Father
    if( fam.f_husb_id ) {
        if( husbFams.size() > iL && husbFams[iL].f_husb_id ) {
            htm << "<b><a href=F" << husbFams[iL].f_id << ">"
                << recIndividual::GetFullName( husbFams[iL].f_husb_id )
                << "</a></b><br>"
                << recIndividual::GetDateEpitaph( husbFams[iL].f_husb_id );
        } else {
            htm << "<a href=$IM" << fam.f_husb_id
                << "><img src=memory:edit.bmp></a>";
        }
    } else {
        htm << "&nbsp;";
    }
    htm << "</td><td align=center width=255>";

    // Wife's Father
    if( fam.f_wife_id ) {
        if( wifeFams.size() > iR && wifeFams[iR].f_husb_id ) {
            htm << "<b><a href='F" << wifeFams[iR].f_id << "'>"
                << recIndividual::GetFullName( wifeFams[iR].f_husb_id )
                << "</a></b><br>"
                << recIndividual::GetDateEpitaph( wifeFams[iR].f_husb_id );
        } else {
            htm << "<a href=$IM" << fam.f_wife_id
                << "><img src=memory:edit.bmp></a>";
        }
    }
    htm << "</td></tr><tr><td align=center width=255>";

    // Husband's Mother
    if( fam.f_husb_id ) {
        if( husbFams.size() > iL && husbFams[iL].f_wife_id ) {
            htm << "<b><a href=F" << husbFams[iL].f_id << ">"
                << recIndividual::GetFullName( husbFams[iL].f_wife_id )
                << "</a></b><br>"
                << recIndividual::GetDateEpitaph( husbFams[iL].f_wife_id );
        } else {
            htm << "<a href=$IF" << fam.f_husb_id
                << "><img src=memory:edit.bmp></a>";
        }
    } else {
        htm << "&nbsp;";
   }
    htm << "</td><td align=center width=255>";

    // Wife's Mother
    if( fam.f_wife_id ) {
        if( wifeFams.size() > iR && wifeFams[iR].f_wife_id ) {
            htm << "<b><a href='F" << wifeFams[iR].f_id << "'>"
                << recIndividual::GetFullName( wifeFams[iR].f_wife_id )
                << "</a></b><br>"
                << recIndividual::GetDateEpitaph( wifeFams[iR].f_wife_id );
        } else {
            htm << "<a href=$IF" << fam.f_wife_id
                << "><img src=memory:edit.bmp></a>";
        }
    }
    htm << "</td></tr></table><br>&nbsp;";

    // Marriage details
    htm << "<table><tr><td align=center width=540>"
        << " m. " << recEvent::GetDetailStr( fam.GetMarriageEvent() )
        << "</td></tr></table>";

    // Family spouses
    htm << "<table border=1><tr><td colspan=2 align=center width=270>";
    if( fam.f_husb_id == 0 ) {
        htm << "<a href=$IL" << fam.f_id
            << "><img src=memory:edit.bmp></a>";
    } else {
        htm << "<font size=+1><b>"
            << recIndividual::GetFullName( fam.f_husb_id )
            << "</b></font><br>"
            << recIndividual::GetDateEpitaph( fam.f_husb_id );
    }
    htm << "</td><td colspan=2 align=center width=270>";
    if( fam.f_wife_id == 0 ) {
        htm << "<a href=$IR" << fam.f_id
            << "><img src=memory:edit.bmp></a>";
    } else {
        htm << "<font size=+1><b>"
            << recIndividual::GetFullName( fam.f_wife_id )
            << "</b></font><br>"
            << recIndividual::GetDateEpitaph( fam.f_wife_id );
    }
    // Write default Events
    htm << "</td></tr><font size=-1><tr align=left><td width=60><b>Birth</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetBirthEvent( hPerID ) )
        << "</td><td width=60><b>Birth</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetBirthEvent( wPerID ) )
        << "</td></tr>";

    htm << "<tr align=left><td width=60><b>Baptism</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetNrBirthEvent( hPerID ) )
        << "</td><td width=60><b>Baptism</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetNrBirthEvent( wPerID ) )
        << "</td></tr>";

    htm << "<tr align=left><td width=60><b>Death</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetDeathEvent( hPerID ) )
        << "</td><td width=60><b>Death</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetDeathEvent( wPerID ) )
        << "</td></tr>";

    htm << "<tr align=left><td width=60><b>Burial</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetNrDeathEvent( hPerID ) )
        << "</td><td width=60><b>Burial</b></td><td width=210>"
        << recEvent::GetDetailStr( recPersona::GetNrDeathEvent( wPerID ) )
        << "</td></tr>";
#if 0
    htm << "<tr align=left><td width=60><b>Occ</b></td><td width=210>"
        << recAttribute::GetValue( recPersona::GetOccAttribute( hPerID ) )
        << "</td><td width=60><b>Occ</b></td><td width=210>"
        << recAttribute::GetValue( recPersona::GetOccAttribute( wPerID ) )
        << "</td></tr>";
#endif
    htm << "</font>"

        << "</table>";

    // Write status, Edit and chart links
    htm << "<table><tr><td align=left width=80>";

    if( fam.f_husb_id != 0 ) {
        htm << "<a href=$MH" << fam.f_husb_id
            << "><img src=memory:menu.bmp></a> <b>"
            << recIndividual::GetIdStr( fam.f_husb_id ) << "</b>";
    }
    htm << "</td><td align=center width=110>";
    if( fam.f_husb_id != 0 ) {
        htm << "<a href=I" << fam.f_husb_id
            << "><img src=memory:ind.bmp></a>";
    }
    if( husbFams.size() )
    {
        htm << "&nbsp<a href=CP" << fam.f_husb_id
            << "><img src=memory:pcht.bmp></a>";
    }
    if( fam.f_husb_id && kids.size() > 0 )
    {
        htm << "&nbsp;<a href=CD" << fam.f_husb_id
            << "><img src=memory:dcht.bmp></a>";
    }
    htm << "</td>";

    htm << "<td align=center width=160>"
        << "<a href=$MF" << fam.f_id
        << "," << fam.f_husb_id << "," << fam.f_wife_id
        << "><img src=memory:menu.bmp></a>";
    if( fam.f_id != 0 ) {
        htm << " <b>F" << fam.f_id << "</b>";
    }

    htm << "</td><td align=center width=110>";

    if( fam.f_wife_id != 0 ) {
        htm << "<a href=I" << fam.f_wife_id
            << "><img src=memory:ind.bmp></a>";
    }
    if( fam.f_wife_id && wifeFams.size() )
    {
        htm << "&nbsp<a href=CP" << fam.f_wife_id
            << "><img src=memory:pcht.bmp></a>";
    }
    if( kids.size() > 0 ) {
        htm << "&nbsp<a href=CD" << fam.f_wife_id
            << "><img src=memory:dcht.bmp></a>";
    }
    htm << "</td><td align=right width=80>";

    if( fam.f_wife_id != 0 ) {
        htm << "<b>" << recIndividual::GetIdStr( fam.f_wife_id ) 
            << "</b> <a href=$MW" << fam.f_wife_id
            << "><img src=memory:menu.bmp></a>";
    }
    htm << "</td></tr></table>";

    // Add Children
    if( kids.size() > 0 ) {
        htm << "<br>&nbsp;<table border=1>";
        for( i = 0 ; i < kids.size() ; i++ ) {
            htm << "<tr><td align=center width=300><b><a href='FI"
                << kids[i].f_id << "'>"
                << kids[i].GetFullName()
                << "</a></b>&nbsp;&nbsp;"
                << kids[i].f_epitaph
                << "</td></tr>";
        }
        htm << "</table>";
    }

    // Add additional Spouses and/or Parents
    if( husbWives.size() > 1 || wifeHusbs.size() > 1 || 
        husbFams.size() > 1 || wifeFams.size() > 1 
    ) {
        htm << "<br>&nbsp;<table><tr><td align=left valign=top width=270>";

        // Display additional Husbands Parents
        if( husbFams.size() > 1 ) {
            htm << "<table><tr><td align=left width=270>Additional Parents</td></tr>";
            for( i = 0 ; i < husbFams.size() ; i++ ) {
                if( i == iL ) continue;
                htm << "<tr><td align=left width=270><b><a href='F"
                    << famID << "," << i << "," << iR << "," << indID << "'>";
                if( husbFams[i].f_husb_id || husbFams[i].f_wife_id ) {
                    if( husbFams[i].f_husb_id ) {
                        htm << recIndividual::GetFullName( husbFams[i].f_husb_id );
                    }
                    if( husbFams[i].f_husb_id && husbFams[i].f_wife_id ) {
                        htm << "<br>";
                    }
                    if( husbFams[i].f_wife_id ) {
                        htm << recIndividual::GetFullName( husbFams[i].f_wife_id );
                    }
                } else {
                    htm << "[Unknown]";
                }
                htm << "</a></b></td></tr>";
            }
            htm << "</table><br><br>";
        }

        // Display additional Husbands Spouses
        if( husbWives.size() > 1 ) {
            htm << "<table><tr><td align=left width=270>Additional Spouses</td></tr>";
            for( i = 0 ; i < husbWives.size() ; i++ ) {
                if( husbWives[i].f_wife_id == wife.f_id ) continue;
                htm << "<tr><td align=left width=270><b><a href='F"
                    << husbWives[i].f_id << "'>";                     // FamID,
                if( husbWives[i].f_wife_id == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetFullName( husbWives[i].f_wife_id );   //  Name
                }
                htm << "</a></b>&nbsp;&nbsp;"
                    << recIndividual::GetDateEpitaph( husbWives[i].f_wife_id )
                    << "</td></tr>";
            }
            htm << wxT("</table>");
        }
        htm << "</td><td align=right valign=top width=270>";

        // Display additional Wifes Parents
        if( wifeFams.size() > 1 ) {
            htm << "<table><tr><td align=right width=270>Additional Parents</td></tr>";
            for( i = 0 ; i < wifeFams.size() ; i++ ) {
                if( i == iR ) continue;
                htm << "<tr><td align=right width=270><b><a href='F"
                    << famID << "," << iL << "," << i << "," << indID << "'>";
                if( wifeFams[i].f_husb_id || wifeFams[i].f_wife_id ) {
                    if( wifeFams[i].f_husb_id ) {
                        htm << recIndividual::GetFullName( wifeFams[i].f_husb_id );
                    }
                    if( wifeFams[i].f_husb_id && wifeFams[i].f_wife_id ) {
                        htm << "<br>";
                    }
                    if( wifeFams[i].f_wife_id ) {
                        htm << recIndividual::GetFullName( wifeFams[i].f_wife_id );
                    }
                } else {
                    htm << "[Unknown]";
                }
                htm << "</a></b></td></tr>";
            }
            htm << "</table><br><br>";
        }

        // Display additional Wifes Spouses
        if( wifeHusbs.size() > 1 ) {
            htm << "<table><tr><td align=right width=270>Additional Spouses</td></tr>";
            for( i = 0 ; i < wifeHusbs.size() ; i++ ) {
                if( wifeHusbs[i].f_husb_id == husb.f_id ) continue;
                htm << "<tr><td align=right width=270><b><a href='F"
                    << wifeHusbs[i].f_id << "'>";                     // FamID,
                if( wifeHusbs[i].f_husb_id == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetFullName( wifeHusbs[i].f_husb_id );  //  Name
                }
                htm << "</a></b>&nbsp;&nbsp;"
                    << recIndividual::GetDateEpitaph( wifeHusbs[i].f_husb_id )
                    << "</td></tr>";
            }
            htm << "</table>";
        }
        htm << "</td></tr></table>";
    }

    htm << "</center></body></html>";

    return htm;
}

wxString tfpWriteFamilyPage( const wxString& str )
{
    unsigned long iL = 0, iR = 0;
    wxStringTokenizer tokenizer( str, "," );
    wxString token = tokenizer.GetNextToken();
    idt famID = recGetID( token );
    token = tokenizer.GetNextToken();
    token.ToCULong( &iL );
    token = tokenizer.GetNextToken();
    token.ToCULong( &iR );
    token = tokenizer.GetNextToken();
    idt indID = recGetID( token );
    return tfpWriteFamilyPage( famID, iL, iR, indID );
}

wxString tfpWriteIndFamilyPage( idt indID )
{
    idt famID = recIndividual::GetDefaultFamily( indID );
    return tfpWriteFamilyPage( famID, 0, 0, indID );
}

// End of tfpWrFam.cpp Source
