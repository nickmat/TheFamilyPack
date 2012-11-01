/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrChart.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Chart functions.
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

#include "tfpWr.h"

#define HTM_CHART_GIF_BLANK 0
#define HTM_CHART_GIF_TEE   2
#define HTM_CHART_GIF_CONT  4
#define HTM_CHART_GIF_END   6
#define HTM_CHART_GIF_DBL   1

#define HTM_CHART_GIF_PTOP  8
#define HTM_CHART_GIF_PUP   9
#define HTM_CHART_GIF_PEND  10
#define HTM_CHART_GIF_PDN   11

const wxString htmChartGif[] = {
    wxT("<img src=memory:ss.png>"),
    wxT("<img src=memory:ds.png>"),
    wxT("<img src=memory:st.png>"),
    wxT("<img src=memory:dt.png>"),
    wxT("<img src=memory:sc.png>"),
    wxT("<img src=memory:dc.png>"),
    wxT("<img src=memory:se.png>"),
    wxT("<img src=memory:de.png>"),
    wxT("<img src=memory:pt.png>"),
    wxT("<img src=memory:pu.png>"),
    wxT("<img src=memory:pe.png>"),
    wxT("<img src=memory:pd.png>")
};

static int GenDChart[100];
static int GenPChart[100];
static wxString htm;

static void WrPedCht( idt indID, Sex sex, int gen );
static void WrDescCht( idt indID, int gen );
static void WrDescLine( idt indID, idt spouseID, idt famID, int gen );

wxString tfpCreatePedChart( idt indID )
{
    htm.Clear();
    recIndividual ind(indID);

    wxString name = ind.GetFullName();

    htm << wxT("<html><head><title>Pedigree Chart for ") << name
        << wxT("</title>")
           wxT("<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>")
           wxT("<link rel='stylesheet' type='text/css' href='memory:tfp.css'>")
           wxT("</head><body link=black>")
           wxT("<h1>Pedigree Chart for ") << name << wxT("</h1>");

    WrPedCht( indID, SEX_Unstated, 0 );

    htm << wxT("</body></html>");

    return htm;
}

void WrPedCht( idt indID, Sex sex, int gen )
{
    recIndividual ind( indID );
    if( ind.f_id == 0 ) return;
    recFamily fam( 0 );

    recFamilyVec famList = ind.GetParentList();
    if( famList.size() > 0 ) {
        fam = famList[0];
    }
    wxString famLk = ( ind.f_fam_id ) ? "F"+recGetStr( ind.f_fam_id ) : "FI"+recGetStr( indID );

    // Construct Pedigree Chart
    GenPChart[gen] = HTM_CHART_GIF_BLANK;
    if( fam.f_husb_id != 0 )
    {
        WrPedCht( fam.f_husb_id, SEX_Male, gen+1 );
    }

    if( sex == SEX_Male ) GenPChart[gen-1] = HTM_CHART_GIF_PTOP;
    if( sex == SEX_Female ) GenPChart[gen-1] = HTM_CHART_GIF_PEND;

    // Write out the given person
    htm << wxT("<table cellspacing=0 cellpadding=0 border=0><tr>");
    for( int i = 0 ; i <= gen ; i++ )
    {
        if( i == gen )
        {
            htm << wxT("<td width=300>&nbsp;&nbsp;<a href='tfp:")
                << famLk << wxT("'><b>")
                << ind.f_given << wxT(" ") << ind.f_surname
                << wxT("</b></a> ") << ind.f_epitaph << wxT("</td>");

            if( gen == 0 )
            {
                htm << wxT("<td>") << htmChartGif[0] << wxT("</td>");
            }
        } else {
            htm << wxT("<td>") << htmChartGif[GenPChart[i]] << wxT("</td>");
        }
    }
    htm << wxT("</tr></table>");

    if( sex == SEX_Male ) GenPChart[gen-1] = HTM_CHART_GIF_PUP;
    if( sex == SEX_Female ) GenPChart[gen-1] = HTM_CHART_GIF_BLANK;

    GenPChart[gen] = HTM_CHART_GIF_PDN;
    if( fam.f_wife_id != 0 )
    {
        WrPedCht( fam.f_wife_id, SEX_Female, gen+1 );
    }
}



wxString tfpCreateDescChart( idt indID )
{
    wxString name = recIndividual::GetFullName( indID );
    htm.Clear();

    htm << wxT("<html><head><title>Descendant Chart for ") << name << wxT("</title>")
           wxT("<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>")
           wxT("<link rel='stylesheet' type='text/css' href='tfp:memory:tfp.css'>")
           wxT("</head><body link=black>")
           wxT("<h1>Descendant Chart for ") << name << wxT("</h1>");

    WrDescCht( indID, 0 );

    htm << wxT("</body></html>");

    return htm;
}

// Recursive function which creates Descendants chart
void WrDescCht( idt indID, int gen )
{
    recIdList children;
    recFamilyVec families = recIndividual::GetFamilyList( indID );
    for( size_t i = 0 ; i < families.size() ; i++ )
    {
        idt famID = families[i].f_id;
        idt dadID = families[i].f_husb_id;
        idt mumID = families[i].f_wife_id;

        if( indID == dadID ) {
            WrDescLine( dadID, mumID, famID, gen );
        } else {
            WrDescLine( mumID, dadID, famID, gen );
        }
        if( gen > 0 ) {
            if( GenDChart[gen-1] == HTM_CHART_GIF_TEE ) {
                GenDChart[gen-1] = HTM_CHART_GIF_CONT;
            }
            if( GenDChart[gen-1] == HTM_CHART_GIF_END ) {
                GenDChart[gen-1] = HTM_CHART_GIF_BLANK;
            }
        }

        // Add Children, if any
        children = recFamily::GetChildrenIds( famID );
        for( size_t j = 0 ; j < children.size() ; j++ ) {
            if( j == children.size()-1 && i == families.size()-1 ) {
                GenDChart[gen] = HTM_CHART_GIF_END;
            } else {
                GenDChart[gen] = HTM_CHART_GIF_TEE;
            }
            WrDescCht( children[j], gen+1 );
        }
    }
    if( families.size() == 0 ) {
        WrDescLine( indID, 0, 0, gen );
    }
}

void WrDescLine( idt indID, idt spouseID, idt famID, int gen )
{
    int dheight = ( spouseID == 0 ) ? 0 : 1;
    wxString famLk = ( famID ) ? "F"+recGetStr( famID ) : "FI"+recGetStr( indID );

    htm << wxT("<table cellspacing=0 cellpadding=0 border=0><tr>");
    for( int i = 0 ; i <= gen ; i++ ) {
        if( i == gen ) {
            htm << wxT("<td width=300>&nbsp;&nbsp;<a href='tfp:")
                << famLk << wxT("'><b>")
                << recIndividual::GetFullName( indID )
                << wxT("</b></a> ")
                << recIndividual::GetDateEpitaph( indID );
            if( spouseID != 0 ) {
                htm << wxT("<br>&nbsp;&nbsp;&nbsp;m. <b>")
                    << recIndividual::GetFullName( spouseID )
                    << wxT("</b> ")
                    << recIndividual::GetDateEpitaph( spouseID );
            }
            htm << wxT("</td>");

            if( gen == 0 ) {
                htm << wxT("<td>") << htmChartGif[0] << wxT("</td>");
            }
        } else {
            htm << wxT("<td>") << htmChartGif[GenDChart[i]+dheight] << wxT("</td>");
        }
    }
    htm << wxT("</tr></table>");
}

// End of tfpWrChart.cpp Source
