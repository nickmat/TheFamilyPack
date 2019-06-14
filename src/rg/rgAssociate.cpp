/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgAssociate.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit and create database Assicate database entity dialogs.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     12th June 2019
 * Copyright:   Copyright (c) 2019 Nick Matthews.
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

#include "rgAssociate.h"
#include "rg/rgDialogs.h"

#include <rec/recAssociate.h>
#include <wx/filename.h>

bool rgEditAssociate( wxWindow * wind )
{
    bool ret = false;
    idt assID = rgSelectAssociate( wind );

    if ( assID != 0 ) {
        const wxString savepoint = recDb::GetSavepointStr();
        recDb::Savepoint( savepoint );

        recAssociate ass( assID );
        wxTextEntryDialog assdlg( wind, _( "Database path:" ), _( "Create Associated Database" ) );
        assdlg.SetValue( ass.FGetPath() );

        if ( assdlg.ShowModal() == wxID_OK ) {
            ass.FSetPath( assdlg.GetValue() );
            ass.Save();
            recDb::ReleaseSavepoint( savepoint );
            ret = true;
        } else {
            recDb::Rollback( savepoint );
        }
    }
    return ret;
}

idt rgCreateAssociate( wxWindow* wind )
{
    wxString caption = _( "Select TFP Database to Associate" );
    wxString wildcard = _( "TFP Database (*.tfpd)|*.tfpd" );
    wxString defaultDir = ".";
    wxString defaultFName = wxEmptyString;

    wxFileDialog dialog( wind, caption, defaultDir, defaultFName, wildcard, wxFD_OPEN );
    if ( dialog.ShowModal() == wxID_OK ) {
        wxString path = dialog.GetPath();
        wxFileName fname( path );
        wxFileName basepath( recDb::GetFileName() );
        fname.MakeRelativeTo( basepath.GetPath() );
        fname.SetExt( "" );
        wxString dbname = fname.GetFullPath( wxPATH_UNIX );
        return recAssociate::Create( dbname );
    }
    return 0;
}

idt rgSelectAssociate( wxWindow* wind, unsigned flag, unsigned* retbutton )
{
    idt assID = 0;
    if ( retbutton ) *retbutton = rgSELSTYLE_None;
    rgDlgSelectAssociate dialog( wind, flag );

    bool cont = true;
    while ( cont ) {
        recAssociateVec vec = recAssociate::GetList();
        wxArrayString table;
        for ( auto ass : vec ) {
            table.push_back( ass.GetIdStr() );
            table.push_back( ass.FGetPath() );
        }
        dialog.SetTable( table );
        if ( vec.size() == 1 ) {
            dialog.SetSelectedRow( 0 );
        }
        if ( dialog.ShowModal() == wxID_OK ) {
            if ( dialog.GetCreatePressed() ) {
                assID = rgCreateAssociate( wind );
                if ( assID ) {
                    if ( retbutton ) *retbutton = rgSELSTYLE_Create;
                    cont = false;
                } else {
                    dialog.SetCreatePressed( false );
                }
                continue;
            }
            if ( dialog.GetUnknownPressed() ) {
                if ( retbutton ) *retbutton = rgSELSTYLE_Unknown;
                assID = 0;
                break;
            }
            size_t item = (size_t)dialog.GetSelectedRow();
            assID = vec[item].FGetID();
        }
        cont = false;
    }

    return assID;
}

//-------------------------------------------------------------------------------
//-------------------[ rgDlgSelectAssociate ]-----------------------------------------
//-------------------------------------------------------------------------------

wxString rgDlgSelectAssociate::sm_colHeaders[COL_MAX] = { _( "ID" ), _( "Path" ) };

// End of src/rg/rgAssociate.cpp file
