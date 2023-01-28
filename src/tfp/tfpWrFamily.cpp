/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrFamily.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Family page functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
 * Copyright:   Copyright (c) 2010..2023, Nick Matthews.
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

#include "tfpWr.h"

#include "tfpFrame.h"

#include <rec/recEvent.h>
#include <rec/recFamily.h>
#include <rec/recIndividual.h>
#include <rec/recPersona.h>

#include <wx/tokenzr.h>


#define BIRTH    recEventTypeRole::ROLE_Birth_Born
#define NR_BIRTH recEventType::ETYPE_Grp_Nr_Birth
#define DEATH    recEventTypeRole::ROLE_Death_Died
#define NR_DEATH recEventType::ETYPE_Grp_Nr_Death


wxString tfpWriteFamilyPage( idt famID, const wxString& extdb, size_t iL, size_t iR )
{
    wxString htm;
    recFamily fam( famID, extdb );
    if ( fam.FGetID() == 0 ) {
        return htm;
    }
    idt hIndID = fam.FGetHusbID();
    idt wIndID = fam.FGetWifeID();

    recIndividual husb( hIndID, extdb );
    recIndividual wife( wIndID, extdb );

    recFamilyVec husbFams = recFamily::GetParentList( hIndID, extdb );
    recFamilyVec wifeFams = recFamily::GetParentList( wIndID, extdb );

    recIndividualVec kids = recIndividual::GetChildren( famID, extdb );
    recFamilyVec husbWives = recFamily::GetFamilyList( hIndID, extdb );
    recFamilyVec wifeHusbs = recFamily::GetFamilyList( wIndID, extdb );

    htm << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
           "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
           "<html>\n<head>\n<title>Family F" << famID << "</title>\n"
           "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
           "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
           "</head>\n<body>\n<div class='tfp'>\n";

    htm << "<table class='core'>\n";

    // Parents
    htm << "<tr>\n<td class='frame frame-top'>\n"
           "<table class='parent'>\n<tr>\n";

    // Hubands Father
    if( fam.FGetHusbID() ) {
        if( husbFams.size() > iL && husbFams[iL].FGetHusbID() ) {
            idt indID = husbFams[iL].FGetHusbID();
            htm << 
                "<td class='" << tfpGetIndSexClass( indID, Sex::male, extdb ) <<
                "'><a href='tfp:F" << husbFams[iL].FGetID() << 
                "'>" << recIndividual::GetName( indID, extdb ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GetEpitaphPrefix::newline, extdb ) <<
                "</td>\n"
            ;
        } else {
            htm << 
                "<td class='male'>\n<a href='tfpe:IM" << fam.FGetHusbID() <<
                "'><img src='memory:blank.png' width='200' height='15' alt='Add Father'>"
                "</a>\n</td>\n";
        }
    } else {
        htm << "<td class='male'>\n&nbsp;\n</td>\n";
    }
    htm << "</tr>\n<tr>\n"; 

    // Husbands Mother
    if( fam.FGetHusbID() ) {
        if( husbFams.size() > iL && husbFams[iL].FGetWifeID() ) {
            idt indID = husbFams[iL].FGetWifeID();
            htm << 
                "<td class='" << tfpGetIndSexClass( indID, Sex::female, extdb ) <<
                "'><a href='tfp:F" << husbFams[iL].FGetID() <<
                "'>" << recIndividual::GetName( indID, extdb ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GetEpitaphPrefix::newline, extdb ) <<
                "</td>\n"
            ;
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
    if( fam.FGetWifeID() ) {
        if( wifeFams.size() > iR && wifeFams[iR].FGetHusbID() ) {
            idt indID = wifeFams[iR].FGetHusbID();
            htm << 
                "<td class='" << tfpGetIndSexClass( indID, Sex::male, extdb ) <<
                "'>\n<a href='tfp:F" << wifeFams[iR].FGetID() << 
                "'>" << recIndividual::GetName( indID, extdb ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GetEpitaphPrefix::newline, extdb ) <<
                "</td>\n"
            ;
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
    if( fam.FGetWifeID() ) {
        if( wifeFams.size() > iR && wifeFams[iR].FGetWifeID() ) {
            idt indID = wifeFams[iR].FGetWifeID();
            htm <<
                "<td class='" << tfpGetIndSexClass( indID, Sex::female, extdb ) <<
                "'>\n<a href='tfp:F" << wifeFams[iR].FGetID() << 
                "'>" << recIndividual::GetName( indID, extdb ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GetEpitaphPrefix::newline, extdb ) <<
                "</td>\n"
            ;
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
    if( fam.FGetID() ) {
        htm <<
            "<tr>\n<td colspan='2' class='both status'>\n"
            "<b>" << fam.GetIdStr() << "&nbsp;&nbsp;</b>"
            "<a href='tfpc:MF" << fam.FGetID() <<
            "," << fam.FGetHusbID() << "," << fam.FGetWifeID() <<
            "'><img src='memory:menu.png' alt='Edit family'></a>\n"
            "</td>\n</tr>\n"
        ;
    }

    // Marriage event
    idt eveID = fam.GetUnionEvent();
    if( eveID ) {
        htm << 
            "<tr>\n<td colspan='2' class='both'><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n</tr>\n"
        ;
    } else {
        htm << "<tr>\n<td colspan='2' class='both'><b>";
        if( fam.FGetHusbID() && fam.FGetWifeID() ) {
            htm <<
                "<a href='tfpe:Em" << fam.FGetHusbID() <<
                "," << fam.FGetWifeID() << "," << famID <<
                "' title='Add Event'>Marriage</a>:"
            ;
        } else {
            htm << "Marriage";
        }
        htm << "</b></td>\n</tr>\n";
    }

    // The happy couple
    htm << "<tr>\n<td class='couple "
        << tfpGetIndSexClass( fam.f_husb_id, Sex::male, extdb )
        << "'>";
    if( fam.f_husb_id == 0 ) {
        htm << "<a href='tfpe:IL" << fam.f_id
            << "'><img src='memory:blank.png' width='200' height='40' alt='Add husband'></a>";
    } else {
        htm << "<a href='tfp:I" << fam.f_husb_id
            << "'>" << recIndividual::GetName( fam.f_husb_id, extdb )
            << "</a><br>"
            << recIndividual::GetEpitaph( fam.f_husb_id, extdb );
    }
    htm << "</td>\n<td class='couple "
        << tfpGetIndSexClass( fam.f_wife_id, Sex::female, extdb )
        << "'>";
    if( fam.f_wife_id == 0 ) {
        htm << "<a href='tfpe:IR" << fam.f_id
            << "'><img src='memory:blank.png' width='200' height='40' alt='Add wife'></a>";
    } else {
        htm << "<a href='tfp:I" << fam.f_wife_id
            << "'>" << recIndividual::GetName( fam.f_wife_id, extdb )
            << "</a><br>"
            << recIndividual::GetEpitaph( fam.f_wife_id, extdb );
    }
    htm << "</td>\n</tr>\n";

    // Standard events
    eveID = husb.GetBirthEvent( extdb );
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n"
        ;
    } else if( fam.FGetHusbID() ) {
        htm <<
            "<tr>\n<td><b><a href='tfpe:Eb" << fam.FGetHusbID() <<
            "' title='Add Event'>Birth</a>:</b></td>\n"
        ;
    } else {
        htm << "<tr>\n<td><b>Birth:</b></td>\n";
    }
    eveID = wife.GetBirthEvent( extdb );
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n</tr>\n"
        ;
    } else if( fam.FGetWifeID() ) {
        htm <<
            "<td><b><a href='tfpe:Eb" << fam.FGetWifeID() <<
            "' title='Add Event'>Birth</a>:</b></td>\n</tr>\n"
        ;
    } else {
        htm << "<td><b>Birth:</b></td>\n</tr>\n";
    }

    eveID = husb.GetNrBirthEventID( extdb );
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n"
        ;
    } else if( fam.FGetHusbID() ) {
        htm <<
            "<tr>\n<td><b><a href='tfpe:Enb" << fam.FGetHusbID() <<
            "' title='Add Event'>Baptism</a>:</b></td>\n"
        ;
    } else {
        htm << "<tr>\n<td><b>Baptism:</b></td>\n";
    }
    eveID = wife.GetNrBirthEventID( extdb );
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n</tr>\n"
        ;
    } else if( fam.FGetWifeID() ) {
        htm <<
            "<td><b><a href='tfpe:Enb" << fam.FGetWifeID() <<
            "' title='Add Event'>Baptism</a>:</b></td>\n</tr>\n"
        ;
    } else {
        htm << "<td><b>Baptism:</b></td>\n</tr>\n";
    }

    eveID = husb.GetDeathEvent( extdb );
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n"
        ;
    } else if( fam.FGetHusbID() ) {
        htm <<
            "<tr>\n<td><b><a href='tfpe:Ed" << fam.FGetHusbID() <<
            "' title='Add Event'>Death</a>:</b></td>\n"
        ;
    } else {
        htm << "<tr>\n<td><b>Death:</b></td>\n";
    }
    eveID = wife.GetDeathEvent( extdb );
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n</tr>\n"
        ;
    } else if( fam.FGetWifeID() ) {
        htm <<
            "<td><b><a href='tfpe:Ed" << fam.FGetWifeID() <<
            "' title='Add Event'>Death</a>:</b></td>\n</tr>\n"
        ;
    } else {
        htm << "<td><b>Death:</b></td>\n</tr>\n";
    }

    eveID = husb.GetNrDeathEventID( extdb );
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n"
        ;
    } else if( fam.FGetHusbID() ) {
        htm <<
            "<tr>\n<td><b><a href='tfpe:End" << fam.FGetHusbID() <<
            "' title='Add Event'>Burial</a>:</b></td>\n"
        ;
    } else {
        htm << "<tr>\n<td><b>Burial:</b></td>\n";
    }
    eveID = wife.GetNrDeathEventID( extdb );
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID, extdb ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID, extdb ) <<
            "</td>\n</tr>\n"
        ;
    } else if( fam.FGetWifeID() ) {
        htm <<
            "<td><b><a href='tfpe:End" << fam.FGetWifeID() <<
            "' title='Add Event'>Burial</a>:</b></td>\n</tr>\n"
        ;
    } else {
        htm << "<td><b>Burial:</b></td>\n</tr>\n";
    }

    idt ieID = husb.GetPersonalSummaryIE( recEventType::ET_Occupation, extdb );
    if( ieID ) {
        recIndividualEvent ie(ieID, extdb );
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << ie.FGetEventID() <<
            "'>Occ:</a>: </b>" << ie.FGetNote() <<
            "</td>\n"
        ;
    } else if( fam.FGetHusbID() ) {
        htm <<
            "<tr>\n<td><b><a href='tfpe:Eo" << fam.FGetHusbID() <<
            "' title='Add Event'>Occ</a>:</b></td>\n"
        ;
    } else {
        htm << "<tr>\n<td><b>Occ:</b></td>\n";
    }
    ieID = wife.GetPersonalSummaryIE( recEventType::ET_Occupation, extdb );
    if( ieID ) {
        recIndividualEvent ie( ieID, extdb );
        htm << 
            "<td><b><a href='tfp:E" << ie.FGetEventID() <<
            "'>Occ:</a>: </b>" << ie.FGetNote() <<
            "</td>\n</tr>\n"
        ;
    } else if( fam.FGetWifeID() ) {
        htm <<
            "<td><b><a href='tfpe:Eo" << fam.FGetWifeID() <<
            "' title='Add Event'>Occ</a>:</b></td>\n</tr>\n"
        ;
    } else {
        htm << "<td><b>Occ:</b></td>\n</tr>\n";
    }

    // Individuals Status bar
    htm << "<tr>\n<td class='status'>\n";
    idt indID = fam.FGetHusbID();
    if( indID != 0 ) {
        htm <<
            "<b>" << recIndividual::GetIdStr( indID ) <<
            "</b>&nbsp;&nbsp;<a href='tfpc:MH" << indID << "+" << famID <<
            "'><img src='memory:menu.png' alt='Edit Individual'></a>\n"
            "&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
            "'><img src=memory:fam.png alt='Family'></a>"
            "&nbsp;&nbsp;<a href='tfp:I" << indID <<
            "'><img src='memory:ind.png' alt='Individual details'></a>\n";
        if( husbFams.size() ) {
            htm << "&nbsp;<a href='tfp:CP" << indID
                << "'><img src='memory:pcht.png' alt='Pedigree'></a>\n";
        }
        if( kids.size() > 0 )
        {
            htm << "&nbsp;<a href='tfp:CD" << indID
                << "'><img src='memory:dcht.png' alt='Descendants'></a>\n";
        }
    }
    htm << "\n</td>\n<td class='status'>\n";
    indID = fam.FGetWifeID();
    if( indID != 0 ) {
        htm <<
            "<b>" << recIndividual::GetIdStr( indID ) <<
            "</b>&nbsp;&nbsp;<a href='tfpc:MW" << indID << "+" << famID <<
            "'><img src='memory:menu.png' alt='Edit Individual'></a>\n"
            "&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
            "'><img src=memory:fam.png alt='Family'></a>"
            "&nbsp;&nbsp;<a href='tfp:I" << indID <<
            "'><img src='memory:ind.png' alt='Individual details'></a>\n";
        if( wifeFams.size() ) {
            htm << "&nbsp;&nbsp;<a href='tfp:CP" << indID
                << "'><img src='memory:pcht.png' alt='Pedigree'></a>\n";
        }
        if( kids.size() > 0 )
        {
            htm << "&nbsp;&nbsp;<a href='tfp:CD" << indID
                << "'><img src='memory:dcht.png' alt='Descendants'></a>\n";
        }
    }
    htm << "</td>\n</tr>\n";

    // Add Children
    if( kids.size() > 0 ) {
        htm << "<tr>\n<td colspan='2' class='frame frame-bot'>\n"
            << "<table class='parent'>\n";
        for( size_t i = 0 ; i < kids.size() ; i++ ) {
            indID = kids[i].FGetID();
            htm <<
                "<tr>\n<td class='" << tfpGetIndSexClass( indID, Sex::unknown, extdb ) <<
                " kids'><b><a href='tfp:FI" << indID <<
                "'>" << kids[i].FGetName() <<
                "</a></b>&nbsp;&nbsp;" << kids[i].f_epitaph <<
                "&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                "'><img src=memory:fam.png></a></td>\n</tr>\n"
            ;
        }
        htm << "</table>\n</td>\n</tr>\n";
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
            for( size_t i = 0 ; i < husbFams.size() ; i++ ) {
                if( i == iL ) {
                    continue;
                }
                indID = husbFams[i].FGetHusbID();
                if( indID ) {
                    htm << 
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID, Sex::male, extdb ) <<
                        "'><a href='tfp:F" << famID <<
                        "," << i << "," << iR <<
                        "'>" << recIndividual::GetName( indID, extdb ) <<
                        "</a>&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png></a></td>\n</tr>\n"
                    ;
                } 
                indID = husbFams[i].FGetWifeID();
                if( indID ) {
                    htm << 
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID, Sex::female, extdb ) <<
                        "'>\n<a href='tfp:F" << famID <<
                        "," << i << "," << iR << 
                        "'>" << recIndividual::GetName( indID, extdb ) <<
                        "</a>&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png></a></td>\n</tr>\n"
                    ;
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
            for( size_t i = 0 ; i < husbWives.size() ; i++ ) {
                indID = husbWives[i].FGetWifeID();
                if( indID == wife.FGetID() ) {
                    continue;
                }
                htm << "<tr>\n<td class='"
                    << tfpGetIndSexClass( indID, Sex::female, extdb )
                    << "'>\n<a href='tfp:F"
                    << husbWives[i].FGetID() << "'>";
                if( indID == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetName( indID, extdb ) <<
                        "</a>&nbsp;&nbsp;" <<
                        recIndividual::GetEpitaph( indID, extdb ) <<
                        "&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png>"
                    ;
                }
                htm << "</a></td>\n</tr>\n";
            }
            htm << "</table>\n";
        }
        htm << "</td>\n<td class='frame frame-bot'>\n";

        // Display additional Wifes Parents
        if( wifeFams.size() > 1 ) {
            htm << "<table class='parent'>\n"
                << "<tr>\n<td class='status'>\nAdditional Parents:\n</td>\n</tr>\n";
            for( size_t i = 0 ; i < wifeFams.size() ; i++ ) {
                if( i == iR ) {
                    continue;
                }
                indID = wifeFams[i].FGetHusbID();
                if( indID ) {
                    htm << 
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID, Sex::male, extdb ) <<
                        "'><a href='tfp:F" << famID <<
                        "," << iL << "," << i <<
                        "'>" << recIndividual::GetName( indID, extdb ) <<
                        "</a>&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png></a></td>\n</tr>\n"
                    ;
                } 
                indID = wifeFams[i].FGetWifeID();
                if( indID ) {
                    htm << 
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID, Sex::female, extdb ) <<
                        "'>\n<a href='tfp:F" << famID <<
                        "," << iL << "," << i << 
                        "'>" << recIndividual::GetName( indID, extdb ) <<
                        "</a>&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png></a></td>\n</tr>\n"
                    ;
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
            for( size_t i = 0 ; i < wifeHusbs.size() ; i++ ) {
                indID = wifeHusbs[i].FGetHusbID();
                if( indID == husb.FGetID() ) {
                    continue;
                }
                htm << "<tr>\n<td class='"
                    << tfpGetIndSexClass( indID, Sex::male, extdb )
                    << "'>\n<a href='tfp:F"
                    << wifeHusbs[i].FGetID() << "'>";
                if( indID == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetName( indID, extdb ) <<
                        "</a>&nbsp;&nbsp;" <<
                        recIndividual::GetEpitaph( indID, extdb ) <<
                        "&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png>"
                    ;
                }
                htm << "</a></td>\n</tr>\n";
            }
            htm << "</table>\n";
        }

        htm << "</td>\n</tr>\n";
    }

    // core done
    htm << "</table>\n</div>\n</body>\n</html>\n";

    return htm;
}

