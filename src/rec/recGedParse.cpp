/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        rec/recGedParse.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Read GEDCOM import files.
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/tokenzr.h>
#include <wx/progdlg.h>
#include <wx/busyinfo.h>

#include "rec/recDb.h"

int recGedParse::m_lineNum = 0;

class GedIndividual
{
private:
    recIndividual        m_ind;
    recPersona           m_per;
    int                  m_nameSeq;

public:
    GedIndividual() : m_ind(0), m_per(0), m_nameSeq(0) { 
        m_per.Save(); 
        m_ind.f_per_id = m_per.f_id;
    }

    idt GetPersonaID() const { return m_per.f_id; }
    int GetNameSeq() { return ++m_nameSeq; }
    wxString GetNameStr() const { return m_per.GetNameStr(); }

    void SetIndId( idt indID ) { m_ind.f_id = indID; }
    void SetSex( Sex sex ) { m_per.f_sex = sex; }

    void Save() { m_per.Save(); m_ind.UpdateNames(); m_ind.Save(); }
};

class GedFamily
{
private:
    recFamily m_fam;
    idt       m_husbPerId;
    idt       m_wifePerId;
    int       m_childSeq;

public:
    GedFamily() : m_fam(0), m_husbPerId(0), m_wifePerId(0), m_childSeq(0) {}

    void SetFamId( idt famID ) { m_fam.f_id = famID; }
    void SetHusb( idt indID ) { 
        m_fam.f_husb_id = indID;
        UpdateIndividual( &m_husbPerId, indID ); 
    }
    void SetWife( idt indID ) { 
        m_fam.f_wife_id = indID;
        UpdateIndividual( &m_wifePerId, indID );
    }

    void AddChild( idt indID );

    idt GetHusbPerId() const { return m_husbPerId; }
    idt GetWifePerId() const { return m_wifePerId; }
    wxString GetHusbNameStr() const { return recPersona::GetNameStr( m_husbPerId ); }
    wxString GetWifeNameStr() const { return recPersona::GetNameStr( m_wifePerId ); }

    void UpdateIndividual( idt* p_perID, idt indID );
    void Save() { m_fam.Save(); }
};

class GedSubmitter
{
private:
    recResearcher  m_res;
    recContactList m_cl;

public:
    GedSubmitter( idt resID );

//    void SetSubmID( idt resID ) { m_res.FSetID( resID ); }
    void SetName( const wxString& nameStr ) { m_res.FSetName( nameStr ); }

    void SaveContact( recContactType::Type type, const wxString& value );
    void Save() { m_res.Save(); }
};

bool recGedParse::Import()
{
    if( recDb::IsGUI() ) {
        return ImportGUI();
    }
    return ImportCmdLine();
}

bool recGedParse::ImportGUI()
{
    wxProgressDialog dialog(
        _("Reading Gedcom"), _("Proccessing..."),
        100, NULL,
        wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME
    );
    m_progress = &dialog;

    if( !Pass1() ) return false;
    m_filestream.SeekI( 0 );
    if( !Pass2() ) return false;
    return true;
}

bool recGedParse::ImportCmdLine()
{
    if( !Pass1() ) return false;
    m_filestream.SeekI( 0 );
    if( !Pass2() ) return false;
    return true;
}

void recGedParse::CleanUp()
{
    recDb::Begin();
    recIndividual::AddMissingFamilies();
    recDb::Commit();
}

bool recGedParse::Pass1()
{
    wxString str;
    wxString xref;
    unsigned long num;
    unsigned index;
    unsigned famCount=0, indiCount=0, submCount=0;

    m_lineNum = 0;
    if( m_progress ) m_progress->Pulse( _("Examining file...") );
    while( !m_input.GetInputStream().Eof() ) {
        m_lineNum++;

        wxStringTokenizer tk( m_input.ReadLine() );
        if( tk.HasMoreTokens() == false ) continue;

        str = tk.GetNextToken(); // read level number
        if( str.ToULong( &num ) == false ) continue; // return false;

        if( tk.HasMoreTokens() == false ) continue; // return false;
        str = tk.GetNextToken();

        if( str[0] != wxS('@') ) continue;

        str.Mid( 2 ).ToULong( &num );

        xref = str.Mid( 1 ).BeforeFirst( wxS('@') );
        if( tk.HasMoreTokens() == false ) continue; // return false;
        str = tk.GetNextToken();

        if(      str.Cmp( "INDI" ) == 0 ) {
            if( m_indiUseXref ) index = (unsigned) num;
            else index = ++indiCount;
            m_indiMap[xref] = index;
        } else if( str.Cmp( "FAM"  ) == 0 ) {
            if( m_famUseXref ) index = (unsigned) num;
            else index = ++famCount;
            m_famMap[xref] = index;
        } else if( str.Cmp( "SUBM" ) == 0 ) {
            m_submMap[xref] = ++submCount;
        }
    }
    m_totalCount = m_lineNum;
    if( m_progress ) m_progress->SetRange( (m_totalCount/100) + 1 );

    return true;
}

