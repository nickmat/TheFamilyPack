/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        rec/recGedExport.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Read GEDCOM import files.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     11th November 2015
 * Copyright:   Copyright (c) 2015, Nick Matthews.
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

#include "rec/recDb.h"

//#include <wx/filename.h>

bool recGedExport::Export()
{
    idt cuser = recSystem::GetPropertyValueID( recSystem::SP_CurrentUser );
    m_out <<
        "0 HEAD\n"
        "1 SOUR TFP\n"
        "2 VERS " << recVerStr << "\n"
        "2 NAME The Family Pack\n"
        "1 SUBM @" << recUser::GetIdStr( cuser ) << "@\n"
        "1 GEDC\n"
        "2 VERS 5.5.1\n"
        "2 FORM LINEAGE-LINKED\n"
        "1 CHAR UTF-8\n"
    ;

    recUserVec users = recUser::GetUsers();
    for( size_t i = 0 ; i < users.size() ; i++ ) {
        if( users[i].FGetID() == 0 ) {
            continue;
        }
        recResearcher res(users[i].FGetResID());
        m_out <<
            "0 @" << users[i].GetIdStr() << "@ SUBM\n"
            "1 NAME " << res.FGetName() << "\n"
        ;
    }
    recIdVec ids = recIndividual::GetIdVec();
    for( size_t i = 0 ; i < ids.size() ; i++ ) {
        ExportIndividual( ids[i], 0 );
    }
    recFamilyVec fams = recFamily::GetFamilyVec();
    for( size_t i = 0 ; i < fams.size() ; i++ ) {
        ExportFamily( fams[i], 0 );
    }

    m_out << "0 TRLR\n";

    return true;
}

void recGedExport::ExportIndividual( idt indID, int level )
{
    m_out << level << " @" << recIndividual::GetIdStr( indID ) << "@ INDI\n";
    level++;
    recNameVec names = recName::GetNames( indID, 0 );
    for( size_t i = 0 ; i < names.size() ; i++ ) {
        m_out << level << " NAME";
        recNamePartVec parts = names[i].GetParts();
        for( size_t k = 0 ; k < parts.size() ; k++ ) {
            if( parts[k].FGetTypeID() == NAME_TYPE_Surname ) {
                m_out << " /" << parts[k].FGetValue() << "/";
            } else {
                m_out << " " << parts[k].FGetValue();
            }
        }
        m_out << "\n";
    }
    Sex sex = recIndividual::GetSex( indID );
    if( sex == SEX_Male ) {
        m_out << level << " SEX M\n";
    } else if( sex == SEX_Female ) {
        m_out << level << " SEX F\n";
    }
    ExportIndEvents( indID, recET_GRP_Birth, level );
    ExportIndEvents( indID, recET_GRP_NrBirth, level );
    ExportIndEvents( indID, recET_GRP_Death, level );
    ExportIndEvents( indID, recET_GRP_NrDeath, level );
    ExportIndEvents( indID, recET_GRP_Personal, level );
    int pri = recIndividual::GetPrivacy( indID );
    if( pri >= 50 ) {
        m_out << level << " _PRI Y\n";
    }
    recFamilyVec fam = recIndividual::GetParentList( indID );
    for( size_t i = 0 ; i < fam.size() ; i++ ) {
        m_out << level << " FAMC @" << fam[i].GetIdStr() << "@\n";
    }
    fam = recIndividual::GetFamilyList( indID );
    for( size_t i = 0 ; i < fam.size() ; i++ ) {
        m_out << level << " FAMS @" << fam[i].GetIdStr() << "@\n";
    }
}

void recGedExport::ExportFamily( const recFamily& fam, int level )
{
    m_out << level << " @" << fam.GetIdStr() << "@ FAM\n";
    level++;
    if( fam.FGetHusbID() ) {
        m_out << level << " HUSB @" << 
            recIndividual::GetIdStr( fam.FGetHusbID() ) << "@\n"; 
    }
    if( fam.FGetWifeID() ) {
        m_out << level << " WIFE @" << 
            recIndividual::GetIdStr( fam.FGetWifeID() ) << "@\n"; 
    }
    ExportFamEvents( fam.FGetID(), level );
    recIdVec ids = fam.GetChildrenIds();
    for( size_t i = 0 ; i < ids.size() ; i++ ) {
        m_out << level << " CHIL @" <<
            recIndividual::GetIdStr( ids[i] ) << "@\n"; 
    }
}

