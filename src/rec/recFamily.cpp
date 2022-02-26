/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recFamily.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 Family record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     8th January 2022
 * Copyright:   Copyright (c) 2022, Nick Matthews.
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

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recFamily.h>

#include <rec/recIndividual.h>

#include <wx/tokenzr.h>


//============================================================================
//-------------------------[ recFamily ]--------------------------------------
//============================================================================

recFamily::recFamily( const recFamily& f )
{
    f_id       = f.f_id;
    f_husb_id  = f.f_husb_id;
    f_wife_id  = f.f_wife_id;
}

void recFamily::Clear()
{
    f_id       = 0;
    f_husb_id  = 0;
    f_wife_id  = 0;
}

void recFamily::Save( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 )
    {
        // Add new record
        sql.Format(
            "INSERT INTO \"%s\".Family (husb_id, wife_id) "
            "VALUES (" ID ", " ID ");",
            UTF8_( dbname ), f_husb_id, f_wife_id
        );
        s_db->ExecuteUpdate( sql );
        f_id = GET_ID( s_db->GetLastRowId() );
    } else {
        // Does record exist
        if( !Exists() )
        {
            // Add new record
            sql.Format(
                "INSERT INTO \"%s\".Family (id, husb_id, wife_id) "
                "VALUES (" ID ", " ID ", " ID ");",
                UTF8_( dbname ), f_id, f_husb_id, f_wife_id
            );
        } else {
            // Update existing record
            sql.Format(
                "UPDATE \"%s\".Family SET husb_id=" ID ", wife_id=" ID " "
                "WHERE id=" ID ";",
                UTF8_( dbname ), f_husb_id, f_wife_id, f_id
            );
        }
        s_db->ExecuteUpdate( sql );
    }
}

bool recFamily::Read( const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT husb_id, wife_id FROM \"%s\".Family WHERE id=" ID ";",
        UTF8_( dbname ), f_id
    );
    result = s_db->GetTable( sql );

    if( result.GetRowCount() != 1 )
    {
        Clear();
        return false;
    }
    result.SetRow( 0 );
    f_husb_id  = GET_ID( result.GetInt64( 0 ) );
    f_wife_id  = GET_ID( result.GetInt64( 1 ) );
    return true;
}

bool recFamily::Equivalent( const recFamily& r2 ) const
{
    return
        f_husb_id == r2.f_husb_id &&
        f_wife_id == r2.f_wife_id
    ;
}

recIdVec recFamily::GetCoupleAsIdVec() const
{
    recIdVec ids;
    if( f_husb_id ) {
        ids.push_back( f_husb_id );
    }
    if( f_wife_id ) {
        ids.push_back( f_wife_id );
    }
    return ids;
}

recIdVec recFamily::GetCoupleAsIdVec( idt famID, const wxString& dbname )
{
    recFamily fam( famID, dbname );
    return fam.GetCoupleAsIdVec();
}