bool recGedParse::Pass2()
{
    m_lineNum = 0;
    recDb::Begin();
    bool cont = ReadNextLine();
    while( cont ) {
        if( m_level == 0 ) {
            if( m_progress ) {
                wxString message = wxString::Format( 
                    "Line number = %d of %d", m_lineNum, m_totalCount 
                );
                if( m_progress->Update( m_lineNum/100, message ) == false ) {
                    recDb::Rollback();
                    return false;
                }
            }
            switch( m_tag )
            {
            case tagINDI:
                ReadIndi( 1 );
                break;
            case tagFAM:
                ReadFam( 1 );
                break;
            case tagSUBM:
                ReadSubm( 1 );
                break;
            case tagHEAD:
                ReadHead( 1 );
                break;
            case tagTRLR:
            case tag_END:
                cont = false;
                break;
            default:
                cont = ReadNextLine();
            }
        } else {
            cont = ReadNextLine();
        }
    }
    if( m_progress ) m_progress->Update( m_lineNum/100, "Finalising..." );
    recDb::Commit();

    return true;
}

bool recGedParse::ReadNextLine()
{
    wxString str;
    wxString xref;
    unsigned long num;

    m_lineNum++;
    m_level = 0;
    m_tag = tagNULL;
    m_text.empty();

    if( m_input.GetInputStream().Eof() == true ) {
        m_tag = tag_END;
        return false;
    }

    wxStringTokenizer tk( m_input.ReadLine() );
    if( tk.HasMoreTokens() == false ) return false;

    str = tk.GetNextToken();
    if( str.ToULong( &num ) == false ) return false;
    m_level = (int) num;

    if( tk.HasMoreTokens() == false ) return false;
    str = tk.GetNextToken();

    if(      str.Cmp( "TRLR" ) == 0 ) m_tag = tag_END;
    if( m_tag != tagNULL ) return true;

    if( str[0] == wxS('@') )
    {
        m_text = str;
        m_index = str.Mid( 1 ).BeforeFirst( wxS('@') );
        if( tk.HasMoreTokens() == false ) return false;
        str = tk.GetNextToken();

        if(      str.Cmp( "INDI" ) == 0 ) m_tag = tagINDI;
        else if( str.Cmp( "FAM"  ) == 0 ) m_tag = tagFAM;
        else if( str.Cmp( "SUBM" ) == 0 ) m_tag = tagSUBM;
        return true;
    }


    if(      str.Cmp( "HUSB" ) == 0 ) m_tag = tagHUSB;
    else if( str.Cmp( "WIFE" ) == 0 ) m_tag = tagWIFE;
    else if( str.Cmp( "CHIL" ) == 0 ) m_tag = tagCHIL;
    else if( str.Cmp( "SUBM" ) == 0 ) m_tag = tagSUBM;

    if( m_tag != tagNULL ) {
        if( tk.HasMoreTokens() == false ) return true;
        str = tk.GetNextToken();
        m_xref = str.Mid( 1 ).BeforeFirst( wxS('@') );
        return true;
    }

    if(      str.Cmp( "CONT" ) == 0 ) m_tag = tagCONT;
    else if( str.Cmp( "NAME" ) == 0 ) m_tag = tagNAME;
    else if( str.Cmp( "SEX"  ) == 0 ) m_tag = tagSEX;
    else if( str.Cmp( "BIRT" ) == 0 ) m_tag = tagBIRT;
    else if( str.Cmp( "CHR"  ) == 0 ) m_tag = tagCHR;
    else if( str.Cmp( "DEAT" ) == 0 ) m_tag = tagDEAT;
    else if( str.Cmp( "BURI" ) == 0 ) m_tag = tagBURI;
    else if( str.Cmp( "OCCU" ) == 0 ) m_tag = tagOCCU;
    else if( str.Cmp( "DATE" ) == 0 ) m_tag = tagDATE;
    else if( str.Cmp( "PLAC" ) == 0 ) m_tag = tagPLAC;
    else if( str.Cmp( "FAMS" ) == 0 ) m_tag = tagFAMS;
    else if( str.Cmp( "FAMC" ) == 0 ) m_tag = tagFAMC;
    else if( str.Cmp( "MARR" ) == 0 ) m_tag = tagMARR;
    else if( str.Cmp( "HEAD" ) == 0 ) m_tag = tagHEAD;
    else if( str.Cmp( "ADDR" ) == 0 ) m_tag = tagADDR;
    else if( str.Cmp( "ADR1" ) == 0 ) m_tag = tagADR1;
    else if( str.Cmp( "ADR2" ) == 0 ) m_tag = tagADR2;
    else if( str.Cmp( "ADR3" ) == 0 ) m_tag = tagADR3;
    else if( str.Cmp( "PHON" ) == 0 ) m_tag = tagPHON;
    else if( str.Cmp( "EMAI" ) == 0 ) m_tag = tagEMAI;
    else if( str.Cmp( "EMAL" ) == 0 ) m_tag = tagEMAI; // Generations 8.5 (at least) uses EMAL.
    else if( str.Cmp( "FAX"  ) == 0 ) m_tag = tagFAX;
    else if( str.Cmp( "WWW"  ) == 0 ) m_tag = tagWWW;
    else if( str.Cmp( "_PRI" ) == 0 ) m_tag = tag_PRI;

    m_text = tk.GetString();

    return true;
}

