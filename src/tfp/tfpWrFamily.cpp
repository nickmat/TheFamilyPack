/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrFamily.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Family page functions.
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

#include <wx/tokenzr.h>

#include <rec/recIndividual.h>
#include <rec/recEvent.h>
#include <rec/recPersona.h>

#include "tfpWr.h"

#define BIRTH    recEventTypeRole::ROLE_Birth_Born
#define NR_BIRTH recEventType::ETYPE_Grp_Nr_Birth
#define DEATH    recEventTypeRole::ROLE_Death_Died
#define NR_DEATH recEventType::ETYPE_Grp_Nr_Death


wxString tfpWriteFamilyPage( idt famID, size_t iL, size_t iR )
{
    wxString htm;
    recFamily fam(famID);
    if ( fam.FGetID() == 0 ) {
        return htm;
    }
    recIndividual husb( fam.f_husb_id );
    recIndividual wife( fam.f_wife_id );
    recFamilyVec husbFams = husb.GetParentList();
    recFamilyVec wifeFams = wife.GetParentList();

    idt hIndID = husb.FGetID();
    idt wIndID = wife.FGetID();
    idt eveID, indID;

    recIndividualList kids = fam.GetChildren();
    recFamilyVec husbWives = recIndividual::GetFamilyList( husb.f_id );
    recFamilyVec wifeHusbs = recIndividual::GetFamilyList( wife.f_id );

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
            indID = husbFams[iL].FGetHusbID();
            htm << 
                "<td class='" << tfpGetIndSexClass( indID, SEX_Male ) <<
                "'><a href='tfp:F" << husbFams[iL].FGetID() << 
                "'>" << recIndividual::GetName( indID ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GE_NewLine ) <<
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
            indID = husbFams[iL].FGetWifeID();
            htm << 
                "<td class='" << tfpGetIndSexClass( indID, SEX_Female ) << 
                "'><a href='tfp:F" << husbFams[iL].FGetID() <<
                "'>" << recIndividual::GetName( indID ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GE_NewLine ) <<
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
            indID = wifeFams[iR].FGetHusbID();
            htm << 
                "<td class='" << tfpGetIndSexClass( indID, SEX_Male ) <<
                "'>\n<a href='tfp:F" << wifeFams[iR].FGetID() << 
                "'>" << recIndividual::GetName( indID ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GE_NewLine ) <<
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
            indID = wifeFams[iR].FGetWifeID();
            htm <<
                "<td class='" << tfpGetIndSexClass( indID, SEX_Female ) <<
                "'>\n<a href='tfp:F" << wifeFams[iR].FGetID() << 
                "'>" << recIndividual::GetName( indID ) <<
                "</a>" << tfpGetEpitaphPlus( indID, GE_NewLine ) <<
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
    eveID = fam.GetUnionEvent();
    if( eveID ) {
        htm << 
            "<tr>\n<td colspan='2' class='both'><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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
        << tfpGetIndSexClass( fam.f_husb_id, SEX_Male )
        << "'>";
    if( fam.f_husb_id == 0 ) {
        htm << "<a href='tfpe:IL" << fam.f_id
            << "'><img src='memory:blank.png' width='200' height='40' alt='Add husband'></a>";
    } else {
        htm << "<a href='tfp:I" << fam.f_husb_id
            << "'>" << recIndividual::GetName( fam.f_husb_id )
            << "</a><br>"
            << recIndividual::GetEpitaph( fam.f_husb_id );
    }
    htm << "</td>\n<td class='couple "
        << tfpGetIndSexClass( fam.f_wife_id, SEX_Female )
        << "'>";
    if( fam.f_wife_id == 0 ) {
        htm << "<a href='tfpe:IR" << fam.f_id
            << "'><img src='memory:blank.png' width='200' height='40' alt='Add wife'></a>";
    } else {
        htm << "<a href='tfp:I" << fam.f_wife_id
            << "'>" << recIndividual::GetName( fam.f_wife_id )
            << "</a><br>"
            << recIndividual::GetEpitaph( fam.f_wife_id );
    }
    htm << "</td>\n</tr>\n";

    // Standard events
    eveID = husb.GetBirthEvent();
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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
    eveID = wife.GetBirthEvent();
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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

    eveID = husb.GetNrBirthEvent();
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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
    eveID = wife.GetNrBirthEvent();
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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

    eveID = husb.GetDeathEvent();
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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
    eveID = wife.GetDeathEvent();
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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

    eveID = husb.GetNrDeathEvent();
    if( eveID ) {
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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
    eveID = wife.GetNrDeathEvent();
    if( eveID ) {
        htm << 
            "<td><b><a href='tfp:E" << eveID <<
            "'>" << recEvent::GetTypeStr( eveID ) <<
            "</a>: </b>" << recEvent::GetDetailStr( eveID ) <<
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

    idt ieID = husb.GetPersonalSummaryIE( recEventType::ET_Occupation );
    if( ieID ) {
        recIndividualEvent ie(ieID);
        htm << 
            "<tr>\n<td><b><a href='tfp:E" << ie.FGetEventID() <<
            "'>Occ:</a>: </b>" << recEventTypeRole::GetName( ie.FGetRoleID() ) <<
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
    ieID = wife.GetPersonalSummaryIE( recEventType::ET_Occupation );
    if( ieID ) {
        recIndividualEvent ie(ieID);
        htm << 
            "<td><b><a href='tfp:E" << ie.FGetEventID() <<
            "'>Occ:</a>: </b>" << recEventTypeRole::GetName( ie.FGetRoleID() ) <<
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
    indID = fam.FGetHusbID();
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
                "<tr>\n<td class='" << tfpGetIndSexClass( indID ) << 
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
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID ) <<
                        "'><a href='tfp:F" << famID <<
                        "," << i << "," << iR <<
                        "'>" << recIndividual::GetName( indID ) <<
                        "</a>&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png></a></td>\n</tr>\n"
                    ;
                } 
                indID = husbFams[i].FGetWifeID();
                if( indID ) {
                    htm << 
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID ) <<
                        "'>\n<a href='tfp:F" << famID <<
                        "," << i << "," << iR << 
                        "'>" << recIndividual::GetName( indID ) <<
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
                    << tfpGetIndSexClass( indID, SEX_Female )
                    << "'>\n<a href='tfp:F"
                    << husbWives[i].FGetID() << "'>";            // FamID,
                if( indID == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetName( indID ) <<    //  Name
                        "</a>&nbsp;&nbsp;" <<
                        recIndividual::GetEpitaph( indID ) <<
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
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID ) <<
                        "'><a href='tfp:F" << famID <<
                        "," << iL << "," << i <<
                        "'>" << recIndividual::GetName( indID ) <<
                        "</a>&nbsp;&nbsp;<a href='tfpc:MR" << indID <<
                        "'><img src=memory:fam.png></a></td>\n</tr>\n"
                    ;
                } 
                indID = wifeFams[i].FGetWifeID();
                if( indID ) {
                    htm << 
                        "<tr>\n<td class='" << tfpGetIndSexClass( indID ) <<
                        "'>\n<a href='tfp:F" << famID <<
                        "," << iL << "," << i << 
                        "'>" << recIndividual::GetName( indID ) <<
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
                    << tfpGetIndSexClass( indID, SEX_Male )
                    << "'>\n<a href='tfp:F"
                    << wifeHusbs[i].FGetID() << "'>";            // FamID,
                if( indID == 0 ) {
                    htm << "[Unknown]";
                } else {
                    htm << recIndividual::GetName( indID ) <<   //  Name
                        "</a>&nbsp;&nbsp;" <<
                        recIndividual::GetEpitaph( indID ) <<
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
    idt famID = recIndividual::GetFamilyID( indID );
    return tfpWriteFamilyPage( famID, 0, 0 );
}

// End of tfpWrFam.cpp Source