recIdVec recFamily::GetFamilyIdVec( const wxString& dbname )
{
    recIdVec famIDs;
    wxSQLite3StatementBuffer sql;

    sql.Format( "SELECT id FROM \"%s\".Family;", UTF8_( dbname ) );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    while( result.NextRow() ) {
        famIDs.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return famIDs;
}

recFamilyVec recFamily::GetFamilyVec( const wxString& dbname )
{
    recFamilyVec fams;
    wxSQLite3StatementBuffer sql;
    sql.Format( 
        "SELECT id, husb_id, wife_id FROM \"%s\".Family;",
        UTF8_( dbname )
    );
    wxSQLite3ResultSet result = s_db->ExecuteQuery( sql );

    recFamily fam(0);
    while( result.NextRow() ) {
        fam.f_id = GET_ID( result.GetInt64( 0 ) );
        fam.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        fam.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        fams.push_back( fam );
    }
    return fams;
}

// Decode the string which is in the form "Fx1" or
// "Fx1,x2,x3" where x1 is the Family id
// x2 is the husband id and x3 the wife id.
// or else string has the form FIx where x
// is a recIndividual id.
// Returns true if successful.
bool recFamily::Decode( const wxString& str, const wxString& dbname )
{
    if( str.StartsWith( "FI" ) ) {
        idt indID = recGetID( str.Mid( 2 ) );
        f_id = recIndividual::GetFamilyID( indID );
        Read( dbname );
        if( f_id == 0 ) {
            Sex sex = recIndividual::GetSex( indID );
            if( sex == Sex::female ) {
                f_wife_id = indID;
            } else {
                f_husb_id = indID;
            }
        }
    } else {
        wxStringTokenizer tk( str.Mid(1), "," );

        if( !tk.HasMoreTokens() ) return false;
        f_id = recGetID( tk.GetNextToken() );

        if( tk.HasMoreTokens() ) {
            f_husb_id = recGetID( tk.GetNextToken() );

            if( !tk.HasMoreTokens() ) return false;
            f_wife_id = recGetID( tk.GetNextToken() );
        } else {
            Read( dbname );
        }
    }
    return true;
}

idt recFamily::GetUnionEvent( idt famID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT FE.event_id"
        " FROM \"%s\".FamilyEvent FE, \"%s\".Event E, \"%s\".EventType ET"
        " WHERE FE.fam_id=" ID " AND FE.event_id=E.id AND E.type_id=ET.id"
        " AND ET.grp=3 ORDER BY FE.fam_seq",
        UTF8_( dbname ), UTF8_( dbname ), UTF8_( dbname ), famID
    );
    result = s_db->ExecuteQuery( sql );
    if( result.NextRow() ) {
        return GET_ID( result.GetInt64( 0 ) );
    }
    return 0;
}

idt recFamily::GetSpouseID( idt indID ) const
{
    if( indID == f_husb_id ) {
        return f_wife_id;
    }
    if( indID == f_wife_id ) {
        return f_husb_id;
    }
    return 0;
}

idt recFamily::Find( idt ind1ID, idt ind2ID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT id FROM \"%s\".Family"
        " WHERE (husb_id=" ID " AND wife_id=" ID ") OR (husb_id=" ID " AND wife_id=" ID ");",
        UTF8_( dbname ), ind1ID, ind2ID, ind2ID, ind1ID
    );
    result = s_db->ExecuteQuery( sql );
    if( result.NextRow() ) {
        return GET_ID( result.GetInt64( 0 ) );
    }
    return 0;
}

recIdVec recFamily::FindVec(
    const recIdVec& ind1IDs, const recIdVec& ind2IDs, const wxString& dbname )
{
    recIdVec famIDs;
    for( size_t i = 0 ; i < ind1IDs.size() ; i++ ) {
        for( size_t j = 0 ; j < ind2IDs.size() ; j++ ) {
            idt famID;

            famID = recFamily::Find( ind1IDs[i], 0, dbname );
            recIdVecAddIfUnique( famIDs, famID );
            famID = recFamily::Find( 0, ind2IDs[j], dbname );
            recIdVecAddIfUnique( famIDs, famID );

            famID = recFamily::Find( ind1IDs[i], ind2IDs[j], dbname );
            recIdVecAddIfUnique( famIDs, famID );
        }
    }
    return famIDs;
}


bool recFamily::ReadParents( idt ind, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;
    wxSQLite3ResultSet result;

    sql.Format(
        "SELECT fam_id FROM \"%s\".FamilyIndividual WHERE ind_id=" ID ";",
        UTF8_( dbname ), ind
    );
    result = s_db->ExecuteQuery( sql );
    f_id =  GET_ID( result.GetInt64( 0 ) );
    return Read();
}

recFamilyVec recFamily::GetFamilyList( idt ind, const wxString& dbname )
{
    recFamilyVec families;
    recFamily family;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( ind == 0 ) return families;

    sql.Format(
        "SELECT id, husb_id, wife_id FROM \"%s\".Family "
        "WHERE husb_id=" ID " OR wife_id=" ID ";",
        UTF8_( dbname ), ind, ind
    );
    result = s_db->GetTable( sql );

    for( int i = 0; i < result.GetRowCount(); i++ ) {
        result.SetRow( i );
        family.f_id = GET_ID( result.GetInt64( 0 ) );
        family.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        family.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        families.push_back( family );
    }
    return families;
}

