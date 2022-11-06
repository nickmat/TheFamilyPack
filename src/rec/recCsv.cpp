/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recCsv.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Handle CSV import and export.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th November 2022
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

#include <rec/recCsv.h>

#include <rec/recDb.h>

#include <wx/dir.h>

#include <fstream>
#include <iostream>
#include <string>

using std::string;

template <class T>
bool WriteTableCsv( const string& csv_dir )
{
    string fname = csv_dir + T::TableName() + ".csv";
    std::ofstream ofile( fname, std::ios::trunc );
    if( !ofile ) {
        return false;
    }
    recIdVec list = T::AllIDs();
    ofile << T::CsvTitles();
    for( idt id : list ) {
        T::CsvWrite( ofile, id );
    }
    return true;
}

bool recExportCsv( const string& path )
{
    wxDir dir( path );
    if( dir.HasFiles() || dir.HasSubDirs() ) {
        return false;
    }
    string pathsep = dir.GetNameWithSep();
    bool ret = WriteTableCsv<recAssociate>( pathsep );
    // TODO: 
    return ret;
}
