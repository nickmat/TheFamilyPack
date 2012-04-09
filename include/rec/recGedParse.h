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

#include <map>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include "rec/recDatabase.h"

typedef std::map< wxString, unsigned > XrefMap;

class GedIndividual;
class GedFamily;
class GedSubmitter;

class recGedParse
{
public:
    recGedParse( const wxString& fname ) 
        : m_filestream(fname), m_input(m_filestream),
        m_level(0), m_tag(tagNULL),
        m_indiUseXref(false), m_famUseXref(false),
        m_user(0)
    {}

    bool Import();

    void CleanUp();

    void SetUseXref( bool useXref ) { m_indiUseXref = m_famUseXref = useXref; }

private:
    enum Tag {
        tagNULL, // Invalid or unset value.
        tagINDI, /* Index of INDIVIDUAL, a person */
        tagFAM,  /* Index of FAMILY, a couple and their children */
        tagSUBM, // Index of Submitter (Researcher) record.
        tagNAME, /* NAME, (one of) the name a person is known by */
        tagADDR, // ADDRESS, Postal address for Submitter
        tagADR1,
        tagADR2,
        tagADR3,
        tagCONT, // Continuation on next line.
        tagPHON, // PHONE, Telephone number.
        tagEMAL, // EMAIL ADDRESS
        tagFAX,  // FAX number.
        tagWWW,  // Web address.
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
        tagHEAD, // HEADER, required. File always starts with this section.
        tagTRLR, // TRAILER, required. It specifies the end of the data, use tag_END
        tag_END  /* _END, end of file */
    };

    bool Pass1();
    bool Pass2();

    bool ReadNextLine();

    void ReadHead( int level );
    void ReadIndi( int level );
    void ReadName( GedIndividual& gind, int level );
    void ReadSex( GedIndividual& gind );
    void ReadIndEvent( GedIndividual& gind, int level );
    void ReadIndAttr( GedIndividual& gind, int level );
    void ReadFam( int level );
    void ReadFamEvent( GedFamily& gfam, int level );
    void ReadSubm( int level );
    wxString ReadAddr( int level );
    idt ParseEvPlace( int level );
    idt ParseEvDate( int level );

    wxFileInputStream m_filestream;
    wxTextInputStream m_input;
    // Current line
    static int m_lineNum; // Leave this static to aid debugging.
    int      m_level;
    wxString m_index;
    wxString m_xref;
    Tag      m_tag;
    wxString m_text;
    // xref_ID pointers
    bool     m_indiUseXref;
    XrefMap  m_indiMap;
    bool     m_famUseXref;
    XrefMap  m_famMap;
    XrefMap  m_submMap;
    // Global settings
    unsigned m_user;
};

#endif // RECGEDPARSE_H