void recGedParse::ReadHead( int level )
{
    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagSUBM:
                m_user = m_submMap[ m_xref ];
                break;
            case tag_END:
                cont = FALSE;
                continue;
            }
        }
        cont = ReadNextLine();
    }
}

void recGedParse::ReadIndi( int level )
{
    GedIndividual gind;
    gind.SetIndId( m_indiMap[ m_index ] );

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagNAME:
                ReadName( gind, level+1 );
                continue;
            case tagSEX:
                ReadSex( gind );
                continue;
            case tagBIRT:
            case tagCHR:
            case tagDEAT:
            case tagBURI:
                ReadIndEvent( gind, level+1 );
                continue;
            case tagOCCU:
                ReadIndAttr( gind, level+1 );
                continue;
            case tag_END:
                cont = false;
                continue;
            }
        }
        cont = ReadNextLine();
    }
    gind.Save();
}

void recGedParse::ReadName( GedIndividual& gind, int level )
{
    recName name(0);
    name.f_per_id = gind.GetPersonaID();
    name.f_sequence = gind.GetNameSeq();
    name.Save();
    wxString nameStr = m_text;
    recNamePart np(0);
    np.f_name_id = name.f_id;
    np.f_type_id = NAME_TYPE_Given_name;
    np.f_sequence = 1;

    wxString::const_iterator i;
    for( i = nameStr.begin() ; i != nameStr.end() ; i++ ) {
        switch( np.f_type_id )
        {
        case NAME_TYPE_Given_name:
        case NAME_TYPE_Post_name:
            if( *i == wxT(' ') ) {
                if( np.f_val.length() == 0 ) continue; // Ignore leading spaces
                np.Save();
                np.f_id = 0;
                np.f_val = wxEmptyString;
                ++np.f_sequence;
                continue;
            }
            if( np.f_val.length() == 0 && *i == wxS('/') ) {
                np.f_type_id = NAME_TYPE_Surname;
                continue;
            }
            break;
        case NAME_TYPE_Surname:
            if( *i == wxS('/') ) {
                np.Save();
                np.f_id = 0;
                np.f_type_id = NAME_TYPE_Post_name;
                np.f_val = wxEmptyString;
                ++np.f_sequence;
                continue;
            }
            break;
        }
        np.f_val += *i;
    }
    if( np.f_val.length() != 0 ) {
        np.Save();
    }
    ReadNextLine();
}

void recGedParse::ReadSex( GedIndividual& gind )
{
    Sex sex;
    wxString text = m_text;
    switch( (wxChar) text.GetChar( 0 ) )
    {
    case 'M':
        sex = SEX_Male;
        break;
    case 'F':
        sex = SEX_Female;
        break;
    default:
        sex = SEX_Unknown;
    }
    gind.SetSex( sex );
    ReadNextLine();
}

