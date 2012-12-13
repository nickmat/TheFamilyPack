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

wxString GetSexClass( idt indID, Sex pref )
{
    Sex sex = recIndividual::GetSex( indID );
    if( sex == SEX_Unstated ) {
        sex = pref;
    }
    switch( sex ) {
    case SEX_Male: 
        return "male";
    case SEX_Female: 
        return "fem";
    }
    return "neut";
}


wxString tfpWriteFamilyPage( idt famID, size_t iL, size_t iR )
{
    size_t i;
    wxString htm;

    recFamily fam(famID);
    recIndividual husb( fam.f_husb_id );
    recIndividual wife( fam.f_wife_id );
    recFamilyVec husbFams = husb.GetParentList();
    recFamilyVec wifeFams = wife.GetParentList();

    idt hIndID = husb.FGetID();
    idt wIndID = wife.FGetID();

    recIndividualList kids = fam.GetChildren();
    recFamilyVec husbWives = recIndividual::GetFamilyList( husb.f_id );
    recFamilyVec wifeHusbs = recIndividual::GetFamilyList( wife.f_id );

    htm << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
           "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
           "<html>\n<head>\n<title>Family F" << famID << "</title>\n"
           "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
           "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
           "</head>\n<body>\n";

    htm << "<table class='core'>\n";

    // Parents
    htm << "<tr>\n<td class='frame frame-top'>\n"
           "<table class='parent'>\n<tr>\n";

    // Hubands Father
    if( fam.f_husb_id ) {
        if( husbFams.size() > iL && husbFams[iL].f_husb_id ) {
            htm << "<td class='" 
                << GetSexClass( husbFams[iL].f_husb_id, SEX_Male )
                << "'>\n<a href='tfp:F" << husbFams[iL].f_id << "'>"
                << recIndividual::GetFullName( husbFams[iL].f_husb_id )
                << "</a><br>"
                << recIndividual::GetDateEpitaph( husbFams[iL].f_husb_id )
                << "\n</td>\n";
        } else {
            htm << "<td class='male'>\n<a href='tfpe:IM" << fam.f_husb_id
                << "'><img src='memory:blank.png' width='200' height='15' alt='Add Father'>"
                << "</a>\n</td>\n";
        }
    } else {
        htm << "<td class='male'>\n&nbsp;\n</td>\n";
    }
    htm << "</tr>\n<tr>\n"; 

    // Husbands Mother
    if( fam.f_husb_id ) {
        if( husbFams.size() > iL && husbFams[iL].f_wife_id ) {
            htm << "<td class='" 
                << GetSexClass( husbFams[iL].f_wife_id, SEX_Female )
                << "'>\n<a href='tfp:F" << husbFams[iL].f_id << "'>"
                << recIndividual::GetFullName( husbFams[iL].f_wife_id )
                << "</a><br>"
                << recIndividual::GetDateEpitaph( husbFams[iL].f_wife_id )
                << "\n</td>\n";
        } else {
            htm << "<td class='fem'>\n<a href='tfpe:IF" << fam.f_husb_id
                << "'><img  src='memory:blank.png' width='200' height='15' alt='Add Mother'>"
                << "</a>\n</td>\n";
        }
    } else {
        htm << "<td class='fem'>\n&nbsp;\n</td>\n";
   }

    htm << "</tr>\n</table>\n"
           "</td>\n<td class='frame frame-top'>\n"
           "<table class='parent'>\n<tr>\n";

    // Wifes Father
    if( fam.f_wife_id ) {
        if( wifeFams.size() > iR && wifeFams[iR].f_husb_id ) {
            htm << "<td class='" 
                << GetSexClass( wifeFams[iR].f_husb_id, SEX_Male )
                << "'>\n<a href='tfp:F" << wifeFams[iR].f_id << "'>"
                << recIndividual::GetFullName( wifeFams[iR].f_husb_id )
                << "</a><br>"
                << recIndividual::GetDateEpitaph( wifeFams[iR].f_husb_id )
                << "\n</td>\n";
        } else {
            htm << "<td class='male'>\n<a href='tfpe:IM" << fam.f_wife_id
                << "'><img src='memory:blank.png' width='200' height='15' alt='Add Father'>"
                << "</a>\n</td>\n";
        }
    } else {
        htm << "<td class='male'>\n&nbsp;\n</td>\n";
    }
    htm << "</tr>\n<tr>\n";

    // Wife Mother
    if( fam.f_wife_id ) {
        if( wifeFams.size() > iR && wifeFams[iR].f_wife_id ) {
            htm << "<td class='" 
                << GetSexClass( wifeFams[iR].f_wife_id, SEX_Female )
                << "'>\n<a href='tfp:F" << wifeFams[iR].f_id << "'>"
                << recIndividual::GetFullName( wifeFams[iR].f_wife_id )
                << "</a><br>"
                << recIndividual::GetDateEpitaph( wifeFams[iR].f_wife_id )
                << "\n</td>\n";
        } else {
            htm << "<td class='fem'>\n<a href='tfpe:IF" << fam.f_wife_id
                << "'><img  src='memory:blank.png' width='200' height='15' alt='Add Mother'>"
                << "</a>\n</td>\n";
        }
    } else {
        htm << "<td class='fem'>\n&nbsp;\n</td>\n";
   }

    htm << "</tr>\n</table>\n"
           "</td>\n</tr>\n";

    // Family status bar
    htm << "<tr>\n<td colspan='2' class='both status'>\n";
    if( fam.f_id != 0 ) {
        htm << "<b>" << fam.GetIdStr() << "&nbsp;&nbsp;</b>";
    }
    htm << "<a href='tfpc:MF" << fam.f_id
        << "," << fam.f_husb_id << "," << fam.f_wife_id
        << "'><img src='memory:menu.png' alt='Edit family'></a>"
        << "\n</td>\n</tr>\n";

    // Marriage event
    htm << "<tr>\n<td colspan='2' class='both'>\n<b>Marriage: </b>"
        << recEvent::GetDetailStr( fam.GetUnionEvent() )
        << "\n</td>\n</tr>\n";

    // The happy couple
    htm << "<tr>\n<td class='couple "
        << GetSexClass( fam.f_husb_id, SEX_Male )
        << "'>";
    if( fam.f_husb_id == 0 ) {
        htm << "<a href='tfpe:IL" << fam.f_id
            << "'><img src='memory:blank.png' width='200' height='40' alt='Add husband'></a>";
    } else {
        htm << "<a href='tfp:I" << fam.f_husb_id
            << "'>" << recIndividual::GetFullName( fam.f_husb_id )
            << "</a><br>"
            << recIndividual::GetDateEpitaph( fam.f_husb_id );
    }
    htm << "</td>\n<td class='couple "
        << GetSexClass( fam.f_wife_id, SEX_Female )
        << "'>";
    if( fam.f_wife_id == 0 ) {
        htm << "<a href='tfpe:IR" << fam.f_id
            << "'><img src='memory:blank.png' width='200' height='40' alt='Add wife'></a>";
    } else {
        htm << "<a href='tfp:I" << fam.f_wife_id
            << "'>" << recIndividual::GetFullName( fam.f_wife_id )
            << "</a><br>"
            << recIndividual::GetDateEpitaph( fam.f_wife_id );
    }
    htm << "</td>\n</tr>\n";

    // Standard events
    htm << "<tr>\n<td>\n<b>Birth: </b>"
        << recEvent::GetDetailStr( recIndividual::GetBirthEvent( hIndID ) )
        << "\n</td>\n<td>\n<b>Birth: </b>"
        << recEvent::GetDetailStr( recIndividual::GetBirthEvent( wIndID ) )
        << "\n</td>\n</tr>\n";

    htm << "<tr>\n<td>\n<b>Baptism: </b>"
        << recEvent::GetDetailStr( recIndividual::GetNrBirthEvent( hIndID ) )
        << "\n</td>\n<td>\n<b>Baptism: </b>"
        << recEvent::GetDetailStr( recIndividual::GetNrBirthEvent( wIndID ) )
        << "\n</td>\n</tr>\n";

    htm << "<tr>\n<td>\n<b>Death: </b>"
        << recEvent::GetDetailStr( recIndividual::GetDeathEvent( hIndID ) )
        << "\n</td>\n<td>\n<b>Death: </b>"
        << recEvent::GetDetailStr( recIndividual::GetDeathEvent( wIndID ) )
        << "\n</td>\n</tr>\n";

    htm << "<tr>\n<td>\n<b>Burial: </b>"
        << recEvent::GetDetailStr( recIndividual::GetNrDeathEvent( hIndID ) )
        << "\n</td>\n<td>\n<b>Burial: </b>"
        << recEvent::GetDetailStr( recIndividual::GetNrDeathEvent( wIndID ) )
        << "\n</td>\n</tr>\n";

    htm << "<tr>\n<td>\n<b>Occ: </b>"
        << recIndividualEvent::GetRoleStr( hIndID, recEventType::ET_Occupation )
        << "\n</td>\n<td>\n<b>Occ: </b>"
        << recIndividualEvent::GetRoleStr( wIndID, recEventType::ET_Occupation )
        << "\n</td>\n</tr>\n";

    // Individuals Status bar
    htm << "<tr>\n<td class='status'>\n";
    if( fam.f_husb_id != 0 ) {
        htm << "<b>" << recIndividual::GetIdStr( fam.f_husb_id ) << "</b>"
            << "&nbsp;&nbsp;<a href='tfpc:MH" << fam.f_husb_id
            << "'><img src='memory:menu.png' alt='Edit'></a>\n"
            << "&nbsp;<a href='tfp:I" << fam.f_husb_id
            << "'><img src='memory:ind.png' alt='Individual details'></a>\n";
        if( husbFams.size() ) {
            htm << "&nbsp;<a href='tfp:CP" << fam.f_husb_id
                << "'><img src='memory:pcht.png' alt='Pedigree'></a>\n";
        }
        if( kids.size() > 0 )
        {
            htm << "&nbsp;<a href='tfp:CD" << fam.f_husb_id
                << "'><img src='memory:dcht.png' alt='Descendants'></a>\n";
        }
    }
    htm << "\n</td>\n<td class='status'>\n";
    if( fam.f_wife_id != 0 ) {
        htm << "<b>" << recIndividual::GetIdStr( fam.f_wife_id ) << "</b>\n"
            << "&nbsp;&nbsp;<a href='tfpc:MW" << fam.f_wife_id
            << "'><img src='memory:menu.png' alt='Edit'></a>\n"
            << "&nbsp;<a href='tfp:I" << fam.f_wife_id
            << "'><img src='memory:ind.png' alt='Individual details'></a>\n";
        if( wifeFams.size() ) {
            htm << "&nbsp;<a href='tfp:CP" << fam.f_wife_id
                << "'><img src='memory:pcht.png' alt='Pedigree'></a>\n";
        }
        if( kids.size() > 0 )
        {
            htm << "&nbsp;<a href='tfp:CD" << fam.f_wife_id
                << "'><img src='memory:dcht.png' alt='Descendants'></a>\n";
        }
    }
    htm << "</td>\n</tr>\n";

    // Add Children
    if( kids.size() > 0 ) {
        htm << "<tr>\n<td colspan='2' class='frame frame-bot'>\n"
            << "<table class='parent'>\n";
        for( i = 0 ; i < kids.size() ; i++ ) {
            htm << "<tr>\n<td class='" 
                << GetSexClass( kids[i].f_id )
                << " kids'>\n<b><a href='tfp:FI"
                << kids[i].f_id << "'>" 
                << kids[i].GetFullName()
                << "</a></b>&nbsp;&nbsp;"
                << kids[i].f_epitaph
                << "\n</td>\n</tr>\n";
        }
        htm << "</tr>\n</table>\n</td>\n";
    }

    // Add additional Spouses and/or Parents
    if( husbWives.size() > 1 || wifeHusbs.size() > 1 || 
        husbFams.size() > 1 || wifeFams.size() > 1 
    ) {
        htm << "<tr>\n<td class='frame frame-bot'>\n";
               
        // Display additional Husbands Parents
        if( husbFams.size() > 1 ) {
            htm << "<table class='parent'>\n"
                << "<tr>\n<td class='status'>\nAdditional Parents:\n</td>\n</tr>\n";
            for( i = 0 ; i < husbFams.size() ; i++ ) {
                if( i == iL ) {
                    continue;
                }
                if( husbFams[i].f_husb_id ) {
                    htm << "<tr>\n<td class='"
                        << GetSexClass( husbFams[i].f_husb_id )
                        << "'>\n<a href='tfp:F"
                        << famID << "," << i << "," << iR << "'>"
                        << recIndividual::GetFullName( husbFams[i].f_husb_id )
                        << "</a>\n</td>\n</tr>\n";
                } 
                if( husbFams[i].f_wife_id ) {
                    htm << "<tr>\n<td class='"
                        << GetSexClass( husbFams[i].f_wife_id )
                        << "'>\n<a href='tfp:F"
                        << famID << "," << i << "," << iR << "'>"
                        << recIndividual::GetFullName( husbFams[i].f_wife_id )
                        << "</a>\n</td>\n</tr>\n";
                }
                if( !( husbFams[i].f_husb_id || husbFams[i].f_wife_id ) ) {
                    htm << "<tr>\n<td class='neut'>\n[Unknown]\n</td>\n</tr>\n";
                }
            }
            htm << "</table>\n";
        }

        // Display additional Husbands Spouses
        if( husbWives.size() > 1 ) {
            htm << "<table class='parent'>\n"
                << "<tr>\n<td class='status'>\nAdditional Spouses:\n</td>\n</tr>\n";
            for( i = 0 ; i < husbWives.size() ; i++ ) {
                if( husbWives[i].f_wife_id == wife.f_id ) {
                    continue;
                }
                htm << "<tr>\n<td class='"
                    << GetSexClass( husbWives[i].f_wife_id, SEX_Female )
                    << "'>\n<a href='tfp:F"
                    << husbWives[i].f_id << "'>";                     // FamID,
                if( husbWives[i].f_wife_id == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetFullName( husbWives[i].f_wife_id );   //  Name
                }
                htm << "</a>&nbsp;&nbsp;"
                    << recIndividual::GetDateEpitaph( husbWives[i].f_wife_id )
                    << "\n</td>\n</tr>\n";
            }
            htm << "</table>\n";
        }

        htm << "</td>\n<td class='frame frame-bot'>\n";

        // Display additional Wifes Parents
        if( wifeFams.size() > 1 ) {
            htm << "<table class='parent'>\n"
                << "<tr>\n<td class='status'>\nAdditional Parents:\n</td>\n</tr>\n";
            for( i = 0 ; i < wifeFams.size() ; i++ ) {
                if( i == iR ) {
                    continue;
                }
                if( wifeFams[i].f_husb_id ) {
                    htm << "<tr>\n<td class='"
                        << GetSexClass( wifeFams[i].f_husb_id )
                        << "'>\n<a href='tfp:F"
                        << famID << "," << iL << "," << i << "'>"
                        << recIndividual::GetFullName( wifeFams[i].f_husb_id )
                        << "</a>\n</td>\n</tr>\n";
                } 
                if( wifeFams[i].f_wife_id ) {
                    htm << "<tr>\n<td class='"
                        << GetSexClass( wifeFams[i].f_wife_id )
                        << "'>\n<a href='tfp:F"
                        << famID << "," << iL << "," << i << "'>"
                        << recIndividual::GetFullName( wifeFams[i].f_wife_id )
                        << "</a>\n</td>\n</tr>\n";
                }
                if( !( wifeFams[i].f_husb_id || wifeFams[i].f_wife_id ) ) {
                    htm << "<tr>\n<td class='neut'>\n[Unknown]\n</td>\n</tr>\n";
                }
            }
            htm << "</table>\n";
        }

        // Display additional Wifes Spouses
        if( wifeHusbs.size() > 1 ) {
            htm << "<table class='parent'>\n"
                << "<tr>\n<td class='status'>\nAdditional Spouses:\n</td>\n</tr>\n";
            for( i = 0 ; i < wifeHusbs.size() ; i++ ) {
                if( wifeHusbs[i].f_husb_id == husb.f_id ) {
                    continue;
                }
                htm << "<tr>\n<td class='"
                    << GetSexClass( wifeHusbs[i].f_husb_id, SEX_Male )
                    << "'>\n<a href='tfp:F"
                    << wifeHusbs[i].f_id << "'>";                     // FamID,
                if( wifeHusbs[i].f_husb_id == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetFullName( wifeHusbs[i].f_husb_id );  //  Name
                }
                htm << "</a>&nbsp;&nbsp;"
                    << recIndividual::GetDateEpitaph( wifeHusbs[i].f_husb_id )
                    << "\n</td>\n</tr>\n";
            }
            htm << "</table>\n";
        }

        htm << "</td>\n</tr>\n";
    }

    // core done
    htm << "</table>\n</body>\n</html>\n";

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
    return tfpWriteFamilyPage( famID, iL, iR );
}

wxString tfpWriteIndFamilyPage( idt indID )
{
    idt famID = recIndividual::GetDefaultFamily( indID );
    return tfpWriteFamilyPage( famID, 0, 0 );
}

// End of tfpWrFam.cpp Source
