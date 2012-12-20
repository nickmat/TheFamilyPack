/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calParse.h
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     Class to parse a date string into tokens.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     20th December 2012
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2012, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

#ifndef CALPARSE_H
#define CALPARSE_H


#include "calendar.h"

enum calTOKEN {
    calTOKEN_NULL,
    calTOKEN_Label,
    calTOKEN_Number,
    calTOKEN_Punct,
    calTOKEN_Scheme,
    calTOKEN_Sep,
    calTOKEN_PeriodSep,
    calTOKEN_RangeSep,
    calTOKEN_Minus
};

class calToken
{
    calTOKEN m_token;
    wxString m_label;
    long     m_number;

public:
    void SetToken( calTOKEN token ) { m_token = token; }
    void SetLabel( const wxString& str ) { m_label = str; }
    void SetNumber( long num ) { m_number = num; }

    calTOKEN GetToken() const { return m_token; }
    wxString GetLabel() const { return m_label; }
    long GetNumber() const { return m_number; }
};

extern calTokenVec calParseStr( const wxString& str );

#endif // CALPARSE_H