wxString tfpWriteFamilyPage( const wxString& str, const wxString& extdb )
{
    unsigned long iL = 0, iR = 0;
    wxStringTokenizer tokenizer( str, "," );
    wxString token = tokenizer.GetNextToken();
    idt famID = recGetID( token );
    token = tokenizer.GetNextToken();
    token.ToCULong( &iL );
    token = tokenizer.GetNextToken();
    token.ToCULong( &iR );
    return tfpWriteFamilyPage( famID, extdb, iL, iR );
}

wxString tfpWriteFamilyPageAsEvent( idt famID, TfpFrame& frame )
{
    const wxString& extdb = frame.GetDbName();
    wxString htm;

    recFamily fam( famID, extdb );
    if( fam.FGetID() == 0 ) return htm;
    recIndividual left( fam.FGetHusbID(), extdb );
    recIndividual right( fam.FGetWifeID(), extdb );

    wxString title;
    if( left.FGetID() && right.FGetID() ) {
        title = left.FGetName() + " and " + right.FGetName() + " Family";
    }
    else {
        title = left.FGetName() + right.FGetName() + " Family";
    }

    htm <<
        tfpWrHeadTfp( "Family " + fam.GetIdStr() ) <<

        "<table class='data'>\n"

        "<tr>\n<td class='status'>\n"
        "<b>Family: " << fam.GetIdStr() << "</b>"
        "</td>\n</tr>\n"

        "<tr>\n<td class='title'>\n" << title << "\n</td>\n</tr>\n"
        "</table>\n"
        ;

    htm << tfpWrTailTfp();

    return htm;
}

wxString tfpWriteIndFamilyPage( idt indID, const wxString& extdb )
{
    idt famID = recIndividual::GetFamilyID( indID, extdb );
    return tfpWriteFamilyPage( famID, extdb, 0, 0 );
}

// End of tfpWrFam.cpp Source