void recGedParse::ReadIndEvent( GedIndividual& gind, int level )
{
    recEvent ev(0);
    ev.Save(); // We need the id number
    recEventPersona ep(0);
    ep.f_event_id = ev.f_id;
    ep.f_per_id = gind.GetPersonaID();
    wxString titlefmt;
    recDate::DatePoint dp;

    switch( m_tag )
    {
    case tagBIRT:
        ev.f_type_id = recEventType::ET_Birth;
        ep.f_role_id = recEventTypeRole::ROLE_Birth_Born;
        titlefmt = _("Birth of %s");
        dp = recDate::DATE_POINT_Beg;
        break;
    case tagCHR:
        ev.f_type_id = recEventType::ET_Baptism;
        ep.f_role_id = recEventTypeRole::ROLE_Baptism_Baptised;
        titlefmt = _("Baptism of %s");
        dp = recDate::DATE_POINT_Beg;
        break;
    case tagDEAT:
        ev.f_type_id = recEventType::ET_Death;
        ep.f_role_id = recEventTypeRole::ROLE_Death_Died;
        titlefmt = _("Death of %s");
        dp = recDate::DATE_POINT_End;
        break;
    case tagBURI:
        ev.f_type_id = recEventType::ET_Burial;
        ep.f_role_id = recEventTypeRole::ROLE_Burial_Deceased;
        titlefmt = _("Burial of %s");
        dp = recDate::DATE_POINT_End;
        break;
    default:
        return; // do nothing
    }

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagDATE:
                ev.f_date1_id = ParseEvDate( level+1 );
                break;
            case tagPLAC:
                ev.f_place_id = ParseEvPlace( level+1 );
                break;
            case tag_END:
                cont = FALSE;
                continue;
            }
        }
        cont = ReadNextLine();
    }
    ev.f_title = wxString::Format( titlefmt, gind.GetNameStr() );
    ev.f_date_pt = recDate::GetDatePoint( ev.f_date1_id, dp );
    ev.Save();
    ep.f_per_seq = ev.GetLastPersonaSeqNumber() + 1;
    ep.Save();
}

idt recGedParse::ParseEvDate( int level )
{
    recDate date(0);
    wxString text = m_text;
    static wxString MonName[] = {
        wxT("JAN"), wxT("FEB"), wxT("MAR"), wxT("APR"), wxT("MAY"), wxT("JUN"),
        wxT("JUL"), wxT("AUG"), wxT("SEP"), wxT("OCT"), wxT("NOV"), wxT("DEC")
    };

    if( text.find( '/' ) != wxNOT_FOUND ) {
        // Date strings with a / char are not (at the moment) valid.
        date.f_descrip = text;
        date.Save();
        return date.f_id;
    }

    wxStringTokenizer tkz( text );
    if( tkz.HasMoreTokens() == false ) return 0;
    wxString token = tkz.GetNextToken();

    if( token.compare( wxT("FROM") ) == 0 ||
        token.compare( wxT("TO") ) == 0 ||
        token.compare( wxT("BET") ) == 0 ||
        token.compare( wxT("INT") ) == 0 )
    {
        date.f_descrip = m_text;
        date.Save();
        return date.f_id;
    }

    CalendarScheme sch = CALENDAR_SCH_Unstated;
    if(      token.compare( wxT("@#DGREGORIAN@") ) == 0 ) sch = CALENDAR_SCH_Gregorian;
    else if( token.compare( wxT("@#DJULIAN@") )    == 0 ) sch = CALENDAR_SCH_Julian;
    else if( token.compare( wxT("@#DUNKNOWN@") )   == 0 ) sch = CALENDAR_SCH_Unknown;
    else if( token.compare( 0, 3, wxT("@#D") )     == 0 ) sch = CALENDAR_SCH_Unlisted;

    if( sch == CALENDAR_SCH_Unlisted || sch == CALENDAR_SCH_Unknown ) {
        date.f_record_sch = date.f_display_sch = sch;
        date.f_descrip = m_text;
        date.Save();
        return date.f_id;
    }

    if( sch == CALENDAR_SCH_Unstated ) {
        // The spec states
        sch = CALENDAR_SCH_Gregorian;
    } else {
        if( tkz.HasMoreTokens() == false ) return 0;
        token = tkz.GetNextToken();
    }

    /* 1st check for prefix */
    recDate::TypePrefix flags = recDate::PREF_Unstated;
    if( token.compare( wxT("ABT") ) == 0 ||
        token.compare( wxT("CAL") ) == 0 ||
        token.compare( wxT("EST") ) == 0 )
    {
        flags = recDate::PREF_About;
    } else if( token.compare( wxT("BEF") ) == 0 ) {
        flags = recDate::PREF_Before;
    } else if( token.compare( wxT("AFT") ) == 0 ) {
        flags = recDate::PREF_After;
    }

    if( flags != recDate::PREF_Unstated ) {
        if( tkz.HasMoreTokens() == false ) return 0;
        token = tkz.GetNextToken();
    } else {
        flags = recDate::PREF_On;
    }

    long day = 0, month = 0, year = 0;
    if( token.ToLong( &day ) == true ) {
        if( tkz.HasMoreTokens() == false ) {
            year = day;
            day = 0;
        } else {
            token = tkz.GetNextToken();
        }
    }
    // look for month
    for( int i = 0 ; i < 12 ; i++ ) {
        if( token.compare( MonName[i] ) == 0 ) {
            month = i+1;
            if( tkz.HasMoreTokens() == false ) {
                // if there is a month there must be a year
                return 0;
            }
            token = tkz.GetNextToken();
            break;
        }
    }
    if( token.ToLong( &year ) == false ) return 0;

    long jdn1 = 0, jdn2 = 0;
    DMYDate dmy;
    dmy.SetDMY( (day==0) ? 1 : day, (month==0) ? 1 : month, year );
    calConvertToJdn( jdn1, dmy, sch );
    if( month == 0 ) month = 12;
    if( day == 0 ) day = calLastDayInMonth( month, year, sch );
    dmy.SetDMY( day, month, year );
    calConvertToJdn( jdn2, dmy, sch );

    date.f_jdn = jdn1;
    date.f_range = jdn2 - jdn1;
    date.f_type = flags;
    date.f_record_sch = date.f_display_sch = sch;
    date.Save();
    return date.f_id;
}

