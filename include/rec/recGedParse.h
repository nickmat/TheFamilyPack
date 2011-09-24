/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        rec/recGedParse.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Read GEDCOM import file header.
 * Author:      Nick Matthews
 * Modified by:
 * Created:     19 September 2011
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2011, Nick Matthews.
 * Website:     http://thefamilypack.org
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

#ifndef RECGEDPARSE_H
#define RECGEDPARSE_H

#include <wx/txtstrm.h>
#include "rec/recDatabase.h"

class GedIndividual;
class GedFamily;

class recGedParse
{
public:
    recGedParse( wxInputStream& stream ) : m_input(stream),
        m_lineNum(0), m_level(0), m_index(0), m_tag(tagNULL),
        m_ref(0) {}

    bool Import();

    void CleanUp();

private:
    enum Tag {
        tagNULL, // Invalid or unset value.
        tagINDI, /* Index of INDIVIDUAL, a person */
        tagFAM,  /* Index of FAMILY, a couple and their children */
        tagNAME, /* NAME, (one of) the name a person is known by */
        tagSEX,  /* SEX, M for Male, F for Female */
        tagBIRT, /* BIRTH, birth event */
        tagCHR,  /* CHRISTENING, christening or baptism event */
        tagDEAT, /* DEATH, death event */
        tagBURI, /* BURIAL, burial event */
        tagOCCU, /* OCCUPATION, Occupation or Profession attribute */
        tagDATE, /* DATE, a calender day event */
        tagPLAC, /* PLACE, a place name (Address) */
        tagFAMS, /* FAMILY_SPOUSE, family in which a person appears as a spouse. */
        tagFAMC, /* FAMILY_CHILD, family in which a person appears as a child. */
        tagHUSB, /* HUSBAND, person - male partner in family */
        tagWIFE, /* WIFE, person - female partner in family */
        tagMARR, /* MARRIAGE, marriage event */
        tagCHIL, /* CHILD, person - (one of) child member of family */
        tag_PRI, /* PRIVATE, person - if Y, details should not be made public */
        tagTRLR, // TRAILER, required. It specifies the end of the data, use tag_END
        tag_END  /* _END, end of file */
    };

    bool ReadNextLine();

    void ReadIndi( int level );
    void ReadName( GedIndividual& gind, int level );
    void ReadSex( GedIndividual& gind );
    void ReadIndEvent( GedIndividual& gind, int level );
    void ReadIndAttr( GedIndividual& gind, int level );
    void ReadFam( int level );
    void ReadFamEvent( GedFamily& gfam, int level );
    idt ParseEvPlace( int level );
    idt ParseEvDate( int level );

    wxTextInputStream m_input;
    // Current line
    int      m_lineNum;
    int      m_level;
    unsigned m_index;
    Tag      m_tag;
    unsigned m_ref;
    wxString m_text;
};

#endif // RECGEDPARSE_H