void recGedExport::ExportIndEvents( idt indID, recET_GRP grp, int level )
{
    recIdVec events = recIndividual::FindEvents( indID, grp );
    ExportEvents( events, level, indID );
}

void recGedExport::ExportFamEvents( idt famID, int level )
{
    recIdVec events = recFamily::GetEventIDs( famID );
    ExportEvents( events, level, famID );
}

void recGedExport::ExportEvents( const recIdVec& events, int level, idt id )
{
    for( size_t i = 0 ; i < events.size() ; i++ ) {
        recEvent eve( events[i] );
        idt type = eve.FGetTypeID();
        recEventType et( type );
        wxString tag, desc;
        switch( type )
        {
        case recEventType::ET_Birth: tag = "BIRT"; break;
        case recEventType::ET_Baptism: tag = "CHR"; break;
        case recEventType::ET_Death: tag = "DEAT"; break;
        case recEventType::ET_Burial: tag = "BURI"; break;
        case recEventType::ET_Marriage: tag = "MARR"; break;
        case recEventType::ET_Occupation: tag = "OCCU"; break;
        default: continue;
        }
        if( et.FGetGrp() == recET_GRP_Personal ) {
            if( eve.FGetHigherID() != 0 ) {
                continue; // only interested in top-most event
            }
            desc = " " + recIndividualEvent::GetRoleStr( id, type );
        }
        m_out << level << " " << tag << desc << "\n";
        // TODO: Handle date period (where date2 != 0)
        ExportDate( eve.FGetDate1ID(), level + 1 );
        ExportPlace( eve.FGetPlaceID(), level + 1 );
    }
}

void recGedExport::ExportDate( idt dateID, int level )
{
    if( dateID == 0 ) return;
    recDate date(dateID);
    recDate::TypePrefix type = (recDate::TypePrefix) date.FGetType();
    if( type == recDate::PREF_Unstated || type == recDate::PREF_Not ) return;

    long beg = date.GetDatePoint( recDate::DATE_POINT_Beg );
    if( beg == 0 ) {
        wxString text = date.FGetDescrip();
        if( !text.empty() ){
            m_out << level << " DATE (" << text << ")\n";
        }
        return;
    }
    wxString prefix;
    if( type == recDate::PREF_About ) {
        prefix = " ABT";
    }
    wxString calEsc;
    CalendarScheme sch = date.FGetDisplaySch();
    switch( sch )
    {
    case CALENDAR_SCH_Gregorian:
        break;
    case CALENDAR_SCH_Julian:
        calEsc = " @#DJULIAN@";
        break;
    case CALENDAR_SCH_FrenchRevolution:
        calEsc = " @#DFRENCH R@";
        break;
    case CALENDAR_SCH_Hebrew:
        calEsc = " @#DHEBREW@";
        break;
    default:
        sch = CALENDAR_SCH_Gregorian; // Only option left
        break;
    }

    wxString datestr = calStrFromJdnRange( date.FGetJdn(), date.GetEndJdn(), sch ).Upper();
    if( datestr.empty() ) {
        return;
    }
    size_t pos = datestr.find( '~' );
    if( pos != wxString::npos ) {
        // treat as BET and AFT dates
        long end = date.GetDatePoint( recDate::DATE_POINT_End );
        wxString begstr = calStrFromJdn( beg, sch ).Upper();
        wxString endstr = calStrFromJdn( end, sch ).Upper();
        m_out << level << " DATE BET" << calEsc << " " << begstr 
            << " AND" << calEsc << " " << endstr << "\n";
        return;
    }
    // treat as single date
    if( type == recDate::PREF_Before || type == recDate::PREF_OrBefore ) {
        prefix = " BEF";
    } else if( type == recDate::PREF_After || type == recDate::PREF_OrAfter ) {
        prefix = " AFT";
    }
    m_out << level << " DATE" << prefix << calEsc << " " << datestr << "\n";
}

void recGedExport::ExportPlace( idt placeID, int level )
{
    if( placeID == 0 ) return;
    wxString place = recPlace::GetAddressStr( placeID );
    if( place.empty() ) return;
    m_out << level << " PLAC " << place << "\n";
}


// End of rec/recGedExport.cpp Source