idt recGedParse::ParseEvPlace( int level )
{
    recPlace place(0);
    place.Save();
    recPlacePart pp(0);
    pp.f_place_id = place.f_id;
    pp.f_type_id = recPlacePartType::TYPE_Address;
    pp.f_val = m_text;
    pp.Save();
    return place.f_id;
}

void recGedParse::ReadIndAttr( GedIndividual& gind, int level )
{
    recAttribute attr(0);
    attr.Save(); // We need th Attribute id
    attr.f_per_id = gind.GetPersonaID();
    switch( m_tag )
    {
    case tagOCCU:
        attr.f_type_id = recAttributeType::ATYPE_Occupation;
        break;
    default:
        return; // ignore unrecognised attribute
    }
    attr.f_val = m_text;

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tag_END:
                cont = false;
                continue;
            }
        }
        cont = ReadNextLine();
    }
    attr.Save();
}

void recGedParse::ReadFam( int level )
{
    GedFamily gfam;
    gfam.SetFamId( m_famMap[ m_index ] );

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagHUSB:
                gfam.SetHusb( m_indiMap[ m_xref ] );
                break;
            case tagWIFE:
                gfam.SetWife( m_indiMap[ m_xref ] );
                break;
            case tagCHIL:
                gfam.AddChild( m_indiMap[ m_xref ] );
                break;
            case tagMARR:
                ReadFamEvent( gfam, level+1 );
                continue;
            case tag_END:
                cont = FALSE;
                continue;
            }
        }
        cont = ReadNextLine();
    }
    gfam.Save();
}

void recGedParse::ReadFamEvent( GedFamily& gfam, int level )
{
    recEvent ev(0);
    ev.Save(); // We need the id number
    wxString titlefmt;

    recEventPersona epHusb(0);
    epHusb.f_event_id = ev.f_id;
    epHusb.f_per_id = gfam.GetHusbPerId();

    recEventPersona epWife(0);
    epWife.f_event_id = ev.f_id;
    epWife.f_per_id = gfam.GetWifePerId();

    switch( m_tag )
    {
    case tagMARR:
        ev.f_type_id = recEventType::ET_Marriage;
        epHusb.f_role_id = recEventTypeRole::ROLE_Marriage_Groom;
        epWife.f_role_id = recEventTypeRole::ROLE_Marriage_Bride;
        titlefmt = _("Marriage of %s and %s");
        break;
    default:
        return; // do nothing
    }

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagDATE:
                ev.f_date1_id = ParseEvDate( level+1 );
                break;
            case tagPLAC:
                ev.f_place_id = ParseEvPlace( level+1 );
                break;
            case tag_END:
                cont = FALSE;
                continue;
            }
        }
        cont = ReadNextLine();
    }

    ev.f_title = wxString::Format( titlefmt, gfam.GetHusbNameStr(), gfam.GetWifeNameStr() );
    ev.f_date_pt = recDate::GetDatePoint( ev.f_date1_id );
    ev.Save();

    int seq = ev.GetLastPersonaSeqNumber();
    epHusb.f_per_seq = seq + 1;
    if( epHusb.FGetPerID() ) epHusb.Save();
    epWife.f_per_seq = seq + 2;
    if( epWife.FGetPerID() ) epWife.Save();
}