recFamilyVec recFamily::GetParentList( idt indID, const wxString& dbname )
{
    recFamily parent;
    recFamilyVec parents;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( indID == 0 ) return parents;

    sql.Format(
        "SELECT F.id, F.husb_id, F.wife_id "
        "FROM \"%s\".Family F, \"%s\".FamilyIndividual FI "
        "WHERE F.id=FI.fam_id AND FI.ind_id=" ID ";",
        UTF8_( dbname ), UTF8_( dbname ), indID
    );
    result = s_db->GetTable( sql );

    for( int i = 0; i < result.GetRowCount(); i++ ) {
        result.SetRow( i );
        parent.f_id = GET_ID( result.GetInt64( 0 ) );
        parent.f_husb_id = GET_ID( result.GetInt64( 1 ) );
        parent.f_wife_id = GET_ID( result.GetInt64( 2 ) );
        parents.push_back( parent );
    }
    return parents;
}

recIdVec recFamily::GetChildrenIds( idt fam, const wxString& dbname )
{
    recIdVec children;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( fam == 0 ) return children;

    sql.Format(
        "SELECT ind_id FROM \"%s\".FamilyIndividual WHERE fam_id=" ID
        " ORDER BY seq_child ASC;",
        UTF8_( dbname ), fam
    );
    result = s_db->GetTable( sql );

    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        children.push_back( GET_ID( result.GetInt64( 0 ) ) );
    }
    return children;
}

int recFamily::GetChildCount( idt famID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT COUNT(*) FROM \"%s\".FamilyIndividual WHERE fam_id=" ID ";",
        UTF8_( dbname ), famID
    );
    return s_db->ExecuteScalar( sql );
}

int recFamily::GetChildNextSequence( idt famID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(seq_child) FROM \"%s\".FamilyIndividual WHERE fam_id=" ID ";",
        UTF8_( dbname ), famID
    );
    return s_db->ExecuteScalar( sql ) + 1;
}

int recFamily::GetParentNextSequence( idt indID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(seq_parent) FROM \"%s\".FamilyIndividual WHERE ind_id=" ID ";",
        UTF8_( dbname ), indID
    );
    return s_db->ExecuteScalar( sql ) + 1;
}

recFamIndVec recFamily::GetChildLinks( idt famID, const wxString& dbname )
{
    recFamIndVec ChildLinks;
    recFamilyIndividual fi;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( famID == 0 ) return ChildLinks;

    sql.Format(
        "SELECT id, ind_id, seq_child, seq_parent FROM \"%s\".FamilyIndividual"
        " WHERE fam_id=" ID " ORDER BY seq_child ASC;",
        UTF8_( dbname ), famID
    );
    result = s_db->GetTable( sql );

    fi.FSetFamID( famID );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        fi.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        fi.FSetIndID( GET_ID( result.GetInt64( 1 ) ) );
        fi.FSetSeqChild( result.GetInt( 2 ) );
        fi.FSetSeqParent( result.GetInt( 3 ) );
        ChildLinks.push_back( fi );
    }
    return ChildLinks;
}

recFamilyEventVec recFamily::GetEvents( idt famID, const wxString& dbname )
{
    recFamilyEventVec fes;
    recFamilyEvent fe;
    wxSQLite3StatementBuffer sql;
    wxSQLite3Table result;

    if( famID == 0 ) return fes;

    sql.Format(
        "SELECT id, event_id, note, fam_seq FROM \"%s\".FamilyEvent"
        " WHERE fam_id=" ID " ORDER BY fam_seq;",
        UTF8_( dbname ), famID
    );
    result = s_db->GetTable( sql );

    fe.FSetFamID( famID );
    for( int i = 0 ; i < result.GetRowCount() ; i++ )
    {
        result.SetRow( i );
        fe.FSetID( GET_ID( result.GetInt64( 0 ) ) );
        fe.FSetEventID( GET_ID( result.GetInt64( 1 ) ) );
        fe.FSetNote( result.GetAsString( 2 ) );
        fe.FSetFamSeq( result.GetInt( 3 ) );
        fes.push_back( fe );
    }
    return fes;
}

