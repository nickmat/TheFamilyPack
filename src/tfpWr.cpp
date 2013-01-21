/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/tfpWr.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Write HTML screen support functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     21st January 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
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

#include <rec/recContact.h>
#include <rec/recUser.h>
#include <rec/recSystem.h>
#include <rec/recIndividual.h>

#include "tfpWr.h"

wxString tfpWrHead( const wxString& title )
{
    wxString htm;
    htm <<
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\""
        " \"http://www.w3.org/TR/html4/loose.dtd\">\n"
        "<html>\n<head>\n"
        "<title>" << title << "</title>\n"
        "<meta http-equiv='Content-Type' content='text/html;charset=utf-8'>\n"
        "<link rel='stylesheet' type='text/css' href='memory:tfp.css'>\n"
        "</head>\n<body>\n<div class='tfp'>\n"
    ;
    return htm;
}

wxString tfpWrTail()
{
    return "</div>\n</body>\n</html>\n";
}

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

wxString wxGetRowClass( int row )
{
    return ( row % 2 ) ? "odd" : "even";
}

// End of src/tfpWr.cpp Source
