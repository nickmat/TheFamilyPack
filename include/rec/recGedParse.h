/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        rec/recGedParse.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Read GEDCOM import file header.
 * Author:      Nick Matthews
 * Created:     19 September 2011
 * Copyright:   Copyright (c) 2011-2015, Nick Matthews.
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
#include <rec/recDatabase.h>
#include <rec/recDate.h>

typedef std::map< wxString, unsigned > XrefMap;

class recEvent;
class GedIndividual;
class GedFamily;
class GedSubmitter;

#define recGED_IMPORT_NO_POST_OPS 0x01 // Do not automatically run DoPostOperations.
#define recGED_IMPORT_NO_SOUR_REC 0x02 // Ignore all SOUR records.

class recGedParse
{
public:
    recGedParse( const wxString& fname ) 
        : m_filestream(fname), m_input(m_filestream), m_progress(NULL),
        m_fileSource(FS_UNKNOWN),
        m_level(0), m_tag(tagNULL),
        m_indiUseXref(false), m_famUseXref(false), m_sourUseXref(false),
        m_totalCount(0),
        m_user(0), m_noSourRec(false)
    {}

    bool Import( unsigned flags = 0 );

    void SetUseXref( bool useXref ) { 
        m_indiUseXref = m_famUseXref = m_sourUseXref = useXref; }
    bool DoPostOperations();

private:
    enum FileSource {
        FS_UNKNOWN,
        FS_EasyTree   // Generations EasyTree
    };
    enum Tag {
        tagNULL, // Invalid or unset value.

        tagADDR, // ADDRESS, Postal address for Submitter
        tagADR1,
        tagADR2,
        tagADR3,
        tagBIRT, /* BIRTH, birth event */
        tagBURI, /* BURIAL, burial event */
        tagCHIL, /* CHILD, person - (one of) child member of family */
        tagCHR,  /* CHRISTENING, christening or baptism event */
        tagCONC, // Continuation without whitespace.
        tagCONT, // Continuation on next line.
        tagDATE, /* DATE, a calender day event */
        tagDEAT, /* DEATH, death event */
        tagEMAI, // EMAIL ADDRESS as defined in (draft) GEDCOM 5.5.1
        tagFAM,  /* Index of FAMILY, a couple and their children */
        tagFAMC, /* FAMILY_CHILD, family in which a person appears as a child. */
        tagFAMS, /* FAMILY_SPOUSE, family in which a person appears as a spouse. */
        tagFAX,  // FAX number.
        tagHEAD, // HEADER, required. File always starts with this section.
        tagHUSB, /* HUSBAND, person - male partner in family */
        tagINDI, /* Index of INDIVIDUAL, a person */
        tagMARR, /* MARRIAGE, marriage event */
        tagNAME, /* NAME, (one of) the name a person is known by */
        tagNOTE, /* NOTE, A note object, index to a note object or a text note */
        tagOCCU, /* OCCUPATION, Occupation or Profession attribute */
        tagPHON, // PHONE, Telephone number.
        tagPLAC, /* PLACE, a place name (Address) */
        tagSEX,  /* SEX, M for Male, F for Female */
        tagSOUR, /* Index of SOURCE, a source note */
        tagSUBM, // Index of Submitter (Researcher) record.
        tagTEXT,
        tagTITL,
        tagTRLR, // TRAILER, required. It specifies the end of the data, use tag_END
        tagWIFE, /* WIFE, person - female partner in family */
        tagWWW,  // Web address.
        tag_PRI, /* PRIVATE, person - if Y, details should not be made public */

        tag_END  /* _END, end of file */
    };

    bool Pass1();
    bool Pass2();

    bool ReadNextLine();

    void ReadHead( int level );
    void ReadIndi( int level );
    void ReadName( GedIndividual& gind, int level );
    void ReadSex( GedIndividual& gind );
    void ReadPrivacy( GedIndividual& gind );
    void ReadIndEvent( GedIndividual& gind, int level );
    void ReadEventSource( recEvent& eve, idt indID, int level );
    void ReadFam( int level );
    void ReadFamEvent( GedFamily& gfam, int level );
    void ReadSour( int level );
    void ReadSubm( int level );
    FileSource ReadFileSource( int level );
    wxString ReadAddr( int level );
    wxString ReadTextNote( int level );
    wxString ReadText( int level, const wxString& start );
    idt ParseEvPlace( int level );
    idt ParseEvDate( int level, idt* d2ID );
    wxString ParseDate( recDate* date, const wxString& str );
    long GetMonth( const wxString& token, CalendarScheme sch );

    wxFileInputStream m_filestream;
    wxTextInputStream m_input;
    void*             m_progress;
    FileSource m_fileSource;
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
    bool     m_sourUseXref;
    XrefMap  m_sourMap;
    XrefMap  m_submMap;
    unsigned m_totalCount;
    // Global settings
    unsigned m_user;
    bool     m_noSourRec;
};

#endif // RECGEDPARSE_H
