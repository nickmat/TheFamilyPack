/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recVersion.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Version record.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2010
 * Copyright:   Copyright (c) 2010 ~ 2019, Nick Matthews.
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

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recVersion.h>

recVersion::recVersion( const recVersion& v )
{
    f_id       = v.f_id;
    f_major    = v.f_major;
    f_minor    = v.f_minor;
    f_revision = v.f_revision;
    f_test     = v.f_test;
}

void recVersion::Clear()
{
    f_id       = 0;
    f_major    = 0;
    f_minor    = 0;
    f_revision = 0;
    f_test     = 0;
}

bool recVersion::Read()
{
    wxSQLite3StatementBuffer sql;

    if ( f_id == 0 ) {
        Clear();
        return false;
    }

    sql.Format(
        "SELECT major, minor, revision, test"
        " FROM Version WHERE id=" ID ";",
        f_id
    );
    wxSQLite3Table result = s_db->GetTable( sql );
    if( result.GetRowCount() != 1 ) {
        Clear();
        return false;
    }
    f_id       = 1;
    f_major    = result.GetInt( 0 );
    f_minor    = result.GetInt( 1 );
    f_revision = result.GetInt( 2 );
    f_test     = result.GetInt( 3 );
    return true;
}


wxString recVersion::GetVersionStr()
{
    recVersion v( DT_Full );
    return wxString::Format(
        "%d.%d.%d.%d",
        v.f_major, v.f_minor, v.f_revision, v.f_test
    );
}

bool recVersion::Manage()
{
    if ( !s_db->IsOpen() || !recVersion::TableExists() ) {
        return false;
    }
    return recDoUpgrade();
}

bool recVersion::IsEqual( int major, int minor, int revision, int test ) const
{
    bool ret = (f_major == major);

    if( minor == -1 ) return ret;
    ret = ret && (f_minor == minor);

    if( revision == -1 ) return ret;
    ret = ret && (f_revision == revision);

    if( test == -1 ) return ret;
    return ret && (f_test == test);
}

bool recVersion::IsMoreThan( int major, int minor, int revision, int test ) const
{
    if( f_major > major ) return true;
    if( f_major < major ) return false;

    if( minor == -1 ) return false;
    if( f_minor > minor ) return true;
    if( f_minor < minor ) return false;

    if( revision == -1 ) return false;
    if( f_revision > revision ) return true;
    if( f_revision < revision ) return false;

    if( test == -1 ) return false;
    if( f_test > test ) return true;
    return false;
}

bool recVersion::IsLessThan( int major, int minor, int revision, int test ) const
{
    if( f_major < major ) return true;
    if( f_major > major ) return false;

    if( minor == -1 ) return false;
    if( f_minor < minor ) return true;
    if( f_minor > minor ) return false;

    if( revision == -1 ) return false;
    if( f_revision < revision ) return true;
    if( f_revision > revision ) return false;

    if( test == -1 ) return false;
    if( f_test < test ) return true;
    return false;
}

// End of src/rec/recVersion.cpp file
