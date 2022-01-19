/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpWrChart.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write screen Chart functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     7 October 2010
 * Copyright:   Copyright (c) 2010..2022, Nick Matthews.
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

#include <rec/recFamily.h>
#include <rec/recIndividual.h>

#include "tfpWr.h"

#define HTM_CHART_GEN_MAX  20

#define HTM_CHART_GIF_SH_BLK 12
#define HTM_CHART_GIF_BLANK  0
#define HTM_CHART_GIF_TEE    2
#define HTM_CHART_GIF_CONT   4
#define HTM_CHART_GIF_END    6
#define HTM_CHART_GIF_DBL    1

#define HTM_CHART_GIF_PTOP  8
#define HTM_CHART_GIF_PUP   9
#define HTM_CHART_GIF_PEND  10
#define HTM_CHART_GIF_PDN   11

const wxString htmChartGif[] = {
    "<img src='memory:ss.png'>",
    "<img src='memory:ds.png'>",
    "<img src='memory:st.png'>",
    "<img src='memory:dt.png'>",
    "<img src='memory:sc.png'>",
    "<img src='memory:dc.png'>",
    "<img src='memory:se.png'>",
    "<img src='memory:de.png'>",
    "<img src='memory:pt.png'>",
    "<img src='memory:pu.png'>",
    "<img src='memory:pe.png'>",
    "<img src='memory:pd.png'>",
    "<img src='memory:sss.png'>",
    "<img src='memory:dss.png'>"
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

    wxString name = ind.FGetName();

    htm << 
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n<title>Pedigree Chart for " << name << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n\n"
        "<h1>Pedigree Chart for " << name << "</h1>\n\n"
        "<table class='chart'>\n"
    ;

    WrPedCht( indID, Sex::unstated, 0 );

    htm << "</table>\n\n</body>\n</html>\n";

    return htm;
}

void WrPedCht( idt indID, Sex sex, int gen )
{
    if( gen == HTM_CHART_GEN_MAX ) {
        return;
    }
    recIndividual ind( indID );
    if( ind.FGetID() == 0 ) return;
    recFamily fam( 0 );

    recFamilyVec famList = recFamily::GetParentList( indID );
    if( famList.size() > 0 ) {
        fam = famList[0];
    }
    wxString famLk = ( ind.f_fam_id ) ? "F"+recGetStr( ind.f_fam_id ) : "FI"+recGetStr( indID );

    // Construct Pedigree Chart
    GenPChart[gen] = HTM_CHART_GIF_BLANK;
    if( fam.f_husb_id != 0 )
    {
        WrPedCht( fam.f_husb_id, Sex::male, gen+1 );
    }

    if( sex == Sex::male ) GenPChart[gen-1] = HTM_CHART_GIF_PTOP;
    if( sex == Sex::female ) GenPChart[gen-1] = HTM_CHART_GIF_PEND;

    // Write out the given person
    htm << "<tr>\n<td><img src='memory:sss.png'></td>\n";
    for( int i = 0 ; i <= gen ; i++ ) {
        if( i == gen ) {
            htm << "<td class='name' colspan='" 
                << HTM_CHART_GEN_MAX - gen << "'><a href='tfp:"
                << famLk << "'><b>"
                << ind.FGetName() << "</b></a> " << ind.FGetEpitaph() 
                << "</td>\n"
            ;
        } else {
            htm << "<td>" << htmChartGif[GenPChart[i]] << "</td>\n";
        }
    }
    htm << "</tr>\n";

    if( sex == Sex::male ) GenPChart[gen-1] = HTM_CHART_GIF_PUP;
    if( sex == Sex::female ) GenPChart[gen-1] = HTM_CHART_GIF_BLANK;

    GenPChart[gen] = HTM_CHART_GIF_PDN;
    if( fam.f_wife_id != 0 )
    {
        WrPedCht( fam.f_wife_id, Sex::female, gen+1 );
    }
}



wxString tfpCreateDescChart( idt indID )
{
    wxString name = recIndividual::GetName( indID );
    htm.Clear();

    htm << 
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n<title>Descendant Chart for " << name << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n"
        "<h1>Descendant Chart for " << name << "</h1>\n\n"
        "<table class='chart'>\n"
    ;

    WrDescCht( indID, 0 );

    htm << "</table>\n\n</body>\n</html>\n";

    return htm;
}

// Recursive function which creates Descendants chart
void WrDescCht( idt indID, int gen )
{
    recIdVec children;
    recFamilyVec families = recFamily::GetFamilyList( indID );
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

    htm << "<tr>\n<td>" << htmChartGif[HTM_CHART_GIF_SH_BLK+dheight] << "</td>\n";
    for( int i = 0 ; i <= gen ; i++ ) {
        if( i == gen ) {
            htm << "<td  class='name' colspan='" 
                << HTM_CHART_GEN_MAX - gen << "'><a href='tfp:"
                << famLk << "'><b>"
                << recIndividual::GetName( indID )
                << "</b></a> "
                << recIndividual::GetEpitaph( indID );
            if( spouseID != 0 ) {
                htm << "<br>\n m. <b>"
                    << recIndividual::GetName( spouseID )
                    << "</b> "
                    << recIndividual::GetEpitaph( spouseID );
            }
            htm << "</td>\n";
        } else {
            htm << "<td>" << htmChartGif[GenDChart[i]+dheight] << "</td>\n";
        }
    }
    htm << "</tr>\n";
}

// End of tfpWrChart.cpp Source
