/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        rec/recGedExport.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Read GEDCOM import file header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th November 2015
 * Copyright:   Copyright (c) 2015..2022, Nick Matthews.
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

#ifndef RECGEDEXPORT_H
#define RECGEDEXPORT_H

#include <rec/recDatabase.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

class recFamily;

class recGedExport
{
public:
    recGedExport( wxOutputStream& stream ) : m_out(stream), m_privacy(0) {}

    void SetPrivacy( int privacy ) { m_privacy = privacy; }

    bool Export();

private:
    void ExportIndividual( idt indID, int level );
    void ExportFamily( const recFamily& fam, int level );
    void ExportIndEvents( idt indID, recEventTypeGrp grp, int level );
    void ExportFamEvents( idt famID, int level );
    void ExportEvents( const recIdVec& events, int level, idt id );
    void ExportDate( idt dateID, int level );
    void ExportPlace( idt placeID, int level );

    wxTextOutputStream m_out;
    int m_privacy;
};

#endif // RECGEDEXPORT_H