void recGedParse::ReadSubm( int level )
{
    GedSubmitter gsubm( m_submMap[ m_index ] );

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagNAME:
                gsubm.SetName( m_text );
                break;
            case tagADDR:
                gsubm.SaveContact( recContactType::CT_Address, ReadAddr( level + 1 ) );
                continue;
            case tagPHON:
                gsubm.SaveContact( recContactType::CT_Telephone, m_text );
                break;
            case tagEMAI:
                gsubm.SaveContact( recContactType::CT_Email, m_text );
                break;
    // TODO: Add Fax to contact types
    //        case tagFAX:
    //            gsubm.SaveContact( recContactType::CT_FAX, m_text );
    //            break;
            case tagWWW:
                gsubm.SaveContact( recContactType::CT_Website, m_text );
                break;
            case tag_END:
                cont = FALSE;
                continue;
            }
        }
        cont = ReadNextLine();
    }
    gsubm.Save();
}

wxString recGedParse::ReadAddr( int level )
{
    wxString addr1 = m_text;
    wxString addr2;
    wxString addr3;
    wxString addrCont;
    int addrCnt = 0;

    bool cont = ReadNextLine();
    while( cont && m_level >= level ) {
        if( m_level == level ) {
            switch( m_tag )
            {
            case tagADR1:
                addr1 = m_text;
                break;
            case tagADR2:
                addr2 = m_text;
                break;
            case tagADR3:
                addr3 = m_text;
                break;
            case tagCONT:
                switch( addrCnt ) 
                {
                case 0:
                    addr2 = m_text;
                    addrCnt = 1;
                    break;
                case 1:
                    addr3 = m_text;
                    addrCnt = 2;
                    break;
                default:
                    if( !addrCont.IsEmpty() ) {
                        addrCont << "\n";
                    }
                    addrCont << m_text;
                }
                break;
            case tag_END:
                cont = FALSE;
                continue;
            }
        }
        cont = ReadNextLine();
    }
    if( !addr1.IsEmpty() && !addr2.IsEmpty() ) addr1 << "\n";
    addr1 << addr2;
    if( !addr1.IsEmpty() && !addr3.IsEmpty() ) addr1 << "\n";
    addr1 << addr3;
    if( !addr1.IsEmpty() && !addrCont.IsEmpty() ) addr1 << "\n";
    addr1 << addrCont;
    return addr1;
}


void GedFamily::UpdateIndividual( idt* p_perID, idt indID )
{
    recIndividual ind(indID);
    if( ind.f_fam_id == 0 ) {
        ind.f_fam_id = m_fam.f_id;
        ind.Save();
    }
    *p_perID = ind.f_per_id;
}

void GedFamily::AddChild( idt indID )
{
    recFamilyIndividual fi(0);
    fi.fSetFamID( m_fam.f_id );
    fi.fSetIndID( indID );
    fi.fSetSeqChild( ++m_childSeq );
    fi.Save();
}

GedSubmitter::GedSubmitter( idt resID ) 
    : m_res(resID)
{ 
    m_cl.ReadID( m_res.FGetConListID() );

    if( m_cl.FGetID() == 0 ) {
        m_cl.Save();
        m_res.FSetConListID( m_cl.FGetID() );
    }
}

void GedSubmitter::SaveContact( recContactType::Type type, const wxString& value )
{
    if( value.IsEmpty() ) return;

    recContact con(0);
    con.FSetTypeID( type );
    con.FSetListID( m_cl.FGetID() );
    con.FSetValue( value );
    con.Save();
}

// End of tfpRdGed.cpp Source
