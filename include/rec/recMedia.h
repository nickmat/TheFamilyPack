/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recMedia.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Media record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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

#ifndef RECMEDIA_H
#define RECMEDIA_H

#include <rec/recDatabase.h>

class recMedia : public recDb
{
public:
    recMedia() {}
    recMedia( idt id ) : recDb( id ) { Read(); }
    recMedia( const recMedia& name );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Media" );
    bool Equivalent( const recMedia& r2 ) const;

    idt FGetDataID() const { return f_data_id; }
    idt FGetAssID() const { return f_ass_id; }
    idt FGetRefID() const { return f_ref_id; }
    int FGetPrivacy() const { return f_privacy; }
    wxString FGetTitle() const { return f_title; }
    wxString FGetNote() const { return f_note; }

    void FSetDataID( idt dataID ) { f_data_id = dataID; }
    void FSetAssID( idt assID ) { f_ass_id = assID; }
    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetPrivacy( int privacy ) { f_privacy = privacy; }
    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt medID ) { return wxString::Format( "M" ID, medID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetTitle( idt medID );

private:
    idt      f_data_id;
    idt      f_ass_id;
    idt      f_ref_id;
    int      f_privacy;
    wxString f_title;
    wxString f_note;
};

inline bool operator==( const recMedia& r1, const recMedia& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recMedia& r1, const recMedia& r2 )
{
    return !( r1 == r2 );
}

#endif // RECMEDIA_H
