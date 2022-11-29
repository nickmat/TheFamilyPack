/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recInterface.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the rec lib command line or GUI interface functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22 October 2012
 * Copyright:   Copyright (c) 2012..2022, Nick Matthews.
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

#ifndef RECINTERFACE_H
#define RECINTERFACE_H

/*! Output a message for the correct environment.
 */
extern void recMessage( const wxString& mess, const wxString& func );

/*! Ask a Yes/No question for the correct environment.
 *  Return true for Yes, false for No or default_val if neither given.
 */
extern bool recPromptYesNo(
    const std::string& prompt, const std::string& title, bool default_val = false );

/*! On GUI, display and update a progress bar.
 */
extern void* recGetProgressDlg( const wxString& title, const wxString& message, int style );
extern bool recProgressPulse( void* progress, const wxString& message );
extern void recProgressSetRange( void* progress, int maximum );
extern bool recProgressUpdate( void* progress, int value, const wxString& message );
extern void recProgressClose( void* progress );

/*! On GUI, select an item from an offered list.
 */
extern int recGetSingleChoiceIndex( const wxString& caption, const wxArrayString& choices );

/*! On GUI, ask permission to upgrade database version.
 */
extern bool recPermissionToUpgrade( const wxString& from, const wxString& to );

#endif // RECINTERFACE_H