recIdVec recFamily::GetEventIDs( idt famID, const wxString& dbname )
{
    const char* fmt =
        "SELECT event_id FROM \"%s\".FamilyEvent"
        " WHERE fam_id=" ID
        " ORDER BY fam_seq;"
    ;
    return ExecuteIdVec( fmt, UTF8_( dbname ), famID );
}

int recFamily::GetMaxEventSeqNumber( idt famID, const wxString& dbname )
{
    wxSQLite3StatementBuffer sql;

    sql.Format(
        "SELECT MAX(fam_seq) FROM \"%s\".FamilyEvent WHERE fam_id=" ID ";",
        UTF8_( dbname ), famID
    );
    return s_db->ExecuteScalar( sql );
}

// A singleton family is one without a partner, attached children
// or FamilyEvent's.
bool recFamily::IsSingleton( const wxString& dbname ) const
{
    if( FGetHusbID() && FGetWifeID() ) {
        return false;
    }
    if( GetChildCount( dbname ) != 0 ) {
        return false;
    }
    recFamilyEventVec es = GetEvents( dbname );
    if( es.empty() ) {
        return true;
    }
    return false;
}

// We will find, modify or create a family for these two individuals.
idt recFamily::FindOrCreate( idt ind1ID, idt ind2ID, const wxString& dbname )
{
    idt famID = recFamily::Find( ind1ID, ind2ID, dbname );
    if( famID ) {
        // The family exists already.
        return famID;
    }
    famID = recIndividual::GetFamilyID( ind1ID, dbname );
    if( recFamily::IsSingleton( famID, dbname ) ) {
        // We will use this family
        idt fam2ID = recIndividual::GetFamilyID( ind2ID, dbname );
        if( recFamily::IsSingleton( fam2ID, dbname ) ) {
            recIndividual ind2( ind2ID, dbname );
            ind2.FSetFamID( famID );
            ind2.Save( dbname );
            // This is no longer needed
            recFamily::Delete( fam2ID, dbname );
        }
        recFamily fam( famID, dbname );
        if( fam.FGetWifeID() == 0 ) {
            fam.FSetWifeID( ind2ID );
        } else {
            assert( fam.FGetHusbID() == 0 );
            fam.FSetHusbID( ind2ID );
        }
        fam.Save( dbname );
        return fam.FGetID();
    }
    return 0;
}

void recFamily::RemoveFromEvents( idt famID, idt indID, const wxString& dbname )
{
    if( famID == 0 || indID == 0 ) return;

    wxSQLite3StatementBuffer sql;
    recFamilyEventVec fes = GetEvents( famID );
    for( size_t i = 0 ; i < fes.size() ; i++ ) {
        sql.Format(
            "DELETE FROM \"%s\".IndividualEvent WHERE ind_id=" ID " AND event_id=" ID ";",
            UTF8_( dbname ), indID, fes[i].FGetEventID()
        );
        s_db->ExecuteUpdate( sql );
    }
}

void recFamily::RemoveFromDatabase( idt famID, const wxString& dbname )
{
    // We are not responsible for deleting the Individuals.
    wxSQLite3StatementBuffer sql;
    sql.Format(
        "DELETE FROM \"%s\".FamilyIndividual WHERE fam_id=" ID " ;"
        "DELETE FROM \"%s\".FamilyEventa WHERE fam_id=" ID " ;"
        "DELETE FROM \"%s\".FamilyEvent WHERE fam_id=" ID " ;",
        UTF8_( dbname ), famID, UTF8_( dbname ), famID, UTF8_( dbname ), famID
    );
    s_db->ExecuteUpdate( sql );
    Delete( famID, dbname );
}


// End of src/rec/recFamily.cpp file
